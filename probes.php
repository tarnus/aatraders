<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: probes.php

include ("config/config.php");
include ("languages/$langdir/lang_probes.inc");
include ("languages/$langdir/lang_planets.inc");
include ("globals/get_shipclassname.inc");
include ("globals/get_player.inc");

get_post_ifset("command, by, by1, by2, by3, dismiss, probe_id");

$title = $l_probe_title;

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if (checklogin() or $tournament_setup_access == 1 || $allow_probes == 0)
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

switch ($command)
{
	case "drop": //drop probe
		$res = $db->SelectLimit("SELECT {$db_prefix}universe.zone_id, {$db_prefix}zones.allow_planet, {$db_prefix}zones.team_zone, " .
							"{$db_prefix}zones.owner FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
							"{$db_prefix}zones.zone_id=$sectorinfo[zone_id] AND {$db_prefix}universe.sector_id = $shipinfo[sector_id]", 1);
		$query97 = $res->fields;

		if($probe_id == "" || empty($probe_id))
		{
			$debug_query = $db->SelectLimit("SELECT probe_id from {$db_prefix}probe WHERE owner_id = $playerinfo[player_id] AND ship_id = $shipinfo[ship_id] and active='P'", 1);
			db_op_result($debug_query,__LINE__,__FILE__);

			$probe_id = $debug_query->fields['probe_id'];
			if($debug_query->RecordCount() == 0)
			{
				close_database();
				echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
				die();
			}
		}

		if($probe_id == "" || empty($probe_id))
		{
			close_database();
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			die();
		}

		if ($query97['allow_planet'] == 'N')
		{
			include ("header.php");
			$template_object->assign("title", $title);
			$template_object->assign("error_msg", $l_probe_forbid);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."genericdie.tpl");
			include ("footer.php");
			die();
		}
		elseif ($query97['allow_planet'] == 'L')
		{
			if ($query97['team_zone'] == 'N')
			{
				$res = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$query97[owner]", 1);
				$ownerinfo = $res->fields;
				if ($ownerinfo['team'] != $playerinfo['team'])
				{
					include ("header.php");
					$template_object->assign("title", $title);
					$template_object->assign("error_msg", $l_probe_forbid);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genericdie.tpl");
					include ("footer.php");
					die();
				}
				else
				{
					$query1 ="update {$db_prefix}probe set active='Y', sector_id=$shipinfo[sector_id] where probe_id=$probe_id";
					$debug_query = $db->Execute($query1);
					db_op_result($debug_query,__LINE__,__FILE__);
					header("location: main.php\r\n");
					die();
				}
			}
			else
			{
				$query1 ="update {$db_prefix}probe set active='Y', sector_id=$shipinfo[sector_id] where probe_id=$probe_id";
				$debug_query = $db->Execute($query1);
				db_op_result($debug_query,__LINE__,__FILE__);
				header("location: main.php\r\n");
				die();
			}
		}
		else
		{
			$query1 ="update {$db_prefix}probe set active='Y', sector_id=$shipinfo[sector_id] where probe_id=$probe_id";
			$debug_query = $db->Execute($query1);
			db_op_result($debug_query,__LINE__,__FILE__);
			header("location: main.php\r\n");
			die();
		}
	break;

	case "detect":   //DETECTED data
		$debug_query = $db->SelectLimit("SELECT owner_id from {$db_prefix}probe WHERE probe_id = $probe_id", 1);
		db_op_result($debug_query,__LINE__,__FILE__);

		$owner_id = $debug_query->fields['owner_id'];

		if($owner_id != $playerinfo['player_id'])
		{
			close_database();
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			die();
		}

		include ("header.php");
		$template_object->assign("title", $title);
		include ("globals/probe_detect.inc");
		$probe_detect = probe_detect( $probe_id );

		$template_object->assign("l_probe_scan", $probe_detect['sectorlink']);
		$template_object->assign("warplinks", $probe_detect['warplinks']);
		$template_object->assign("lastship", $probe_detect['lastship']);
		$template_object->assign("portinfo", $probe_detect['portinfo']);
		$template_object->assign("sector_def", $probe_detect['sector_def']);
		$template_object->assign("shipdetect", $probe_detect['shipdetect']);
		$template_object->assign("planetinfo", $probe_detect['planetinfo']);
		$template_object->assign("nothing_detected", (empty($probe_detect['warplinks']) && empty($probe_detect['lastship']) && empty($probe_detect['portinfo']) && empty($probe_detect['sector_def']) && empty($probe_detect['shipdetect']) && empty($probe_detect['planetinfo'])) ? 1 : 0);
		$template_object->assign("l_probe2_nothing", $l_probe2_nothing);

		$template_object->assign("l_probe_linkback", $l_probe_linkback);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."probes/probes_detect.tpl");
	break;

	default:
		include ("header.php");
		$template_object->assign("title", $title);
		$template_object->assign("l_probe_defaulttitle1", $l_probe_defaulttitle1);
		$template_object->assign("l_probe_defaulttitle2", $l_probe_defaulttitle2);
		$template_object->assign("l_probe_codenumber", $l_probe_codenumber);
		$template_object->assign("l_probe_type", $l_probe_type);
		$template_object->assign("l_probe_sector", $l_probe_sector);
		$template_object->assign("l_probe_tsector", $l_probe_tsector);
		$template_object->assign("l_probe_engine", $l_probe_engine);
		$template_object->assign("l_probe_sensors", $l_probe_sensors);
		$template_object->assign("l_probe_cloak", $l_probe_cloak);
		$template_object->assign("l_probe_detect", $l_probe_detect);

		$l_probe_typen = array();
		$probe_object = array();
		$filelist = get_dirlist($gameroot."class/probes/");
		for ($c=0; $c<count($filelist); $c++) {
			if($filelist[$c] != "index.html")
			{
				$probename =  str_replace(".inc", "", $filelist[$c]); 
				if(!class_exists($probename)){
					include ("class/probes/" . $probename . ".inc");
				}
				$probeobject = new $probename();
				$type = $probeobject->type;
				$l_probe_typen[$type] = $probeobject->l_probe_type;
				$probe_object[$type] = $probeobject;
			}
		}

		if ($by1 == 'sector')   $by11 = "sector_id asc";
		elseif ($by1 == 'tsector')   $by11 = "sector_id asc";
		elseif ($by1 == 'engines')   $by11 = "engines asc";
		elseif ($by1 == 'sensors')   $by11 = "sensors asc";
		elseif ($by1 == 'cloak')   $by11 = "cloak asc";
		elseif ($by1 == 'move_type')   $by11 = "type asc, probe_id asc";
		else						  $by11 = "probe_id asc";

		$line_color = "#23244F";
		$res = $db->Execute("SELECT * from {$db_prefix}probe where owner_id=$playerinfo[player_id] and active='Y' ORDER BY $by11");

		$probe_id = array();
		$probe_type = array();
		$probe_current_sector = array();
		$probe_target_sector = array();
		$probe_sensors = array();
		$probe_engines = array();
		$probe_cloak = array();
		$probe_display = array();

		if ($res->RecordCount())
		{
			while (!$res->EOF)
			{
				$probe = $res->fields;

  				if ($probe['target_sector']==0 && $probe['target_sector']==0)
  				{
					$probe['target_sector']=$probe['sector_id'];
				}

				$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probe['sector_id'], 1);
				db_op_result($resx,__LINE__,__FILE__);
				$start_sector = $resx->fields['sector_name'];
				$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probe['target_sector'], 1);
				db_op_result($resx,__LINE__,__FILE__);
				$target_sector = $resx->fields['sector_name'];

				$probe_id[] = $probe['probe_id'];
				$probe_type[] = $l_probe_typen[$probe['type']];
				$probe_current_sector[] = $start_sector;
				$probe_target_sector[] = $target_sector;
				$probe_engines[] = $probe['engines'];
				$probe_sensors[] = $probe['sensors'];
				$probe_cloak[] = $probe['cloak'];
				$probe_display[] = $probe_object[$probe['type']]->probe_display_code($probe['data']);
				$res->MoveNext();
			}
		}

		$template_object->assign("probe_id", $probe_id);
		$template_object->assign("probe_type", $probe_type);
		$template_object->assign("probe_current_sector", $probe_current_sector);
		$template_object->assign("probe_target_sector", $probe_target_sector);
		$template_object->assign("probe_engines", $probe_engines);
		$template_object->assign("probe_sensors", $probe_sensors);
		$template_object->assign("probe_cloak", $probe_cloak);
		$template_object->assign("probe_display", $probe_display);

		$template_object->assign("l_probe_view", $l_probe_view);
		$template_object->assign("l_probe_no1", $l_probe_no1);
		$template_object->assign("probes_in_space", $res->RecordCount());

		$ship_probe_id = array();
		$ship_probe_type = array();
		$ship_probe_sensors = array();
		$ship_probe_engines = array();
		$ship_probe_cloak = array();

		$res = $db->Execute("SELECT * from {$db_prefix}probe where owner_id=$playerinfo[player_id] and active='P' ORDER BY $by11");
		if ($res->RecordCount())
		{
			while (!$res->EOF)
			{
				$probe = $res->fields;
				$ship_probe_id[] = $probe['probe_id'];
				$ship_probe_type[] = $l_probe_typen[$probe['type']];
				$ship_probe_engines[] = $probe['engines'];
				$ship_probe_sensors[] = $probe['sensors'];
				$ship_probe_cloak[] = $probe['cloak'];
				$res->MoveNext();
			}
		}

		$template_object->assign("ship_probe_id", $ship_probe_id);
		$template_object->assign("ship_probe_type", $ship_probe_type);
		$template_object->assign("ship_probe_engines", $ship_probe_engines);
		$template_object->assign("ship_probe_sensors", $ship_probe_sensors);
		$template_object->assign("ship_probe_cloak", $ship_probe_cloak);
		$template_object->assign("l_probe_launch", $l_probe_launch);

		$template_object->assign("l_probe_no2", $l_probe_no2);
		$template_object->assign("probes_in_ship", $res->RecordCount());

		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."probes/probes_listing.tpl");

	break;
}

include ("footer.php");
?>
