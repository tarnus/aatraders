<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: emerwarp.php

include ("config/config.php");
include ("languages/$langdir/lang_emerwarp.inc");
include ("globals/log_move.inc");

$title = $l_ewd_title;

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

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if ($shipdevice['dev_emerwarp']['amount'] > 0)
{
	$source_sector = $shipinfo['sector_id'];
	$randplay=mt_rand(0,($totrecs-1));
	$findem = $db->SelectLimit("SELECT sector_id, sector_name FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 3 ORDER BY rand()", 1);
	$dest_sector = $findem->fields['sector_id'];
	$dest_sector_name = $findem->fields['sector_name'];
	$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET sector_id=$dest_sector WHERE ship_id=$shipinfo[ship_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_emerwarp']['device_id']);
	db_op_result($debug_query,__LINE__,__FILE__);

	$zone_query = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$source_sector", 1);
	db_op_result($zone_query,__LINE__,__FILE__);
	$zones = $zone_query->fields;

	log_move($playerinfo['player_id'],$shipinfo['ship_id'],$source_sector,$dest_sector,$shipinfo['class'],$shipinfo['cloak'],$zones['zone_id']);
	$l_ewd_used=str_replace("[sector]",$dest_sector_name,$l_ewd_used);
	$ewd_echo = $l_ewd_used;
} 
else 
{
	$ewd_echo = $l_ewd_none;
}

$template_object->assign("title", $title);
$template_object->assign("ewd_echo", $ewd_echo);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."emerwarp.tpl");

include ("footer.php");

?>
