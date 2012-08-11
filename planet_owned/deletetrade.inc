<?php
if($allow_autotrades == 0)
{
	die();
}

get_post_ifset("traderoute_id");

		if($planetinfo['owner'] == $playerinfo['player_id'])
		{
			$result_auto = $db->Execute("DELETE FROM {$db_prefix}autotrades WHERE owner=$playerinfo[player_id] and traderoute_id=$traderoute_id");
			$temp = $l_planet_tradedeleted;
		}else{
			$temp = $l_planet_cargonoown;
		}
		$template_object->assign("error_msg", $temp);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
		include ("footer.php");
		die();


?>