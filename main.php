<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: main.php

include ("config/config.php");
include ("globals/get_shipclassname.inc");
include ("globals/get_player.inc");
include ("globals/display_this_planet.inc");
include ("globals/scanlevel.inc");
include ("globals/last_ship_seen.inc");
include ("globals/device_ship_tech_modify.inc");

get_post_ifset("move_method, move_defense_type, lobby_mode");

$title = $l_main_title;

if (checklogin())
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

// Skinning stuff
if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}

$template_object->assign("l_templatechange", $l_templatechange);
$template_object->assign("template_changed", $_SESSION['template_changed']);
$_SESSION['template_changed'] = 0;

if($lobby_mode == "end" || $tournament_setup_access == 1)
{
	$_SESSION['lobby_mode'] = 0;
}

if($lobby_mode == "start")
{
	$_SESSION['lobby_mode'] = 1;
}

$template_object->assign("lobby_mode", $_SESSION['lobby_mode']);

if($tournament_setup_access == 1 || $_SESSION['lobby_mode'] == 1){

	include ("header.php");
	include ("globals/player_insignia_name.inc");

	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$shipinfo[class]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$classinfo = $debug_query->fields;

	$startdate = date("Y/m/d");
	$shoutcount = 0;
	$res = $db->Execute("SELECT * FROM {$db_prefix}shoutbox WHERE sb_alli = 0 ORDER BY sb_date desc  LIMIT 0,5");

	if($res->EOF)
	{
		$shoutmessage[$shoutcount] = $l_news_none;
		$shoutposter[$shoutcount] = "";
		$shoutcount++;
	}
	else
	{
		while (!$res->EOF) 
		{
			$row = $res->fields;
			$newsdata = stripslashes(rawurldecode($row['sb_text']));
			$shoutmessage[$shoutcount] = $newsdata;
			$shoutposter[$shoutcount] = $row['player_name'];
			$shoutcount++;
			$res->MoveNext();
		}
	}

	$template_object->assign("shoutcount", $shoutcount);
	$template_object->assign("shoutmessage", $shoutmessage);
	$template_object->assign("shoutposter", $shoutposter);

	$newposts = 0;
	if($playerinfo['team'] != 0){
		$debug_query = $db->SelectLimit("select lastonline from {$db_prefix}team_forum_players WHERE player_id=$playerinfo[player_id]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumplayer = $debug_query->fields;

		$debug_query = $db->SelectLimit("select forum_id from {$db_prefix}team_forums where teams=$playerinfo[team]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$forumdata = $debug_query->fields;

		$query2 = $db->Execute("select COUNT(post_id) AS total from {$db_prefix}team_forum_posts where forum_id=$forumdata[forum_id] and post_time>='$forumplayer[lastonline]' order by post_time");
		db_op_result($query2,__LINE__,__FILE__);
		$newposts = $query2->fields['total'];
	}

	$template_object->assign("newposts", $newposts);

//---------------

	include("languages/$langdir/lang_forums.inc");
	$debug_query = $db->SelectLimit("select * from {$db_prefix}casino_forums where casino_sector=1", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$forumdata = $debug_query->fields;

	$debug_query = $db->Execute("select * from {$db_prefix}casino_topics where forum_id=$forumdata[forum_id] order by topic_status desc,lastpostdate desc");
	db_op_result($debug_query,__LINE__,__FILE__);
	$reccount = $debug_query->RecordCount();

	$template_object->assign("forumname", $forumdata['forum_name']);
	$template_object->assign("l_forums_topics", $l_forums_topics);
	$template_object->assign("reccount", $reccount);

	$new_posts = 0;
	$count = 0;
	while (!$debug_query->EOF){
		$topicinfo = $debug_query->fields;

		if($topicinfo['topic_status'] == 9)
		{
			$topictype = $l_forums_sticky;

			$query2 = $db->Execute("select post_player_id from {$db_prefix}casino_posts where topic_id=$topicinfo[topic_id] order by post_time");
			db_op_result($query2,__LINE__,__FILE__);
			$num2 = $query2->RecordCount();

			if($num2 > 0){
				$post_player_id = $query2->fields['post_player_id'];
			}

			$query2 = $db->Execute("select post_id from {$db_prefix}casino_posts where topic_id=$topicinfo[topic_id] and post_time>='$playerinfo[forum_login]' order by post_time");
			db_op_result($query2,__LINE__,__FILE__);
			$newposts = $query2->RecordCount();
			$post_id = $query2->fields['post_id'];

			if(!isset($post_id))
				$post_id=0;

			if($newposts > 0)
				$new_posts++;

			$newpost[$count] = $newposts;
			$topicid[$count] = $topicinfo['topic_id'];
			$postid[$count] = $post_id;
			$topictitle[$count] = $topicinfo['topic_title'];
			$number[$count] = $num2;
			$count++;
		}
		$debug_query->MoveNext();
	}
	$template_object->assign("new_posts", $new_posts);
	$template_object->assign("newpost", $newpost);
	$template_object->assign("topicid", $topicid);
	$template_object->assign("postid", $postid);
	$template_object->assign("topictitle", $topictitle);
	$template_object->assign("number", $number);
	$template_object->assign("count", $count);
	$template_object->assign("l_forums_new", $l_forums_new);

//---------------

	$template_object->assign("title", $title);
	$template_object->assign("l_main_title", $l_main_title);

	$player_insignia = player_insignia_name($playerinfo['player_id']);
	$template_object->assign("insignia", $player_insignia[0]);
	$template_object->assign("insignia_name", $player_insignia[1]);
	$template_object->assign("avatar", $playerinfo['avatar']);
	$template_object->assign("teamicon", $teamicon);
	$template_object->assign("player_name", $playerinfo['character_name']);
	$template_object->assign("team_id", $playerinfo['team']);
	$template_object->assign("shipname", $shipinfo['name']);

	$template_object->assign("basefontsize", $basefontsize);
	$template_object->assign("l_abord", $l_abord);
	$template_object->assign("l_commands", $l_commands);
	$template_object->assign("shoutboxtitle", "Shout Box");

	$template_object->assign("command3dmap", "&nbsp;<a class=mnu href=\"galaxy_map3d.php\">$l_3dmap</a>&nbsp;");
	$template_object->assign("l_3dmap", $l_3dmap);
	$template_object->assign("gd_enabled", extension_loaded("gd"));
	$template_object->assign("enable_spiral_galaxy", $enable_spiral_galaxy);
	$template_object->assign("galaxy_map_enabled", $galaxy_map_enabled);
	$template_object->assign("l_messages", $l_messages);
	$template_object->assign("l_maps", $l_maps);

	$template_object->assign("commandteamshoutbox", "&nbsp;<a class=mnu href=\"#\" onClick=\"window.open('shoutbox_team.php','team_shoutbox','toolbar=no,width=600, height=450');\">$l_team_shoutbox</a>&nbsp;");
	$template_object->assign("l_team_shoutbox", $l_team_shoutbox);

	$template_object->assign("l_help", $l_help);

	$template_object->assign("forum_link", $link_forums);
	if (!empty($link_forums))
	{
		$template_object->assign("commandforums", "&nbsp;<a class=\"mnu\" href=\"$link_forums\" TARGET=\"_blank\">$l_forums</a>&nbsp;");
		$template_object->assign("l_forums", $l_forums);
		$template_object->assign("link_forums", 1);
	}

	$template_object->assign("commandlog", "&nbsp;<a class=mnu href=\"log.php\">$l_log</a>&nbsp;");
	$template_object->assign("l_log", $l_log);

	$template_object->assign("commandreadmail", "&nbsp;<a class=mnu href=\"message_read.php\">$l_read_msg</A>&nbsp;");
	$template_object->assign("l_read_msg", $l_read_msg);

	$template_object->assign("commandsendmail", "&nbsp;<a class=mnu href=\"message_send.php\">$l_send_msg</a>&nbsp;");
	$template_object->assign("l_send_msg", $l_send_msg);

	$template_object->assign("commandblockmail", "&nbsp;<a class=mnu href=\"messageblockmanager.php\">$l_block_msg</a>&nbsp;");
	$template_object->assign("l_block_msg", $l_block_msg);

	$template_object->assign("commandranking", "&nbsp;<a class=mnu href=\"ranking.php\">$l_rankings</a>&nbsp;");
	$template_object->assign("l_rankings", $l_rankings);

	$template_object->assign("commandteams", "&nbsp;<a class=mnu href=\"teams.php\">$l_teams</a>&nbsp;");
	$template_object->assign("l_teams", $l_teams);

	$template_object->assign("commandteamforum", "&nbsp;<a class=mnu href=\"team_forum.php?command=showtopics\">$l_teamforum<font size=\"1\"> - New: $newposts</font></a>&nbsp;");
	$template_object->assign("l_teamforum", $l_teamforum);

	$template_object->assign("commandteamship", "&nbsp;<a class=mnu href=\"team_report.php\">$l_teamships</a>&nbsp;");
	$template_object->assign("l_teamships", $l_teamships);

	$template_object->assign("commanddestruct", "&nbsp;<a class=mnu href=\"self_destruct.php\">$l_ohno</a>&nbsp;");
	$template_object->assign("l_ohno", $l_ohno);

	$template_object->assign("commandoptions", "&nbsp;<a class=mnu href=\"options.php\">$l_options</a>&nbsp;");
	$template_object->assign("l_options", $l_options);

	$template_object->assign("commandfeedback", "&nbsp;<a class=mnu href=\"feedback.php\">$l_feedback</a>&nbsp;");
	$template_object->assign("l_feedback", $l_feedback);

	$template_object->assign("commandlogout", "&nbsp;<a class=mnu href=\"logout.php\">$l_logout</a>&nbsp;");
	$template_object->assign("l_logout", $l_logout);

	$template_object->assign("avatar", $playerinfo['avatar']);

	if($playerinfo['team'] != 0){
		$result = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
		$teamicon = $result->fields['icon'];
	}else{
		$teamicon="default_icon.gif";
	}
	$template_object->assign("teamicon", $teamicon);

	$template_object->assign("classname", $classinfo['name']);
	$template_object->assign("templatename", $templatename);

	include ("globals/translate_news_headline.inc");
	if($playerinfo['show_newscrawl'] == 1 && $allow_newscrawl == 1)
	{
		$startdate = date("Y-m-d");
		$newscount = 0;

		$res = $db->Execute("SELECT * from {$db_prefix}news where LEFT(date,10) = '$startdate' order by news_id desc");
		if($res->EOF)
		{
			$newsmessage[$newscount] = $l_news_none;
			$newscount++;
		}
		else
		{
			while (!$res->EOF) 
			{
				$row = $res->fields;
				$newsheadline = translate_news_headline($row);
				$newsmessage[$newscount] = $newsheadline;
				$newscount++;
				$res->MoveNext();
			}
		}
		$res->close();
		$template_object->assign("newscount", $newscount);
		$template_object->assign("newsmessage", $newsmessage);
		$template_object->assign("show_newscrawl", 1);
	}
	else
	{
		$template_object->assign("show_newscrawl", 0);
	}

	$template_object->display($templatename."tourney.tpl");
	include ("footer.php");
	die();
}

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if ($shipinfo['on_planet'] == "Y")
{
	$res2 = $db->Execute("SELECT planet_id, owner FROM {$db_prefix}planets WHERE planet_id=$shipinfo[planet_id]");
	if ($res2->RecordCount() != 0)
	{

		close_database();
		echo "<A HREF=planet.php?planet_id=$shipinfo[planet_id]>$l_clickme</A> $l_toplanetmenu	<BR>";
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=planet.php?planet_id=$shipinfo[planet_id]&id=".$playerinfo['player_id']."\">";
		die();
	}
	else
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet='N' WHERE player_id=$playerinfo[player_id] AND ship_id=$playerinfo[currentship]");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

if ((!isset($move_method)) || ($move_method == '') || $destination == $shipinfo['sector_id'])
{
	include ("header.php");
	if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
		include ("globals/base_template_data.inc");
	}
	else
	{
		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);
	}
	$move_method='';
}
else
{
	if ((!isset($move_defense_type)) || ($move_defense_type == ''))
	{
		$move_defense_type='';
	}
	else
	{
		$move_defense_type = "_" . $move_defense_type;
	}
	$is_header = 0;
	include ("globals/move_player_start.inc");
	include ("globals/move_player_defenses" . $move_defense_type . ".inc");
	include ("globals/move_player_finish.inc");
	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$playerinfo[player_id]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$playerinfo = $debug_query->fields;

	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id=$playerinfo[player_id] AND ship_id=$playerinfo[currentship]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$shipinfo = $debug_query->fields;

	$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$shipinfo[sector_id]'", 1);
	$sectorinfo = $result2->fields;

	if($is_header == 0)
	{
		include ("header.php");
	}
	if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
		include ("globals/base_template_data.inc");
	}
	else
	{
		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);
	}
}

