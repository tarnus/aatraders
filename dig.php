<?php
include("config/config.php");

include("languages/$langdir/lang_planets.inc");
include ("languages/$langdir/lang_dig.inc");

get_post_ifset("command, by2, digchanged, dig_id, changedig, digcount, planet_id");

$title=$l_dig_title;

if(!$enable_dignitaries)
{
	$template_object->assign("title", $title);
	$template_object->assign("error_msg", $l_dig_disabled);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."dig-die.tpl");
	include("footer.php");
	die();
}

if(checklogin() or $tournament_setup_access == 1)
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

$template_object->assign("command", $command);

$dignitary_object = array();
$job_type = array();
$job_name = array();
$classcount = 1;
$job_type[0] = 0;
$job_name[0] = $l_dig_waiting;
$max_digs[0] = $max_dignitary_per_planet;
$description[0] = $l_dig_waiting_description;
$filelist = get_dirlist($gameroot."class/dignitaries/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$dignitary_classname =  str_replace(".inc", "", $filelist[$c]); 
		if(!class_exists($dignitary_classname)){
			include ("class/dignitaries/" . $dignitary_classname . ".inc");
		}
		$store_object = new $dignitary_classname();
		$job_type[$classcount] = $store_object->id;
		$job_name[$job_type[$classcount]] = $store_object->classname;
		$max_digs[$job_type[$classcount]] = $store_object->max_digs;
		$description[$job_type[$classcount]] = $store_object->description;
		$dignitary_object[$job_type[$classcount]] = $store_object;
		$classcount++;
	}
}

$template_object->assign("job_name", $job_name);
$template_object->assign("max_digs", $max_digs);
$template_object->assign("l_dig_max", $l_dig_max);
$template_object->assign("l_dig_legend", $l_dig_legend);
$template_object->assign("description", $description);
$template_object->assign("l_dig_description", $l_dig_description);
$template_object->assign("l_dig_changeerror", $l_dig_changeerror);

$error_result = array();
if ($command == "update")
{
	for($i = 0; $i < $digcount; $i++){
		if($digchanged[$i]){
			if($changedig[$i] != 0)
			{
				$error_result[$dig_id[$i]] = $dignitary_object[$changedig[$i]]->change_dignitary($dig_id[$i], $planet_id[$i], $changedig[$i]);
			}
			else
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET job_id='0', percent='0.0', embezzler = 0 WHERE dig_id=$dig_id[$i] ");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}
	}
}

if($by2 == 'planet')		  $by22 = "{$db_prefix}planets.name asc, {$db_prefix}planets.sector_id asc, dig_id asc";
elseif($by2 == 'id')			$by22 = "dig_id asc";
elseif($by2 == 'job_id')	  $by22 = "job_id desc, percent desc, dig_id asc";
else						  $by22 = "{$db_prefix}planets.sector_id asc, {$db_prefix}planets.name asc, dig_id asc";

$res = $db->Execute("SELECT * FROM {$db_prefix}dignitary WHERE {$db_prefix}dignitary.owner_id=$playerinfo[player_id] ");
$template_object->assign("totaldigs", $res->RecordCount());
if($res->RecordCount())
{
	$line_color = "#23244F";
	$res = $db->Execute("SELECT {$db_prefix}universe.sector_name, {$db_prefix}dignitary.*, {$db_prefix}planets.name, {$db_prefix}planets.planet_id, {$db_prefix}players.character_name FROM {$db_prefix}universe, {$db_prefix}dignitary INNER JOIN {$db_prefix}planets ON {$db_prefix}dignitary.planet_id={$db_prefix}planets.planet_id LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id={$db_prefix}planets.owner WHERE {$db_prefix}dignitary.owner_id=$playerinfo[player_id] AND {$db_prefix}dignitary.owner_id={$db_prefix}planets.owner and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id ORDER BY $by22 ");
	$template_object->assign("totaldigsbyplanet", $res->RecordCount());
	if($res->RecordCount())
	{
		$template_object->assign("l_dig_defaulttitle2", $l_dig_defaulttitle2);
		$template_object->assign("l_dig_codenumber", $l_dig_codenumber);
		$template_object->assign("l_dig_planetname", $l_dig_planetname);
		$template_object->assign("l_dig_sector", $l_dig_sector);
		$template_object->assign("l_dig_job", $l_dig_job);
		$template_object->assign("l_dig_dismiss", $l_dig_dismiss);

		$digcount = 0;
		while(!$res->EOF)
		{
			$dig = $res->fields;

			if(empty($dig['name']))
				$dig['name'] = $l_unnamed;

			$digplanetid[$digcount] = $dig['planet_id'];
			$digid[$digcount] = $dig['dig_id'];
			$digname[$digcount] = $dig['name'];
			$digsector[$digcount] = $dig['sector_name'];
			$digjob[$digcount] = $dig['job_id'];
			$digerrorresult[$digcount] = (isset($error_result[$dig['dig_id']])) ? $error_result[$dig['dig_id']] : "&nbsp;";
			$digcount++;
			$res->MoveNext();
		}

		$template_object->assign("l_dig_changebutton", $l_dig_changebutton);
		$template_object->assign("digerrorresult", $digerrorresult);
		$template_object->assign("digplanetid", $digplanetid);
		$template_object->assign("digcount", $digcount);
		$template_object->assign("digid", $digid);
		$template_object->assign("digname", $digname);
		$template_object->assign("digsector", $digsector);
		$template_object->assign("digjob", $digjob);
		$template_object->assign("job_name", $job_name);
		$template_object->assign("job_type", $job_type);
		$template_object->assign("classcount", $classcount);
	}
	else
	{
		$template_object->assign("l_dig_no2", $l_dig_no2);
	}

	$res = $db->Execute("SELECT COUNT(dig_id) AS as_dig_id FROM {$db_prefix}dignitary WHERE active='N' AND owner_id=$playerinfo[player_id] AND ship_id=$shipinfo[ship_id] AND planet_id='0'");
	$template_object->assign("digonship", $res->RecordCount());

	if ($res->RecordCount()) {
		$dig = $res->fields;
		$template_object->assign("l_dig_defaulttitle4", $l_dig_defaulttitle4);
		$template_object->assign("digshiptotal", $dig['as_dig_id']);
	} else { 
		$template_object->assign("l_dig_no4", $l_dig_no4);
	}
}
else
{
	$template_object->assign("l_dig_nodignitaryatall", $l_dig_nodignitaryatall);
}

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."dig.tpl");

include("footer.php");
?>
