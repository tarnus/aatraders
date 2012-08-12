<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: self_destruct.php

include ("config/config.php");
include ("languages/$langdir/lang_self_destruct.inc");
include ("globals/db_kill_player.inc");
include ("globals/cancel_bounty.inc");

get_post_ifset("sure");

$title = $l_die_title;

if (checklogin() || $tournament_mode == 1)
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

if ((!isset($sure)) || ($sure == ''))
{
	$sure = 0;
}

if ($sure == 2)
{
	$logout_link="<a href=logout.php?self_destruct=true>$l_die_please1</a>";
	$l_die_please2=str_replace("[logout_link]",$logout_link,$l_die_please2);

	if($playerinfo['destroyed'] != 'Y')
	{
		db_kill_player($playerinfo['player_id'], 0, 0, "killedsuicide");
		cancel_bounty($playerinfo['player_id']);
		adminlog("LOG0_ADMIN_HARAKIRI", "$playerinfo[character_name]|$ip");
		playerlog($playerinfo['player_id'], "LOG0_HARAKIRI", "$ip");
	}
}

if ($sure != 2)
{
	$template_object->assign("gotomain", $l_global_mmenu);
}

$template_object->assign("sure", $sure);
$template_object->assign("l_die_rusure", $l_die_rusure);
$template_object->assign("l_die_nonono", $l_die_nonono);
$template_object->assign("l_yes", $l_yes);
$template_object->assign("l_die_goodbye", $l_die_goodbye);
$template_object->assign("l_die_check", $l_die_check);
$template_object->assign("l_die_what", $l_die_what);
$template_object->assign("l_die_count", $l_die_count);
$template_object->assign("l_die_vapor", $l_die_vapor);
$template_object->assign("l_die_please1", $l_die_please1);
$template_object->assign("l_die_please2", $l_die_please2);
$template_object->display($templatename."self_destruct.tpl");
include ("footer.php");

?>
