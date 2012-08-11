<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: preset.php

include ("config/config.php");
include ("languages/$langdir/lang_presets.inc");
include ("globals/calc_dist.inc");

get_post_ifset("name, preset, presetstuff");

$title = "$l_pre_title";

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

$debug_query = $db->Execute("SELECT sector_id, preset, info FROM {$db_prefix}presets, {$db_prefix}universe WHERE {$db_prefix}presets.player_id=$playerinfo[player_id] and {$db_prefix}universe.sector_name ={$db_prefix}presets.preset order by {$db_prefix}presets.info, {$db_prefix}presets.preset");
db_op_result($debug_query,__LINE__,__FILE__);
$presettotal = $debug_query->RecordCount();
$presettotal = 0;

while(!$debug_query->EOF){
	$presetinfo[$presettotal] = $debug_query->fields['preset'];
	$presettext[$presettotal] = $debug_query->fields['info'];
	$presetdist[$presettotal] = round(max(1, (calc_dist($shipinfo['sector_id'], $debug_query->fields['sector_id'])/ mypw($level_factor, $shipinfo['engines']))));
	$debug_query->MoveNext();
	$presettotal++;
}

$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
db_op_result($max_query,__LINE__,__FILE__);

$sector_max = $max_query->fields['sector_id'];

if ($name == "add")
{
	$template_object->assign("l_pre_set", $l_pre_set);
	$template_object->assign("presettotal", $presettotal);
	$template_object->assign("l_pre_info", $l_pre_info);
	$template_object->assign("l_pre_save", $l_pre_save);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."presetadd.tpl");
	include ("footer.php");
	die();
}

if ($name == "addcomplete")
{
	$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($preset), 1);
	$sector_type = $sector_res->fields['sg_sector'];
	if ($sector_type != 0)
	{
   		$l_pre_exceed = str_replace("[preset]", $presettotal, $l_pre_exceed);
	   	$l_pre_exceed = str_replace("[sector_max]", $sector_max, $l_pre_exceed);
		$complete_msg = $l_pre_exceed;
	}else{
		if($sector_res->RecordCount() != 0)
		{
			$complete_msg = "$l_pre_set $presettotal: <a href=main.php?move_method=real&engage=1&destination=".$preset.">".$preset."</a> - $l_pre_info: $presetstuff<br>";
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}presets (player_id,preset,info) VALUES ($playerinfo[player_id], '$preset', " . $db->qstr($presetstuff) . ")");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		else
		{
			$l_pre_invalid = str_replace("[sector]", $preset, $l_pre_invalid);
			$complete_msg = $l_pre_invalid;
		}
	}
	$template_object->assign("l_pre_set", $l_pre_set);
	$template_object->assign("presettotal", $presettotal);
	$template_object->assign("presetinfo", $presetinfo);
	$template_object->assign("presettext", $presettext);
	$template_object->assign("complete_msg", $complete_msg);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."presetaddcomplete.tpl");
	include ("footer.php");
	die();
}

if ($name == "set")
{
	$template_object->assign("l_pre_set", $l_pre_set);
	$template_object->assign("presettotal", $presettotal);
	$template_object->assign("presetinfo", $presetinfo);
	$template_object->assign("presettext", $presettext);
	$template_object->assign("l_pre_save", $l_pre_save);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."presetset.tpl");
	include ("footer.php");
	die();
}


if ($name == "change")
{
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}presets WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	for($totals = 0; $totals < $presettotal; $totals++){
		$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($preset[$totals]), 1);
		$sector_type = $sector_res->fields['sg_sector'];
		if ($sector_type != 0)
		{
			$l_pre_invalidchange = str_replace("[sector]", $totals, $l_pre_invalidchange);
			$presetjunk[$totals] = $l_pre_invalidchange;
		}else{
			if($sector_res->RecordCount() != 0)
			{
				
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}presets (player_id,preset,info) VALUES ($playerinfo[player_id], '$preset[$totals]', " . $db->qstr($presetstuff[$totals]) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			else
			{
				if ($preset[$totals]!=""){
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}presets (player_id,preset,info) VALUES ($playerinfo[player_id], '$presetinfo[$totals]', " . $db->qstr($presettext[$totals]) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$l_pre_invalid = str_replace("[sector]", $preset[$totals], $l_pre_invalid);
				$presetjunk[$totals] = $l_pre_invalid;
				$sector_type = 1;
			}
		}
		}
		$presettype[$totals] = $sector_type;
	}
	$template_object->assign("presettype", $presettype);
	$template_object->assign("presettotal", $presettotal);
	$template_object->assign("l_pre_set", $l_pre_set);
	$template_object->assign("l_pre_info", $l_pre_info);
	$template_object->assign("preset", $preset);
	$template_object->assign("presetjunk", $presetstuff);
	$template_object->assign("sector_max", $sector_max);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."presetchange.tpl");
	include ("footer.php");
	die();
}

close_database();
?>


