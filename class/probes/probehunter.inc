<?php
class probehunter {
	var $class = "probehunter";
	var $type = 999999;
	var $l_probe_type;
	var $l_probe_description;
	var $l_stationary;
	var $l_roaming;

	// fill language variables
	function probehunter()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_probe_type = "Probe Hunter Probe";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;

			case "french":
				$this->l_probe_type = "Probe Hunter Probe";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;

			case "german":
				$this->l_probe_type = "Probe Hunter Probe";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;

			case "italian":
				$this->l_probe_type = "Probe Hunter Warp";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;

			case "russian":
				$this->l_probe_type = "Probe Hunter Probe";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;

			case "spanish":
				$this->l_probe_type = "Probe Hunter Probe";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;

			default:
				$this->l_probe_type = "Probe Hunter Probe";
				$this->l_probe_description = "The Probe Hunter is designed to seek out and destroy all enemy probes.  It will only use Warp Links to move and it can travel in SG Sectors.  When it finds a probe it will destroy it and continue looking for more probes to destroy.  The Scan Tech is used to try and find cloaked enemy probes.";
				$this->l_stationary = "Stationary Guard Probe";
				$this->l_roaming = "Roaming Attack Probe";
			break;
		}
	}

	var $tag = "LOG5_PROBE_HUNTER_PROBE";

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
		$items = explode(",", trim($data));
		for($i = 0; $i < count($items); $i++)
		{
			$variable = explode("=", $items[$i]);
			$variable[0] = trim($variable[0]);
			$variable[1] = trim($variable[1]);
			$$variable[0] = $variable[1];
		}
		if($probe_hunter_list == 0)
		{
			$info = $this->l_stationary;
		}
		else
		{
			$info = $this->l_roaming;
		}
		return $info;
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
		$orders_array[] = "probe_hunter_list = 0;	list ; 0=Stationary Guard Probe, 1=Roaming Attack Probe ;A Stationary Guard Probe will sit in the sector you have dropped it and attack any probe that enters the sector.  The Roaming Attack Probe will use warp links to travel around the universe attacking all probes it can find.";
		return $orders_array;
	}
 
	function probe_finishorders_code()
	{
		global $db, $db_prefix, $warp_target_sector, $template_object, $l_global_mmenu, $templatename, $title, $sectorinfo;
		global $probeclass, $title, $new_type, $l_probe_forbidSG, $l_probe_forbidFED, $l_probe_forbidINVALID, $probe_id;

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
		$data = "probe_hunter_list=" . $_POST['probe_hunter_list'];

		$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET class='$probeclass[$new_type]', type=$new_type, data=" . $db->qstr($data) . " WHERE probe_id=$probe_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=probes.php\">";
	}

	function probe_move_code($probeinfo, $shiptype, $destination)
	{
	}

	function probe_scheduler_code($probeinfo)
	{
		global $db, $db_prefix, $level_factor;

		$items = explode(",", trim($probeinfo['data']));
		for($i = 0; $i < count($items); $i++)
		{
			$variable = explode("=", $items[$i]);
			$variable[0] = trim($variable[0]);
			$variable[1] = trim($variable[1]);
			$$variable[0] = $variable[1];
		}

		if($probe_hunter_list == 1)
		{
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
				$resultcc = $db->SelectLimit("SELECT turns, team, character_name FROM {$db_prefix}players WHERE player_id=$probeinfo[owner_id]", 1);
				db_op_result($resultcc,__LINE__,__FILE__);
				if ($resultcc > 0)
				{
					if ($resultcc->fields['turns'] >= 1)
					{
						TextFlush ($this->l_roaming . " Safe Move to sector $targetlink <br>");
						$query="UPDATE {$db_prefix}players SET  turns_used=turns_used+1, turns=turns-1 WHERE player_id=$probeinfo[owner_id]";
						$move_result = $db->Execute ("$query");
						$db->Execute("UPDATE {$db_prefix}probe SET sector_id = $targetlink WHERE probe_id = $probeinfo[probe_id]");

						$this->scan_for_probe($probeinfo, $resultcc->fields['team'], $resultcc->fields['character_name']);
						log_move($probeinfo['owner_id'], $probeinfo['probe_id'], $probeinfo['sector_id'], $targetlink, 1, $probeinfo['cloak'], $sectres->fields['zone_id']);
					}else{
						TextFlush ("Failed Move not enough turns - 1 turn needed <br>");
						PROBE_playerlog($probeinfo['owner_id'], "LOG9_PROBE_NOTURNS", "$probeinfo[probe_id]|$targetlink"); 
					}
				}
			}
		}
		else
		{
			$resultcc = $db->SelectLimit("SELECT team, character_name FROM {$db_prefix}players WHERE player_id=$probeinfo[owner_id]", 1);
			db_op_result($resultcc,__LINE__,__FILE__);
			TextFlush ($this->l_stationary . "<br>");
			$this->scan_for_probe($probeinfo, $resultcc->fields['team'], $resultcc->fields['character_name']);
		}
	}

	function scan_for_probe($probeinfo, $team, $character_name)
	{
		global $db, $db_prefix;
		$targetlink = $probeinfo['sector_id'];
		$owner_id = $probeinfo['owner_id'];
		$probe_id = $probeinfo['probe_id'];
		if($team == 0)
		{
			$query = "SELECT * FROM {$db_prefix}probe, {$db_prefix}players WHERE {$db_prefix}probe.sector_id = $targetlink and {$db_prefix}probe.owner_id != $owner_id and {$db_prefix}players.player_id={$db_prefix}probe.owner_id";
		}
		else
		{
			$query = "SELECT * FROM {$db_prefix}probe, {$db_prefix}players WHERE {$db_prefix}probe.sector_id = $targetlink and {$db_prefix}probe.owner_id != $owner_id and ({$db_prefix}players.player_id={$db_prefix}probe.owner_id and {$db_prefix}players.team != $team)";
		}
		$result4 = $db->Execute($query);
		db_op_result($result4,__LINE__,__FILE__);
		if($result4->RecordCount() > 0)
		{
			while (!$result4->EOF)
			{
				$moreinfo = $result4->fields;
				TextFlush ("<font color=\"lime\"><b>Found $moreinfo[character_name]'s $moreinfo[class] probe!</b></font><br>");
				$success = SCAN_SUCCESS($probeinfo['sensors'], $moreinfo['cloak'], 1);
				if (mt_rand(1, 100) < $success)
				{
					TextFlush ("<font color=\"yellow\"><b>ATTACKING $moreinfo[character_name]'s $moreinfo[class] probe!</b></font><br>");
					PROBE_playerlog($owner_id, "LOG9_PROBEHUNTER_SUCCEED", "$moreinfo[class]|$targetlink|$moreinfo[character_name]");
					PROBE_playerlog($moreinfo['owner_id'], "LOG9_PROBEHUNTER_DESTROYED", "$moreinfo[class]|$targetlink|$character_name");
					$debug_query = $db->Execute("DELETE from {$db_prefix}probe where probe_id=$moreinfo[probe_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					if(mt_rand(1, 1500) < 250)
					{
						TextFlush ("<font color=\"red\"><b>Probe destroyed in explosion from attacked probe.</b></font><br>");
						PROBE_playerlog($owner_id, "LOG9_PROBEHUNTER_EXPLODED", "$moreinfo[class]|$targetlink|$moreinfo[character_name]");
						$debug_query = $db->Execute("DELETE from {$db_prefix}probe where probe_id=$probe_id");
						db_op_result($debug_query,__LINE__,__FILE__);
						break;
					}
				}
				$result4->MoveNext();
			}
		}
	}
}

?>