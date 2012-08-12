<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: login_process.php

include ("config/config.php");
include ("languages/$langdir/lang_login2.inc");
include ("globals/AddELog.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/ord_crypt_encode.inc");
$template_object->enable_gzip = 0;

function ip_log($player_id,$ip_address)
{
	global $db, $db_prefix,$enhanced_logging;
	if ($enhanced_logging)
	{
		$stamp = date("Y-m-d H:i:s"); 
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_log (player_id,ip_address,time) VALUES ($player_id,'$ip_address','$stamp')");
		db_op_result($debug_query,__LINE__,__FILE__); 
	}
}

if ((!isset($_POST['character_name'])) || ($_POST['character_name'] == ''))
{
	$_POST['character_name'] = '';
}

// Cleans character name before we run the select below. Otherwise, someone can use
// semi-colons in the char name at login and sql inject.
// Allows A-Z, a-z, 0-9, whitespace, minus/dash, equals, backslash, explanation point, ampersand, asterix, and underscore.

$_POST['character_name'] = preg_replace ("/[^A-Za-z0-9\s\-\=\\\'\!\&\*\_]/","",$_POST['character_name']);

if ((!isset($_POST['pass'])) || ($_POST['pass'] == ''))
{
	$_POST['pass'] = '';
}

$_POST['pass'] = ord_crypt_encode($_POST['pass']);

// If the server is closed tell the tards to leave and read the login screen next time.

$playerfound = 0;

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE character_name=" . $db->qstr($_POST['character_name']) . " and password='$_POST[pass]'", 1);
db_op_result($debug_query,__LINE__,__FILE__);

if ($debug_query)
{
	$playerfound = $debug_query->RecordCount();
	$playerinfo = $debug_query->fields;
}

if($playerinfo['player_id'] > 3 && $playerinfo['npc'] != 0){
	$playerfound = 0;
}

if ($server_closed && $playerinfo['admin'] == 0)
{
	$title = $l_login_sclosed;
	// Skinning stuff
	if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
		$templatename = $default_template;
	}else{
		$templatename = $playerinfo['template'];
	}
	include ("header.php");

	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);

	$template_object->assign("error_msg", $l_login_closed_message);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mlogin);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

// If there is a player limit on the server check to see if the max players has been reached and prevent them from logging in.

if($player_limit > 0 && $playerfound != 0)
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
    $debug_query = $db->Execute("SELECT COUNT(player_id) AS total from {$db_prefix}players WHERE TIMESTAMPDIFF(MINUTE,last_login,'". date("Y-m-d H:i:s") . "') < 5 and email NOT LIKE '%@npc' and player_id > 3 $overlimitwhere");
    db_op_result($debug_query,__LINE__,__FILE__);
	$online = $debug_query->fields['total'];

	if($online >= $player_limit && $playerinfo['player_id'] > 3)
	{
		$title = $l_login_title2;
		// Skinning stuff
		if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
			$templatename = $default_template;
		}else{
			$templatename = $playerinfo['template'];
		}
		include ("header.php");

		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);

		$template_object->assign("error_msg", "<font size=3 color=yellow>$l_login_playerlimit</font>");
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mlogin);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}
}

if ($playerfound)
{
	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id=$playerinfo[player_id] AND " .
								"ship_id=$playerinfo[currentship]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$shipinfo = $debug_query->fields;

	if($playerinfo['team'] != 0){
		$debug_query = $db->SelectLimit("select * from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$time = date("Y-m-d H:i:s");
		$debug_query = $db->Execute("update {$db_prefix}team_forum_players set lastonline='$forumplayer[currenttime]', currenttime='$time' where player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
	}

	$debug_query = $db->Execute("SELECT COUNT(ban_id) AS total FROM {$db_prefix}ip_bans WHERE '$ip' LIKE ban_mask OR '$playerinfo[ip_address]' LIKE ban_mask or email='$playerinfo[email]'");
	db_op_result($debug_query,__LINE__,__FILE__);

	if ($debug_query->fields['total'] != 0)
	{
		$banned = 1;
		$title = $l_login_title2;
		// Skinning stuff
		if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
			$templatename = $default_template;
		}else{
			$templatename = $playerinfo['template'];
		}
		include ("header.php");

		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);

		$template_object->assign("error_msg", "<font size=3 color=red>$l_login_banned</font>");
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mlogin);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}

