<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: spy.php

include ("config/config.php");
include ("languages/$langdir/lang_planets.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_spy.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/myrand.inc");
include ("globals/device_ship_tech_modify.inc");
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

get_post_ifset("info_id_all, info_id, command, by, by1, by2, by3, planet_id, spy_id, dismiss, doit, mode, jobid, type");

function calc_ship_cleanup_cost($level_avg = 0, $type = 1)
{
	global $level_factor, $upgrade_cost;
  
	if ($type==1)
	{
		$c=1;
	}
	elseif ($type==2)
	{
		$c=2;
	}
	else
	{
		$c=4;
	}

	// You must check for upper boundary. Otherwise the typecast can cause it to flip to negative amounts.
	$cl_cost = (mypw($level_factor, ($level_avg * 1.1)) * 70 * $upgrade_cost * $c);

	if ($cl_cost < 0)
	{
		$cl_cost = 2000000000;
	}
  
	$cl_cost = floor( $cl_cost);  
	return $cl_cost;
}

function calc_planet_cleanup_cost($colo = 0, $type = 1)
{
	global $db, $db_prefix, $planet_id, $planetinfo;
	global $colonist_limit, $colonist_tech_add, $spy_cleanup_planet_credits1, $spy_cleanup_planet_credits2, $spy_cleanup_planet_credits3, $max_spies_per_planet;

	$spy_cleanup_planet_credits[1] = $spy_cleanup_planet_credits1;
	$spy_cleanup_planet_credits[2] = $spy_cleanup_planet_credits2;
	$spy_cleanup_planet_credits[3] = $spy_cleanup_planet_credits3;
	$cl_cost = ($colonist_limit + ($colonist_tech_add * (($planetinfo['fighter_normal'] + $planetinfo['cloak_normal'] + $planetinfo['jammer_normal'] + $planetinfo['shields_normal'] + $planetinfo['torp_launchers_normal'] + $planetinfo['beams_normal'] + $planetinfo['sensors_normal']) / 7))) * $spy_cleanup_planet_credits[$type];

	// Here we reduce the costs of scans by 9.9% per spy the owner has on the planet.
	$res66 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id=$planet_id AND owner_id=$planetinfo[owner]");
	$spies_on_planet = $res66->RecordCount();
  
	$cl_cost = ($cl_cost - ($cl_cost * $spies_on_planet / $max_spies_per_planet * 0.50) );  
	
	$cl_cost = floor( $cl_cost);  
	return $cl_cost;
}

$title = $l_spy_title;

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if (!$enable_spies) {
	$template_object->assign("title", $title);
	$template_object->assign("error_msg", $l_spy_disabled);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."spy-die.tpl");
	include ("footer.php");
	die();
}

