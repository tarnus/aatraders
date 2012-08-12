<?
if (!function_exists('probe_detect'))
{
	function probe_detect( $probe_id )
	{
		global $lssd_level_two,$lssd_level_three, $lss_decay_time, $langdir, $shiptypes;
		global $db, $db_prefix;

		include ("languages/$langdir/lang_common.inc");
		include ("languages/$langdir/lang_probes.inc");
		include ("languages/$langdir/lang_planet.inc");
		include ("languages/$langdir/lang_planets.inc");
		include ("languages/$langdir/lang_combat.inc");
		include ("languages/$langdir/lang_report.inc");
		include ("languages/$langdir/lang_ports.inc");
		include ("globals/get_shipclassname.inc");
		include ("globals/get_player.inc");

		$query ="select * from  {$db_prefix}probe  where probe_id=$probe_id";
		$res0 = $db->SelectLimit($query, 1);
		db_op_result($res0,__LINE__,__FILE__);

		if ($res0->RecordCount()!=0)
		{
   			$probeinfo=$res0->fields;
			$sensors = $probeinfo['sensors'];
			$probe_id=$probeinfo['probe_id'];
			$owner_id=$probeinfo['owner_id'];
			$sector=$probeinfo['sector_id'];
			$resx = $db->SelectLimit("SELECT sector_name,sg_sector from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
			db_op_result($resx,__LINE__,__FILE__);
			$sectorname = $resx->fields['sector_name'];
			$sector_sg = $resx->fields['sg_sector'];
			$success = SCAN_SUCCESS($sensors, 50);
			$roll = mt_rand(1, 100);
			if ($roll < $success)
			{
				// Warp Links
				$result2 = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start='$sector'");
				$num_links = $result2->RecordCount();
				$warplinks="";
				if ($num_links == 0)
				{
					$warplinks= "";
				}
				else
				{
					$warplinks= "";
					$linknumber= 0;
					for($i = 0; $i < $num_links; $i++)
					{
						$links[$i] = $result2->fields;
						// Last Ship Seen
						if ($links[$i] != '0')
						{
							$linknumber++;
							$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $links[$i]['link_dest'], 1);
							db_op_result($resx,__LINE__,__FILE__);
							$linkdestination = $resx->fields['sector_name'];
							
							$warplinks.="$l_probe2_warplink $linknumber: <a href=main.php?move_method=real&engage=1&destination=" . urlencode($linkdestination) . ">$linkdestination</a>";
							$destination=$links[$i]['link_dest'];
							$oldstamp = strtotime(date("Y-m-d H:i:s")) - ($lss_decay_time * 86400);
							$decaydate = date("Y-m-d H:i:s", $oldstamp);
							$resx = $db->SelectLimit("SELECT * from {$db_prefix}sector_log WHERE player_id <> '$owner_id' AND source = $destination and time > '$decaydate' and destination!=0 ORDER BY time DESC", 1);
							db_op_result($resx,__LINE__,__FILE__);
							$myrow = $resx->fields;
							$count = $resx->RecordCount();
//							echo $count;
							if (!$myrow)
							{
								$warplinks.= " - $l_none<br>";
							}
							else
							{
								if($destination != 1)
								{
									if ($sensors >= $lssd_level_three)
									{
										$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $myrow['destination'], 1);
										db_op_result($resx,__LINE__,__FILE__);
										$myrow['destination'] = $resx->fields['sector_name'];
										$warplinks.= " - $l_probe2_player " . get_player($myrow['player_id']) . " $l_probe2_onboarda " . get_shipclassname($myrow['ship_class']) . " $l_probe2_classship $l_probe2_traveled " . $myrow['destination'] . " <br>";
									}
									elseif ($sensors >= $lssd_level_two)
									{
										$warplinks.= " - $l_probe2_player " . get_player($myrow['player_id']) . " $l_probe2_onboarda " . get_shipclassname($myrow['ship_class']) . " $l_probe2_classship. <br>";
									}
									else
									{
										$warplinks.= " - " . get_shipclassname($myrow['ship_class']) . " $l_probe2_classship. <br>";
									}
								}
								else
								{
									$warplinks.= " - $l_probe2_fedjammed <br>";
								}
							}
						}
						$result2->MoveNext();
					}
				}
			}else{
				$warplinks="";
			}
			// Last Ship Seen in sector
			$success = SCAN_SUCCESS($sensors, 100);
			$roll = mt_rand(1, 100);
			if ($roll < $success)
			{
				$oldstamp = strtotime(date("Y-m-d H:i:s")) - ($lss_decay_time * 86400);
				$decaydate = date("Y-m-d H:i:s", $oldstamp);
				$resx = $db->SelectLimit("SELECT * from {$db_prefix}sector_log WHERE player_id <> '$owner_id' AND source = $sector and time > '$decaydate' and destination!=0 ORDER BY time DESC", 1);
				db_op_result($resx,__LINE__,__FILE__);
				$myrow = $resx->fields;
				$lastship="";
				if (!$myrow)
				{
					$lastship.= "Last Ship Seen: $l_none<br>";
				}
				else
				{
					if($sector != 1)
					{
						if ($sensors >= $lssd_level_three)
						{
							$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $myrow['destination'], 1);
							db_op_result($resx,__LINE__,__FILE__);
							$myrow['destination'] = $resx->fields['sector_name'];
							$lastship.= "$l_probe2_lastseen: $l_probe2_player " . get_player($myrow['player_id']) . " $l_probe2_onboarda " . get_shipclassname($myrow['ship_class']) . " $l_probe2_classship $l_probe2_traveled " . $myrow['destination'] . " <br>";
						}
						elseif ($sensors >= $lssd_level_two)
						{
							$lastship.= "$l_probe2_lastseen: $l_probe2_player " . get_player($myrow['player_id']) . " $l_probe2_onboarda " . get_shipclassname($myrow['ship_class']) . " $l_probe2_classship. <br>";
						}
						else
						{
							$lastship.= "$l_probe2_lastseen: " . get_shipclassname($myrow['ship_class']) . " $l_probe2_classship. <br>";
						}
					}
					else
					{
						$lastship = "$l_probe2_fedjammed <br>";
					}
				}
			}else{
				$lastship="";
			}
			// Detect port and sun and warps
			$success = SCAN_SUCCESS($sensors, 50);
			$roll = mt_rand(1, 100);
			if ($roll < $success)
			{
				$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$sector'", 1);
				$query96 = $result2->fields;
				$port_type = $query96['port_type'];
				$star_size = $query96['star_size']; 
				$portinfo="$l_probe2_portfound: ".$port_type." - $l_probe2_supports ".$star_size." $l_probe2_planets.<br>";
			}
			else
			{
				$portinfo="";
			}
			$success = SCAN_SUCCESS($sensors, 150);
			$roll = mt_rand(1, 100);
			if ($roll < $success)
			{
				// Detect Sector defense
				$resultSDa = $db->Execute("SELECT SUM(quantity) as mines from {$db_prefix}sector_defense WHERE sector_id='$sector' and defense_type='mines'");
				$resultSDb = $db->Execute("SELECT SUM(quantity) as fighters from {$db_prefix}sector_defense WHERE sector_id='$sector' and defense_type='fighters'");
				$defM = $resultSDa->fields;
				$defF = $resultSDb->fields;
				$has_mines = NUMBER($defM['mines']);
				$has_fighters = NUMBER($defF['fighters']);
				$sector_def="$l_probe2_sectord: ".$has_mines." $l_probe2_mines ".$has_fighters." $l_probe2_fighters<br>";
			}
			else
			{
				$sector_def="";
			}
			// Detect ships
			$success = SCAN_SUCCESS($sensors, 100);
			$roll = mt_rand(1, 100);
			if ($roll < $success)
			{
				if ($sector != 0)
				{
					// get ships located in the scanned sector
					$result4 = $db->Execute("SELECT * FROM {$db_prefix}ships " .
										"LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id " .
										"WHERE sector_id='$sector' AND on_planet='N' and storage_planet_id=0");
					$shipdetect="";
					if ($result4->EOF)
					{
						$shipdetect.= "$l_probe2_ships: $l_none<br>";
					}
					else
					{
						$num_detected = 0;
						while (!$result4->EOF)
						{
							$row = $result4->fields;
							$result = $db->Execute("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]");
							db_op_result($result,__LINE__,__FILE__);

							while(!$result->EOF)
							{
								$devicename = $result->fields['device_name'];
								$targetshipdevice[$devicename] = $result->fields['amount'];
								$result->MoveNext();
							}
							// display other ships in sector - unless they are successfully cloaked
							$success = SCAN_SUCCESS($sensors, $row['cloak'], $shiptypes[$row['class']]['basehull']);
							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$num_detected++;
								$shipdetect.="$l_probe2_ships2 $num_detected: ".$row['name'] . "(" . $row['character_name'] . ") - ";
								// probe detect incoming ship
								// Get type of ship
			 					$roll = mt_rand(1, 100);
								$shiptype=$l_unknown;
								if ($roll < $success)
								{
									$res2 = $db->SelectLimit("SELECT name FROM {$db_prefix}ship_types WHERE type_id=$row[class]", 1);
									db_op_result($res2,__LINE__,__FILE__);
									$shiptype = $res2->fields['name'];
								}
//								$res3 = $db->SelectLimit("SELECT name FROM {$db_prefix}ship_types WHERE type_id=$row[class]", 1);
//								db_op_result($res3,__LINE__,__FILE__);
//								$shiptype = $res3->fields['name'];
								$shipdetect.="($shiptype)<br>";
								$roll = mt_rand(1, 100);
								//scan ship
								if($sensors > 1)
								{
									if ($roll < $success)
									{
										$sc_hull = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['hull']) : "???";
										$sc_engines = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['engines']) : "???";
										$sc_power = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['power']) : "???";
										$sc_fighter = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['fighter']) : "???";
										$sc_sensors = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['sensors']) : "???";
										$sc_beams = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['beams']) : "???";
										$sc_torp_launchers = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['torp_launchers']) : "???";
										$sc_armor = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['armor']) : "???";
										$sc_shields = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['shields']) : "???";
										$sc_cloak = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['cloak']) : "???";
										$sc_ecm = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $row['ecm']) : "???";
										$sc_armor_pts = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['armor_pts'])) : "???";
										$sc_ship_fighters = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['fighters'])) : "???";
										$sc_torps = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['torps'])) : "???";
										$sc_credits = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['credits'])) : "???";
										$sc_ship_energy = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['energy'])) : "???";
										$sc_dev_minedeflector = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $targetshipdevice['dev_minedeflector']['amount'])) : "???";
										$sc_dev_emerwarp = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $targetshipdevice['dev_emerwarp']['amount']) : "???";
										$sc_dev_pod = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $targetshipdevice['dev_escapepod']['amount']) : "???";
										$sc_ship_colonists = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['colonists'])) : "???";
										$sc_ship_ore = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['ore'])) : "???";
										$sc_ship_organics = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['organics'])) : "???";
										$sc_ship_goods = (mt_rand(1, 100) < $success) ? NUMBER(SCAN_ERROR($sensors, $row['cloak'], $row['goods'])) : "???";
										$sc_dev_warpedit = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $targetshipdevice['dev_warpedit']['amount']) : "???";
										$sc_dev_genesis = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $targetshipdevice['dev_genesis']['amount']) : "???";
										$sc_scoop = (mt_rand(1, 100) < $success) ? SCAN_ERROR($sensors, $row['cloak'], $targetshipdevice['dev_fuelscoop']['amount']) : "???";
										$shipdetect.="&nbsp;&nbsp;&nbsp;$l_hull: ".$sc_hull." $l_engines: ".$sc_engines." $l_power: ".$sc_power." $l_fighter: ".$sc_fighter." $l_sensors: ".$sc_sensors."<br>&nbsp;&nbsp;&nbsp;$l_beams: ".$sc_beams." $l_torp_launch: ".$sc_torp_launchers." $l_armor: ".$sc_armor." $l_shields: ".$sc_shields." $l_cloak: ".$sc_cloak." $l_ecm: ".$sc_ecm."<br>&nbsp;&nbsp;&nbsp;$l_armorpts: ".$sc_armor_pts." $l_fighters: ".$sc_ship_fighters." $l_torps: ".$sc_torps." $l_energy: ".$sc_ship_energy." $l_credits: ".$sc_credits."<br>&nbsp;&nbsp;&nbsp;$l_deflect: ".$sc_dev_minedeflector." $l_ewd: ".$sc_dev_emerwarp." $l_escape_pod: ".$sc_dev_pod."<br>";
									}
								}
							}
							$result4->MoveNext();
						}
						if (!$num_detected)
						{
							$shipdetect = "$l_probe2_ships: $l_none<br>";
						}
					}
				}
			}
			else
			{
				$shipdetect="";
			}

			$success = SCAN_SUCCESS($sensors, 50);
			$roll = mt_rand(1, 100);
			if ($roll < $success)
			{
				// Detect Planets
				$has_planets = 0;
				$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE sector_id='$sector' and owner!=$owner_id", 5);

				db_op_result($result3,__LINE__,__FILE__);
				$planetinfo="";
				if ($result3->RecordCount() ==0)
				{
		  			$planetinfo="$l_probe2_noneowned<br>";
			  	}

				$totalplanetsfound = 0;
				while (!$result3->EOF)
				{
					$uber = 0;
					$success = 0;
					$hiding_planet[$i] = $result3->fields;
					$powner=$hiding_planet[$i]['owner'];
//					echo $powner;
					// Get Char name
					$pname = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id = $powner", 1);
	 				db_op_result($pname,__LINE__,__FILE__);
					if ($pname)
					{
						$resn = $pname->fields;
						$playername = $resn['character_name'];
					}
					else
					{
						$playername=$l_unknown;
					}
					if ($hiding_planet[$i]['owner'] == $owner_id)
					{
						$uber = 1;
					}

					if ($hiding_planet[$i]['team'] != 0)
					{
						if ($hiding_planet[$i]['team'] == $owner_id)
						{
							$uber = 1;
						}
					}

					if ($sensors >= $hiding_planet[$i]['cloak'])
					{
						$uber = 1;
					}

					if ($uber == 0) //Not yet 'visible'
					{
						$success = SCAN_SUCCESS($sensors, $hiding_planet[$i]['cloak']);
						$roll = mt_rand(1, 100);
						if ($roll <= $success) // If able to see the planet
						{
							$uber = 1; //confirmed working
						}
						if ($uber == 0 && $enable_spies)  // Still not yet 'visible'
						{
							$res_s = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '" . $hiding_planet[$i]['planet_id'] . "' AND owner_id = '$playerinfo[player_id]'");
							if ($res_s->RecordCount())
							{
								$uber = 1;
							}
						}
					}

					if ($uber == 1)
					{
						$totalplanetsfound++;
						$planets[$i] = $result3->fields;
						$success = SCAN_SUCCESS($sensors, $hiding_planet[$i]['cloak'] / 2);
						$roll = mt_rand(1, 100);
						if ($roll > $success)
						{
							// if scan fails - inform both player and target. 
							$planetinfo.= "$l_planet_noscan<BR><BR>";
						}
						else
						{
							// scramble results by scan error factor. 
							if (empty($hiding_planet[$i]['name']))
							{
								$hiding_planet[$i]['name'] = $l_unnamed;
							}
							$preport = str_replace("[name]",$hiding_planet[$i]['name'] ,$l_planet_scn_report );
							$preport = str_replace("[owner]",$playername ,$preport );
							$planetinfo.= "$l_probe_planetname $totalplanetsfound: $preport<BR>";
							$planetinfo.= "&nbsp;&nbsp;&nbsp;$l_organics: ";
							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_organics=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['organics']));
								$planetinfo.= "$sc_planet_organics";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_ore: ";
							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_ore=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['ore']));
								$planetinfo.= "$sc_planet_ore";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_goods: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_goods=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['goods']));
								$planetinfo.= "$sc_planet_goods";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_energy: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_energy=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['energy']));
								$planetinfo.= "$sc_planet_energy";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_colonists: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_colonists=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['colonists']));
								$planetinfo.= "$sc_planet_colonists";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_credits: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_credits=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['credits']));
								$planetinfo.= "$sc_planet_credits";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= "<br><br>$l_defense:<br>";
							$planetinfo.= "&nbsp;&nbsp;&nbsp;$l_base: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$planetinfo.= $hiding_planet[$i]['base'];
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_torps: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_base_torp=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['torps']));
								$planetinfo.= "$sc_base_torp";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_fighters: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_fighters=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['fighters']));
								$planetinfo.= "$sc_planet_fighters";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= "<br>&nbsp;&nbsp;&nbsp;$l_planetary_fighter: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_planet_fighter=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['fighter']));
								$planetinfo.= "$sc_planet_fighter";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_beams: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_beams=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['beams']));
								$planetinfo.= "$sc_beams";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_torp_launch: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_torp_launchers=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['torp_launchers']));
								$planetinfo.= "$sc_torp_launchers";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_sensors: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_sensors=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['sensors']));
								$planetinfo.= "$sc_sensors";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= "<br>&nbsp;&nbsp;&nbsp;$l_planetary_cloak: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_cloak=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['cloak']));
								$planetinfo.= "$sc_cloak";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_shields: ";
							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_shields=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['shields']));
								$planetinfo.= "$sc_shields";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_jammer: ";
							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_jammer=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['jammer']));
								$planetinfo.= "$sc_jammer";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_armor: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_armor=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['armor']));
								$planetinfo.= "$sc_armor";
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_armorpts: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$sc_armor_pts=NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['armor_pts']));
								$planetinfo.= "$sc_armor_pts";
							}
							else
							{
								$planetinfo.= "???";
							}
