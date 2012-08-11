<?php
// 1
// 1
// 10080
// 0
// Y
// How often to optimize highly updated tables.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

if($db_type == "mysql" and $db_mysql_type == "default"){

	TextFlush ("<b>Starting Database Optimization</b><br><br>");

	$debug_query = $db->Execute("OPTIMIZE TABLE {$db_prefix}zones, {$db_prefix}teams, {$db_prefix}spies, {$db_prefix}ship_holds, {$db_prefix}ship_devices, {$db_prefix}ships, {$db_prefix}sector_notes, {$db_prefix}sector_log, {$db_prefix}sector_defense, {$db_prefix}probe, {$db_prefix}players, {$db_prefix}planet_log, {$db_prefix}news, {$db_prefix}logs, {$db_prefix}dignitary, {$db_prefix}detect, {$db_prefix}admin_extended_logging");
	db_op_result($debug_query,__LINE__,__FILE__);
	TextFlush ("<b>Optimized Tables: {$db_prefix}zones, {$db_prefix}teams, {$db_prefix}spies, {$db_prefix}ship_holds, {$db_prefix}ship_devices, {$db_prefix}ships, {$db_prefix}sector_notes, {$db_prefix}sector_log, {$db_prefix}sector_defense, {$db_prefix}probe, {$db_prefix}players, {$db_prefix}planet_log, {$db_prefix}news, {$db_prefix}logs, {$db_prefix}dignitary, {$db_prefix}detect, {$db_prefix}admin_extended_logging</b> - <b>OK</b><br><br>");
}

$multiplier = 0;
?>

