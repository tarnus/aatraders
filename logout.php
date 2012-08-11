<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: logout.php

include ("config/config.php");
include ("languages/$langdir/lang_logout.inc");
include ("globals/gen_score.inc");
include ("globals/good_neutral_evil.inc");

get_post_ifset("self_destruct, game_number");

$title = $l_logout_title;

if ((!isset($self_destruct)) && checklogin())
{
	if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
		$templatename = $default_template;
	}else{
		$templatename = $playerinfo['template'];
	}
	include ("header.php");

	$template_object->assign("title", $title);

	$template_object->assign("error_msg", $l_global_needlogin);
	$template_object->assign("error_msg", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

$difftime = TIME() - 360;
$stamp = date("Y-m-d H:i:s", $difftime);
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', logged_out='Y', profile_cached='Y', sessionid='' WHERE player_id = $playerinfo[player_id]");

setcookie("PHPSESSID","",0,"/");
session_destroy();

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

if (isset($self_destruct))
{
	$template_object->assign("error_msg", $l_global_mlogin);
	$template_object->assign("error_msg", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

$returnscore = gen_score($playerinfo['player_id']);
$current_score = NUMBER( $returnscore[0]);
playerlog($playerinfo['player_id'], "LOG_LOGOUT", $ip);

$l_logout_text = str_replace("[name]",$playerinfo['character_name'],$l_logout_text);

$template_object->assign("title", $title);
$template_object->assign("l_logout_score", $l_logout_score);
$template_object->assign("current_score", $current_score);
$template_object->assign("l_logout_text", $l_logout_text);
$template_object->display($templatename."logout.tpl");

include ("footer.php");
?>
