<?php
$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ship_holds WHERE cargo_name!='energy' and ship_id=$playerinfo[currentship]");
db_op_result($debug_query,__LINE__,__FILE__);

$ship_item_count = 0;
$ship_holds_used = 0;

while(!$debug_query->EOF){
	$ship_commodity_id[$ship_item_count] = $debug_query->fields['hold_id'];
	$ship_commodity_type[$ship_item_count] = $debug_query->fields['cargo_name'];
	$ship_commodity_class[$ship_item_count] = $debug_query->fields['cargo_class'];
	$ship_commodity_amount[$ship_item_count] = $debug_query->fields['amount'];
	$ship_commodity_holds[$ship_item_count] = $debug_query->fields['hold_space'];
	$ship_holds_used += ($debug_query->fields['hold_space'] * $debug_query->fields['amount']);
	$ship_commodity_ref[$ship_commodity_type[$ship_item_count]] = $ship_item_count;

	$ship_item_count++;
	$debug_query->MoveNext();
}
$debug_query->close();

$ship_commodity_id[$ship_item_count] = 0;
$ship_commodity_type[$ship_item_count] = "energy";
$ship_commodity_class[$ship_item_count] = "commodity";
$ship_commodity_amount[$ship_item_count] = $shipinfo['energy'];
$ship_commodity_holds[$ship_item_count] = 0;
$ship_commodity_ref[$ship_commodity_type[$ship_item_count]] = $ship_item_count;
$ship_item_count++;

$commodity_query = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities");
db_op_result($commodity_query,__LINE__,__FILE__);
while(!$commodity_query->EOF){
	$commodity = $commodity_query->fields['classname'];
	$commodity_hold_space[$commodity] = $commodity_query->fields['hold_space'];
	$commodity_total_sold[$commodity] = 0;
	$commodity_total_credits_made[$commodity] = 0;
	$commodity_total_bought[$commodity] = 0;
	$commodity_total_credits_lost[$commodity] = 0;
	$commodity_query->MoveNext();
}
$commodity_query->close();

$template_object->assign("l_energy", "Energy");

// ------------ Determine if Source is Planet or Port
$name_result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=" . $sourceport['sector_id'], 1);
//echo "$l_tdr_planet $source[name] in " . $name_result->fields['sector_name'] . "<br>";
$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$traderoute[source_planet_id]", 1);
if ($result2)
	$planet_source_info=$result2->fields;
$result2->close();

//echo nl2br(print_r($planet_source_info, true)) . "<hr>";

$template_object->assign("source_planet_name", $source['name']);
$template_object->assign("source_sector_name", $name_result->fields['sector_name']);
$name_result->close();

for ($item = 0; $item < $ship_item_count; $item++)
{
	if($ship_commodity_type[$item] != $planet_source_info['special_name'])
	{
		$planet_source_commodity_type[$item] = $ship_commodity_type[$item];
		$planet_source_commodity_amount[$item] = $planet_source_info[$ship_commodity_type[$item]];
	}
	else
	{
		$planet_source_commodity_type[$item] = $ship_commodity_type[$item];
		$planet_source_commodity_amount[$item] = $planet_source_info['special_amount'];
	}
}

$template_object->assign("planet_source_commodity_type", $planet_source_commodity_type);
$template_object->assign("planet_source_energy_start", $planet_source_info['energy']);
$template_object->assign("planet_source_start_amount", $planet_source_commodity_amount);

// ------------ Determine if Destination is Planet or Port
$name_result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=" . $destport['sector_id'], 1);
//echo "$l_tdr_planet $dest[name] in " . $name_result->fields['sector_name'] . "<br>";
$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$traderoute[destination_planet_id]", 1);
if ($result3)
	$planet_destination_info=$result3->fields;
$result3->close();

$template_object->assign("destination_planet_name", $dest['name']);
$template_object->assign("destination_sector_name", $name_result->fields['sector_name']);
$name_result->close();

for ($item = 0; $item < $ship_item_count; $item++)
{
	if($ship_commodity_type[$item] != $planet_destination_info['special_name'])
	{
		$planet_destination_commodity_type[$item] = $ship_commodity_type[$item];
		$planet_destination_commodity_amount[$item] = $planet_destination_info[$ship_commodity_type[$item]];
	}
	else
	{
		$planet_destination_commodity_type[$item] = $ship_commodity_type[$item];
		$planet_destination_commodity_amount[$item] = $planet_destination_info['special_amount'];
	}
}