if (checklogin() or $tournament_setup_access == 1) {
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id=$sectorinfo[zone_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$zoneinfo = $debug_query->fields;

if($playerinfo['template'] == '' or !isset($playerinfo['template'])) {
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

if ((!isset($planet_id)) || ($planet_id == '')) {
	$planet_id = '-1';
}

if ((!isset($spy_id)) || ($spy_id == '')) {
	$spy_id = '-1';
}

$template_object->assign("command", $command);
$template_object->assign("l_spy_menu", $l_spy_menu);
$template_object->assign("l_clickme", $l_clickme);

$spy_cleanup_ship_turns[1] = $spy_cleanup_ship_turns1;
$spy_cleanup_ship_turns[2] = $spy_cleanup_ship_turns2;
$spy_cleanup_ship_turns[3] = $spy_cleanup_ship_turns3;

$spy_cleanup_planet_turns[1] = $spy_cleanup_planet_turns1;
$spy_cleanup_planet_turns[2] = $spy_cleanup_planet_turns2;
$spy_cleanup_planet_turns[3] = $spy_cleanup_planet_turns3;

$spy_cleanup_planet_credits[1] = $spy_cleanup_planet_credits1;
$spy_cleanup_planet_credits[2] = $spy_cleanup_planet_credits2;
$spy_cleanup_planet_credits[3] = $spy_cleanup_planet_credits3;

$spy_object = array();
$job_type = array();
$job_name = array();
$classcount = 0;

$filelist = get_dirlist($gameroot."class/spies/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$spy_classname =  str_replace(".inc", "", $filelist[$c]); 
		if(!class_exists($spy_classname)){
			include ("class/spies/" . $spy_classname . ".inc");
		}
		$store_object = new $spy_classname();
		$job_type[$classcount] = $store_object->id;
		$job_name[$job_type[$classcount]] = $store_object->classname;
		$description[$job_type[$classcount]] = $store_object->description;
		$spy_object[$job_type[$classcount]] = $store_object;
		$classcount++;
	}
}

$template_object->assign("job_name", $job_name);
$template_object->assign("l_spy_legend", $l_spy_legend);
$template_object->assign("description", $description);
$template_object->assign("l_spy_description", $l_spy_description);
$template_object->assign("l_spy_changeerror", $l_spy_changeerror);
$template_object->assign("l_spy_changebutton", $l_spy_changebutton);
$template_object->assign("l_spy_changejob", $l_spy_changejob);

switch ($command)
{
	case "send":	 //SENDING spy to enemy planet
	$res3 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$planet_id", 1);
	$planetinfo = $res3->fields;
	if ($planetinfo['owner'] == 2 or $planetinfo['owner'] == 3)
	{
		$template_object->assign("error_msg", $l_spy_cantsendfeds);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}

	if ($planetinfo['team'] != 0)
	{
		if($planetinfo['owner'] != $playerinfo['player_id'])
		{
			if($planetinfo['team'] == $playerinfo['team'])
			{
				$template_object->assign("error_msg", $l_spy_cantsendteam);
				$template_object->assign("error_msg2", "");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."spy-die.tpl");
				include ("footer.php");
				die();
			}
		}
	}

	if ($playerinfo['turns'] < 1) {
		$template_object->assign("error_msg", $l_spy_noturn);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}
  
	$res2 = $db->Execute("SELECT spy_id, job_id FROM {$db_prefix}spies WHERE owner_id = $playerinfo[player_id] AND ship_id = $shipinfo[ship_id] LIMIT 1");// AND active = 'N'
	$result = $res2->RecordCount();
	if (!$result) {
		$template_object->assign("error_msg", $l_spy_notonboard);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	} else {
		$spyinfo = $res2->fields['spy_id'];
		$job_id = $res2->fields['job_id'];
	}

//	$base_factor = ($planetinfo['base'] == 'Y') ? $basedefense : 0;
	$base_factor = 0;
	$planetinfo['sensors'] += $base_factor;

	$res = $db->Execute("SELECT max(sensors) as maxsensors FROM {$db_prefix}ships WHERE planet_id=$planet_id AND on_planet='Y'");
	if ($planetinfo['sensors'] < $res->fields['maxsensors']) {
		$planetinfo['sensors'] = $res->fields['maxsensors'];
	}
  
	if ($shipinfo['sector_id'] != $planetinfo['sector_id']) {
		$template_object->assign("error_msg", $l_planet_none);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}

	if ($planetinfo['owner'] == $playerinfo['player_id']) {
		$template_object->assign("error_msg", $l_spy_ownplanet);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}
	elseif ($planetinfo['owner'] == 0)
	{
		$template_object->assign("error_msg", $l_spy_unownedplanet);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}
  
	$res5 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id=$planet_id AND owner_id=$playerinfo[player_id]");
	$num_spies = $res5->RecordCount();
	if ($num_spies >= $max_spies_per_planet) {
		$l_spy_planetfull = str_replace("[max]", $max_spies_per_planet, $l_spy_planetfull);
		$template_object->assign("error_msg", $l_spy_planetfull);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}

	$template_object->assign("executecommand", empty($doit));
	if (empty($doit)) {
		$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$planetinfo[owner]", 1);
		$ownerinfo = $result3->fields;

		$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 0);

		if($isfedbounty > 0)
		{
			$template_object->assign("bountystatus", $l_by_fedbountyspy);
		}
		else
		{
			$template_object->assign("bountystatus", $l_by_nofedbountyspy);
		}

		$template_object->assign("jobid", $job_id);
		$l_spy_sendtitle = str_replace("[spyID]", "$spyinfo", $l_spy_sendtitle);
		$template_object->assign("l_spy_sendtitle", $l_spy_sendtitle);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_spy_type1", $l_spy_type1);
		$template_object->assign("l_spy_type2", $l_spy_type2);
		$template_object->assign("l_spy_type3", $l_spy_type3);
		$template_object->assign("l_spy_trytitle", $l_spy_trytitle);
		$template_object->assign("l_spy_sendbutton", $l_spy_sendbutton);
	} else {
		$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$planetinfo[owner]", 1);
		$ownerinfo = $result3->fields;

		$template_object->assign("playerbounty", "");

		$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 1);

		if($isfedbounty > 0)
		{
			$template_object->assign("error_msg", $l_by_fedbounty2);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."spy-die.tpl");
			include ("footer.php");
			die();
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns_used=turns_used+1, turns=turns-1 WHERE player_id=$playerinfo[player_id] ");
		db_op_result($debug_query,__LINE__,__FILE__);

		$success = SCAN_SUCCESS($planetinfo['sensors'], $shipinfo['cloak']);

		// Here we subtract 4% for every spy the planet owner has on the planet from the success score.
		$res66 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id=$planet_id AND owner_id=$planetinfo[owner]");
		$num_spies = $res66->RecordCount();
		$success = $success + ($num_spies * 4);

		// Here we add 4% for every spy the spy owner has on the planet to the success score.
		$res77 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id=$planet_id AND owner_id=$playerinfo[player_id]");
		$num_own_spies = $res77->RecordCount();
		$success = $success - ($num_own_spies * 4);

		$success = min(max($success, 1), 90);

		$roll = mt_rand(1,100);

		if ($roll < $success) 
		{
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE spy_id=$spyinfo ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("sendstatus", $l_spy_sendfailed);
			if (!$planetinfo['name']) 
			{
				$planetinfo['name'] = $l_unnamed;
			}
			playerlog($planetinfo['owner'], "LOG2_SPY_SEND_FAIL", "$planetinfo[name]|$planetinfo[sector_id]|$playerinfo[character_name]");
		} else {
			if (empty($mode) || ($mode!="toship" && $mode!="toplanet" && $mode!="none")) 
			{
				$mode = "toship";
			}

			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET active='Y', planet_id='$planet_id', ship_id='0', spy_cloak=$shipinfo[cloak] WHERE spy_id='$spyinfo' ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$resultinfo = $spy_object[$jobid]->change_spy($spyinfo, $planet_id, $mode);
			$template_object->assign("sendstatus", $l_spy_sendsuccessful);
		}
	}   
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	break;

