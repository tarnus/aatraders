<?php
// This program is free software; you can redistribute it and/or modify it	
// under the terms of the GNU General Public License as published by the	  
// Free Software Foundation; either version 2 of the License, or (at your	 
// option) any later version.																
// 
// File: teams.php

include ("config/config.php");
include ("languages/$langdir/lang_teams.inc");
include ("globals/db_kill_player.inc");
include ("globals/cancel_bounty.inc");
include ("globals/calc_ownership.inc");

get_post_ifset("command, team_id, canceled, who, teamname, teamdesc, order, type, update, confirmed, invited, confirmleave, newcreator");

$title = $l_team_title;

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
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

/* Get user info */
$debug_query = $db->SelectLimit("SELECT {$db_prefix}players.*, {$db_prefix}teams.team_name, {$db_prefix}teams.description, {$db_prefix}teams.creator, {$db_prefix}teams.id
							FROM {$db_prefix}players
							LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team = {$db_prefix}teams.id
							WHERE {$db_prefix}players.player_id=$playerinfo[player_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$thisplayer_info = $debug_query->fields;

/*
	We do not want to query the database
	if it is not necessary.
*/
if ($thisplayer_info['team_invite'] != "") {
	/* Get invite info */
	$debug_query = $db->SelectLimit(" SELECT {$db_prefix}players.player_id, {$db_prefix}players.team_invite, {$db_prefix}teams.team_name,{$db_prefix}teams.id
								 FROM {$db_prefix}players
								 LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team_invite = {$db_prefix}teams.id
								 WHERE {$db_prefix}players.player_id=$playerinfo[player_id]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$invite_info = $debug_query->fields;
}

/*
	Get Team Info
*/
$team_id = stripnum($team_id);
if ($team_id)
{
	$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$team_id", 1);
	$team = $result_team->fields;
} else {
	$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$thisplayer_info[team]", 1);
	$team = $result_team->fields;
}

function change_planet_team($player_id, $team_id = 0)
{
	global $db, $db_prefix;

	$res = $db->Execute("SELECT DISTINCT sector_id FROM {$db_prefix}planets WHERE owner=$player_id AND base='Y'");
	$i=0;
	while(!$res->EOF){
		$sectors[$i] = $res->fields['sector_id'];
		$i++;
		$res->MoveNext();
	}

	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team=$team_id WHERE owner=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);

	if(!empty($sectors)){
		foreach($sectors as $sector){
			calc_ownership($sector);
		}
	}
}

function change_teammates_planets($old_team_id, $new_team_id)
{
	global $db, $db_prefix;

	$res = $db->Execute("SELECT DISTINCT sector_id FROM {$db_prefix}planets WHERE team=$old_team_id AND base='Y'");
	$i=0;
	while(!$res->EOF){
		$sectors[$i] = $res->fields['sector_id'];
		$i++;
		$res->MoveNext();
	}

	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team=$new_team_id WHERE team=$old_team_id");
	db_op_result($debug_query,__LINE__,__FILE__);

	if(!empty($sectors)){
		foreach($sectors as $sector){
			calc_ownership($sector);
		}
	}
}

function kick_off_planet($player_id, $team_id)
{
	global $db, $db_prefix;

	$result1 = $db->Execute("SELECT * from {$db_prefix}planets where owner = '$player_id' ");
	db_op_result($result1,__LINE__,__FILE__);

	if ($result1 > 0)
	{
		while (!$result1->EOF)
		{
			$row = $result1->fields;
			$result2 = $db->Execute("SELECT * from {$db_prefix}ships where on_planet = 'Y' and planet_id = '$row[planet_id]' and player_id <> '$player_id' ");
			db_op_result($result2,__LINE__,__FILE__);
			if ($result2 > 0)
			{
				while (!$result2->EOF )
				{
					$cur = $result2->fields;
					$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet = 'N',planet_id = '0' WHERE ship_id='$cur[ship_id]'");
					db_op_result($debug_query,__LINE__,__FILE__);

					playerlog($cur[player_id], "LOG0_PLANET_EJECT", "$cur[sector_id]|$row[character_name]");
					$result2->MoveNext();
				}
			}
			$result1->MoveNext();
		}
	}
}

function defense_vs_defense($player_id)
{
	global $db, $db_prefix;

	$result1 = $db->Execute("SELECT * from {$db_prefix}sector_defense where player_id = $player_id");
	db_op_result($result1,__LINE__,__FILE__);

	if ($result1 > 0)
	{
		while (!$result1->EOF)
		{
			$row = $result1->fields;
			$deftype = $row[defense_type] == 'fighters' ? 'Fighters' : 'Mines';
			$qty = $row['quantity'];
			$result2 = $db->Execute("SELECT * from {$db_prefix}sector_defense where sector_id = $row[sector_id] and player_id <> $player_id ORDER BY quantity DESC");
			db_op_result($result2,__LINE__,__FILE__);
			if ($result2 > 0)
			{
				while (!$result2->EOF && $qty > 0)
				{
					$cur = $result2->fields;
					$targetdeftype = $cur[defense_type] == 'fighters' ? $l_fighters : $l_mines;
					if ($qty > $cur['quantity'])
					{
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE defense_id = $cur[defense_id]");
						$qty -= $cur['quantity'];
						db_op_result($debug_query,__LINE__,__FILE__);

						$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense SET quantity = $qty where defense_id = $row[defense_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($cur[player_id], "LOG5_DEFS_DESTROYED", "$cur[quantity]|$targetdeftype|$row[sector_id]");
						playerlog($row[player_id], "LOG5_DEFS_DESTROYED", "$cur[quantity]|$deftype|$row[sector_id]");
					}else{
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE defense_id = $row[defense_id]");
						db_op_result($debug_query,__LINE__,__FILE__);

						$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense SET quantity=quantity - $qty WHERE defense_id = $cur[defense_id]");
						db_op_result($debug_query,__LINE__,__FILE__);

						playerlog($cur[player_id], "LOG5_DEFS_DESTROYED", "$qty|$targetdeftype|$row[sector_id]");
						playerlog($row[player_id], "LOG5_DEFS_DESTROYED", "$qty|$deftype|$row[sector_id]");
						$qty = 0;
					}
					$result2->MoveNext();
				}
			}
			$result1->MoveNext();
		}
		$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE quantity <= 0");
		db_op_result($debug_query,__LINE__,__FILE__);	  
	}
}

function showinfo($team_id,$isowner)
{
	global $thisplayer_info, $invite_info, $l_team_cancelinv, $team, $l_team_coord, $l_team_member, $l_options, $l_team_ed, $l_team_inv, $l_team_leave, $l_team_members, $l_score, $l_team_noinvites, $l_team_pending;
	global $l_team_noinvite, $l_team_ifyouwant, $l_team_tocreate, $l_clickme, $l_team_injoin, $l_team_tojoin, $l_team_reject, $l_team_or;
	global $db, $db_prefix, $l_team_eject;
	global $template_object;

	$result_team = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$team[id]", 1);
	$teamstuff = $result_team->fields;
	/* Heading */
	$template_object->assign("teamicon", $teamstuff['icon']);
	$template_object->assign("teamname", $team['team_name']);
	$template_object->assign("teamdescription", $team['description']);
	$template_object->assign("playerteammatch", $thisplayer_info['team'] == $team['id']);
	if ($thisplayer_info['team'] == $team['id'])
	{
		$template_object->assign("isplayercreator", $thisplayer_info['player_id'] == $team['creator']);
		$template_object->assign("playerteamid", $thisplayer_info['team']);
		$template_object->assign("l_team_ed", $l_team_ed);
		$template_object->assign("l_team_inv", $l_team_inv);
		$template_object->assign("l_team_cancelinv", $l_team_cancelinv);
		$template_object->assign("l_team_leave", $l_team_leave);
	}
	$template_object->assign("teaminvite", $thisplayer_info['team_invite']);
	$template_object->assign("l_team_noinvite", $l_team_noinvite);
	$template_object->assign("l_team_ifyouwant", $l_team_ifyouwant);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_team_tocreate", $l_team_tocreate);
	$template_object->assign("l_team_injoin", $l_team_injoin);
	$template_object->assign("inviteinfo", $invite_info['team_name']);
	$template_object->assign("l_team_tojoin", $l_team_tojoin);
	$template_object->assign("l_team_or", $l_team_or);
	$template_object->assign("l_team_reject", $l_team_reject);

	/* Main table */
	$result_zone = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE owner=$team_id and team_zone='Y'", 1);
	$zone = $result_zone->fields;

	if($zone['zone_color'] == "#000000")
		$zonecolor = "#400040";
	else $zonecolor = $zone['zone_color'];
	
	$template_object->assign("zonecolor", $zonecolor);
	$template_object->assign("l_team_members", $l_team_members);

	$count = 0;
	$result  = $db->Execute("SELECT * FROM {$db_prefix}players WHERE team=$team_id");
	while (!$result->EOF) {
		$member = $result->fields;
		$teammember[$count] = $member['character_name'];
		$memberscore[$count] = NUMBER($member['score']);
		$memberowner[$count] = ($isowner && ($member['player_id'] != $thisplayer_info['player_id']));
		if ($isowner && ($member['player_id'] != $thisplayer_info['player_id'])) {
			$memberid[$count] = $member['player_id'];
		} else {
			$iscreator[$count] = $member['player_id'] == $team['creator'];
		}
		$count++;
		$result->MoveNext();
	}

	$template_object->assign("teammember", $teammember);
	$template_object->assign("memberscore", $memberscore);
	$template_object->assign("memberowner", $memberowner);
	$template_object->assign("memberid", $memberid);
	$template_object->assign("iscreator", $iscreator);
	$template_object->assign("teamcount", $count);
	$template_object->assign("l_score", $l_score);
	$template_object->assign("l_team_coord", $l_team_coord);
	$template_object->assign("l_team_eject", $l_team_eject);
	$template_object->assign("l_team_pending", $l_team_pending);

	/* Displays for members name */
	$count = 0;
	$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players WHERE team_invite=$team_id");
	if ($res->RecordCount() > 0) {
		while (!$res->EOF) {
			$who = $res->fields;
			$membername[$count] = $who['character_name'];
			$count++;
			$res->MoveNext();
		}
	}
	$template_object->assign("membercount", $count);
	$template_object->assign("membername", $membername);
	$template_object->assign("l_team_noinvites", $l_team_noinvites);
}

switch ($command) {
	 case 1:	 // INFO on single team
		showinfo($team_id, 0);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-info.tpl");
		break;

	 case 2:	 // LEAVE
		if (!isset($confirmleave) || ($confirmleave == '') || (!$confirmleave)){
			$template_object->assign("confirmleave", 0);
			$template_object->assign("l_team_confirmleave", $l_team_confirmleave);
			$template_object->assign("teamname", $team['team_name']);
			$template_object->assign("command", $command);
			$template_object->assign("team_id", $team_id);
			$template_object->assign("l_yes", $l_yes);
			$template_object->assign("l_no", $l_no);
		}else{
			$template_object->assign("confirmleave", $confirmleave);
			if ($confirmleave == 1) {
				$res = $db->Execute("SELECT COUNT(*) as number_of_members
							FROM {$db_prefix}players
							WHERE team = $team_id");
				db_op_result($res,__LINE__,__FILE__);
				$template_object->assign("number_of_members", $res->fields['number_of_members']);
				if ($res->fields['number_of_members'] == 1) {
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_players WHERE player_id=$thisplayer_info[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
		 			$debug_query = $db->SelectLimit("SELECT forum_id FROM {$db_prefix}team_forums WHERE teams=$thisplayer_info[player_id]",1);
			  		db_op_result($debug_query,__LINE__,__FILE__);
				 	$forum_id = $debug_query->fields['forum_id'];
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_topics WHERE forum_id=$forum_id");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_posts WHERE forum_id=$forum_id");
					db_op_result($debug_query,__LINE__,__FILE__);
		 			$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_posts_text WHERE forum_id=$forum_id");
			  		db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forums WHERE teams=$thisplayer_info[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

		 			$debug_query = $db->SelectLimit("SELECT team_name FROM {$db_prefix}teams WHERE id=$team_id", 1);
			  		db_op_result($debug_query,__LINE__,__FILE__);
				 	$team_name = $debug_query->fields['team_name'];

					$debug_query = $db->Execute("DELETE FROM {$db_prefix}teams WHERE id=$team_id");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}zones WHERE owner=$team_id and team_zone='Y'");
					db_op_result($debug_query,__LINE__,__FILE__);
					$time = date("Y-m-d H:i:s");
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($thisplayer_info[player_id], $thisplayer_info[player_id], 'last player', '$time', " . $db->qstr($team_name) . ")");
					db_op_result($debug_query,__LINE__,__FILE__);

		  			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='0' WHERE player_id='$thisplayer_info[player_id]'");
			  		db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE team_invite=$team_id");
					db_op_result($debug_query,__LINE__,__FILE__);

					change_planet_team($thisplayer_info['player_id']);
			 		defense_vs_defense($playerinfo['player_id']);
				  	kick_off_planet($playerinfo['player_id'],$team_id);

					$l_team_onlymember = str_replace("[team_name]", "<b>$team[team_name]</b>", $l_team_onlymember);
					$template_object->assign("l_team_onlymember", $l_team_onlymember);
					playerlog($playerinfo['player_id'], "LOG0_TEAM_LEAVE", "$team[team_name]");
				} else {
					$template_object->assign("iscreator", ($team['creator'] == $playerinfo['player_id']));
					if ($team['creator'] == $playerinfo['player_id']) {
						$template_object->assign("l_team_youarecoord", $l_team_youarecoord);
						$template_object->assign("teamname", $team['team_name']);
						$template_object->assign("l_team_relinq", $l_team_relinq);
						$template_object->assign("team_id", $team_id);
						$template_object->assign("command", $command);
						$template_object->assign("l_team_newc", $l_team_newc);
						$template_object->assign("l_team_onlymember", $l_team_onlymember);
						$count = 0;
					 	$res = $db->Execute("SELECT character_name,player_id FROM {$db_prefix}players WHERE team=$team_id ORDER BY character_name ASC");
						while(!$res->EOF) {
							$row = $res->fields;
							if ($row['player_id'] != $team['creator']){
								$playerid[$count] = $row['player_id'];
								$playername[$count] = $row['character_name'];
								$count++;
							}
							$res->MoveNext();
	 					}
						$template_object->assign("count", $count);
						$template_object->assign("playerid", $playerid);
						$template_object->assign("playername", $playername);
						$template_object->assign("l_submit", $l_submit);
					} else {
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_players WHERE player_id=$thisplayer_info[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);

			 			$debug_query = $db->SelectLimit("SELECT team_name FROM {$db_prefix}teams WHERE id=$team_id", 1);
				  		db_op_result($debug_query,__LINE__,__FILE__);
					 	$team_name = $debug_query->fields['team_name'];

						$stamp = date("Y-m-d H:i:s");
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($thisplayer_info[player_id], $team_id, 'left team', '$stamp', " . $db->qstr($team_name) . ")");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='0', last_team=$team_id, left_team_time='$stamp' WHERE player_id='$thisplayer_info[player_id]'");
	  					db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE team_invite=$team_id");
						db_op_result($debug_query,__LINE__,__FILE__);

						change_planet_team($thisplayer_info['player_id']);

						$template_object->assign("l_team_youveleft", $l_team_youveleft);
						$template_object->assign("teamname", $team['team_name']);
						defense_vs_defense($playerinfo['player_id']);
						kick_off_planet($playerinfo['player_id'],$team_id);
						playerlog($playerinfo['player_id'], "LOG0_TEAM_LEAVE", "$team[team_name]");
		 				playerlog($team['creator'], "LOG0_TEAM_NOT_LEAVE", "$thisplayer_info[character_name]");
					}
				}
			}

			if ($confirmleave == 2) { // owner of a team is leaving and set a new owner
				$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=$newcreator", 1);
				$newcreatorname = $res->fields;
				$template_object->assign("l_team_youveleft", $l_team_youveleft);
				$template_object->assign("teamname", $team['team_name']);
				$template_object->assign("l_team_relto", $l_team_relto);
				$template_object->assign("newcreator", $newcreatorname['character_name']);
		  		$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_players WHERE player_id=$thisplayer_info[player_id]");
			 	db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}team_forums SET teams=$newcreator WHERE teams=$thisplayer_info[player_id]");
			 	db_op_result($debug_query,__LINE__,__FILE__);

	 			$debug_query = $db->SelectLimit("SELECT team_name FROM {$db_prefix}teams WHERE id=$team_id", 1);
		  		db_op_result($debug_query,__LINE__,__FILE__);
			 	$team_name = $debug_query->fields['team_name'];

				$stamp = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($thisplayer_info[player_id], $team_id, 'left team', '$stamp', " . $db->qstr($team_name) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='0', last_team=$team_id, left_team_time='$stamp' WHERE player_id='$thisplayer_info[player_id]'");
				db_op_result($debug_query,__LINE__,__FILE__);
	 			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team=$newcreator WHERE team=$thisplayer_info[player_id]");
		 		db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE team_invite=$thisplayer_info[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets set team=$newcreator WHERE team = $thisplayer_info[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}teams SET creator=$newcreator, id=$newcreator WHERE id=$thisplayer_info[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}zones SET owner=$newcreator WHERE team_zone='Y' AND owner=$thisplayer_info[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				change_teammates_planets($thisplayer_info['player_id'], $newcreator);
				defense_vs_defense($thisplayer_info['player_id']);
				kick_off_planet($thisplayer_info['player_id'],$team_id);

				playerlog($playerinfo[player_id], "LOG0_TEAM_NEWLEAD", "$team[team_name]|$newcreatorname[character_name]");
				playerlog($newcreator, "LOG0_TEAM_LEAD","$team[team_name]");
			}
		}
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-leave.tpl");
		break;

	 case 3: // JOIN
		$template_object->assign("team_join_count", $thisplayer_info['team_join_count']);
		$template_object->assign("max_team_changes", $max_team_changes);
		if($thisplayer_info['team_join_count'] < $max_team_changes){
			$template_object->assign("playerteam", $thisplayer_info['team']);
			if ($thisplayer_info['team'] <> 0)
			{
				$template_object->assign("l_team_leavefirst", $l_team_leavefirst);
			}
			else
			{
				$template_object->assign("isplayerteaminvite", ($thisplayer_info['team_invite'] == $team_id));
				if ($thisplayer_info['team_invite'] == $team_id)
				{
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team=$team_id,team_invite=0, team_join_count=team_join_count+1 WHERE player_id=$thisplayer_info[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					change_planet_team($thisplayer_info['player_id'], $team_id);
					$template_object->assign("l_team_welcome", $l_team_welcome);
					$template_object->assign("teamname", $team['team_name']);
					playerlog($thisplayer_info['player_id'], "LOG0_TEAM_JOIN", "$team[team_name]");
					playerlog($team['creator'], "LOG0_TEAM_NEWMEMBER", "$team[team_name]|$thisplayer_info[character_name]");

					$time = date("Y-m-d H:i:s");
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($thisplayer_info[player_id], $team_id, 'joined team', '$time', " . $db->qstr($team['team_name']) . ")");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}team_forum_players (player_id, playername, signupdate, currenttime) values ($thisplayer_info[player_id], " . $db->qstr($thisplayer_info['character_name']) . ", '$time', '$time')");
					db_op_result($debug_query,__LINE__,__FILE__);
				}else{
					$template_object->assign("l_team_noinviteto", $l_team_noinviteto);
				}
			}
		}
		else
		{
			$template_object->assign("l_team_cantjoin", $l_team_cantjoin);
		}
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-join.tpl");
		break;

	 case 4:
		 // Cancel Invitation

		$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players WHERE team_invite=$team_id ORDER BY character_name ASC");
		$total = $res->RecordCount();
		$template_object->assign("canceled", (!isset($canceled) || ($canceled == '') || !($canceled)));
		if (!isset($canceled) || ($canceled == '') || !($canceled))
		{
			$template_object->assign("command", $command);
			$template_object->assign("team_id", $team_id);
			$template_object->assign("l_team_cancelplayer", $l_team_cancelplayer);
			$count = 0;
			while(!$res->EOF) {
				$row = $res->fields;
				$playerid[$count] = $row['player_id'];
				$playername[$count] = $row['character_name'];
				$count++;
				$res->MoveNext();
			}
			$template_object->assign("count", $count);
			$template_object->assign("l_submit", $l_submit);
			$template_object->assign("playerid", $playerid);
			$template_object->assign("playername", $playername);
		} else {
			$template_object->assign("isplayerteam", ($thisplayer_info['team'] == $team_id));
			if($thisplayer_info['team'] == $team_id)
			{
				$res = $db->SelectLimit("SELECT character_name,team_invite FROM {$db_prefix}players WHERE player_id=$who", 1);
				$newpl = $res->fields;
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE player_id=$who");
				db_op_result($debug_query,__LINE__,__FILE__);
				$template_object->assign("l_team_cancelinvites", $l_team_cancelinvites);
				$template_object->assign("playername", $newpl['character_name']);
				playerlog($who,"LOG0_TEAM_CANCEL", "$team[team_name]");
			}else{
				$template_object->assign("l_team_notyours", $l_team_notyours);
			}
		}
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-cancelinvite.tpl");
		break;

	 case 5: // Eject member
		$template_object->assign("isplayerteam", ($thisplayer_info['team'] == $team['id']));
		if ($thisplayer_info['team'] == $team['id'])
		{
			$who = stripnum($who);
			$result = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$who", 1);
			$whotoexpel = $result->fields;
			$template_object->assign("confirmed", $confirmed);
			if (!$confirmed) {
				$template_object->assign("l_team_ejectsure", $l_team_ejectsure);
				$template_object->assign("playername", $whotoexpel['character_name']);
				$template_object->assign("command", $command);
				$template_object->assign("who", $who);
				$template_object->assign("l_yes", $l_yes);
				$template_object->assign("l_no", $l_no);
			} else {
				/*
				check whether the player we are ejecting might have already left in the meantime
				should go here	 if ($whotoexpel[team] ==
				*/
	 			$debug_query = $db->SelectLimit("SELECT team_name FROM {$db_prefix}teams WHERE id=$thisplayer_info[team]", 1);
		  		db_op_result($debug_query,__LINE__,__FILE__);
			 	$team_name = $debug_query->fields['team_name'];

				$stamp = date("Y-m-d H:i:s");
				change_planet_team($who);

				$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($who, $whotoexpel[team], 'kicked', '$stamp', " . $db->qstr($team_name) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='0', last_team=$whotoexpel[team], left_team_time='$stamp'  WHERE player_id='$who'");
				db_op_result($debug_query,__LINE__,__FILE__);

				$result2 = $db->Execute("SELECT * from {$db_prefix}ships where on_planet = 'Y' and ship_id = $whotoexpel[currentship]");
				db_op_result($result2,__LINE__,__FILE__);

				if ($result2 > 0)
				{
					$cur = $result2->fields;
					$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet = 'N',planet_id = '0' WHERE ship_id='$cur[ship_id]'");
					db_op_result($debug_query,__LINE__,__FILE__);

					playerlog($cur['player_id'], "LOG0_PLANET_EJECT", "$cur[sector_id]|$whotoexpel[character_name]");
				}

				$debug_query = $db->Execute("DELETE FROM {$db_prefix}team_forum_players WHERE player_id=$who");
				db_op_result($debug_query,__LINE__,__FILE__);
				playerlog($who, "LOG0_TEAM_KICK", "$team[team_name]");
				$template_object->assign("l_team_ejected", $l_team_ejected);
				$template_object->assign("playername", $whotoexpel['character_name']);
				defense_vs_defense($who);
				kick_off_planet($who, $whotoexpel['team']);
			}
		}else{
			adminlog("LOG0_CHEAT_TEAM", "$thisplayer_info[character_name]|$ip");
			$template_object->assign("l_team_cheater", $l_team_cheater);
			$template_object->assign("l_team_punishment", $l_team_punishment);
			$template_object->assign("l_die_vapor", $l_die_vapor);
			$template_object->assign("l_die_please", $l_die_please);
			db_kill_player($thisplayer_info['player_id'], 0, 0);
			cancel_bounty($thisplayer_info['player_id']);
			adminlog("LOG0_ADMIN_HARAKIRI", "$thisplayer_info[character_name]|$ip");
			playerlog($thisplayer_info[player_id], "LOG0_HARAKIRI", "$ip");
		} 
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-ejectmember.tpl");
		break;

	 case 6: // Create Team
		$template_object->assign("team_join_count", $thisplayer_info['team_join_count']);
		$template_object->assign("max_team_changes", $max_team_changes);
		if($thisplayer_info['team_join_count'] < $max_team_changes){
			$template_object->assign("playerteam", $thisplayer_info['team']);
			if($thisplayer_info['team'] == 0){
				$teamname = trim($teamname);
				$teamdesc = trim($teamdesc);
				$template_object->assign("isteamname", (!isset($teamname) || ($teamname =='')));
				if (!isset($teamname) || ($teamname ==''))
	 			{
					$template_object->assign("l_team_entername", $l_team_entername);
					$template_object->assign("command", $command);
					$template_object->assign("l_team_enterdesc", $l_team_enterdesc);
					$template_object->assign("l_submit", $l_submit);
					$template_object->assign("l_reset", $l_reset);
	 			} else {
		  			$teamname = htmlspecialchars($teamname,ENT_QUOTES);
					$teamdesc = htmlspecialchars($teamdesc,ENT_QUOTES);
					$res = $db->Execute("SELECT * FROM {$db_prefix}teams WHERE LOWER(team_name)=LOWER(" . $db->qstr($teamname) . ")");
					$template_object->assign("count", $res->RecordCount());
					if($res->RecordCount() == 0){
						$debug_query = $db->SelectLimit("SELECT zone_color FROM {$db_prefix}zones WHERE owner=$thisplayer_info[player_id] and team_zone='N'", 1);
						db_op_result($debug_query,__LINE__,__FILE__);
						$zonecolor = $debug_query->fields['zone_color'];
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}teams (id,creator,team_name,description, icon) VALUES ('$thisplayer_info[player_id]','$thisplayer_info[player_id]'," . $db->qstr($teamname) . ", " . $db->qstr($teamdesc) . ", 'default_icon.gif')");
			 			db_op_result($debug_query,__LINE__,__FILE__);

						$debug_query = $db->Execute("INSERT INTO {$db_prefix}zones (zone_name,owner,team_zone,allow_attack,allow_planetattack,allow_warpedit,allow_planet,allow_trade,allow_defenses,max_hull,zone_color) VALUES(" . $db->qstr($teamname . "'s Empire") . ", $thisplayer_info[player_id], 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 0, '$zonecolor')");
		 				db_op_result($debug_query,__LINE__,__FILE__);

						$time = date("Y-m-d H:i:s");
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($thisplayer_info[player_id], $thisplayer_info[player_id], 'created team', '$time', " . $db->qstr($teamname) . ")");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team='$thisplayer_info[player_id]', team_join_count=team_join_count+1 WHERE player_id='$thisplayer_info[player_id]'");
		 				db_op_result($debug_query,__LINE__,__FILE__);

						$debug_query = $db->Execute("INSERT INTO {$db_prefix}team_forums (forum_name, forum_desc, private, teams) values (" . $db->qstr($teamname) . ", " . $db->qstr($teamdesc) . ", 1, $thisplayer_info[player_id])");
			 			db_op_result($debug_query,__LINE__,__FILE__);

						$time = date("Y-m-d H:i:s");
			 			$debug_query = $db->Execute("INSERT INTO {$db_prefix}team_forum_players (player_id, playername, signupdate, currenttime, admin) values ($thisplayer_info[player_id], " . $db->qstr($thisplayer_info['character_name']) . ", '$time', '$time', 1)");
				  		db_op_result($debug_query,__LINE__,__FILE__);

						change_planet_team($thisplayer_info['player_id'], $thisplayer_info['player_id']);
						$template_object->assign("l_team", $l_team);
						$template_object->assign("teamname", $teamname);
						$template_object->assign("l_team_hcreated", $l_team_hcreated);
		 				playerlog($thisplayer_info['player_id'], "LOG0_TEAM_CREATE", "$teamname");
					}
					else
					{
						$template_object->assign("l_team_nocreatesamename", $l_team_nocreatesamename);
					}
				}
			}else{
				$template_object->assign("l_team_leavefirst", $l_team_leavefirst);
			}
		}
		else
		{
			$template_object->assign("l_team_cantcreate", $l_team_cantcreate);
		}
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-createteam.tpl");
		break;

	 case 7: // INVITE player
		$result  = $db->Execute("SELECT * FROM {$db_prefix}players WHERE team=$team_id");
		$total = $result->RecordCount();

		$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players WHERE team_invite=$team_id");
		$total = $total + $res->RecordCount();
		$template_object->assign("notteamlimit", ($total < $team_limit));
		if($total < $team_limit){
			$template_object->assign("invited", (!isset($invited) || ($invited == '') || !($invited)));
			if (!isset($invited) || ($invited == '') || !($invited))
			{
				$template_object->assign("command", $command);
				$template_object->assign("team_id", $team_id);
				$template_object->assign("l_team_selectp", $l_team_selectp);
				$template_object->assign("command", $command);
				$count = 0;
				$res = $db->Execute("SELECT character_name,player_id FROM {$db_prefix}players WHERE team<>$team_id and player_id > 3 ORDER BY character_name ASC");
				while(!$res->EOF) {
					$row = $res->fields;
					if ($row[player_id] != $team['creator']){
						$playerid[$count] = $row['player_id'];
						$playername[$count] = $row['character_name'];
					}
					$count++;
					$res->MoveNext();
				}
				$template_object->assign("count", $count);
				$template_object->assign("l_submit", $l_submit);
				$template_object->assign("playerid", $playerid);
				$template_object->assign("playername", $playername);
			} else {
				$template_object->assign("team_join_count", $thisplayer_info['team_join_count']);
				$template_object->assign("max_team_changes", $max_team_changes);
				$res = $db->SelectLimit("SELECT character_name,team_invite, team_join_count FROM {$db_prefix}players WHERE player_id=$who", 1);
				$newpl = $res->fields;
				if($newpl['team_join_count'] < $max_team_changes){
					$template_object->assign("issameteam", ($thisplayer_info['team'] == $team_id));
					if($thisplayer_info['team'] == $team_id)
					{
						$template_object->assign("team_invite", $newpl['team_invite']);
						if ($newpl['team_invite']) 
						{
							$l_team_isorry = str_replace("[name]", $newpl['character_name'], $l_team_isorry);
							$template_object->assign("l_team_isorry", $l_team_isorry);
						}else{
							$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=$team_id WHERE player_id=$who");
							db_op_result($debug_query,__LINE__,__FILE__);
							$template_object->assign("l_team_plinvted", $l_team_plinvted);
							playerlog($who,"LOG0_TEAM_INVITE", "$team[team_name]");
						}
					}else{
						$template_object->assign("l_team_notyours", $l_team_notyours);
					}
				}
				else
				{
					$template_object->assign("l_team_cantinvite", $l_team_cantinvite);
				}
			}
		}else{
			$template_object->assign("l_team_full", $l_team_full);
		}
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-invite.tpl");
		break;

	 case 8: // REFUSE invitation
		$template_object->assign("l_team_refuse", $l_team_refuse);
		$template_object->assign("inviteteam_name", $invite_info['team_name']);
		$debug_query = $db->SelectLimit("SELECT team_name FROM {$db_prefix}teams WHERE id=$thisplayer_info[team_invite]", 1);
  		db_op_result($debug_query,__LINE__,__FILE__);
	 	$team_name = $debug_query->fields['team_name'];

		$time = date("Y-m-d H:i:s");
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($thisplayer_info[player_id], $thisplayer_info[team_invite], 'refused invite', '$time', " . $db->qstr($team_name) . ")");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_invite=0 WHERE player_id=$thisplayer_info[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		playerlog($team['creator'], "LOG0_TEAM_REJECT", "$thisplayer_info[character_name]|$invite_info[team_name]");
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-refuse.tpl");
		break;

	 case 9: // Edit Team
		$template_object->assign("teammatch", ($thisplayer_info['team'] == $team_id));
		if ($thisplayer_info['team'] == $team_id) {
			$template_object->assign("update", (!isset($update) || ($update == '')));
			if (!isset($update) || ($update == ''))
			{
				$template_object->assign("l_team_edname", $l_team_edname);
				$template_object->assign("command", $command);
				$template_object->assign("team_id", $team_id);
				$template_object->assign("team_name", $team['team_name']);
				$template_object->assign("l_team_eddesc", $l_team_eddesc);
				$template_object->assign("description", $team['description']);
				$template_object->assign("l_submit", $l_submit);
				$template_object->assign("l_reset", $l_reset);
			} else {
				$teamname = trim($teamname);
				$teamdesc = trim($teamdesc);
	  			$teamname = htmlspecialchars($teamname,ENT_QUOTES);
				$teamdesc = htmlspecialchars($teamdesc,ENT_QUOTES);
				$res = $db->Execute("SELECT * FROM {$db_prefix}teams WHERE LOWER(team_name)=LOWER(" . $db->qstr($teamname) . ") and id!=$team_id");
				$template_object->assign("count", $res->RecordCount());
				if($res->RecordCount() == 0){
					$debug_query = $db->Execute("UPDATE {$db_prefix}teams SET team_name=" . $db->qstr($teamname) . ", description=" . $db->qstr($teamdesc) . " WHERE id=$team_id");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("UPDATE {$db_prefix}zones SET zone_name=" . $db->qstr($teamname . "'s Empire") . " WHERE owner=$team_id and team_zone='Y'");
					db_op_result($debug_query,__LINE__,__FILE__);
					$template_object->assign("l_team", $l_team);
					$template_object->assign("teamname", $teamname);
					$template_object->assign("l_team_hasbeenr", $l_team_hasbeenr);
					/*
						Adding a log entry to all members of the renamed team
					*/
					$time = date("Y-m-d H:i:s");
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}player_team_history (player_id, history_team_id, info, left_team, history_team_name) values ($team_id, $team_id, 'edit team', '$time', " . $db->qstr($teamname) . ")");
					db_op_result($debug_query,__LINE__,__FILE__);

					$result_team_name = $db->Execute("SELECT player_id FROM {$db_prefix}players WHERE team=$team_id AND player_id<>$thisplayer_info[player_id]");
					playerlog($thisplayer_info['player_id'], "LOG0_TEAM_RENAME", "$teamname");
					while (!$result_team_name->EOF) {
						$teamname_array = $result_team_name->fields;
						playerlog($teamname_array['player_id'], "LOG0_TEAM_M_RENAME", "$teamname");
						$result_team_name->MoveNext();
					}
				}
				else
				{
					$template_object->assign("l_team_noupdatesamename", $l_team_noupdatesamename);
				}
			}
		}else{
			$template_object->assign("l_team_error", $l_team_error);
		}
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-edit.tpl");
		break;

	 default:
		if (!$thisplayer_info['team']) {
			$template_object->assign("l_team_notmember", $l_team_notmember);
			$template_object->assign("l_team_noinvite", $l_team_noinvite);
			$template_object->assign("playerteamid", $thisplayer_info['team']);
			$template_object->assign("l_team_ifyouwant", $l_team_ifyouwant);
			$template_object->assign("l_team_tocreate", $l_team_tocreate);
			$template_object->assign("l_team_injoin", $l_team_injoin);
			$template_object->assign("l_team_tojoin", $l_team_tojoin);
			$template_object->assign("l_team_tocreate", $l_team_tocreate);
			$template_object->assign("l_team_reject", $l_team_reject);
			$template_object->assign("teaminvite", $thisplayer_info['team_invite']);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("inviteinfo", $invite_info['team_name']);
		} else {
			if ($thisplayer_info['team'] < 0) {
				$thisplayer_info['team'] = -$thisplayer_info['team'];
				$result = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$thisplayer_info[team]", 1);
				$team_id = $result->fields;
				$template_object->assign("teamname", $team_id['team_name']);
				$template_object->assign("l_team_urejected", $l_team_urejected);
				$template_object->assign("l_clickme", $l_clickme);
				$template_object->assign("l_team_menu", $l_team_menu);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."teams-reject.tpl");
				break;
			}
			$result = $db->Execute("SELECT * FROM {$db_prefix}teams WHERE id=$thisplayer_info[team]");
			$team_id = $result->fields;
			if ($thisplayer_info['team_invite']) {
				$result = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$thisplayer_info[team_invite]", 1);
				$whichinvitingteam = $result->fields;
			}
			$isowner = ($thisplayer_info['player_id'] == $team_id['creator']);
			showinfo($thisplayer_info['team'],$isowner);
		}

		$res = $db->Execute("SELECT * FROM {$db_prefix}teams");
		$teams_count = $res->RecordCount();
		$template_object->assign("teams_count", $teams_count);
		if ($teams_count > 0) 
		{
			$template_object->assign("l_team_galax", $l_team_galax);

			if ($type == "d") {
				$type = "a";
				$by = "ASC";
			} else {
				$type = "d";
				$by = "DESC";
			}

			$template_object->assign("type", $type);
			$template_object->assign("l_name", $l_name);
			$template_object->assign("l_team_members", $l_team_members);
			$template_object->assign("l_team_coord", $l_team_coord);
			$template_object->assign("l_score", $l_score);

			$sql_query = "SELECT {$db_prefix}players.character_name,
						COUNT(*) as number_of_members,
						SUM({$db_prefix}players.score) as total_score,
						{$db_prefix}teams.id,
						{$db_prefix}teams.team_name,
						{$db_prefix}teams.icon,
						{$db_prefix}teams.creator
						FROM {$db_prefix}players, {$db_prefix}ships, {$db_prefix}teams
						WHERE {$db_prefix}players.team = {$db_prefix}teams.id AND {$db_prefix}ships.ship_id = {$db_prefix}players.currentship
						AND {$db_prefix}players.destroyed != 'Y'
						GROUP BY {$db_prefix}teams.team_name";

			/*
				Setting if the order is Ascending or descending, if any.
				Default is ordered by teams.team_name
			*/
			if ($order)
			{
				$sql_query = $sql_query ." ORDER BY " . $order . " $by";
			}
			$res = $db->Execute($sql_query);
			$count = 0;
			while (!$res->EOF) {
				$row = $res->fields;
				$teamlisticon[$count] = $row['icon'];
				$teamlistid[$count] = $row['id'];
				$teamlistname[$count] = $row['team_name'];
				$teamlistnumber[$count] = $row['number_of_members'];

				$sql_query_2 = "SELECT character_name FROM {$db_prefix}players WHERE player_id = $row[id]";
				$res2 = $db->SelectLimit($sql_query_2, 1);
				$teamlistcname[$count] = $res2->fields['character_name'];

				$teamlistscore[$count] = NUMBER($row['total_score']);

				$count++;
				$res->MoveNext();
			}
			$template_object->assign("teamlistcname", $teamlistcname);
			$template_object->assign("teamlistscore", $teamlistscore);
			$template_object->assign("teamlisticon", $teamlisticon);
			$template_object->assign("teamlistid", $teamlistid);
			$template_object->assign("teamlistname", $teamlistname);
			$template_object->assign("teamlistnumber", $teamlistnumber);
			$template_object->assign("totalteamcount", $count);
			$template_object->assign("color", $color);
		}else{
			$template_object->assign("l_team_noteams", $l_team_noteams);
		}

		$template_object->assign("max_team_changes", $max_team_changes);
		$template_object->assign("team_join_count", $thisplayer_info['team_join_count']);
		$template_object->assign("l_team_allowedfront", $l_team_allowedfront);
		$template_object->assign("l_team_reachedlimit", $l_team_reachedlimit);
		$template_object->assign("l_team_allowedback", $l_team_allowedback);
		$template_object->assign("l_team_noteams", $l_team_noteams);

		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_team_menu", $l_team_menu);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."teams-default.tpl");
		break;
} // switch ($command)

include ("footer.php");
?>

