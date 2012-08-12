<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: new.php

include ("config/config.php");
include ("languages/$langdir/lang_new.inc");
include ("languages/$langdir/lang_profile.inc");

$title = $l_new_title;
// Skinning stuff
if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");
$template_object->assign("templatename", $templatename);

$template_object->assign("title", $title);
$template_object->assign("l_new_closed_message", $l_new_closed_message);
$template_object->assign("account_creation_closed", $account_creation_closed);
$template_object->assign("l_login_email", $l_login_email);
$template_object->assign("l_new_shipname", $l_new_shipname);
$template_object->assign("l_new_pname", $l_new_pname);
$template_object->assign("l_submit", $l_submit);
$template_object->assign("l_reset", $l_reset);
$template_object->assign("l_new_info", $l_new_info);

$template_object->assign("tournament_setup_access", $tournament_setup_access);
$template_object->assign("tournament_mode", $tournament_mode);
$template_object->assign("profile_only_server", $profile_only_server);
$template_object->assign("enable_profilesupport", $enable_profilesupport);
$template_object->assign("l_profile_description", $l_profile_description);
$template_object->assign("l_profile_name", $l_profile_name);
$template_object->assign("l_profile_password", $l_profile_password);
$template_object->assign("url", rawurlencode($_SERVER['HTTP_HOST'] . $gamepath));
$template_object->assign("game", rawurlencode($game_name));
$template_object->assign("game_number", $game_number);

$template_object->display($default_template."new.tpl");

include ("footer.php"); 

?>