if ($sectorinfo['port_type'] != "none")
{
	$basename = $sectorinfo['port_type'];
}
else
{
	$portname = ucfirst($l_none);
}

$template_object->assign("port_type", AAT_strtolower($sectorinfo['port_type']));
$template_object->assign("portname", ucfirst($sectorinfo['port_type']));
$countplanet = 0;

$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

$res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE sector_id='$shipinfo[sector_id]'", 5);

$i = 0;
$successful_display = 0;

while (!$res->EOF)
{
	$show_planet = 0; 
	$success = 0;
	$hiding_planet[$i] = $res->fields;

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
		if ($roll <= $success) // If able to see the planet
		{
			$show_planet = 1; //confirmed working
		}
	
		if ($show_planet == 0 && $enable_spies)  // Still not yet 'visible'
		{
			$res_s = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '" . $hiding_planet[$i]['planet_id'] . "' AND owner_id = '$playerinfo[player_id]'");
			if ($res_s->RecordCount())
			{
				 $show_planet = 1;
			}
		}
	}
	
	if ($show_planet == 1)
	{
		$planets[$i] = $res->fields;
		display_this_planet($planets[$i]);
		$successful_display++;
	}
	$i++;
	$res->MoveNext();
}

if (($i > 0) && ($successful_display < 1))
{
	$countplanet = 0;
}

