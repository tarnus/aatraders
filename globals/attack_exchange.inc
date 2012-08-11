<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: attack_exchange.inc

// Order of attack results in a foreach array
// $attacker_beam_result array
// $target_beam_result array
// $attacker_fighter_result array
// $target_fighter_result array
// $attacker_torp_result array
// $target_torp_result array

if (preg_match("/attack_exchange.inc/i", $_SERVER['PHP_SELF'])) 
{ 
		 echo "You can not access this file directly!"; 
		 die(); 
} 
include ("globals/get_player.inc");

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Combat Start:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " (id: $playerinfo[player_id]) Attacker Score: " . $debug_attack['attackerscore'] . ", Owns Sector: " . $debug_attack['isowner'] . ",  Opposite Alignment: " . $debug_attack['isopposite'] . ", Attack Ratio: " . $debug_attack['ratio'] . ", <br>
$l_cmb_beams:<B> ".$attacker_beam_energy."</B>, $l_cmb_fighters: <B>".$attackerfighters."</B>, $l_cmb_shields: <B>$attacker_shield_energy</B>, $l_cmb_torps: <B>$attackertorps</B>. $l_cmb_armor: <B>$attackerarmor</B>
<br>Shield Tech: $shipinfo[shields] , Armor Tech: $shipinfo[armor] , Torp Tech: $shipinfo[torp_launchers] , Beam Tech: $shipinfo[beams] , Fighter Bay: $shipinfo[fighter]<br>
<br>Defender ".$targetname . " (id: $targetinfo[player_id]) Target Score: " . $debug_attack['targetscore'] . ", Has Bounty: " . $debug_attack['hasbounty'] . ", Target Turns: " . $debug_attack['turns'] . ", <br>
$l_cmb_beams=<B>".$target_beam_energy."</B>, $l_cmb_fighters: <B>".$targetfighters."</B>, $l_cmb_shields: <B>$target_shield_energy</B>, $l_cmb_torps: <B>$targettorps</B>. $l_cmb_armor: <B>$targetarmor</B>
<br>Shield Tech: $targetshipshields , Armor Tech: $targetshiparmor , Torp Tech: $targetshiptorp_launchers , Beam Tech: $targetshipbeams , Fighter Bay: $targetshipfighter , Base Factor: $base_factor");

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Combat Class Values:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " fighter_damage_shields:<B> ".$fighter_damage_shields.
"</B>, fighter_damage_all: <B>".$fighter_damage_all."</B>, fighter_hit_pts: <B>$fighter_hit_pts</B>, beam_damage_shields: <B>$beam_damage_shields</B>. $beam_damage_all: <B>$beam_damage_all</B>
<br>torp_damage_shields: <B>$torp_damage_shields</B> , torp_damage_all: <B>$torp_damage_all</B> , torp_hit_pts: <B>$torp_hit_pts</B> , ship_shield_hit_pts: <B>$ship_shield_hit_pts</B> , ship_armor_hit_pts: <B>$ship_armor_hit_pts</B><br>");

if($attacktype == "planet")
{
	$success = SCAN_SUCCESS($shipinfo['sensors'], $planetinfo['cloak']);

	$template_object->assign("start_target_beams", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_beam_energy)));
	$template_object->assign("start_target_fighters", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targetfighters)));
	$template_object->assign("start_target_shields", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_shield_energy)));
	$template_object->assign("start_target_torps", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targettorps)));
	$template_object->assign("start_target_armor", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targetarmor)));

	$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 1);
	$target_title = str_replace("[player]", $ownerinfo['character_name'], str_replace("[planet]", $planetinfo['name'], $l_cmb_title_target_planet));
	include ("globals/display_this_planet.inc");
	$countplanet = 0;
	display_this_planet($planetinfo);
	$titleimage = $planetimg[0];
}
else
{
	$success = SCAN_SUCCESS($shipinfo['sensors'], $targetship['cloak']);

	$template_object->assign("start_target_beams", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_beam_energy)));
	$template_object->assign("start_target_fighters", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $targetfighters)));
	$template_object->assign("start_target_shields", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_shield_energy)));
	$template_object->assign("start_target_torps", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $targettorps)));
	$template_object->assign("start_target_armor", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $targetarmor)));

	$isfedbounty = ship_bounty_check($playerinfo, $shipinfo['sector_id'], $targetinfo, 1);
	$target_title = str_replace("[player]", $targetinfo['character_name'], str_replace("[ship]", $targetship['name'], $l_cmb_title_target_ship));
	$getshipimage = $db->SelectLimit("SELECT image FROM {$db_prefix}ship_types WHERE type_id = $targetship[class]", 1);
	$titleimage = $getshipimage->fields['image'];
}

