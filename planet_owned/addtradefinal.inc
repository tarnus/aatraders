<?php
if($allow_autotrades == 0)
{
	die();
}

get_post_ifset("port_id_goods, port_id_ore, port_id_organics, port_id_energy, port_id_colonist, planet_id");

		if($planetinfo['owner'] == $playerinfo['player_id'])
		{
			//dbase sanity check for source
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

			if ($sectorinfo['sg_sector'] != 0)
			{
				$template_object->assign("error_msg", $l_tdr_errnosg);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
				include ("footer.php");
				die();
			}

			if($port_id_goods != ""){
				//dbase sanity check for dest
				$query = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($port_id_goods) . " and sg_sector = 0", 1);
				if (!$query || $query->EOF)
				{
					$l_tdr_errnotvaliddestport = str_replace("[tdr_port_id]", $port_id_goods, $l_tdr_errnotvaliddestport);
					$template_object->assign("error_msg", $l_tdr_errnotvaliddestport);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				$destination=$query->fields;
				$query->close();
				if ($destination['port_type'] == 'none')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_goods, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				if ($destination['port_type'] == 'devices' || $destination['port_type'] == 'upgrades' || $destination['port_type'] == 'spacedock' || $destination['port_type'] == 'casino')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_goods, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				// ensure that they have been in the sector for the second port, but only if its a valid port type.
				$res1 = $db->Execute("SELECT * from {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] AND source = $destination[sector_id]");
				if (!$res1 || $res1->EOF)
				{
					$template_object->assign("error_msg", $l_tdr_explorefirst);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}
				$res1->close();
				$port_id_goods = $destination['sector_id'];
			}

			if($port_id_ore != "")
			{
				//dbase sanity check for dest
				$query = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($port_id_ore) . " and sg_sector = 0", 1);
				if (!$query || $query->EOF)
				{
					$l_tdr_errnotvaliddestport = str_replace("[tdr_port_id]", $port_id_ore, $l_tdr_errnotvaliddestport);
					$template_object->assign("error_msg", $l_tdr_errnotvaliddestport);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				$destination=$query->fields;
				$query->close();
				if ($destination['port_type'] == 'none')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_ore, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				if ($destination['port_type'] == 'devices' || $destination['port_type'] == 'upgrades' || $destination['port_type'] == 'spacedock' || $destination['port_type'] == 'casino')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_ore, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				// ensure that they have been in the sector for the second port, but only if its a valid port type.
				$res1 = $db->Execute("SELECT * from {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] AND source = $destination[sector_id]");
				if (!$res1 || $res1->EOF)
				{
					$template_object->assign("error_msg", $l_tdr_explorefirst);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}
				$res1->close();
				$port_id_ore = $destination['sector_id'];
			}

			if($port_id_organics != "")
			{
				//dbase sanity check for dest
				$query = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($port_id_organics) . " and sg_sector = 0", 1);
				if (!$query || $query->EOF)
				{
					$l_tdr_errnotvaliddestport = str_replace("[tdr_port_id]", $port_id_organics, $l_tdr_errnotvaliddestport);
					$template_object->assign("error_msg", $l_tdr_errnotvaliddestport);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				$destination=$query->fields;
				$query->close();
				if ($destination['port_type'] == 'none')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_organics, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				if ($destination['port_type'] == 'devices' || $destination['port_type'] == 'upgrades' || $destination['port_type'] == 'spacedock' || $destination['port_type'] == 'casino')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_organics, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				// ensure that they have been in the sector for the second port, but only if its a valid port type.
				$res1 = $db->Execute("SELECT * from {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] AND source = $destination[sector_id]");
				if (!$res1 || $res1->EOF)
				{
					$template_object->assign("error_msg", $l_tdr_explorefirst);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}
				$res1->close();
				$port_id_organics = $destination['sector_id'];
			}

			if($port_id_energy != "")
			{
				//dbase sanity check for dest
				$query = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($port_id_energy) . " and sg_sector = 0", 1);
				if (!$query || $query->EOF)
				{
					$l_tdr_errnotvaliddestport = str_replace("[tdr_port_id]", $port_id_energy, $l_tdr_errnotvaliddestport);
					$template_object->assign("error_msg", $l_tdr_errnotvaliddestport);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				$destination=$query->fields;
				$query->close();
				if ($destination['port_type'] == 'none')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_energy, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				if ($destination['port_type'] == 'devices' || $destination['port_type'] == 'upgrades' || $destination['port_type'] == 'spacedock' || $destination['port_type'] == 'casino')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_energy, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				// ensure that they have been in the sector for the second port, but only if its a valid port type.
				$res1 = $db->Execute("SELECT * from {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] AND source = $destination[sector_id]");
				if (!$res1 || $res1->EOF)
				{
					$template_object->assign("error_msg", $l_tdr_explorefirst);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}
				$res1->close();
				$port_id_energy = $destination['sector_id'];
			}

			if($port_id_colonist != "")
			{
				//dbase sanity check for dest
				$query = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($port_id_colonist) . " and sg_sector = 0", 1);
				if (!$query || $query->EOF)
				{
					$l_tdr_errnotvaliddestport = str_replace("[tdr_port_id]", $port_id_colonist, $l_tdr_errnotvaliddestport);
					$template_object->assign("error_msg", $l_tdr_errnotvaliddestport);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				$destination=$query->fields;
				$query->close();
				if ($destination['port_type'] == 'none')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_colonist, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				if ($destination['port_type'] == 'devices' || $destination['port_type'] == 'upgrades' || $destination['port_type'] == 'spacedock' || $destination['port_type'] == 'casino')
				{
					$l_tdr_errnoport2 = str_replace("[tdr_port_id]", $port_id_colonist, $l_tdr_errnoport2);
					$template_object->assign("error_msg", $l_tdr_errnoport2);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}

				// ensure that they have been in the sector for the second port, but only if its a valid port type.
				$res1 = $db->Execute("SELECT * from {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] AND source = $destination[sector_id]");
				if (!$res1 || $res1->EOF)
				{
					$template_object->assign("error_msg", $l_tdr_explorefirst);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
					include ("footer.php");
					die();
				}
				$res1->close();
				$port_id_colonist = $destination['sector_id'];
			}

			$src_id = $planet_id;

			if(!isset($port_id_goods) || empty($port_id_goods))
				$port_id_goods = 0;
			if(!isset($port_id_ore) || empty($port_id_ore))
				$port_id_ore = 0;
			if(!isset($port_id_organics) || empty($port_id_organics))
				$port_id_organics = 0;
			if(!isset($port_id_energy) || empty($port_id_energy))
				$port_id_energy = 0;
			if(!isset($port_id_colonist) || empty($port_id_colonist))
				$port_id_colonist = 0;

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}autotrades (planet_id, port_id_goods, port_id_ore, port_id_organics, port_id_energy, port_id_colonist, owner ) VALUES($src_id, '$port_id_goods', '$port_id_ore', '$port_id_organics', '$port_id_energy', '$port_id_colonist', $playerinfo[player_id])");
			db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("error_msg", $l_planet_tradeadded);
		}

		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_owneddie.tpl");
		include ("footer.php");
		die();

?>