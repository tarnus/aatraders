<?php
include ("globals/good_neutral_evil.inc");
include ("globals/scanlevel.inc");

if (!function_exists('display_this_planet')) {
	function display_this_planet($this_planet) 
	{
		global $planettypes, $basefontsize, $l_unowned, $l_unnamed, $basefontsize, $db_prefix, $db, $colonist_limit, $max_tech_level, $colonist_tech_add;
		global $l_ranks_evil, $l_ranks_good, $l_ranks_neutral, $planetrating, $planetid, $planetimg, $planetname, $planetowner, $countplanet, $shipinfo, $playerinfo, $techowner, $techjammer;

		$totalcount = 0;
		$curcount = 0;
		$i = 0;
		$planetlevel = 0;
		if ($this_planet['owner'] != 0)
		{
			$result5 = $db->SelectLimit("SELECT character_name, rating FROM {$db_prefix}players WHERE player_id=". $this_planet['owner'] . "", 1);
			$planet_owner = $result5->fields;
			$result5->close();

			$techowner = $this_planet['owner'];
			$techjammer = $this_planet['jammer'];

			$planetavg = scanlevel($this_planet['fighter']) + scanlevel($this_planet['sensors']) + scanlevel($this_planet['beams']) + scanlevel($this_planet['torp_launchers']) + scanlevel($this_planet['shields']) + scanlevel($this_planet['cloak']);
			$maximum_colonists = $colonist_limit + floor($colonist_tech_add * floor($planetavg / 6));
			$planetavg += scanlevel(($this_planet['colonists'] / $maximum_colonists) * $max_tech_level);
			$planetavg =  floor((($planetavg / 7) / $max_tech_level) * 10 );

			$planetlevel = max(0, min(9, $planetavg));
			$rating = good_neutral_evil($planet_owner['rating']);
			$planetrating[$countplanet] = $rating[1];
			$planetratingnumber[$countplanet] = $rating[0];
		}
		else
		{
			$planetrating[$countplanet] = $l_ranks_neutral;
		}
		$planetid[$countplanet] = $this_planet['planet_id'];

		if($this_planet['ore_planet'] >= 1 && $this_planet['organics_planet'] >= 1)
		{
			$planettype = "oo";
		}

		if($this_planet['ore_planet'] >= 1 && $this_planet['organics_planet'] < 1)
		{
			$planettype = "oo-";
		}

		if($this_planet['ore_planet'] < 1 && $this_planet['organics_planet'] >= 1)
		{
			$planettype = "o-o";
		}

		if($this_planet['ore_planet'] < 1 && $this_planet['organics_planet'] < 1)
		{
			$planettype = "o-o-";
		}

		$planetimg[$countplanet] = $planettype . (string)($planetlevel + 1);
		if (empty($this_planet['name']))
		{
			$planetname[$countplanet] = $l_unnamed;
		}
		else
		{
			$planetname[$countplanet] = $this_planet['name'];
		}

		if ($this_planet['owner'] == 0)
		{
			$planetowner[$countplanet] = "$l_unowned";
		}
		else
		{
			$planetowner[$countplanet] = "$planet_owner[character_name]";
		}
		$countplanet++;
		return;
	}
}
?>
