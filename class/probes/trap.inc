<?php
class trap {
	var $class = "trap";
	var $type = 4;
	var $l_probe_type;
	var $probe_cost = 1000000;
	var $l_probe_target;
	var $l_probe_shipclass;
	var $l_probe_description;
	var $l_probe_info;
	var $l_probe_imtitle;
	var $l_probe_imbody;

	// fill language variables
	function trap()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;

			case "french":
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;

			case "german":
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;

			case "italian":
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;

			case "russian":
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;

			case "spanish":
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;

			default:
				$this->l_probe_type = "Sentry Trap Probe";
				$this->l_probe_target = "Targeted Player";
				$this->l_probe_shipclass = "Ship Class to Target";
				$this->l_probe_description = "Probe Cost: " . $this->probe_cost . "<br><br>Sentry Trap Probes are designed to wait for a specific enemy ship to enter a sector and attack it.  You can select the player and the ship class you want the probe to attack.  If the targetted player enter the sector where the probe is waiting and they are in the selected ship class it will detonate like a sector missile.  The only difference between a Sentry Trap Probe and a Sector Missile is the targetted ship CANNOT evade the attack.";
				$this->l_probe_info = "Target: [target]<br>Ship Class: [class]";
				$this->l_probe_imtitle = "Ship Under Attack";
				$this->l_probe_imbody = "A Sentry Trap Probe owned by [playername] is attacking your ship!";
			break;
		}
	}

	var $tag = "LOG5_PROBE_TRAP";

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
		include ("globals/get_player.inc");
		include ("globals/get_shipclassname.inc");
		$items = explode(",", trim($data));
		for($i = 0; $i < count($items); $i++)
		{
			$variable = explode("=", $items[$i]);
			$variable[0] = trim($variable[0]);
			$variable[1] = trim($variable[1]);
			$$variable[0] = $variable[1];
		}
		$info = str_replace("[target]", get_player($trap_target_player_id), $this->l_probe_info);
		$info = str_replace("[class]", get_shipclassname($trap_ship_class), $info);
		return $info;
	}

	// htmlreturnvar = defaultvalue; inputtype ; availableselections ; description
	//
	// radiobutton = 0;	radio ; 0=Profiles Not Required, 1=Profiles Required ;0 = profiles are not required to play on this server, 1 = Thie server requires allplayers to have a registered profile before they are allowed to create a player.
	// numberonly = 10;	number; 5-50 ; 0 = No player limit, Any number over 0 is the number of players online at the same time the game will support.  If anyone tries to login when the limit is reached they will be told to wait and log in later.
	// textinput = 240;	text  ; ; 0 = No player online timelimit, Any number over 0 is the number of minutes a player is allowed to be online per day.  Default is 4 hours.
	// listselection = 5; list  ; 1=1 Planet, 2=2 Planets, 3=3 Planets, 4=4 Planets, 5=5 Planets; This is the maximum number of sector sizes.  This size determines how many planets/cities each sector can support. Do not set this higher than 5 but it can be set from 1 to 5.
	// noinput = ; noinput  ; ; Information text

	function probe_orders_code()
	{
		global $db, $db_prefix;
		$orders_array = array();
		$playerlist = "";
		$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players where player_id>3 ORDER BY character_name");
		$totalplayers = $res->RecordCount();
		$playercount = 0;
		while (!$res->EOF)
		{
			$row = $res->fields;
			$playerlist .= "$row[player_id]=$row[character_name]";
			$playercount++;
			if($playercount != $totalplayers)
			{
				$playerlist .= ", ";
			}
			$res->MoveNext();
		}

		$classdata = "";
		$res = $db->Execute("SELECT type_id,name FROM {$db_prefix}ship_types where buyable='Y' ORDER BY type_id");
		$totalclasses = $res->RecordCount();
		$classrcount = 0;
		while (!$res->EOF)
		{
			$row = $res->fields;
			$classdata .= "$row[type_id]=$row[name]";
			$classrcount++;
			if($classrcount != $totalclasses)
			{
				$classdata .= ", ";
			}
			$res->MoveNext();
		}

		$orders_array[] = "trap_target_player_id = ;	list  ;" . $playerlist . " ; " . $this->l_probe_target;
		$orders_array[] = "trap_ship_class = ;	list  ;" . $classdata . " ; " . $this->l_probe_shipclass;
		return $orders_array;
	}
 
	function probe_finishorders_code()
	{
		global $db, $db_prefix, $trap_target_player_id, $trap_ship_class, $l_global_mmenu, $probe_id;
		global $probeclass, $new_type, $probe_id, $playerinfo, $l_probe2_nocredits, $template_object, $templatename, $l_probe_forbidFED, $title, $sectorinfo;

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
		if($playerinfo['credits'] < $this->probe_cost)
		{
			include ("header.php");
			$template_object->assign("title", $title);
			$l_probe2_nocredits = str_replace("[total]", NUMBER($this->probe_cost), $l_probe2_nocredits);
			$l_probe2_nocredits = str_replace("[credits]", NUMBER($playerinfo['credits']), $l_probe2_nocredits);
			$template_object->assign("error_msg", $l_probe2_nocredits);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."genericdie.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			$data = "trap_target_player_id=" . $_POST['trap_target_player_id'] . ",trap_ship_class=" . $_POST['trap_ship_class'];

			$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET class='$probeclass[$new_type]', type=$new_type, data=" . $db->qstr($data) . " WHERE probe_id=$probe_id");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$this->probe_cost WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=probes.php\">";
			die();
		}
	}

	function probe_move_code($probeinfo, $shiptype, $destination)
	{
		global $db, $db_prefix, $shipinfo, $playerinfo, $shipdevice, $langdir, $full_attack_modifier, $shipdevice, $shiptypes;

		include ("globals/combat_functions.inc");
		include ("globals/ship_bounty_check.inc");
		include ("globals/collect_bounty.inc");
		include ("globals/db_kill_player.inc");
		include ("globals/player_ship_destroyed.inc");
		include ("globals/get_player.inc");
		include ("globals/send_system_im.inc");

		$items = explode(",", trim($probeinfo['data']));
		for($i = 0; $i < count($items); $i++)
		{
			$variable = explode("=", $items[$i]);
			$variable[0] = trim($variable[0]);
			$variable[1] = trim($variable[1]);
			$$variable[0] = $variable[1];
		}

		if($trap_target_player_id == $playerinfo['player_id'] && $trap_ship_class == $shipinfo['class'])
		{
			$success = SCAN_SUCCESS($probeinfo['sensors'], $shipinfo['cloak'], $shiptypes[$shipinfo['class']]['basehull']);

			if (mt_rand(1, 100) < $success)
			{
				$resteam = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$probeinfo[owner_id]", 1);
				db_op_result($resteam,__LINE__,__FILE__);
				$teammate = $resteam->fields['team'];
				$probeownerinfo = $resteam->fields;
				$resteam->close();
				$isfedbounty = ship_bounty_check($probeownerinfo, $destination, $playerinfo, 0);

				if ($playerinfo['team'] != $teammate && $isfedbounty == 0 && $probeownerinfo['player_id'] != $playerinfo['player_id'])
				{
					$sm_damage_shields = 11000;
					$sm_damage_all = 9000;

					if(!class_exists($shipinfo['armor_class'])){
						include ("class/" . $shipinfo['armor_class'] . ".inc");
					}

					// get target beam, shield and armor values
					$target_shield_energy = floor($shipinfo['energy'] * 0.4);
					$sectormissile_attack_energy = $shipinfo['energy'] - $target_shield_energy;

					if (NUM_SHIELDS($shipinfo['shields']) < $target_shield_energy)
					{
						$target_shield_energy = NUM_SHIELDS($shipinfo['shields']);
					}

					$targetenergyset = $target_shield_energy + $sectormissile_attack_energy;

					$left_over_energy = max(0, $shipinfo['energy'] - $targetenergyset);

					$targetarmor = $shipinfo['armor_pts'];

					$shipinfoshields = $shipinfo['shields'];
					$shipinfoarmor = $shipinfo['armor'];
					$targetname = $playerinfo['character_name'];

					if(!class_exists($shipinfo['shield_class'])){
						include ("class/" . $shipinfo['shield_class'] . ".inc");
					}

					$targetobject = new $shipinfo['shield_class']();
					$ship_shield_hit_pts = $targetobject->ship_shield_hit_pts;

					if(!class_exists($shipinfo['armor_class'])){
						include ("class/" . $shipinfo['armor_class'] . ".inc");
					}

					$targetobject = new $shipinfo['armor_class']();
					$ship_armor_hit_pts = $targetobject->ship_armor_hit_pts;

					adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Sentry Trap Probe Combat Start:</B></font><BR>Attacker " . get_player($probeinfo['owner_id']) . " (id: $probeinfo[owner_id]) 
					<br>Sensor Tech: $probeinfo[sensors], Cloak Tech: $probeinfo[cloak], Attacking Energy: $sectormissile_attack_energy<br>
					<br>Defender ". $playerinfo['character_name'] . " (id: $playerinfo[player_id]) 
					<br>Sensor Tech: $shipinfo[sensors], Shield Tech: $shipinfo[shields], Engine Tech: $shipinfo[engines], Energy Tech: $shipinfo[power], Armor Tech: $shipinfo[armor], Cloak Tech: $shipinfo[cloak]
					<br>Defending Energy: $target_shield_energy, Defender total energy: $shipinfo[energy], Energy Left Over: $left_over_energy");

					$attackerlowpercent = ecmcheck($shipinfo['ecm'], $probeinfo['sensors'], -mt_rand($full_attack_modifier, 90));

					if($sectormissile_attack_energy != 0)
					{
						$attack_fire_damage = calc_damage($sectormissile_attack_energy, $sm_damage_shields, $attackerlowpercent, $shipinfoshields, $shipinfoshields);
						$target_shields = calc_failure($target_shield_energy, $shipinfoshields, $shipinfoshields);
						$target_shield_hit_pts = $target_shield_energy * $ship_shield_hit_pts;
						$target_armor = calc_failure($targetarmor, $shipinfoarmor, $shipinfoshields);
						$target_armor_hit_pts = $targetarmor * $ship_armor_hit_pts;
						$attacker_energy_left = $attack_fire_damage[1];

						if($attack_fire_damage[0] > $target_shield_hit_pts)
						{
							$attack_fire_damage[0] = $attack_fire_damage[0] - $target_shield_hit_pts;
							$target_shields_left = 0;
							$attacker_energy_left = floor($attack_fire_damage[0] / $sm_damage_shields);

							$attackerlowpercent = ecmcheck($shipinfo['ecm'], $probeinfo['sensors'], -mt_rand($full_attack_modifier, 90));
							$attack_fire2_damage = calc_damage($attacker_energy_left, $sm_damage_all, $attackerlowpercent, $shipinfoarmor, $shipinfoarmor);
							$attacker_energy_left += $attack_fire2_damage[1];

							if($attack_fire2_damage[0] > $target_armor_hit_pts)
							{
								$attack_fire2_damage[0] = $attack_fire2_damage[0] - $target_armor_hit_pts;
								$attack_damage = floor($target_armor_hit_pts / $ship_armor_hit_pts);
								$attacker_energy_left += floor($attack_fire2_damage[0] / $sm_damage_all);
								$target_armor_left = 0;
							}
							else
							{
								$target_armor_hit_pts = $target_armor_hit_pts - $attack_fire2_damage[0];
								$target_armor_used = floor($attack_fire2_damage[0] / $ship_armor_hit_pts);
								$target_armor_left = floor($target_armor_hit_pts / $ship_armor_hit_pts);
							}
						}
						else
						{
							$target_shield_hit_pts = $target_shield_hit_pts - $attack_fire_damage[0];
							$target_shields_used = floor($attack_fire_damage[0] / $ship_shield_hit_pts);
							$target_shields_left = floor($target_shield_hit_pts / $ship_shield_hit_pts);
							$target_armor_left = $targetarmor;
						}
					}
					else
					{
						$target_shields_left = $target_shield_energy;
						$target_armor_left = $targetarmor;
						$attacker_energy_left = 0;
					}

					//                 End of Attack code
					$target_shields_left += $left_over_energy;

					adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Sentry Trap Probe Combat End:</B></font><BR>Defender ".$targetname . " Shields Left = <B>".$target_shields_left.
					"</B>, Armor Left = <B>$target_armor_left</B>");

					$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST($target_armor_left, 0), energy=GREATEST($target_shields_left, 0)WHERE ship_id=$shipinfo[ship_id]");
					db_op_result($debug_query,__LINE__,__FILE__);

					if ($target_armor_left < 1)
					{
						//	target_died();
						if ($shipdevice['dev_escapepod']['amount'] == 1)
						{
							player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], $probeownerinfo['player_id'], $probeownerinfo['rating'], "killedtrapprobepod");
							playerlog($playerinfo['player_id'], "LOG5_DESTROYED_PROBE_ATTACK", "$probeownerinfo[character_name]|$destination");
							playerlog($probeownerinfo['player_id'], "LOG5_PROBE_ATTACK_SUCCEEDED", "$playerinfo[character_name]|$destination");
							collect_bounty($probeownerinfo['player_id'],$playerinfo['player_id']);
						}
						else
						{
							playerlog($playerinfo['player_id'], "LOG5_DESTROYED_PROBE_ATTACK", "$probeownerinfo[character_name]|$destination");
							playerlog($probeownerinfo['player_id'], "LOG5_PROBE_ATTACK_SUCCEEDED", "$playerinfo[character_name]|$destination");
							db_kill_player($playerinfo['player_id'], $probeownerinfo['player_id'], $probeownerinfo['rating'], "killedtrapprobe");
							collect_bounty($probeownerinfo['player_id'],$playerinfo['player_id']);
						}
					}
					else
					{
						if($target_armor_left > 0)
						{
							calc_internal_damage($shipinfo['ship_id'], 0, ($shipinfo['armor_pts']-$target_armor_left) / $shipinfo['armor_pts']);
						}
						$armor_lost=$shipinfo['armor_pts'] - $target_armor_left;
						$energy_lost=$shipinfo['energy'] - $target_shields_left;
						playerlog($playerinfo['player_id'], "LOG5_SURVIVE_PROBE_ATTACK", "$probeownerinfo[character_name]|$armor_lost|$energy_lost|$destination");
						playerlog($probeownerinfo['player_id'], "LOG5_PROBE_ATTACK_FAILED", "$playerinfo[character_name]|$destination");
					}
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}probe WHERE probe_id=$probeinfo[probe_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$l_probe_imbody = str_replace("[playername]", $probeownerinfo['character_name'], $this->l_probe_imbody);
					send_system_im($playerinfo['player_id'], $this->l_probe_imtitle, $l_probe_imbody, $playerinfo['last_login']);
				}
			}
		}
	}

	function probe_scheduler_code()
	{
	}
}

?>