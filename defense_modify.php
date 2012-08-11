<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: defense_modify.php

include ("config/config.php");
include ("globals/combat_functions.inc");
include ("languages/$langdir/lang_modify_defenses.inc");
include ("globals/explode_mines.inc");
include ("globals/message_defense_owner.inc");

get_post_ifset("defense_id, response, quantity");

$template_object->enable_gzip = 0;

$title = $l_md_title;

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

if (!isset($defense_id))
{
	$template_object->assign("error_msg", $l_md_invalid);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_modify_die.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns']<1)
{
	$template_object->assign("error_msg", $l_md_noturn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_modify_die.tpl");
	include ("footer.php");
	die();
}

$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}sector_defense WHERE defense_id=$defense_id ", 1);
//Put the defense information into the array "defenseinfo"
if ($result3 == 0)
{
	$template_object->assign("error_msg", $l_md_nolonger);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_modify_die.tpl");
	include ("footer.php");
	die();
}

$defenseinfo = $result3->fields;
if ($defenseinfo['sector_id'] <> $shipinfo['sector_id'])
{
	$template_object->assign("error_msg", $l_md_nothere);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_modify_die.tpl");
	include ("footer.php");
	die();
}
if ($defenseinfo['player_id'] == $playerinfo['player_id'])
{
	$defense_owner = $l_md_you;
}
else
{
	$defense_player_id = $defenseinfo['player_id'];
	$resulta = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id = $defense_player_id ", 1);
	$ownerinfo = $resulta->fields;
	$defense_owner = $ownerinfo['character_name'];
}

$defense_type = $defenseinfo['defense_type'] == 'fighters' ? $l_fighters : $l_mines;
$qty = $defenseinfo['quantity'];

switch($response)
{
	case "fight":
		if ($defenseinfo['player_id'] == $playerinfo['player_id'])
		{
			$template_object->assign("error_msg", $l_md_yours);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."defense_modify_die.tpl");
			include ("footer.php");
			die();
		}

		$sector = $shipinfo['sector_id'] ;
		$num_defenses = 0;
		$result3 = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sector' and player_id != '$playerinfo[player_id]' ORDER BY quantity DESC");
		if ($result3 > 0)
		{
			while (!$result3->EOF)
			{
				$row = $result3->fields;
				$defenses[$num_defenses] = $row;
				if ($defenses[$num_defenses]['defense_type'] == 'fighters')
				{
					$total_sector_fighters += $defenses[$num_defenses]['quantity'];
				}
				elseif ($defenses[$num_defenses]['defense_type'] == 'mines')
				{
					$total_sector_mines += $defenses[$num_defenses]['quantity'];
				}

				$num_defenses++;
				$result3->MoveNext();
			}
		}
		$defenses['mines']=$total_sector_mines;
		$defenses['fighters']=$total_sector_fighters;

		$fm_owner = $defenses[0]['player_id'];
		$result9 = $db->Execute("SELECT * from {$db_prefix}players where player_id=$fm_owner");
		$fighters_owner = $result9->fields;

		if ($defenseinfo['defense_type'] == 'fighters')
		{
			$destination = $sector;
			include ("sector_defense/fighters.inc");

			$template_object->assign("error_msg", "");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."defense_modify_die.tpl");
			include ("footer.php"); 
			die();
		}
		else
		{
			// Attack mines goes here
			$destination = $sector;
			$total_sector_mines= $defenses['mines'];
			$target_mine_used = 0;
			$attacker_shield_energy = floor($shipinfo['energy'] * 0.4);
			$attacker_beam_energy = $shipinfo['energy'] - $attacker_shield_energy;

			$attackerbeams = NUM_BEAMS($shipinfo['beams']);

			if ($attackerbeams < $attacker_beam_energy)
			{
				$attacker_beam_energy = $attackerbeams;
			}

			$attack_beamtomine_dmg = floor($attacker_beam_energy * 0.025);

			$highsensors=0;
			// get planet sensors
			$result4 = $db->SelectLimit("SELECT sector_defense_sensors from {$db_prefix}planets where (owner!=$playerinfo[player_id] and (team > 0 and team!=$playerinfo[team])) and base='Y' and sector_id='$destination' order by sensors DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;

			if ($highsensors < $planets['sector_defense_sensors']){
				$highsensors=$planets['sector_defense_sensors'];
			}

			$highcloak=0;
			// get planet sensors
			$result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner!=$playerinfo[player_id] and (team > 0 and team!=$playerinfo[team])) and base='Y' and sector_id='$destination' order by cloak DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;

			if ($highcloak < $planets['sector_defense_cloak']){
				$highcloak=$planets['sector_defense_cloak'];
			}

			$attackerlowpercent = ecmcheck($highcloak, $shipinfo['sensors'], $full_attack_modifier);
			$targetlowpercent = ecmcheck($shipinfo['cloak'], $highsensors, -$full_attack_modifier);

			if(!class_exists($shipinfo['beam_class'])){
				include ("class/" . $shipinfo['beam_class'] . ".inc");
			}

			$attackobject = new $shipinfo['beam_class']();
			$beam_damage_all = $attackobject->beam_damage_all;

			if(!class_exists("Sector_Mine")){
				include ("class/sector/Sector_Mine.inc");
			}

			$targetobject = new Sector_Mine();
			$mine_hit_pts = $targetobject->hit_pts;
   
			$target_mines_used = 0;
			$attack_energy_left = $attack_beamtomine_dmg;
			if($attack_beamtomine_dmg != 0)
			{
				$attack_mine_damage = calc_damage($attack_beamtomine_dmg, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $highcloak);
				$attack_energy_left = $attack_mine_damage[1];

				$target_mine_hit_pts = $total_sector_mines * $mine_hit_pts;
				if($attack_mine_damage[0] > $target_mine_hit_pts)
				{
					$attack_mine_damage[0] = $attack_mine_damage[0] - $target_mine_hit_pts;
					$attack_energy_left = floor($attack_mine_damage[0] / $beam_damage_all);
					$target_mine_used = $total_sector_mines;
				} 
				else
				{
					$target_mine_used = floor($attack_mine_damage[0] / $mine_hit_pts);
				}
			}

			$attackerenergyused = $attack_beamtomine_dmg - $attack_energy_left;

			$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET energy=energy-$attackerenergyused WHERE " .
										"ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			if($target_mine_used > 0){
				explode_mines($destination, $target_mine_used);
			}
			$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$sector'", 1);
			if($sector_check->RecordCount()){
				$sect = $sector_check->fields;
				$sectorname = $sect['sector_name'];
			}

			$inputtype[0] = "[sector]";
			$inputdata[0] = "<a href=main.php?move_method=real&engage=1&destination=$sectorname>$sectorname</a>";
			$inputtype[1] = "[mines]";
			$inputdata[1] = NUMBER($target_mine_used);
			$inputtype[2] = "[name]";
			$inputdata[2] = $playerinfo['character_name'];
			message_defense_owner($sector, "l_md_msgdownerb", "lang_modify_defenses.inc", "mines", $inputtype, $inputdata);

			$l_md_msgdownerb = str_replace("[name]", $playerinfo['character_name'], str_replace("[mines]", NUMBER($target_mine_used), str_replace("[sector]", "<a href=main.php?move_method=real&engage=1&destination=$sectorname>$sectorname</a>", $l_md_msgdownerb)));
			$template_object->assign("error_msg", $l_md_msgdownerb);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."defense_modify_die.tpl");
			include ("footer.php");
			die();
		}
		break;

	case "retrieve":
		if ($defenseinfo['player_id'] <> $playerinfo['player_id'])
		{
			$template_object->assign("error_msg", "$l_md_bmines $playerbeams $l_mines");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."defense_modify_die.tpl");
			include ("footer.php");
			die();
		}

		$quantity = stripnum($quantity);
		if ($quantity < 0)
		{
			$quantity = 0;
		}

		if ($quantity > $defenseinfo['quantity'])
		{
			$quantity = $defenseinfo['quantity'];
		}

		$torpedo_max = NUM_TORPEDOES($shipinfo['torp_launchers']) - $shipinfo['torps'];
		$fighter_max = NUM_FIGHTERS($shipinfo['fighter']) - $shipinfo['fighters'];
		if ($defenseinfo['defense_type'] == 'fighters')
		{
			if ($quantity > $fighter_max)
			{
				$quantity = $fighter_max;
			}
		}

		if ($defenseinfo['defense_type'] == 'mines')
		{
			if ($quantity > $torpedo_max)
			{
				$quantity = $torpedo_max;
			}
		}

		$ship_id = $shipinfo['ship_id'];
		if ($quantity > 0)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense SET quantity=quantity - $quantity WHERE " .
										"defense_id = $defense_id");
			db_op_result($debug_query,__LINE__,__FILE__);

			if ($defenseinfo['defense_type'] == 'mines')
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}ships set torps=torps + $quantity WHERE ship_id = $ship_id");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			else
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}ships set fighters=fighters + $quantity WHERE ship_id = $ship_id");
				db_op_result($debug_query,__LINE__,__FILE__);
			}

			$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE quantity <= 0");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$stamp = date("Y-m-d H:i:s");

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp',turns=turns-1, turns_used=turns_used+1 " .
									"WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id] WHERE " .
									"player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$template_object->assign("error_msg", "$l_md_retr $quantity $defense_type.");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."defense_modify_die.tpl");
		include ("footer.php");
		die();
		break;

	default:
		$l_md_consist=str_replace("[qty]",$qty,$l_md_consist);
		$l_md_consist=str_replace("[type]",$defense_type,$l_md_consist);
		$l_md_consist=str_replace("[owner]",$defense_owner,$l_md_consist);

		if ($defenseinfo['player_id'] != $playerinfo['player_id'])
		{
			$player_id = $defenseinfo['player_id'];
			$result2 = $db->SelectLimit("SELECT team from {$db_prefix}players where player_id=$player_id", 1);
			$fighters_owner = $result2->fields;

			if ($fighters_owner['team'] != $playerinfo['team'] || $playerinfo['team'] == 0)
			{
				$fight = 1;
			}else{
				$fight = 0;
			}
		}

		$template_object->assign("l_md_consist", $l_md_consist);
		$template_object->assign("defenseid", $defenseinfo['player_id']);
		$template_object->assign("playerid", $playerinfo['player_id']);
		$template_object->assign("l_md_youcan", $l_md_youcan);
		$template_object->assign("l_md_retrieve", $l_md_retrieve);
		$template_object->assign("defense_type", $defense_type);
		$template_object->assign("defense_id", $defense_id);
		$template_object->assign("l_submit", $l_submit);
		$template_object->assign("defensetype", $defenseinfo['defense_type']);
		$template_object->assign("l_md_attack", $l_md_attack);
		$template_object->assign("fight", $fight);
		$template_object->assign("l_md_consist", $l_md_consist);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."defense_modify.tpl");
		include ("footer.php");
		die();
		break;
}

close_database();
?>
