<?php
include ("config/config.php");
include ("languages/$langdir/lang_beacon.inc");
include ("globals/clean_words.inc");

get_post_ifset("beacon_text");

$title = $l_beacon_title;

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

$allowed_rsw = "N";

if ($shipdevice['dev_beacon']['amount'] > 0)
{
	$res = $db->SelectLimit("SELECT allow_beacon FROM {$db_prefix}zones WHERE zone_id='$sectorinfo[zone_id]'", 1);
	$zoneinfo = $res->fields;
	if ($zoneinfo['allow_beacon'] == 'N')
	{
		$template_object->assign("error_msg", $l_beacon_notpermitted);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."beaconsdie.tpl");
		include ("footer.php");
		die();
	}
	elseif ($zoneinfo['allow_beacon'] == 'L')
	{
		$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id='$sectorinfo[zone_id]'", 1);
		$zoneowner_info = $result3->fields;

		$result5 = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id='$zoneowner_info[owner]'", 1);
		$zoneteam = $result5->fields;

		if ($zoneowner_info[owner] != $playerinfo[player_id])
		{
			if (($zoneteam[team] != $playerinfo[team]) || ($playerinfo[team] == 0))
			{
				$template_object->assign("error_msg", $l_beacon_notpermitted);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."beaconsdie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$allowed_rsw = "Y";
			}
		}
		else
		{
			$allowed_rsw = "Y";
		}
	}
	else
	{
		$allowed_rsw = "Y";
	}

	if ($allowed_rsw == "Y")
	{
		if ((!isset($beacon_text)) || ($beacon_text == ''))
		{
			if ($sectorinfo['beacon'] != "")
			{
				$template_object->assign("beacon_info", "$l_beacon_reads: \"$sectorinfo[beacon]\"");
			}
			else
			{
				$template_object->assign("beacon_info", $l_beacon_none);
			}

			$template_object->assign("l_beacon_enter", $l_beacon_enter);
			$template_object->assign("l_submit", $l_submit);
			$template_object->assign("l_reset", $l_reset);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."beacons.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			$beacon_text = clean_words(trim(strip_tags($beacon_text)));
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET beacon=" . $db->qstr($beacon_text) . " WHERE sector_id=$sectorinfo[sector_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_beacon']['device_id']);
			db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("error_msg", "$l_beacon_nowreads: \"$beacon_text\".");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."beaconsdie.tpl");
			include ("footer.php");
			die();
		}
	}
}
else
{
	$template_object->assign("error_msg", $l_beacon_donthave);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."beaconsdie.tpl");
	include ("footer.php");
	die();
}

close_database();
?>