$template_object->assign("countplanet", $countplanet);
$template_object->assign("planetid", $planetid);
$template_object->assign("planetimg", $planetimg);
$template_object->assign("planetname", $planetname);
$template_object->assign("planetowner", $planetowner);
$template_object->assign("planetrating", $planetrating);
$template_object->assign("planetratingnumber", $planetratingnumber);

$playercount = 0;

if ($shipinfo['sector_id'] != 1)
{
	$result4 = $db->Execute(" SELECT DISTINCT
							  {$db_prefix}ships.*,
							  {$db_prefix}players.*,
							  {$db_prefix}teams.team_name,
							  {$db_prefix}teams.id
							  FROM {$db_prefix}ships
							  LEFT JOIN {$db_prefix}players ON {$db_prefix}ships.player_id={$db_prefix}players.player_id
							  LEFT JOIN {$db_prefix}teams
							  ON {$db_prefix}players.team = {$db_prefix}teams.id
							  WHERE {$db_prefix}ships.player_id<>$playerinfo[player_id]
							  AND {$db_prefix}ships.sector_id=$shipinfo[sector_id]
							  AND {$db_prefix}ships.on_planet='N' AND  {$db_prefix}players.currentship={$db_prefix}ships.ship_id");
	$totalcount = 0;

	if ($result4 > 0)
	{
		while (!$result4->EOF)
		{
			$row = $result4->fields;
			$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]", '', 'class');
			$row = device_ship_tech_modify($row, $targetshipdevice);
			$success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], $shiptypes[$row['class']]['basehull']);

			$roll = mt_rand(1, 100);

			if ($roll < $success)
			{
				$shipavg = $row['hull'] + $row['engines'] + $row['fighter'] + $row['beams'] + $row['torp_launchers'] + $row['shields'] + $row['armor'];
				$shipavg /= 7;
				$shipclass=$row['class'];
				$player_id[$playercount] = $row['player_id'];
				$ship_id[$playercount] = $row['ship_id'];
				$getshipimage = $db->SelectLimit("SELECT image FROM {$db_prefix}ship_types WHERE type_id = $shipclass", 1);
				$image = $getshipimage->fields['image'];

				$shipimage[$playercount] = $image;
				$shipnames[$playercount] = $row['name'];
				$playername[$playercount] = $row['character_name'];
				$shipprobe[$playercount] = "ship";

				$rating = good_neutral_evil($row['rating']);
				$shiprating[$playercount] = $rating[1];
				$shipratingnumber[$playercount] = $rating[0];

				if ($row['team_name']) 
				{
					$teamname[$playercount] = $row['team_name'];
				}
				else
				{
					$teamname[$playercount] = "";
				}
				$totalcount++;
				$playercount++;
			}
			$result4->MoveNext();
		}
	}

	$template_object->assign("shiprating", $shiprating);
	$template_object->assign("shipratingnumber", $shipratingnumber);

