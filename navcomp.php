<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: navcomp.php

include ("config/config.php");
include ("languages/$langdir/lang_navcomp.inc");
include ("languages/$langdir/lang_check_fighters.inc");
include ("languages/$langdir/lang_check_mines.inc");
include ("languages/$langdir/lang_autoroutes.inc");
include ("globals/calc_dist.inc");
include ("globals/log_move.inc");

get_post_ifset("state, dismiss, start_sector, stop_sector, destination, warp_list, autoroute_id, autodelete, autocount, name, delete_id, warponly");

$title = $l_nav_title;

if ((!isset($state)) || ($state == ''))
{
	$state = 0;
}

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

$template_object->assign("templatename", $templatename);

function autowarpmove($targetlink)
{
	// *********************************
	// *** SETUP GENERAL VARIABLES  ****
	// *********************************
	global $db, $db_prefix, $playerinfo, $shipinfo,$level_factor, $zoneinfo, $shiptypes, $automove_result;
	global $l_chm_youhitsomemines, $l_chm_hehitminesinsector, $l_chm_youlostminedeflectors, $l_chm_youlostallminedeflectors;
	global $l_chm_youhadnominedeflectors, $l_chm_yourshieldshitforminesdmg, $l_chm_yourshieldsaredown, $l_chm_youlostallyourshields;
	global $l_chm_yourarmorhitforminesdmg, $l_chm_yourhullisbreached, $l_chm_hewasdestroyedbyyourmines, $l_chm_luckescapepod;
	global $l_autoroute_missingwarp, $l_autoroute_fighterabort, $l_autoroute_turns, $l_autoroute_noturns;

	$sectres = $db->SelectLimit("SELECT sector_id, sector_name, zone_id FROM {$db_prefix}universe WHERE sector_name='$targetlink'", 1);
	$sectrow = $sectres->fields;
	$rswarp='';
	$linkres = $db->Execute ("SELECT u.sector_name FROM {$db_prefix}links as l, {$db_prefix}universe as u WHERE l.link_start='$shipinfo[sector_id]' and u.sector_id=l.link_dest");
	if ($linkres > 0)
	{
		while (!$linkres->EOF)
		{
			$row = $linkres->fields;
			if($row['sector_name'] == $sectrow['sector_name']){
				// *** OBTAIN SECTOR INFORMATION ***
				$sectres = $db->SelectLimit("SELECT sector_id, sector_name, zone_id FROM {$db_prefix}universe WHERE sector_name='$row[sector_name]'", 1);
				$sectrow = $sectres->fields;
				$zoneres = $db->SelectLimit("SELECT zone_id,allow_attack FROM {$db_prefix}zones WHERE zone_id=$sectrow[zone_id]", 1);
				$zonerow = $zoneres->fields;
				$rswarp = $targetlink;
			}
			$linkres->MoveNext();
		}
	}

	// *********************************
	// ***** IF NO ACCEPTABLE LINK *****
	// *********************************

	if($rswarp == ''){
		$automove_result[] = $l_autoroute_missingwarp;
		return "abort";
	}

	$resultf = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sectrow[sector_id]' and defense_type ='fighters' and player_id != '$playerinfo[player_id]' ORDER BY quantity DESC");
		$i = 0;
		$total_sector_fighters = 0;
		$highsensors=0;
		if ($resultf > 0)
		{
			while (!$resultf->EOF)
			{
				$defenses[$i] = $resultf->fields;
				$fmowners = $defenses[$i]['player_id'];
				
				
				$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fmowners", 1);
				$fighters_owner = $result2->fields;
				if ($fighters_owner['team'] != $playerinfo['team'] || $playerinfo['team'] == 0)
				{
					$total_sector_fighters += $defenses[$i]['quantity'];
					// Get Players ship sensors
					$result3 = $db->SelectLimit("SELECT sensors from {$db_prefix}ships where player_id=$fighters_owner[player_id] and ship_id=$fighters_owner[currentship]", 1);
					$ship_owner = $result3->fields;
					if ($ship_owner['sensors'] > $highsensors){
						$highsensors=$ship_owner['sensors'];
					}
					// get planet sensors
					$result4 = $db->SelectLimit("SELECT sensors from {$db_prefix}planets where (owner=$fighters_owner[player_id] or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$sectrow[sector_id]' order by sensors DESC", 1);
					$planets = $result4->fields;
					if ($planets['sensors'] > $highsensors){
						$highsensors=$planets['sensors'];
					}
				}
				$i++;
				$resultf->MoveNext();
			}
		}

		$resultm = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sectrow[sector_id]' and defense_type ='mines' and player_id != '$playerinfo[player_id]' ");
		$i = 0;
		$total_sector_mines = 0;
		$highsensors=0;
		if ($resultm > 0)
		{
			while (!$resultm->EOF)
			{
				$defenses[$i] = $resultm->fields;
				$fmowners = $defenses[$i]['player_id'];

				$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fmowners", 1);
				$mine_owner = $result2->fields;

				if ($mine_owner['team'] != $playerinfo['team'] || $playerinfo['team'] == 0) // Are the mine owner and player are on the same team?
				{
					$total_sector_mines += $defenses[$i]['quantity'];
					// Get Players ship sensors
					$result3 = $db->SelectLimit("SELECT sensors from {$db_prefix}ships where player_id=$mine_owner[player_id] and ship_id=$mine_owner[currentship]", 1);
					$ship_owner = $result3->fields;
					if ($ship_owner['sensors'] > $highsensors){
						$highsensors=$ship_owner['sensors'];
					}
					// get planet sensors
					$result4 = $db->SelectLimit("SELECT sensors from {$db_prefix}planets where (owner=$mine_owner[player_id] or  (team > 0 and team=$mine_owner[team])) and base='Y' and sector_id='$sectrow[sector_id]' order by sensors DESC", 1);
					$planets = $result4->fields;
					if ($planets['sensors'] > $highsensors){
						$highsensors=$planets['sensors'];
					}
				}
				$i++;
				$resultm->MoveNext();
			}
		}

		if ($total_sector_fighters>0 || $total_sector_mines>0 || ($total_sector_fighters>0 && $total_sector_mines>0))
		// ********************************
		// **** DEST LINK HAS defenseS ****
		// ********************************
		{
			$success = SCAN_SUCCESS($highsensors, $shipinfo['cloak'], $shiptypes[$shipinfo['class']]['basehull']);
			$roll = mt_rand(1, 100);
			if (($roll < $success)and ($total_sector_fighters>0)) 
			{
				$automove_result[] = $l_autoroute_SDabort;
				return "abort";
			}

			if ($total_sector_mines>0)
			{
				$automove_result[] = $l_autoroute_SDabort;
				return "abort";
			}

			$triptime = 1;

			if ($playerinfo['turns'] >= $triptime)
			{
		   		$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+$triptime, turns=turns-$triptime " .
					   "WHERE player_id=$playerinfo[player_id]";
		   		$move_result = $db->Execute ("$query");
		   		$query="UPDATE {$db_prefix}ships SET sector_id=$sectrow[sector_id] " .
					   "WHERE ship_id=$shipinfo[ship_id]";
		   		$move_result = $db->Execute ("$query");
				$shipinfo['sector_id'] = $sectrow['sector_id'];
				$playerinfo['turns']--;
				$l_autoroute_turns2 = str_replace("[triptime]", $triptime, $l_autoroute_turns);
				$l_autoroute_turns2 = str_replace("[targetlink]", $targetlink, $l_autoroute_turns2);
				$automove_result[] = $l_autoroute_turns2;
				return "ok";
   			}else{
				$automove_result[] = $l_autoroute_noturns;
				return "abort";
			}
		}	
		else
		// ********************************
		// **** Safe Move ***
		// ********************************
		{
			$triptime = 1;

			if ($playerinfo['turns'] >= $triptime)
			{
   				$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+$triptime, turns=turns-$triptime " .
	   				   "WHERE player_id=$playerinfo[player_id]";
				$move_result = $db->Execute ("$query");
					$query="UPDATE {$db_prefix}ships SET sector_id=$sectrow[sector_id] " .
					   "WHERE ship_id=$shipinfo[ship_id]";
		   		$move_result = $db->Execute ("$query");
				log_move($playerinfo['player_id'], $shipinfo['ship_id'], $shipinfo['sector_id'], $sectrow['sector_id'], $shipinfo['class'], $shipinfo['cloak'], $sectrow['zone_id']);
				$shipinfo['sector_id'] = $sectrow['sector_id'];
				$playerinfo['turns']--;
				$l_autoroute_turns2 = str_replace("[triptime]", $triptime, $l_autoroute_turns);
				$l_autoroute_turns2 = str_replace("[targetlink]", $targetlink, $l_autoroute_turns2);
				$automove_result[] = $l_autoroute_turns2;
				return "ok";
			}else{
				$automove_result[] = $l_autoroute_noturns;
				return "abort";
			}
		}
}

