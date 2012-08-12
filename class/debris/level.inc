<?php
class level {
	var $classname = "level";
	var $success = "400";	// Random value range
	var $trigger = "200";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_upgradelevel;
	var $l_debris_degradelevel;

	// fill language variables
	function level()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_upgradelevel = "You have found an upgrade package that will upgrade the [tech] by [levels] levels.";
				$this->l_debris_degradelevel = "You have found a Nanite Cluster that attacks your [tech] tech and destroys [levels] before you can stop it.";
			break;

			case "french":
				$this->l_debris_upgradelevel = "Vous avez trouvé un ensemble de mise à jour qui améliorera la technologie [tech] de [levels] niveaux.";
				$this->l_debris_degradelevel = "Vous avez trouvé un contenant de nanorobots anti-[tech] qui parviennent à détruire [levels] niveaux avant que vous les éliminiez.";
			break;

			case "german":
				$this->l_debris_upgradelevel = "Sie haben ein Nachrüstungsbündel gefunden welches den [tech] um [levels] Levels erhöht.";
				$this->l_debris_degradelevel = "Sie haben einen Nanit-Cluster gefunden, der Sie attackiert hat und [levels] [tech] tech zerstörte, bevor Sie ihn aufhalten konnten.";
			break;

			case "italian":
				$this->l_debris_upgradelevel = "Hai trovato un sistema di potenziamento che aggiorna il sistema [tech] di [levels] livelli.";
				$this->l_debris_degradelevel = "Sei incappato in un gruppo di Naniti che attaccano il tuo sistema [tech] e ti tolgono [levels] livelli di tecnologia, prima di essere distrutti.";
			break;

			case "russian":
				$this->l_debris_upgradelevel = "You have found an upgrade package that will upgrade the [tech] by [levels] levels.";
				$this->l_debris_degradelevel = "You have found a Nanite Cluster that attacks your [tech] tech and destroys [levels] before you can stop it.";
			break;

			case "spanish":
				$this->l_debris_upgradelevel = "You have found an upgrade package that will upgrade the [tech] by [levels] levels.";
				$this->l_debris_degradelevel = "You have found a Nanite Cluster that attacks your [tech] tech and destroys [levels] before you can stop it.";
			break;

			default:
				$this->l_debris_upgradelevel = "You have found an upgrade package that will upgrade the [tech] by [levels] levels.";
				$this->l_debris_degradelevel = "You have found a Nanite Cluster that attacks your [tech] tech and destroys [levels] before you can stop it.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo;
		global $l_hull, $l_engines, $l_power, $l_fighter, $l_sensors, $l_beams, $l_torp_launch, $l_shields, $l_armor, $l_cloak, $l_ecm;

		$amount = mt_rand(1, 2);
		$tech = mt_rand(1, 11);
		if($row['debris_data'] == 1)
		{
			if($tech == 1){
				$techname = $l_hull;
				$query = "hull_normal=hull_normal + $amount, hull=hull + $amount";
			}
			if($tech == 2){
				$techname = $l_engines;
				$query = "engines_normal=engines_normal + $amount, engines=engines + $amount";
			}
			if($tech == 3){
				$techname = $l_power;
				$query = "power_normal=power_normal + $amount, power=power + $amount";
			}
			if($tech == 4){
				$techname = $l_fighter;
				$query = "fighter_normal=fighter_normal + $amount, fighter=fighter + $amount";
			}
			if($tech == 5){
				$techname = $l_sensors;
				$query = "sensors_normal=sensors_normal + $amount, sensors=sensors + $amount";
			}
			if($tech == 6){
				$techname = $l_beams;
				$query = "beams_normal=beams_normal + $amount, beams=beams + $amount";
			}
			if($tech == 7){
				$techname = $l_torp_launch;
				$query = "torp_launchers_normal=torp_launchers_normal + $amount, torp_launchers=torp_launchers + $amount";
			}
			if($tech == 8){
				$techname = $l_shields;
				$query = "shields_normal=shields_normal + $amount, shields=shields + $amount";
			}
			if($tech == 9){
				$techname = $l_armor;
				$query = "armor_normal=armor_normal + $amount, armor=armor + $amount";
			}
			if($tech == 10){
				$techname = $l_cloak;
				$query = "cloak_normal=cloak_normal + $amount, cloak=cloak + $amount";
			}
			if($tech == 11){
				$techname = $l_ecm;
				$query = "ecm_normal=ecm_normal + $amount, ecm=ecm + $amount";
			}
			$debrismessage = str_replace("[tech]", $techname, $this->l_debris_upgradelevel);
			$debrismessage = str_replace("[levels]", NUMBER($amount), $debrismessage);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET $query WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			if($tech == 1){
				$techname = $l_hull;
				$query = "hull_normal=GREATEST(hull_normal - $amount, 0), hull=GREATEST(hull - $amount, 0)";
				$techdamage = ($shipinfo['hull'] - $amount) / $shipinfo['hull'];
				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=amount * $techdamage WHERE ship_id=$shipinfo[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			if($tech == 2){
				$techname = $l_engines;
				$query = "engines_normal=GREATEST(engines_normal - $amount, 0), engines=GREATEST(engines - $amount, 0)";
			}
			if($tech == 3){
				$techname = $l_power;
				$query = "power_normal=GREATEST(power_normal - $amount, 0), power=GREATEST(power - $amount, 0)";
			}
			if($tech == 4){
				$techname = $l_fighter;
				$query = "fighter_normal=GREATEST(fighter_normal - $amount, 0), fighter=GREATEST(fighter - $amount, 0)";
			}
			if($tech == 5){
				$techname = $l_sensors;
				$query = "sensors_normal=GREATEST(sensors_normal - $amount, 0), sensors=GREATEST(sensors - $amount, 0)";
			}
			if($tech == 6){
				$techname = $l_beams;
				$query = "beams_normal=GREATEST(beams_normal - $amount, 0), beams=GREATEST(beams - $amount, 0)";
			}
			if($tech == 7){
				$techname = $l_torp_launch;
				$query = "torp_launchers_normal=GREATEST(torp_launchers_normal - $amount, 0), torp_launchers=GREATEST(torp_launchers - $amount, 0)";
			}
			if($tech == 8){
				$techname = $l_shields;
				$query = "shields_normal=GREATEST(shields_normal - $amount, 0), shields=GREATEST(shields - $amount, 0)";
			}
			if($tech == 9){
				$techname = $l_armor;
				$query = "armor_normal=GREATEST(armor_normal - $amount, 0), armor=GREATEST(armor - $amount, 0)";
			}
			if($tech == 10){
				$techname = $l_cloak;
				$query = "cloak_normal=GREATEST(cloak_normal - $amount, 0), cloak=GREATEST(cloak - $amount, 0)";
			}
			if($tech == 11){
				$techname = $l_ecm;
				$query = "ecm_normal=GREATEST(ecm_normal - $amount, 0), ecm=GREATEST(ecm - $amount, 0)";
			}

			$debrismessage = str_replace("[tech]", $techname, $this->l_debris_degradelevel);
			$debrismessage = str_replace("[levels]", NUMBER($amount), $debrismessage);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET $query WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
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