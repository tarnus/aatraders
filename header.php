<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: header.php

if (preg_match("/header.php/i", $_SERVER['PHP_SELF']))
{
	echo "You can not access this file directly!";
	die();
}

get_post_ifset("no_body");

// Defines to avoid warnings
if ((!isset($no_body)) || ($no_body == ''))
{
	$no_body = '';
}

$banner_top = "";
$lines = @file ("config/banner_top.inc");
for($i=0; $i<count($lines); $i++){
	$banner_top .= $lines[$i];
}

$lines = file ("templates/" . $templatename . "base_template_list.inc");
for($i = 0; $i < count($lines); $i++){
	$lines[$i] = trim($lines[$i]);
	if($lines[$i] != "done"){
		$base_template[$lines[$i]] = 1;
	}
	else
	{
		break;
	}
}

function insert_img($params, &$tpl) {

	$class = (isset($params['class']) ? " class=\"iehax " . $params['class'] . "\" " : " class=\"iehax\" ");
	$id    = (isset($params['id']) ? " id=\"" . $params['id'] . "\" " : "");
	$style = (isset($params['style']) ? " style=\"" . $params['style'] . "\" " : " ");
	$border = (isset($params['border']) ? $params['border'] : 0);
	$alt = (isset($params['alt']) ? $params['alt'] : "image");

	static $firsttime = 0;

	$str = '';
	if($firsttime == 0)
	{
		$firsttime = 1;
		$str = '
<style type="text/css">
<!--
	span.iehax { display: none; }
	img.iehaxblank { display: none; }
-->
</style>
<!--[if IE]>
	<style type="text/css">
	<!--
		img.iehaxblank { display: inline ! important }
		img.iehaximg { display: none ! important }
	-->
	</style>
<![endif]-->
		';
	}

	$str .= '
<!--[if IE]>
	<span ' . $id . $class . '
		style="height: ' . $params['height'] . 'px; 
			width: ' . $params['width'] . 'px; 
			filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(src=\'' .
				$params['src'] . '\',sizingMethod=\'scale\'); 
			display:inline; position:absolute; ">
	</span>
<![endif]-->
<img class="iehaxblank" width="' . $params['width'] . '" height="' . $params['height'] . '" 
	src="images/spacer.gif" alt="."  border="' . $border . '"/>
<img class="iehaximg" src="' . $params['src'] . '" alt="' . $params['alt'] . '" 
	width="' . $params['width'] . '" height="' . $params['height'] . '" border="' . $border . '"/>';

    return $str;
}

$currentprogram = basename($_SERVER['PHP_SELF']);
$currentprogram = str_replace(".php", ".inc", $currentprogram);
$template_object->assign("currentprogram", $currentprogram);
$template_object->assign("game_charset", $game_charset);

$template_object->assign("banner_top", $banner_top);
$template_object->assign("templatename", $templatename);
$template_object->assign("full_url", "http://" . $gameurl . $gamepath . ($gamepath == "/" ? "" : "/") );

$template_object->assign("player_id", $playerinfo['player_id']);
$template_object->assign("gameroot", $gameroot);
$template_object->assign("spiral_arm", $sectorinfo['spiral_arm']);
$template_object->assign("style_sheet_file", "templates/".$templatename."style.css");
$template_object->assign("Title", $title);
$template_object->assign("no_body", $no_body);
$template_object->send_now = 1 - $template_object->enable_gzip;
//$template_object->send_now = 1;
$template_object->display($templatename."header.tpl");

?>
