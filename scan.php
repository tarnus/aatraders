<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: report.php

include ("config/config.php");
include ("languages/$langdir/lang_scan.inc");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_planets.inc");
include ("globals/ship_bounty_check.inc");
include ("globals/MakeBars.inc");
include ("globals/device_ship_tech_modify.inc");

get_post_ifset("player_id, ship_id");

$title = $l_scan_title;

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$player_id'", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$targetinfo = $debug_query->fields;

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE ship_id=$ship_id", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$targetshipinfo = $debug_query->fields;

$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$ship_id", '', 'class');

$targetship = device_ship_tech_modify($targetship, $targetshipdevice);
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

/* check to ensure target is in the same sector as player */
if ($targetshipinfo['sector_id'] != $shipinfo['sector_id'] || $shipinfo['sector_id'] == 1)
{
	$template_object->assign("error_msg", $l_planet_noscan);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."scandie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_scan_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."scandie.tpl");
	include ("footer.php");
	die();
}


// determine per cent chance of success in scanning target ship - 
// Based on player's sensors and opponent's cloak

$success = SCAN_SUCCESS($shipinfo['sensors'], $targetshipinfo['cloak'], $shiptypes[$targetshipinfo['class']]['basehull']);

$roll = mt_rand(1, 100);
if ($roll > $success)
{
	// if scan fails - inform both player and target.
	playerlog($targetinfo['player_id'], "LOG6_SHIP_SCAN_FAIL", "$playerinfo[character_name]");
	$template_object->assign("error_msg", $l_planet_noscan);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."scandie.tpl");
	include ("footer.php");
	die();
}

// if scan succeeds, show results and inform target.
// cramble results by scan error factor.
// Get total bounty on this player, if any
$btyamount = 0;
$debug_query = $db->Execute("SELECT SUM(amount) AS btytotal FROM {$db_prefix}bounty WHERE bounty_on = $targetinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$scanbounty = 1;
$scanfedbounty = 1;

$isfedbounty = ship_bounty_check($playerinfo, $shipinfo['sector_id'], $targetinfo, 0);

if($isfedbounty > 0)
{
	$fedcheckbounty = $l_by_fedbounty;
	$btyamount = NUMBER($isfedbounty);
	$l_scan_bounty = str_replace("[amount]",$btyamount,$l_scan_bounty);
	$scanbounty = $l_scan_bounty;
}
else
{
	$fedcheckbounty = $l_by_nofedbounty;
}

$targetname = $targetshipinfo['name'];
$targetinfoname = $targetinfo['character_name'];

$sc_hull = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['hull']) : 0;
$sc_engines = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['engines']) : 0;
$sc_power = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['power']) : 0;
$sc_fighter = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['fighter']) : 0;
$sc_sensors = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['sensors']) : 0;
$sc_beams = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['beams']) : 0;
$sc_torp_launchers = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['torp_launchers']) : 0;
$sc_armor = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['armor']) : 0;
$sc_shields = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['shields']) : 0;
$sc_cloak = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['cloak']) : 0;
$sc_ecm = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['ecm']) : 0;
$sc_armor_pts = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['armor_pts']) : 0;
$sc_ship_fighters = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['fighters']) : 0;
$sc_torps = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['torps']) : 0;
$sc_credits = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['credits']) : 0;
$sc_ship_colonists = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $targetshipinfo['colonists']) : 0;

$res = $db->Execute("SELECT cargo_name, amount FROM {$db_prefix}ship_holds WHERE ship_id=$playerinfo[currentship] ");

$cargo_items = 0;
$hold_space = 0;
while(!$res->EOF)
{
	$cargo_name[$cargo_items] = $res->fields['cargo_name'];

	$cargo_amount[$cargo_items] = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $targetshipinfo['cloak'], $res->fields['amount']) : 0;
	$hold_space += ($res->fields['hold_space'] * $res->fields['amount']);
	$cargo_holds[$cargo_items] = $res->fields['hold_space'];

	$cargo_items++;
	$res->MoveNext();
}

