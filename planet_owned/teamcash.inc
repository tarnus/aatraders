<?php
	if ($playerinfo['player_id'] == $planetinfo['owner'])
	{
		if ($planetinfo['team_cash'] == "Y")
		{
			$template_object->assign("result", $l_planet_not_teamcash);
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET team_cash='N' WHERE planet_id=$planet_id and owner=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		else
		{
			$template_object->assign("result", $l_planet_teamcash);
			$debug_query = $db->Execute ("UPDATE {$db_prefix}planets SET team_cash='Y' WHERE planet_id=$planet_id and owner=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
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
		$template_object->assign("result", $l_command_no);
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


?>