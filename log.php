<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: log.php

include ("config/config.php");
include ("languages/$langdir/lang_lrscan.inc");
include ("languages/$langdir/lang_planet.inc"); 
include ("support/log_data/$langdir/lang_log.inc");
include ("support/log_data/log_switch_data.inc");

get_post_ifset("nonext, loglist, startdate, dberror, combat, dead_player, menu");

$title = $l_log_titlet;
$md5adminpass = md5($adminpass);

if (isset($_GET['md5admin_password']))
{
	$md5admin_password = $_GET['md5admin_password'];
}

if (isset($_POST['md5admin_password']))
{
	$md5admin_password = $_POST['md5admin_password'];
}

if ((!isset($md5admin_password)) || ($md5admin_password == ''))
{
	$md5admin_password = '';
}

if (isset($_GET['player']))
{
	$player = $_GET['player'];
}

if (isset($_POST['player']))
{
	$player = $_POST['player'];
}

if ((!isset($player)) || ($player == ''))
{
	$player = '';
}

if ($md5adminpass <> $md5admin_password)
{
	if (checklogin())
	{
		$template_object->enable_gzip = 0;
		include ("footer.php");
		die();
	}
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


if ($md5admin_password == $md5adminpass) //check if called by admin script
{
	$playerinfo['player_id'] = $player;

	if ($player == 0)
	{
		$playerinfo['character_name'] = 'Administrator';
	}
	else
	{
		if($dead_player == 1)
		{
			$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}dead_players WHERE player_id=$player", 1);
			db_op_result($res,__LINE__,__FILE__);					
			$targetname = $res->fields;
			$playerinfo['character_name'] = "<font color=\"ff0000\">(DEAD)</font> " . $targetname['character_name'];
		}
		else
		{
			$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$player", 1);
			db_op_result($res,__LINE__,__FILE__);					
			$targetname = $res->fields;
			$playerinfo['character_name'] = $targetname['character_name'];
		}
	}

	$loglist = 8;
}
else
{
	$player = $playerinfo['player_id'];
}

//Recognizes only some (d, j, F, M, Y, H, i) format string components!
function simple_date($frmtstr, $full_year, $month_full, $month_short, $day, $hour, $min)
{
	$retvalue="";
	for($cntr=0; $cntr < AAT_strlen($frmtstr); $cntr++)
	{
		switch (AAT_substr($frmtstr,$cntr,1))
		{
			case "d":
				if (AAT_strlen($day)==1)
				{
					$retvalue .= "0$day";
				}
				else
				{
					$retvalue .= $day;
				}
			break;
			
			case "j":
				$retvalue .= NUMBER($day);
			break;
			
			case "F":
				$retvalue .= $month_full;
			break;
			
			case "M":
				$retvalue .= $month_short;
			break;
			
			case "Y":
				$retvalue .= $full_year;
			break;

			case "H":
				if (AAT_strlen($hour)==1)
				{
					$retvalue .= "0$hour";
				}
				else
				{
					$retvalue .= $hour;
				}
			break;
			
			case "i":
				if (AAT_strlen($min)==1)
				{
					$retvalue .= "0$min";
				}
				else
				{
					$retvalue .= $min;
				}
			break;
			
			default:
				$retvalue .= AAT_substr($frmtstr,$cntr,1);
			break;
		}
	}
	return $retvalue;
}

function get_probe_class_names()
{
	global $probetypeinfo;
	$probetypeinfo = array();
	$filelist = get_dirlist($gameroot."class/probes/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$probename =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($probename)){
				include ("class/probes/" . $probename . ".inc");
			}
			$probeobject = new $probename();
			$class = $probeobject->class;
			$probetypeinfo[$class] = $probeobject->l_probe_type;
		}
	}
}

$template_object->assign("isadmin", ($md5adminpass == $md5admin_password));
$template_object->assign("l_log_select", $l_log_select);
$template_object->assign("startdate", $startdate.$postlink);
$template_object->assign("l_log_general", $l_log_general);
$template_object->assign("l_log_dig", $l_log_dig);
$template_object->assign("l_log_spy", $l_log_spy);
$template_object->assign("l_log_disaster", $l_log_disaster);
$template_object->assign("l_log_nova", $l_log_nova);
$template_object->assign("l_log_attack", $l_log_attack);
$template_object->assign("l_log_scan", $l_log_scan);
$template_object->assign("l_log_starv", $l_log_starv);
$template_object->assign("l_log_probe", $l_log_probe);
$template_object->assign("l_log_autotrade", $l_log_autotrade);
$template_object->assign("l_log_combined", $l_log_combined);

$logline = str_replace("[player]", "$playerinfo[character_name]", $l_log_log);

$template_object->assign("templatename", $templatename);
$template_object->assign("logline", $logline);
$template_object->assign("l_log_combined", $l_log_combined);

if($loglist == ""){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG0_%') ";
	$logtype = $l_log_general;
}

if($loglist == 1){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG1_%') ";
	$logtype = $l_log_dig;
}

if($loglist == 2){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG2_%') ";
	$logtype = $l_log_spy;
}

if($loglist == 3){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG3_%') ";
	$logtype = $l_log_disaster;
}

if($loglist == 4){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG4_%') ";
	$logtype = $l_log_nova;
}

if($loglist == 5){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG5_%') ";
	$logtype = $l_log_attack;
}