$template_object->assign("planet_destination_commodity_type", $planet_destination_commodity_type);
$template_object->assign("planet_destination_energy_start", $planet_destination_info['energy']);
$template_object->assign("planet_destination_start_amount", $planet_destination_commodity_amount);

$template_object->assign("l_tdr_within", $l_tdr_within);
$template_object->assign("l_tdr_trade", $l_tdr_trade);
$template_object->assign("l_tdr_planet", $l_tdr_planet);
$template_object->assign("l_tdr_start", $l_tdr_start);
$template_object->assign("l_tdr_finish", $l_tdr_finish);
$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->assign("l_tdr_buying", $l_tdr_buying);
$template_object->assign("l_tdr_selling", $l_tdr_selling);
$template_object->assign("l_tdr_units", $l_tdr_units);
$template_object->assign("l_tdr_credits", $l_tdr_credits);
$template_object->assign("l_tdr_dumped", $l_tdr_dumped);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_torps", $l_torps);


$template_object->assign("source_start_fighters", NUMBER($planet_source_info['fighters']));
$template_object->assign("destination_start_fighters", NUMBER($planet_destination_info['fighters']));
$template_object->assign("source_start_torps", NUMBER($planet_source_info['torps']));
$template_object->assign("destination_start_torps", NUMBER($planet_destination_info['torps']));
$template_object->assign("source_commodity_start", NUMBER($planet_source_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("source_commodity2_start", NUMBER($planet_source_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));
$template_object->assign("destination_commodity_start", NUMBER($planet_destination_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("destination_commodity2_start", NUMBER($planet_destination_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));


$sourceplanet_buy_commodity_amount = array();
$sourceplanet_buy_item_type = array();
$total_energy_dumped = 0;
$total_fighters_dumped = 0;
$total_torps_dumped = 0;
$total_turns_used = 0;
$total_fighters_bought = 0;
$total_torps_bought = 0;
$total_energy_scooped = 0;
$trades_completed = $tr_repeat;
$source_commodity_loaded = 0;
$destination_commodity_loaded = 0;
$source_commodity_dumped = 0;
$destination_commodity_dumped = 0;

for ($i = 0; $i < $tr_repeat; $i++)
{
	$total_experience += $trading_exp;
	$fighters_buy = 0;
	$torps_buy = 0;

	// Source is a port
//	echo "Source $traderoute[source_commodity] Planet<br>";
	$ship_holds_used = 0;

	if ($traderoute['trade_fighters'] == 'Y')
	{
		$free_fighters = NUM_FIGHTERS($shipinfo['fighter']) - $shipinfo['fighters'];
		$fighters_buy = $free_fighters;
		if($planet_source_info['fighters'] < $fighters_buy)
			$fighters_buy = $planet_source_info['fighters'];

		if ($fighters_buy > 0)
		{
//			echo "$l_tdr_bought " . NUMBER($fighters_buy) . " $l_tdr_fighters<br>";
		}
		else $fighters_buy = 0;
		$total_fighters_dumped += ($fighters_buy + $shipinfo['fighters']);
		$shipinfo['fighters'] = 0;
	}
	else
	{
		$fighters_buy = 0;
	}
	$total_fighters_bought += $fighters_buy;

	if ($traderoute['trade_torps'] == 'Y')
	{
		$free_torps = NUM_TORPEDOES($shipinfo['torp_launchers']) - $shipinfo['torps'];
		$torps_buy = $free_torps;
		if($planet_source_info['torps'] < $torps_buy)
			$torps_buy = $planet_source_info['torps'];

		if ($torps_buy > 0){
//				echo "$l_tdr_bought " . NUMBER($torps_buy) . " $l_tdr_torps<br>";
		}
		else $torps_buy = 0;
		$total_torps_dumped += ($torps_buy + $shipinfo['torps']);
		$shipinfo['torps'] = 0;
	}
	else
	{
		$torps_buy = 0;
	}
	$total_torps_bought += $torps_buy;

	$planet_source_info['fighters'] -= $fighters_buy;
	$planet_source_info['torps'] -= $torps_buy;

	if ($traderoute['trade_energy'] == 'Y')
	{
		$energy_dump = $ship_commodity_amount[$ship_commodity_ref['energy']];
		$planet_source_commodity_amount[$ship_commodity_ref['energy']] += $energy_dump;
		$ship_commodity_amount[$ship_commodity_ref['energy']] = 0;
//		echo "$l_tdr_dumped " . NUMBER($energy_dump) . " Energy<br>";
	}
	else
	{
		$energy_dump = 0;
	}

	$total_energy_dumped += $energy_dump;

	for ($item = 0; $item < $ship_item_count; $item++)
	{
//		echo "$l_tdr_dumped " . NUMBER($ship_commodity_amount[$item]) . " " . $ship_commodity_type[$item] . "<br>";
		$planet_source_commodity_amount[$item] += $ship_commodity_amount[$item];
		if($ship_commodity_type[$item] == $traderoute['destination_commodity'])
		{
			$destination_commodity_dumped += $ship_commodity_amount[$item];
		}
		$ship_commodity_amount[$item] = 0;
	}

	if ($enable_spies && ($i % 5) == 0)
	{
//		echo "Finish : $traderoute[source_planet_id], $shipinfo[ship_id], $planet_detect_success1<BR>";
		spy_sneak_to_planet($traderoute['source_planet_id'], $shipinfo['ship_id']);
		spy_sneak_to_ship($traderoute['source_planet_id'], $shipinfo['ship_id']);
		spy_detect_planet($shipinfo['ship_id'], $traderoute['source_planet_id'], $planet_detect_success1);
	}

	$ship_holds_used = 0;
	for($itemcount = 0; $itemcount < $ship_item_count; $itemcount++)
	{
		$ship_holds_used += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
	}

	$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
	$free_energy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];

	foreach($planet_source_commodity_type as $key=>$value){ 
		if($value == $traderoute['source_commodity'])
		{
			if($value != "energy")
			{
				$free_holds = max(0, floor($free_holds / $ship_commodity_holds[$key]));
				$free_holds = min($free_holds, $planet_source_commodity_amount[$key]);
				$planet_source_commodity_amount[$key] -= $free_holds;
				$ship_commodity_amount[$key] += $free_holds;
				$source_commodity_loaded += $free_holds;
//				echo "Loading: $value - $free_holds - $ship_commodity_holds[$key]<br>";
			}
			else
			{
				$free_energy = ($planet_source_commodity_amount[$key] < $free_energy) ? $planet_source_commodity_amount[$key] : $free_energy;
				$planet_source_commodity_amount[$key] -= $free_energy;
				$ship_commodity_amount[$key] += $free_energy;
				$source_commodity_loaded += $free_energy;
//				echo "Loading: $value - $free_energy<br>";
			}
		}
//		echo "$value: " . number($planet_source_commodity_amount[$key]) . "<br>";
	}
//	echo"<br>";

	if ($shipdevice['dev_fuelscoop']['amount'] == 1){
		if(($dist['scooped1'] + $ship_commodity_amount[$ship_commodity_ref['energy']]) < NUM_ENERGY($shipinfo['power']))
		{
			$scoopedenergy = $dist['scooped1'];
		}
		else
		{
			$scoopedenergy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
		}
		$total_energy_scooped += $scoopedenergy;
		$ship_commodity_amount[$ship_commodity_ref['energy']] += $scoopedenergy;
//		echo"Energy Scooped: " . NUMBER($scoopedenergy) . "<br><br>";
//		echo"Energy Ship: " . NUMBER($ship_commodity_amount[$ship_commodity_ref['energy']]) . "<br><br>";
//		echo"Energy Max: " . NUMBER(NUM_ENERGY($shipinfo['power'])) . "<br><br>";
	}

//	foreach($ship_commodity_type as $key=>$value){ 
//			echo "$value $key: " . number($ship_commodity_amount[$key]) . "<br>";
//	}
//	echo"<br>";

	//Destination is a planet
//	echo "Destination $traderoute[destination_commodity] planet<br>";
	if ($traderoute['destination_type'] == 'planet'	|| $traderoute['destination_type'] == 'team_planet')
	{

		if ($traderoute['trade_energy'] == 'Y')
		{
			$energy_dump = $ship_commodity_amount[$ship_commodity_ref['energy']];
			$planet_destination_commodity_amount[$ship_commodity_ref['energy']] += $energy_dump;
			$total_energy_dumped += $energy_dump;
			$ship_commodity_amount[$ship_commodity_ref['energy']] = 0;
//			echo "$l_tdr_dumped " . NUMBER($energy_dump) . " Energy<br>";
		}
		else
		{
			$energy_dump = 0;
		}

		$total_energy_dumped += $energy_dump;

		for ($item = 0; $item < $ship_item_count; $item++)
		{
//			echo "$l_tdr_dumped " . NUMBER($ship_commodity_amount[$item]) . " " . $ship_commodity_type[$item] . "<br>";
			$planet_destination_commodity_amount[$item] += $ship_commodity_amount[$item];
			if($ship_commodity_type[$item] == $traderoute['source_commodity'])
			{
				$source_commodity_dumped += $ship_commodity_amount[$item];
			}
			$ship_commodity_amount[$item] = 0;
		}

		if ($enable_spies && ($i % 5) == 0)
		{
//			echo "Finish : $traderoute[destination_planet_id], $shipinfo[ship_id], $planet_detect_success1<BR>";
			spy_sneak_to_planet($traderoute['destination_planet_id'], $shipinfo['ship_id']);
			spy_sneak_to_ship($traderoute['destination_planet_id'], $shipinfo['ship_id']);
			spy_detect_planet($shipinfo['ship_id'], $traderoute['destination_planet_id'], $planet_detect_success1);
		}
	}

//	echo"<br>";
//	echo "Trade Route One-Way<br>";
//	foreach($ship_commodity_type as $key=>$value){ 
//			echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//	}
//	echo"<br>";

//	echo "Planet Energy = " . number($planet_destination_info['energy']) . "<br>";
//	foreach($planet_destination_commodity_type as $key=>$value){ 
//		echo "$value: " . number($planet_destination_commodity_amount[$key]) . "<br>";
//	}

//	echo "Turns Used = " . $dist['triptime'] . "<br>";
//	echo "Player Turns = " . $playerinfo['turns'] . "<br>";
//	echo "Player Turns Used = " . $playerinfo['turns_used'] . "<br>";
	$playerinfo['turns'] = max (0, $playerinfo['turns'] - $dist['triptime']);
	$playerinfo['turns_used'] = max (0, $playerinfo['turns_used'] + $dist['triptime']);
//	echo "Player Turns - Turns Used = " . $playerinfo['turns'] . "<br>";
//	echo "Player Turns Used + Turns Used = " . $playerinfo['turns_used'] . "<br>";
	$total_turns_used += $dist['triptime'];

	$shipinfo['sector_id'] = $dest['sector_id'];

	if($playerinfo['turns'] <= 0)
	{
		$trades_completed = $i;
		$i = $tr_repeat;
	}
//	echo"<hr>";

	if($traderoute['roundtrip'] == "Y" && $playerinfo['turns'] > 0)
	{
//		echo"<br>";
//		echo "Trade Route Return Trip<br>";

		if ($shipdevice['dev_fuelscoop']['amount'] == 1 && $sourceport['sector_id'] != $destport['sector_id']){
			if(($dist['scooped2'] + $ship_commodity_amount[$ship_commodity_ref['energy']]) < NUM_ENERGY($shipinfo['power']))
			{
				$scoopedenergy = $dist['scooped2'];
			}
			else
			{
				$scoopedenergy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
			}
//			echo"Energy Scooped: " . NUMBER($scoopedenergy) . "<br><br>";
			$total_energy_scooped += $scoopedenergy;
			$ship_commodity_amount[$ship_commodity_ref['energy']] += $scoopedenergy;
		}

//		echo "Planet Energy = " . number($planet_destination_info['energy']) . "<br>";

		$ship_holds_used_return = 0;
		$ship_energy_used_return = 0;
		for($itemcount = 0; $itemcount < $ship_item_count; $itemcount++)
		{
			$ship_holds_used_return += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
		}
		$free_holds_return = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used_return;
		$free_energy_return = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];

		foreach($planet_destination_commodity_type as $key=>$value)
		{ 
//echo $value . " - " . $traderoute['destination_commodity'] . "<br>";
			if($value == $traderoute['destination_commodity'])
			{
				if($value != "energy")
				{
					$return_amount = (($planet_destination_commodity_amount[$key] * $ship_commodity_holds[$key]) < $free_holds_return) ? $planet_destination_commodity_amount[$key] : floor($free_holds_return / $ship_commodity_holds[$key]);
					$planet_destination_commodity_amount[$key] -= $return_amount;
					$ship_commodity_amount[$key] += $return_amount;
					$destination_commodity_loaded += $return_amount;
//					echo "Loading: $value - $return_amount<br>";
				}
				else
				{
					$free_energy_return = ($planet_source_commodity_amount[$key] < $free_energy_return) ? $planet_source_commodity_amount[$key] : $free_energy_return;
					$planet_destination_commodity_amount[$key] -= $free_energy_return;
					$ship_commodity_amount[$key] += $free_energy_return;
					$destination_commodity_loaded += $free_energy_return;
					echo "Loading: $value - $free_energy_return<br>";
				}
//			echo "$value: " . number($planet_destination_commodity_amount[$key]) . "<br>";
			}
		}
//		echo"<br>";

//		foreach($ship_commodity_type as $key=>$value){ 
//				echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//		}

//		echo "Turns Used = " . $dist['triptime'] . "<br>";
//		echo "Player Turns = " . $playerinfo['turns'] . "<br>";
//		echo "Player Turns Used = " . $playerinfo['turns_used'] . "<br>";
		$playerinfo['turns'] = max (0, $playerinfo['turns'] - $dist['triptime']);
		$playerinfo['turns_used'] = max (0, $playerinfo['turns_used'] + $dist['triptime']);
//		echo "Player Turns - Turns Used = " . $playerinfo['turns'] . "<br>";
//		echo "Player Turns Used + Turns Used = " . $playerinfo['turns_used'] . "<br>";
		$total_turns_used += $dist['triptime'];
		$shipinfo['sector_id'] = $source['sector_id'];
	}
//	echo"<hr>";
	if($playerinfo['turns'] <= 0)
	{
		$trades_completed = $i;
		$i = $tr_repeat;
	}
}

//$ship_commodity_amount[$ship_commodity_ref['energy']] = min($ship_commodity_amount[$ship_commodity_ref['energy']], NUM_ENERGY($shipinfo['power']));
//echo "UPDATE {$db_prefix}planets SET fighters=$planet_source_info[fighters], torps=$planet_source_info[torps], energy=$planet_source_info[energy], organics=" . $planet_source_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_source_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_source_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_source_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[source_planet_id]<br><br>";
if(empty($planet_source_info['special_name']))
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=$planet_source_info[fighters], torps=$planet_source_info[torps], energy=" . $planet_source_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_source_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_source_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_source_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_source_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[source_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
else
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=$planet_source_info[fighters], torps=$planet_source_info[torps], special_amount=" . $planet_source_commodity_amount[$ship_commodity_ref[$planet_source_info['special_name']]] . ", energy=" . $planet_source_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_source_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_source_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_source_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_source_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[source_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}

//echo "UPDATE {$db_prefix}planets SET fighters=fighters+$total_fighters_dumped, torps=torps+$total_torps_dumped, energy=$planet_destination_info[energy], organics=" . $planet_destination_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_destination_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_destination_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_destination_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[destination_planet_id]<br><br>";
if(empty($planet_destination_info['special_name']))
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=fighters+$total_fighters_dumped, torps=torps+$total_torps_dumped, energy=" . $planet_destination_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_destination_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_destination_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_destination_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_destination_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[destination_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
else
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=fighters+$total_fighters_dumped, torps=torps+$total_torps_dumped, special_amount=" . $planet_destination_commodity_amount[$ship_commodity_ref[$planet_destination_info['special_name']]] . ", energy=" . $planet_destination_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_destination_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_destination_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_destination_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_destination_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[destination_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}

//echo "UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . ", fighters=$shipinfo[fighters], torps=$shipinfo[torps] WHERE ship_id=$shipinfo[ship_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . ", fighters=$shipinfo[fighters], torps=$shipinfo[torps] WHERE ship_id=$shipinfo[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);
//echo "UPDATE {$db_prefix}players SET turns=$playerinfo[turns], turns_used=$playerinfo[turns_used] WHERE player_id=$playerinfo[player_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=$playerinfo[turns], turns_used=$playerinfo[turns_used] WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

foreach($ship_commodity_type as $key=>$value){ 
	if($ship_commodity_id[$key] != 0)
	{
//		echo "UPDATE {$db_prefix}ship_holds SET amount=" . floor($ship_commodity_amount[$key]) . " WHERE hold_id=" . $ship_commodity_id[$key] . "<br><br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=" . floor($ship_commodity_amount[$key]) . " WHERE hold_id=" . $ship_commodity_id[$key]);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

//echo"<br>";

$template_object->assign("total_energy_dumped", NUMBER($total_energy_dumped));
$template_object->assign("total_energy_scooped", NUMBER($total_energy_scooped));

$template_object->assign("planet_energy_end", $planet_destination_info['energy']);
$template_object->assign("planet_end_amount", $planet_destination_commodity_amount);

$template_object->assign("l_tdr_start", $l_tdr_start);
$template_object->assign("l_tdr_finish", $l_tdr_finish);
$template_object->assign("l_tdr_total", $l_tdr_total);
$template_object->assign("l_tdr_loaded", $l_tdr_loaded);
$template_object->assign("l_tdr_dumped", $l_tdr_dumped);
$template_object->assign("l_tdr_bought", $l_tdr_bought);
$template_object->assign("l_tdr_sold", $l_tdr_sold);
$template_object->assign("total_turns_used", NUMBER($total_turns_used));
$template_object->assign("turns_left", NUMBER($playerinfo['turns']));
$template_object->assign("l_tdr_turnsleft", $l_tdr_turnsleft);
$template_object->assign("l_tdr_turnsused", $l_tdr_turnsused);
$template_object->assign("l_tdr_scooped", $l_tdr_scooped);
$template_object->assign("l_tdr_energy", $l_tdr_energy);
$template_object->assign("tr_repeat", $trades_completed);
$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->assign("l_tdr_runscompleted", $l_tdr_runscompleted);
$template_object->assign("l_global_mmenu", $l_global_mmenu);

$template_object->assign("total_fighters_bought", NUMBER($total_fighters_bought));
$template_object->assign("total_fighters_dumped", NUMBER($total_fighters_dumped));
$template_object->assign("total_torps_bought", NUMBER($total_torps_bought));
$template_object->assign("total_torps_dumped", NUMBER($total_torps_dumped));
$template_object->assign("source_commodity", ucfirst($traderoute['source_commodity']));
$template_object->assign("destination_commodity", ucfirst($traderoute['destination_commodity']));
$template_object->assign("source_commodity_loaded", NUMBER($source_commodity_loaded));
$template_object->assign("destination_commodity_loaded", NUMBER($destination_commodity_loaded));
$template_object->assign("source_commodity_dumped", NUMBER($source_commodity_dumped));
$template_object->assign("destination_commodity_dumped", NUMBER($destination_commodity_dumped));

$template_object->assign("source_total_fighters", NUMBER($planet_source_info['fighters']));
$template_object->assign("destination_total_fighters", NUMBER($planet_destination_info['fighters'] + $total_fighters_dumped));
$template_object->assign("source_total_torps", NUMBER($planet_source_info['torps']));
$template_object->assign("destination_total_torps", NUMBER($planet_destination_info['torps'] + $total_torps_dumped));
$template_object->assign("source_commodity_total", NUMBER($planet_source_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("source_commodity2_total", NUMBER($planet_source_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));
$template_object->assign("destination_commodity_total", NUMBER($planet_destination_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("destination_commodity2_total", NUMBER($planet_destination_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));

$l_tdr_engageagain = str_replace("[tdr_engage]", $engage, $l_tdr_engageagain);
$template_object->assign("l_tdr_engageagain", $l_tdr_engageagain);
$template_object->assign("engage", $engage);
$template_object->assign("l_tdr_timestorep", $l_tdr_timestorep);
$template_object->assign("l_submit", $l_submit);

$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->send_now = 0;
$template_object->display($templatename."traderoute_planet2planet.tpl");
?>
