<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: defense-report.php

include ("config/config.php");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_defense_report.inc");
include("languages/$langdir/lang_teams.inc");
include ("languages/$langdir/lang_device.inc");

get_post_ifset("sort");

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

if($playerinfo['team'] != 0){

	$query = "SELECT * FROM {$db_prefix}sector_defense,{$db_prefix}players WHERE {$db_prefix}sector_defense.player_id={$db_prefix}players.player_id and {$db_prefix}players.team=$playerinfo[team] ";

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
		elseif ($sort == "character")
		{
			$query .= " character_name ASC,  sector_id ASC";
		}
	   else
	   {
		   $query .= " sector_id ASC,character_name ASC,defense_type ASC,quantity ASC";
	   }
	}

	$res = $db->Execute($query);

	$i = 0;
	if ($res)
	{
		while (!$res->EOF)
		{
			$check = $res->fields;
			$query1 = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}planets.* FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.team=$playerinfo[team] and {$db_prefix}planets.sector_id=$check[sector_id] and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id";
			$res1 = $db->Execute($query1);
			if ($res1->RecordCount() > 0){
				$sectorn[$i] = $res1->fields;
				$sector[$i] = $res->fields;
				$i++;
			}
			$res->MoveNext();
		}
	}

	$num_sectors = $i;
	if ($num_sectors < 1)
	{
		$template_object->assign("error_msg", $l_sdf_none);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."defensereportdie.tpl");
		include ("footer.php"); 
		die();
	}
	else
	{
		$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
		$template_object->assign("l_sector", $l_sector);
		$template_object->assign("l_qty", $l_qty);
		$template_object->assign("l_sdf_type", $l_sdf_type);
		for($i=0; $i<$num_sectors; $i++)
		{
			$dsector[$i] = $sector[$i]['sector_id'];
			$dsectorname[$i] = $sectorn[$i]['sector_name'];
			$dquantity[$i] = NUMBER($sector[$i]['quantity']);
			$dquantityraw[$i] = $sector[$i]['quantity'];
			$playername[$i]= $sector[$i]['character_name'];
			$defense_type[$i] = $sector[$i]['defense_type'] == 'fighters' ? $l_fighters : $l_mines;
		}
	}
	$template_object->assign("sort", $sort);
	$template_object->assign("playername", $playername);
	$template_object->assign("dsector", $dsector);
	$template_object->assign("dsectorname", $dsectorname);
	$template_object->assign("dquantity", $dquantity);
	$template_object->assign("dquantityraw", $dquantityraw);
	$template_object->assign("defense_type", $defense_type);
	$template_object->assign("num_sectors", $num_sectors);
	$template_object->assign("l_team_members", $l_team_members);
	
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team-defensereport.tpl");
}

include ("footer.php");
?>
