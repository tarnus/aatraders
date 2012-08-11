<?php
class energy_dump {
	var $classname = "energy_dump";
	var $success = "200";	// Random value range
	var $trigger = "100";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "1";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addenergy;
	var $l_debris_removeenergy;

	// fill language variables
	function energy_dump()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addenergy = "You have found portable energy contains that can give your ship a one time boost of [amount] units of energy.";
				$this->l_debris_removeenergy = "You have brought abord an energy sink that triggered as soon as the artificial gravity was enabled and it removed [amount] units of energy.";
			break;

			case "french":
				$this->l_debris_addenergy = "Vous avez trouvé des contenants d'énergie portatifs. Ils peuvent vous assurer une seule accélération temporaire de [amount] points d'énergie.";
				$this->l_debris_removeenergy = "Vous avez malencontreusement ramené un dissipateur d'énergie qui s'est activé dès qu'il a détecté la gravité artificielle. Vous avez perdu [amount] points d'énergie.";
			break;

			case "german":
				$this->l_debris_addenergy = "Sie haben tragbare Energie gefunden. Ihr Fund bringt Ihnen einen einmaligen Energieschub von [amount].";
				$this->l_debris_removeenergy = "Sie haben eine Energie-Quelle an Bord gebracht, die Ihnen, als Sie das künstliche Schwerkraftfeld aktivierten [amount] Einheiten Energie abgezogen hat.";
			break;

			case "italian":
				$this->l_debris_addenergy = "Hai scoperto un modulo portatile di immagazzinamento dell'energia, che ti fornisce una carica aggiuntiva di [amount] unità di energia, utilizzabile una volta sola.";
				$this->l_debris_removeenergy = "Hai portato a bordo un condotto d'energia che si è attivato appena subiti gli effetti della gravità artificiale, sottraendo [amount] unità di energia.";
			break;

			case "russian":
				$this->l_debris_addenergy = "You have found portable energy contains that can give your ship a one time boost of [amount] units of energy.";
				$this->l_debris_removeenergy = "You have brought abord an energy sink that triggered as soon as the artificial gravity was enabled and it removed [amount] units of energy.";
			break;

			case "spanish":
				$this->l_debris_addenergy = "You have found portable energy contains that can give your ship a one time boost of [amount] units of energy.";
				$this->l_debris_removeenergy = "You have brought abord an energy sink that triggered as soon as the artificial gravity was enabled and it removed [amount] units of energy.";
			break;

			default:
				$this->l_debris_addenergy = "You have found portable energy contains that can give your ship a one time boost of [amount] units of energy.";
				$this->l_debris_removeenergy = "You have brought abord an energy sink that triggered as soon as the artificial gravity was enabled and it removed [amount] units of energy.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo;

		if($row['debris_data'] > 1)
		{
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_addenergy);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET energy=energy+$row[debris_data] WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			if(($shipinfo['energy'] + $row['debris_data']) <= 0){
				$row['debris_data'] = 1 - $shipinfo['energy'];
			}
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_removeenergy);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET energy=GREATEST(energy+$row[debris_data], 0) WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$amount = mt_rand(50, 50 + $destroyed_ship_info['energy']);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$amount = mt_rand(50, 50 + NUM_ENERGY($max_list['power_max']));
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}
}

?>