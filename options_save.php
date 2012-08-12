<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: options_save.php

include ("config/config.php");
include ("languages/$langdir/lang_option2.inc");
include ("globals/clean_words.inc");
include ("globals/RecurseDir.inc");
include ("globals/ord_crypt_encode.inc");
include ("globals/ord_crypt_decode.inc");
include ("globals/insert_news.inc");

get_post_ifset("newhomeplanet, newpass1, newpass2, oldpass, newshipname, newlang, newtemplate, map_width, show_shoutbox, show_newscrawl, newplayername");

if (checklogin())
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$title = "$l_opt2_title";

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

//-------------------------------------------------------------------------------------------------

if (($newpass1 == $newpass2) && ($playerinfo['password'] == ord_crypt_encode($oldpass)) && ($newpass1 != ''))
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET password='" . ord_crypt_encode($newpass1) . "' WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

//	$userpass = $username."+".$newpass1;
//	$_SESSION['userpass'] = $userpass;
}

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

for ($i=0; $i < $maxval; $i++)
{
	if ($avail_lang[$i]['value'] == $newlang)
	{
		$langdir = $newlang;
		$_SESSION['langdir'] = $langdir;
		include ("languages/$langdir/lang_option2.inc");
		$l_opt2_chlang = str_replace("[lang]", $avail_lang[$i]['name'], $l_opt2_chlang);
		break;
	}
}

if(is_file($gameroot."templates/" . $newtemplate . "/about_template.inc")){
	$templatedata = file("templates/" . $newtemplate . "/about_template.inc");
	$variable = explode("=", $templatedata[0], 2);
	$templatefullname = str_replace("\"", "", trim($variable[1]));
}
else
{
	$templatefullname = $newtemplate;
}

if($playerinfo['template'] != $newtemplate)
{
	$_SESSION['template_changed'] = 1;
}

$l_opt2_chtemplate = str_replace("[template]", $templatefullname, $l_opt2_chtemplate);

$newtemplate .= "/";

include ("templates/" . $newtemplate . "about_template_options.inc");

if($map_width < 10)
	$map_width = 10;

if($map_width > 100)
	$map_width = 100;

$playerinfo['map_width'] = $map_width;

$changedplayername = "";
$changedplayernamefee = 0;

if (AAT_substr_count("guide", AAT_strtolower($newplayername)) == 0 && AAT_strtolower($newplayername) != AAT_strtolower($playerinfo['character_name']) && AAT_strtolower($newplayername) != "unowned" && AAT_strtolower($newplayername) != "unchartered" && AAT_strtolower($newplayername) != "uncharted") 
{
	$newplayername = preg_replace ("/[^\w\d\s\']/","",clean_words($newplayername));
	$newplayername = preg_replace ("/[^A-Za-z0-9\s\-\=\\\'\!\&\*\_]/","",trim($newplayername));
	$failnamechange = 0;

	if($newplayername == "")
	{
		$failnamechange = 1;
	}

	$result = $db->Execute ("SELECT character_name FROM {$db_prefix}players WHERE player_id!=$playerinfo[player_id]");
	if ($result>0)
	{
		while (!$result->EOF)
		{
			$row = $result->fields;
			if (AAT_strtolower($row['character_name']) == AAT_strtolower($newplayername)) 
			{ 
				$failnamechange = 1;
			}
			elseif (metaphone($row['character_name']) == metaphone($newplayername)) 
			{ 
				$failnamechange = 1;
			}
			$result->MoveNext();
		}
	}
	if($failnamechange == 0 && $playerinfo['credits'] >= ROUND($playerinfo['score'] * $playerinfo['score'] * $namechange_fee_adjustment))
	{
		$changedplayernamefee = ROUND($playerinfo['score'] * $playerinfo['score'] * $namechange_fee_adjustment);
		$changedplayername = "character_name = " . $db->qstr($newplayername) . " , ";
		$zone_name = $db->qstr($newplayername . "'s Territory");
		$debug_query2 = $db->Execute("UPDATE {$db_prefix}zones SET zone_name=$zone_name WHERE owner=$playerinfo[player_id] and team_zone='N'");
		db_op_result($debug_query2,__LINE__,__FILE__);
		$template_object->assign("l_opt2_playernamechanged", str_replace("[amount]", NUMBER($changedplayernamefee), str_replace("[name]", $newplayername, $l_opt2_playernamechanged)));
		insert_news("$playerinfo[character_name]|$newplayername", $playerinfo['player_id'], "namechange");
	}
}