//
							$planetinfo.= " - $l_planetary_SD_weapons: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$planetinfo.= NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['sector_defense_weapons']));
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_SD_sensors: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$planetinfo.= NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['sector_defense_sensors']));
							}
							else
							{
								$planetinfo.= "???";
							}
							$planetinfo.= " - $l_planetary_SD_cloak: ";

							$roll = mt_rand(1, 100);
							if ($roll < $success)
							{
								$planetinfo.= NUMBER(SCAN_ERROR($sensors, $hiding_planet[$i]['jammer'], $hiding_planet[$i]['sector_defense_cloak']));
							}
							else
							{
								$planetinfo.= "???";
							}
//
							$planetinfo.= "<BR>";
							$planet_id=$hiding_planet[$i]['planet_id'];
							$resa = $db->Execute("SELECT {$db_prefix}ships.class, {$db_prefix}ships.cloak, {$db_prefix}players.character_name FROM {$db_prefix}ships LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE on_planet = 'Y' and planet_id = $planet_id");
							db_op_result($resa,__LINE__,__FILE__);
							while (!$resa->EOF)
							{
								$row = $resa->fields;
								$success = SCAN_SUCCESS($sensors, $row['cloak'], $shiptypes[$row['class']]['basehull']);
								$roll = mt_rand(1, 100);

								if ($roll < $success)
								{
				 					$roll = mt_rand(1, 100);
									$shiptype=$l_unknown;
									if ($roll < $success)
									{
										$res2 = $db->SelectLimit("SELECT name FROM {$db_prefix}ship_types WHERE type_id=$row[class]", 1);
										db_op_result($res2,__LINE__,__FILE__);
										$shiptype = $res2->fields['name'];
									}
									$planetinfo.= "&nbsp;&nbsp;&nbsp;<B>$row[character_name] ($shiptype) $l_planet_ison</B><BR>";
								}
								$resa->MoveNext();
							}
