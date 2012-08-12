<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: mail.php

include ("config/config.php");
include ("languages/$langdir/lang_mail.inc");
include ("globals/AddELog.inc");
include ("globals/ord_crypt_decode.inc");

get_post_ifset("mail");

$title = $l_mail_title;
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

$result = $db->Execute ("select email, password, character_name from {$db_prefix}players where player_id='$mail'");
if (!$result->EOF) 
{
	$mailplayer_info = $result->fields;
	$l_mail_message = str_replace("[pass]",ord_crypt_decode($mailplayer_info['password']),$l_mail_message);
	$msg = $l_mail_message;
	$msg .="\r\n\r\nhttp://$SERVER_NAME$gamepath\r\n";
	$msg = AAT_ereg_replace("\r\n.\r\n","\r\n. \r\n",$msg);
	$hdrs = "From: Alien Assault Tradewars Mailer <$admin_mail>\r\n"; 
	if($SMTP_Enabled == 0)
	{
		$e_response = mail($mailplayer_info['email'],$l_mail_topic,$msg,$hdrs); 
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
		$message =& new Swift_Message($l_mail_topic, $msg);
		$e_response = $swift->send($message, $mailplayer_info['email'], $SMTP_Email_Address);
	}

	if ($e_response > 0)
	{ 
		$template_object->assign("mailresult", "<font color=\"lime\">$l_mail_sent $mailplayer_info[character_name].</font>");
		AddELog($mailplayer_info['email'],3,'Y',$l_mail_topic,$e_response); 
	} 
	else 
	{ 
		$template_object->assign("mailresult", "<font color=\"red\">$l_mail_failed $mailplayer_info[character_name].</font>");
		AddELog($mailplayer_info['email'],3,'N',$l_mail_topic,$e_response); 
	} 
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_new_login", $l_new_login);
} 
else 
{ 
	$template_object->assign("mailresult", $l_mail_noplayer);
	$template_object->assign("l_clickme", "");
	$template_object->assign("l_new_login", "");
}

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."mail.tpl");
include ("footer.php");
?>

