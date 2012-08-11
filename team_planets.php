<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: team_planets.php

include ("config/config.php");
include ("languages/$langdir/lang_team_planets.inc");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_planets.inc");
include ("languages/$langdir/lang_ports.inc");
include("languages/$langdir/lang_report.inc");
include ("globals/spy_detect_planet.inc");

get_post_ifset("sort, page ");

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
	$template_object->display($templatename."team-planetsdie.tpl");
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
if (!empty($sort))
{
	$query .= " ORDER BY";
	if ($sort == "name")
	{
		$query .= " $sort ASC";
	}
	elseif ($sort == "organics" || $sort == "ore" || $sort == "goods" || $sort == "energy" || $sort == "colonists" || $sort == "credits" || $sort == "fighters")
	{
		$query .= " $sort DESC";
	}
	elseif ($sort == "torp")
	{
		$query .= " torps DESC";
	}
	elseif ($sort == "max_credits")
	{
		$query .= " max_credits DESC, sector_id ASC";
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
if ($num_planets < 1)
{
	$template_object->assign("error_msg", $l_teamplanet_noplanet);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team-planetsdie.tpl");
	include ("footer.php");
	die();
}

$total_organics = 0;
$total_ore = 0;
$total_goods = 0;
$total_energy = 0;
$total_colonists = 0;
$total_credits = 0;
$total_fighters = 0;
$total_torp = 0;
$total_base = 0;

for ($i=0; $i<$num_planets; $i++)
{
	$total_organics += $planet[$i]['organics'];
	$total_ore += $planet[$i]['ore'];
	$total_goods += $planet[$i]['goods'];
	$total_energy += $planet[$i]['energy'];
	$total_colonists += $planet[$i]['colonists'];
	$total_credits += $planet[$i]['credits'];
	$total_fighters += $planet[$i]['fighters'];
	$total_torp += $planet[$i]['torps'];
	if ($planet[$i]['base'] == "Y")
	{
		$total_base += 1;
	}

	if (empty($planet[$i]['name']))
	{
		$planet[$i]['name'] = "$l_unnamed";
	}

	$owner = $planet[$i]['owner'];
	$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$owner", 1);
	$player = $res->fields['character_name'];

	$planetsector[$i] = $planet[$i]['sector_name'];
	$planetname[$i] = $planet[$i]['name'];
	$planetore[$i] = NUMBER($planet[$i]['ore']);
	$planetorganics[$i] = NUMBER($planet[$i]['organics']);
	$planetgoods[$i] = NUMBER($planet[$i]['goods']);
	$planetenergy[$i] = NUMBER($planet[$i]['energy']);
	$planetcolonists[$i] = NUMBER($planet[$i]['colonists']);
	$planetcredits[$i] = NUMBER($planet[$i]['credits']);
	$planetmaxcredits[$i] = round(($planet[$i]['credits']/$planet[$i]['max_credits'])*100);
	$planetfighters[$i] = NUMBER($planet[$i]['fighters']);
	$planettorps[$i] = NUMBER($planet[$i]['torps']);
	$planetbase[$i] = ($planet[$i]['base'] == 'Y' ? "$l_yes" : "$l_no");
	$planetplayer[$i] = $player;
}

$template_object->assign("l_pr_menulink", $l_pr_menulink);
$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
$template_object->assign("l_sector", $l_sector);
$template_object->assign("l_name", $l_name);
$template_object->assign("l_ore", $l_ore);
$template_object->assign("l_organics", $l_organics);
$template_object->assign("l_goods", $l_goods);
$template_object->assign("l_energy", $l_energy);
$template_object->assign("l_colonists", $l_colonists);
$template_object->assign("l_credits", $l_credits);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_torps", $l_torps);
$template_object->assign("l_base", $l_base);
$template_object->assign("l_player", $l_player);
$template_object->assign("num_planets", $num_planets);
$template_object->assign("total_ore", NUMBER($total_ore));
$template_object->assign("total_organics", NUMBER($total_organics));
$template_object->assign("total_goods", NUMBER($total_goods));
$template_object->assign("total_energy", NUMBER($total_energy));
$template_object->assign("total_colonists", NUMBER($total_colonists));
$template_object->assign("total_credits", NUMBER($total_credits));
$template_object->assign("total_fighters", NUMBER($total_fighters));
$template_object->assign("total_torp", NUMBER($total_torp));
$template_object->assign("total_base", NUMBER($total_base));
$template_object->assign("planetsector", $planetsector);
$template_object->assign("planetname", $planetname);
$template_object->assign("planetore", $planetore);
$template_object->assign("planetorganics", $planetorganics);
$template_object->assign("planetgoods", $planetgoods);
$template_object->assign("planetenergy", $planetenergy);
$template_object->assign("planetcolonists", $planetcolonists);
$template_object->assign("planetcredits", $planetcredits);
$template_object->assign("planetmaxcredits", $planetmaxcredits);
$template_object->assign("planetfighters", $planetfighters);
$template_object->assign("planettorps", $planettorps);
$template_object->assign("planetbase", $planetbase);
$template_object->assign("planetplayer", $planetplayer);
$template_object->assign("l_max", $l_max);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."team-planets.tpl");
include ("footer.php");
?>