case "comeback";   //GETTING your spy back from enemy planet

	if ($playerinfo['turns'] < 1) {
		$template_object->assign("error_msg", $l_spy_noturn2);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}
  
	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$planet_id", 1);
	$planetinfo = $res->fields;
	if ($shipinfo['sector_id'] != $planetinfo['sector_id']) {
		$template_object->assign("error_msg", $l_planet_none);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
	}
  
	$res = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE owner_id = $playerinfo[player_id] AND spy_id = $spy_id  AND active = 'Y' AND planet_id = $planetinfo[planet_id]");
	$template_object->assign("planetspies", $res->RecordCount());
	if ($res->RecordCount()) {
		$template_object->assign("executecommand", empty($doit));
		if (empty($doit))
		{
			$spy = $res->fields;
			$l_spy_confirm = str_replace("[spyID]", "$spy[spy_id]", $l_spy_confirm);
			$template_object->assign("l_spy_codenumber", $l_spy_codenumber);
			$template_object->assign("l_spy_job", $l_spy_job);
			$template_object->assign("l_spy_percent", $l_spy_percent);
			$template_object->assign("l_spy_move", $l_spy_move);
			$template_object->assign("l_spy_action", $l_spy_action);

			$job = "<a href=spy.php?command=change&spy_id=$spy[spy_id]&planet_id=$planet_id>" . $job_name[$spy['job_id']] . "</a>";
			$move = $l_spy_moves[$spy['move_type']];


			$template_object->assign("l_spy_confirm", $l_spy_confirm);
			$template_object->assign("spyid", $spy['spy_id']);
			$template_object->assign("job", $job);
			$template_object->assign("planet_id", $planet_id);
			$template_object->assign("move", $move);
			$template_object->assign("l_yes", $l_yes);
			$template_object->assign("l_no", $l_no);
		} else {
			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET planet_id='0', job_id='0', spy_percent='0.0', ship_id='$shipinfo[ship_id]', active='N' WHERE spy_id=$spy_id ");
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns_used=turns_used+1, turns=turns-1 WHERE player_id=$playerinfo[player_id] ");
			db_op_result($debug_query,__LINE__,__FILE__);

			$template_object->assign("l_spy_backonship", $l_spy_backonship);
		}
	} else {
		$template_object->assign("l_spy_backfailed", $l_spy_backfailed);
	}
	
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
break;

case "change":   //CHANGING your spy settings on enemy planet

	$res = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE owner_id = '$playerinfo[player_id]' AND spy_id = '$spy_id'");
	$spy = $res->fields;

	$template_object->assign("spycount", $res->RecordCount());
	if ($res->RecordCount()) {
		$template_object->assign("executecommand", empty($doit));
		if (empty($doit)) {
	  
		  if ($spy['move_type'] == 'none')
		  {
		  	$set_1 = 'CHECKED';
		  	$set_2 = '';   
		  	$set_3 = ''; 
		  }
		  elseif ($spy['move_type'] == 'toship') 
		  { 
		  	$set_1 = '';   
		  	$set_2 = 'CHECKED';   
		  	$set_3 = ''; 
		  }
		  else
		  {
		  	$set_1 = '';   
		  	$set_2 = '';   
		  	$set_3 = 'CHECKED'; 
		  }
	  
		  if ($spy['planet_id'] == '0') { $set_1 .= " DISABLED"; }

		  $l_spy_changetitle = str_replace("[spyID]", "$spy_id", $l_spy_changetitle);
			$template_object->assign("l_spy_changetitle", $l_spy_changetitle);
			$template_object->assign("spy_id", $spy_id);
			$template_object->assign("planet_id", $planet_id);
			$template_object->assign("set_1", $set_1);
			$template_object->assign("l_spy_type1", $l_spy_type1);
			$template_object->assign("set_2", $set_2);
			$template_object->assign("l_spy_type2", $l_spy_type2);
			$template_object->assign("set_3", $set_3);
			$template_object->assign("l_spy_type3", $l_spy_type3);

			$template_object->assign("jobid", $spy['job_id']);

			$template_object->assign("l_spy_trytitle", $l_spy_trytitle);
			$template_object->assign("l_spy_changebutton", $l_spy_changebutton);
		  if ($planet_id == -1) { // Not called from Planet Menu
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("l_spy_linkback", $l_spy_linkback);
			} else {
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
			}
		}
		else
		{
		  if ($mode!="toship" && $mode!="toplanet" && $mode!="none")
		  {
			$mode = "toship";
		  }
		  if ($spy['planet_id']=='0' && $mode == "none")
		  {
			$mode = "toship";
		  }

			$resultinfo = $spy_object[$jobid]->change_spy($spy_id, $spy['planet_id'], $mode);
			unset($_SESSION['currentprogram'], $currentprogram);
			unset ($template_object);
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=spy.php\">";
			die();

		}
  } else {
	$template_object->assign("l_spy_changefailed", $l_spy_changefailed);
  }
break;

