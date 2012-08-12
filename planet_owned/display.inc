<?php
$lastvisited_date = date("Y-m-d H:i:s");
$result = $db->Execute("UPDATE {$db_prefix}planets SET last_visited='$lastvisited_date' WHERE owner=$playerinfo[player_id] and planet_id=$planetinfo[planet_id]");

$template_object->assign("planet_id", $planet_id);

$days_since = sprintf("%01.2f", (strtotime(date("Y-m-d H:i:s")) - strtotime($planetinfo['last_visited'])) / 86400);
$last_visited_formatted = date($local_date_full_format, strtotime($planetinfo['last_visited']));

$l_planet_lastvisited = str_replace("[date]", $last_visited_formatted, $l_planet_lastvisited);
$l_planet_lastvisited = str_replace("[days]", $days_since, $l_planet_lastvisited);

$template_object->assign("l_planet_lastvisited", $l_planet_lastvisited);

$planetavg = $planetinfo['fighter'] + $planetinfo['sensors'] + $planetinfo['beams'] + $planetinfo['torp_launchers'] + $planetinfo['shields'] + $planetinfo['cloak'];
$maximum_colonists = $colonist_limit + floor($colonist_tech_add * floor($planetavg / 6));
$planetavg += ($planetinfo['colonists'] / $maximum_colonists) * $max_tech_level;
$planetavg =  floor((($planetavg / 7) / $max_tech_level) * 10 );

$planetlevel = max(0, min(9, $planetavg));

if($planetinfo['ore_planet'] >= 1 && $planetinfo['organics_planet'] >= 1)
{
	$planettype = "oo";
}

if($planetinfo['ore_planet'] >= 1 && $planetinfo['organics_planet'] < 1)
{
	$planettype = "oo-";
}

if($planetinfo['ore_planet'] < 1 && $planetinfo['organics_planet'] >= 1)
{
	$planettype = "o-o";
}

if($planetinfo['ore_planet'] < 1 && $planetinfo['organics_planet'] < 1)
{
	$planettype = "o-o-";
}

$template_object->assign("planettype", $planettype . (string)(max(0, min(10, $planetlevel)) + 1));

if (empty($planetinfo['name']))
{
	$l_planet_unnamed=str_replace("[name]","<b><font color='yellow'>$ownerinfo[character_name]</font></b>",$l_planet_unnamed);
	$l_planet_unnamed=str_replace("[sector]","<b><font color='#79f487'>$sectorinfo[sector_name]</font></b>",$l_planet_unnamed);
	$l_planet_unnamed=str_replace(", ","<br>",$l_planet_unnamed);
//	$l_planet_unnamed=str_replace(".","",$l_planet_unnamed);
	if ($planetinfo['base'] == "Y")
 		{
		$l_planet_unnamed.= " $l_planet_based";
	}
	$planetname = $l_planet_unnamed;
}
else
{
	$l_planet_named=str_replace("[name]","<b><font color='yellow'>$ownerinfo[character_name]</font></b>",$l_planet_named);
	$l_planet_named=str_replace("[planetname]","<b><font color='#87d8ec'>$planetinfo[name]</font></b>",$l_planet_named);
	if ($planetinfo['base'] == "Y")
	{
		$l_planet_named.= " $l_planet_based";
	}
	$l_planet_named=str_replace("[sector]","<b><font color='#79f487'>$sectorinfo[sector_name]</font></b>",$l_planet_named);
	$l_planet_named=str_replace(", ","<br>",$l_planet_named);
//	$l_planet_named=str_replace(".","",$l_planet_named);
	$planetname = $l_planet_named;
}
$template_object->assign("planetname", $planetname);

$l_planet_name_link = "<a href='planet.php?planet_id=$planet_id&command=name'>" . $l_planet_name_link . "</a>";
$l_planet_name =str_replace("[name]",$l_planet_name_link,$l_planet_name2);
$template_object->assign("l_planet_name", $l_planet_name);

$template_object->assign("allow_genesis_destroy", $allow_genesis_destroy);
if ($allow_genesis_destroy)
{
	$template_object->assign("l_planet_destroyplanet", $l_planet_destroyplanet);
	$template_object->assign("l_planet_warning", $l_planet_warning);
}

