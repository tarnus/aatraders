<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: options.php

include ("config/config.php");
include ("languages/$langdir/lang_options.inc");
include ("globals/RecurseDir.inc");

get_post_ifset("i");

$title = $l_opt_title;

if ((!isset($i)) || ($i == ''))
{
	$i = 0;
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

$dirlist=RecurseDir($gameroot."languages"); 
chdir($gameroot);

$login_drop_down = '';
$i = 0;

foreach ($dirlist as $key=>$val) { 
	$temp = str_replace($gameroot."languages/", "", $val);
	$languages = explode("/", $temp);

	if(is_file($gameroot."languages/" . $languages[0] . "/about_language.txt")){
		$languagesdir[$templatecount] = $languages[0];
		$languagesdata = file("languages/" . $languages[0] . "/about_language.txt");
		$avail_lang[$i]['name'] = $languagesdata[0];
		$avail_lang[$i]['value'] = $languages[0];
		$i++;
	}
}

$maxval = count($avail_lang);
for ($i=0; $i<$maxval; $i++)
{
	if ($avail_lang[$i]['value'] == $langdir)
	{
		$selected = " selected";
	}
	else
	{
		$selected = "";
	}
	$lang_drop_down = $lang_drop_down . "<option value=\"" . $avail_lang[$i]['value'] . "\"$selected>" . $avail_lang[$i]['name'] . "</option>\n";
}

$template_drop_down = '';
$dirlist=RecurseDir($gameroot."templates"); 
chdir($gameroot);
$templatecount = 0;
$authorarray = "";
$emailarray = "";
$websitearray = "";
$descriptionarray = "";
$picturearray = "";
$picturesmallarray = "";

foreach ($dirlist as $key=>$val) { 
	$temp = str_replace($gameroot."templates/", "", $val);
	$template = explode("/", $temp);

	if(is_file($gameroot."templates/" . $template[0] . "/about_template.inc")){
		$templatedir[$templatecount] = $template[0];

		$templatedata = file("templates/" . $template[0] . "/about_template.inc");
		$variable = explode("=", $templatedata[0], 2);
		$templatefullname[$templatecount] = str_replace("\"", "", trim($variable[1]));
		$variable = explode("=", $templatedata[1], 2);
		$templateauthor[$templatecount] = str_replace("\"", "", trim($variable[1]));
		$variable = explode("=", $templatedata[2], 2);
		$templateemail[$templatecount] = str_replace("\"", "", trim($variable[1]));
		$variable = explode("=", $templatedata[3], 2);
		$templatewebsite[$templatecount] = str_replace("\"", "", trim($variable[1]));
		$variable = explode("=", $templatedata[4], 2);
		$templatedescription[$templatecount] = str_replace("\"", "", trim($variable[1]));

		$templatepicturesmall[$templatecount] = "templates/" . $template[0] . "/about_picture_small.gif";
		$templatepicture[$templatecount] = "templates/" . $template[0] . "/about_picture.gif";

		$authorarray .= "author[$templatecount] = '" . addslashes($templateauthor[$templatecount]) . "';\n";
		$emailarray .= "email[$templatecount] = '" . $templateemail[$templatecount] . "';\n";
		$websitearray .= "website[$templatecount] = '" . $templatewebsite[$templatecount] . "';\n";
		$descriptionarray .= "descriptions[$templatecount] = '" . addslashes($templatedescription[$templatecount]) . "';\n";
		$picturearray .= "pictures[$templatecount] = '" . $templatepicture[$templatecount] . "';\n";
		$picturesmallarray .= "picturessmall[$templatecount] = '" . $templatepicturesmall[$templatecount] . "';\n";

		if($playerinfo['template'] == $template[0]."/")
		{
			$selected = "selected";
			$template_author = $templateauthor[$templatecount];
			$template_email = $templateemail[$templatecount];
			$template_website = $templatewebsite[$templatecount];
			$template_description = $templatedescription[$templatecount];
			$template_picturesmall = $templatepicturesmall[$templatecount];
			$template_picture = $templatepicture[$templatecount];
		}
		else
		{
			$selected = "";
		}

		$template_drop_down = $template_drop_down . "<option value=\"" . $templatedir[$templatecount] . "\" $selected>" . $templatefullname[$templatecount] . "</option>\n";
		$templatecount++;
	} 
}

$template_object->assign("authorarray", $authorarray);
$template_object->assign("emailarray", $emailarray);
$template_object->assign("websitearray", $websitearray);
$template_object->assign("descriptionarray", $descriptionarray);
$template_object->assign("picturearray", $picturearray);
$template_object->assign("picturesmallarray", $picturesmallarray);


$template_object->assign("templatedir", $templatedir);
$template_object->assign("templatepicture", $templatepicture);
$template_object->assign("templatepicturesmall", $templatepicturesmall);
$template_object->assign("templatefullname", $templatefullname);
$template_object->assign("templateauthor", $templateauthor);
$template_object->assign("templateemail", $templateemail);
$template_object->assign("templatewebsite", $templatewebsite);
$template_object->assign("templatedescription", $templatedescription);
$template_object->assign("templatecount", $templatecount);

$template_object->assign("template_author", $template_author);
$template_object->assign("template_email", $template_email);
$template_object->assign("template_website", $template_website);
$template_object->assign("template_description", $template_description);
$template_object->assign("template_picture", $template_picture);
$template_object->assign("template_picturesmall", $template_picturesmall);

$showteamicon = 1;

if($playerinfo['team'] == 0){
	$showteamicon = 0;
}

$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
$teamstuff = $result_team->fields;

if($teamstuff['id'] != $playerinfo['player_id']){
	$showteamicon = 0;
}

if ((isset($playerinfo['profile_name'])) && ($playerinfo['profile_name'] != ''))
{
	$registeredprofile = 1;
}
else
{
	$registeredprofile = 0;
}

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$planet_drop_down = "<option value=\"0\">$l_none</option>\n";

$res = $db->Execute("SELECT {$db_prefix}planets.planet_id, {$db_prefix}planets.name, {$db_prefix}universe.sector_name FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.owner=$playerinfo[player_id] and {$db_prefix}universe.sector_id={$db_prefix}planets.sector_id ORDER BY name");
db_op_result($res,__LINE__,__FILE__);
while (!$res->EOF)
{
	$row = $res->fields;
	if ($row['name'] == "")
	{
		$row['name'] = "Unnamed";
	}

	if ($row['planet_id'] == $playerinfo['home_planet_id'])
	{
		$selected = " selected";
	}
	else
	{
		$selected = "";
	}

	$planet_drop_down = $planet_drop_down . "<option value=\"" . $row['planet_id'] . "\"$selected>" . $row['name'] . " ($row[sector_name])" . "</option>\n";
	$res->MoveNext();
}
$template_object->assign("planet_drop_down", $planet_drop_down);

$home_planet_query = $db->SelectLimit("SELECT name from {$db_prefix}planets WHERE sector_id=$playerinfo[home_planet_id]", 1);
db_op_result($home_planet_query,__LINE__,__FILE__);
$template_object->assign("home_planet_name", ($home_planet_query->fields['name'] == "") ? $l_none : $home_planet_query->fields['name']);

$template_object->assign("title", $title);
$template_object->assign("l_home_planet", $l_home_planet);
$template_object->assign("enable_profilesupport", $enable_profilesupport);
$template_object->assign("l_here", $l_here);
$template_object->assign("l_opt_profiletitle", $l_opt_profiletitle);
$template_object->assign("l_opt_profile", $l_opt_profile);
$template_object->assign("l_opt_profilereg", $l_opt_profilereg);
$template_object->assign("l_opt_profilerereg", $l_opt_profilerereg);
$template_object->assign("registeredprofile", $registeredprofile);
$template_object->assign("l_opt_mapwidth", $l_opt_mapwidth);
$template_object->assign("map_width", $playerinfo['map_width']);
$template_object->assign("oldshipname", $shipinfo['name']);
$template_object->assign("l_opt_shipname", $l_opt_shipname);
$template_object->assign("allow_shipnamechange", $allow_shipnamechange);
$template_object->assign("teamicon", $teamstuff['icon']);
$template_object->assign("l_opt_teamicon", $l_opt_teamicon);
$template_object->assign("showteamicon", $showteamicon);
$template_object->assign("l_avatar", $l_avatar);
$template_object->assign("l_set", $l_set);
$template_object->assign("allow_avatar", $playerinfo['allow_avatar']);
$template_object->assign("avatar", $playerinfo['avatar']);
$template_object->assign("l_opt_chpass", $l_opt_chpass);
$template_object->assign("l_opt_curpass", $l_opt_curpass);
$template_object->assign("l_opt_newpass", $l_opt_newpass);
$template_object->assign("l_opt_newpagain", $l_opt_newpagain);
$template_object->assign("l_opt_usenew", $l_opt_usenew);
$template_object->assign("l_opt_lang", $l_opt_lang);
$template_object->assign("l_opt_select", $l_opt_select);
$template_object->assign("l_opt_template", $l_opt_template);
$template_object->assign("lang_drop_down", $lang_drop_down);
$template_object->assign("template_drop_down", $template_drop_down);
$template_object->assign("l_opt_enabled", $l_opt_enabled);
$template_object->assign("l_opt_save", $l_opt_save);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->assign("show_shoutbox", $playerinfo['show_shoutbox']);
$template_object->assign("show_newscrawl", $playerinfo['show_newscrawl']);
$template_object->assign("l_opt_showshoutbox", $l_opt_showshoutbox);
$template_object->assign("l_opt_shownewscrawl", $l_opt_shownewscrawl);
$template_object->assign("l_opt_profileupdate", $l_opt_profileupdate);
$template_object->assign("l_opt_profileupdate2", $l_opt_profileupdate2);
$template_object->assign("l_yes", $l_yes);
$template_object->assign("l_no", $l_no);
$template_object->assign("l_opt_playername", $l_opt_playername);
$template_object->assign("playername", $playerinfo['character_name']);
$template_object->assign("l_opt_playernamecost", str_replace("[amount]", NUMBER(ROUND($playerinfo['score'] * $playerinfo['score'] * $namechange_fee_adjustment)), $l_opt_playernamecost));

$template_object->assign("is_newuserpopup", 0);
if(is_file($gameroot.'support/newuserpopup.inc') && $playerinfo['turns_used'] == 0)
{
	if(filesize($gameroot.'support/newuserpopup.inc') > 0)
	{
		$lines = @file ($gameroot.'support/newuserpopup.inc');
		$newuserpopup = "";
		for($i=0; $i < count($lines); $i++)
		{
			$newuserpopup .= $lines[$i];
		}
		$template_object->assign("newuserpopup", $newuserpopup);
		$template_object->assign("is_newuserpopup", 1);
	}
}

$template_object->display($templatename."options.tpl");

include ("footer.php");
?>
