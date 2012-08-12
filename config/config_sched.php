<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the     
// Free Software Foundation; either version 2 of the License, or (at your    
// option) any later version.                                                
// 
// File: config.php

if (preg_match("/config_sched.php/i", $_SERVER['PHP_SELF']))
{
  echo "You can not access this file directly!";
  die();
}

error_reporting (E_ALL ^ E_NOTICE);

include ("globals/AAT_mbstring.inc");

if (get_magic_quotes_gpc())
{
	function strip_gpc_slashes(&$array)
	{
		if (!is_array ($array))
			return;
		foreach($array as $key => $val)
			is_array( $array[$key] ) ? strip_gpc_slashes($array[$key]) : ($array[$key] = stripslashes ($array[$key]));
	}
	$gpc = array(&$_GET, &$_POST);
	strip_gpc_slashes($gpc);
}

function decoder($data, $key = "aatrade") {
	$result = '';
	$data =  @pack("H" . AAT_strlen($data), $data); 

	for($i=0; $i < AAT_strlen($data); $i++) {
		$char = AAT_substr($data, $i, 1);
		$keychar = AAT_substr($key, ($i % AAT_strlen($key))-1, 1);
		$char = chr(ord($char)-ord($keychar));
		$result.=$char;
	}
	return $result;
}

function get_post_ifset($test_vars)
{
	if (!is_array($test_vars))
	{
		$test_vars=explode(",",$test_vars);
	}
	foreach($test_vars as $test_var)
	{
		$test_var = trim($test_var);
		if (isset($_POST[$test_var]))
		{
			global $$test_var;
			$$test_var = $_POST[$test_var];
		} else if (isset($_GET[$test_var]))
		{
			global $$test_var;
			$$test_var = $_GET[$test_var];
		}
	}
}

get_post_ifset("admin_password, adminexecuted, game_number, encoded");

$scheduler_passes = 1;

if(!empty($encoded) && $encoded != '')
{
	$variablestring = decoder($encoded);
	$variablelist = explode("&", $variablestring);
	if($variablelist[0] == "AADATA")
	{
		for($i = 1; $i < count($variablelist); $i++)
		{
			$variable = explode("=", $variablelist[$i]);
			$variable[0] = trim($variable[0]);
			$variable[1] = trim($variable[1]);

			if($variable[0]){
				$$variable[0] = $variable[1];
			}
		}
		if($enable_pseudo_cron == 1 && @ini_get("allow_url_fopen") == 1)
		{
			get_post_ifset("scheduler_passes");
		}
	}
}

if ((!isset($admin_password)) || ($admin_password == ''))
{
	$admin_password = '';
}

if ((!isset($game_number)) || ($game_number == ''))
{
	$game_number = 0;
}

// Include the DB config file:
include ("config/config_local" . $game_number . ".php");

// Include adodb:
include ("backends/adodb_lite/adodb.inc.php");

$ADODB_COUNTRECS = false;
$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;
if (!empty($dbport))
{
	$dbhost.= ":$dbport";
}

$db = ADONewConnection("$db_type", "adodblite");
$db->debug=0;
$result = $db->Connect("$dbhost", "$dbuname", "$dbpass", "$dbname");

if (!$result)
{
	die ("Unable to connect to the database");
}

$version = @mysql_get_server_info();
$versioncheck = AAT_ereg_replace("[^0-9.]","", $version);
if (strnatcmp($versioncheck, '5.0.2') >= 0)
{
	$debug_query = $db->Execute("SET sql_mode = ''");
}

$mbstring_supported = 0;

if (@extension_loaded('mbstring'))
{
	if (strnatcmp($versioncheck, '4.2.3') != 1)
	{
		$mbstring_supported = 1;
		mb_internal_encoding("UTF-8");
	}
}

global $db, $db_prefix, $mbstring_supported;

// Get the config_values from the DB - silently.
$silent = 1;

$release_version = "0.41"; // *DO NOT EDIT* This is the actual release version *DO NOT EDIT*   
$aatrade_server_list_url = "http://www.aatraders.com/"; // *DO NOT EDIT*
global $db, $release_version;
global $gameurl, $gamepath, $dbprefix;

include("support/variables" . $game_number . ".inc");

include ("global_sched_funcs.php");

?>
