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
	$name_result = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=" . $dest['sector_id'], 1);
//	echo ucfirst($dest['port_type']) . " $l_tdr_portin " . $name_result->fields['sector_name'];
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$dest[sector_id] ORDER BY data_id DESC");
	db_op_result($debug_query,__LINE__,__FILE__);
	$destinationport_commodity_count = 0;
	while(!$debug_query->EOF){
		$destinationport_data_id[$destinationport_commodity_count] = $debug_query->fields['data_id'];
		$destinationport_commodity_type[$destinationport_commodity_count] = $debug_query->fields['commodity_type'];
		$destinationport_commodity_amount[$destinationport_commodity_count] = $debug_query->fields['commodity_amount'];
		$destinationport_commodity_price[$destinationport_commodity_count] = $debug_query->fields['commodity_price'];
		$destinationport_goodevil[$destinationport_commodity_count] = $debug_query->fields['goodevil'];
		$destinationport_commodity_count++;
		$debug_query->MoveNext();
	}
	$debug_query->close();

$template_object->assign("destination_port_type", ucfirst($dest['port_type']));
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
$template_object->assign("l_tdr_dumped", $l_tdr_dumped);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_torps", $l_torps);


$template_object->assign("source_start_fighters", NUMBER($planet_source_info['fighters']));
$template_object->assign("source_start_torps", NUMBER($planet_source_info['torps']));
$template_object->assign("source_commodity_start", NUMBER($planet_source_commodity_amount[$ship_commodity_ref[$traderoute['source_commodity']]]));
$template_object->assign("source_commodity2_start", NUMBER($planet_source_commodity_amount[$ship_commodity_ref[$traderoute['destination_commodity']]]));


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
$destinationport_buy_commodity_amount = array();
$destinationport_buy_item_price = array();
$destinationport_buy_item_type = array();

for ($i = 0; $i < $tr_repeat; $i++)
{
	$total_experience += $trading_exp;

		$final_destination_buy_price = array();
		$final_destination_buy_amount = array();
		$final_destination_buy_type = array();

	// Source is a port
//	echo "Source $traderoute[source_commodity] Planet<br>";

		$total_sale=0;
		$total_cost=0;
		$sourcecost=0;
		// Source is a port
//		echo "Source $traderoute[source_commodity] Port<br>";
		$ship_holds_used = 0;
		$amount_buy_tot = 0;
		$amount_port_buy = 0;
		$amount_port_sell = 0;
		$amount_player_buy = 0;
		$credits_made = 0;

	if ($traderoute['trade_energy'] == 'Y')
	{
		$energy_dump = $ship_commodity_amount[$ship_commodity_ref['energy']];
		$planet_source_commodity_amount[$ship_commodity_ref['energy']] += $energy_dump;
		$destination_commodity_dumped += $energy_dump;
		$ship_commodity_amount[$ship_commodity_ref['energy']] = 0;
//		echo "$l_tdr_dumped " . NUMBER($energy_dump) . " Energy<br>";
	}
	else
	{
		$energy_dump = 0;
	}
 
	$total_energy_dumped += $energy_dump;

	for ($item = 0; $item < $ship_item_count - 1; $item++)
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
	for($itemcount = 0; $itemcount < $ship_item_count - 1; $itemcount++)
	{
		$ship_holds_used += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
	}

	$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
	$free_energy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
//	echo "free_holds: $free_holds<br>";

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

		$ship_holds_used = 0;
		for($itemcount = 0; $itemcount < $ship_item_count - 1; $itemcount++)
		{
			$ship_holds_used += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
		}
		$ship_holds_used_test = $ship_holds_used;
		for($itemcount = 0; $itemcount < $destinationport_commodity_count; $itemcount++)
		{
			if($dest['port_type'] == $destinationport_commodity_type[$itemcount])
			{
/*
				if($destinationport_commodity_type[$itemcount] != "energy")
				{
					$amount_player_buy = max(0, floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used_test) / $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]));
				}
				else
				{
					$ship_commodity_number = $ship_commodity_ref[$sourceport_commodity_type[$itemcount]];
					if($traderoute['trade_energy'] == 'Y')
						$amount_player_buy = NUM_ENERGY($shipinfo['power']) - $cargo_amount[$ship_commodity_number];
					else
						$amount_player_buy = 0;
				}
				$offered_sell_price = max($destinationport_commodity_price[$itemcount] - $commodity_delta[$destinationport_commodity_type[$itemcount]] * $amount_player_buy / $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
				$amount_player_buy = min($amount_player_buy, floor(($playerinfo['credits'] + $credits_made) / $offered_sell_price));
				$amount_player_buy = min($amount_player_buy, $destinationport_commodity_amount[$itemcount]);
				if($destinationport_commodity_type[$itemcount] != "energy")
				{
					$ship_holds_used_test += ($ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] * $amount_player_buy);
				}
*/
				$amount_player_buy = 0;
				$amount_port_sell = $destinationport_commodity_amount[$itemcount];
//				echo ucfirst($dest['port_type']) . " $l_selling " . NUMBER($amount_port_sell) . " - $amount_player_buy " . NUMBER($ship_commodity_amount[$itemcount]) . " : " . $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] . "</br><br>";
			}
			else
			{
				$offered_buy_price = max($destinationport_commodity_price[$itemcount] + $commodity_price[$destinationport_commodity_type[$itemcount]] + $commodity_delta[$destinationport_commodity_type[$itemcount]] * $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] / $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] * $inventory_factor, 0.01);

				if($offered_buy_price <= 0)
					$offered_buy_price = 0.01;

				$ship_commodity_number = $ship_commodity_ref[$destinationport_commodity_type[$itemcount]];
				$cargo_amount[$ship_commodity_number] = (isset($ship_commodity_amount[$ship_commodity_number])) ? $ship_commodity_amount[$ship_commodity_number] : 0;
				$cargo_amount[$ship_commodity_number] = min($cargo_amount[$ship_commodity_number], $destinationport_commodity_amount[$itemcount]);
				if($traderoute['trade_energy'] == 'N' && $sourceport_commodity_type[$itemcount] == "energy")
					$cargo_amount[$ship_commodity_number] = 0;
				$credits_made += floor(($cargo_amount[$ship_commodity_number] * $offered_buy_price));
//				echo ucfirst($destinationport_commodity_type[$itemcount]) . " $l_buying " . NUMBER($destinationport_commodity_amount[$itemcount]) . " ".($offered_buy_price)." =$cargo_amount[$ship_commodity_number]= " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . "<br>";
				$amount_port_buy = $cargo_amount[$ship_commodity_number];
				if($destinationport_commodity_type[$itemcount] != "energy")
				{
//					echo "cargo amount = " . $cargo_amount[$ship_commodity_number] . " : ship holds = " . $ship_commodity_holds[$ship_commodity_number] . "<br>";
					$ship_holds_used_test -= ($cargo_amount[$ship_commodity_number] * $ship_commodity_holds[$ship_commodity_number]);
					$amount_buy_tot+=$amount_port_buy;
				}
			}
