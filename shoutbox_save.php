<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: shoutbox2.php

include ("config/config.php");

include ("languages/$langdir/lang_shoutbox.inc");
include ("globals/clean_words.inc");

get_post_ifset("sbt, SBPB, returntomain");

if (checklogin())
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

function filter_test($test_var){
	$filter="MIME-Version: 1.0|multipart/mixed|This is a multi-part message|Content-Type|MIME format|[url|http://|.com|.org|.net|.biz|.tv|.gov|.us|www.";
	$list_item=explode("|",$filter);
	$list_count=count($list_item);
	$badcount=0;
	for ($x=0;$x < $list_count;$x++){
		if (strstr($test_var,$list_item[$x])){
			$badcount++;
		}		
		
	}
	
	if ($badcount > 0 || AAT_substr_count($test_var, 'http://') > 1)
	{
		return true;
	}else{
		return false;
	}
}

// Add Shout only if not empty !
if (trim($sbt) != "")
{
	$result = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$playerinfo[player_id]", 1);
	db_op_result($result,__LINE__,__FILE__);
	$playerinfo = $result->fields;

	$sbt = htmlspecialchars(clean_words($sbt));

	// Check Team shout or public
	$sb_alli = (($playerinfo['team']<=0) ? -1 : $playerinfo['team']);

	$shoutbox_return = "shoutbox_team.php";
	if (!empty($SBPB))
	{
		$sb_alli = 0;
		$shoutbox_return = "shoutbox.php";
	}

	if($returntomain == 1)
	{
		$shoutbox_return = "main.php";
	}

	// Check double post!
	$result = $db->SelectLimit("SELECT * FROM {$db_prefix}shoutbox ORDER BY sb_date DESC", 1);
	db_op_result($result,__LINE__,__FILE__);
	$lastshout = $result->fields;
	if ($lastshout['sb_text'] == $sbt)
	{
		$sbt = "";
	}

	if (filter_test($sbt))
	{
		$sbt = "";
	}

	// Add Shout only if not empty !
	if (trim($sbt) != "" && $playerinfo['shoutbox_ban'] == 0)
	{
		$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES ($playerinfo[player_id]," . $db->qstr($playerinfo['character_name']) . "," . time() . ", " . $db->qstr($sbt) . ", $sb_alli) ");
		db_op_result($res,__LINE__,__FILE__);
	}
}

echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
		<html>
			<head>
					<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=$shoutbox_return\">
				<title>Navcomp</title>
			</head>
			<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
			</body>
		</html>";
?>
