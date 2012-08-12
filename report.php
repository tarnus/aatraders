<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: report.php

include ("config/config.php");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_spy.inc");
include ("languages/$langdir/lang_dig.inc");
include ("globals/MakeBars.inc");

$title = $l_report_title;

if (checklogin())
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$shipinfo[class]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$classinfo = $debug_query->fields;

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

if (isset($_GET['sid']))  //Called fron the Spy menu
{
	$sid=$_GET['sid'];
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE owner_id=$playerinfo[player_id] and ship_id='$sid'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$ok = $debug_query->RecordCount();

	if ($ok)  // Player has a spy on the target ship. Let's change the ****info-s.
	{
        $debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE ship_id='$sid'", 1);
        db_op_result($debug_query,__LINE__,__FILE__);
        $shipinfo = $debug_query->fields;

		$shipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$sid", '', 'class');

        $debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$shipinfo[player_id]'", 1);
        db_op_result($debug_query,__LINE__,__FILE__);
        $playerinfo = $debug_query->fields;

        $debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$shipinfo[class]", 1);
        db_op_result($debug_query,__LINE__,__FILE__);
        $classinfo = $debug_query->fields;
	}
	else
	{
		$template_object->assign("error_msg", $l_report_cheater);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}

}

$holds_max = NUM_HOLDS($shipinfo['hull']);

$armor_pts_max = NUM_armor($shipinfo['armor']);
$ship_fighters_max = NUM_FIGHTERS($shipinfo['fighter']);
$torps_max = NUM_TORPEDOES($shipinfo['torp_launchers']);
$energy_max = NUM_ENERGY($shipinfo['power']);

$average_stats = (($shipinfo['hull_normal'] + $shipinfo['cloak_normal'] + $shipinfo['sensors_normal'] + $shipinfo['power_normal'] + $shipinfo['engines_normal'] + $shipinfo['fighter_normal'] + $shipinfo['armor_normal'] + $shipinfo['shields_normal'] + $shipinfo['beams_normal'] + $shipinfo['torp_launchers_normal'] + $shipinfo['ecm_normal'] ) / 11 );
$average_stats_max = (($classinfo['maxhull'] + $classinfo['maxcloak'] + $classinfo['maxsensors'] + $classinfo['maxpower'] + $classinfo['maxengines'] + $classinfo['maxfighter'] + $classinfo['maxarmor'] + $classinfo['maxshields'] + $classinfo['maxbeams'] + $classinfo['maxtorp_launchers'] + $classinfo['maxecm'] ) / 11 );

$hull_bars = MakeBars($shipinfo['hull'], $classinfo['maxhull'], "damage");
$engines_bars = MakeBars($shipinfo['engines'], $classinfo['maxengines'], "damage");
$power_bars = MakeBars($shipinfo['power'], $classinfo['maxpower'], "damage");
$fighter_bars = MakeBars($shipinfo['fighter'], $classinfo['maxfighter'], "damage");
$sensors_bars = MakeBars($shipinfo['sensors'], $classinfo['maxsensors'], "damage");
$armor_bars = MakeBars($shipinfo['armor'], $classinfo['maxarmor'], "damage");
$shields_bars = MakeBars($shipinfo['shields'], $classinfo['maxshields'], "damage");
$beams_bars = MakeBars($shipinfo['beams'], $classinfo['maxbeams'], "damage");
$torp_launchers_bars = MakeBars($shipinfo['torp_launchers'], $classinfo['maxtorp_launchers'], "damage");
$cloak_bars = MakeBars($shipinfo['cloak'], $classinfo['maxcloak'], "damage");
$ecm_bars = MakeBars($shipinfo['ecm'], $classinfo['maxecm'], "damage");
$average_bars = MakeBars($average_stats, $average_stats_max, "damage");

