<?php
include ("globals/clean_words.inc");

get_post_ifset("new_name");

		/* name2 menu */
		$new_name = str_replace("|", "!", clean_words(trim(strip_tags($new_name))));

		if (metaphone("unowned") == metaphone($new_name) || metaphone("unknown") == metaphone($new_name) || metaphone("unchartered") == metaphone($new_name) || metaphone("uncharted") == metaphone($new_name) || metaphone("federation") == metaphone($new_name) || metaphone("independent") == metaphone($new_name)) 
		{
			$new_name = "Cheater";
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET name=" . $db->qstr($new_name) . " WHERE planet_id=$planet_id and owner=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$template_object->assign("l_planet_cname", $l_planet_cname);
		$template_object->assign("new_name", $new_name);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownednamefinal.tpl");
		include ("footer.php");
		die();

?>