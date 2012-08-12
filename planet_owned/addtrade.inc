<?php
if($allow_autotrades == 0)
{
	die();
}

		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}autotrades WHERE planet_id=$planet_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($debug_query->RecordCount() != 0)
		{
			$template_object->assign("error_msg", $l_tdr_errhaveauto);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
			include ("footer.php");
			die();
		}
		$debug_query->close();
		if($planetinfo['owner'] == $playerinfo['player_id'])
		{
			$isowner = 1;
			if($planetinfo['cargo_hull'] == 0 or $planetinfo['cargo_hull'] == '')
			{
				$needcargo = 1;
			}
		}

		$template_object->assign("l_tdr_create", $l_tdr_create);
		$template_object->assign("l_colonist", $l_colonists);
		$template_object->assign("l_energy", $l_energy);
		$template_object->assign("l_organics", $l_organics);
		$template_object->assign("l_ore", $l_ore);
		$template_object->assign("l_tdr_selendpoint", $l_tdr_selendpoint);
		$template_object->assign("l_goods", $l_goods);
		$template_object->assign("l_planet_cargonoown", $l_planet_cargonoown);
		$template_object->assign("l_planet_needcargo", $l_planet_needcargo);
		$template_object->assign("needcargo", $needcargo);
		$template_object->assign("isowner", $isowner);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedaddtrade.tpl");
		include ("footer.php");
		die();

?>