<?php
include ("globals/player_ship_destroyed.inc");

class boobytrap {
	var $classname = "boobytrap";
	var $success = "1600";	// Random value range
	var $trigger = "800";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_zeroship;
	var $l_debris_destroyship;

	// fill language variables
	function boobytrap()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;

			case "french":
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;

			case "german":
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;

			case "italian":
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;

			case "russian":
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;

			case "spanish":
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;

			default:
				$this->l_debris_boobytrap = "The debris has been BOOBY TRAPPED!  Your ship suffers massive damage!<br><br>[hull] drops to [newhull]<br>[engines] drops to [newengines]<br>[power] drops to [newpower]<br>[fighter] drops to [newfighter]<br>[sensors] drops to [newsensors]<br>[beams] drops to [newbeams]<br>[torp_launchers] drops to [newtorp_launchers]<br>[shields] drops to [newshields]<br>[cloak] drops to [newcloak]<br>[armor] drops to [newarmor]<br>[armor_pts] drops to [newarmor_pts]<br>[torps] drops to [newtorps]<br>[fighters] drops to [newfighters]<br>[energy] drops to [newenergy]<br>[ecm] drops to [newecm]<br>";
			break;
		}
	}
 
	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo, $shipdevice, $playerinfo, $start_armor, $start_energy, $start_fighters;

		$debrismessage = str_replace("[hull]", $shipinfo['hull'], $this->l_debris_boobytrap);
		$debrismessage = str_replace("[engines]", $shipinfo['engines'], $debrismessage);
		$debrismessage = str_replace("[power]", $shipinfo['power'], $debrismessage);
		$debrismessage = str_replace("[fighter]", $shipinfo['fighter'], $debrismessage);
		$debrismessage = str_replace("[sensors]", $shipinfo['sensors'], $debrismessage);
		$debrismessage = str_replace("[beams]", $shipinfo['beams'], $debrismessage);
		$debrismessage = str_replace("[torp_launchers]", $shipinfo['torp_launchers'], $debrismessage);
		$debrismessage = str_replace("[shields]", $shipinfo['shields'], $debrismessage);
		$debrismessage = str_replace("[cloak]", $shipinfo['cloak'], $debrismessage);
		$debrismessage = str_replace("[armor]", $shipinfo['armor'], $debrismessage);
		$debrismessage = str_replace("[armor_pts]", $shipinfo['armor_pts'], $debrismessage);
		$debrismessage = str_replace("[torps]", $shipinfo['torps'], $debrismessage);
		$debrismessage = str_replace("[fighters]", $shipinfo['fighters'], $debrismessage);
		$debrismessage = str_replace("[energy]", $shipinfo['energy'], $debrismessage);
		$debrismessage = str_replace("[ecm]", $shipinfo['ecm'], $debrismessage);

		$techdamage = (mt_rand(50, 75) * 0.01);
		$shipinfo['hull'] = floor($shipinfo['hull'] * $techdamage);
		$shipinfo['engines'] = floor($shipinfo['engines'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['power'] = floor($shipinfo['power'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['fighter'] = floor($shipinfo['fighter'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['sensors'] = floor($shipinfo['sensors'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['beams'] = floor($shipinfo['beams'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['torp_launchers'] = floor($shipinfo['torp_launchers'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['shields'] = floor($shipinfo['shields'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['cloak'] = floor($shipinfo['cloak'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['armor'] = floor($shipinfo['armor'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['armor_pts'] = floor($shipinfo['armor_pts'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['torps'] = floor($shipinfo['torps'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['fighters'] = floor($shipinfo['fighters'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['energy'] = floor($shipinfo['energy'] * (mt_rand(50, 75) * 0.01));
		$shipinfo['ecm'] = floor($shipinfo['ecm'] * (mt_rand(50, 75) * 0.01));

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET hull=$shipinfo[hull], engines=$shipinfo[engines], 
		power=$shipinfo[power], fighter=$shipinfo[fighter], sensors=$shipinfo[sensors], beams=$shipinfo[beams], 
		torp_launchers=$shipinfo[torp_launchers], shields=$shipinfo[shields], cloak=$shipinfo[cloak], 
		armor=$shipinfo[armor], armor_pts=$shipinfo[armor_pts], torps=$shipinfo[torps], fighters=$shipinfo[fighters], 
		energy=$shipinfo[energy], ecm=$shipinfo[ecm] WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=amount * $techdamage WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$debrismessage = str_replace("[newhull]", $shipinfo['hull'], $debrismessage);
		$debrismessage = str_replace("[newengines]", $shipinfo['engines'], $debrismessage);
		$debrismessage = str_replace("[newpower]", $shipinfo['power'], $debrismessage);
		$debrismessage = str_replace("[newfighter]", $shipinfo['fighter'], $debrismessage);
		$debrismessage = str_replace("[newsensors]", $shipinfo['sensors'], $debrismessage);
		$debrismessage = str_replace("[newbeams]", $shipinfo['beams'], $debrismessage);
		$debrismessage = str_replace("[newtorp_launchers]", $shipinfo['torp_launchers'], $debrismessage);
		$debrismessage = str_replace("[newshields]", $shipinfo['shields'], $debrismessage);
		$debrismessage = str_replace("[newcloak]", $shipinfo['cloak'], $debrismessage);
		$debrismessage = str_replace("[newarmor]", $shipinfo['armor'], $debrismessage);
		$debrismessage = str_replace("[newarmor_pts]", $shipinfo['armor_pts'], $debrismessage);
		$debrismessage = str_replace("[newtorps]", $shipinfo['torps'], $debrismessage);
		$debrismessage = str_replace("[newfighters]", $shipinfo['fighters'], $debrismessage);
		$debrismessage = str_replace("[newenergy]", $shipinfo['energy'], $debrismessage);
		$debrismessage = str_replace("[newecm]", $shipinfo['ecm'], $debrismessage);
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$debris_data = (mt_rand(0, 1) == 1) ? -1 : 1;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$debris_data = (mt_rand(0, 1) == 1) ? -1 : 1;
		return $debris_data;
	}
}

?>