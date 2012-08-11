<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: combat_sector_missile.php

include ("config/config.php");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_sectormissile.inc");
include ("globals/combat_functions.inc");
include ("globals/ship_bounty_check.inc");
include ("globals/collect_bounty.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/send_system_im.inc");
include ("globals/get_player.inc");
include ("globals/log_move.inc");
include ("globals/get_rating_change.inc");
include ("globals/device_ship_tech_modify.inc");

get_post_ifset("sector, ship_id");

$template_object->enable_gzip = 0;

$title = $l_sm_title;

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

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

$ship_id = stripnum($ship_id);

$result = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE ship_id='$ship_id'", 1);
$targetship = $result->fields;

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$targetship[player_id]", 1);
$targetinfo = $result2->fields;

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sector), 1);
$targetsector = $result2->fields;

$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$ship_id", '', 'class');

$targetship = device_ship_tech_modify($targetship, $targetshipdevice);
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

if ($targetsector['zone_id'] == 2 || $shipinfo['ship_id'] == $ship_id || $targetship['sector_id'] != $targetsector['sector_id'] || $targetship['on_planet'] == "Y" || $ship_id != $targetinfo['currentship'])
{
	$template_object->assign("error_msg", $l_sm_notarg);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_sm_noturn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if ($shipdevice['dev_sectormissile']['amount'] < 1)
{
	$template_object->assign("error_msg", $l_sm_nosectormissile);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

$result = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start='$shipinfo[sector_id]' AND link_dest='$targetsector[sector_id]'");
if($result) {
	if($result->RecordCount() == 0)
	{
		$template_object->assign("error_msg", $l_sm_invalid);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}
}

$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_sectormissile']['device_id']);
db_op_result($debug_query,__LINE__,__FILE__);

/* determine percent chance of success in detecting target ship - based on player's sensors and opponent's cloak */
$success = SCAN_SUCCESS($shipinfo['sensors'], $targetship['cloak'], $shiptypes[$targetship['class']]['basehull']);
$roll = mt_rand(1, 100);
if ($roll > $success)
{
	/* if scan fails - inform both player and target. */
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	playerlog($targetinfo['player_id'], "LOG5_SM_OUTSCAN", "$playerinfo[character_name]");
	$template_object->assign("error_msg", $l_sm_noscan);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

$is_missile_detected = 0;
$success = SCAN_SUCCESS($targetship['sensors'], $shipinfo['cloak'], $shiptypes[$shipinfo['class']]['basehull']);

$roll = mt_rand(1, 100);
if ($roll > $success)
{
	playerlog($targetinfo['player_id'], "LOG5_SM_ATTACK", "$playerinfo[character_name]|$shipinfo[sector_id]");
	$is_missile_detected = 1;
	$player_name = $playerinfo['character_name'];
}
else
{
	$player_name = $l_unknown;
}

$success = SCAN_SUCCESS($shipinfo['engines'], ($targetship['engines'] / 2), $shiptypes[$targetship['class']]['basehull']);
$roll2 = mt_rand(1, 100);

if (($success < $roll2 && $is_missile_detected) || $targetship['player_id'] < 4)
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
	playerlog($targetinfo['player_id'], "LOG5_SM_OUTMAN", "$player_name");
	$template_object->assign("error_msg", $l_sm_flee);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if($is_missile_detected)
{
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
		/* need to change warp destination to random sector in universe */
		$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_sector_missile_attack);
		$source_sector = $shipinfo['sector_id'];

		$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 5 ORDER BY rand()", 1);
		$dest_sector = $findem->fields['sector_id'];

		$debug_query = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$source_sector", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$zones = $debug_query->fields;

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1,rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		playerlog($targetinfo['player_id'], "LOG5_SM_EWD", "$player_name");

		$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET sector_id=$dest_sector, cleared_defenses=' ', on_planet='N' WHERE ship_id=$ship_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
		db_op_result($debug_query,__LINE__,__FILE__);

		log_move($targetinfo['player_id'],$targetship['ship_id'],$source_sector,$dest_sector,$shipinfo['class'],$shipinfo['cloak'],$zones['zone_id']);
		$template_object->assign("error_msg", $l_sm_ewd);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attackdie.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		playerlog($targetinfo['player_id'], "LOG5_SM_EWDFAIL", $playerinfo['character_name']);
	}
}

echo "<H1>$title</H1>\n";

$l_sm_attacking = str_replace("[target]", "<font color=#00ffff><b>$targetinfo[character_name]</b></font>", $l_sm_attacking);
$l_sm_attacking = str_replace("[shipname]", "<font color=white><b>$targetship[name]</b></font>", $l_sm_attacking);
echo "<center><br><b><font size=3 color=#00ff00>$l_sm_attacking</font></b><BR><BR>";

$l_sm_imbody = str_replace("[playername]", "<font color=white><b>$player_name</b></font>", $l_sm_imbody);
send_system_im($targetinfo['player_id'], $l_sm_imtitle, $l_sm_imbody, $targetinfo['last_login']);

$isfedbounty = ship_bounty_check($playerinfo, $targetsector['sector_id'], $targetinfo, 1);

if($isfedbounty > 0)
{
	echo $l_by_fedbounty2 . "<BR><BR>";
}

if(!class_exists('dev_sectormissile')){
	include ("class/devices/dev_sectormissile.inc");
}

$sm_object = new dev_sectormissile();
$sm_damage_shields = $sm_object->damage_shields;
$sm_damage_all = $sm_object->damage_all;

if(!class_exists($targetship['armor_class'])){
	include ("class/" . $targetship['armor_class'] . ".inc");
}

// get target beam, shield and armor values
$target_shield_energy = floor($targetship['energy'] * 0.4);
$sectormissile_attack_energy = $targetship['energy'] - $target_shield_energy;

if (NUM_SHIELDS($targetship['shields']) < $target_shield_energy)
{
	$target_shield_energy = NUM_SHIELDS($targetship['shields']);
}

$targetenergyset = $target_shield_energy + $sectormissile_attack_energy;

$left_over_energy = max(0, $targetship['energy'] - $targetenergyset);

$targetarmor = $targetship['armor_pts'];

$targetshipshields = $targetship['shields'];
$targetshiparmor = $targetship['armor'];
$targetname = $targetinfo['character_name'];

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

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Sector Missile Combat Start:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " (id: $playerinfo[player_id]) 
<br>Sensor Tech: $shipinfo[sensors], Engine Tech: $shipinfo[engines], Cloak Tech: $shipinfo[cloak], Attacking Energy: $sectormissile_attack_energy<br>
<br>Defender ". $targetinfo['character_name'] . " (id: $targetinfo[player_id]) 
<br>Sensor Tech: $targetship[sensors], Shield Tech: $targetship[shields], Engine Tech: $targetship[engines], Energy Tech: $targetship[power], Armor Tech: $targetship[armor], Cloak Tech: $targetship[cloak]
<br>Defending Energy: $target_shield_energy, Defender total energy: $targetship[energy], Energy Left Over: $left_over_energy");

//                 Insert attack code here
echo "<table width=\"500\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" bgcolor=\"#000000\">
	<tr>
		<td align=\"center\">";

$attackerlowpercent = ecmcheck($targetship['ecm'], $shipinfo['sensors'], -mt_rand($full_attack_modifier, 90));
//echo nl2br(print_r($attackerlowpercent, true)) . "<hr>";

if($sectormissile_attack_energy != 0)
{
//	echo "Attack Energy: $sectormissile_attack_energy<br>";
//	echo "Target Energy: $target_shield_energy<br>";
//	echo "Damage Shields:  $sm_damage_shields<br>";
	$attack_fire_damage = calc_damage($sectormissile_attack_energy, $sm_damage_shields, $attackerlowpercent, $targetshipshields, $targetshipshields);

//	echo nl2br(print_r($attack_fire_damage, true)) . "<hr>";

	if($attack_fire_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_sm_sectormissilefail</font><br><br>";
	}

	//
	$target_shields = calc_failure($target_shield_energy, $targetshipshields, $targetshipshields);

	$target_shield_hit_pts = $target_shield_energy * $ship_shield_hit_pts;

	//
	$target_armor = calc_failure($targetarmor, $targetshiparmor, $targetshipshields);

	$target_armor_hit_pts = $targetarmor * $ship_armor_hit_pts;

	$attacker_energy_left = $attack_fire_damage[1];
//	echo $attacker_energy_left . "<br><br>";

	if($attack_fire_damage[0] > $target_shield_hit_pts)
	{
//		echo "Attack Damage: " . $attack_fire_damage[0] . "<br>";
//		echo "Shields hit points:  $target_shield_hit_pts<br><br>";
		$attack_fire_damage[0] = $attack_fire_damage[0] - $target_shield_hit_pts;
//		echo "Attack Damage after: " . $attack_fire_damage[0] . "<br>";
		if($target_shield_energy > 0)
		{
			$l_sm_shieldhit = str_replace("[target]", "<font color=white><b>$targetname</b></font>", $l_sm_shieldhit);
			$l_sm_shieldhit = str_replace("[amount]", "<font color=yellow><b>" . NUMBER($target_shield_energy) . "</b></font>", $l_sm_shieldhit);
			echo "<font color='#00ff00'><b>" . $l_sm_shieldhit . "</b></font><br>";
		}
		$l_sm_shieldsdown = str_replace("[target]", "<font color=yellow><b>$targetname</b></font>", $l_sm_shieldsdown);
		echo "<br><font color='#ff0000' ><b>$l_sm_shieldsdown</b></font><br><br>";
		$target_shields_left = 0;
		$attacker_energy_left = floor($attack_fire_damage[0] / $sm_damage_shields);
//		echo "Attack Damage after: " . $attack_fire_damage[0] . "<br>";
//		echo "Attack shield damage points: " . $sm_damage_shields . "<br>";

		$attackerlowpercent = ecmcheck($targetship['ecm'], $shipinfo['sensors'], -mt_rand($full_attack_modifier, 90));
//		echo nl2br(print_r($attackerlowpercent, true)) . "<hr>";
//		echo "Attack Energy: $attacker_energy_left<br>";
//		echo "Damage Shields:  $sm_damage_all<br><br>";
		$attack_fire2_damage = calc_damage($attacker_energy_left, $sm_damage_all, $attackerlowpercent, $targetshiparmor, $targetshiparmor);
		$attacker_energy_left += $attack_fire2_damage[1];

		if($attack_fire2_damage[2] > 0){
			echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_sm_sectormissilefail2</font><br><br>";
		}
//		echo "Attack damage: " . $attack_fire2_damage[0] . "<br>";
//		echo "Target armor hitpts: " . $target_armor_hit_pts . "<br>";

		if($attack_fire2_damage[0] > $target_armor_hit_pts)
		{
			$attack_fire2_damage[0] = $attack_fire2_damage[0] - $target_armor_hit_pts;
			$attack_damage = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
			{
				$l_sm_armorhit = str_replace("[target]", "<font color=white><b>$targetname</b></font>", $l_sm_armorhit);
				$l_sm_armorhit = str_replace("[amount]", "<font color=yellow><b>" . NUMBER($attack_damage) . "</b></font>", $l_sm_armorhit);
				echo "<font color='#00ff00'><b>" . $l_sm_armorhit . "</b></font><br>";
			}
			$l_sm_armorbreached = str_replace("[target]", "<font color=yellow><b>$targetname</b></font>", $l_sm_armorbreached);
			echo "<br><font color='#ff0000' ><b>$l_sm_armorbreached</b></font><br><br>";
			$attacker_energy_left += floor($attack_fire2_damage[0] / $sm_damage_all);
			$target_armor_left = 0;
		}
		else
		{
			$target_armor_hit_pts = $target_armor_hit_pts - $attack_fire2_damage[0];
			$target_armor_used = floor($attack_fire2_damage[0] / $ship_armor_hit_pts);
//			echo "Target armor hitpts: " . $target_armor_hit_pts . "<br>";
//			echo "Target armor used: " . $target_armor_used . "<br>";
			$l_sm_armorhit = str_replace("[target]", "<font color=white><b>$targetname</b></font>", $l_sm_armorhit);
			$l_sm_armorhit = str_replace("[amount]", "<font color=yellow><b>" . NUMBER($target_armor_used) . "</b></font>", $l_sm_armorhit);
			echo "<font color='#00ff00'><b>" . $l_sm_armorhit . "</b></font><br>";
			$target_armor_left = floor($target_armor_hit_pts / $ship_armor_hit_pts);
		}
	}
	else
	{
		$target_shield_hit_pts = $target_shield_hit_pts - $attack_fire_damage[0];
		$target_shields_used = floor($attack_fire_damage[0] / $ship_shield_hit_pts);
		$l_sm_shieldhit = str_replace("[target]", "<font color=white><b>$targetname</b></font>", $l_sm_shieldhit);
		$l_sm_shieldhit = str_replace("[amount]", "<font color=yellow><b>" . NUMBER($target_shields_used) . "</b></font>", $l_sm_shieldhit);
		echo "<font color='#00ff00'><b>" . $l_sm_shieldhit . "</b></font><br>";
		$target_shields_left = floor($target_shield_hit_pts / $ship_shield_hit_pts);
		$target_armor_left = $targetarmor;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_sm_targetnoenergy</font><b><br><br>";
	$target_shields_left = $target_shield_energy;
	$target_armor_left = $targetarmor;
	$attacker_energy_left = 0;
}

//echo "Shields Energy Left: $target_shields_left<br>";
//echo "Armor Left: $target_armor_left<br>";

//                 End of Attack code
$target_shields_left += $left_over_energy;

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Sector Missile Combat End:</B></font><BR>Defender ".$targetname . " Shields Left = <B>".$target_shields_left.
"</B>, Armor Left = <B>$target_armor_left</B>");

$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST($target_armor_left, 0), energy=GREATEST($target_shields_left, 0)WHERE ship_id=$targetship[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);

update_player_experience($playerinfo['player_id'], $attacking_ship);

if ($target_armor_left < 1)
{
	//	target_died();
	update_player_experience($playerinfo['player_id'], $destroying_enemyship);
	$l_sm_destroyed = str_replace("[target]", "<font color=white><b>" . $targetinfo['character_name'] . "</b></font>", $l_sm_destroyed);
	echo "<BR><font color=#00ffff>". $l_sm_destroyed ."</font><BR>";
	if ($targetshipdevice['dev_escapepod']['amount'] == 1)
	{
		echo "<font color=#ffff00>$l_sm_escapepod</font><BR><BR>";

		player_ship_destroyed($targetship['ship_id'], $targetinfo['player_id'], $targetinfo['rating'], $playerinfo['player_id'], $playerinfo['rating'], "killedsectormissilepod");

		playerlog($targetinfo['player_id'], "LOG5_SM_LOSE", "$player_name|" . $targetshipdevice['dev_escapepod']['amount']);

		collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
	}
	else
	{
		playerlog($targetinfo['player_id'], "LOG5_SM_LOSE", "$playerinfo[character_name]|" . $targetshipdevice['dev_escapepod']['amount']);
		db_kill_player($targetinfo['player_id'], $playerinfo['player_id'], $playerinfo['rating'], "killedsectormissile");
		collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
	}

	$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_sector_missile_attack);

	$ship_value=$upgrade_cost*(round(mypw($upgrade_factor, $targetship['hull']))+round(mypw($upgrade_factor, $targetship['engines']))+round(mypw($upgrade_factor, $targetship['power']))+round(mypw($upgrade_factor, $targetship['fighter']))+round(mypw($upgrade_factor, $targetship['sensors']))+round(mypw($upgrade_factor, $targetship['beams']))+round(mypw($upgrade_factor, $targetship['torp_launchers']))+round(mypw($upgrade_factor, $targetship['shields']))+round(mypw($upgrade_factor, $targetship['armor']))+round(mypw($upgrade_factor, $targetship['cloak']))+round(mypw($upgrade_factor, $targetship['ecm'])));
	$ship_salvage_rate = mt_rand(10,20);
	$ship_salvage=$ship_value*$ship_salvage_rate/100;

	$l_att_ysalv=str_replace("[ship_salvage_rate]","<font color=#ffffff>". $ship_salvage_rate . "</font>",$l_att_ysalv);
	$l_att_ysalv=str_replace("[ship_salvage]","<font color=#ffffff>". NUMBER($ship_salvage) . "</font>",$l_att_ysalv);
	$l_att_ysalv=str_replace("[rating_change]","<font color=#ffffff>". NUMBER(abs($rating_change)) . "</font>",$l_att_ysalv);

	echo "<font color=#00ff00>$l_att_ysalv</font>";

	$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET credits=credits+$ship_salvage, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$armor_lost=$targetship['armor_pts']-$target_armor_left;
	$energy_lost=$targetship['energy'] - $target_shields_left;

	$l_sm_lost = str_replace("[target]", "<font color=white><b>$targetinfo[character_name]</b></font>", $l_sm_lost);
	$l_sm_lost = str_replace("[armor]", "<font color=yellow><b>" . NUMBER($armor_lost) . "</b></font>", $l_sm_lost);
	$l_sm_lost = str_replace("[energy]", "<font color=white><b>" . NUMBER($energy_lost) . "</b></font>", $l_sm_lost);
	echo "<font color=#00ff00>$l_sm_lost</font><BR><BR>";

}
else
{
	$l_sm_targetok=str_replace("[name]",$targetinfo['character_name'],$l_sm_targetok);
	echo "<b><font color=#ff0000>$l_sm_targetok</font></b><BR><br>";

	if($target_armor_left > 0)
	{
		calc_internal_damage($targetship['ship_id'], 0, ($targetship['armor_pts']-$target_armor_left) / $targetship['armor_pts']);
	}
	$armor_lost=$targetship['armor_pts'] - $target_armor_left;
	$energy_lost=$targetship['energy'] - $target_shields_left;
	playerlog($targetinfo['player_id'], "LOG5_SM_WIN", "$player_name|$armor_lost|$energy_lost");
	$l_sm_lost = str_replace("[target]", "<font color=white><b>$targetinfo[character_name]</b></font>", $l_sm_lost);
	$l_sm_lost = str_replace("[armor]", "<font color=yellow><b>" . NUMBER($armor_lost) . "</b></font>", $l_sm_lost);
	$l_sm_lost = str_replace("[energy]", "<font color=white><b>" . NUMBER($energy_lost) . "</b></font>", $l_sm_lost);
	echo "<font color=#00ff00>$l_sm_lost</font><BR><BR>";

	$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship);
	$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1, rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}

echo "</td></tr></table></center>";
echo "<br><br>";

echo $l_global_mmenu;

include ("footer.php");

?>
