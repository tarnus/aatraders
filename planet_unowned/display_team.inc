<?php
	$template_object->assign("l_planet_team", $l_planet_team);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("allow_ibank", $allow_ibank);
	$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
	$template_object->assign("l_igb_term", $l_igb_term);
	$template_object->assign("l_by_placebounty", $l_by_placebounty);

	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_unowned/planet_display_team.tpl");
	include ("footer.php");
	die();
?>