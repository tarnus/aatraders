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
	$commodity_query->MoveNext();
}
$commodity_query->close();

// ------------ Determine if Source is Planet or Port
$name_result = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=" . $source['sector_id'], 1);
//echo ucfirst($source['port_type']) . " $l_tdr_portin " . $name_result->fields['sector_name'];

$template_object->assign("source_port_type", ucfirst($source['port_type']));
$template_object->assign("l_tdr_portin", $l_tdr_portin);
$template_object->assign("source_sector_name", $name_result->fields['sector_name']);
$name_result->close();

// ------------ Determine if Destination is Planet or Port
$name_result = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id=" . $destport['sector_id'], 1);
//echo "$l_tdr_planet $dest[name] in " . $name_result->fields['sector_name'];
$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id=$traderoute[destination_planet_id]", 1);
if ($result3)
	$planetinfo=$result3->fields;
$result3->close();

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

if(!class_exists($shipinfo['fighter_class'])){
	include ("class/" . $shipinfo['fighter_class'] . ".inc");
}

$fighterobject = new $shipinfo['fighter_class']();
$fighter_price = $fighterobject->fighter_price * $fighterobject->price_modifier;

if(!class_exists($shipinfo['torp_class'])){
	include ("class/" . $shipinfo['torp_class'] . ".inc");
}

$torpobject = new $shipinfo['torp_class']();
$torpedo_price = $torpobject->torpedo_price * $torpobject->price_modifier;

$total_energy_dumped = 0;
$total_fighters_dumped = 0;
$total_torps_dumped = 0;
$starting_player_credits = $playerinfo['credits'];
$total_turns_used = 0;
$total_fighters_bought = 0;
$total_torps_bought = 0;
$total_energy_scooped = 0;
$trades_completed = $tr_repeat;