$debug_query2 = $db->Execute("UPDATE {$db_prefix}players SET home_planet_id=$newhomeplanet, langdir='$langdir', credits=credits-$changedplayernamefee, $changedplayername map_width=$map_width, template='$newtemplate', show_shoutbox=$show_shoutbox, show_newscrawl=$show_newscrawl WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query2,__LINE__,__FILE__);

if($allow_shipnamechange == 1){
	$newshipname = preg_replace ("/[^\w\d\s\']/","",clean_words($newshipname));
	$newshipname = preg_replace ("/[^A-Za-z0-9\s\-\=\\\'\!\&\*\_]/","",trim($newshipname));

	if($newshipname == "")
	{
		$newshipname = $shipinfo['name'];
	}

	$result = $db->Execute ("SELECT name FROM {$db_prefix}ships WHERE player_id!=$playerinfo[player_id]");

	if ($result>0)
	{
		while (!$result->EOF)
		{
			$row = $result->fields;
			if (AAT_strtolower($row['name']) == AAT_strtolower($newshipname)) 
			{ 
				$newshipname = $shipinfo['name'];
			}
			elseif (metaphone($row['name']) == metaphone($newshipname)) 
			{ 
				$newshipname = $shipinfo['name'];
			}
			$result->MoveNext();
		}
	}

	if (AAT_strtolower($newshipname) == "unknown" || AAT_strtolower($newshipname) == "unowned" || AAT_strtolower($newshipname) == "unchartered" || AAT_strtolower($newshipname) == "uncharted") 
	{ 
		$newshipname = $shipinfo['name'];
	}
	else
	{
		$debug_query2 = $db->Execute("UPDATE {$db_prefix}ships SET name=" . $db->qstr($newshipname) . " WHERE player_id=$playerinfo[player_id] AND ship_id=$playerinfo[currentship]");
		db_op_result($debug_query2,__LINE__,__FILE__);
	}
}

//-------------------------------------------------------------------------------------------------

$home_planet_query = $db->SelectLimit("SELECT name from {$db_prefix}planets WHERE sector_id=$newhomeplanet", 1);
db_op_result($home_planet_query,__LINE__,__FILE__);
$template_object->assign("home_planet_name", ($home_planet_query->fields['name'] == "") ? $l_none : $home_planet_query->fields['name']);

$template_object->assign("title", $title);
$template_object->assign("l_home_planet", $l_home_planet);
$template_object->assign("l_opt2_mapwidth", $l_opt2_mapwidth);
$template_object->assign("map_width", $playerinfo['map_width']);
$template_object->assign("l_opt2_shipnamechanged", str_replace("[name]", $newshipname, $l_opt2_shipnamechanged));
$template_object->assign("allow_shipnamechange", $allow_shipnamechange);
$template_object->assign("password", ord_crypt_decode($playerinfo['password']));
$template_object->assign("newpass1", $newpass1);
$template_object->assign("newpass2", $newpass2);
$template_object->assign("l_opt2_passunchanged", $l_opt2_passunchanged);
$template_object->assign("l_opt2_newpassnomatch", $l_opt2_newpassnomatch);
$template_object->assign("oldpass", $oldpass);
$template_object->assign("l_opt2_srcpassfalse", $l_opt2_srcpassfalse);
$template_object->assign("debug_query", $debug_query);
$template_object->assign("l_opt2_passchanged", $l_opt2_passchanged);
$template_object->assign("l_opt2_passchangeerr", $l_opt2_passchangeerr);
$template_object->assign("l_opt2_chlang", $l_opt2_chlang);
$template_object->assign("l_opt2_chtemplate", $l_opt2_chtemplate);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."option2.tpl");

include ("footer.php");

?>
