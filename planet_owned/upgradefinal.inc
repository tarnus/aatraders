<?php
get_post_ifset("sector_defense_cloak_upgrade, sector_defense_sensors_upgrade, sector_defense_weapons_upgrade, cloak_upgrade, jammer_upgrade, shields_upgrade, torp_launchers_upgrade, beams_upgrade, sensors_upgrade, fighter_upgrade, total_cost");

function phpTrueDelta($futurevalue,$planetvalue)
{
	$tempval = $futurevalue - $planetvalue;
	return $tempval;
}

	if (!empty($planetinfo))
	{
		if ($planetinfo['base'] == "N")
		{
			$template_object->assign("error_msg", $l_planet_upgradebase);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/planet_upgradedie.tpl");
			include ("footer.php");
			die();
		}

		$color_red	 = "red";
		$color_green   = "#00FF00"; //light green
		$trade_deficit = "$l_cost : ";
		$trade_benefit = "$l_profit : ";

// Fighters
		$fighter_upgrade_cost = 0;
		if($planetinfo['fighter'] == $planetinfo['fighter_normal']){
			if ($fighter_upgrade > $max_tech_level)
				$fighter_upgrade = $max_tech_level;

			if ($fighter_upgrade < 0)
				$fighter_upgrade = 0;

			if ($fighter_upgrade > $planetinfo['fighter_normal'])
			{
				$fighter_upgrade_cost = phpChangePlanetDelta($fighter_upgrade, $planetinfo['fighter_normal']);
			}
		}
		else
		{
			$fighter_upgrade = $planetinfo['fighter_normal'];
		}

// Sensors
		$sensors_upgrade_cost = 0;
		if($planetinfo['sensors'] == $planetinfo['sensors_normal']){
			if ($sensors_upgrade > $max_tech_level)
				$sensors_upgrade = $max_tech_level;

			if ($sensors_upgrade < 0)
				$sensors_upgrade = 0;

			if ($sensors_upgrade > $planetinfo['sensors_normal'])
			{
				$sensors_upgrade_cost = phpChangePlanetDelta($sensors_upgrade, $planetinfo['sensors_normal']);
			}
		}
		else
		{
			$sensors_upgrade = $planetinfo['sensors_normal'];
		}

// Beams
		$beams_upgrade_cost = 0;
		if($planetinfo['beams'] == $planetinfo['beams_normal']){
			if ($beams_upgrade > $max_tech_level)
				$beams_upgrade = $max_tech_level;

			if ($beams_upgrade < 0)
				$beams_upgrade = 0;

			if ($beams_upgrade > $planetinfo['beams_normal'])
			{
				$beams_upgrade_cost = phpChangePlanetDelta($beams_upgrade, $planetinfo['beams_normal']);
			}
		}
		else
		{
			$beams_upgrade = $planetinfo['beams_normal'];
		}

// Cloak
		$cloak_upgrade_cost = 0;
		if($planetinfo['cloak'] == $planetinfo['cloak_normal']){
			if ($cloak_upgrade > $max_tech_level)
				$cloak_upgrade = $max_tech_level;

			if ($cloak_upgrade < 0)
				$cloak_upgrade = 0;

			if ($cloak_upgrade > $planetinfo['cloak_normal'])
			{
				$cloak_upgrade_cost = phpChangePlanetDelta($cloak_upgrade, $planetinfo['cloak_normal']);
			}
		}
		else
		{
			$cloak_upgrade = $planetinfo['cloak_normal'];
		}

// Torp_launchers
		$torp_launchers_upgrade_cost = 0;
		if($planetinfo['torp_launchers'] == $planetinfo['torp_launchers_normal']){
			if ($torp_launchers_upgrade > $max_tech_level)
				$torp_launchers_upgrade = $max_tech_level;

			if ($torp_launchers_upgrade < 0)
				$torp_launchers_upgrade = 0;

			if ($torp_launchers_upgrade > $planetinfo['torp_launchers_normal'])
			{
				$torp_launchers_upgrade_cost = phpChangePlanetDelta($torp_launchers_upgrade, $planetinfo['torp_launchers_normal']);
			}
		}
		else
		{
			$torp_launchers_upgrade = $planetinfo['torp_launchers_normal'];
		}

// Shields
		$shields_upgrade_cost = 0;
		if($planetinfo['shields'] == $planetinfo['shields_normal']){
			if ($shields_upgrade > $max_tech_level)
				$shields_upgrade = $max_tech_level;

			if ($shields_upgrade < 0)
				$shields_upgrade = 0;

			if ($shields_upgrade > $planetinfo['shields_normal'])
			{
				$shields_upgrade_cost = phpChangePlanetDelta($shields_upgrade, $planetinfo['shields_normal']);
			}
		}
		else
		{
			$shields_upgrade = $planetinfo['shields_normal'];
		}

// Jammer
		$jammer_upgrade_cost = 0;
		if($planetinfo['jammer'] == $planetinfo['jammer_normal']){
			if ($jammer_upgrade > $max_tech_level)
				$jammer_upgrade = $max_tech_level;

			if ($jammer_upgrade < 0)
				$jammer_upgrade = 0;

			if ($jammer_upgrade > $planetinfo['jammer'])
			{
				$jammer_upgrade_cost = phpChangePlanetDelta($jammer_upgrade, $planetinfo['jammer']);
			}
		}
		else
		{
			$jammer_upgrade = $planetinfo['jammer_normal'];
		}

// SD Weapons
		$sector_defense_weapons_upgrade_cost = 0;
		if($planetinfo['sector_defense_weapons'] == $planetinfo['sector_defense_weapons_normal']){
			if ($sector_defense_weapons_upgrade > $max_tech_level)
				$sector_defense_weapons_upgrade = $max_tech_level;

			if ($sector_defense_weapons_upgrade < 0)
				$sector_defense_weapons_upgrade = 0;

			if ($sector_defense_weapons_upgrade > $planetinfo['sector_defense_weapons'])
			{
				$sector_defense_weapons_upgrade_cost = phpChangePlanetSDDelta($sector_defense_weapons_upgrade, $planetinfo['sector_defense_weapons']);
			}
		}
		else
		{
			$sector_defense_weapons_upgrade = $planetinfo['sector_defense_weapons_normal'];
		}

// SD Sensors
		$sector_defense_sensors_upgrade_cost = 0;
		if($planetinfo['sector_defense_sensors'] == $planetinfo['sector_defense_sensors_normal']){
			if ($sector_defense_sensors_upgrade > $max_tech_level)
				$sector_defense_sensors_upgrade = $max_tech_level;

			if ($sector_defense_sensors_upgrade < 0)
				$sector_defense_sensors_upgrade = 0;

			if ($sector_defense_sensors_upgrade > $planetinfo['sector_defense_sensors'])
			{
				$sector_defense_sensors_upgrade_cost = phpChangePlanetSDDelta($sector_defense_sensors_upgrade, $planetinfo['sector_defense_sensors']);
			}
		}
		else
		{
			$sector_defense_sensors_upgrade = $planetinfo['sector_defense_sensors_normal'];
		}

// SD Cloak
		$sector_defense_cloak_upgrade_cost = 0;
		if($planetinfo['sector_defense_cloak'] == $planetinfo['sector_defense_cloak_normal']){
			if ($sector_defense_cloak_upgrade > $max_tech_level)
				$sector_defense_cloak_upgrade = $max_tech_level;

			if ($sector_defense_cloak_upgrade < 0)
				$sector_defense_cloak_upgrade = 0;

			if ($sector_defense_cloak_upgrade > $planetinfo['sector_defense_cloak'])
			{
				$sector_defense_cloak_upgrade_cost = phpChangePlanetSDDelta($sector_defense_cloak_upgrade, $planetinfo['sector_defense_cloak']);
			}
		}
		else
		{
			$sector_defense_cloak_upgrade = $planetinfo['sector_defense_cloak_normal'];
		}

		$total_cost = $fighter_upgrade_cost + $sector_defense_weapons_upgrade_cost + $sector_defense_sensors_upgrade_cost +
		$sensors_upgrade_cost + $beams_upgrade_cost + $cloak_upgrade_cost + $sector_defense_cloak_upgrade_cost + 
		$torp_launchers_upgrade_cost + $shields_upgrade_cost+ $jammer_upgrade_cost;

		if ($total_cost > $playerinfo['credits'])
		{
			$l_planet_nomoney = str_replace("[cost]", NUMBER($total_cost), $l_planet_nomoney);
			$l_planet_nomoney = str_replace("[credits]", NUMBER($playerinfo['credits']), $l_planet_nomoney);
			$template_object->assign("error_msg", $l_planet_nomoney);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/planet_upgradedie.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			$trade_credits = NUMBER(abs($total_cost));

			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$total_cost,turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$max_credits = 0;
			$query = "UPDATE {$db_prefix}planets SET planet_id=$planet_id ";
// Fighters
			if ($fighter_upgrade > $planetinfo['fighter_normal'])
			{
				$query = $query . ", fighter=$fighter_upgrade, fighter_normal=$fighter_upgrade";
				$upgradefighter = 1;
				$max_credits += phpMaxCreditsDelta($fighter_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['fighter_normal'], 0);
			}
// Sensors
			if ($sensors_upgrade > $planetinfo['sensors_normal'])
			{
				$query = $query . ", sensors=$sensors_upgrade, sensors_normal=$sensors_upgrade";
				$upgradesensors = 1;
				$max_credits += phpMaxCreditsDelta($sensors_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['sensors_normal'], 0);
			}
// Beam Weapons
			if ($beams_upgrade > $planetinfo['beams_normal'])
			{
				$query = $query . ", beams=$beams_upgrade, beams_normal=$beams_upgrade";
				$upgradebeams = 1;
				$max_credits += phpMaxCreditsDelta($beams_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['beams_normal'], 0);
			}
// Torpedo Launchers
			if ($torp_launchers_upgrade > $planetinfo['torp_launchers_normal'])
			{
				$query = $query . ", torp_launchers=$torp_launchers_upgrade, torp_launchers_normal=$torp_launchers_upgrade";
				$upgradetorps = 1;
				$max_credits += phpMaxCreditsDelta($torp_launchers_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['torp_launchers_normal'], 0);
			}
// Shields
			if ($shields_upgrade > $planetinfo['shields_normal'])
			{
				$query = $query . ", shields=$shields_upgrade, shields_normal=$shields_upgrade";
				$upgradeshields = 1;
				$max_credits += phpMaxCreditsDelta($shields_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['shields_normal'], 0);
			}
// Jammer
			if ($jammer_upgrade > $planetinfo['jammer_normal'])
			{
				$query = $query . ", jammer=$jammer_upgrade, jammer_normal=$jammer_upgrade";
				$upgradejammer = 1;
				$max_credits += phpMaxCreditsDelta($jammer_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['jammer_normal'], 0);
			}
// SD Weapons
			if ($sector_defense_weapons_upgrade > $planetinfo['sector_defense_weapons_normal'])
			{
				$query = $query . ", sector_defense_weapons=$sector_defense_weapons_upgrade, sector_defense_weapons_normal=$sector_defense_weapons_upgrade";
				$upgradesdweapons = 1;
   			}

// SD Sensors
			if ($sector_defense_sensors_upgrade > $planetinfo['sector_defense_sensors_normal'])
			{
				$query = $query . ", sector_defense_sensors=$sector_defense_sensors_upgrade, sector_defense_sensors_normal=$sector_defense_sensors_upgrade";
				$upgradesdsensors = 1;
   			}


// SD Cloak
			if ($sector_defense_cloak_upgrade > $planetinfo['sector_defense_cloak_normal'])
			{
				$query = $query . ", sector_defense_cloak=$sector_defense_cloak_upgrade, sector_defense_cloak_normal=$sector_defense_cloak_upgrade";
				$upgradesdcloak = 1;
   			}

// Cloak
			if ($cloak_upgrade > $planetinfo['cloak_normal'])
			{
				$query = $query . ", cloak=$cloak_upgrade, cloak_normal=$cloak_upgrade";
				$upgradecloak = 1;
				$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET spy_cloak=$cloak_upgrade WHERE planet_id = '$planetinfo[planet_id]' and ship_id = '0' and active = 'N'");
				db_op_result($debug_query,__LINE__,__FILE__);
				$max_credits += phpMaxCreditsDelta($cloak_upgrade, 0);
   			}
			else
			{
				$max_credits += phpMaxCreditsDelta($planetinfo['cloak_normal'], 0);
			}

			$max_credits = ($max_credits * $planet_credit_multi) + $base_credits;
			$query = $query . ", max_credits=$max_credits WHERE planet_id=$planet_id";
			$debug_query = $db->Execute("$query");
			db_op_result($debug_query,__LINE__,__FILE__);

			$template_object->assign("l_trade_result", $l_trade_result);
			$template_object->assign("l_cost", $l_cost);
			$template_object->assign("trade_credits", $trade_credits);
			$template_object->assign("l_credits", $l_credits);
			$template_object->assign("l_trade_upgraded", $l_trade_upgraded);
			$template_object->assign("l_fighter", $l_fighter);
			$template_object->assign("fighter_upgrade", $fighter_upgrade);
			$template_object->assign("l_sensors", $l_sensors);
			$template_object->assign("sensors_upgrade", $sensors_upgrade);
			$template_object->assign("l_beams", $l_beams);
			$template_object->assign("beams_upgrade", $beams_upgrade);
			$template_object->assign("l_torp_launch", $l_torp_launch);
			$template_object->assign("torp_launchers_upgrade", $torp_launchers_upgrade);
			$template_object->assign("l_shields", $l_shields);
			$template_object->assign("shields_upgrade", $shields_upgrade);
			$template_object->assign("l_jammer", $l_jammer);
			$template_object->assign("jammer_upgrade", $jammer_upgrade);
			$template_object->assign("l_cloak", $l_cloak);
			$template_object->assign("cloak_upgrade", $cloak_upgrade);
			$template_object->assign("planet_id", $planet_id);
			$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("upgradefighter", $upgradefighter);
			$template_object->assign("upgradesensors", $upgradesensors);
			$template_object->assign("upgradebeams", $upgradebeams);
			$template_object->assign("upgradetorps", $upgradetorps);
			$template_object->assign("upgradeshields", $upgradeshields);
			$template_object->assign("upgradejammer", $upgradejammer);
			$template_object->assign("upgradecloak", $upgradecloak);

			$template_object->assign("upgradesdweapons", $upgradesdweapons);
			$template_object->assign("upgradesdsensors", $upgradesdsensors);
			$template_object->assign("upgradesdcloak", $upgradesdcloak);

			$template_object->assign("sector_defense_weapons_upgrade", $sector_defense_weapons_upgrade);
			$template_object->assign("sector_defense_sensors_upgrade", $sector_defense_sensors_upgrade);
			$template_object->assign("sector_defense_cloak_upgrade", $sector_defense_cloak_upgrade);
			$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
			$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
			$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);

			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/planet_upgrade.tpl");
			include ("footer.php");
			die();
		}
	}

?>
