<?php
include ("globals/insert_news.inc");
include ("globals/artifacts_move.inc");

if (!function_exists('player_ship_destroyed')) {

	function player_ship_destroyed($ship_id, $target_id, $target_rating, $killer_id, $killer_rating, $kill_type = "nodisplay", $is_SD = "N"){

		global $db, $db_prefix, $start_armor, $start_energy, $start_fighters, $deathlostpercent;
		global $enable_dignitaries, $enable_spies, $start_ship_class, $rating_destroy_ship, $l_unknown, $l_player;

		if ($enable_dignitaries){
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $ship_id "); 
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if ($enable_spies){
			if ($killer_id)
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET active ='N', job_id = '0', spy_percent = '0.0', planet_id='0' WHERE ship_id = $ship_id AND owner_id = $killer_id"); 
				db_op_result($debug_query,__LINE__,__FILE__);
			}

			$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}players.character_name, {$db_prefix}ships.name AS ship_name FROM {$db_prefix}ships INNER JOIN {$db_prefix}players ON {$db_prefix}ships.player_id = {$db_prefix}players.player_id INNER JOIN {$db_prefix}spies ON {$db_prefix}spies.ship_id = {$db_prefix}ships.ship_id  WHERE {$db_prefix}spies.ship_id = $ship_id "); 
			while (!$res->EOF)
			{
				$owners = $res->fields;
				if($owners['owner_id'] != $target_id)
				{
					playerlog($owners['owner_id'], "LOG2_SHIPSPY_CATACLYSM", "$owners[spy_id]|$owners[character_name]|$owners[ship_name]");
				}
				$res->MoveNext();
			}
			$res->close();

			$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $ship_id "); 
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$debug_query = $db->Execute("DELETE FROM {$db_prefix}probe WHERE ship_id = $ship_id and active='P'"); 
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE currentship=$ship_id", 1);
		db_op_result($debug_query,__LINE__,__FILE__);

		$home_planet_id = $debug_query->fields['home_planet_id'];
		$player_id = $debug_query->fields['player_id'];
		$targetname = $debug_query->fields['character_name'];
		$credits = $debug_query->fields['credits'];
		$shiplosses = $debug_query->fields['ship_losses'];
		$debug_query->close();

		$debug_query2 = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE ship_id=$ship_id", 1);
		db_op_result($debug_query2,__LINE__,__FILE__);
		$class = $debug_query2->fields['class'];
		$destroyed_ship_info = $debug_query2->fields;
		$debug_query2->close();
		$average_stats = floor((($destroyed_ship_info['hull'] + $destroyed_ship_info['cloak'] + $destroyed_ship_info['sensors'] + $destroyed_ship_info['power'] + $destroyed_ship_info['engines'] + $destroyed_ship_info['fighter'] + $destroyed_ship_info['armor'] + $destroyed_ship_info['shields'] + $destroyed_ship_info['beams'] + $destroyed_ship_info['torp_launchers'] + $destroyed_ship_info['ecm'] ) / 11 ) * $destroyed_ship_info['basehull'] * 0.025);

		$price_modifier_base = explode("|", $shiplosses);
		for($i = 0; $i < count($price_modifier_base); $i++){
			$items = explode("-", $price_modifier_base[$i]);
			$element = $items[0];
			$price_modifier[$element] = $items[1];
			if($price_modifier[$element] < 1)
				$price_modifier[$element] = 0;
		}

		$res = $db->Execute("SELECT type_id FROM {$db_prefix}ship_types WHERE buyable = 'Y'");
		$type_count = $res->RecordCount(); 

		$new_losses = "";
		for($i = 0; $i < $type_count; $i++){
			$element = $res->fields['type_id'];
			if($price_modifier[$element] < 1)
				$price_modifier[$element] = 0;
			if($element == $class)
				$price_modifier[$element]++;
			$new_losses .= $element . "-" . ($price_modifier[$element]);
			if($i != ($type_count - 1))
				$new_losses .= "|";
			$res->MoveNext();
		}
		$res->close();

		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id = $start_ship_class", 1);
		db_op_result($res,__LINE__,__FILE__);
		$shipdata = $res->fields;
		$res->close();

		$res = $db->SelectLimit("SELECT sector_id, owner FROM {$db_prefix}planets WHERE planet_id = $home_planet_id", 1);
		db_op_result($res,__LINE__,__FILE__);
		$home_planet_owner = $res->fields['owner'];
		$home_planet_sector_id = $res->fields['sector_id'];
		$is_homeplanet = $res->RecordCount();
		$res->close();

		if($home_planet_owner != $player_id || $home_planet_id == 0 || $is_homeplanet != 1)
		{
			$respawn_sector = 1;
			$onplanet = "N";
			$onplanet_id = 0;
		}
		else
		{
			$respawn_sector = $home_planet_sector_id;
			$onplanet = "Y";
			$onplanet_id = $home_planet_id;
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET class=$start_ship_class, basehull=$shipdata[basehull], hull=$shipdata[minhull],engines=$shipdata[minengines],
									power=$shipdata[minpower],sensors=$shipdata[minsensors],fighter=$shipdata[minfighter],beams=$shipdata[minbeams],torp_launchers=$shipdata[mintorp_launchers],torps=0,armor=$shipdata[minarmor],armor_pts=$start_armor,cloak=$shipdata[mincloak],
									shields=$shipdata[minshields],ecm=$shipdata[minecm],sector_id=$respawn_sector,energy=$start_energy,fighters=$start_fighters, on_planet='$onplanet', planet_id=$onplanet_id, storage_planet_id=0,
									hull_normal=$shipdata[minhull],engines_normal=$shipdata[minengines],power_normal=$shipdata[minpower],sensors_normal=$shipdata[minsensors],fighter_normal=$shipdata[minfighter],beams_normal=$shipdata[minbeams],
									torp_launchers_normal=$shipdata[mintorp_launchers],armor_normal=$shipdata[minarmor],cloak_normal=$shipdata[mincloak],shields_normal=$shipdata[minshields], ecm_normal=$shipdata[minecm] 
									WHERE ship_id=$ship_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount = 0 WHERE ship_id=$ship_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount = 0 WHERE ship_id=$ship_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET destroyed='K', ship_losses='$new_losses', deaths=deaths+1 WHERE player_id=$target_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		if($killer_id > 3 && $is_SD == "N" && $target_id > 3){
			$rating_change=get_rating_change($killer_rating, $target_rating, $rating_destroy_ship);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET kill_efficiency=kill_efficiency+$average_stats, rating=rating+$rating_change, kills=kills+1 WHERE player_id=$killer_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$flag = 0;

		$amount = round($credits * (mt_rand(($deathlostpercent / 2), $deathlostpercent) / 100));

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$amount WHERE player_id=$player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$result4 = $db->Execute(" SELECT classname, success, trigger_value, enable  FROM {$db_prefix}class_modules_debris WHERE enable=1 and destroyship_debris=1");
		db_op_result($result4,__LINE__,__FILE__);
		$debris_info = $result4->GetArray();
		$debris_count = count($debris_info);
		$result4->close();

		$debris_type = "ship_credits";

		$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe ORDER BY rand()", 1);
		$targetlink = $findem->fields['sector_id'];

		$debug_query = $db->Execute("INSERT INTO {$db_prefix}debris (debris_type, debris_data, sector_id) values ('$debris_type','$amount', $targetlink)");
		db_op_result($debug_query,__LINE__,__FILE__);

		$result4 = $db->SelectLimit("SELECT MAX(sh.hull) AS hull_max, MAX(sh.ecm) AS ecm_max, MAX(sh.cloak) AS cloak_max, MAX(sh.armor) AS armor_max, MAX(sh.shields) AS shields_max, MAX(sh.engines) AS engines_max, MAX(sh.power) AS power_max, MAX(sh.fighter) AS fighter_max, MAX(sh.sensors) AS sensors_max, MAX(sh.beams) AS beams_max, MAX(sh.torp_launchers) AS torp_launchers_max FROM {$db_prefix}ships as sh,  {$db_prefix}players as pl where pl.player_id=sh.player_id and pl.npc=0", 1);
		db_op_result($result4,__LINE__,__FILE__);
		$max_list = $result4->fields;
		$result4->close();

		for($ii = 0; $ii < $debris_count; $ii++)
		{
			$success = mt_rand(0, $debris_info[$debris_count]['success']);
			if ($success == $debris_info[$debris_count]['trigger_value'] && $debris_info[$debris_count]['enable'] != 0)
			{
				$flag = 1;
				$debris_type = $debris_info[$debris_count]['classname'];
				if(!class_exists($debris_type)){
					include ("class/debris/" . $debris_type . ".inc");
				}
				$debrisobject = new $debris_type();
				$debris_data = $debrisobject->destroyship_debris_code($max_list, $destroyed_ship_info);
				if($flag == 1)
					$ii = $debris_count;
			}
		}

		if ($flag == 1)
		{
			$randplay=mt_rand(0,($totrecs-1));
			$targetlink = $getit[$randplay]['sector_id'];
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}debris (debris_type, debris_data, sector_id) values ('$debris_type','$debris_data', $targetlink)");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if($kill_type != "nodisplay")
		{
			if($killer_id != 0){
				$debug_query = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id='$killer_id'", 1);
				db_op_result($debug_query,__LINE__,__FILE__);
				$name = $debug_query->fields['character_name'];
				$debug_query->close();
			}
			else
			{
				$name = "??????";
			}
			insert_news("$targetname|$name", $target_id, $kill_type);
		}

		artifacts_move(0, $player_id, $killer_id);
	}
}
?>
