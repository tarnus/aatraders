<?php
// Create dropdowns when called
function dropdown($element_name,$current_value, $max_value)
{
	global $onchange;
	$i = $current_value;
	$dropdownvar = "<select size='1' name='$element_name'";
	$dropdownvar = "$dropdownvar ONCHANGE=\"countTotal()\">\n";
	while ($i <= $max_value)
	{
		if ($current_value == $i)
		{
			$dropdownvar = "$dropdownvar		<option value='$i' selected>$i</option>\n";
		}
		else
		{
			$dropdownvar = "$dropdownvar		<option value='$i'>$i</option>\n";
		}
		$i++;
	}
	$dropdownvar = "$dropdownvar	   </select>\n";
	return $dropdownvar;
}


		if ($planetinfo['base'] == "N")
		{
			$template_object->assign("result", $l_planet_nobase);
			$template_object->assign("planet_id", $planet_id);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
			$template_object->assign("l_igb_term", $l_igb_term);
			$template_object->assign("allow_ibank", $allow_ibank);
			$template_object->assign("l_by_placebounty", $l_by_placebounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/planet_ownedgeneric2.tpl");
			include ("footer.php");
			die();
		}
		else
		{

			$l_creds_to_spend=str_replace("[credits]",NUMBER($playerinfo['credits']),$l_creds_to_spend);

			if ($allow_ibank)
			{
				$igblink = "<A HREF=igb.php>$l_igb_term</a>";
				$l_ifyouneedmore=str_replace("[igb]",$igblink,$l_ifyouneedmore);
			}
			$planet_ratio=round(($planetinfo['credits']/$planetinfo['max_credits'])*100);
			$template_object->assign("java_cloak_normal", $planetinfo['cloak_normal']);
			$template_object->assign("java_jammer_normal", $planetinfo['jammer_normal']);
			$template_object->assign("java_shields_normal", $planetinfo['shields_normal']);
			$template_object->assign("java_torps_normal", $planetinfo['torp_launchers_normal']);
			$template_object->assign("java_beams_normal", $planetinfo['beams_normal']);
			$template_object->assign("java_sensors_normal", $planetinfo['sensors_normal']);
			$template_object->assign("java_fighter_normal", $planetinfo['fighter_normal']);
			$template_object->assign("java_sector_defense_weapons_normal", $planetinfo['sector_defense_weapons_normal']);
			$template_object->assign("java_sector_defense_sensors_normal", $planetinfo['sector_defense_sensors_normal']);
			$template_object->assign("java_sector_defense_cloak_normal", $planetinfo['sector_defense_cloak_normal']);

			$template_object->assign("java_cloak", $planetinfo['cloak']);
			$template_object->assign("java_jammer", $planetinfo['jammer']);
			$template_object->assign("java_shields", $planetinfo['shields']);
			$template_object->assign("java_torps", $planetinfo['torp_launchers']);
			$template_object->assign("java_beams", $planetinfo['beams']);
			$template_object->assign("java_sensors", $planetinfo['sensors']);
			$template_object->assign("java_fighter", $planetinfo['fighter']);
			$template_object->assign("java_sector_defense_weapons", $planetinfo['sector_defense_weapons']);
			$template_object->assign("java_sector_defense_sensors", $planetinfo['sector_defense_sensors']);
			$template_object->assign("java_sector_defense_cloak", $planetinfo['sector_defense_cloak']);
			$template_object->assign("java_credits", $playerinfo['credits']);
			$template_object->assign("planet_credits", $planetinfo['credits']);
			$template_object->assign("planet_creditsout", NUMBER($planetinfo['credits']));
			$template_object->assign("planet_ratio", $planet_ratio);
			$template_object->assign("planet_max_credits", $planetinfo['max_credits']);
			$template_object->assign("planet_max_creditsout", NUMBER($planetinfo['max_credits']));
			$template_object->assign("planet_credit_multi", $planet_credit_multi);
			$template_object->assign("base_credits", $base_credits);			
			$template_object->assign("l_no_credits", $l_no_credits);
			$template_object->assign("upgrade_cost", $upgrade_cost);
			$template_object->assign("planet_upgrade_factor", $planet_upgrade_factor);
			$template_object->assign("planet_SD_upgrade_factor", $planet_SD_upgrade_factor);
			$template_object->assign("l_creds_to_spend", $l_creds_to_spend);
			$template_object->assign("l_ifyouneedmore", $l_ifyouneedmore);
			$template_object->assign("l_planetary_defense_levels", $l_planetary_defense_levels);
			$template_object->assign("l_cost", $l_cost);
			$template_object->assign("l_current_level", $l_current_level);
			$template_object->assign("l_upgrade", $l_upgrade);
			$template_object->assign("l_overall", $l_overall);
			$template_object->assign("l_planetary_credits", $l_planetary_credits);			
			$template_object->assign("l_fighter", $l_fighter);
			$template_object->assign("l_credits", $l_credits);
			$template_object->assign("l_max_credits", $l_max_credits);
			$template_object->assign("l_sensors", $l_sensors);
			$template_object->assign("l_beams", $l_beams);
			$template_object->assign("l_torp_launch", $l_torp_launch);
			$template_object->assign("l_shields", $l_shields);
			$template_object->assign("l_jammer", $l_jammer);
			$template_object->assign("l_cloak", $l_cloak);
			$template_object->assign("onclick", $onclick);
			$template_object->assign("l_buy", $l_buy);
			$template_object->assign("l_totalcost", $l_totalcost);
			$template_object->assign("planetcloak", $planetinfo['cloak']);
			$template_object->assign("planet_cloak", dropdown("cloak_upgrade",$planetinfo['cloak'], $max_tech_level));
			$template_object->assign("planetjammer", $planetinfo['jammer']);
			$template_object->assign("planet_jammer", dropdown("jammer_upgrade",$planetinfo['jammer'], $max_tech_level));
			$template_object->assign("planetshields", $planetinfo['shields']);
			$template_object->assign("planet_shields", dropdown("shields_upgrade",$planetinfo['shields'], $max_tech_level));
			$minoverall = min($planetinfo['cloak'], min($planetinfo['jammer'], min($planetinfo['shields'], min($planetinfo['torp_launchers'], min($planetinfo['beams'], min($planetinfo['sensors'], $planetinfo['fighter']))))));
			$template_object->assign("minoverall", $minoverall);
			$template_object->assign("planet_overall", dropdown("overall_upgrade",$minoverall, $max_tech_level));
			$template_object->assign("planettorps", $planetinfo['torp_launchers']);
			$template_object->assign("planet_torps", dropdown("torp_launchers_upgrade",$planetinfo['torp_launchers'], $max_tech_level));
			$template_object->assign("planetbeams", $planetinfo['beams']);
			$template_object->assign("planet_beams", dropdown("beams_upgrade",$planetinfo['beams'], $max_tech_level));
			$template_object->assign("planetsensors", $planetinfo['sensors']);
			$template_object->assign("planet_sensors", dropdown("sensors_upgrade",$planetinfo['sensors'], $max_tech_level));
			$template_object->assign("planetfighter", $planetinfo['fighter']);
			$template_object->assign("planet_fighter", dropdown("fighter_upgrade",$planetinfo['fighter'], $max_tech_level));
			$template_object->assign("planetsectordefenseweapons", $planetinfo['sector_defense_weapons']);
			$template_object->assign("planetsector_defense_weapons", dropdown("sector_defense_weapons_upgrade",$planetinfo['sector_defense_weapons'], $max_tech_level));
			$template_object->assign("planetsectordefensesensors", $planetinfo['sector_defense_sensors']);
			$template_object->assign("planetsector_defense_sensors", dropdown("sector_defense_sensors_upgrade",$planetinfo['sector_defense_sensors'], $max_tech_level));
			$template_object->assign("planetsectordefensecloak", $planetinfo['sector_defense_cloak']);
			$template_object->assign("planetsector_defense_cloak", dropdown("sector_defense_cloak_upgrade",$planetinfo['sector_defense_cloak'], $max_tech_level));

			$template_object->assign("planetcloak_normal", $planetinfo['cloak_normal']);
			$template_object->assign("planetjammer_normal", $planetinfo['jammer_normal']);
			$template_object->assign("planetshields_normal", $planetinfo['shields_normal']);
			$template_object->assign("planettorps_normal", $planetinfo['torp_launchers_normal']);
			$template_object->assign("planetbeams_normal", $planetinfo['beams_normal']);
			$template_object->assign("planetsensors_normal", $planetinfo['sensors_normal']);
			$template_object->assign("planetfighter_normal", $planetinfo['fighter_normal']);
			$template_object->assign("planetsectordefenseweapons_normal", $planetinfo['sector_defense_weapons_normal']);
			$template_object->assign("planetsectordefensesensors_normal", $planetinfo['sector_defense_sensors_normal']);
			$template_object->assign("planetsectordefensecloak_normal", $planetinfo['sector_defense_cloak_normal']);
			$template_object->assign("l_planet_repair", $l_planet_repair);
			$template_object->assign("max_tech_level", $max_tech_level);

			$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
			$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
			$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);

			$template_object->assign("planet_id", $planet_id);
			$template_object->assign("l_clickme", $l_clickme);
			$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
			$template_object->assign("l_igb_term", $l_igb_term);
			$template_object->assign("allow_ibank", $allow_ibank);
			$template_object->assign("l_by_placebounty", $l_by_placebounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/planet_owneddefenses.tpl");
			include ("footer.php");
			die();
		}

?>