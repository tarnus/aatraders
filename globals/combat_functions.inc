<?php
// Calculate the top and bottom percentage range used in calculating the damage percentage
// range each items damage amount.
if (!function_exists('ecmcheck')) {

	function ecmcheck($targetecm, $shipsensor, $modifier){
		global $ecm_modifier, $lowpercent_ecm_modifier;

		$lowpercent = (($lowpercent_ecm_modifier - $targetecm + $shipsensor) * $ecm_modifier);
		$lowpercent = max(min($lowpercent, 50), 1) + $modifier;
		$lowpercent = max(min($lowpercent, 75), 1);

		if($modifier < 0)
		{
			$highpercent = max(floor(100 + $modifier), 1);
		}
		else
		{
			$highpercent = 100;
		}

		$percent_calc[0] = $lowpercent;
		$percent_calc[1] = $highpercent;
//echo print_r($percent_calc, true) . "<br>";
		return $percent_calc;
	}

// Calculate the amount of damage caused by the number of units involved.

	function calc_damage($units, $damagemax, $percent_calc, $attacktech, $targettech){
		global $group_divider, $reliability_modifier, $failure_modifier, $tech_complete_failure, $confusion_modifier;
//echo "start: $units<br>";
		$damage[0] = 0; // total damage points
		$damage[1] = 0; // number of units that were not used
		$damage[2] = 0; // percentage of units not used

		// The higher the tech level the more likely part of it will fail lowering its effictiveness.  With a slim chance of 100% failure.
		$failure = floor($attacktech * $reliability_modifier);
		if(mt_rand(1, 100) < $failure){
			if(mt_rand(1, 100) <= $tech_complete_failure){
				$damage[0] = 0;
				$damage[1] = $units;
				$damage[2] = 100;
				return $damage;
			}
			else
			{
				$damage[2] = mt_rand(1, floor($attacktech * $failure_modifier));
				$damage[1] = floor($units * ($damage[2] * 0.01));
				$units = $units - $damage[1];
			}
		}
		$units = max(1, $units);
//echo "working: $units<br>";

		// If there is a really WIDE disparity between tech levels there can be confusion where the target tech misses
		// the enemy targets because there are too many friendlies in the way and a danger of hitting them.
		$confusion = max(floor(($attacktech - $targettech) * $confusion_modifier), 0);

//echo "confusion: $confusion<br>";
		$groups = min($group_divider, $units);

		$group = floor($units / $groups);
//echo "groups: $groups - group size: $group<br>";
//echo "low: $percent_calc[0] - high: $percent_calc[1]<br>";
		for($i = 0; $i < $groups; $i++){
			$groupdamage = $group * floor($damagemax * (mt_rand($percent_calc[0], $percent_calc[1]) * 0.01));
			if(mt_rand(1, 100) < $confusion)
				$groupdamage = 0;
			$damage[0] += $groupdamage;
		}
//echo "<br>";
		$last_group = $units - ($group * $groups);
		if($last_group)
			$damage[0] += $last_group * floor($damagemax * (mt_rand($percent_calc[0], $percent_calc[1]) * 0.01));
//echo "total damage points: $damage[0]<br>";
//echo "number of units that were not used: $damage[1]<br>";
//echo "percentage of units not used: $damage[2]<br>";
		return $damage;
	}

// Calculate the amount of damage caused by the number of units involved in an Sector Defense Attack.

	function calc_SD_damage($units, $damagemax, $percent_calc, $attacktech, $targettech){
		global $group_divider, $reliability_modifier, $failure_modifier, $tech_complete_failure, $confusion_modifier;
//echo "start: $units<br>";
		$damage[0] = 0; // total damage points
		$damage[1] = 0; // number of units that were not used
		$damage[2] = 0; // percentage of units not used

	// The higher the tech level the more likely part of it will fail lowering its effictiveness.  With a slim chance of 100% failure.
		$failure = floor($attacktech * $reliability_modifier);
		if(mt_rand(1, 100) < $failure){
			if(mt_rand(1, 100) <= $tech_complete_failure){
				$damage[0] = 0;
				$damage[1] = $units;
				$damage[2] = 100;
				return $damage;
			}
			else
			{
				$damage[2] = mt_rand(1, floor($attacktech * $failure_modifier));
				$damage[1] = floor($units * ($damage[2] * 0.01));
				$units = $units - $damage[1];
			}
		}
		$units = max(1, $units);
//echo "working: $units<br>";

		// If there is a really WIDE disparity between tech levels there can be confusion where the target tech misses
		// the enemy targets because there are too many friendlies in the way and a danger of hitting them.
		$confusion = max(floor(($attacktech - $targettech) * $confusion_modifier), 0);

//echo "confusion: $confusion<br>";
		$groups = min($group_divider, $units);

		$group = floor($units / $groups);
//echo "groups: $groups - group size: $group<br>";
//echo "low: $percent_calc[0] - high: $percent_calc[1]<br>";
		for($i = 0; $i < $groups; $i++){
			$groupdamage = $group * floor($damagemax * (mt_rand($percent_calc[0], $percent_calc[1]) * 0.01));
			if(mt_rand(1, 100) < $confusion)
				$groupdamage = 0;
			$damage[0] += $groupdamage;
		}
//echo "<br>";
		$last_group = $units - ($group * $groups);
		if($last_group)
			$damage[0] += $last_group * floor($damagemax * (mt_rand($percent_calc[0], $percent_calc[1]) * 0.01));
//echo "total damage points: $damage[0]<br>";
//echo "number of units that were not used: $damage[1]<br>";
//echo "percentage of units not used: $damage[2]<br>";
		return $damage;
	}

// This is the same as the calcdamage but without the damage being calculated.
// It returns the percentage failure and the amounts.

	function calc_failure($units, $attacktech, $targettech){
		global $reliability_modifier, $failure_modifier;

		$failed[0] = $units; // number of units that were used
		$failed[1] = 0; // number of units that were not used
		$failed[2] = 0; // percentage of units not used

		$failure = floor($attacktech * $reliability_modifier);
//echo "fail percentage: $failure<br>";
		if(mt_rand(1, 100) < $failure){
			$failed[2] = mt_rand(1, floor($attacktech * $failure_modifier));
			$failed[1] = floor($units * ($failed[2] * 0.01));
			$failed[0] = $units - $failed[1];
		}

//echo "fail used: $failed[0]<br>";
//echo "fail not used: $failed[1]<br>";
//echo "fail percent: $failed[2]<br>";
		return $failed;
	}

// Calculates the amount of damage done to individual tech levels based upon the percentage
// of armor lost in combat and updates either the planet or player ship table.
// $id = ship_id or planet_id
// $type = 0 - ship, 1 - planet
// $percentage = percentage of armor lost

	function calc_internal_damage($id, $type, $percentage, $test = false){
		global $db, $db_prefix;
		global $internal_damage_percent;

		$percentage = abs($percentage);

		if($test)
		{
			echo "id: $id - type: $type - percentage: $percentage<br>";
		}

		$techsdamaged = floor($percentage * 10);
		for($i = 0; $i < 11; $i++){
			if(mt_rand(1, 10000) < ($internal_damage_percent * 100)){
				if($techsdamaged != 0){
					$techsdamaged--;
					$techdamage[$i] = mt_rand(100 - floor($percentage * 100), 100) * 0.01;
				}
				else
				{
					$techdamage[$i] = 1;
				}
			}
			else
			{
				$techdamage[$i] = 1;
			}
		}

		if($type){
			if($test)
			{
				echo "UPDATE {$db_prefix}planets SET armor=armor * $techdamage[0], fighter=fighter * $techdamage[1], sensors=sensors * $techdamage[2], beams=beams * $techdamage[3], torp_launchers=torp_launchers * $techdamage[4], shields=shields * $techdamage[5], cloak=cloak * $techdamage[6], jammer=jammer * $techdamage[7], sector_defense_weapons=sector_defense_weapons * $techdamage[8], sector_defense_sensors=sector_defense_sensors * $techdamage[9], sector_defense_cloak=sector_defense_cloak * $techdamage[10] WHERE planet_id=$id<br>";
			}
			else
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET armor=armor * $techdamage[0], fighter=fighter * $techdamage[1], sensors=sensors * $techdamage[2], beams=beams * $techdamage[3], torp_launchers=torp_launchers * $techdamage[4], shields=shields * $techdamage[5], cloak=cloak * $techdamage[6], jammer=jammer * $techdamage[7], sector_defense_weapons=sector_defense_weapons * $techdamage[8], sector_defense_sensors=sector_defense_sensors * $techdamage[9], sector_defense_cloak=sector_defense_cloak * $techdamage[10] WHERE planet_id=$id");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}
		else
		{
			if($test)
			{
				echo "UPDATE {$db_prefix}ships SET engines=engines * $techdamage[0], power=power * $techdamage[1], armor=armor * $techdamage[2], hull=hull * $techdamage[3], fighter=fighter * $techdamage[4], sensors=sensors * $techdamage[5], beams=beams * $techdamage[6], torp_launchers=torp_launchers * $techdamage[7], shields=shields * $techdamage[8], cloak=cloak * $techdamage[9], ecm=ecm * $techdamage[10] WHERE ship_id=$id<br>";
			}
			else
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET engines=engines * $techdamage[0], power=power * $techdamage[1], armor=armor * $techdamage[2], hull=hull * $techdamage[3], fighter=fighter * $techdamage[4], sensors=sensors * $techdamage[5], beams=beams * $techdamage[6], torp_launchers=torp_launchers * $techdamage[7], shields=shields * $techdamage[8], cloak=cloak * $techdamage[9], ecm=ecm * $techdamage[10] WHERE ship_id=$id");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=amount * $techdamage[3] WHERE ship_id=" . $id);
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}
	}

// Calculate the amount of damage caused by the number of mines involved.

	function calc_damage_mines($units, $damagemax, $units_defender, $damagemax_defender, $percent_calc, $attacktech, $targettech){
		global $group_divider, $reliability_modifier, $failure_modifier, $tech_complete_failure, $confusion_modifier;
//echo "start: $units<br>";
		$damage[0] = 0; // total damage points
		$damage[1] = 0; // number of units that were not used
		$damage[2] = 0; // percentage of units not used

		$total_units = $units;
		$defender_hitpoints = $units_defender * $damagemax_defender;
//echo "defender_hitpoints: $defender_hitpoints<br>";
		// The higher the tech level the more likely part of it will fail lowering its effictiveness.  With a slim chance of 100% failure.
		$failure = floor($attacktech * $reliability_modifier);
		if(mt_rand(1, 100) < $failure){
			if(mt_rand(1, 100) <= $tech_complete_failure){
				$damage[0] = 0;
				$damage[1] = $units;
				$damage[2] = 100;
				return $damage;
			}
			else
			{
				$damage[2] = mt_rand(1, floor($attacktech * $failure_modifier));
				$damage[1] = floor($units * ($damage[2] * 0.01));
				$units = $units - $damage[1];
			}
		}
		$units = max(1, $units);
//echo "working: $units<br>";

		// If there is a really WIDE disparity between tech levels there can be confusion where the target tech misses
		// the enemy targets because there are too many friendlies in the way and a danger of hitting them.
		$confusion = max(floor(($attacktech - $targettech) * $confusion_modifier), 0);

//echo "confusion: $confusion<br>";
		$groups = min($group_divider, $units);

		$group = floor($units / $groups);

//echo "groups: $groups - group size: $group<br>";
//echo "low: $percent_calc[0] - high: $percent_calc[1]<br>";
		for($i = 0; $i < $groups; $i++){
			$groupdamage = $group * floor($damagemax * (mt_rand($percent_calc[0], $percent_calc[1]) * 0.01));
			if(mt_rand(1, 100) < $confusion)
				$groupdamage = 0;
			$damage[0] += $groupdamage;

			$defender_hitpoints -= $groupdamage;
//echo "groupdamage: $groupdamage<br>";
//echo "defender_hitpoints: $defender_hitpoints<br>";
//echo "damage[0]: $damage[0]<br>";
			if($defender_hitpoints <= 0)
			{
//echo "i = $i - " . (($groups - $i) * $group);
				$damage[0] += $defender_hitpoints;
				$damage[1] = $damage[1] + (($groups - ($i)) * $group) + (abs($defender_hitpoints) / $damagemax);
				$i = $groups;
			}
		}
//echo "<br>";
		$last_group = $units - ($group * $groups);
		if($last_group && $defender_hitpoints > 0)
		{
			$damage[0] += $last_group * floor($damagemax * (mt_rand($percent_calc[0], $percent_calc[1]) * 0.01));
		}
//echo "total damage points: $damage[0]<br>";
//echo "number of units that were not used: $damage[1]<br>";
//echo "percentage of units not used: $damage[2]<br>";
		return $damage;
	}
}
?>
