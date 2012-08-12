<?php
include ("globals/cleanjs.inc");

cleanjs('');
$template_object->assign("cleanjs", $cleanjs);

$l_port_welcome = str_replace("[player]", $playerinfo['character_name'], str_replace("[sectorname]", $sectorinfo['sector_name'], $l_port_welcome));
$template_object->assign("l_port_welcome", $l_port_welcome);
$template_object->assign("cleanjs", $cleanjs);
$template_object->assign("l_port_cargoholds", $l_port_cargoholds);
$template_object->assign("l_port_perform", $l_port_perform);

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
$ship_commodity_class[$ship_item_count] = "commodity";
$ship_commodity_type[$ship_item_count] = "energy";
$ship_commodity_amount[$ship_item_count] = $shipinfo['energy'];
$ship_commodity_holds[$ship_item_count] = 0;
$ship_commodity_ref[$ship_commodity_type[$ship_item_count]] = $ship_item_count;
$ship_item_count++;

$sellcommodity = array();
$holdsperunitsell = array();
$howmanysell = array();
$amountportbuy = array();
$sellinputname = array();

$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$credits_made = 0;
$amount_buy_tot=0;
while(!$debug_query->EOF){
	$data_id = $debug_query->fields['data_id'];
	$commodity_type = $debug_query->fields['commodity_type'];
	$commodity_amount = $debug_query->fields['commodity_amount'];
	$commodity_price = $debug_query->fields['commodity_price'];
	$goodevil = $debug_query->fields['goodevil'];

	$commodity_query = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities WHERE classname='$commodity_type'");
	db_op_result($commodity_query,__LINE__,__FILE__);

	$delta = $commodity_query->fields['delta'];
	$limit = $commodity_query->fields['itemlimit'];
	$price = $commodity_query->fields['price'];
	$hold_space = $commodity_query->fields['hold_space'];

	if($sectorinfo['port_type'] == AAT_strtolower($commodity_type))
	{
		$offered_sell_price = max($commodity_price - $commodity_query->fields['delta'] * $debug_query->fields['commodity_amount'] / $commodity_query->fields['itemlimit'] * $inventory_factor, 0.01);
		if($commodity_type != "energy")
		{
			$amount_player_buy = floor((NUM_HOLDS($shipinfo['hull']) - $ship_holds_used) / $ship_commodity_holds[$ship_commodity_ref[$sectorinfo['port_type']]]);
		}
		else
		{
			$amount_player_buy = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];
		}
		$amount_player_buy = min($amount_player_buy, floor(($playerinfo['credits'] + $credits_made) / $offered_sell_price));
		if($amount_player_buy > $commodity_amount)
		{
			$amount_player_buy = $commodity_amount;
		}
		$amount_port_sell = $commodity_amount;
	}
	else
	{
		$offered_buy_price = max($commodity_price + $commodity_query->fields['price'] + $commodity_query->fields['delta'] * $commodity_query->fields['itemlimit'] / $commodity_query->fields['itemlimit'] * $inventory_factor, 0.01);

		if($offered_buy_price <= 0)
			$offered_buy_price = 0.01;

		$ship_commodity_number = $ship_commodity_ref[$commodity_type];
		$amount_port_buy = (isset($ship_commodity_amount[$ship_commodity_number])) ? $ship_commodity_amount[$ship_commodity_number] : 0;
		$amount_port_buy = floor(min($amount_port_buy, $commodity_amount));
		$credits_made += ($amount_port_buy * $offered_buy_price);

		$howmanysellwork = str_replace("[amount]", NUMBER($commodity_amount), $l_port_howmanysell);
		$howmanysellwork = str_replace("[credits]", NUMBER($offered_buy_price), $howmanysellwork);
		$howmanysell[] = str_replace("[commodity]", ucwords($commodity_type), $howmanysellwork);
		$sellcommodity[] = $commodity_type;
		$holdsperunitsell[] = str_replace("[holds]", NUMBER($hold_space), $l_port_holdsperunit);
		$amountportbuy[] = $amount_port_buy;
		$sellinputname[] = "trade_" . str_replace(" ", "_", $commodity_type);
	}
	$commodity_query->close();
	
	if($commodity_type != "energy")
	{
		$amount_buy_tot+=$amount_port_buy;
	}
	$debug_query->MoveNext();
}
$debug_query->close();

$template_object->assign("sellcommodity", $sellcommodity);
$template_object->assign("holdsperunitsell", $holdsperunitsell);
$template_object->assign("howmanysell", $howmanysell);
$template_object->assign("l_port_unitstosell", $l_port_unitstosell);
$template_object->assign("amountportbuy", $amountportbuy);
$template_object->assign("sellinputname", $sellinputname);

$free_holds = NUM_HOLDS($shipinfo['hull']) - $ship_holds_used;
//echo "Holds used: $ship_holds_used<br>";
//if ($amount_buy_tot==0 || $amount_buy_tot==""){
//	$amount_buy_tot=$free_holds;
//}

//if($sectorinfo['port_type'] != "energy")
//{
//	$amount_player_buy += $amount_buy_tot;
//}

$ship_commodity_number = $ship_commodity_ref[$sectorinfo['port_type']];

$template_object->assign("buycommodity", $sectorinfo['port_type']);
$l_port_amountforsale = str_replace("[amount]", NUMBER($commodity_amount), $l_port_amountforsale);
$l_port_amountforsale = str_replace("[credits]", NUMBER($offered_sell_price), $l_port_amountforsale);
$l_port_amountforsale = str_replace("[commodity]", ucwords($sectorinfo['port_type']), $l_port_amountforsale);
$template_object->assign("l_port_amountforsale", $l_port_amountforsale);
$template_object->assign("amount_player_buy", $amount_player_buy);
$template_object->assign("buyinputname", "trade_" . str_replace(" ", "_", $sectorinfo['port_type']));
$template_object->assign("l_port_holdsperunit", str_replace("[holds]", NUMBER($ship_commodity_holds[$ship_commodity_number]), $l_port_holdsperunit));
$template_object->assign("l_port_howmanypurchase", str_replace("[commodity]", ucwords($sectorinfo['port_type']), $l_port_howmanypurchase));
$template_object->assign("l_port_unitstobuy", $l_port_unitstobuy);

$l_port_shipcarryingbuy = str_replace("[shipunits]", NUMBER($ship_commodity_amount[$ship_commodity_number]), $l_port_shipcarryingbuy);
$l_port_shipcarryingbuy = str_replace("[buyunits]", NUMBER($amount_player_buy), $l_port_shipcarryingbuy);
$l_port_shipcarryingbuy = str_replace("[commodity]", ucwords($sectorinfo['port_type']), $l_port_shipcarryingbuy);
$template_object->assign("l_port_shipcarryingbuy", $l_port_shipcarryingbuy);

$free_power = NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'];

$l_trade_st_info=str_replace("[free_holds]",NUMBER($free_holds),$l_trade_st_info);
$l_trade_st_info=str_replace("[free_power]",NUMBER($free_power),$l_trade_st_info);
$l_trade_st_info=str_replace("[credits]",NUMBER($playerinfo['credits']),$l_trade_st_info);

$template_object->assign("l_trade_st_info", $l_trade_st_info);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ports/commodity_view.tpl");

include ("footer.php");

?>
