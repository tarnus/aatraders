<?php
include ("globals/get_rating_change.inc");
include ("globals/artifacts_move.inc");

if ($playerinfo['player_id'] == $planetinfo['owner'])
{
	get_post_ifset("destroy");

	if (($destroy==1 or $destroy==2) && $allow_genesis_destroy){
		if (empty($planetinfo['name']))
		{
			$l_planet_unnamed=str_replace("[name]",$ownerinfo['character_name'],$l_planet_unnamed);
			$l_planet_unnamed=str_replace("[sector]",$planetinfo['sector_name'],$l_planet_unnamed);
			$planetname = $l_planet_unnamed;
		}
		else
		{
			$l_planet_named=str_replace("[name]",$ownerinfo['character_name'],$l_planet_named);
			$l_planet_named=str_replace("[planetname]",$planetinfo['name'],$l_planet_named);
			$l_planet_named=str_replace("[sector]",$planetinfo['sector_name'],$l_planet_named);
			$planetname = $l_planet_named;
		}

		if ($destroy==2 && $allow_genesis_destroy)
		{
			if ($shipdevice['dev_genesis']['amount'] < 1)
			{
				$template_object->assign("error_msg", $l_planet_nogenesis);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
				include ("footer.php");
				die();
			}

			if ($playerinfo['turns'] < 1)
			{
				$template_object->assign("error_msg", $l_planet_genesisnoturn);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
				include ("footer.php");
				die();
			}

			if ($enable_spies)
			{
				$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}planets.sector_id FROM {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id = {$db_prefix}planets.planet_id WHERE {$db_prefix}spies.planet_id = '$planet_id' ");
				while (!$res->EOF)
				{
					$owners = $res->fields;
					playerlog($owners['owner_id'], "LOG2_SPY_CATACLYSM", "$owners[spy_id]|$owners[name]|$owners[sector_id]");
					$res->MoveNext();
				}
				$res->close();
				$db->Execute("DELETE FROM {$db_prefix}spies WHERE planet_id = '$planet_id' ");
			}

			$debug_query = $db->Execute("DELETE from {$db_prefix}planets where planet_id=$planet_id");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("DELETE from {$db_prefix}dignitary where planet_id=$planet_id");
			db_op_result($debug_query,__LINE__,__FILE__);

			$averagetechlvl = floor((($planetinfo['fighter'] + $planetinfo['sensors'] + $planetinfo['beams'] + $planetinfo['torp_launchers'] + $planetinfo['shields'] + $planetinfo['jammer'] + $planetinfo['cloak']) / 7) / 600 * 100);
			if($planetinfo['persuasion_countdown'] == 0)
			{
				$planet_rating = $playerinfo['rating'];
			}
			else
			{
				$planet_rating = $planetinfo['last_owner_rating'];
			}
			if($planet_rating == 2)
			{
				$rating_change = 0;
			}
			else
			{
				$rating_change=get_rating_change($playerinfo['rating'], $planet_rating, $rating_genesis_destroy * $averagetechlvl);
			}
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET rating=rating+$rating_change, planets_destroyed=planets_destroyed+1, turns_used=turns_used+1, turns=turns-1 WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_genesis']['device_id']);
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query=$db->Execute("UPDATE {$db_prefix}ships SET on_planet='N', planet_id=0, storage_planet_id = 0 WHERE planet_id=$planet_id and on_planet='Y'");
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE storage_planet_id = $planet_id");
			db_op_result($debug_query,__LINE__,__FILE__);
			if ($debug_query > 0)
			{
				while (!$debug_query->EOF)
				{
					$ship_id = $debug_query->fields['ship_id'];
					$delete_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id = $ship_id");
					db_op_result($delete_query,__LINE__,__FILE__);
					$delete_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id = $ship_id");
					db_op_result($delete_query,__LINE__,__FILE__);
					$delete_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id = $ship_id");
					db_op_result($delete_query,__LINE__,__FILE__);
					$debug_query->MoveNext();
				}
			}
			$debug_query->close();

			calc_ownership($shipinfo['sector_id']);
			artifacts_move($planet_id, 0, 0);
			close_database();
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			die();
		}

		$template_object->assign("planetname", $planetname);
		$template_object->assign("destroy", $destroy);
		$template_object->assign("allow_genesis_destroy", $allow_genesis_destroy);
		$template_object->assign("l_planet_confirm", $l_planet_confirm);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_no", $l_no);
		$template_object->assign("l_yes", $l_yes);
		$template_object->assign("l_gns_nogenesis", $l_gns_nogenesis);
		$template_object->assign("l_gns_turn", $l_gns_turn);
		$template_object->assign("shipgenesis", $shipdevice['dev_genesis']['amount']);
		$template_object->assign("turns", $playerinfo['turns']);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planetdestroy.tpl");
		include ("footer.php");
		die();
	}
}
else
{
	$template_object->assign("error_msg", $l_planet2_notowner);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
	include ("footer.php");
	die();
}
?>

