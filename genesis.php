<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: genesis.php

include ("config/config.php");
include ("languages/$langdir/lang_genesis.inc");
include ("globals/planet_log.inc");
include ("globals/myrand.inc");


$title = $l_gns_title;

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

$persuasion_countdown = mt_rand(floor($persuasion_countdown_max / 3), $persuasion_countdown_max * 2);
$old_owner_rating = 2;

$result3 = $db->Execute("SELECT COUNT(planet_id) AS total FROM {$db_prefix}planets WHERE owner=$playerinfo[player_id] and base='N'");
$num_unbased_planets = $result3->fields['total'];
$result3->close();

$result3 = $db->Execute("SELECT COUNT(planet_id) AS total FROM {$db_prefix}planets WHERE sector_id='$shipinfo[sector_id]'");
$num_planets = $result3->fields['total'];
$result3->close();

$res = $db->SelectLimit("SELECT {$db_prefix}universe.zone_id, {$db_prefix}zones.allow_planet, {$db_prefix}zones.team_zone, " .
					"{$db_prefix}zones.owner FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
					"{$db_prefix}zones.zone_id=$sectorinfo[zone_id] AND {$db_prefix}universe.sector_id = $shipinfo[sector_id]", 1);
$query97 = $res->fields;

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$dobuild = 0;

if ($num_unbased_planets >= $max_unbased_planets)
{
	$template_object->assign("error_msg", str_replace("[max_unbased_planets]", $max_unbased_planets, $l_gns_max_unbased_planets));
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genesisdie.tpl");
	include ("footer.php");
	die();
}
elseif ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_gns_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genesisdie.tpl");
	include ("footer.php");
	die();
}
elseif ($shipinfo['on_planet'] == 'Y')
{
	$template_object->assign("error_msg", $l_gns_onplanet);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genesisdie.tpl");
	include ("footer.php");
	die();
}
elseif ($num_planets >= $sectorinfo['star_size'])
{
	$template_object->assign("error_msg", $l_gns_full);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genesisdie.tpl");
	include ("footer.php");
	die();
}
elseif ($shipdevice['dev_genesis']['amount'] < 1)
{
	$template_object->assign("error_msg", $l_gns_nogenesis);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genesisdie.tpl");
	include ("footer.php");
	die();
}
else
{
	if ($query97['allow_planet'] == 'N')
	{
		// foo - error occurs here, although removing this section leaves no way for the creation to occur.
		$template_object->assign("error_msg", $l_gns_forbid);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genesisdie.tpl");
		include ("footer.php");
		die();
	}
	elseif ($query97['allow_planet'] == 'L')
	{
		if ($query97['team_zone'] == 'N')
		{
			if ($playerinfo['team'] == 0 && $playerinfo['player_id'] != $query97['owner'])
			{
				$template_object->assign("error_msg", $l_gns_bforbid);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genesisdie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$res = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$query97[owner]", 1);
				$ownerinfo = $res->fields;
				if ($ownerinfo['team'] != $playerinfo['team'] && $playerinfo['player_id'] != $query97['owner'])
				{
					$template_object->assign("error_msg", $l_gns_bforbid);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genesisdie.tpl");
					include ("footer.php");
					die();
				}
				else
				{
					$dobuild = 1;
				}
			}
		}
		elseif ($playerinfo['team'] != $query97['owner'])
		{
			$template_object->assign("error_msg", $l_gns_bforbid);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."genesisdie.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			$dobuild = 1;
		}
	}
	else
	{
		$dobuild = 1;
	}
}

