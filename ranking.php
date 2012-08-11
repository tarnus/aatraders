<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: ranking.php

include ("config/config.php");
include ("languages/$langdir/lang_ranking.inc");
include ("languages/$langdir/lang_teams.inc");
include ("globals/gen_score.inc");
include ("globals/player_insignia_name.inc");

get_post_ifset("sort, page");

$title = "Player Rankings";

$noreturn = 1;
$isonline = checklogin();

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if($showzeroranking == 1)
	$showzero = "";
else $showzero = "{$db_prefix}players.turns_used != 0 and";

if ($hide_admin_rank == 1)
{
	$query = " AND {$db_prefix}players.player_id > 3 ";
}
else
{
	$query = " ";
}

if($isonline != 1){
	if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
		include ("globals/base_template_data.inc");
	}
	else
	{
		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);
	}
}
else
{
	if(time() > (@filemtime($gameroot . "templates_c/rankingupdate.txt") + 1800) || !file_exists($gameroot . "templates_c/rankingupdate.txt"))
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}players, {$db_prefix}ships " .
					" WHERE ".$showzero." {$db_prefix}players.player_id = {$db_prefix}ships.player_id and {$db_prefix}players.destroyed!='Y' and {$db_prefix}players.player_id > 3 and  {$db_prefix}players.currentship={$db_prefix}ships.ship_id " .
					"and email NOT LIKE '%@npc' ". $query);
		while (!$res->EOF)
		{
			$row = $res->fields;
			gen_score($row['player_id']);
			$res->MoveNext();
		}
	}
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}
 
