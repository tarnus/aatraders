<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: header.php

include ("config/config.php");
include ("languages/$langdir/lang_contact_admin.inc");

get_post_ifset("comments, contact_name, email");

$stamp = date("Y-m-d H:i:s");

$title = $l_contact_admin_thanks;
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

function filter_test($test_var){
	$filter="MIME-Version: 1.0|multipart/mixed|This is a multi-part message|Content-Type|MIME format|[url|spears.com";
	$list_item=explode("|",$filter);
	$list_count=count($list_item);
	$badcount=0;
	for ($x=0;$x < $list_count;$x++){
		if (strstr($test_var,$list_item[$x])){
			$badcount++;
		}		
		
	}
	
	if ($badcount > 0 || AAT_substr_count($test_var, 'http://') > 1)
	{
		return true;
	}else{
		return false;
	}
}      

$comments2=wordwrap( stripslashes(strip_tags($comments)), 70 );

function GetIP()
{
   if (getenv("HTTP_CLIENT_IP") && strcasecmp(getenv("HTTP_CLIENT_IP"), "unknown"))
           $ip = getenv("HTTP_CLIENT_IP");
       else if (getenv("HTTP_X_FORWARDED_FOR") && strcasecmp(getenv("HTTP_X_FORWARDED_FOR"), "unknown"))
           $ip = getenv("HTTP_X_FORWARDED_FOR");
       else if (getenv("REMOTE_ADDR") && strcasecmp(getenv("REMOTE_ADDR"), "unknown"))
           $ip = getenv("REMOTE_ADDR");
       else if (isset($_SERVER['REMOTE_ADDR']) && $_SERVER['REMOTE_ADDR'] && strcasecmp($_SERVER['REMOTE_ADDR'], "unknown"))
           $ip = $_SERVER['REMOTE_ADDR'];
       else
           $ip = "unknown";
   return($ip);
}/*-------GetIP()-------*/

$remote_ip=GetIP();

if (filter_test($comments) or  filter_test($email))
{
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ip_bans WHERE '$remote_ip' LIKE ban_mask");
	db_op_result($debug_query,__LINE__,__FILE__);
	$ipinfo = $debug_query->fields;
	if($debug_query->RecordCount() == 0)
	{
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans (ban_mask, email)VALUES('$remote_ip', '0')");
		db_op_result($debug_query,__LINE__,__FILE__);
		$ipinfo['ban_mask'] = $remote_ip;
		$ipinfo['email'] = 0;
	}

	$ipinfo['email'] += 1;

	$debug_query = $db->Execute("UPDATE {$db_prefix}ip_bans SET email='$ipinfo[email]' WHERE '$remote_ip' LIKE ban_mask");
	db_op_result($debug_query,__LINE__,__FILE__);

	if($ipinfo['email'] < 3)
	{
		$l_contact_admin_thanks_comment = "<br><br><font color=\"red\" size=\"2\">I am watching you.  This IP has been logged for spam practices and this is being forwarded to your ISP!  <p>Have a Nice Day!</font><br>";
		$message="SMTP Injection attempt in progress.\n\nOffending IP is: ".$remote_ip;
		if($SMTP_Enabled == 0)
		{
			mail($admin_mail,
			"AATRADE Smtp Injection attempt!",
			$message,
			"From: $admin_mail\n");
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
			$message =& new Swift_Message("AATRADE Smtp Injection attempt!", $message);
			$e_response = $swift->send($message, $SMTP_Email_Address, $admin_mail);
		}
	}
	else
	{
		$l_contact_admin_thanks_comment = "<br><br><font color=\"red\" size=\"2\">This IP has been BANNED and nothing will be accepted from it.  <p>Have a Nice Day!</font><br>";
	}
}else{

	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ip_bans WHERE '$remote_ip' LIKE ban_mask and email > '3'");
	db_op_result($debug_query,__LINE__,__FILE__);

	if($debug_query->RecordCount() != 0)
	{
		$l_contact_admin_thanks_comment = "<br><br><font color=\"red\" size=\"2\">This IP has been BANNED and nothing will be accepted from it.  <p>Have a Nice Day!</font><br>";
		$template_object->assign("l_contact_admin_thanks_comment", $l_contact_admin_thanks_comment);
		$template_object->assign("l_contact_admin_close", $l_contact_admin_close);
		$template_object->assign("l_contact_admin_email_alert", $l_contact_admin_email_alert);
		$template_object->display($default_template . "contactthanks.tpl");

		$index_page = 1;
		include ("footer.php");
		die();
	}


	$message="\n
Name:        $contact_name\n
Email:       $email\n

Comments\n
====================================================\n
$comments2\n
IPAddress: $remote_ip
";

	if($email!=""){
		$sendemail = $admin_mail;
		$email = str_replace(array("\r", "\n"), '', $email); 
		if($SMTP_Enabled == 0)
		{
			mail($sendemail,
				"AATRADERS: $game_name",
				$message,
				"From: ".$email."\n");
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
			$message =& new Swift_Message("AATRADERS Comment: $game_name", $message);
			$e_response = $swift->send($message, $SMTP_Email_Address, $email);
		}
	}
}

$template_object->assign("l_contact_admin_thanks_comment", $l_contact_admin_thanks_comment);
$template_object->assign("l_contact_admin_close", $l_contact_admin_close);
$template_object->assign("l_contact_admin_email_alert", $l_contact_admin_email_alert);

$template_object->display($default_template."contactthanks.tpl");

$index_page = 1;
include ("footer.php");
?>

