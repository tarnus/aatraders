<?php
// 1
// 400
// 2
// 0
// Y
// How often the spies on planets will check to pick a job.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/change_planet_ownership.inc");
include ("globals/calc_ownership.inc");
include ("globals/myrand.inc");
include ("globals/capture_planet_ships.inc");
include ("globals/good_neutral_evil.inc");

TextFlush ( "<b>SPIES</b><br>\n");

if ($enable_spies)
{

	$kill = 4000;
	$kill_trigger = (int) (50 / $spy_kill_factor);

	$lower = -$kill + 100 / $spy_kill_factor;
	$i = 0;

	$spy_object = array();
	$filelist = get_dirlist($gameroot."class/spies/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$spy_classname =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($spy_classname)){
				include ("class/spies/" . $spy_classname . ".inc");
			}

			$store_object = new $spy_classname();
			$job_type = $store_object->id;
			$spy_object[$job_type] = $store_object;

			if($spy_object[$job_type]->singlepass == 1)
			{
				$spy_object[$job_type]->sched_process_spy();
			}
		}
	}

	// Getting all possibly needed information about the spy, the planet, the spy owner and his ship
	$spies = $db->Execute("SELECT {$db_prefix}planets.*, {$db_prefix}spies.*, {$db_prefix}players.character_name FROM {$db_prefix}planets INNER JOIN {$db_prefix}spies ON {$db_prefix}planets.planet_id = {$db_prefix}spies.planet_id INNER JOIN {$db_prefix}players ON {$db_prefix}spies.owner_id = {$db_prefix}players.player_id WHERE {$db_prefix}spies.planet_id != '0' AND {$db_prefix}spies.active='Y' AND {$db_prefix}spies.ship_id = '0' ");

	$num_spies = $spies->RecordCount();
	TextFlush ("Processing " . $num_spies . " spies.<br>");

	while (!$spies->EOF)
	{
		$spy = $spies->fields;
		$flag = 1;

		if (!$spy['name'])
		{
			$spy['name'] = $l_unnamed;
		}

		$multiplier_count = $multiplier;

		while($multiplier_count > 0)
		{
			if($spy_object[$spy['job_id']]->singlepass != 1)
			{
				$spy_object[$spy['job_id']]->sched_process_spy();
			}

			$base_factor = ($spy['base'] == 'Y') ? $basedefense : 0;
			$spy['sensors'] += $base_factor;

			$kill2 = ($spy['spy_cloak'] - $spy['sensors']) * $kill * 0.1;
			if ($kill2 > $kill)
			{
				$kill2 = $kill;
			}

			if ($kill2 < $lower)
			{
				$kill2 = $lower;
			}

			$kill2 = floor($kill2 + $kill) + 1;
			$success = mt_rand(0, $kill2);
			//echo "$spy[spy_cloak] -- $spy[sensors] -- $kill -- $kill2 -- $success -- $kill_trigger<BR>";
			if ($success == $kill_trigger && $flag)
			{
				TextFlush("Killed Spy: $spy[name] ($spy[character_name])<br>");
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE spy_id=$spy[spy_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				playerlog($spy['owner_id'], "LOG2_SPY_KILLED_SPYOWNER", "$spy[spy_id]|$spy[name]|$spy[sector_id]");
				playerlog($spy['owner'], "LOG2_SPY_KILLED", "$spy[name]|$spy[sector_id]|$spy[character_name]");
				$flag = 0;
			}
			$multiplier_count--;
		}
		$spies->MoveNext();
	} //while
	$spies->close();

	TextFlush ( "Spies updated.<BR><BR>");
}
else
{
	TextFlush ( "Spies are disabled in this game.<BR><br>");
}

$multiplier = 0;
?>