$template_object->assign("cargo_holds", $cargo_holds);
$template_object->assign("cargo_items", $cargo_items);
$template_object->assign("cargo_name", $cargo_name);
$template_object->assign("cargo_amount", $cargo_amount);
$template_object->assign("hold_space_used", $hold_space);
$template_object->assign("hold_space_free", NUMBER(NUM_HOLDS($targetshipinfo['hull']) - $hold_space));
$template_object->assign("l_hold_space_used", $l_hold_space_used);
$template_object->assign("l_hold_space_free", $l_hold_space_free);

playerlog($targetinfo['player_id'], "LOG6_SHIP_SCAN", "$playerinfo[character_name]");

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$holds_max = NUM_HOLDS($sc_hull);
if($holds_max < $hold_space)
	$hold_space = $holds_max;

$armor_pts_max = NUM_armor($sc_armor);

$ship_fighters_max = NUM_FIGHTERS($sc_fighter);

$torps_max = NUM_TORPEDOES($sc_torp_launchers);

$energy_max = NUM_ENERGY($sc_power);

$average_stats = (($sc_hull + $sc_cloak + $sc_sensors + $sc_power + $sc_engines + $sc_fighter + $sc_armor + $sc_shields + $sc_beams + $sc_torp_launchers + $sc_ecm ) / 11 );

$hull_normal_bars = MakeBars($sc_hull, $max_tech_level, "normal");
$engines_normal_bars = MakeBars($sc_engines, $max_tech_level, "normal");
$power_normal_bars = MakeBars($sc_power, $max_tech_level, "normal");
$fighter_normal_bars = MakeBars($sc_fighter, $max_tech_level, "normal");
$sensors_normal_bars = MakeBars($sc_sensors, $max_tech_level, "normal");
$armor_normal_bars = MakeBars($sc_armor, $max_tech_level, "normal");
$shields_normal_bars = MakeBars($sc_shields, $max_tech_level, "normal");
$beams_normal_bars = MakeBars($sc_beams, $max_tech_level, "normal");
$torp_launchers_normal_bars = MakeBars($sc_torp_launchers, $max_tech_level, "normal");
$cloak_normal_bars = MakeBars($sc_cloak, $max_tech_level, "normal");
$ecm_normal_bars = MakeBars($sc_ecm, $max_tech_level, "normal");
$average_bars = MakeBars($average_stats, $max_tech_level, "normal");

$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$targetinfo[team]", 1);
$teamstuff = $result_team->fields;
$template_object->assign("scanbounty", $scanbounty);
$template_object->assign("scanfedbounty", $scanfedbounty);
$template_object->assign("fedcheckbounty", $fedcheckbounty);
$template_object->assign("l_scan_ron", $l_scan_ron);
$template_object->assign("l_scan_capt", $l_scan_capt);
$template_object->assign("targetinfoname", $targetinfoname);

$template_object->assign("teamicon", $teamstuff['icon']);
$template_object->assign("avatar", $targetinfo['avatar']);
$template_object->assign("shipname", $targetshipinfo['name']);
$template_object->assign("l_ship_levels", $l_ship_levels);

$template_object->assign("l_hull", $l_hull);
$template_object->assign("l_hull_normal", $l_hull_normal);
$template_object->assign("shipinfo_hull_normal", $sc_hull);
$template_object->assign("classinfo_maxhull", $max_tech_level);
$template_object->assign("hull_normal_bars", $hull_normal_bars);

$template_object->assign("l_engines", $l_engines);
$template_object->assign("l_engines_normal", $l_engines_normal);
$template_object->assign("shipinfo_engines_normal", $sc_engines);
$template_object->assign("classinfo_maxengines", $max_tech_level);
$template_object->assign("engines_normal_bars", $engines_normal_bars);

$template_object->assign("l_power", $l_power);
$template_object->assign("l_power_normal", $l_power_normal);
$template_object->assign("shipinfo_power_normal", $sc_power);
$template_object->assign("classinfo_maxpower", $max_tech_level);
$template_object->assign("power_normal_bars", $power_normal_bars);

