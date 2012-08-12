<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File){ showdebris.php

include ("config/config.php");

include ("languages/$langdir/lang_debris.inc");
include ("languages/$langdir/lang_report.inc");
include ("globals/player_ship_destroyed.inc");

get_post_ifset("debris_id");

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$title = $l_debris_title;
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

$result4 = $db->Execute(" SELECT * FROM {$db_prefix}debris where debris_id=$debris_id and sector_id=$shipinfo[sector_id]");
db_op_result($result4,__LINE__,__FILE__);

if ($result4->recordcount())
{
	$row = $result4->fields;

	$debris_type = $row['debris_type'];
	if(!class_exists($debris_type)){
		include ("class/debris/" . $debris_type . ".inc");
	}
	$debrisobject = new $debris_type();
	$debrismessage = $debrisobject->show_debris_code();

	$debug_query = $db->Execute("DELETE FROM {$db_prefix}debris WHERE debris_id=$debris_id");
	db_op_result($debug_query,__LINE__,__FILE__);

	$template_object->assign("error_msg", $debrismessage);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."debris.tpl");
	include ("footer.php");
}else{
	$template_object->assign("error_msg", $l_debris_cantfind);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."debris.tpl");
	include ("footer.php");
}

close_database();
?>