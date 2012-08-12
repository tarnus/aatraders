<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: igb.php

include ("config/config.php");
include ("languages/$langdir/lang_igb.inc");
include ("globals/gen_score.inc");

get_post_ifset("command");

function igb_error($errmsg, $backlink, $title="Error!")
{
	global $l_igb_igberrreport, $l_igb_back, $l_igb_logout,$template_object,$templatename;

	$title = $l_igb_igberrreport;
	global $templatename;

	$template_object->assign("title", $title);
	$template_object->assign("errmsg", $errmsg);
	$template_object->assign("backlink", $backlink);
	$template_object->assign("l_igb_back", $l_igb_back);
	$template_object->assign("l_igb_logout", $l_igb_logout);

	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."igb/igb_error.tpl");
	include ("footer.php");
	die();
}

$title=$l_igb_title;

if (checklogin() or $tournament_setup_access == 1) {
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

$result = $db->SelectLimit("SELECT * FROM {$db_prefix}ibank_accounts WHERE player_id=$playerinfo[player_id]", 1);
$account = $result->fields;

$how_many2 = 0;
$result3 = $db->Execute("SELECT COUNT(planet_id) AS total FROM {$db_prefix}planets WHERE sector_id=$shipinfo[sector_id]");
if ($result3)
	$how_many2 = $result3->fields['total'];

if($sectorinfo['port_type'] == "casino")
{
	$how_many2 = 0;
}
else
{
	$how_many2 = 1;
}

if (!$allow_ibank || $how_many2 == 0)
	igb_error($l_igb_malfunction, "main.php");

if (is_file($gameroot . "igb/". $command . ".inc"))
{
	@include ("igb/". $command . ".inc");
	include ("footer.php");
	die();
}
else
{
	$template_object->assign("l_igb_welcometoigb", $l_igb_welcometoigb);
	$template_object->assign("l_igb_accountholder", $l_igb_accountholder);
	$template_object->assign("l_igb_shipaccount", $l_igb_shipaccount);
	$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
	$template_object->assign("playername", $playerinfo['character_name']);
	$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
	$template_object->assign("l_igb_credit_symbol", $l_igb_credit_symbol);
	$template_object->assign("l_igb_operations", $l_igb_operations);
	$template_object->assign("l_igb_withdraw", $l_igb_withdraw);
	$template_object->assign("l_igb_deposit", $l_igb_deposit);
	$template_object->assign("l_igb_transfer", $l_igb_transfer);
	$template_object->assign("l_igb_loans", $l_igb_loans);
	$template_object->assign("l_igb_back", $l_igb_back);
	$template_object->assign("l_igb_logout", $l_igb_logout);
	$template_object->assign("accountbalance", NUMBER($account['balance']));

	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."igb/igb_main.tpl");
	include ("footer.php");
	die();
}

close_database();
?>
