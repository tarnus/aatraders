<?php
class level_all {
	var $classname = "level_all";
	var $success = "450";	// Random value range
	var $trigger = "225";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_upgradeall;
	var $l_debris_degradeall;

	// fill language variables
	function level_all()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_upgradeall = "You have found a military grade upgrade package that upgrades all of your tech levels by [level].";
				$this->l_debris_degradeall = "A massive antimatter explosion occurs when you approach the debris and it damages all of your tech levels by [level].";
			break;

			case "french":
				$this->l_debris_upgradeall = "Vous trouvez un ensemble de mise à jour de qualité militaire. Il peut ajouter [level] niveaux à toutes vos technologies.";
				$this->l_debris_degradeall = "Une gigantesque explosion d'antimatière se produit lorsque vous approchez des débris. Toute votre technologie est endommagée et réduite de [level] niveaux.";
			break;

			case "german":
				$this->l_debris_upgradeall = "Sie haben ein militärisches Aufrüstpaket gefunden, dass alle Ihre Tech-Levels um [level] erhöht.";
				$this->l_debris_degradeall = "Eine massive Antimaterie-Explosion während Sie den Fund bergen. All Ihre Tech-Levels wurden um [level] verbraucht.";
			break;

			case "italian":
				$this->l_debris_upgradeall = "Hai trovato un set di potenziamento militare che potenzia tutti i tuoi sistemi di [level] livelli.";
				$this->l_debris_degradeall = "Una grande esplosione di antimateria mentre ti stai avvicinando ai rottami danneggia tutti i tuoi sistemi di [level] livelli.";
			break;

			case "russian":
				$this->l_debris_upgradeall = "You have found a military grade upgrade package that upgrades all of your tech levels by [level].";
				$this->l_debris_degradeall = "A massive antimatter explosion occurs when you approach the debris and it damages all of your tech levels by [level].";
			break;

			case "spanish":
				$this->l_debris_upgradeall = "You have found a military grade upgrade package that upgrades all of your tech levels by [level].";
				$this->l_debris_degradeall = "A massive antimatter explosion occurs when you approach the debris and it damages all of your tech levels by [level].";
			break;

			default:
				$this->l_debris_upgradeall = "You have found a military grade upgrade package that upgrades all of your tech levels by [level].";
				$this->l_debris_degradeall = "A massive antimatter explosion occurs when you approach the debris and it damages all of your tech levels by [level].";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo;

		$amount = 1;
		if($row['debris_data'] == 1)
		{
			$debrismessage = str_replace("[level]", NUMBER($amount), $this->l_debris_upgradeall);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET hull_normal=hull_normal+1, engines_normal=engines_normal+1, power_normal=power_normal+1, fighter_normal=fighter_normal+1, sensors_normal=sensors_normal+1, beams_normal=beams_normal+1, torp_launchers_normal=torp_launchers_normal+1, shields_normal=shields_normal+1, armor_normal=armor_normal+1, cloak_normal=cloak_normal+1, ecm_normal=ecm_normal+1, hull=hull+1, engines=engines+1, power=power+1, fighter=fighter+1, sensors=sensors+1, beams=beams+1, torp_launchers=torp_launchers+1, shields=shields+1, armor=armor+1, cloak=cloak+1, ecm=ecm+1 WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			$debrismessage = str_replace("[level]", NUMBER($amount), $this->l_debris_degradeall);
			$query = "hull_normal=GREATEST(hull_normal - $amount, 0), hull=GREATEST(hull - $amount, 0),";
			$query .= "engines_normal=GREATEST(engines_normal - $amount, 0), engines=GREATEST(engines - $amount, 0),";
			$query .= "power_normal=GREATEST(power_normal - $amount, 0), power=GREATEST(power - $amount, 0),";
			$query .= "fighter_normal=GREATEST(fighter_normal - $amount, 0), fighter=GREATEST(fighter - $amount, 0),";
			$query .= "sensors_normal=GREATEST(sensors_normal - $amount, 0), sensors=GREATEST(sensors - $amount, 0),";
			$query .= "beams_normal=GREATEST(beams_normal - $amount, 0), beams=GREATEST(beams - $amount, 0),";
			$query .= "torp_launchers_normal=GREATEST(torp_launchers_normal - $amount, 0), torp_launchers=GREATEST(torp_launchers - $amount, 0),";
			$query .= "shields_normal=GREATEST(shields_normal - $amount, 0), shields=GREATEST(shields - $amount, 0),";
			$query .= "armor_normal=GREATEST(armor_normal - $amount, 0), armor=GREATEST(armor - $amount, 0),";
			$query .= "cloak_normal=GREATEST(cloak_normal - $amount, 0), cloak=GREATEST(cloak - $amount, 0),";
			$query .= "ecm_normal=GREATEST(ecm_normal - $amount, 0), ecm=GREATEST(ecm - $amount, 0)";

			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET $query WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$techdamage = ($shipinfo['hull'] - $amount) / $shipinfo['hull'];
			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=amount * $techdamage WHERE ship_id=$shipinfo[ship_id]");
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