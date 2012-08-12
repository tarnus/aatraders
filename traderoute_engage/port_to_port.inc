<?php
$port_debuging = 0;
 
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
	$name_result = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=" . $source['sector_id'], 1);
	if($port_debuging)
		echo ucfirst($source['port_type']) . " $l_tdr_portin " . $name_result->fields['sector_name'] . "<br>";
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
	$name_result = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=" . $dest['sector_id'], 1);
	if($port_debuging)
		echo ucfirst($dest['port_type']) . " $l_tdr_portin " . $name_result->fields['sector_name'] . "<br>";
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
$template_object->assign("l_tdr_trade", $l_tdr_trade);
$template_object->assign("l_tdr_start", $l_tdr_start);
$template_object->assign("l_tdr_finish", $l_tdr_finish);
$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->assign("l_tdr_buying", $l_tdr_buying);
$template_object->assign("l_tdr_selling", $l_tdr_selling);
$template_object->assign("l_tdr_units", $l_tdr_units);
$template_object->assign("l_tdr_credits", $l_tdr_credits);

$sourceport_buy_commodity_amount = array();
$sourceport_buy_item_price = array();
$sourceport_buy_item_type = array();
$destinationport_buy_commodity_amount = array();
$destinationport_buy_item_price = array();
$destinationport_buy_item_type = array();
$total_energy_scooped = 0;
$starting_player_credits = $playerinfo['credits'];
$total_turns_used = 0;
$trades_completed = $tr_repeat;

	for ($i = 0; $i < $tr_repeat; $i++)
	{
 		$total_experience += $trading_exp;
		$fighters_buy = 0;
		$torps_buy = 0;
		$energy_buy = 0;

		$final_source_buy_price = array();
		$final_source_buy_amount = array();
		$final_source_buy_type = array();
		$final_destination_buy_price = array();
		$final_destination_buy_amount = array();
		$final_destination_buy_type = array();

		$total_sale=0;
		$total_cost=0;
		$sourcecost=0;
		// Source is a port
	if($port_debuging)
			echo "Source $traderoute[source_commodity] Port<br>";
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
					$amount_player_buy = max(0, floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used_test) / $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]]));
	if($port_debuging)
		echo "Buying: $amount_player_buy<br>";
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
	if($port_debuging)
		echo "Buying: $amount_player_buy<br>";
				$amount_player_buy = min(max(0, $amount_player_buy), $sourceport_commodity_amount[$itemcount]);
	if($port_debuging)
		echo "Buying: $amount_player_buy<br>";
				if($sourceport_commodity_type[$itemcount] != "energy")
				{
					$ship_holds_used_test += ($ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] * $amount_player_buy);
				}
				$amount_port_sell = $sourceport_commodity_amount[$itemcount];
	if($port_debuging)
					echo "SOURCE: " . ucfirst($traderoute['source_commodity']) . " $l_selling amount:" . NUMBER($amount_port_sell) . " - buy amount: $amount_player_buy - on ship: " . NUMBER($ship_commodity_amount[$itemcount]) . " : " . $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] . "</br><br>";
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
	if($port_debuging)
					echo ucfirst($sourceport_commodity_type[$itemcount]) . " $l_buying " . NUMBER($sourceport_commodity_amount[$itemcount]) . " ".($offered_buy_price)." =$cargo_amount[$ship_commodity_number]= " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . " : " . $ship_commodity_holds[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] . "<br>";
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

	if($port_debuging)
			echo ucfirst($traderoute['source_commodity']) . " $l_selling " . NUMBER($amount_port_sell) . " $amount_player_buy " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . "</br><br>";
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

	if($port_debuging)
					echo "Sell to port $sourceport_commodity_type[$itemcount] - " . $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] . " - $item_price<br>";
				$ship_commodity_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] -= $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]];

				$commodity_total_sold[$sourceport_commodity_type[$itemcount]] += $cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]];
				$commodity_total_credits_made[$sourceport_commodity_type[$itemcount]] += $sale_price;
				$cargo_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] = 0;
			}
			else
			{
//				$item_price = $commodity_price[$sourceport_commodity_type[$itemcount]] - $commodity_delta[$sourceport_commodity_type[$itemcount]] * $amount_player_buy / $commodity_itemlimit[$sourceport_commodity_type[$itemcount]] * $inventory_factor;
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
//				$ship_commodity_amount[$ship_commodity_ref[$sourceport_commodity_type[$itemcount]]] += $amount_player_buy;

	if($port_debuging)
					echo "Buy from port $sourceport_commodity_type[$itemcount] - " . $amount_player_buy . " - $item_price<br>";
			}
		}

		$template_object->assign("sourceport_buy_commodity_amount", $sourceport_buy_commodity_amount);
		$template_object->assign("sourceport_buy_item_price", $sourceport_buy_item_price);
		$template_object->assign("sourceport_buy_item_type", $sourceport_buy_item_type);

	if($port_debuging)
			echo "Total Cost: " . floor($total_sale - $total_cost) . "<br>";
		$playerinfo['credits'] += $total_sale - $total_cost;
	if($port_debuging)
			echo "Credits = " . number($playerinfo['credits']) . "<br><br>";

		if ($shipdevice['dev_fuelscoop']['amount'] == 1){
			if(($dist['scooped1'] + $ship_commodity_amount[$ship_commodity_ref['energy']]) < NUM_ENERGY($shipinfo['power']))
			{
				$scoopedenergy = $dist['scooped1'];
			}
			else
			{
				$scoopedenergy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
			}
	if($port_debuging)
				echo"Energy Scooped: " . NUMBER($scoopedenergy) . "<br><br>";
			$total_energy_scooped += $scoopedenergy;
			$ship_commodity_amount[$ship_commodity_ref['energy']] += $scoopedenergy;
		}

	if($port_debuging)
	{		echo "Ship Fighters = " . number($shipinfo['fighters']) . "<br>";
		echo "Ship Torps = " . number($shipinfo['torps']) . "<br>";
		foreach($ship_commodity_type as $key=>$value){ 
				echo "$value $key: " . number($ship_commodity_amount[$key]) . " : " . $ship_commodity_holds[$key] . "<br>";
		}
		echo"<br>";
	}

		$amount_buy_tot = 0;
		$amount_port_buy = 0;
		$amount_port_sell = 0;
		$amount_player_buy = 0;
		$total_sale=0;
		$total_cost=0;
		$credits_made = 0;
		// Destination is a port
	if($port_debuging)
			echo "<br>Destination $traderoute[destination_commodity] Port<br><br>";

	$ship_holds_used = 0;
	for($itemcount = 0; $itemcount < $ship_item_count - 1; $itemcount++)
	{
		$ship_holds_used += ($ship_commodity_amount[$itemcount] * $ship_commodity_holds[$itemcount]);
	}
	$ship_holds_used_test = $ship_holds_used;
	if($port_debuging)
	{		echo "NUM_HOLDS: " . NUM_HOLDS($shipinfo['hull']) . "<br>";
		echo "ship_holds_used: $ship_holds_used<br>";
	}
		for($itemcount = 0; $itemcount < $destinationport_commodity_count; $itemcount++)
		{
			if($dest['port_type'] == $destinationport_commodity_type[$itemcount])
			{
				if($destinationport_commodity_type[$itemcount] != "energy")
				{
					$amount_player_buy = max(0, floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used_test) / $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]]));
				}
				else
				{
					$ship_commodity_number = $ship_commodity_ref[$destinationport_commodity_type[$itemcount]];
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
				$amount_port_sell = $destinationport_commodity_amount[$itemcount];
	if($port_debuging)
					echo "DESTINATION: " . ucfirst($destinationport_commodity_type[$itemcount]) . " $l_selling " . NUMBER($amount_port_sell) . " - $amount_player_buy " . NUMBER($ship_commodity_amount[$itemcount]) . " : " . $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] . "</br><br>";
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
	if($port_debuging)
					echo ucfirst($destinationport_commodity_type[$itemcount]) . " $l_buying " . NUMBER($destinationport_commodity_amount[$itemcount]) . " ".($offered_buy_price)." =$cargo_amount[$ship_commodity_number]= " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . "<br>";
				$amount_port_buy = $cargo_amount[$ship_commodity_number];
				if($destinationport_commodity_type[$itemcount] != "energy")
				{
	if($port_debuging)
						echo "cargo amount = " . $cargo_amount[$ship_commodity_number] . " : ship holds = " . $ship_commodity_holds[$ship_commodity_number] . "<br>";
					$ship_holds_used_test -= ($cargo_amount[$ship_commodity_number] * $ship_commodity_holds[$ship_commodity_number]);
					$amount_buy_tot+=$amount_port_buy;
				}
			}
	if($port_debuging)
				echo "ship_holds_used_test = $ship_holds_used_test <br>";
		}

		$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;