$debug_query = $db->SelectLimit("SELECT rating FROM {$db_prefix}players order by rating DESC", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$top_rating = $debug_query->fields['rating'];

$debug_query = $db->SelectLimit("SELECT rating FROM {$db_prefix}players order by rating ASC", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$bottom_rating = $debug_query->fields['rating'];

$lowend_neutral = floor($bottom_rating * ($neutral_neg_percent / 100));
$highend_neutral = floor($top_rating * ($neutral_pos_percent / 100));

$res = $db->Execute("SELECT count({$db_prefix}players.player_id) as total FROM {$db_prefix}players, {$db_prefix}ships " .
					" WHERE ".$showzero." {$db_prefix}players.player_id = {$db_prefix}ships.player_id and {$db_prefix}players.destroyed!='Y' and {$db_prefix}players.player_id > 3 and  {$db_prefix}players.currentship={$db_prefix}ships.ship_id " .
					"and email NOT LIKE '%@npc' ". $query);

$num_players = $res->fields['total'];

if(!empty($playerinfo['player_id'])){
	gen_score($playerinfo['player_id']);
}

if ((!isset($page)) || ($page == ''))
{
	$page = 0;
}

$temp = floor($num_players / $max_rank);

if ($page == -1)
{
	$page = 0;
	$max_rank = $num_players;
}

if ($sort == "turns")
{
	$by = "turns_used DESC";
}
elseif ($sort == "kill_efficiency")
{
	$by = "kill_efficiency2 DESC";
}
elseif ($sort == "login")
{
	$by = "logged_out ASC, last_login DESC,character_name ASC";
}
elseif ($sort == "good")
{
	$by = "rating DESC";
}
elseif ($sort == "bad")
{
	$by = "rating ASC";
}
elseif ($sort == "team")
{
	$by = "{$db_prefix}teams.team_name DESC, character_name ASC";
}
elseif ($sort == "efficiency")
{
	$by = "efficiency DESC";
}
elseif ($sort == "kills")
{
	$by = "kills DESC";
}
elseif ($sort == "deaths")
{
	$by = "deaths DESC";
}
elseif ($sort == "captures")
{
	$by = "captures DESC";
}
elseif ($sort == "lost")
{
	$by = "planets_lost DESC";
}
elseif ($sort == "built")
{
	$by = "planets_built DESC";
}
elseif ($sort == "experience")
{
	$by = "experience DESC";
}
elseif ($sort == "name")
{
	$by = "character_name ASC";
}
elseif ($sort == "based")
{
	$by = "planets_based DESC";
}
elseif ($sort == "destroyed")
{
	$by = "planets_destroyed DESC";
}
else
{
	$by = "score DESC,character_name ASC";
}
 
$res = $db->Execute("SELECT ({$db_prefix}players.kill_efficiency / {$db_prefix}players.kills) as kill_efficiency2, {$db_prefix}players.kill_efficiency, {$db_prefix}players.experience, {$db_prefix}players.email, {$db_prefix}players.score, {$db_prefix}players.attackscore, {$db_prefix}players.player_id, " .
                        "{$db_prefix}players.character_name, {$db_prefix}players.avatar, {$db_prefix}players.kills, {$db_prefix}players.deaths, 
						{$db_prefix}players.captures, {$db_prefix}players.planets_lost, {$db_prefix}players.planets_built, {$db_prefix}players.planets_based, {$db_prefix}players.planets_destroyed, 
						{$db_prefix}players.profile_id, " .
                        "{$db_prefix}players.turns_used, {$db_prefix}players.last_login, " .
                        "{$db_prefix}players.rating, {$db_prefix}players.logged_out, " .
                        "{$db_prefix}teams.team_name, " .
                        "IF({$db_prefix}players.turns_used<150,0,ROUND({$db_prefix}players.score/{$db_prefix}players.turns_used)) " .
                        "AS efficiency FROM {$db_prefix}players LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team " .
                        "= {$db_prefix}teams.id LEFT JOIN {$db_prefix}ships ON " .
                        "{$db_prefix}players.player_id={$db_prefix}ships.player_id WHERE ".$showzero." {$db_prefix}players.currentship={$db_prefix}ships.ship_id and {$db_prefix}players.destroyed!='Y' " .
                        "and email NOT LIKE '%@npc'".$query." ORDER BY $by  LIMIT ". $page * $max_rank .",$max_rank");
db_op_result($res,__LINE__,__FILE__);

$template_object->assign("sort", $sort);
$template_object->assign("multiplepages", $temp);
$template_object->assign("pages", $pages);
$template_object->assign("max_rank", $max_rank);
$template_object->assign("allselected", $allselected);
$template_object->assign("l_all", $l_all);
$template_object->assign("l_submit", $l_submit);
$template_object->assign("prevlink", $page - 1);
$template_object->assign("nextlink", $page + 1);
$template_object->assign("l_ranks_next", $l_ranks_next);
$template_object->assign("l_ranks_prev", $l_ranks_prev);
$template_object->assign("res", $res);
$template_object->assign("l_ranks_none", $l_ranks_none);
$template_object->assign("l_ranks_select", $l_ranks_select);
$template_object->assign("l_ranks_page", $l_ranks_page);
$template_object->assign("l_ranks_killefficiency", $l_ranks_killefficiency);

$i = 1;

if ($res)
{
	$rankto = ($page * $max_rank + $res->recordcount());

	$template_object->assign("l_ranks_pnum", $l_ranks_pnum);
	$template_object->assign("l_ranks_show", $l_ranks_show);
	$template_object->assign("l_ranks_dships", $l_ranks_dships);
	$template_object->assign("l_ranks_to", $l_ranks_to);
	$template_object->assign("l_ranks_standing", $l_ranks_standing);
	$template_object->assign("l_score", $l_score);
	$template_object->assign("page", $page);
	$template_object->assign("l_ranks_rank", $l_ranks_rank);
	$template_object->assign("l_player", $l_player);
	$template_object->assign("l_turns_used", $l_turns_used);
	$template_object->assign("l_ranks_lastlog", $l_ranks_lastlog);
	$template_object->assign("l_ranks_good", $l_ranks_good);
	$template_object->assign("l_team", $l_team);
	$template_object->assign("l_ranks_online", $l_ranks_online);
	$template_object->assign("l_ranks_rating", $l_ranks_rating);
	$template_object->assign("l_ranks_evil", $l_ranks_evil);
	$template_object->assign("num_players", NUMBER($num_players));
	$template_object->assign("rankfrom", ($page * $max_rank + 1));
	$template_object->assign("userid", $_SESSION['session_player_id']);
	$template_object->assign("rankto", $rankto);
	$template_object->assign("l_ranks_kills", $l_ranks_kills);
	$template_object->assign("l_ranks_deaths", $l_ranks_deaths);
	$template_object->assign("l_ranks_captures", $l_ranks_captures);
	$template_object->assign("l_ranks_lost", $l_ranks_lost);
	$template_object->assign("l_ranks_built", $l_ranks_built);
	$template_object->assign("l_ranks_based", $l_ranks_based);
	$template_object->assign("l_ranks_destroyed", $l_ranks_destroyed);
	$template_object->assign("l_ranks_experience", $l_ranks_experience);

	$rankcount = 0;
	$playerscore=$playerinfo['attackscore']*$playerinfo['attackscore'];

	$file_open = 0;
	if($by == "score DESC,character_name ASC" && $page == 0 && time() > (@filemtime($gameroot . "templates_c/rankingupdate.txt") + 1800))
	{
		@unlink($gameroot."templates_c/rankingupdate.txt");
		$file = fopen($gameroot . "templates_c/rankingupdate.txt","w") or die ("Failed opening file: enable write permissions for '" . $gameroot . "templates_c/rankingupdate.txt'");
		$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
		@fwrite($file, "server:$game_name\n");
		$gm_url = $gameurl . $gamepath;
		@fwrite($file, "url:$gm_url\n");
		@fwrite($file, "version:$release_version\n");
		@fwrite($file, "page_size:20\n"); // this is the total number of lines for each block of player data
		$file_open = 1;
	}

	while (!$res->EOF)
	{
		$row = $res->fields;
//		$rating = sign($row['rating']) * round(sqrt( abs($row['rating']) ));
		if($row['rating'] < $lowend_neutral && $row['rating'] < (($neutral_safezone / 2) - $neutral_safezone))
		{
			$rating = $l_ranks_evil;
		}
		else
		if($row['rating'] > $highend_neutral && $row['rating'] > ($neutral_safezone / 2))
		{
			$rating = $l_ranks_good;
		}
		else
		{
			$rating = $l_ranks_neutral;
		}

		$temp_turns = $row['turns_used'];
		if ($temp_turns <= 0)
		{
			$temp_turns = 1;
		}

		$curtime = TIME();
		$lasttime = strtotime($row['last_login']);
		$difftime = ($curtime - $lasttime) / 60;
		$online = "";
		if ($difftime <= 5) 
		{
			$online = "Online";
		}else{
			$online = "";
		}

		$lastlogin = date($local_date_full_format, strtotime($row['last_login']));

		$playerid[$rankcount] = $row['player_id'];

		$rankprofileid[$rankcount] =  $row['profile_id'];
		$ranknumber[$rankcount] =  NUMBER($i + ($page * $max_rank));
		$rankscore[$rankcount] =  NUMBER($row['score']);
		// bounty check
		
		 $rankbounty[$rankcount]="";	
		if ($_SESSION['session_player_id'] != 0){
			$targetscore=$row['attackscore'] * $row['attackscore'];
			if ($targetscore==0){
				$targetscore=1;
			}
			if ($playerscore==0){
				$playerscore=1;
			}
			$bratio=$targetscore / $playerscore;
			$rankbounty[$rankcount]="";	

			if ($_SESSION['session_player_id'] != $playerid[$i]){
				if(($bratio < $bounty_ratio) and ($bratio > $planet_bounty_ratio)){
					$rankbounty[$rankcount]="*";	
				}
				if (($bratio < $bounty_ratio) and ($bratio < $planet_bounty_ratio)) {
					$rankbounty[$rankcount]="**";	
				}
			}else{
					 $rankbounty[$rankcount]="";	
			}
			$bratiob= $playerscore /$targetscore;
			$rankbountyb[$rankcount]="";	

			if ($_SESSION['session_player_id'] != $playerid[$i]){
				if(($bratiob < $bounty_ratio) and ($bratiob > $planet_bounty_ratio)){
					$rankbountyb[$rankcount]="*";	
				}
				if (($bratiob < $bounty_ratio) and ($bratiob < $planet_bounty_ratio)) {
					$rankbountyb[$rankcount]="**";	
				}
			}else{
					 $rankbountyb[$rankcount]="";	
			}
			
		}
		$player_insignia = player_insignia_name($row['player_id']);
		$rankimage[$rankcount] = $player_insignia[0];
		$rankimage_name[$rankcount] = $player_insignia[1];
		$rankplayerid[$rankcount] = $row['player_id'];
		$publicavatar[$rankcount] = "avatars/".$row['avatar'];
		$rankname[$rankcount] = $row['character_name'];
		$rankturns[$rankcount] = NUMBER($row['turns_used']);
		$ranklastlogin[$rankcount] = $lastlogin;
		$rankrating[$rankcount] = $rating;
		$rankteam[$rankcount] = $row['team_name'];
		$rankonline[$rankcount] = $online;
		$rankkills[$rankcount] = NUMBER($row['kills']);
		if($row['kills'] == 0)
		{
			$rankkilleff[$rankcount] = 0;
		}
		else
		{
			$rankkilleff[$rankcount] = NUMBER(round($row['kill_efficiency'] / $row['kills']));
		}
		$rankdeaths[$rankcount] = NUMBER($row['deaths']);
		$rankcaptures[$rankcount] = NUMBER($row['captures']);
		$ranklost[$rankcount] = NUMBER($row['planets_lost']);
		$rankbuilt[$rankcount] = NUMBER($row['planets_built']);
		$rankbased[$rankcount] = NUMBER($row['planets_based']);
		$rankdestroyed[$rankcount] = NUMBER($row['planets_destroyed']);
		$rankexperience[$rankcount] = NUMBER(floor($row['experience']));

		$rankeff[$rankcount] = $row['efficiency'];

		if($file_open == 1)
		{
			fwrite($file, "score=" . NUMBER($row['score']) . "\n");
			fwrite($file, "rankimg=" . $player_insignia[0] . "\n");
			fwrite($file, "rankname=" . $player_insignia[1] . "\n");
			fwrite($file, "avatar=" . "avatars/".$row['avatar'] . "\n");
			fwrite($file, "playername=" . $row['character_name'] . "\n");
			fwrite($file, "turnsused=" . NUMBER($row['turns_used']) . "\n");
			fwrite($file, "lastlogin=" . $lastlogin . "\n");
			fwrite($file, "rating=" . $rating . "\n");
			fwrite($file, "teamname=" . $row['team_name'] . "\n");
			fwrite($file, "kills=" . NUMBER($row['kills']) . "\n");
			if($row['kills'] == 0)
			{
				fwrite($file, "killeff=" . "0\n");
			}
			else
			{
				fwrite($file, "killeff=" . NUMBER(round($row['kill_efficiency'] / $row['kills'])) . "\n");
			}
			fwrite($file, "deaths=" . NUMBER($row['deaths']) . "\n");
			fwrite($file, "captures=" . NUMBER($row['captures']) . "\n");
			fwrite($file, "planets_lost=" . NUMBER($row['planets_lost']) . "\n");
			fwrite($file, "planets_built=" . NUMBER($row['planets_built']) . "\n");
			fwrite($file, "planets_based=" . NUMBER($row['planets_based']) . "\n");
			fwrite($file, "planets_destroyed=" . NUMBER($row['planets_destroyed']) . "\n");
			fwrite($file, "experience=" . NUMBER(floor($row['experience'])) . "\n");
			fwrite($file, "efficiency=" . $row['efficiency'] . "\n");
			fwrite($file, "\n");
		}

		$rankcount++;
		$i++;
		$res->MoveNext();
	}
	if($file_open == 1)
	{
		fclose($file);
	}
}

if (empty($_SESSION['session_player_id']))
{
	$template_object->assign("gotomain", $l_global_mlogin);
}
else
{
	$template_object->assign("gotomain", $l_global_mmenu);
}


$template_object->assign("rankplayerid", $rankplayerid);
$template_object->assign("rankbounty", $rankbounty);
$template_object->assign("rankbountyb", $rankbountyb);
$template_object->assign("rankprofileid", $rankprofileid);
$template_object->assign("rankonline", $rankonline);
$template_object->assign("ranklastlogin", $ranklastlogin);
$template_object->assign("publicavatar", $publicavatar);
$template_object->assign("rankimage", $rankimage);
$template_object->assign("rankimage_name", $rankimage_name);

$template_object->assign("rankexperience", $rankexperience);
$template_object->assign("ranklost", $ranklost);
$template_object->assign("rankbuilt", $rankbuilt);
$template_object->assign("rankkills", $rankkills);
$template_object->assign("rankkilleff", $rankkilleff);
$template_object->assign("rankdeaths", $rankdeaths);
$template_object->assign("rankcaptures", $rankcaptures);
$template_object->assign("rankbased", $rankbased);
$template_object->assign("rankdestroyed", $rankdestroyed);
$template_object->assign("rankeff", $rankeff);
$template_object->assign("rankteam", $rankteam);
$template_object->assign("rankrating", $rankrating);
$template_object->assign("rankturns", $rankturns);
$template_object->assign("rankname", $rankname);
$template_object->assign("rankscore", $rankscore);
$template_object->assign("ranknumber", $ranknumber);

$template_object->assign("rankcount", $rankcount);

$res = $db->Execute("SELECT * FROM {$db_prefix}teams");
$teams_count = $res->RecordCount();
$template_object->assign("teams_count", $teams_count);
if ($teams_count > 0) 
{
	$template_object->assign("l_team_galax", $l_team_galax);
	$template_object->assign("type", $type);
	$template_object->assign("l_name", $l_name);
	$template_object->assign("l_team_members", $l_team_members);
	$template_object->assign("l_team_coord", $l_team_coord);
	$template_object->assign("l_score", $l_score);

	$sql_query = "SELECT {$db_prefix}players.character_name,
				COUNT(*) as number_of_members,
				ROUND(SUM({$db_prefix}players.score) / COUNT(*)) as total_score,
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
	$sql_query = $sql_query ." ORDER BY total_score DESC";

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

$res = $db->Execute("SELECT experience, score, player_id, " .
                        "character_name, kills, deaths, captures, planets_lost, planets_built, profile_id, " .
                        "turns_used, last_login, rating, death_type," .
                        "IF(turns_used<150,0,ROUND(score/turns_used)) " .
                        "AS efficiency FROM {$db_prefix}dead_players " .
                        "ORDER BY dead_id DESC LIMIT 10");
db_op_result($res,__LINE__,__FILE__);

$i = 1;
$deadrankcount = 0;

while (!$res->EOF)
{
	$row = $res->fields;

	$temp_turns = $row['turns_used'];
	if ($temp_turns <= 0)
	{
		$temp_turns = 1;
	}

	$lastlogin = date($local_date_full_format, strtotime($row['last_login']));

	$deadrankprofileid[$deadrankcount] =  $row['profile_id'];
	$deadranknumber[$deadrankcount] =  NUMBER($i);
	$deadrankscore[$deadrankcount] =  NUMBER($row['score']);
	$deadrankplayerid[$deadrankcount] = $row['player_id'];
	$deadrankname[$deadrankcount] = $row['character_name'];
	$deadrankturns[$deadrankcount] = NUMBER($row['turns_used']);
	$deadranklastlogin[$deadrankcount] = $lastlogin;

	if($row['rating'] == -1)
	{
		$rating = $l_ranks_evil;
	}
	else
	if($row['rating'] == 1)
	{
		$rating = $l_ranks_good;
	}
	else
	{
		$rating = $l_ranks_neutral;
	}

	$deadrankrating[$deadrankcount] = $rating;
	$deadrankkills[$deadrankcount] = NUMBER($row['kills']);
	$deadrankdeaths[$deadrankcount] = NUMBER($row['deaths']);
	$deadrankcaptures[$deadrankcount] = NUMBER($row['captures']);
	$deadranklost[$deadrankcount] = NUMBER($row['planets_lost']);
	$deadrankbuilt[$deadrankcount] = NUMBER($row['planets_built']);
	$deadrankexperience[$deadrankcount] = NUMBER(floor($row['experience']));
	$deaddeath_type[$deadrankcount] = $l_ranks_kill[$row['death_type']];
	$deadrankeff[$deadrankcount] = NUMBER($row['efficiency']);

	$deadrankcount++;
	$i++;
	$res->MoveNext();
}

$template_object->assign("deaddeath_type", $deaddeath_type);
$template_object->assign("deadrankplayerid", $deadrankplayerid);
$template_object->assign("deadrankexperience", $deadrankexperience);
$template_object->assign("deadrankprofileid", $deadrankprofileid);
$template_object->assign("deadranklost", $deadranklost);
$template_object->assign("deadrankbuilt", $deadrankbuilt);
$template_object->assign("deadrankkills", $deadrankkills);
$template_object->assign("deadrankdeaths", $deadrankdeaths);
$template_object->assign("deadrankcaptures", $deadrankcaptures);
$template_object->assign("deadrankeff", $deadrankeff);
$template_object->assign("deadrankonline", $deadrankonline);
$template_object->assign("deadrankrating", $deadrankrating);
$template_object->assign("deadranklastlogin", $deadranklastlogin);
$template_object->assign("deadrankturns", $deadrankturns);
$template_object->assign("deadrankname", $deadrankname);
$template_object->assign("deadrankscore", $deadrankscore);
$template_object->assign("deadranknumber", $deadranknumber);
$template_object->assign("deadrankcount", $deadrankcount);
$template_object->assign("l_ranks_death_type", $l_ranks_death_type);
$template_object->assign("l_ranks_deadtitle", $l_ranks_deadtitle);

$template_object->display($templatename."ranking.tpl");
include ("footer.php");
?>
