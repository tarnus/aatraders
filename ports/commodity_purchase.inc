<?php
$l_port_welcome = str_replace("[player]", $playerinfo['character_name'], str_replace("[sectorname]", $sectorinfo['sector_name'], $l_port_welcome));
$template_object->assign("l_port_welcome", $l_port_welcome);

$average_stats = (($shipinfo['hull_normal'] + $shipinfo['cloak_normal'] + $shipinfo['sensors_normal'] + $shipinfo['power_normal'] + $shipinfo['engines_normal'] + $shipinfo['fighter_normal'] + $shipinfo['armor_normal'] + $shipinfo['shields_normal'] + $shipinfo['beams_normal'] + $shipinfo['torp_launchers_normal'] + $shipinfo['ecm_normal'] ) / 11 );
if ($zoneinfo['zone_id'] == 2 && $zoneinfo['max_hull'] < $average_stats && $playerinfo['player_id'] > 3)
{
	$template_object->assign("error_msg", $l_port_shiptoolarge);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_trade_turnneed);
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ship_holds WHERE cargo_name!='energy' and ship_id=$playerinfo[currentship]");
db_op_result($debug_query,__LINE__,__FILE__);

$ship_item_count = 0;
$ship_holds_used = 0;

while(!$debug_query->EOF)
{
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

$trade_date = date("Y-m-d H:i:s");

$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id] ORDER BY data_id DESC");
db_op_result($debug_query,__LINE__,__FILE__);

$total_cost = 0;
$total_sale = 0;
$failed = 0;
$update_ship_query = array();
$update_universe_query = array();
$commodity_name = array();
$commodity_value = array();
$commodity_total = array();
$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
// echo $sectorinfo['sector_id'] . " - " . $debug_query->RecordCount() . " - Free: $free_holds<br>";
while(!$debug_query->EOF)
{
	$data_id = $debug_query->fields['data_id'];
	$commodity_type = $debug_query->fields['commodity_type'];
	$commodity_amount = $debug_query->fields['commodity_amount'];
	$commodity_price = $debug_query->fields['commodity_price'];

	$variable = "trade_" . str_replace(" ", "_", $commodity_type);

	get_post_ifset($variable);
// echo $variable . " - " . $$variable . " - " . $variable . "<br>";

	$cargo_amount = round(abs($$variable));

	$commodity_query = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities WHERE classname='" . $commodity_type . "'");
	db_op_result($commodity_query,__LINE__,__FILE__);

	if($commodity_type != AAT_strtolower($sectorinfo['port_type']))
	{
		$item_price = max($commodity_price + $commodity_query->fields['price'] + $commodity_query->fields['delta'] * $commodity_query->fields['itemlimit'] / $commodity_query->fields['itemlimit'] * $inventory_factor, 0.01);
		if($commodity_type != "energy")
		{
			$free_holds += ($cargo_amount * $commodity_query->fields['hold_space']);
		}
		$total_sale += floor($item_price) * $cargo_amount;
		$reduce_rate = ($commodity_price > $commodity_query->fields['price']) ? ($commodity_query->fields['reducerate'] * ($commodity_price / $commodity_query->fields['price'])) : $commodity_query->fields['reducerate'];
		$reduce_rate = $commodity_query->fields['reducerate'];
		$newcommodity_price = $commodity_price - ($reduce_rate * $cargo_amount);
		$cargo_amount = 0-$cargo_amount;
		$$variable = $cargo_amount;
		$commodity_boughtsold[] = $l_sold;
//		echo "Sell to port ";
	}
	else
	{
		$item_price = max($commodity_price - $commodity_query->fields['delta'] * $commodity_amount / $commodity_query->fields['itemlimit'] * $inventory_factor, 0.01);
		if($commodity_type != "energy")
		{
			$free_holds -= ($cargo_amount * $commodity_query->fields['hold_space']);
		}
		$goodevil = $debug_query->fields['goodevil'];
		$total_cost += floor($item_price) * $cargo_amount;
		$portlimit = $commodity_query->fields['itemlimit'];
		$newcommodity_price = $commodity_price;
		$commodity_boughtsold[] = $l_bought;
//		echo "Buy from port ";
	}
	$commodity_query->close();

	$commodity_name[] = ucwords($commodity_type);
	$commodity_value[] = floor($item_price);
	$commodity_total[] = $cargo_amount;

//	echo $commodity_type . " - Free: $free_holds - Cargo Amount: $cargo_amount - Port Amount: $commodity_amount<br><br>";

	if($commodity_type != "energy")
	{
		if ($cargo_amount < 0)
		{
			if (abs($ship_commodity_amount[$ship_commodity_ref[$commodity_type]]) < abs($cargo_amount))
			{
				$template_object->assign("error_msg", str_replace("[commodity]", ucwords($commodity_type), $l_notenough_commodity));
				$template_object->assign("error_msg2", "");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}
		}
		else
		{
			if (abs($cargo_amount) > $commodity_amount)
			{
				$template_object->assign("error_msg", str_replace("[commodity]", ucwords($commodity_type), $l_exceed_commodity));
				$template_object->assign("error_msg2", "");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}
		}
	}

	$itemnumber = $ship_commodity_ref[$commodity_type];
	if($commodity_type != "energy")
	{
		$update_ship_query[] = "UPDATE {$db_prefix}ship_holds SET amount=GREATEST(amount+$cargo_amount, 0) WHERE hold_id=" . $ship_commodity_id[$itemnumber];
	}
	else
	{
		$update_ship_query[] = "UPDATE {$db_prefix}ships SET energy=GREATEST(energy+$cargo_amount, 0) WHERE ship_id=" . $playerinfo[currentship];
		$port_energy = $commodity_amount;
	}

	$update_universe_query[] = "UPDATE {$db_prefix}universe_ports SET trade_date='$trade_date', commodity_price=$newcommodity_price, commodity_amount=greatest((commodity_amount-abs($cargo_amount)), 0) WHERE data_id=" . $data_id;

	$debug_query->MoveNext();
}
$debug_query->close();

