<?php
// 1
// 80
// 5
// 0
// Y
// How Often tournament mode will be checked and player timelimits updated..


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/end_of_game.inc");

$turns_results1 = '';
$turns_results2 = '';

function exportvariables(){
	global $gameroot;
	global $db, $db_prefix, $game_number;
	$filename = $gameroot . "support/variables" . $game_number . ".inc";
	$file = fopen($filename,"w") or die ("Failed opening file: enable write permissions for '$filename'");
	echo "<b>Saving $filename</b><br><br>";
	
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}config_values");
	db_op_result($debug_query,__LINE__,__FILE__);

	fwrite($file,"<?\n"); 
	while (!$debug_query->EOF && $debug_query)
	{
		$row = $debug_query->fields;
		$db_config_name = $row['name'];
		$db_config_value = $row['value'];
//		echo "Writing data: " . $db_config_name . "=\"" . $db_config_value . "\";<br>"; 
		fwrite($file,"$" . $db_config_name . "=\"" . $db_config_value . "\";\n"); 
		$debug_query->MoveNext();
	}
	fwrite($file,"?>\n"); 
	fclose($file);
	$debug_query->close();
	echo "Success.";
}

TextFlush ( "<b>Tournament, Game Reset and Player Time Limit Reset Check</b><br><br>");

$date = date("Y-m-d");

if($tournament_start_date != "0000-00-00")
{
	if($date == $tournament_start_date)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=0 WHERE name='tournament_setup_access'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=1 WHERE name='account_creation_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0000-00-00 00:00:00' WHERE name='tournament_start_date'");
		db_op_result($debug_query,__LINE__,__FILE__);
		exportvariables();
	}
}

if($scheduled_reset != "0000-00-00")
{
	if($date == $scheduled_reset)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=0 WHERE name='enable_scheduler'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=1 WHERE name='server_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=1 WHERE name='account_creation_closed'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0000-00-00 00:00:00' WHERE name='scheduled_reset'");
		db_op_result($debug_query,__LINE__,__FILE__);
		exportvariables();
		end_of_game();
	}
}

if(date("H") == "00" and (intval(date("i")) >= 0 and intval(date("i")) < 20))
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET player_online_time=0");
	db_op_result($debug_query,__LINE__,__FILE__);
}

TextFlush ( "Completed successfully!");
TextFlush (  "<br><br>");

$multiplier = 0;

?>
