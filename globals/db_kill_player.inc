<?php
include ("globals/calc_ownership.inc");
include ("globals/planet_log.inc");
include ("globals/insert_news.inc");
include ("globals/good_neutral_evil.inc");
include ("globals/get_rating_change.inc");
include ("globals/artifacts_move.inc");

if (!function_exists('db_kill_player')) {

	function db_kill_player($player_id, $killer_id, $killer_rating, $kill_type = "killed", $is_SD = "N")
	{
		global $default_prod_ore, $default_prod_organics, $default_prod_goods, $default_prod_energy;
		global $default_prod_fighters, $default_prod_torp, $rating_destroy_ship;
		global $db, $db_prefix;
		global $langdir, $l_unknown, $l_player;
		global $enable_spies; // Used for spies

		$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$player_id'", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$killedplayer = $debug_query->fields;
		$debug_query->close();

		$debug_query2 = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE ship_id=$killedplayer[currentship]", 1);
		db_op_result($debug_query2,__LINE__,__FILE__);
		$destroyed_ship_info = $debug_query2->fields;
		$debug_query2->close();
		$average_stats = floor((($destroyed_ship_info['hull'] + $destroyed_ship_info['cloak'] + $destroyed_ship_info['sensors'] + $destroyed_ship_info['power'] + $destroyed_ship_info['engines'] + $destroyed_ship_info['fighter'] + $destroyed_ship_info['armor'] + $destroyed_ship_info['shields'] + $destroyed_ship_info['beams'] + $destroyed_ship_info['torp_launchers'] + $destroyed_ship_info['ecm'] ) / 11 ) * $destroyed_ship_info['basehull'] * 0.025);

		if($killer_id > 3 && $is_SD == "N" && $player_id > 3){
			$rating_change=get_rating_change($killer_rating, $killedplayer['rating'], $rating_destroy_ship);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET kill_efficiency=kill_efficiency+$average_stats, rating=rating+$rating_change, kills=kills+1 WHERE player_id=$killer_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET destroyed='Y', profile_cached='Y', death_type='$kill_type' WHERE player_id='$killedplayer[player_id]'");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("DELETE FROM {$db_prefix}casino_topics WHERE post_player_id=$killedplayer[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("DELETE FROM {$db_prefix}casino_posts WHERE post_player_id=$killedplayer[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("DELETE FROM {$db_prefix}casino_posts_text WHERE post_player_id=$killedplayer[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if($killedplayer['player_id'] == $killedplayer['team']){
			$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$killedplayer[team]", 1);
			$team = $result_team->fields;
			$result_team->close();
			$res = $db->SelectLimit("SELECT COUNT(*) as number_of_members
						FROM {$db_prefix}players
						WHERE team = $team[creator]", 1);
			db_op_result($res,__LINE__,__FILE__);

			if ($res->fields['number_of_members'] == 1) {
				$res->close();
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_players WHERE player_id=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->SelectLimit("SELECT forum_id FROM {$db_prefix}team_forums WHERE teams=$killedplayer[player_id]", 1);
	  			db_op_result($debug_query,__LINE__,__FILE__);
		 		$forum_id = $debug_query->fields['forum_id'];
				$debug_query->close();
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_topics WHERE forum_id=$forum_id");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_posts WHERE forum_id=$forum_id");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_posts_text WHERE forum_id=$forum_id");
  				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forums WHERE teams=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("DELETE FROM {$db_prefix}teams WHERE id=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}zones WHERE owner=$killedplayer[player_id] and team_zone='Y'");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='0' WHERE player_id='$killedplayer[player_id]'");
  				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE team_invite=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team=0 WHERE owner=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			} else {
				$res->close();
		 		$res = $db->SelectLimit("SELECT player_id FROM {$db_prefix}players WHERE team=$killedplayer[player_id] and player_id != $killedplayer[player_id]", 1);
				$newcreator = $res->fields['player_id'];
				$res->close();

				$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$newcreator", 1);
				$newcreatorname = $res->fields;
				$res->close();
	  			$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_players WHERE player_id=$killedplayer[player_id]");
		 		db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}team_forums SET teams=$newcreator WHERE teams=$killedplayer[player_id]");
			 	db_op_result($debug_query,__LINE__,__FILE__);
				$stamp = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='0', last_team=$killedplayer[player_id], left_team_time='$stamp' WHERE player_id='$killedplayer[player_id]'");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE team_invite=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
 				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team=$newcreator WHERE team=$killedplayer[player_id]");
		 		db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}teams SET creator=$newcreator,id=$newcreator WHERE id=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
	 			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team=$newcreator WHERE team=$killedplayer[player_id]");
		 		db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team=0 WHERE owner=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("UPDATE {$db_prefix}zones SET owner=$newcreator WHERE team_zone='Y' AND owner=$killedplayer[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				playerlog($newcreator, "LOG0_TEAM_LEAD","$team[team_name]");
			}
		}

		$result1 = $db->Execute("SELECT * from {$db_prefix}planets where owner = '$player_id' ");
		db_op_result($result1,__LINE__,__FILE__);

		if ($result1 > 0)
		{
			while (!$result1->EOF)
			{
				$row = $result1->fields;
				$result2 = $db->Execute("SELECT * from {$db_prefix}ships where on_planet = 'Y' and planet_id = '$row[planet_id]' and player_id <> '$player_id' ");
				db_op_result($result2,__LINE__,__FILE__);
				if ($result2 > 0)
				{
					while (!$result2->EOF )
					{
						$cur = $result2->fields;
						$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet = 'N',planet_id = '0' WHERE ship_id='$cur[ship_id]'");
						db_op_result($debug_query,__LINE__,__FILE__);

						playerlog($cur[player_id], "LOG0_PLANET_EJECT", "$cur[sector_id]|$row[character_name]");
						$result2->MoveNext();
					}
				}
				$result2->close();
				$result1->MoveNext();
			}
		}
		$result1->close();

/*		$result1 = $db->Execute("SELECT ship_id from {$db_prefix}ships where player_id = '$player_id' ");
		db_op_result($result1,__LINE__,__FILE__);

		if ($result1 > 0)
		{
			while (!$result1->EOF)
			{
				$ship_id = $result1->fields['ship_id'];
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id=$ship_id");
				db_op_result($debug_query,__LINE__,__FILE__);
				$result1->MoveNext();
			}
		}
*/
		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet='N',sector_id=1,cleared_defenses=' ' WHERE player_id=$player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=0 WHERE player_id=$player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("DELETE from {$db_prefix}bounty WHERE placed_by = $player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		// If I lost my ship, all spies on it are killed and the spy owners will get log messages about it.
		if ($enable_spies)
		{
			$debug_query = $db->SelectLimit("SELECT ship_id FROM {$db_prefix}ships WHERE player_id = $player_id", 1);
			db_op_result($debug_query,__LINE__,__FILE__);
			$ship_id = $debug_query->fields['ship_id'];
			$debug_query->close();

			$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}players.character_name, {$db_prefix}ships.name AS ship_name FROM {$db_prefix}ships INNER JOIN {$db_prefix}players ON {$db_prefix}ships.player_id = {$db_prefix}players.player_id INNER JOIN {$db_prefix}spies ON {$db_prefix}spies.ship_id = {$db_prefix}ships.ship_id  WHERE {$db_prefix}spies.ship_id = $ship_id "); 
			if ($res)
			{
				while (!$res->EOF)
				{
					$owners = $res->fields;
					playerlog($owners['owner_id'], "LOG2_SHIPSPY_CATACLYSM", "$owners[spy_id]|$owners[character_name]|$owners[ship_name]");
					$res->MoveNext();
				}
			}
			$res->close();

			$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $ship_id "); 
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE owner_id = $player_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if ($enable_dignitaries)
		{
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE owner_id = $player_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$debug_query = $db->Execute("SELECT DISTINCT sector_id FROM {$db_prefix}planets WHERE owner='$player_id' AND base='Y'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$i = 0;

		while (!$debug_query->EOF && $debug_query)
		{
			$sectors[$i] = $debug_query->fields['sector_id'];
			$i++;
			$debug_query->MoveNext();
		}
		$debug_query->close();

		if (!empty($sectors))
		{
			foreach($sectors as $sector)
			{
				calc_ownership($sector);
			}
		}

		$debug_query = $db->Execute("SELECT planet_id FROM {$db_prefix}planets WHERE owner='$player_id'");
		while (!$debug_query->EOF && $debug_query)
		{
			planet_log($debug_query->fields['planet_id'],$player_id,$player_id,"PLOG_OWNER_DEAD");
			$debug_query->MoveNext();
		}
		$debug_query->close();

		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET cargo_hull=0,cargo_power=0,owner=2,team=0, base='N' WHERE owner=$player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query  = $db->Execute("SELECT ship_id FROM {$db_prefix}ships WHERE player_id=$player_id and storage_planet_id != 0");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($debug_query > 0)
		{
			while (!$debug_query->EOF)
			{
				$ship_id = $debug_query->fields['ship_id'];
				$debug_query2 = $db->Execute("UPDATE {$db_prefix}ships SET player_id = 2 WHERE ship_id='$ship_id'");
				db_op_result($debug_query2,__LINE__,__FILE__);
				$debug_query->MoveNext();
			}
		}
		$debug_query->close();

		$debug_query = $db->Execute("DELETE FROM {$db_prefix}autotrades WHERE owner = $player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense where player_id=$player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("DELETE FROM {$db_prefix}probe where owner_id=$player_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}zones WHERE team_zone='N' AND owner=$player_id", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$zone = $debug_query->fields;
		$debug_query->close();

		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=1 WHERE zone_id=$zone[zone_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$rating_type = good_neutral_evil($killedplayer['rating']);
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}dead_players (player_id, character_name, credits, turns_used, signup_date, last_login,
			rating, score, kills, deaths, captures, planets_built, planets_lost, profile_name, profile_password, profile_id, ip_address, ship_losses,
			experience, player_total_online, death_type) 
			VALUES 
			('$killedplayer[player_id]', " . $db->qstr($killedplayer['character_name']) . ", '$killedplayer[credits]', '$killedplayer[turns_used]', '$killedplayer[signup_date]', '$killedplayer[last_login]',
			'$rating_type[0]', '$killedplayer[score]', '$killedplayer[kills]', '$killedplayer[deaths]', '$killedplayer[captures]', '$killedplayer[planets_built]', '$killedplayer[planets_lost]', '$killedplayer[profile_name]', '$killedplayer[profile_password]', '$killedplayer[profile_id]', '$killedplayer[ip_address]', '$killedplayer[ship_losses]',
			'$killedplayer[experience]', '$killedplayer[player_total_online]', '$kill_type')");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("insert into {$db_prefix}dead_player_admin_extended_logging SELECT * FROM {$db_prefix}admin_extended_logging WHERE player_id=$killedplayer[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("insert into {$db_prefix}dead_player_logs SELECT * FROM {$db_prefix}logs WHERE player_id=$killedplayer[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if($killer_id > 3 && $is_SD == "N" && $player_id > 3){
			$debug_query = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id='$killer_id'", 1);
			db_op_result($debug_query,__LINE__,__FILE__);
			$name = $debug_query->fields['character_name'];
			$debug_query->close();
		}
		else
		{
			$name = "??????";
		}

		insert_news("$killedplayer[character_name]|$name", $player_id, $kill_type);
		artifacts_move(0, $killedplayer['player_id'], $killer_id);
	}
}
?>
