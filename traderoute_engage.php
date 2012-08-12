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
include ("globals/spy_detect_planet.inc");
include ("globals/spy_sneak_to_planet.inc");
include ("globals/spy_sneak_to_ship.inc");
include ("globals/calc_dist.inc");
include ("globals/isLoanPending.inc");

get_post_ifset("tr_repeat, engage");

$template_object->enable_gzip = 0;
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

$template_object->assign("title", $title);

// Error in trade route

function traderoute_die($error_msg)
{
	global $l_global_mmenu, $playerinfo, $total_experience, $l_footer_until_update, $l_footer_players_on_1, $l_footer_players_on_2, $l_footer_one_player_on, $sched_ticks, $template_object;
	echo "<p>$error_msg<p>";

	update_player_experience($playerinfo['player_id'], $total_experience);

	echo $l_global_mmenu;
	include ("footer.php");
	die();
}

// calculate trip time and energy scooped

function traderoute_distance($type1, $type2, $start, $dest, $circuit)
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
		$retvalue['triptime'] = 1;
		$retvalue['max_triptime'] = 2;
		return $retvalue;
	}

	$distance=calc_dist($start,$dest);

	$shipspeed = mypw($level_factor, $shipinfo['engines']);
	$triptime = round($distance / $shipspeed);

	if (!$triptime && $destination != $shipinfo['sector_id'])
	{
		$triptime = 1;
	}

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
		if ($shipdevice['dev_fuelscoop']['amount'] == 1 && $type2 == 0 && $dest['port_type'] != 'energy')
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

	$max_triptime = $triptime;
	if ($circuit == 'Y')
	{
		$max_triptime*=2;
		$max_triptime+=2;
	}
	else
	{
		$max_triptime+=1;
	}

	$triptime+=1;
	$retvalue['max_triptime'] = $max_triptime;
	$retvalue['triptime'] = $triptime;
	$retvalue['scooped'] = $retvalue['scooped1'] + $retvalue['scooped2'];

	return $retvalue;
}

$maxholds = NUM_HOLDS($shipinfo['hull']);
$maxenergy = NUM_ENERGY($shipinfo['power']);

$res = $db->Execute("SELECT cargo_name, amount, hold_space FROM {$db_prefix}ship_holds WHERE ship_id=$playerinfo[currentship] ");

$cargo_items = 0;
$hold_space = 0;
while(!$res->EOF)
{
	$cargo_name[$cargo_items] = $res->fields['cargo_name'];
	$cargo_amount[$cargo_items] = $res->fields['amount'];
	$hold_space += ($res->fields['hold_space'] * $res->fields['amount']);
	$cargo_items++;
	$res->MoveNext();
}

$freeholds = NUM_HOLDS($shipinfo['hull']) - $hold_space;

if (!isset($tr_repeat) || $tr_repeat <= 0)
{
	$tr_repeat = 1;
}

