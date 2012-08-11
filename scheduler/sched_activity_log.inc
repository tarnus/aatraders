<?php
// 1
// 90
// 5
// 0
// Y
// Player Count Logging

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

if($player_online_timelimit > 0 && isset($playerinfo['player_online_time']))
{
	$overlimitwhere = " and floor($playerinfo[player_online_time] / 60) <= $player_online_timelimit";
}
else
{
	$overlimitwhere = "";
}

$debug_query = $db->Execute("SELECT COUNT(player_id) AS total from {$db_prefix}players WHERE TIMESTAMPDIFF(MINUTE,last_login,'". date("Y-m-d H:i:s") . "') < 5 and email NOT LIKE '%@npc' and player_id > 3 $overlimitwhere");
db_op_result($debug_query,__LINE__,__FILE__);
$player_count = $debug_query->fields['total'];
$debug_query->close();

$debug_query = $db->Execute("INSERT INTO {$db_prefix}site_activity_log (player_count, time, year, month, day, hour, minute) 
							VALUES
							('$player_count', '$stamp', '$year', '$month', '$day', '$hour', '$minute')");
db_op_result($debug_query,__LINE__,__FILE__);

if($adminexecuted == 1){
	TextFlush ( "<b>Player Activity Count Updated: $player_count player(s)</b><br><br>");
}

$multiplier = 0;

?>
