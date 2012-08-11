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
	$commodity_price[$commodity] = $commodity_query->fields['price'];
	$commodity_delta[$commodity] = $commodity_query->fields['delta'];
	$commodity_itemlimit[$commodity] = $commodity_query->fields['itemlimit'];
	$commodity_reducerate[$commodity] = $commodity_query->fields['reducerate'];
	$commodity_hold_space[$commodity] = $commodity_query->fields['hold_space'];
	$commodity_total_sold[$commodity] = 0;
	$commodity_total_credits_made[$commodity] = 0;
	$commodity_total_bought[$commodity] = 0;
	$commodity_total_credits_lost[$commodity] = 0;
	$commodity_query->MoveNext();
}
$commodity_query->close();

// ------------ Determine if Source is Planet or Port
$name_result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=" . $source['sector_id'], 1);
//echo ucfirst($source['port_type']) . " $l_tdr_portin " . $name_result->fields['sector_name'];
$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$source[sector_id] ORDER BY data_id DESC");
db_op_result($debug_query,__LINE__,__FILE__);
$sourceport_commodity_count = 0;
while(!$debug_query->EOF){
	$sourceport_data_id[$sourceport_commodity_count] = $debug_query->fields['data_id'];
	$sourceport_commodity_type[$sourceport_commodity_count] = $debug_query->fields['commodity_type'];
	$sourceport_commodity_amount[$sourceport_commodity_count] = $debug_query->fields['commodity_amount'];
	$sourceport_commodity_price[$sourceport_commodity_count] = $debug_query->fields['commodity_price'];
	$sourceport_goodevil[$sourceport_commodity_count] = $debug_query->fields['goodevil'];
	$sourceport_commodity_count++;
	$debug_query->MoveNext();
}
$debug_query->close();

$template_object->assign("source_port_type", ucfirst($source['port_type']));
$template_object->assign("l_tdr_portin", $l_tdr_portin);
$template_object->assign("source_sector_name", $name_result->fields['sector_name']);
$name_result->close();

// ------------ Determine if Destination is Planet or Port
$name_result = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id=" . $destport['sector_id'], 1);
//echo "$l_tdr_planet $dest[name] in " . $name_result->fields['sector_name'];
$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$traderoute[destination_planet_id]", 1);
if ($result3)
	$planetinfo=$result3->fields;
$result3->close();

for ($item = 0; $item < $ship_item_count; $item++)
{
	if($ship_commodity_type[$item] != $planetinfo['special_name'])
	{
		$planet_commodity_type[$item] = $ship_commodity_type[$item];
		$planet_commodity_amount[$item] = $planetinfo[$ship_commodity_type[$item]];
	}
	else
	{
		$planet_commodity_type[$item] = $ship_commodity_type[$item];
		$planet_commodity_amount[$item] = $planetinfo['special_amount'];
	}
}

$template_object->assign("planet_commodity_type", $planet_commodity_type);
$template_object->assign("l_energy", "Energy");
$template_object->assign("planet_energy_start", $planetinfo['energy']);
$template_object->assign("planet_start_amount", $planet_commodity_amount);

$template_object->assign("destination_planet_name", $dest['name']);
$template_object->assign("destination_sector_name", $name_result->fields['sector_name']);
$name_result->close();
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