case "cleanup_planet":   // TRYING to find enemy spies on my planet

	$template_object->assign("l_spy_cleanupplanettitle", $l_spy_cleanupplanettitle);

	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id='$planet_id' ", 1);
	$planetinfo=$res->fields;
	
	if ($shipinfo['sector_id'] != $planetinfo['sector_id'])
  {
		$template_object->assign("error_msg", $l_spy_cleanupplanettitle);
		$template_object->assign("error_msg2", $l_planet_none);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
  }
	
	if ($playerinfo['player_id'] != $planetinfo['owner'])
  {
		$template_object->assign("error_msg", $l_spy_cleanupplanettitle);
		$template_object->assign("error_msg2", $l_spy_notyourplanet);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
  }
  
	if($zoneinfo['zone_id'] != 3){
		$alliancefactor = 1;
	}

  for($a=1; $a<=3; $a++)
  {
	$spy_cleanup_planet_credits[$a]=calc_planet_cleanup_cost($planetinfo['colonists'],$a) * $alliancefactor; 
	$l_spy_cleanuptext[$a]=str_replace("[creds]", NUMBER($spy_cleanup_planet_credits[$a]), $l_spy_cleanuptext[$a]);
	$l_spy_cleanuptext[$a]=str_replace("[turns]", NUMBER($spy_cleanup_planet_turns[$a]), $l_spy_cleanuptext[$a]);
  }

  if ($planetinfo['credits'] < $spy_cleanup_planet_credits[1] || $playerinfo['turns'] < $spy_cleanup_planet_turns[1])
	$set[1] = "DISABLED";
  else
	$set[1] = "CHECKED";
 
  if ($planetinfo['credits'] < $spy_cleanup_planet_credits[2] || $playerinfo['turns'] < $spy_cleanup_planet_turns[2])
	$set[2] = "DISABLED";
  elseif ($set[1] == "CHECKED")
	$set[2] = "";
  else  
	$set[2] = "CHECKED";

  if ($planetinfo['credits'] < $spy_cleanup_planet_credits[3] || $playerinfo['turns'] < $spy_cleanup_planet_turns[3])
	$set[3] = "DISABLED";
  elseif ($set[1] == "CHECKED" || $set[2] == "CHECKED")
	$set[3] = "";
  else
	$set[3] = "CHECKED";

	$template_object->assign("executecommand", empty($doit));
  if (empty($doit))
  { 
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("set1", $set[1]);
	$template_object->assign("l_spy_cleanuptext1", $l_spy_cleanuptext[1]);
	$template_object->assign("set2", $set[2]);
	$template_object->assign("l_spy_cleanuptext2", $l_spy_cleanuptext[2]);
	$template_object->assign("set3", $set[3]);
	$template_object->assign("l_spy_cleanuptext3", $l_spy_cleanuptext[3]);
	$template_object->assign("disabled", ($set[1] == "DISABLED" && $set[2] == "DISABLED" && $set[3] == "DISABLED"));
	
	if ($set[1] == "DISABLED" && $set[2] == "DISABLED" && $set[3] == "DISABLED")
	{
	  $l_spy_cannotcleanupplanet = str_replace("[credits]" , NUMBER($planetinfo['credits']), $l_spy_cannotcleanupplanet);
	  $l_spy_cannotcleanupplanet = str_replace("[turns]" , NUMBER($playerinfo['turns']), $l_spy_cannotcleanupplanet);
		$template_object->assign("cleanupstatus", $l_spy_cannotcleanupplanet);
	}
	else
	{
		$template_object->assign("cleanupstatus", $l_spy_cleanupbutton1);
	}
  }
  else
  {
	$template_object->assign("l_spy_cleanupplanettitle2", $l_spy_cleanupplanettitle2);
	if ($type != 1 && $type != 2 && $type != 3)
	  $type = 1;

	$template_object->assign("disabled", $set[$type]);
	if ($set[$type] != "DISABLED") 
	{  
		mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

	  $found=0;
	  $debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns_used=turns_used+$spy_cleanup_planet_turns[$type], turns=turns-$spy_cleanup_planet_turns[$type] WHERE player_id=$playerinfo[player_id] ");
	  db_op_result($debug_query,__LINE__,__FILE__);

	  $debug_query = $db->Execute("UPDATE {$db_prefix}planets SET credits=credits-$spy_cleanup_planet_credits[$type] WHERE planet_id=$planet_id ");
	  db_op_result($debug_query,__LINE__,__FILE__);

	  $res = $db->Execute("SELECT max(sensors) AS maxsensors FROM {$db_prefix}ships WHERE planet_id=$planet_id AND on_planet='Y'");
	  if (!$res->EOF)
		if ($shipinfo['sensors'] < $res->fields['maxsensors'])
		  $shipinfo['sensors'] = $res->fields['maxsensors'];

		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id='$planet_id' ", 1);
		$planetinfo=$res->fields;

	  $res = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE active='Y' AND ship_id='0' and planet_id='$planet_id'");
		$spycount = 0;
	  while (!$res->EOF)
	  {
		$info = $res->fields;
		
		$base_factor = ($planetinfo['base'] == 'Y') ? $basedefense : 0;
		$planetinfo['sensors'] += $base_factor;

		if ($planetinfo['sensors'] < $shipinfo['sensors'])
		  $planetinfo['sensors'] = $shipinfo['sensors'];

		$spycloak = $info['spy_cloak'];

		if ($type==1)
		{
		  $success = SCAN_SUCCESS(($planetinfo['sensors'] * 0.4), $spycloak);
		}
		elseif ($type==2)
		{
		  $success = SCAN_SUCCESS(($planetinfo['sensors'] * 0.58), $spycloak);
		}
		else
		{
		  $success = SCAN_SUCCESS(($planetinfo['sensors'] * 0.61), $spycloak);
		}
		$roll = mt_rand(1,100);
		if ($roll<$success)
		{
		  $found = 1;
		$res2 = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$info[owner_id]", 1);
		db_op_result($res2,__LINE__,__FILE__);
		$character_name = $res2->fields['character_name'];
		  $l_spy_spyfoundonplanet2 = str_replace("[player]", "<B>$character_name</B>", $l_spy_spyfoundonplanet);
		  $l_spy_spyfoundonplanet2 = str_replace("[spyID]", "<B>$info[spy_id]</B>", $l_spy_spyfoundonplanet2);
		  $spyinfo[$spycount] = $l_spy_spyfoundonplanet2;
		  $spycount++;
		  if (!$planetinfo['name']) $planetinfo['name'] = $l_unnamed;
		  $res2 = $db->Execute("DELETE FROM {$db_prefix}spies WHERE spy_id=$info[spy_id]");
		  playerlog($info['owner_id'], "LOG2_SPY_KILLED_SPYOWNER", "$info[spy_id]|$planetinfo[name]|$planetinfo[sector_id]");
		}
		$res->MoveNext();
	  }

		$template_object->assign("spycount", $spycount);
		$template_object->assign("spyinfo", $spyinfo);
		$template_object->assign("found", $found);
	  if (!$found)
	  {
		$template_object->assign("l_spy_spynotfoundonplanet", $l_spy_spynotfoundonplanet);
	  }
	}  
	else
	{
		$template_object->assign("l_spy_notenough", $l_spy_notenough);
	  }
  }
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
break;

