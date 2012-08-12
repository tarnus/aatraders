<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: shoutbox_smilie.php

include ("config/config.php");

include ("languages/$langdir/lang_shoutbox.inc");

$title = $l_teamm_title;

if (checklogin())
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

function display_smilies()
{
		global $db, $db_prefix, $a, $image;
		$orig = $repl = array();

		$result = $db->Execute("SELECT * FROM {$db_prefix}smilies");
		$smilies = $result->GetArray();

		for ($i = 0; $i < count($smilies); $i++)
		{
			$a[] = $smilies[$i]['code'];
			$image[] = '<img src="images/smiles/' . $smilies[$i]['smile_image'] . '" alt="' . $smilies[$i]['emoticon'] . '" border="0" />';
		}

	return $message;
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

$a = array();
$image = array();
display_smilies();

$r = count($a);

$template_object->assign("count", $r);
$template_object->assign("l_shout_return", $l_shout_return);
$template_object->assign("l_shout_title", $l_shout_title);
$template_object->assign("l_shout_close", $l_shout_close);
$template_object->assign("smile_text", $a);
$template_object->assign("image", $image);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."shoutbox_smile.tpl");

include ("footer.php");

?>