<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: device.php

include ("config/config.php");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_device.inc");

$title = $l_device_title;

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

$template_object->assign("l_device_expl", $l_device_expl);
$template_object->assign("l_device", $l_device);
$template_object->assign("l_qty", $l_qty);
$template_object->assign("l_usage", $l_usage);
$template_object->assign("l_mines", $l_mines);
$template_object->assign("dev_torps", NUMBER($shipinfo['torps']));
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("dev_fighters", NUMBER($shipinfo['fighters']));

$devicename = array();
$deviceamount = array();
$deviceclass = array();
$deviceprogram = array();

$count = 0;
foreach ($shipdevice as $key => $data) 
{
	if($data['class'] == "dev_probes" && $allow_probes == 0)
	{
		//
	}
	else
	{
		$deviceprogram[$count] = $data['program'];
		$deviceclass[$count] = $data['class'];
		$devicename[$count] = $data['device_name'];
		$deviceamount[$count] = NUMBER($data['amount']);

		$device_type = $deviceclass[$count];
		if(!class_exists($device_type)){
			include ("class/devices/" . $device_type . ".inc");
		}
		$deviceobject = new $device_type();
		$deviceamount[$count] = $deviceobject->device_code();

		$count++;
	}
}

$template_object->assign("deviceprogram", $deviceprogram);
$template_object->assign("deviceclass", $deviceclass);
$template_object->assign("devicename", $devicename);
$template_object->assign("deviceamount", $deviceamount);

$template_object->assign("l_yes", $l_yes);
$template_object->assign("l_no", $l_no);
$template_object->assign("title", $title);
$template_object->assign("gotomain", $l_global_mmenu);

$template_object->display($templatename."device.tpl");

include ("footer.php");

?>