function autorealspacemove($targetlink)
{
	// *********************************
	// *** SETUP GENERAL VARIABLES  ****
	// *********************************
	global $db, $db_prefix, $playerinfo, $shipinfo,$level_factor, $zoneinfo, $automove_result;
	global $l_chm_youhitsomemines, $l_chm_hehitminesinsector, $l_chm_youlostminedeflectors, $l_chm_youlostallminedeflectors;
	global $l_chm_youhadnominedeflectors, $l_chm_yourshieldshitforminesdmg, $l_chm_yourshieldsaredown, $l_chm_youlostallyourshields;
	global $l_chm_yourarmorhitforminesdmg, $l_chm_yourhullisbreached, $l_chm_hewasdestroyedbyyourmines, $l_chm_luckescapepod;
	global $l_autoroute_missingwarp, $l_autoroute_fighterabort, $l_autoroute_turns, $l_autoroute_noturns;

	 // *** OBTAIN SECTOR INFORMATION ***
	$sectres = $db->SelectLimit("SELECT sector_id, sector_name, zone_id FROM {$db_prefix}universe WHERE sector_name='$targetlink'", 1);
	$sectrow = $sectres->fields;
	$zoneres = $db->SelectLimit("SELECT zone_id,allow_attack FROM {$db_prefix}zones WHERE zone_id=$sectrow[zone_id]", 1);
	$zonerow = $zoneres->fields;

	$resultf = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sectrow[sector_id]' and defense_type ='fighters' and player_id != '$playerinfo[player_id]' ORDER BY quantity DESC");
	$i = 0;
	$total_sector_fighters = 0;
	$highsensors=0;
	if ($resultf > 0)
	{
		while (!$resultf->EOF)
		{
			$defenses[$i] = $resultf->fields;
			$fmowners = $defenses[$i]['player_id'];

			$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fmowners", 1);
			$fighters_owner = $result2->fields;
			if ($fighters_owner['team'] != $playerinfo['team'] || $playerinfo['team'] == 0)
			{
				$total_sector_fighters += $defenses[$i]['quantity'];
				// Get Players ship sensors
				$result3 = $db->SelectLimit("SELECT sensors from {$db_prefix}ships where player_id=$fighters_owner[player_id] and ship_id=$fighters_owner[currentship]", 1);
				$ship_owner = $result3->fields;
				if ($ship_owner['sensors'] > $highsensors){
					$highsensors=$ship_owner['sensors'];
				}
				// get planet sensors
				$result4 = $db->SelectLimit("SELECT sensors from {$db_prefix}planets where (owner=$fighters_owner[player_id] or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$sectrow[sector_id]' order by sensors", 1);
				$planets = $result4->fields;
				if ($planets['sensors'] > $highsensors){
					$highsensors=$planets['sensors'];
				}
			}
			$i++;
			$resultf->MoveNext();
		}
	}

	$resultm = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sectrow[sector_id]' and defense_type ='mines' and player_id != '$playerinfo[player_id]' ");
	$i = 0;
	$total_sector_mines = 0;
	$highsensors=0;
	if ($resultm > 0)
	{
		while (!$resultm->EOF)
		{
			$defenses[$i] = $resultm->fields;
			$fmowners = $defenses[$i]['player_id'];

			$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fmowners", 1);
			$mine_owner = $result2->fields;

			if ($mine_owner['team'] != $playerinfo['team'] || $playerinfo['team'] == 0) // Are the mine owner and player are on the same team?
			{
				$total_sector_mines += $defenses[$i]['quantity'];
				// Get Players ship sensors
				$result3 = $db->SelectLimit("SELECT sensors from {$db_prefix}ships where player_id=$mine_owner[player_id] and ship_id=$mine_owner[currentship]", 1);
				$ship_owner = $result3->fields;
				if ($ship_owner['sensors'] > $highsensors){
					$highsensors=$ship_owner['sensors'];
				}
				// get planet sensors
				$result4 = $db->SelectLimit("SELECT sensors from {$db_prefix}planets where (owner=$mine_owner[player_id] or  (team > 0 and team=$mine_owner[team])) and base='Y' and sector_id='$sectrow[sector_id]' order by sensors", 1);
				$planets = $result4->fields;
				if ($planets['sensors'] > $highsensors){
					$highsensors=$planets['sensors'];
				}
			}
			$i++;
			$resultm->MoveNext();
		}
	}

	if ($total_sector_fighters>0 || $total_sector_mines>0 || ($total_sector_fighters>0 && $total_sector_mines>0))
	// ********************************
	// **** DEST LINK HAS defenseS ****
	// ********************************
	{
		$success = SCAN_SUCCESS($highsensors, $shipinfo['cloak'], $shiptypes[$shipinfo['class']]['basehull']);

		$roll = mt_rand(1, 100);
		if (($roll < $success)and ($total_sector_fighters>0)) 
		{
			$automove_result[] = $l_autoroute_fighterabort;
			return "abort";
		}

		if ($total_sector_mines>0)
		{
			$automove_result[] = $l_autoroute_SDabort;
			return "abort";
		}

		$distance = calc_dist($shipinfo['sector_id'],$sectrow['sector_id']);
   		$shipspeed = mypw($level_factor, $shipinfo['engines']);
	   	$triptime = round($distance / $shipspeed);

	   	if ($triptime == 0 && $sectrow['sector_id'] != $shipinfo['sector_id'])
	   	{
			$triptime = 1;
	   	}
		if ($playerinfo['turns'] >= $triptime)
		{
	   		$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+$triptime, turns=turns-$triptime " .
				   "WHERE player_id=$playerinfo[player_id]";
	   		$move_result = $db->Execute ("$query");
	   		$query="UPDATE {$db_prefix}ships SET sector_id=$sectrow[sector_id] " .
				   "WHERE ship_id=$shipinfo[ship_id]";
	   		$move_result = $db->Execute ("$query");
			$shipinfo['sector_id'] = $sectrow['sector_id'];
			$playerinfo['turns'] -= $triptime;
			$l_autoroute_turns2 = str_replace("[triptime]", $triptime, $l_autoroute_turns);
			$l_autoroute_turns2 = str_replace("[targetlink]", $targetlink, $l_autoroute_turns2);
			$automove_result[] = $l_autoroute_turns2;
	   		return "ok";
		}else{
			$automove_result[] = $l_autoroute_noturns;
			return "abort";
		}
	}
	else
	// ********************************
	// **** Safe Move ***
	// ********************************
	{
	//  Calculate number of turns for RS
		$distance = calc_dist($shipinfo['sector_id'],$sectrow['sector_id']);
		$shipspeed = mypw($level_factor, $shipinfo['engines']);
		$triptime = round($distance / $shipspeed);

		if ($triptime == 0 && $sectrow['sector_id'] != $shipinfo['sector_id'])
		{
			$triptime = 1;
		}
		if ($playerinfo['turns'] >= $triptime)
		{
			$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+$triptime, turns=turns-$triptime " .
				   "WHERE player_id=$playerinfo[player_id]";
			$move_result = $db->Execute ("$query");
	   		$query="UPDATE {$db_prefix}ships SET sector_id=$sectrow[sector_id] " .
				   "WHERE ship_id=$shipinfo[ship_id]";
	   		$move_result = $db->Execute ("$query");
			log_move($playerinfo['player_id'], $shipinfo['ship_id'], $shipinfo['sector_id'], $sectrow['sector_id'], $shipinfo['class'], $shipinfo['cloak'], $sectrow['zone_id']);
			$shipinfo['sector_id'] = $sectrow['sector_id'];
			$playerinfo['turns'] -= $triptime;
			$l_autoroute_turns2 = str_replace("[triptime]", $triptime, $l_autoroute_turns);
			$l_autoroute_turns2 = str_replace("[targetlink]", $targetlink, $l_autoroute_turns2);
			$automove_result[] = $l_autoroute_turns2;
			return "ok";
		}else{
			$automove_result[] = $l_autoroute_noturns;
			return "abort";
		}
	}
}