$hull_normal_bars = MakeBars($shipinfo['hull_normal'], $classinfo['maxhull'], "normal");
$engines_normal_bars = MakeBars($shipinfo['engines_normal'], $classinfo['maxengines'], "normal");
$power_normal_bars = MakeBars($shipinfo['power_normal'], $classinfo['maxpower'], "normal");
$fighter_normal_bars = MakeBars($shipinfo['fighter_normal'], $classinfo['maxfighter'], "normal");
$sensors_normal_bars = MakeBars($shipinfo['sensors_normal'], $classinfo['maxsensors'], "normal");
$armor_normal_bars = MakeBars($shipinfo['armor_normal'], $classinfo['maxarmor'], "normal");
$shields_normal_bars = MakeBars($shipinfo['shields_normal'], $classinfo['maxshields'], "normal");
$beams_normal_bars = MakeBars($shipinfo['beams_normal'], $classinfo['maxbeams'], "normal");
$torp_launchers_normal_bars = MakeBars($shipinfo['torp_launchers_normal'], $classinfo['maxtorp_launchers'], "normal");
$cloak_normal_bars = MakeBars($shipinfo['cloak_normal'], $classinfo['maxcloak'], "normal");
$ecm_normal_bars = MakeBars($shipinfo['ecm_normal'], $classinfo['maxecm'], "normal");

$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
$teamstuff = $result_team->fields;

$template_object->assign("teamicon", $teamstuff['icon']);
$template_object->assign("avatar", $playerinfo['avatar']);
$template_object->assign("enable_spies", $enable_spies);
$template_object->assign("enable_dignitaries", $enable_dignitaries);
$template_object->assign("shipname", $shipinfo['name']);
$template_object->assign("classname", $classinfo['name']);
$template_object->assign("classdescription", $classinfo['description']);
$template_object->assign("classimage", "templates/".$templatename."images/".$classinfo['image']);
$template_object->assign("l_ship_levels", $l_ship_levels);
$template_object->assign("l_damaged", $l_damaged);

$template_object->assign("l_hull", $l_hull);
$template_object->assign("l_hull_normal", $l_hull_normal);
$template_object->assign("shipinfo_hull", $shipinfo['hull']);
$template_object->assign("shipinfo_hull_normal", $shipinfo['hull_normal']);
$template_object->assign("classinfo_maxhull", $classinfo['maxhull']);
$template_object->assign("hull_bars", $hull_bars);
$template_object->assign("hull_normal_bars", $hull_normal_bars);

$template_object->assign("l_engines", $l_engines);
$template_object->assign("l_engines_normal", $l_engines_normal);
$template_object->assign("shipinfo_engines", $shipinfo['engines']);
$template_object->assign("shipinfo_engines_normal", $shipinfo['engines_normal']);
$template_object->assign("classinfo_maxengines", $classinfo['maxengines']);
$template_object->assign("engines_bars", $engines_bars);
$template_object->assign("engines_normal_bars", $engines_normal_bars);

$template_object->assign("l_power", $l_power);
$template_object->assign("l_power_normal", $l_power_normal);
$template_object->assign("shipinfo_power", $shipinfo['power']);
$template_object->assign("shipinfo_power_normal", $shipinfo['power_normal']);
$template_object->assign("classinfo_maxpower", $classinfo['maxpower']);
$template_object->assign("power_bars", $power_bars);
$template_object->assign("power_normal_bars", $power_normal_bars);

$template_object->assign("l_fighter", $l_fighter);
$template_object->assign("l_fighter_normal", $l_fighter_normal);
$template_object->assign("shipinfo_fighter", $shipinfo['fighter']);
$template_object->assign("shipinfo_fighter_normal", $shipinfo['fighter_normal']);
$template_object->assign("classinfo_maxfighter", $classinfo['maxfighter']);
$template_object->assign("fighter_bars", $fighter_bars);
$template_object->assign("fighter_normal_bars", $fighter_normal_bars);
$template_object->assign("shipinfo_fighter_class", AAT_substr($shipinfo['fighter_class'], 0, AAT_strpos($shipinfo['fighter_class'], "_")));

