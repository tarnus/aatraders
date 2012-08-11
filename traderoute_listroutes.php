<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the		 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: traderoute_create.php

include ("config/config.php");
include ("languages/$langdir/lang_traderoute.inc");
include ("languages/$langdir/lang_teams.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_ports.inc");
include ("globals/calc_dist.inc");

$total_experience = 0;

$title = $l_tdr_title;

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

//-------------------------------------------------------------------------------------------------

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$result = $db->Execute("SELECT * FROM {$db_prefix}traderoutes WHERE player_id=$playerinfo[player_id]");
$num_traderoutes = $result->RecordCount();

$i = 0;
while (!$result->EOF)
{
	$traderoutes[$i] = $result->fields;
	$i++;
	$result->MoveNext();
}

// calculate trip time and energy scooped

function traderoute_distance($type1, $type2, $start, $dest, $circuit, $sells = 'N')
{
	global $playerinfo, $shipinfo, $template_object, $shipdevice;
	global $level_factor;
//	global $db, $db_prefix;

	$retvalue['triptime'] = 0;
	$retvalue['scooped1'] = 0;
	$retvalue['scooped2'] = 0;
	$retvalue['scooped'] = 0;

	if ($start == $dest)
	{
		$retvalue['triptime'] = 2;
		return $retvalue;
	}

	$distance=calc_dist($start,$dest);

	$shipspeed = mypw($level_factor, $shipinfo['engines']);
	$triptime = round($distance / $shipspeed);

	if (!$triptime && $destination != $shipinfo['sector_id'])
	$triptime = 1;

	if ($shipdevice['dev_fuelscoop']['amount'] == 1)
	{
		$energyscooped = $distance * 10;
	}
	else
	{
		$energyscooped = 0;
	}

	if ($shipdevice['dev_fuelscoop']['amount'] == 1 && !$energyscooped && $triptime == 1)
	{
		$energyscooped = 10;
	}

	$free_power = NUM_ENERGY($shipinfo['power']);

	if ($free_power < $energyscooped)
	{
		$energyscooped = $free_power;
	}

	if ($energyscooped < 1)
	{
		$energyscooped = 0;
	}

	$retvalue['scooped1'] = floor($energyscooped);

	if ($circuit == 'Y')
	{
		if ($sells == 'Y' && $shipdevice['dev_fuelscoop']['amount'] == 1 && $type2 == 0 && $dest['port_type'] != 'energy')
		{
			$energyscooped = $distance * 10;
			$free_power = NUM_ENERGY($shipinfo['power']);
			if ($free_power < $energyscooped)
			{
				$energyscooped = $free_power;
			}
			$retvalue['scooped2'] = floor($energyscooped);
		}
		elseif ($shipdevice['dev_fuelscoop']['amount'] == 1)
		{
			$energyscooped = $distance * 10;
			$free_power = NUM_ENERGY($shipinfo['power']);
			if ($free_power < $energyscooped)
			{
				$energyscooped = $free_power;
			}
			$retvalue['scooped2'] = floor($energyscooped);
		}
	}

	if ($circuit == 'Y')
	{
		$triptime*=2;
		$triptime+=2;
	}
	else
	{
		$triptime+=1;
	}

	$retvalue['triptime'] = $triptime;
	$retvalue['scooped'] = $retvalue['scooped1'] + $retvalue['scooped2'];

	return $retvalue;
}

$template_object->assign("l_tdr_newtdr", $l_tdr_newtdr);