for ($i = 0; $i < $tr_repeat; $i++)
{
	$total_experience += $trading_exp;
	$fighters_buy = 0;
	$torps_buy = 0;
	$energy_buy = 0;

	$sourcecost=0;
//	echo "Source Upgrade Port<br>";

	if ($traderoute['trade_fighters'] == 'Y')
	{
		$free_fighters = NUM_FIGHTERS($shipinfo['fighter']) - $shipinfo['fighters'];
		$fighters_buy = $free_fighters;

		if ($playerinfo['credits'] < $fighters_buy * $fighter_price)
			$fighters_buy = $playerinfo['credits'] / $fighter_price;

		if ($fighters_buy > 0)
		{
//			echo "$l_tdr_bought " . NUMBER($fighters_buy) . " $l_tdr_fighters @ " . number($fighter_price) . "<br>";
		}
		else $fighters_buy = 0;

		$sourcecost-=$fighters_buy * $fighter_price;
		$playerinfo['credits']-=$fighters_buy * $fighter_price;
	}
	else
		$fighters_buy = 0;
	$total_fighters_bought += $fighters_buy;

	if ($traderoute['trade_torps'] == 'Y')
	{
		$free_torps = NUM_TORPEDOES($shipinfo['torp_launchers']) - $shipinfo['torps'];
		$torps_buy = $free_torps;

		if ($playerinfo['credits'] < $torps_buy * $torpedo_price)
			$torps_buy = $playerinfo['credits'] / $torpedo_price;

		if ($torps_buy > 0)
		{
//			echo "$l_tdr_bought " . NUMBER($torps_buy) . " $l_tdr_torps @ " . number($torpedo_price) . "<br>";
		}
		else $torps_buy = 0;

		$sourcecost-=$torps_buy * $torpedo_price;
		$playerinfo['credits']-=$torps_buy * $torpedo_price;
	}
	else
		$torps_buy = 0;

	$total_torps_bought += $torps_buy;
//	if ($torps_buy == 0 && $fighters_buy == 0)
//		echo "$l_tdr_nothingtotrade<br>";

	$shipinfo['fighters'] += $fighters_buy;
	$shipinfo['torps'] += $torps_buy;

	if ($shipdevice['dev_fuelscoop']['amount'] == 1 && $sourceport['sector_id'] != $destport['sector_id']){
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

	//Destination is a planet
//	echo "Destination $traderoute[destination_commodity] planet<br>";
	if ($traderoute['destination_type'] == 'planet'	|| $traderoute['destination_type'] == 'team_planet')
	{
		if ($traderoute['trade_fighters'] == 'Y')
		{
			$fight_dump = $shipinfo['fighters'];
			$shipinfo['fighters'] = 0;
//			echo "$l_tdr_dumped " . NUMBER($fight_dump) . " $l_tdr_fighters<br>";
		}
		else
			$fight_dump = 0;

		$total_fighters_dumped += $fight_dump;

		if ($traderoute['trade_torps'] == 'Y')
		{
			$torps_dump = $shipinfo['torps'];
			$shipinfo['torps'] = 0;
//			echo "$l_tdr_dumped " . NUMBER($torps_dump) . " $l_tdr_torps<br>";
		}
		else
			$torps_dump = 0;

		$total_torps_dumped += $torps_dump;

		if ($traderoute['trade_energy'] == 'Y')
		{
			$energy_dump = $ship_commodity_amount[$ship_commodity_ref['energy']];
			$ship_commodity_amount[$ship_commodity_ref['energy']] = 0;
//			echo "$l_tdr_dumped " . NUMBER($energy_dump) . " Energy<br>";
		}
		else
			$energy_dump = 0;

		$total_energy_dumped += $energy_dump;

//		if ($torps_dump == 0 && $fight_dump == 0 && $energy_dump == 0)
//			echo "$l_tdr_nothingtodump<br>";

		$planetinfo['fighters'] += $fight_dump;
		$planetinfo['torps'] += $torps_dump;
		$planetinfo['energy'] += $energy_dump;

		for ($item = 0; $item < $ship_item_count-1; $item++)
		{
//			echo "$l_tdr_dumped " . NUMBER($ship_commodity_amount[$item]) . " " . $ship_commodity_type[$item] . "<br>";
			$planet_commodity_amount[$ship_commodity_type[$item]] = $ship_commodity_amount[$item];
			$ship_commodity_amount[$item] = 0;
		}

		if ($enable_spies && ($i % 5) == 0)
		{
			//echo "Finish : $traderoute[destination_planet_id], $shipinfo[ship_id], $planet_detect_success1<BR>";
			spy_sneak_to_planet($traderoute['destination_planet_id'], $shipinfo['ship_id']);
			spy_sneak_to_ship($traderoute['destination_planet_id'], $shipinfo['ship_id']);
			spy_detect_planet($shipinfo['ship_id'], $traderoute['destination_planet_id'], $planet_detect_success1);
		}
	}

//	echo"<br>";
//	echo "Trade Route One-Way<br>";
//	echo "Credits = " . number($playerinfo['credits']) . "<br>";
//	echo "Ship Fighters = " . number($shipinfo['fighters']) . "<br>";
//	echo "Ship Torps = " . number($shipinfo['torps']) . "<br>";
//	foreach($ship_commodity_type as $key=>$value){ 
//			echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//	}
//	echo"<br>";

//	echo "Planet Energy = " . number($planetinfo['energy']) . "<br>";
//	echo "Planet Fighters = " . number($planetinfo['fighters']) . "<br>";
//	echo "Planet Torps = " . number($planetinfo['torps']) . "<br>";
//	foreach($planet_commodity_amount as $key=>$value){ 
//		echo "$key: " . number($value) . "<br>";
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

//		echo "Ship Fighters = " . number($shipinfo['fighters']) . "<br>";
//		echo "Ship Torps = " . number($shipinfo['torps']) . "<br>";
//		foreach($ship_commodity_type as $key=>$value){ 
//				echo "$value: " . number($ship_commodity_amount[$key]) . "<br>";
//		}
//		echo"<br>";

//		echo "Planet Energy = " . number($planetinfo['energy']) . "<br>";
//		echo "Planet Fighters = " . number($planetinfo['fighters']) . "<br>";
//		echo "Planet Torps = " . number($planetinfo['torps']) . "<br>";
//		foreach($planet_commodity_amount as $key=>$value){ 
//			echo "$key: " . number($value) . "<br>";
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

$ship_commodity_amount[$ship_commodity_ref['energy']] = min($ship_commodity_amount[$ship_commodity_ref['energy']], NUM_ENERGY($shipinfo['power']));
//echo "UPDATE {$db_prefix}planets SET fighters=$planetinfo[fighters], torps=$planetinfo[torps], energy=$planetinfo[energy] WHERE planet_id=$traderoute[destination_planet_id]<br><br>";
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=$planetinfo[fighters], torps=$planetinfo[torps], energy=$planetinfo[energy] WHERE planet_id=$traderoute[destination_planet_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
//echo "UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], fighters=$shipinfo[fighters], torps=$shipinfo[torps], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]<br><br>";
	$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id], fighters=$shipinfo[fighters], torps=$shipinfo[torps], energy=" . $ship_commodity_amount[$ship_commodity_ref['energy']] . " WHERE ship_id=$shipinfo[ship_id]");
	db_op_result($debug_query,__LINE__,__FILE__);
//echo "UPDATE {$db_prefix}players SET credits=" . floor($playerinfo['credits']) . ", turns=$playerinfo[turns], turns_used=$playerinfo[turns_used] WHERE player_id=$playerinfo[player_id]<br><br>";
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=" . floor($playerinfo['credits']) . ", turns=$playerinfo[turns], turns_used=$playerinfo[turns_used] WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

$template_object->assign("total_fighters_dumped",  NUMBER($total_fighters_dumped));
$template_object->assign("total_torps_dumped",  NUMBER($total_torps_dumped));
$template_object->assign("total_energy_dumped", NUMBER($total_energy_dumped));
$template_object->assign("total_energy_scooped", NUMBER($total_energy_scooped));

$template_object->assign("total_fighters_bought", NUMBER($total_fighters_bought));
$template_object->assign("fighter_price", NUMBER($fighter_price));
$template_object->assign("total_torps_bought", NUMBER($total_torps_bought));
$template_object->assign("torpedo_price", NUMBER($torpedo_price));

$template_object->assign("l_tdr_dumped", $l_tdr_dumped);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_torps", $l_torps);
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

$l_tdr_engageagain = str_replace("[tdr_engage]", $engage, $l_tdr_engageagain);
$template_object->assign("l_tdr_engageagain", $l_tdr_engageagain);
$template_object->assign("engage", $engage);
$template_object->assign("l_tdr_timestorep", $l_tdr_timestorep);
$template_object->assign("l_submit", $l_submit);

$template_object->assign("l_tdr_tdrres", $l_tdr_tdrres);
$template_object->send_now = 0;
$template_object->display($templatename."traderoute_upgrade2planet.tpl");
?>
