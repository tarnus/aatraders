<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: messageblockmanager.php

include ("config/config.php");
include ("languages/$langdir/lang_blockmanager.inc");

get_post_ifset("command, to2, to");

$title = $l_block_title;

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

if($command == "block"){
	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE character_name=" . $db->qstr($to2), 1);
	$target_info = $res->fields;
	if($target_info['player_id'] > 3){
		$db->Execute("DELETE FROM {$db_prefix}messages WHERE sender_id='".$target_info['player_id']."' AND recp_id='".$playerinfo['player_id']."'");
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}message_block (blocked_player_id, player_id) VALUES " .
					   "('" . $target_info['player_id'] . "', '" . $playerinfo['player_id'] . "')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

if($command == "unblock"){
	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE character_name=" . $db->qstr($to), 1);
	$target_info = $res->fields;
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}message_block WHERE blocked_player_id = $target_info[player_id] and player_id = $playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}

// Get Blocked Players
$res = $db->Execute("SELECT {$db_prefix}players.character_name, {$db_prefix}players.player_id FROM {$db_prefix}players, {$db_prefix}message_block WHERE {$db_prefix}players.player_id <> $playerinfo[player_id]
					and {$db_prefix}message_block.player_id = $playerinfo[player_id] and {$db_prefix}message_block.blocked_player_id = {$db_prefix}players.player_id ORDER BY {$db_prefix}players.character_name ASC");
$blockcount = 0;
while (!$res->EOF)
{
	$row = $res->fields;
	$blockedplayers[$blockcount] = $row['character_name'];
	$blockcount++;
	$res->MoveNext();
}

// Get Unblocked Players

$res = $db->Execute("SELECT character_name, player_id FROM {$db_prefix}players WHERE player_id <> $playerinfo[player_id]
					and player_id > 3 ORDER BY character_name ASC");
$unblockcount = 0;
while (!$res->EOF)
{
	$row = $res->fields;
	$res2 = $db->Execute("SELECT * FROM {$db_prefix}message_block WHERE player_id = $playerinfo[player_id] and blocked_player_id = $row[player_id]");
	if($res2->RecordCount() == 0){
		$unblockedplayers[$unblockcount] = $row['character_name'];
		$unblockcount++;
	}
	$res->MoveNext();
}


$template_object->assign("blockedplayers", $blockedplayers);
$template_object->assign("blockcount", $blockcount);
$template_object->assign("unblockedplayers", $unblockedplayers);
$template_object->assign("unblockcount", $unblockcount);
$template_object->assign("l_block_receivefrom", $l_block_receivefrom);
$template_object->assign("l_block_block", $l_block_block);
$template_object->assign("l_block_blockfrom", $l_block_blockfrom);
$template_object->assign("l_block_unblock", $l_block_unblock);
$template_object->assign("l_block_empty", $l_block_empty);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."blockmanager.tpl");
include ("footer.php");

close_database();
?>
