<?php
class megaplanet
{
	var $class = "megaplanet";
	var $pieces = 30;
	var $min_cloak = 350; // Cloak value of each artifact piece
	var $max_cloak = 410; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 0; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 1; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function megaplanet()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
			break;

			case "french":
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
			break;

			case "german":
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
			break;

			case "italian":
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
			break;

			case "russian":
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
			break;

			case "spanish":
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
			break;

			default:
				$this->classname = "Mega Planet Artifact";
				$this->description = "This Artifact will create a Mega Planet in a single planet Realspace Sector.  The planet will have 400 levels on techs, 60% of the maximum number of supported colonists and 300% energy production.  The fourth commodity will be Ship Hulls.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found the Mega Planet will be created.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  The Mega Planet has been created in sector [sector].";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
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
		global $db, $db_prefix, $playerinfo, $enable_spiral_galaxy, $universe_size, $spiral_galaxy_arms;

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
			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);

			$collisions = 0;
			# calculate the scale to use such that 
			# the max distance between 2 points will be
			# approx $universe_size.
			$scale = $universe_size / (4.0*pi());

			# compute the angle between arms
			$angle = deg2rad(360/$spiral_galaxy_arms);

			$sector = '';
			$collision = FALSE;
			while (TRUE) 
			{
				if($enable_spiral_galaxy != 1){
					// Lot of shortcuts here. Basically we generate a spherical coordinate and convert it to cartesian.
					// Why? Cause random spherical coordinates tend to be denser towards the center.
					// Should really be like a spiral arm galaxy but this'll do for now.
					$radius = mt_rand(100,$universe_size*100)/100;

					$temp_a = deg2rad(mt_rand(0,36000)/100-180);
					$temp_b = deg2rad(mt_rand(0,18000)/100-90);
					$temp_c = $radius*sin($temp_b);

					$sector['x'] = round(cos($temp_a)*$temp_c);
					$sector['y'] = round(sin($temp_a)*$temp_c);
					$sector['z'] = round($radius*cos($temp_b));
					$sector['spiral_arm'] = 0;

					// Collision check
					$debug_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe WHERE x=$sector[x] and y=$sector[y] and z=$sector[z] ", 1);
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();

					if ($debug_query->RecordCOunt() != 0) 
					{
						$collisions++;
					} 
					else 
					{
						break;
					}
				}
				else
				{
					//The Spiral Galaxy Code was proviced by "Kelly Shane Harrelson" <shane@mo-ware.com> 
					# need to randomly assign this point to an arm.
					$arm = mt_rand(0,$spiral_galaxy_arms-1);
					$arm_offset = $arm * $angle;

					# generate the logical position on the spiral (0 being closer to the center).
					# the double rand puts more towards the center.
					$u = deg2rad(mt_rand(0, mt_rand(0, 360)));

					# generate the base x,y,z location in cartesian form
					$bx = $u*cos($u+$arm_offset);
					$by = $u*sin($u+$arm_offset);
					$bz = 0.0;

					# generate a max delta from the base x, y, z.
					# this will be larger closer to the center,
					# tapering off the further out you are. 
					# this will create the bulge like effect in 
					# the center.	this is just a rough function
					# and there are probably better ones out there.
					$d = ($u<0.3) ? 1.5 : (log($u,10)*-1.0)+1.0;	# log base 10

					# generate random angles and distance for offsets from base x,y,z
					$dt = deg2rad(mt_rand(0, 360)); # angle theta 0-360
					$dp = deg2rad(mt_rand(0, 360)); # angle phi	0-360
					$dd = $d*mt_rand(1,100)/100;	 # distance	 0-$d

					# based on random angles and distance, generate cartesian offsets for base x,y,z
					$dx = $dd*sin($dt)*cos($dp);
					$dy = $dd*sin($dt)*sin($dp);
					$dz = $dd*cos($dt);

					# we want the arms to flatten out away from center
					$dz *= ($d/1.5);	

					# calcuate final cartesian coordinate 
					$x = $bx + $dx;
					$y = $by + $dy;
					$z = $bz + $dz;

					# now scale them to fit $universe_size
					$x *= $scale;
					$y *= $scale;
					$z *= $scale;

					$sector['x'] = $x;
					$sector['y'] = $y;
					$sector['z'] = $z;
					$sector['spiral_arm'] = $arm;

					// Collision check
					$debug_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe WHERE x=$sector[x] and y=$sector[y] and z=$sector[z] ", 1);
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();

					if ($debug_query->RecordCOunt() != 0) 
					{
						$collisions++;
					}
					else 
					{
						break;
					}
				}
			}

			$stamp = date("Y-m-d H:i:s");
			$sectorname = $this->create_sector_number(chr(80 + $sector['spiral_arm']) . "1");

			$res = $db->Execute("INSERT INTO {$db_prefix}universe (zone_id, star_size, x, y, z, spiral_arm, port_type, creation_date, sector_name) VALUES (1, 1, $sector[x], $sector[y], $sector[z], $sector[spiral_arm], 'none', '$stamp', " . $db->qstr($sectorname) . ") ");
			db_op_result($res,__LINE__,__FILE__);
			$sector_id = $db->insert_id();
			$res->close();

			$debug_query = $db->Execute("INSERT INTO `aatrade_planets` (`sector_id`, `name`, `owner`, `team`, `base`, `defeated`, `fighter`, `fighter_normal`, `fighter_class`, `sensors`, `sensors_normal`, `beams`, `beams_normal`, `beam_class`, `torp_launchers`, `torp_launchers_normal`, `torp_class`, `shields`, `shields_normal`, `shield_class`, `jammer`, `jammer_normal`, `armor`, `armor_normal`, `armor_class`, `cloak`, `cloak_normal`, `sector_defense_weapons`, `sector_defense_weapons_normal`, `sector_defense_sensors`, `sector_defense_sensors_normal`, `sector_defense_cloak`, `sector_defense_cloak_normal`, `team_cash`, `colonists`, `organics`, `organics_planet`, `ore`, `ore_planet`, `goods`, `goods_planet`, `energy`, `energy_planet`, `fighters`, `torps`, `armor_pts`, `credits`, `max_credits`, `special_name`, `special_amount`, `special_goodevil`, `prod_special`, `prod_organics`, `prod_ore`, `prod_goods`, `prod_energy`, `prod_fighters`, `prod_torp`, `prod_research`, `prod_build`, `cargo_hull`, `cargo_power`, `mission_id`, `creation_date`, `last_visited`, `creator_id`, `use_age`, `hidden_credits`, `captured_countdown`, `persuasion_countdown`, `last_owner_rating`, `personality`) VALUES
										($sector_id, 'Mega Planet', $playerinfo[player_id], $playerinfo[team], 'Y', 'N', 400, 400, 'Planet_Fighter', 400, 400, 400, 400, 'Planet_Beam', 400, 400, 'Planet_Torpedo', 400, 400, 'Planet_Shield', 400, 400, 0, 0, 'Planet_Armor', 400, 400, 400, 400, 400, 400, 400, 400, 'Y', 0, 0, 1.00000, 0, 1.00000, 0, 1.00000, 0, 3.00000, 0, 0, 1, 0, 118956509006240, 'ship hulls', 0, 1, 0, 20, 20, 20, 20, 10, 10, 0, 0, 0, 0, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', 0, 0, 0, 0, 0, 0, 0);");
    		db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();

			$findem = $db->Execute("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 3");
			$sector_list_total=$findem->RecordCount(); 
			$sector_list=$findem->GetArray();
			$findem->close();

			$numlinks = mt_rand(0,5);
			for ($j = 0; $j < $numlinks; $j++)
			{
				$randplay=mt_rand(0,($sector_list_total-1));
				$destination = $sector_list[$randplay]['sector_id'];

				$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES ($sector_id,$destination);");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
				$link_odds = mt_rand(0,100);
				if ($link_odds < 50)
				{
					$result4 = $db->Execute(" SELECT * FROM {$db_prefix}links where link_start=$destination");
					db_op_result($result4,__LINE__,__FILE__);

					$totalcount = $result4->RecordCount();
					$result4->close();
					if($totalcount <= 5){
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES ($destination,$sector_id);");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query->close();
					}
				}
			}
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}navmap");
			db_op_result($debug_query,__LINE__,__FILE__);

			insert_news($this->classname . "|" . $playerinfo['character_name'], 1, "artifact");
   			$success = str_replace("[planet]" , "Mega Planet", $this->success);
   			$success = str_replace("[sector]" , $sectorname, $success);
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

	function create_sector_number($prefix)
	{
		global $db, $db_prefix;

		$alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		$newname = $prefix . AAT_substr($alphanumeric, mt_rand(26, 35), 1) . AAT_substr($alphanumeric, mt_rand(0, 35), 1) . AAT_substr($alphanumeric, mt_rand(26, 35), 1) . AAT_substr($alphanumeric, mt_rand(0, 35), 1) . AAT_substr($alphanumeric, mt_rand(0, 35), 1);
		$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($newname), 1);
		db_op_result($sector_check,__LINE__,__FILE__);

		if($sector_check->RecordCount() != 0)
		{
			create_sector_number($prefix);
		} 
		else 
		{
			return $newname;
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