$l_planet_readlog_link="<a href=log.php>" . $l_planet_readlog_link ."</a>";
$l_planet_readlog=str_replace("[View]",$l_planet_readlog_link,$l_planet_readlog);
$template_object->assign("l_planet_readlog", $l_planet_readlog);

$l_planet_leave_link = "<a href='planet.php?planet_id=$planet_id&command=leave'>" . $l_planet_leave_link . "</a>";
$l_planet_leave=str_replace("[leave]",$l_planet_leave_link,$l_planet_leave);

$l_planet_land_link = "<a href='planet.php?planet_id=$planet_id&command=land'>" . $l_planet_land_link . "</a>";
$l_planet_land=str_replace("[land]",$l_planet_land_link,$l_planet_land);

if ($shipinfo['on_planet'] == 'Y' && $shipinfo['planet_id'] == $planet_id)
{
	$template_object->assign("l_planet_land", $l_planet_leave);
}
else
{
	$template_object->assign("l_planet_land", $l_planet_land);
}

if ($shipinfo['on_planet'] == 'Y' && $shipinfo['planet_id'] == $planet_id)
{
	$logout_link ="<a href=logout.php>$l_planet_logout1</a>";
	$l_planet_logout2=str_replace("[logout]",$logout_link,$l_planet_logout2);
	$template_object->assign("l_planet_logout2", $l_planet_logout2);
	$template_object->assign("logout_link", $logout_link);
	$template_object->assign("onplanet", 1);
}else{
	$template_object->assign("l_planet_logout2", "");
	$template_object->assign("logout_link", "");
	$template_object->assign("onplanet", 0);
}

$l_planet_transfer_link="<a href='planet.php?planet_id=$planet_id&command=transfer'>" . $l_planet_transfer_link . "</a>";
$l_planet_transfer=str_replace("[transfer]",$l_planet_transfer_link,$l_planet_transfer);
$template_object->assign("l_planet_transfer_link", $l_planet_transfer_link);
$template_object->assign("planetbased", $planetinfo['base']);
$template_object->assign("l_main_shipyard1", $l_main_shipyard1);
$template_object->assign("l_main_shipyard2", $l_main_shipyard2);
$template_object->assign("l_planet_upgrade", $l_planet_upgrade);
$template_object->assign("l_planetary_defense_levels", $l_planetary_defense_levels);
$template_object->assign("l_turns_have", $l_turns_have);
$template_object->assign("playerturns", NUMBER($playerinfo['turns']));
$template_object->assign("l_planetary_armorpts", $l_planetary_armorpts);
$template_object->assign("planetarmorpts", NUMBER($planetinfo['armor_pts']));
$template_object->assign("torpprod", $planetinfo['prod_torp']);
$template_object->assign("l_torps", $l_torps);
$template_object->assign("torptotal", NUMBER($planetinfo['torps']));
$template_object->assign("fighterprod", $planetinfo['prod_fighters']);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("fightertotal", NUMBER($planetinfo['fighters']));
$template_object->assign("energyprod", $planetinfo['prod_energy']);
$template_object->assign("l_energy", $l_energy);
$template_object->assign("energytotal", NUMBER($planetinfo['energy']));
$template_object->assign("oreprod", $planetinfo['prod_ore']);
$template_object->assign("l_ore", $l_ore);
$template_object->assign("oretotal", NUMBER($planetinfo['ore']));
$template_object->assign("organicsprod", $planetinfo['prod_organics']);
$template_object->assign("l_organics", $l_organics);
$template_object->assign("organicstotal", NUMBER($planetinfo['organics']));
$template_object->assign("goodsprod", $planetinfo['prod_goods']);
$template_object->assign("l_goods", $l_goods);
$template_object->assign("goodstotal", NUMBER($planetinfo['goods']));
$template_object->assign("creditprod", 100 - $planetinfo['prod_torp'] - $planetinfo['prod_fighters'] - $planetinfo['prod_energy'] - $planetinfo['prod_ore'] - $planetinfo['prod_organics'] - $planetinfo['prod_goods'] - $planetinfo['prod_research'] - $planetinfo['prod_build'] - $planetinfo['prod_special']);
$template_object->assign("researchprod", $planetinfo['prod_research']);
$template_object->assign("l_pr_research", $l_pr_research);
$template_object->assign("buildprod", $planetinfo['prod_build']);
$template_object->assign("l_pr_build", $l_pr_build);

