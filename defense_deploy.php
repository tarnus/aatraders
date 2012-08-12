<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: defense_deploy.php

include ("config/config.php");
include ("languages/$langdir/lang_defense_deploy.inc");

get_post_ifset("nummines, numfighters");

$title = $l_defense_deploy_title;

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

//-------------------------------------------------------------------------------------------------

$max_sector_defense_fighters = 0;
$res = $db->Execute("SELECT sector_defense_weapons from {$db_prefix}planets where ((owner = $playerinfo[player_id] or (team = $playerinfo[team] AND $playerinfo[team] <> 0)) and sector_id = $shipinfo[sector_id] and base = 'Y')");
db_op_result($res,__LINE__,__FILE__);
if ($res > 0)
{
	while (!$res->EOF)
	{
		$max_sector_defense_fighters += NUM_PER_LEVEL($res->fields['sector_defense_weapons']) * $sector_fighter_multiplier;
		$res->MoveNext();
	}
}

$result3 = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id=$shipinfo[sector_id] ");
$defenseinfo = $result3->fields;

//Put the defense information into the array "defenseinfo"
$i = 0;
$total_sector_fighters = 0;
$total_sector_mines = 0;
$owns_all = true;
$fighter_id = 0;
$mine_id = 0;

if ($result3 > 0)
{
	while (!$result3->EOF)
	{
		$defenses[$i] = $result3->fields;
		if ($defenses[$i]['defense_type'] == 'fighters')
		{
			$total_sector_fighters += $defenses[$i]['quantity'];
		}
		else
		{
			$total_sector_mines += $defenses[$i]['quantity'];
		}

		if ($defenses[$i]['player_id'] != $playerinfo['player_id'])
		{
			$owns_all = false;
		}
		else
		{
			if ($defenses[$i]['defense_type'] == 'fighters')
			{
				$fighter_id = $defenses[$i]['defense_id'];
			}
			else
			{
				$mine_id = $defenses[$i]['defense_id'];
			}
		}
		$i++;
		$result3->MoveNext();
	}
}

$num_defensesm = $i;

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_defense_deploy_noturn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_deploy_die.tpl");
	include ("footer.php");
	die();
}

$res = $db->SelectLimit("SELECT allow_defenses, {$db_prefix}universe.zone_id, owner FROM {$db_prefix}zones,{$db_prefix}universe " .
					"WHERE sector_id=$shipinfo[sector_id] AND {$db_prefix}zones.zone_id={$db_prefix}universe.zone_id", 1);
$query97 = $res->fields;