if ($num_traderoutes == 0)
{
	$template_object->assign("l_tdr_noactive", $l_tdr_noactive);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."traderoute_none.tpl");
	include ("footer.php");
	die();
}else{
	$template_object->assign("l_tdr_curtdr", $l_tdr_curtdr);
	$template_object->assign("l_tdr_src", $l_tdr_src);
	$template_object->assign("l_tdr_srctype", $l_tdr_srctype);
	$template_object->assign("l_tdr_dest", $l_tdr_dest);
	$template_object->assign("l_tdr_desttype", $l_tdr_desttype);
	$template_object->assign("l_tdr_move", $l_tdr_move);
	$template_object->assign("l_tdr_circuit", $l_tdr_circuit);
	$template_object->assign("l_tdr_change", $l_tdr_change);
	$template_object->assign("l_tdr_del", $l_tdr_del);
	$template_object->assign("num_traderoutes", $num_traderoutes);

	$template_object->assign("l_tdr_portin", $l_tdr_portin);
	$template_object->assign("l_tdr_planet", $l_tdr_planet);
	$template_object->assign("l_tdr_within", $l_tdr_within);
	$template_object->assign("l_tdr_nonexistance", $l_tdr_nonexistance);
	$template_object->assign("l_tdr_na", $l_tdr_na);
	$template_object->assign("l_tdr_cargo", $l_tdr_cargo);
	$template_object->assign("l_tdr_none", $l_tdr_none);
	$template_object->assign("l_tdr_colonists", $l_tdr_colonists);
	$template_object->assign("l_tdr_torps", $l_tdr_torps);
	$template_object->assign("l_tdr_fighters", $l_tdr_fighters);
	$template_object->assign("l_tdr_warp", $l_tdr_warp);
	$template_object->assign("l_tdr_turns", $l_tdr_turns);
	$template_object->assign("l_tdr_way", $l_tdr_way);
	$template_object->assign("l_tdr_ways", $l_tdr_ways);
	$template_object->assign("l_tdr_edit", $l_tdr_edit);
	$template_object->assign("l_tdr_trade", $l_tdr_trade);
	$template_object->assign("l_tdr_energy", ucfirst($l_tdr_energy));

	$i = 0;
	while ($i < $num_traderoutes)
	{
		$query = $db->SelectLimit("SELECT {$db_prefix}universe.sector_name, {$db_prefix}zones.zone_name FROM {$db_prefix}universe, {$db_prefix}zones WHERE {$db_prefix}universe.sector_id='" . $traderoutes[$i]['source_sector'] . "' and {$db_prefix}zones.zone_id = {$db_prefix}universe.zone_id", 1);
		db_op_result($query,__LINE__,__FILE__);
		$tradesource_sector[$i] = $query->fields['sector_name'];
		$tradesource_zone[$i] = $query->fields['zone_name'];
		$tradesource_planet_id[$i] = $traderoutes[$i]['source_planet_id'];
		$tradesource_commodity[$i] = ucfirst($traderoutes[$i]['source_commodity']);
		$query = $db->SelectLimit("SELECT {$db_prefix}universe.sector_name, {$db_prefix}zones.zone_name FROM {$db_prefix}universe, {$db_prefix}zones WHERE {$db_prefix}universe.sector_id='" . $traderoutes[$i]['destination_sector'] . "' and {$db_prefix}zones.zone_id = {$db_prefix}universe.zone_id", 1);
		db_op_result($query,__LINE__,__FILE__);
		$trade_destination_sector[$i] = $query->fields['sector_name'];
		$trade_destination_zone[$i] = $query->fields['zone_name'];
		$tradedestination_planet_id[$i] = $traderoutes[$i]['destination_planet_id'];
		$tradedestination_commodity[$i] = ucfirst($traderoutes[$i]['destination_commodity']);
		$trademove_energy[$i] = $traderoutes[$i]['trade_energy'];
		$trademove_fighters[$i] = $traderoutes[$i]['trade_fighters'];
		$trademove_torps[$i] = $traderoutes[$i]['trade_torps'];
		$trademove_type[$i] = $traderoutes[$i]['move_type'];
		$traderoute_id[$i] = $traderoutes[$i]['traderoute_id'];

		$tradesource_commodity[$i] = ucfirst($traderoutes[$i]['source_commodity']);
		$tradesource_name[$i] = "";
		if ($traderoutes[$i]['source_planet_id'] != 0)
		{
			$query = $db->SelectLimit("SELECT name FROM {$db_prefix}planets WHERE planet_id=" . $traderoutes[$i]['source_planet_id'], 1);
			if (!$query || $query->RecordCount() == 0)
			{
				$tradesource_name[$i] = "$l_tdr_nonexistance ";
			}
			else
			{
				$planet = $query->fields;
				if ($planet['name'] == "")
				{
					$tradesource_name[$i] = "$l_unnamed ";
					$tradesource_commodity[$i] = ucfirst($traderoutes[$i]['source_commodity']);
				}
				else
				{
					$tradesource_name[$i] = "$planet[name] ";
					$tradesource_commodity[$i] = ucfirst($traderoutes[$i]['source_commodity']);
				}
			}
		}

		$tradedestination_commodity[$i] = ucfirst($traderoutes[$i]['destination_commodity']);
		$tradedestination_name[$i] = "";
		if ($traderoutes[$i]['destination_planet_id'] != 0)
		{
			$query = $db->SelectLimit("SELECT name FROM {$db_prefix}planets WHERE planet_id=" . $traderoutes[$i]['destination_planet_id'], 1);
			if (!$query || $query->RecordCount() == 0)
			{
				$tradedestination_name[$i] = "$l_tdr_nonexistance ";
			}
			else
			{
				$planet = $query->fields;
				if ($planet['name'] == "")
				{
					$tradedestination_name[$i] = "$l_unnamed ";
					$tradedestination_commodity[$i] = ucfirst($traderoutes[$i]['destination_commodity']);
				}
				else
				{
					$tradedestination_name[$i] = "$planet[name] ";
					$tradedestination_commodity[$i] = ucfirst($traderoutes[$i]['destination_commodity']);
				}
			}
		}
		$trade_roundtrip[$i] = $traderoutes[$i]['roundtrip'];
		if ($traderoutes[$i]['move_type'] == 'R')
		{
			$dist = traderoute_distance($traderoutes[$i]['source_planet_id'], $traderoutes[$i]['destination_planet_id'], $traderoutes[$i]['source_sector'], $traderoutes[$i]['destination_sector'], $traderoutes[$i]['roundtrip']);
			$l_tdr_escooped2 = $l_tdr_escooped;
			$l_tdr_escooped2 = str_replace("[tdr_dist_triptime]", number($dist['triptime']), $l_tdr_escooped2);
			$l_tdr_escooped2 = str_replace("[tdr_dist_scooped]", number($dist['scooped']), $l_tdr_escooped2);
			$trade_energyscoop[$i] = $l_tdr_escooped2;
		}else{
			if ($traderoutes[$i]['roundtrip'] != 'Y' || $traderoutes[$i]['source_sector'] == $traderoutes[$i]['destination_sector'])
			{
				$trade_energyscoop[$i] = 2;
			}else{
				$trade_energyscoop[$i] = 4;
			}
		}
		$i++;
	}

	$template_object->assign("tradesource_sector", $tradesource_sector);
	$template_object->assign("tradesource_zone", $tradesource_zone);
	$template_object->assign("tradesource_planet_id", $tradesource_planet_id);
	$template_object->assign("tradesource_commodity", $tradesource_commodity);
	$template_object->assign("trade_destination_sector", $trade_destination_sector);
	$template_object->assign("trade_destination_zone", $trade_destination_zone);
	$template_object->assign("tradedestination_planet_id", $tradedestination_planet_id);
	$template_object->assign("tradedestination_commodity", $tradedestination_commodity);
	$template_object->assign("trademove_energy", $trademove_energy);
	$template_object->assign("trademove_fighters", $trademove_fighters);
	$template_object->assign("trademove_torps", $trademove_torps);
	$template_object->assign("trademove_type", $trademove_type);
	$template_object->assign("trade_roundtrip", $trade_roundtrip);
	$template_object->assign("traderoute_id", $traderoute_id);

	$template_object->assign("tradesource_name", $tradesource_name);
	$template_object->assign("tradedestination_name", $tradedestination_name);
	$template_object->assign("trade_energyscoop", $trade_energyscoop);

	$template_object->assign("l_sector", $l_sector);
	$template_object->assign("l_delete", $l_tdr_del);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."traderoute_listroutes.tpl");
	include ("footer.php");
}

?>
