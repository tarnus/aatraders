<?php
class armor {
	var $classname = "armor";
	var $success = "150";	// Random value range
	var $trigger = "75";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "1";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addarmor;
	var $l_debris_removearmor;

	// fill language variables
	function armor()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addarmor = "You have found a derelict ship with [amount] units of armor you can add to your ship.";
				$this->l_debris_removearmor = "As you approached the debris it exploded in a thermonuclear fireball that stripped off [amount] units of your ships armor.";
			break;

			case "french":
				$this->l_debris_addarmor = "Vous trouvez un vaisseau à la dérive, qui comporte encore [amount] unités pouvant être  ajoutées à l'armure de votre vaisseau.";
				$this->l_debris_removearmor = "L'approche des débris cause une explosion thermonucléaire qui effectue [amount] points de dommage à l'armure de votre vaisseau.";
			break;

			case "german":
				$this->l_debris_addarmor = "Sie haben ein verlassenes Schiff mit [amount] Einheiten Ausrüstung entdeckt, die Sie Ihrem Schiff hinzufügen können.";
				$this->l_debris_removearmor = "Als Sie sich dem Schutt näherten ist es in einem thermonuklearen Feuerball explodiert. Der Schiffausrüstung wurden [amount] Einheiten abgezogen.";
			break;

			case "italian":
				$this->l_debris_addarmor = "Hai trovato un relitto di nave, contenente [amount] unità di armatura che puoi aggiungere ala tua nave.";
				$this->l_debris_removearmor = "Come ti avvicini ai rottami questi esplodono a causa di una carica termonucleare, distruggendo [amount] dei tuoi punti armatura.";
			break;

			case "russian":
				$this->l_debris_addarmor = "You have found a derelict ship with [amount] units of armor you can add to your ship.";
				$this->l_debris_removearmor = "As you approached the debris it exploded in a thermonuclear fireball that stripped off [amount] units of your ships armor.";
			break;

			case "spanish":
				$this->l_debris_addarmor = "You have found a derelict ship with [amount] units of armor you can add to your ship.";
				$this->l_debris_removearmor = "As you approached the debris it exploded in a thermonuclear fireball that stripped off [amount] units of your ships armor.";
			break;

			default:
				$this->l_debris_addarmor = "You have found a derelict ship with [amount] units of armor you can add to your ship.";
				$this->l_debris_removearmor = "As you approached the debris it exploded in a thermonuclear fireball that stripped off [amount] units of your ships armor.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo;

		if($row['debris_data'] > 0)
		{
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_addarmor);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=armor_pts+$row[debris_data] WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			if(($shipinfo['armor_pts'] + $row['debris_data']) <= 0){
				$row['debris_data'] = 1 - $shipinfo['armor_pts'];
			}
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_removearmor);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=GREATEST(armor_pts+$row[debris_data], 1) WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$amount = mt_rand(50, 50 + $destroyed_ship_info['armor_pts']);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$amount = mt_rand(50, 50 + NUM_PER_LEVEL($max_list['armor_max']));
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}
}

?>