if($dobuild)
{
	$stamp = date("Y-m-d H:i:s");
	$defaultcargototal = 0;
	$extracargototal = 0;

	$cargo_query = $db->SelectLimit("SELECT * from {$db_prefix}class_modules_commodities where defaultcargoplanet!=1 and cargoplanet=1 order by default_create_percent DESC", 1);
	db_op_result($cargo_query,__LINE__,__FILE__);

	$p_create_ratio = 100 / $cargo_query->fields['default_create_percent'];

	$cargo_query = $db->Execute("SELECT default_create_percent, classname, cargoclass, default_prod, default_indy_prod, goodevil, defaultcargoplanet, cargoplanet from {$db_prefix}class_modules_commodities where defaultcargoplanet=1 or cargoplanet=1");
	db_op_result($cargo_query,__LINE__,__FILE__);
	while (!$cargo_query->EOF) 
	{
		$cargo_info = $cargo_query->fields;
		if($cargo_info['defaultcargoplanet'] == 1)
		{
			$dnewcargotype[$defaultcargototal] = $cargo_info['classname'];
			$dcargoclass[$defaultcargototal] = $cargo_info['cargoclass'];
			$ddefault_prod[$defaultcargototal] = $cargo_info['default_prod'];
			$ddefault_indy_prod[$defaultcargototal] = $cargo_info['default_indy_prod'];
			$dis_prod[$defaultcargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
			$dgoodevil[$defaultcargototal] = $cargo_info['goodevil'];
			$defaultcargototal++;
		}
		else
		{
			if($cargo_info['cargoplanet'] == 1)
			{
				$newcargotype[$extracargototal] = $cargo_info['classname'];
				$cargoclass[$extracargototal] = $cargo_info['cargoclass'];
				$default_prod[$extracargototal] = $cargo_info['default_prod'];
				$default_indy_prod[$extracargototal] = $cargo_info['default_indy_prod'];
				$is_prod[$extracargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
				$goodevil[$extracargototal] = $cargo_info['goodevil'];
				$p_create_percent[$extracargototal] = $cargo_info['default_create_percent'] * $p_create_ratio;
				$extracargototal++;
			}
		}
		$cargo_query->Movenext();
	}

	array_multisort($p_create_percent, $newcargotype, $cargoclass, $default_prod, $default_indy_prod, $is_prod, $goodevil);

	$insertlist = "";
	$insertlistprod = "";
	for($ii = 0; $ii < $defaultcargototal; $ii++)
	{
		if($ddefault_prod[$ii] > 0)
		{
			$insertlist .= ", prod_" . AAT_strtolower($dnewcargotype[$ii]);
			$insertlistprod .= ", '$ddefault_prod[$ii]'";
		}
	}

/*	if(mt_rand(0, 100) < 10 && $extracargototal != 0)
	{
		$specialcargo = mt_rand(0, 10000);
		for($checkcargo = $extracargototal - 1; $checkcargo >= 0; $checkcargo--)
		{
			if($specialcargo < floor($p_create_percent[$checkcargo] * 100))
			{
				$special_cargo = $newcargotype[$checkcargo];
				$special_goodevil = $goodevil[$checkcargo];
			}
		}
	}
	else
	{
*/
		$special_cargo = '';
		$special_goodevil = 0;
//	}

	if(mt_rand(1, 100) <= $planet_production_skew)
	{
		$organics_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
	}
	else
	{
		$organics_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
	}

	if(mt_rand(1, 100) <= $planet_production_skew)
	{
		$ore_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
	}
	else
	{
		$ore_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
	}

	if(mt_rand(1, 100) <= $planet_production_skew)
	{
		$goods_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
	}
	else
	{
		$goods_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
	}

	if(mt_rand(1, 100) <= $planet_production_skew)
	{
		$energy_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
	}
	else
	{
		$energy_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
	}

	$creation_date = date("Y-m-d H:i:s");
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}planets 
		(sector_id, last_owner_rating, persuasion_countdown, max_credits, prod_fighters, prod_torp, special_name, special_goodevil, organics_planet, ore_planet, goods_planet, energy_planet, creation_date, creator_id" . $insertlist . ") 
		VALUES 
		('$shipinfo[sector_id]', $old_owner_rating, $persuasion_countdown, '$base_credits', '$default_prod_fighters', '$default_prod_torp', '$special_cargo', '$special_goodevil', '$organics_planet', '$ore_planet', '$goods_planet', '$energy_planet', '$creation_date', $playerinfo[player_id]" . $insertlistprod . ")");
	db_op_result($debug_query,__LINE__,__FILE__);

	$query2 = "UPDATE {$db_prefix}players SET turns_used=turns_used+1, turns=turns-1, planets_built=planets_built+1, planet_update='Y' WHERE " .
			  "player_id=$playerinfo[player_id]";
	$debug_query = $db->Execute($query2);
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_genesis']['device_id']);
	db_op_result($debug_query,__LINE__,__FILE__);

	$logres = $db->Execute("SELECT MAX(planet_id) AS planet_id FROM {$db_prefix}planets WHERE owner = $playerinfo[player_id]");
	
	$newplanet_id = $logres->fields['planet_id'];
	if ($newplanet_id==""){
		$newplanet_id=1;
	}
	$result3 = $db->Execute("SELECT COUNT(planet_id) AS total FROM {$db_prefix}planets WHERE sector_id='$shipinfo[sector_id]'");
	$num_planets = $result3->fields['total'];
	if ($num_planets > $sectorinfo['star_size'])
	{
		$debug_query = $db->Execute("DELETE from {$db_prefix}planets where planet_id=$newplanet_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		$template_object->assign("error_msg", $l_gns_full);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genesisdie.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		planet_log($newplanet_id,$playerinfo['player_id'],$playerinfo['player_id'],"PLOG_GENESIS_CREATE");
		$template_object->assign("error_msg", $l_gns_pcreate);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genesisdie.tpl");
		include ("footer.php");
		die();
	}
}

close_database();
?>
