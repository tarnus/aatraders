<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: warpedit2.php

include ("config/config.php");
include ("languages/$langdir/lang_warpedit2.inc");
include ("globals/calc_dist.inc");

get_post_ifset("flag, target_sector, oneway, flag2");

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

$res = $db->SelectLimit("SELECT allow_warpedit,{$db_prefix}universe.zone_id FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
					"sector_id=$shipinfo[sector_id] AND {$db_prefix}universe.zone_id={$db_prefix}zones.zone_id", 1);
$query97 = $res->fields;

$distance = floor(calc_dist($shipinfo['sector_id'],$target_sector_id));
$cost = $distance * $warplink_build_cost;
$energycost = $distance * $warplink_build_energy;

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_warp_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_add.tpl");
	include ("footer.php");
	die();
}

if ($shipdevice['dev_warpedit']['amount'] < 1)
{
	$template_object->assign("error_msg", $l_warp_none);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_add.tpl");
	include ("footer.php");
	die();
}

if ($shipinfo['energy'] < $energycost)
{
	$template_object->assign("error_msg", $l_warp_noenergy);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_add.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['credits'] < $cost)
{
	$template_object->assign("error_msg", $l_warp_nomoney);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_add.tpl");
	include ("footer.php");
	die();
}

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

$result3 = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start=$shipinfo[sector_id]");
$numlink_start = $result3->RecordCount();

if ($numlink_start >= $link_max )
{
	$template_object->assign("error_msg", $l_warp_sectex);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."warpedit_add.tpl");
	include ("footer.php");
	die();
}

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

	if ($flag == 1)
	{
		$l_warp_linked = str_replace("[target_sector]", $target_sector, $l_warp_linked);
		$template_object->assign("error_msg", $l_warp_linked);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}
	elseif ($shipinfo['sector_id'] == $target_sector)
	{
		$template_object->assign("error_msg", $l_warp_cantsame);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."warpedit_add.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links SET link_start=$shipinfo[sector_id], link_dest=$target_sector_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET energy=energy-$energycost WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_warpedit']['device_id']);
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET credits=credits-$cost, turns=turns-1, " .
									 "turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($oneway)
		{
			$template_object->assign("error_msg", "$l_warp_coneway $target_sector.");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."warpedit_add.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			$result4 = $db->Execute ("SELECT * FROM {$db_prefix}links WHERE link_start=$target_sector_id");
			if ($result4)
			{
				while (!$result4->EOF)
				{
					$row = $result4->fields;
					if ($shipinfo['sector_id'] == $row['link_dest'])
					{
						$flag2 = 1;
					}

					$result4->MoveNext();
				}
			}

			if ($flag2 != 1)
			{
				$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links SET link_start=$target_sector_id, " .
											 "link_dest=$shipinfo[sector_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			$template_object->assign("error_msg", "$l_warp_ctwoway $target_sector.");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."warpedit_add.tpl");
			include ("footer.php");
			die();
		}
	}
}

include ("footer.php");

?>
