<?php
include ("globals/planet_log.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/scanlevel.inc");
include ("globals/device_ship_tech_modify.inc");
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

function base_string($base)
{
	global $l_planet_based;
	return ($base=='Y') ? $l_planet_based : "N";
}

/* check to ensure target is in the same sector as player */
if ($planetinfo['sector_id'] != $shipinfo['sector_id'])
{
	$template_object->assign("error_msg", $l_planet_noscan);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."scandie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_plant_scn_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planetdie.tpl");
	include ("footer.php");
	die();
}

// determine per cent chance of success in scanning target ship - 
// Based on player's sensors and opponent's cloak

planet_log($planetinfo['planet_id'],$planetinfo['owner'],$playerinfo['player_id'],"PLOG_SCANNED");

/* determine per cent chance of success in scanning target ship - based on player's sensors and opponent's planet's cloak */
$success = SCAN_SUCCESS($shipinfo['sensors'], $planetinfo['cloak']);

$roll = mt_rand(1, 100);
if ($roll > $success)
{
	// if scan fails - inform both player and target.
	playerlog($planetinfo['owner'], "LOG6_PLANET_SCAN_FAIL", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
	$template_object->assign("error_msg", $l_planet_noscan);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planetdie.tpl");
	include ("footer.php");
	die();
}

// Player will get a Federation Bounty on themselves if they attack a player who's score is less than 
// bounty_ratio of themselves. If the target has a Federation Bounty, they can attack without attracting a bounty on themselves.

$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$planetinfo[owner]", 1);
$ownerinfo = $result3->fields;
$result3->close();

$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 0);

if($isfedbounty > 0)
{
	$fedcheckbounty = $l_by_fedbounty;
}
else
{
	$fedcheckbounty = $l_by_nofedbounty;
}

if (empty($planetinfo['name']))
   $planetinfo['name'] = $l_unnamed;

$targetname = $planetinfo['name'];
$targetinfoname = $ownerinfo['character_name'];

$sc_fighter = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['fighter']) : 0;
$sc_sensors = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['sensors']) : 0;
$sc_beams = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['beams']) : 0;
$sc_torp_launchers = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['torp_launchers']) : 0;
$sc_armor = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['armor']) : 0;
$sc_shields = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['shields']) : 0;
$sc_cloak = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['cloak']) : 0;
$sc_jammer = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['jammer']) : 0;
$sc_armor_pts = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['armor_pts']) : 0;
$sc_ship_fighters = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['fighters']) : 0;
$sc_torps = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['torps']) : 0;
$sc_credits = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['credits']) : 0;
$sc_ship_energy = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['energy']) : 0;
$sc_ship_colonists = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['colonists']) : 0;
$sc_ship_ore = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['ore']) : 0;
$sc_ship_organics = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['organics']) : 0;
$sc_sdweapons = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['sector_defense_weapons']) : 0;
$sc_sdsensors = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['sector_defense_sensors']) : 0;
$sc_sdcloak = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['sector_defense_cloak']) : 0;
$sc_ship_goods = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $planetinfo['goods']) : 0;

$sc_ship_special = (mt_rand(1, 100) < $success) ? SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], floor($planetinfo['special_amount'])) : 0;
$template_object->assign("l_specialname", ucwords($planetinfo['special_name']));
$template_object->assign("l_special_image", $planetinfo['special_name']);
$template_object->assign("planetinfo_special", NUMBER($sc_ship_special));


$sc_base = (mt_rand(1, 100) < $success) ? base_string($planetinfo['base']) : "N";

