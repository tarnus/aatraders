<?php
// 1
// 2100
// 360
// 0
// Y
// How often independent planets will upgrade themselves.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/set_max_credits.inc");
include ("globals/calc_ownership.inc");

TextFlush ( "<b>Planetary Independance Upgrade</b><br><br>");

$base_query = $db->Execute("SELECT * from {$db_prefix}planets WHERE (owner='2' or owner='1') and base='N'");
db_op_result($base_query,__LINE__,__FILE__);

$reccount = $base_query->RecordCount();
$totalupdates = 0;

if ($base_query && $reccount > 0){
	while (!$base_query->EOF){
		$targetinfo = $base_query->fields;

		/* build a base */
		if ($targetinfo['ore'] >= $base_ore && $targetinfo['organics'] >= $base_organics && $targetinfo['goods'] >= $base_goods && $targetinfo['credits'] >= $base_credits)
		{
			// ** Create The Base
			$makebase_query = $db->Execute("UPDATE {$db_prefix}planets SET base='Y', ore=ore-$base_ore, organics=organics-$base_organics, goods=goods-$base_goods, credits=credits-$base_credits WHERE planet_id=$targetinfo[planet_id]");
			db_op_result($makebase_query,__LINE__,__FILE__);

			// ** Calc Ownership and Notify User Of Results
			$ownership = calc_ownership($targetinfo['sector_id']);

			$totalupdates++;
		}

		$base_query->MoveNext();
	}
	$base_query->close();
}
TextFlush ("<br>Non-Based Independent Planets Based: $totalupdates<br>");
TextFlush ( "<br>");

$debug_query = $db->Execute("SELECT * from {$db_prefix}planets WHERE owner='2' and base='Y'");
db_op_result($debug_query,__LINE__,__FILE__);

$reccount = $debug_query->RecordCount();
$totalupdates = 0;

$random_range_max = round($max_tech_level / 100);

