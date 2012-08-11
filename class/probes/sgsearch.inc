<?php
class sgsearch {
	var $class = "sgsearch";
	var $type = 7;
	var $l_probe_type;
	var $l_probe_target;
	var $l_probe_description;

	// fill language variables
	function sgsearch()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;

			case "french":
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;

			case "german":
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;

			case "italian":
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;

			case "russian":
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;

			case "spanish":
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;

			default:
				$this->l_probe_type = "SG Sector Search Probe";
				$this->l_probe_description = "An SG Sector Search Probe is a very powerful probe.  You drop the probe into SG Sector and the probe will automatically start searching all of the SG sectors behind the Gateway Sector and never leave the SG area.  It will keep track of all the SG Sectors it has searched and always chose an unsearched SG sector from the warp links found.  It will send back any information just like a Warp Probe based upon the Sensor Level of the SG Search Probe. If the probe is dropped into a sector without a warp link to an SG sector it will convert into a Sentry Probe.";
			break;
		}
	}

	var $tag = "LOG5_PROBE_SGSEARCH";

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
		global $db, $db_prefix, $warp_target_sector, $template_object, $l_global_mmenu, $templatename, $title, $sectorinfo;
		global $probeclass, $title, $new_type, $probe_id;

		$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET class='$probeclass[$new_type]', type=$new_type, data='' WHERE probe_id=$probe_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=probes.php\">";
	}

	function probe_move_code($probeinfo, $shiptype, $destination)
	{
	}

	function probe_scheduler_code($probeinfo)
	{
		global $db, $db_prefix, $level_factor;

		$sector_id_list = explode(",", trim($probeinfo['data']));
		$targetlink = 0;
		$oldlinks = array();

		$linkres = $db->Execute ("SELECT link_dest FROM {$db_prefix}links WHERE link_start='$probeinfo[sector_id]'");
		db_op_result($linkres,__LINE__,__FILE__);
		while (!$linkres->EOF)
		{
			$oldlinks[] = $linkres->fields['link_dest'];
			echo $linkres->fields['link_dest'] . " - ";
			$sectres = $db->Execute ("SELECT zone_id, sg_sector FROM {$db_prefix}universe WHERE sector_id='" . $linkres->fields['link_dest'] . "'");
			if ($sectres->fields['zone_id'] == 2 || $sectres->fields['sg_sector'] == 0)
			{
				array_pop($oldlinks);
			}
			else
			{
				if(!in_array($linkres->fields['link_dest'], $sector_id_list) && $targetlink == 0)
				{
					$targetlink = $linkres->fields['link_dest'];
				}
			}
//echo $targetlink . "<br>";
//print_r( $oldlinks ). "<br>";
			$linkres->MoveNext();
		}

		if($targetlink == 0)
		{
//echo $targetlink . "<br>";
//echo count($oldlinks) . "<br>";
//print_r( $oldlinks ). "<br>";
			if(count($oldlinks) > 0)
			{
				$targetlink = $oldlinks[array_rand($oldlinks)];
//echo $targetlink . "<br>";
			}
			else
			{
				$result = $db->Execute("UPDATE {$db_prefix}probe SET type=0, class='sentry' WHERE probe_id=$probeinfo[probe_id]");
				db_op_result($result,__LINE__,__FILE__);
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
					if(!in_array($targetlink, $sector_id_list))
					{
						$probeinfo['data'] .= "$targetlink,";
					}
					$db->Execute("UPDATE {$db_prefix}probe SET sector_id = $targetlink, data=" . $db->qstr($probeinfo['data']) . " WHERE probe_id = $probeinfo[probe_id]");

					sched_probe_detect( $probeinfo );
					log_move($probeinfo['owner_id'], $probeinfo['probe_id'], $probeinfo['sector_id'], $targetlink, 1, $probeinfo['cloak'], $sectres->fields['zone_id']);
				}else{
					TextFlush ("Failed Move not enough turns - 1 turn needed <br>");
					PROBE_playerlog($probeinfo['owner_id'], "LOG9_PROBE_NOTURNS", "$probeinfo[probe_id]|$targetlink"); 
				}
			}
		}
	}
}
?>