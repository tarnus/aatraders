<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: message_read.php

include ("config/config.php");
include ("languages/$langdir/lang_readmail.inc");
include ("languages/$langdir/lang_mailto2.inc");

get_post_ifset("action, name, ID, page");

$title = $l_readm_title;

if ((!isset($action)) || ($action == ''))
{
	$action = '';
}

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

if ($action == "delete")
{
	$db->Execute("DELETE FROM {$db_prefix}messages WHERE ID='".$ID."' AND recp_id='".$playerinfo['player_id']."'");
}
else if ($action == "delete_all")
{
	$db->Execute("DELETE FROM {$db_prefix}messages WHERE recp_id='".$playerinfo['player_id']."'");
}

if ($action == "block" && $name > 3)
{
	$db->Execute("DELETE FROM {$db_prefix}messages WHERE sender_id='".$name."' AND recp_id='".$playerinfo['player_id']."'");
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}message_block (blocked_player_id, player_id) VALUES " .
				   "('" . $name . "', '" . $playerinfo['player_id'] . "')");
	db_op_result($debug_query,__LINE__,__FILE__);
}

$cur_D = date("Y-m-d");
$cur_T = date("H:i:s");

if(empty($page))
{
	$page = 1;
}

$entries_per_page = 25;

$res1 = $db->SelectLimit("SELECT count(ID) as total FROM {$db_prefix}messages WHERE recp_id='".$playerinfo['player_id'] . "'", 1);
$totalmessages = $res1->fields['total'];
$res1->close();

$start = ($page - 1) * $entries_per_page;
$totalpages = ceil($totalmessages / $entries_per_page);
$currentpage = $page;
if($page < $totalpages)
{
	$nextpage = $page + 1;
}
else
{
	$nextpage = $page;
}

if($page > 1)
{
	$previouspage = $page - 1;
}
else
{
	$previouspage = 1;
}

$template_object->assign("totalpages", $totalpages);
$template_object->assign("nextpage", $nextpage);
$template_object->assign("previouspage", $previouspage);
$template_object->assign("currentpage", $currentpage);
$template_object->assign("totalmessages", $totalmessages);

$template_object->assign("l_common_prev", $l_common_prev);
$template_object->assign("l_common_next", $l_common_next);
$template_object->assign("l_common_totalpages", $l_common_totalpages);
$template_object->assign("l_common_selectpage", $l_common_selectpage);
$template_object->assign("l_common_page", $l_common_page);
$template_object->assign("l_submit", $l_submit);

$res = $db->SelectLimit("SELECT * FROM {$db_prefix}messages WHERE recp_id='".$playerinfo['player_id']."' ORDER BY sent DESC", $entries_per_page, $start);

$template_object->assign("l_readm_center", $l_readm_center);
$template_object->assign("cur_D", $cur_D);
$template_object->assign("cur_T", $cur_T);

if ($res->EOF)
{
	$template_object->assign("nomessages", 1);
	$template_object->assign("l_readm_nomessage", $l_readm_nomessage);
}
else
{
	$template_object->assign("nomessages", 0);
	$line_counter = true;
	$messagecount = 0;
	while (!$res->EOF)
	{
		$msg = $res->fields;
		if($msg['sender_id'] == 0)
		{
			$sender['avatar'] = "default_avatar.gif";
			$sender['player_id'] = 0;
			$sender['character_name'] = $l_readm_alert;
			$sendership['name'] = $l_readm_alertbody;
		}
		else
		{
			$result = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id='".$msg['sender_id']."'", 1);
			$sendership = $result->fields;
			$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='".$msg['sender_id']."'", 1);
			$sender = $result2->fields;
		}
		$avatar[$messagecount] = $sender['avatar'];
		$msgid[$messagecount] = $msg['ID'];
		$sendername[$messagecount] = $sender['character_name'];
		$senderid[$messagecount] = $sender['player_id'];
		$msgsent[$messagecount] = $msg['sent'];
		$sendname[$messagecount] = $sendership['name'];
		$subject[$messagecount] = $msg['subject'];
		$message[$messagecount] = nl2br($msg['message']);

		$messagecount++;
		$res->MoveNext();
	}
}

$template_object->assign("avatar", $avatar);
$template_object->assign("sender", $sendername);
$template_object->assign("senderid", $senderid);
$template_object->assign("msgsent", $msgsent);
$template_object->assign("msgid", $msgid);
$template_object->assign("sendname", $sendname);
$template_object->assign("subject", $subject);
$template_object->assign("message", $message);

$template_object->assign("messagecount", $messagecount);
$template_object->assign("l_readm_subject", $l_readm_subject);
$template_object->assign("l_readm_sender", $l_readm_sender);
$template_object->assign("l_readm_captn", $l_readm_captn);
$template_object->assign("l_readm_del", $l_readm_del);
$template_object->assign("l_readm_repl", $l_readm_repl);
$template_object->assign("l_readm_title2", $l_readm_title2);
$template_object->assign("l_readm_delete", $l_readm_delete);
$template_object->assign("l_readm_quote", $l_readm_quote);
$template_object->assign("l_readm_block", $l_readm_block);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."readmail.tpl");
include ("footer.php");
?>