$template_object->assign("attacktype", $attacktype);
$template_object->assign("titleimage", $titleimage);
$template_object->assign("target_title", $target_title);
$template_object->assign("isfedbounty", $isfedbounty);
$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);

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
$template_object->assign("start_attackerfighters", NUMBER($attackerfighters));
$template_object->assign("start_attacker_shield_energy", NUMBER($attacker_shield_energy));
$template_object->assign("start_attackertorps", NUMBER($attackertorps));
$template_object->assign("start_attackerarmor", NUMBER($attackerarmor));

$template_object->assign("l_cmb_beam_exchange", $l_cmb_beam_exchange);

$attacker_beam_result = array();

if($attacker_beam_energy != 0)
{
	$attack_fire_damage = calc_damage($attacker_beam_energy, $beam_damage_shields, $attackerlowpercent, $shipinfo['beams'], $targetshipshields);

	if($attack_fire_damage[2] > 0){
		$attacker_beam_result[] = $l_cmb_yourbeamfail1;
		$attacker_beam_result[] = str_replace("[percent]", (100 - $attack_fire_damage[2]), $l_cmb_yourbeamfail2);
	}

	//
	$target_shields = calc_failure($target_shield_energy, $targetshipshields, $shipinfo['beams']);

	$target_shield_hit_pts = $target_shield_energy * $ship_shield_hit_pts;

	//
	$target_armor = calc_failure($targetarmor, $targetshiparmor, $shipinfo['beams']);

	$target_armor_hit_pts = $targetarmor * $ship_armor_hit_pts;

	$attacker_energy_left = $attack_fire_damage[1];

	if($attack_fire_damage[0] > $target_shield_hit_pts)
	{
		$attack_fire_damage[0] = $attack_fire_damage[0] - $target_shield_hit_pts;
		if($target_shield_energy > 0)
		{
			$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($target_shield_energy), $l_cmb_target_shields_hit));
		}
		$attacker_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_shields_down);
		$target_shields_left = 0;
		$attacker_energy_left = floor($attack_fire_damage[0] / $beam_damage_shields);
		$attack_fire2_damage = calc_damage($attacker_energy_left, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $targetshiparmor);
		$attacker_energy_left += $attack_fire2_damage[1];

		if($attack_fire2_damage[2] > 0){
			$attacker_beam_result[] = $l_cmb_yourbeamfail1;
			$attacker_beam_result[] = str_replace("[percent]", (100 - $attack_fire2_damage[2]), $l_cmb_yourbeamfail2);
		}

		if($attack_fire2_damage[0] > $target_armor_hit_pts)
		{
			$attack_fire2_damage[0] = $attack_fire2_damage[0] - $target_armor_hit_pts;
			$attack_damage = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
			{
				$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($attack_damage), $l_cmb_target_armor_hit));
			}
			$attacker_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_armor_down);
			$attacker_energy_left += floor($attack_fire2_damage[0] / $beam_damage_all);
			$target_armor_left = 0;
		}
		else
		{
			$target_armor_hit_pts = $target_armor_hit_pts - $attack_fire2_damage[0];
			$target_armor_used = floor($attack_fire2_damage[0] / $ship_armor_hit_pts);
			$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($target_armor_used), $l_cmb_target_armor_hit));
			$target_armor_left = floor($target_armor_hit_pts / $ship_armor_hit_pts);
		}
	}
	else
	{
		$target_shield_hit_pts = $target_shield_hit_pts - $attack_fire_damage[0];
		$target_shields_used = floor($attack_fire_damage[0] / $ship_shield_hit_pts);
		$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($target_shields_used), $l_cmb_target_shields_hit));
		$target_shields_left = floor($target_shield_hit_pts / $ship_shield_hit_pts);
		$target_armor_left = $targetarmor;
	}
}
else
{
	$attacker_beam_result[] = $l_cmb_attacker_no_beams;
	$target_shields_left = $target_shield_energy;
	$target_armor_left = $targetarmor;
	$attacker_energy_left = 0;
}

