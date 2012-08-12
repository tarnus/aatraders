<?php
get_post_ifset("transfer_special, tpspecial, allspecial, transfer_ore, transfer_organics, transfer_goods, transfer_energy, transfer_colonists, transfer_fighters, transfer_torps, transfer_credits, tpore, tporganics, tpgoods, tpenergy, tpcolonists, tpfighters, tptorps, tpcredits, allore, allorganics, allgoods, allenergy, allcolonists, allfighters, alltorps, allcredits, transfer_spies, transfer_dignitary, tpspies, tpdigs, allspies, alldigs");
include ("globals/gen_score.inc");

if($playerinfo['player_id'] != $planetinfo['owner'])
{
	$returnscore = gen_score($playerinfo['player_id']);
	$score = $returnscore[0];
	$maxteamcash_ship = $score * $score * ($team_cash_percentage / 100);

	$returnscore = gen_score($planetinfo['owner']);
	$score = $returnscore[0];
	$maxteamcash_planet = $score * $score * ($team_cash_percentage / 100);
	$max_team_cash_transfer = MIN($maxteamcash_ship, $maxteamcash_planet);
	$is_teamcash_able = 1;
}
else
{
	$max_team_cash_transfer = 0;
	$is_teamcash_able = 0;
}

if (($playerinfo['team_cash_countdown'] == 0 && $max_team_cash_transfer != 0) || $max_team_cash_transfer == 0)
{
	if($max_team_cash_transfer > 0)
	{
		if($allcredits == -1)
		{
			$allcredits = 0;
			if ($tpcredits==-1)
			{
				$transfer_credits = MIN($playerinfo['credits'], $max_team_cash_transfer);
			}
			else
			{
				$transfer_credits = MIN($planetinfo['credits'], $max_team_cash_transfer);
			}
		}
	}
}
else
{
	$allcredits = 0;
	$tpcredits = 0;
	$transfer_credits = 0;
}

function transfer_to_planet_spy($player_id, $planet_id, $spy_cloak, $how_many = 1)
{
	global $db;
	global $db_prefix;
	global $max_spies_per_planet;
	global $shipinfo;
	$res = $db->Execute("SELECT COUNT(spy_id) AS n FROM {$db_prefix}spies WHERE owner_id = $player_id AND ship_id = '0' AND planet_id = $planet_id");
	$on_planet = $res->fields['n'];
	$res->close();
	$can_transfer = min(($max_spies_per_planet - $on_planet), $how_many);
	if ($can_transfer < 0)
	{
		$can_transfer = 0;
	}

	$res = $db->Execute("SELECT spy_id FROM {$db_prefix}spies WHERE owner_id = $player_id AND ship_id = $shipinfo[ship_id] LIMIT $can_transfer");
	$how_many2 = $res->RecordCount();
  
	if (!$how_many2)
	{
		return 0;
	}
	else  
	{
		while (!$res->EOF)
		{
			$spy = $res->fields['spy_id'];
			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET planet_id = '$planet_id', ship_id = '0', active = 'N', job_id = '0', spy_percent = '0.0', spy_cloak=$spy_cloak WHERE spy_id = $spy");
			db_op_result($debug_query,__LINE__,__FILE__);

			$res->MoveNext();
		}
		$res->close();
		return $how_many2;
	}
}

function transfer_to_planet_dig($player_id, $planet_id, $how_many = 1)
{
  global $db;
  global $db_prefix;
  global $max_dignitary_per_planet;
  global $shipinfo;
  $res = $db->Execute("SELECT COUNT(dig_id) AS n FROM {$db_prefix}dignitary WHERE owner_id = $player_id AND ship_id = '0' AND planet_id = $planet_id");
  $on_planet = $res->fields['n'];
	$res->close();
  $can_transfer = min(($max_dignitary_per_planet - $on_planet), $how_many);
  if($can_transfer < 0)
	$can_transfer = 0;
  $res = $db->Execute("SELECT dig_id FROM {$db_prefix}dignitary WHERE owner_id = $player_id AND ship_id = $shipinfo[ship_id] LIMIT $can_transfer");
  $how_many2 = $res->RecordCount();
  
  if(!$how_many2)
	return 0;
  else  
  {
	while(!$res->EOF)
	{
	  $spy = $res->fields['dig_id'];
	  $debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET planet_id = '$planet_id', ship_id = '0', active = 'Y', job_id = '0', percent = '0.0', embezzler = 0 WHERE dig_id = $spy");
	  db_op_result($debug_query,__LINE__,__FILE__);

	  $res->MoveNext();
	}
	$res->close();
	return $how_many2;
  }   
}