//
							$planetinfo.= "<BR>";
							$planet_id=$hiding_planet[$i]['planet_id'];
							$resa = $db->Execute("SELECT {$db_prefix}ships.class, {$db_prefix}ships.cloak, {$db_prefix}players.character_name FROM {$db_prefix}ships LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE on_planet='N' and storage_planet_id = $planet_id");
							db_op_result($resa,__LINE__,__FILE__);
							while (!$resa->EOF)
							{
								$row = $resa->fields;
								$success = SCAN_SUCCESS($sensors, $row['cloak'], $shiptypes[$row['class']]['basehull']);
								$roll = mt_rand(1, 100);

								if ($roll < $success)
								{
				 					$roll = mt_rand(1, 100);
									$shiptype=$l_unknown;
									if ($roll < $success)
									{
										$res2 = $db->SelectLimit("SELECT name FROM {$db_prefix}ship_types WHERE type_id=$row[class]", 1);
										db_op_result($res2,__LINE__,__FILE__);
										$shiptype = $res2->fields['name'];
									}
									$planetinfo.= "&nbsp;&nbsp;&nbsp;<B>$row[character_name] ($shiptype) $l_main_shipyard1</B><BR>";
								}
								$resa->MoveNext();
							}
						}
						$has_planets++;
					}
					$planetinfo.="<br>";
					$i++;
					$result3->MoveNext();
				}
			}else{
				$planetinfo="";
			}
		}

		$probe_detect = array();
		$probe_detect['sectorlink'] = str_replace("[sector]","<a href=main.php?move_method=real&engage=1&destination=" . urlencode($sectorname) . ">$sectorname" . (($sector_sg == 0) ? "" : " - {SG}") . "</a>",$l_probe_scan);
		if ($warplinks!="")
		{
			$probe_detect['warplinks'] = $warplinks;
		}
		if ($lastship!="")
		{
			$probe_detect['lastship'] =  $lastship;
		}
		if ($portinfo!="") 
		{
			$probe_detect['portinfo'] =  $portinfo;
		}
		if ($sector_def!="")
		{
			$probe_detect['sector_def'] =  $sector_def;
		}
		if ($shipdetect!="")
		{
			$probe_detect['shipdetect'] =  $shipdetect;
		}
		if ($planetinfo!="")
		{
			$probe_detect['planetinfo'] =  $planetinfo;
		}
		return $probe_detect;
	}
}

?>