$template_object->assign("destination_commodity_start", NUMBER($planet_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("destination_commodity2_start", NUMBER($planet_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));
$template_object->assign("source_commodity", ucwords($traderoute['source_commodity']));
$template_object->assign("destination_commodity", ucwords($traderoute['destination_commodity']));

$sourceport_buy_commodity_amount = array();
$sourceport_buy_item_price = array();
$sourceport_buy_item_type = array();
$total_energy_dumped = 0;
$starting_player_credits = $playerinfo['credits'];
$total_turns_used = 0;
$total_energy_scooped = 0;
$trades_completed = $tr_repeat;

for ($i = 0; $i < $tr_repeat; $i++)
{
	$total_experience += $trading_exp;

	$final_source_buy_price = array();
	$final_source_buy_amount = array();
	$final_source_buy_type = array();

	$total_sale=0;
	$total_cost=0;
	$sourcecost=0;
	// Source is a port
//	echo "Source $traderoute[source_commodity] Port<br>";
	$ship_holds_used = 0;
	$amount_buy_tot = 0;
	$amount_port_buy = 0;
	$amount_port_sell = 0;
	$amount_player_buy = 0;
	$credits_made = 0;
	for($itemcount = 0; $itemcount < $ship_item_count - 1; $itemcount++)
	{
		$ship_holds_used += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
	}
	$ship_holds_used_test = $ship_holds_used;
	for($itemcount = 0; $itemcount < $sourceport_commodity_count; $itemcount++)
	{
		if($source['port_type'] == $sourceport_commodity_type[$itemcount])
		{
			if($sourceport_commodity_type[$itemcount] != "energy")
			{
				$amount_player_buy = max(0, floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used) / $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]));
			}
			else
			{
				$ship_commodity_number = $ship_commodity_ref[$sourceport_commodity_type[$itemcount]];
				if($traderoute['trade_energy'] == 'Y')
					$amount_player_buy = NUM_ENERGY($shipinfo['power']) - $cargo_amount[$ship_commodity_number];
				else
					$amount_player_buy = 0;
			}
			$offered_sell_price = max($sourceport_commodity_price[$itemcount] - $commodity_delta[$sourceport_commodity_type[$itemcount]] * $amount_player_buy / $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
			$amount_player_buy = min($amount_player_buy, floor(($playerinfo['credits'] + $credits_made) / $offered_sell_price));
			$amount_player_buy = min($amount_player_buy, $sourceport_commodity_amount[$itemcount]);
			if($sourceport_commodity_type[$itemcount] != "energy")
			{
				$ship_holds_used_test += ($ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] * $amount_player_buy);
			}
			$amount_port_sell = $sourceport_commodity_amount[$itemcount];
//			echo ucfirst($traderoute['source_commodity']) . " $l_selling " . NUMBER($amount_port_sell) . " $amount_player_buy " . NUMBER($ship_commodity_amount[$itemcount]) . " : " . $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] . "</br><br>";
		}
		else
		{
			$offered_buy_price = max($sourceport_commodity_price[$itemcount] + $commodity_price[$sourceport_commodity_type[$itemcount]] + $commodity_delta[$sourceport_commodity_type[$itemcount]] * $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] / $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
			$ship_commodity_number = $ship_commodity_ref[$sourceport_commodity_type[$itemcount]];
			$cargo_amount[$ship_commodity_number] = (isset($ship_commodity_amount[$ship_commodity_number])) ? $ship_commodity_amount[$ship_commodity_number] : 0;
			$cargo_amount[$ship_commodity_number] = min($cargo_amount[$ship_commodity_number], $sourceport_commodity_amount[$itemcount]);
			if($traderoute['trade_energy'] == 'N' && $sourceport_commodity_type[$itemcount] == "energy")
			{
				$cargo_amount[$ship_commodity_number] = 0;
			}
			if($sourceport_commodity_type[$itemcount] != "energy")
			{
				$ship_holds_used_test -= ($ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] * $cargo_amount[$ship_commodity_number]);
			}
			$credits_made += floor(($cargo_amount[$ship_commodity_number] * $offered_buy_price));
//			echo ucfirst($sourceport_commodity_type[$itemcount]) . " $l_buying " . NUMBER($sourceport_commodity_amount[$itemcount]) . " ".($offered_buy_price)." =$cargo_amount[$ship_commodity_number]= " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . "<br>";
			$amount_port_buy = $cargo_amount[$ship_commodity_number];
		}

		if($sourceport_commodity_type[$itemcount] != "energy")
		{
			$amount_buy_tot+=$amount_port_buy;
		}
	}

	$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;

	$ship_commodity_number = $ship_commodity_ref[AAT_strtolower($traderoute['source_commodity'])];
	$credits_made -= floor(($amount_player_buy * $offered_sell_price));

