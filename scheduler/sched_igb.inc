<?php
// 1
// 100
// 1440
// 0
// Y
// How often igb interests are added.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

$igb_results = '';

$exponinter = mypw($ibank_interest + 1, $multiplier);
$expoloan = mypw($ibank_loaninterest + 1, $multiplier);

$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET balance=IF($max_igb_storage = 0, balance * $exponinter, LEAST(balance * $exponinter, $max_igb_storage)), loan=loan * $expoloan");
db_op_result($debug_query,__LINE__,__FILE__);

while (!$debug_query->EOF && $debug_query !='')
{
	$igb_results = $debug_query;
}

if($adminexecuted == 1){
	TextFlush ( "<b>IGB</b><br><br>");

	if ($igb_results != '')
	{
		TextFlush (  "Errors encountered: $igb_results");
	}else{
		TextFlush (  "All IGB accounts updated $multiplier times successfully!");
	}
	TextFlush (  "<br><br>");
}
$multiplier = 0;

?>
