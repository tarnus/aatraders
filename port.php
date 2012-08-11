<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: port.php

include ("config/config.php");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_ports.inc");
include ("languages/$langdir/lang_device.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_spy.inc");
include ("languages/$langdir/lang_dig.inc");

get_post_ifset("pay");

$template_object->enable_gzip = 1;

$title = $l_title_port;

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$shipinfo[class]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$classinfo = $debug_query->fields;

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id=$sectorinfo[zone_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$zoneinfo = $debug_query->fields;

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

$template_object->assign("templatename", $templatename);

if ($zoneinfo['zone_id'] == 4)
{
	$title=$l_sector_war;

		$template_object->assign("error_msg", $l_war_info);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");

	die();
}
elseif ($zoneinfo['allow_trade'] == 'N')
{
	$title="Trade forbidden";

		$template_object->assign("error_msg", $l_no_trade_info);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");

	die();
}

elseif ($zoneinfo['allow_trade'] == 'L')
{
	if ($zoneinfo[team_zone] == 'N')
	{
	$res = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$zoneinfo[owner]", 1);
	$ownerinfo = $res->fields;

	if ($playerinfo['player_id'] != $zoneinfo['owner'] && $playerinfo['team'] == 0 || $playerinfo['team'] != $ownerinfo['team'])
	{
		$title=$l_ports_tradeforbidden;
		$template_object->assign("error_msg", $l_ports_nooutsiders);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");

		die();
	}
	}
	else
	{
	if ($playerinfo['team'] != $zoneinfo['owner'])
	{
		$title=$l_no_trade;
		$template_object->assign("error_msg", $l_no_trade_out);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");

		die();
	}
	}
}

$artifact_description = array();
$artifact_id = array();
$artifactimage = array();
$artifactname = array();
$artifactcount = 0;
$result4 = $db->Execute("SELECT artifact_id, artifact_type, cloak, scoremax FROM {$db_prefix}artifacts WHERE sector_id=$shipinfo[sector_id] and on_port=1");
db_op_result($result4,__LINE__,__FILE__);

while (!$result4->EOF)
{
	$row = $result4->fields;
	if($row['scoremax'] == 0 || $playerinfo['score'] < $row['scoremax'])
	{
		$success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], 1);

		$roll = mt_rand(1, 100);
		if ($roll < $success)
		{
			if(!class_exists($row['artifact_type'])){
				include ("class/artifacts/" . $row['artifact_type'] . ".inc");
			}
			$artifact_object = new $row['artifact_type'];

			$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $artifact_object->class . "'");
	   		db_op_result($res,__LINE__,__FILE__);
			if($res->fields['total'] < $artifact_object->pieces)
			{
				$artifactname[$artifactcount] = $artifact_object->classname;
				$artifact_description[$artifactcount] = addslashes($artifact_object->description);
				$artifact_id[$artifactcount] = $row['artifact_id'];
				$artifactimage[$artifactcount] = $row['artifact_type'];
				$artifactcount++;
			}
		}
	}
	$result4->MoveNext();
}

$template_object->assign("artifactimage", $artifactimage);
$template_object->assign("artifact_id", $artifact_id);
$template_object->assign("artifact_description", $artifact_description);
$template_object->assign("artifactname", $artifactname);
$template_object->assign("artifactcount", $artifactcount);

if(AAT_strtolower($sectorinfo['port_type']) == "devices" || AAT_strtolower($sectorinfo['port_type']) == "casino" || AAT_strtolower($sectorinfo['port_type']) == "none" || AAT_strtolower($sectorinfo['port_type']) == "spacedock" || AAT_strtolower($sectorinfo['port_type']) == "upgrades")
{
	include ("ports/" . AAT_strtolower($sectorinfo['port_type']) . ".inc");
}
else
{
	include ("ports/commodity_view.inc");
}
?>