$template_object->assign("prod_special", $planetinfo['prod_special']);
$template_object->assign("special_name", ucwords($planetinfo['special_name']));
$template_object->assign("special_amount", NUMBER($planetinfo['special_amount']));

$template_object->assign("sg_sector", $sectorinfo['sg_sector']);

if($planetinfo['use_age'] > 0)
{
	$template_object->assign("energypercent", "N/A");
	$template_object->assign("orepercent", "N/A");
	$template_object->assign("organicspercent", "N/A");
	$template_object->assign("goodspercent", "N/A");
}
else
{
	$template_object->assign("energypercent", (string)($planetinfo['energy_planet'] * 100) . "%");
	$template_object->assign("orepercent", (string)($planetinfo['ore_planet'] * 100) . "%");
	$template_object->assign("organicspercent", (string)($planetinfo['organics_planet'] * 100) . "%");
	$template_object->assign("goodspercent", (string)($planetinfo['goods_planet'] * 100) . "%");
}

$res = $db->execute("SELECT COUNT(dig_id) AS total FROM {$db_prefix}dignitary WHERE planet_id = '$planet_id' AND owner_id = '$playerinfo[player_id]' ");
$n = $res->fields['total'];
$res->close();
$template_object->assign("l_dig", $l_dig);
$template_object->assign("digtotal", $n);

$res = $db->execute("SELECT COUNT(spy_id) AS total FROM {$db_prefix}spies WHERE planet_id = '$planet_id' AND owner_id = '$playerinfo[player_id]' ");
$n = $res->fields['total'];
$res->close();
$template_object->assign("l_spy", $l_spy);
$template_object->assign("spytotal", $n);

$template_object->assign("l_colonists", $l_colonists);
$template_object->assign("colonisttotal", NUMBER($planetinfo['colonists']));
$template_object->assign("l_credits", $l_credits);
$template_object->assign("credittotal", NUMBER($planetinfo['credits']));
$template_object->assign("max_credits", NUMBER($planetinfo['max_credits']));
$template_object->assign("l_planet_interest", $l_planet_interest);
$template_object->assign("l_planet_update", $l_planet_update);
$template_object->assign("l_planet_repair", $l_planet_repair);

$template_object->assign("l_planetary_fighter", $l_planetary_fighter);
$template_object->assign("l_level", $l_level);
$template_object->assign("l_planetary_sensors", $l_planetary_sensors);
$template_object->assign("l_planetary_beams", $l_planetary_beams);
$template_object->assign("l_planetary_torp_launch", $l_planetary_torp_launch);
$template_object->assign("l_planetary_shields", $l_planetary_shields);
$template_object->assign("l_planetary_jammer", $l_planetary_jammer);
$template_object->assign("l_planetary_cloak", $l_planetary_cloak);
$template_object->assign("l_planetary_armor", $l_planetary_armor);
$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);
$template_object->assign("l_max", $l_max);

$template_object->assign("l_damaged", $l_damaged);
$template_object->assign("l_normal", $l_normal);

$template_object->assign("planetfighter", $planetinfo['fighter']);
$template_object->assign("planetsensors", $planetinfo['sensors']);
$template_object->assign("planetbeams", $planetinfo['beams']);
$template_object->assign("planettorps", $planetinfo['torp_launchers']);
$template_object->assign("planetshields", $planetinfo['shields']);
$template_object->assign("planetjammer", $planetinfo['jammer']);
$template_object->assign("planetcloak", $planetinfo['cloak']);
$template_object->assign("planetarmor", $planetinfo['armor']);
$template_object->assign("planetsector_defense_weapons", $planetinfo['sector_defense_weapons']);
$template_object->assign("planetsector_defense_sensors", $planetinfo['sector_defense_sensors']);
$template_object->assign("planetsector_defense_cloak", $planetinfo['sector_defense_cloak']);

