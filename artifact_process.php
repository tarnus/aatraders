<?php
// Galaxy
//
// The second line MUST be the name of the command that is to be shown in the command list.
//
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: artifact_process.php

include ("config/config.php");
include("languages/$langdir/lang_artifacts.inc");
get_post_ifset("artifact, process_type");
$template_object->enable_gzip = 0;

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
$template_object->assign("templatename", $templatename);
$template_object->assign("title", $l_artifact_title);

if(!class_exists($artifact)){
	include ("class/artifacts/" . $artifact . ".inc");
}
$artifacts_object = new $artifact();

if($process_type == "post")
{
	echo $artifacts_object->postprocess_artifact($artifact);
}
else
{
	echo $artifacts_object->preprocess_artifact($artifact);
}

include ("footer.php");
?> 

