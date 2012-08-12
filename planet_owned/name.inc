<?php
		$template_object->assign("l_planet_iname", $l_planet_iname);
		$template_object->assign("planetname", $planetinfo['name']);
		$template_object->assign("l_reset", $l_reset);
		$template_object->assign("l_submit", $l_submit);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedname.tpl");
		include ("footer.php");
		die();

?>