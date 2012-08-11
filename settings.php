<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: settings.php

include ("config/config.php");
include ("languages/$langdir/lang_settings.inc");

$title = $l_s_gamesettings;
if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

function TRUEFALSE ($truefalse,$Stat,$True,$False)
{
	return(($truefalse == $Stat) ? $True : $False);
}

$template_object->assign("templatename", $templatename);

$num = 0;

// Game Status
$template_object->assign("title", $l_s_gamestatus);

$template_object->assign("version", "Game release version");
$template_object->assign("release_version", $release_version);
$template_object->assign("l_s_time_since_reset", $l_s_time_since_reset);

$time_since = time() - strtotime($reset_date . " 00:00:00");
$timestring = '';

$weeks = $time_since/604800;
$days = ($time_since%604800)/86400;

if (round($weeks))
{
    $timestring=floor($weeks)." weeks ";
}

if (round($days))
{
    $timestring.=floor($days)." days ";
}

$template_object->assign("totaltime", $timestring);

$template_object->assign("l_s_allowpl", $l_s_allowpl);
$template_object->assign("l_s_allowplresponse", TRUEFALSE($server_closed,False,$l_s_yes,"<font color=red>$l_s_no</font>"));
$template_object->assign("l_s_allownewpl", $l_s_allownewpl);
$template_object->assign("l_s_allownewplresponse", TRUEFALSE($account_creation_closed,False,$l_s_yes,"<font color=red>$l_s_no</font>"));

// Game Options

$template_object->assign("title2", $l_s_gameoptions);

$template_object->assign("l_s_allowteamplcreds", $l_s_allowteamplcreds);
$template_object->assign("l_s_allowteamplcredsresponse", TRUEFALSE($team_planet_transfers,1,$l_s_yes,"<font color=red>$l_s_no</font>"));
$template_object->assign("l_s_allowfullscan", $l_s_allowfullscan);
$template_object->assign("l_s_allowfullscanresponse", TRUEFALSE($allow_fullscan,True,$l_s_yes,"<font color=red>$l_s_no</font>"));
$template_object->assign("l_s_sofa", $l_s_sofa);
$template_object->assign("l_s_sofaresponse", TRUEFALSE($sofa_on,True,$l_s_yes,"<font color=red>$l_s_no</font>"));
$template_object->assign("l_s_showpassword", $l_s_showpassword);
$template_object->assign("l_s_showpasswordresponse", TRUEFALSE($display_password,True,$l_s_yes,"<font color=red>$l_s_no</font>"));
$template_object->assign("l_s_genesisdestroy", $l_s_genesisdestroy);
$template_object->assign("l_s_genesisdestroyresponse", TRUEFALSE($allow_genesis_destroy,True,$l_s_yes,"<font color=red>$l_s_no</font>"));
$template_object->assign("l_s_igb", $l_s_igb);
$template_object->assign("l_s_igbresponse", TRUEFALSE($allow_ibank,True,$l_s_enabled,"<font color=red>$l_s_disabled</font>"));
$template_object->assign("l_s_ksm", $l_s_ksm);
$template_object->assign("l_s_ksmresponse", TRUEFALSE($galaxy_map_enabled,True,$l_s_enabled,"<font color=red>$l_s_disabled</font>"));
$template_object->assign("l_s_navcomp", $l_s_navcomp);
$template_object->assign("l_s_navcompresponse", TRUEFALSE($allow_navcomp,True,$l_s_enabled,"<font color=red>$l_s_disabled</font>"));
$template_object->assign("l_s_newbienice", $l_s_newbienice);
$template_object->assign("l_s_newbieniceresponse", TRUEFALSE($newbie_nice,"YES",$l_s_enabled,"<font color=red>$l_s_disabled</font>"));
$temp = ($enable_spies) ? "YES": "NO";
$template_object->assign("l_s_spies", $l_s_spies);
$template_object->assign("l_s_spiesresponse", TRUEFALSE($temp,"YES",$l_s_enabled,"<font color=red>$l_s_disabled</font>"));

$template_object->assign("enable_spies", $enable_spies);
if ($enable_spies)
{
	$temp = ($allow_spy_capture_planets) ? "YES": "NO";
	$template_object->assign("l_s_spycapture", $l_s_spycapture);
	$template_object->assign("l_s_spycaptureresponse", TRUEFALSE($temp,"YES",$l_s_yes,"<font color=red>$l_s_no</font>"));
}

// Game Settings

$template_object->assign("title3", $l_s_gamesettings);

$template_object->assign("l_s_gameversion", $l_s_gameversion);
$template_object->assign("game_name", $game_name);
$template_object->assign("l_s_minhullmines", $l_s_minhullmines);
$template_object->assign("l_s_averagetechewd", $l_s_averagetechewd);
$template_object->assign("ewd_maxavgtechlevel", $ewd_maxavgtechlevel);

$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
db_op_result($max_query,__LINE__,__FILE__);

$sector_max = $max_query->fields['sector_id'];

$template_object->assign("l_s_numsectors", $l_s_numsectors);
$template_object->assign("sector_max", NUMBER($sector_max));
$template_object->assign("l_s_maxwarpspersector", $l_s_maxwarpspersector);
$template_object->assign("link_max", $link_max);
$template_object->assign("l_s_averagetechfed", $l_s_averagetechfed);
$template_object->assign("fed_max_avg_tech", $fed_max_avg_tech);

