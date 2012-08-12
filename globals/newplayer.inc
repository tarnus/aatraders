<?php
if (!function_exists('newplayer')) {

	function newplayer($email, $char, $pass, $ship_name, $npclevel=0, $player_id=0, $admin=0)
	{
		global $db, $db_prefix, $db_type;
		global $start_credits, $start_credits_modifier, $start_turns, $default_lang, $random_default_template, $default_template_alt, $start_ship_class;
		global $start_armor, $start_energy, $start_fighters, $max_turns, $default_template;

		$stamp = date("Y-m-d H:i:s");

		$credit_query = $db->Execute("SELECT avg(score) as scores FROM {$db_prefix}players where player_id > 3 and npc = 0");
		db_op_result($credit_query,__LINE__,__FILE__);
		$start_credits = $start_credits + floor($credit_query->fields['scores'] * $start_credits_modifier);

		$query = $db->Execute("SELECT MAX(turns_used + turns) AS mturns FROM {$db_prefix}players");
		db_op_result($query,__LINE__,__FILE__);
		$res = $query->fields;
		$query->close();

		$mturns = min(max($res['mturns'], $start_turns), $max_turns);

		if($player_id != 0)
		{
			$query = $db->Execute("delete FROM {$db_prefix}players where player_id = $player_id");
			$query = $db->Execute("delete FROM {$db_prefix}ships where player_id = $player_id");

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}players (player_id, currentship, ".
										"character_name, password, email, credits, turns, ".
										"turns_used, signup_date, last_login, rating, ".
										"score, team, team_invite, ip_address, langdir, 
										 template, avatar, npc, admin, destroyed) VALUES(" .
										"$player_id," .			 //player_id
										"$player_id," .				//currentship
										$db->qstr($char) . "," .		//character_name
										"'$pass'," .		//password
										"'$email'," .		//email
										"$start_credits," . //credits
										"$mturns," .		//turns
										"0," .				//turns_used
										"'$stamp'," .		//last_login
										"'$stamp'," .		//last_login
										"0," .				//rating
										"0," .				//score
										"0," .				//team
										"0," .				//team_invite
										"'". getenv("REMOTE_ADDR") ."'," .			//ip_address
										"'$default_lang'," .
										"'$default_template',
										'default_avatar.gif', 1, $admin, 'N')");
			db_op_result($debug_query,__LINE__,__FILE__);

			// Create player's ship 
			$res = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id = $start_ship_class", 1);
			db_op_result($res,__LINE__,__FILE__);
			$shipdata = $res->fields;
			$res->close();
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}ships 
									(player_id,
									class,
									name,
									basehull,
									hull,
									engines,
									power,
									fighter,
									sensors,
									beams,
									torp_launchers,
									torps,
									shields,
									armor,
									armor_pts,
									cloak,
									ecm,
									sector_id,
									energy,
									fighters,
									on_planet,
									planet_id,
									cleared_defenses,
									hull_normal,
									engines_normal,
									power_normal,
									fighter_normal,
									sensors_normal,
									beams_normal,
									torp_launchers_normal,
									shields_normal,
									armor_normal,
									cloak_normal,
									ecm_normal
									)
									VALUES(" .
									"$player_id," .		 // player_id
									"'$start_ship_class'," .					   // class
									$db->qstr($ship_name) . "," .					// name
									"$shipdata[basehull]," .				// basehull
									"$shipdata[minhull]," .				// hull
									"$shipdata[minengines]," .			 // engines
									"$shipdata[minpower]," .			   // power
									"$shipdata[minfighter]," .			// fighter
									"$shipdata[minsensors]," .			 // sensors
									"$shipdata[minbeams]," .			   // beams
									"$shipdata[mintorp_launchers]," .	  // torp_launchers
									"0," .							  // torps
									"$shipdata[minshields]," .			 // shields
									"$shipdata[minarmor]," .			  // armor
									"$start_armor," .				  // armor_pts
									"$shipdata[mincloak]," .			   // cloak
									"$shipdata[minecm]," .				// ecm
									"1," .		   // sector_id
									"$start_energy," .				  // energy
									"$start_fighters," .				// fighters
									"'N'," .							// on_planet
									"0," .							  // planet_id
									"'', " .							 // cleared_defenses
									"$shipdata[minhull]," .				// hull
									"$shipdata[minengines]," .			 // engines
									"$shipdata[minpower]," .			   // power
									"$shipdata[minfighter]," .			// fighter
									"$shipdata[minsensors]," .			 // sensors
									"$shipdata[minbeams]," .			   // beams
									"$shipdata[mintorp_launchers]," .	  // torp_launchers
									"$shipdata[minshields]," .			 // shields
									"$shipdata[minarmor]," .			  // armor
									"$shipdata[mincloak]," .			   // cloak
									"$shipdata[minecm]" .				// ecm
									")");

			db_op_result($debug_query,__LINE__,__FILE__);
			$ship_id = $player_id;

			$filelist = get_dirlist($gameroot."class/devices/");
			for ($c=0; $c<count($filelist); $c++) {
				if($filelist[$c] != "index.html")
				{
					$device_classname =  str_replace(".inc", "", $filelist[$c]); 
					if(!class_exists($device_classname)){
						include ("class/devices/" . $device_classname . ".inc");
					}
					$device_object = new $device_classname();

					$amount = 0;
					if($device_classname == 'dev_escapepod')
					{
						$amount = 1;
					}
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_devices (player_id, ".
												"ship_id, class, device_name, cargo_class, program, techmodify, ".
												"amount) VALUES(" .
												"'$player_id'," .
												"'$ship_id'," .
												"'" . $device_classname . "'," .
												"'" . $device_object->classname . "'," .
												"'" . $device_object->cargoclass . "'," .
												"'" . $device_object->program . "'," .
												"'" . $device_object->techmodify . "'," .
												"'$amount'" .
												")");
					db_op_result($debug_query,__LINE__,__FILE__);
				}
			}

			$result2 = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities");
			while (!$result2->EOF) 
			{
				$row2 = $result2->fields;
				$amount = 0;
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_holds (".
											"ship_id, class, cargo_name, cargo_class, hold_space,".
											"amount) VALUES(" .
											"'$ship_id'," .
											"'$row2[class]'," .
											"'$row2[classname]'," .
											"'$row2[cargoclass]'," .
											"'$row2[hold_space]'," .
											"'$amount'" .
											")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$result2->Movenext();
			}
			$result2->close();
		}
		else
		{

			$zonecolor = "#" . sprintf("%02X%02X%02X", 50 + mt_rand(0, 205), 50 + mt_rand(0, 205), 50 + mt_rand(0, 205));

			if (mt_rand(0, 100) < 50 && $random_default_template)
			{
				$pick_template = $default_template_alt;
			}else{
				$pick_template = $default_template;
			}

			//Create player
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}players (currentship, ".
										"character_name, password, email, credits, turns, ".
										"turns_used, signup_date, last_login, rating, ".
										"score, team, team_invite, ip_address, langdir, 
										template, avatar, destroyed) VALUES(" .
										"0," .			  //currentship
										$db->qstr($char) . "," .		//character_name
										"'$pass'," .		//password
										"'$email'," .	   //email
										"$start_credits," . //credits
										"$mturns," .		//turns
										"0," .			  //turns_used
										"'$stamp'," .	   //last_login
										"'$stamp'," .	   //last_login
										"0," .			  //rating
										"0," .			  //score
										"0," .			  //team
										"0," .			  //team_invite
										"'". getenv("REMOTE_ADDR") ."'," .		  //ip_address
										"'$default_lang'," .
										"'$pick_template',
										'default_avatar.gif', 'N')");
			db_op_result($debug_query,__LINE__,__FILE__);

			// Get the new player's id
			$res = $db->Execute("SELECT player_id from {$db_prefix}players WHERE email='$email'");
			db_op_result($res,__LINE__,__FILE__);
			$player_id = $res->fields['player_id'];
			$res->close();

			// Create player's ship
			if($npclevel == 0)
			{
				$res = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id = $start_ship_class", 1);
				db_op_result($res,__LINE__,__FILE__);
				$shipdata = $res->fields;
				$res->close();
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}ships 
									(player_id,
									class,
									name,
									basehull,
									hull,
									engines,
									power,
									fighter,
									sensors,
									beams,
									torp_launchers,
									torps,
									shields,
									armor,
									armor_pts,
									cloak,
									ecm,
									sector_id,
									energy,
									fighters,
									on_planet,
									planet_id,
									cleared_defenses,
									hull_normal,
									engines_normal,
									power_normal,
									fighter_normal,
									sensors_normal,
									beams_normal,
									torp_launchers_normal,
									shields_normal,
									armor_normal,
									cloak_normal,
									ecm_normal
									)
									VALUES(" .
									"$player_id," .		 // player_id
									"'$start_ship_class'," .					   // class
									$db->qstr($ship_name) . "," .					// name
									"$shipdata[basehull]," .				// basehull
									"$shipdata[minhull]," .				// hull
									"$shipdata[minengines]," .			 // engines
									"$shipdata[minpower]," .			   // power
									"$shipdata[minfighter]," .			// fighter
									"$shipdata[minsensors]," .			 // sensors
									"$shipdata[minbeams]," .			   // beams
									"$shipdata[mintorp_launchers]," .	  // torp_launchers
									"0," .							  // torps
									"$shipdata[minshields]," .			 // shields
									"$shipdata[minarmor]," .			  // armor
									"$start_armor," .				  // armor_pts
									"$shipdata[mincloak]," .			   // cloak
									"$shipdata[minecm]," .				// ecm
									"1," .		   // sector_id
									"$start_energy," .				  // energy
									"$start_fighters," .				// fighters
									"'N'," .							// on_planet
									"0," .							  // planet_id
									"'', " .							 // cleared_defenses
									"$shipdata[minhull]," .				// hull
									"$shipdata[minengines]," .			 // engines
									"$shipdata[minpower]," .			   // power
									"$shipdata[minfighter]," .			// fighter
									"$shipdata[minsensors]," .			 // sensors
									"$shipdata[minbeams]," .			   // beams
									"$shipdata[mintorp_launchers]," .	  // torp_launchers
									"$shipdata[minshields]," .			 // shields
									"$shipdata[minarmor]," .			  // armor
									"$shipdata[mincloak]," .			   // cloak
									"$shipdata[minecm]" .				// ecm
									")");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			else
			{
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}ships (player_id, ".
											"class, name, basehull, hull, engines, ".
											"power, fighter, sensors, beams, ".
											"torp_launchers, torps, shields, armor, ".
											"armor_pts, cloak, ecm, sector_id, ".
											"energy, ".
											"fighters, on_planet, planet_id, ".
											"cleared_defenses) VALUES(" .
											"'$player_id'," .	 //player_id
											"'10'," .			//class
											$db->qstr($ship_name) . "," .   //name
											"10,".				//basehull
											"$npclevel," .			  //hull
											"$npclevel," .			  //engines
											"$npclevel," .			  //power
											"$npclevel," .			  //fighter
											"$npclevel," .			  //sensors
											"$npclevel," .			  //beams
											"$npclevel," .			  //torp_launchers
											"$npclevel," .			  //torps
											"$npclevel," .			  //shields
											"$npclevel," .			  //armor
											"$start_armor," .  //armor_pts
											"$npclevel," .			  //cloak
											"$npclevel," .			  //ecm
											"1," .			  //sector_id
											"$start_energy," .  //energy
											"$start_fighters," .//fighters
											"'N'," .			//on_planet
											"0," .			  //planet_id
											"''" .			 //cleared_defenses
											")");
				db_op_result($debug_query,__LINE__,__FILE__);
			}

			// Get the new ship's id
			$res = $db->Execute("SELECT ship_id from {$db_prefix}ships WHERE player_id=$player_id");
			db_op_result($res,__LINE__,__FILE__);
			$ship_id = $res->fields['ship_id'];
			$res->close();

			$filelist = get_dirlist($gameroot."class/devices/");
			for ($c=0; $c<count($filelist); $c++) {
				if($filelist[$c] != "index.html")
				{
					$device_classname =  str_replace(".inc", "", $filelist[$c]); 
					if(!class_exists($device_classname)){
						include ("class/devices/" . $device_classname . ".inc");
					}
					$device_object = new $device_classname();

					$amount = 0;
					if($device_classname == 'dev_escapepod')
					{
						$amount = 1;
					}
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_devices (player_id, ".
												"ship_id, class, device_name, cargo_class, program, techmodify, " .
												"amount) VALUES(" .
												"'$player_id'," .
												"'$ship_id'," .
												"'" . $device_classname . "'," .
												"'" . $device_object->classname . "'," .
												"'" . $device_object->cargoclass . "'," .
												"'" . $device_object->program . "'," .
												"'" . $device_object->techmodify . "'," .
												"'$amount'" .
												")");
					db_op_result($debug_query,__LINE__,__FILE__);
				}
			}

			$result2 = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities");
			while (!$result2->EOF) 
			{
				$row2 = $result2->fields;
				$amount = 0;
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_holds (".
											"ship_id, class, cargo_name, cargo_class, hold_space,".
											"amount) VALUES(" .
											"'$ship_id'," .
											"'$row2[class]'," .
											"'$row2[classname]'," .
											"'$row2[cargoclass]'," .
											"'$row2[hold_space]'," .
											"'$amount'" .
											")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$result2->Movenext();
			}
			$result2->close();

			// Insert current ship in players table
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET currentship=$ship_id WHERE player_id=$player_id");
			db_op_result($debug_query,__LINE__,__FILE__);

			// Create player's zone
			$zone_name = "$char" . "'s Territory";
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}zones (zone_name, ".
										"owner, team_zone, allow_attack, ".
										"allow_planetattack, allow_warpedit, ".
										"allow_planet, allow_trade, allow_defenses, ".
										"max_hull, zone_color) VALUES(" .
										$db->qstr($zone_name) . "," .   //zone_name
										"'$player_id'," .	 //owner
										"'N'," .			//team_zone
										"'Y'," .			//allow_attack
										"'Y'," .			//allow_planetattack
										"'Y'," .			//allow_warpedit
										"'Y'," .			//allow_planet
										"'Y'," .			//allow_trade
										"'Y'," .			//allow_defenses
										"0," .			   //max_hull
										"'$zonecolor'" .			   //player color
										")");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		for($total = 0; $total < 3; $total++){
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}presets (player_id,preset) VALUES ('$player_id','Sol')");	 
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		$stamp = date("Y-m-d H:i:s");	 
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ibank_accounts (player_id,balance,loan,loantime) VALUES ('$player_id',0,0,'$stamp')");	 
		db_op_result($debug_query,__LINE__,__FILE__);

		return $player_id;
	}
}
?>