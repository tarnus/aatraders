<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: global_funcs.php

if (preg_match("/global_funcs.php/i", $_SERVER['PHP_SELF'])) 
{
	echo "You can not access this file directly!";
	die();
}

if ((!isset($_SESSION['langdir'])) || ($_SESSION['langdir'] == ''))
{
	$_SESSION['langdir'] = $default_lang;
}

$langdir = $_SESSION['langdir'];

include ("languages/$langdir/lang_common.inc");

if (!preg_match("/create_game.php/i", $_SERVER['PHP_SELF']))
{
	$shiptypes = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_types", '', 'type_id');
}

function checklogin()
{
	$flag = 0;

	global $db, $db_prefix, $playerinfo, $shipinfo, $sectorinfo, $shipdevice, $shipcommodities; 
	global $enable_spies, $response, $player_onlinetime_left;
	global $l_global_needlogin, $l_global_died, $l_login_died, $l_die_please;
	global $start_fighters, $start_armor, $start_energy, $noreturn, $silent, $create_game, $refreshcount, $refresh_max, $idle_max;
	global $server_closed, $player_online_timelimit, $l_global_limitreached;
	global $l_login_closed_message, $onlinetime_left, $tournament_setup_access, $enable_mass_logging;
//echo print_r($_SESSION) . "<br>";
	if ($_SESSION['session_player_id'] == '' || empty($_SESSION['session_player_id']))
	{
		if($noreturn != 1)
			echo $l_global_needlogin;
		return 1;
	}

	$temp = $silent;
	$silent = 1;

	$debug_query = $db->SelectLimit("SELECT {$db_prefix}players.*, {$db_prefix}teams.team_name, {$db_prefix}teams.id
								FROM {$db_prefix}players
								LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team = {$db_prefix}teams.id
								WHERE {$db_prefix}players.player_id=$_SESSION[session_player_id]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
//	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$_SESSION[session_player_id]'", 1);
	$playerinfo = $debug_query->fields;
	$_SESSION['character_name'] = $playerinfo['character_name'];
	$_SESSION['team_name'] = $playerinfo['team_name'];
	$_SESSION['team_id'] = $playerinfo['id'];
	$_SESSION['langdir'] = $playerinfo['langdir'];
	$debug_query->close();

	if ($playerinfo['logged_out'] == 'Y')
	{
		if($noreturn != 1)
			echo $l_global_needlogin;
		return 1;
	}

	if($playerinfo['allow_avatar'] == 0)
		$playerinfo['avatar'] = '';

	// Check sessionid against database
	if (session_id() != $playerinfo['sessionid'])
	{
		echo $l_global_needlogin;
		$flag = 1;
	}

	$stamp = date("Y-m-d H:i:s");
	$time_diff = (TIME() - strtotime($playerinfo['last_login']));

	$delay_flag = 0;

	if(empty($_SESSION['artifact']) || !isset($_SESSION['artifact']))
	{
		$_SESSION['artifact'] = 0;
	}

	if(((TIME() - $_SESSION['artifact']) / 60) > $idle_max)
	{
		$_SESSION['artifact'] = 0;
	}

	if($time_diff / 60 > $idle_max || $refreshcount >= $refresh_max)
	{
//		echo rawurldecode($_SERVER['PHP_SELF']) . "</br>";
		$_SESSION['artifact'] = 0;
		if (stristr($_SERVER['PHP_SELF'], "team_forum.php") || 
		stristr($_SERVER['PHP_SELF'], "casino.php") || 
		stristr($_SERVER['PHP_SELF'], "message_send.php") || 
		stristr($_SERVER['PHP_SELF'], "feedback.php") || 
		stristr($_SERVER['PHP_SELF'], "sector_notes.php"))
		{
			$flag = 1;
			$delay_flag = 1;
		}
		else
		{
			$stamp = date("Y-m-d H:i:s", (TIME() - 360));
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', logged_out='Y', profile_cached='Y', player_total_online=player_total_online+$time_diff, player_online_time=player_online_time+$time_diff, sessionid='' WHERE player_id = $playerinfo[player_id]");

			session_destroy();
			if($noreturn != 1)
			{
				echo $l_global_needlogin;
			}
			return 1;
		}
	}

	$onlinetime_left = ($player_online_timelimit == 0) ? 0 : $player_online_timelimit - floor(($playerinfo['player_online_time'] + $time_diff) / 60);

	$player_onlinetime_left = ($player_online_timelimit * 60) - ($playerinfo['player_online_time'] + $time_diff);

	if($player_online_timelimit != 0 && $onlinetime_left < 0)
	{
		$tournament_setup_access = 1;
	}

	if($tournament_setup_access == 1)
	{
		$time_diff = 0;
	}

	$silent = $temp;

	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id=$playerinfo[player_id] AND ship_id=$playerinfo[currentship]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$shipinfo = $debug_query->fields;
	$debug_query->close();

	$shipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$playerinfo[currentship]", '', 'class');
	$shipcommodities = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_holds WHERE ship_id=$playerinfo[currentship]", '', 'cargo_name');

	$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$shipinfo[sector_id]'", 1);
	db_op_result($result2,__LINE__,__FILE__);
	$sectorinfo = $result2->fields;
	$result2->close();

	if ($shipinfo['cleared_defenses'] > ' ')
	{
		header("location: $shipinfo[cleared_defenses]\n");
	}

	if ($playerinfo['destroyed'] == "Y") // Check for destroyed ship
	{
		if ($shipdevice['dev_escapepod']['amount'] == 1)  // If the player has an escapepod, set the player up with a new ship.
		{
			include ("globals/player_ship_destroyed.inc");
			player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], 0, 0);

			echo $l_login_died;
			$flag = 1;
		}
		else
		{
			if(basename($_SESSION['currentprogram']) != 'login_process.pgp' && basename($_SESSION['currentprogram']) != 'log.php')
			{
				echo $l_global_died . "<br>";
				echo $l_die_please . "<br>";
				echo $l_global_needlogin . "<br>";
				$flag = 1;
			}
		}
	}

	if ($playerinfo['destroyed'] == "K") // Check for destroyed ship
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET destroyed='N' WHERE player_id=" . $playerinfo['player_id']);
		db_op_result($debug_query,__LINE__,__FILE__);
	}

	if ($server_closed && $flag == 0 && $playerinfo['admin'] == 0)
	{
		echo $l_login_closed_message;
		$flag = 1;
	}

	if($flag != 1)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', player_total_online=player_total_online+$time_diff, player_online_time=player_online_time+$time_diff WHERE player_id = $playerinfo[player_id]");
	}

	if($playerinfo['admin_extended_logging'] == 1 || $enable_mass_logging == 1)
	{
		if (!empty($_GET)) {
			$get_data = print_r($_GET, true);
		} else if (!empty($HTTP_GET_VARS)) {
			$get_data = print_r($HTTP_GET_VARS, true);
		}

		if (!empty($_POST)) {
			$post_data = print_r($_POST, true);
		} else if (!empty($HTTP_POST_VARS)) {
			$post_data = print_r($HTTP_POST_VARS, true);
		}

		$query = "INSERT INTO {$db_prefix}admin_extended_logging (player_id, time,  request_uri, get_data, post_data, score, ip_address, currentship, credits, turns, player_online_time) 
		VALUES ($playerinfo[player_id], '$stamp', " . $db->qstr($_SERVER['REQUEST_URI']) . ", " . $db->qstr($get_data) . ", " . $db->qstr($post_data) . ", $playerinfo[score], '$playerinfo[ip_address]', $playerinfo[currentship], $playerinfo[credits], $playerinfo[turns], $player_onlinetime_left)"; 
		$debug_query = $db->Execute($query);
		db_op_result($debug_query,__LINE__,__FILE__);
	}

	if($delay_flag == 1)
	{
		$flag = 0;
	}

	return $flag;
}

