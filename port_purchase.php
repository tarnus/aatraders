<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: port_purchase.php

include ("config/config.php");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_ports.inc");

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

if($zoneinfo['zone_id'] != 3)
{
	$alliancefactor = 1;
}
else
{
	$res2 = $db->Execute("SELECT COUNT(*) as number_of_bounties FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1) AND bounty_on = $playerinfo[player_id]");
	db_op_result($res2,__LINE__,__FILE__);
	if ($res2)
	{
		$alliancefactor = $alliancefactor * max($res2->fields['number_of_bounties'], 1);
	}
	$res2->close();
}

if ($zoneinfo['allow_trade'] == 'N')
{
	$title=$l_no_trade;
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
			$title=$l_no_trade;
			$template_object->assign("error_msg", $l_no_trade_out);
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

$trade_deficit = "$l_cost";
$trade_benefit = "$l_profit";
$template_object->assign("l_cost", $l_cost);
$template_object->assign("l_profit", $l_profit);

function phpTrueDelta($futurevalue,$shipvalue)
{
	$tempval = $futurevalue - $shipvalue;
	return $tempval;
}

if(AAT_strtolower($sectorinfo['port_type']) == "devices" || AAT_strtolower($sectorinfo['port_type']) == "none" || AAT_strtolower($sectorinfo['port_type']) == "spacedock" || AAT_strtolower($sectorinfo['port_type']) == "upgrades")
{
	include ("ports/purchase_" . AAT_strtolower($sectorinfo['port_type']) . ".inc");
}
else
{
	include ("ports/commodity_purchase.inc");

}
?>
