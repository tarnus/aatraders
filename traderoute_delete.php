<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the		 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: traderoute_create.php

include ("config/config.php");
include ("languages/$langdir/lang_traderoute.inc");
include ("languages/$langdir/lang_teams.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_ports.inc");

get_post_ifset("TRDel");

$total_experience = 0;

$title = $l_tdr_title;

if (checklogin() or $tournament_setup_access == 1)
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

if (isset($_POST["TRDel"]))
{
	for ($i = 0; $i < count($TRDel); $i++)
	{
		$get_planetinfo = $db->Execute("delete from {$db_prefix}traderoutes WHERE  traderoute_id =$TRDel[$i] and player_id=$playerinfo[player_id]");
	}

	$template_object->assign("error_msg", $l_tdr_tdrdeleted);
	$template_object->assign("error_msg2", $l_tdr_returnmenu);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."traderoute_die.tpl");
	include ("footer.php");
}else{
	$template_object->assign("error_msg", $l_tdr_returnmenu);
	$template_object->assign("error_msg2", '');
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."traderoute_die.tpl");
	include ("footer.php");
}
?>