if($attack_beamtofighter_dmg != 0)
{
	$attack_fighter_damage = calc_damage($attack_beamtofighter_dmg, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $targetshipfighter);

	if($attack_fighter_damage[2] > 0){
		$attacker_beam_result[] = $l_cmb_yourbeamfail1;
		$attacker_beam_result[] = str_replace("[percent]", (100 - $attack_fighter_damage[2]), $l_cmb_yourbeamfail2);
	}

	$attacker_energy_left += $attack_fighter_damage[1];

	$target_fighter_hit_pts = $targetfighters * $fighter_hit_pts;
	if($attack_fighter_damage[0] > $target_fighter_hit_pts)
	{
		$attack_fighter_damage[0] = $attack_fighter_damage[0] - $target_fighter_hit_pts;
		if($targetfighters > 0)
		{
			$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[fighterslost]", NUMBER($targetfighters), $l_cmb_target_fighters_lost));
		}
		$attacker_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_lost_all_fighters);
		$attacker_energy_left += floor($attack_fighter_damage[0] / $beam_damage_all);
		$target_fighters_left = 0;
	}
	else
	{
		$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_fighter_damage[0];
		$target_fighters_used = floor($attack_fighter_damage[0] / $fighter_hit_pts);
		$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[fighterslost]", NUMBER($target_fighters_used), $l_cmb_target_fighters_lost));
		$target_fighters_left = floor($target_fighter_hit_pts / $fighter_hit_pts);
	}
}
else
{
	$attacker_beam_result[] = $l_cmb_attacker_no_beams;
	$target_fighters_left = $targetfighters;
}

if($attack_beamtotorp_dmg != 0)
{
	$attack_torp_damage = calc_damage($attack_beamtotorp_dmg, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $targetshiptorp_launchers);

	if($attack_torp_damage[2] > 0){
		$attacker_beam_result[] = $l_cmb_yourbeamfail1;
		$attacker_beam_result[] = str_replace("[percent]", (100 - $attack_torp_damage[2]), $l_cmb_yourbeamfail2);
	}

	$attacker_energy_left += $attack_torp_damage[1];

	$target_torp_hit_pts = $targettorps * $torp_hit_pts;
	if($attack_torp_damage[0] > $target_torp_hit_pts)
	{
		$attack_torp_damage[0] = $attack_torp_damage[0] - $target_torp_hit_pts;
		if($targettorps > 0)
		{
			$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[torpslost]", NUMBER($targettorps), $l_cmb_target_torps_lost));
		}
		$attacker_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_lost_all_torps);
		$attacker_energy_left += floor($attack_torp_damage[0] / $beam_damage_all);
		$target_torps_left = 0;
	}
	else
	{
		$target_torp_hit_pts = $target_torp_hit_pts - $attack_torp_damage[0];
		$target_torps_used = floor($attack_torp_damage[0] / $torp_hit_pts);
		$attacker_beam_result[] = str_replace("[player]", $targetname, str_replace("[torpslost]", NUMBER($target_torps_used), $l_cmb_target_torps_lost));
		$target_torps_left = floor($target_torp_hit_pts / $torp_hit_pts);
	}
}
else
{
	$attacker_beam_result[] = $l_cmb_attacker_no_beams;
	$target_torps_left = $targettorps;
}

$template_object->assign("attacker_beam_result", $attacker_beam_result);

$target_beam_result = array();

if($target_beam_energy != 0)
{
	$target_fire_damage = calc_damage($target_beam_energy, $beam_damage_shields, $targetlowpercent, $targetshipbeams, $shipinfo['shields']);

	if($target_fire_damage[2] == 100)
	{
		$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_enemybeamfailshield);
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_fire_damage[0] = $target_fire_damage[0] * $defender_lucky_multiplier;
		$target_beam_result[] = str_replace("[times]", $defender_lucky_multiplier, $l_cmb_target_beams_overload);
	}

	$target_energy_left = $target_fire_damage[1];

	$attacker_shields = calc_failure($attacker_shield_energy, $shipinfo['shields'], $targetshipbeams);
	$attack_shield_hit_pts = $attacker_shield_energy * $ship_shield_hit_pts;
	$attacker_armor = calc_failure($attackerarmor, $shipinfo['armor'], $targetshipbeams);

	$attack_armor_hit_pts = $attackerarmor * $ship_armor_hit_pts;
	if($target_fire_damage[0] > $attack_shield_hit_pts)
	{
		$target_fire_damage[0] = $target_fire_damage[0] - $attack_shield_hit_pts;
		if($attacker_shield_energy > 0)
		{
			$target_beam_result[] = str_replace("[damage]", NUMBER($attacker_shield_energy), $l_cmb_attacker_shields_hit);
		}
		$target_beam_result[] = $l_cmb_attacker_shields_down;
		$attacker_shields_left = 0;
		$target_energy_left += floor($target_fire_damage[0] / $beam_damage_shields);
		$target_fire2_damage = calc_damage($target_energy_left, $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['armor']);
		$target_energy_left += $target_fire2_damage[1];

		if($target_fire2_damage[2] == 100){
			$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_enemybeamfailarmor);
		}

		if($target_fire2_damage[0] > $attack_armor_hit_pts)
		{
			$target_fire2_damage[0] = $target_fire2_damage[0] - $attack_armor_hit_pts;
			$attack_damage = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
			{
				$target_beam_result[] = str_replace("[damage]", NUMBER($attack_damage), $l_cmb_attacker_armor_hit);
			}
			$target_beam_result[] = $l_cmb_attacker_armor_down;
			$target_energy_left += floor($target_fire2_damage[0] / $beam_damage_all);
			$attacker_armor_left = 0;
		}
		else
		{
			$attack_armor_hit_pts = $attack_armor_hit_pts - $target_fire2_damage[0];
			$attacker_armor_used = floor($target_fire2_damage[0] / $ship_armor_hit_pts);
			$target_beam_result[] = str_replace("[damage]", NUMBER($attacker_armor_used), $l_cmb_attacker_armor_hit);
			$attacker_armor_left = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
		}
	}
	else
	{
		$attack_shield_hit_pts = $attack_shield_hit_pts - $target_fire_damage[0];
		$attacker_shields_used = floor($target_fire_damage[0] / $ship_shield_hit_pts);
		$target_beam_result[] = str_replace("[damage]", NUMBER($attacker_shields_used), $l_cmb_attacker_shields_hit);
		$attacker_shields_left = floor($attack_shield_hit_pts / $ship_shield_hit_pts);
		$attacker_armor_left = $attackerarmor;
	}
}
else
{
	$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_no_beams);
	$attacker_shields_left = $attacker_shield_energy;
	$attacker_armor_left = $attackerarmor;
	$target_energy_left = 0;
}

