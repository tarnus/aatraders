<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: feedback.php

include ("config/config.php");
include ("languages/$langdir/lang_feedback.inc");
include ("globals/AddELog.inc");
include ("backends/SwiftMailer/lib/Swift.php");
include ("backends/SwiftMailer/lib/Swift/Connection/SMTP.php");

$title = $l_feedback_title;

function filter_test($test_var){
	$filter="MIME-Version: 1.0|multipart/mixed|This is a multi-part message|Content-Type|MIME format";
	$list_item=explode("|",$filter);
	$list_count=count($list_item);
	$badcount=0;
	for ($x=0;$x < $list_count;$x++){
		if (strstr($test_var,$list_item[$x])){
			$badcount++;
		}		
		
	}
	if ($badcount > 0){
		
		return true;
	}else{
		return false;
	}
}

if (checklogin()) 
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
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

if (empty($_POST['content']))
{

	$template_object->assign("l_feedback_info", $l_feedback_info);
	$template_object->assign("l_feedback_to", $l_feedback_to);
	$template_object->assign("l_feedback_from", $l_feedback_from);
	$template_object->assign("l_feedback_topi", $l_feedback_topi);
	$template_object->assign("l_feedback_message", $l_feedback_message);
	$template_object->assign("l_submit", $l_submit);
	$template_object->assign("playername", $playerinfo['character_name']);
	$template_object->assign("playeremail", $playerinfo['email']);
	$template_object->assign("l_feedback_feedback", $l_feedback_feedback);
	$template_object->assign("l_reset", $l_reset);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."feedbackenter.tpl");
	include ("footer.php");
	die();
} 
else 
{
	// New lines to prevent SQL injection. Bad stuff.
	$content = strip_tags(stripslashes($_POST['content']));
	$subject = ": " . strip_tags(stripslashes($_POST['subject']));
	$msg = "IP address - " . getenv("REMOTE_ADDR") . "\r\nPlayer Name - $playerinfo[character_name]\r\n\r\n$content\n\nhttp://". $_SERVER['HTTP_HOST'] . "$gamepath\r\n";
	$msg = AAT_ereg_replace("\r\n.\r\n","\r\n. \r\n", $msg);
	$hdrs = "From: $playerinfo[character_name] <$playerinfo[email]>\r\n";

	$warning="";
	if (filter_test($subject) || filter_test($msg)){
		$error_msg= "<br><br><font color=\"red\" size=\"2\">I am watching you.  This IP has been logged for spam practices and this is being forwarded to your ISP!  <p>Have a Nice Day!</font><br>";
		$message="SMTP Injection attempt in progress.   \n\nOffending IP is: " . getenv("REMOTE_ADDR");
		if($SMTP_Enabled == 0)
		{
			mail($admin_mail,
			"AATRADE Email Injection attempt!",
			$message,
			"From: $playerinfo[character_name] <$playerinfo[email]>\r\n");
		}
		else
		{
			$smtp =& new Swift_Connection_SMTP($SMTP_Server_Address, $SMPT_Server_Port);
			$smtp->setUsername($SMTP_User_Name);
			$smtp->setPassword($SMTP_User_Password);

			$swift =& new Swift($smtp);

			//Create the message
			$message =& new Swift_Message("AATRADE Email Injection attempt!", $message);
			$e_response = $swift->send($message, $SMTP_Email_Address, $admin_mail);
		}
		AddELog($admin_mail,2,'N',$l_feedback_subj . $subject,$e_response);
	}else{
		if($SMTP_Enabled == 0)
		{
			$e_response = mail($admin_mail,$l_feedback_subj . $subject,$msg,$hdrs);
		}
		else
		{
			$smtp =& new Swift_Connection_SMTP($SMTP_Server_Address, $SMPT_Server_Port);
			$smtp->setUsername($SMTP_User_Name);
			$smtp->setPassword($SMTP_User_Password);

			$swift =& new Swift($smtp);

			//Create the message
			$message =& new Swift_Message($l_feedback_subj, $msg);
			$e_response = $swift->send($message, $SMTP_Email_Address, $playerinfo['email']);
		}
		if ($e_response)
		{
			$error_msg = "<font color=\"lime\">Message Sent</font><br>";
			AddELog($admin_mail,2,'Y',$l_feedback_subj . $subject,$e_response);
		}
		else
		{
			$error_msg = "<font color=\"red\">Message failed to send!</font><br>$SMTP_Server_Address, $SMPT_Server_Port, $SMTP_User_Name, $SMTP_User_Password\n" . $log->dump(true);
			AddELog($admin_mail,2,'N',$l_feedback_subj . $subject,$e_response);
		}
	}

	$template_object->assign("error_msg", $error_msg);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."feedbacksend.tpl");
	include ("footer.php");
	die();
}

close_database();
?>
