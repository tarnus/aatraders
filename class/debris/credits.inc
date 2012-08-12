<?php
class credits {
	var $classname = "credits";
	var $success = "250";	// Random value range
	var $trigger = "125";	// Midpoint in random value range.  If random value from success range equals trigger then debris added
	var $destroyship_debris = "1";	// Set to 1 is this debris can be created when a ship is destroyed
	var $autoadd_debris = 1; // Set to 1 for the scheduler to auto add this debris,
	var $maximum_amount = "50000000";	// Set to maximum amount that can be stored in a debris item
	var $enable = "1";	// 1 = debris enabled in the game, 0 = debris disabled in the game

	// language variables
	var $l_debris_addcredits;
	var $l_debris_removecredits;

	// fill language variables
	function credits()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->l_debris_addcredits = "You have stumbled upon a hidden pirate credit bank and it contained [amount] credits.";
				$this->l_debris_removecredits = "The debris was actually a disguised pirate ship.  They boarded your ship and stole [amount] credits.";
			break;

			case "french":
				$this->l_debris_addcredits = "La chance vous dévoile une banque de pirates cachée! Elle contient [amount] crédits.";
				$this->l_debris_removecredits = "Les débris étaient réellement un vaisseau pirate caché... Ils vous ont volé [amount] crédits.";
			break;

			case "german":
				$this->l_debris_addcredits = "Sie sind zufällig auf ein Piraten-Konto auf der Bank gestossen, welches Ihnen [amount] Credits einbringt.";
				$this->l_debris_removecredits = "Der Schutt war in Wirklichkeit ein verstecktes Piratenschiff. Sie haben [amount] Credits gestohlen.";
			break;

			case "italian":
				$this->l_debris_addcredits = "Ti sei imbattuto in una banca pirata segreta contenente [amount] crediti.";
				$this->l_debris_removecredits = "I rottami non erano altro che una nave camuffata, dalla quale dei pirati hanno abbordato la tua nave, rubandoti [amount] crediti.";
			break;

			case "russian":
				$this->l_debris_addcredits = "You have stumbled upon a hidden pirate credit bank and it contained [amount] credits.";
				$this->l_debris_removecredits = "The debris was actually a disguised pirate ship.  They boarded your ship and stole [amount] credits.";
			break;

			case "spanish":
				$this->l_debris_addcredits = "You have stumbled upon a hidden pirate credit bank and it contained [amount] credits.";
				$this->l_debris_removecredits = "The debris was actually a disguised pirate ship.  They boarded your ship and stole [amount] credits.";
			break;

			default:
				$this->l_debris_addcredits = "You have stumbled upon a hidden pirate credit bank and it contained [amount] credits.";
				$this->l_debris_removecredits = "The debris was actually a disguised pirate ship.  They boarded your ship and stole [amount] credits.";
			break;
		}
	}

	// Code to execute when showdebris.php is executed.
	function show_debris_code()
	{
		global $db, $db_prefix, $row, $playerinfo, $piratestealpercent;

		if($row['debris_data'] > 0)
		{
			$debrismessage = str_replace("[amount]", NUMBER($row['debris_data']), $this->l_debris_addcredits);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits+$row[debris_data] WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			$amount = round($playerinfo['credits'] * ($piratestealpercent / 100));

			$debrismessage = str_replace("[amount]", NUMBER($amount), $this->l_debris_removecredits);
			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=GREATEST(credits-$amount, 0) WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe ORDER BY rand()", 1);
			$targetlink = $findem->fields['sector_id'];

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}debris (debris_type, debris_data, sector_id) values ('ship_credits','$amount', $targetlink)");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		return $debrismessage;
	}

	// Code to execute when a ship has been destroyed
	function destroyship_debris_code($max_list, $destroyed_ship_info)
	{
		$amount = mt_rand(50, 50 + $this->maximum_amount);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}

	// Code to execute when the scheduler adds this item to the universe
	function autoadd_debris_code($max_list)
	{
		$amount = mt_rand(50, 50 + $this->maximum_amount);
		$debris_data = (mt_rand(0, 1) == 1) ? -$amount : $amount;
		return $debris_data;
	}
}

?>