if($loglist == 6){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG6_%') ";
	$logtype = $l_log_scan;
}

if($loglist == 7){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG7_%') ";
	$logtype = $l_log_starv;
}

if($loglist == 8){
	$typelist = "";
	$logtype = $l_log_combined;
	get_probe_class_names();
}

if($loglist == 9){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG9_%') ";
	$logtype = $l_log_probe;
	get_probe_class_names();
}

if($loglist == 10){
	$typelist = " and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG10_%') ";
	$logtype = $l_log_autotrade;
}

if (empty($startdate))
  $startdate = date("Y-m-d");

$entry = simple_date($local_logdate_med_format, AAT_substr($startdate, 0, 4), $l_log_months[AAT_substr($startdate, 5, 2) - 1], $l_log_months_short[AAT_substr($startdate, 5, 2) - 1], AAT_substr($startdate, 8, 2), 0, 0 ) ;

$template_object->assign("l_log_start", $l_log_start);
$template_object->assign("entry", $entry);
$template_object->assign("logtype", $logtype);
$template_object->assign("dead_player", $dead_player);
$template_object->assign("menu", $menu);

if ($player == 0)
{
	if($dberror == 1 )
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}admin_log WHERE time LIKE '$startdate%' and type='LOG0_ADMIN_DBERROR' ORDER BY time DESC, log_id DESC");
		db_op_result($res,__LINE__,__FILE__);					
	}
	else
	if($combat == 1 )
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}admin_log WHERE time LIKE '$startdate%' and type='LOG0_ADMIN_COMBAT' ORDER BY time DESC, log_id DESC");
		db_op_result($res,__LINE__,__FILE__);					
	}
	else
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}admin_log WHERE time LIKE '$startdate%' and (type='LOG_LOGIN' or type='LOG_LOGOUT' or type LIKE 'LOG0_%') and type!='LOG0_ADMIN_DBERROR' and type!='LOG0_ADMIN_COMBAT' ORDER BY time DESC, log_id DESC");
		db_op_result($res,__LINE__,__FILE__);					
	}
}
else
{
	if($dead_player == 1)
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}dead_player_logs WHERE player_id=$playerinfo[player_id] AND time LIKE '$startdate%' ".$typelist."ORDER BY time DESC, log_id DESC");
		db_op_result($res,__LINE__,__FILE__);					
	}
	else
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}logs WHERE player_id=$playerinfo[player_id] AND time LIKE '$startdate%' ".$typelist."ORDER BY time DESC, log_id DESC");
		db_op_result($res,__LINE__,__FILE__);					
	}
}

$logcount = 0;
while (!$res->EOF)
{
	$event = log_parse($res->fields);
	$time = simple_date($local_logdate_full_format, AAT_substr($res->fields['time'], 0, 4), $l_log_months[AAT_substr($res->fields['time'], 5, 2) - 1], $l_log_months_short[AAT_substr($res->fields['time'], 5, 2) - 1], AAT_substr($res->fields['time'], 8, 2), AAT_substr($res->fields['time'], 11, 2), AAT_substr($res->fields['time'], 14, 2) );

	$logtitle[$logcount] = $event['title'];
	$logbody[$logcount] = $event['text'];
	$logtime[$logcount] = $time;
	$logcount++;
	$res->MoveNext();
}

$template_object->assign("logtitle", $logtitle);
$template_object->assign("logbody", $logbody);
$template_object->assign("logtime", $logtime);
$template_object->assign("logcount", $logcount);

$template_object->assign("l_log_end", $l_log_end);
$template_object->assign("endentry", $entry);

$month = AAT_substr($startdate, 5, 2);
$day = AAT_substr($startdate, 8, 2) - 1;
$year = AAT_substr($startdate, 0, 4);

$backlink = mktime (0,0,0,$month,$day,$year);
$backlink = date("Y-m-d", $backlink);
$backdate = simple_date($local_logdate_short_format, 0, $l_log_months[AAT_substr($backlink, 5, 2) - 1], $l_log_months_short[AAT_substr($backlink, 5, 2) - 1], AAT_substr($backlink, 8, 2), 0, 0);

$day = substr($startdate, 8, 2) + 1;

$nextlink = mktime (0,0,0,$month,$day,$year);
$nextlink = date("Y-m-d", $nextlink);
$nextdate = simple_date($local_logdate_short_format, 0, $l_log_months[AAT_substr($nextlink, 5, 2) - 1], $l_log_months_short[AAT_substr($nextlink, 5, 2) - 1], AAT_substr($nextlink, 8, 2), 0, 0);

if ($md5admin_password == $md5adminpass) //fix for admin log view
  $postlink =  "&player=$player&dberror=$dberror&combat=$combat&md5admin_password=" . urlencode($md5admin_password) . "&dead_player=$dead_player&menu=$menu";
else
  $postlink = "";

$template_object->assign("loglist", $loglist);
$template_object->assign("backlink", $backlink.$postlink);
$template_object->assign("nextlink", $nextlink.$postlink);
$template_object->assign("nextdate", $nextdate);
$template_object->assign("backdate", $backdate);
$template_object->assign("md5admin_password", $md5admin_password);
$template_object->assign("dberror", $dberror);
$template_object->assign("combat", $combat);
$template_object->assign("l_log_click", $l_log_click);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."log.tpl");
include ('footer.php');

close_database();
?>
