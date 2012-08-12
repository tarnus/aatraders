<?php
class dreadnought
{
	var $class = "dreadnought";
	var $pieces = 30;
	var $min_cloak = 350; // Cloak value of each artifact piece
	var $max_cloak = 410; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 0; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 1; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function dreadnought()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;

			case "french":
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;

			case "german":
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;

			case "italian":
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;

			case "russian":
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;

			case "spanish":
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;

			default:
				$this->classname = "Dreadnought Artifact";
				$this->description = "This Artifact will summon a Stripped-Down Federation Battle Cruiser.  The Battle Cruiser has 400 tech levels and can be upgraded to 900.  The Battle Cruiser will NOT include fighters, mines, armor, energy, mine deflectors, escape pod or any other device.  When summoned the Battle Cruiser will appear in storage on your Home Planet.  If you don't have a home planet a based planet will be randomly picked to store the Battle Cruiser.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Battle Cruiser will be summoned.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The ship has been summoned and stored on planet [planet] in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noplanets = "You do not own any planets to store the Dreadnought.  You lose the Dreadnought and all collected Dreadnought Artifact pieces.";
			break;
		}
	}

	function sched_process_artifact($artifact_type)
	{
		global $db, $db_prefix, $adminexecuted;

		include ("globals/artifacts_sched.inc");

		if($adminexecuted == 1)
		{
			TextFlush ( "<b>" . ucwords($artifact_type) . " Artifact Added</b><br>");
		}

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);

 		$totalpieces = ($this->pieces * $this->maximum_in_galaxy) - $res->fields['total'];
		for ($i = 1; $i <= $totalpieces; $i++)
		{
			artifacts_sched($artifact_type, $this->min_cloak, $this->max_cloak, $this->scoremax, $i);
		}
	}

	function found_artifact_piece($artifact_id)
	{
		global $db, $db_prefix, $playerinfo, $start_armor, $start_energy, $start_fighters;

		include ("globals/insert_news.inc");

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
			$updateit = $db->Execute("UPDATE {$db_prefix}artifacts SET on_port=0, on_planet_id=0, sector_id=0, player_id = $playerinfo[player_id] WHERE artifact_id=$artifact_id");
    		db_op_result($updateit,__LINE__,__FILE__);
    		$res->fields['total']++;
    	}

   		if($res->fields['total'] == $this->pieces)
   		{
   			if($playerinfo['home_planet_id'] == 0)
   			{
				$findem = $db->SelectLimit("SELECT sector_id, planet_id, name FROM {$db_prefix}planets where owner = " . $playerinfo['player_id'] . " ORDER BY rand()", 1);
		   		db_op_result($findem,__LINE__,__FILE__);
				$home_sector = $findem->fields['sector_id'];
				$home_planet_id = $findem->fields['planet_id'];
				$home_planet_name = $findem->fields['name'];
				if($findem->RecordCount() == 0)
				{
					return $this->noplanets;
				}
   			}
   			else
   			{
 				$findem = $db->SelectLimit("SELECT sector_id, name FROM {$db_prefix}planets where planet_id = $playerinfo[home_planet_id]", 1);
		   		db_op_result($findem,__LINE__,__FILE__);
  				$home_planet_id = $playerinfo['home_planet_id'];
				$home_sector = $findem->fields['sector_id'];
				$home_planet_name = $findem->fields['name'];
   			}
			$findem = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe where sector_id = $home_sector", 1);
	   		db_op_result($findem,__LINE__,__FILE__);
			$sector_name = $findem->fields['sector_name'];

			$res = $db->SelectLimit("SELECT basehull FROM {$db_prefix}ship_types WHERE type_id = 100", 1);
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
									ecm_normal,
									storage_planet_id
									)
									VALUES(" .
									"$playerinfo[player_id]," .		 // player_id
									"'100'," .					   // class
									$db->qstr("The Dreadnought") . "," .					// name
									"$shipdata[basehull]," .				// basehull
									"400," .				// hull
									"400," .			 // engines
									"400," .			   // power
									"400," .			// fighter
									"400," .			 // sensors
									"400," .			   // beams
									"400," .	  // torp_launchers
									"0," .							  // torps
									"400," .			 // shields
									"400," .			  // armor
									"$start_armor," .				  // armor_pts
									"400," .			   // cloak
									"400," .				// ecm
									"$home_sector," .		   // sector_id
									"$start_energy," .				  // energy
									"$start_fighters," .				// fighters
									"'Y'," .							// on_planet
									"0," .							  // planet_id
									"'', " .							 // cleared_defenses
									"400," .				// hull
									"400," .			 // engines
									"400," .			   // power
									"400," .			// fighter
									"400," .			 // sensors
									"400," .			   // beams
									"400," .	  // torp_launchers
									"400," .			 // shields
									"400," .			  // armor
									"400," .			   // cloak
									"400," .				// ecm
									"$home_planet_id" .
									")");

			db_op_result($debug_query,__LINE__,__FILE__);

			//get new ship_id
			$res = $db->SelectLimit("SELECT max(ship_id) as ship_id from {$db_prefix}ships WHERE player_id=$playerinfo[player_id]" .
								" AND class='100'", 1);
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

					$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_devices (player_id, ".
												"ship_id, class, device_name, cargo_class, program, techmodify, ".
												"amount) VALUES(" .
												"'$playerinfo[player_id]'," .
												"'$ship_id'," .
												"'" . $device_classname . "'," .
												"'" . $device_object->classname . "'," .
												"'" . $device_object->cargoclass . "'," .
												"'" . $device_object->program . "'," .
												"'" . $device_object->techmodify . "'," .
												"'0'" .
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

			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);
			insert_news($this->classname . "|" . $playerinfo['character_name'], 1, "artifact");
   			$success = str_replace("[planet]" , $home_planet_name, $this->success);
   			$success = str_replace("[sector]" , $sector_name, $success);
   			return $success;
   		}
   		else
   		{
   			$incomplete = str_replace("[pieces]", $res->fields['total'], $this->incomplete);
   			$left = $this->pieces - $res->fields['total'];
   			$incomplete = str_replace("[left]", $left, $incomplete);
  			if($left == 1)
   			{
   				$incomplete = str_replace("[piece]", $this->singular, $incomplete);
   				$pieces = $this->singular;
   			}
   			else
   			{
   				$incomplete = str_replace("[piece]", $this->plural, $incomplete);
    			$pieces = $this->plural;
  			}
			insert_news($this->classname . "|" . $playerinfo['character_name'] . "|$left|$pieces", 1, "artifactfound");
   			return $incomplete;
   		}
	}

	function preprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo;
	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo;
	}
}

?>