//			echo "ship_holds_used_test = $ship_holds_used_test<br>";
		}

		$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;

//		echo "Credit Made: $credits_made<br>";
		$ship_commodity_number = $ship_commodity_ref[AAT_strtolower($traderoute['destination_commodity'])];
		$credits_made -= floor(($amount_player_buy * $offered_sell_price));
//		echo "Credit Made: $credits_made - $offered_sell_price<br>";

//		echo ucfirst($traderoute['destination_commodity']) . " $l_selling " . NUMBER($amount_port_sell) . " $amount_player_buy " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . "</br><br>";
		$ship_commodity_amount[$ship_commodity_number] += $amount_player_buy;

		for($itemcount = 0; $itemcount < $destinationport_commodity_count; $itemcount++)
		{
			if($destinationport_commodity_type[$itemcount] != AAT_strtolower($traderoute['destination_commodity'])){
				$item_price = max($destinationport_commodity_price[$itemcount] + $commodity_price[$destinationport_commodity_type[$itemcount]] + $commodity_delta[$destinationport_commodity_type[$itemcount]] * $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] / $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
				if($destinationport_commodity_amount[$itemcount] < $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]])
					$cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] = $destinationport_commodity_amount[$itemcount];

				if($destinationport_commodity_type[$itemcount] != "energy")
					$free_holds += ($cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] * $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]);

				$sale_price = $item_price * abs($cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]);
				$total_sale += $sale_price;
				$reduce_rate = ($destinationport_commodity_price[$itemcount] > $commodity_price[$destinationport_commodity_type[$itemcount]]) ? ($commodity_reducerate[$destinationport_commodity_type[$itemcount]] * ($destinationport_commodity_price[$itemcount] / $commodity_price[$destinationport_commodity_type[$itemcount]])) : $commodity_reducerate[$destinationport_commodity_type[$itemcount]];
				$reduce_rate = $commodity_reducerate[$destinationport_commodity_type[$itemcount]];
				$destinationport_commodity_price[$itemcount] = $destinationport_commodity_price[$itemcount] - ($reduce_rate * $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]);

				if($i == 0)
				{
					$destinationport_buy_commodity_amount[] = NUMBER($destinationport_commodity_amount[$itemcount]);
					$destinationport_buy_item_price[] = NUMBER($item_price);
					$destinationport_buy_item_type[] = ucfirst($destinationport_commodity_type[$itemcount]);
				}

				$destinationport_commodity_amount[$itemcount] = max(0, $destinationport_commodity_amount[$itemcount] - $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]);
				if($i == ($tr_repeat - 1))
				{
					$new_price = max($destinationport_commodity_price[$itemcount] + $commodity_price[$destinationport_commodity_type[$itemcount]] + $commodity_delta[$destinationport_commodity_type[$itemcount]] * $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] / $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
					$final_destination_buy_price[] = NUMBER($new_price);
					$final_destination_buy_amount[] = NUMBER($destinationport_commodity_amount[$itemcount]);
					$final_destination_buy_type[] = ucfirst($destinationport_commodity_type[$itemcount]);
				}

