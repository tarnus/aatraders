<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: galaxy_map.php

include ("config/config.php");
include ("languages/$langdir/lang_galaxy2.inc");

get_post_ifset("startsector");

$title = $l_map;

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

if (empty($startsector) || $startsector == '')
{
	$startsector = 1;
}

$endsector = $startsector + 1000;

$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
db_op_result($max_query,__LINE__,__FILE__);

$sector_max = $max_query->fields['sector_id'];

if($startsector == "-1"){
	$startsector = 1;
	$endsector = $sector_max;
	$allselected = "selected";
}

$result = $db->Execute ("SELECT sector_name, spiral_arm, sector_id, port_type, x, y, z, zone_id FROM {$db_prefix}universe where sector_id >= $startsector and sector_id <= $endsector and sg_sector = 0 ORDER BY sector_id ASC");

$porttypes[0] = 'unknown';
$porttypes[1] = 'none';
$porttypes[2] = 'upgrades';
$porttypes[3] = 'devices';
$porttypes[4] = 'spacedock';
$porttypes[5] = 'casino';

$typecount = 6;

$cargo_query = $db->Execute("SELECT classname from {$db_prefix}class_modules_commodities where cargoport=1 and cargosellbuy!=1 order by price");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$porttypes[$typecount] = $cargo_query->fields['classname'];
	$typecount++;
	$cargo_query->Movenext();
}

$template_object->assign("porttypes", $porttypes);
$template_object->assign("typecount", $typecount);

$pages = floor($sector_max / 1000);

$result2 = $db->Execute("SELECT distinct source, zone_id, warp_links, port_buys FROM {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] order by source ASC, time DESC");
while (!$result2->EOF) 
{
	$row2 = $result2->fields;
	$temp = $row2['source'];
	$sectorzone[$temp] = $row2['zone_id'];
	$sectorlist[$temp] = $row2['warp_links'];
	$port_buys[$temp] = $row2['port_buys'];
	$result2->Movenext();
}

$totalzones = 0;

$result4 = $db->Execute ("SELECT distinct zone_id, zone_color, zone_name, team_zone FROM {$db_prefix}zones, {$db_prefix}players WHERE {$db_prefix}zones.owner = {$db_prefix}players.player_id and {$db_prefix}players.destroyed != 'Y' and {$db_prefix}players.turns_used > 0 ORDER BY zone_name ASC");
while (!$result4->EOF) 
{
	$row4 = $result4->fields;
	$temp = $row4['zone_id'];
	$zoneinfo[$temp] = $row4['zone_color'];
	$zonename[$temp] = $row4['zone_name'];
	$zoneteam[$temp] = $row4['team_zone'];
	$zonenumber[$totalzones] = $temp;
	$totalzones++;
	$result4->Movenext();
}

$mapsectorcount = 0;

while (!$result->EOF)
{
	$row   = $result->fields;

	$tempsector = $row['sector_id'];

	if ($sectorzone[$tempsector] > 0 )
	{
		$sectorid[$mapsectorcount] = $row['sector_id'];
		$sectorname[$mapsectorcount] = rawurlencode($row['sector_name']);
		$position[$mapsectorcount]= $row['x']."|".$row['y']."|".$row['z'];
		$galacticarm[$mapsectorcount]= $row['spiral_arm'];

		$temp = $sectorzone[$tempsector];
		$link_list[$mapsectorcount] = empty($sectorlist[$tempsector]) ? $l_none : $sectorlist[$tempsector];
		$buy_list[$mapsectorcount] = empty($port_buys[$tempsector]) ? $l_none : str_replace("|", "<br>", $port_buys[$tempsector]);
		$zonecolor = $zoneinfo[$temp];
		$port = $row['port_type'];
		$alt  = "$row[sector_name] - $text[$port] - ". $zonename[$temp];
		$altsector[$mapsectorcount]  = $row['sector_name'];
		$altport[$mapsectorcount]  = $text[$port];
		$altzone[$mapsectorcount]  = addslashes(rawurldecode(str_replace("&#39;", "'", $zonename[$temp])));

		$sectorzonecolor[$mapsectorcount] = $zonecolor;
		$sectorimage[$mapsectorcount] = $port;
		$sectortitle[$mapsectorcount] = $alt;

		$result_sn = $db->SelectLimit("SELECT note_data FROM {$db_prefix}sector_notes WHERE note_sector_id=$row[sector_id] and note_player_id=$playerinfo[player_id] ORDER BY note_date DESC", 1);
		if(!$result_sn->EOF && $result_sn)
		{
			$notelistnote[$mapsectorcount] = addslashes(str_replace("\r", "", str_replace("\n", "<br>", rawurldecode("Personal: " . $result_sn->fields['note_data'] . "<br><br>"))));
		}
		else
		{
			$notelistnote[$mapsectorcount] = "";
		}

		if($playerinfo['team'] > 0){
			$result_sn = $db->SelectLimit("SELECT note_data FROM {$db_prefix}sector_notes WHERE note_sector_id=$row[sector_id] and note_team_id=$playerinfo[team] ORDER BY note_date DESC", 1);
			if(!$result_sn->EOF && $result_sn)
			{
				$teamnotelistnote[$mapsectorcount] = addslashes(str_replace("\r", "", str_replace("\n", "<br>", rawurldecode("Team: " . $result_sn->fields['note_data']))));
			}
			else
			{
				$teamnotelistnote[$mapsectorcount] = "";
			}
		}
		else
		{
			$teamnotelistnote[$mapsectorcount] = "";
		}

		$mapsectorcount++;
	}
	$result->Movenext();
}	


