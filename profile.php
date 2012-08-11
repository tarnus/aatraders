<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: profile.php

include ("config/config.php");
include ("languages/$langdir/lang_profile.inc");

get_post_ifset("command, profilename, profilepassword, url, game");

$title = $l_profile_title;

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

if($enable_profilesupport == 1){
	if ($command == "Register"){
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
		if($result == "ok"){
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET show_shoutbox = $show_shoutbox, show_newscrawl = $show_news, profile_name='$name', profile_password='$password', profile_id=$profile_id WHERE player_id = $playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("message", $l_profile_registered);
			$template_object->assign("message2", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."profile.tpl");
			include ("footer.php");
			die();
		}
		elseif($result == "bad")
		{
			$template_object->assign("l_profile_nomatch", $l_profile_nomatch);
			$template_object->assign("l_profile_tryagain", $l_profile_tryagain);
			$template_object->assign("l_here", $l_here);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."profile-bad.tpl");
			include ("footer.php");
			die();
		}
		else
		if($result == "banned")
		{
			if($name == "server"){
				$template_object->assign("message", $l_profile_bannedserver);
				$template_object->assign("message2", "");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."profile.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$template_object->assign("message", $l_profile_bannedplayer);
				$template_object->assign("message2", "");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."profile.tpl");
				include ("footer.php");
				die();
			}
		}
		else
		{
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->assign("message", "Unknown Error: Please report the folowing information to the Admin.");
			$template_object->assign("message2", print_r($profilelines));
			$template_object->display($templatename."profile.tpl");
			include ("footer.php");
			die();
		}
	}
	else
	{
		$template_object->assign("l_profile_name", $l_profile_name);
		$template_object->assign("l_profile_password", $l_profile_password);
		$template_object->assign("url", rawurlencode($_SERVER['HTTP_HOST'] . $gamepath));
		$template_object->assign("game", rawurlencode($game_name));
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."profile-register.tpl");
		include ("footer.php");
		die();
	}
}
else
{
	$template_object->assign("message", $l_profile_notenabled);
	$template_object->assign("message2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."profile.tpl");
	include ("footer.php");
	die();
}
?>