if($target_beamtofighter_dmg != 0)
{
	$target_fighter_damage = calc_damage($target_beamtofighter_dmg, $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['fighters']);

	if($target_fighter_damage[2] == 100){
		$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_enemybeamfailfighter);
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] * $defender_lucky_multiplier;
		$target_beam_result[] = str_replace("[times]", $defender_lucky_multiplier, $l_cmb_target_beams_overload);
	}

	$target_energy_left += $target_fighter_damage[1];

	$attack_fighter_hit_pts = $attackerfighters * $fighter_hit_pts;
	if($target_fighter_damage[0] > $attack_fighter_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_fighter_hit_pts;
		if($attackerfighters > 0)
		{
			$target_beam_result[] = str_replace("[fighterslost]", NUMBER($attackerfighters), $l_cmb_attacker_fighters_lost);
		}
		$target_beam_result[] = $l_cmb_attacker_lost_all_fighters;
		$attacker_fighters_left = 0;
	}
	else
	{
		$attack_fighter_hit_pts = $attack_fighter_hit_pts - $target_fighter_damage[0];
		$attacker_fighters_used = floor($target_fighter_damage[0] / $fighter_hit_pts);
		$target_beam_result[] = str_replace("[fighterslost]", NUMBER($attacker_fighters_used), $l_cmb_attacker_fighters_lost);
		$attacker_fighters_left = floor($attack_fighter_hit_pts / $fighter_hit_pts);
	}
}
else
{
	$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_no_beams);
	$attacker_fighters_left = $attackerfighters;
}

if($target_beamtotorp_dmg != 0)
{
	$target_torp_damage = calc_damage($target_beamtotorp_dmg, $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['torp_launchers']);

	if($target_torp_damage[2] == 100){
		$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_enemybeamfailtorp);
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_torp_damage[0] = $target_torp_damage[0] * $defender_lucky_multiplier;
		$target_beam_result[] = str_replace("[times]", $defender_lucky_multiplier, $l_cmb_target_beams_overload);
	}

	$target_energy_left += $target_torp_damage[1];

	$attack_torp_hit_pts = $attackertorps * $torp_hit_pts;
	if($target_torp_damage[0] > $attack_torp_hit_pts)
	{
		$target_torp_damage[0] = $target_torp_damage[0] - $attack_torp_hit_pts;
		if($attackertorps > 0)
		{
			$target_beam_result[] = str_replace("[torpslost]", NUMBER($attackertorps), $l_cmb_attacker_torps_lost);
		}
		$target_beam_result[] = $l_cmb_attacker_lost_all_torps;
		$attacker_torps_left = 0;
	}
	else
	{
		$attack_torp_hit_pts = $attack_torp_hit_pts - $target_torp_damage[0];
		$attacker_torps_used = floor($target_torp_damage[0] / $torp_hit_pts);
		$target_beam_result[] = str_replace("[torpslost]", NUMBER($attacker_torps_used), $l_cmb_attacker_torps_lost);
		$attacker_torps_left = floor($attack_torp_hit_pts / $torp_hit_pts);
	}
}
else
{
	$target_beam_result[] = str_replace("[player]", $targetname, $l_cmb_target_no_beams);
	$attacker_torps_left = $attackertorps;
}