//				echo "Sell to port $destinationport_commodity_type[$itemcount] - " . $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] . " - $item_price<br>";
				$ship_commodity_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] -= $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]];

				$commodity_total_sold[$destinationport_commodity_type[$itemcount]] += $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]];
				$commodity_total_credits_made[$destinationport_commodity_type[$itemcount]] += $sale_price;
				$cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] = 0;
			}
			else
			{
				$item_price = max($commodity_price[$destinationport_commodity_type[$itemcount]] - $commodity_delta[$destinationport_commodity_type[$itemcount]] * $amount_player_buy / $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] * $inventory_factor, 0.01);
//				$item_price = $offered_sell_price;
				if($destinationport_commodity_type[$itemcount] != "energy")
					$free_holds -= ($amount_player_buy * $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]);
				$goodevil = $destinationport_goodevil[$itemcount];
				$total_cost = $item_price * $amount_player_buy;
				$portlimit = $commodity_itemlimit[$destinationport_commodity_type[$itemcount]];

				if($i == 0)
				{
					$template_object->assign("destinationport_sell_commodity_amount", NUMBER($destinationport_commodity_amount[$itemcount]));
					$template_object->assign("destinationport_sell_item_price", NUMBER($item_price));
					$template_object->assign("destinationport_sell_item_type", ucfirst($destinationport_commodity_type[$itemcount]));
				}

				$destinationport_commodity_amount[$itemcount] = max(0, $destinationport_commodity_amount[$itemcount] - $amount_player_buy);
				$final_destination_sell_price = NUMBER($item_price);
				$final_destination_sell_amount = NUMBER($destinationport_commodity_amount[$itemcount]);

				$commodity_total_bought[$destinationport_commodity_type[$itemcount]] += $amount_player_buy;
				$commodity_total_credits_lost[$destinationport_commodity_type[$itemcount]] += $total_cost;
				$cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] = 0;

//				echo "Buy from port $destinationport_commodity_type[$itemcount] - " . $amount_player_buy . " - $item_price<br>";
			}
		}

		$template_object->assign("destinationport_buy_commodity_amount", $destinationport_buy_commodity_amount);
		$template_object->assign("destinationport_buy_item_price", $destinationport_buy_item_price);
		$template_object->assign("destinationport_buy_item_type", $destinationport_buy_item_type);

//		echo "Total Cost: " . floor($total_sale - $total_cost) . "<br>";
		$playerinfo['credits'] += $total_sale - $total_cost;

//		echo"<br>";
//		echo "Trade Route One-Way<br>";
//		echo "Credits = " . number($playerinfo['credits']) . "<br>";
//		foreach($ship_commodity_type as $key=>$value){ 
//				echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//		}
//		echo"<br>";

//		foreach($sourceport_commodity_amount as $key=>$value){ 
//			echo "SOurce Port $sourceport_commodity_type[$key]: " . number($value) . "<br>";
//		}
//		echo "<br>";
//		foreach($destinationport_commodity_amount as $key=>$value){ 
//			echo "Destination Port $destinationport_commodity_type[$key]: " . number($value) . "<br>";
//		}
//		echo "<br>Turns Used = " . $dist['triptime'] . "<br>";
//		echo "Player Turns = " . $playerinfo['turns'] . "<br>";
//		echo "Player Turns Used = " . $playerinfo['turns_used'] . "<br>";
		$playerinfo['turns'] = max (0, $playerinfo['turns'] - $dist['triptime']);
		$playerinfo['turns_used'] = max (0, $playerinfo['turns_used'] + $dist['triptime']);
//		echo "Player Turns - Turns Used = " . $playerinfo['turns'] . "<br>";
//		echo "Player Turns Used + Turns Used = " . $playerinfo['turns_used'] . "<br>";
		$total_turns_used += $dist['triptime'];

		$shipinfo['sector_id'] = $dest['sector_id'];

		if($playerinfo['turns'] <= 0)
		{
			$trades_completed = $i;
			$i = $tr_repeat;
		}
