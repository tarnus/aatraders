<?php
// 1
// 500
// 2
// 0
// Y
// How often ports will generate more supplies for trading.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

TextFlush ( "<B>PORT RESTOCKING</B><BR>");
TextFlush ( "\nAdding commodities to all ports...<br>");

$cargo_query = $db->Execute("SELECT classname, itemlimit, rate from {$db_prefix}class_modules_commodities where cargoport=1");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['classname'];
	$limit = $cargo_query->fields['itemlimit'];
	$rate = $cargo_query->fields['rate'];

	TextFlush ( "\nUpdating " . $cargotype . " commodity amounts at all ports...<br>");
	$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET 
						commodity_amount=GREATEST(LEAST(commodity_amount + ($rate * $multiplier), $limit), 0)
						WHERE commodity_type = '" . $cargotype . "'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$cargo_query->Movenext();
}
$cargo_query->close();

$multiplier = 0;
TextFlush ( "<BR>\n");
?>