//		if($dest['port_type'] != "energy")
//		{
//			$amount_player_buy += $amount_buy_tot;
//		}

	if($port_debuging)
	{		echo "Credit Made: $credits_made<br>";
		echo "amount_player_buy: $amount_player_buy<br>";
	}
	if($port_debuging)
			echo "amount_player_buy: $amount_player_buy<br>";
		$ship_commodity_number = $ship_commodity_ref[AAT_strtolower($traderoute['destination_commodity'])];
		$credits_made -= floor(($amount_player_buy * $offered_sell_price));
	if($port_debuging)
			echo "Credit Made: $credits_made - $offered_sell_price<br>";

	if($port_debuging)
			echo ucfirst($traderoute['destination_commodity']) . " $l_selling " . NUMBER($amount_port_sell) . " - $amount_player_buy " . NUMBER($ship_commodity_amount[$ship_commodity_number]) . " : " . $ship_commodity_holds[$ship_commodity_ref[$destinationport_commodity_type[$ship_commodity_number]]] . "</br><br>";
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
//echo "reduce_rate: $reduce_rate, " . $destinationport_commodity_price[$itemcount] . "<br>";
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

	if($port_debuging)
					echo "Sell to port $destinationport_commodity_type[$itemcount] - " . $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] . " - $item_price<br>";
				$ship_commodity_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] -= $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]];

				$commodity_total_sold[$destinationport_commodity_type[$itemcount]] += $cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]];
				$commodity_total_credits_made[$destinationport_commodity_type[$itemcount]] += $sale_price;
				$cargo_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] = 0;
			}
			else
			{
//				$item_price = $commodity_price[$destinationport_commodity_type[$itemcount]] - $commodity_delta[$destinationport_commodity_type[$itemcount]] * $amount_player_buy / $commodity_itemlimit[$destinationport_commodity_type[$itemcount]] * $inventory_factor;
				$item_price = $offered_sell_price;
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
//				$ship_commodity_amount[$ship_commodity_ref[$destinationport_commodity_type[$itemcount]]] += $amount_player_buy;

	if($port_debuging)
					echo "Buy from port $destinationport_commodity_type[$itemcount] - " . $amount_player_buy . " - $item_price<br>";
			}
		}

		$template_object->assign("destinationport_buy_commodity_amount", $destinationport_buy_commodity_amount);
		$template_object->assign("destinationport_buy_item_price", $destinationport_buy_item_price);
		$template_object->assign("destinationport_buy_item_type", $destinationport_buy_item_type);

	if($port_debuging)
			echo "Total Cost: " . floor($total_sale - $total_cost) . "<br>";
		$playerinfo['credits'] += ($total_sale - $total_cost);

	if($port_debuging)
	{		echo"<br>";
		echo "Trade Route One-Way<br>";
		echo "Credits = " . number($playerinfo['credits']) . "<br>";
		echo "Ship Fighters = " . number($shipinfo['fighters']) . "<br>";
		echo "Ship Torps = " . number($shipinfo['torps']) . "<br>";
		foreach($ship_commodity_type as $key=>$value){ 
				echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
		}
		echo"<br>";

		foreach($sourceport_commodity_amount as $key=>$value){ 
			echo "SOurce Port $sourceport_commodity_type[$key]: " . number($value) . "<br>";
		}
		echo "<br>";
		foreach($destinationport_commodity_amount as $key=>$value){ 
			echo "Destination Port $destinationport_commodity_type[$key]: " . number($value) . "<br>";
		}
		echo "<br>Turns Used = " . $dist['triptime'] . "<br>";
		echo "Player Turns = " . $playerinfo['turns'] . "<br>";
		echo "Player Turns Used = " . $playerinfo['turns_used'] . "<br>";
	}
		$playerinfo['turns'] = max (0, $playerinfo['turns'] - $dist['triptime']);
		$playerinfo['turns_used'] = max (0, $playerinfo['turns_used'] + $dist['triptime']);
	if($port_debuging)
	{		echo "Player Turns - Turns Used = " . $playerinfo['turns'] . "<br>";
		echo "Player Turns Used + Turns Used = " . $playerinfo['turns_used'] . "<br>";
	}
		$total_turns_used += $dist['triptime'];

		$shipinfo['sector_id'] = $dest['sector_id'];

		if($playerinfo['turns'] <= 0)
		{
			$trades_completed = $i;
			$i = $tr_repeat;
		}
	if($port_debuging)
			echo"<hr>";

		if($traderoute['roundtrip'] == "Y" && $playerinfo['turns'] > 0)
		{
	if($port_debuging)
	{			echo"<br>";
			echo "Trade Route Return Trip<br><br>";
		}

			if ($shipdevice['dev_fuelscoop']['amount'] == 1){
				if(($dist['scooped2'] + $ship_commodity_amount[$ship_commodity_ref['energy']]) < NUM_ENERGY($shipinfo['power']))
				{
					$scoopedenergy = $dist['scooped2'];
				}
				else
				{
					$scoopedenergy = NUM_ENERGY($shipinfo['power']) - $ship_commodity_amount[$ship_commodity_ref['energy']];
				}
	if($port_debuging)
					echo"Energy Scooped: " . NUMBER($scoopedenergy) . "<br><br>";
				$total_energy_scooped += $scoopedenergy;
				$ship_commodity_amount[$ship_commodity_ref['energy']] += $scoopedenergy;
			}

	if($port_debuging)
	{
			echo "Ship Fighters = " . number($shipinfo['fighters']) . "<br>";
			echo "Ship Torps = " . number($shipinfo['torps']) . "<br>";
			foreach($ship_commodity_type as $key=>$value){ 
					echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
			}
			echo"<br>";

			echo "Turns Used = " . $dist['triptime'] . "<br>";
			echo "Player Turns = " . $playerinfo['turns'] . "<br>";
			echo "Player Turns Used = " . $playerinfo['turns_used'] . "<br>";
		}
			$playerinfo['turns'] = max (0, $playerinfo['turns'] - $dist['triptime']);
			$playerinfo['turns_used'] = max (0, $playerinfo['turns_used'] + $dist['triptime']);
	if($port_debuging)
	{
			echo "Player Turns - Turns Used = " . $playerinfo['turns'] . "<br>";
			echo "Player Turns Used + Turns Used = " . $playerinfo['turns_used'] . "<br>";
		}
			$total_turns_used += $dist['triptime'];

			$shipinfo['sector_id'] = $source['sector_id'];
		}
	if($port_debuging)
			echo"<hr>";
		if($playerinfo['credits'] <= 0 || $playerinfo['turns'] <= 0){
			$trades_completed = $i;
			$i = $tr_repeat;
		}
 	}

