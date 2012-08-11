<?php
class seeker {
	var $class = "seeker";
	var $type = 6;
	var $l_probe_type;
	var $l_probe_target;
	var $l_probe_description;

	// fill language variables
	function seeker()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;

			case "french":
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;

			case "german":
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Ziel-Sector";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;

			case "italian":
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Settore di destinazione";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;

			case "russian":
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;

			case "spanish":
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;

			default:
				$this->l_probe_type = "Seeker Probe";
				$this->l_probe_target = "Target Sector";
				$this->l_probe_description = "The Seeker Probe is specifically designed to search out Gateway Sectors leading to sectors created with a Sector Genesis Device.  The probes will not report on any ships or planets it finds.  The probe will only report the existance of a Gateway Sector when it finds one.  It will not search SG sectors.  Once it finds and reports a Gateway Sector it will continue looking for more Gateway Sectors in realspace.";
			break;
		}
	}

	var $tag = "LOG5_PROBE_SEEKER";

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
		return $orders_array;
	}

	function probe_finishorders_code()
	{
		global $db, $db_prefix, $l_global_mmenu, $templatename, $template_object;
		global $probeclass, $new_type, $probe_id, $l_probe_forbidFED, $title, $sectorinfo;

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
		else
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET class='$probeclass[$new_type]', type=$new_type, data='' WHERE probe_id=$probe_id");
			db_op_result($debug_query,__LINE__,__FILE__);
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=probes.php\">";
			die();
		}
	}

	function probe_move_code($probeinfo, $shiptype, $destination)
	{
	}

	function probe_scheduler_code($probeinfo)
	{
		global $db, $db_prefix, $level_factor;

		$linkres = $db->Execute ("SELECT link_dest FROM {$db_prefix}links WHERE link_start='$probeinfo[sector_id]'");
		db_op_result($linkres,__LINE__,__FILE__);

		$targetlink = 0;
		if($linkres->RecordCount() == 0)
		{
			$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and zone_id != 2 ORDER BY rand()", 1);
			$targetlink = $findem->fields['sector_id'];
		}

		while (!$linkres->EOF)
		{
			if(( mt_rand(1,1000) <= 250 && $targetlink == 0) || $linkres->fields['link_dest'] == $probeinfo['target_sector'])
			{
				$targetlink = $linkres->fields['link_dest'];
			}
			$linkres->MoveNext();
		}

		if($targetlink > 0)
		{
			$sectres = $db->Execute ("SELECT zone_id, sg_sector FROM {$db_prefix}universe WHERE sector_id='$targetlink'");
			if ($sectres->fields['zone_id'] == 2 || $sectres->fields['sg_sector'] != 0)
			{
				$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and zone_id != 2 ORDER BY rand()", 1);
				$targetlink = $findem->fields['sector_id'];
			}
		}

		if($targetlink > 0)
		{
			$resultcc = $db->SelectLimit("SELECT turns FROM {$db_prefix}players WHERE player_id=$probeinfo[owner_id]", 1);
			db_op_result($resultcc,__LINE__,__FILE__);
			if ($resultcc > 0)
			{
				if ($resultcc->fields['turns'] >= 1)
				{
					TextFlush ("Safe Move to sector $targetlink <br>");
					$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+1, turns=turns-1 WHERE player_id=$probeinfo[owner_id]";
					$move_result = $db->Execute ("$query");
					$db->Execute("UPDATE {$db_prefix}probe SET sector_id = $targetlink WHERE probe_id = $probeinfo[probe_id]");

					$this->scan_for_SG($targetlink, $probeinfo['owner_id'], $probeinfo['probe_id']);
					log_move($probeinfo['owner_id'], $probeinfo['probe_id'], $probeinfo['sector_id'], $targetlink, 1, $probeinfo['cloak'], $sectres->fields['zone_id']);
				}else{
					TextFlush ("Failed Move not enough turns - 1 turn needed <br>");
					PROBE_playerlog($probeinfo['owner_id'], "LOG9_PROBE_NOTURNS", "$probeinfo[probe_id]|$targetlink"); 
				}
			}
		}
	}

	function scan_for_SG($targetlink, $owner_id, $probe_id)
	{
		global $db, $db_prefix;
		$res = $db->Execute("SELECT {$db_prefix}universe.sector_name FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$targetlink' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest and {$db_prefix}universe.sg_sector!=0");
		db_op_result($res,__LINE__,__FILE__);
		if($res->RecordCount() > 0)
		{
			TextFlush ("<font color=\"lime\"><b>Found a Gateway!</b></font><br>");
			PROBE_playerlog($owner_id, "LOG9_PROBE_DETECTED_GATEWAY", "$probe_id|$targetlink");
		}
	}
}

?>