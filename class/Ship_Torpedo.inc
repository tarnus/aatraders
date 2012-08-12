<?php
class Ship_Torpedo {

	var $mine_damage_shields = 500; // amount of damage to enemy shield hit points per torp
	var $mine_damage_all = 1000; // amount of damage to all enemy items except shields per torp
	var $torp_damage_shields = 750; // amount of damage to enemy shield hit points per torp
	var $torp_damage_all = 2500; // amount of damage to all enemy items except shields per torp
	var $mine_deflector_damage = 50; // amound of damage to mines when each mine deflector hits

	var $mine_hit_pts = 300; // the amount of damage a mine take before it is destroyed
	var $torp_hit_pts = 200; // the amount of damage a torp can take before it is destroyed

	var $price_modifier = 1; // The cost of each torp is multiplied by this number
	var $torpedo_price = 25; // The cost of each torp is multiplied by this number
}

?>