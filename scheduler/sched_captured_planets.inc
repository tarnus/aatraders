<?php
// 1
// 301
// 5
// 0
// Y
// Reduce capture countdown and move hidden credits to main credits on captured planets.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

if($adminexecuted == 1){
	TextFlush ("<b>Capture Planets Countdown</b><br><br>");
}

$debug_query = $db->Execute("SELECT planet_id, name, captured_countdown, hidden_credits FROM {$db_prefix}planets WHERE planet_id NOT IN ($starvation_list) and captured_countdown > 0 and base = 'Y' and owner != 0");
db_op_result($debug_query,__LINE__,__FILE__);

if ($debug_query)
{
	$num_planets = $debug_query->RecordCount();
	$count = 0;
	TextFlush ( "$num_planets planets to find credits:<br>");
	while (!$debug_query->EOF)
	{
		$row = $debug_query->fields;

		if($row['hidden_credits'] == 0)
		{
			$update_query = $db->Execute("UPDATE {$db_prefix}planets SET captured_countdown = 0 WHERE planet_id=$row[planet_id]");
			db_op_result($update_query,__LINE__,__FILE__);
			$debug_query->MoveNext();
		}
		else
		{
			$dignitaries = $db->Execute("SELECT COUNT(dig_id) as total FROM {$db_prefix}dignitary WHERE active='Y' AND ship_id = '0' AND planet_id = $row[planet_id]");
			db_op_result($dignitaries,__LINE__,__FILE__);
			$num_digs = $dignitaries->RecordCount();
			$spies = $db->Execute("SELECT COUNT(spy_id) as total FROM {$db_prefix}spies WHERE active='Y' AND ship_id = '0' AND planet_id = $row[planet_id]");
			db_op_result($spies,__LINE__,__FILE__);
			$num_spies = $spies->RecordCount();

			$countdownamount = 1;
			if ($row['captured_countdown'] == 1)
			{
				$credits = $row['hidden_credits'];
			}
			else
			{
				$percentage_found = (($capture_countdown_max - $row['captured_countdown']) + $num_spies + $num_digs) * $capture_find_percentage;
				$credits = floor(($row['hidden_credits'] / 2) * $percentage_found);
				$credits = floor($credits * (rand(50, 100) * 0.01));
				if ($credits == 0)
				{
						$credits = $row['hidden_credits'];
						$countdownamount = $row['captured_countdown'];
				}
			}

			if($adminexecuted == 1){
				TextFlush ( "Planet $row[name] with $num_digs dignitaries and $num_spies spies found " . NUMBER($credits) . " credits. $row[captured_countdown] ticks until all credits found.<br>");
			}
			$update_query = $db->Execute("UPDATE {$db_prefix}planets SET credits = credits + $credits, captured_countdown = captured_countdown - $countdownamount, hidden_credits = hidden_credits - $credits WHERE planet_id=$row[planet_id]");
			db_op_result($update_query,__LINE__,__FILE__);
			$debug_query->MoveNext();
		}
	}
	$debug_query->close();
}

$planetupdate = "UPDATE {$db_prefix}planets SET persuasion_countdown=GREATEST(0, persuasion_countdown-1) WHERE planet_id NOT IN ($starvation_list) and persuasion_countdown > 0 and base = 'Y'";
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);

$planetupdate = "UPDATE {$db_prefix}planets SET last_owner_rating=0 WHERE planet_id NOT IN ($starvation_list) and last_owner_rating != 0 and persuasion_countdown = 0 and base = 'Y'";
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);

if($adminexecuted == 1){
	TextFlush (  "<br><br>");
}

$multiplier = 0;
?>
