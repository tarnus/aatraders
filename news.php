<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: news.php

include ("config/config.php");
include ("languages/$langdir/lang_news.inc");
include ("globals/translate_news.inc");

get_post_ifset("startdate");

$title = $l_news_title;

$noreturn = 1;
$isonline = checklogin();

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if($isonline != 1){
	if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
		include ("globals/base_template_data.inc");
	}
	else
	{
		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);
	}
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}
//Check to see if the date was passed in the query string
if ((!isset($startdate)) || ($startdate == ''))
{
	//The date wasn't supplied so use today's date
	$startdate = date("Y-m-d");
}

$month = AAT_substr($startdate, 5, 2);
$day = AAT_substr($startdate, 8, 2);
$year = AAT_substr($startdate, 0, 4);
$today = mktime (0,0,0,$month,$day,$year);
$today = date($local_date_short_format, $today);
$previousday = date("Y-m-d",strtotime($startdate) - 86400);
$nextday = date("Y-m-d",strtotime($startdate) + 86400);

$template_object->assign("isonline", $isonline);
$template_object->assign("l_news_info", $l_news_info);
$template_object->assign("l_news_for", $l_news_for);
$template_object->assign("today", $today);
$template_object->assign("l_news_prev", $l_news_prev);
$template_object->assign("nextday", $nextday);
$template_object->assign("l_news_next", $l_news_next);
$template_object->assign("previousday", $previousday);

$template_object->assign("l_news_bestviewed", $l_news_bestviewed);
$template_object->assign("l_news_fedannouncements", $l_news_fedannouncements);
$template_object->assign("l_news_planetarynews", $l_news_planetarynews);
$template_object->assign("l_news_afteractionnews", $l_news_afteractionnews);
$template_object->assign("l_news_planetshipnews", $l_news_planetshipnews);

$newscount = 0;

//Select news for date range
$res = $db->Execute("SELECT * from {$db_prefix}news where LEFT(date,10) = '$startdate' order by news_id desc");

//Check to see if there was any news to be shown
if ($res->EOF && $res)
{
	//No news
	//Display link to the main page
	if (empty($_SESSION['session_player_id']) || $_SESSION['session_player_id'] == '')
	{
		$template_object->assign("gotomain", $l_global_mlogin);
	}
	else
	{
		$template_object->assign("gotomain", $l_global_mmenu);
	}
	
	$headline[$newscount] = $l_news_flash;
	$newstext[$newscount] = $l_news_none;
	$newstype[$newscount] = "general";
	$newsdate[$newscount] = date($local_date_full_format, strtotime($startdate));
	$newscount++;
	$headline[$newscount] = $l_news_flash;
	$newstext[$newscount] = $l_news_none;
	$newstype[$newscount] = "indi";
	$newsdate[$newscount] = date($local_date_full_format, strtotime($startdate));
	$newscount++;
	$headline[$newscount] = $l_news_flash;
	$newstext[$newscount] = $l_news_none;
	$newstype[$newscount] = "killedpod";
	$newsdate[$newscount] = date($local_date_full_format, strtotime($startdate));
	$newscount++;
	$headline[$newscount] = $l_news_flash;
	$newstext[$newscount] = $l_news_none;
	$newstype[$newscount] = "shipattack";
	$newsdate[$newscount] = date($local_date_full_format, strtotime($startdate));
	$newscount++;
	$template_object->assign("newscount", $newscount);
	$template_object->assign("headline", $headline);
	$template_object->assign("newstext", $newstext);
	$template_object->assign("newstype", $newstype);
	$template_object->assign("newsdate", $newsdate);
	$template_object->display($templatename."news.tpl");
	include ("footer.php");
	die();
}

$template_object->assign("dummyheadline", $l_news_flash);
$template_object->assign("dummynewstext", $l_news_none);
$template_object->assign("dummynewsdate", date($local_date_full_format, strtotime($startdate)));

while (!$res->EOF && $res)
{
	$row = $res->fields;
	$newsdata = translate_news($row);
	$headline[$newscount] = $newsdata['headline'];
	$newstext[$newscount] = $newsdata['newstext'];
	$newstype[$newscount] = $newsdata['newstype'];
	$newsdate[$newscount] = date($local_date_full_format, strtotime($row['date']));
	$newscount++;
	$res->MoveNext();
}

if (empty($_SESSION['session_player_id']) || $_SESSION['session_player_id'] == '')
{
	$template_object->assign("gotomain", $l_global_mlogin);
}
else
{
	$template_object->assign("gotomain", $l_global_mmenu);
}

$template_object->assign("newscount", $newscount);
$template_object->assign("headline", $headline);
$template_object->assign("newstext", $newstext);
$template_object->assign("newstype", $newstype);
$template_object->assign("newsdate", $newsdate);
$template_object->display($templatename."news.tpl");
include ("footer.php");
?>
