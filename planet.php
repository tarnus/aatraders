<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: planet.php

include ("config/config.php");
include ("languages/$langdir/lang_planet.inc");
include ("languages/$langdir/lang_planets.inc");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_combat.inc");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_ports.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_shipyard.inc");
include ("languages/$langdir/lang_traderoute.inc");
include ("languages/$langdir/lang_spy.inc");
include ("languages/$langdir/lang_dig.inc");
include ("globals/spy_detect_planet.inc");
include ("globals/MakeBars.inc");
include ("globals/calc_ownership.inc");
include ("globals/spy_sneak_to_planet.inc");
include ("globals/spy_sneak_to_ship.inc");


get_post_ifset("command, destroy, planet_id");

$title = $l_planet_title;

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

if ((!isset($command)) || ($command == ''))
{
	$command = 'display';
}

$planet_id = stripnum($planet_id);

$result3 = $db->SelectLimit("SELECT pl.*, un.sector_name FROM {$db_prefix}planets as pl, {$db_prefix}universe as un WHERE pl.planet_id=$planet_id and un.sector_id=pl.sector_id", 1);
if ($result3)
  $planetinfo=$result3->fields;

// No planet

if (empty($planetinfo))
{
	$template_object->assign("error_msg", $l_planet_none);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planetdie.tpl");
	include ("footer.php");
	die();
}


if ($shipinfo['sector_id'] != $planetinfo['sector_id'])
{
	if ($shipinfo['on_planet'] == 'Y')
	{
	  $debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet='N' WHERE ship_id=$shipinfo[ship_id]");
	  db_op_result($debug_query,__LINE__,__FILE__);
	}
	$template_object->assign("error_msg", $l_planet_none);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planetdie.tpl");
	include ("footer.php");
	die();
}

if (($planetinfo['owner'] == 0  || $planetinfo['defeated'] == 'Y') && $command != "capture")
{
	$capture_link="<a href='planet.php?planet_id=$planet_id&command=capture'>$l_planet_capture1</a>";
	$l_planet_capture2=str_replace("[capture]",$capture_link,$l_planet_capture2);
	$template_object->assign("error_msg", $l_planet_capture2);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planetdie.tpl");
	include ("footer.php");
	die();
}

if ($planetinfo['owner'] != 0)
{
	if ($enable_spies)
	{
	  spy_detect_planet($shipinfo['ship_id'], $planetinfo['planet_id'], $planet_detect_success1);
	}
	$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$planetinfo[owner]", 1);
	$ownerinfo = $result3->fields;

	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id=$planetinfo[owner] AND ship_id=$ownerinfo[currentship]", 1);
	$ownershipinfo = $res->fields;
}

if ($planetinfo['owner'] == $playerinfo['player_id'] || ($planetinfo['team'] == $playerinfo['team'] && $playerinfo['team'] > 0 && $planetinfo['owner'] > 0))
{
	spy_sneak_to_planet($planetinfo['planet_id'], $shipinfo['ship_id']);
	spy_sneak_to_ship($planetinfo['planet_id'], $shipinfo['ship_id']);
	$found = @include ("planet_owned/" . $command . ".inc");
	$is_owned = "You own or team owned.";
}
else
{
	if($ownerinfo['team'] == $playerinfo['team'] && $ownerinfo['team'] != 0)
	{
		$command = "display_team";
	}
	$found = @include ("planet_unowned/" . $command . ".inc");
	$is_owned = "Planet not owned by you or your team.";
}

if(!$found)
{
	$template_object->assign("error_msg", "Illegal Command ($command) you freaking cheater.  $is_owned ($planetinfo[owner]) ($playerinfo[player_id]) ($planetinfo[team]) ($playerinfo[team])");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planetdie.tpl");
	include ("footer.php");
	die();
}

close_database();

?>