$template_object->assign("target_beam_result", $target_beam_result);

$template_object->assign("stage2_attacker_energy", NUMBER($attacker_energy_left));
$template_object->assign("stage2_attacker_fighters", NUMBER($attacker_fighters_left));
$template_object->assign("stage2_attacker_shields", NUMBER($attacker_shields_left));
$template_object->assign("stage2_attacker_torps", NUMBER($attacker_torps_left));
$template_object->assign("stage2_attacker_armor", NUMBER($attacker_armor_left));

// Stage 2 fighter Exchange

$template_object->assign("l_cmb_fighter_exchange", $l_cmb_fighter_exchange);

$attacker_fighter_result = array();

if($attacker_fighters_left != 0)
{
	$attack_fighter_damage = calc_damage($attacker_fighters_left, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $targetshipfighter);

	if($attack_fighter_damage[2] > 0){
		$attacker_fighter_result[] = $l_cmb_yourfighterfail1;
		$attacker_fighter_result[] = str_replace("[percent]", (100 - $attack_fighter_damage[2]), $l_cmb_yourfighterfail2);
	}

	$target_fighter_hit_pts = $target_fighters_left * $fighter_hit_pts;
	if($attack_fighter_damage[0] > $target_fighter_hit_pts)
	{
		$attack_fighter_damage[0] = $attack_fighter_damage[0] - $target_fighter_hit_pts;
		if($target_fighters_left > 0)
		{
			$attacker_fighter_result[] = str_replace("[player]", $targetname, str_replace("[fighterslost]", NUMBER($target_fighters_left), $l_cmb_target_fighters_lost));
		}
		$attacker_fighter_result[] = str_replace("[player]", $targetname, $l_cmb_target_lost_all_fighters);

		$target_fighters_left2 = 0;
		$attacker_fighters_left2 = floor($attack_fighter_damage[0] / $fighter_damage_all);
		$attack_fighter2_damage = calc_damage($attacker_fighters_left2, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $targetshiptorp_launchers);

		if($attack_fighter2_damage[2] > 0){
			$attacker_fighter_result[] = $l_cmb_yourfighterfail1;
			$attacker_fighter_result[] = str_replace("[percent]", (100 - $attack_fighter2_damage[2]), $l_cmb_yourfighterfail2);
		}

		$target_torp_hit_pts = $target_torps_left * $torp_hit_pts;
		if($attack_fighter2_damage[0] > $target_torp_hit_pts)
		{
			$attack_fighter2_damage[0] = $attack_fighter2_damage[0] - $target_torp_hit_pts;
			$attack_damage = floor($target_torp_hit_pts / $torp_hit_pts);
			if($attack_damage > 0)
			{
				$attacker_fighter_result[] = str_replace("[player]", $targetname, str_replace("[torpslost]", NUMBER($attack_damage), $l_cmb_target_torps_lost));
			}
			$attacker_fighter_result[] = str_replace("[player]", $targetname, $l_cmb_target_lost_all_torps);
			$target_torps_left2 = 0;
		}
		else
		{
			$target_torp_hit_pts = $target_torp_hit_pts - $attack_fighter2_damage[0];
			$target_torps_used = floor($attack_fighter2_damage[0] / $torp_hit_pts);
			$attacker_fighter_result[] = str_replace("[player]", $targetname, str_replace("[torpslost]", NUMBER($target_torps_used), $l_cmb_target_torps_lost));
			$target_torps_left2 = floor($target_torp_hit_pts / $torp_hit_pts);
		}
	}
	else
	{
		$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_fighter_damage[0];
		$target_fighters_used = floor($attack_fighter_damage[0] / $fighter_hit_pts);
		$attacker_fighter_result[] = str_replace("[player]", $targetname, str_replace("[fighterslost]", NUMBER($target_fighters_used), $l_cmb_target_fighters_lost));
		$target_fighters_left2 = floor($target_fighter_hit_pts / $fighter_hit_pts);
		$target_torps_left2 = $target_torps_left;
	}
}
else
{
	$attacker_fighter_result[] = $l_cmb_attacker_no_fighters;
	$target_fighters_left2 = $target_fighters_left;
	$target_torps_left2 = $target_torps_left;
}

$template_object->assign("attacker_fighter_result", $attacker_fighter_result);
$target_fighter_result = array();