$ship_commodity_amount[$ship_commodity_ref['energy']] = min($ship_commodity_amount[$ship_commodity_ref['energy']], NUM_ENERGY($shipinfo['power']));
//echo "UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], fighters=$shipinfo[fighters], torps=$shipinfo[torps], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], fighters=$shipinfo[fighters], torps=$shipinfo[torps], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]");
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
for($i = 0; $i < $destinationport_commodity_count; $i++)
{
//	echo $destinationport_commodity_type[$i] . "<br>";
//	echo "UPDATE {$db_prefix}universe_ports SET commodity_amount=$destinationport_commodity_amount[$i], commodity_price=$destinationport_commodity_price[$i] WHERE data_id=$destinationport_data_id[$i]<br><br>";
	$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET trade_date='$trade_date', commodity_amount=$destinationport_commodity_amount[$i], commodity_price=$destinationport_commodity_price[$i] WHERE data_id=$destinationport_data_id[$i]");
	db_op_result($debug_query,__LINE__,__FILE__);
}


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
$template_object->assign("total_energy_scooped", NUMBER($total_energy_scooped));
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

$l_tdr_engageagain = str_replace("[tdr_engage]", $engage, $l_tdr_engageagain);
$template_object->assign("l_tdr_engageagain", $l_tdr_engageagain);
$template_object->assign("engage", $engage);
$template_object->assign("l_tdr_timestorep", $l_tdr_timestorep);
$template_object->assign("l_submit", $l_submit);

$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->send_now = 0;
$template_object->display($templatename."traderoute_port2port.tpl");
?>