$template_object->assign("l_sensors", $l_sensors);
$template_object->assign("l_sensors_normal", $l_sensors_normal);
$template_object->assign("shipinfo_sensors", $shipinfo['sensors']);
$template_object->assign("shipinfo_sensors_normal", $shipinfo['sensors_normal']);
$template_object->assign("classinfo_maxsensors", $classinfo['maxsensors']);
$template_object->assign("sensors_bars", $sensors_bars);
$template_object->assign("sensors_normal_bars", $sensors_normal_bars);

$template_object->assign("l_avg_stats", $l_shipavg);
$template_object->assign("average_stats", NUMBER($average_stats,1));
$template_object->assign("average_stats_max", NUMBER($average_stats_max,1));
$template_object->assign("average_bars", $average_bars);

$template_object->assign("l_armor", $l_armor);
$template_object->assign("l_armor_normal", $l_armor_normal);
$template_object->assign("shipinfo_armor", $shipinfo['armor']);
$template_object->assign("shipinfo_armor_normal", $shipinfo['armor_normal']);
$template_object->assign("classinfo_maxarmor", $classinfo['maxarmor']);
$template_object->assign("armor_bars", $armor_bars);
$template_object->assign("armor_normal_bars", $armor_normal_bars);
$template_object->assign("shipinfo_armor_class", AAT_substr($shipinfo['armor_class'], 0, AAT_strpos($shipinfo['armor_class'], "_")));

$template_object->assign("l_shields", $l_shields);
$template_object->assign("l_shields_normal", $l_shields_normal);
$template_object->assign("shipinfo_shields", $shipinfo['shields']);
$template_object->assign("shipinfo_shields_normal", $shipinfo['shields_normal']);
$template_object->assign("classinfo_maxshields", $classinfo['maxshields']);
$template_object->assign("shields_bars", $shields_bars);
$template_object->assign("shields_normal_bars", $shields_normal_bars);
$template_object->assign("shipinfo_shields_class", AAT_substr($shipinfo['shield_class'], 0, AAT_strpos($shipinfo['shield_class'], "_")));

$template_object->assign("l_beams", $l_beams);
$template_object->assign("l_beams_normal", $l_beams_normal);
$template_object->assign("shipinfo_beams", $shipinfo['beams']);
$template_object->assign("shipinfo_beams_normal", $shipinfo['beams_normal']);
$template_object->assign("classinfo_maxbeams", $classinfo['maxbeams']);
$template_object->assign("beams_bars", $beams_bars);
$template_object->assign("beams_normal_bars", $beams_normal_bars);
$template_object->assign("shipinfo_beams_class", AAT_substr($shipinfo['beam_class'], 0, AAT_strpos($shipinfo['beam_class'], "_")));

$template_object->assign("l_torp_launch", $l_torp_launch);
$template_object->assign("l_torp_launch_normal", $l_torp_launch_normal);
$template_object->assign("shipinfo_torp_launchers", $shipinfo['torp_launchers']);
$template_object->assign("shipinfo_torp_launchers_normal", $shipinfo['torp_launchers_normal']);
$template_object->assign("classinfo_maxtorp_launchers", $classinfo['maxtorp_launchers']);
$template_object->assign("torp_launchers_bars", $torp_launchers_bars);
$template_object->assign("torp_launchers_normal_bars", $torp_launchers_normal_bars);
$template_object->assign("shipinfo_torp_launchers_class", AAT_substr($shipinfo['torp_class'], 0, AAT_strpos($shipinfo['torp_class'], "_")));

$template_object->assign("l_cloak", $l_cloak);
$template_object->assign("l_cloak_normal", $l_cloak_normal);
$template_object->assign("shipinfo_cloak", $shipinfo['cloak']);
$template_object->assign("shipinfo_cloak_normal", $shipinfo['cloak_normal']);
$template_object->assign("classinfo_maxcloak", $classinfo['maxcloak']);
$template_object->assign("cloak_bars", $cloak_bars);
$template_object->assign("cloak_normal_bars", $cloak_normal_bars);

