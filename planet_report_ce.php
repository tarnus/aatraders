<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: planet_report_ce.php

include ("config/config.php");
include ("languages/$langdir/lang_move.inc");
include ("languages/$langdir/lang_planet_report.inc");
include ("languages/$langdir/lang_planets.inc");

if ((!isset($team_id)) || ($team_id == ''))
{
	$team_id = '';
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

for (reset($_POST); list($commod_type) = each($_POST);)
{  
	$totalplanets = 0;
	for (reset($_POST[$commod_type]); list($key) = each($_POST[$commod_type]);)
	{
		$prodpercent = $_POST[$commod_type][$key];
		if($prodpercent < 0)
			$prodpercent = 0;

		if ($commod_type == "planetsector")
		{
			$planetsector[$totalplanets] = $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "planetname")
		{
			$planetname[$totalplanets] = $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_ore")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] = "prod_ore=$prodpercent, ";
			$percentage[$totalplanets] = $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_organics")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_organics=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_goods")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_goods=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_energy")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_energy=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_special")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_special=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}
 
		if ($commod_type == "prod_fighters")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_fighters=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_torp")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_torp=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_research")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_research=$prodpercent, ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "prod_build")
		{
			$prodpercent = stripnum($prodpercent);
			$planetquery[$totalplanets] .= "prod_build=$prodpercent ";
			$percentage[$totalplanets] += $prodpercent;
			$totalplanets++;
		}

		if ($commod_type == "team")
		{
			if($prodpercent == 1)
				$prodpercent = $playerinfo['team'];
			else $prodpercent = 0;
			$planetquery[$totalplanets] .= ", team=$prodpercent, ";
			$totalplanets++;
		}

		if ($commod_type == "team_cash")
		{
			if($prodpercent == 1)
				$prodpercent = "Y";
			else $prodpercent = "N";
			$planetquery[$totalplanets] .= "team_cash='$prodpercent' ";
			$totalplanets++;
		}

		if ($commod_type == "prod_done")
		{
			$planetquery[$totalplanets] .= "where planet_id=$prodpercent and owner=$playerinfo[player_id]";
			$totalplanets++;
		}
	}
}

$exceeded = 0;
for($i = 0; $i < $totalplanets; $i++){
	if ($percentage[$i] > 100)
	{
		$l_pr_prexeeds2 = str_replace("[name]", $planetname[$i], $l_pr_prexeeds);
		$l_pr_prexeeds2 = str_replace("[sector_id]", $planetsector[$i], $l_pr_prexeeds2);

		$planetexceeded[$exceeded] =  $l_pr_prexeeds2;
		$exceeded++;
	}
	else
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET " . $planetquery[$i]);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

$template_object->assign("l_pr_menulink", $l_pr_menulink);
$template_object->assign("l_pr_changeprods", $l_pr_changeprods);
$template_object->assign("l_pr_ppupdated", $l_pr_ppupdated);
$template_object->assign("l_pr_prexeedcheck", $l_pr_prexeedcheck);
$template_object->assign("exceeded", $exceeded);
$template_object->assign("planetexceeded", $planetexceeded);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."planet-report-ceprod.tpl");
include ("footer.php");

?>