playerlog($planetinfo['owner'], "LOG6_PLANET_SCAN", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$average_stats = (($sc_cloak + $sc_sensors + $sc_fighter + $sc_armor + $sc_shields + $sc_beams + $sc_torp_launchers + $sc_jammer ) / 8 );

$fighter_normal_bars = MakeBars($sc_fighter, $max_tech_level, "normal");
$sensors_normal_bars = MakeBars($sc_sensors, $max_tech_level, "normal");
$armor_normal_bars = MakeBars($sc_armor, $max_tech_level, "normal");
$shields_normal_bars = MakeBars($sc_shields, $max_tech_level, "normal");
$beams_normal_bars = MakeBars($sc_beams, $max_tech_level, "normal");
$torp_launchers_normal_bars = MakeBars($sc_torp_launchers, $max_tech_level, "normal");
$cloak_normal_bars = MakeBars($sc_cloak, $max_tech_level, "normal");
$jammer_normal_bars = MakeBars($sc_jammer, $max_tech_level, "normal");

$sdweapons_normal_bars = MakeBars($sc_sdweapons, $max_tech_level, "normal");
$sdsensors_normal_bars = MakeBars($sc_sdsensors, $max_tech_level, "normal");
$sdcloak_normal_bars = MakeBars($sc_sdcloak, $max_tech_level, "normal");

$average_bars = MakeBars($average_stats, $max_tech_level, "normal");

$planetavg = scanlevel($planetinfo['fighter']) + scanlevel($planetinfo['sensors']) + scanlevel($planetinfo['beams']) + scanlevel($planetinfo['torp_launchers']) + scanlevel($planetinfo['shields']) + scanlevel($planetinfo['cloak']);
$maximum_colonists = $colonist_limit + floor($colonist_tech_add * $planetavg);
$planertavg += scanlevel(($planetinfo['colonists'] / $maximum_colonists) * $max_tech_level);
$planetavg =  floor((($planetavg / 7) / $max_tech_level) * 10 );

$planetlevel = max(0, min(10, $planetavg));

if($planetinfo['ore_planet'] >= 1 && $planetinfo['organics_planet'] >= 1)
{
	$planettype = "oo";
}

if($planetinfo['ore_planet'] >= 1 && $planetinfo['organics_planet'] < 1)
{
	$planettype = "oo-";
}

if($planetinfo['ore_planet'] < 1 && $planetinfo['organics_planet'] >= 1)
{
	$planettype = "o-o";
}

if($planetinfo['ore_planet'] < 1 && $planetinfo['organics_planet'] < 1)
{
	$planettype = "o-o-";
}
$template_object->assign("planettype", $planettype . (string)(max(0, min(10, $planetlevel)) + 1));

$res = $db->Execute("SELECT {$db_prefix}ships.*, {$db_prefix}players.character_name FROM {$db_prefix}ships LEFT JOIN " .
				   "{$db_prefix}players ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE " .
				   "on_planet = 'Y' and planet_id = $planetinfo[planet_id]");

$shipcount = 0;
while (!$res->EOF)
{
	$row = $res->fields;
	$success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], $shiptypes[$row['class']]['basehull']);
	$roll = mt_rand(1, 100);

	if ($roll < $success)
	{
		$playeronplanet[$shipcount] = $row['character_name'];
		$shipcount++;
	}
	$res->MoveNext();
}
$res->close();
$template_object->assign("l_planet_noone", ucfirst($l_planet_noone));
$template_object->assign("l_none", $l_none);
$template_object->assign("playeronplanet", $playeronplanet);
$template_object->assign("l_planet_ison", $l_planet_ison);
$template_object->assign("shipcount", $shipcount);
$template_object->assign("sc_base", $sc_base);

$template_object->assign("scanbounty", $scanbounty);
$template_object->assign("scanfedbounty", $scanfedbounty);
$template_object->assign("fedcheckbounty", $fedcheckbounty);
$template_object->assign("l_scan_ron", $l_scan_ron);
$template_object->assign("targetinfoname", $targetinfoname);

$template_object->assign("avatar", $ownerinfo['avatar']);
$template_object->assign("planetname", $planetinfo['name']);
$template_object->assign("l_planetary_defense_levels", $l_planetary_defense_levels);

$template_object->assign("l_planetary_fighter", $l_planetary_fighter);
$template_object->assign("planetinfo_fighter_normal", $sc_fighter);
$template_object->assign("classinfo_maxfighter", $max_tech_level);
$template_object->assign("fighter_normal_bars", $fighter_normal_bars);

$template_object->assign("l_planetary_sensors", $l_planetary_sensors);
$template_object->assign("planetinfo_sensors_normal", $sc_sensors);
$template_object->assign("classinfo_maxsensors", $max_tech_level);
$template_object->assign("sensors_normal_bars", $sensors_normal_bars);

$template_object->assign("l_avg_stats", $l_shipavg);
$template_object->assign("average_stats", NUMBER($average_stats,1));
$template_object->assign("average_bars", $average_bars);