function mypw($one,$two)
{
	return exp($two * log(max($one, 1)));
}

function MaxCreditsPOW($one,$two)
{
	global $max_tech_level;
	$increment = 0;

	$oldvalue = 0;
	$breakpoint = floor($max_tech_level * 0.435);
	if($two > $breakpoint)
	{
		$oldvalue = pow($one,$breakpoint);
		$multiplier = pow($one,$breakpoint) - pow($one,($breakpoint - 1));
		$numberlevels = $two - $breakpoint;
		$newvalue = $numberlevels * ($multiplier + pow($one, ($two - $breakpoint)));

		$breakpoint2 = floor($max_tech_level * 0.62);
		if($two > $breakpoint2)
		{
			$numberlevels = $breakpoint2 - $breakpoint;
			$newvalue = $numberlevels * ($multiplier + pow($one, ($breakpoint2 - $breakpoint)));
			$numberlevels = $breakpoint2 - $breakpoint + 1;
			$newvalue2 = $numberlevels * ($multiplier + pow($one, ($breakpoint2 - $breakpoint)));
			$increment = $newvalue2 - $newvalue;
			$newvalue = ($increment * ($two - $breakpoint)) + (110000 * ($two - $breakpoint2));
			return $newvalue + $oldvalue;
		}
		else
		{
			return $newvalue + $oldvalue;
		}
	}
	else
	{
		return pow($one,$two);
	}
}

