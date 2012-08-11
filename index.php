<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: index.php

include ("config/config_local0.php");
if (!$game_installed)
{
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<META HTTP-EQUIV="Refresh" CONTENT="0;URL=installer.php">
		<title>Running Installer</title>
	</head>
	<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor="#000000">
	</body>
</html>
<?php
	die();
}

$_SESSION['game_number'] = 0;
$game_number = $_SESSION['game_number'];
include ("config/config.php");

if (empty($langdir))
{
	$langdir = $default_lang;
}

$no_body = 1;
$title = $game_name . " - " . $release_version;

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}

include ("header.php");
include ("languages/$langdir/lang_login.inc");
include ("languages/$langdir/lang_new.inc");
include ("languages/$langdir/lang_login2.inc");
include ("languages/$langdir/lang_footer.inc");
include ("globals/RecurseDir.inc");

$template_object->assign("templatename", $templatename);

if ((!isset($serverlisturlcheck)) || ($serverlisturlcheck == ''))
{
	$serverlisturlcheck = '';
}else{
	$urlcheck = "url=".rawurlencode($serverlisturlcheck);
}

if ((!isset($serverlistnamecheck)) || ($serverlistnamecheck == ''))
{
	$serverlistnamecheck = '';
}else{
	$namecheck = "name=".rawurlencode($serverlistnamecheck);
}

if($serverlistnamecheck != '' or $serverlisturlcheck != ''){
	$where = "?";
	if($serverlistnamecheck == ''){
		$where .= $urlcheck;
	}else{
		$where .= $namecheck;
		if($serverlisturlcheck != '')
			$where .= "&". $urlcheck;
	}
}else{
	$where = "";
}

if($showserverlist == 1){
	$url = "http://www.aatraders.com/get_server_list.php" . $where;
	$ch=curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
	$var = curl_exec ($ch);
	$server_data = explode("\n", trim($var));
	curl_close ($ch);

	$servercount = 0;
	for($i = 0; $i < count($server_data); $i++){
		$lines = $server_data[$i];
		$servers = explode("|", $lines);
		if($servers[0] != "" and $servers[1] != $_SERVER['HTTP_HOST'] . $gamepath){
			if(strstr($servers[6], "0000-00-00 00:00:00"))
				$reset = $l_login_reset1;
			else $reset = $l_login_reset3 . date($local_date_short_format, strtotime($servers[6]));

			$serverurl[$servercount] = $servers[1];
			$servername[$servercount] = $servers[0];
			$serversectors[$servercount] = $servers[2];
			$serverplayers[$servercount] = $servers[3];
			$servertop[$servercount] = $servers[4] . ": " . NUMBER($servers[5]);
			$serverreset[$servercount] = $reset;
			$servercount++;
		}
	}
}

$template_object->assign("servercount", $servercount);
$template_object->assign("serverurl", $serverurl);
$template_object->assign("servername", $servername);
$template_object->assign("serversectors", $serversectors);
$template_object->assign("serverplayers", $serverplayers);
$template_object->assign("servertop", $servertop);
$template_object->assign("serverreset", $serverreset);
$template_object->assign("showserverlist", $showserverlist);

$newscount = 0;
$res = $db->Execute("SELECT * FROM {$db_prefix}adminnews ORDER BY an_id desc");

if($res->EOF)
{
	$template_object->assign("newscount", 0);
}
else
{
	while (!$res->EOF) 
	{
		$row = $res->fields;
		$newsdata[$newscount] = str_replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;", str_replace("\r", "", str_replace("\n", "", $row[an_text])));
		$newscount++;
		$res->MoveNext();
	}
	$template_object->assign("newscount", $newscount);
	$template_object->assign("newsdata", $newsdata);
	$template_object->assign("l_login_notice", $l_login_notice);
}

function index_connectdb($db_type, $dbhost, $dbuname, $dbpass, $dbname, $db_persistent, $dbport, $totalgames)
{
	$ADODB_COUNTRECS = false;
	$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;
	if (!empty($dbport))
	{
		$dbhost.= ":$dbport";
	}

	$index_db = ADONewConnection("$db_type");

	$result = $index_db->NConnect("$dbhost", "$dbuname", "$dbpass", "$dbname");

	if (!$result)
	{
		die ("Unable to connect to the game $totalgames database, check the config_local" . $totalgames . ".php located in the config directory or use the intaller.php to correct the error.");
	}

	return $index_db;
}

