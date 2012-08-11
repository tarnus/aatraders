<?php
class wormhole {
	var $classname = "wormhole";
	var $success = "350";	// Random value range
	var $trigger = "175";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "0";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_wormhole;

	// fill language variables
	function wormhole()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_wormhole = "You have found an artifact that triggered as you approached.  It created a worm hole in space and sent you to sector [sector].";
			break;

			case "french":
				$this->l_debris_wormhole = "Un objet a créé un trou de ver en réagissant à votre approche. Vous vous retrouvez au secteur [sector].";
			break;

			case "german":
				$this->l_debris_wormhole = "Sie haben ein Artifakt gefunden, welches aktiviert wurde, als Sie aufgetaucht sind. Es hat ein Wurmloch erstellt und Sie in den Sektor [sector] transportiert.";
			break;

			case "italian":
				$this->l_debris_wormhole = "Hai trovato un artefatto che si è attivato non appena ti sei avvicinato. Questo ha creato un wormhole che ti ha trasportato nel settore [sector].";
			break;

			case "russian":
				$this->l_debris_wormhole = "You have found an artifact that triggered as you approached.  It created a worm hole in space and sent you to sector [sector].";
			break;

			case "spanish":
				$this->l_debris_wormhole = "You have found an artifact that triggered as you approached.  It created a worm hole in space and sent you to sector [sector].";
			break;

			default:
				$this->l_debris_wormhole = "You have found an artifact that triggered as you approached.  It created a worm hole in space and sent you to sector [sector].";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $shipinfo;
		$findem = $db->SelectLimit("SELECT sector_name, sector_id FROM {$db_prefix}universe ORDER BY rand()", 1);
		$targetlink = $findem->fields['sector_id'];
		$targetname = $findem->fields['sector_name'];

		$debrismessage = str_replace("[sector]", $targetname, $this->l_debris_wormhole);

		$query = "UPDATE {$db_prefix}ships SET sector_id=$targetlink WHERE ship_id=$shipinfo[ship_id]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$debris_data = 1;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$debris_data = 1;
		return $debris_data;
	}
}

?>