case "cleanup_ship":   // TRYING to find enemy spies on my ship

	$template_object->assign("l_spy_cleanupshiptitle", $l_spy_cleanupshiptitle);

  if ($sectorinfo['port_type']!="devices")
  {
		$template_object->assign("error_msg", $l_spy_cleanupshiptitle);
		$template_object->assign("error_msg2", $l_spy_notinspecial);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die.tpl");
		include ("footer.php");
		die();
  }

  $level_avg = $shipinfo['hull'] + $shipinfo['engines'] + $shipinfo['fighter'] + $shipinfo['beams'] + $shipinfo['torp_launchers'] + $shipinfo['shields'] + $shipinfo['armor'];
  $level_avg /=7;
  
if($zoneinfo['zone_id'] != 3){
	$alliancefactor = 1;
}

  for($a=1; $a<=3; $a++)
  {
	$spy_cleanup_ship_credits[$a]=calc_ship_cleanup_cost($level_avg,$a) * $alliancefactor;
	$l_spy_cleanupshiptext[$a]=str_replace("[creds]", NUMBER($spy_cleanup_ship_credits[$a]), $l_spy_cleanupshiptext[$a]);
	$l_spy_cleanupshiptext[$a]=str_replace("[turns]", NUMBER($spy_cleanup_ship_turns[$a]), $l_spy_cleanupshiptext[$a]);
  }

  if ($playerinfo['credits'] < $spy_cleanup_ship_credits[1] || $playerinfo['turns'] < $spy_cleanup_ship_turns[1])
	$set[1] = "DISABLED";
  else
	$set[1] = "CHECKED";
 
  if ($playerinfo['credits'] < $spy_cleanup_ship_credits[2] || $playerinfo['turns'] < $spy_cleanup_ship_turns[2])
	$set[2] = "DISABLED";
  elseif ($set[1] == "CHECKED")
	$set[2] = "";
  else  
	$set[2] = "CHECKED";

  if ($playerinfo['credits'] < $spy_cleanup_ship_credits[3] || $playerinfo['turns'] < $spy_cleanup_ship_turns[3])
	$set[3] = "DISABLED";
  elseif ($set[1] == "CHECKED" || $set[2] == "CHECKED")
	$set[3] = "";
  else
	$set[3] = "CHECKED";

	$template_object->assign("executecommand", empty($doit));
  if (empty($doit))
  { 
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("set1", $set[1]);
	$template_object->assign("l_spy_cleanupshiptext1", $l_spy_cleanupshiptext[1]);
	$template_object->assign("set2", $set[2]);
	$template_object->assign("l_spy_cleanupshiptext2", $l_spy_cleanupshiptext[2]);
	$template_object->assign("set3", $set[3]);
	$template_object->assign("l_spy_cleanupshiptext3", $l_spy_cleanupshiptext[3]);
	$template_object->assign("disabled", ($set[1] == "DISABLED" && $set[2] == "DISABLED" && $set[3] == "DISABLED"));

	
	if ($set[1] == "DISABLED" && $set[2] == "DISABLED" && $set[3] == "DISABLED")
	{
	  $l_spy_cannotcleanupship = str_replace("[credits]" , NUMBER($playerinfo['credits']), $l_spy_cannotcleanupship);
	  $l_spy_cannotcleanupship = str_replace("[turns]" , NUMBER($playerinfo['turns']), $l_spy_cannotcleanupship);
		$template_object->assign("cleanupstatus", $l_spy_cannotcleanupship);
	}
	else
	{
		$template_object->assign("cleanupstatus", $l_spy_cleanupbutton2);
	}
  }
  else
  {
		$template_object->assign("l_spy_cleanupshiptitle2", $l_spy_cleanupshiptitle2);
	if ($type != 1 && $type != 2 && $type != 3)
	  $type = 1;

	$template_object->assign("disabled", $set[$type]);
	if ($set[$type] != "DISABLED") 
	{  
		mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

	  $found=0;
	  $debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns_used=turns_used+$spy_cleanup_ship_turns[$type], turns=turns-$spy_cleanup_ship_turns[$type], credits=credits-$spy_cleanup_ship_credits[$type] WHERE player_id=$playerinfo[player_id] ");
	  db_op_result($debug_query,__LINE__,__FILE__);

	  $res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}ships.cloak, {$db_prefix}players.character_name FROM {$db_prefix}ships INNER JOIN {$db_prefix}players ON {$db_prefix}ships.player_id = {$db_prefix}players.player_id INNER JOIN {$db_prefix}spies ON {$db_prefix}players.player_id={$db_prefix}spies.owner_id WHERE {$db_prefix}spies.ship_id=$shipinfo[ship_id] AND {$db_prefix}spies.active='Y' AND {$db_prefix}spies.planet_id='0'");
		$spycount = 0;
	  while (!$res->EOF)
	  {
		$info = $res->fields;
		if ($type==1)
		{
		  $success = SCAN_SUCCESS(($shipinfo['sensors'] * 0.55), $info['spy_cloak']);
		}
		elseif ($type==2)
		{
		  $success = SCAN_SUCCESS(($shipinfo['sensors'] * 0.6), $info['spy_cloak']);
		}
		else
		{
		  $success = SCAN_SUCCESS(($shipinfo['sensors'] * 0.85), $info['spy_cloak']);
		}
		$roll = mt_rand(1,100);
		if ($roll<$success)
		{
		  $found = 1;
		  $l_spy_spyfoundonship2 = str_replace("[player]", "<B>$info[character_name]</B>", $l_spy_spyfoundonship);
		  $l_spy_spyfoundonship2 = str_replace("[spyID]", "<B>$info[spy_id]</B>", $l_spy_spyfoundonship2);
		  $spyinfo[$spycount] = $l_spy_spyfoundonship2;
			$spycount++;
		  $res2 = $db->Execute("DELETE FROM {$db_prefix}spies WHERE spy_id=$info[spy_id]");
		  playerlog($info['owner_id'], "LOG2_SHIPSPY_KILLED", "$info[spy_id]|$playerinfo[character_name]|$shipinfo[name]");
		}
		$res->MoveNext();
	  }

		$template_object->assign("spycount", $spycount);
		$template_object->assign("spyinfo", $spyinfo);
		$template_object->assign("found", $found);
	  if (!$found)
	  {
		$template_object->assign("l_spy_spynotfoundonship", $l_spy_spynotfoundonship);
	  }
	}
	else
	{
		$template_object->assign("l_spy_notenough", $l_spy_notenough);
	}
  }