$template_object->assign("l_ecm", $l_ecm);
$template_object->assign("l_ecm_normal", $l_ecm_normal);
$template_object->assign("shipinfo_ecm", $shipinfo['ecm']);
$template_object->assign("shipinfo_ecm_normal", $shipinfo['ecm_normal']);
$template_object->assign("classinfo_maxecm", $classinfo['maxecm']);
$template_object->assign("ecm_bars", $ecm_bars);
$template_object->assign("ecm_normal_bars", $ecm_normal_bars);

$template_object->assign("l_class", $l_class);
$template_object->assign("l_holds", $l_holds);
$template_object->assign("l_arm_weap", $l_arm_weap);
$template_object->assign("l_devices", $l_devices);
$template_object->assign("l_total_cargo", $l_total_cargo);
$template_object->assign("holds_max", NUMBER($holds_max));
$template_object->assign("l_energy", $l_energy);
$template_object->assign("shipinfo_energy", NUMBER($shipinfo['energy']));
$template_object->assign("energy_max", NUMBER($energy_max));
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("shipinfo_fighters", NUMBER($shipinfo['fighters']));
$template_object->assign("ship_fighters_max", NUMBER($ship_fighters_max));
$template_object->assign("l_torps", $l_torps);
$template_object->assign("shipinfo_torps", NUMBER($shipinfo['torps']));
$template_object->assign("torps_max", NUMBER($torps_max));
$template_object->assign("l_armorpts", $l_armorpts);
$template_object->assign("shipinfo_armor_pts", NUMBER($shipinfo['armor_pts']));
$template_object->assign("armor_pts_max", NUMBER($armor_pts_max));

$devicename = array();
$deviceamount = array();
$deviceclass = array();
$deviceprogram = array();

$count = 0;
foreach ($shipdevice as $key => $data) 
{
	$deviceprogram[$count] = $data['program'];
	$deviceclass[$count] = $data['class'];
	$devicename[$count] = $data['device_name'];
	$deviceamount[$count] = NUMBER($data['amount']);

	$device_type = $deviceclass[$count];
	if(!class_exists($device_type)){
		include ("class/devices/" . $device_type . ".inc");
	}
	$deviceobject = new $device_type();
	$deviceamount[$count] = $deviceobject->device_code();
	$deviceinfo[$count] = $deviceobject->report_code($deviceamount[$count]);

	$count++;
}

$template_object->assign("deviceprogram", $deviceprogram);
$template_object->assign("deviceclass", $deviceclass);
$template_object->assign("devicename", $devicename);
$template_object->assign("deviceamount", $deviceamount);
$template_object->assign("deviceinfo", $deviceinfo);

$template_object->assign("l_credits", $l_credits);
$template_object->assign("shipinfo_credits", NUMBER($playerinfo['credits']));
$template_object->assign("title", $title);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("templatename", $templatename);
$template_object->assign("l_spy_linkback", $l_spy_linkback);
$template_object->assign("spycheck", isset($_GET['sid']));

$res = $db->Execute("SELECT cargo_name, amount, hold_space FROM {$db_prefix}ship_holds WHERE ship_id=$playerinfo[currentship] ");

$cargo_items = 0;
$hold_space = 0;
while(!$res->EOF)
{
	$cargo_name[$cargo_items] = $res->fields['cargo_name'];

	$cargo_amount[$cargo_items] = NUMBER($res->fields['amount']);
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
$template_object->assign("hold_space_free", NUMBER(NUM_HOLDS($shipinfo['hull']) - $hold_space));
$template_object->assign("l_hold_space_used", $l_hold_space_used);
$template_object->assign("l_hold_space_free", $l_hold_space_free);

$template_object->assign("hold_space", NUMBER($hold_space));

$template_object->display($templatename."report.tpl");

include ("footer.php");

?>

