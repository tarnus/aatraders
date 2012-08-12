<?php
class spy {
	var $classname = "spy";
	var $success = "300";	// Random value range
	var $trigger = "150";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_nothing;

	// fill language variables
	function spy()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			case "french":
				$this->l_debris_nothing = "Vos ingénieurs décident qu'il s'agit de simples détritus.";
			break;

			case "german":
				$this->l_debris_nothing = "Ihre Ingenieure haben herausgefunden, dass es nur nutzloser Weltraumschrott ist.";
			break;

			case "italian":
				$this->l_debris_nothing = "I tuoi ingenieri hanno analizzato il rottame e non hanno trovato altro che inutilizzabili rifiuti spaziali.";
			break;

			case "russian":
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			case "spanish":
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;

			default:
				$this->l_debris_nothing = "Your engineers have determined it is useless space junk.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $playerinfo, $shipinfo;

		$debrismessage = $this->l_debris_nothing;

		$findem = $db->SelectLimit("SELECT player_id FROM {$db_prefix}players where player_id != $playerinfo[player_id] and npc=0 ORDER BY rand()", 1);
		$fromplayer = $findem->fields['player_id'];

		$debug_query = $db->Execute("INSERT INTO {$db_prefix}spies (active, owner_id, planet_id, ship_id, job_id, spy_percent, move_type) values ('Y',$fromplayer,'0','$shipinfo[ship_id]','0','0.0','toship')");
		db_op_result($debug_query,__LINE__,__FILE__);
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