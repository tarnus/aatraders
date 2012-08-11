<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: zoneedit.php

include ("config/config.php");
include ("languages/$langdir/lang_zoneinfo.inc");
include ("languages/$langdir/lang_zoneedit.inc");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_ports.inc");
include ("globals/clean_words.inc");

get_post_ifset("command, nbeacon, lbeacon, nattack, nwarpedit, lwarpedit, ndefense, ldefense, nplanet, lplanet, ntrade, ltrade, yplanet, name, attacks, warpedits, planets, beacons, trades, defenses");

$title = $l_ze_title;

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id=$sectorinfo[zone_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$zoneinfo = $debug_query->fields;

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

if ($zoneinfo['team_zone'] == 'N')
{
	$result = $db->SelectLimit("SELECT player_id FROM {$db_prefix}players WHERE player_id=$playerinfo[player_id]", 1);
	$ownerinfo = $result->fields;
}
else
{
	$result = $db->SelectLimit("SELECT creator, id FROM {$db_prefix}teams WHERE creator=$zoneinfo[owner]", 1);
	$ownerinfo = $result->fields;
}

if (($zoneinfo['team_zone'] == 'N' && $zoneinfo['owner'] != $ownerinfo['player_id']) || ($zoneinfo['team_zone'] == 'Y' && $zoneinfo['owner'] != $ownerinfo['id'] && $row[owner] == $ownerinfo['creator']))
{
	zoneedit_die($l_ze_notowner);
	include ("footer.php");
	die();
}

if ($command == 'change')
{
	zoneedit_change();
	include ("footer.php");
	die();
}

if ($zoneinfo['allow_beacon'] == 'Y'){
	$ybeacon = "checked";
}
elseif ($zoneinfo['allow_beacon'] == 'N'){
	$nbeacon = "checked";
}else{
	$lbeacon = "checked";
}

if ($zoneinfo['allow_attack'] == 'Y')
{
	$yattack = "checked";
}
else
{
	$nattack = "checked";
}

if ($zoneinfo['allow_warpedit'] == 'Y')
{
	$ywarpedit = "checked";
}
elseif ($zoneinfo['allow_warpedit'] == 'N')
{
	$nwarpedit = "checked";
}
else
{
	$lwarpedit = "checked";
}

if ($zoneinfo['allow_planet'] == 'Y')
{
	$yplanet = "checked";
}
elseif ($zoneinfo['allow_planet'] == 'N')
{
	$nplanet = "checked";
}
else
{
	$lplanet = "checked";
}

if ($zoneinfo['allow_trade'] == 'Y')
{
	$ytrade = "checked";
}
elseif ($zoneinfo['allow_trade'] == 'N')
{
	$ntrade = "checked";
}
else
{
	$ltrade = "checked";
}

if ($zoneinfo['allow_defenses'] == 'Y')
{
	$ydefense = "checked";
}
elseif ($zoneinfo['allow_defenses'] == 'N')
{
	$ndefense = "checked";
}
else
{
	$ldefense = "checked";
}

$template_object->assign("zone", $zoneinfo['zone_id']);
$template_object->assign("l_ze_name", $l_ze_name);
$template_object->assign("name", $zoneinfo['zone_name']);
$template_object->assign("l_beacons", $l_beacons);
$template_object->assign("ybeacon", $ybeacon);
$template_object->assign("l_yes", $l_yes);
$template_object->assign("nbeacon", $nbeacon);
$template_object->assign("l_no", $l_no);
$template_object->assign("lbeacon", $lbeacon);
$template_object->assign("l_zi_limit", $l_zi_limit);
$template_object->assign("l_ze_attacks", $l_ze_attacks);
$template_object->assign("yattack", $yattack);
$template_object->assign("nattack", $nattack);
$template_object->assign("l_ze_allow", $l_ze_allow);
$template_object->assign("l_warpedit", $l_warpedit);
$template_object->assign("ywarpedit", $ywarpedit);
$template_object->assign("nwarpedit", $nwarpedit);
$template_object->assign("lwarpedit", $lwarpedit);
$template_object->assign("l_sector_def", $l_sector_def);
$template_object->assign("ydefense", $ydefense);
$template_object->assign("ndefense", $ndefense);
$template_object->assign("ldefense", $ldefense);
$template_object->assign("l_ze_genesis", $l_ze_genesis);
$template_object->assign("yplanet", $yplanet);
$template_object->assign("nplanet", $nplanet);
$template_object->assign("lplanet", $lplanet);
$template_object->assign("l_title_port", $l_title_port);
$template_object->assign("ytrade", $ytrade);
$template_object->assign("ntrade", $ntrade);
$template_object->assign("ltrade", $ltrade);
$template_object->assign("l_submit", $l_submit);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("zone2", $zone);
$template_object->assign("l_ze_return", $l_ze_return);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."zoneedit.tpl");

include ("footer.php");

//-----------------------------------------------------------------

function zoneedit_change()
{
	global $templatename, $template_object, $sectorinfo;
	global $name, $l_global_mmenu, $l_ze_namematch;
	global $attacks;
	global $warpedits;
	global $planets;
	global $beacons;
	global $trades;
	global $defenses;
	global $l_clickme, $l_ze_saved, $l_ze_return;
	global $db,$db_prefix;

	$name = trim($name);
	
	$result = $db->Execute ("SELECT zone_name FROM {$db_prefix}zones where zone_id!=$sectorinfo[zone_id]");

	if ($result>0)
	{
		while (!$result->EOF)
		{
			$zone_name = $result->fields['zone_name'];

			if (AAT_strtolower($zone_name) == AAT_strtolower($name) || metaphone($zone_name) == metaphone($name) || $name == '') 
			{ 
				$template_object->assign("l_ze_namematch", $l_ze_namematch);
				$template_object->assign("zone", $zone);
				$template_object->assign("l_clickme", $l_clickme);
				$template_object->assign("l_ze_return", $l_ze_return);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."zoneeditsamename.tpl");
				include ("footer.php");
				die();
			}
			$result->MoveNext();
		}
	}

	if (metaphone("unowned") == metaphone($name) || metaphone("unknown") == metaphone($name) || metaphone("unchartered") == metaphone($name) || metaphone("uncharted") == metaphone($name) || metaphone("federation") == metaphone($name) || metaphone("independent") == metaphone($name)) 
	{
		$name = "Cheater";
	}

	$name = clean_words($name);

	$debug_query = $db->Execute("UPDATE {$db_prefix}zones SET zone_name=" . $db->qstr($name) . ", allow_beacon='$beacons', allow_attack='$attacks', allow_warpedit='$warpedits', allow_planet='$planets', allow_trade='$trades', allow_defenses='$defenses' WHERE zone_id=$sectorinfo[zone_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$template_object->assign("l_ze_saved", $l_ze_saved);
	$template_object->assign("zone", $zone);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_ze_return", $l_ze_return);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."zoneeditchange.tpl");

}

function zoneedit_die($error_msg)
{

	global $templatename, $template_object, $l_global_mmenu;
	$template_object->assign("error_msg", $error_msg);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."zoneeditdie.tpl");

}

?>
