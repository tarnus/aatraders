<?php
// 3D Galaxy Map
//
// The second line MUST be the name of the command that is to be shown in the command list.
//
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: galaxy_map3d.php

include ("config/config.php");
include("languages/$langdir/lang_galaxy3d.inc");
include ("languages/$langdir/lang_galaxy_local.inc");

get_post_ifset("arm, turns");

if (checklogin())
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$title = $l_g3d_title;
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

if($arm == '')
	$selected = "selected";
else $selected = "";

$armdropdown = "<option value=\"\" $selected>All</option>\n";
for($i = 0; $i < $spiral_galaxy_arms; $i++){
	if($arm == $i and $arm != '')
		$selected = "selected";
	else $selected = "";
	
	$armdropdown .= "<option value=\"". $i ."\" $selected>".  $i ."</option>\n";
}

if($turns != '')
{
	$shipspeed = mypw($level_factor, $shipinfo['engines']);
	$distance = number($turns * $shipspeed);
}

$template_object->assign("l_submit", $l_submit);
$template_object->assign("l_glxy_turns", $l_glxy_turns);
$template_object->assign("l_glxy_select", $l_glxy_select);
$template_object->assign("distance", $distance);
$template_object->assign("turns", $turns);
$template_object->assign("armdropdown", $armdropdown);
$template_object->assign("spiral_galaxy_arms", $spiral_galaxy_arms);
$template_object->assign("arm", $arm);
$template_object->assign("l_g3d_wait", $l_g3d_wait);
$template_object->assign("shipsector", $shipinfo['sector_id']);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."galaxy3d.tpl");
include ("footer.php");
?>