$template_object->assign("planetfighter_normal", $planetinfo['fighter_normal']);
$template_object->assign("planetsensors_normal", $planetinfo['sensors_normal']);
$template_object->assign("planetbeams_normal", $planetinfo['beams_normal']);
$template_object->assign("planettorps_normal", $planetinfo['torp_launchers_normal']);
$template_object->assign("planetshields_normal", $planetinfo['shields_normal']);
$template_object->assign("planetjammer_normal", $planetinfo['jammer_normal']);
$template_object->assign("planetcloak_normal", $planetinfo['cloak_normal']);
$template_object->assign("planetarmor_normal", $planetinfo['armor_normal']);
$template_object->assign("planetsector_defense_weapons_normal", $planetinfo['sector_defense_weapons_normal']);
$template_object->assign("planetsector_defense_sensors_normal", $planetinfo['sector_defense_sensors_normal']);
$template_object->assign("planetsector_defense_cloak_normal", $planetinfo['sector_defense_cloak_normal']);

$template_object->assign("max_tech_level", $max_tech_level);
$template_object->assign("fighterbar", MakeBars($planetinfo['fighter'], $max_tech_level, "damage"));
$template_object->assign("sensorbar", MakeBars($planetinfo['sensors'], $max_tech_level, "damage"));
$template_object->assign("beambar", MakeBars($planetinfo['beams'], $max_tech_level, "damage"));
$template_object->assign("torpbar", MakeBars($planetinfo['torp_launchers'], $max_tech_level, "damage"));
$template_object->assign("shieldbar", MakeBars($planetinfo['shields'], $max_tech_level, "damage"));
$template_object->assign("jammerbar", MakeBars($planetinfo['jammer'], $max_tech_level, "damage"));
$template_object->assign("cloakbar", MakeBars($planetinfo['cloak'], $max_tech_level, "damage"));
$template_object->assign("armorbar", MakeBars($planetinfo['armor'], $max_tech_level, "damage"));
$template_object->assign("sector_defense_weaponsbar", MakeBars($planetinfo['sector_defense_weapons'], $max_tech_level, "damage"));
$template_object->assign("sector_defense_sensorsbar", MakeBars($planetinfo['sector_defense_sensors'], $max_tech_level, "damage"));
$template_object->assign("sector_defense_cloakbar", MakeBars($planetinfo['sector_defense_cloak'], $max_tech_level, "damage"));

$template_object->assign("fighterbar_normal", MakeBars($planetinfo['fighter_normal'], $max_tech_level, "normal"));
$template_object->assign("sensorbar_normal", MakeBars($planetinfo['sensors_normal'], $max_tech_level, "normal"));
$template_object->assign("beambar_normal", MakeBars($planetinfo['beams_normal'], $max_tech_level, "normal"));
$template_object->assign("torpbar_normal", MakeBars($planetinfo['torp_launchers_normal'], $max_tech_level, "normal"));
$template_object->assign("shieldbar_normal", MakeBars($planetinfo['shields_normal'], $max_tech_level, "normal"));
$template_object->assign("jammerbar_normal", MakeBars($planetinfo['jammer_normal'], $max_tech_level, "normal"));
$template_object->assign("cloakbar_normal", MakeBars($planetinfo['cloak_normal'], $max_tech_level, "normal"));
$template_object->assign("armorbar_normal", MakeBars($planetinfo['armor_normal'], $max_tech_level, "normal"));
$template_object->assign("sector_defense_weaponsbar_normal", MakeBars($planetinfo['sector_defense_weapons_normal'], $max_tech_level, "normal"));
$template_object->assign("sector_defense_sensorsbar_normal", MakeBars($planetinfo['sector_defense_sensors_normal'], $max_tech_level, "normal"));
$template_object->assign("sector_defense_cloakbar_normal", MakeBars($planetinfo['sector_defense_cloak_normal'], $max_tech_level, "normal"));

