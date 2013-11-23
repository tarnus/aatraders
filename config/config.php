
<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the     
// Free Software Foundation; either version 2 of the License, or (at your    
// option) any later version.                                                
// 
// File: config.php

if (preg_match("/config.php/i", $_SERVER['PHP_SELF']))
{
  echo "You can not access this file directly!";
  die();
}

ini_set ("session.use_trans_sid","0"); // Otherwise, on re-login, it will append a session id on the url - blech.
include ("globals/global_declare.inc");
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
	$gpc = array(&$_GET, &$_POST, &$_COOKIE, &$_FILES);
	strip_gpc_slashes($gpc);
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

get_post_ifset("create_game, game_number");

error_reporting (E_ALL ^ (E_NOTICE | E_WARNING));

include ("config/config_master.php");

include ("backends/adodb_lite/adodb.inc.php");

// Include adodb:
if($use_session_database == 1)
{
	include ("backends/adodb_lite/session/adodb-session.php");
}

// If a player id hasnt been set in the session, and its not create_game, then start a session.
if ((!isset($_SESSION['session_player_id'])) && $create_game != 1)
{
	session_start();
}

if (isset($game_number)) 
{ 
	$_SESSION['game_number'] = $game_number; 
}

if ((!isset($_SESSION['game_number'])) || ($_SESSION['game_number'] == ''))
{
	$_SESSION['game_number'] = 0;
}

$game_number = $_SESSION['game_number'];

// Include the DB config file:
include ("config/config_local" . $_SESSION['game_number'] . ".php");

// Define the template directory:
//define ('TEMPLATE_DIR',"$gameroot" . "backends/Smarty2/libs/");
define ('TEMPLATE_LITE_DIR',"$gameroot" . "backends/template_lite/src/");

// Define the template class location:
//define('TEMPLATE_CLASS', TEMPLATE_DIR . "Smarty.class.php");   
define('TEMPLATE_CLASS', TEMPLATE_LITE_DIR . "class.template.php");   

define ("OrdKey","j0w06ej3gw29jn3h1"); 

$ip = getenv("REMOTE_ADDR");
$mbstring_supported = 0;

function connectdb()
{
	// connect to database - and if we can't stop right there
	global $dbhost, $dbport, $dbuname, $dbpass;
	global $db, $dbname, $db_type, $db_persistent, $ADODB_vers;
	global $default_lang, $gameroot, $ADODB_FETCH_MODE, $ADODB_COUNTRECS, $mbstring_supported;

	$ADODB_COUNTRECS = false;
	$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;
	if (!empty($dbport))
	{
		$dbhost.= ":$dbport";
	}

	$db = ADONewConnection("$db_type", "adodblite");
	$result = $db->Connect("$dbhost", "$dbuname", "$dbpass", "$dbname");

	if (!$result)
	{
		die ("Unable to connect to the database");
	}

	$version = @mysql_get_server_info();
	$versioncheck=preg_replace("/[^0-9.]/", "",$version); 
	

	if (@extension_loaded('mbstring'))
	{
		if (strnatcmp($versioncheck, '4.2.3') == 1)
		{
			$mbstring_supported = 1;
			mb_internal_encoding("UTF-8");
		}
	}

//	$db->debug_console = true;
//	$db->debug=1;
}

if ((!isset($create_game)) || ($create_game == ''))
{
	$create_game = 0;
}

//echo $_SESSION['lag_delay_time'];
if ($_SESSION['currentprogram'] == $_SERVER['PHP_SELF'] && ($_SESSION['lag_delay_time'] >= time() || $_SESSION['lag_delay_time'] == 0))
{
	echo"<script language=\"javascript\" type=\"text/javascript\">{ alert('Please wait for the page to load!'); }</script>";
	echo "<table border=0 cellspacing=0 cellpadding=2 width=\"100%\" align=center>
		<tr><td align=center><br><br><b>You are using a lag cheat or you are in too much of a hurry.  Wait for the page to load.<b><br><br></td></tr></table>";
	echo"<script language=\"javascript\" type=\"text/javascript\">
			var mysleep = 15;
			setTimeout(\"countdown();\",1000);
			function countdown()
			{
				mysleep = mysleep - 1;
				if (mysleep <= 0)
				{
					mysleep = 0;
					document.getElementById(\"showlink\").innerHTML = \"Click <A HREF=main.php>here</A> to return to the main menu.\";
				}
				document.getElementById(\"sleeptimer\").innerHTML = mysleep;
				setTimeout(\"countdown();\",1000);
			}
			</script>
			<table width=\"100%\" border=0 cellspacing=0 cellpadding=0><tr><td align=center class=\"footer\"><b>Wait <span id=sleeptimer class=\"footer\">15</span> seconds</b></td></tr></table>";
	echo "<table border=0 cellspacing=0 cellpadding=2 width=\"100%\" align=center><tr><td><br><br><span id=showlink class=\"footer\">&nbsp;</span><br><br></td></tr>
		</table>";
  	flush();
	$_SESSION['lag_delay_time'] = time() + 15;
	unset ($template_object);
	die();
}

$_SESSION['lag_delay_time'] = 0;
$_SESSION['currentprogram'] = $_SERVER['PHP_SELF'];

$_SESSION['refreshprogram'] = $_SESSION['loadprogram'];
$_SESSION['refreshuri'] = $_SESSION['loaduri'];
$_SESSION['loadprogram'] = $_SERVER['PHP_SELF'];
$_SESSION['loaduri'] = $_SERVER['REQUEST_URI'];

if($_SESSION['refreshprogram'] == $_SESSION['loadprogram'] && $_SESSION['refreshuri'] == $_SESSION['loaduri'])
{
	$_SESSION['refreshcount']++;
}
else
{
	$_SESSION['refreshcount'] = 0;
}

$refreshcount = $_SESSION['refreshcount'];

$release_version = "0.41"; // *DO NOT EDIT* This is the actual release version *DO NOT EDIT*   
$aatrade_server_list_url = "http://www.aatraders.com/"; // *DO NOT EDIT*
$_SESSION['game_name'] = $game_name;

if ($create_game != 1)
{
    // Get the config_values from the DB - silently.
    $silent = 1;
    connectdb();
	include("support/variables" . $game_number . ".inc");
}

require_once (TEMPLATE_CLASS);
$template_object = new Template_Lite;
//$template_object = new Smarty;
$template_object->template_dir = "./templates/";
$template_object->compile_dir = "./templates_c/";
$template_object->encode_file_name = $encode_file_name;
$template_object->enable_gzip = $enable_gzip;
$template_object->compression_level = $compression_level;
$template_object->force_compression = $force_compession;
$template_object->php_extract_vars = true;
//$template_object->debugging = true;

if($template_object->enable_gzip)
	$template_object->load_filter('output','gzip');

include ("global_funcs.php");

?>