$template_object->assign("startingsector", $sectorinfo['sector_name']);

$fighter_tech  = $shipinfo['fighter'];

// Without these here.  You will receive warnings.
$search_results_echo = NULL;
$links = NULL;
$search_depth = NULL;

$automove_result = array();

switch ($state)
{
	case "0":
		include ("header.php");
		$autocount = 0;

		$res = $db->Execute("SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.sector_id, {$db_prefix}links.link_dest FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$sectorinfo[sector_id]' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");

		$resultlist = array();
		if ($res > 0)
		{
			while (!$res->EOF)
			{
				$res_return = $db->Execute("SELECT source FROM {$db_prefix}sector_log WHERE player_id=$playerinfo[player_id] and (source='" . $res->fields['sector_id'] . "' or destination='" . $res->fields['sector_id'] . "')");
				db_op_result($res_return,__LINE__,__FILE__);
				$visitedcount = $res_return->RecordCount();
				$res_return->close();
				$visited = 0;
				if($visitedcount == 0)
				{
					$visited = 1;
				}
				$resultlist[] = $res->fields['sector_name'];
				$resultvisitedlist[] = $visited;
				$res->MoveNext();
			}
		}
		$res->close();
		$template_object->assign("resultlist", $resultlist);
		$template_object->assign("resultvisitedlist", $resultvisitedlist);

		$res = $db->Execute("SELECT * FROM {$db_prefix}autoroutes WHERE player_id=$playerinfo[player_id] ");
		if($res->RecordCount())
		{
			while(!$res->EOF)
			{
				$autoroute = $res->fields;

				if($autoroute['warp_list'] == "")
					$autoroute['warp_list'] = "None";

				$autolinecolor[$autocount] = "#000000";
				$autorouteid[$autocount] = $autoroute['autoroute_id'];
				$autostart[$autocount] = $autoroute['start_sector'];
				$autoend[$autocount] = $autoroute['destination'];
				$autoname[$autocount] = $autoroute['name'];
				$warplist[$autocount] = $autoroute['warp_list'];
				$autodelete[$autocount] = "dismiss[$autocount]";
				$res->MoveNext();
				$autocount++;
			}
		}

		$template_object->assign("title", $title);
		$template_object->assign("warplist", $warplist);
		$template_object->assign("autorouteid", $autorouteid);
		$template_object->assign("autostart", $autostart);
		$template_object->assign("autoend", $autoend);
		$template_object->assign("autoname", $autoname);
		$template_object->assign("autodelete", $autodelete);
		$template_object->assign("autolinecolor", $autolinecolor);
		$template_object->assign("autocount", $autocount);
		$template_object->assign("l_autoroute_id", $l_autoroute_id);
		$template_object->assign("l_autoroute_start", $l_autoroute_start);
		$template_object->assign("l_autoroute_destination", $l_autoroute_destination);
		$template_object->assign("l_autoroute_warps", $l_autoroute_warps);
		$template_object->assign("l_autoroute_deleteroute", $l_autoroute_deleteroute);
		$template_object->assign("l_autoroute_noroutes", $l_autoroute_noroutes);

		$template_object->assign("l_autoroute_title", $l_autoroute_title);
		$template_object->assign("l_autoroute_delete2", $l_autoroute_delete2);
		$template_object->assign("l_autoroute_info", $l_autoroute_info);
		$template_object->assign("l_autoroute_editname", $l_autoroute_editname);

		$template_object->assign("l_nav_notinlogs", $l_nav_notinlogs);
		$template_object->assign("l_nav_warp_from", $l_nav_warp_from);
		$template_object->assign("l_nav_rs_from", $l_nav_rs_from);
		$template_object->assign("l_nav_manuallist", $l_nav_manuallist);
		$template_object->assign("l_nav_nowarplinksleaving", $l_nav_nowarplinksleaving);
		$template_object->assign("l_nav_autoroutename", $l_nav_autoroutename);
		$template_object->assign("l_autoroute_createroute", $l_autoroute_createroute);
		$template_object->assign("l_nav_nocomp", $l_nav_nocomp);
		$template_object->assign("allow_navcomp", $allow_navcomp);
		$template_object->assign("l_submit", $l_submit);
		$template_object->assign("state", $_POST['state']);
		$template_object->assign("search_results_echo", $search_results_echo);
		$template_object->assign("start_sector", (empty($links[0])) ? $sectorinfo['sector_name'] : $links[0]);
		$template_object->assign("l_nav_warplinksleaving", str_replace("[sector_name]", (empty($links[0])) ? $sectorinfo['sector_name'] : $links[0], $l_nav_warplinksleaving));
		$template_object->assign("found", $found);
		$template_object->assign("search_depth", $search_depth);
		$template_object->assign("l_nav_answ1", $l_nav_answ1);
		$template_object->assign("l_nav_answ2", $l_nav_answ2);
		$template_object->assign("l_nav_proper", $l_nav_proper);
		$template_object->assign("l_nav_query", $l_nav_query);
		$template_object->assign("l_autoroute_return", $l_autoroute_return);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."navcomp/navcomp2.tpl");

		include ("footer.php");
		break;

	case "1":

		if ($allow_navcomp)
		{
			include ("header.php");
			$max_search_depth = round($fighter_tech / (5 * ($max_tech_level / 54)))+2;

			$result2 = $db->SelectLimit("SELECT sector_id, sg_sector FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr(trim($_POST['stop_sector'])), 1);
			db_op_result($result2,__LINE__,__FILE__);
			if($result2->RecordCount() > 0)
			{
				$sector_id = $result2->fields['sector_id'];
				$sg_sector = $result2->fields['sg_sector'];

				for ($search_depth = 1; $search_depth <= $max_search_depth; $search_depth++)
				{
					$search_query = "SELECT a1.link_start , a1.link_dest \n";
					for ($i = 2; $i<=$search_depth; $i++)
					{
						$search_query = $search_query . " ,a". $i . ".link_dest \n";
					}

					$search_query = $search_query . "FROM {$db_prefix}links AS a1 \n";
					for ($i = 2; $i<=$search_depth; $i++)
					{
						$search_query = $search_query . " ,{$db_prefix}links AS a". $i . " \n";
					}

					$search_query = $search_query . "WHERE a1.link_start = $shipinfo[sector_id] \n";
					for ($i = 2; $i<=$search_depth; $i++)
					{
						$k = $i-1;
						$search_query = $search_query . " AND a" . $k . ".link_dest = a" . $i . ".link_start \n";
					}

					$search_query = $search_query . " AND a" . $search_depth . ".link_dest = $sector_id \n";
					$search_query = $search_query . " AND a1.link_dest != a1.link_start \n";
					for ($i=2; $i<=$search_depth; $i++)
					{
						$search_query = $search_query . " AND a" . $i . ".link_dest not in (a1.link_dest, a1.link_start ";
						for ($j=2; $j<$i; $j++)
						{
							$search_query = $search_query . ",a".$j.".link_dest ";
						}
						$search_query = $search_query . ")\n";
	 				}

					$search_query = $search_query . "ORDER BY a1.link_start, a1.link_dest ";
					for ($i=2; $i<=$search_depth; $i++)
					{
						$search_query = $search_query . ", a" . $i . ".link_dest";
					}

					$search_query = $search_query . " \nLIMIT 1";

					// Okay, this is tricky. We need the db returns to be numeric, not associative, so that we 
					// can get a count from it. A good page on it is here: http://php.weblogs.com/adodb_tutorial .
					// We also dont need to set it BACK to the game default, because each page sets it again (by calling config).
					// If someone can think of a way to recode this to not need this line, I would deeply appreciate it!
					//echo "$search_query<br><br>";
					$ADODB_FETCH_MODE = ADODB_FETCH_NUM;
					$debug_query = $db->Execute ($search_query);
					db_op_result($debug_query,__LINE__,__FILE__);
					$found = $debug_query->RecordCount();
//					echo "$found<br><br>";
					if ($found > 0)
					{
						break;
					}
				}
			}
			else
			{
				$found = -1;
			}

			if ($found > 0)
			{
				$links = $debug_query->fields;
				$search_results_echo = '';
				$warp_list = '';
				$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;
				$result2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=$links[0]", 1);
				$start_name = $result2->fields['sector_name'];
				for ($i=1; $i<$search_depth+1; $i++)
				{
					$result2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=$links[$i]", 1);
					$sector_name = $result2->fields['sector_name'];
					if ($i==1)
					{
						$search_results_echo = $search_results_echo . " >> " . "<a href=main.php?move_method=warp&destination=" . rawurlencode($sector_name) . ">$sector_name</a>";
					}
					else
					{
						$search_results_echo = $search_results_echo . " >> " . $sector_name;
					}
					if($i <= ($search_depth -1)){
						$warp_list = $warp_list . $sector_name;
						if($i != ($search_depth - 1))
							$warp_list = $warp_list . "|";
					}
				}
			}

			$template_object->assign("title", $title);
			$template_object->assign("sectorname", $_POST['stop_sector']);
			$template_object->assign("l_nav_notinlogs", $l_nav_notinlogs);
			$template_object->assign("l_nav_nocomp", $l_nav_nocomp);
			$template_object->assign("l_nav_pathfnd", $l_nav_pathfnd);
			$template_object->assign("allow_navcomp", $allow_navcomp);
			$template_object->assign("l_submit", $l_submit);
			$template_object->assign("state", $_POST['state']);
			$template_object->assign("search_results_echo", $search_results_echo);
			$template_object->assign("start_sector", $start_name);
			$template_object->assign("found", $found);
			$template_object->assign("search_depth", $search_depth);
			$template_object->assign("l_nav_answ1", $l_nav_answ1);
			$template_object->assign("l_nav_answ2", $l_nav_answ2);
			$template_object->assign("l_nav_proper", $l_nav_proper);
			$template_object->assign("l_nav_query", $l_nav_query);
			$template_object->assign("destination", $sector_name);
			$template_object->assign("warp_list", $warp_list);
			$template_object->assign("l_nav_autoroutename", $l_nav_autoroutename);
			$template_object->assign("l_autoroute_createroute", $l_autoroute_createroute);
			$template_object->assign("found", $found);
			$template_object->assign("l_autoroute_return", $l_autoroute_return);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."navcomp/navcomp.tpl");

			include ("footer.php");
		}
		else
		{
			include ("header.php");
			include ("footer.php");
		}
		break;

	case "dismiss":
		$debug_query = $db->Execute("delete from {$db_prefix}autoroutes WHERE autoroute_id=$delete_id and player_id=$playerinfo[player_id] ");
		db_op_result($debug_query,__LINE__,__FILE__);

		unset($_SESSION['currentprogram'], $currentprogram);
		unset ($template_object);
		echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
				<html>
					<head>
							<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=navcomp.php\">
						<title>Navcomp</title>
					</head>
					<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
					</body>
				</html>";
		die();
		break;

	case "create":
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}autoroutes " .
									"(start_sector ,destination ,warp_list ,player_id, name ) values " .
									"('$start_sector','$destination','$warp_list',$playerinfo[player_id], " . $db->qstr(trim($name)) . ")");
		db_op_result($debug_query,__LINE__,__FILE__);
		unset($_SESSION['currentprogram'], $currentprogram);
		unset ($template_object);
		echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
				<html>
					<head>
							<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=navcomp.php\">
						<title>Navcomp</title>
					</head>
					<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
					</body>
				</html>";
		die();
		break;

	case "editname":
		if(trim($name) != trim($autoroute_id))
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}autoroutes SET name = " . $db->qstr(trim($name)) . " WHERE autoroute_id=$autoroute_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
				<html>
					<head>
							<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=navcomp.php\">
						<title>Navcomp</title>
					</head>
					<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
					</body>
				</html>";
		unset($_SESSION['currentprogram'], $currentprogram);
		unset ($template_object);
		die();
		break;

	case "start":

		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}autoroutes WHERE autoroute_id=$autoroute_id and player_id=$playerinfo[player_id] ", 1);

		if($res->RecordCount() != 1)
		{
			echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
				<html>
					<head>
							<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">
						<title>Navcomp Failed</title>
					</head>
					<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
					</body>
				</html>";
			die();
			break;
		}

		include ("header.php");
		$template_object->assign("title", $title);
		$autoroute = $res->fields;

		$sector_res = $db->SelectLimit("SELECT sg_sector, sector_name FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
		$sector_type = $sector_res->fields['sg_sector'];
		$sector_name = $sector_res->fields['sector_name'];

		$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($autoroute['start_sector']), 1);
		$route_type = $sector_res->fields['sg_sector'];

		if($sector_name != $autoroute['start_sector'] && $warponly != 1){
			$template_object->assign("part1", 1);
			$automove_result = array();
			$template_object->assign("startmovetype", $l_autoroute_realmove);
			$template_object->assign("sectorstart", $autoroute['start_sector']);
			if($sector_type == 0 and $route_type == 0){
				if(autorealspacemove($autoroute['start_sector']) != "ok")
				{
					$template_object->assign("start_result", $automove_result);
					$template_object->assign("l_autoroute_return", $l_autoroute_return);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."navcomp/autoroute_result.tpl");
					include ("footer.php");
					break;
				}
			}else{
				if(autowarpmove($autoroute['start_sector']) != "ok")
				{
					$template_object->assign("start_result", $automove_result);
					$template_object->assign("l_autoroute_return", $l_autoroute_return);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."navcomp/autoroute_result.tpl");
					include ("footer.php");
					break;
				}
			}
			$template_object->assign("start_result", $automove_result);
		}
		$template_object->assign("part2", 1);

		if($autoroute['warp_list'] != ""){
			$warpsectors = explode("|", $autoroute['warp_list']);
			$warp_list_movetype = array();
			$warp_list_sector = array();
			$automove_result = array();
			for($i = 0; $i <count($warpsectors); $i++){
				$warp_list_movetype[] = $l_autoroute_warpmove;
				$warp_list_sector[] = $warpsectors[$i];
				if(autowarpmove($warpsectors[$i]) != "ok")
				{
					$template_object->assign("warp_list_movetype", $warp_list_movetype);
					$template_object->assign("warp_list_sector", $warp_list_sector);
					$template_object->assign("move_result", $automove_result);
					$template_object->assign("l_autoroute_return", $l_autoroute_return);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."navcomp/autoroute_result.tpl");
					include ("footer.php");
					break;
				}
			}
		}
		$template_object->assign("part3", 1);
		$template_object->assign("warp_list_movetype", $warp_list_movetype);
		$template_object->assign("warp_list_sector", $warp_list_sector);
		$template_object->assign("move_result", $automove_result);
		$template_object->assign("endmovetype", $l_autoroute_warpfinal);
		$template_object->assign("endsector", $autoroute['destination']);
		$automove_result = array();
		autowarpmove($autoroute['destination']);
		$template_object->assign("endmove_result", $automove_result);
		$template_object->assign("l_autoroute_return", $l_autoroute_return);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."navcomp/autoroute_result.tpl");
		include ("footer.php");
		break;

	case "reverse":

		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}autoroutes WHERE autoroute_id=$autoroute_id and player_id=$playerinfo[player_id] ", 1);

		if($res->RecordCount() != 1)
		{
			echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
				<html>
					<head>
							<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">
						<title>Navcomp Failed</title>
					</head>
					<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor=\"#000000\">
					</body>
				</html>";
			die();
			break;
		}

		include ("header.php");
		$template_object->assign("title", $title);
		$autoroute = $res->fields;

		$sector_res = $db->SelectLimit("SELECT sg_sector, sector_name FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
		$sector_type = $sector_res->fields['sg_sector'];
		$sector_name = $sector_res->fields['sector_name'];

		$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($autoroute['destination']), 1);
		$route_type = $sector_res->fields['sg_sector'];

		if($sector_name != $autoroute['destination'] && $warponly != 1){
			$template_object->assign("part1", 1);
			$automove_result = array();
			$template_object->assign("startmovetype", $l_autoroute_realmove);
			$template_object->assign("sectorstart", $autoroute['destination']);
			if($sector_type == 0 and $route_type == 0){
				if(autorealspacemove($autoroute['destination']) != "ok")
				{
					$template_object->assign("start_result", $automove_result);
					$template_object->assign("l_autoroute_return", $l_autoroute_return);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."navcomp/autoroute_result.tpl");
					include ("footer.php");
					break;
				}
			}else{
				if(autowarpmove($autoroute['destination']) != "ok")
				{
					$template_object->assign("start_result", $automove_result);
					$template_object->assign("l_autoroute_return", $l_autoroute_return);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."navcomp/autoroute_result.tpl");
					include ("footer.php");
					break;
				}
			}
			$template_object->assign("start_result", $automove_result);
		}
		$template_object->assign("part2", 1);

		if($autoroute['warp_list'] != ""){
			$warpsectors = explode("|", $autoroute['warp_list']);
			$warp_list_movetype = array();
			$warp_list_sector = array();
			$automove_result = array();
			for($i = (count($warpsectors) - 1); $i >= 0; $i--){
				$warp_list_movetype[] = $l_autoroute_warpmove;
				$warp_list_sector[] = $warpsectors[$i];
				if(autowarpmove($warpsectors[$i]) != "ok")
				{
					$template_object->assign("warp_list_movetype", $warp_list_movetype);
					$template_object->assign("warp_list_sector", $warp_list_sector);
					$template_object->assign("move_result", $automove_result);
					$template_object->assign("l_autoroute_return", $l_autoroute_return);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."navcomp/autoroute_result.tpl");
					include ("footer.php");
					break;
				}
			}
		}
		$template_object->assign("part3", 1);
		$template_object->assign("warp_list_movetype", $warp_list_movetype);
		$template_object->assign("warp_list_sector", $warp_list_sector);
		$template_object->assign("move_result", $automove_result);
		$template_object->assign("endmovetype", $l_autoroute_warpfinal);
		$template_object->assign("endsector", $autoroute['start_sector']);
		$automove_result = array();
		autowarpmove($autoroute['start_sector']);
		$template_object->assign("endmove_result", $automove_result);
		$template_object->assign("l_autoroute_return", $l_autoroute_return);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."navcomp/autoroute_result.tpl");
		include ("footer.php");
		break;
}

?>
