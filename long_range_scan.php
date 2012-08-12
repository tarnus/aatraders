<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: lrscan.php

include ("config/config.php");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_lrscan.inc");
include ("languages/$langdir/lang_sector_notes.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/log_scan.inc");
include ("globals/get_shipclassname.inc");
include ("globals/get_player.inc");
include ("globals/scanlevel.inc");
include ("globals/last_ship_seen.inc");
include ("globals/display_this_planet.inc");
include ("globals/device_ship_tech_modify.inc");
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

get_post_ifset("game_number");

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

$sector = urldecode($_GET['sector']);

if ((!isset($sector)) || ($sector == ''))
{
	$sector = '';
}

$template_object->assign("title", $l_lrs_title);

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if (!$allow_fullscan)
{
	$template_object->assign("error_msg", $l_lrs_nofull);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < $fullscan_cost)
{
	$template_object->assign("error_msg", $l_lrs_noturns);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

$template_object->assign("l_lrs_used", $l_lrs_used);
$template_object->assign("fullscan_cost", NUMBER($fullscan_cost));
$template_object->assign("l_lrs_turns", $l_lrs_turns);
$template_object->assign("turnsleft", NUMBER($playerinfo['turns'] - $fullscan_cost));
$template_object->assign("l_lrs_left", $l_lrs_left);

// deduct the appropriate number of turns
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-$fullscan_cost, turns_used=turns_used+$fullscan_cost WHERE player_id='$playerinfo[player_id]'");
db_op_result($debug_query,__LINE__,__FILE__);

// user requested a full long range scan
$l_lrs_reach=str_replace("[sector]",$sectorinfo['sector_name'],$l_lrs_reach);
$template_object->assign("l_lrs_reach", $l_lrs_reach);

// get sectors which can be reached from the player's current sector
$result = $db->Execute("SELECT {$db_prefix}universe.zone_id, {$db_prefix}universe.port_type, {$db_prefix}universe.sector_name, {$db_prefix}links.* FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$shipinfo[sector_id]' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest  ORDER BY {$db_prefix}universe.sector_name ASC");
$template_object->assign("l_sector", $l_sector);
$template_object->assign("l_lrs_links", $l_lrs_links);
$template_object->assign("l_lrs_ships", $l_lrs_ships);
$template_object->assign("l_port", $l_port);
$template_object->assign("l_planets", $l_planets);
$template_object->assign("l_mines", $l_mines);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_lss", $l_lss);

$lr_zonetype = array();
$lr_sector = array();
$lr_links = array();
$lr_ships = array();
$lr_port = array();
$lr_image = array();
$lr_image_alt = array();
$lr_planets = array();
$lr_mines = array();
$lr_fighters = array();
$lr_lss = array();

	while (!$result->EOF)
	{
		$row = $result->fields;
		// get number of sectors which can be reached from scanned sector
		$result2 = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start='$row[link_dest]'");
		$num_links = $result2->RecordCount();

		// get number of ships in scanned sector
		$result2 = $db->Execute("SELECT * FROM {$db_prefix}ships LEFT JOIN {$db_prefix}players ON {$db_prefix}ships.player_id={$db_prefix}players.player_id WHERE {$db_prefix}players.currentship={$db_prefix}ships.ship_id AND sector_id='$row[link_dest]' AND on_planet='N' and {$db_prefix}players.destroyed='N'");
		
		$num_ships = 0;
		while (!$result2->EOF)
		{
			$shiprow = $result2->fields;
			$success = SCAN_SUCCESS($shipinfo['sensors'], $shiprow['cloak'], $shiptypes[$shiprow['class']]['basehull']);
			$roll = mt_rand(1, 100);

			if ($roll < $success)
			{
				$num_ships++;
			}
			$result2->MoveNext();
		}
		
		// get port type and discover the presence of a planet in scanned sector
//		$result2 = $db->Execute("SELECT * FROM {$db_prefix}universe WHERE sector_id='$row[link_dest]'");
//		$query96 = $result2->fields;
		$port_type = $row['port_type'];
		$has_planets = 0;

		$resultSDa = $db->Execute("SELECT * from {$db_prefix}sector_defense WHERE sector_id='$row[link_dest]' and defense_type='mines'");
		$resultSDb = $db->Execute("SELECT * from {$db_prefix}sector_defense WHERE sector_id='$row[link_dest]' and defense_type='fighters'");

		//==================================================================
		$has_fighters = 0;
		$highjammer=0;
		if ($resultSDb > 0)
		{
			while (!$resultSDb->EOF)
			{
				$fm_owner = $resultSDb->fields['player_id'];
				$result_fo = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fm_owner", 1);
				$fighters_owner = $result_fo->fields;
				$result3 = $db->SelectLimit("SELECT * from {$db_prefix}ships where player_id=$fighters_owner[player_id] and ship_id=$fighters_owner[currentship]", 1);
				db_op_result($result3,__LINE__,__FILE__);
				$ship_owner = $result3->fields;

				// get planet sensors
				$result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$row[link_dest]' order by sector_defense_cloak DESC", 1);
				db_op_result($result4,__LINE__,__FILE__);
				$planets = $result4->fields;
				if ($highcloak < $planets['sector_defense_cloak']){
					$highcloak=$planets['sector_defense_cloak'];
				}
				$result4 = $db->SelectLimit("SELECT jammer from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$row[link_dest]' order by jammer DESC", 1);
				db_op_result($result4,__LINE__,__FILE__);
				$planets = $result4->fields;
				if ($highjammer < $planets['jammer']){
					$highjammer=$planets['jammer'];
				}

				$success = SCAN_SUCCESS($shipinfo['sensors'], $highcloak);

				$roll = mt_rand(1, 100);
				if ($roll < $success)
				{
					$mines = $resultSDb->fields['quantity'];
					$planet_comp_level = SCAN_ERROR($shipinfo['sensors'], $highjammer, $mines);

					if ($planet_comp_level > $mines)
					{
						$planetfighters = $mines;
					}
					else
					{
						$planetfighters = $planet_comp_level;
					}

					$has_fighters += $planetfighters;
				}
				$resultSDb->MoveNext();
			}
			$has_fighters = NUMBER($has_fighters);
		}
		//=========================================================================
		//==================================================================
		$has_mines = 0;
		$highjammer=0;
		if ($resultSDa > 0)
		{
			while (!$resultSDa->EOF)
			{
				$mn_owner = $resultSDa->fields['player_id'];
				$result_mn = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$mn_owner", 1);
				$mine_owner = $result_mn->fields;
				$result3 = $db->SelectLimit("SELECT * from {$db_prefix}ships where player_id=$mine_owner[player_id] and ship_id=$mine_owner[currentship]", 1);
				db_op_result($result3,__LINE__,__FILE__);
				$ship_owner = $result3->fields;

				// get planet sensors
				$result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner=$mn_owner or  (team > 0 and team=$mine_owner[team])) and base='Y' and sector_id='$row[link_dest]' order by sector_defense_cloak DESC", 1);
				db_op_result($result4,__LINE__,__FILE__);
				$planets = $result4->fields;
				if ($highcloak < $planets['sector_defense_cloak']){
					$highcloak=$planets['sector_defense_cloak'];
				}
				$result4 = $db->SelectLimit("SELECT jammer from {$db_prefix}planets where (owner=$mn_owner or  (team > 0 and team=$mine_owner[team])) and base='Y' and sector_id='$row[link_dest]' order by jammer DESC", 1);
				db_op_result($result4,__LINE__,__FILE__);
				$planets = $result4->fields;
				if ($highjammer < $planets['jammer']){
					$highjammer=$planets['jammer'];
				}

				$success = SCAN_SUCCESS($shipinfo['sensors'], $highcloak);

				$roll = mt_rand(1, 100);
				if ($roll < $success)
				{
					$mines = $resultSDa->fields['quantity'];
					$planet_comp_level = SCAN_ERROR($shipinfo['sensors'], $highjammer, $mines);

					if ($planet_comp_level > $mines)
					{
						$planetmines = $mines;
					}
					else
					{
						$planetmines = $planet_comp_level;
					}

					$has_mines += $planetmines;
				}
				$resultSDa->MoveNext();
			}
			$has_mines = NUMBER($has_mines);
		}
		//=========================================================================

		$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE sector_id='$row[link_dest]'", 5);
		while (!$result3->EOF)
		{
			$show_planet = 0;
			$success = 0;
			$hiding_planet[$i] = $result3->fields;

			if ($hiding_planet[$i]['owner'] == $playerinfo['player_id'])
			{
				$show_planet = 1;
			}

			if ($hiding_planet[$i]['team'] != 0)
			{
				if ($hiding_planet[$i]['team'] == $playerinfo['team'])
				{
					$show_planet = 1;
				}
			}

			if ($shipinfo['sensors'] >= $hiding_planet[$i]['cloak'])
			{
				$show_planet = 1;
			}

			if ($show_planet == 0) //Not yet 'visible'
			{
				$success = SCAN_SUCCESS($shipinfo['sensors'], $hiding_planet[$i]['cloak']);
				$roll = mt_rand(1, 100);
				if ($roll < $success) // If able to see the planet
				{
					$show_planet = 1; //confirmed working
				}
	
			 ///
				if ($show_planet == 0 && $enable_spies)  // Still not yet 'visible'
				{
					$res_s = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '" . $hiding_planet[$i]['planet_id'] . "' AND owner_id = '$playerinfo[player_id]'");
					if ($res_s->RecordCount())
					$show_planet = 1;
				}
			}

			if ($show_planet == 1)
			{
				$planets[$i] = $result3->fields;
				$has_planets++;
			}
			$i++;
			$result3->MoveNext();
		}

		if ($port_type != "none") 
		{
			$icon_alt_text = $port_type;
			$icon_port_type_name = $port_type . ".png";
		} 
		else 
		{
			$icon_alt_text = "";
			$icon_port_type_name = "";
		}

//		$zone_query = $db->Execute("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$row[link_dest]");
//		db_op_result($zone_query,__LINE__,__FILE__);
//		$zones = $zone_query->fields;

		log_scan($playerinfo['player_id'], $row['link_dest'],$row['zone_id']);

		$lr_zonetype[] = ($row['zone_id'] == 2) ? "F> " : "=> ";
		$lr_sector[] = $row['sector_name'];
		$lr_links[] = $num_links;
		$lr_ships[] = $num_ships;
		$lr_port[] = ucfirst($port_type);
		$lr_planets[] = $has_planets;
		$lr_mines[] = $has_mines;
		$lr_fighters[] = $has_fighters;
		$lr_image[] = $port_type;
		$lr_image_alt[] = $icon_alt_text;
		
		$lss_info = last_ship_seen($row['link_dest'], $playerinfo['player_id'], $shipinfo['sensors']);
		if ($row['link_dest'] != '1')
		{
			$lr_lss[] = $lss_info;
		}
		else
		{
			$lr_lss[] = $l_lrs_fedjammed;
		}
		$result->MoveNext();
	}
$template_object->assign("lr_zonetype", $lr_zonetype);
$template_object->assign("lr_sector", $lr_sector);
$template_object->assign("lr_links", $lr_links);
$template_object->assign("lr_ships", $lr_ships);
$template_object->assign("lr_port", $lr_port);
$template_object->assign("lr_image", $lr_image);
$template_object->assign("lr_image_alt", $lr_image_alt);
$template_object->assign("lr_planets", $lr_planets);
$template_object->assign("lr_mines", $lr_mines);
$template_object->assign("lr_fighters", $lr_fighters);
$template_object->assign("lr_lss", $lr_lss);
$template_object->assign("l_scan", ucfirst($l_scan));

	if ($num_links == 0)
	{
		$template_object->assign("l_lrs_click", $l_none);
	}
	else
	{
		$template_object->assign("l_lrs_click", $l_lrs_click);
	}

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."long_range_scan.tpl");

include ("footer.php");

?>
