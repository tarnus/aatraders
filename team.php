<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: team.php

include ("config/config.php");
include ("languages/$langdir/lang_team.inc");
include ("globals/calc_ownership.inc");

get_post_ifset("planet_id, action");

$title = $l_teamm_title;

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
	base_template_data();
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$planet_id = stripnum($planet_id);

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$planet_id and owner=$playerinfo[player_id]", 1);
if ($result2)
{
	$planetinfo=$result2->fields;

	if ($planetinfo['owner'] == $playerinfo['player_id'] && $playerinfo['team'] > 0)
	{
		if ($action == "planetteam")
		{
			$template_object->assign("error_msg", $l_teamm_toteam);
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team='$playerinfo[team]' WHERE planet_id=$planet_id");
			db_op_result($debug_query,__LINE__,__FILE__);
			$ownership = calc_ownership($shipinfo['sector_id']);
		}
		if ($action == "planetpersonal" && $planetinfo['team'] == $playerinfo['team'])
		{
			$template_object->assign("error_msg", $l_teamm_topersonal);
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team='0' WHERE planet_id=$planet_id");
			db_op_result($debug_query,__LINE__,__FILE__);

			$ownership = calc_ownership($shipinfo['sector_id']);

			// Kick other players off the planet
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet='N' WHERE on_planet='Y' AND planet_id = $planet_id AND player_id <> $playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		$template_object->assign("error_msg2", $ownership);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."team.tpl");
		include ("footer.php");
		die();
	}else{
		$template_object->assign("error_msg", $l_teamm_exploit);
		$template_object->assign("error_msg2", "");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."team.tpl");
		include ("footer.php");
		die();
	}
}else{
	$template_object->assign("error_msg", $l_teamm_exploit);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team.tpl");
	include ("footer.php");
	die();
}

close_database();
?>