if($target_fighters_left != 0)
{
	$target_fighter_damage = calc_damage($target_fighters_left, $fighter_damage_all, $targetlowpercent, $targetshipfighter, $shipinfo['fighter']);

	if($target_fighter_damage[2] == 100){
		$target_fighter_result[] = str_replace("[player]", $targetname, $l_cmb_enemyfighterfailfighter);
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] * $defender_lucky_multiplier;
		$target_fighter_result[] = str_replace("[times]", $defender_lucky_multiplier, $l_cmb_target_surprise_fighters);
	}

	$attack_fighter_hit_pts = $attacker_fighters_left * $fighter_hit_pts;
	if($target_fighter_damage[0] > $attack_fighter_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_fighter_hit_pts;
		if($attacker_fighters_left > 0)
		{
			$target_fighter_result[] = str_replace("[fighterslost]", NUMBER($attacker_fighters_left), $l_cmb_attacker_fighters_lost);
		}
		$target_fighter_result[] = $l_cmb_attacker_lost_all_fighters;
		$attacker_fighters_left2 = 0;
		$target_fighters_left3 = floor($target_fighter_damage[0] / $fighter_damage_all);
		$target_fighter2_damage = calc_damage($target_fighters_left3, $fighter_damage_all, $targetlowpercent, $targetshipfighter, $shipinfo['torp_launchers']);

		if($target_fighter2_damage[2] == 100){
			$target_fighter_result[] = str_replace("[player]", $targetname, $l_cmb_enemyfighterfailtorp);
		}

		$attack_torp_hit_pts = $attacker_torps_left * $torp_hit_pts;
		if($target_fighter2_damage[0] > $attack_torp_hit_pts)
		{
			$target_fighter2_damage[0] = $target_fighter2_damage[0] - $attack_torp_hit_pts;
			$attack_damage = floor($attack_torp_hit_pts / $torp_hit_pts);
			if($attack_damage > 0)
			{
				$target_fighter_result[] = str_replace("[torpslost]", NUMBER($attack_damage), $l_cmb_attacker_torps_lost);
			}
			$target_fighter_result[] = $l_cmb_attacker_lost_all_torps;
			$attacker_torps_left2 = 0;
		}
		else
		{
			$attack_torp_hit_pts = $attack_torp_hit_pts - $target_fighter2_damage[0];
			$attack_torps_used = floor($target_fighter2_damage[0] / $torp_hit_pts);
			$target_fighter_result[] = str_replace("[torpslost]", NUMBER($attack_torps_used), $l_cmb_attacker_torps_lost);
			$attacker_torps_left2 = floor($attack_torp_hit_pts / $torp_hit_pts);
		}
	}
	else
	{
		$attack_fighter_hit_pts = $attack_fighter_hit_pts - $target_fighter_damage[0];
		$attack_fighters_used = floor($target_fighter_damage[0] / $fighter_hit_pts);
		$target_fighter_result[] = str_replace("[fighterslost]", NUMBER($attack_fighters_used), $l_cmb_attacker_fighters_lost);
		$attacker_fighters_left2 = floor($attack_fighter_hit_pts / $fighter_hit_pts);
		$attacker_torps_left2 = $attacker_torps_left;
	}
}
else
{
	$target_fighter_result[] = str_replace("[player]", $targetname, $l_cmb_target_no_send_fighteres);
	$attacker_fighters_left2 = $attacker_fighters_left;
	$attacker_torps_left2 = $attacker_torps_left;
}

$template_object->assign("target_fighter_result", $target_fighter_result);

$template_object->assign("stage3_attacker_energy", NUMBER($attacker_energy_left));
$template_object->assign("stage3_attacker_fighters", NUMBER($attacker_fighters_left2));
$template_object->assign("stage3_attacker_shields", NUMBER($attacker_shields_left));
$template_object->assign("stage3_attacker_torps", NUMBER($attacker_torps_left2));
$template_object->assign("stage3_attacker_armor", NUMBER($attacker_armor_left));

// Stage 3 torp Exchange

$template_object->assign("l_cmb_torp_exchange", $l_cmb_torp_exchange);

$attacker_torp_result = array();

