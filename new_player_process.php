<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: new_finish.php

include ("config/config.php");
include ("languages/$langdir/lang_mail.inc");
include ("languages/$langdir/lang_new2.inc");
include ("languages/$langdir/lang_login2.inc");
include ("languages/$langdir/lang_profile.inc");
include ("globals/AddELog.inc");
include ("globals/clean_words.inc");
include ("globals/newplayer.inc");
include ("globals/RecurseDir.inc");
include ("globals/ord_crypt_encode.inc");

get_post_ifset("character, shipname, username, url, game, profilename, profilepassword");

function is_valid_email_eregi ($address) { 

	return (AAT_eregi( 
		'^[-!#$%&\'*+\\./0-9=?A-Z^_`{|}~]+'.	  // the user name 
		'@'.									  // the ubiquitous at-sign 
		'([-0-9A-Z]+\.)+' .					   // host, sub-, and domain names 
		'([0-9A-Z]){2,4}$',					   // top-level domain (TLD) 
		trim($address))); 
} 

$character = trim($character);
$shipname = trim($shipname);
$username = trim($username);

$makepass = '';
$title = $l_new_title2;
// Skinning stuff
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

if ((!isset($hdrs)) || ($hdrs == ''))
{
	$hdrs = '';
}

if ($account_creation_closed)
{
	include ("languages/$langdir/lang_new.inc");
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_new_closed_message);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}

// Limit all entries to A-Z (word characters \w), 0-9 (digits \d), whitespace (\s), and single quote. Our big concern is semicolons.
// Username has to allow @ signs and periods for email. :)
if(is_valid_email_eregi($_POST['username'])){
	$username = $_POST['username'];
}else{
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_new_invalidemail);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}

$shipname = preg_replace ("/[^\w\d\s\']/","",clean_words($shipname));
$character = preg_replace ("/[^\w\d\s\']/","",clean_words($character));

// Convert any html entities. Prevents html/js exploit crap.
$username = htmlspecialchars($username,ENT_QUOTES);
$shipname = preg_replace ("/[^A-Za-z0-9\s\-\=\\\'\!\&\*\_]/","",trim($shipname));
$character = preg_replace ("/[^A-Za-z0-9\s\-\=\\\'\!\&\*\_]/","",trim($character));

if ($username == '' || $character == '' || $shipname == '' )
{ 
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_new_blank);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ip_bans WHERE '$ip' LIKE ban_mask or email=" . $db->qstr($username) . "", 1);
db_op_result($debug_query,__LINE__,__FILE__);

if ($debug_query->RecordCount() != 0)
{
	$title = $l_login_title2;
	$template_object->assign("title", $title);
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_login_banned);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}
elseif ($server_closed)
{
	$title = $l_login_sclosed;
	$template_object->assign("title", $title);
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_login_closed_message);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}

$result = $db->Execute("SELECT email, character_name FROM {$db_prefix}players");

if ($result>0)
{
	while(!$result->EOF)
	{
		$row = $result->fields;
		if (AAT_strtolower($row['email']) == AAT_strtolower($username)) 
		{ 
			$l_new_inuse = str_replace("[username]", "\"$username\"", $l_new_inuse);
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("error_msg", $l_new_inuse);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}

		if (AAT_strtolower($row['character_name']) == AAT_strtolower($character)) 
		{ 
			$l_new_inusechar = str_replace("[character]", "\"$character\"", $l_new_inusechar);
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("error_msg", $l_new_inusechar);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}
		elseif (metaphone($row['character_name']) == metaphone($character)) 
		{ 
			$l_new_similar_inusechar = str_replace("[character]", "\"$row[character_name]\"", $l_new_similar_inusechar);
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("error_msg", $l_new_similar_inusechar);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}
		$result->MoveNext();
	}
}

if (AAT_substr_count("guide", AAT_strtolower($newplayername)) > 0 || AAT_strtolower($character) == "unknown" || AAT_strtolower($character) == "unowned" || AAT_strtolower($character) == "unchartered" || AAT_strtolower($character) == "uncharted") 
{ 
	$l_new_inusechar = str_replace("[character]", "\"$character\"", $l_new_inusechar);
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_new_inusechar);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}

$result = $db->Execute("SELECT name FROM {$db_prefix}ships");

