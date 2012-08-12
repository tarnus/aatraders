<?php
// 1
// 70
// 5
// 0
// Y
// How Often Turns will be added to all players.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule


$turns_results1 = '';
$turns_results2 = '';

$unixstamp = time();
$stamp = date("Y-m-d H:i:s", ($unixstamp - 360));

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET sessionid='', last_login='$stamp', logged_out='Y', profile_cached='Y' WHERE ($unixstamp - UNIX_TIMESTAMP(last_login)) / 60 > $idle_max and email NOT LIKE '%@npc' and logged_out != 'Y'");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=LEAST(turns+$turn_rate, $max_turns), team_cash_countdown=GREATEST(0, team_cash_countdown - 1)");
db_op_result($debug_query,__LINE__,__FILE__);

while (!$debug_query->EOF && $debug_query !='')
{
	$turns_results1 = $debug_query;
}

if($adminexecuted == 1){
	TextFlush ( "<b>TURNS</b><br><br>");

	if ($turns_results1 != '')
	{
		TextFlush ( "Errors encountered: $turns_results1");
	}else{
		TextFlush ( "Completed successfully!");
	}
	TextFlush (  "<br><br>");
}

$multiplier = 0;

?>
