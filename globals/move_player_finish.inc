<?php
if($destination != $shipinfo['sector_id'])
{
	if($move_failed != 1) {
		$stamp = date("Y-m-d H:i:s");
		$source_sector = $shipinfo['sector_id'];
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', turns=greatest(turns-$turns_required, 0),turns_used=turns_used+$turns_required WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$destination, energy=energy+$energy_collected WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$l_rs_ready = str_replace("[sector]",$destination_name,$l_rs_ready);
		$l_rs_ready = str_replace("[triptime]",NUMBER($turns_required),$l_rs_ready);
		$l_rs_ready = str_replace("[energy]",NUMBER($energy_collected),$l_rs_ready);

		log_move($playerinfo['player_id'],$shipinfo['ship_id'],$shipinfo['sector_id'],$destination,$shipinfo['class'],$shipinfo['cloak'], $sectorinfo['zone_id']);

		$l_probe_typen = array();
		$probe_object = array();

		$probe_query = $db->Execute("SELECT * FROM {$db_prefix}probe WHERE sector_id=$destination and owner_id != $shipinfo[player_id] and active='Y';");
		db_op_result($probe_query,__LINE__,__FILE__);

		if($probe_query->RecordCount() > 0)
		{
			$shiptype = get_shipclassname($shipinfo['class']);
			include ("languages/$default_lang/lang_probes.inc");
			while (!$probe_query->EOF)
			{
				$probeinfo = $probe_query->fields;

				if(!class_exists($probeinfo['class'])){
					include ("class/probes/" . $probeinfo['class'] . ".inc");
					$probeobject = new $probeinfo['class']();
					$type = $probeobject->type;
					$probe_object[$type] = $probeobject;
				}
 
				$probe_object[$probeinfo['type']]->probe_move_code($probeinfo, $shiptype, $destination);
				$probe_query->MoveNext();
			}
			$probe_query->close();
		}

		if (($move_method == "real" && $engage != 1 && isset($explore)) || $minesfound == 1 || $sector_combat==1)
		{
			if($is_header == 0)
			{
				include ("header.php");
			}
			$template_object->assign("error_msg", $l_rs_ready);
			$template_object->assign("error_msg2", '');
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."move.tpl");
			include ("footer.php");
			die();
			break;
		}
		
	}
	else
	{
		if($is_header == 0)
		{
			include ("header.php");
		}
		$template_object->assign("error_msg", $l_move_failed);
		$template_object->assign("error_msg2", '');
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."move.tpl");
		include ("footer.php");
		die();
		break;
	}
	  	
}
?>