if($attacker_torps_left2 != 0)
{
	$attack_torp_damage = calc_damage($attacker_torps_left2, $torp_damage_shields, $attackerlowpercent, $shipinfo['torp_launchers'], $targetshipshields);

	if($attack_torp_damage[2] > 0){
		$attacker_torp_result[] = $l_cmb_yourtorpfail1;
		$attacker_torp_result[] = str_replace("[percent]", (100 - $attack_torp_damage[2]), $l_cmb_yourtorpfail2);
	}

	$target_shields = calc_failure($target_shields_left, $targetshipshields, $shipinfo['torp_launchers']);
	$target_shield_hit_pts = $target_shields_left * $ship_shield_hit_pts;
	$target_armor = calc_failure($target_armor_left, $targetshiparmor, $shipinfo['torp_launchers']);

	$target_armor_hit_pts = $target_armor_left * $ship_armor_hit_pts;
	if($attack_torp_damage[0] > $target_shield_hit_pts)
	{
		$attack_torp_damage[0] = $attack_torp_damage[0] - $target_shield_hit_pts;
		if($target_shields_left > 0)
		{
			$attacker_torp_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($target_shields_left), $l_cmb_target_shields_hit));
		}
		$attacker_torp_result[] = str_replace("[player]", $targetname, $l_cmb_target_shields_down);
		$target_shields_left = 0;
		$attacker_torps_left2 = floor($attack_torp_damage[0] / $torp_damage_shields);
		$attack_torp2_damage = calc_damage($attacker_torps_left2, $torp_damage_all, $attackerlowpercent, $shipinfo['torp_launchers'], $targetshiparmor);

		if($attack_torp2_damage[2] > 0){
			$attacker_torp_result[] = $l_cmb_yourtorpfail1;
			$attacker_torp_result[] = str_replace("[percent]", (100 - $attack_torp2_damage[2]), $l_cmb_yourtorpfail2);
		}

		if($attack_torp2_damage[0] > $target_armor_hit_pts)
		{
			$attack_torp2_damage[0] = $attack_torp2_damage[0] - $target_armor_hit_pts;
			$attack_damage = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
			{
				$attacker_torp_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($attack_damage), $l_cmb_target_shields_hit));
			}
			$attacker_torp_result[] = str_replace("[player]", $targetname, $l_cmb_target_armor_down);
			$attacker_torps_left = floor($attack_torp2_damage[0] / $torp_damage_all);
			$target_armor_left = 0;
		}
		else
		{
			$target_armor_hit_pts = $target_armor_hit_pts - $attack_torp2_damage[0];
			$target_armor_used = floor($attack_torp2_damage[0] / $ship_armor_hit_pts);
			$attacker_torp_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($target_armor_used), $l_cmb_target_armor_hit));
			$target_armor_left = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			$attacker_torps_left = 0;
		}
	}
	else
	{
		$target_shield_hit_pts = $target_shield_hit_pts - $attack_torp_damage[0];
		$target_shields_used = floor($attack_torp_damage[0] / $ship_shield_hit_pts);
		$attacker_torp_result[] = str_replace("[player]", $targetname, str_replace("[damage]", NUMBER($target_shields_used), $l_cmb_target_shields_hit));
		$target_shields_left = floor($target_shield_hit_pts / $ship_shield_hit_pts);
		$attacker_torps_left = 0;
	}
}
else
{
	$attacker_torp_result[] = $l_cmb_attacker_no_torps;
	$attacker_torps_left = 0;
	$attack_torp_damage[1] = 0;
	$attack_torp2_damage[1] = 0;
}

$attacker_torps_left += ($attack_torp_damage[1] + $attack_torp2_damage[1]);

$template_object->assign("attacker_torp_result", $attacker_torp_result);

$target_torp_result = array();