$template_object->assign("planetbase", $planetinfo['base']);
if ($planetinfo['base'] == "N")
{
	$l_planet_bbase_link = "<a href='planet.php?planet_id=$planet_id&command=base'>" . $l_planet_bbase_link . "</a>";
	$l_planet_bbase=str_replace("[build]",$l_planet_bbase_link,$l_planet_bbase);
	$template_object->assign("l_planet_bbase", $l_planet_bbase);
}else{
	$template_object->assign("l_planet_bbase", "&nbsp;");
}

if ($playerinfo['player_id'] == $planetinfo['owner'])
{
	if ($playerinfo['team'] <> 0)
	{
		if ($planetinfo['team'] == 0)
		{
			$l_planet_mteam_linkC = "<a href='team.php?planet_id=$planet_id&action=planetteam'>" . $l_planet_mteam_linkC . "</a>";
			$l_planet_mteam=str_replace("[planet]",$l_planet_mteam_linkC,$l_planet_mteam);
			$template_object->assign("l_planet_mteam", $l_planet_mteam);
		}
		else
		{
			$l_planet_mteam_linkP = "<a href='team.php?planet_id=$planet_id&action=planetpersonal'>" . $l_planet_mteam_linkP . "</a>";
			$l_planet_mteam=str_replace("[planet]",$l_planet_mteam_linkP,$l_planet_mteam);
			$template_object->assign("l_planet_mteam", $l_planet_mteam);
		}
	}
}

if ($playerinfo['player_id'] == $planetinfo['owner'])
{
	if ($planetinfo['team_cash'] == "Y")
	{
		$template_object->assign("cashstatus", $l_planet_teamcash);
	}
	else
	{
		$template_object->assign("cashstatus", $l_planet_not_teamcash);
	}
	$l_planet_tcash_link="<a href='planet.php?planet_id=$planet_id&command=teamcash'>" . $l_planet_tcash_link ."</a>";
	$l_planet_tcash=str_replace("[teamcash]",$l_planet_tcash_link,$l_planet_tcash);
	$template_object->assign("l_planet_tcash", $l_planet_tcash);
}

$template_object->assign("l_spy_cleanupplanet", $l_spy_cleanupplanet);
$template_object->assign("l_clickme", $l_clickme);

if ($enable_spies)
{
	$template_object->assign("spycleaner", $planetinfo['planet_id']);
}
else
{
	$template_object->assign("spycleaner", 0);
}

if ($planetinfo['base'] == "Y")
{	 
	$template_object->assign("digtransfer", $planet_id);
}else{
	$template_object->assign("digtransfer", 0);
}

$template_object->assign("l_igb_term", $l_igb_term);
if ($allow_ibank)
{
	$template_object->assign("igbplanet", $planet_id);
}else{
	$template_object->assign("igbplanet", 0);
}
$template_object->assign("l_by_placebounty", $l_by_placebounty);

$result_auto = $db->Execute("SELECT * FROM {$db_prefix}autotrades WHERE owner=$playerinfo[player_id] and planet_id=$planetinfo[planet_id]");
$num_traderoute = $result_auto->RecordCount();

$template_object->assign("num_traderoute", $num_traderoute);

