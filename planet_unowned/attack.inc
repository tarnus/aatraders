<?php
include ("languages/$langdir/lang_attack.inc");
include ("globals/combat_functions.inc");
include ("globals/change_planet_ownership.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/collect_bounty.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/send_system_im.inc");
include ("globals/log_move.inc");
include ("globals/get_player.inc");
include ("globals/calc_ownership.inc");
include ("globals/gen_score.inc");
include ("globals/planet_log.inc");
include ("globals/insert_news.inc");
include ("globals/capture_planet_ships.inc");
include ("globals/get_rating_change.inc");
include ("globals/good_neutral_evil.inc");
include ("globals/artifacts_move.inc");
include ("globals/device_ship_tech_modify.inc");
include ("globals/display_this_planet.inc");
//error_reporting(E_ALL);
$template_object->enable_gzip = 0;

$shipinfo_old = $shipinfo;
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

// check sector defense
if($playerinfo['team'] == 0)
{
	$result3 = $db->Execute ("SELECT defense_type, SUM(quantity) as amount FROM {$db_prefix}sector_defense WHERE sector_id='$shipinfo[sector_id]' and player_id != '$playerinfo[player_id]' GROUP BY defense_type");
}
else
{
	$result3 = $db->Execute ("SELECT {$db_prefix}sector_defense.defense_type, SUM({$db_prefix}sector_defense.quantity) as amount FROM {$db_prefix}sector_defense, {$db_prefix}players WHERE {$db_prefix}sector_defense.sector_id='$shipinfo[sector_id]' and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]' and ({$db_prefix}players.player_id={$db_prefix}sector_defense.player_id and {$db_prefix}players.team != $playerinfo[team]) GROUP BY {$db_prefix}sector_defense.defense_type");
}
db_op_result($result3,__LINE__,__FILE__);

while (!$result3->EOF)
{
	$row = $result3->fields;
	$defenses[$row['defense_type']] = $row['amount'];

	$result3->MoveNext();
}
$result3->close();

$is_header = 0;

