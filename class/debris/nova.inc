<?php
class nova {
	var $classname = "nova";
	var $success = "550";	// Random value range
	var $trigger = "275";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addnova;
	var $l_debris_nothing;
	var $l_debris_removenova;

	// fill language variables
	function nova()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addnova = "You have found the floating wreckage of a large starship and locate a usable Nova Bomb inside the hulk.";
				$this->l_debris_removenova = "As you approach the debris a message comes over the communications saying that planet killer weapons are not allowed in this area of space.  Your Nova Bomb immediately becomes unusable for no apparent reason.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			case "french":
				$this->l_debris_addnova = "Vous avez trouvé la carcasse d'un grand vaisseau à la dérive. Vous en ramenez une bombe Nova toujours utilisable.";
				$this->l_debris_removenova = "En approchant des débris, un message vous parvient indiquant que les armes antiplanètes sont illégales dans cette région de l'espace. Votre bombe Nova devient soudainement inutilisable!";
				$this->l_debris_nothing = "Vos ingénieurs décident qu'il s'agit de simples détritus.";
			break;

			case "german":
				$this->l_debris_addnova = "Sie haben ein schwebendes Wrack eines großen Raumschiffs mit einer eingebauten voll funktionsfähigen Nova-Bombe gefunden.";
				$this->l_debris_removenova = "Als Sie sich den Trümmern nähern empfängen Sie eine Nachricht, welche sagt, dass in dieser Gegend keine Planeten zerstörenden Waffen erlaubt sind. Ihre Nova-Bombe wurde sofort unbrauchbar gemacht.";
				$this->l_debris_nothing = "Ihre Ingenieure haben herausgefunden, dass es nur nutzloser Weltraumschrott ist.";
			break;

			case "italian":
				$this->l_debris_addnova = "Una Bomba Nova utilizzabile è stata individuata tra i rottami vaganti di una larga nave spaziale.";
				$this->l_debris_removenova = "Mentre ti avvicini ai rottami, ricevi un messaggio attraverso il sistema di comunicazione della nave che afferma che armi di distruzione planetaria non sono permesse in quest'area  di spazio. La tua Bomba Nova diviene inutilizzabile per nessuna ragione apparente..";
				$this->l_debris_nothing = "I tuoi ingenieri hanno analizzato il rottame e non hanno trovato altro che inutilizzabili rifiuti spaziali.";
			break;

			case "russian":
				$this->l_debris_addnova = "You have found the floating wreckage of a large starship and locate a usable Nova Bomb inside the hulk.";
				$this->l_debris_removenova = "As you approach the debris a message comes over the communications saying that planet killer weapons are not allowed in this area of space.  Your Nova Bomb immediately becomes unusable for no apparent reason.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			case "spanish":
				$this->l_debris_addnova = "You have found the floating wreckage of a large starship and locate a usable Nova Bomb inside the hulk.";
				$this->l_debris_removenova = "As you approach the debris a message comes over the communications saying that planet killer weapons are not allowed in this area of space.  Your Nova Bomb immediately becomes unusable for no apparent reason.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			default:
				$this->l_debris_addnova = "You have found the floating wreckage of a large starship and locate a usable Nova Bomb inside the hulk.";
				$this->l_debris_removenova = "As you approach the debris a message comes over the communications saying that planet killer weapons are not allowed in this area of space.  Your Nova Bomb immediately becomes unusable for no apparent reason.";
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo, $shipdevice, $dev_nova_shiplimit;

		if($row['debris_data'] == 1)
		{
			if($shipdevice['dev_nova']['amount'] == "0" && $dev_nova_shiplimit <= $shipinfo['class']){
				$debrismessage = $this->l_debris_addnova;
				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=10 WHERE device_id=" . $shipdevice['dev_nova']['device_id']);
				db_op_result($debug_query,__LINE__,__FILE__);
			}else{
				$debrismessage = $this->l_debris_nothing;
			}
		}else{
			if($shipdevice['dev_nova']['amount'] != "0"){
				$debrismessage = $this->l_debris_removenova;
				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=0 WHERE device_id=" . $shipdevice['dev_nova']['device_id']);
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