<?php
class dev_dignitaries {

	function dev_dignitaries()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Dignitary";
			break;

			case "french":
				$this->classname = "Dignitary";
			break;

			case "german":
				$this->classname = "Dignitary";
			break;

			case "italian":
				$this->classname = "Dignitary";
			break;

			case "russian":
				$this->classname = "Dignitary";
			break;

			case "spanish":
				$this->classname = "Dignitary";
			break;

			default:
				$this->classname = "Dignitary";
			break;
		}
	}

	var $techmodify = ""; // If not empty then this tech will be modified by the device prefix ship_ for ship tech and prefix planet_ for planet tech
	var $cargoclass = "shipdevice";	// the class of cargo (commodity, generic, shipweapon, planetweapon, sectordefense, ect)
	var $deviceport = "1";	// is this a port item that can be bought and sold (yes or no)
	var $upgradeport = "0";	// is this a port item that can be bought and sold (yes or no)
	var $cargoport = "0";	// is this a port item that can be bought and sold (yes or no)
	var $cargoplanet = "0";	// is this an item that can be from a planet (yes or no)
	var $defaultcargoplanet = "0";	// is this a default item from a planet (yes or no)
	var $defaultcargoship = "0";	// is this a default item always carried by a ship (yes or no)
	var $shipdevice = "1";	// can this be used as a ship device (yes or no)
	var $planetdevice = "0";	// can this be used as a planet device (yes or no)
	var $shipdevicemax = "200";	// maximum number of this device a ship can carry
	var $planetdevicemax = "0";	// maximum number of this device a planet can hold
	var $researchonly = "0";	// this item can only be built at a research station if set to 1
	var $goodevil = "1"; // good or evil commodity
	var $price = 1000000; // Default Price
	var $delta = 0; // Price modifier
	var $rate = 0; // Replenishment rate
	var $reducerate = 0.00; // Percentage prices will reduce per unit purchaced by port
	var $increaserate = 0.00; // Percentage prices will increase per trade schedule tick
	var $limit = 0; // Maximum amount of commodity port can hold
	var $prate = 0.0; // Production Rate
	var $default_prod = 0; // Planet production percentage
	var $default_indy_prod = 0; // Planet production percentage
	var $default_create_percent = 0; // Percentage of item to create during Create Game
	var $fixed_start_price = 0; // this is the max fixed start price for this item 

	var $damage_shields = 0; // amount of damage to enemy shield hit points per torp
	var $damage_all = 0; // amount of damage to all enemy items except shields per torp
	var $deflector_damage = 0; // amound of damage to mines when each mine deflector hits
	var $hit_pts = 0; // the amount of damage a mine take before it is destroyed
	var $price_modifier = 0; // The cost of each torp is multiplied by this number
	var $energy_usage = 0; // How many units of energy is used

	var $researchcredits = 0; // How many credits to use per tick to research an item
	var $researchore = 0; // How much ore to use per tick to research an item
	var $researchorganics = 0; // How much organics to use per tick to research an item
	var $researchgoods = 0; // How many goods to use per tick to research an item
	var $researchenergy = 0; // How much energy to use per tick to research an item
	var $researchticks = 0; // How many ticks it takes to complete the researching of an item
	var $buildcredits = 0; // How many credits to use per tick to research an item
	var $buildore = 0; // How much ore to use per tick to research an item
	var $buildorganics = 0; // How much organics to use per tick to research an item
	var $buildgoods = 0; // How many goods to use per tick to research an item
	var $buildenergy = 0; // How much energy to use per tick to research an item
	var $buildticks = 0; // How many ticks it takes to complete building an item
	var $program = "dig.php"; // program to execute when player selects item
	var $hold_space = 1; // the amount of hold space each item requires for storage

	// Port Device View Functions
	var $device_free = 0;
	var $ship_amount = 0;
	function get_device_java_countTotal($alliancefactor)
	{
		$device_java = "(form.elements['dig_number'].value * " . $this->price . " * $alliancefactor)";
		return $device_java;
	}

	function get_device_java2_countTotal()
	{
		global $shipdevice, $db, $db_prefix, $playerinfo, $shipinfo;

		$res=$db->Execute("SELECT count(dig_id) as dig_num from {$db_prefix}dignitary where owner_id=$playerinfo[player_id] AND ship_id=$shipinfo[ship_id] and active='N'");
		$dig_num = $res->fields['dig_num'];
		$res->close();

		$this->ship_amount = $dig_num;
		$this->device_free = $this->shipdevicemax - $dig_num;

		$device_java = "if ((" . $this->device_free . " < form.dig_number.value) && (form.dig_number.value != 'Full'))\n";
		$device_java .= "{\n";
		$device_java .= "	form.dig_number.value=0;\n";
		$device_java .= "}\n";
		return $device_java;
	}

	function get_device_java_function($alliancefactor)
	{
		$device_java = "";
		return $device_java;
	}

	function get_device_input()
	{
		$device_input = "<input class=\"inputcss\" style=\"text-align:right\" size=\"4\" type=\"text\" name=\"" . $this->form_name . "\" value=\"0\" ONBLUR=\"countTotal()\">";
		return $device_input;
	}

	var $form_name = "dig_number";

	// Port Device Purchase Functions
	var $device_amount = 0;
	function get_device_totalcost()
	{
		global $db, $db_prefix, $playerinfo, $shipinfo, $enable_dignitaries;

		$formname = $this->form_name;

		if($enable_dignitaries)
		{
			$this->device_amount = $_POST[$formname];
			$res=$db->Execute("SELECT count(dig_id) as dig_num from {$db_prefix}dignitary where owner_id=$playerinfo[player_id] AND ship_id=$shipinfo[ship_id] and active='N'");
			$dig_num = $res->fields['dig_num'];
			$res->close();
			if($spy_num <= $this->shipdevicemax)
			{
				$this->device_amount = max(0, min(round(abs($this->device_amount)), $this->shipdevicemax - $dig_num));
			}
			else
			{
				$this->device_amount = 0;
			}
		}
		else
		{
			$this->device_amount = 0;
		}
		return $this->device_amount * $this->price;
	}

	function complete_purchase()
	{
		global $db, $db_prefix, $playerinfo, $shipinfo;

		for($i = 1; $i <= $this->device_amount; $i++)
		{
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}dignitary (dig_id, active, owner_id, planet_id, ship_id, job_id, percent) values ('','N',$playerinfo[player_id],'0','$shipinfo[ship_id]','0','0.0')");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}

	// General Device Functions
	function device_code()
	{
		global $db, $db_prefix, $enable_dignitaries, $playerinfo, $shipinfo;

		$amount = 0;
		if ($enable_dignitaries)
		{
			$debug_query = $db->Execute("SELECT * from {$db_prefix}dignitary WHERE owner_id = $playerinfo[player_id] AND ship_id = $shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$deviceamount[$count] = $debug_query->RecordCount();
			$amount = $debug_query->RecordCount();
		}
		return $amount;
	}

	function report_code()
	{
	}

	function scan_code()
	{
	}

	function port_devices_code()
	{
	}

	function port_devices_buy_code()
	{
	}

	function devices_score_code($player_id)
	{
		global $db, $db_prefix, $enable_dignitaries;

		$amount = 0;
		if ($enable_dignitaries)
		{
			$debug_query = $db->Execute("SELECT * from {$db_prefix}dignitary WHERE owner_id = $player_id");
			db_op_result($debug_query,__LINE__,__FILE__);

			$amount = $debug_query->RecordCount();
		}
		return $amount;
	}

	function modify_tech_code($shipinfo)
	{
		global $shiptypes;
	}
}

?>