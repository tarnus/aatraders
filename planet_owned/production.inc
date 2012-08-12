<?php
		/* change production percentages */
get_post_ifset("porganics, pore, pgoods, penergy, pfighters, ptorp, presearch, pbuild, pspecial");

if(empty($pspecial))
{
	$pspecial = 0;
}
else
{
	$pspecial = stripnum($pspecial);
}

		$porganics = stripnum($porganics);
		$pore = stripnum($pore);
		$pgoods = stripnum($pgoods);
		$penergy = stripnum($penergy);
		$pfighters = stripnum($pfighters);
		$ptorp = stripnum($ptorp);
		$presearch = stripnum($presearch);
		$pbuild = stripnum($pbuild);
		if ($pspecial < 0.0 || $porganics < 0.0 || $pore < 0.0 || $pgoods < 0.0 || $penergy < 0.0 || $pfighters < 0.0 || $ptorp < 0.0 || $presearch < 0.0 || $pbuild < 0.0)
		{
			$result = $l_planet_p_under;
		}
		elseif (($pspecial + $porganics + $pore + $pgoods + $penergy + $pfighters + $ptorp + $presearch + $pbuild) > 100.0)
		{
			$result = $l_planet_p_over;
		}
		else
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET prod_special=$pspecial, prod_ore=$pore,prod_organics=$porganics,prod_goods=$pgoods,prod_energy=$penergy,prod_fighters=$pfighters,prod_torp=$ptorp,prod_research=$presearch,prod_build=$pbuild WHERE planet_id=$planetinfo[planet_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$result = $l_planet_p_changed;
		}

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