unset ($server_closed);
unset ($account_creation_closed);
unset ($tournament_setup_access);
unset ($profile_only_server);
unset ($tournament_start_date);

$totalgames = 0;
$filelist = get_dirlist($gameroot."config/");
$total_closed = 0;
$total_signupclosed = 0;
sort($filelist);
for ($c=0; $c<count($filelist); $c++) { 
	if(strstr($filelist[$c], "config_local")){
		$gamenumber[$totalgames] =  str_replace("config_local", "", str_replace(".php", "", $filelist[$c])); 

		$lines = file ("support/variables" . $gamenumber[$totalgames] . ".inc");
		for($i = 0; $i < count($lines); $i++){
			$variable = explode("=", trim($lines[$i]));
			$variable[0] = str_replace("$", "", trim($variable[0]));
			$variable[1] = str_replace(";", "", str_replace("\"", "", trim($variable[1])));
			if($variable[0] == "scheduled_reset")
			{
				if(strstr($variable[1], "0000-00-00"))
				{
					$scheduled_reset_set[$totalgames] = 0;
					$scheduled_resetdate[$totalgames] = $l_login_reset1;
				}
				else
				{
					$scheduled_reset_set[$totalgames] = 1;
					$scheduled_resetdate[$totalgames] = date($local_date_short_format, strtotime($variable[1]));
				}
			}
			if($variable[0] == "server_closed")
			{
				$server_closed[$totalgames] = $variable[1];
				$total_closed += $variable[1];
			}
			if($variable[0] == "account_creation_closed")
			{
				$account_creation_closed[$totalgames] = $variable[1];
				$total_signupclosed += $variable[1];
			}
			if($variable[0] == "tournament_setup_access")
			{
				$tournament_setup_access[$totalgames] = $variable[1];
			}
			if($variable[0] == "profile_only_server")
			{
				$profile_only_server[$totalgames] = $variable[1];
			}
			if($variable[0] == "tournament_start_date")
			{
				if(strstr($variable[1], "0000-00-00"))
					$tournament_start_date[$totalgames] = "";
				else $tournament_start_date[$totalgames] = date($local_date_short_format, strtotime($variable[1]));
			}
			if($variable[0] == "tournament_mode")
			{
				$tournament_mode[$totalgames] = $variable[1];
			}
			if($variable[0] == "player_limit")
			{
				$index_player_limit[$totalgames] = $variable[1];
			}
		}

		$config_lines = file ($gameroot."config/".$filelist[$c]);

		$found_element = 0;
		for($i = 0; $i < count($config_lines) - 1; $i++){
			$config_data = explode("=", trim($config_lines[$i]));
			$config_element = str_replace("$", "", trim($config_data[0]));
			if($found_element == 1 or $config_element == 'game_name')
			{
				$config_array[$config_element] = str_replace(";", "", str_replace("\"", "", trim($config_data[1])));
				$found_element = 1;
			}
		}

		if($totalgames == 0)
		{
			$index_db = $db;
		}
		else
		{
			$index_db = index_connectdb($config_array['db_type'], $config_array['dbhost'], $config_array['dbuname'], $config_array['dbpass'], $config_array['dbname'], $config_array['db_persistent'], $config_array['dbport'], $totalgames);
		}
		$gamename[$totalgames] = $config_array['game_name'];

		$unixstamp = time();

		if($player_online_timelimit > 0 && isset($playerinfo['player_online_time']))
		{
			$overlimitwhere = " and floor($playerinfo[player_online_time] / 60) <= $player_online_timelimit";
		}
		else
		{
			$overlimitwhere = "";
		}
		$debug_query = $index_db->Execute("SELECT COUNT(player_id) AS total from " . $config_array['db_prefix'] . "players WHERE TIMESTAMPDIFF(MINUTE,last_login,'". date("Y-m-d H:i:s") . "') < 5 and email NOT LIKE '%@npc' $overlimitwhere");
		$index_online = $debug_query->fields['total'];

		// Time left til next update
		$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;
		$debug_query = $index_db->SelectLimit("SELECT last_run FROM " . $config_array['db_prefix'] . "scheduler WHERE sched_file='sched_turns.inc'", 1);
		$last_run = $debug_query->fields['last_run'];

		$index_scheduler_ticks[$totalgames] = $config_array['sched_ticks'];
		$index_seconds_until_update[$totalgames] = ($config_array['sched_ticks'] * 60) - ($unixstamp-strtotime($last_run));
		if ($index_seconds_until_update[$totalgames] <= 0)
		{
			$index_seconds_until_update[$totalgames] = 1;
		}

		if ($index_online == 0)
		{
			$index_players_online[$totalgames] = $l_footer_no_players_on;
		}
		else
		{
			$index_players_online[$totalgames] = $l_footer_players_on_2 . $index_online;
		}

		if($index_player_limit[$totalgames] > 0)
		{
			$index_players_open[$totalgames] = $l_footer_open_slots . $index_player_limit[$totalgames];
		}

		$db->query_list += $index_db->query_list;
		$db->query_list_time += $index_db->query_list_time;

		$index_db->close();
		unset ($index_db);

		$totalgames++;
	}
}