function phpChangeDelta($desiredvalue,$currentvalue)
{
	global $upgrade_cost, $upgrade_factor;
	return (mypw($upgrade_factor, $desiredvalue) - mypw($upgrade_factor, $currentvalue)) * $upgrade_cost;
}

function phpChangePlanetDelta($desiredvalue,$currentvalue)
{
	global $upgrade_cost, $planet_upgrade_factor;
	return (mypw($planet_upgrade_factor, $desiredvalue) - mypw($planet_upgrade_factor, $currentvalue)) * $upgrade_cost;
}

function phpChangePlanetSDDelta($desiredvalue,$currentvalue)
{
	global $upgrade_cost, $planet_SD_upgrade_factor;
	return (mypw($planet_SD_upgrade_factor, $desiredvalue) - mypw($planet_SD_upgrade_factor, $currentvalue)) * $upgrade_cost;
}

function phpMaxCreditsDelta($desiredvalue,$currentvalue)
{
	global $upgrade_cost, $planet_upgrade_factor;

	return MaxCreditsPOW($planet_upgrade_factor, $desiredvalue) * $upgrade_cost;
}

function NUMBER($number, $decimals = 0)
{
	global $local_number_dec_point;
	global $local_number_thousands_sep;
	return number_format($number, $decimals, $local_number_dec_point, $local_number_thousands_sep);
}

function NUM_PER_LEVEL($level)
{
	global $level_factor;
	return round(mypw($level_factor, $level) * 10);
}

function NUM_HOLDS($level_hull)
{
	return NUM_PER_LEVEL($level_hull);
}

function NUM_ENERGY($level_power)
{
	global $level_factor;
	return round(mypw($level_factor, $level_power) * 50);
}

function NUM_FIGHTERS($level_fighter)
{
	return NUM_PER_LEVEL($level_fighter);
}

function NUM_TORPEDOES($level_torp_launchers)
{
	return NUM_PER_LEVEL($level_torp_launchers);
}

function NUM_armor($level_armor)
{
	return NUM_PER_LEVEL($level_armor);
}

function NUM_SENSORS($level_sensors)
{
	return NUM_PER_LEVEL($level_sensors);
}

function NUM_BEAMS($level_beams)
{
	return NUM_PER_LEVEL($level_beams);
}

function NUM_SHIELDS($level_shields)
{
	return NUM_PER_LEVEL($level_shields);
}

function SCAN_SUCCESS($level_scan, $level_cloak, $hullsize = 0)
{
	if($hullsize > 0)
	{
		$level_cloak += ( 150 - $hullsize);
	}

	$level_scan = max(0.01, $level_scan);
	$level_cloak = max(0.01, $level_cloak);
	$success = $level_scan / $level_cloak;
	if($success > 1)
	{
		$success = -$level_cloak / $level_scan;
		$success = 60 + (50 - (abs($success) * 50));
	}
	else if($success == 1)
	{
		$success = 50;
	}
	else
	{
		$success = ($success * 50) - 10;
	}
	$success = min(max($success, 1), 90);
	return floor($success);
}

function SCAN_ERROR($level_scan, $level_cloak, $correct_value)
{
	$level_scan = max(0.01, $level_scan);
	$level_cloak = max(0.01, $level_cloak);
	$success = $level_scan / $level_cloak;
	if($success > 1)
	{
		$success = -$level_cloak / $level_scan;
		$success = 60 + (50 - (abs($success) * 50));
	}
	else if($success == 1)
	{
		$success = 50;
	}
	else
	{
		$success = ($success * 50) - 10;
	}
	$success = min(max($success, 1), 100);

	$sc_error = 100 - floor($success);

	if(mt_rand(1, 100) <= $sc_error)
	{
		// scan errored and returned false info
		$halfpercent = floor($sc_error / 2);
		$sc_error = floor($correct_value * (mt_rand((100000 - ($halfpercent * 1000)), (100000 + ($halfpercent * 1000)))) / 100000);
	}
	else
	{
		// scan worked and returned almost correct info
		// 99% to 101% of the correct value
		$sc_error = floor($correct_value * (mt_rand(99999, 100999) / 100000));
		$sc_error = $correct_value;
	}
	return $sc_error;
}

