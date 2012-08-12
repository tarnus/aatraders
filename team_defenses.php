<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: team_defenses.php

include ("config/config.php");
include ("languages/$langdir/lang_team_planets.inc");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_planets.inc");
include ("languages/$langdir/lang_ports.inc");
include("languages/$langdir/lang_report.inc");
include ("globals/spy_detect_planet.inc");

get_post_ifset("sort, page");

if(empty($page))
{
	$page = 1;
}

$title = $l_teamplanet_title;

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

if ($playerinfo['team'] == 0)
{
	$template_object->assign("error_msg", $l_teamplanet_notally);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team-defensesdie.tpl");
	include ("footer.php");
	die();
}

$entries_per_page = 25;
$template_object->assign("sort", $sort);
$template_object->assign("l_submit", $l_submit);
$template_object->assign("l_rpt_prev", $l_rpt_prev);
$template_object->assign("l_rpt_next", $l_rpt_next);
$template_object->assign("l_rpt_totalpages", $l_rpt_totalpages);
$template_object->assign("l_rpt_selectpage", $l_rpt_selectpage);
$template_object->assign("l_rpt_page", $l_rpt_page);
$template_object->assign("l_pr_planetstatus", $l_pr_planetstatus);
$template_object->assign("l_pr_pdefense", $l_pr_pdefense);
$template_object->assign("l_pr_changeprods", $l_pr_changeprods);
$template_object->assign("l_pr_baserequired", $l_pr_baserequired);
$template_object->assign("l_pr_prod_disp", $l_pr_prod_disp);
$template_object->assign("l_pr_teamlink", $l_pr_teamlink);
$template_object->assign("l_pr_showtd", $l_pr_showtd);
$template_object->assign("l_pr_showd", $l_pr_showd);
$template_object->assign("l_pr_comm_disp", $l_pr_comm_disp);
$template_object->assign("l_pr_display", $l_pr_display);
$template_object->assign("l_pr_team_disp", $l_pr_team_disp);

$query = "SELECT count(planet_id) as total FROM {$db_prefix}planets WHERE team=$playerinfo[team]";
$res = $db->SelectLimit($query, 1);
$totalplanets = $res->fields['total'];
$res->close();

$start = ($page - 1) * $entries_per_page;
$totalpages = ceil($totalplanets / $entries_per_page);
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
$template_object->assign("totalplanets", $totalplanets);

$query = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}planets.* FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.team=$playerinfo[team] and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id";

if(!empty($sort))
{
	$query .= " ORDER BY";
	if($sort == "name")
	{
	  $query .= " $sort ASC";
	}
	elseif($sort == "fighter" || $sort == "sensors" || $sort == "beams" || $sort == "torp_launchers" ||
	  $sort == "shields" || $sort == "cloak" || $sort == "owner" || $sort == "base" || $sort == "jammer")
	{
	  $query .= " $sort DESC, sector_name ASC";
	}
	else
	{
	  $query .= " sector_name ASC";
	}

}
else
{
	 $query .= " ORDER BY sector_name ASC";
}

$res = $db->SelectLimit($query, $entries_per_page, $start);

$i = 0;
if ($res)
{
	while (!$res->EOF)
	{
		$planet[$i] = $res->fields;
		///
		if ($enable_spies)
		{
			spy_detect_planet($shipinfo['ship_id'], $planet[$i]['planet_id'], $planet_detect_success2);
		}

		$i++;
		$res->Movenext();
	}
}

$num_planets = $i;
if($num_planets < 1)
{
	$template_object->assign("l_pr_noplanet", $l_pr_noplanet);
	$template_object->assign("l_pr_menulink", $l_pr_menulink);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team-defensesnone.tpl");
	include ("footer.php");
	die();
}

$total_base = 0;

for($i=0; $i<$num_planets; $i++)
{
	if(empty($planet[$i]['name']))
	{
		$planet[$i]['name'] = $l_unnamed;
	}

	$owner = $planet[$i]['owner'];
	$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$owner", 1);
	$player = $res->fields['character_name'];

	$teamsector[$i] = $planet[$i]['sector_name'];
	$planetname[$i] = $planet[$i]['name'];
	$planetfighter[$i] = NUMBER($planet[$i]['fighter']);
	$planetsensors[$i] = NUMBER($planet[$i]['sensors']);
	$planetbeams[$i] = NUMBER($planet[$i]['beams']);
	$planettorps[$i] = NUMBER($planet[$i]['torp_launchers']);
	$planetshields[$i] = NUMBER($planet[$i]['shields']);
	$planetjammer[$i] = NUMBER($planet[$i]['jammer']);
	$planetcloak[$i] = NUMBER($planet[$i]['cloak']);
	$planetsdweapons[$i] = NUMBER($planet[$i]['sector_defense_weapons']);
	$planetsdsensors[$i] = NUMBER($planet[$i]['sector_defense_sensors']);
	$planetsdcloak[$i] = NUMBER($planet[$i]['sector_defense_cloak']);
	$planetbase[$i] = ($planet[$i]['base'] == 'Y' ? "$l_yes" : "$l_no");
	$playername[$i] = $player;

	if($planet[$i]['base'] == 'Y')
		$total_base++;
}


$template_object->assign("l_pr_menulink", $l_pr_menulink);
$template_object->assign("teamsector", $teamsector);
$template_object->assign("planetname", $planetname);
$template_object->assign("planetfighter", $planetfighter);
$template_object->assign("planetsensors", $planetsensors);
$template_object->assign("planetbeams", $planetbeams);
$template_object->assign("planettorps", $planettorps);
$template_object->assign("planetshields", $planetshields);
$template_object->assign("planetjammer", $planetjammer);
$template_object->assign("planetcloak", $planetcloak);
$template_object->assign("planetsdweapons", $planetsdweapons);
$template_object->assign("planetsdsensors", $planetsdsensors);
$template_object->assign("planetsdcloak", $planetsdcloak);
$template_object->assign("planetbase", $planetbase);
$template_object->assign("playername", $playername);
$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);

$template_object->assign("num_planets", $num_planets);
$template_object->assign("l_pr_totals", $l_pr_totals);
$template_object->assign("total_base", $total_base);
$template_object->assign("l_teamplanet_owner", $l_teamplanet_owner);
$template_object->assign("l_base", $l_base);
$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
$template_object->assign("l_sector", $l_sector);
$template_object->assign("l_name", $l_name);
$template_object->assign("l_fighter", $l_fighter);
$template_object->assign("l_sensors", $l_sensors);
$template_object->assign("l_beams", $l_beams);
$template_object->assign("l_torp_launch", $l_torp_launch);
$template_object->assign("l_shields", $l_shields);
$template_object->assign("l_jammer", $l_jammer);
$template_object->assign("l_cloak", $l_cloak);
$template_object->assign("l_teamplanet_personal", $l_teamplanet_personal);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."team-defenses.tpl");
include ("footer.php");
?>