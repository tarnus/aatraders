<?php
class torpedoes {
	var $classname = "torpedoes";
	var $success = "90";	// Random value range
	var $trigger = "45";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "1";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addtorps;
	var $l_debris_removetorps;

	// fill language variables
	function torpedoes()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addtorps = "You have found a crate containing [amount] torps.";
				$this->l_debris_removetorps = "As you approach the debris it stabs at your ship with a bomb pumped graser and destroys [amount] torps.";
			break;

			case "french":
				$this->l_debris_addtorps = "Vous trouvez une caisse contenant [amount] torpilles.";
				$this->l_debris_removetorps = "En vous approchant des débris, un graser à bombe attaque votre vaisseau et détruit [amount] torpilles.";
			break;

			case "german":
				$this->l_debris_addtorps = "Sie haben eine Kiste mit [amount] Torps gefunden.";
				$this->l_debris_removetorps = "Als Sie sich dem Schutt nähern ziel es auf Ihr Schiff und zündet eine Bombe, die [amount] Ihrer torps vernichtet.";
			break;

			case "italian":
				$this->l_debris_addtorps = "Tra i rottami hai indivuato uno stock di [amount] siluri.";
				$this->l_debris_removetorps = "Avvicinandoti ai rottami questi vengono attratti dalla massa metallica della tua nave e dopo aver intasato i tubi lanciasiluri esplodono distruggendo [amount] siluri.";
			break;

			case "russian":
				$this->l_debris_addtorps = "You have found a crate containing [amount] torps.";
				$this->l_debris_removetorps = "As you approach the debris it stabs at your ship with a bomb pumped graser and destroys [amount] torps.";
			break;

			case "spanish":
				$this->l_debris_addtorps = "You have found a crate containing [amount] torps.";
				$this->l_debris_removetorps = "As you approach the debris it stabs at your ship with a bomb pumped graser and destroys [amount] torps.";
			break;

			default:
				$this->l_debris_addtorps = "You have found a crate containing [amount] torps.";
				$this->l_debris_removetorps = "As you approach the debris it stabs at your ship with a bomb pumped graser and destroys [amount] torps.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo;

		if($row['debris_data'] > 1)
		{
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_addtorps);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET torps=torps+$row[debris_data] WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			if(($shipinfo['torps'] + $row['debris_data']) <= 0){
				$row['debris_data'] = 1 - $shipinfo['torps'];
			}
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_removetorps);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET torps=GREATEST(torps+$row[debris_data], 0) WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$amount = mt_rand(50, 50 + $destroyed_ship_info['torps']);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$amount = mt_rand(50, 50 + NUM_PER_LEVEL($max_list['torp_launchers_max']));
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}
}

?>