<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: shipyard_purchase.inc

include ("languages/$langdir/lang_shipyard.inc");
include ("languages/$langdir/lang_shipyard2.inc");
include ("globals/gen_score.inc");

get_post_ifset("hull_upgrade, engine_upgrade, power_upgrade, fighter_upgrade, sensors_upgrade, armor_upgrade, shields_upgrade, beams_upgrade, torp_launchers_upgrade, cloak_upgrade, ecm_upgrade, confirm, keep, total_cost, stype, newshipvalue, switch, shipid1");

if ($switch!="yes"){
$title = $l_ship2_buytitle;
}else{
$title = $l_ship2_storetitle;
}
$template_object->assign("planet_id",$planet_id);
$template_object->assign("l_clickme",$l_clickme);
$template_object->assign("l_toplanetmenu",$l_toplanetmenu);

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id=$sectorinfo[zone_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$zoneinfo = $debug_query->fields;
$debug_query->close();
/*  Commented out for fed changes 4-13-2010
$res2 = $db->Execute("SELECT SUM(amount) as total_bounty FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1) AND bounty_on = $shipinfo[player_id]");
if ($res2)
{
	$bty = $res2->fields;
	if ($bty['total_bounty'] > 0)
	{
		if ($pay <> 1)
		{
			$l_port_bounty2 = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_bounty2);
			$template_object->assign("l_port_bounty", $l_port_bounty);
			$template_object->assign("l_port_bounty2", $l_port_bounty2);
			$template_object->assign("l_by_placebounty", $l_by_placebounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/shipyardbounty.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			if ($playerinfo['credits'] < $bty['total_bounty'])
			{
				$l_port_btynotenough = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_btynotenough);
				$template_object->assign("error_msg", $l_port_btynotenough);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/shipyarddie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$bty[total_bounty] WHERE player_id = $shipinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE from {$db_prefix}bounty WHERE bounty_on = $shipinfo[player_id] AND (placed_by = 3 or placed_by = 1)");
				db_op_result($debug_query,__LINE__,__FILE__);

				$template_object->assign("error_msg", $l_port_bountypaid);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/shipyarddie.tpl");
				include ("footer.php");
				die();
			}
		}
	}
}
$res2->close();
*/
if($zoneinfo['zone_id'] != 3){
	$alliancefactor = 1;
}

$res = $db->Execute("SELECT * FROM {$db_prefix}ship_types WHERE buyable = 'Y' order by type_id");
while (!$res->EOF)
{
	$ships[] = $res->fields;
	$res->MoveNext();
}
$res->close();

if (isset($stype))
{
	$lastship = end($ships);
	if ($stype < 1 || $stype > $lastship['type_id'])
	{
		$template_object->assign("error_msg", $l_ship2_wrongclass);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/shipyard2die.tpl");
		include ("footer.php");
		die();
	}
}
else
{
	$template_object->assign("error_msg", $l_ship2_wrongclass);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/shipyard2die.tpl");
	include ("footer.php");
	die();
}

foreach($ships as $testship)
{
	if ($testship['type_id'] == $stype)
	{
		$sship = $testship;
		break;
	}
}

if (!isset($confirm)) //display info only
{
	
	$calc_hull = phpChangeDelta($shipinfo['hull'], 0);
	$calc_engines = phpChangeDelta($shipinfo['engines'], 0);
	$calc_power = phpChangeDelta($shipinfo['power'], 0);
	$calc_fighter = phpChangeDelta($shipinfo['fighter'], 0);
	$calc_sensors = phpChangeDelta($shipinfo['sensors'], 0);
	$calc_beams = phpChangeDelta($shipinfo['beams'], 0);
	$calc_torp_launchers = phpChangeDelta($shipinfo['torp_launchers'], 0);
	$calc_shields = phpChangeDelta($shipinfo['shields'], 0);
	$calc_armor = phpChangeDelta($shipinfo['armor'], 0);
	$calc_cloak = phpChangeDelta($shipinfo['cloak'], 0);
	$calc_ecm = phpChangeDelta($shipinfo['ecm'], 0);

	$res = $db->SelectLimit("SELECT cost_tobuild FROM {$db_prefix}ship_types WHERE type_id = $shipinfo[class]", 1);
	db_op_result($res,__LINE__,__FILE__);
	$shipcost = $res->fields['cost_tobuild'];
	$res->close();

	$creditreturn = 0;
	if ($shipinfo['class']!=10){
		$creditreturn = $shipdevice['dev_warpedit']['amount']*$dev_warpedit_price;
		$creditreturn += $shipdevice['dev_genesis']['amount']*$dev_genesis_price;
		$creditreturn += $shipdevice['dev_sectorgenesis']['amount']*$dev_sectorgenesis_price;
		$creditreturn += $shipdevice['dev_emerwarp']['amount']*$dev_emerwarp_price;
		$creditreturn += $shipdevice['dev_escapepod']['amount']* $dev_escapepod_price;
		$creditreturn += $shipdevice['dev_fuelscoop']['amount']* $dev_fuelscoop_price;
		$creditreturn += $shipdevice['dev_nova']['amount'] * $dev_nova_price;
		$creditreturn += $shipdevice['dev_minedeflector']['amount']*$dev_minedeflector_price;
	}

	$creditreturn += $shipinfo['torps']*$torpedo_price;
	$creditreturn += $shipinfo['armor_pts']*$armor_price;
	$creditreturn += $shipinfo['ore']*$ore_price;
	$creditreturn += $shipinfo['organics']*$organics_price;
	$creditreturn += $shipinfo['goods']*$goods_price;
	$creditreturn += $shipinfo['energy']*$energy_price;
	$creditreturn += $shipinfo['colonists']*$colonist_price;
	$creditreturn += $shipinfo['fighters']*$fighter_price;

	$shipvalue = $creditreturn + $shipcost + $calc_hull+$calc_engines+$calc_power+$calc_fighter+$calc_sensors+$calc_beams+$calc_torp_launchers+$calc_shields+$calc_armor+$calc_cloak+$calc_ecm;
	$shipvalue /= 2;

	$price_modifier_base = explode("|", $playerinfo['ship_losses']);

	for($i = 0; $i < count($price_modifier_base); $i++){
		$items = explode("-", $price_modifier_base[$i]);
		$element = $items[0];
		$price_modifier[$element] = $items[1];
		if($price_modifier[$element] < 1)
			$price_modifier[$element] = 0;
	}

	$res = $db->Execute("SELECT type_id FROM {$db_prefix}ship_types WHERE buyable = 'Y'");
	$type_count = $res->RecordCount(); 

	$new_losses = "";
	for($i = 0; $i < $type_count; $i++){
		$element = $res->fields['type_id'];
		if($price_modifier[$element] < 1)
			$price_modifier[$element] = 0;
		$res->MoveNext();
	}
	$res->close();

	$ship_price = ($price_modifier[$stype] * ($sship['cost_tobuild'] * ($ship_cost_increase / 100))) + $sship['cost_tobuild'];
		
	$calc_nhull = phpChangeDelta($hull_upgrade, 0);
	$calc_nengines = phpChangeDelta($engine_upgrade, 0);
	$calc_npower = phpChangeDelta($power_upgrade,0);
	$calc_nfighter = phpChangeDelta($fighter_upgrade, 0);
	$calc_nsensors = phpChangeDelta($sensors_upgrade, 0);
	$calc_nbeams = phpChangeDelta($beams_upgrade, 0);
	$calc_ntorp_launchers = phpChangeDelta($torp_launchers_upgrade, 0);
	$calc_nshields = phpChangeDelta($shields_upgrade, 0);
	$calc_narmor = phpChangeDelta($armor_upgrade, 0);
	$calc_ncloak = phpChangeDelta($cloak_upgrade, 0);
	$calc_necm = phpChangeDelta($ecm_upgrade, 0);

	$techvalue = $calc_nhull+$calc_nengines+$calc_npower+$calc_nfighter+$calc_nsensors+$calc_nbeams+$calc_ntorp_launchers+$calc_nshields+$calc_narmor+$calc_ncloak+$calc_necm;
	$newshipvalue=($techvalue + $ship_price) * $alliancefactor;

	$totalcost = $newshipvalue - $shipvalue; 

	$template_object->assign("l_player", $l_player);
	$template_object->assign("l_credits", $l_credits);
	$template_object->assign("l_ship2_buying", $l_ship2_buying);
	$template_object->assign("hull_upgrade", $hull_upgrade);
	$template_object->assign("engine_upgrade", $engine_upgrade);
	$template_object->assign("power_upgrade", $power_upgrade);
	$template_object->assign("fighter_upgrade", $fighter_upgrade);
	$template_object->assign("sensors_upgrade", $sensors_upgrade);
	$template_object->assign("beams_upgrade", $beams_upgrade);
	$template_object->assign("torp_launchers_upgrade", $torp_launchers_upgrade);
	$template_object->assign("shields_upgrade", $shields_upgrade);
	$template_object->assign("armor_upgrade", $armor_upgrade);
	$template_object->assign("cloak_upgrade", $cloak_upgrade);
	$template_object->assign("ecm_upgrade", $ecm_upgrade);
	
	$template_object->assign("shipname", $sship['name']);
	$template_object->assign("shipimage", "templates/".$templatename."images/$sship[image]");
	$template_object->assign("shipinfo", $sship['description']);
	$template_object->assign("l_ship2_tradein", $l_ship2_tradein);
	$template_object->assign("l_ship2_value", $l_ship2_value);
	$template_object->assign("shipvalue", NUMBER($shipvalue));
	$template_object->assign("newshipcheck", $newshipvalue);
	$template_object->assign("newshipvalue", NUMBER($newshipvalue));
	$template_object->assign("numbertotalcost", $totalcost);
	$template_object->assign("totalcost", NUMBER($totalcost));
	$template_object->assign("l_ship2_newvalue", $l_ship2_newvalue);
	$template_object->assign("l_ship2_totalcost", $l_ship2_totalcost);
	$template_object->assign("totalcost", NUMBER($totalcost));
	$template_object->assign("credits", $playerinfo['credits']);
	$template_object->assign("numbercredits", NUMBER($playerinfo['credits']));
	$template_object->assign("l_ship2_nomoney", $l_ship2_nomoney);
	$template_object->assign("stype", $stype);
	$template_object->assign("l_ship2_purchase", $l_ship2_purchase);
	$template_object->assign("class", $shipinfo['class']);
	$template_object->assign("l_ship2_buynstore", $l_ship2_buynstore);
	$template_object->assign("l_ship2_newvalue", $l_ship2_newvalue);
	$template_object->assign("newshipvalue2", NUMBER($newshipvalue));
	$template_object->assign("newshipvalue3", $newshipvalue);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/shipyard2.tpl");
	include ("footer.php");
	die();
}
else //ok, now we buy the ship for true
{
	// place ship in storage and get one out of storage.
	if ($switch=="yes"){
		$res2 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE ship_id=$shipid1");

		while (!$res2->EOF)
		{
			$ships2 = $res2->fields;
			$res2->MoveNext();
			$storageflag=1;
		}

		//update old ship and add initial storage fee
		$creditreturn = 0;
		if ($shipinfo['class']!=10)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET storage_planet_id='$planet_id', on_planet='N', planet_id=0
										WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			$debug_query = $db->Execute("delete from  {$db_prefix}ships WHERE ship_id=$shipinfo[ship_id]");
			$debug_query = $db->Execute("delete from  {$db_prefix}ship_devices WHERE ship_id=$shipinfo[ship_id]");
			$debug_query = $db->Execute("delete from  {$db_prefix}ship_holds WHERE ship_id=$shipinfo[ship_id]");
			//sell stuff back0
			$creditreturn = $shipdevice['dev_warpedit']['amount']*$dev_warpedit_price;
			$creditreturn += $shipdevice['dev_genesis']['amount']*$dev_genesis_price;
			$creditreturn += $shipdevice['dev_sectorgenesis']['amount']*$dev_sectorgenesis_price;
			$creditreturn += $shipdevice['dev_emerwarp']['amount']*$dev_emerwarp_price;
			$creditreturn += $shipdevice['dev_escapepod']['amount']* $dev_escapepod_price;
			$creditreturn += $shipdevice['dev_fuelscoop']['amount']* $dev_fuelscoop_price;
			$creditreturn += $shipdevice['dev_nova']['amount'] * $dev_nova_price;
			$creditreturn += $shipdevice['dev_minedeflector']['amount']*$dev_minedeflector_price;

			$creditreturn += $shipinfo['torps']*$torpedo_price;
			$creditreturn += $shipinfo['armor_pts']*$armor_price;
			$creditreturn += $shipinfo['ore']*$ore_price;
			$creditreturn += $shipinfo['organics']*$organics_price;
			$creditreturn += $shipinfo['goods']*$goods_price;
			$creditreturn += $shipinfo['energy']*$energy_price;
			$creditreturn += $shipinfo['colonists']*$colonist_price;
			$creditreturn += $shipinfo['fighters']*$fighter_price;
			$creditreturn /= 2;
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], storage_planet_id=0, planet_id=0, on_planet='N' WHERE ship_id=$shipid1");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($enable_spies)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET ship_id = $shipid1 WHERE ship_id = $shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if ($enable_dignitaries)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET ship_id = $shipid1 WHERE ship_id = $shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET ship_id = $shipid1 WHERE ship_id = $shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		//Insert current ship in players table
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET currentship=$shipid1, credits=credits + $creditreturn " . 
									"WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$template_object->assign("error_msg", $l_ship2_paystorage);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/shipyard2die.tpl");
		include ("footer.php");
		die();
	}else{
		// buy new ship
		$calc_hull = phpChangeDelta($shipinfo['hull'], 0);
		$calc_engines = phpChangeDelta($shipinfo['engines'], 0);
		$calc_power = phpChangeDelta($shipinfo['power'], 0);
		$calc_fighter = phpChangeDelta($shipinfo['fighter'], 0);
		$calc_sensors = phpChangeDelta($shipinfo['sensors'], 0);
		$calc_beams = phpChangeDelta($shipinfo['beams'], 0);
		$calc_torp_launchers = phpChangeDelta($shipinfo['torp_launchers'], 0);
		$calc_shields = phpChangeDelta($shipinfo['shields'], 0);
		$calc_armor = phpChangeDelta($shipinfo['armor'], 0);
		$calc_cloak = phpChangeDelta($shipinfo['cloak'], 0);
		$calc_ecm = phpChangeDelta($shipinfo['ecm'], 0);

		$res = $db->SelectLimit("SELECT cost_tobuild FROM {$db_prefix}ship_types WHERE type_id = $shipinfo[class]", 1);
		db_op_result($res,__LINE__,__FILE__);
		$shipcost = $res->fields['cost_tobuild'];
		$res->close();

		$shipvalue = $shipcost + $calc_hull+$calc_engines+$calc_power+$calc_fighter+$calc_sensors+$calc_beams+$calc_torp_launchers+$calc_shields+$calc_armor+$calc_cloak+$calc_ecm;
		$shipvalue /= 2;

		$price_modifier_base = explode("|", $playerinfo['ship_losses']);

		for($i = 0; $i < count($price_modifier_base); $i++){
			$items = explode("-", $price_modifier_base[$i]);
			$element = $items[0];
			$price_modifier[$element] = $items[1];
			if($price_modifier[$element] < 1)
				$price_modifier[$element] = 0;
		}

		$res = $db->Execute("SELECT type_id FROM {$db_prefix}ship_types WHERE buyable = 'Y'");
		$type_count = $res->RecordCount(); 

		$new_losses = "";
		for($i = 0; $i < $type_count; $i++){
			$element = $res->fields['type_id'];
			if($price_modifier[$element] < 1)
				$price_modifier[$element] = 0;
			$res->MoveNext();
		}
		$res->close();

		$ship_price = ($price_modifier[$stype] * ($sship['cost_tobuild'] * ($ship_cost_increase / 100))) + $sship['cost_tobuild'];
		
	$calc_nhull = phpChangeDelta($hull_upgrade, 0);
	$calc_nengines = phpChangeDelta($engine_upgrade, 0);
	$calc_npower = phpChangeDelta($power_upgrade,0);
	$calc_nfighter = phpChangeDelta($fighter_upgrade, 0);
	$calc_nsensors = phpChangeDelta($sensors_upgrade, 0);
	$calc_nbeams = phpChangeDelta($beams_upgrade, 0);
	$calc_ntorp_launchers = phpChangeDelta($torp_launchers_upgrade, 0);
	$calc_nshields = phpChangeDelta($shields_upgrade, 0);
	$calc_narmor = phpChangeDelta($armor_upgrade, 0);
	$calc_ncloak = phpChangeDelta($cloak_upgrade, 0);
	$calc_necm = phpChangeDelta($ecm_upgrade, 0);
	/*
		$calc_nhull = phpChangeDelta($sship['minhull'], 0);
		$calc_nengines = phpChangeDelta($sship['minengines'], 0);
		$calc_npower = phpChangeDelta($sship['minpower'], 0);
		$calc_nfighter = phpChangeDelta($sship['minfighter'], 0);
		$calc_nsensors = phpChangeDelta($sship['minsensors'], 0);
		$calc_nbeams = phpChangeDelta($sship['minbeams'], 0);
		$calc_ntorp_launchers = phpChangeDelta($sship['mintorp_launchers'], 0);
		$calc_nshields = phpChangeDelta($sship['minshields'], 0);
		$calc_narmor = phpChangeDelta($sship['minarmor'], 0);
		$calc_ncloak = phpChangeDelta($sship['mincloak'], 0);
		$calc_necm = phpChangeDelta($sship['minecm'], 0);
*/
		$techvalue = $calc_nhull+$calc_nengines+$calc_npower+$calc_nfighter+$calc_nsensors+$calc_nbeams+$calc_ntorp_launchers+$calc_nshields+$calc_narmor+$calc_ncloak+$calc_necm;
		$newshipvalue=($techvalue + $ship_price) * $alliancefactor;

		$creditreturn = 0;
		if ($shipinfo['class']!=10){
			$creditreturn = $shipdevice['dev_warpedit']['amount']*$dev_warpedit_price;
			$creditreturn += $shipdevice['dev_genesis']['amount']*$dev_genesis_price;
			$creditreturn += $shipdevice['dev_sectorgenesis']['amount']*$dev_sectorgenesis_price;
			$creditreturn += $shipdevice['dev_emerwarp']['amount']*$dev_emerwarp_price;
			$creditreturn += $shipdevice['dev_escapepod']['amount']* $dev_escapepod_price;
			$creditreturn += $shipdevice['dev_fuelscoop']['amount']* $dev_fuelscoop_price;
			$creditreturn += $shipdevice['dev_nova']['amount']* $dev_nova_price;
			$creditreturn += $shipdevice['dev_minedeflector']['amount']*$dev_minedeflector_price;
		}

		$creditreturn += $shipinfo['torps']*$torpedo_price;
		$creditreturn += $shipinfo['armor_pts']*$armor_price;
		$creditreturn += $shipinfo['ore']*$ore_price;
		$creditreturn += $shipinfo['organics']*$organics_price;
		$creditreturn += $shipinfo['goods']*$goods_price;
		$creditreturn += $shipinfo['energy']*$energy_price;
		$creditreturn += $shipinfo['colonists']*$colonist_price;
		$creditreturn += $shipinfo['fighters']*$fighter_price;
		$creditreturn /= 2;

		if ($keep!="yes" or $shipinfo['class']==10){
			$totalcost = $newshipvalue - ($shipvalue + $creditreturn);
		}else{
			$totalcost = $newshipvalue;
		}

		//Let's do the regular sanity checks first

		if ($playerinfo['turns'] < $sship['turnstobuild'])
		{
			$l_ship2_turns =  str_replace("[turns]", NUMBER($sship['turnstobuild']), $l_ship2_turns);
			$template_object->assign("error_msg", $l_ship2_turns);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/shipyarddie.tpl");
			include ("footer.php");
			die();
		}

		if (!isset($sship))
		{
			$template_object->assign("error_msg", $l_ship2_error);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/shipyarddie.tpl");
			include ("footer.php");
			die();
		}

		if ($sship['type_id'] == $shipinfo['class'])
		{
			$template_object->assign("error_msg", $l_ship2_owned);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/shipyarddie.tpl");
			include ("footer.php");
			die();
		}

		if ($playerinfo['credits'] < $totalcost)
		{
			$template_object->assign("error_msg", $l_ship2_nomoney2);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/shipyarddie.tpl");
			include ("footer.php");
			die();
		}

		//Okay, we're done checking. Now time to create the new ship and assign it as current

		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ships 
									(player_id,
									class,
									name,
									basehull,
									hull,
									engines,
									power,
									fighter,
									sensors,
									beams,
									torp_launchers,
									torps,
									shields,
									armor,
									armor_pts,
									cloak,
									ecm,
									sector_id,
									energy,
									fighters,
									on_planet,
									planet_id,
									cleared_defenses,
									hull_normal,
									engines_normal,
									power_normal,
									fighter_normal,
									sensors_normal,
									beams_normal,
									torp_launchers_normal,
									shields_normal,
									armor_normal,
									cloak_normal,
									ecm_normal
									)
									VALUES(" .
									"$playerinfo[player_id]," .		 // player_id
									"'$stype'," .					   // class
									$db->qstr($shipinfo['name']) . "," .					// name
									"$sship[basehull]," .				// basehull
									"$hull_upgrade," .				// hull
									"$engine_upgrade," .			 // engines
									"$power_upgrade," .			   // power
									"$fighter_upgrade," .			// fighter
									"$sensors_upgrade," .			 // sensors
									"$beams_upgrade," .			   // beams
									"$torp_launchers_upgrade," .	  // torp_launchers
									"0," .							  // torps
									"$shields_upgrade," .			 // shields
									"$armor_upgrade," .			  // armor
									"$start_armor," .				  // armor_pts
									"$cloak_upgrade," .			   // cloak
									"$ecm_upgrade," .				// ecm
									"$shipinfo[sector_id]," .		   // sector_id
									"$start_energy," .				  // energy
									"$start_fighters," .				// fighters
									"'N'," .							// on_planet
									"0," .							  // planet_id
									"'', " .							 // cleared_defenses
									"$hull_upgrade," .				// hull
									"$engine_upgrade," .			 // engines
									"$power_upgrade," .			   // power
									"$fighter_upgrade," .			// fighter
									"$sensors_upgrade," .			 // sensors
									"$beams_upgrade," .			   // beams
									"$torp_launchers_upgrade," .	  // torp_launchers
									"$shields_upgrade," .			 // shields
									"$armor_upgrade," .			  // armor
									"$cloak_upgrade," .			   // cloak
									"$ecm_upgrade" .				// ecm
									")");
		db_op_result($debug_query,__LINE__,__FILE__);

		//get new ship_id
		$res = $db->SelectLimit("SELECT max(ship_id) as ship_id from {$db_prefix}ships WHERE player_id=$playerinfo[player_id]" .
							" AND class='$stype'", 1);
		$ship_id = $res->fields['ship_id'];
		$res->close();

		$filelist = get_dirlist($gameroot."class/devices/");
		for ($c=0; $c<count($filelist); $c++) {
			if($filelist[$c] != "index.html")
			{
				$device_classname =  str_replace(".inc", "", $filelist[$c]); 
				if(!class_exists($device_classname)){
					include ("class/devices/" . $device_classname . ".inc");
				}
				$device_object = new $device_classname();

				$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_devices (player_id, ".
											"ship_id, class, device_name, cargo_class, program, techmodify, ".
											"amount) VALUES(" .
											"'$playerinfo[player_id]'," .
											"'$ship_id'," .
											"'" . $device_classname . "'," .
											"'" . $device_object->classname . "'," .
											"'" . $device_object->cargoclass . "'," .
											"'" . $device_object->program . "'," .
											"'" . $device_object->techmodify . "'," .
											"'0'" .
											")");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}

		$result2 = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities");
		while (!$result2->EOF) 
		{
			$row2 = $result2->fields;
			$amount = 0;
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_holds (".
										"ship_id, class, cargo_name, cargo_class, hold_space,".
										"amount) VALUES(" .
										"'$ship_id'," .
										"'$row2[class]'," .
										"'$row2[classname]'," .
										"'$row2[cargoclass]'," .
										"'$row2[hold_space]'," .
										"'$amount'" .
										")");
			db_op_result($debug_query,__LINE__,__FILE__);
			$result2->Movenext();
		}
		$result2->close();

		//update old ship and add initial storage fee
		if ($keep=="yes")
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET storage_planet_id='$planet_id', planet_id=0, on_planet='N'
										WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET storage_planet_id=0, planet_id=0, on_planet='N' WHERE ship_id=$ship_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			$debug_query = $db->Execute("delete from  {$db_prefix}ships  " . 
										"WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("delete from  {$db_prefix}ship_devices  " . 
										"WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("delete from  {$db_prefix}ship_holds  " . 
										"WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if ($shipinfo['class']==10){
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("delete from  {$db_prefix}ship_devices  " . 
										"WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("delete from  {$db_prefix}ship_holds  " . 
										"WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		//Insert current ship in players table
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET currentship=$ship_id " . 
									"WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($enable_spies)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET ship_id = $ship_id WHERE ship_id = $shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if ($enable_dignitaries)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET ship_id = $ship_id WHERE ship_id = $shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET ship_id = $ship_id WHERE ship_id = $shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		//Now update player credits & turns

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-$sship[turnstobuild], turns_used=turns_used+$sship[turnstobuild], credits=credits-$totalcost WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		gen_score($playerinfo['player_id']);

		$template_object->assign("error_msg", $l_ship2_shipbought);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/shipyarddie.tpl");
		include ("footer.php");
		die();
	}// End switch stuff
}

die();
?>
