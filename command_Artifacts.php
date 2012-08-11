<?php
// Artifact List
//
// The second line MUST be the name of the command that is to be shown in the command list.
//
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: galaxy.php

include ("config/config.php");
include("languages/$langdir/lang_artifacts.inc");

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
$template_object->assign("title", $l_artifact_list_title);

$incomplete = array();
$classname = array();
$description = array();
$imagename = array();

$filelist = get_dirlist($gameroot."class/artifacts/");
sort($filelist);
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$artifacts_classname = str_replace(".inc", "", $filelist[$c]); 
		$result4 = $db->Execute(" SELECT count(artifact_id) total FROM {$db_prefix}artifacts where player_id=$playerinfo[player_id] and artifact_type='$artifacts_classname'");
		db_op_result($result4,__LINE__,__FILE__);
		$total = $result4->fields['total'];

		if(!class_exists($artifacts_classname)){
			include ("class/artifacts/" . $artifacts_classname . ".inc");
		}
		$artifacts_object = new $artifacts_classname();
		if($total >= $artifacts_object->pieces && $artifacts_object->delayedprocess == 0)
		{
			$total = 0;
			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $artifacts_classname . "'");
			db_op_result($res,__LINE__,__FILE__);
		}

		$scoremax = $artifacts_object->scoremax;
		if($scoremax == 0 || $playerinfo['score'] <= $scoremax)
		{
			$incompletework = $artifacts_object->incomplete;
			$singular = $artifacts_object->singular;
			$plural = $artifacts_object->plural;
			$pieces = $artifacts_object->pieces;
			$incompletework = str_replace("[pieces]", $total, $incompletework);
			$left = $pieces - $total;
			$incompletework = str_replace("[left]", $left, $incompletework);
			if($left == 1)
			{
				$incomplete[] = str_replace("[piece]", $singular, $incompletework);
			}
			else
			{
				$incomplete[] = str_replace("[piece]", $plural, $incompletework);
			}
			$classname[] = $artifacts_object->classname;
			$description[] = $artifacts_object->description;
			$imagename[] = $artifacts_classname;
			$delayedprocess[] = $artifacts_object->delayedprocess;
			$class[] = $artifacts_object->class;
			$completed[] = ($left <= 0) ? 1 : 0;
		}
		else
		{
			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $artifacts_classname . "'");
			db_op_result($res,__LINE__,__FILE__);
		}
	}
}

$template_object->assign("classname", $classname);
$template_object->assign("description", $description);
$template_object->assign("imagename", $imagename);
$template_object->assign("incomplete", $incomplete);
$template_object->assign("delayedprocess", $delayedprocess);
$template_object->assign("class", $class);
$template_object->assign("completed", $completed);

$template_object->assign("l_artifact_classname", $l_artifact_classname);
$template_object->assign("l_artifact_description", $l_artifact_description);
$template_object->assign("l_artifact_imagename", $l_artifact_imagename);
$template_object->assign("l_artifact_incomplete", $l_artifact_incomplete);
$template_object->assign("l_artifact_process", $l_artifact_process);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."artifact_list.tpl");

include ("footer.php");
?> 

