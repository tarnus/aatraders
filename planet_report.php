<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: planet_report.php

include ("config/config.php");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_planets.inc");
include("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_teams.inc");
include ("languages/$langdir/lang_ports.inc");
include ("globals/spy_detect_planet.inc");

get_post_ifset("PRepType, sort, page");

if(empty($page))
{
	$page = 1;
}

$title = $l_pr_title;

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

// determine what type of report is displayed and display it's title

if($PRepType==3 || !isset($PRepType)) // display the defenses on the planets
{
	$query = "SELECT count(planet_id) as total FROM {$db_prefix}planets WHERE owner=$playerinfo[player_id]";
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

	$query = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.zone_id, {$db_prefix}universe.sg_sector, {$db_prefix}planets.* FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.owner=$playerinfo[player_id] and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id";

	if(!empty($sort))
	{
		$query .= " ORDER BY";
	if($sort == "name")
	{
		$query .= " $sort ASC";
	}
	elseif($sort == "fighter" || $sort == "sensors" || $sort == "beams" || $sort == "torp_launchers" ||  
		$sort == "shields" || $sort == "cloak" || $sort == "base" || $sort == "jammer")
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

	$planet_sg_zone = array();
	$i = 0;
	if($res)
	{
		while(!$res->EOF)
		{
			$planet[$i] = $res->fields;
			if($planet[$i]['sg_sector'] == 0)
			{
				$planet_sg_zone[$planet[$i]['sector_id']] = $planet[$i]['zone_id'];
			}
			else
			{
				if(!isset($planet_sg_zone[$planet[$i]['sg_sector']]))
				{
					$query = "SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=" . $planet[$i]['sg_sector'];
					$getzone = $db->SelectLimit($query, 1);
					$planet_sg_zone[$planet[$i]['sg_sector']] = $getzone->fields['zone_id'];
				}
			}

//echo $planet[$i]['sector_id'] . " - " . $planet[$i]['sg_sector'] . " - " . $planet[$i]['zone_id'] . "<br>";
			if($enable_spies)
			{
				spy_detect_planet($shipinfo['ship_id'], $planet[$i]['planet_id'], $planet_detect_success2);
			}
			$i++;
			$res->MoveNext();
		}
	}

	$num_planets = $i;

	$total_base = 0;

	for($i=0; $i<$num_planets; $i++)
	{
		if(empty($planet[$i]['name']))
		{
			$planet[$i]['name'] = $l_unnamed;
		}
		$planetsector[$i] = $planet[$i]['sector_name'];
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

		$planetbase[$i] = $planet[$i]['base'];
		$planetbaseitems[$i] = ($planet[$i]['ore'] >= $base_ore && $planet[$i]['organics'] >= $base_organics && $planet[$i]['goods'] >= $base_goods && $planet[$i]['credits'] >= $base_credits);
		$planetid[$i] = $planet[$i]["planet_id"];
		$planetzone_id[$i] = ($planet[$i]['sg_sector'] == 0) ? $planet[$i]['zone_id'] : $planet_sg_zone[$planet[$i]['sg_sector']];
//echo $planet[$i]['sg_sector'] . " - " . $planetzone_id[$i] . "<br>";

		$total_base += 1;
	}

	$template_object->assign("title", $title);
	$template_object->assign("l_pr_menulink", $l_pr_menulink);
	$template_object->assign("playerteam", $playerinfo['team']);
	$template_object->assign("num_planets", $num_planets);
	$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
	$template_object->assign("l_pr_totals", $l_pr_totals);
	$template_object->assign("total_base", $total_base);
	$template_object->assign("l_yes", $l_yes);
	$template_object->assign("l_no", $l_no);
	$template_object->assign("l_pr_build", $l_pr_build);
	$template_object->assign("planetsector", $planetsector);
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
	$template_object->assign("planetbaseitems", $planetbaseitems);
	$template_object->assign("planetid", $planetid);
	$template_object->assign("planetzone_id", $planetzone_id);
	$template_object->assign("l_pr_sector", $l_pr_sector);
	$template_object->assign("l_name", $l_name);
	$template_object->assign("l_fighter", $l_fighter);
	$template_object->assign("l_sensors", $l_sensors);
	$template_object->assign("l_beams", $l_beams);
	$template_object->assign("l_torp_launch", $l_torp_launch);
	$template_object->assign("l_shields", $l_shields);
	$template_object->assign("l_jammer", $l_jammer);
	$template_object->assign("l_cloak", $l_cloak);
	$template_object->assign("l_base", $l_base);
	$template_object->assign("l_pr_noplanet", $l_pr_noplanet);

	$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
	$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
	$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);

	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet-report-defenses.tpl");
	include ("footer.php");
	die();
}