$template_object->assign("allow_ibank", $allow_ibank);
if ($allow_ibank)
{
	$template_object->assign("l_s_igbirateperupdate", $l_s_igbirateperupdate);
	$template_object->assign("bankinterest", $ibank_interest * 100);
	$template_object->assign("l_s_igblrateperupdate", $l_s_igblrateperupdate);
	$template_object->assign("loaninterest", $ibank_loaninterest * 100);
}  

$template_object->assign("l_s_techupgradebase", $l_s_techupgradebase);
$template_object->assign("basedefense", $basedefense);

$template_object->assign("l_s_collimit", $l_s_collimit);
$template_object->assign("colonist_limit", NUMBER($colonist_limit));

$template_object->assign("l_s_maxturns", $l_s_maxturns);
$template_object->assign("max_turns", NUMBER($max_turns));
$template_object->assign("l_s_maxplanetssector", $l_s_maxplanetssector);
$template_object->assign("max_planets_sector", $max_sector_size);
$template_object->assign("l_s_maxtraderoutes", $l_s_maxtraderoutes);
$template_object->assign("max_traderoutes_player", $max_traderoutes_player);
$template_object->assign("l_s_colreprodrate", $l_s_colreprodrate);
$template_object->assign("colonist_reproduction_rate", $colonist_reproduction_rate);
$template_object->assign("l_s_energyperfighter", $l_s_energyperfighter);
$template_object->assign("energy_per_fighter", $energy_per_fighter);

$template_object->assign("l_s_secfighterdegrade", $l_s_secfighterdegrade);
$template_object->assign("defense_degrade_rate", $defense_degrade_rate * 100);

$template_object->assign("enable_spies", $enable_spies);
if ($enable_spies)
{
	$template_object->assign("l_s_spiesperplanet", $l_s_spiesperplanet);
	$template_object->assign("max_spies_per_planet", $max_spies_per_planet);
	$template_object->assign("l_s_spysuccessfactor", $l_s_spysuccessfactor);
	$template_object->assign("enable_spies2", NUMBER($enable_spies,1));
	$template_object->assign("l_s_spykillfactor", $l_s_spykillfactor);
	$template_object->assign("spy_kill_factor", NUMBER($spy_kill_factor,1));
}

$cargo_query = $db->SelectLimit("SELECT prate from {$db_prefix}class_modules_commodities where class='colonists'", 1);
db_op_result($cargo_query,__LINE__,__FILE__);

$rate = 1 / $cargo_query->fields['prate'];

$cargo_query = $db->Execute("SELECT classname, prate from {$db_prefix}class_modules_commodities where cargoplanet=1 and class != 'colonists'");
db_op_result($cargo_query,__LINE__,__FILE__);

$cargoproductionname = array();
$cargoprate = array();

while (!$cargo_query->EOF) 
{
	$cargoname = $cargo_query->fields['classname'];
	$cargoprate[] = ($cargo_query->fields['prate'] == 0) ? 0 : NUMBER($rate/$cargo_query->fields['prate']);
	$cargoproductionname[] = str_replace("[commodity]", ucwords($cargoname), $l_s_colsper);
	$cargo_query->Movenext();
}

$template_object->assign("cargoprate", $cargoprate);
$template_object->assign("cargoproductionname", $cargoproductionname);

$template_object->assign("l_s_colspercreds", $l_s_colspercreds);
$template_object->assign("credits_prate", NUMBER($rate/$credits_prate));

$cargo_query = $db->Execute("SELECT class, prate from {$db_prefix}class_modules_planet where class = 'Planet_Torpedo' or class = 'Planet_Fighter'");
db_op_result($cargo_query,__LINE__,__FILE__);

while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['class'];
	$prate[$cargotype] = $cargo_query->fields['prate'];
	$cargo_query->Movenext();
}

$template_object->assign("l_s_colsperfighter", $l_s_colsperfighter);
$template_object->assign("fighter_prate", NUMBER($rate/$prate['Planet_Fighter']));

$template_object->assign("l_s_colspertorp", $l_s_colspertorp);
$template_object->assign("torpedo_prate", NUMBER($rate/$prate['Planet_Torpedo']));

$debug_query = $db->Execute("SELECT * FROM {$db_prefix}config_values order by section, name");
db_op_result($debug_query,__LINE__,__FILE__);

$listcount = 0;
while (!$debug_query->EOF && $debug_query)
{
	$row = $debug_query->fields;
	$db_config_name = $row['name'];
	$db_config_value = $row['value'];
	$db_config_info = $row['description'];
	if(trim($row['section']) != "Backup Settings" && trim($row['section']) != "Database Debug Settings" && trim($row['section']) != "GZip Compression" && trim($row['section']) != "Server Lists" && trim($row['section']) != "Template Engine Settings" && trim($row['section']) != "SMTP Email Settings")
	{
		if($db_config_section != trim($row['section']) and trim($row['section']) != ""){
			$db_config_section = trim($row['section']);
			if($db_config_section != "Reset Date"){
				$variablelist[$listcount] =  "section|" . $db_config_section . "|section";
				$listcount++;
			}
		}
		if($db_config_name != "scheduled_reset" && $db_config_name != "reset_date")
		{
			$variablelist[$listcount] =  $db_config_name . "|" . $db_config_value . "|" . $db_config_info;
			$listcount++;
		}
	}
	$debug_query->MoveNext();
}

$template_object->assign("listcount", $listcount);
$template_object->assign("variablelist", $variablelist);

$template_object->assign("l_global_mlogin", $l_global_mlogin);
$template_object->display($templatename."settings.tpl");
include ("footer.php");

?>