function transfer_to_ship_spy($player_id, $planet_id, $spy_cloak, $how_many = 1)
{
	global $db;
	global $db_prefix;
	global $shipinfo;

	$res = $db->Execute("SELECT spy_id FROM {$db_prefix}spies WHERE owner_id = $player_id AND planet_id = $planet_id LIMIT $how_many");// AND active = 'N'
	$how_many2 = $res->RecordCount();
  
	if (!$how_many2)
	{
		return 0;
	}
	else  
	{
		while (!$res->EOF)
		{
			$spy = $res->fields['spy_id'];
			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET planet_id = 0, ship_id = $shipinfo[ship_id], active = 'N', job_id = '0', spy_percent = '0.0', spy_cloak=$spy_cloak WHERE spy_id = $spy");
			db_op_result($debug_query,__LINE__,__FILE__);

			$res->MoveNext();
		}
	$res->close();
	return $how_many2;
	}   
}

function transfer_to_ship_dig($player_id, $planet_id, $how_many = 1)
{
  global $db;
  global $db_prefix;
  global $shipinfo;

  $res=$db->Execute("SELECT dig_id FROM {$db_prefix}dignitary WHERE owner_id = $player_id AND planet_id = $planet_id LIMIT $how_many");// AND active = 'N'
  $how_many2 = $res->RecordCount();
  
  if(!$how_many2)
	return 0;
  else  
  {
	while(!$res->EOF)
	{
	  $spy = $res->fields['dig_id'];
	  $debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET planet_id = 0, ship_id = $shipinfo[ship_id], active = 'N', job_id = '0', percent = '0.0', embezzler = 0 WHERE dig_id = $spy");
	  db_op_result($debug_query,__LINE__,__FILE__);

	  $res->MoveNext();
	}
	$res->close();
	return $how_many2;
  }   
}


if ($planetinfo['sector_id'] <> $shipinfo['sector_id'])
{
	$template_object->assign("error_msg", $l_planet2_sector);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/planet_transferdie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_planet2_noturn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/planet_transferdie.tpl");
	include ("footer.php");
	die();
}

$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ship_holds WHERE cargo_name!='energy' and ship_id=$playerinfo[currentship]");
db_op_result($debug_query,__LINE__,__FILE__);

$ship_item_count = 0;
$ship_holds_used = 0;

while(!$debug_query->EOF){
	$shipinfo[$debug_query->fields['cargo_name']] = $debug_query->fields['amount'];
	if($planetinfo['special_name'] == $debug_query->fields['cargo_name'])
	{
		$shipspecialname = $debug_query->fields['cargo_name'];
		$shipspecial = $debug_query->fields['amount'];
		$special_holds = $debug_query->fields['hold_space'];
	}

	$ship_holds_used += ($debug_query->fields['hold_space'] * $debug_query->fields['amount']);

	$debug_query->MoveNext();
}
$debug_query->close();

$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
$free_power = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];
$free_fighter = NUM_FIGHTERS($shipinfo['fighter']) - $shipinfo['fighters'];
$free_torpedo = NUM_TORPEDOES($shipinfo['torp_launchers']) - $shipinfo['torps'];

$total_holds = NUM_HOLDS($shipinfo['hull']);
$ship_fighters_max = NUM_FIGHTERS($shipinfo['fighter']);
$torps_max = NUM_TORPEDOES($shipinfo['torp_launchers']);
$energy_max = NUM_ENERGY($shipinfo['power']);

$planetinfo['special_amount'] = floor($planetinfo['special_amount']);

// first setup the tp flags
if ($tpspecial != -1)
{
	$tpspecial = 1;
}
if ($tpore != -1)
{
	$tpore = 1;
}
if ($tporganics != -1)
{
	$tporganics  = 1;
}
if ($tpgoods != -1)
{
	$tpgoods = 1;
}
if ($tpenergy != -1)
{
	$tpenergy = 1;
}
if ($tpcolonists != -1)
{
	$tpcolonists = 1;
}
if ($tpcredits != -1)
{
	$tpcredits = 1;
}
if ($tptorps != -1)
{
	$tptorps = 1;
}
if ($tpfighters != -1)
{
	$tpfighters = 1;
}
if ($tpspies != -1)
{
	$tpspies = 1;
}
if ($tpdigs != -1)
{
	$tpdigs = 1;
}

