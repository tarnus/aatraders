<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: shoutbox.php

include ("config/config.php");

include ("languages/$langdir/lang_shoutbox.inc");
include ("globals/add_smilies.inc");

get_post_ifset("page");

$title = $l_shout_title;

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

if(empty($page))
{
	$page = 1;
}

$entries_per_page = 25;

$res1 = $db->SelectLimit("SELECT count(sb_alli) as total FROM {$db_prefix}shoutbox WHERE sb_alli = 0", 1);
$totalshouts = $res1->fields['total'];
$res1->close();

$start = ($page - 1) * $entries_per_page;
$totalpages = ceil($totalshouts / $entries_per_page);
$template_object->assign("currentpage", $page);
if($page < $totalpages)
{
	$next = $page + 1;
}
else
{
	$next = $page;
}
$template_object->assign("nextpage", $next);
if($page > 1)
{
	$prev = $page - 1;
}
else
{
	$prev = 1;
}
$template_object->assign("previouspage", $prev);
$template_object->assign("totalpages", $totalpages);
$template_object->assign("totalshouts", $totalshouts);

$query = "SELECT * FROM {$db_prefix}shoutbox WHERE sb_alli = 0 ORDER BY sb_date desc ";
$res1 = $db->SelectLimit($query, $entries_per_page, $start);

$publicavatar = array();
$playernamea = array();
$datea = array();
$messagea = array();

while (!$res1->EOF)
{
	$row1 = $res1->fields;
	$result = $db->SelectLimit("SELECT avatar FROM {$db_prefix}players WHERE player_id=$row1[player_id]", 1);
	$avatar = $result->fields;
	$publicavatar[] = "avatars/".$avatar['avatar'];
	$playernamea[] = $row1['player_name'];
	$datea[] = date("m/d/Y G:i",$row1['sb_date']);
	$messagea[] = add_smilies(stripslashes(stripslashes(rawurldecode($row1['sb_text']))));
	$res1->MoveNext();
}

$template_object->assign("l_submit", $l_submit);
$template_object->assign("l_shout_prev", $l_shout_prev);
$template_object->assign("l_shout_next", $l_shout_next);
$template_object->assign("l_shout_selectpage", $l_shout_selectpage);
$template_object->assign("l_shout_page", $l_shout_page);

$template_object->assign("publicavatar", $publicavatar);
$template_object->assign("playernamea", $playernamea);
$template_object->assign("datea", $datea);
$template_object->assign("messagea", $messagea);
$template_object->assign("template", $playerinfo['template']);
$template_object->assign("l_shout_smiles", $l_shout_smiles);
$template_object->assign("l_shout_else", $l_shout_else);
$template_object->assign("l_shout_refresh", $l_shout_refresh);
$template_object->assign("l_shout_close", $l_shout_close);
$template_object->assign("color_header", $color_header);
$template_object->assign("l_shout_public", $l_shout_public);
$template_object->assign("l_shout_team", $l_shout_team);
$template_object->assign("l_shout_title2", $l_shout_title2);
$template_object->assign("l_global_mmenu", $l_global_mmenu);
$template_object->display($templatename."shoutbox.tpl");

include ("footer.php");
?>
