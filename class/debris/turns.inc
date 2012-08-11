<?php
class turns {
	var $classname = "turns";
	var $success = "80";	// Random value range
	var $trigger = "40";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $maximum_amount = "450";	// Set to maximum amount that can be stored in a debris item
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addturns;
	var $l_debris_removeturns;

	// fill language variables
	function turns()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addturns = "You have found extra booster modules that give you [amount] turns of movement.";
				$this->l_debris_removeturns = "The debris was boobytrapped and caused massive electrical damage that takes [amount] turns to repair.";
			break;

			case "french":
				$this->l_debris_addturns = "Vous trouvez des modules accélérateurs qui vous donnent [amount] tours de plus.";
				$this->l_debris_removeturns = "Les débris étaient piégés! Votre vaisseau subit d'importants dommages électriques qui prennent [amount] tours avant d'être réparés.";
			break;

			case "german":
				$this->l_debris_addturns = "Sie haben eine Extre-Boost-Modul gefunden, dass Ihnen [amount] Turns einbringt.";
				$this->l_debris_removeturns = "Der Schutt wurde anfängerhaft eingefangen und hat massiven Schaden in der Elektrik hervorgerufen, der Sie [amount] Turns für die Reparatur kostet.";
			break;

			case "italian":
				$this->l_debris_addturns = "Hai individuato un modulo extra di alimentazione che ti permette [amount] turni aggiuntivi.";
				$this->l_debris_removeturns = "I rottami erano in effetti una trappola che causa un guasto elettrico generale. PEr ripararlo impieghi [amount] turni.";
			break;

			case "russian":
				$this->l_debris_addturns = "You have found extra booster modules that give you [amount] turns of movement.";
				$this->l_debris_removeturns = "The debris was boobytrapped and caused massive electrical damage that takes [amount] turns to repair.";
			break;

			case "spanish":
				$this->l_debris_addturns = "You have found extra booster modules that give you [amount] turns of movement.";
				$this->l_debris_removeturns = "The debris was boobytrapped and caused massive electrical damage that takes [amount] turns to repair.";
			break;

			default:
				$this->l_debris_addturns = "You have found extra booster modules that give you [amount] turns of movement.";
				$this->l_debris_removeturns = "The debris was boobytrapped and caused massive electrical damage that takes [amount] turns to repair.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $playerinfo;

		if($row['debris_data'] > 1)
		{
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_addturns);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns+$row[debris_data] WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			if(($playerinfo['turns'] + $row['debris_data']) < 0){
				$row['debris_data'] = 1 - $playerinfo['turns'];
			}
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_removeturns);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns+$row[debris_data] WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$amount = mt_rand(1, $this->maximum_amount);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$amount = mt_rand(1, $this->maximum_amount);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}
}

?>