if (isset($engage)) //performs trade route
{
//$db->debug=1;
	$result = $db->SelectLimit("SELECT * FROM {$db_prefix}traderoutes WHERE player_id=$playerinfo[player_id] and traderoute_id=$engage", 1);

	if ($result->RecordCount() == 0)
		traderoute_die($l_tdr_engagenonexist);

	$traderoute = $result->fields;

	// ********************************
	// ***** Source Check ************
	// ********************************
	if ($traderoute['source_type'] == 'port')
	{
		//retrieve port info here, we'll need it later anyway
		$result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=$traderoute[source_sector]", 1);
		if (!$result || $result->EOF)
			traderoute_die($l_tdr_invalidspoint);

		$source = $result->fields;

		if ($traderoute['source_sector'] != $shipinfo['sector_id'])
		{
			$l_tdr_inittdr = str_replace("[tdr_source_id]", $traderoute['source_sector'], $l_tdr_inittdr);
			traderoute_die($l_tdr_inittdr);
		}
	}

	if(($traderoute['source_type'] == 'planet' && $traderoute['destination_type'] == 'planet') && ($traderoute['source_planet_id'] == $traderoute['destination_planet_id']))
	{
		traderoute_die($l_tdr_invaliddplanet);
	}

	if($traderoute['source_type'] != 'port'){
		if ($traderoute['source_type'] == 'planet' || $traderoute['source_type'] == 'team_planet')	// get data from planet table
		{
			$result = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$traderoute[source_planet_id]", 1);
			if (!$result || $result->EOF)
				traderoute_die($l_tdr_invalidsrc);

			$source = $result->fields;

			if ($source['sector_id'] != $shipinfo['sector_id'])
			{
				$l_tdr_inittdrsector = str_replace("[tdr_source_sector_id]", $source['sector_name'], $l_tdr_inittdrsector);
				traderoute_die($l_tdr_inittdrsector);
			}

			if ($traderoute['source_type'] == 'planet')
			{
				if ($source['owner'] != $playerinfo['player_id'])
				{
					$l_tdr_notyourplanet = str_replace("[tdr_source_name]", $source['name'], $l_tdr_notyourplanet);
					$l_tdr_notyourplanet = str_replace("[tdr_source_sector_id]", $source['sector_name'], $l_tdr_notyourplanet);
					traderoute_die($l_tdr_notyourplanet);
				}
			}
			elseif ($traderoute['source_type'] == 'team_planet')	 // check to make sure player and planet are in the same team.
			{
				if ($source['team'] != $playerinfo[team])
				{
					$l_tdr_notyourplanet = str_replace("[tdr_source_name]", $source['name'], $l_tdr_notyourplanet);
					$l_tdr_notyourplanet = str_replace("[tdr_source_sector_id]", $source['sector_name'], $l_tdr_notyourplanet);
					$not_team_planet = "$source[name] in $source[sector_id] not a Copporate Planet";
					traderoute_die($not_team_planet);
				}
			}

			//store starting port info, we'll need it later
			$result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=$source[sector_id]", 1);
			if (!$result || $result->EOF)
				traderoute_die($l_tdr_invalidssector);

			$sourceport = $result->fields;
		}
	}

	// ********************************
	// ***** Destination Check ********
	// ********************************
	if ($traderoute['destination_type'] == 'port')
	{
		$result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=$traderoute[destination_sector]", 1);
		if (!$result || $result->EOF)
			traderoute_die($l_tdr_invaliddport);

		$dest = $result->fields;
	}

	if ($traderoute['destination_type'] != 'port'){
		if (($traderoute['destination_type'] == 'planet') || ($traderoute['destination_type'] == 'team_planet'))	// get data from planet table
		{
			$result = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$traderoute[destination_planet_id]", 1);
			if (!$result || $result->EOF)
				traderoute_die($l_tdr_invaliddplanet);

			$dest = $result->fields;
			
			if ($traderoute['destination_type'] == 'planet')
			{
				if ($dest['owner'] != $playerinfo['player_id'])
				{
					$l_tdr_notyourplanet = str_replace("[tdr_source_name]", $dest['name'], $l_tdr_notyourplanet);
					$l_tdr_notyourplanet = str_replace("[tdr_source_sector_id]", $dest['sector_name'], $l_tdr_notyourplanet);
					traderoute_die($l_tdr_notyourplanet);
				}
			}
			elseif ($traderoute['destination_type'] == 'team_planet')	 // check to make sure player and planet are in the same team.
			{
				if ($dest['team'] != $playerinfo['team'])
				{
					$l_tdr_notyourplanet = str_replace("[tdr_source_name]", $dest['name'], $l_tdr_notyourplanet);
					$l_tdr_notyourplanet = str_replace("[tdr_source_sector_id]", $dest['sector_name'], $l_tdr_notyourplanet);
					$not_team_planet = "$dest[name] in $dest[sector_id] not a Copporate Planet";
					traderoute_die($not_team_planet);
				}
			}

			$result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=$dest[sector_id]", 1);
			if (!$result || $result->EOF)
				traderoute_die($l_tdr_invaliddsector);

			$destport = $result->fields;
		}
	}

	if (!isset($sourceport))
		$sourceport=$source;
	if (!isset($destport))
		$destport=$dest;

	// ***************************************************
	// ***** Warp or RealSpace and generate distance *****
	// ***************************************************
	if ($traderoute['move_type'] == 'W' && $source['sector_id'] != $dest['sector_id'])
	{
		$query = $db->SelectLimit("SELECT link_id FROM {$db_prefix}links WHERE link_start=$source[sector_id] AND link_dest=$dest[sector_id]", 1);
		if ($query->EOF)
		{
			$l_tdr_nowlink1 = str_replace("[tdr_src_sector_id]", $source['sector_name'], $l_tdr_nowlink1);
			$l_tdr_nowlink1 = str_replace("[tdr_dest_sector_id]", $dest['sector_name'], $l_tdr_nowlink1);
			traderoute_die($l_tdr_nowlink1);
		}
		if ($traderoute['roundtrip'] == 'Y')
		{
			$query = $db->SelectLimit("SELECT link_id FROM {$db_prefix}links WHERE link_start=$dest[sector_id] AND link_dest=$source[sector_id]", 1);
			if ($query->EOF)
			{
				$l_tdr_nowlink2 = str_replace("[tdr_src_sector_id]", $source['sector_name'], $l_tdr_nowlink2);
				$l_tdr_nowlink2 = str_replace("[tdr_dest_sector_id]", $dest['sector_name'], $l_tdr_nowlink2);
				traderoute_die($l_tdr_nowlink2);
			}
			$dist['triptime'] = 2;
		}
		else
			$dist['triptime'] = 1;

		$dist['max_triptime'] = $dist['triptime'] * 2;
		$dist['scooped'] = 0;
		$dist['scooped1'] = 0;
		$dist['scooped2'] = 0;
	}
	else
		$dist = traderoute_distance('P', 'P', $sourceport['sector_id'], $destport['sector_id'], $traderoute['roundtrip']);

	if ($sourceport['sector_id'] == $destport['sector_id'])
	{
		$dist['triptime'] = 1;
		$dist['max_triptime'] = 2;
	}

	// ********************************************
	// ***** Check if player has enough turns *****
	// ********************************************
	if ($playerinfo['turns'] < $dist['max_triptime'])
	{
		$l_tdr_moreturnsneeded = str_replace("[tdr_dist_triptime]", $dist['triptime'], $l_tdr_moreturnsneeded);
		$l_tdr_moreturnsneeded = str_replace("[tdr_playerinfo_turns]", $playerinfo['turns'], $l_tdr_moreturnsneeded);
		traderoute_die($l_tdr_moreturnsneeded);
	}

	// ********************************
	// ***** Sector Defense Check *****
	// ********************************
	$hostile = 0;

	$result99 = $db->SelectLimit("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id = $source[sector_id] AND player_id <> $playerinfo[player_id]", 1);
	if (!$result99->EOF)
	{
		 $fighters_owner = $result99->fields;
		 $nsresult = $db->SelectLimit("SELECT team from {$db_prefix}players where player_id=$fighters_owner[player_id]", 1);
		 $nsfighters = $nsresult->fields;
		 if ($nsfighters['team'] != $playerinfo['team'] || $playerinfo['team']==0)
			$hostile = 1;
	}

	$result98 = $db->SelectLimit("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id = $dest[sector_id] AND player_id <> $playerinfo[player_id]", 1);
	if (!$result98->EOF)
	{
		 $fighters_owner = $result98->fields;
		 $nsresult = $db->SelectLimit("SELECT team from {$db_prefix}players where player_id=$fighters_owner[player_id]", 1);
		 $nsfighters = $nsresult->fields;
		 if ($nsfighters['team'] != $playerinfo['team'] || $playerinfo['team']==0)
			$hostile = 1;
	}

	if ($hostile > 0)
		 traderoute_die($l_tdr_tdrhostdef);

	// ***************************************
	// ***** Upgrades Port Nothing to do *****
	// ***************************************
	if ($traderoute['source_type'] == 'port' && $source['port_type'] == 'upgrades' && $playerinfo['trade_colonists'] == 'N' && $playerinfo['trade_fighters'] == 'N' && $playerinfo['trade_torps'] == 'N')
		traderoute_die($l_tdr_globalsetbuynothing);

	$average_stats = (($shipinfo['hull_normal'] + $shipinfo['cloak_normal'] + $shipinfo['sensors_normal'] + $shipinfo['power_normal'] + $shipinfo['engines_normal'] + $shipinfo['fighter_normal'] + $shipinfo['armor_normal'] + $shipinfo['shields_normal'] + $shipinfo['beams_normal'] + $shipinfo['torp_launchers_normal'] + $shipinfo['ecm_normal'] ) / 11 );
	// *********************************************
	// ***** Check if zone allows trading	SRC *****
	// *********************************************
	if ($traderoute['source_type'] == 'port')
	{
		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}zones,{$db_prefix}universe WHERE {$db_prefix}universe.sector_id=$traderoute[source_sector] AND {$db_prefix}zones.zone_id={$db_prefix}universe.zone_id", 1);
		$query97 = $res->fields;
		if ($query97['allow_trade'] == 'N')
			traderoute_die($l_tdr_nosrcporttrade);
		elseif ($query97['allow_trade'] == 'planet')
		{
			if ($query97['team_zone'] == 'N')
			{
				$res = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$query97[owner]", 1);
				$ownerinfo = $res->fields;

				if ($playerinfo['player_id'] != $query97['owner'] && $playerinfo['team'] == 0 || $playerinfo['team'] != $ownerinfo['team'])
					traderoute_die($l_tdr_tradesrcportoutsider);
			}
			else
			{
				if ($playerinfo['team'] != $query97['owner'])
					traderoute_die($l_tdr_tradesrcportoutsider);
			}
		}
		if ($source['port_type'] != 'spacedock' && $source['port_type'] != 'casino' && $source['port_type'] != 'devices' && $source['port_type'] != 'upgrade')
		{
			if ($query97['zone_id'] == 2 && $query97['max_hull'] < $average_stats && $playerinfo['player_id'] > 3)
			{
				$l_tdr_shiptoolarge = str_replace("[port_type]", ucfirst($source['port_type']), $l_tdr_shiptoolarge);
				$l_tdr_shiptoolarge = str_replace("[sector_name]", $query97['sector_name'], $l_tdr_shiptoolarge);
				traderoute_die($l_tdr_shiptoolarge);
			}
		}
	}

	// **********************************************
	// ***** Check if zone allows trading	DEST *****
	// **********************************************
	if ($traderoute['destination_type'] == 'port')
	{
		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}zones,{$db_prefix}universe WHERE {$db_prefix}universe.sector_id=$traderoute[destination_sector] AND {$db_prefix}zones.zone_id={$db_prefix}universe.zone_id", 1);
		$query97 = $res->fields;
		if ($query97['allow_trade'] == 'N')
			traderoute_die($l_tdr_nodestporttrade);
		elseif ($query97['allow_trade'] == 'planet')
		{
			if ($query97[team_zone] == 'N')
			{
				$res = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$query97[owner]", 1);
				$ownerinfo = $res->fields;

				if ($playerinfo['player_id'] != $query97['owner'] && $playerinfo['team'] == 0 || $playerinfo['team'] != $ownerinfo['team'])
					traderoute_die($l_tdr_tradedestportoutsider);
			}
			else
			{
				if ($playerinfo['team'] != $query97['owner'])
					traderoute_die($l_tdr_tradedestportoutsider);
			}
		}
		if ($dest['port_type'] != 'spacedock' && $dest['port_type'] != 'casino' && $dest['port_type'] != 'devices' && $dest['port_type'] != 'upgrade')
		{
			if ($query97['zone_id'] == 2 && $query97['max_hull'] < $average_stats && $playerinfo['player_id'] > 3)
			{
				$l_tdr_shiptoolarge = str_replace("[port_type]", ucfirst($dest['port_type']), $l_tdr_shiptoolarge);
				$l_tdr_shiptoolarge = str_replace("[sector_name]", $query97['sector_name'], $l_tdr_shiptoolarge);
				traderoute_die($l_tdr_shiptoolarge);
			}
		}
	}

	// **********************************************
	// ***** Check if player has a loan pending *****
	// **********************************************

	if ($traderoute['source_type'] == 'port' && $source['port_type'] == 'upgrades' && isLoanPending($playerinfo['player_id']))
	{
		global $l_port_loannotrade, $l_igb_term;
		traderoute_die("$l_port_loannotrade<p><A HREF=igb.php>$l_igb_term</a><p>");
	}

	// *******************************************
	// ***** Check if player has a fedbounty *****
	// *******************************************

	if ($traderoute['source_type'] == 'port' && $source['port_type'] == 'upgrades')
	{
		global $l_port_bounty, $l_port_bounty2, $l_by_placebounty;
		$res2 = $db->Execute("SELECT SUM(amount) as total_bounty FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1) AND bounty_on = $playerinfo[player_id]");
		if ($res2)
		{
			$bty = $res2->fields;
			if ($bty['total_bounty'] > 0)
			{
				$l_port_bounty2 = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_bounty2);
				traderoute_die("$l_port_bounty $l_port_bounty2 <BR> <A HREF=\"bounty.php\">$l_by_placebounty</A><BR><BR>");
			}
		}
	}

	//-------- If spacedock kill trade ------
	if ($source['port_type'] == 'spacedock' || $source['port_type'] == 'casino' || $source['port_type'] == 'devices')
	{
		traderoute_die($l_tdr_invalidspoint);
	}
	if ($dest['port_type'] == 'spacedock' || $dest['port_type'] == 'casino' || $source['port_type'] == 'devices')
	{
		traderoute_die($l_tdr_invaliddport);
	}

	if($traderoute['roundtrip'] != "Y")
		$tr_repeat = 1;

	if($tr_repeat > 200)
		$tr_repeat = 200;

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//--------- We're done with checks!	All that's left is to make it happen --------
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------

	if ($traderoute['source_type'] == 'port' && $traderoute['destination_type'] == 'port')
		include("traderoute_engage/port_to_port.inc");
	else
	if ($traderoute['source_type'] == 'port' && $traderoute['destination_type'] != 'port' && $traderoute['source_commodity'] == 'upgrades')
		include("traderoute_engage/upgrade_to_planet.inc");
	else
	if ($traderoute['source_type'] != 'port' && $traderoute['destination_type'] == 'port' && $traderoute['destination_commodity'] == 'upgrades')
		include("traderoute_engage/planet_to_upgrade.inc");
	else
	if ($traderoute['source_type'] == 'port' && $traderoute['destination_type'] != 'port')
		include("traderoute_engage/port_to_planet.inc");
	else
	if ($traderoute['source_type'] != 'port' && $traderoute['destination_type'] == 'port')
		include("traderoute_engage/planet_to_port.inc");
	else
	if ($traderoute['source_type'] != 'port' && $traderoute['destination_type'] != 'port')
		include("traderoute_engage/planet_to_planet.inc");

	update_player_experience($playerinfo['player_id'], $total_experience);
}

include ("footer.php");

?>
