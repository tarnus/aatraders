<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: attack.php

include ("config/config.php");
include ("languages/$langdir/lang_attack.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_planets.inc");
include ("languages/$langdir/lang_combat.inc");
include ("globals/combat_functions.inc");
include ("globals/ship_bounty_check.inc");
include ("globals/collect_bounty.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/send_system_im.inc");
include ("globals/log_move.inc");
include ("globals/get_rating_change.inc");
include ("globals/device_ship_tech_modify.inc");

get_post_ifset("player_id, ship_id");

$title = $l_att_title;

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

$ship_id = stripnum($ship_id);

$result = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE ship_id='$ship_id'", 1);
$targetship = $result->fields;

$player_id = $targetship['player_id'];

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$player_id'", 1);
$targetinfo = $result2->fields;

$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$ship_id", '', 'class');

$targetship_old = $targetship;
$shipinfo_old = $shipinfo;
$targetship = device_ship_tech_modify($targetship, $targetshipdevice);
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

if ($playerinfo['team'] == $targetinfo['team'] && $targetinfo['team'] > 0)
{
	$template_object->assign("error_msg", $l_att_flee);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($targetship['sector_id'] != $shipinfo['sector_id'] || $targetship['on_planet'] == "Y")
{
	$template_object->assign("error_msg", $l_att_notarg);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_att_noturn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

/* determine percent chance of success in detecting target ship - based on player's sensors and opponent's cloak */
$targetcloak = $targetship['cloak'];

$success = SCAN_SUCCESS($shipinfo['sensors'], $targetcloak, $shiptypes[$targetship['class']]['basehull']);

$targetengines = $targetship['engines'];

$flee = SCAN_SUCCESS($shipinfo['engines'], $targetengines, $shiptypes[$targetship['class']]['basehull']); 
$roll = mt_rand(1, 100);
$roll2 = mt_rand(1, 100);

$res = $db->Execute("SELECT allow_attack,{$db_prefix}universe.zone_id FROM {$db_prefix}zones,{$db_prefix}universe WHERE sector_id='$targetship[sector_id]' AND {$db_prefix}zones.zone_id={$db_prefix}universe.zone_id");
$query97 = $res->fields;

if ($query97['allow_attack'] == 'N' and $onplanet == 0)
{
	$template_object->assign("error_msg", $l_att_noatt);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($flee < $roll2)
{
	send_system_im($targetinfo['player_id'], $l_att_imtitle, $playerinfo['character_name'] . " $l_att_imbody", $targetinfo['last_login']);
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
	playerlog($targetinfo['player_id'], "LOG5_ATTACK_OUTMAN", "$playerinfo[character_name]");
	$template_object->assign("error_msg", $l_att_flee);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($roll > $success)
{
	/* if scan fails - inform both player and target. */
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	playerlog($targetinfo['player_id'], "LOG5_ATTACK_OUTSCAN", "$playerinfo[character_name]");
	$template_object->assign("error_msg", $l_planet_noscan);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

/* if scan succeeds, show results and inform target. */
$shipavg = $targetship['basehull'] + ($targetship['hull'] + $targetship['engines'] + $targetship['power'] + $targetship['fighter'] + $targetship['sensors'] + $targetship['beams'] + $targetship['torp_launchers'] + $targetship['shields'] + $targetship['cloak'] + $targetship['armor'] + $targetship['ecm']) / 11;

if ($shipavg > $ewd_maxavgtechlevel)
{
	$chance = round($shipavg / $max_tech_level) * 100;
}
else
{
	$chance = 0;
}

$random_value = mt_rand(1,100);
if ($targetshipdevice['dev_emerwarp']['amount'] > 0 && $random_value > $chance)
{
	send_system_im($targetinfo['player_id'], $l_att_imtitle, $playerinfo['character_name'] . " $l_att_imbody", $targetinfo['last_login']);
	/* need to change warp destination to random sector in universe */
	$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship);
	$source_sector = $shipinfo['sector_id'];

	$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 3 ORDER BY rand()", 1);
	$dest_sector = $findem->fields['sector_id'];

	$debug_query = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$source_sector", 1);
	db_op_result($debug_query,__LINE__,__FILE__);
	$zones = $debug_query->fields;

	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1,rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	playerlog($targetinfo['player_id'], "LOG5_ATTACK_EWD", "$playerinfo[character_name]");

	$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET sector_id=$dest_sector, cleared_defenses=' ', on_planet='N' WHERE ship_id=$ship_id");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
	db_op_result($debug_query,__LINE__,__FILE__);

	log_move($targetinfo['player_id'],$targetship['ship_id'],$source_sector,$dest_sector,$shipinfo['class'],$shipinfo['cloak'],$zones['zone_id']);
	$template_object->assign("error_msg", $l_att_ewd);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}
else
{
	playerlog($targetinfo['player_id'], "LOG5_ATTACK_EWDFAIL", $playerinfo['character_name']);
}

send_system_im($targetinfo['player_id'], $l_att_imtitle, $playerinfo['character_name'] . " $l_att_imbody", $targetinfo['last_login']);

// get attacker beam, shield and armor values
$attacker_shield_energy = floor($shipinfo['energy'] * 0.4);
$attacker_beam_energy = $shipinfo['energy'] - $attacker_shield_energy;

$attackershields = NUM_SHIELDS($shipinfo['shields']);

if ($attackershields < $attacker_shield_energy)
{
	$attacker_shield_energy = $attackershields;
}

$attackerbeams = NUM_BEAMS($shipinfo['beams']);

if ($attackerbeams < $attacker_beam_energy)
{
	$attacker_beam_energy = $attackerbeams;
}

$attackerenergyset = $attacker_beam_energy + $attacker_shield_energy;

$attack_beamtofighter_dmg = floor($attacker_beam_energy * 0.05);
$attacker_beam_energy -= $attack_beamtofighter_dmg;
$attack_beamtotorp_dmg = floor($attacker_beam_energy * 0.025);
$attacker_beam_energy -= $attack_beamtotorp_dmg;

// get target beam, shield and armor values
$target_shield_energy = floor($targetship['energy'] * 0.4);
$target_beam_energy = $targetship['energy'] - $target_shield_energy;

$targetshields = NUM_SHIELDS($targetship['shields']);

if ($targetshields < $target_shield_energy)
{
	$target_shield_energy = $targetshields;
}

$targetbeams = NUM_BEAMS($targetship['beams']);

if ($targetbeams < $target_beam_energy)
{
	$target_beam_energy = $targetbeams;
}

$targetenergyset = $target_shield_energy + $target_beam_energy;

$target_beamtofighter_dmg = floor($target_beam_energy * 0.05);
$target_beam_energy -= $target_beamtofighter_dmg;
$target_beamtotorp_dmg = floor($target_beam_energy * 0.025);
$target_beam_energy -= $target_beamtotorp_dmg;

// next
$attackertorps = $shipinfo['torps'];

$attackerarmor = $shipinfo['armor_pts'];

$attackerfighters = $shipinfo['fighters'];

$targettorps = $targetship['torps'];

$targetarmor = $targetship['armor_pts'];

$targetfighters = $targetship['fighters'];

$attackerlowpercent = ecmcheck($targetship['ecm'], $shipinfo['sensors'], $full_attack_modifier);
$targetlowpercent = ecmcheck($shipinfo['ecm'], $targetship['sensors'], -$full_attack_modifier);

$targetshipshields = $targetship['shields'];
$targetshiparmor = $targetship['armor'];
$targetshiptorp_launchers = $targetship['torp_launchers'];
$targetshipbeams = $targetship['beams'];
$targetshipfighter = $targetship['fighter'];
$targetname = $targetinfo['character_name'];

if(!class_exists($shipinfo['fighter_class'])){
	include ("class/" . $shipinfo['fighter_class'] . ".inc");
}

$attackobject = new $shipinfo['fighter_class']();
$fighter_damage_shields = $attackobject->fighter_damage_shields;
$fighter_damage_all = $attackobject->fighter_damage_all;
$fighter_hit_pts = $attackobject->fighter_hit_pts;

if(!class_exists($shipinfo['beam_class'])){
	include ("class/" . $shipinfo['beam_class'] . ".inc");
}

$attackobject = new $shipinfo['beam_class']();
$beam_damage_shields = $attackobject->beam_damage_shields;
$beam_damage_all = $attackobject->beam_damage_all;

if(!class_exists($shipinfo['torp_class'])){
	include ("class/" . $shipinfo['torp_class'] . ".inc");
}

$attackobject = new $shipinfo['torp_class']();
$torp_damage_shields = $attackobject->torp_damage_shields;
$torp_damage_all = $attackobject->torp_damage_all;
$torp_hit_pts = $attackobject->torp_hit_pts;

if(!class_exists($shipinfo['shield_class'])){
	include ("class/" . $shipinfo['shield_class'] . ".inc");
}

$attackobject = new $shipinfo['shield_class']();
$ship_shield_hit_pts = $attackobject->ship_shield_hit_pts;

if(!class_exists($shipinfo['armor_class'])){
	include ("class/" . $shipinfo['armor_class'] . ".inc");
}

$attackobject = new $shipinfo['armor_class']();
$ship_armor_hit_pts = $attackobject->hit_pts;

if(!class_exists($targetship['fighter_class'])){
	include ("class/" . $targetship['fighter_class'] . ".inc");
}

$targetobject = new $targetship['fighter_class']();
$fighter_damage_shields = $targetobject->fighter_damage_shields;
$fighter_damage_all = $targetobject->fighter_damage_all;
$fighter_hit_pts = $targetobject->fighter_hit_pts;

if(!class_exists($targetship['beam_class'])){
	include ("class/" . $targetship['beam_class'] . ".inc");
}

$targetobject = new $targetship['beam_class']();
$beam_damage_shields = $targetobject->beam_damage_shields;
$beam_damage_all = $targetobject->beam_damage_all;

if(!class_exists($targetship['torp_class'])){
	include ("class/" . $targetship['torp_class'] . ".inc");
}

$targetobject = new $targetship['torp_class']();
$torp_damage_shields = $targetobject->torp_damage_shields;
$torp_damage_all = $targetobject->torp_damage_all;
$torp_hit_pts = $targetobject->torp_hit_pts;

if(!class_exists($targetship['shield_class'])){
	include ("class/" . $targetship['shield_class'] . ".inc");
}

$targetobject = new $targetship['shield_class']();
$ship_shield_hit_pts = $targetobject->ship_shield_hit_pts;

if(!class_exists($targetship['armor_class'])){
	include ("class/" . $targetship['armor_class'] . ".inc");
}

$targetobject = new $targetship['armor_class']();
$ship_armor_hit_pts = $targetobject->ship_armor_hit_pts;

update_player_experience($playerinfo['player_id'], $attacking_ship);

$attacktype = "ship";

// --------------------------------------------
// execute attack exchange code

include ("globals/attack_exchange.inc");

// --------------------------------------------
$template_object->assign("l_cmb_attack_exchange_results", $l_cmb_attack_exchange_results);
$attacker_exchange_result = array();
$target_exchange_result = array();

$attacker_armor_lost = $shipinfo['armor_pts'] - $attacker_armor_left;
$attacker_fighters_lost = $shipinfo['fighters'] - $attacker_fighters_left;
$attacker_torps_lost = $shipinfo['torps'] - ($attacker_torps_left);
$attacker_energy_lost = $attackerenergyset - ($attacker_energy_left + $attacker_shields_left);

$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST(armor_pts - $attacker_armor_lost, 0), energy=GREATEST(energy - $attacker_energy_lost, 0), fighters=GREATEST(fighters - $attacker_fighters_lost, 0), torps=GREATEST(torps - $attacker_torps_lost, 0) WHERE ship_id=$shipinfo[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$target_armor_lost = $targetship['armor_pts'] - $target_armor_left;
$target_fighters_lost = $targetship['fighters'] - $target_fighters_left;
$target_torps_lost = $targetship['torps'] - ($target_torps_left);
$target_energy_lost = $targetenergyset - ($target_energy_left + $target_shields_left);

$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST(armor_pts - $target_armor_lost, 0), energy=GREATEST(energy - $target_energy_lost, 0), fighters=GREATEST(fighters - $target_fighters_lost, 0), torps=GREATEST(torps - $target_torps_lost, 0) WHERE ship_id=$targetship[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$attacker_exchange_result = array();
$target_exchange_result = array();

// Both Attacker and Target Ships Destroyed
if(($attacker_armor_left < 1 and $attacker_shields_left < 1) and ($target_armor_left < 1 and $target_shields_left < 1))
{
	update_player_experience($playerinfo['player_id'], $destroying_enemyship + $losing_yourship);
	update_player_experience($targetinfo['player_id'], $destroying_enemyship + $losing_yourship);
	//	target_died
	$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_target_ship_destroyed);
	if ($targetshipdevice['dev_escapepod']['amount'] == 1)
	{
		$target_exchange_result[] = $l_cmb_escapepod_launched;
		player_ship_destroyed($targetship['ship_id'], $targetinfo['player_id'], $targetinfo['rating'], $playerinfo['player_id'], $playerinfo['rating'], "killedshippod");
		playerlog($targetinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|Y");
		collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
	}
	else
	{
		$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_escapepod_failure);
		playerlog($targetinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|N");
		db_kill_player($targetinfo['player_id'], $playerinfo['player_id'], $playerinfo['rating'], "killedship");
		collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
	}

	//	attacker_died
	$attacker_exchange_result[] = $l_cmb_attacker_ship_destroyed;
	if ($shipdevice['dev_escapepod']['amount'] == 1)
	{
		$attacker_exchange_result[] = $l_cmb_escapepod_launched;
		player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], $targetinfo['player_id'], $targetinfo['rating'], "killedshippod");
		collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
	}
	else
	{
		$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
		db_kill_player($playerinfo['player_id'], $targetinfo['player_id'], $targetinfo['rating'], "killedship");
		collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
	}

	$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
	$template_object->assign("target_exchange_result", $target_exchange_result);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attack_exchange.tpl");

	include ("footer.php");
	die();
}

if(($attacker_armor_left < 1 and $attacker_shields_left < 1) or ($target_armor_left < 1 and $target_shields_left < 1))
{
	if ($target_armor_left < 1 and $target_shields_left < 1)
	{
		//	target_died
		update_player_experience($playerinfo['player_id'], $destroying_enemyship);
		update_player_experience($targetinfo['player_id'], $losing_yourship);
		$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_target_ship_destroyed);
		if ($targetshipdevice['dev_escapepod']['amount'] == 1)
		{
			$target_exchange_result[] = $l_cmb_escapepod_launched;
			player_ship_destroyed($targetship['ship_id'], $targetinfo['player_id'], $targetinfo['rating'], $playerinfo['player_id'], $playerinfo['rating'], "killedshippod");
			playerlog($targetinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|" . $targetshipdevice['dev_escapepod']['amount']);
			collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
		}
		else
		{
			$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_escapepod_failure);
			playerlog($targetinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|" . $targetshipdevice['dev_escapepod']['amount']);
			db_kill_player($targetinfo['player_id'], $playerinfo['player_id'], $playerinfo['rating'], "killedship");
			collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
		}

		$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship);

		adminlog("LOG0_ADMIN_COMBAT", "<font color=\"yellow\"><B>Salvage Ship Values:</B></font><BR> " . print_r($targetship, true) . "<br>");
		$ship_value=$upgrade_cost*(round(mypw($upgrade_factor, $targetship_old['hull']))+round(mypw($upgrade_factor, $targetship_old['engines']))+round(mypw($upgrade_factor, $targetship_old['power']))+round(mypw($upgrade_factor, $targetship_old['fighter']))+round(mypw($upgrade_factor, $targetship_old['sensors']))+round(mypw($upgrade_factor, $targetship_old['beams']))+round(mypw($upgrade_factor, $targetship_old['torp_launchers']))+round(mypw($upgrade_factor, $targetship_old['shields']))+round(mypw($upgrade_factor, $targetship_old['armor']))+round(mypw($upgrade_factor, $targetship_old['cloak']))+round(mypw($upgrade_factor, $targetship_old['ecm'])));
		$ship_salvage_rate = mt_rand(10,20);
		$ship_salvage=$ship_value * ($ship_salvage_rate/100);
		$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET credits=credits+$ship_salvage, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$l_cmb_attacker_salvage=str_replace("[ship_salvage_rate]","<font color=\"#00ff00\">". $ship_salvage_rate . "</font>",$l_cmb_attacker_salvage);
		$l_cmb_attacker_salvage=str_replace("[ship_salvage]","<font color=\"#00ff00\">". NUMBER($ship_salvage) . "</font>",$l_cmb_attacker_salvage);
		$l_cmb_attacker_salvage=str_replace("[rating_change]","<font color=\"#00ff00\">". NUMBER(abs($rating_change)) . "</font>",$l_cmb_attacker_salvage);
		$attacker_exchange_result[] = $l_cmb_attacker_salvage;
		playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $l_cmb_attacker_salvage);

		adminlog("LOG0_ADMIN_COMBAT", "<font color=\"yellow\"><B>Salvage Values:</B></font><BR> Ship Value: $ship_value - $l_att_ysalv : upgrade_cost = $upgrade_cost, upgrade_factor = $upgrade_factor<br>");

		$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $targetinfo['character_name'] . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
		$target_exchange_result[] = $l_cmb_target_lost_list;
		playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);
	}
	else
	{
		$attacker_exchange_result[] = str_replace("[name]",$targetinfo['character_name'],$l_cmp_target_survives);

		if($target_armor_left > 0 && $target_armor_left < $targetship['armor_pts'])
		{
			calc_internal_damage($targetship['ship_id'], 0, ($targetship['armor_pts']-$target_armor_left) / $targetship['armor_pts']);
			$result = $db->SelectLimit("SELECT hull, engines, power, fighter, sensors, beams, torp_launchers, shields, cloak, ecm, armor FROM {$db_prefix}ships WHERE ship_id='$targetship[ship_id]'", 1);
			$afteractionshiptech = $result->fields;
			$attacker_exchange_result[] = $l_cmb_attacker_lost_tech;

			$build_log_entry = $l_cmb_attacker_tech_drop;
			$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
			playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);
		}

		playerlog($targetinfo['player_id'], "LOG5_ATTACKED_WIN", "$playerinfo[character_name]|$armor_lost|$fighters_lost");
		$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $targetinfo['character_name'] . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
		$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
		$target_exchange_result[] = $l_cmb_target_lost_list;
		playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);
	}

	if ($attacker_armor_left < 1 and $attacker_shields_left < 1)
	{
		//	attacker_died
		update_player_experience($targetinfo['player_id'], $destroying_enemyship);
		update_player_experience($playerinfo['player_id'], $losing_yourship);
		$attacker_exchange_result[] = $l_cmb_attacker_ship_destroyed;
		if ($shipdevice['dev_escapepod']['amount'] == 1)
		{
			$attacker_exchange_result[] = $l_cmb_escapepod_launched;
			player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], $targetinfo['player_id'], $targetinfo['rating'], "killedshippod");
			collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
		}
		else
		{
			$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
			db_kill_player($playerinfo['player_id'], $targetinfo['player_id'], $targetinfo['rating'], "killedship");
			collect_bounty($targetinfo['player_id'],$playerinfo['player_id']);
		}

		adminlog("LOG0_ADMIN_COMBAT", "<font color=\"yellow\"><B>Salvage Ship Values:</B></font><BR> " . print_r($shipinfo, true) . "<br>");
		$ship_value=$upgrade_cost*(round(mypw($upgrade_factor, $shipinfo_old['hull']))+round(mypw($upgrade_factor, $shipinfo_old['engines']))+round(mypw($upgrade_factor, $shipinfo_old['power']))+round(mypw($upgrade_factor, $shipinfo_old['fighter']))+round(mypw($upgrade_factor, $shipinfo_old['sensors']))+round(mypw($upgrade_factor, $shipinfo_old['beams']))+round(mypw($upgrade_factor, $shipinfo_old['torp_launchers']))+round(mypw($upgrade_factor, $shipinfo_old['shields']))+round(mypw($upgrade_factor, $shipinfo_old['armor']))+round(mypw($upgrade_factor, $shipinfo_old['cloak']))+round(mypw($upgrade_factor, $shipinfo_old['ecm'])));
		$ship_salvage_rate = mt_rand(10,20);
		$ship_salvage=$ship_value * ($ship_salvage_rate/100);

		$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET credits=credits+$ship_salvage WHERE player_id=$targetinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$l_cmb_target_salvage=str_replace("[ship_salvage_rate]","<font color=\"#00ff00\">". $ship_salvage_rate . "</font>",$l_cmb_target_salvage);
		$l_cmb_target_salvage=str_replace("[ship_salvage]","<font color=\"#00ff00\">". NUMBER($ship_salvage) . "</font>",$l_cmb_target_salvage);
		$l_cmb_target_salvage=str_replace("[name]","<font color=\"#00ffff\">". $targetinfo['character_name'] . "</font>",$l_cmb_target_salvage);
		$target_exchange_result[] = $l_cmb_target_salvage;
		playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_salvage);

		adminlog("LOG0_ADMIN_COMBAT", "<font color=\"yellow\"><B>Salvage Values:</B></font><BR> Ship Value: $ship_value - $l_att_salv : upgrade_cost = $upgrade_cost, upgrade_factor = $upgrade_factor<br>");

		$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($attacker_fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($attacker_torps_lost) . "</font>",$l_cmb_attacker_lost_list);
		$attacker_exchange_result[] = $l_cmb_attacker_lost_list;
		playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);
	}
	else
	{
		if($attacker_armor_left > 0 && $attacker_armor_left < $shipinfo['armor_pts'])
		{
			calc_internal_damage($shipinfo['ship_id'], 0, ($shipinfo['armor_pts']-$attacker_armor_left) / $shipinfo['armor_pts']);
			$result = $db->SelectLimit("SELECT hull, engines, power, fighter, sensors, beams, torp_launchers, shields, cloak, ecm, armor FROM {$db_prefix}ships WHERE ship_id='$shipinfo[ship_id]'", 1);
			$afteractionshiptech = $result->fields;
			$attacker_exchange_result[] = $l_cmb_attacker_lost_tech;

			$build_log_entry = $l_cmb_attacker_tech_drop;
			$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
			$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
			playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

			if($afteractionshiptech['hull'] < $shipinfo_old['hull'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['engines'] < $shipinfo_old['engines'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['power'] < $shipinfo_old['power'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['fighter'] < $shipinfo_old['fighter'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['sensors'] < $shipinfo_old['sensors'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['beams'] < $shipinfo_old['beams'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['torp_launchers'] < $shipinfo_old['torp_launchers'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['shields'] < $shipinfo_old['shields'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['cloak'] < $shipinfo_old['cloak'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['ecm'] < $shipinfo_old['ecm'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			if($afteractionshiptech['armor'] < $shipinfo_old['armor'])
			{
				$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$l_cmb_attacker_tech_drop);
			}
			else
			{
				$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
				$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
			}

			$attacker_exchange_result[] = $l_cmb_attacker_tech_drop;
		}

		$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship);
		$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($attacker_fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
		$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($attacker_torps_lost) . "</font>",$l_cmb_attacker_lost_list);
		$attacker_exchange_result[] = $l_cmb_attacker_lost_list;
		playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);
	}

	$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
	$template_object->assign("target_exchange_result", $target_exchange_result);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attack_exchange.tpl");

	include ("footer.php");
	die();
}

// Attacker and Target Survived

$attacker_exchange_result[] = str_replace("[name]",$targetinfo['character_name'],$l_cmp_target_survives);

if($target_armor_left > 0 && $target_armor_left < $targetship['armor_pts'])
{
	calc_internal_damage($targetship['ship_id'], 0, ($targetship['armor_pts']-$target_armor_left) / $targetship['armor_pts']);
	$result = $db->SelectLimit("SELECT hull, engines, power, fighter, sensors, beams, torp_launchers, shields, cloak, ecm, armor FROM {$db_prefix}ships WHERE ship_id='$targetship[ship_id]'", 1);
	$afteractionshiptech = $result->fields;
	$attacker_exchange_result[] = $l_cmb_attacker_lost_tech;

	$build_log_entry = $l_cmb_attacker_tech_drop;
	$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
	playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);
}

playerlog($targetinfo['player_id'], "LOG5_ATTACKED_WIN", "$playerinfo[character_name]|$armor_lost|$fighters_lost");
$l_cmb_target_lost_list=str_replace("[player]","<font color=\"#ff0000\">". $targetinfo['character_name'] . "</font>",$l_cmb_target_lost_list);
$l_cmb_target_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($target_armor_lost) . "</font>",$l_cmb_target_lost_list);
$l_cmb_target_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($target_fighters_lost) . "</font>",$l_cmb_target_lost_list);
$l_cmb_target_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($target_energy_lost) . "</font>",$l_cmb_target_lost_list);
$l_cmb_target_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($target_torps_lost) . "</font>",$l_cmb_target_lost_list);
$target_exchange_result[] = $l_cmb_target_lost_list;
playerlog($targetinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $playerinfo['character_name'], $l_cmb_combat_player) . $l_cmb_target_lost_list);

if($attacker_armor_left > 0 && $attacker_armor_left < $shipinfo['armor_pts'])
{
	calc_internal_damage($shipinfo['ship_id'], 0, ($shipinfo['armor_pts']-$attacker_armor_left) / $shipinfo['armor_pts']);
	$result = $db->SelectLimit("SELECT hull, engines, power, fighter, sensors, beams, torp_launchers, shields, cloak, ecm, armor FROM {$db_prefix}ships WHERE ship_id='$shipinfo[ship_id]'", 1);
	$afteractionshiptech = $result->fields;
	$attacker_exchange_result[] = $l_cmb_attacker_lost_tech;

	$build_log_entry = $l_cmb_attacker_tech_drop;
	$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
	$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
	playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

	if($afteractionshiptech['hull'] < $shipinfo_old['hull'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['engines'] < $shipinfo_old['engines'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['power'] < $shipinfo_old['power'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['fighter'] < $shipinfo_old['fighter'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['sensors'] < $shipinfo_old['sensors'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['beams'] < $shipinfo_old['beams'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['torp_launchers'] < $shipinfo_old['torp_launchers'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['shields'] < $shipinfo_old['shields'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['cloak'] < $shipinfo_old['cloak'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['ecm'] < $shipinfo_old['ecm'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	if($afteractionshiptech['armor'] < $shipinfo_old['armor'])
	{
		$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$l_cmb_attacker_tech_drop);
	}
	else
	{
		$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
		$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
	}

	$attacker_exchange_result[] = $l_cmb_attacker_tech_drop;
}

$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship);
$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$l_cmb_attacker_lost_list=str_replace("[armorlost]","<font color=\"#ff0000\">". NUMBER($attacker_armor_lost) . "</font>",$l_cmb_attacker_lost_list);
$l_cmb_attacker_lost_list=str_replace("[fighterslost]","<font color=\"#ff0000\">". NUMBER($attacker_fighters_lost) . "</font>",$l_cmb_attacker_lost_list);
$l_cmb_attacker_lost_list=str_replace("[energylost]","<font color=\"#ff0000\">". NUMBER($attacker_energy_lost) . "</font>",$l_cmb_attacker_lost_list);
$l_cmb_attacker_lost_list=str_replace("[torpslost]","<font color=\"#ff0000\">". NUMBER($attacker_torps_lost) . "</font>",$l_cmb_attacker_lost_list);
$attacker_exchange_result[] = $l_cmb_attacker_lost_list;
playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", str_replace("[player]", $targetinfo['character_name'], $l_cmb_combat_player) . $l_cmb_attacker_lost_list);

$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
$template_object->assign("target_exchange_result", $target_exchange_result);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."attack_exchange.tpl");
include ("footer.php");

?>
