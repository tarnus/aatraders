<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: footer.php

$silent = 1;
$timeleft = '';

global $db ,$db_prefix, $sched_ticks, $langdir, $create_universe, $default_template, $playerinfo, $template_object;

include ("languages/$langdir/lang_footer.inc");

$template_object->assign("is_adminpopup", 0);

if(is_file($gameroot.'support/adminpopup.inc'))
{
	$new_time = @filemtime($gameroot.'support/adminpopup.inc') + 60;

	if($new_time < time())
	{
		@unlink($gameroot.'support/adminpopup.inc');
	}
	else
	{
		$lines = @file ($gameroot.'support/adminpopup.inc');
		$adminpopup = "";
		for($i=0; $i<count($lines); $i++)
			$adminpopup .= $lines[$i];

		$template_object->assign("adminpopup", $adminpopup);
		$template_object->assign("is_adminpopup", 1);
	}
}

// Players online now
if($index_page != 1)
{
	$unixstamp = time();

	if($player_online_timelimit > 0 && isset($playerinfo['player_online_time']))
	{
		$overlimitwhere = " and floor($playerinfo[player_online_time] / 60) <= $player_online_timelimit";
	}
	else
	{
		$overlimitwhere = "";
	}

	$debug_query = $db->Execute("SELECT player_id from {$db_prefix}players WHERE TIMESTAMPDIFF(MINUTE,last_login,'" . date("Y-m-d H:i:s") . "') < 5 and email NOT LIKE '%@npc' and player_id > 3 $overlimitwhere");
	db_op_result($debug_query,__LINE__,__FILE__);
	$online = $debug_query->RecordCount();

	// Time left til next update
	$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;
	$debug_query = $db->Execute("SELECT last_run FROM {$db_prefix}scheduler WHERE sched_file ='sched_turns.inc'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$row = $debug_query->fields['last_run'];

	$mySEC = ($sched_ticks * 60) - ($unixstamp-strtotime($row));
	if ($mySEC <= 0)
	{
		$mySEC = 1;
	}

	if ($online == 0)
	{
		$players_online = $l_footer_no_players_on;
	}
	else
	{
		$players_online = $l_footer_players_on_2 . $online;
	}

	if($player_limit > 0)
	{
		$players_open .= $l_footer_open_slots . $player_limit;
	}
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}

if (isset($template_object))
{
	$currentprogram = basename($_SERVER['PHP_SELF']);
	$currentprogram = str_replace(".php", ".inc", $currentprogram);
	$template_object->assign("currentprogram", $currentprogram);

	if($playerinfo['player_id'] != '' && isset($playerinfo['player_id']) && basename($_SERVER['PHP_SELF']) != "log.php"){
		$result = $db->Execute("SELECT COUNT(ID) as total FROM {$db_prefix}messages WHERE recp_id='".$playerinfo['player_id']."' AND notified='N'");
		$template_object->assign("instantmessagecount", $result->fields['total']);
		$template_object->assign("l_instant_messages_waiting", str_replace("[count]", $result->fields['total'], $l_instant_messages_waiting));
		if ($result->fields['total'] > 0)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}messages SET notified='Y' WHERE recp_id='".$playerinfo['player_id']."'");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}
	else
	{
		$template_object->assign("instantmessagecount", 0);
	}

	$template_object->assign("player_online_timelimit", $player_online_timelimit);
	$template_object->assign("player_onlinetime_left", isset($player_onlinetime_left) ? $player_onlinetime_left : 0);
	$template_object->assign("l_footer_onlinecountdown", $l_footer_onlinecountdown);

	$template_object->assign("seconds_until_update", $mySEC);
	$template_object->assign("footer_players_online", $players_online);
	$template_object->assign("footer_players_open", $players_open);
	$template_object->assign("footer_until_update", $l_footer_until_update);
	$template_object->assign("footer_type", $footer_type);
	$template_object->assign("scheduler_ticks", $sched_ticks);
	$template_object->assign("l_footer_news", $l_footer_news);
	$template_object->assign("l_footer_title", $l_footer_title);
	$template_object->assign("l_here", $l_here);
	$template_object->assign("l_footer_help", $l_footer_help);
	$template_object->assign("l_footer_click", $l_footer_click);
	$template_object->assign("index_page", $index_page);
	$lines = @file ("config/banner_bottom.inc");
	$banner_bottom = "";
	for($i=0; $i<count($lines); $i++)
		$banner_bottom .= $lines[$i];

	$template_object->assign("banner_bottom", $banner_bottom);

	$onlinehours_reset = 23 - intval(date("G"));
	$onlineminutes_reset = 60 - intval(date("i"));
	$onlineseconds_reset = 60 - intval(date("s"));
	$onlinetime_reset = sprintf("%02d:%02d:%02d", $onlinehours_reset, $onlineminutes_reset, $onlineseconds_reset);
	$template_object->assign("onlinetime_reset", $onlinetime_reset);
	$template_object->assign("player_online_timelimit", $player_online_timelimit);
	$template_object->assign("l_footer_onlinereset", $l_footer_onlinereset);

	$template_object->assign("query_count", $db->query_count);
	$template_object->assign("time_total", sprintf("%01.4f", $db->query_time_total));

	$template_object->assign("query_debug", $db->debug_console);
	$template_object->assign("query_list", $db->query_list);
	$template_object->assign("query_list_time", $db->query_list_time);
	$template_object->assign("query_list_errors", $db->query_list_errors);

	$template_object->send_now = 1;
	$template_object->display($templatename."footer.tpl");
}

unset($_SESSION['currentprogram'], $currentprogram);
unset ($template_object);

$stuffing = "file:/this/is/the/time_5-23.tpl";
$stuffing_data = explode(":", $stuffing);
preg_match_all('/(?:([0-9a-z._-]+))/i', $stuffing, $stuff);
//print_r($stuff);
//echo "<br>Path: " . str_replace($stuff[0][count($stuff[0]) - 1], "", $stuffing);
//echo "<br>Filename: " . $stuff[0][count($stuff[0]) - 1];
//echo "<br>";


close_database();

flush();
if($enable_pseudo_cron == 1)
{
	include ("backends/pseudo-cron/pseudo-cron.inc.php");
}

die();
exit; // To prevent pop-up windows ;)
?>
