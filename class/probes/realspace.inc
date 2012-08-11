<?php
class realspace {
	var $class = "realspace";
	var $type = 3;
	var $l_probe_type;
	var $l_probe_target;
	var $l_probe_description;

	// fill language variables
	function realspace()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_probe_type = "Realspace Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;

			case "french":
				$this->l_probe_type = "Realspace Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;

			case "german":
				$this->l_probe_type = "Realspace-Sonde";
				$this->l_probe_target = "Ziel-Sector";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;

			case "italian":
				$this->l_probe_type = "Sonda in Spazioreale";
				$this->l_probe_target = "Settore di destinazione";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;

			case "russian":
				$this->l_probe_type = "Realspace Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;

			case "spanish":
				$this->l_probe_type = "Realspace Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;

			default:
				$this->l_probe_type = "Realspace Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "A Real Space probe will immediately jump to the target sector and turn into a Sentry Probe.  It will scan and report information about planets and other players in any sector it enters. The probe will also use your turns to make the realspace move.  Larger engines will reduce the number of turns it takes for the probe to move.  If you are out of turns the probe will not move.";
				$this->lss1 = "Current Sector: [destination_name], Last Ship Seen: [shiptype] class ship.";
				$this->lss2 = "Current Sector: [destination_name], Last Ship Seen: Player [character_name] on board a [shiptype] class ship.";
			break;
		}
	}

	var $tag = "LOG5_PROBE_REALSPACE";

	function log_switch_data()
	{
		$data = '<?php
  if($entry[\'type\'] == "' . $this->tag . '")
  {
	list($name,$sector,$organics,$goods,$ore,$torps,$col,$credit,$fighter,$energy) = AAT_split ("\|", $entry[\'data\']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields[\'sector_name\'];
	$retvalue[\'text\'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry[\'type\']]);
	$retvalue[\'title\'] = $l_log_title[$entry[\'type\']];
  }
?>
';
//		return $data;
	return;
	}

	function log_language_data()
	{
/*
		$log_language_data["estonian"]["title"] = "";
		$log_language_data["estonian"]["text"] = "";
		$log_language_data["french"]["title"] = "";
		$log_language_data["french"]["text"] = "";
		$log_language_data["german"]["title"] = "";
		$log_language_data["german"]["text"] = "";
		$log_language_data["italian"]["title"] = "";
		$log_language_data["italian"]["text"] = "";
		$log_language_data["russian"]["title"] = "";
		$log_language_data["russian"]["text"] = "";
		$log_language_data["spanish"]["title"] = "";
		$log_language_data["spanish"]["text"] = "";
		$log_language_data["english"]["title"] = "";
		$log_language_data["english"]["text"] = "";
*/
		return $log_language_data;
	}

	function probe_display_code($data)
	{
		
	}

	// htmlreturnvar = defaultvalue; inputtype ; availableselections ; description
	//
	// radiobutton = 0;	radio ; 0=Profiles Not Required, 1=Profiles Required ;0 = profiles are not required to play on this server, 1 = Thie server requires allplayers to have a registered profile before they are allowed to create a player.
	// numberonly = 10;	number; 5-50 ; 0 = No player limit, Any number over 0 is the number of players online at the same time the game will support.  If anyone tries to login when the limit is reached they will be told to wait and log in later.
	// textinput = 240;	text  ; ; 0 = No player online timelimit, Any number over 0 is the number of minutes a player is allowed to be online per day.  Default is 4 hours.
	// listselection = 5;list  ; 1=1 Planet, 2=2 Planets, 3=3 Planets, 4=4 Planets, 5=5 Planets; This is the maximum number of sector sizes.  This size determines how many planets/cities each sector can support. Do not set this higher than 5 but it can be set from 1 to 5.
	// noinput = ; noinput  ; ; Information text

	function probe_orders_code()
	{
		$orders_array = array();
		$orders_array[] = "rs_target_sector = ;	text  ; ; " . $this->l_probe_target;
		return $orders_array;
	}

	function probe_finishorders_code()
	{
		global $db, $db_prefix, $rs_target_sector, $template_object, $l_global_mmenu, $templatename, $title, $sectorinfo;
		global $probeclass, $title, $new_type, $l_probe_forbidSG, $l_probe_forbidFED, $l_probe_forbidINVALID, $probe_id;

		$rs_target_sector = $_POST['rs_target_sector'];

		if($sectorinfo['zone_id'] == 2)
		{
			include ("header.php");
			$template_object->assign("title", $title);
			$template_object->assign("error_msg", $l_probe_forbidFED);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."genericdie.tpl");
			include ("footer.php");
			die();
		}

		if(empty($rs_target_sector))
		{
			$rs_target_sector = "";
		}

		$resx = $db->SelectLimit("SELECT sector_id, zone_id, sg_sector from {$db_prefix}universe WHERE sector_name =" . $db->qstr($rs_target_sector), 1);
		db_op_result($resx,__LINE__,__FILE__);
		if($resx->RecordCount() > 0)
		{
			$sector_id = $resx->fields['sector_id'];
		}
		else
		{
			$sector_id = 0;
		}

		if((empty($sector_id) || $sector_id == 0 || $resx->fields['zone_id'] == 2 || ($resx->fields['sg_sector'] != 0 && $new_type == 3)) && $new_type != 0)
		{
			include ("header.php");
			$template_object->assign("title", $title);
			if($resx->fields['sg_sector'] != 0 && $new_type == 3)
			{
				$template_object->assign("error_msg", $l_probe_forbidSG);
			}
			if($resx->fields['zone_id'] == 2 || $resx->fields['zone_id'] == 3)
			{
				$template_object->assign("error_msg", $l_probe_forbidFED);
			}
			else
			{
				$template_object->assign("error_msg", $l_probe_forbidINVALID);
			}
			$sector_id = 1;
			$new_type = 0;

			$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET class='$probeclass[$new_type]', type=$new_type, target_sector=$sector_id, data='' WHERE probe_id=$probe_id");
			db_op_result($debug_query,__LINE__,__FILE__);

			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."genericdie.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			if(!empty($sector_id))
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET class='$probeclass[$new_type]', type=$new_type, target_sector=$sector_id, data='' WHERE probe_id=$probe_id");
				db_op_result($debug_query,__LINE__,__FILE__);
			}

			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=probes.php\">";
			die();
		}
	}

	function probe_move_code($probeinfo, $shiptype, $destination)
	{
		global $db, $db_prefix, $shipinfo, $playerinfo, $shipdevice, $langdir, $lssd_level_two, $destination_name;

		include ("languages/$langdir/lang_probes.inc");

		$sensors = $probeinfo['sensors'];
		$probe_id = $probeinfo['probe_id'];
		$owner_id = $probeinfo['owner_id'];

		if (mt_rand(1, 100) < $success)
		{
			$resteam = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$owner_id", 1);
			db_op_result($resteam,__LINE__,__FILE__);
			$sb_alli = $resteam->fields['team'];
			$resteam->close();

			if ($sb_alli != 0)
			{
				if ($sensors >= $lssd_level_two)
				{
					$sbt = str_replace("[destination_name]", $destination_name, $this->lss2);
					$sbt = str_replace("[character_name]", $playerinfo['character_name'], $sbt);
					$sbt = str_replace("[shiptype]", $shiptype, $sbt);
				}
				else
				{
					$sbt = str_replace("[destination_name]", $destination_name, $this->lss1);
					$sbt = str_replace("[shiptype]", $shiptype, $sbt);
				}

			  	$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES ($owner_id,'probe - $probe_id'," . time() . ",'$sbt',$sb_alli) ");
				db_op_result($res3,__LINE__,__FILE__);
			}

			if ($sensors >= $lssd_level_two)
			{
				playerlog($owner_id, "LOG9_PROBE_DETECTED_SHIP", "$probe_id|$destination|$playerinfo[character_name]($shiptype)");
			}
			else
			{
				playerlog($owner_id, "LOG9_PROBE_DETECTED_SHIP", "$probe_id|$destination|$l_unknown($shiptype)");
			}

			if (mt_rand(1, 100) < $success)
			{
				$sc_hull = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['hull']) : "???";
				$sc_engines = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['engines']) : "???";
				$sc_power = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['power']) : "???";
				$sc_fighter = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['fighter']) : "???";
				$sc_sensors = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['sensors']) : "???";
				$sc_beams = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['beams']) : "???";
				$sc_torp_launchers = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['torp_launchers']) : "???";
				$sc_armor = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['armor']) : "???";
				$sc_shields = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['shields']) : "???";
				$sc_cloak = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['cloak']) : "???";
				$sc_ecm = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['ecm']) : "???";
				$sc_armor_pts = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['armor_pts'])) : "???";
				$sc_ship_fighters = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['fighters'])) : "???";
				$sc_torps = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['torps'])) : "???";
				$sc_credits = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['credits'])) : "???";
				$sc_ship_energy = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['energy'])) : "???";
				$sc_dev_minedeflector = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipdevice['dev_minedeflector']['amount'])) : "???";
				$sc_dev_emerwarp = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipdevice['dev_emerwarp']['amount']) : "???";
				$sc_dev_pod = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipdevice['dev_escapepod']['amount']) : "???";
				$sc_ship_colonists = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['colonists'])) : "???";
				$sc_ship_ore = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['ore'])) : "???";
				$sc_ship_organics = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['organics'])) : "???";
				$sc_ship_goods = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $shipinfo['cloak'], $shipinfo['goods'])) : "???";
				$sc_dev_warpedit = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipdevice['dev_warpedit']['amount']) : "???";
				$sc_dev_genesis = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipdevice['dev_genesis']['amount']) : "???";
				$sc_scoop = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $shipinfo['cloak'], $shipdevice['dev_fuelscoop']['amount']) : "???";
				playerlog($owner_id, "LOG9_PROBE_SCAN_SHIP", "$probe_id|$destination|$playerinfo[character_name]($shiptype)|$sc_hull|$sc_engines|$sc_power|$sc_fighter|$sc_sensors|$sc_beams|$sc_torp_launchers|$sc_armor|$sc_shields|$sc_cloak|$sc_armor_pts|$sc_ship_fighters|$sc_torps|$sc_credits|$sc_ship_energy|$sc_dev_minedeflector|$sc_dev_emerwarp|$sc_dev_pod|$sc_ecm");
			}
		}
	}

	function probe_scheduler_code($probeinfo)
	{
		include ("globals/calc_dist.inc");
		global $db, $db_prefix,$level_factor;

		if($probeinfo['sector_id'] == $probeinfo['target_sector'])
		{
			$result = $db->Execute("UPDATE {$db_prefix}probe SET type=0, class='sentry' WHERE probe_id=$probeinfo[probe_id]");
			db_op_result($result,__LINE__,__FILE__);
		}

		$targetlink = $probeinfo['target_sector'];

		//  Calculate number of turns for RS
		$distance = calc_dist($probeinfo['sector_id'], $targetlink);
		$shipspeed = mypw($level_factor, $probeinfo['engines']);
		$triptime = round($distance / $shipspeed);

		if ($triptime == 0)
		{
			$triptime = 1;
		}
		$resultcc = $db->SelectLimit("SELECT turns FROM {$db_prefix}players WHERE player_id=$probeinfo[owner_id]", 1);
		db_op_result($resultcc,__LINE__,__FILE__);
		if ($resultcc > 0)
		{
			if ($resultcc->fields['turns'] >= $triptime)
			{
				TextFlush ("Safe Move to sector $targetlink <br>");
				$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+$triptime, turns=turns-$triptime WHERE player_id=$probeinfo[owner_id]";
				$move_result = $db->Execute ("$query");
				$db->Execute("UPDATE {$db_prefix}probe SET sector_id=$targetlink WHERE probe_id=$probeinfo[probe_id]");

				sched_probe_detect( $probeinfo );
				return;
			}else{
				TextFlush ("Failed Move not enough turns - $triptime turn(s) needed <br>");
				PROBE_playerlog($probeinfo['owner_id'], "LOG9_PROBE_NOTURNS", "$probeinfo[probe_id]|$targetlink"); 
				return;
			}
		}
	}
}

?>