<?php
include ("globals/isLoanPending.inc");

get_post_ifset("hull_upgrade, engine_upgrade, power_upgrade, fighter_upgrade, sensors_upgrade, beams_upgrade, armor_upgrade, cloak_upgrade, ecm_upgrade, torp_launchers_upgrade, shields_upgrade, total_cost, total_cost2");

$l_port_welcome = str_replace("[player]", $playerinfo['character_name'], str_replace("[sectorname]", $sectorinfo['sector_name'], $l_port_welcome));
$template_object->assign("l_port_welcome", $l_port_welcome);
$template_object->assign("l_spacedock", $l_spacedock);

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_trade_turnneed);
	$template_object->assign("error_msg2", "<A HREF=port.php>$l_clickme</A> $l_port_returntospecial");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

if ($sectorinfo['port_type'] == "spacedock")
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
	if($shipinfo['hull'] != $shipinfo['hull_normal'])
	{
		if ($hull_upgrade > $shipinfo['hull_normal'])
		{
			$hull_upgrade = $shipinfo['hull_normal'];
		}

		if ($hull_upgrade < 0)
		{
			$hull_upgrade = 0;
		}

		if ($hull_upgrade > $shipinfo['hull'])
		{
			$hull_upgrade_cost = phpChangeDelta($hull_upgrade, $shipinfo['hull']);
		}
	}
	else
	{
		$hull_upgrade = $shipinfo['hull'];
	}

	$engine_upgrade_cost = 0;
	if($shipinfo['engines'] != $shipinfo['engines_normal'])
	{
		if ($engine_upgrade > $shipinfo['engines_normal'])
		{
			$engine_upgrade = $shipinfo['engines_normal'];
		}

		if ($engine_upgrade < 0)
		{
			$engine_upgrade = 0;
		}

		if ($engine_upgrade > $shipinfo['engines'])
		{
			$engine_upgrade_cost = phpChangeDelta($engine_upgrade, $shipinfo['engines']);
		}
	}
	else
	{
		$engine_upgrade = $shipinfo['engines'];
	}

	$power_upgrade_cost = 0;
	if($shipinfo['power'] != $shipinfo['power_normal'])
	{
		if ($power_upgrade > $shipinfo['power_normal'])
		{
			$power_upgrade = $shipinfo['power_normal'];
		}

		if ($power_upgrade < 0)
		{
			$power_upgrade = 0;
		}

		if ($power_upgrade > $shipinfo['power'])
		{
			$power_upgrade_cost = phpChangeDelta($power_upgrade, $shipinfo['power']);
		}
	}
	else
	{
		$power_upgrade = $shipinfo['power'];
	}

	$fighter_upgrade_cost = 0;
	if($shipinfo['fighter'] != $shipinfo['fighter_normal'])
	{
		if ($fighter_upgrade > $shipinfo['fighter_normal'])
		{
			$fighter_upgrade = $shipinfo['fighter_normal'];
		}

		if ($fighter_upgrade < 0)
		{
			$fighter_upgrade = 0;
		}

		if ($fighter_upgrade > $shipinfo['fighter'])
		{
			$fighter_upgrade_cost = phpChangeDelta($fighter_upgrade, $shipinfo['fighter']);
		}
	}
	else
	{
		$fighter_upgrade = $shipinfo['fighter'];
	}

	$sensors_upgrade_cost = 0;
	if($shipinfo['sensors'] != $shipinfo['sensors_normal'])
	{
		if ($sensors_upgrade > $shipinfo['sensors_normal'])
		{
			$sensors_upgrade = $shipinfo['sensors_normal'];
		}

		if ($sensors_upgrade < 0)
		{
			$sensors_upgrade = 0;
		}

		if ($sensors_upgrade > $shipinfo['sensors'])
		{
			$sensors_upgrade_cost = phpChangeDelta($sensors_upgrade, $shipinfo['sensors']);
		}
	}
	else
	{
		$sensors_upgrade = $shipinfo['sensors'];
	}

	$beams_upgrade_cost = 0;
	if($shipinfo['beams'] != $shipinfo['beams_normal'])
	{
		if ($beams_upgrade > $shipinfo['beams_normal'])
		{
			$beams_upgrade = $shipinfo['beams_normal'];
		}

		if ($beams_upgrade < 0)
		{
			$beams_upgrade = 0;
		}

		if ($beams_upgrade > $shipinfo['beams'])
		{
			$beams_upgrade_cost = phpChangeDelta($beams_upgrade, $shipinfo['beams']);
		}
	}
	else
	{
		$beams_upgrade = $shipinfo['beams'];
	}

	$armor_upgrade_cost = 0;
	if($shipinfo['armor'] != $shipinfo['armor_normal'])
	{
		if ($armor_upgrade > $shipinfo['armor_normal'])
		{
			$armor_upgrade = $shipinfo['armor_normal'];
		}

		if ($armor_upgrade < 0)
		{
			$armor_upgrade = 0;
		}

		if ($armor_upgrade > $shipinfo['armor'])
		{
			$armor_upgrade_cost = phpChangeDelta($armor_upgrade, $shipinfo['armor']);
		}
	}
	else
	{
		$armor_upgrade = $shipinfo['armor'];
	}

	$cloak_upgrade_cost = 0;
	if($shipinfo['cloak'] != $shipinfo['cloak_normal'])
	{
		if ($cloak_upgrade > $shipinfo['cloak_normal'])
		{
			$cloak_upgrade = $shipinfo['cloak_normal'];
		}

		if ($cloak_upgrade < 0)
		{
			$cloak_upgrade = 0;
		}

		if ($cloak_upgrade > $shipinfo['cloak'])
		{
			$cloak_upgrade_cost = phpChangeDelta($cloak_upgrade, $shipinfo['cloak']);
		}
	}
	else
	{
		$cloak_upgradegrade = $shipinfo['cloak'];
	}

	$torp_launchers_upgrade_cost = 0;
	if($shipinfo['torp_launchers'] != $shipinfo['torp_launchers_normal'])
	{
		if ($torp_launchers_upgrade > $shipinfo['torp_launchers_normal'])
		{
			$torp_launchers_upgrade = $shipinfo['torp_launchers_normal'];
		}

		if ($torp_launchers_upgrade < 0)
		{
			$torp_launchers_upgrade = 0;
		}

		if ($torp_launchers_upgrade > $shipinfo['torp_launchers'])
		{
			$torp_launchers_upgrade_cost = phpChangeDelta($torp_launchers_upgrade, $shipinfo['torp_launchers']);
		}
	}
	else
	{
		$torp_launchers_upgrade = $shipinfo['torp_launchers'];
	}

	$shields_upgrade_cost = 0;
	if($shipinfo['shields'] != $shipinfo['shields_normal'])
	{
		if ($shields_upgrade > $shipinfo['shields_normal'])
		{
			$shields_upgrade = $shipinfo['shields_normal'];
		}

		if ($shields_upgrade < 0)
		{
			$shields_upgrade = 0;
		}

		if ($shields_upgrade > $shipinfo['shields'])
		{
			$shields_upgrade_cost = phpChangeDelta($shields_upgrade, $shipinfo['shields']);
		}
	}
	else
	{
		$shields_upgrade = $shipinfo['shields'];
	}

	$ecm_upgrade_cost = 0;
	if($shipinfo['ecm'] != $shipinfo['ecm_normal'])
	{
		if ($ecm_upgrade > $shipinfo['ecm_normal'])
		{
			$ecm_upgrade = $shipinfo['ecm_normal'];
		}

		if ($ecm_upgrade < 0)
		{
			$ecm_upgrade = 0;
		}

		if ($ecm_upgrade > $shipinfo['ecm'])
		{
			$ecm_upgrade_cost = phpChangeDelta($ecm_upgrade, $shipinfo['ecm']);
		}
	}
	else
	{
		$ecm_upgrade = $shipinfo['ecm'];
	}

	$total_cost = $hull_upgrade_cost + $engine_upgrade_cost + $power_upgrade_cost + $fighter_upgrade_cost +
					$sensors_upgrade_cost + $beams_upgrade_cost + $armor_upgrade_cost + $cloak_upgrade_cost +
					$torp_launchers_upgrade_cost + $shields_upgrade_cost + $ecm_upgrade_cost;

	$total_cost = round($total_cost * $alliancefactor * ($repair_modifier / 100));

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

		//	Total cost is " . NUMBER(abs($total_cost)) . " credits.<BR><BR>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$total_cost,turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$query = "UPDATE {$db_prefix}ships SET class=$shipinfo[class] ";
		$techname = array();
		$upgradeamount = array();

		if ($hull_upgrade > $shipinfo['hull'])
		{
			$query = $query . ", hull=$hull_upgrade";
			$techname[] = $l_hull;
			$upgradeamount[] = $hull_upgrade;
		}
		if ($engine_upgrade > $shipinfo['engines'])
		{
			$query = $query . ", engines=$engine_upgrade";
			$techname[] = $l_engines;
			$upgradeamount[] = $engine_upgrade;
		}
		if ($power_upgrade > $shipinfo['power'])
		{
			$query = $query . ", power=$power_upgrade";
			$techname[] = $l_power;
			$upgradeamount[] = $power_upgrade;
		}
		if ($fighter_upgrade > $shipinfo['fighter'])
		{
			$query = $query . ", fighter=$fighter_upgrade";
			$techname[] = $l_fighter;
			$upgradeamount[] = $fighter_upgrade;
		}
		if ($sensors_upgrade > $shipinfo['sensors'])
		{
			$query = $query . ", sensors=$sensors_upgrade";
			$techname[] = $l_sensors;
			$upgradeamount[] = $sensors_upgrade;
		}
		if ($beams_upgrade > $shipinfo['beams'])
		{
			$query = $query . ", beams=$beams_upgrade";
			$techname[] = $l_beams;
			$upgradeamount[] = $beams_upgrade;
		}
		if ($armor_upgrade > $shipinfo['armor'])
		{
			$query = $query . ", armor=$armor_upgrade";
			$techname[] = $l_armor;
			$upgradeamount[] = $armor_upgrade;
		}
		if ($cloak_upgrade > $shipinfo['cloak'])
		{
			$query = $query . ", cloak=$cloak_upgrade";
			$techname[] = $l_cloak;
			$upgradeamount[] = $cloak_upgrade;
		}
		if ($torp_launchers_upgrade > $shipinfo['torp_launchers'])
		{
			$query = $query . ", torp_launchers=$torp_launchers_upgrade";
			$techname[] = $l_torp_launch;
			$upgradeamount[] = $torp_launchers_upgrade;
		}
		if ($shields_upgrade > $shipinfo['shields'])
		{
			$query = $query . ", shields=$shields_upgrade";
			$techname[] = $l_shields;
			$upgradeamount[] = $shields_upgrade;
		}
		if ($ecm_upgrade > $shipinfo['ecm'])
		{
			$query = $query . ", ecm=$ecm_upgrade";
			$techname[] = $l_ecm;
			$upgradeamount[] = $ecm_upgrade;
		}

		$query = $query . " WHERE ship_id=$shipinfo[ship_id]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);

		$hull_upgrade=0;
	}
	$template_object->assign("techname", $techname);
	$template_object->assign("upgradeamount", $upgradeamount);
}

$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_port_returntospecial", $l_port_returntospecial);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ports/spacedock_purchase.tpl");

include ("footer.php");

?>
