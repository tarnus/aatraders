<?php
// 1
// 8900
// 5
// 0
// Y
// Building researched items on each planet

// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minutes between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

$stamp = date("Y-m-d H:i:s");
$year = date("Y");
$month = date("n");
$day = date("j");
$hour = date("G");
$minute = floor((int)date("i") / 5) * 5;

$unixstamp = time();

//$debug_query = $db->Execute("SELECT COUNT(player_id) AS total from {$db_prefix}players WHERE ($unixstamp - UNIX_TIMESTAMP({$db_prefix}players.last_login)) / 60 < 5 and email NOT LIKE '%@npc'");
//db_op_result($debug_query,__LINE__,__FILE__);
//$player_count = $debug_query->fields['total'];
//$debug_query->close();

if($adminexecuted == 1){
	TextFlush ( "<b>Planet Item Build Count Updated: $planet_count planet(s)</b><br><br>");
}

$multiplier = 0;

?>