if ($defenses['fighters'] > 0 && $playerinfo['player_id'] != 3)
{
	unset($_SESSION['movedefense'], $movedefense);
	$destination=$shipinfo['sector_id'];
	include ("sector_defense/fighters.inc");
	$template_object->assign("error_msg", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($planetinfo['owner'] != 3)
{
	if ($playerinfo['turns'] < 1)
	{
		$template_object->assign("error_msg", $l_cmb_atleastoneturn);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attackdie.tpl");
		include ("footer.php");
		die();
	}

	$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$planetinfo[owner]'", 1);
	$targetinfo = $result2->fields;
	$result2->close();

	send_system_im($planetinfo['owner'], $l_planet_imtitleattack, $playerinfo['character_name'] . " $l_planet_imisattacking $planetinfo[name] $l_planet_iminsector $planetinfo[sector_name].", $targetinfo['last_login']);

	$result4 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	$shipsonplanet = 0;

	$onplanet = array();
	if ($result4->RecordCount() > 0)
	{
		$l_cmb_ships_are_landed = str_replace("[cmb_shipsonplanet]", $result4->RecordCount(), $l_cmb_ships_are_landed);
		$template_object->assign("l_cmb_ships_are_landed", $l_cmb_ships_are_landed);
		$template_object->assign("l_cmb_engshiptoshipcombat", $l_cmb_engshiptoshipcombat);

		$shiponplanet_list = array();
		while (!$result4->EOF)
		{
			$onplanet[$shipsonplanet] = $result4->fields;
			$shiponplanet_list[] = str_replace("[player]", $onplanet[$shipsonplanet]['name'], $l_cmb_approachattackvector);
			adminlog("LOG0_ADMIN_COMBAT","<font color=\"yellow\"><B>Landed Ship:</B></font><BR>" . print_r($onplanet[$shipsonplanet], true) . "<br>");
			$shipsonplanet++;
			$result4->MoveNext();
		}
		$result4->close();
		$template_object->assign("shiponplanet_list", $shiponplanet_list);
	}
	else
	{
		$template_object->assign("l_cmb_noshipslanded", $l_cmb_noshipslanded);
	}

	$template_object->assign("shipsonplanet", $shipsonplanet);

	// get attacker beam, shield and armor values
	$attacker_shield_energy = floor($shipinfo['energy'] * 0.4);
	$attacker_beam_energy = $shipinfo['energy'] - $attacker_shield_energy;

	$attackershields = NUM_SHIELDS($shipinfo['shields']);

	if ($attackershields < $attacker_shield_energy)
	{
		$attacker_shield_energy = $attackershields;
	}

	$attackerbeams = NUM_BEAMS($shipinfo['beams']);

	if ($attackerbeams < $attacker_beam_energy)
	{
		$attacker_beam_energy = $attackerbeams;
	}

	$attackerenergyset = $attacker_beam_energy + $attacker_shield_energy;
	$attackerstartenergy = ($attacker_beam_energy + $attacker_shield_energy);
	$attack_beamtofighter_dmg = floor($attacker_beam_energy * 0.05);
	$attacker_beam_energy -= $attack_beamtofighter_dmg;
	$attack_beamtotorp_dmg = floor($attacker_beam_energy * 0.05);
	$attacker_beam_energy -= $attack_beamtotorp_dmg;

	$attackertorps = $shipinfo['torps'];

	$attackerarmor = $shipinfo['armor_pts'];

	$attackerfighters = $shipinfo['fighters'];

	$attackerlowpercent = ecmcheck($shipinfo['sensors'], $shipinfo['sensors'], $full_attack_modifier);

	// get target beam, shield and armor values
	$target_shield_energy = floor($planetinfo['energy'] * 0.4);
	$target_beam_energy = $planetinfo['energy'] - $target_shield_energy;

	$base_factor = ($planetinfo['base'] == 'Y') ? max(round($basedefense * (1 - ($planetinfo['shields'] / ($max_tech_level / 2)))), 0) : 0;
	if ($planetinfo['shields'] == 0) 
	{
		$targetshields = 0;
	}
	else
	{
		$targetshields = NUM_SHIELDS($planetinfo['shields'] + $base_factor);
	}

	for($i = 0; $i < $shipsonplanet; $i++)
	{
		$targetshields += NUM_SHIELDS($onplanet[$i]['shields']);
	}

	$full_target_shield_energy = $target_shield_energy;

	if (($targetshields * $planet_shield_multiplier) < $target_shield_energy)
	{
		$target_shield_energy = $targetshields;
	}
	else
	{
		$target_shield_energy = floor($target_shield_energy / $planet_shield_multiplier);
	}

	$base_factor = ($planetinfo['base'] == 'Y') ? max(round($basedefense * (1 - ($planetinfo['beams'] / ($max_tech_level / 2)))), 0) : 0;
	if ($planetinfo['beams'] == 0) 
	{
		$targetbeams = 0;
	}
	else
	{
		$targetbeams = NUM_BEAMS($planetinfo['beams'] + $base_factor);
	}

	for($i = 0; $i < $shipsonplanet; $i++)
	{
		$targetbeams += NUM_BEAMS($onplanet[$i]['beams']);
	}

	if ($targetbeams < $target_beam_energy)
	{
		$target_beam_energy = $targetbeams;
	}

	$targetenergyset = ($target_shield_energy * $planet_shield_multiplier) + $target_beam_energy;

	$target_beamtofighter_dmg = floor($target_beam_energy * 0.05);
	$target_beam_energy -= $target_beamtofighter_dmg;
	$target_beamtotorp_dmg = floor($target_beam_energy * 0.05);
	$target_beam_energy -= $target_beamtotorp_dmg;

	$base_factor = ($planetinfo['base'] == 'Y') ? max(round($basedefense * (1 - ($planetinfo['torp_launchers'] / ($max_tech_level / 2)))), 0) : 0;
	$torp_launchers = NUM_TORPEDOES($planetinfo['torp_launchers'] + $base_factor) ;
	$torps = $planetinfo['torps'];

	for($i = 0; $i < $shipsonplanet; $i++)
	{
		$torps += $onplanet[$i]['torps'];  
		$ship_torps =  NUM_TORPEDOES($onplanet[$i]['torp_launchers']);
		$torp_launchers = $torp_launchers + $ship_torps;
	}
	if ($torp_launchers > $torps)
	{
		$targettorps = $torps;
	}
	else
	{
		$targettorps = $torp_launchers;
	}

	$targetarmor = $planetinfo['armor_pts'];

	$base_factor = ($planetinfo['base'] == 'Y') ? max(round($basedefense * (1 - ($planetinfo['fighter'] / ($max_tech_level / 2)))), 0) : 0;
	$planet_comp_level = NUM_FIGHTERS($planetinfo['fighter'] + $base_factor);
	$figs = $planetinfo['fighters'];
	for($i = 0; $i < $shipsonplanet; $i++)
	{
		$figs += $onplanet[$i]['fighters'];  
		$ship_comp =  NUM_FIGHTERS($onplanet[$i]['fighter']);  
		$planet_comp_level = $planet_comp_level + $ship_comp;  
	}

	if ($planet_comp_level > $figs)
	{
		$targetfighters = $figs;
	}
	else
	{
		$targetfighters = $planet_comp_level;
	}

	$targetlowpercent = ecmcheck($shipinfo['ecm'], $planetinfo['sensors'], -$full_attack_modifier);

	update_player_experience($playerinfo['player_id'], $attacking_planet);
	planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_ATTACKED");
	// Planetary defense system calculation

	// Begin actual combat calculations

	$targetshipshields = $planetinfo['shields'];
	$targetshiparmor = $planetinfo['armor'];
	$targetshiptorp_launchers = $planetinfo['torp_launchers'];
	$targetshipbeams = $planetinfo['beams'];
	$targetshipfighter = $planetinfo['fighter'];

	$planetinfoarmor_pts = $targetarmor;
	$planetinfofighters = $targetfighters;
	$planetinfotorps = $targettorps;
	$planetinfoenergy = ($target_beam_energy + $target_shield_energy);

	$targetname = "$l_cmb_planet " . $planetinfo['name'];

	if(!class_exists($shipinfo['fighter_class']))
	{
		include ("class/" . $shipinfo['fighter_class'] . ".inc");
	}

	$attackobject = new $shipinfo['fighter_class']();
	$fighter_damage_shields = $attackobject->fighter_damage_shields;
	$fighter_damage_all = $attackobject->fighter_damage_all;
	$fighter_hit_pts = $attackobject->fighter_hit_pts;

	if(!class_exists($shipinfo['beam_class']))
	{
		include ("class/" . $shipinfo['beam_class'] . ".inc");
	}

	$attackobject = new $shipinfo['beam_class']();
	$beam_damage_shields = $attackobject->beam_damage_shields;
	$beam_damage_all = $attackobject->beam_damage_all;

	if(!class_exists($shipinfo['torp_class']))
	{
		include ("class/" . $shipinfo['torp_class'] . ".inc");
	}

	$attackobject = new $shipinfo['torp_class']();
	$torp_damage_shields = $attackobject->torp_damage_shields;
	$torp_damage_all = $attackobject->torp_damage_all;
	$torp_hit_pts = $attackobject->torp_hit_pts;

	if(!class_exists($shipinfo['shield_class']))
	{
		include ("class/" . $shipinfo['shield_class'] . ".inc");
	}

	$attackobject = new $shipinfo['shield_class']();
	$ship_shield_hit_pts = $attackobject->ship_shield_hit_pts;

	if(!class_exists($shipinfo['armor_class']))
	{
		include ("class/" . $shipinfo['armor_class'] . ".inc");
	}

	$attackobject = new $shipinfo['armor_class']();
	$ship_armor_hit_pts = $attackobject->ship_armor_hit_pts;

	if(!class_exists($planetinfo['fighter_class']))
	{
		include ("class/planet/" . $planetinfo['fighter_class'] . ".inc");
	}

	$targetobject = new $planetinfo['fighter_class']();
	$fighter_damage_shields = $targetobject->damage_shields;
	$fighter_damage_all = $targetobject->damage_all;
	$fighter_hit_pts = $targetobject->hit_pts;

	if(!class_exists($planetinfo['beam_class']))
	{
		include ("class/planet/" . $planetinfo['beam_class'] . ".inc");
	}

	$targetobject = new $planetinfo['beam_class']();
	$beam_damage_shields = $targetobject->damage_shields;
	$beam_damage_all = $targetobject->damage_all;

	if(!class_exists($planetinfo['torp_class']))
	{
		include ("class/planet/" . $planetinfo['torp_class'] . ".inc");
	}

	$targetobject = new $planetinfo['torp_class']();
	$torp_damage_shields = $targetobject->damage_shields;
	$torp_damage_all = $targetobject->damage_all;
	$torp_hit_pts = $targetobject->hit_pts;

	if(!class_exists($planetinfo['shield_class']))
	{
		include ("class/planet/" . $planetinfo['shield_class'] . ".inc");
	}

	$targetobject = new $planetinfo['shield_class']();
	$ship_shield_hit_pts = $targetobject->hit_pts;

	if(!class_exists($planetinfo['armor_class']))
	{
		include ("class/planet/" . $planetinfo['armor_class'] . ".inc");
	}

	$targetobject = new $planetinfo['armor_class']();
	$ship_armor_hit_pts = $targetobject->hit_pts;

	// --------------------------------------------
	// execute attack exchange code

	$attacktype = "planet";
	include ("globals/attack_exchange.inc");

	// --------------------------------------------

	$template_object->assign("l_cmb_attack_exchange_results", $l_cmb_attack_exchange_results);

	if($targetinfo['player_id'] > 3)
	{
		$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_planet, $targetinfo['player_id']);
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
	}

	$attacker_armor_lost = max(0, $shipinfo['armor_pts'] - $attacker_armor_left);
	$attacker_fighters_lost = max(0, $shipinfo['fighters'] - $attacker_fighters_left);
	$attacker_torps_lost = max(0, $shipinfo['torps'] - $attacker_torps_left);
	$attacker_energy_lost = max(0, $attackerenergyset - ($attacker_energy_left + $attacker_shields_left));

	$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST(armor_pts - $attacker_armor_lost, 0), energy=GREATEST(energy - $attacker_energy_lost, 0), fighters=GREATEST(fighters - $attacker_fighters_lost, 0), torps=GREATEST(torps - $attacker_torps_lost, 0) WHERE ship_id=$shipinfo[ship_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$target_armor_lost = max(0, $planetinfoarmor_pts - $target_armor_left);
	$target_fighters_lost = max(0, $planetinfofighters - $target_fighters_left);
	$target_torps_lost = max(0, $planetinfotorps - $target_torps_left);
	$target_energy_lost = max(0, $targetenergyset - ($target_energy_left + ($target_shields_left * $planet_shield_multiplier)));

	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET armor_pts=GREATEST(armor_pts - $target_armor_lost, 0), energy=GREATEST(energy - $target_energy_lost, 0), fighters=GREATEST(fighters - $target_fighters_lost, 0), torps=GREATEST(torps - $target_torps_lost, 0) WHERE planet_id=$planetinfo[planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	if($shipsonplanet > 0)
	{
		$leftoverenergy = max(floor(($target_energy_lost - $planetinfo['energy']) / $shipsonplanet), 0);
		$leftoverfighters = max(floor(($target_fighters_lost - $planetinfo['fighters']) / $shipsonplanet), 0);
		$leftovertorps = max(floor(($target_torps_lost - $planetinfo['torps']) / $shipsonplanet), 0);
		for($i = 0; $i < $shipsonplanet; $i++)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET energy=GREATEST(energy - $leftoverenergy, 0), fighters=GREATEST(fighters - $leftoverfighters, 0), torps=GREATEST(torps - $leftovertorps, 0) WHERE ship_id=" . $onplanet[$i]['ship_id']);
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	} 

	$attacker_exchange_result = array();
	$target_exchange_result = array();

	if(($attacker_armor_left < 1 and $attacker_shields_left < 1) and ($target_armor_left < 1 and $target_shields_left < 1))
	{
		update_player_experience($playerinfo['player_id'], $losing_yourship);
		$target_exchange_result[] = str_replace("[planet]", $targetname, $l_cmb_planetnotdefeated);

		$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $targetname . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
		$target_exchange_result[] = $l_cmb_target_lost_list;
		playerlog($planetinfo['owner'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);
		playerlog($planetinfo['owner'], "LOG5_PLANET_NOT_DEFEATED", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]|$free_ore|$free_organics|$free_goods|$ship_salvage_rate|$ship_salvage");
		gen_score($planetinfo['owner']);

		if($planetinfo['owner'] != 2)
		{
			$playernames = $playerinfo['character_name']."|".get_player($planetinfo['owner']);
			insert_news($playernames, 1, "planetnotdefeated");
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		//	attacker_died
		$attacker_exchange_result[] = $l_cmb_attacker_ship_destroyed;
		if ($shipdevice['dev_escapepod']['amount'] == 1) 
		{
			$attacker_exchange_result[] = $l_cmb_escapepod_launched;
			player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], $targetinfo['player_id'], $targetinfo['rating'], "killedplanetpod");
			collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
		}
		else
		{
			$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
			db_kill_player($playerinfo['player_id'], $targetinfo['player_id'], $targetinfo['rating'], "killedplanet");
			collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
		}

		$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
		$template_object->assign("target_exchange_result", $target_exchange_result);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attack_exchange.tpl");
		include ("footer.php");
		die();
	}

	if(($attacker_armor_left < 1 and $attacker_shields_left < 1) or ($target_armor_left < 1 and $target_shields_left < 1))
	{
		if ($target_armor_left < 1 and $target_shields_left < 1)
		{
			//	target_died
			update_player_experience($planetinfo['owner'], $losing_planet);
			$attacker_exchange_result[] = str_replace("[planet]", $targetname, $l_cmb_planetdefeated);
			planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_DEFEATED");

			if ($shipsonplanet > 0)
			{
				$l_cmb_ships_were_landed = str_replace("[cmb_shipsonplanet]", $shipsonplanet, $l_cmb_ships_were_landed);
				$target_exchange_result[] = $l_cmb_ships_were_landed;

				for($i = 0; $i < $shipsonplanet; $i++)
				{
					$targetship = $onplanet[$i];

					$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$targetship[ship_id]", '', 'class');
					$targetship_old = $targetship;
					$targetship = device_ship_tech_modify($targetship, $targetshipdevice);
					$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$targetship[player_id]", 1);
					$targetshipplayerinfo = $result2->fields;
					$result2->close();

					// determine percent chance of success in detecting target ship - based on player's sensors and opponent's cloak 
					$targetcloak = floor($targetship['cloak'] * 0.75);
					$success = SCAN_SUCCESS($shipinfo['sensors'], $targetcloak, $shiptypes[$targetship['class']]['basehull']);
					$targetengines = floor($targetship['engines'] * 0.50);

					$flee = SCAN_SUCCESS($shipinfo['engines'], $targetengines, $shiptypes[$targetship['class']]['basehull']);
					$roll = mt_rand(1, 100);
					$roll2 = mt_rand(1, 100);

					if ($flee < $roll2)
					{
						$target_exchange_result[] = str_replace("[player]", $targetshipplayerinfo['character_name'], $l_cmb_outmanuvered);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($targetshipplayerinfo['player_id'], "LOG5_ATTACK_OUTMAN", "$playerinfo[character_name]");
						$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET on_planet='N', planet_id=0, storage_planet_id=0 WHERE ship_id=$targetship[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}else if ($roll > $success)
					{
						// if scan fails - inform both player and target. 
						$attacker_exchange_result[] = str_replace("[player]", $targetshipplayerinfo['character_name'], $l_cmb_attacker_scan_fail);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($targetshipplayerinfo['player_id'], "LOG5_ATTACK_OUTSCAN", "$playerinfo[character_name]");
						$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET on_planet='N', planet_id=0, storage_planet_id=0 WHERE ship_id=$targetship[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
					else
					{
						// if scan succeeds, show results and inform target. 
						$shipavg = $targetship['basehull'] + ($targetship['hull'] + $targetship['engines'] + $targetship['power'] + $targetship['fighter'] + $targetship['sensors'] + $targetship['beams'] + $targetship['torp_launchers'] + $targetship['shields'] + $targetship['cloak'] + $targetship['armor'] + $targetship['ecm']) / 11;
						if ($shipavg > $ewd_maxavgtechlevel)
						{
							$chance = round($shipavg / $max_tech_level) * 100;
						}
						else
						{
							$chance = 0;
						}

						$random_value = mt_rand(1,100);
						if (($targetshipdevice['dev_emerwarp']['amount'] > 0) && $random_value > $chance)
						{
							// need to change warp destination to random sector in universe 
							if($targetshipplayerinfo['player_id'] <= 3)
							{
								$rating_attack_ship = 0;
							}

							$rating_change=get_rating_change($playerinfo['rating'], $targetshipplayerinfo['rating'], $rating_attack_ship, $targetshipplayerinfo['player_id']);
							$source_sector = $shipinfo['sector_id'];
							$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 3 ORDER BY rand()", 1);
							$dest_sector = $findem->fields['sector_id'];

							$debug_query = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$source_sector", 1);
							db_op_result($debug_query,__LINE__,__FILE__);
							$zones = $debug_query->fields;
							$debug_query->close();

							$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1,rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
							db_op_result($debug_query,__LINE__,__FILE__);

							playerlog($targetshipplayerinfo['player_id'], "LOG5_ATTACK_EWD", "$playerinfo[character_name]");

							$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET planet_id=0, storage_planet_id=0, sector_id=$dest_sector, cleared_defenses=' ', on_planet='N' WHERE ship_id=$targetship[ship_id]");
							db_op_result($debug_query,__LINE__,__FILE__);
							$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
							db_op_result($debug_query,__LINE__,__FILE__);

							log_move($targetshipplayerinfo['player_id'],$targetship['ship_id'],$source_sector,$dest_sector,$shipinfo['class'],$shipinfo['cloak'],$zones['zone_id']);
							$target_exchange_result[] = str_replace("[player]", $targetshipplayerinfo['character_name'], $l_cmb_ewd_engaged);
						}
						else
						{
							$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_target_ship_destroyed);
							if ($targetshipdevice['dev_escapepod']['amount'] == 1)
							{
								$target_exchange_result[] = $l_cmb_escapepod_launched;
								player_ship_destroyed($targetship['ship_id'], $targetshipplayerinfo['player_id'], $targetshipplayerinfo['rating'], $playerinfo['player_id'], $playerinfo['rating'], "killedshippod");
								playerlog($targetshipplayerinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|Y");
								collect_bounty($playerinfo['player_id'],$targetshipplayerinfo['player_id']);
							}
							else
							{
								$target_exchange_result[] = str_replace("[player]", $targetshipplayerinfo['character_name'], $l_cmb_escapepod_failure);
								playerlog($targetshipplayerinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|N");
								db_kill_player($targetshipplayerinfo['player_id'], $playerinfo['player_id'], $playerinfo['rating'], "killedship");
								collect_bounty($playerinfo['player_id'],$targetshipplayerinfo['player_id']);
							}
						}
					}
				}
			}

			if($targetinfo['player_id'] <= 3)
			{
				$rating_defeat_planet = 0;
			}
			$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_defeat_planet, $targetinfo['player_id']);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			if ($min_value_capture != 0)
			{
				$returnscore = gen_score($playerinfo['player_id']);
				$planetplayerscore = $returnscore[0];

				if ($planetplayerscore < 1) 
				{
					$planetplayerscore = 1;
				}

				$planetscore = $planetinfo['organics'] * $organics_price + $planetinfo['ore'] * $ore_price + $planetinfo['goods'] * $goods_price + $planetinfo['energy'] * $energy_price + $planetinfo['fighters'] * $fighter_price + $planetinfo['torps'] * $torpedo_price + $planetinfo['colonists'] * $colonist_price + $planetinfo['credits'];
				$planetscore += ($planetinfo['base'] = 'Y' ? $base_credits : 0);
				$planetscore += $planetinfo['credits'] + $planetinfo['hidden_credits'];

				$planetscore2 = exp($planetinfo['fighter'] * log(max($planet_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['sensors'] * log(max($planet_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['beams'] * log(max($planet_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['torp_launchers'] * log(max($planet_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['shields'] * log(max($planet_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['jammer'] * log(max($planet_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['cloak'] * log(max($planet_upgrade_factor, 1)));

				$planetscore2 += exp($planetinfo['sector_defense_weapons'] * log(max($planet_SD_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['sector_defense_sensors'] * log(max($planet_SD_upgrade_factor, 1)));
				$planetscore2 += exp($planetinfo['sector_defense_cloak'] * log(max($planet_SD_upgrade_factor, 1)));
				$planetscore3 = $planetscore + ($planetscore2 * $upgrade_cost);
				$planetscore3 = sign($planetscore3) * ROUND(SQRT(ABS($planetscore3)));

				$isless = (($planetplayerscore / $planetscore3) > ($min_value_capture / 100)) ? "No" : "Yes";
				adminlog("LOG0_ADMIN_COMBAT","<font color=\"yellow\"><b>Planet Captured:</b></font><br>Attacker " . get_player($playerinfo['player_id']) . " (id: $playerinfo[player_id]) - Attacker Score: " . NUMBER($planetplayerscore) . "<br>
				Defender Planet: " . $planetinfo['name'] . " : $planetinfo[planet_id] (id: $planetinfo[owner] ($targetinfo[character_name])) Planet Score: " . NUMBER($planetscore3) . "<br>
				Planet min_value_capture: " . ($planetplayerscore / $planetscore3) . " > " . ($min_value_capture / 100) . " - Is Player less than min_value_capture: " . $isless . "<br>");

				if ($isless == "Yes")
				{
					planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_PLANET_DESTRUCT");
					$target_exchange_result[] = $l_cmb_citizenswanttodie;
					if ($enable_spies)
					{
						$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}planets.sector_id FROM {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id = {$db_prefix}planets.planet_id WHERE {$db_prefix}spies.planet_id = '$planetinfo[planet_id]' ");
						while (!$res->EOF)
						{
							$owners = $res->fields;
							playerlog($owners[owner_id], "LOG2_SPY_CATACLYSM", "$owners[spy_id]|$owners[name]|$owners[sector_id]");
							$res->MoveNext();
						}
						$res->close();
						$db->Execute("DELETE FROM {$db_prefix}spies WHERE planet_id = '$planetinfo[planet_id]' ");
					}
					capture_planet_ships($playerinfo['player_id'], $planetinfo['planet_id'], 1);
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}planets WHERE planet_id=$planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					playerlog($planetinfo['owner'], "LOG5_PLANET_DEFEATED_D", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
					adminlog("LOG0_ADMIN_PLANETDEL", "$playerinfo[character_name]|$ownerinfo[character_name]|$shipinfo[sector_id]");
					gen_score($planetinfo['owner']);
					calc_ownership($planetinfo['sector_id']); // Doesnt seem to run otherwise - per SF BUG # 588421
					$debug_query = $db->Execute("DELETE from {$db_prefix}dignitary WHERE planet_id = $planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("DELETE from {$db_prefix}autotrades WHERE planet_id = $planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					if($planetinfo['owner'] != 2)
					{
						$playernames = $playerinfo['character_name']."|".get_player($planetinfo['owner']);
						insert_news($playernames, 1, "planetdestroyed");
					}
					artifacts_move($planetinfo['planet_id'], 0, 0);
				}
				else
				{
					if($planetinfo['owner'] != 0 && $planetinfo['owner'] != 2 && $planetinfo['owner'] != 3)
					{
						update_player_experience($playerinfo['player_id'], $defeating_planet);
					}
					if($auto_capture_planets != 1)
					{
						$attacker_exchange_result[] = str_replace("[planet_id]", $planetinfo['planet_id'], $l_cmb_youmaycapture);
					}
					playerlog($ownerinfo['player_id'], "LOG5_PLANET_DEFEATED", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
					gen_score($ownerinfo['player_id']);

					if ($enable_spies)
					{
						$spies = $db->Execute("SELECT COUNT(spy_id) as total FROM {$db_prefix}spies WHERE active='Y' AND ship_id = '0' AND planet_id = $planetinfo[planet_id]");
						db_op_result($spies,__LINE__,__FILE__);
						$num_spies = $spies->RecordCount();
					}
					else
					{
						$num_spies = 0;
					}
					$new_age = ($display_percentage_age / 2) + mt_rand(0, $display_percentage_age);
					$capture_countdown = mt_rand(floor($capture_countdown_max / 3), $capture_countdown_max);
					$capture_quickfind = floor($planetinfo['credits'] * ((mt_rand(floor($capture_quickfind_percentage / 2), $capture_quickfind_percentage) + $num_spies) * 0.01));
					$hiddencredits = max($planetinfo['credits'] - $capture_quickfind, 0);
					$persuasion_countdown = mt_rand(floor($persuasion_countdown_max / 3), $persuasion_countdown_max);
					if($planetinfo['owner'] == 0)
					{
						$old_owner_rating = 0;
					}
					else
					{
						$old_rating = good_neutral_evil($planetinfo['owner']);
						$old_owner_rating = $old_rating[0];
					}

					$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET last_owner_rating = $old_owner_rating, persuasion_countdown = $persuasion_countdown, credits = $capture_quickfind, captured_countdown = $capture_countdown, hidden_credits = $hiddencredits, sector_defense_weapons=0, sector_defense_weapons_normal=0, sector_defense_sensors=0, sector_defense_sensors_normal=0, sector_defense_cloak=0, sector_defense_cloak_normal=0, use_age=$new_age, cargo_hull = 0, cargo_power = 0, base='N', defeated='Y' WHERE planet_id=$planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					$debug_query = $db->Execute("DELETE from {$db_prefix}dignitary WHERE planet_id = $planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("DELETE from {$db_prefix}autotrades WHERE planet_id = $planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$old_owner_id = $planetinfo['owner'];
				    change_planet_ownership($planetinfo['planet_id'],$old_owner_id,0);
					if($ownerinfo['player_id'] != 2)
					{
						$playernames = $playerinfo['character_name']."|".get_player($old_owner_id);
						insert_news($playernames, 1, "planetdefeated");
						if($targetinfo['home_planet_id'] == $planetinfo['planet_id'])
						{
							$reset_home_planet = "home_planet_id=0,";
						}
						else
						{
							$reset_home_planet = "";
						}
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET $reset_home_planet planets_lost=planets_lost+1, planet_update='Y' WHERE player_id=$old_owner_id");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
					if($auto_capture_planets == 1)
					{
						$attacker_exchange_result[] = $l_planet_captured;
						change_planet_ownership($planetinfo['planet_id'], 0, $playerinfo['player_id']);
						$new_age = ($display_percentage_age / 2) + mt_rand(0, $display_percentage_age);
						$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET sector_defense_weapons=0, sector_defense_weapons_normal=0, sector_defense_sensors=0, sector_defense_sensors_normal=0, sector_defense_cloak=0, sector_defense_cloak_normal=0, use_age=$new_age, cargo_hull = 0, cargo_power = 0, team=null, owner=$playerinfo[player_id], base='N', defeated='N' WHERE planet_id=$planetinfo[planet_id]");
						db_op_result($debug_query,__LINE__,__FILE__);

						$ownership = calc_ownership($shipinfo['sector_id']);

						if (!empty($ownership))
						{
							$attacker_exchange_result[] = $ownership;
						}

						$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$planetinfo[owner]", 1);
						$query = $res->fields;
						$res->close();
						$planetowner=$query['character_name'];
						playerlog($planetinfo['owner'],"LOG5_PLANET_YOUR_CAPTURED","$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
						planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_CAPTURE");
						playerlog($playerinfo['player_id'], "LOG5_PLANET_CAPTURED", "$planetinfo[colonists]|$planetinfo[credits]|$planetowner");
						capture_planet_ships($playerinfo['player_id'], $planetinfo['planet_id']);

						if(($planetinfo['team'] != $playerinfo['team'] && $playerinfo['team'] != 0) || $playerinfo['team'] == 0)
						{
							if($targetinfo['player_id'] <= 3)
							{
								$rating_capture_planet = 0;
							}
							$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_capture_planet, $targetinfo['player_id']);
							$debug_query = $db->Execute("UPDATE {$db_prefix}players SET captures=captures+1, rating=rating+$rating_change, planet_update='Y' WHERE player_id=$playerinfo[player_id]");
							db_op_result($debug_query,__LINE__,__FILE__);
						}
					}
				}
			}
			else
			{
				if($planetinfo['owner'] != 0 && $planetinfo['owner'] != 2 && $planetinfo['owner'] != 3)
				{
					update_player_experience($playerinfo['player_id'], $defeating_planet);
				}
				if($auto_capture_planets != 1)
				{
					$attacker_exchange_result[] = str_replace("[planet_id]", $planetinfo['planet_id'], $l_cmb_youmaycapture);
				}
				playerlog($ownerinfo['player_id'], "LOG5_PLANET_DEFEATED", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
				gen_score($ownerinfo['player_id']);

				if ($enable_spies)
				{
					$spies = $db->Execute("SELECT COUNT(spy_id) as total FROM {$db_prefix}spies WHERE active='Y' AND ship_id = '0' AND planet_id = $planetinfo[planet_id]");
					db_op_result($spies,__LINE__,__FILE__);
					$num_spies = $spies->RecordCount();
				}
				else
				{
					$num_spies = 0;
				}
				$new_age = ($display_percentage_age / 2) + mt_rand(0, $display_percentage_age);
				$capture_countdown = mt_rand(floor($capture_countdown_max / 3), $capture_countdown_max);
				$capture_quickfind = floor($planetinfo['credits'] * ((mt_rand(floor($capture_quickfind_percentage / 2), $capture_quickfind_percentage) + $num_spies) * 0.01));
				$hiddencredits = max($planetinfo['credits'] - $capture_quickfind, 0);
				$persuasion_countdown = mt_rand(floor($persuasion_countdown_max / 3), $persuasion_countdown_max);
				if($planetinfo['owner'] == 0)
				{
					$old_owner_rating = 0;
				}
				else
				{
					$old_rating = good_neutral_evil($planetinfo['owner']);
					$old_owner_rating = $old_rating[0];
				}

				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET last_owner_rating = $old_owner_rating, persuasion_countdown = $persuasion_countdown, credits = $capture_quickfind, captured_countdown = $capture_countdown, hidden_credits = $hiddencredits, sector_defense_weapons=0, sector_defense_weapons_normal=0, sector_defense_sensors=0, sector_defense_sensors_normal=0, sector_defense_cloak=0, sector_defense_cloak_normal=0, use_age=$new_age, cargo_hull = 0, cargo_power = 0, base='N', defeated='Y' WHERE planet_id=$planetinfo[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("DELETE from {$db_prefix}dignitary WHERE planet_id = $planetinfo[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE from {$db_prefix}autotrades WHERE planet_id = $planetinfo[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$old_owner_id = $planetinfo['owner'];
			    change_planet_ownership($planetinfo['planet_id'],$old_owner_id,0);
				if($ownerinfo['player_id'] != 2)
				{
					$playernames = $playerinfo['character_name']."|".get_player($old_owner_id);
					insert_news($playernames, 1, "planetdefeated");
					if($targetinfo['home_planet_id'] == $planetinfo['planet_id'])
					{
						$reset_home_planet = "home_planet_id=0,";
					}
					else
					{
						$reset_home_planet = "";
					}
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET $reset_home_planet planets_lost=planets_lost+1, planet_update='Y' WHERE player_id=$old_owner_id");
					db_op_result($debug_query,__LINE__,__FILE__);
				}
				if($auto_capture_planets == 1)
				{
					$attacker_exchange_result[] = $l_planet_captured;
					change_planet_ownership($planetinfo['planet_id'], 0, $playerinfo['player_id']);

					$new_age = ($display_percentage_age / 2) + mt_rand(0, $display_percentage_age);
					$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET sector_defense_weapons=0, sector_defense_weapons_normal=0, sector_defense_sensors=0, sector_defense_sensors_normal=0, sector_defense_cloak=0, sector_defense_cloak_normal=0, use_age=$new_age, cargo_hull = 0, cargo_power = 0, team=null, owner=$playerinfo[player_id], base='N', defeated='N' WHERE planet_id=$planetinfo[planet_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					$ownership = calc_ownership($shipinfo['sector_id']);

					if (!empty($ownership))
					{
						$attacker_exchange_result[] = $ownership;
					}

					$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$planetinfo[owner]", 1);
					$query = $res->fields;
					$res->close();
					$planetowner=$query['character_name'];
					playerlog($planetinfo['owner'],"LOG5_PLANET_YOUR_CAPTURED","$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
					planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_CAPTURE");
					playerlog($playerinfo['player_id'], "LOG5_PLANET_CAPTURED", "$planetinfo[colonists]|$planetinfo[credits]|$planetowner");
					capture_planet_ships($playerinfo['player_id'], $planetinfo['planet_id']);

					if(($planetinfo['team'] != $playerinfo['team'] && $playerinfo['team'] != 0) || $playerinfo['team'] == 0)
					{
						if($targetinfo['player_id'] <= 3)
						{
							$rating_capture_planet = 0;
						}
						$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_capture_planet, $targetinfo['player_id']);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET captures=captures+1, rating=rating+$rating_change, planet_update='Y' WHERE player_id=$playerinfo[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
				}
			}

			if($planetinfoarmor_pts > 0)
			{
				calc_internal_damage($planetinfo['planet_id'], 1, ($planetinfoarmor_pts-$target_armor_left) / $planetinfoarmor_pts);
			}
			else
			{
				calc_internal_damage($planetinfo['planet_id'], 1, 1);
			}

			$result = $db->SelectLimit("SELECT sector_defense_weapons, sector_defense_sensors, sector_defense_cloak, fighter, sensors, beams, torp_launchers, shields, cloak, jammer, armor FROM {$db_prefix}planets WHERE planet_id='$planetinfo[planet_id]'", 1);
			$afteractionplanettech = $result->fields;

			$build_log_entry = $l_cmb_planet_tech_drop;
			$build_log_entry=str_replace("[sector_defense_weapons]","<font color=\"#00ff00\">". $planetinfo['sector_defense_weapons'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_weapons_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_weapons'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_sensors]","<font color=\"#00ff00\">". $planetinfo['sector_defense_sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_cloak]","<font color=\"#00ff00\">". $planetinfo['sector_defense_cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $planetinfo['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionplanettech['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $planetinfo['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $planetinfo['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionplanettech['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $planetinfo['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionplanettech['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $planetinfo['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionplanettech['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $planetinfo['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[jammer]","<font color=\"#00ff00\">". $planetinfo['jammer'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[jammer_new]","<font color=\"#ff0000\">". $afteractionplanettech['jammer'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $planetinfo['armor'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionplanettech['armor'] . "</font>",$build_log_entry);
			playerlog($planetinfo['owner'], "LOG5_AFTER_ACTION", $build_log_entry);

			$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $planetinfo['name'] . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
			$target_exchange_result[] = $l_cmb_target_lost_list;
			playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);
		}
		else
		{
			$attacker_exchange_result[] = str_replace("[planet]", $targetname, $l_cmb_planetdefeated);

			if($planetinfoarmor_pts > 0)
			{
				calc_internal_damage($planetinfo['planet_id'], 1, ($planetinfoarmor_pts-$target_armor_left) / $planetinfoarmor_pts);
			}
			else
			{
				calc_internal_damage($planetinfo['planet_id'], 1, 1);
			}

			$result = $db->SelectLimit("SELECT sector_defense_weapons, sector_defense_sensors, sector_defense_cloak, fighter, sensors, beams, torp_launchers, shields, cloak, jammer, armor FROM {$db_prefix}planets WHERE planet_id='$planetinfo[planet_id]'", 1);
			$afteractionplanettech = $result->fields;

			$build_log_entry = $l_cmb_planet_tech_drop;
			$build_log_entry=str_replace("[sector_defense_weapons]","<font color=\"#00ff00\">". $planetinfo['sector_defense_weapons'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_weapons_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_weapons'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_sensors]","<font color=\"#00ff00\">". $planetinfo['sector_defense_sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_cloak]","<font color=\"#00ff00\">". $planetinfo['sector_defense_cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sector_defense_cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $planetinfo['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionplanettech['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $planetinfo['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $planetinfo['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionplanettech['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $planetinfo['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionplanettech['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $planetinfo['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionplanettech['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $planetinfo['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[jammer]","<font color=\"#00ff00\">". $planetinfo['jammer'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[jammer_new]","<font color=\"#ff0000\">". $afteractionplanettech['jammer'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $planetinfo['armor'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionplanettech['armor'] . "</font>",$build_log_entry);
			playerlog($planetinfo['owner'], "LOG5_AFTER_ACTION", $build_log_entry);

			$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $planetinfo['name'] . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
			$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
			$target_exchange_result[] = $l_cmb_target_lost_list;
			playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);
			playerlog($planetinfo['owner'], "LOG5_ATTACKED_WIN", "$playerinfo[character_name]|$armor_lost|$fighters_lost");
		}

		if ($attacker_armor_left < 1 and $attacker_shields_left < 1)
		{
			//	attacker_died
			update_player_experience($targetinfo['player_id'], $destroying_enemyship);
			update_player_experience($playerinfo['player_id'], $losing_yourship);
			$attacker_exchange_result[] = $l_cmb_attacker_ship_destroyed;
			if ($shipdevice['dev_escapepod']['amount'] == 1)
			{
				$attacker_exchange_result[] = $l_cmb_escapepod_launched;
				player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], $targetinfo['player_id'], $targetinfo['rating'], "killedplanetpod");
				collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
			}
			else
			{
				$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
				db_kill_player($playerinfo['player_id'], $targetinfo['player_id'], $targetinfo['rating'], "killedplanet");
				collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
			}

			$ship_value=$upgrade_cost*(round(mypw($upgrade_factor, $shipinfo_old['hull']))+round(mypw($upgrade_factor, $shipinfo_old['engines']))+round(mypw($upgrade_factor, $shipinfo_old['power']))+round(mypw($upgrade_factor, $shipinfo_old['fighter']))+round(mypw($upgrade_factor, $shipinfo_old['sensors']))+round(mypw($upgrade_factor, $shipinfo_old['beams']))+round(mypw($upgrade_factor, $shipinfo_old['torp_launchers']))+round(mypw($upgrade_factor, $shipinfo_old['shields']))+round(mypw($upgrade_factor, $shipinfo_old['armor']))+round(mypw($upgrade_factor, $shipinfo_old['cloak']))+round(mypw($upgrade_factor, $shipinfo_old['ecm'])));
			$ship_salvage_rate = mt_rand(10,20);
			$ship_salvage=$ship_value*$ship_salvage_rate/100;

			$l_cmb_target_salvage=str_replace("[ship_salvage_rate]","<font color=\"#00ff00\">". $ship_salvage_rate . "</font>",$l_cmb_target_salvage);
			$l_cmb_target_salvage=str_replace("[ship_salvage]","<font color=\"#00ff00\">". NUMBER($ship_salvage) . "</font>",$l_cmb_target_salvage);
			$l_cmb_target_salvage=str_replace("[name]","<font color=\"#00ffff\">". $targetinfo['character_name'] . "</font>",$l_cmb_target_salvage);
			$target_exchange_result[] = $l_cmb_target_salvage;
			playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_salvage);

			$debug_query = $db->Execute ("UPDATE {$db_prefix}planets SET credits=credits+$ship_salvage WHERE planet_id=$planetinfo[planet_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
			$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($attacker_fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
			$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
			$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($attacker_torps_lost) . "</font>",$l_cmb_attacker_lost_list);
			$attacker_exchange_result[] = $l_cmb_attacker_lost_list;
			playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);
		}
		else
		{
			if($attacker_armor_left > 0 && $attacker_armor_left < $shipinfo['armor_pts'])
			{
				calc_internal_damage($shipinfo['ship_id'], 0, ($shipinfo['armor_pts']-$attacker_armor_left) / $shipinfo['armor_pts']);
				$result = $db->SelectLimit("SELECT hull, engines, power, fighter, sensors, beams, torp_launchers, shields, cloak, ecm, armor FROM {$db_prefix}ships WHERE ship_id='$shipinfo[ship_id]'", 1);
				$afteractionshiptech = $result->fields;
				$attacker_exchange_result[] = $l_cmb_attacker_lost_tech;

				$build_log_entry = $l_cmb_attacker_tech_drop;
				$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
				playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

				if($afteractionshiptech['hull'] < $shipinfo_old['hull'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['engines'] < $shipinfo_old['engines'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['power'] < $shipinfo_old['power'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['fighter'] < $shipinfo_old['fighter'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['sensors'] < $shipinfo_old['sensors'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['beams'] < $shipinfo_old['beams'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['torp_launchers'] < $shipinfo_old['torp_launchers'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['shields'] < $shipinfo_old['shields'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['cloak'] < $shipinfo_old['cloak'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['ecm'] < $shipinfo_old['ecm'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				if($afteractionshiptech['armor'] < $shipinfo_old['armor'])
				{
					$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$l_cmb_attacker_tech_drop);
				}
				else
				{
					$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
					$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
				}

				$attacker_exchange_result[] = $l_cmb_attacker_tech_drop;
			}

			if($targetinfo['player_id'] <= 3)
			{
				$rating_attack_ship = 0;
			}
			$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship, $targetinfo['player_id']);
			$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
			$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($attacker_fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
			$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
			$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($attacker_torps_lost) . "</font>",$l_cmb_attacker_lost_list);
			$attacker_exchange_result[] = $l_cmb_attacker_lost_list;
			playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);
		}

		$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
		$template_object->assign("target_exchange_result", $target_exchange_result);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attack_exchange.tpl");

		include ("footer.php");
		die();
	}

	// both players bounced

	$target_exchange_result[] = str_replace("[planet]", $targetname, $l_cmb_planetnotdefeated);

	if($planetinfoarmor_pts > 0)
	{
		calc_internal_damage($planetinfo['planet_id'], 1, ($planetinfoarmor_pts-$target_armor_left) / $planetinfoarmor_pts);

		$result = $db->SelectLimit("SELECT sector_defense_weapons, sector_defense_sensors, sector_defense_cloak, fighter, sensors, beams, torp_launchers, shields, cloak, jammer, armor FROM {$db_prefix}planets WHERE planet_id='$planetinfo[planet_id]'", 1);
		$afteractionplanettech = $result->fields;

		$build_log_entry = $l_cmb_planet_tech_drop;
		$build_log_entry=str_replace("[sector_defense_weapons]","<font color=\"#00ff00\">". $planetinfo['sector_defense_weapons'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sector_defense_weapons_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_weapons'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sector_defense_sensors]","<font color=\"#00ff00\">". $planetinfo['sector_defense_sensors'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sector_defense_sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_sensors'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sector_defense_cloak]","<font color=\"#00ff00\">". $planetinfo['sector_defense_cloak'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sector_defense_cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_cloak'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $planetinfo['fighter'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionplanettech['fighter'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $planetinfo['sensors'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sensors'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $planetinfo['beams'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionplanettech['beams'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $planetinfo['torp_launchers'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionplanettech['torp_launchers'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $planetinfo['shields'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionplanettech['shields'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $planetinfo['cloak'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['cloak'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[jammer]","<font color=\"#00ff00\">". $planetinfo['jammer'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[jammer_new]","<font color=\"#ff0000\">". $afteractionplanettech['jammer'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $planetinfo['armor'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionplanettech['armor'] . "</font>",$build_log_entry);
		playerlog($planetinfo['owner'], "LOG5_AFTER_ACTION", $build_log_entry);
	}

	playerlog($planetinfo['owner'], "LOG5_PLANET_BOMBED", "$targetname|$shipinfo[sector_id]|$playerinfo[character_name]|$energy_lost|$torps_lost|$fighters_lost");
	$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $planetinfo['name'] . "</font>",$l_cmb_target_lost_list);
	$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
	$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
	$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
	$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
	$target_exchange_result[] = $l_cmb_target_lost_list;
	playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);

	if($attacker_armor_left > 0 && $attacker_armor_left < $shipinfo['armor_pts'])
	{
		calc_internal_damage($shipinfo['ship_id'], 0, ($shipinfo['armor_pts']-$attacker_armor_left) / $shipinfo['armor_pts']);
		$result = $db->SelectLimit("SELECT hull, engines, power, fighter, sensors, beams, torp_launchers, shields, cloak, ecm, armor FROM {$db_prefix}ships WHERE ship_id='$shipinfo[ship_id]'", 1);
		$afteractionshiptech = $result->fields;
		$attacker_exchange_result[] = $l_cmb_attacker_lost_tech;

		$build_log_entry = $l_cmb_attacker_tech_drop;
		$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
		$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
		playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

		if($afteractionshiptech['hull'] < $shipinfo_old['hull'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['engines'] < $shipinfo_old['engines'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['power'] < $shipinfo_old['power'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['fighter'] < $shipinfo_old['fighter'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['sensors'] < $shipinfo_old['sensors'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['beams'] < $shipinfo_old['beams'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['torp_launchers'] < $shipinfo_old['torp_launchers'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['shields'] < $shipinfo_old['shields'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['cloak'] < $shipinfo_old['cloak'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['ecm'] < $shipinfo_old['ecm'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		if($afteractionshiptech['armor'] < $shipinfo_old['armor'])
		{
			$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$l_cmb_attacker_tech_drop);
		}
		else
		{
			$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
			$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
		}

		$attacker_exchange_result[] = $l_cmb_attacker_tech_drop;
	}

	if($targetinfo['player_id'] <= 3)
	{
		$rating_attack_ship = 0;
	}
	$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship, $targetinfo['player_id']);
	$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
	$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($attacker_fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
	$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
	$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($attacker_torps_lost) . "</font>",$l_cmb_attacker_lost_list);
	$attacker_exchange_result[] = $l_cmb_attacker_lost_list;
	playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);

	$attacker_exchange_result[] = "<a href=\"planet.php?planet_id=$planet_id\">$l_clickme</a> $l_toplanetmenu";

	$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
	$template_object->assign("target_exchange_result", $target_exchange_result);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attack_exchange.tpl");

	include ("footer.php");
	die();
}
else
{
	$attacker_exchange_result[] = $l_command_no;
	$target_exchange_result[] = "<a href=\"planet.php?planet_id=$planet_id\">$l_clickme</a> $l_toplanetmenu";

	$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
	$template_object->assign("target_exchange_result", $target_exchange_result);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attack_exchange.tpl");

	include ("footer.php");
	die();
}

?>