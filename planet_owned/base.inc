<?php
include ("globals/calc_ownership.inc");

		/* build a base */
		if ($planetinfo['ore'] >= $base_ore && $planetinfo['organics'] >= $base_organics && $planetinfo['goods'] >= $base_goods && $planetinfo['credits'] >= $base_credits)
		{
			// Check to see if the player has less than one turn available
			// and if so return to the main menu
			if ($playerinfo['turns']<1)
			{
				$template_object->assign("error_msg", $l_planet_basenoturn);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
				include ("footer.php");
				die();
			}

			// ** Create The Base
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET base='Y', ore=$planetinfo[ore]-$base_ore, organics=$planetinfo[organics]-$base_organics, goods=$planetinfo[goods]-$base_goods, credits=$planetinfo[credits]-$base_credits WHERE planet_id=$planet_id and owner=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			// ** Update User Turns
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET planets_based=planets_based+1, turns=turns-1, turns_used=turns_used+1, planet_update='Y' where player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			// ** Refresh Plant Info
			$result3 = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE planet_id=$planet_id");
			$planetinfo=$result3->fields;
			$result3->close();

			// ** Notify User Of Base Results
			$result = $l_planet_bbuild;
			// ** Calc Ownership and Notify User Of Results
			$ownership = calc_ownership($shipinfo['sector_id']);
			update_player_experience($playerinfo['player_id'], $basing_planet);
		}
		else
		{
			$result = $l_planet_baseinfo;
		}

		$template_object->assign("ownership", $ownership);
		$template_object->assign("result", $result);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedgeneric1.tpl");
		include ("footer.php");
		die();

?>