$temp = $zonenumber[0];
$teamzonecount = 1;
for($i = 0; $i <= $totalzones; $i++){
	$temp = $zonenumber[$i];
	if($zoneinfo[$temp] != "#000000" && $zoneteam[$temp] == "Y"){
		$namezone[$teamzonecount] = $zonename[$temp];
		$namezonecolor[$teamzonecount] = $zoneinfo[$temp];
		$teamzonecount++;
	}
}
$template_object->assign("namezone", $namezone);
$template_object->assign("namezonecolor", $namezonecolor);
$template_object->assign("teamzonecount", $teamzonecount);

$temp = $zonenumber[0];
$player_count = 2;
$playerzone[1] = $l_zname[1];
$playerzonecolor[1] = "#000000";
for($i = 0; $i <= $totalzones; $i++){
	$temp = $zonenumber[$i];
	if($zoneinfo[$temp] != "#000000" && $zoneteam[$temp] == "N"){
		$playerzone[$player_count] = $zonename[$temp];
		$playerzonecolor[$player_count] = $zoneinfo[$temp];
		$player_count++;
	}
}
$template_object->assign("player_count", $player_count);
$template_object->assign("playerzone", $playerzone);
$template_object->assign("playerzonecolor", $playerzonecolor);

$template_object->assign("l_commodities", $l_commodities);
$template_object->assign("l_player", $l_player);
$template_object->assign("l_teams", $l_teams);

$template_object->assign("l_glxy_nosectors", $l_glxy_nosectors);
$template_object->assign("l_common_prev", $l_common_prev);
$template_object->assign("l_common_next", $l_common_next);
$template_object->assign("l_common_selectpage", $l_common_selectpage);
$template_object->assign("l_port_buys", $l_port_buys);
$template_object->assign("buy_list", $buy_list);
$template_object->assign("link_list", $link_list);
$template_object->assign("l_glxy_personal", $l_glxy_personal);
$template_object->assign("l_galacticarm", $l_galacticarm);
$template_object->assign("galacticarm", $galacticarm);
$template_object->assign("nav_scan_coords", $position);

$template_object->assign("sector_max", $sector_max);
$template_object->assign("sectorname", $sectorname);
$template_object->assign("altsector", $altsector);
$template_object->assign("altport", $altport);
$template_object->assign("altzone", $altzone);
$template_object->assign("notelistnote", $notelistnote);
$template_object->assign("teamnotelistnote", $teamnotelistnote);
$template_object->assign("map_width", $playerinfo['map_width']);
$template_object->assign("pages", $pages);
$template_object->assign("startsector", $startsector);
$template_object->assign("divider", 1000);
$template_object->assign("endsector", $endsector);
$template_object->assign("allselected", $allselected);
$template_object->assign("totalzones", $totalzones);
$template_object->assign("sectorid", $sectorid);
$template_object->assign("sectorzonecolor", $sectorzonecolor);
$template_object->assign("sectorimage", $sectorimage);
$template_object->assign("sectortitle", $sectortitle);
$template_object->assign("mapsectorcount", $mapsectorcount);
$template_object->assign("l_casino", $l_casino);

$template_object->assign("l_spacedock", $l_spacedock);
$template_object->assign("l_glxy_select", $l_glxy_select);
$template_object->assign("l_all", $l_all);
$template_object->assign("l_device_ports", $l_device_ports);
$template_object->assign("l_upgrade_ports", $l_upgrade_ports);
$template_object->assign("l_ore", $l_ore);
$template_object->assign("l_organics", $l_organics);
$template_object->assign("l_energy", $l_energy);
$template_object->assign("l_goods", $l_goods);
$template_object->assign("l_none", $l_none);
$template_object->assign("l_unknown", $l_unknown);
$template_object->assign("l_sector", $l_sector);
$template_object->assign("l_glxy_nonteamed", $l_glxy_nonteamed);
$template_object->assign("l_links", $l_links);
$template_object->assign("l_submit", $l_submit);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."galaxy_map.tpl");
include ("footer.php");

?>