//	$userpass = $playerinfo['email']."+".$_POST['pass'];
//	$_SESSION['session_userpass'] = $userpass;
	$_SESSION['session_player_id'] = $playerinfo['player_id'];

	if ($playerinfo['destroyed'] == "N")
	{
		// player's ship has not been destroyed
		playerlog($playerinfo['player_id'], "LOG_LOGIN", $ip);
		ip_log($playerinfo['player_id'],$ip);
		$stamp = date("Y-m-d H:i:s");
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET profile_cached='N', logged_out='N', forum_login='$playerinfo[last_login]', last_login='$stamp', ip_address='$ip', sessionid='" . session_id() . "' WHERE " .
									"player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		close_database();
		$_SESSION['lobby_mode'] = 1;
		if ($playerinfo['turns_used'] == 0)
		{
			echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
					<html>
						<head>
								<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=options.php\">
							<title>Loading Options</title>
						</head>
						<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
						</body>
					</html>";
			die();
		}
		else
		{
			echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
					<html>
						<head>
							<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">
							<title>Loading Main</title>
						</head>
						<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
						</body>
					</html>";
			die();
		}
	}
	else
	{
		// player's ship has been destroyed
		if ($playerinfo['destroyed'] == "Y")
		{
			if ($newbie_nice == "YES")
			{
				$debug_query = $db->Execute("SELECT hull,engines,power,fighter,sensors,armor,shields,beams,torp_launchers,cloak FROM {$db_prefix}ships WHERE player_id='$playerinfo[player_id]' AND ship_id=$playerinfo[currentship] AND hull<='$newbie_hull' AND engines<='$newbie_engines' AND power<='$newbie_power' AND fighter<='$newbie_fighter' AND sensors<='$newbie_sensors' AND armor<='$newbie_armor' AND shields<='$newbie_shields' AND beams<='$newbie_beams' AND torp_launchers<='$newbie_torp_launchers' AND cloak<='$newbie_cloak'");
				db_op_result($debug_query,__LINE__,__FILE__);
				$num_rows = $debug_query->RecordCount();

				if ($num_rows and $playerinfo['turns_used'] < $start_turns)
				{
					$title = $l_login_title2;
					// Skinning stuff
					if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
						$templatename = $default_template;
					}else{
						$templatename = $playerinfo['template'];
					}
					include ("header.php");

					$template_object->assign("title", $title);
					$template_object->assign("templatename", $templatename);
					player_ship_destroyed($playerinfo['currentship'], $playerinfo['player_id'], $playerinfo['rating'], 0, 0);
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET destroyed='N' WHERE player_id=$playerinfo[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					$stamp = date("Y-m-d H:i:s");
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET profile_cached='N', logged_out='N', forum_login='$playerinfo[last_login]', last_login='$stamp', credits=credits+1000, sessionid='" . session_id() . "' WHERE player_id=$playerinfo[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					$template_object->assign("l_here", ucfirst($l_here));
					$template_object->assign("l_login_blackbox", $l_login_blackbox);
					$template_object->assign("l_login_newbie", $l_login_newbie);
					$template_object->assign("error_msg", $l_login_diedincident);
					$template_object->assign("error_msg2", $l_login_newlife);
					$template_object->assign("l_clickme", $l_clickme);
					$template_object->assign("l_new_login", $l_new_login);
					$template_object->display($templatename."login2.tpl");
					include ("footer.php");
					die();
				}
				else
				{
					playerlog($playerinfo['player_id'], "LOG_LOGIN", $ip);
					ip_log($playerinfo['player_id'],$ip);
					$stamp = date("Y-m-d H:i:s");
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET profile_cached='N', logged_out='N', forum_login='$playerinfo[last_login]', last_login='$stamp', ip_address='$ip', sessionid='" . session_id() . "' WHERE " .
												"player_id=$playerinfo[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
							<html>
								<head>
									<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=log.php\">
									<title>Loading Player Log</title>
								</head>
								<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
								</body>
							</html>";
					die();
				}
			}
			else
			{
				playerlog($playerinfo['player_id'], "LOG_LOGIN", $ip);
				ip_log($playerinfo['player_id'],$ip);
				$stamp = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET profile_cached='N', logged_out='N', ip_address='$ip', sessionid='" . session_id() . "' WHERE " .
											"player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
						<html>
							<head>
								<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=log.php\">
								<title>Loading Player Log</title>
							</head>
							<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
							</body>
						</html>";
				die();
			}
		}
		else 
		{
			$title = $l_login_title2;
			// Skinning stuff
			if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
				$templatename = $default_template;
			}else{
				$templatename = $playerinfo['template'];
			}
			include ("header.php");

			$template_object->assign("title", $title);
			$template_object->assign("templatename", $templatename);
			playerlog($playerinfo['player_id'], "LOG_LOGIN", $ip);
			ip_log($playerinfo['player_id'],$ip);
			$stamp = date("Y-m-d H:i:s");
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET profile_cached='N', logged_out='N', forum_login='$playerinfo[last_login]', last_login='$stamp', ip_address='$ip', sessionid='" . session_id() . "' WHERE " .
										"player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET destroyed='N' WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$_SESSION['lobby_mode'] = 1;

			$template_object->assign("error_msg", $l_login_died);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."genericdie.tpl");
			include ("footer.php");
			die();
		}
	}
}
else
{
	$title = $l_login_title2;
	// Skinning stuff
	if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
		$templatename = $default_template;
	}else{
		$templatename = $playerinfo['template'];
	}
	include ("header.php");

	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);

	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE character_name=" . $db->qstr($_POST['character_name']) . "", 1);
	db_op_result($debug_query,__LINE__,__FILE__);

	if ($debug_query)
	{
		$playerfound = $debug_query->RecordCount();
	}

	if($playerfound)
	{
		// password is incorrect
		$playerinfo = $debug_query->fields;

		$l_new_message = "Someone attempted to login to your player account with a bad password from IP: $ip\r\n\r\n";

		$msg = "$l_new_message\r\n\r\nhttp://". $_SERVER['HTTP_HOST'] . "$gamepath\r\n";
		$msg = AAT_ereg_replace("\r\n.\r\n","\r\n. \r\n",$msg);
		$hdrs .= "From: AATRADE System Mailer <$admin_mail>\r\n";

		if($SMTP_Enabled == 0)
		{
			$e_response = mail($playerinfo['email'],"A Bad Login Attempt Detected", $msg,$hdrs);
		}
		else
		{
			require_once "backends/SwiftMailer/lib/Swift.php";
			require_once "backends/SwiftMailer/lib/Swift/Connection/SMTP.php";

			$smtp =& new Swift_Connection_SMTP($SMTP_Server_Address, $SMPT_Server_Port);
			$smtp->setUsername($SMTP_User_Name);
			$smtp->setPassword($SMTP_User_Password);

			$swift =& new Swift($smtp);

			//Create the message
			$message =& new Swift_Message("A Bad Login Attempt Detected", $msg);
			$e_response = $swift->send($message, $playerinfo['email'], $SMTP_Email_Address);
		}

		if ($e_response > 0)
		{
			$template_object->assign("emailresult", "<font color=\"lime\">Bad Login Email sent to $username</font>");
			AddELog($playerinfo['email'],4,'Y',"A Bad Login Attempt Detected",$e_response);
		}
		else
		{
			$template_object->assign("emailresult", "<font color=\"Red\">Bad Login Email failed to send to $username</font>");
			AddELog($playerinfo['email'],4,'N',"A Bad Login Attempt Detected",$e_response);
		}

		$template_object->assign("l_login_4gotpw1", $l_login_4gotpw1);
		$template_object->assign("playeremail", $playerinfo['player_id']);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_login_4gotpw2", $l_login_4gotpw2);
		$template_object->assign("l_login_4gotpw3", $l_login_4gotpw3);
		$template_object->assign("ip", $ip);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_new_login", $l_new_login);
		$template_object->display($templatename."login2-badpassword.tpl");
		include ("footer.php");
		playerlog($playerinfo['player_id'], "LOG0_BADLOGIN", $ip);
		die();
	}
	else
	{
		$template_object->assign("error_msg", $l_login_noone);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mlogin);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}
}

?>
