<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: warpedit.php

include ("config/config.php");
include ("languages/$langdir/lang_warpedit1.inc");
include ("languages/$langdir/lang_report.inc");
include ("globals/calc_dist.inc");

get_post_ifset("confirm, target_sector, oneway, bothway");

$title = $l_warp_title;

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

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_warp_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpeditdie.tpl");
	include ("footer.php");
	die();
}

if ($shipdevice['dev_warpedit']['amount'] < 1)
{
	$template_object->assign("error_msg", $l_warp_none);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpeditdie.tpl");
	include ("footer.php");
	die();
}

if ($zoneinfo['allow_warpedit'] == 'N')
{
	$template_object->assign("error_msg", $l_warp_forbid);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpeditdie.tpl");
	include ("footer.php");
	die();
}

if ($zoneinfo['allow_warpedit'] == 'L')
{
	$result5 = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id='$zoneinfo[owner]'", 1);
	$zoneteam = $result5->fields;

	if ($zoneinfo['owner'] != $playerinfo['player_id'])
	{
		if (($zoneteam['team'] != $playerinfo['team']) || ($playerinfo['team'] == 0))
		{
			$template_object->assign("error_msg", $l_warp_forbid);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."warpeditdie.tpl");
			include ("footer.php");
			die();
		}
	}
}


if(!isset($confirm)){
	$linkcount = 0;

	$result2 = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start=$shipinfo[sector_id] ORDER BY link_dest ASC");
	if ($result2 < 1)
	{
		$template_object->assign("linkmessage", $l_warp_nolink);
	}
	else
	{
		$template_object->assign("linkmessage", $l_warp_linkto);
		$linkcount = 0;
		while (!$result2->EOF)
		{
			$nameresult = $db->Execute("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=" . $result2->fields['link_dest']);
			$linklist[$linkcount] = $nameresult->fields['sector_name'];
			$linkcount++;
			$result2->MoveNext();
		}
	}

	$template_object->assign("linkcount", $linkcount);
	$template_object->assign("linklist", $linklist);

	$template_object->assign("l_warp_query", $l_warp_query);
	$template_object->assign("l_warp_oneway", $l_warp_oneway);
	$template_object->assign("l_reset", $l_reset);
	$template_object->assign("l_warp_dest", $l_warp_dest);
	$template_object->assign("l_warp_destquery", $l_warp_destquery);
	$template_object->assign("l_warp_bothway", $l_warp_bothway);
	$template_object->assign("l_submit", $l_submit);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit.tpl");

	include ("footer.php");
}else{
	$nameresult = $db->Execute("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($target_sector));
	$target_sector_id = $nameresult->fields['sector_id'];
	$distance = floor(calc_dist($shipinfo['sector_id'],$target_sector_id));
	$cost = $distance * $warplink_build_cost;
	$energycost = $distance * $warplink_build_energy;

	if ($shipdevice['dev_warpedit']['amount'] < 1)
	{
		$template_object->assign("error_msg", $l_warp_none);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}

	$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
	db_op_result($max_query,__LINE__,__FILE__);

	$sector_max = $max_query->fields['sector_id'];

	$res = $db->SelectLimit("SELECT allow_warpedit,{$db_prefix}universe.zone_id FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
						"sector_id=$shipinfo[sector_id] AND {$db_prefix}universe.zone_id={$db_prefix}zones.zone_id", 1);
	$query97 = $res->fields;

	$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_id=$target_sector_id", 1);
	$target_type = $sector_res->fields['sg_sector'];

	$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
	$sector_type = $sector_res->fields['sg_sector'];

	if (($query97['allow_warpedit'] == 'N') || ($shipinfo['sector_id'] > $sector_max) || ($shipinfo['sector_id'] == $target_sector_id) || ($target_sector_id > $sector_max) || ($target_type != 0) || ($sector_type != 0))
	{
		$template_object->assign("error_msg", $l_warp_forbid);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}

	if ($shipinfo['sector_id'] > $sector_max || $sector_type != 0){
		$template_object->assign("error_msg", $l_swarp_forbid);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}

	if ($target_sector_id > $sector_max || $target_sector_id < 1 || $target_type != 0){
		$template_object->assign("error_msg", $l_swarp_forbid);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}

	$result2 = $db->SelectLimit ("SELECT * FROM {$db_prefix}universe WHERE sector_id=$target_sector_id", 1);
	$row = $result2->fields;
	if (!$row)
	{
		$template_object->assign("error_msg", $l_warp_nosector);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}

	$res = $db->SelectLimit("SELECT allow_warpedit,{$db_prefix}universe.zone_id FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
						"sector_id=$target_sector_id AND {$db_prefix}universe.zone_id={$db_prefix}zones.zone_id", 1);
	$query97 = $res->fields;
	if ($query97['allow_warpedit'] == 'N' && !$oneway)
	{
		$l_warp_twoerror = str_replace("[target_sector]", $target_sector, $l_warp_twoerror);
		$template_object->assign("error_msg", $l_warp_twoerror);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}

	$template_object->assign("l_player", $l_player);
	$template_object->assign("l_ship", $l_ship);
	$template_object->assign("l_energy", $l_energy);
	$template_object->assign("l_credits", $l_credits);
	$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
	$template_object->assign("shipenergy", NUMBER($shipinfo['energy']));
	$template_object->assign("l_warp_costenergy", $l_warp_costenergy);
	$template_object->assign("l_warp_costdelete", $l_warp_costdelete);
	$template_object->assign("l_warp_costcreate", $l_warp_costcreate);
	$template_object->assign("l_warp_delete", $l_warp_delete);
	$template_object->assign("l_warp_lightyears", $l_warp_lightyears);
	$template_object->assign("l_warp_distance", $l_warp_distance);
	$template_object->assign("l_warp_andsector", $l_warp_andsector);
	$template_object->assign("l_warp_create", $l_warp_create);
	$template_object->assign("startsector", $shipinfo['sector_id']);
	$template_object->assign("cost", NUMBER($cost));
	$template_object->assign("energycost", NUMBER($energycost));
	$template_object->assign("distance", $distance);
	$template_object->assign("l_yes", $l_yes);
	$template_object->assign("l_no", $l_no);
	$template_object->assign("confirm", $confirm);
	$template_object->assign("target_sector", $target_sector);
	$template_object->assign("bothway", $bothway);
	$template_object->assign("oneway", $oneway);
	$template_object->assign("l_warp_query", $l_warp_query);
	$template_object->assign("l_warp_oneway", $l_warp_oneway);
	$template_object->assign("l_reset", $l_reset);
	$template_object->assign("l_warp_dest", $l_warp_dest);
	$template_object->assign("l_warp_destquery", $l_warp_destquery);
	$template_object->assign("l_warp_bothway", $l_warp_bothway);
	$template_object->assign("l_submit", $l_submit);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_confirm.tpl");

	include ("footer.php");
}


close_database();
?>
