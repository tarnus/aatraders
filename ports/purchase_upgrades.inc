<?php
include ("globals/isLoanPending.inc");

get_post_ifset("fighter_number, torpedo_number, armor_number, total_cost, total_cost2, hull_upgrade, engine_upgrade, power_upgrade, fighter_upgrade, sensors_upgrade, beams_upgrade, armor_upgrade, cloak_upgrade, ecm_upgrade, torp_launchers_upgrade, shields_upgrade");

$l_port_welcome = str_replace("[player]", $playerinfo['character_name'], str_replace("[sectorname]", $sectorinfo['sector_name'], $l_port_welcome));
$template_object->assign("l_port_welcome", $l_port_welcome);
$template_object->assign("l_upgrade", $l_upgrade);

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_trade_turnneed);
	$template_object->assign("error_msg2", "<A HREF=port.php>$l_clickme</A> $l_port_returntospecial");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

if ($sectorinfo['port_type'] == "upgrades")
{
	if (isLoanPending($playerinfo['player_id']))
	{
		$template_object->assign("error_msg", $l_port_loannotrade);
		$template_object->assign("error_msg2", "<A HREF=igb.php>$l_igb_term</a>");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}

	$hull_upgrade_cost = 0;
	if($shipinfo['hull'] == $shipinfo['hull_normal'])
	{
		if ($hull_upgrade > $classinfo['maxhull'])
		{
			$hull_upgrade = $classinfo['maxhull'];
		}

		if ($hull_upgrade < $classinfo['minhull'])
		{
			$hull_upgrade = $classinfo['minhull'];
		}

		if ($hull_upgrade > $shipinfo['hull_normal'])
		{
			$hull_upgrade_cost = phpChangeDelta($hull_upgrade, $shipinfo['hull_normal']);
		}
	}
	else
	{
		$hull_upgrade = $shipinfo['hull_normal'];
	}

	$engine_upgrade_cost = 0;
	if($shipinfo['engines'] == $shipinfo['engines_normal'])
	{
		if ($engine_upgrade > $classinfo['maxengines'])
		{
			$engine_upgrade = $classinfo['maxengines'];
		}

		if ($engine_upgrade < $classinfo['minengines'])
		{
			$engine_upgrade = $classinfo['minengines'];
		}

		if ($engine_upgrade > $shipinfo['engines_normal'])
		{
			$engine_upgrade_cost = phpChangeDelta($engine_upgrade, $shipinfo['engines_normal']);
		}
	}
	else
	{
		$engine_upgrade = $shipinfo['engines_normal'];
	}

	$power_upgrade_cost = 0;
	if($shipinfo['power'] == $shipinfo['power_normal'])
	{
		if ($power_upgrade > $classinfo['maxpower'])
		{
			$power_upgrade = $classinfo['maxpower'];
		}

		if ($power_upgrade < $classinfo['minpower'])
		{
			$power_upgrade = $classinfo['minpower'];
		}

		if ($power_upgrade > $shipinfo['power_normal'])
		{
			$power_upgrade_cost = phpChangeDelta($power_upgrade, $shipinfo['power_normal']);
		}
	}
	else
	{
		$power_upgrade = $shipinfo['power_normal'];
	}

	$fighter_upgrade_cost = 0;
	if($shipinfo['fighter'] == $shipinfo['fighter_normal'])
	{
		if ($fighter_upgrade > $classinfo['maxfighter'])
		{
			$fighter_upgrade = $classinfo['maxfighter'];
		}

		if ($fighter_upgrade < $classinfo['minfighter'])
		{
			$fighter_upgrade = $classinfo['minfighter'];
		}

		if ($fighter_upgrade > $shipinfo['fighter_normal'])
		{
			$fighter_upgrade_cost = phpChangeDelta($fighter_upgrade, $shipinfo['fighter_normal']);
		}
	}
	else
	{
		$fighter_upgrade = $shipinfo['fighter_normal'];
	}

	$sensors_upgrade_cost = 0;
	if($shipinfo['sensors'] == $shipinfo['sensors_normal'])
	{
		if ($sensors_upgrade > $classinfo['maxsensors'])
		{
			$sensors_upgrade = $classinfo['maxsensors'];
		}

		if ($sensors_upgrade < $classinfo['minsensors'])
		{
			$sensors_upgrade = $classinfo['minsensors'];
		}

		if ($sensors_upgrade > $shipinfo['sensors_normal'])
		{
			$sensors_upgrade_cost = phpChangeDelta($sensors_upgrade, $shipinfo['sensors_normal']);
		}
	}
	else
	{
		$sensors_upgrade = $shipinfo['sensors_normal'];
	}

	$beams_upgrade_cost = 0;
	if($shipinfo['beams'] == $shipinfo['beams_normal'])
	{
		if ($beams_upgrade > $classinfo['maxbeams'])
		{
			$beams_upgrade = $classinfo['maxbeams'];
		}

		if ($beams_upgrade < $classinfo['minbeams'])
		{
			$beams_upgrade = $classinfo['minbeams'];
		}

		if ($beams_upgrade > $shipinfo['beams_normal'])
		{
			$beams_upgrade_cost = phpChangeDelta($beams_upgrade, $shipinfo['beams_normal']);
		}
	}
	else
	{
		$beams_upgrade = $shipinfo['beams_normal'];
	}

	$armor_upgrade_cost = 0;
	if($shipinfo['armor'] == $shipinfo['armor_normal'])
	{
		if ($armor_upgrade > $classinfo['maxarmor'])
		{
			$armor_upgrade = $classinfo['maxarmor'];
		}

		if ($armor_upgrade < $classinfo['minarmor'])
		{
			$armor_upgrade = $classinfo['minarmor'];
		}

		if ($armor_upgrade > $shipinfo['armor_normal'])
		{
			$armor_upgrade_cost = phpChangeDelta($armor_upgrade, $shipinfo['armor_normal']);
		}
	}
	else
	{
		$armor_upgrade = $shipinfo['armor_normal'];
	}

	$cloak_upgrade_cost = 0;
	if($shipinfo['cloak'] == $shipinfo['cloak_normal'])
	{
		if ($cloak_upgrade > $classinfo['maxcloak'])
		{
			$cloak_upgrade = $classinfo['maxcloak'];
		}

		if ($cloak_upgrade < $classinfo['mincloak'])
		{
			$cloak_upgrade = $classinfo['mincloak'];
		}

		if ($cloak_upgrade > $shipinfo['cloak_normal'])
		{
			$cloak_upgrade_cost = phpChangeDelta($cloak_upgrade, $shipinfo['cloak_normal']);
		}
	}
	else
	{
		$cloak_upgrade = $shipinfo['cloak_normal'];
	}

	$torp_launchers_upgrade_cost = 0;
	if($shipinfo['torp_launchers'] == $shipinfo['torp_launchers_normal'])
	{
		if ($torp_launchers_upgrade > $classinfo['maxtorp_launchers'])
		{
			$torp_launchers_upgrade = $classinfo['maxtorp_launchers'];
		}

		if ($torp_launchers_upgrade < $classinfo['mintorp_launchers'])
		{
			$torp_launchers_upgrade = $classinfo['mintorp_launchers'];
		}

		if ($torp_launchers_upgrade > $shipinfo['torp_launchers_normal'])
		{
			$torp_launchers_upgrade_cost = phpChangeDelta($torp_launchers_upgrade, $shipinfo['torp_launchers_normal']);
		}
	}
	else
	{
		$torp_launchers_upgrade = $shipinfo['torp_launchers_normal'];
	}

	$shields_upgrade_cost = 0;
	if($shipinfo['shields'] == $shipinfo['shields_normal'])
	{
		if ($shields_upgrade > $classinfo['maxshields'])
		{
			$shields_upgrade = $classinfo['maxshields'];
		}

		if ($shields_upgrade < $classinfo['minshields'])
		{
			$shields_upgrade = $classinfo['minshields'];
		}

		if ($shields_upgrade > $shipinfo['shields_normal'])
		{
			$shields_upgrade_cost = phpChangeDelta($shields_upgrade, $shipinfo['shields_normal']);
		}
	}
	else
	{
		$shields_upgrade = $shipinfo['shields_normal'];
	}

	$ecm_upgrade_cost = 0;
	if($shipinfo['ecm'] == $shipinfo['ecm_normal'])
	{
		if ($ecm_upgrade > $classinfo['maxecm'])
		{
			$ecm_upgrade = $classinfo['maxecm'];
		}

		if ($ecm_upgrade < $classinfo['minecm'])
		{
			$ecm_upgrade = $classinfo['minecm'];
		}

		if ($ecm_upgrade > $shipinfo['ecm_normal'])
		{
			$ecm_upgrade_cost = phpChangeDelta($ecm_upgrade, $shipinfo['ecm_normal']);
		}
	}
	else
	{
		$ecm_upgrade = $shipinfo['ecm_normal'];
	}

	if ($fighter_number < 0)
	{
		 $fighter_number = 0;
	}
	$fighter_number	= round(abs($fighter_number));
	$fighter_max	 = NUM_FIGHTERS($shipinfo['fighter']) - $shipinfo['fighters'];
	if ($fighter_max < 0)
	{
		$fighter_max = 0;
	}
	if ($fighter_number > $fighter_max)
	{
		$fighter_number = $fighter_max;
	}

	if(!class_exists($shipinfo['fighter_class']))
	{
		include ("class/" . $shipinfo['fighter_class'] . ".inc");
	}

	$fighterobject = new $shipinfo['fighter_class']();
	$fighter_price_modifier = $fighterobject->price_modifier;
	$fighter_price = $fighterobject->fighter_price;
	$fighter_cost	= $fighter_number * $fighter_price * $fighter_price_modifier;
	if ($torpedo_number < 0)
	{
		 $torpedo_number = 0;
	}
	$torpedo_number	= round(abs($torpedo_number));
	$torpedo_max	 = NUM_TORPEDOES($shipinfo['torp_launchers']) - $shipinfo['torps'];
	if ($torpedo_max < 0)
	{
		$torpedo_max = 0;
	}
	if ($torpedo_number > $torpedo_max)
	{
		$torpedo_number = $torpedo_max;
	}

	if(!class_exists($shipinfo['torp_class']))
	{
		include ("class/" . $shipinfo['torp_class'] . ".inc");
	}

	$torpobject = new $shipinfo['torp_class']();
	$torp_price_modifier = $torpobject->price_modifier;
	$torpedo_price = $torpobject->torpedo_price;
	$torpedo_cost = $torpedo_number * $torpedo_price * $torp_price_modifier;
	if ($armor_number < 0)
	{
		 $armor_number = 0;
	}
	$armor_number = round(abs($armor_number));
	$armor_max = NUM_armor($shipinfo['armor']) - $shipinfo['armor_pts'];
	if ($armor_max < 0)
	{
		$armor_max = 0;
	}
	if ($armor_number > $armor_max)
	{
		$armor_number = $armor_max;
	}

	if(!class_exists($shipinfo['armor_class']))
	{
		include ("class/" . $shipinfo['armor_class'] . ".inc");
	}

	$armorobject = new $shipinfo['armor_class']();
	$armor_price_modifier = $armorobject->price_modifier;
	$armor_price = $armorobject->armor_price;
	$armor_cost	 = $armor_number * $armor_price * $armor_price_modifier;

	$total_cost = $hull_upgrade_cost + $engine_upgrade_cost + $power_upgrade_cost + $fighter_upgrade_cost + $ecm_upgrade_cost +
					$sensors_upgrade_cost + $beams_upgrade_cost + $armor_upgrade_cost + $cloak_upgrade_cost + $shields_upgrade_cost +
					$torp_launchers_upgrade_cost + $fighter_cost + $torpedo_cost + $armor_cost;

	$total_cost = round($total_cost * $alliancefactor);

	if ($total_cost > $playerinfo['credits'])
	{
		$template_object->assign("error_msg", "$l_ports_needcredits " . NUMBER($total_cost) . " $l_ports_needcredits1 " . NUMBER($playerinfo['credits']) . " $l_credits.");
		$template_object->assign("error_msg2", "<A HREF=port.php>$l_clickme</A> $l_port_returntospecial");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		$trade_credits = NUMBER(abs($total_cost));
		$template_object->assign("l_trade_result", $l_trade_result);
		$template_object->assign("l_cost", $l_cost);
		$template_object->assign("l_credits", $l_credits);
		$template_object->assign("trade_credits", $trade_credits);
		$template_object->assign("l_trade_upgraded", $l_trade_upgraded);
		$template_object->assign("l_trade_added", $l_trade_added);

		 //	Total cost is " . NUMBER(abs($total_cost)) . " credits.<BR><BR>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$total_cost,turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$query = "UPDATE {$db_prefix}ships SET class=$shipinfo[class] ";
		$techname = array();
		$upgradeamount = array();
		$not_tech = array();

		if ($hull_upgrade > $shipinfo['hull_normal'])
		{
			$query = $query . ", hull=$hull_upgrade, hull_normal=$hull_upgrade";
			$techname[] = $l_hull;
			$upgradeamount[] = $hull_upgrade;
			$not_tech[] = 0;
		}
		if ($engine_upgrade > $shipinfo['engines_normal'])
		{
			$query = $query . ", engines=$engine_upgrade, engines_normal=$engine_upgrade";
			$techname[] = $l_engines;
			$upgradeamount[] = $engine_upgrade;
			$not_tech[] = 0;
		}
		if ($power_upgrade > $shipinfo['power_normal'])
		{
			$query = $query . ", power=$power_upgrade, power_normal=$power_upgrade";
			$techname[] = $l_power;
			$upgradeamount[] = $power_upgrade;
			$not_tech[] = 0;
		}
		if ($fighter_upgrade > $shipinfo['fighter_normal'])
		{
			$query = $query . ", fighter=$fighter_upgrade, fighter_normal=$fighter_upgrade";
			$techname[] = $l_fighter;
			$upgradeamount[] = $fighter_upgrade;
			$not_tech[] = 0;
		}
		if ($sensors_upgrade > $shipinfo['sensors_normal'])
		{
			$query = $query . ", sensors=$sensors_upgrade, sensors_normal=$sensors_upgrade";
			$techname[] = $l_sensors;
			$upgradeamount[] = $sensors_upgrade;
			$not_tech[] = 0;
		}
		if ($beams_upgrade > $shipinfo['beams_normal'])
		{
			$query = $query . ", beams=$beams_upgrade, beams_normal=$beams_upgrade";
			$techname[] = $l_beams;
			$upgradeamount[] = $beams_upgrade;
			$not_tech[] = 0;
		}
		if ($armor_upgrade > $shipinfo['armor_normal'])
		{
			$query = $query . ", armor=$armor_upgrade, armor_normal=$armor_upgrade";
			$techname[] = $l_armor;
			$upgradeamount[] = $armor_upgrade;
			$not_tech[] = 0;
		}
		if ($cloak_upgrade > $shipinfo['cloak_normal'])
		{
			$query = $query . ", cloak=$cloak_upgrade, cloak_normal=$cloak_upgrade";
			$techname[] = $l_cloak;
			$upgradeamount[] = $cloak_upgrade;
			$not_tech[] = 0;
		}
		if ($torp_launchers_upgrade > $shipinfo['torp_launchers_normal'])
		{
			$query = $query . ", torp_launchers=$torp_launchers_upgrade, torp_launchers_normal=$torp_launchers_upgrade";
			$techname[] = $l_torp_launch;
			$upgradeamount[] = $torp_launchers_upgrade;
			$not_tech[] = 0;
		}
		if ($shields_upgrade > $shipinfo['shields_normal'])
		{
			$query = $query . ", shields=$shields_upgrade, shields_normal=$shields_upgrade";
			$techname[] = $l_shields;
			$upgradeamount[] = $shields_upgrade;
			$not_tech[] = 0;
		}
		if ($ecm_upgrade > $shipinfo['ecm_normal'])
		{
			$query = $query . ", ecm=$ecm_upgrade, ecm_normal=$ecm_upgrade";
			$techname[] = $l_ecm;
			$upgradeamount[] = $ecm_upgrade;
			$not_tech[] = 0;
		}
		if ($fighter_number)
		{
			$query = $query . ", fighters=fighters+$fighter_number";
			$techname[] = "$l_fighters";
			$upgradeamount[] = NUMBER($fighter_number);
			$not_tech[] = 1;
		}
		if ($torpedo_number)
		{
			$query = $query . ", torps=torps+$torpedo_number";
			$techname[] = "$l_torps";
			$upgradeamount[] = NUMBER($torpedo_number);
			$not_tech[] = 1;
		}
		if ($armor_number)
		{
			$query = $query . ", armor_pts=armor_pts+$armor_number";
			$techname[] = "$l_armorpts";
			$upgradeamount[] = NUMBER($armor_number);
			$not_tech[] = 1;
		}

		$query = $query . " WHERE ship_id=$shipinfo[ship_id]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);

		$hull_upgrade=0;
		$template_object->assign("techname", $techname);
		$template_object->assign("upgradeamount", $upgradeamount);
		$template_object->assign("not_tech", $not_tech);
	}
}

$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_port_returntospecial", $l_port_returntospecial);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ports/upgrades_purchase.tpl");

include ("footer.php");

?>