function get_dirlist($dirPath)
{
	if ($handle = opendir($dirPath)) 
	{
		while (false !== ($file = readdir($handle))) 
			if ($file != "." && $file != "..") 
				$filesArr[] = trim($file);
			closedir($handle);
	}
	return $filesArr; 
}

function update_player_experience($player_id, $experience){
	global $db, $db_prefix;

	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET experience=GREATEST(experience + $experience, 0) WHERE player_id=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	adminlog("LOG0_RAW","UPDATE {$db_prefix}players SET experience=GREATEST(experience + $experience, 0) WHERE player_id=$player_id");
}

// remove all non-numerics but leave decimal point
function stripnum($str)
{
	$str = (string)$str;
	$output = AAT_ereg_replace("[^0-9.]","",$str);
	return (float)$output;
}

//remove all non-numerics
function StripNonNum($str)
{
  $str=(string)$str;
  $output = AAT_ereg_replace("[^0-9]","",$str);
  return $output;
}

function close_database(){
	global $db;

//	$db->close();
}

function sign( $data )
{
	if ($data > 0)
	{
		return 1;
	}
	elseif ($data < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

function db_op_result($query,$served_line,$served_page)
{
	global $db, $db_prefix, $silent, $_SERVER, $cumulative, $db_type;

	if ($db->ErrorNo() == 0)
	{
		if (!$silent)
		{
			echo "<font color=\"lime\">- operation completed successfully.</font><br>\n";
		}
	}
	else
	{
		$temp_error = $db->ErrorMsg();
		$dberror = "A Database error occurred in " . $served_page . " on line " . ($served_line-1) . " (called from: $_SERVER[PHP_SELF]): " . $temp_error . " - Original SQL: " . $db->sql;
		$dberror = AAT_ereg_replace("'","&#039;",$dberror); // Allows the use of apostrophes.
		adminlog("LOG0_ADMIN_DBERROR", $dberror);
		$cumulative = 1; // For areas with multiple actions needing status - 0 is all good so far, 1 is at least one bad.

		if(strstr(AAT_strtolower($temp_error), "can't open file") and strstr(AAT_strtolower($temp_error), ".myi") and strstr($temp_error, "145")){
			$deoperror = 1;
			adminlog("LOG0_ADMIN_DBERROR","Running sched_repair.inc to repair table.");
			include ("scheduler/sched_repair.inc");
		}

		if (!$silent)
		{
			echo "<font color=\"red\">- failed to complete database operation in $served_page on line " .($served_line-1). ". Error code follows:\n";
			echo "<hr>\n";
			echo $temp_error . "<br><br>Original SQL: " . $db->sql;
			echo "<hr>\n";
			echo "</font><br>\n";
		}
	}
}

function template_display($templatename, $templatefile)
{
	global $template_object, $default_template;

	if(is_file($gameroot.$templatename.$templatefile)){
		$template_object->display($templatename.$templatefile);
	}
	else
	{
		$template_object->display($default_template.$templatefile);
	}
}

function playerlog($sid, $log_type, $data = '')
{
	global $db, $db_prefix;

	// write log_entry to the player's log - identified by player's player_id - sid.
	if ($sid != '' && !empty($log_type))
	{
		$stamp = date("Y-m-d H:i:s");
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}logs (player_id, type, time, data) VALUES($sid, '$log_type', '$stamp', " . $db->qstr($data) . ")");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

function adminlog($log_type, $data = '')
{
	global $db, $db_prefix;

	// Failures should be silent, since its the admin log.
	$silent = 1;

	// write log_entry to the admin log
	if (!empty($log_type))
	{
		$stamp = date("Y-m-d H:i:s");
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}admin_log (type, time, data) VALUES('$log_type', '$stamp', " . $db->qstr($data) . ")");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

?>