$transfer_special = abs($transfer_special * 1); 
$transfer_ore =	abs($transfer_ore * 1); 
$transfer_organics = abs($transfer_organics * 1);
$transfer_goods = abs($transfer_goods * 1); 
$transfer_energy = abs($transfer_energy * 1);
$transfer_colonists = abs($transfer_colonists * 1); 
$transfer_credits =	abs($transfer_credits * 1); 
$transfer_torps = abs($transfer_torps * 1);
$transfer_fighters = abs($transfer_fighters * 1); 
$transfer_spies = abs($transfer_spies * 1); 
$transfer_dignitary = abs($transfer_dignitary * 1);

if ($allspecial == -1)
{
	if ($tpspecial == -1)
	{
		$transfer_special = $shipspecial;
		$ship_holds_used -= ($transfer_special * $special_holds);
	}
	else
	{
		if(($planetinfo['special_amount'] * $special_holds) > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_special = floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used) / $special_holds);
			$ship_holds_used += ($transfer_special * $special_holds);
		}
		else
		{
			$transfer_special = $planetinfo['special_amount'];
			$ship_holds_used += ($transfer_special * $special_holds);
		}
	}
}

if ($allore==-1)
{
	if ($tpore == -1)
	{
		$transfer_ore = $shipinfo['ore'];
		$ship_holds_used -= $transfer_ore;
	}
	else
	{
		if($planetinfo['ore'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_ore = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_ore;
		}
		else
		{
			$transfer_ore = $planetinfo['ore'];
			$ship_holds_used += $transfer_ore;
		}
	}
}

if ($allorganics==-1)
{
	if ($tporganics==-1)
	{
		$transfer_organics = $shipinfo['organics'];
		$ship_holds_used -= $transfer_organics;
	}
	else
	{
		if($planetinfo['organics'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_organics = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_organics;
		}
		else
		{
			$transfer_organics = $planetinfo['organics'];
			$ship_holds_used += $transfer_organics;
		}
	}
}

if ($allgoods==-1)
{
	if ($tpgoods==-1)
	{
		$transfer_goods = $shipinfo['goods'];
		$ship_holds_used -= $transfer_goods;
	}
	else
	{
		if($planetinfo['goods'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_goods = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_goods;
		}
		else
		{
			$transfer_goods = $planetinfo['goods'];
			$ship_holds_used += $transfer_goods;
		}
	}
}

$averagetechlvl = ($planetinfo['fighter'] + $planetinfo['sensors'] + $planetinfo['beams'] + $planetinfo['torp_launchers'] + $planetinfo['shields'] + $planetinfo['jammer'] + $planetinfo['cloak']) / 7;
$colonists_max = $colonist_limit + floor($colonist_tech_add * $averagetechlvl);
$free_colonists = $colonists_max - $planetinfo['colonists'];

if ($allcolonists==-1)
{
	if ($tpcolonists==-1)
	{
		if($free_colonists > $shipinfo['colonists'])
		{
			$transfer_colonists = $shipinfo['colonists'];
			$ship_holds_used -= $transfer_colonists;
		}
		else
		{
			$transfer_colonists = $free_colonists;
			$ship_holds_used -= $transfer_colonists;
		}
	}
	else
	{
		if($planetinfo['colonists'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_colonists = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_colonists;
		}
		else
		{
			$transfer_colonists = $planetinfo['colonists'];
			$ship_holds_used += $transfer_colonists;
		}
	}
}

if ($allenergy==-1)
{
	if ($tpenergy==-1)
	{
		$transfer_energy = $shipinfo['energy'];
	}
	else
	{
		if($planetinfo['energy'] > (NUM_ENERGY($shipinfo['power']) - $shipinfo['energy']))
		{
			$transfer_energy = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];
		}
		else
		{
			$transfer_energy = $planetinfo['energy'];
		}
	}
}

if ($allcredits==-1)
{
	if ($tpcredits==-1)
	{
		$transfer_credits = $playerinfo['credits'];
	}
	else
	{
		$transfer_credits = $planetinfo['credits'];
	}
}

if ($alltorps==-1)
{
	if ($tptorps==-1)
	{
		$transfer_torps = $shipinfo['torps'];
	}
	else
	{
		if($free_torpedo <=  $planetinfo['torps'])
		{
			$transfer_torps = $free_torpedo;
		}
		else
		{
			$transfer_torps = $planetinfo['torps'];
		}
	}
}

if ($allfighters==-1)
{
	if ($tpfighters==-1)
	{
		$transfer_fighters = $shipinfo['fighters'];
	}
	else
	{
		if($free_fighter <=  $planetinfo['fighters'])
		{
			$transfer_fighters = $free_fighter;
		}
		else
		{
			$transfer_fighters = $planetinfo['fighters'];
		}
	}
}

if ($allspies==-1)
{
	if ($tpspies==-1)
	{
		$res = $db->execute("SELECT * FROM {$db_prefix}spies WHERE ship_id = '$shipinfo[ship_id]' AND owner_id = '$playerinfo[player_id]' ");
		$transfer_spies = $res->RecordCount();
		$res->close();
	}
	else
	{
		$res = $db->execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '$planet_id' AND owner_id = '$playerinfo[player_id]' ");
		$transfer_spies = $res->RecordCount();
		$res->close();
	}
}

if ($alldigs==-1)
{
	if ($tpdigs==-1)
	{
		$res = $db->execute("SELECT * FROM {$db_prefix}dignitary WHERE ship_id = '$shipinfo[ship_id]' AND owner_id = '$playerinfo[player_id]' ");
		$transfer_dignitary = $res->RecordCount();
		$res->close();
	}
	else
	{
		$res = $db->execute("SELECT * FROM {$db_prefix}dignitary WHERE planet_id = '$planet_id' AND owner_id = '$playerinfo[player_id]' ");
		$transfer_dignitary = $res->RecordCount();
		$res->close();
	}
}

$spytotal = 0;
if ($enable_spies)
{
	if ($transfer_spies and ($playerinfo['player_id'] == $planetinfo['owner']))
	{
		if($planetinfo['cloak'] < $shipinfo['cloak'])
			$spy_cloak = $shipinfo['cloak'];
		else
			$spy_cloak = $planetinfo['cloak'];
			if ($tpspies<0)
			$spytotal = transfer_to_planet_spy($playerinfo['player_id'], $planetinfo['planet_id'], $spy_cloak, $transfer_spies);
		else
			$spytotal = transfer_to_ship_spy($playerinfo['player_id'], $planetinfo['planet_id'], $shipinfo['cloak'], $transfer_spies);
	}
}

$digtotal = 0;
if ($enable_dignitaries)
{
	if ($transfer_dignitary and ($playerinfo['player_id'] == $planetinfo['owner']))
	{
		if ($tpdigs<0)
			$digtotal = transfer_to_planet_dig($playerinfo['player_id'], $planetinfo['planet_id'], $transfer_dignitary);
		else
			$digtotal = transfer_to_ship_dig($playerinfo['player_id'], $planetinfo['planet_id'], $transfer_dignitary);
	}
}

// move commodities from ship to planet
if ($allspecial != -1)
{
	if (($tpspecial == -1) && ($transfer_special > $shipspecial))
	{
		$ship_holds_used -= ($shipspecial * $special_holds);
		$transfer_special = $shipspecial;
	}else{
		if($tpspecial == -1)
		{
			$ship_holds_used -= ($transfer_special * $special_holds);
		}
	}
}

if ($allore != -1)
{
	if (($tpore == -1) && ($transfer_ore > $shipinfo['ore']))
	{
		$ship_holds_used -= $shipinfo['ore'];
		$transfer_ore = $shipinfo['ore'];
	}else{
		if($tpore == -1)
		{
			$ship_holds_used -= $transfer_ore;
		}
	}
}

if ($allorganics != -1)
{
	if (($tporganics == -1) && ($transfer_organics > $shipinfo['organics']))
	{
		$ship_holds_used -= $shipinfo['organics'];
		$transfer_organics = $shipinfo['organics'];
	}else{
		if($tporganics == -1)
		{
			$ship_holds_used -= $transfer_organics;
		}
	}
}

if ($allgoods != -1)
{
	if (($tpgoods == -1) && ($transfer_goods > $shipinfo['goods']))
	{
		$ship_holds_used -= $shipinfo['goods'];
		$transfer_goods = $shipinfo['goods'];
	}else{
		if($tpgoods == -1)
		{
			$ship_holds_used -= $transfer_goods;
		}
	}
}

if ($allcolonists != -1)
{
	if (($tpcolonists == -1) && ($transfer_colonists > $shipinfo['colonists']))
	{
		if($free_colonists > $shipinfo['colonists'])
		{
			$ship_holds_used -= $shipinfo['colonists'];
			$transfer_colonists = $shipinfo['colonists'];
		}
		else
		{
			$transfer_colonists = $free_colonists;
			$ship_holds_used -= $transfer_colonists;
		}
	}else{
		if($tpcolonists == -1)
		{
			if($free_colonists > $transfer_colonists)
			{
				$ship_holds_used -= $transfer_colonists;
			}
			else
			{
				$transfer_colonists = $free_colonists;
				$ship_holds_used -= $transfer_colonists;
			}
		}
	}
}

if ($alltorps != -1)
{
	if (($tptorps == -1) && ($transfer_torps > $shipinfo['torps']))
	{
		$transfer_torps = $shipinfo['torps'];
	}
}

if ($allfighters != -1)
{
	if (($tpfighters == -1) && ($transfer_fighters > $shipinfo['fighters']))
	{
		$transfer_fighters = $shipinfo['fighters'];
	}
}

if ($allenergy != -1)
{
	if (($tpenergy == -1) && ($transfer_energy > $shipinfo['energy']))
	{
		$transfer_energy = $shipinfo['energy'];
	}
}

if ($allcredits != -1)
{
	if (($tpcredits == -1) && ($transfer_credits > $playerinfo['credits']))
	{
		$transfer_credits = $playerinfo['credits'];
	}
}

if (($tpcredits == -1) && $planetinfo['base'] == 'N' && ($transfer_credits + $planetinfo['credits'] > $max_credits_without_base))
{
	$transfer_credits = MAX($max_credits_without_base - $planetinfo['credits'],0);
}

// move commodities from planet to ship
if ($allspecial != -1)
{
	if (($tpspecial == 1) && ($transfer_special > $planetinfo['special_amount']))
	{
		if(($planetinfo['special_amount'] * $special_holds) > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_special = floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used) / $special_holds);
			$ship_holds_used += ($transfer_special * $special_holds);
		}
		else
		{
			$transfer_special = $planetinfo['special_amount'];
			$ship_holds_used += ($transfer_special * $special_holds);
		}
	}
	else
	{
		if($tpspecial == 1)
		{
			if(($transfer_special * $special_holds) > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
			{
				$transfer_special = floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used) / $special_holds);
				$ship_holds_used += ($transfer_special * $special_holds);
			}
			else
			{
				$ship_holds_used += ($transfer_special * $special_holds);
			}
		}
	}
}