//	$probe_object = array();
	$result4 = $db->Execute(" SELECT DISTINCT
							  {$db_prefix}probe.*,
							  {$db_prefix}players.*,
							  {$db_prefix}teams.team_name,
							  {$db_prefix}teams.id
							  FROM {$db_prefix}probe
							  LEFT JOIN {$db_prefix}players ON {$db_prefix}probe.owner_id={$db_prefix}players.player_id
							  LEFT JOIN {$db_prefix}teams
							  ON {$db_prefix}players.team = {$db_prefix}teams.id
							  WHERE  {$db_prefix}probe.sector_id=$shipinfo[sector_id] and {$db_prefix}probe.active='Y'
							  ");
	$totalcount = 0;

	if ($result4 > 0)
	{
		while (!$result4->EOF)
		{
			$row = $result4->fields;
			$success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], $shiptypes['1']['basehull']);

			$roll = mt_rand(1, 100);

			if (($roll < $success) || ($shipinfo['player_id']==$row['owner_id']))
			{
				if(!class_exists($row['class'])){
					include ("class/probes/" . $row['class'] . ".inc");
				}
				$probe_object = new $row['class'];
				$shipnames[$playercount] = $probe_object->l_probe_type;

				$player_id[$playercount] = $row['probe_id'];
				$ship_id[$playercount] = "";
				$shipimage[$playercount] = "probe";
				$playername[$playercount] = $row['character_name'];
				if($row['team_name'] != ''){
					$teamname[$playercount] = $row['team_name'];
				}else{
					$teamname[$playercount] = "";
				}

				$shipprobe[$playercount] = "probe";
				$playercount++;
				$totalcount++;
			}
			$result4->MoveNext();
		}
	}

	$result4 = $db->Execute(" SELECT debris_id FROM {$db_prefix}debris WHERE sector_id=$shipinfo[sector_id]");
	$totalcount = 0;

	if ($result4 > 0)
	{
		while (!$result4->EOF)
		{
			$row = $result4->fields;

			$player_id[$playercount] = $row['debris_id'];
			$shipimage[$playercount] = "debris";
			$playername[$playercount] = $l_debris;

			$shipprobe[$playercount] = "debris";
			$playercount++;
			$totalcount++;

			$result4->MoveNext();
		}
	}

	$artifact_description = array();
	$result4 = $db->Execute(" SELECT artifact_id, artifact_type, cloak, scoremax, on_planet_id, on_port FROM {$db_prefix}artifacts WHERE sector_id=$shipinfo[sector_id]");
	$totalcount = 0;

	if ($result4 > 0)
	{
		while (!$result4->EOF)
		{
			$row = $result4->fields;

			if($row['on_planet_id'] == 0 && $row['on_port'] == 0)
			{
				if($row['scoremax'] == 0 || $playerinfo['score'] < $row['scoremax'])
				{
					$success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], 1);

					$roll = mt_rand(1, 100);

					if ($roll < $success)
					{
						if(!class_exists($row['artifact_type'])){
							include ("class/artifacts/" . $row['artifact_type'] . ".inc");
						}
						$artifact_object = new $row['artifact_type'];

						$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $artifact_object->class . "'");
				   		db_op_result($res,__LINE__,__FILE__);
	   					if($res->fields['total'] < $artifact_object->pieces)
   						{
							$playername[$playercount] = $artifact_object->classname;
							$artifact_description[$playercount] = addslashes($artifact_object->description);
							$player_id[$playercount] = $row['artifact_id'];
							$shipimage[$playercount] = $row['artifact_type'];
							$shipprobe[$playercount] = "artifact";
							$playercount++;
							$totalcount++;
						}
					}
				}
			}
			$result4->MoveNext();
		}
	}
}

