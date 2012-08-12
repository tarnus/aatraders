<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: ship.php

include ("config/config.php");
include ("languages/$langdir/lang_ship.inc");
include ("languages/$langdir/lang_planets.inc");

get_post_ifset("ship_id, player_id");

$title = $l_ship_title;

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

$debug_query = $db->SelectLimit("SELECT name, character_name, sector_id FROM {$db_prefix}ships " .
							"LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id " .
							"WHERE ship_id=$ship_id", 1);
db_op_result($debug_query,__LINE__,__FILE__);

$otherplayer = $debug_query->fields;

$result2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$otherplayer[sector_id]'", 1);
db_op_result($result2,__LINE__,__FILE__);
$sector_name = $result2->fields['sector_name'];
$result2->close();

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$template_object->assign("title", $title);
$template_object->assign("ship_id", $ship_id);
$template_object->assign("gamepath", $gamepath);
$template_object->assign("player_id", $player_id);
$template_object->assign("l_planet_att_link", $l_planet_att_link);
$template_object->assign("l_planet_scn_link", $l_planet_scn_link);
$template_object->assign("l_ship_perform", $l_ship_perform);
$template_object->assign("l_ship_owned", $l_ship_owned);
$template_object->assign("l_send_msg", $l_send_msg);
$template_object->assign("l_ship_youc", $l_ship_youc);
$template_object->assign("l_ship_the", $l_ship_the);
$template_object->assign("l_ship_nolonger", $l_ship_nolonger);
$template_object->assign("otherplayer_character_name", $otherplayer['character_name']);
$template_object->assign("otherplayer_name", $otherplayer['name']);
$template_object->assign("otherplayer_sector_id", $sector_name);
$template_object->assign("shipinfo_sector_id", $sectorinfo['sector_name']);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ship.tpl");

include ("footer.php");

?>