if ($allore != -1)
{
	if (($tpore == 1) && ($transfer_ore > $planetinfo['ore']))
	{
		if($planetinfo['ore'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_ore = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_ore;
		}
		else
		{
			$transfer_ore = $planetinfo['ore'];
			$ship_holds_used += $transfer_ore;
		}
	}
	else
	{
		if($tpore == 1)
		{
			if($transfer_ore > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
			{
				$transfer_ore = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
				$ship_holds_used += $transfer_ore;
			}
			else
			{
				$ship_holds_used += $transfer_ore;
			}
		}
	}
}

if ($allorganics != -1)
{
	if (($tporganics == 1) && ($transfer_organics > $planetinfo['organics']))
	{
		if($planetinfo['organics'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_organics = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_organics;
		}
		else
		{
			$transfer_organics = $planetinfo['organics'];
			$ship_holds_used += $transfer_organics;
		}
	}
	else
	{
		if($tporganics == 1)
		{
			if($transfer_organics > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
			{
				$transfer_organics = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
				$ship_holds_used += $transfer_organics;
			}
			else
			{
				$ship_holds_used += $transfer_organics;
			}
		}
	}
}

if ($allgoods != -1)
{
	if (($tpgoods == 1) && ($transfer_goods > $planetinfo['goods']))
	{
		if($planetinfo['goods'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_goods = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_goods;
		}
		else
		{
			$transfer_goods = $planetinfo['goods'];
			$ship_holds_used += $transfer_goods;
		}
	}
	else
	{
		if($tpgoods == 1)
		{
			if($transfer_goods > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
			{
				$transfer_goods = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
				$ship_holds_used += $transfer_goods;
			}
			else
			{
				$ship_holds_used += $transfer_goods;
			}
		}
	}
}

if ($allcolonists != -1)
{
	if (($tpcolonists == 1) && ($transfer_colonists > $planetinfo['colonists']))
	{
		if($planetinfo['colonists'] > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
		{
			$transfer_colonists = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
			$ship_holds_used += $transfer_colonists;
		}
		else
		{
			$transfer_colonists = $planetinfo['colonists'];
			$ship_holds_used += $transfer_colonists;
		}
	}
	else
	{
		if($tpcolonists == 1)
		{
			if($transfer_colonists > (NUM_HOLDS($shipinfo['hull']) - $ship_holds_used))
			{
				$transfer_colonists = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
				$ship_holds_used += $transfer_colonists;
			}
			else
			{
				$ship_holds_used += $transfer_colonists;
			}
		}
	}
}

if ($allenergy != -1)
{
	if (($tpenergy == 1) && ($transfer_energy > $planetinfo['energy']))
	{
		if($planetinfo['energy'] > (NUM_ENERGY($shipinfo['power']) - $shipinfo['energy']))
		{
			$transfer_energy = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];
		}
		else
		{
			$transfer_energy = $planetinfo['energy'];
		}
	}
	else
	{
		if($tpenergy == 1)
		{
			if($transfer_energy > (NUM_ENERGY($shipinfo['power']) - $shipinfo['energy']))
			{
				$transfer_energy = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];
			}
		}
	}
}

if ($allcredits != -1)
{
	if (($tpcredits == 1) && ($transfer_credits > $planetinfo['credits']))
	{
		$transfer_credits = $planetinfo['credits'];
	}
}

if ($alltorps != -1)
{
	if (($tptorps == 1) && ($transfer_torps > $planetinfo['torps']))
	{
		if($free_torpedo <=  $planetinfo['torps'])
		{
			$transfer_torps = $free_torpedo;
		}
		else
		{
			$transfer_torps = $planetinfo['torps'];
		}
	}
	else
	{
		if ($tptorps == 1)
		{
			if($transfer_torps > $free_torpedo)
			{
				$transfer_torps = $free_torpedo;
			}
		}
	}
}

if ($allfighters != -1)
{
	if (($tpfighters == 1) && ($transfer_fighters > $planetinfo['fighters']))
	{
		if($free_fighter <=  $planetinfo['fighters'])
		{
			$transfer_fighters = $free_fighter;
		}
		else
		{
			$transfer_fighters = $planetinfo['fighters'];
		}
	}
	else
	{
		if ($tpfighters == 1)
		{
			if($transfer_fighters > $free_fighter)
			{
				$transfer_fighters = $free_fighter;
			}
		}
	}
}

// Now that we have the amounts adjusted to suit available resources, go ahead and multiply them by their tpflag.
if($playerinfo['player_id'] == $planetinfo['owner'])
{
	$transfer_special = $transfer_special * $tpspecial;
}
else
{
	$transfer_special = 0;
}
$transfer_ore = $transfer_ore * $tpore;
$transfer_organics = $transfer_organics * $tporganics;
$transfer_goods = $transfer_goods * $tpgoods;
$transfer_energy = $transfer_energy * $tpenergy;
$transfer_colonists = $transfer_colonists * $tpcolonists;
$transfer_credits = $transfer_credits * $tpcredits;
$transfer_torps = $transfer_torps * $tptorps;
$transfer_fighters = $transfer_fighters * $tpfighters;

$template_object->assign("enable_spies", $enable_spies);
$template_object->assign("enable_dignitaries", $enable_dignitaries);
$template_object->assign("l_spy_transferred", $l_spy_transferred);
$template_object->assign("l_dig_transferred", $l_dig_transferred);
$template_object->assign("digtotal", $digtotal);
$template_object->assign("spytotal", $spytotal);
$template_object->assign("l_planet2_noten", $l_planet2_noten);
$template_object->assign("l_planet2_settr", $l_planet2_settr);
$template_object->assign("l_units", $l_units);
$template_object->assign("l_ore", $l_ore);
$template_object->assign("l_organics", $l_organics);
$template_object->assign("l_goods", $l_goods);
$template_object->assign("l_energy", $l_energy);
$template_object->assign("l_colonists", $l_colonists);
$template_object->assign("l_credits", $l_credits);
$template_object->assign("l_planet2_baseexceeded", $l_planet2_baseexceeded);
$template_object->assign("l_torps", $l_torps);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_planet2_losup", $l_planet2_losup);

if ($playerinfo['player_id'] != $planetinfo['owner'] && $transfer_credits != 0 && $team_planet_transfers != 1)
{
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_planet2_noteamtransfer", $l_planet2_noteamtransfer . "" . "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/planet_transfernoteam.tpl");
	include ("footer.php");
	die();
}

if ($ship_holds_used > NUM_HOLDS($shipinfo['hull']))
{
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_planet2_fortr", $l_planet2_fortr);
	$template_object->assign("l_holds", $l_holds);
	$template_object->assign("l_planet2_noten", $l_planet2_noten);
	$template_object->assign("gotomain", $l_global_mmenu . " - " . $ship_holds_used . " - " . NUM_HOLDS($shipinfo['hull']));
	$template_object->display($templatename."planet_owned/planet_transfernoholds.tpl");
	include ("footer.php");
	die();
}

if (!empty($planetinfo))
{
	if ($planetinfo['owner'] == $playerinfo['player_id'] || ($planetinfo['team'] == $playerinfo['team'] && $playerinfo['team'] <> 0))
	{
		$mineteam = 1;

		if ($transfer_credits > 0 and $planetinfo['team_cash'] == "N" and $playerinfo['player_id'] != $planetinfo['owner'])
		{
			$transfer_credits = 0;
		}

		if($transfer_credits < 0){
			if (abs($transfer_credits) + $planetinfo['credits'] > $planetinfo['max_credits'])
			{
				$transfer_credits = -($planetinfo['max_credits'] - $planetinfo['credits']);
			}
		}

		$tcredits=NUMBER(abs($transfer_credits));
		if($transfer_credits > 0)
			$direction = $l_planet_from;
		else $direction = $l_planet_to;

		if (abs($transfer_credits) > 0 and $playerinfo['player_id'] != $planetinfo['owner'] and $planetinfo['team_cash'] == "Y")
		{
			$logtransfer = str_replace("[character_name]", "<font color=white><b>$playerinfo[character_name]</b></font>", $l_planet_teamcredits);
			$logtransfer = str_replace("[tcredits]", "<font color=white><b>$tcredits</b></font>", $logtransfer);
			$logtransfer = str_replace("[name]", "<font color=white><b>$planetinfo[name]</b></font>", $logtransfer);
			$logtransfer = str_replace("[direction]", "<font color=white><b>$direction</b></font>", $logtransfer);
			$logtransfer = str_replace("[sector_id]", "<br><font color=white><b>$planetinfo[sector_name]</b></font>", $logtransfer);
			playerlog($planetinfo['owner'], "LOG0_RAW", $logtransfer);
			if ($planetinfo['team'] > 0 && $planetinfo['owner'] != $planetinfo['team']){
				playerlog($planetinfo['team'], "LOG0_RAW", $logtransfer);
			}
		}

		if(!empty($shipspecialname))
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=greatest(amount+$transfer_special, 0) WHERE ship_id=$playerinfo[currentship] and cargo_name='$shipspecialname'");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=greatest(amount+$transfer_ore, 0) WHERE ship_id=$playerinfo[currentship] and cargo_name='ore'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=greatest(amount+$transfer_goods, 0) WHERE ship_id=$playerinfo[currentship] and cargo_name='goods'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=greatest(amount+$transfer_organics, 0) WHERE ship_id=$playerinfo[currentship] and cargo_name='organics'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=greatest(amount+$transfer_colonists, 0) WHERE ship_id=$playerinfo[currentship] and cargo_name='colonists'");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET energy=energy+$transfer_energy, torps=torps+$transfer_torps, fighters=fighters+$transfer_fighters WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		if($is_teamcash_able == 1 && $transfer_credits != 0)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET team_cash_countdown = $team_cash_delay, credits=credits+$transfer_credits, turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		else
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits+$transfer_credits, turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET special_amount=special_amount-$transfer_special, ore=ore-$transfer_ore, organics=organics-$transfer_organics, goods=goods-$transfer_goods, energy=energy-$transfer_energy, colonists=colonists-$transfer_colonists, torps=torps-$transfer_torps, fighters=fighters-$transfer_fighters, credits=credits-$transfer_credits WHERE planet_id=$planet_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		$template_object->assign("s_special", ($transfer_special < 0) ? str_replace("[amount]", abs($transfer_special), str_replace("[commodity]", ucwords($shipspecialname), $l_planet_to_planet)) : '');
		$template_object->assign("s_ore", ($transfer_ore < 0) ? str_replace("[amount]", abs($transfer_ore), str_replace("[commodity]", $l_ore, $l_planet_to_planet)) : '');
		$template_object->assign("s_goods", ($transfer_goods < 0) ? str_replace("[amount]", abs($transfer_goods), str_replace("[commodity]", $l_goods, $l_planet_to_planet)) : '');
		$template_object->assign("s_organics", ($transfer_organics < 0) ? str_replace("[amount]", abs($transfer_organics), str_replace("[commodity]", $l_organics, $l_planet_to_planet)) : '');
		$template_object->assign("s_colonists", ($transfer_colonists < 0) ? str_replace("[amount]", abs($transfer_colonists), str_replace("[commodity]", $l_colonists, $l_planet_to_planet)) : '');
		$template_object->assign("s_energy", ($transfer_energy < 0) ? str_replace("[amount]", abs($transfer_energy), str_replace("[commodity]", $l_energy, $l_planet_to_planet)) : '');
		$template_object->assign("s_torps", ($transfer_torps < 0) ? str_replace("[amount]", abs($transfer_torps), str_replace("[commodity]", $l_torps, $l_planet_to_planet)) : '');
		$template_object->assign("s_fighters", ($transfer_fighters < 0) ? str_replace("[amount]", abs($transfer_fighters), str_replace("[commodity]", $l_fighters, $l_planet_to_planet)) : '');
		$template_object->assign("s_credits", ($transfer_credits < 0) ? str_replace("[amount]", abs($transfer_credits), str_replace("[commodity]", $l_credits, $l_planet_to_planet)) : '');

		$template_object->assign("p_special", ($transfer_special > 0) ? str_replace("[amount]", $transfer_special, str_replace("[commodity]", ucwords($shipspecialname), $l_planet_to_ship)) : '');
		$template_object->assign("p_ore", ($transfer_ore > 0) ? str_replace("[amount]", $transfer_ore, str_replace("[commodity]", $l_ore, $l_planet_to_ship)) : '');
		$template_object->assign("p_goods", ($transfer_goods > 0) ? str_replace("[amount]", $transfer_goods, str_replace("[commodity]", $l_goods, $l_planet_to_ship)) : '');
		$template_object->assign("p_organics", ($transfer_organics > 0) ? str_replace("[amount]", $transfer_organics, str_replace("[commodity]", $l_organics, $l_planet_to_ship)) : '');
		$template_object->assign("p_colonists", ($transfer_colonists > 0) ? str_replace("[amount]", $transfer_colonists, str_replace("[commodity]", $l_colonists, $l_planet_to_ship)) : '');
		$template_object->assign("p_energy", ($transfer_energy > 0) ? str_replace("[amount]", $transfer_energy, str_replace("[commodity]", $l_energy, $l_planet_to_ship)) : '');
		$template_object->assign("p_torps", ($transfer_torps > 0) ? str_replace("[amount]", $transfer_torps, str_replace("[commodity]", $l_torps, $l_planet_to_ship)) : '');
		$template_object->assign("p_fighters", ($transfer_fighters > 0) ? str_replace("[amount]", $transfer_fighters, str_replace("[commodity]", $l_fighters, $l_planet_to_ship)) : '');
		$template_object->assign("p_credits", ($transfer_credits > 0) ? str_replace("[amount]", $transfer_credits, str_replace("[commodity]", $l_credits, $l_planet_to_ship)) : '');
	}
	else
	{
		$mineteam = 0;
	}
	$template_object->assign("l_planet_transfer_return", $l_planet_transfer_return);
	$template_object->assign("l_planet", $l_planet);
	$template_object->assign("mineteam", $mineteam);
	$template_object->assign("l_planet2_notowner", $l_planet2_notowner);
	$template_object->assign("l_planet2_compl", $l_planet2_compl);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("l_planet2_fortr", $l_planet2_fortr);
	$template_object->assign("l_planet2_power", $l_planet2_power);
	$template_object->assign("l_planet2_comp", $l_planet2_comp);
	$template_object->assign("l_planet2_laun", $l_planet2_laun);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/planet_transfer.tpl");
	include ("footer.php");
	die();
}

?>