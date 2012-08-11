<?php
// 1
// 600
// 10
// 0
// Y
// How often ports will generate new prices based upon how often they are being traded..


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

TextFlush ( "<b>PORT TRADE PRICES</b><br>\n");

TextFlush ( "\nAdding price increases to all ports...<br>");

//echo "<br>Current Stamp: ".strtotime(date("Y-m-d H:i:s"));
$stamp = strtotime(date("Y-m-d H:i:s")) - $notradeperiod;
//echo "<br>Stamp: $stamp";
$trade_date = date("Y-m-d H:i:s", $stamp);
TextFlush ( "<br>Date range to prevent port price upgrades<br> Start: $trade_date<br> End:   ".date("Y-m-d H:i:s")."<br><br>");

$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET commodity_price = 0 WHERE commodity_price < 0");
db_op_result($debug_query,__LINE__,__FILE__);

$cargo_query = $db->Execute("SELECT classname, increaserate, price from {$db_prefix}class_modules_commodities where cargoport=1");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['classname'];
	$increaserate = $cargo_query->fields['increaserate'];

	if($increaserate != 0)
	{
		TextFlush ( "\nUpdating " . $cargotype . " Buy Port Prices...<br>");
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports, {$db_prefix}universe SET 
							{$db_prefix}universe_ports.commodity_price={$db_prefix}universe_ports.commodity_price+((RAND()*$increaserate * $multiplier) * $port_price_control)
							WHERE {$db_prefix}universe.port_type != {$db_prefix}universe_ports.commodity_type
							AND {$db_prefix}universe.sector_id = {$db_prefix}universe_ports.sector_id
							AND {$db_prefix}universe_ports.commodity_type = '" . $cargotype . "' AND " .
							"{$db_prefix}universe_ports.trade_date <= '$trade_date'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
		TextFlush ( "\nUpdating " . $cargotype . " Sell Port Prices...<br>");
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports, {$db_prefix}universe SET 
							{$db_prefix}universe_ports.commodity_price={$db_prefix}universe_ports.commodity_price+((RAND() * ($increaserate * 0.7) * $multiplier) * $port_price_control)
							WHERE {$db_prefix}universe.port_type = {$db_prefix}universe_ports.commodity_type
							AND {$db_prefix}universe.sector_id = {$db_prefix}universe_ports.sector_id
							AND {$db_prefix}universe_ports.commodity_type = '" . $cargotype . "'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
	$cargo_query->Movenext();
}
$cargo_query->close();

TextFlush ( "<br>\n");
$multiplier = 0; //no use to run this again

?>
