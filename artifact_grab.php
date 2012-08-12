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
// File: artifact_grab.php

include ("config/config.php");
include("languages/$langdir/lang_artifacts.inc");
get_post_ifset("artifact_id");

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

$result4 = $db->Execute(" SELECT * FROM {$db_prefix}artifacts where artifact_id=$artifact_id and sector_id=$shipinfo[sector_id]");
db_op_result($result4,__LINE__,__FILE__);

if ($result4->recordcount())
{
	$artifactinfo = $result4->fields;
	if ($playerinfo['turns'] < 1)
	{
		$template_object->assign("resultinfo", $l_artifact_noturn);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."artifact_grab.tpl");
		include ("footer.php");
		die();
	}

	if($artifactinfo['scoremax'] == 0 || $playerinfo['score'] < $artifactinfo['scoremax'])
	{
		$success = SCAN_SUCCESS($shipinfo['sensors'], $artifactinfo['cloak'], 1);

		$roll = mt_rand(1, 100);

		if ($roll >= $success)
		{
			$template_object->assign("resultinfo", $l_artifact_noscan);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."artifact_grab.tpl");
			include ("footer.php");
			die();
		}
	}

	if(!class_exists($artifactinfo['artifact_type'])){
		include ("class/artifacts/" . $artifactinfo['artifact_type'] . ".inc");
	}

	$artifacts_object = new $artifactinfo['artifact_type']();
	$resultinfo = $artifacts_object->found_artifact_piece($artifact_id);

	$template_object->assign("resultinfo", $resultinfo);
}
else
{
	$template_object->assign("resultinfo", $l_artifact_noscan);
}

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."artifact_grab.tpl");

include ("footer.php");
?> 

