<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: warpedit3.php

include ("config/config.php");
include ("languages/$langdir/lang_warpedit3.inc");
include ("globals/calc_dist.inc");

get_post_ifset("target_sector, flag, bothway");

$title = $l_warp_title;

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

$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
db_op_result($max_query,__LINE__,__FILE__);

$sector_max = $max_query->fields['sector_id'];

$nameresult = $db->Execute("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($target_sector));
$target_sector_id = $nameresult->fields['sector_id'];

$distance = floor(calc_dist($shipinfo['sector_id'],$target_sector_id));
$cost = $distance * $warplink_build_cost;
$energycost = $distance * $warplink_build_energy;

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_warp_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();

}

if ($shipdevice['dev_warpedit']['amount'] < 1)
{
	$template_object->assign("error_msg", $l_warp_none);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();

}

if ($shipinfo['energy'] < $energycost)
{
	$template_object->assign("error_msg", $l_warp_noenergy);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['credits'] < $cost)
{
	$template_object->assign("error_msg", $l_warp_nomoney);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();
}

$res = $db->SelectLimit("SELECT allow_warpedit,{$db_prefix}universe.zone_id FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
					"sector_id=$shipinfo[sector_id] AND {$db_prefix}universe.zone_id={$db_prefix}zones.zone_id", 1);
$query97 = $res->fields;

$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_id=$target_sector_id", 1);
$target_type = $sector_res->fields['sg_sector'];

$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
$sector_type = $sector_res->fields['sg_sector'];

if (($query97['allow_warpedit'] == 'N')or($shipinfo['sector_id'] > $sector_max) or ($target_sector_id > $sector_max) or ($target_type != 0) or ($sector_type != 0))
{
	$template_object->assign("error_msg", $l_warp_forbid);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();

}

$res = $db->SelectLimit("SELECT allow_warpedit,{$db_prefix}universe.zone_id FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
					"sector_id=$target_sector_id AND {$db_prefix}universe.zone_id={$db_prefix}zones.zone_id", 1);
$query97 = $res->fields;
if ($query97['allow_warpedit'] == 'N' && $bothway)
{
	$l_warp_forbidtwo = str_replace("[target_sector]", $target_sector, $l_warp_forbidtwo);
	$template_object->assign("error_msg", $l_warp_forbidtwo);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();

}

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=$target_sector_id", 1);
$row = $result2->fields;
if (!$row)
{
	$template_object->assign("error_msg", $l_warp_nosector);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_delete.tpl");
	include ("footer.php");
	die();
}

$result3 = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start=$shipinfo[sector_id]");
if ($result3 > 0)
{
	while (!$result3->EOF)
	{
		$row = $result3->fields;
		if ($target_sector_id == $row['link_dest'])
		{
			$flag = 1;
		}

		$result3->MoveNext();
	}

	if ($flag != 1)
	{
		$l_warp_unlinked = str_replace("[target_sector]", $target_sector, $l_warp_unlinked);
		$template_object->assign("error_msg", $l_warp_unlinked);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_delete.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		$debug_query = $db->Execute("DELETE FROM {$db_prefix}links WHERE link_start=$shipinfo[sector_id] AND " .
									"link_dest=$target_sector_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET energy=energy-$energycost WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_warpedit']['device_id']);
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$cost, turns=turns-1, " .
									"turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if (!$bothway)
		{
			$template_object->assign("error_msg", "$l_warp_removed $target_sector.");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."warpedit_delete.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}links WHERE link_start=$target_sector_id AND " .
										"link_dest=$shipinfo[sector_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("error_msg", "$l_warp_removedtwo $target_sector.");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."warpedit_delete.tpl");
			include ("footer.php");
			die();
		}
	}
}

close_database();
?>