$template_object->assign("l_planetary_armor", $l_planetary_armor);
$template_object->assign("planetinfo_armor_normal", $sc_armor);
$template_object->assign("classinfo_maxarmor", $max_tech_level);
$template_object->assign("armor_normal_bars", $armor_normal_bars);

$template_object->assign("l_planetary_shields", $l_planetary_shields);
$template_object->assign("planetinfo_shields_normal", $sc_shields);
$template_object->assign("classinfo_maxshields", $max_tech_level);
$template_object->assign("shields_normal_bars", $shields_normal_bars);

$template_object->assign("l_planetary_beams", $l_planetary_beams);
$template_object->assign("planetinfo_beams_normal", $sc_beams);
$template_object->assign("classinfo_maxbeams", $max_tech_level);
$template_object->assign("beams_normal_bars", $beams_normal_bars);

$template_object->assign("l_planetary_torp_launch", $l_planetary_torp_launch);
$template_object->assign("planetinfo_torp_launchers_normal", $sc_torp_launchers);
$template_object->assign("classinfo_maxtorp_launchers", $max_tech_level);
$template_object->assign("torp_launchers_normal_bars", $torp_launchers_normal_bars);

$template_object->assign("l_planetary_cloak", $l_planetary_cloak);
$template_object->assign("planetinfo_cloak_normal", $sc_cloak);
$template_object->assign("classinfo_maxcloak", $max_tech_level);
$template_object->assign("cloak_normal_bars", $cloak_normal_bars);

$template_object->assign("l_planetary_jammer", $l_planetary_jammer);
$template_object->assign("planetinfo_jammer_normal", $sc_jammer);
$template_object->assign("classinfo_maxjammer", $max_tech_level);
$template_object->assign("jammer_normal_bars", $jammer_normal_bars);


$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
$template_object->assign("planetinfo_sdweapons_normal", $sc_sdweapons);
$template_object->assign("classinfo_maxsdweapons", $max_tech_level);
$template_object->assign("sdweapons_normal_bars", $sdweapons_normal_bars);

$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
$template_object->assign("planetinfo_sdsensors_normal", $sc_sdsensors);
$template_object->assign("classinfo_maxsdsensors", $max_tech_level);
$template_object->assign("sdsensors_normal_bars", $sdsensors_normal_bars);

$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);
$template_object->assign("planetinfo_sdcloak_normal", $sc_sdcloak);
$template_object->assign("classinfo_maxsdcloak", $max_tech_level);
$template_object->assign("sdcloak_normal_bars", $sdcloak_normal_bars);


$template_object->assign("l_holds", $l_holds);
$template_object->assign("l_arm_weap", $l_arm_weap);
$template_object->assign("l_devices", $l_devices);
$template_object->assign("l_total_cargo", $l_total_cargo);
$template_object->assign("holds_used", NUMBER($holds_used));
$template_object->assign("l_ore", $l_ore);
$template_object->assign("planetinfo_ore", NUMBER($sc_ship_ore));
$template_object->assign("l_organics", $l_organics);
$template_object->assign("planetinfo_organics", NUMBER($sc_ship_organics));
$template_object->assign("l_goods", $l_goods);
$template_object->assign("planetinfo_goods", NUMBER($sc_ship_goods));
$template_object->assign("l_colonists", $l_colonists);
$template_object->assign("planetinfo_colonists", NUMBER($sc_ship_colonists));
$template_object->assign("l_energy", $l_energy);
$template_object->assign("planetinfo_energy", NUMBER($sc_ship_energy));
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("planetinfo_fighters", NUMBER($sc_ship_fighters));
$template_object->assign("l_torps", $l_torps);
$template_object->assign("planetinfo_torps", NUMBER($sc_torps));
$template_object->assign("l_armorpts", $l_armorpts);
$template_object->assign("planetinfo_armor_pts", NUMBER($sc_armor_pts));
$template_object->assign("l_credits", $l_credits);
$template_object->assign("planetinfo_credits", NUMBER($sc_credits));
$template_object->assign("title", $title);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("templatename", $templatename);

$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
$template_object->assign("allow_ibank", $allow_ibank);
$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
$template_object->assign("planet_id", $planetinfo['planet_id']);
$template_object->assign("l_igb_term", $l_igb_term);
$template_object->assign("l_by_placebounty", $l_by_placebounty);

$template_object->display($templatename."planet_unowned/planet_scan.tpl");

include ("footer.php");

?>

