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

function scheduler_log($data, $lf){
	global $enable_schedule_log;
	if($enable_schedule_log){
		$stamp = date("Y-m-d H:i:s");
		$filename = $gameroot . "config/scheduler.log";
		$file = fopen($filename,"a") or die ("Failed opening file: enable write permissions for '$filename'");
		fwrite($file,$data . " = " . $stamp . "\n" . $lf); 
		fclose($file);
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

class c_Timer
{
	var $t_start = 0;
	var $t_stop = 0;
	var $t_elapsed = 0;

	function start()
	{
		$this->t_start = microtime();
	}

	function stop()
	{
		$this->t_stop	= microtime();
	}

	function elapsed()
	{
		$start_u = AAT_substr($this->t_start,0,10); $start_s = AAT_substr($this->t_start,11,10);
		$stop_u	= AAT_substr($this->t_stop,0,10);	$stop_s	= AAT_substr($this->t_stop,11,10);
		$start_total = doubleval($start_u) + $start_s;
		$stop_total	= doubleval($stop_u) + $stop_s;
		$this->t_elapsed = $stop_total - $start_total;
		return (float)$this->t_elapsed;
	}
}

function TextFlush($Text="") 
{
	global $adminexecuted;
	if($adminexecuted == 1){
		echo "$Text";
		flush();
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

function mypw($one,$two)
{
	return exp($two * log(max($one, 1)));
}

function MaxCreditsPOW($one,$two)
{
	global $max_tech_level;
	$increment = 0;

	$oldvalue = 0;
	$breakpoint = floor($max_tech_level * 0.38);
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
		$sc_error = floor($correct_value * (mt_rand((1000000 - ($halfpercent * 10000)), (1000000 + ($halfpercent * 10000)))) / 1000000);
	}
	else
	{
		// scan worked and returned almost correct info
		// 99% to 101% of the correct value
		$sc_error = floor($correct_value * (mt_rand(99999999, 100999999) / 100000000));
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

function NUM_PER_LEVEL($level)
{
	global $level_factor;
	return round(mypw($level_factor, $level) * 10);
}

function NUM_ENERGY($level_power)
{
	global $level_factor;
	return round(mypw($level_factor, $level_power) * 50);
}

function NUM_HOLDS($level_hull)
{
	return NUM_PER_LEVEL($level_hull);
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

function update_player_experience($player_id, $experience){
	global $db, $db_prefix;

	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET experience=GREATEST(experience + $experience, 0) WHERE player_id=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
}

function stripnum($str)
{
	$str = (string)$str;
	$output = AAT_ereg_replace("[^0-9.]","",$str);
	return (float)$output;
}

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

?>
