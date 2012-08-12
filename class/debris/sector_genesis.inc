<?php
class sector_genesis {
	var $classname = "sector_genesis";
	var $success = "500";	// Random value range
	var $trigger = "250";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addsg;
	var $l_debris_removesg;
	var $l_debris_nothing;

	// fill language variables
	function sector_genesis()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addsg = "Though slightly damaged you have found a usable Sector Genesis Device.";
				$this->l_debris_removesg = "An Electromagnetic Pulse suddenly erupts from the debris destroying one of your Sector Genesis Devices.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			case "french":
				$this->l_debris_addsg = "Vous avez trouvé une torpille genesis fonctionnelle, bien que légèrement endommagée.";
				$this->l_debris_removesg = "Des impulsions électromagnétiques sont soudainement émises par les débris. Une de vos torpilles genesis est détruite.";
				$this->l_debris_nothing = "Vos ingénieurs décident qu'il s'agit de simples détritus.";
			break;

			case "german":
				$this->l_debris_addsg = "Obwohl sichtbar beschädigt haben Sie ein brauchbares Sektor-Genesis-Gerät gefunden.";
				$this->l_debris_removesg = "Ein elektormagnetsicher Puls vom Fund hat plötzlich eine Ihrer Sektor-Genesis-Geräte vernichtet.";
				$this->l_debris_nothing = "Ihre Ingenieure haben herausgefunden, dass es nur nutzloser Weltraumschrott ist.";
			break;

			case "italian":
				$this->l_debris_addsg = "Anche se leggermente danneggiato, hai trovato un Dispositivo Genesis di Settori utilizzabile.";
				$this->l_debris_removesg = "Un Impulso elettromagnetico erutta improvvisamente dai rottami, distruggendo uno dei tuoi Dispositivi Genesis di Settori.";
				$this->l_debris_nothing = "I tuoi ingenieri hanno analizzato il rottame e non hanno trovato altro che inutilizzabili rifiuti spaziali.";
			break;

			case "russian":
				$this->l_debris_addsg = "Though slightly damaged you have found a usable Sector Genesis Device.";
				$this->l_debris_removesg = "An Electromagnetic Pulse suddenly erupts from the debris destroying one of your Sector Genesis Devices.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			case "spanish":
				$this->l_debris_addsg = "Though slightly damaged you have found a usable Sector Genesis Device.";
				$this->l_debris_removesg = "An Electromagnetic Pulse suddenly erupts from the debris destroying one of your Sector Genesis Devices.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			default:
				$this->l_debris_addsg = "Though slightly damaged you have found a usable Sector Genesis Device.";
				$this->l_debris_removesg = "An Electromagnetic Pulse suddenly erupts from the debris destroying one of your Sector Genesis Devices.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo, $shipdevice;

		if($row['debris_data'] == 1)
		{
			$debrismessage = $this->l_debris_addsg;
			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount+1 WHERE device_id=" . $shipdevice['dev_sectorgenesis']['device_id']);
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			if($shipdevice['dev_sectorgenesis']['amount'] == 0){
				if(($shipdevice['dev_sectorgenesis']['amount'] - 1) < 0){
					$amount = $shipdevice['dev_sectorgenesis']['amount'];
				}
				$debrismessage = $this->l_debris_removesg;
				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=GREATEST(amount-1, 0) WHERE device_id=" . $shipdevice['dev_sectorgenesis']['device_id']);
				db_op_result($debug_query,__LINE__,__FILE__);
			}else{
				$debrismessage = $this->l_debris_nothing;
			}
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