if($num_traderoute != 0){
	$traderoute = $result_auto->fields;
	$routecount = 0;
	$l_planet_autotrade .= " - $l_hull: <font color='yellow'>$planetinfo[cargo_hull]</font>&nbsp;&nbsp;$l_planet_cargocapacity<font color='yellow'>".NUMBER(NUM_HOLDS($planetinfo['cargo_hull']))."</font> - $l_power: <font color='yellow'>$planetinfo[cargo_power]</font>&nbsp;&nbsp;$l_planet_cargocapacity<font color='yellow'>".NUMBER(NUM_ENERGY($planetinfo['cargo_power']))."</font><br>";
	$template_object->assign("cargohullsize", $planetinfo['cargo_hull']);
	$template_object->assign("l_planet_cargocapacity", $l_planet_cargocapacity);
	$template_object->assign("cargototalholds", NUMBER(NUM_HOLDS($planetinfo['cargo_hull'])));
	$template_object->assign("l_hull", $l_hull);
	$template_object->assign("l_power", $l_power);
	$template_object->assign("cargopowersize", $planetinfo['cargo_power']);
	$template_object->assign("cargototalpower", NUMBER(NUM_ENERGY($planetinfo['cargo_power'])));

	$res5 = $db->Execute("SELECT sector_name FROM {$db_prefix}universe where sector_id='$traderoute[port_id_goods]'");
	db_op_result($res5,__LINE__,__FILE__);
	$destinationport = $res5->fields['sector_name'];
	$template_object->assign("cargoportidgoods", $destinationport);
	$template_object->assign("l_goods", $l_goods);
	if($traderoute['port_id_goods'] != 0){
		$temp = str_replace("[source_type]","<b><font color='yellow'>$l_goods</font></b>",$l_planet_autotradetype);
		if($traderoute['goods_price'] != 0)
			$tradeprice = " @ <font color='yellow'>$traderoute[goods_price]c</font>";
		else $tradeprice = "";
		$l_planet_autotrade .= str_replace("[dest_id]","<b><font color='#87d8ec'>$destinationport</font>$tradeprice</b>",$temp);
		$template_object->assign("goodstradeprice", $tradeprice);
		$routecount++;
	}

	$res5 = $db->Execute("SELECT sector_name FROM {$db_prefix}universe where sector_id='$traderoute[port_id_ore]'");
	db_op_result($res5,__LINE__,__FILE__);
	$destinationport = $res5->fields['sector_name'];
	$template_object->assign("cargoportidore", $destinationport);
	$template_object->assign("l_ore", $l_ore);
	if($traderoute['port_id_ore'] != 0){
		$temp = str_replace("[source_type]","<b><font color='yellow'>$l_ore</font></b>",$l_planet_autotradetype);
		if($traderoute['ore_price'] != 0)
			$tradeprice = " @ <font color='yellow'>$traderoute[ore_price]c</font>";
		else $tradeprice = "";
		$l_planet_autotrade .= str_replace("[dest_id]","<b><font color='#87d8ec'>$destinationport</font>$tradeprice</b>",$temp);
		$template_object->assign("oretradeprice", $tradeprice);
		$routecount++;
		if($routecount == 2)
			$l_planet_autotrade .= "-<br>";
	}

	$res5 = $db->Execute("SELECT sector_name FROM {$db_prefix}universe where sector_id='$traderoute[port_id_organics]'");
	db_op_result($res5,__LINE__,__FILE__);
	$destinationport = $res5->fields['sector_name'];
	$template_object->assign("cargoportidorganics", $destinationport);
	$template_object->assign("l_organics", $l_organics);
	if($traderoute['port_id_organics'] != 0){
		$temp = str_replace("[source_type]","<b><font color='yellow'>$l_organics</font></b>",$l_planet_autotradetype);
		if($traderoute['organics_price'] != 0)
		 	$tradeprice = " @ <font color='yellow'>$traderoute[organics_price]c</font>";
		else $tradeprice = "";
		$l_planet_autotrade .= str_replace("[dest_id]","<b><font color='#87d8ec'>$destinationport</font>$tradeprice</b>",$temp);
		$template_object->assign("organicstradeprice", $tradeprice);
		$routecount++;
		if($routecount == 2)
			$l_planet_autotrade .= "-<br>";
	}

	$res5 = $db->Execute("SELECT sector_name FROM {$db_prefix}universe where sector_id='$traderoute[port_id_energy]'");
	db_op_result($res5,__LINE__,__FILE__);
	$destinationport = $res5->fields['sector_name'];
	$template_object->assign("cargoportidenergy", $destinationport);
	$template_object->assign("l_energy", $l_energy);
	if($traderoute['port_id_energy'] != 0){
		$temp = str_replace("[source_type]","<b><font color='yellow'>$l_energy</font></b>",$l_planet_autotradetype);
		if($traderoute['energy_price'] != 0)
		 	$tradeprice = " @ <font color='yellow'>$traderoute[energy_price]c</font>";
		else $tradeprice = "";
		$l_planet_autotrade .= str_replace("[dest_id]","<b><font color='#87d8ec'>$destinationport</font>$tradeprice</b>",$temp);
		$routecount++;
		$template_object->assign("energytradeprice", $tradeprice);
		if($routecount == 2)
			$l_planet_autotrade .= "-<br>";
	}

	$res5 = $db->Execute("SELECT sector_name FROM {$db_prefix}universe where sector_id='$traderoute[port_id_colonist]'");
	db_op_result($res5,__LINE__,__FILE__);
	$destinationport = $res5->fields['sector_name'];
	$template_object->assign("cargoportidcolonists", $destinationport);
	$template_object->assign("l_colonists", $l_colonists);
	if($traderoute['port_id_colonist'] != 0){
		$temp = str_replace("[source_type]","<b><font color='yellow'>$l_colonists</font></b>",$l_planet_autotradetype);
		if($traderoute['colonist_price'] != 0)
		 	$tradeprice = " @ <font color='yellow'>$traderoute[colonist_price]c</font>";
		else $tradeprice = "";
		$l_planet_autotrade .= str_replace("[dest_id]","<b><font color='#87d8ec'>$destinationport</font>$tradeprice</b>",$temp);
		$routecount++;
		$template_object->assign("colonisttradeprice", $tradeprice);
		if($routecount == 2)
			$l_planet_autotrade .= "-<br>";
	}

	if($routecount != 2)
		$l_planet_autotrade .= "-<br>";

	$template_object->assign("l_planet_cargocredits", $l_planet_cargocredits);
	$template_object->assign("tradecredits", number($traderoute['current_trade']));
	$template_object->assign("traderoute_id", $traderoute['traderoute_id']);
	$template_object->assign("l_planet_autotradedelete", $l_planet_autotradedelete);
	$template_object->assign("l_planet_upgradecargo", $l_planet_upgradecargo);
	$template_object->assign("l_clickme", $l_clickme);

	$l_planet_autotrade .= "$l_planet_cargocredits <font color='yellow'>".number($traderoute['current_trade'])."</font><br>";
	$l_planet_autotrade .= "<a href='planet.php?planet_id=$planet_id&traderoute_id=$traderoute[traderoute_id]&command=deletetrade'>$l_planet_autotradedelete</a><br>$l_planet_upgradecargo <a href='planet.php?planet_id=$planet_id&command=upgradecargo'>$l_clickme</a>.</font>";
	$cargolevel = floor($planetinfo['cargo_hull'] / ceil($max_tech_level / 6));
	$cargoimage="<img src='templates/".$templatename."images/cargo/$cargolevel.png' border='0'>";
}else{
	$l_planet_autotrade = $l_planet_noautotrade."&nbsp;-&nbsp;<a href='planet.php?planet_id=$planet_id&command=addtrade'>$l_planet_autotradeadd</a><br>$l_planet_purchasecargo <a href='planet.php?planet_id=$planet_id&command=buycargoship'>$l_clickme</a>.";
	$template_object->assign("l_planet_autotradeadd", $l_planet_autotradeadd);
	$template_object->assign("l_planet_purchasecargo", $l_planet_purchasecargo);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("planetcargohull", $planetinfo['cargo_hull']);
	if($planetinfo['cargo_hull'] == 0){
		$l_planet_autotrade = $l_planet_noautotrade."&nbsp;-&nbsp;<a href='planet.php?planet_id=$planet_id&command=addtrade'>$l_planet_autotradeadd</a><br>$l_planet_purchasecargo <a href='planet.php?planet_id=$planet_id&command=buycargoship'>$l_clickme</a>.";
		$template_object->assign("l_planet_autotradeadd", $l_planet_autotradeadd);
		$template_object->assign("l_planet_purchasecargo", $l_planet_purchasecargo);
		$template_object->assign("l_clickme", $l_clickme);
		$cargoimage="<img src='templates/".$templatename."images/cargo/empty.png' border='0'>";
	}else{
		$l_planet_autotrade = $l_planet_noautotrade."&nbsp;-&nbsp;<a href='planet.php?planet_id=$planet_id&command=addtrade'>$l_planet_autotradeadd</a><br>$l_hull: <font color='yellow'>$planetinfo[cargo_hull]</font>&nbsp;&nbsp;$l_planet_cargocapacity<font color='yellow'>".NUMBER(NUM_HOLDS($planetinfo['cargo_hull']))."</font> - $l_power: <font color='yellow'>$planetinfo[cargo_power]</font>&nbsp;&nbsp;$l_planet_cargocapacity<font color='yellow'>".NUMBER(NUM_HOLDS($planetinfo['cargo_power']))."</font><br>$l_planet_upgradecargo <a href='planet.php?planet_id=$planet_id&command=upgradecargo'>$l_clickme</a>.";
		$template_object->assign("cargohullsize", $planetinfo['cargo_hull']);
		$template_object->assign("l_planet_cargocapacity", $l_planet_cargocapacity);
		$template_object->assign("cargototalholds", NUMBER(NUM_HOLDS($planetinfo['cargo_hull'])));
		$template_object->assign("l_hull", $l_hull);
		$template_object->assign("l_power", $l_power);
		$template_object->assign("cargopowersize", $planetinfo['cargo_power']);
		$template_object->assign("cargototalpower", NUMBER(NUM_ENERGY($planetinfo['cargo_power'])));
		$template_object->assign("l_planet_autotradeadd", $l_planet_autotradeadd);
		$template_object->assign("l_planet_upgradecargo", $l_planet_upgradecargo);
		$template_object->assign("l_clickme", $l_clickme);
		$cargolevel = floor($planetinfo['cargo_hull'] / ceil($max_tech_level / 6));
		$cargoimage="<img src='templates/".$templatename."images/cargo/$cargolevel.png' border='0'>";
	}
}
$result_auto->close();

