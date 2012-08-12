<?php
		/* transfer menu */
		
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
	}
	else
	{
		$max_team_cash_transfer = 0;
	}

		if ($enable_spies and ($playerinfo['player_id'] == $planetinfo['owner']))
		{
			$res = $db->execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '$planet_id' AND owner_id = '$playerinfo[player_id]' ");
			$n_pl = $res->RecordCount();
			$res->close();
			$res = $db->execute("SELECT * FROM {$db_prefix}spies WHERE ship_id = '$shipinfo[ship_id]' AND owner_id = '$playerinfo[player_id]' ");
			$n_sh = $res->RecordCount();
			$res->close();
			$spytransfer = 1;
		}
		if ($enable_dignitaries and ($playerinfo['player_id'] == $planetinfo['owner']))
		{
			$res = $db->execute("SELECT * FROM {$db_prefix}dignitary WHERE planet_id = '$planet_id' AND owner_id = '$playerinfo[player_id]' ");
			$n_pld = $res->RecordCount();
			$res->close();
			$res = $db->execute("SELECT * FROM {$db_prefix}dignitary WHERE ship_id = '$shipinfo[ship_id]' AND owner_id = '$playerinfo[player_id]' ");
			$n_shd = $res->RecordCount();
			$res->close();
			$digtransfer = 1;
		}

		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ship_holds WHERE cargo_name!='energy' and ship_id=$playerinfo[currentship]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$ship_item_count = 0;
		$ship_holds_used = 0;

		while(!$debug_query->EOF){
			$shipinfo[$debug_query->fields['cargo_name']] = $debug_query->fields['amount'];
			if($planetinfo['special_name'] == $debug_query->fields['cargo_name'])
			{
				$shipspecial = $debug_query->fields['amount'];
				$special_holds = $debug_query->fields['hold_space'];
			}
			$ship_holds_used += ($debug_query->fields['hold_space'] * $debug_query->fields['amount']);
			$debug_query->MoveNext();
		}
		$debug_query->close();

		$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
		$free_power = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];

		$l_planet_cinfo=str_replace("[cargo]",NUMBER($free_holds),$l_planet_cinfo);
		$l_planet_cinfo=str_replace("[energy]",NUMBER($free_power),$l_planet_cinfo);

		$template_object->assign("l_planet", $l_planet);
		$template_object->assign("spytransfer", $spytransfer);
		$template_object->assign("digtransfer", $digtransfer);
		$template_object->assign("l_planet_transfer_link", $l_planet_transfer_link);
		$template_object->assign("l_reset", $l_reset);
		$template_object->assign("l_planet_cinfo", $l_planet_cinfo);
		$template_object->assign("l_commodity", $l_commodity);
		$template_object->assign("l_ore", $l_ore);
		$template_object->assign("l_organics", $l_organics);
		$template_object->assign("l_goods", $l_goods);
		$template_object->assign("l_energy", $l_energy);
		$template_object->assign("l_colonists", $l_colonists);
		$template_object->assign("l_fighters", $l_fighters);
		$template_object->assign("l_torps", $l_torps);
		$template_object->assign("l_credits", $l_credits);
		$template_object->assign("l_max", $l_max);
		$template_object->assign("planetmaxcredit", NUMBER($planetinfo['max_credits']));
		$template_object->assign("planetore", NUMBER($planetinfo['ore']));
		$template_object->assign("planetorganics", NUMBER($planetinfo['organics']));
		if($playerinfo['player_id'] == $planetinfo['owner'])
		{
			$template_object->assign("planetspecial", NUMBER(floor($planetinfo['special_amount'])));
		}
		else
		{
			$template_object->assign("planetspecial", 0);
		}
		$template_object->assign("special_name", ucwords($planetinfo['special_name']));
		$template_object->assign("special_holds", NUMBER($special_holds));
		$template_object->assign("l_port_hold_unit", $l_port_hold_unit);
		$template_object->assign("shipspecial", $shipspecial);
		$template_object->assign("planetgoods", NUMBER($planetinfo['goods']));
		$template_object->assign("planetenergy", NUMBER($planetinfo['energy']));
		$template_object->assign("planetcolonists", NUMBER($planetinfo['colonists']));
		$template_object->assign("planetfighters", NUMBER($planetinfo['fighters']));
		$template_object->assign("planettorps", NUMBER($planetinfo['torps']));
		$template_object->assign("planetcredits", NUMBER($planetinfo['credits']));
		$template_object->assign("shipore", NUMBER($shipinfo['ore']));
		$template_object->assign("shiporganics", NUMBER($shipinfo['organics']));
		$template_object->assign("shipgoods", NUMBER($shipinfo['goods']));
		$template_object->assign("shipenergy", NUMBER($shipinfo['energy']));
		$template_object->assign("shipcolonists", NUMBER($shipinfo['colonists']));
		$template_object->assign("shipfighters", NUMBER($shipinfo['fighters']));
		$template_object->assign("shiptorps", NUMBER($shipinfo['torps']));
		$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
		$template_object->assign("maxtransfercredits_formatted", NUMBER($max_team_cash_transfer));
		$template_object->assign("maxtransfercredits", $max_team_cash_transfer);
		$template_object->assign("team_cash_countdown", $playerinfo['team_cash_countdown']);
		$template_object->assign("l_planet_max_transfer", $l_planet_max_transfer);
		$template_object->assign("l_planet_unlimited", $l_planet_unlimited);
		$template_object->assign("l_ship", $l_ship);
		$template_object->assign("l_planet_transfer_link", $l_planet_transfer_link);
		$template_object->assign("l_planet_toplanet", $l_planet_toplanet);
		$template_object->assign("l_all", $l_all);
		$template_object->assign("l_spy", $l_spy);
		$template_object->assign("n_pl", NUMBER($n_pl));
		$template_object->assign("n_sh", NUMBER($n_sh));
		$template_object->assign("l_dig", $l_dig);
		$template_object->assign("n_pld", NUMBER($n_pld));
		$template_object->assign("n_shd", NUMBER($n_shd));
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedtransfer.tpl");
		include ("footer.php");
		die();

?>