$template_object->assign("shipimage", $shipimage);
$template_object->assign("player_id", $player_id);
$template_object->assign("artifact_description", $artifact_description);
$template_object->assign("playername", $playername);
$template_object->assign("playercount", $playercount);

$template_object->assign("l_fedinfo", $l_fedinfo);
$template_object->assign("sector_location", $shipinfo['sector_id']);
$template_object->assign("ship_id", $ship_id);
$template_object->assign("shipnames", $shipnames);
$template_object->assign("teamname", $teamname);
$template_object->assign("shipprobe", $shipprobe);
$template_object->assign("l_sector_0", $l_sector_0);

$lss_info = last_ship_seen($shipinfo['sector_id'], $playerinfo['player_id'], $shipinfo['sensors']);
$template_object->assign("l_lss", $l_lss);
$template_object->assign("lss_info", $lss_info);

$res = $db->Execute("SELECT * FROM {$db_prefix}sector_defense,{$db_prefix}players WHERE {$db_prefix}sector_defense.sector_id='$shipinfo[sector_id]'
													AND {$db_prefix}players.player_id = {$db_prefix}sector_defense.player_id order by {$db_prefix}players.character_name");
$i = 0;
if ($res > 0)
{
	while (!$res->EOF)
	{
		$defenses[$i] = $res->fields;
		$i++;
		$res->MoveNext();
	}
}
$num_defenses = $i;

$defensecount = 0;
$totalcount = 0;
$curcount = 0;
$fightercount = 0;
$minecount = 0;

if ($num_defenses > 0) 
{
	$i = 0;
	while ($i < $num_defenses)
	{
		$defense_id = $defenses[$i]['defense_id'];
		if ($defenses[$i]['defense_type'] == 'fighters')
		{
			$defenseid[$defensecount] = $defense_id;
			$defenseimage[$defensecount] = "fighters";
			$def_type = $l_fighters;
			$fightercount++;
		}
		elseif ($defenses[$i]['defense_type'] == 'mines')
		{
			$defenseid[$defensecount] = $defense_id;
			$defenseimage[$defensecount] = "mines";
			$def_type = $l_mines;
			$minecount++;
		}

		$defensetype[$defensecount] = $defenses[$i]['defense_type'];
		$defensemode[$defensecount] = $def_type;
		$defplayername[$defensecount] = $defenses[$i]['character_name'];
		$defenseqty[$defensecount] = NUMBER($defenses[$i]['quantity']);

		$rating = good_neutral_evil($defenses[$i]['rating']);
		$sdrating[$defensecount] = $rating[1];
		$sdratingnumber[$defensecount] = $rating[0];

		$totalcount++;
		$i++;
		$defensecount++;
	}
}

$template_object->assign("sdrating", $sdrating);
$template_object->assign("sdratingnumber", $sdratingnumber);

$template_object->assign("fightercount", $fightercount);
$template_object->assign("minecount", $minecount);
$template_object->assign("defensetype", $defensetype);
$template_object->assign("defensecount", $defensecount);
$template_object->assign("defenseid", $defenseid);
$template_object->assign("defenseimage", $defenseimage);
$template_object->assign("defensemode", $defensemode);
$template_object->assign("defplayername", $defplayername);
$template_object->assign("defenseqty", $defenseqty);

$template_object->assign("l_sector_def", $l_sector_def);

// Start of center


$template_object->assign("l_tradingport", $l_tradingport);
$template_object->assign("l_planet_in_sec", $l_planet_in_sec);
$template_object->assign("l_ships_in_sec", $l_ships_in_sec);
$template_object->assign("l_sector_def", $l_sector_def);
$template_object->assign("max_planets", $sectorinfo['star_size']);
$template_object->assign("starsize", $sectorinfo['star_size']);
$template_object->assign("l_max_planets", $l_max_planets);
$template_object->assign("basefontsize", $basefontsize + 2);
$template_object->assign("sectorzero", $shipinfo['sector_id']);
$template_object->assign("sg_sector", $sectorinfo['sg_sector']);

//-------------------------------------------------------------------------------------------------
// end of center

$template_object->display($templatename."main.tpl");

include ("footer.php");
 ?>