$template_object->assign("l_fighter", $l_fighter);
$template_object->assign("l_fighter_normal", $l_fighter_normal);
$template_object->assign("shipinfo_fighter_normal", $sc_fighter);
$template_object->assign("classinfo_maxfighter", $max_tech_level);
$template_object->assign("fighter_normal_bars", $fighter_normal_bars);

$template_object->assign("l_sensors", $l_sensors);
$template_object->assign("l_sensors_normal", $l_sensors_normal);
$template_object->assign("shipinfo_sensors_normal", $sc_sensors);
$template_object->assign("classinfo_maxsensors", $max_tech_level);
$template_object->assign("sensors_normal_bars", $sensors_normal_bars);

$template_object->assign("l_avg_stats", $l_shipavg);
$template_object->assign("average_stats", NUMBER($average_stats,1));
$template_object->assign("average_bars", $average_bars);

$template_object->assign("l_armor", $l_armor);
$template_object->assign("l_armor_normal", $l_armor_normal);
$template_object->assign("shipinfo_armor_normal", $sc_armor);
$template_object->assign("classinfo_maxarmor", $max_tech_level);
$template_object->assign("armor_normal_bars", $armor_normal_bars);

$template_object->assign("l_shields", $l_shields);
$template_object->assign("l_shields_normal", $l_shields_normal);
$template_object->assign("shipinfo_shields_normal", $sc_shields);
$template_object->assign("classinfo_maxshields", $max_tech_level);
$template_object->assign("shields_normal_bars", $shields_normal_bars);

$template_object->assign("l_beams", $l_beams);
$template_object->assign("l_beams_normal", $l_beams_normal);
$template_object->assign("shipinfo_beams_normal", $sc_beams);
$template_object->assign("classinfo_maxbeams", $max_tech_level);
$template_object->assign("beams_normal_bars", $beams_normal_bars);

$template_object->assign("l_torp_launch", $l_torp_launch);
$template_object->assign("l_torp_launch_normal", $l_torp_launch_normal);
$template_object->assign("shipinfo_torp_launchers_normal", $sc_torp_launchers);
$template_object->assign("classinfo_maxtorp_launchers", $max_tech_level);
$template_object->assign("torp_launchers_normal_bars", $torp_launchers_normal_bars);

$template_object->assign("l_cloak", $l_cloak);
$template_object->assign("l_cloak_normal", $l_cloak_normal);
$template_object->assign("shipinfo_cloak_normal", $sc_cloak);
$template_object->assign("classinfo_maxcloak", $max_tech_level);
$template_object->assign("cloak_normal_bars", $cloak_normal_bars);

$template_object->assign("l_ecm", $l_ecm);
$template_object->assign("l_ecm_normal", $l_ecm_normal);
$template_object->assign("shipinfo_ecm_normal", $sc_ecm);
$template_object->assign("classinfo_maxecm", $max_tech_level);
$template_object->assign("ecm_normal_bars", $ecm_normal_bars);

$template_object->assign("l_holds", $l_holds);
$template_object->assign("l_arm_weap", $l_arm_weap);
$template_object->assign("l_devices", $l_devices);
$template_object->assign("l_total_cargo", $l_total_cargo);
$template_object->assign("holds_used", NUMBER($hold_space));
$template_object->assign("holds_max", NUMBER($holds_max));
$template_object->assign("energy_max", NUMBER($energy_max));
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("shipinfo_fighters", NUMBER($sc_ship_fighters));
$template_object->assign("ship_fighters_max", NUMBER($ship_fighters_max));
$template_object->assign("l_torps", $l_torps);
$template_object->assign("shipinfo_torps", NUMBER($sc_torps));
$template_object->assign("torps_max", NUMBER($torps_max));
$template_object->assign("l_armorpts", $l_armorpts);
$template_object->assign("shipinfo_armor_pts", NUMBER($sc_armor_pts));
$template_object->assign("armor_pts_max", NUMBER($armor_pts_max));

$template_object->assign("l_credits", $l_credits);
$template_object->assign("shipinfo_credits", NUMBER($sc_credits));
$template_object->assign("title", $title);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("templatename", $templatename);

$template_object->display($templatename."scan.tpl");

include ("footer.php");

?>

