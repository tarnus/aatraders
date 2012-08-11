<?php
include("config/config.php");
include("languages/$langdir/lang_teams.inc");
include("languages/$langdir/lang_report.inc");
include ("globals/device_ship_tech_modify.inc");

get_post_ifset("orderby, direction, whichteam");

$title=$l_title_teamreport;

if (checklogin()) {
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

if ((!isset($orderby)) || ($orderby == ''))
{
	$orderby = 'p.character_name';
}

/* Get user info */
$result		= $db->SelectLimit("SELECT {$db_prefix}players.*, {$db_prefix}teams.team_name, {$db_prefix}teams.description, {$db_prefix}teams.creator, {$db_prefix}teams.id
						FROM {$db_prefix}players
						LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team = {$db_prefix}teams.id
						WHERE {$db_prefix}players.player_id=$playerinfo[player_id]", 1);
$playerinfo	= $result->fields;

/*
   Get Team Info
*/
$whichteam = stripnum($whichteam);
if ($whichteam)
{
	$result_team   = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$whichteam", 1);
	$team		  = $result_team->fields;
} else {
	$result_team   = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
	$team		  = $result_team->fields;
}

if($playerinfo[team] != 0){
	$result = $db->SelectLimit("SELECT * FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
	$whichteam = $result->fields;
	$isowner = ($playerinfo['player_id'] == $whichteam['creator']);
	$whichteam = $playerinfo['team'];

	for($iz=0; $iz<50; $iz++){
		if($iz<10)
			$colorarray[$iz] = "#FFADAD";
		if($iz>9 and $iz<20)
			$colorarray[$iz] = "#FFFF00";
		if($iz>19 and $iz<30)
			$colorarray[$iz] = "#0CD616";
		if($iz>29)
			$colorarray[$iz] = "#ffffff";
	}

	$result  = $db->Execute("SELECT * FROM {$db_prefix}players as p, {$db_prefix}ships as s WHERE p.team=$whichteam and s.player_id=p.player_id AND s.ship_id=p.currentship order by ".$orderby." ".$direction);
	$shipcount = 0;
	while (!$result->EOF) {
		$member = $result->fields;

		$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$member[class]", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$classstuff = $debug_query->fields;
		$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$member[ship_id]", '', 'class');
		$member = device_ship_tech_modify($member, $targetshipdevice);

		$hull[$shipcount] = $member['hull'];
		$engines[$shipcount] = $member['engines'];
		$power[$shipcount] = $member['power'];
		$fighter[$shipcount] = $member['fighter'];
		$sensors[$shipcount] = $member['sensors'];
		$armor[$shipcount] = $member['armor'];
		$shields[$shipcount] = $member['shields'];
		$beams[$shipcount] = $member['beams'];
		$torps[$shipcount] = $member['torp_launchers'];
		$cloak[$shipcount] = $member['cloak'];
		$ecm[$shipcount] = $member['ecm'];
		$shipname[$shipcount] = $member['name'];
		$playername[$shipcount] = $member['character_name'];
		$playeravatar[$shipcount] = $member['avatar'];
		$shipclassname[$shipcount] = $classstuff['name'];
		$memberclass[$shipcount] = $member['class'];
		$colorhull[$shipcount] = $colorarray[$hull[$shipcount]];
		$colorengines[$shipcount] = $colorarray[$engines[$shipcount]];
		$colorpower[$shipcount] = $colorarray[$power[$shipcount]];
		$colorfighter[$shipcount] = $colorarray[$fighter[$shipcount]];
		$colorsensors[$shipcount] = $colorarray[$sensors[$shipcount]];
		$colorarmor[$shipcount] = $colorarray[$armor[$shipcount]];
		$colorshields[$shipcount] = $colorarray[$shields[$shipcount]];
		$colorbeams[$shipcount] = $colorarray[$beams[$shipcount]];
		$colortorps[$shipcount] = $colorarray[$torps[$shipcount]];
		$colorcloak[$shipcount] = $colorarray[$cloak[$shipcount]];
		$colorecm[$shipcount] = $colorarray[$ecm[$shipcount]];
		$score[$shipcount] = NUMBER($member['score']);
		$linecolor[$shipcount] = "#23244F";
		$coordinator[$shipcount] = "";

		if ($member['player_id'] == $team['creator'])
		{
			$coordinator[$shipcount] = $l_team_coord;
		}

		$shipcount++;
		$result->MoveNext();
	}

	$template_object->assign("l_avatar", $l_avatar);
	$template_object->assign("l_team_members", $l_team_members);
	$template_object->assign("l_hull", $l_hull);
	$template_object->assign("l_engines", $l_engines);
	$template_object->assign("l_power", $l_power);
	$template_object->assign("l_fighter", $l_fighter);
	$template_object->assign("l_sensors", $l_sensors);
	$template_object->assign("l_armor", $l_armor);
	$template_object->assign("l_shields", $l_shields);
	$template_object->assign("l_beams", $l_beams);
	$template_object->assign("l_torp_launch", $l_torp_launch);
	$template_object->assign("l_cloak", $l_cloak);
	$template_object->assign("l_ecm", $l_ecm);
	$template_object->assign("l_team_score", $l_team_score);
	$template_object->assign("teamname", $team['team_name']);
	$template_object->assign("description", $team['description']);
	$template_object->assign("shipcount", $shipcount);
	$template_object->assign("l_team_class", $l_team_class);
	$template_object->assign("hull", $hull);
	$template_object->assign("engines", $engines);
	$template_object->assign("power", $power);
	$template_object->assign("fighter", $fighter);
	$template_object->assign("sensors", $sensors);
	$template_object->assign("armor", $armor);
	$template_object->assign("shields", $shields);
	$template_object->assign("beams", $beams);
	$template_object->assign("torps", $torps);
	$template_object->assign("cloak", $cloak);
	$template_object->assign("ecm", $ecm);
	$template_object->assign("shipname", $shipname);
	$template_object->assign("playername", $playername);
	$template_object->assign("playeravatar", $playeravatar);
	$template_object->assign("shipclassname", $shipclassname);
	$template_object->assign("memberclass", $memberclass);
	$template_object->assign("colorhull", $colorhull);
	$template_object->assign("colorengines", $colorengines);
	$template_object->assign("colorpower", $colorpower);
	$template_object->assign("colorfighter", $colorfighter);
	$template_object->assign("colorsensors", $colorsensors);
	$template_object->assign("colorarmor", $colorarmor);
	$template_object->assign("colorshields", $colorshields);
	$template_object->assign("colorbeams", $colorbeams);
	$template_object->assign("colortorps", $colortorps);
	$template_object->assign("colorcloak", $colorcloak);
	$template_object->assign("colorecm", $colorecm);
	$template_object->assign("score", $score);
	$template_object->assign("linecolor", $linecolor);
	$template_object->assign("coordinator", $coordinator);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team-report.tpl");
	include ("footer.php");
	die();
}else{
	$template_object->assign("error_msg", $l_team_notmember);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."team-reportdie.tpl");
	include ("footer.php");
	die();
}

close_database();
?>