//	echo ucfirst($traderoute['source_commodity']) . " $l_selling " . NUMBER($amount_port_sell) . " $amount_player_buy " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . "</br><br>";
	$ship_commodity_amount[$ship_commodity_number] += $amount_player_buy;

	for($itemcount = 0; $itemcount < $sourceport_commodity_count; $itemcount++)
	{
		if($sourceport_commodity_type[$itemcount] != AAT_strtolower($traderoute['source_commodity'])){
			$item_price = max($sourceport_commodity_price[$itemcount] + $commodity_price[$sourceport_commodity_type[$itemcount]] + $commodity_delta[$sourceport_commodity_type[$itemcount]] * $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] / $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
			if($sourceport_commodity_amount[$itemcount] < $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]])
				$cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] = $sourceport_commodity_amount[$itemcount];

			if($sourceport_commodity_type[$itemcount] != "energy")
				$free_holds += ($cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] * $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]);

			$sale_price = $item_price * abs($cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]);
			$total_sale += $sale_price;
			$reduce_rate = ($sourceport_commodity_price[$itemcount] > $commodity_price[$sourceport_commodity_type[$itemcount]]) ? ($commodity_reducerate[$sourceport_commodity_type[$itemcount]] * ($sourceport_commodity_price[$itemcount] / $commodity_price[$sourceport_commodity_type[$itemcount]])) : $commodity_reducerate[$sourceport_commodity_type[$itemcount]];
			$reduce_rate = $commodity_reducerate[$sourceport_commodity_type[$itemcount]];
			$sourceport_commodity_price[$itemcount] = $sourceport_commodity_price[$itemcount] - ($reduce_rate * $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]);

			if($i == 0)
			{
				$sourceport_buy_commodity_amount[] = NUMBER($sourceport_commodity_amount[$itemcount]);
				$sourceport_buy_item_price[] = NUMBER($item_price);
				$sourceport_buy_item_type[] = ucfirst($sourceport_commodity_type[$itemcount]);
			}

			$sourceport_commodity_amount[$itemcount] = max(0, $sourceport_commodity_amount[$itemcount] - $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]);
			if($i == ($tr_repeat - 1))
			{
				$new_price = max($sourceport_commodity_price[$itemcount] + $commodity_price[$sourceport_commodity_type[$itemcount]] + $commodity_delta[$sourceport_commodity_type[$itemcount]] * $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] / $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
				$final_source_buy_price[] = NUMBER($new_price);
				$final_source_buy_amount[] = NUMBER($sourceport_commodity_amount[$itemcount]);
				$final_source_buy_type[] = ucfirst($sourceport_commodity_type[$itemcount]);
			}

//			echo "Sell to port $sourceport_commodity_type[$itemcount] - " . $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] . " - $item_price<br>";
			$ship_commodity_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] -= $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]];

			$commodity_total_sold[$sourceport_commodity_type[$itemcount]] += $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]];
			$commodity_total_credits_made[$sourceport_commodity_type[$itemcount]] += $sale_price;
			$cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] = 0;
		}
		else
		{
//			$item_price = $commodity_price[$sourceport_commodity_type[$itemcount]] - $commodity_delta[$sourceport_commodity_type[$itemcount]] * $amount_player_buy / $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] * $inventory_factor;
			$item_price = $offered_sell_price;
			if($sourceport_commodity_type[$itemcount] != "energy")
				$free_holds -= ($amount_player_buy * $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]);
			$goodevil = $sourceport_goodevil[$itemcount];
			$total_cost = $item_price * $amount_player_buy;
			$portlimit = $commodity_itemlimit[$sourceport_commodity_type[$itemcount]];

			if($i == 0)
			{
				$template_object->assign("sourceport_sell_commodity_amount", NUMBER($sourceport_commodity_amount[$itemcount]));
				$template_object->assign("sourceport_sell_item_price", NUMBER($item_price));
				$template_object->assign("sourceport_sell_item_type", ucfirst($sourceport_commodity_type[$itemcount]));
			}

			$sourceport_commodity_amount[$itemcount] = max(0, $sourceport_commodity_amount[$itemcount] - $amount_player_buy);
			$final_source_sell_price = NUMBER($item_price);
			$final_source_sell_amount = NUMBER($sourceport_commodity_amount[$itemcount]);

			$commodity_total_bought[$sourceport_commodity_type[$itemcount]] += $amount_player_buy;
			$commodity_total_credits_lost[$sourceport_commodity_type[$itemcount]] += $total_cost;
			$cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] = 0;
