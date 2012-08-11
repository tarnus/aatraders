<?php
if($allow_autotrades == 0 || $sectorinfo['sg_sector'] != 0)
{
	die();
}

get_post_ifset("cargoshiphull, cargoshippower, total_cost");

function phpTrueDelta($futurevalue,$shipvalue)
{
	$tempval = $futurevalue - $shipvalue;
	return $tempval;
}


		if($planetinfo['owner'] == $playerinfo['player_id'])
		{
			$isowner = 1;
			$cargoshipcost = 0;
			
			if($cargoshiphull > floor($max_tech_level * 0.53))
				$cargoshiphull = $planetinfo['cargo_hull'];

			if ($cargoshiphull > $planetinfo['cargo_hull'])
			{
				$cargoshipcost = phpChangeDelta($cargoshiphull, $planetinfo['cargo_hull']) + 116383500;
			}
			else
			{
				$cargoshiphull = $planetinfo['cargo_hull'];
			}

			if($cargoshippower > floor($max_tech_level * 0.53))
				$cargoshippower = $planetinfo['cargo_power'];

			if ($cargoshippower > $planetinfo['cargo_power'])
			{
				$cargoshipcost += phpChangeDelta($cargoshippower, $planetinfo['cargo_power']);
			}
			else
			{
				$cargoshippower = $planetinfo['cargo_power'];
			}

			if ($cargoshipcost > $playerinfo['credits'])
			{
				$nomoney = 1;
			}
			else
			{
				$trade_credits = NUMBER(abs($cargoshipcost));
				$tempvar = 0;
				if ($cargoshiphull > $planetinfo['cargo_hull'])
				{
					$tempvar=phpTrueDelta($cargoshiphull, $planetinfo['cargo_hull']);
				}
				$tempvar2 = 0;
				if ($cargoshippower > $planetinfo['cargo_power'])
				{
					$tempvar2=phpTrueDelta($cargoshippower, $planetinfo['cargo_power']);
				}

				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$cargoshipcost,turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET cargo_hull=$cargoshiphull, cargo_power=$cargoshippower WHERE planet_id=$planetinfo[planet_id] and owner=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}

		$template_object->assign("l_planet_nocredits1", $l_planet_nocredits1);
		$template_object->assign("l_planet_nocredits2", $l_planet_nocredits2);
		$template_object->assign("cargoshipcost", NUMBER($cargoshipcost));
		$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
		$template_object->assign("l_trade_result", $l_trade_result);
		$template_object->assign("l_cost", $l_cost);
		$template_object->assign("l_credits", $l_credits);
		$template_object->assign("trade_credits", $trade_credits);
		$template_object->assign("l_hull", $l_hull);
		$template_object->assign("l_trade_upgraded", $l_trade_upgraded);
		$template_object->assign("cargoshiphull", $cargoshiphull);
		$template_object->assign("l_power", $l_power);
		$template_object->assign("l_trade_upgraded", $l_trade_upgraded);
		$template_object->assign("cargoshippower", $cargoshippower);
		$template_object->assign("tempvar2", $tempvar2);
		$template_object->assign("tempvar", $tempvar);
		$template_object->assign("nomoney", $nomoney);
		$template_object->assign("isowner", $isowner);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedbuycargofinal.tpl");
		include ("footer.php");
		die();


?>