if ($result>0)
{
	while(!$result->EOF)
	{
		$row = $result->fields;
		if (AAT_strtolower($row['name']) == AAT_strtolower($shipname)) 
		{
			$l_new_inuseship = str_replace("[shipname]", "\"$shipname\"", $l_new_inuseship);
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("error_msg", $l_new_inuseship);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}
		elseif (metaphone($row['name']) == metaphone($shipname)) 
		{ 
			$l_new_similar_inuseship = str_replace("[shipname]", "\"$row[name]\"", $l_new_similar_inuseship);
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("error_msg", $l_new_similar_inuseship);
			$template_object->assign("error_msg2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}
		$result->MoveNext();
	}
}

if (AAT_strtolower($shipname) == "unknown" || AAT_strtolower($shipname) == "unowned" || AAT_strtolower($shipname) == "unchartered" || AAT_strtolower($shipname) == "uncharted") 
{ 
	$l_new_inuseship = str_replace("[shipname]", "\"$shipname\"", $l_new_inuseship);
	$template_object->assign("l_new_login", $l_new_login);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("error_msg", $l_new_inuseship);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."new2-die.tpl");
	include ("footer.php");
	die();
}

$isprofileset = 0;
if ($enable_profilesupport == 1 && ($tournament_setup_access == 1 || $tournament_mode == 1 || $profile_only_server == 1))
{
	if($enable_profilesupport == 1 && ($profilename != '' || !empty($profilename))){
		$url = "http://www.aatraders.com/validate_player_profile30.php?name=" . rawurlencode($profilename) . "&password=" . rawurlencode($profilepassword) . "&url=$url&game=$game&game_number=" . $game_number;

//		echo "\n\n<!--" . $url . "-->\n\n";

		if(@ini_get("allow_url_fopen") == 1)
		{
			$fp = @fopen ($url,"r");
			if($fp)
			{
				while(!@feof($fp)){
					$profilelines[] = str_replace("\n", "", trim(@fgets($fp)));
				}
				fclose ($fp);
			}
		}
		else
		if(function_exists('curl_init'))
		{
			$ch=curl_init();
			curl_setopt($ch, CURLOPT_URL, $url);
			curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
			$var = curl_exec ($ch);
			$profilelines = explode("\n", trim($var));
			curl_close ($ch);
		}

		$result = trim($profilelines[0]);
		$name = trim($profilelines[1]);
		$password = trim($profilelines[2]);
		$profile_id = trim($profilelines[3]);
		$show_shoutbox = trim($profilelines[4]);
		$show_news = trim($profilelines[5]);
		$game_template = trim($profilelines[6]);

		$dirlist=RecurseDir($gameroot."templates"); 
		chdir($gameroot);
		$template_query = '';

		foreach ($dirlist as $key=>$val) { 
			$temp = str_replace($gameroot."templates/", "", $val);
			$template = explode("/", $temp);

			if(is_file($gameroot."templates/" . $template[0] . "/about_template.inc")){
				$templatedir = $template[0] . "/";
				if($game_template == $templatedir)
					$template_query = ", template='$game_template'";
			}
		}

		if($result == "ok"){
			$template_object->assign("message", $l_profile_registered);
			$template_object->assign("message2", "");
			$isprofileset = 1;
		}
		else
		if($result == "bad")
		{
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->assign("error_msg", $l_profile_nomatch);
			$template_object->assign("error_msg2", $l_profile_tryagain);
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}
		else
		if($result == "banned")
		{
			if($name == "server"){
				$template_object->assign("l_new_login", $l_new_login);
				$template_object->assign("l_clickme", $l_clickme);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->assign("error_msg", $l_profile_bannedserver);
				$template_object->assign("error_msg2", "");
				$template_object->display($templatename."new2-die.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$template_object->assign("l_new_login", $l_new_login);
				$template_object->assign("l_clickme", $l_clickme);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->assign("error_msg", $l_profile_bannedplayer);
				$template_object->assign("error_msg2", "");
				$template_object->display($templatename."new2-die.tpl");
				include ("footer.php");
				die();
			}
		}
		else
		{
			$template_object->assign("l_new_login", $l_new_login);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->assign("error_msg", "Unknown Error: Please report the following information to the Admin.");
			$template_object->assign("error_msg2", print_r($profilelines));
			$template_object->display($templatename."new2-die.tpl");
			include ("footer.php");
			die();
		}
	}
	else
	{
		$template_object->assign("l_new_login", $l_new_login);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->assign("error_msg", $l_profile_nomatch);
		$template_object->assign("error_msg2", $l_profile_tryagain);
		$template_object->display($templatename."new2-die.tpl");
		include ("footer.php");
		die();
	}
}

/* insert code to add player to database */
$syllables = "er,in,tia,wol,fe,pre,vet,jo,nes,al,len,son,cha,ir,ler,bo,ok,tio,nar,sim,ple,bla,ten,toe,cho,co,lat,spe,ak,er,po,co,lor,pen,cil,li,ght,wh,at,the,he,ck,is,mam,bo,no,fi,ve,any,way,pol,iti,cs,ra,dio,sou,rce,sea,rch,pa,per,com,bo,sp,eak,st,fi,rst,gr,oup,boy,ea,gle,tr,ail,bi,ble,brb,pri,dee,kay,en,be,se";
$syllable_array = explode(",", $syllables);
mt_srand((double)microtime()*1000000);
for ($count=1;$count<=4;$count++) 
{
	if (mt_rand()%10 == 1) 
	{
		$makepass .= sprintf("%0.0f",(mt_rand()%50)+1);
	} 
	else 
	{
		$makepass .= sprintf("%s",$syllable_array[mt_rand()%62]);
	}
}

$player_id = newplayer($username, $character, ord_crypt_encode($makepass), $shipname);
$l_new_message = str_replace("[pass]", $makepass, $l_new_message);

$msg = "$l_new_message\r\n\r\nhttp://". $_SERVER['HTTP_HOST'] . "$gamepath\r\n";
$msg = AAT_ereg_replace("\r\n.\r\n","\r\n. \r\n",$msg);
$hdrs .= "From: AATRADE System Mailer <$admin_mail>\r\n";

if($SMTP_Enabled == 0)
{
	$e_response = mail($username,$l_new_topic, $msg,$hdrs);
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
	$message =& new Swift_Message($l_new_topic, $msg);
	$e_response = $swift->send($message, $username, $SMTP_Email_Address);
}

if ($e_response > 0)
{
	$template_object->assign("emailresult", "<font color=\"lime\">Email sent to $username</font>");
	AddELog($username,1,'Y',$l_new_topic,$e_response);
}	   
else
{
	$template_object->assign("emailresult", "<font color=\"Red\">Email failed to send to $username</font>");
	AddELog($username,1,'N',$l_new_topic,$e_response);
}

if($enable_profilesupport == 1 && $isprofileset == 0 && ($profilename != '' || !empty($profilename))){
	$url = "http://www.aatraders.com/validate_player_profile30.php?name=" . rawurlencode($profilename) . "&password=" . rawurlencode($profilepassword) . "&url=$url&game=$game&game_number=" . $game_number;

//	echo "\n\n<!--" . $url . "-->\n\n";

	if(@ini_get("allow_url_fopen") == 1)
	{
		$fp = @fopen ($url,"r");
		if($fp)
		{
			while(!@feof($fp)){
				$profilelines[] = str_replace("\n", "", trim(@fgets($fp)));
			}
			fclose ($fp);
		}
	}
	else
	if(function_exists('curl_init'))
	{
		$ch=curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
		$var = curl_exec ($ch);
		$profilelines = explode("\n", trim($var));
		curl_close ($ch);
	}

	$result = trim($profilelines[0]);
	$name = trim($profilelines[1]);
	$password = trim($profilelines[2]);
	$profile_id = trim($profilelines[3]);
	$show_shoutbox = trim($profilelines[4]);
	$show_news = trim($profilelines[5]);
	$game_template = trim($profilelines[6]);

	$dirlist=RecurseDir($gameroot."templates"); 
	chdir($gameroot);
	$template_query = '';

	foreach ($dirlist as $key=>$val) { 
		$temp = str_replace($gameroot."templates/", "", $val);
		$template = explode("/", $temp);

		if(is_file($gameroot."templates/" . $template[0] . "/about_template.inc")){
			$templatedir = $template[0] . "/";
			if($game_template == $templatedir)
				$template_query = ", template='$game_template'";
		}
	}

	if($result == "ok"){
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET show_shoutbox = $show_shoutbox, show_newscrawl = $show_news, profile_name='$name', profile_password='$password', profile_id=$profile_id $template_query WHERE player_id = $player_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		$template_object->assign("message", $l_profile_registered);
		$template_object->assign("message2", "");
	}
	else if($result == "bad")
	{
		$template_object->assign("l_profile_nomatch", $l_profile_nomatch);
		$template_object->assign("l_profile_tryagain", $l_profile_tryagain);
	}
	else if($result == "banned")
	{
		if($name == "server"){
			$template_object->assign("message", $l_profile_bannedserver);
			$template_object->assign("message2", "");
		}
		else
		{
			$template_object->assign("message", $l_profile_bannedplayer);
			$template_object->assign("message2", "");
		}
	}
	else
	{
		$template_object->assign("l_new_login", $l_new_login);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->assign("error_msg", "Unknown Error: Please report the following information to the Admin.");
		$template_object->assign("error_msg2", print_r($profilelines));
		$template_object->display($templatename."new2-die.tpl");
		include ("footer.php");
		die();
	}
}
else
{
	if($isprofileset == 1)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET show_shoutbox = $show_shoutbox, show_newscrawl = $show_news, profile_name='$name', profile_password='$password', profile_id=$profile_id $template_query WHERE player_id = $player_id");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

$template_object->assign("enable_profilesupport", $enable_profilesupport);
$template_object->assign("l_here", $l_here);
$template_object->assign("l_new_profile", $l_new_profile);
$template_object->assign("l_new_tutorial", $l_new_tutorial);
$template_object->assign("display_password", $display_password);
$template_object->assign("l_new_pwis", $l_new_pwis);
$template_object->assign("l_new_charis", $l_new_charis);
$template_object->assign("makepass", $makepass);
$template_object->assign("character", $character);
$template_object->assign("username", $username);
$template_object->assign("l_new_login", $l_new_login);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_new_err", $l_new_err);
$template_object->display($templatename."new2.tpl");

include ("footer.php");
?>