//			$ship_commodity_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] += $amount_player_buy;

//			echo "Buy from port $sourceport_commodity_type[$itemcount] - " . $amount_player_buy . " - $item_price<br>";
		}
	}

	$template_object->assign("sourceport_buy_commodity_amount", $sourceport_buy_commodity_amount);
	$template_object->assign("sourceport_buy_item_price", $sourceport_buy_item_price);
	$template_object->assign("sourceport_buy_item_type", $sourceport_buy_item_type);

//	echo "Total Cost: " . floor($total_sale - $total_cost) . "<br>";
	$playerinfo['credits'] += floor($total_sale - $total_cost);
//	echo "Credits = " . number($playerinfo['credits']) . "<br><br>";

	if ($shipdevice['dev_fuelscoop']['amount'] == 1){
		if(($dist['scooped1'] + $ship_commodity_amount[$ship_commodity_ref['energy']]) < NUM_ENERGY($shipinfo['power']))
		{
			$scoopedenergy = $dist['scooped1'];
		}
		else
		{
			$scoopedenergy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
		}
//		echo"Energy Scooped: " . NUMBER($scoopedenergy) . "<br><br>";
		$total_energy_scooped += $scoopedenergy;
		$ship_commodity_amount[$ship_commodity_ref['energy']] += $scoopedenergy;
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
			$planet_commodity_amount[$ship_commodity_ref['energy']] += $energy_dump;
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
		//	echo "$l_tdr_dumped " . NUMBER($ship_commodity_amount[$item]) . " " . $ship_commodity_type[$item] . "<br>";
			$planet_commodity_amount[$item] += $ship_commodity_amount[$item];
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
//	echo "Credits = " . number($playerinfo['credits']) . "<br>";
//	foreach($ship_commodity_type as $key=>$value){ 
//			echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//	}
//	echo"<br>";

//	echo "Planet Energy = " . number($planetinfo['energy']) . "<br>";
//	foreach($planet_commodity_type as $key=>$value){ 
//		echo "$value: " . number($planet_commodity_amount[$key]) . "<br>";
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
//		echo "Credits = " . number($playerinfo['credits']) . "<br>";

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

//		echo "Planet Energy = " . number($planet_commodity_amount[$ship_commodity_ref['energy']]) . "<br>";

		$ship_holds_used_return = 0;
		$ship_energy_used_return = 0;
		for($itemcount = 0; $itemcount < $ship_item_count - 1; $itemcount++)
		{
			$ship_holds_used_return += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
		}
		$free_holds_return = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used_return;
		$free_energy_return = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
//echo $free_energy_return . "<br>";
		foreach($planet_commodity_type as $key=>$value)
		{ 
//echo $value . " - " . $traderoute['destination_commodity'] . "<br>";
			if($value == $traderoute['destination_commodity'])
			{
				if($value != "energy")
				{
					$return_amount = (($planet_commodity_amount[$key] * $ship_commodity_holds[$key]) < $free_holds_return) ? $planet_commodity_amount[$key] : floor($free_holds_return / $ship_commodity_holds[$key]);
					$planet_commodity_amount[$key] -= $return_amount;
					$ship_commodity_amount[$key] += $return_amount;
					$destination_commodity_loaded += $return_amount;
//					echo "Loading: $value - $return_amount<br>";
				}
				else
				{
					$free_energy_return = ($planet_commodity_amount[$key] < $free_energy_return) ? $planet_commodity_amount[$key] : $free_energy_return;
					$planet_commodity_amount[$key] -= $free_energy_return;
					$ship_commodity_amount[$key] += $free_energy_return;
					$destination_commodity_loaded += $free_energy_return;
//					echo "Loading: $value - $free_energy_return<br>";
				}
			}
//			echo "$value: " . number($planet_commodity_amount[$key]) . "<br>";
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
	if($playerinfo['credits'] <= 0 || $playerinfo['turns'] <= 0)
	{
		$trades_completed = $i;
		$i = $tr_repeat;
	}
}

//echo "UPDATE {$db_prefix}planets SET energy=$planetinfo[energy], organics=" . $planet_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[destination_planet_id]<br><br>";
if(empty($planetinfo['special_name']))
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET energy=" . $planet_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[destination_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
else
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET special_amount=" . $planet_commodity_amount[$ship_commodity_ref[$planetinfo['special_name']]] . ", energy=" . $planet_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[destination_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
//echo "UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);
//echo "UPDATE {$db_prefix}players SET credits=" . floor($playerinfo['credits']) . ", turns=$playerinfo[turns], turns_used=$playerinfo[turns_used] WHERE player_id=$playerinfo[player_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=" . floor($playerinfo['credits']) . ", turns=$playerinfo[turns], turns_used=$playerinfo[turns_used] WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

foreach($ship_commodity_type as $key=>$value){ 
	if($ship_commodity_id[$key] != 0)
	{
//		echo "UPDATE {$db_prefix}ship_holds SET amount=" . floor($ship_commodity_amount[$key]) . " WHERE hold_id=" . $ship_commodity_id[$key] . "<br><br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount=" . floor($ship_commodity_amount[$key]) . " WHERE hold_id=" . $ship_commodity_id[$key]);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

$total_credits_made = 0;
foreach($commodity_total_sold as $key=>$value){ 
	if($commodity_total_sold[$key] != 0)
	{
//		echo "Sold " . $commodity_total_sold[$key] . " " . $key . " for " . number($commodity_total_credits_made[$key]) . " credits <br>";
		$commodity_total_sold[$key] = NUMBER($commodity_total_sold[$key]);
		$total_credits_made += $commodity_total_credits_made[$key];
		$commodity_total_credits_made[$key] = NUMBER($commodity_total_credits_made[$key]);
	}
}
$template_object->assign("commodity_total_sold", $commodity_total_sold);
$template_object->assign("commodity_total_credits_made", $commodity_total_credits_made);
$template_object->assign("total_credits_made", NUMBER($total_credits_made));

$total_credits_lost = 0;
foreach($commodity_total_bought as $key=>$value){ 
	if($commodity_total_bought[$key] != 0)
	{
//		echo "Bought " . $commodity_total_bought[$key] . " " . $key . " for " . number($commodity_total_credits_lost[$key]) . " credits <br>";
		$commodity_total_bought[$key] = NUMBER($commodity_total_bought[$key]);
		$total_credits_lost += $commodity_total_credits_lost[$key];
		$commodity_total_credits_lost[$key] = NUMBER($commodity_total_credits_lost[$key]);
	}
}
$template_object->assign("commodity_total_bought", $commodity_total_bought);
$template_object->assign("commodity_total_credits_lost", $commodity_total_credits_lost);
$template_object->assign("total_credits_lost", NUMBER($total_credits_lost));

$trade_date = date("Y-m-d H:i:s");

//echo "Credit Result: " . ($total_credits_made - $total_credits_lost) . "<br><br>";
for($i = 0; $i < $sourceport_commodity_count; $i++)
{
//	echo $sourceport_commodity_type[$i] . "<br>";
//	echo "UPDATE {$db_prefix}universe_ports SET commodity_amount=$sourceport_commodity_amount[$i], commodity_price=$sourceport_commodity_price[$i] WHERE data_id=$sourceport_data_id[$i]<br><br>";
	$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET trade_date='$trade_date', commodity_amount=$sourceport_commodity_amount[$i], commodity_price=$sourceport_commodity_price[$i] WHERE data_id=$sourceport_data_id[$i]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
//echo"<br>";

$template_object->assign("total_energy_dumped", NUMBER($total_energy_dumped));
$template_object->assign("total_energy_scooped", NUMBER($total_energy_scooped));

$template_object->assign("planet_energy_end", NUMBER($planetinfo['energy']));
$template_object->assign("planet_end_amount", $planet_commodity_amount);

$template_object->assign("l_tdr_dumped", $l_tdr_dumped);
$template_object->assign("l_tdr_starting_credits", $l_tdr_starting_credits);
$template_object->assign("l_tdr_ending_credits", $l_tdr_ending_credits);
$template_object->assign("starting_player_credits", NUMBER($starting_player_credits));
$template_object->assign("ending_player_credits", NUMBER($playerinfo['credits']));
$template_object->assign("l_tdr_bought", $l_tdr_bought);
$template_object->assign("l_tdr_sold", $l_tdr_sold);
$template_object->assign("total_turns_used", $total_turns_used);
$template_object->assign("turns_left", $playerinfo['turns']);
$template_object->assign("l_tdr_turnsleft", $l_tdr_turnsleft);
$template_object->assign("l_tdr_turnsused", $l_tdr_turnsused);
$template_object->assign("final_credits", NUMBER($playerinfo['credits'] - $starting_player_credits));
$template_object->assign("l_tdr_scooped", $l_tdr_scooped);
$template_object->assign("l_tdr_energy", $l_tdr_energy);
$template_object->assign("tr_repeat", $trades_completed);
$template_object->assign("profit_loss", ($playerinfo['credits'] < $starting_player_credits));
$template_object->assign("l_tdr_totalcost", $l_tdr_totalcost);
$template_object->assign("l_tdr_totalprofit", $l_tdr_totalprofit);
$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->assign("l_tdr_runscompleted", $l_tdr_runscompleted);
$template_object->assign("l_global_mmenu", $l_global_mmenu);
$template_object->assign("final_source_sell_amount", $final_source_sell_amount);
$template_object->assign("final_source_sell_price", $final_source_sell_price);
$template_object->assign("final_destination_sell_amount", $final_destination_sell_amount);
$template_object->assign("final_destination_sell_price", $final_destination_sell_price);
$template_object->assign("final_destination_buy_price", $final_destination_buy_price);
$template_object->assign("final_destination_buy_amount", $final_destination_buy_amount);
$template_object->assign("final_destination_buy_type", $final_destination_buy_type);
$template_object->assign("final_source_buy_price", $final_source_buy_price);
$template_object->assign("final_source_buy_amount", $final_source_buy_amount);
$template_object->assign("final_source_buy_type", $final_source_buy_type);
$template_object->assign("destination_commodity_total", NUMBER($planet_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("destination_commodity2_total", NUMBER($planet_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));

$l_tdr_engageagain = str_replace("[tdr_engage]", $engage, $l_tdr_engageagain);
$template_object->assign("l_tdr_engageagain", $l_tdr_engageagain);
$template_object->assign("engage", $engage);
$template_object->assign("l_tdr_timestorep", $l_tdr_timestorep);
$template_object->assign("l_submit", $l_submit);

$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->send_now = 0;
$template_object->display($templatename."traderoute_port2planet.tpl");
?>