if ($debug_query && $reccount > 0){
	while (!$debug_query->EOF){
		$targetinfo = $debug_query->fields;
		$upgraded = 0;

		$upgradelist = '';

		$credits_to_use = 0;
		$startcredits = $targetinfo['credits'];
		if($startcredits > ($targetinfo['max_credits'] * 0.9))
		{
			$credits_to_use = $targetinfo['credits'] - ($targetinfo['max_credits'] * 0.9);
		}
		$credits_to_use += ($targetinfo['credits'] * 0.01);
		$unused_credits = $targetinfo['credits'] - $credits_to_use;
		$targetinfo['credits'] = $credits_to_use;

		// Upgrade Sector Defense Tech
		$random_upgrade = mt_rand(1, $random_range_max);
		$fighter_upgrade_cost = phpChangeDelta($targetinfo['sector_defense_weapons']+$random_upgrade, $targetinfo['sector_defense_weapons']);
		if($fighter_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 6500){
			$targetinfo['credits'] -= $fighter_upgrade_cost;
			$targetinfo['sector_defense_weapons'] += $random_upgrade;
			if($targetinfo['sector_defense_weapons_normal'] < $targetinfo['sector_defense_weapons'])
			{
				$targetinfo['sector_defense_weapons_normal'] = $targetinfo['sector_defense_weapons'];
			}
			$upgraded = 1;
			$upgradelist .= "- Sector Defense Weapons <font color='#ffffff'>$targetinfo[sector_defense_weapons]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$beams_upgrade_cost = phpChangeDelta($targetinfo['sector_defense_sensors']+$random_upgrade, $targetinfo['sector_defense_sensors']);
		if($beams_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 5500){
			$targetinfo['credits'] -= $beams_upgrade_cost;
			$targetinfo['sector_defense_sensors'] += $random_upgrade;
			if($targetinfo['sector_defense_sensors_normal'] < $targetinfo['sector_defense_sensors'])
			{
				$targetinfo['sector_defense_sensors_normal'] = $targetinfo['sector_defense_sensors'];
			}
			$upgraded = 1;
			$upgradelist .= "- Sector Defense Sensors <font color='#ffffff'>$targetinfo[sector_defense_sensors]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$torp_launchers_upgrade_cost = phpChangeDelta($targetinfo['sector_defense_cloak']+$random_upgrade, $targetinfo['sector_defense_cloak']);
		if($torp_launchers_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 4500){
			$targetinfo['credits'] -= $torp_launchers_upgrade_cost;
			$targetinfo['sector_defense_cloak'] += $random_upgrade;
			if($targetinfo['sector_defense_cloak_normal'] < $targetinfo['sector_defense_cloak'])
			{
				$targetinfo['sector_defense_cloak_normal'] = $targetinfo['sector_defense_cloak'];
			}
			$upgraded = 1;
			$upgradelist .= "- Sector Defense Cloak <font color='#ffffff'>$targetinfo[sector_defense_cloak]</font> ";
		}

		$max_sector_defense_fighters = 0;
		$max_defense = $db->Execute("SELECT sector_defense_weapons from {$db_prefix}planets where owner = 2 and sector_id = $targetinfo[sector_id] and base = 'Y'");
		db_op_result($max_defense,__LINE__,__FILE__);
		if ($max_defense > 0)
		{
			while (!$max_defense->EOF)
			{
				$max_sector_defense_fighters += NUM_PER_LEVEL($max_defense->fields['sector_defense_weapons']) * $sector_fighter_multiplier;
				$max_defense->MoveNext();
			}
		}

		// Upgrade Sector Defenses

		$res = $db->Execute("SELECT allow_defenses, {$db_prefix}universe.zone_id, owner FROM {$db_prefix}zones,{$db_prefix}universe " .
							"WHERE sector_id=$targetinfo[sector_id] AND {$db_prefix}zones.zone_id={$db_prefix}universe.zone_id");
		$query97 = $res->fields;
		$res->close();

		if ($query97['allow_defenses'] != 'N')
		{
			//Put the defense information into the array "defenseinfo"
			$result3 = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id=$targetinfo[sector_id] ");
			$defenseinfo = $result3->fields;
			$randomcheck = 100;
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

					if ($defenses[$i]['player_id'] != 2)
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
			$result3->close();

			if ($i > 0)
			{
				if (!$owns_all)
				{
					$defense_owner = $defenses[0]['player_id'];
					$result2 = $db->Execute("SELECT * from {$db_prefix}players where player_id=$defense_owner");
					$fighters_owner = $result2->fields;
					$result2->close();

					if ($fighters_owner['team'] != 2)
					{
						$randomcheck = 0;
					}
				}
			}

			if ($query97['allow_defenses'] == 'L' and $randomcheck != 0)
			{
				$zone_owner = $query97['owner'];
				$result2 = $db->Execute("SELECT * from {$db_prefix}players where player_id=$zone_owner");
				$zoneowner_info = $result2->fields;
				$result2->close();

				if ($zone_owner <> 2)
				{
					 if ($zoneowner_info['team'] != 2)
					 {
						$randomcheck = 0;
					 }
				}
			}

			if(mt_rand(1, 10000) < $randomcheck){
				$res = $db->SelectLimit("SELECT * from {$db_prefix}sector_defense where defense_type = 'fighters' and player_id=2 and sector_id=$targetinfo[sector_id]", 1);
				$row = $res->fields;
				$res->close();
				$energy_required = ROUND($row['quantity'] * $energy_per_fighter);
				$res4 = $db->Execute("SELECT IFNULL(SUM(energy),0) as energy_available from {$db_prefix}planets where owner = 2 and sector_id = $targetinfo[sector_id]"); 
				$planet_energy = $res4->fields;
				$res4->close();
				$energy_available = $planet_energy['energy_available'];
				$maxfighters = min(floor(($energy_available - $energy_required) * $energy_per_fighter), $max_sector_defense_fighters);
				$addfighters = floor($maxfighters * 0.015);
				$fightercost = $addfighters * $fighter_price;
				if($fightercost > $targetinfo['credits']){
					$addfighters = floor($targetinfo['credits'] / $fighter_price);
					$fightercost = $addfighters * $fighter_price;
				}
				$addfighters = floor($addfighters * (rand(10, 75) * 0.01));
				$fightercost = $addfighters * $fighter_price;
				$targetinfo['credits'] -= $fightercost;
//			echo "available $energy_available, required $energy_required, max add fighters $maxfighters, fighters to add $addfighters, fighter cost $fightercost, credits left $targetinfo[credits].<br>\n";

				if ($addfighters > 0)
				{
					if ($row['defense_id'] != 0)
					{
						$fighter_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $addfighters " .
													"where defense_id = $row[defense_id]");
						db_op_result($fighter_query,__LINE__,__FILE__);
					}
					else
					{
						$fighter_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
													"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
													"(2,$targetinfo[sector_id],'fighters',$addfighters, 'Sector_Fighter')");
						db_op_result($fighter_query,__LINE__,__FILE__);
					}
					$upgraded = 1;
					$upgradelist .= "- Sector Fighters <font color='#ffffff'>$addfighters</font> ";
				}
			}

			if(mt_rand(1, 10000) < $randomcheck){
				$minecost = floor($targetinfo['credits'] * 0.02);
				$addmines = floor($minecost / $torpedo_price);
				$addmines = floor($addmines * (rand(10, 75) * 0.01));
				$minecost = $addmines * $torpedo_price;
				$targetinfo['credits'] -= $minecost;
//			echo "mines to add $addmines, mine cost $minecost, credits left $targetinfo[credits].<br>\n";

				$res = $db->Execute("SELECT * from {$db_prefix}sector_defense where defense_type = 'mines' and player_id=2 and sector_id=$targetinfo[sector_id]");
				$row = $res->fields;
				$res->close();
				if ($addmines > 0)
				{
					if ($row['defense_id'] != 0)
					{
						$mines_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $addmines " .
													"where defense_id = $row[defense_id]");
						db_op_result($mines_query,__LINE__,__FILE__);
					}
					else
					{
						$mines_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
													"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
													"(2,$targetinfo[sector_id],'mines',$addmines, 'Sector_Mine')");
						db_op_result($mines_query,__LINE__,__FILE__);
					}
					$upgraded = 1;
					$upgradelist .= "- Sector Mines <font color='#ffffff'>$addmines</font> ";
				}
			}
		}

		// Upgrade Planet Tech

		$random_upgrade = mt_rand(1, $random_range_max);
		$shields_upgrade_cost = phpChangePlanetDelta($targetinfo['shields']+$random_upgrade, $targetinfo['shields']);
		if($shields_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 4000){
			$targetinfo['credits'] -= $shields_upgrade_cost;
			$targetinfo['shields'] += $random_upgrade;
			if($targetinfo['shields_normal'] < $targetinfo['shields'])
			{
				$targetinfo['shields_normal'] = $targetinfo['shields'];
			}
			$upgraded = 1;
			$upgradelist .= "- Shields <font color='#ffffff'>$targetinfo[shields]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$beams_upgrade_cost = phpChangePlanetDelta($targetinfo['beams']+$random_upgrade, $targetinfo['beams']);
		if($beams_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 5000){
			$targetinfo['credits'] -= $beams_upgrade_cost;
			$targetinfo['beams'] += $random_upgrade;
			if($targetinfo['beams_normal'] < $targetinfo['beams'])
			{
				$targetinfo['beams_normal'] = $targetinfo['beams'];
			}
			$upgraded = 1;
			$upgradelist .= "- Beams <font color='#ffffff'>$targetinfo[beams]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$torp_launchers_upgrade_cost = phpChangePlanetDelta($targetinfo['torp_launchers']+$random_upgrade, $targetinfo['torp_launchers']);
		if($torp_launchers_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 4500){
			$targetinfo['credits'] -= $torp_launchers_upgrade_cost;
			$targetinfo['torp_launchers'] += $random_upgrade;
			if($targetinfo['torp_launchers_normal'] < $targetinfo['torp_launchers'])
			{
				$targetinfo['torp_launchers_normal'] = $targetinfo['torp_launchers'];
			}
			$upgraded = 1;
			$upgradelist .= "- Torps <font color='#ffffff'>$targetinfo[torp_launchers]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$sensors_upgrade_cost = phpChangePlanetDelta($targetinfo['sensors']+$random_upgrade, $targetinfo['sensors']);
		if($sensors_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 2500){
			$targetinfo['credits'] -= $sensors_upgrade_cost;
			$targetinfo['sensors'] += $random_upgrade;
			if($targetinfo['sensors_normal'] < $targetinfo['sensors'])
			{
				$targetinfo['sensors_normal'] = $targetinfo['sensors'];
			}
			$upgraded = 1;
			$upgradelist .= "- Sensors <font color='#ffffff'>$targetinfo[sensors]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$fighter_upgrade_cost = phpChangePlanetDelta($targetinfo['fighter']+$random_upgrade, $targetinfo['fighter']);
		if($fighter_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 6000){
			$targetinfo['credits'] -= $fighter_upgrade_cost;
			$targetinfo['fighter'] += $random_upgrade;
			if($targetinfo['fighter_normal'] < $targetinfo['fighter'])
			{
				$targetinfo['fighter_normal'] = $targetinfo['fighter'];
			}
			$upgraded = 1;
			$upgradelist .= "- Fighters <font color='#ffffff'>$targetinfo[fighter]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$jammer_upgrade_cost = phpChangePlanetDelta($targetinfo['jammer']+$random_upgrade, $targetinfo['jammer']);
		if($jammer_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 3500){
			$targetinfo['credits'] -= $jammer_upgrade_cost;
			$targetinfo['jammer'] += $random_upgrade;
			if($targetinfo['jammer_normal'] < $targetinfo['jammer'])
			{
				$targetinfo['jammer_normal'] = $targetinfo['jammer'];
			}
			$upgraded = 1;
			$upgradelist .= "- Jammer <font color='#ffffff'>$targetinfo[jammer]</font> ";
		}

		$random_upgrade = mt_rand(1, $random_range_max);
		$cloak_upgrade_cost = phpChangePlanetDelta($targetinfo['cloak']+$random_upgrade, $targetinfo['cloak']);
		if($cloak_upgrade_cost < $targetinfo['credits'] and mt_rand(1, 10000) < 3000){
			$targetinfo['credits'] -= $cloak_upgrade_cost;
			$targetinfo['cloak'] += $random_upgrade;
			if($targetinfo['cloak_normal'] < $targetinfo['cloak'])
			{
				$targetinfo['cloak_normal'] = $targetinfo['cloak'];
			}
			$upgraded = 1;
			$upgradelist .= "- Cloak <font color='#ffffff'>$targetinfo[cloak]</font> ";
		}

		if($upgraded == 1){
			$update_query = $db->Execute("UPDATE {$db_prefix}planets SET 
			credits=$targetinfo[credits] + $unused_credits, fighter=$targetinfo[fighter], sensors=$targetinfo[sensors], beams=$targetinfo[beams], torp_launchers=$targetinfo[torp_launchers], 
			shields=$targetinfo[shields], jammer=$targetinfo[jammer], cloak=$targetinfo[cloak], fighter_normal=$targetinfo[fighter_normal], 
			sensors_normal=$targetinfo[sensors_normal], beams_normal=$targetinfo[beams_normal], torp_launchers_normal=$targetinfo[torp_launchers_normal], 
			shields_normal=$targetinfo[shields_normal], jammer_normal=$targetinfo[jammer_normal], cloak_normal=$targetinfo[cloak_normal], 
			sector_defense_weapons=$targetinfo[sector_defense_weapons], sector_defense_sensors=$targetinfo[sector_defense_sensors], sector_defense_cloak=$targetinfo[sector_defense_cloak], 
			sector_defense_weapons_normal=$targetinfo[sector_defense_weapons_normal], sector_defense_sensors_normal=$targetinfo[sector_defense_sensors_normal], sector_defense_cloak_normal=$targetinfo[sector_defense_cloak_normal] 
			WHERE planet_id = $targetinfo[planet_id]");
			db_op_result($update_query,__LINE__,__FILE__);
			if($targetinfo['shields'] == 1)
			{
				$who = "Alliance";
			}
			else
			{
				$who = "Independent";
			}
			TextFlush ( "<font color='#00ff00'>$who Upgraded planet <font color='#ffffff'>$targetinfo[name]</font> in sector <font color='#ffff00'>$targetinfo[sector_id]</font>, credits spent = <font color='#ff0000'>".NUMBER($startcredits - ($targetinfo['credits'] + $unused_credits))."</font>, credits left = <font color='#ffffff'>".NUMBER(($targetinfo['credits'] + $unused_credits))."</font>:  <font color='#00ffff'>$upgradelist-</font></font><br>");
			$totalupdates++;
		}
		set_max_credits($targetinfo['planet_id']);
		$debug_query->MoveNext();
	}
	$debug_query->close();
}

TextFlush ("<br>Based: $totalupdates - Upgraded Levels<br>");
TextFlush ( "<br>");

$new_ticks = 300 + mt_rand(0, 300);
TextFlush ("Next Indy Update: $new_ticks ticks<br><br>");
$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET ticks_full=$new_ticks WHERE sched_file='sched_indy_upgrade.inc'");
db_op_result($debug_query,__LINE__,__FILE__);
?>