//		echo"<hr>";

		if($traderoute['roundtrip'] == "Y" && $playerinfo['turns'] > 0)
		{
//			echo"<br>";
//			echo "Trade Route Return Trip<br><br>";

			if ($shipdevice['dev_fuelscoop']['amount'] == 1){
				if(($dist['scooped2'] + $ship_commodity_amount[$ship_commodity_ref['energy']]) < NUM_ENERGY($shipinfo['power']))
				{
					$scoopedenergy = $dist['scooped2'];
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

//			foreach($ship_commodity_type as $key=>$value){ 
//					echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//			}
//			echo"<br>";

//			echo "Turns Used = " . $dist['triptime'] . "<br>";
//			echo "Player Turns = " . $playerinfo['turns'] . "<br>";
//			echo "Player Turns Used = " . $playerinfo['turns_used'] . "<br>";
			$playerinfo['turns'] = max (0, $playerinfo['turns'] - $dist['triptime']);
			$playerinfo['turns_used'] = max (0, $playerinfo['turns_used'] + $dist['triptime']);
//			echo "Player Turns - Turns Used = " . $playerinfo['turns'] . "<br>";
//			echo "Player Turns Used + Turns Used = " . $playerinfo['turns_used'] . "<br>";
			$total_turns_used += $dist['triptime'];

			$shipinfo['sector_id'] = $source['sector_id'];
		}
//		echo"<hr>";
		if($playerinfo['credits'] <= 0 || $playerinfo['turns'] <= 0){
			$trades_completed = $i;
			$i = $tr_repeat;
		}
}

//echo "UPDATE {$db_prefix}planets SET energy=" . $planet_source_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_source_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_source_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_source_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_source_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[source_planet_id]<br><br>";
if(empty($planet_source_info['special_name']))
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET energy=" . $planet_source_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_source_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_source_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_source_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_source_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[source_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
else
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET special_amount=" . $planet_source_commodity_amount[$ship_commodity_ref[$planet_source_info['special_name']]] . ", energy=" . $planet_source_commodity_amount[$ship_commodity_ref['energy']] . ", organics=" . $planet_source_commodity_amount[$ship_commodity_ref['organics']] . ", ore=" . $planet_source_commodity_amount[$ship_commodity_ref['ore']] . ", goods=" . $planet_source_commodity_amount[$ship_commodity_ref['goods']] . ", colonists=" . $planet_source_commodity_amount[$ship_commodity_ref['colonists']] . " WHERE planet_id=$traderoute[source_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
}
//echo "UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);
//echo "UPDATE {$db_prefix}players SET turns=$playerinfo[turns], turns_used=$playerinfo[turns_used], credits=$playerinfo[credits] WHERE player_id=$playerinfo[player_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=$playerinfo[turns], turns_used=$playerinfo[turns_used], credits=$playerinfo[credits] WHERE player_id=$playerinfo[player_id]");
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

$template_object->assign("l_tdr_totalprofit", $l_tdr_totalprofit);
$template_object->assign("is_profit", (($total_credits_made - $total_credits_lost) >= 0) ? 1 : 0);
$template_object->assign("total_profit", NUMBER($total_credits_made - $total_credits_lost));

$trade_date = date("Y-m-d H:i:s");

//echo"<br>";
for($i = 0; $i < $destinationport_commodity_count; $i++)
{
//	echo $destinationport_commodity_type[$i] . "<br>";
//	echo "UPDATE {$db_prefix}universe_ports SET commodity_amount=$destinationport_commodity_amount[$i], commodity_price=$destinationport_commodity_price[$i] WHERE data_id=$destinationport_data_id[$i]<br><br>";
	$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET trade_date='$trade_date', commodity_amount=$destinationport_commodity_amount[$i], commodity_price=$destinationport_commodity_price[$i] WHERE data_id=$destinationport_data_id[$i]");
	db_op_result($debug_query,__LINE__,__FILE__);
}



$template_object->assign("total_energy_dumped", NUMBER($total_energy_dumped));
$template_object->assign("total_energy_scooped", NUMBER($total_energy_scooped));

$template_object->assign("planet_energy_end", $planet_destination_info['energy']);
$template_object->assign("planet_end_amount", $planet_destination_commodity_amount);

$template_object->assign("l_tdr_portin", $l_tdr_portin);
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
$template_object->assign("final_destination_sell_amount", $final_destination_sell_amount);
$template_object->assign("final_destination_sell_price", $final_destination_sell_price);
$template_object->assign("final_destination_buy_price", $final_destination_buy_price);
$template_object->assign("final_destination_buy_amount", $final_destination_buy_amount);
$template_object->assign("final_destination_buy_type", $final_destination_buy_type);

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
$template_object->display($templatename."traderoute_planet2port.tpl");
?>