break;

case "detect":   //DETECTED data

  if ($by=="time")	  $by2="det_type asc, det_time desc";
  elseif ($by=="time")  $by2="data asc, det_time desc";
  else				 $by2="det_time desc";
  
  $res = $db->Execute("SELECT * FROM {$db_prefix}detect WHERE {$db_prefix}detect.owner_id=$playerinfo[player_id] ORDER BY $by2");
  if (!$res->RecordCount()) {
		$template_object->assign("error_msg", $l_spy_noinfo);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_spy_linkback", $l_spy_linkback);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."spy-die2.tpl");
		include ("footer.php");
		die();
  }

	$template_object->assign("isinfoid", empty($info_id));
  if (!empty($info_id)) {
		$res2 = $db->Execute("SELECT * FROM {$db_prefix}detect WHERE {$db_prefix}detect.owner_id=$playerinfo[player_id] AND det_id='$info_id'");
		$template_object->assign("infocount", $res->RecordCount());
		if ($res->RecordCount()) {
			$template_object->assign("l_spy_infodeleted", $l_spy_infodeleted);
		  $res2 = $db->Execute("DELETE FROM {$db_prefix}detect WHERE det_id='$info_id'");
		} else {
			$template_object->assign("l_spy_infonotyours", $l_spy_infonotyours);
		}
  }

	$template_object->assign("isinfoidall", empty($info_id_all));
  if (!empty($info_id_all)) {
		$res2 = $db->Execute("DELETE FROM {$db_prefix}detect WHERE {$db_prefix}detect.owner_id=$playerinfo[player_id]");
		$template_object->assign("l_spy_messagesdeleted", $l_spy_messagesdeleted);
  }

	$template_object->assign("l_spy_infotitle", $l_spy_infotitle);
	$template_object->assign("l_spy_time", $l_spy_time);
	$template_object->assign("l_spy_type", $l_spy_type);
	$template_object->assign("l_spy_info", $l_spy_info);
	$template_object->assign("l_spy_deleteall", $l_spy_deleteall);

	$detectcount = 0;
  while (!$res->EOF) {
		$info = $res->fields;

		switch($info['det_type']) {
		  case 0:
				list($sector, $owner, $planet)= AAT_split ("\|", $info['data']);
				$result2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$sector'", 1);
					$sector_name = $result2->fields['sector_name'];
				
				$planet = stripslashes($planet);
				$l_spy_datatextF = str_replace("[sector]", "<a href=main.php?move_method=real&engage=1&destination=$sector_name>$sector_name</a>", $l_spy_datatext[1]);
				$l_spy_datatextF = str_replace("[player]", "<font color=white><b>$owner</b></font>", $l_spy_datatextF);
				$l_spy_datatextF = str_replace("[planet]", "<font color=white><b>$planet</b></font>", $l_spy_datatextF);
				$data=$l_spy_datatextF;
				$data_type=$l_spy_datatype[1];
			  break;
	  
			case 1:
				list($inf, $sender, $receiver,$type)= AAT_split ("\>", $info['data']);	// I use that symbol, because a letter may include '|' symbols, but cannot include '>' symbols
				if ($type == 'alliance') {
				  $l_spy_datatextF = str_replace("[sender]", "<font color=white><b>$sender</b></font>", $l_spy_datatext[2]);
				  $l_spy_datatextF = str_replace("[receiver]", "<font color=white><b>$receiver</b></font>", $l_spy_datatextF);
				  $l_spy_datatextF = str_replace("[letter]", "<font color=white><b>$inf</b></font>", $l_spy_datatextF);
				  $data=$l_spy_datatextF;
				} else {
				  $l_spy_datatextF = str_replace("[sender]", "<font color=white><b>$sender</b></font>", $l_spy_datatext[3]);
				  $l_spy_datatextF = str_replace("[receiver]", "<font color=white><b>$receiver</b></font>", $l_spy_datatextF);
				  $l_spy_datatextF = str_replace("[letter]", "<font color=white><b>$inf</b></font>", $l_spy_datatextF);
				  $data=$l_spy_datatextF;
				}
		
				$data_type=$l_spy_datatype[2];
			  break;
		}

		$det_time[$detectcount] = $info['det_time'];
		$datatype[$detectcount] = $data_type;
		$datainfo[$detectcount] = $data;
		$det_id[$detectcount] = $info['det_id'];
		$detectcount++;
		$res->MoveNext();
  }

	$template_object->assign("detectcount", $detectcount);
	$template_object->assign("l_spy_delete", $l_spy_delete);
	$template_object->assign("by", $by);
	$template_object->assign("det_time", $det_time);
	$template_object->assign("datatype", $datatype);
	$template_object->assign("datainfo", $datainfo);
	$template_object->assign("det_id", $det_id);
