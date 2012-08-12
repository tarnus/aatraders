<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: defense_report.php

include ("config/config.php");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_defense_report.inc");
include ("languages/$langdir/lang_device.inc");
include("languages/$langdir/lang_report.inc");

get_post_ifset("sort, page");

if(empty($page))
{
	$page = 1;
}

$title = $l_sdf_title;

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

$entries_per_page = 25;
$template_object->assign("sort", $sort);
$template_object->assign("l_submit", $l_submit);
$template_object->assign("l_rpt_prev", $l_rpt_prev);
$template_object->assign("l_rpt_next", $l_rpt_next);
$template_object->assign("l_rpt_totalpages", $l_rpt_totalpages);
$template_object->assign("l_rpt_selectpage", $l_rpt_selectpage);
$template_object->assign("l_rpt_page", $l_rpt_page);

$query = "SELECT count(defense_id) as total FROM {$db_prefix}sector_defense WHERE player_id=$playerinfo[player_id]";
$res = $db->SelectLimit($query, 1);
$totaldefense = $res->fields['total'];
$res->close();

$start = ($page - 1) * $entries_per_page;
$totalpages = ceil($totaldefense / $entries_per_page);
$template_object->assign("currentpage", $page);
if($page < $totalpages)
{
	$next = $page + 1;
}
else
{
	$next = $page;
}
$template_object->assign("nextpage", $next);
if($page > 1)
{
	$prev = $page - 1;
}
else
{
	$prev = 1;
}
$template_object->assign("previouspage", $prev);
$template_object->assign("totalpages", $totalpages);
$template_object->assign("totaldefense", $totaldefense);

$query = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}sector_defense.* FROM {$db_prefix}sector_defense, {$db_prefix}universe WHERE {$db_prefix}sector_defense.player_id=$playerinfo[player_id] and {$db_prefix}universe.sector_id ={$db_prefix}sector_defense.sector_id";

if (!empty($sort))
{
	$query .= " ORDER BY";
	if ($sort == "quantity")
	{
		$query .= " quantity ASC";
	}
	elseif ($sort == "type")
	{
		$query .= " defense_type ASC";
   }
   else
   {
	   $query .= " sector_id ASC";
   }
}

$res = $db->SelectLimit($query, $entries_per_page, $start);

$i = 0;
if ($res)
{
	while (!$res->EOF)
	{
		$sector[$i] = $res->fields;
		$i++;
		$res->MoveNext();
	}
}

$num_sectors = $i;
if ($num_sectors < 1)
{
	$template_object->assign("error_msg", $l_sdf_none);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defensereportdie.tpl");
}
else
{
	$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
	$template_object->assign("l_sector", $l_sector);
	$template_object->assign("l_qty", $l_qty);
	$template_object->assign("l_sdf_type", $l_sdf_type);
	$color = "#3A3B6E";
	for($i=0; $i<$num_sectors; $i++)
	{
		$dsector[$i] = $sector[$i]['sector_name'];
		$dquantity[$i] = NUMBER($sector[$i]['quantity']);
		$defense_type[$i] = $sector[$i]['defense_type'] == 'fighters' ? $l_fighters : $l_mines;

		if ($color == "#3A3B6E")
		{
			$color = "#23244F";
		}
		else
		{
			$color = "#3A3B6E";
		}
	}

	$template_object->assign("dsector", $dsector);
	$template_object->assign("dquantity", $dquantity);
	$template_object->assign("defense_type", $defense_type);
	$template_object->assign("num_sectors", $num_sectors);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defensereport.tpl");
}

include ("footer.php");
?>