if ($PRepType==1 || !isset($PRepType)) // display the commodities on the planets
{
	$query = "SELECT count(planet_id) as total FROM {$db_prefix}planets WHERE owner=$playerinfo[player_id]";
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

	$query = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.zone_id, {$db_prefix}universe.sg_sector, {$db_prefix}planets.* FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.owner=$playerinfo[player_id] and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id";

	if (!empty($sort))
	{
		$query .= " ORDER BY";
		if ($sort == "name")
		{
			$query .= " $sort ASC";
		}  else if( $sort == "last_visited"    ){
         $query .= " {$db_prefix}planets.last_visited ";    
    }
		elseif ($sort == "organics" || $sort == "ore" || $sort == "goods" || $sort == "energy" ||
			$sort == "colonists" || $sort == "credits" || $sort == "fighters")
		{
			$query .= " $sort DESC, sector_id ASC";
		}
		elseif ($sort == "torp")
		{
			$query .= " torps DESC, sector_id ASC";
		}
		elseif ($sort == "max_credits")
		{
			$query .= " max_credits DESC, sector_id ASC";
		}
		elseif ($sort == "special")
		{
			$query .= " special_name DESC";
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

	$planet_sg_zone = array();
	$i = 0;
	if ($res)
	{
		while (!$res->EOF)
		{
			$planet[$i] = $res->fields;
			if($planet[$i]['sg_sector'] == 0)
			{
				$planet_sg_zone[$planet[$i]['sector_id']] = $planet[$i]['zone_id'];
			}
			else
			{
				if(!isset($planet_sg_zone[$planet[$i]['sg_sector']]))
				{
					$query = "SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=" . $planet[$i]['sg_sector'];
					$getzone = $db->SelectLimit($query, 1);
					$planet_sg_zone[$planet[$i]['sg_sector']] = $getzone->fields['zone_id'];
				}
			}
			if ($enable_spies)
			{
				spy_detect_planet($shipinfo['ship_id'], $planet[$i]['planet_id'], $planet_detect_success2);
			}

			$i++;
			$res->MoveNext();
		}
	}

	$num_planets = $i;

	$total_organics = 0;
	$total_ore = 0;
	$total_goods = 0;
	$total_energy = 0;
	$total_colonists = 0;
	$total_credits = 0;
	$total_fighters = 0;
	$total_torp = 0;
	$total_base = 0;
	$total_team = 0;
	$total_teamcash = 0;
	for($i=0; $i<$num_planets; $i++)
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
		if ($planet[$i]['team'] > 0)
		{
			$total_team += 1;
		}
		if ($planet[$i]['team_cash'] == "Y")
		{
			$total_teamcash += 1;
		}
		if (empty($planet[$i]['name']))
		{
			$planet[$i]['name'] = $l_unnamed;
		}
		$planetsector[$i] = $planet[$i]['sector_name'];
		$planetname[$i] = $planet[$i]['name'];
		$planetore[$i] = NUMBER($planet[$i]['ore']);
		$planetorganics[$i] = NUMBER($planet[$i]['organics']);
		$planetgoods[$i] = NUMBER($planet[$i]['goods']);
		$planetenergy[$i] = NUMBER($planet[$i]['energy']);
		$planetspecial[$i] = NUMBER($planet[$i]["special_amount"]);
		$planetspecialname[$i] = ucwords($planet[$i]["special_name"]);
		$planetcolonists[$i] = NUMBER($planet[$i]['colonists']);
		$planetcredits[$i] = NUMBER($planet[$i]['credits']);
		$planetmaxcredits[$i] = round(($planet[$i]['credits']/$planet[$i]['max_credits'])*100);
		$planetid[$i] = $planet[$i]["planet_id"];
		$planetfighters[$i] = NUMBER($planet[$i]['fighters']);
		$planettorps[$i] = NUMBER($planet[$i]['torps']);
		$planetbase[$i] = $planet[$i]['base'];
		$planetbaseitems[$i] = ($planet[$i]['ore'] >= $base_ore && $planet[$i]['organics'] >= $base_organics && $planet[$i]['goods'] >= $base_goods && $planet[$i]['credits'] >= $base_credits);
		$planetteam[$i] = $planet[$i]['team'];
		$planettcash[$i] = $planet[$i]['team_cash'];
		$planetzone_id[$i] = ($planet[$i]['sg_sector'] == 0) ? $planet[$i]['zone_id'] : $planet_sg_zone[$planet[$i]['sg_sector']];

        $planetlastvisited[$i]= sprintf("%01.2f", (strtotime(date("Y-m-d H:i:s")) - strtotime($planet[$i]['last_visited'])) / 86400);  
       
	}

	$template_object->assign("title", $title);
	$template_object->assign("l_pr_status", $l_pr_status);
	$template_object->assign("l_pr_menulink", $l_pr_menulink);
	$template_object->assign("playerteam", $playerinfo['team']);
	$template_object->assign("num_planets", $num_planets);
	$template_object->assign("l_pr_noplanet", $l_pr_noplanet);
	$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
	$template_object->assign("l_pr_warning", $l_pr_warning);
	$template_object->assign("l_pr_sector", $l_pr_sector);
	$template_object->assign("l_name", $l_name);
	$template_object->assign("l_ore", $l_ore);
	$template_object->assign("l_organics", $l_organics);
	$template_object->assign("l_goods", $l_goods);
	$template_object->assign("l_energy", $l_energy);
	$template_object->assign("l_colonists", $l_colonists);
	$template_object->assign("l_credits", $l_credits);
	$template_object->assign("l_pr_takecreds", $l_pr_takecreds);
	$template_object->assign("l_fighters", $l_fighters);
	$template_object->assign("l_torps", $l_torps);
	$template_object->assign("l_base", $l_base);
	$template_object->assign("l_team", $l_team);
	$template_object->assign("l_teamcash", $l_teamcash);
	$template_object->assign("l_pr_collectcreds", $l_pr_collectcreds);
	$template_object->assign("l_pr_selectall", $l_pr_selectall);
	$template_object->assign("l_reset", $l_reset);
	$template_object->assign("total_teamcash", NUMBER($total_teamcash));
	$template_object->assign("total_team", NUMBER($total_team));
	$template_object->assign("total_base", NUMBER($total_base));
	$template_object->assign("total_torp", NUMBER($total_torp));
	$template_object->assign("total_fighters", NUMBER($total_fighters));
	$template_object->assign("total_credits", NUMBER($total_credits));
	$template_object->assign("total_colonists", NUMBER($total_colonists));
	$template_object->assign("total_energy", NUMBER($total_energy));
	$template_object->assign("total_goods", NUMBER($total_goods));
	$template_object->assign("total_organics", NUMBER($total_organics));
	$template_object->assign("total_ore", NUMBER($total_ore));
	$template_object->assign("l_pr_totals", $l_pr_totals);
	$template_object->assign("l_yes", $l_yes);
	$template_object->assign("l_pr_build", $l_pr_build);
	$template_object->assign("l_no", $l_no);
	$template_object->assign("planetbase", $planetbase);
	$template_object->assign("planetsector", $planetsector);
	$template_object->assign("planetname", $planetname);
	$template_object->assign("planetore", $planetore);
	$template_object->assign("planetorganics", $planetorganics);
	$template_object->assign("planetgoods", $planetgoods);
	$template_object->assign("planetenergy", $planetenergy);
	$template_object->assign("l_pr_special", $l_pr_special);
	$template_object->assign("planetspecial", $planetspecial);
	$template_object->assign("planetspecialname", $planetspecialname);
	$template_object->assign("planetcolonists", $planetcolonists);
	$template_object->assign("planetcredits", $planetcredits);
	$template_object->assign("planetmaxcredits", $planetmaxcredits);
	$template_object->assign("planetid", $planetid);
	$template_object->assign("planetfighters", $planetfighters);
	$template_object->assign("planettorps", $planettorps);
	$template_object->assign("planetbaseitems", $planetbaseitems);
	$template_object->assign("planetteam", $planetteam);
	$template_object->assign("planettcash", $planettcash);
	$template_object->assign("planetzone_id", $planetzone_id);
    $template_object->assign("planetlastvisited", $planetlastvisited); 
    
	$template_object->assign("l_max", $l_max);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet-report-commodities.tpl");
	include ("footer.php");
	die();
}

if ($PRepType==2)	// display the production values of your planets and allow changing
{
	$query = "SELECT count(planet_id) as total FROM {$db_prefix}planets WHERE owner=$playerinfo[player_id]";
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

	$query = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.sg_sector, {$db_prefix}universe.zone_id, {$db_prefix}planets.* FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.owner=$playerinfo[player_id] AND {$db_prefix}planets.base='Y' and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id";

	if (!empty($sort))
	{
		$query .= " ORDER BY";
		if ($sort == "name")
		{
			$query .= " $sort ASC";
		}
		elseif ($sort == "organics" || $sort == "ore" || $sort == "goods" || $sort == "energy" || $sort == "fighters" || $sort == "special")
		{
			$query .= " prod_$sort DESC, sector_id ASC";
		}
		elseif ($sort == "colonists" || $sort == "credits")
		{
			$query .= " $sort DESC, sector_id ASC";
		}
		elseif ($sort == "torp")
		{
			$query .= " prod_torp DESC, sector_id ASC";
		}
		else
		{
			$query .= " sector_id ASC";
		}
	}
	else
	{
		$query .= " ORDER BY sector_id ASC";
	}

	$res = $db->SelectLimit($query, $entries_per_page, $start);

	$planet_sg_zone = array();
	$i = 0;
	if ($res)
	{
		while (!$res->EOF)
		{
			$planet[$i] = $res->fields;
			if($planet[$i]['sg_sector'] == 0)
			{
				$planet_sg_zone[$planet[$i]['sector_id']] = $planet[$i]['zone_id'];
			}
			else
			{
				if(!isset($planet_sg_zone[$planet[$i]['sg_sector']]))
				{
					$query = "SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=" . $planet[$i]['sg_sector'];
					$getzone = $db->SelectLimit($query, 1);
					$planet_sg_zone[$planet[$i]['sg_sector']] = $getzone->fields['zone_id'];
				}
			}
			if ($enable_spies)
			{
				spy_detect_planet($shipinfo['ship_id'], $planet[$i]['planet_id'], $planet_detect_success2);
			}

			$i++;
			$res->MoveNext();
		}
	}

	$num_planets = $i;

	$total_colonists = 0;
	$total_credits = 0;
	$total_team = 0;

	$temp_var = 0;

	for($i=0; $i<$num_planets; $i++)
	{
		$total_colonists += $planet[$i]['colonists'];
		$total_credits += $planet[$i]['credits'];
		if (empty($planet[$i]['name']))
		{
			$planet[$i]['name'] = $l_unnamed;
		}
		$planetsector[$i] = $planet[$i]['sector_name'];
		$planetname[$i] = $planet[$i]['name'];
		$planetid[$i] = $planet[$i]["planet_id"];
		$planetore[$i] = $planet[$i]["prod_ore"];
		$planetorganics[$i] = $planet[$i]["prod_organics"];
		$planetgoods[$i] = $planet[$i]["prod_goods"];
		$planetenergy[$i] = $planet[$i]["prod_energy"];
		$planetspecial[$i] = $planet[$i]["prod_special"];
		$planetspecialname[$i] = $planet[$i]["special_name"];
		$planetcolonists[$i] = NUMBER($planet[$i]['colonists']);
		$planetcredits[$i] = NUMBER($planet[$i]['credits']);
		$planetfighters[$i] = $planet[$i]["prod_fighters"];
		$planettorps[$i] = $planet[$i]["prod_torp"];
		$planetresearch[$i] = $planet[$i]["prod_research"];
		$planetbuild[$i] = $planet[$i]["prod_build"];
		$planetzone_id[$i] = ($planet[$i]['sg_sector'] == 0) ? $planet[$i]['zone_id'] : $planet_sg_zone[$planet[$i]['sg_sector']];

		if ($playerinfo['team'] > 0){
			$planetteam[$i] = $planet[$i]['team'];
		}
		$planettcash[$i] = $planet[$i]['team_cash'];
	}

	$template_object->assign("title", $title);
	$template_object->assign("l_pr_special", $l_pr_special);
	$template_object->assign("planetspecialname", $planetspecialname);
	$template_object->assign("planetspecial", $planetspecial);
	$template_object->assign("l_pr_build", $l_pr_build);
	$template_object->assign("l_pr_research", $l_pr_research);
	$template_object->assign("l_pr_production", $l_pr_production);
	$template_object->assign("l_pr_menulink", $l_pr_menulink);
	$template_object->assign("playerteam", $playerinfo['team']);
	$template_object->assign("num_planets", $num_planets);
	$template_object->assign("l_pr_noplanet", $l_pr_noplanet);
	$template_object->assign("l_pr_clicktosort", $l_pr_clicktosort);
	$template_object->assign("l_pr_sector", $l_pr_sector);
	$template_object->assign("l_name", $l_name);
	$template_object->assign("l_ore", $l_ore);
	$template_object->assign("l_organics", $l_organics);
	$template_object->assign("l_goods", $l_goods);
	$template_object->assign("l_energy", $l_energy);
	$template_object->assign("l_colonists", $l_colonists);
	$template_object->assign("l_credits", $l_credits);
	$template_object->assign("l_fighters", $l_fighters);
	$template_object->assign("l_torps", $l_torps);
	$template_object->assign("l_team", $l_team);
	$template_object->assign("l_teamcash", $l_teamcash);
	$template_object->assign("l_pr_totals", $l_pr_totals);
	$template_object->assign("total_colonists", NUMBER($total_colonists));
	$template_object->assign("total_credits", NUMBER($total_credits));
	$template_object->assign("player_id", $playerinfo['player_id']);
	$template_object->assign("l_submit", $l_submit);
	$template_object->assign("l_reset", $l_reset);
	$template_object->assign("planetzone_id", $planetzone_id);
	$template_object->assign("planetsector", $planetsector);
	$template_object->assign("planetname", $planetname);
	$template_object->assign("planetid", $planetid);
	$template_object->assign("planetore", $planetore);
	$template_object->assign("planetorganics", $planetorganics);
	$template_object->assign("planetgoods", $planetgoods);
	$template_object->assign("planetenergy", $planetenergy);
	$template_object->assign("planetcolonists", $planetcolonists);
	$template_object->assign("planetcredits", $planetcredits);
	$template_object->assign("planetfighters", $planetfighters);
	$template_object->assign("planettorps", $planettorps);
	$template_object->assign("planetresearch", $planetresearch);
	$template_object->assign("planetbuild", $planetbuild);
	$template_object->assign("planetteam", $planetteam);
	$template_object->assign("planettcash", $planettcash);
	$template_object->assign("gotomain", $l_global_mmenu);
	
	$template_object->display($templatename."planet-report-production.tpl");
	include ("footer.php");
	die();
}

if ($PRepType==0)					// For typing in manually to get a report menu
{
	$template_object->assign("title", $title);
	$template_object->assign("l_pr_menu", $l_pr_menu);
	$template_object->assign("playerteam", $playerinfo['team']);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet-report-menu.tpl");
	include ("footer.php");
	die();
}

close_database();
?>