if($target_torps_left2 != 0)
{
	$target_torp_damage = calc_damage($target_torps_left2, $torp_damage_shields, $targetlowpercent, $targetshiptorp_launchers, $shipinfo['shields']);

	if($target_torp_damage[2] == 100){
		$target_torp_result[] = str_replace("[player]", $targetname, $l_cmb_enemytorpfailshields);
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_torp_damage[0] = $target_torp_damage[0] * $defender_lucky_multiplier;
		$target_torp_result[] = str_replace("[times]", $defender_lucky_multiplier, $l_cmb_target_surprise_torps);
	}

	$attacker_shields = calc_failure($attacker_shields_left, $shipinfo['shields'], $targetshiptorp_launchers);
	$attack_shield_hit_pts = $attacker_shields_left * $ship_shield_hit_pts;
	$attacker_armor = calc_failure($attacker_armor_left, $shipinfo['shields'], $targetshiptorp_launchers);

	$attack_armor_hit_pts = $attacker_armor_left * $ship_armor_hit_pts;
	if($target_torp_damage[0] > $attack_shield_hit_pts)
	{
		$target_torp_damage[0] = $target_torp_damage[0] - $attack_shield_hit_pts;
		if($attacker_shields_left > 0)
		{
			$target_torp_result[] = str_replace("[damage]", NUMBER($attacker_shields_left), $l_cmb_attacker_shields_hit);
		}
		$target_torp_result[] = $l_cmb_attacker_shields_down;
		$attacker_shields_left = 0;
		$target_torps_left2 = floor($target_torp_damage[0] / $torp_damage_shields);
		$target_torp2_damage = calc_damage($target_torps_left2, $torp_damage_all, $targetlowpercent, $targetshiptorp_launchers, $shipinfo['armor']);

		if($target_torp2_damage[2] == 100){
			$target_torp_result[] = str_replace("[player]", $targetname, $l_cmb_enemytorpfailarmor);
		}

		if($target_torp2_damage[0] > $attack_armor_hit_pts)
		{
			$target_torp2_damage[0] = $target_torp2_damage[0] - $attack_armor_hit_pts;
			$attack_damage = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
			{
				$target_torp_result[] = str_replace("[damage]", NUMBER($attack_damage), $l_cmb_attacker_armor_hit);
			}
			$target_torp_result[] = $l_cmb_attacker_armor_down;
			$target_torps_left = floor($target_torp2_damage[0] / $torp_damage_all);
			$attacker_armor_left = 0;
		}
		else
		{
			$attack_armor_hit_pts = $attack_armor_hit_pts - $target_torp2_damage[0];
			$attacker_armor_used = floor($target_torp2_damage[0] / $ship_armor_hit_pts);
			$target_torp_result[] = str_replace("[damage]", NUMBER($attacker_armor_used), $l_cmb_attacker_armor_hit);
			$attacker_armor_left = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
			$target_torps_left = 0;
		}
	}
	else
	{
		$attack_shield_hit_pts = $attack_shield_hit_pts - $target_torp_damage[0];
		$attacker_shields_used = floor($target_torp_damage[0] / $ship_shield_hit_pts);
		$target_torp_result[] = str_replace("[damage]", NUMBER($attacker_shields_used), $l_cmb_attacker_shields_hit);
		$attacker_shields_left = floor($attack_shield_hit_pts / $ship_shield_hit_pts);
		$target_torps_left = 0;
	}
}
else
{
	$target_torp_result[] = str_replace("[player]", $targetname, $l_cmb_target_no_torps);
	$target_torps_left = 0;
	$target_torp_damage[1] = 0;
	$target_torp2_damage[1] = 0;
}

$target_torps_left += ($target_torp_damage[1] + $target_torp2_damage[1]);

$template_object->assign("target_torp_result", $target_torp_result);

$template_object->assign("end_attacker_energy", NUMBER($attacker_energy_left));
$template_object->assign("end_attacker_fighters", NUMBER($attacker_fighters_left2));
$template_object->assign("end_attacker_shields", NUMBER($attacker_shields_left));
$template_object->assign("end_attacker_torps", NUMBER($attacker_torps_left));
$template_object->assign("end_attacker_armor", NUMBER($attacker_armor_left));


if($attacktype == "planet")
{
	$success = SCAN_SUCCESS($shipinfo['sensors'], $planetinfo['cloak']);

	$template_object->assign("end_target_beams", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_energy_left)));
	$template_object->assign("end_target_fighters", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_fighters_left2)));
	$template_object->assign("end_target_shields", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_shields_left)));
	$template_object->assign("end_target_torps", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_torps_left)));
	$template_object->assign("end_target_armor", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_armor_left)));
}
else
{
	$success = SCAN_SUCCESS($shipinfo['sensors'], $targetship['cloak']);

	$template_object->assign("end_target_beams", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_energy_left)));
	$template_object->assign("end_target_fighters", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_fighters_left2)));
	$template_object->assign("end_target_shields", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_shields_left)));
	$template_object->assign("end_target_torps", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_torps_left)));
	$template_object->assign("end_target_armor", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $targetship['ecm'], $target_armor_left)));
}

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Combat End:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " $l_cmb_beams=<B>".$attacker_energy_left.
"</B>, $l_cmb_fighters=<B>".$attacker_fighters_left2."</B>, $l_cmb_shields: <B>$attacker_shields_left</B>, $l_cmb_torps: <B>$attacker_torps_left</B>. $l_cmb_armor=<B>$attacker_armor_left</B><br>Defender ".$targetname . " $l_cmb_beams=<B>".$target_energy_left.
"</B>, $l_cmb_fighters=<B>".$target_fighters_left2."</B>, $l_cmb_shields: <B>$target_shields_left</B>, $l_cmb_torps: <B>$target_torps_left</B>. $l_cmb_armor=<B>$target_armor_left</B>");

?>