array_pop($commodity_name);
array_pop($commodity_value);
array_pop($commodity_total);
$template_object->assign("buycommodity", $commodity_type);
$template_object->assign("youbought", $l_bought . " " . ucwords($commodity_type));
$template_object->assign("buyprice", NUMBER(floor($item_price)));
$template_object->assign("buyamount", NUMBER($cargo_amount));
$template_object->assign("buycost", NUMBER(-($cargo_amount * floor($item_price))));

$free_power = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];

// echo "Free: $free_holds<br><br>";
if ($free_holds < 0)
{
	$template_object->assign("error_msg", "$l_notenough_cargo	$l_returnto_port");
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}
elseif ($trade_energy > $free_power)
{
	$template_object->assign("error_msg", "$l_notenough_power	$l_returnto_port");
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}
elseif ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", "$l_notenough_turns");
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}
elseif ($playerinfo['credits'] + $total_sale < $total_cost)
{
	$template_object->assign("error_msg", "$l_notenough_credits");
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}
elseif ($trade_energy < 0 && abs($shipinfo['energy']) < abs($trade_energy))
{
	$template_object->assign("error_msg", "$l_notenough_energy");
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}
elseif (abs($trade_energy) > $port_energy)
{
	$template_object->assign("error_msg", str_replace("[commodity]", ucwords($l_energy), $l_exceed_commodity));
	$template_object->assign("error_msg2", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

if ($total_cost == 0 )
{
	$trade_color	 = "DarkGreen";
	$trade_result	= $trade_benefit;
}
elseif (($total_sale - $total_cost) >= 0 )
{
	$trade_color	 = "DarkGreen";
	$trade_result	= $trade_benefit;
}
else
{
	$trade_color	 = "red";
	$trade_result	= $trade_deficit;
}

$sellcost = array();
foreach($commodity_name as $key => $value)
{
	$sellcost[$key] = NUMBER(floor(-($commodity_total[$key] * $commodity_value[$key])));
	$commodity_total[$key] = NUMBER(floor(abs($commodity_total[$key])));
	$commodity_value[$key] = NUMBER(floor($commodity_value[$key]));
}
$template_object->assign("commodity_boughtsold", $commodity_boughtsold);
$template_object->assign("commodity_name", $commodity_name);
$template_object->assign("commodity_total", $commodity_total);
$template_object->assign("commodity_value", $commodity_value);
$template_object->assign("sellcost", $sellcost);
$template_object->assign("l_trade_result", $l_trade_result);

$template_object->assign("trade_color", $trade_color);
$template_object->assign("trade_result", $trade_result);
$template_object->assign("trade_result_total", NUMBER($total_sale - $total_cost));
$template_object->assign("l_credits", $l_credits);

/* Update ship cargo, credits and turns */
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1, rating=rating+$goodevil, credits=credits+($total_sale-$total_cost) WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);
//$db->debug=1;
for($i = 0; $i < count($update_ship_query); $i++)
{
	$db->Execute($update_ship_query[$i]);
}

/* Decrease supply and demand on port */
for($i = 0; $i < count($update_universe_query); $i++)
{
	$db->Execute($update_universe_query[$i]);
}

$template_object->assign("l_trade_result", $l_trade_result);
$template_object->assign("l_trade_complete", $l_trade_complete);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ports/commodity_purchase.tpl");

include ("footer.php");
?>
