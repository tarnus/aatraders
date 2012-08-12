<?php
class entertainmentsoftware {
	var $classname = "entertainment software";
	var $cargoclass = "commodity";	// the class of cargo (commodity, generic, shipweapon, planetweapon, sectordefense, ect)
	var $upgradeport = "0";	// is this a port item that can be bought and sold (yes or no)
	var $deviceport = "0";	// is this a port item that can be bought and sold (yes or no)
	var $cargoport = "1";	// is this a port item that can be bought and sold (yes or no)
	var $cargosellbuy = "0";	// 0 = sell and buy at ports, 1 = ports buy only, 2 = ports sell only
	var $cargoplanet = "1";	// is this an item that can be from a planet (yes or no)
	var $defaultcargoplanet = "0";	// is this a default item from a planet (yes or no)
	var $defaultcargoship = "0";	// is this a default item always carried by a ship (yes or no)
	var $shipdevice = "0";	// can this be used as a ship device (yes or no)
	var $planetdevice = "0";	// can this be used as a planet device (yes or no)
	var $shipdevicemax = "0";	// maximum number of this device a ship can carry
	var $planetdevicemax = "0";	// maximum number of this device a planet can hold
	var $researchonly = "0";	// this item can only be built at a research station if set to 1
	var $goodevil = "1"; // good or evil commodity
	var $price = 3500; // Default Price
	var $delta = 700; // Price modifier - reduce port sell price by this amount and increase port buy price by this amount
	var $rate = 21000; // How many items to add back to a port per tick
	var $reducerate = 0.000583; // Price reduces per item traded (calculated from (price * multiplier / itemlimit) multiplier between 1-25 lower value higher the price)
	var $increaserate = 0.6022749; // Percentage prices will increase per trade schedule tick
	var $limit = 30000000; // Maximum amount of commodity port can hold
	var $prate = 0.00045; // Planetary Production Rate
	var $default_prod = 1; // Planet production percentage
	var $default_indy_prod = 13; // Planet production percentage
	var $default_create_percent = 2; // Percentage of item to create during Create Game
	var $fixed_start_price = 5600; // this is the max fixed start price for this item 

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
	var $program = ""; // program to execute when player selects item
	var $hold_space = 19; // the amount of hold space each item requires for storage

	var $image_location = 0; // 0 = inside each template image file, 1 = inside /images/classes

	// return language
	function entertainmentsoftware()
	{
		global $langdir, $l_entertainmentsoftware;
		switch ($langdir)
		{
			case "estonian":
				$l_entertainmentsoftware = "Entertainment Software";
			break;

			case "french":
				$l_entertainmentsoftware = "Entertainment Software";
			break;

			case "german":
				$l_entertainmentsoftware = "Entertainment Software";
			break;

			case "italian":
				$l_entertainmentsoftware = "Entertainment Software";
			break;

			case "russian":
				$l_entertainmentsoftware = "Entertainment Software";
			break;

			case "spanish":
				$l_entertainmentsoftware = "Entertainment Software";
			break;

			default:
				$l_entertainmentsoftware = "Entertainment Software";
			break;
		}
	}
}
?>
