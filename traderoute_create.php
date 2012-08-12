<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the		 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: traderoute_create.php

include ("config/config.php");
include ("languages/$langdir/lang_traderoute.inc");
include ("languages/$langdir/lang_teams.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_ports.inc");
$total_experience = 0;

$title = $l_tdr_title;

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

//-------------------------------------------------------------------------------------------------

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$result = $db->Execute("SELECT * FROM {$db_prefix}traderoutes WHERE player_id=$playerinfo[player_id]");
$num_traderoutes = $result->RecordCount();

$i = 0;
while (!$result->EOF)
{
	$traderoutes[$i] = $result->fields;
	$i++;
	$result->MoveNext();
}

if ($num_traderoutes >= $max_traderoutes_player)
{
	$template_object->assign("error_msg", $l_tdr_maxtdr);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."traderoute_die.tpl");
	include ("footer.php");
	die();
}

$template_object->assign("l_tdr_createnew", $l_tdr_createnew);
$template_object->assign("l_tdr_traderoute", $l_tdr_traderoute);

$result = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE owner=$playerinfo[player_id] ORDER BY sector_id");

$num_planets = $result->RecordCount();
$i=0;
while (!$result->EOF)
{
	$planets[$i] = $result->fields;
	if ($planets[$i]['name'] == "")
		$planets[$i]['name'] = $l_tdr_unnamed;
	$i++;
	$result->MoveNext();
}
/*
$result = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE team=$playerinfo[team] AND team!=0 AND owner<>$playerinfo[player_id] ORDER BY sector_id");
$num_team_planets = $result->RecordCount();
$i=0;
while (!$result->EOF)
{
	$planets_team[$i] = $result->fields;
	if ($planets_team[$i]['name'] == "")
		$planets_team[$i]['name'] = $l_tdr_unnamed;
	$i++;
	$result->MoveNext();
}
*/
$template_object->assign("l_tdr_cursector", $l_tdr_cursector);
$template_object->assign("shipsector", $sectorinfo['sector_name']);

$template_object->assign("l_tdr_selspoint", $l_tdr_selspoint);
$template_object->assign("l_tdr_port", $l_tdr_port);

//-------------------- Personal Planet
$template_object->assign("l_tdr_planet", $l_tdr_planet);
$template_object->assign("num_planets", $num_planets);
$template_object->assign("l_tdr_none", $l_tdr_none);
$planetspecial = "";
if ($num_planets != 0)
{
	$planetcount=0;
	while ($planetcount < $num_planets)
	{
		if ($planets[$planetcount]['planet_id'] == $editroute['source_id']){
			$planetselected[$planetcount] = "selected ";
		}else{
			$planetselected[$planetcount] = " ";
		}
		$planetid[$planetcount] = $planets[$planetcount]['planet_id'];
		$planetname[$planetcount] = $planets[$planetcount]['name'];
		$planetspecial .= "planetspecial[" . $planetid[$planetcount] . "] = '" . $planets[$planetcount]['special_name'] . "';\n";
		$name_result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=" . $planets[$planetcount]['sector_id'], 1);
		$planetsectorid[$planetcount] = $name_result->fields['sector_name'];
		$planetcount++;
	}
}
$template_object->assign("planetspecial", $planetspecial);
$template_object->assign("planetcount", $planetcount);
$template_object->assign("planetselected", $planetselected);
$template_object->assign("l_tdr_insector", $l_tdr_insector);
$template_object->assign("planetid", $planetid);
$template_object->assign("planetname", $planetname);
$template_object->assign("planetsectorid", $planetsectorid);

//----------------------- team Planet
/*
$template_object->assign("l_team", $l_team);

$template_object->assign("num_team_planets", $num_team_planets);
$planetspecialteam="";
if ($num_team_planets != 0)
{
	$planetcountteam=0;
	while ($planetcountteam < $num_team_planets)
	{
		if ($planets_team[$planetcountteam]['planet_id'] == $editroute['source_id']){
			$planetselectedteam[$planetcountteam] = "selected ";
		}else{
			$planetselectedteam[$planetcountteam] = " ";
		}
		$planetidteam[$planetcountteam] = $planets_team[$planetcountteam]['planet_id'];
		$planetnameteam[$planetcountteam] = $planets_team[$planetcountteam]['name'];
		$planetspecialteam .= "planetspecialteam[" . $planetidteam[$planetcountteam] . "] = '" . $planets_team[$planetcountteam]['special_name'] . "';\n";
		$name_result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=" . $planets_team[$planetcountteam]['sector_id'], 1);
		$planetsectoridteam[$planetcountteam] = $name_result->fields['sector_name'];
		$planetcountteam++;
	}
}
$template_object->assign("planetspecialteam", $planetspecialteam);
*/
$commodity_item_count=1;
$commodity_commodity_type[0] = "None";
$debug_query = $db->Execute("SELECT classname FROM {$db_prefix}class_modules_commodities WHERE defaultcargoplanet=1");
db_op_result($debug_query,__LINE__,__FILE__);
while(!$debug_query->EOF){
	$commodity_commodity_type[$commodity_item_count] = $debug_query->fields['classname'];
	$commodity_item_count++;
	$debug_query->MoveNext();
}

$template_object->assign("commodity_item_count", $commodity_item_count);
$template_object->assign("commodity_commodity_type", $commodity_commodity_type);
//$template_object->assign("planetcountteam", $planetcountteam);
//$template_object->assign("planetselectedteam", $planetselectedteam);
//$template_object->assign("planetidteam", $planetidteam);
//$template_object->assign("planetnameteam", $planetnameteam);
//$template_object->assign("planetsectoridteam", $planetsectoridteam);

$template_object->assign("l_tdr_selendpoint", $l_tdr_selendpoint);
//$template_object->assign("planetsectoridteam", $planetsectoridteam);

$template_object->assign("l_tdr_selmovetype", $l_tdr_selmovetype);
$template_object->assign("l_tdr_realspace", $l_tdr_realspace);
$template_object->assign("l_tdr_warp", $l_tdr_warp);
$template_object->assign("l_tdr_selcircuit", $l_tdr_selcircuit);
$template_object->assign("l_tdr_oneway", $l_tdr_oneway);
$template_object->assign("l_tdr_bothways", $l_tdr_bothways);
$template_object->assign("l_tdr_create", $l_tdr_create);
$template_object->assign("l_tdr_returnmenu", $l_tdr_returnmenu);
$template_object->assign("l_tdr_tdrescooped", $l_tdr_tdrescooped);
$template_object->assign("l_tdr_trade", $l_tdr_trade);
$template_object->assign("l_tdr_keep", $l_tdr_keep);
$template_object->assign("l_tdr_fighters", $l_tdr_fighters);
$template_object->assign("l_tdr_torps", $l_tdr_torps);
$template_object->assign("l_upgrade_ports", $l_upgrade_ports);
$template_object->assign("l_port", $l_port);
$template_object->assign("l_trade", $l_trade);
$template_object->assign("l_commodity", $l_commodity);
$template_object->assign("l_planets", $l_planets);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."traderoute_create.tpl");
include ("footer.php");

?>