$template_object->assign("allow_autotrades", $allow_autotrades);
$template_object->assign("cargoimage", $cargoimage);
$template_object->assign("l_planet_autotrade", $l_planet_autotrade);
$planet_ratio=round(($planetinfo['credits']/$planetinfo['max_credits'])*100);
$template_object->assign("l_planet_hidden_credits", $l_planet_hidden_credits);		
$template_object->assign("captured_countdown", $planetinfo['captured_countdown']);		
$template_object->assign("l_max_credits", $l_max_credits);		
$template_object->assign("planet_ratio", $planet_ratio);	

$artifact_description = array();
$artifact_id = array();
$artifactimage = array();
$artifactname = array();
$artifactcount = 0;
$result4 = $db->Execute(" SELECT artifact_id, artifact_type, cloak, scoremax FROM {$db_prefix}artifacts WHERE sector_id=$shipinfo[sector_id] and on_planet_id=$planetinfo[planet_id]");

while (!$result4->EOF)
{
	$row = $result4->fields;
	if($row['scoremax'] == 0 || $playerinfo['score'] < $row['scoremax'])
	{
		$success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], 1);

		$roll = mt_rand(1, 100);
		if ($roll < $success)
		{
			if(!class_exists($row['artifact_type'])){
				include ("class/artifacts/" . $row['artifact_type'] . ".inc");
			}
			$artifact_object = new $row['artifact_type'];

			$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $artifact_object->class . "'");
	   		db_op_result($res,__LINE__,__FILE__);
			if($res->fields['total'] < $artifact_object->pieces)
			{
				$artifactname[$artifactcount] = $artifact_object->classname;
				$artifact_description[$artifactcount] = addslashes($artifact_object->description);
				$artifact_id[$artifactcount] = $row['artifact_id'];
				$artifactimage[$artifactcount] = $row['artifact_type'];
				$artifactcount++;
			}
		}
	}
	$result4->MoveNext();
}

$template_object->assign("artifactimage", $artifactimage);
$template_object->assign("artifact_id", $artifact_id);
$template_object->assign("artifact_description", $artifact_description);
$template_object->assign("artifactname", $artifactname);
$template_object->assign("artifactcount", $artifactcount);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."planet_owned/planet_display.tpl");
include ("footer.php");

?>