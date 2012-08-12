<?php
include("config/config.php");
include("languages/$langdir/lang_teams.inc");
include("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_common.inc");
include ("globals/device_ship_tech_modify.inc");

get_post_ifset("orderby, direction, whichteam");

$title=$l_title_storedship;

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
	$orderby = 'class DESC';
}



for($iz=0; $iz <= $max_tech_level; $iz++){
	if($iz < floor($max_tech_level/4))
		$colorarray[$iz] = "#FFADAD";
	if($iz >= floor($max_tech_level/4) and $iz < (floor($max_tech_level/4) * 2))
		$colorarray[$iz] = "#FFFF00";
	if($iz >= (floor($max_tech_level/4) * 2) and $iz < (floor($max_tech_level/4) * 3))
		$colorarray[$iz] = "#0CD616";
	if($iz >= (floor($max_tech_level/4) * 3))
		$colorarray[$iz] = "#ffffff";
}

$result  = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE player_id=$playerinfo[player_id] order by ".$orderby." ".$direction);
db_op_result($result,__LINE__,__FILE__);

$shipcount = 0;
while (!$result->EOF) {
	$member = $result->fields;

	$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$member[class]", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$classstuff = $debug_query->fields;
	$ship_id[$shipcount] = $member['ship_id'];
	$currentship[$shipcount] = $playerinfo['currentship'];
	$storage_planet_id[$shipcount] = $member['storage_planet_id'];
	$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$member[ship_id]", '', 'class');
	$member = device_ship_tech_modify($member, $targetshipdevice);

	if ($member['storage_planet_id'] != 0){
		$planetquery = $db->SelectLimit("SELECT p.name,u.sector_name FROM {$db_prefix}planets p, {$db_prefix}universe u WHERE p.sector_id=u.sector_id and p.owner='$playerinfo[player_id]' and p.planet_id='$member[storage_planet_id]'");
		db_op_result($planetquery,__LINE__,__FILE__);
		$planetstuff = $planetquery->fields;
		$planetname[$shipcount] = $planetstuff['name'];
		$sector_name[$shipcount] = $planetstuff['sector_name'];
	}else{
		$planetname[$shipcount] = "";
		$sector_name[$shipcount] = "";
	}

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

$template_object->assign("l_sector", $l_sector);
$template_object->assign("l_planets", $l_planets );
$template_object->assign("l_ships", $l_ships);
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

$template_object->assign("ship_id", $ship_id);
$template_object->assign("storage_planet_id", $storage_planet_id);
$template_object->assign("planetname", $planetname);
$template_object->assign("sector_name", $sector_name);
$template_object->assign("currentship", $currentship);

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
$template_object->display($templatename."stored-ship-report.tpl");
include ("footer.php");
die();

close_database();
?>