$template_object->assign("index_seconds_until_update", $index_seconds_until_update);
$template_object->assign("index_players_online", $index_players_online);
$template_object->assign("index_footer_until_update", $l_footer_until_update);
$template_object->assign("index_players_open", $index_players_open);
$template_object->assign("index_scheduler_ticks", $index_scheduler_ticks);

$template_object->assign("player_limit", $player_limit);
$template_object->assign("total_closed", $total_closed);
$template_object->assign("total_signupclosed", $total_signupclosed);
$template_object->assign("tournament_mode", $tournament_mode);
$template_object->assign("server_closed", $server_closed);
$template_object->assign("account_creation_closed", $account_creation_closed);
$template_object->assign("tournament_setup_access", $tournament_setup_access);
$template_object->assign("profile_only_server", $profile_only_server);
$template_object->assign("tournament_start_date", $tournament_start_date);
$template_object->assign("scheduled_reset_set", $scheduled_reset_set);
$template_object->assign("scheduled_resetdate", $scheduled_resetdate);
$scheduled_resetdatezone = date("O");
$template_object->assign("scheduled_resetdatezone", $scheduled_resetdatezone);
$template_object->assign("l_login_reset2", $l_login_reset2);
$template_object->assign("gamenumber", $gamenumber);
$template_object->assign("gamename", $gamename);
$template_object->assign("totalgames", $totalgames);
$template_object->assign("l_login_profile_only", $l_login_profile_only);
$template_object->assign("l_login_newclosed_message", $l_login_newclosed_message);
$template_object->assign("l_login_tourneymode", $l_login_tourneymode);
$template_object->assign("l_login_sclosed", $l_login_sclosed);

$template_object->assign("l_login_tourney_signup", $l_login_tourney_signup);
$template_object->assign("l_login_closed_message", $l_login_closed_message);
$template_object->assign("scheduled_reset", $reset);
$template_object->assign("version", $release_version);
$template_object->assign("main_site", $main_site);
$template_object->assign("login_drop_down",$login_drop_down);
$template_object->assign("l_new_pname", $l_new_pname);
$template_object->assign("l_login_pw", $l_login_pw);
$template_object->assign("character_name", $character_name);
$template_object->assign("password", $password);
$template_object->assign("l_login_forgot_pw", $l_login_forgot_pw);
$template_object->assign("l_login_chooseres", $l_login_chooseres);
$template_object->assign("l_login_emailus", $l_login_emailus);
$template_object->assign("admin_mail", $admin_mail);
$template_object->assign("l_login_prbs", $l_login_prbs);
$template_object->assign("l_login_newp", $l_login_newp);
$template_object->assign("l_login_title", $l_login_title);
$template_object->assign("link_forums", $link_forums);
$template_object->assign("l_forums", $l_forums);
$template_object->assign("l_rankings", $l_rankings);
$template_object->assign("l_login_settings", $l_login_settings);
$template_object->assign("avail_lang", $avail_lang);
$template_object->assign("login_language_change", $l_login_change);
$template_object->assign("maxlen_password", $maxlen_password);
$template_object->assign("serverlist", $aatrade_server_list_url);
$template_object->assign("l_footer_news", $l_footer_news);

$template_object->display($default_template."index.tpl");
//$template_object->display("file:/aatrade/aatrade/templates/default_paged/index.tpl");

$index_page = 1;
include ("footer.php");

?>