break;

default:	// SHOWING a summary table of all spies
	$template_object->assign("l_spy_messages", $l_spy_messages);
  
  if ($by1 == 'character_name')  $by11 = "character_name asc";
  elseif ($by1 == 'ship_name')   $by11 = "ship_name asc";
  elseif ($by1 == 'ship_type')   $by11 = "c_name asc";
  elseif ($by1 == 'move_type')   $by11 = "move_type asc, spy_id asc";
  else						  $by11 = "spy_id asc";

  if ($by2 == 'planet')		  $by22 = "{$db_prefix}planets.name asc, {$db_prefix}planets.sector_id asc, spy_id asc";
  elseif ($by2 == 'id')			$by22 = "spy_id asc";
  elseif ($by2 == 'job_id')	  $by22 = "job_id desc, spy_percent desc, spy_id asc";
  elseif ($by2 == 'percent')	 $by22 = "spy_percent desc, {$db_prefix}planets.sector_id asc, {$db_prefix}planets.name asc, spy_id asc";
  elseif ($by2 == 'move_type')   $by22 = "move_type asc, {$db_prefix}planets.sector_id asc, {$db_prefix}planets.name asc, spy_id asc";
  elseif ($by2 == 'owner')	   $by22 = "{$db_prefix}players.character_name asc, {$db_prefix}planets.sector_id asc, {$db_prefix}planets.name asc, spy_id asc";
  else						  $by22 = "{$db_prefix}planets.sector_id asc, {$db_prefix}planets.name asc, spy_id asc";

  if ($by3 == 'spycnt')			  $by33 = "spy_id_cnt ASC, {$db_prefix}planets.sector_id ASC";
  elseif ($by3 == 'plnname')	  $by33 = "{$db_prefix}planets.name ASC";
  else             $by33 = "{$db_prefix}planets.sector_id ASC";

  $res = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE {$db_prefix}spies.owner_id=$playerinfo[player_id] ");
	$template_object->assign("spycount", $res->RecordCount());
  if ($res->RecordCount()) {

		/* 4 */
		/* show, how many spies on own ship */
		$res = $db->Execute("SELECT COUNT(spy_id) AS as_spy_id FROM {$db_prefix}spies WHERE active='N' AND owner_id=$playerinfo[player_id] AND ship_id=$shipinfo[ship_id] AND planet_id='0'");
		$template_object->assign("shipspycount", $res->RecordCount());
		if ($res->RecordCount()) {
			$spy = $res->fields;
			$template_object->assign("l_spy_defaulttitle4", $l_spy_defaulttitle4);
			$template_object->assign("shipspytotal", $spy['as_spy_id']);
		} else { 
			$template_object->assign("l_spy_no4", $l_spy_no4);
		}

			/* 1 */
			/* show, spies on other ships */
			$res = $db->Execute("SELECT {$db_prefix}universe.sector_name, {$db_prefix}spies.*, {$db_prefix}players.character_name, {$db_prefix}ships.name AS ship_name, {$db_prefix}ship_types.name AS c_name, UNIX_TIMESTAMP({$db_prefix}players.last_login) AS online 
			FROM {$db_prefix}universe, {$db_prefix}spies INNER JOIN {$db_prefix}ships ON {$db_prefix}spies.ship_id={$db_prefix}ships.ship_id INNER JOIN {$db_prefix}ship_types ON {$db_prefix}ships.class={$db_prefix}ship_types.type_id INNER JOIN {$db_prefix}players ON {$db_prefix}players.player_id={$db_prefix}ships.player_id 
			WHERE {$db_prefix}spies.active='Y' AND {$db_prefix}spies.owner_id=$playerinfo[player_id] and {$db_prefix}universe.sector_id ={$db_prefix}ships.sector_id ORDER BY $by11 ");
			$template_object->assign("enemyshipspycount", $res->RecordCount());
			if ($res->RecordCount()) {
				$template_object->assign("l_spy_defaulttitle1", $l_spy_defaulttitle1);
				$template_object->assign("by2", $by2);
				$template_object->assign("by3", $by3);
				$template_object->assign("l_spy_codenumber", $l_spy_codenumber);
				$template_object->assign("l_spy_shipowner", $l_spy_shipowner);
				$template_object->assign("l_spy_shipname", $l_spy_shipname);
				$template_object->assign("l_spy_shiptype", $l_spy_shiptype);
				$template_object->assign("l_spy_shiplocation", $l_spy_shiplocation);
				$template_object->assign("l_spy_move", $l_spy_move);
				$enemyshipcount = 0;
			while (!$res->EOF) {
				$spy = $res->fields;
				if ((time() - $spy['online'])/60 > 5) {
					$spy['sector_name'] = $l_spy_notknown;
				} else {
				  $spy['sector_name'] = "<a href=main.php?move_method=real&engage=1&destination=$spy[sector_name]>$spy[sector_name]</a>";
				}
				$move = $l_spy_moves[$spy['move_type']];

				$spy_id[$enemyshipcount] = $spy['spy_id'];
				$playername[$enemyshipcount] = $spy['character_name'];
				$shipid[$enemyshipcount] = $spy['ship_id'];
				$shipname[$enemyshipcount] = $spy['ship_name'];
				$shipclass[$enemyshipcount] = $spy['c_name'];
				$spysector[$enemyshipcount] = $spy['sector_name'];
				$movetype[$enemyshipcount] = $move;

				$enemyshipcount++;
				$res->MoveNext();
			}
			$template_object->assign("enemyshipcount", $enemyshipcount);
			$template_object->assign("spy_id", $spy_id);
			$template_object->assign("playername", $playername);
			$template_object->assign("shipid", $shipid);
			$template_object->assign("shipname", $shipname);
			$template_object->assign("shipclass", $shipclass);
			$template_object->assign("spysector", $spysector);
			$template_object->assign("movetype", $movetype);
		} else {
			$template_object->assign("l_spy_no1", $l_spy_no1);
		}

		/* 2 */
		/* show spies on enemy planets */
		$res = $db->Execute("SELECT {$db_prefix}universe.sector_name, {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}players.character_name FROM {$db_prefix}universe, {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id={$db_prefix}planets.planet_id LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id={$db_prefix}planets.owner WHERE {$db_prefix}spies.owner_id=$playerinfo[player_id] AND {$db_prefix}spies.owner_id<>{$db_prefix}planets.owner and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id ORDER BY $by22 ");
		$template_object->assign("planetspycount", $res->RecordCount());
		if ($res->RecordCount()) {
			$template_object->assign("l_spy_defaulttitle2", $l_spy_defaulttitle2);
			$template_object->assign("by1", $by1);
			$template_object->assign("by3", $by3);
			$template_object->assign("l_spy_codenumber", $l_spy_codenumber);
			$template_object->assign("l_spy_planetowner", $l_spy_planetowner);
			$template_object->assign("l_spy_planetname", $l_spy_planetname);
			$template_object->assign("l_spy_sector", $l_spy_sector);
			$template_object->assign("l_spy_job", $l_spy_job);
			$template_object->assign("l_spy_percent", $l_spy_percent);
			$template_object->assign("l_spy_move", $l_spy_move);

			$enemyplanetcount = 0;
		  while (!$res->EOF) {
				$spy = $res->fields;

				  $job = $job_name[$spy['job_id']];

				$temp = $spy['move_type'];
				$move = $l_spy_moves[$temp];

				if (empty($spy['name'])) { $spy['name'] = $l_unnamed; }
		 		if (empty($spy['character_name'])) { $spy['character_name'] = $l_unowned; }

				$pspy_id[$enemyplanetcount] = $spy['spy_id'];
				$pplayername[$enemyplanetcount] = $spy['character_name'];
				$pname[$enemyplanetcount] = $spy['name'];
				$psector[$enemyplanetcount] = $spy['sector_name'];
				$pjob[$enemyplanetcount] = $job;
				$pmovetype[$enemyplanetcount] = $move;
				
				$enemyplanetcount++;
				$res->MoveNext();
		  }
			$template_object->assign("enemyplanetcount", $enemyplanetcount);
			$template_object->assign("pspy_id", $pspy_id);
			$template_object->assign("pplayername", $pplayername);
			$template_object->assign("pname", $pname);
			$template_object->assign("psector", $psector);
			$template_object->assign("pjob", $pjob);
			$template_object->assign("ppercent", $ppercent);
			$template_object->assign("pmovetype", $pmovetype);
		} else {
			$template_object->assign("l_spy_no2", $l_spy_no2);
		}

		/* 3 */
		/* show spies on own planets */
		$line_color = "#23244F";
		$res = $db->Execute("SELECT COUNT({$db_prefix}spies.spy_id) AS spy_id_cnt, {$db_prefix}planets.name, {$db_prefix}universe.sector_name FROM {$db_prefix}universe, {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id={$db_prefix}planets.planet_id WHERE {$db_prefix}spies.active='N' AND {$db_prefix}planets.owner=$playerinfo[player_id] AND {$db_prefix}spies.owner_id=$playerinfo[player_id] and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id GROUP BY {$db_prefix}planets.planet_id ORDER BY $by33 ");
		$template_object->assign("myplanetspycount", $res->RecordCount());
		if ($res->RecordCount()) {
			$template_object->assign("l_spy_defaulttitle3", $l_spy_defaulttitle3);
			$template_object->assign("l_spy_sector", $l_spy_sector);
			$template_object->assign("l_spy_planetname", $l_spy_planetname);
			$template_object->assign("l_spy_onplanet", $l_spy_onplanet);
			$ownplanetspycount = 0;
		  while (!$res->EOF) {
				$spy = $res->fields;
		
				if (empty($spy['name'])) { $spy['name'] = $l_unnamed; }

				$mpsector[$ownplanetspycount] = $spy['sector_name'];
				$mpname[$ownplanetspycount] = $spy['name'];
				$mpcount[$ownplanetspycount] = $spy['spy_id_cnt'];

				$ownplanetspycount++;
				$res->MoveNext();
		  }
			$template_object->assign("ownplanetspycount", $ownplanetspycount);
			$template_object->assign("mpsector", $mpsector);
			$template_object->assign("mpname", $mpname);
			$template_object->assign("mpcount", $mpcount);
		} else {
			$template_object->assign("l_spy_no3", $l_spy_no3);
		}
	/* show message - player not own spies */
	} else {
		$template_object->assign("l_spy_nospiesatall", $l_spy_nospiesatall);
	}
break;
}   //swich

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."spy.tpl");

include ("footer.php");
?>