if ($query97['allow_defenses'] == 'N')
{
	$template_object->assign("error_msg", $l_defense_deploy_nopermit);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_deploy_die.tpl");
	include ("footer.php");
	die();
}
else
{
	if ($num_defensesm > 0)
	{
		if (!$owns_all)
		{
			$defense_owner = $defenses[0]['player_id'];
			$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$defense_owner", 1);
			$fighters_owner = $result2->fields;

			if ($fighters_owner['team'] != $playerinfo['team'] || $playerinfo['team'] == 0)
			{
				$template_object->assign("error_msg", $l_defense_deploy_nodeploy);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."defense_deploy_die.tpl");
				include ("footer.php");
				die();
			}
		}
	}

	if ($query97['allow_defenses'] == 'L')
	{
		$zone_owner = $query97['owner'];
		$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$zone_owner", 1);
		$zoneowner_info = $result2->fields;

		if ($zone_owner <> $playerinfo['player_id'])
		{
			 if ($zoneowner_info['team'] != $playerinfo['team'] || $playerinfo['team'] == 0)
			 {
				$template_object->assign("error_msg", $l_defense_deploy_nopermit);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."defense_deploy_die.tpl");
				include ("footer.php");
				die();
			 }
		}
	}

	if (!isset($nummines) or !isset($numfighters))
	{
		$availmines = NUMBER($shipinfo['torps']);
		$availfighters = NUMBER($shipinfo['fighters']);
		$l_defense_deploy_info1=str_replace("[sector]",$sectorinfo['sector_name'], $l_defense_deploy_info1);
		$l_defense_deploy_info1=str_replace("[mines]",NUMBER($total_sector_mines), $l_defense_deploy_info1);
		$l_defense_deploy_info1=str_replace("[fighters]",NUMBER($total_sector_fighters), $l_defense_deploy_info1);
		$l_defense_deploy_info2=str_replace("[mines]",$availmines, $l_defense_deploy_info2);
		$l_defense_deploy_info2=str_replace("[fighters]",$availfighters, $l_defense_deploy_info2);

		$l_defense_deploy_max_fighters=str_replace("[amount]", $max_sector_defense_fighters, $l_defense_deploy_max_fighters);

		$template_object->assign("l_defense_deploy_max_fighters", $l_defense_deploy_max_fighters);
		$template_object->assign("l_defense_deploy_info1", $l_defense_deploy_info1);
		$template_object->assign("l_defense_deploy_info2", $l_defense_deploy_info2);
		$template_object->assign("l_defense_deploy_deploy", $l_defense_deploy_deploy);
		$template_object->assign("l_submit", $l_submit);
		$template_object->assign("l_reset", $l_reset);
		$template_object->assign("l_mines_att", $l_defense_deploy_att);
		$template_object->assign("l_fighters", $l_fighters);
		$template_object->assign("l_mines", $l_mines);
		$template_object->assign("shiptorps", $shipinfo['torps']);
		$template_object->assign("shipfighters", (max(0, $max_sector_defense_fighters - $total_sector_fighters) < $shipinfo['fighters']) ? max(0, $max_sector_defense_fighters - $total_sector_fighters) : $shipinfo['fighters']);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."defense_deploy.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		$nummines = stripnum($nummines);
		$numfighters = stripnum($numfighters);
		if (empty($nummines)) 
		{
			$nummines = 0;
		}

		if (empty($numfighters))
		{
			$numfighters = 0;
		}

		if ($nummines < 0) 
		{
			$nummines = 0;
		}

		if ($numfighters < 0) 
		{
			$numfighters =0;
		}

		if ($nummines > $shipinfo['torps'])
		{
			$showmines = $l_defense_deploy_notorps;
			$nummines = 0;
		}
		else
		{
			$l_defense_deploy_dmines=str_replace("[mines]",$nummines, $l_defense_deploy_dmines);
			$showmines = $l_defense_deploy_dmines;
		}

		if ($numfighters > max(0, $max_sector_defense_fighters - $total_sector_fighters))
		{
			$showfighters = $l_defense_deploy_toomanyfighters;
			$numfighters = 0;
		}
		else
		if ($numfighters > $shipinfo['fighters'])
		{
			$showfighters = $l_defense_deploy_nofighters;
			$numfighters = 0;
		}
		else
		{
			$l_defense_deploy_dfighter=str_replace("[fighters]",$numfighters, $l_defense_deploy_dfighter);
			$showfighters = $l_defense_deploy_dfighter;
		}

		$stamp = date("Y-m-d H:i:s");
		if ($numfighters > 0)
		{
			if ($fighter_id != 0)
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $numfighters " .
											"where defense_id = $fighter_id");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			else
			{
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
											"(player_id,sector_id,defense_type,quantity) values " .
											"($playerinfo[player_id],$shipinfo[sector_id],'fighters',$numfighters)");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}

		if ($nummines > 0)
		{
			if ($mine_id != 0)
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $nummines " .
											"where defense_id = $mine_id");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			else
			{
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
											"(player_id,sector_id,defense_type,quantity) values " .
											"($playerinfo[player_id],$shipinfo[sector_id],'mines',$nummines)");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', turns=turns-1, turns_used=turns_used+1 " .
									"WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET fighters=fighters-$numfighters, torps=torps-$nummines WHERE " .
									"ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
	$template_object->assign("showfighters", $showfighters);
	$template_object->assign("showmines", $showmines);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."defense_deploy_show.tpl");
	include ("footer.php");
	die();
}

close_database();
?>
