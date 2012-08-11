<?php

include ("languages/$langdir/lang_combat.inc");
include ("globals/combat_functions.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/collect_bounty.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/send_system_im.inc");
include ("globals/planet_log.inc");
include ("globals/insert_news.inc");
include ("globals/get_rating_change.inc");
include ("globals/device_ship_tech_modify.inc");
include ("globals/display_this_planet.inc");

$shipinfo_old = $shipinfo;
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

$countplanet = 0;
display_this_planet($planetinfo);
$titleimage = $planetimg[0];
$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 0);
$template_object->assign("isfedbounty", $isfedbounty);
$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);
$template_object->assign("l_by_nofedbounty", $l_by_nofedbounty);

$template_object->assign("titleimage", $titleimage);

$template_object->assign("planetname", $planetinfo['name']);
$template_object->assign("l_sofa", $l_sofa);

if ($sofa_on && $planetinfo['owner'] != 3)
{
	if($playerinfo[turns] < 1)
	{
		$template_object->assign("error_msg", $l_cmb_atleastoneturn);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attackdie.tpl");
		include("footer.php");
		die();
	}
	if($shipinfo[fighters] < 1)
	{
		$template_object->assign("error_msg", $l_cmb_needfighters);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attackdie.tpl");
		include("footer.php");
		die();
	}

	$attacker_exchange_result = array();
	$target_exchange_result = array();

	$res = $db->SelectLimit("SELECT last_login FROM {$db_prefix}players WHERE player_id = $ownerinfo[player_id]", 1);
	$last_login = $res->fields['last_login'];
	$res->close();
	send_system_im($ownerinfo['player_id'], $l_planet_imtitleattack, $playerinfo['character_name'] . " $l_planet_imsofa $planetinfo[name] $l_planet_iminsector $planetinfo[sector_name].", $last_login);

	update_player_experience($playerinfo['player_id'], $sofa_planet);

	$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 1);
	$template_object->assign("isfedbounty", $isfedbounty);
	$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);
	$template_object->assign("l_by_nofedbounty", $l_by_nofedbounty);

	planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_SOFA");

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['fighter'] / $max_tech_level))) : 0;
	$planet_comp_level = NUM_FIGHTERS($planetinfo['fighter'] + $base_factor);
	$figs = $planetinfo['fighters'];
	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	if ($res)  
	{
		while (!$res->EOF)  
		{
			$figs += $res->fields['fighters'];  
			$ship_comp =  NUM_FIGHTERS($res->fields['fighter']);  
			$planet_comp_level = $planet_comp_level + $ship_comp;  
			$res->MoveNext();  
		}
	}
	$res->close();

	if ($planet_comp_level > $figs)
	{
		$targetfighters = $figs;
	}
	else
	{
		$targetfighters = $planet_comp_level;
	}

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['torps'] / $max_tech_level))) : 0;
	$planet_comp_level = NUM_TORPEDOES($planetinfo['torps'] + $base_factor);
	$torps = $planetinfo['torps'];
	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	if ($res)  
	{
		while (!$res->EOF)  
		{
			$torps += $res->fields['torps'];  
			$ship_comp =  NUM_TORPEDOES($res->fields['torps']);  
			$planet_comp_level = $planet_comp_level + $ship_comp;  
			$res->MoveNext();  
		}
	}
	$res->close();

	if ($planet_comp_level > $torps)
	{
		$target_torps_left = $torps;
	}
	else
	{
		$target_torps_left = $planet_comp_level;
	}

	$attacker_fighters_left = $shipinfo['fighters'];
	$target_shield_energy = floor($planetinfo['energy'] * 0.4);
	$target_beam_energy = $planetinfo['energy'] - $target_shield_energy;

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['beams'] / $max_tech_level))) : 0;
	if ($planetinfo['beams'] == 0) 
	{
		$targetbeams = 0;
	}
	else
	{
		$targetbeams = NUM_BEAMS($planetinfo['beams'] + $base_factor);
	}

	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	while (!$res->EOF)
	{
		$targetbeams += NUM_BEAMS($res->fields['beams']);
		$res->MoveNext();
	}
	$res->close();

	if ($targetbeams < $target_beam_energy)
	{
		$target_beam_energy = $targetbeams;
	}

	$targetenergyset = $target_beam_energy;

	// get attacker beam, shield and armor values
	$attacker_shield_energy = floor($shipinfo['energy'] * 0.4);

	$attackershields = NUM_SHIELDS($shipinfo['shields']);

	if ($attackershields < $attacker_shield_energy)
	{
		$attacker_shield_energy = $attackershields;
	}

	$attackerarmor = $shipinfo['armor_pts'];
	$attackerenergyset = $attacker_shield_energy;

	$targetlowpercent = ecmcheck($shipinfo['ecm'], $planetinfo['sensors'], -$full_attack_modifier);
	$attackerlowpercent = ecmcheck($shipinfo['sensors'], $shipinfo['sensors'], $full_attack_modifier);

	if(!class_exists($shipinfo['fighter_class']))
	{
		include ("class/" . $shipinfo['fighter_class'] . ".inc");
	}

	$attackobject = new $shipinfo['fighter_class']();
	$fighter_damage_all = $attackobject->fighter_damage_all;

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
	$fighter_hit_pts = $targetobject->hit_pts;

	if(!class_exists($planetinfo['beam_class']))
	{
		include ("class/planet/" . $planetinfo['beam_class'] . ".inc");
	}

	$targetobject = new $planetinfo['beam_class']();
	$beam_damage_all = $targetobject->damage_all;
	$beam_damage_shields = $targetobject->damage_shields;

	if(!class_exists($planetinfo['torp_class']))
	{
		include ("class/planet/" . $planetinfo['torp_class'] . ".inc");
	}

	$targetobject = new $planetinfo['torp_class']();
	$torp_hit_pts = $targetobject->hit_pts;

	$success = SCAN_SUCCESS($shipinfo['sensors'], $planetinfo['cloak']);

	$template_object->assign("start_target_beams", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_beam_energy)));
	$template_object->assign("start_target_fighters", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targetfighters)));
	$template_object->assign("start_target_shields", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_shield_energy)));
	$template_object->assign("start_target_torps", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_torps_left)));
	$template_object->assign("start_target_armor", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['armor_pts'])));

	$template_object->assign("l_cmb_attacker_beams", $l_cmb_attacker_beams);
	$template_object->assign("l_cmb_attacker_fighters", $l_cmb_attacker_fighters);
	$template_object->assign("l_cmb_attacker_shields", $l_cmb_attacker_shields);
	$template_object->assign("l_cmb_attacker_torps", $l_cmb_attacker_torps);
	$template_object->assign("l_cmb_attacker_armor", $l_cmb_attacker_armor);
	$template_object->assign("l_cmb_target_beams", $l_cmb_target_beams);
	$template_object->assign("l_cmb_target_fighters", $l_cmb_target_fighters);
	$template_object->assign("l_cmb_target_shields", $l_cmb_target_shields);
	$template_object->assign("l_cmb_target_torps", $l_cmb_target_torps);
	$template_object->assign("l_cmb_target_armor", $l_cmb_target_armor);
	$template_object->assign("l_cmb_you", $l_cmb_you);

	$template_object->assign("start_attacker_beam_energy", NUMBER($attacker_beam_energy));
	$template_object->assign("start_attackerfighters", NUMBER($attacker_fighters_left));
	$template_object->assign("start_attacker_shield_energy", NUMBER($attacker_shield_energy));
	$template_object->assign("start_attackertorps", NUMBER($shipinfo['torps']));
	$template_object->assign("start_attackerarmor", NUMBER($attackerarmor));

	//  Check to see if planet detects planet bombs.
	$success = SCAN_SUCCESS($planetinfo['sensors'], $shipinfo['cloak']);

	$energy_lost = 0;
	//echo "$attackercloak $planetsensors $roll  $success<br>";
	if (mt_rand(1, 100) < $success)
	{
		// All of Beams Fire
		$ddamageroll=mt_rand(1,25);
		if ($ddamageroll==1)
		{
			$target_beam_energy = round(mt_rand(round($target_beam_energy/2), $target_beam_energy)*2);
			$target_exchange_result[] = $l_planet_beamfire1;
		}
		if ($ddamageroll==2)
		{
			$target_beam_energy = round(mt_rand(round($target_beam_energy/2), $target_beam_energy)*3);
			$target_exchange_result[] = $l_planet_beamfire2;
		}
		if($ddamageroll==3)
		{
			$target_beam_energy = round(mt_rand(round($target_beam_energy/2), $target_beam_energy)*4);
			$target_exchange_result[] = $l_planet_beamfire3;
		}
		if($ddamageroll > 3)
		{
			$target_beam_energy = mt_rand(round($target_beam_energy/2), $target_beam_energy);
			$target_exchange_result[] = $l_planet_beamfire4;
		}

		$template_object->assign("l_cmb_beam_exchange", $l_cmb_beam_exchange);

		$unused_target_beams = 0;
		if($target_beam_energy != 0)
		{
			$attack_shield_hit_pts = $attacker_shield_energy * $ship_shield_hit_pts;
			$attack_armor_hit_pts = $attackerarmor * $ship_armor_hit_pts;
			$target_fire_damage = calc_damage($target_beam_energy, $beam_damage_shields, $targetlowpercent, $targetshipbeams, $shipinfo['shields'], $attack_shield_hit_pts);
			if($target_fire_damage[2] == 100)
			{
				$target_exchange_result[] = str_replace("[player]", $targetname, $l_cmb_enemybeamfailshield);
			}
			$unused_target_beams = $target_fire_damage[1];

			if($target_fire_damage[0] > $attack_shield_hit_pts)
			{
				if($attacker_shield_energy > 0)
				{
					$target_exchange_result[] = str_replace("[damage]", NUMBER($attacker_shield_energy), $l_cmb_attacker_shields_hit);
				}
				$target_exchange_result[] = $l_cmb_attacker_shields_down;
				$attacker_shields_left = 0;
				$target_fire2_damage = calc_damage($target_fire_damage[1], $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['armor'], $attack_armor_hit_pts);
				$unused_target_beams += $target_fire2_damage[1];
				$target_fire_damage[4] = $target_fire2_damage[4];

				if($target_fire2_damage[2] == 100)
				{
					$target_exchange_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_enemybeamfailarmor);
				}

				if($target_fire2_damage[0] > $attack_armor_hit_pts)
				{
					$target_fire2_damage[0] = $target_fire2_damage[0] - $attack_armor_hit_pts;
					$attack_damage = floor($attack_armor_hit_pts / max(1,$ship_armor_hit_pts));
					if($attack_damage > 0)
					{
						$target_exchange_result[] = str_replace("[damage]", NUMBER($attack_damage), $l_cmb_attacker_armor_hit);
					}
					$target_exchange_result[] = $l_cmb_attacker_armor_down;
					$attacker_armor_left = 0;
				}
				else
				{
					$attack_armor_hit_pts = $attack_armor_hit_pts - $target_fire2_damage[0];
					$attacker_armor_used = floor($target_fire2_damage[0] / max(1,$ship_armor_hit_pts));
					$target_exchange_result[] = str_replace("[damage]", NUMBER($attacker_armor_used), $l_cmb_attacker_armor_hit);
					$attacker_armor_left = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
				}
			}
			else
			{
				$attack_shield_hit_pts = $attack_shield_hit_pts - $target_fire_damage[0];
				$attacker_shields_used = floor($target_fire_damage[0] / max(1,$ship_shield_hit_pts));
				$target_exchange_result[] = str_replace("[damage]", NUMBER($attacker_shields_used), $l_cmb_attacker_shields_hit);
				$attacker_shields_left = floor($attack_shield_hit_pts / $ship_shield_hit_pts);
				$attacker_armor_left = $attackerarmor;
			}
			$unused_target_beams += $target_fire_damage[4];
		}
		else
		{
			$target_exchange_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_target_no_beams);
			$attacker_shields_left = $attacker_shield_energy;
			$attacker_armor_left = $attackerarmor;
		}

		$attacker_armor_lost=$shipinfo['armor_pts'] - $attacker_armor_left;
		$attacker_energy_lost=$attackerenergyset - $attacker_shields_left;

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST(armor_pts - $attacker_armor_lost, 0), energy=GREATEST(energy - $attacker_energy_lost, 0) WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$target_energy_lost=$targetenergyset - $unused_target_beams;

		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET energy=GREATEST(energy - $target_energy_lost, 0) WHERE planet_id=$planetinfo[planet_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if($attacker_armor_left < 1 and $attacker_shields_left < 1)
		{
			$free_ore = round($shipinfo['ore']/2);
			$free_organics = round($shipinfo['organics']/2);
			$free_goods = round($shipinfo['goods']/2);
			$ship_value=$upgrade_cost*(round(mypw($upgrade_factor, $shipinfo['hull']))+round(mypw($upgrade_factor, $shipinfo['engines']))+round(mypw($upgrade_factor, $shipinfo['power']))+round(mypw($upgrade_factor, $shipinfo['fighter']))+round(mypw($upgrade_factor, $shipinfo['sensors']))+round(mypw($upgrade_factor, $shipinfo['beams']))+round(mypw($upgrade_factor, $shipinfo['torp_launchers']))+round(mypw($upgrade_factor, $shipinfo['shields']))+round(mypw($upgrade_factor, $shipinfo['armor']))+round(mypw($upgrade_factor, $shipinfo['cloak']))+round(mypw($upgrade_factor, $shipinfo['ecm'])));
			$ship_salvage_rate=mt_rand(0,10);
			$ship_salvage=$ship_value*$ship_salvage_rate/100;
			$attacker_exchange_result[] = $l_cmb_attacker_ship_destroyed;

			if($shipdevice['dev_escapepod']['amount'] == 1) 
			{
				$shipid1=$shipinfo['ship_id'];
				$attacker_exchange_result[] = $l_cmb_escapepod_launched;
				player_ship_destroyed($shipid1, $playerinfo['player_id'], $playerinfo['rating'], 0, 0, "killedsofapod");
				collect_bounty($planetinfo['owner'],$playerinfo['player_id']);
				$playernames = $playerinfo['character_name'];
				insert_news($playernames, 1, "pattackerpod");
			}
			else
			{
				$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
				db_kill_player($playerinfo['player_id'], 0, 0, "killedsofa");
				collect_bounty($planetinfo['owner'],$playerinfo['player_id']);
				$playernames = $playerinfo['character_name'];
				insert_news($playernames, 1, "pattackerdied");
			}
		}
		else
		{
			$free_ore=0;
			$free_goods=0;
			$free_organics=0;
			$ship_salvage_rate=0;
			$ship_salvage=0;

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
			$attacker_exchange_result[] = $l_cmb_you_survived_sofa_beams;
		}
	}
	else
	{
		$attacker_exchange_result[] = $l_cmb_you_survived_sofa_beams;
		$attacker_shields_left = $attacker_shield_energy;
		$attacker_armor_left = $attackerarmor;
	}

	$template_object->assign("attacker_beam_result", $attacker_exchange_result);
	$template_object->assign("target_beam_result", $target_exchange_result);

	$attacker_fighter_result = array();
	$target_fighter_result = array();
	$template_object->assign("is_fighter_echange", 0);

	if($attacker_armor_left > 0 or $attacker_shields_left > 0)
	{
		$template_object->assign("l_cmb_fighter_exchange", $l_cmb_fighter_exchange);
		$template_object->assign("is_fighter_echange", 1);
		$unused_target_fighters = 0;
		$unused_attack_fighters = 0;

		if($targetfighters != 0)
		{
			$attack_fighter_hit_pts = $attacker_fighters_left * $fighter_hit_pts;
			$target_fighter_damage = calc_damage($targetfighters, $fighter_damage_all, $targetlowpercent, $targetshipfighter, $shipinfo['fighter'], $attack_fighter_hit_pts);

			if($target_fighter_damage[2] == 100)
			{
				$target_fighter_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_enemyfighterfailfighter);
			}
			$unused_target_fighters = $target_fighter_damage[1];
		}

		if($attacker_fighters_left != 0)
		{
			$target_fighter_hit_pts = $targetfighters * $fighter_hit_pts;
			$target_torp_hit_pts = $target_torps_left * $torp_hit_pts;
			$attack_fighter_damage = calc_damage($attacker_fighters_left, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $targetshipfighter, $target_fighter_hit_pts);
			$unused_attack_fighters = $attack_fighter_damage[1];

			if($attack_fighter_damage[2] > 0)
			{
				$attacker_fighter_result[] = $l_cmb_yourfighterfail1;
				$attacker_fighter_result[] = str_replace("[percent]", (100 - $attack_fighter_damage[2]), $l_cmb_yourfighterfail2);
			}

			if($attack_fighter_damage[0] > $target_fighter_hit_pts)
			{
				if($target_fighters_left > 0)
				{
					$attacker_fighter_result[] = str_replace("[player]", $planetinfo['name'], str_replace("[fighterslost]", NUMBER($target_fighters_left), $l_cmb_target_fighters_lost));
				}
				$attacker_fighter_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_target_lost_all_fighters);
				$attack_fighter2_damage = calc_damage($attack_fighter_damage[4], $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $targetshiptorp_launchers, $target_torp_hit_pts);
				$unused_attack_fighters += $attack_fighter2_damage[1];
				$attack_fighter_damage[4] = $attack_fighter2_damage[4];

				if($attack_fighter2_damage[2] > 0)
				{
					$attacker_fighter_result[] = $l_cmb_yourfighterfail1;
					$attacker_fighter_result[] = str_replace("[percent]", (100 - $attack_fighter2_damage[2]), $l_cmb_yourfighterfail2);
				}

				if($attack_fighter2_damage[0] > $target_torp_hit_pts)
				{
					$attack_fighter2_damage[0] = $attack_fighter2_damage[0] - $target_torp_hit_pts;
					$attack_damage = floor($target_torp_hit_pts / $torp_hit_pts);
					if($attack_damage > 0)
					{
						$attacker_fighter_result[] = str_replace("[player]", $planetinfo['name'], str_replace("[torpslost]", NUMBER($attack_damage), $l_cmb_target_torps_lost));
					}
					$attacker_fighter_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_target_lost_all_torps);
					$target_torps_left2 = 0;
					$target_torps_died = $target_torps_left;
				}
				else
				{
					$target_torp_hit_pts = $target_torp_hit_pts - $attack_fighter2_damage[0];
					$target_torps_used = floor($attack_fighter2_damage[0] / $torp_hit_pts);
					$attacker_fighter_result[] = str_replace("[player]", $planetinfo['name'], str_replace("[torpslost]", NUMBER($target_torps_used), $l_cmb_target_torps_lost));
					$target_torps_left2 = floor($target_torp_hit_pts / $torp_hit_pts);
					$target_torps_died = $target_torps_left - $target_torps_left2;
				}
			}
			else
			{
				$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_fighter_damage[0];
				$target_fighters_used = floor($attack_fighter_damage[0] / $fighter_hit_pts);
				$attacker_fighter_result[] = str_replace("[player]", $planetinfo['name'], str_replace("[fighterslost]", NUMBER($target_fighters_used), $l_cmb_target_fighters_lost));
				$target_fighters_left2 = floor($target_fighter_hit_pts / $fighter_hit_pts);
				$target_fighters_died = $target_fighters_left - $target_fighters_left2;
				$target_torps_left2 = $target_torps_left;
				$target_torps_died = 0;
			}
			$unused_attack_fighters += $attack_fighter_damage[4];
		}
		else
		{
			$attacker_fighter_result[] = $l_cmb_attacker_no_fighters;
			$target_fighters_left2 = $target_fighters_left;
			$target_fighters_died = 0;
			$target_torps_left2 = $target_torps_left;
			$target_torps_died = 0;
		}

		if($targetfighters != 0)
		{
			if(mt_rand(1, 100) <= $defender_lucky_percentage)
			{
				$target_fighter_damage[0] = $target_fighter_damage[0] * $defender_lucky_multiplier;
				$target_fighter_result[] = str_replace("[times]", $defender_lucky_multiplier, $l_cmb_target_surprise_fighters);
			}

			if($target_fighter_damage[0] > $attack_fighter_hit_pts)
			{
				if($attacker_fighters_left > 0)
				{
					$target_fighter_result[] = str_replace("[fighterslost]", NUMBER($attacker_fighters_left), $l_cmb_attacker_fighters_lost);
				}
				$attacker_fighters_left = 0;

				$target_fighter_result[] = $l_cmb_attacker_lost_all_fighters;
				$target_fighter2_damage = calc_damage($target_fighter_damage[4], $fighter_damage_all, $targetlowpercent, $targetshipfighter, $shipinfo['torp_launchers']);
				$unused_target_fighters += $target_fighter2_damage[1];
				$target_fighter_damage[4] = $target_fighter2_damage[4];

				if($target_fighter2_damage[2] == 100)
				{
					$target_fighter_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_enemyfighterfailtorp);
				}

				if($target_fighter2_damage[0] > $attack_torp_hit_pts)
				{
					$attack_damage = floor($attack_torp_hit_pts / $torp_hit_pts);
					if($attack_damage > 0)
					{
						$target_fighter_result[] = str_replace("[torpslost]", NUMBER($attack_damage), $l_cmb_attacker_torps_lost);
					}
					$target_fighter_result[] = $l_cmb_attacker_lost_all_torps;
					$attacker_torps_left = 0;
				}
				else
				{
					$attack_torp_hit_pts = $attack_torp_hit_pts - $target_fighter2_damage[0];
					$attack_torps_used = floor($target_fighter2_damage[0] / $torp_hit_pts);
					$target_fighter_result[] = str_replace("[torpslost]", NUMBER($attack_torps_used), $l_cmb_attacker_torps_lost);
					$attacker_torps_left = floor($attack_torp_hit_pts / $torp_hit_pts);
				}
			}
			else
			{
				$attack_fighter_hit_pts = $attack_fighter_hit_pts - $target_fighter_damage[0];
				$attack_fighters_used = floor($target_fighter_damage[0] / $fighter_hit_pts);
				$target_fighter_result[] = str_replace("[fighterslost]", NUMBER($attack_fighters_used), $l_cmb_attacker_fighters_lost);
				$attacker_fighters_left = floor($attack_fighter_hit_pts / $fighter_hit_pts);
			}
			$unused_target_fighters += $target_fighter_damage[4];
		}
		else
		{
			$target_fighter_result[] = str_replace("[player]", $planetinfo['name'], $l_cmb_target_no_send_fighteres);
		}

		$target_fighters_left -= $target_fighters_died;
		$target_torps_left -= $target_torps_died;

		if($targetinfo['player_id'] <= 3)
		{
			$rating_SOFA_attack_planet = 0;
		}

		$rating_change=get_rating_change($playerinfo['rating'], $ownerinfo['rating'], $rating_SOFA_attack_planet, $ownerinfo['player_id']);
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET rating=rating+$rating_change, turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$fighters_lost=$shipinfo['fighters']-$attacker_fighters_left;
		$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\>". NUMBER($fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">0</font>",$l_cmb_attacker_lost_list);
		$attacker_fighter_result[] = $l_cmb_attacker_lost_list;
		playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET fighters=GREATEST(fighters-$fighters_lost, 0) WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$fighters_lost=$planetinfo['fighters']-$target_fighters_left;
		$torps_lost=$planetinfo['torps']-$target_torps_left;
		$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $planetinfo['name'] . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">0</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($fighters_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($torps_lost) . "</font>",$l_cmb_target_lost_list);
		$target_fighter_result[] = $l_cmb_target_lost_list;
		playerlog($planetinfo['owner'], "LOG5_AFTER_ACTION", str_replace("[player]", $planetinfo['name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);

		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=GREATEST(fighters-$fighters_lost, 0), torps=GREATEST(torps-$torps_lost, 0) WHERE planet_id=$planetinfo[planet_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		playerlog($ownerinfo['player_id'], "LOG5_PLANET_BOMBED", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]|$beamsused|$torps_lost|$fighters_lost");

		$template_object->assign("attacker_fighter_result", $attacker_fighter_result);
		$template_object->assign("target_fighter_result", $target_fighter_result);
	}

	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("allow_ibank", $allow_ibank);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_igb_term", $l_igb_term);
	$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
	$template_object->assign("l_by_placebounty", $l_by_placebounty);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_unowned/sofa_attack.tpl");
	include ("footer.php");
	die();
}
else
{
	$template_object->assign("l_command_no", $l_command_no);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("allow_ibank", $allow_ibank);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_igb_term", $l_igb_term);
	$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
	$template_object->assign("l_by_placebounty", $l_by_placebounty);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_unowned/sofa_attack.tpl");
	include ("footer.php");
	die();
}

?>