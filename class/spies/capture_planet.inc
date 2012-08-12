<?php
class capture_planet {
	var $id = "0";
	var $singlepass = 0;

	function capture_planet()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "planeeti h&otilde;ivata";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Capture Planet";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "den Planeten zu übernehmen";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Catturare il pianeta";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Capture Planet";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Capturar el planeta";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Capture Planet";
				$this->description = "Spy will foment unrest in the population causing them to revolt and change allegiance to you.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier, $spy, $allow_spy_capture_planets, $display_percentage_age, $capture_countdown_max, $capture_quickfind_percentage, $persuasion_countdown_max;

		if ($allow_spy_capture_planets)
		{
			$capture = 20000;
			$capture_trigger = (int) ($capture / 2);

			$success = mt_rand(0, $capture);
			if ($success == $capture_trigger)
			{
				TextFlush ( "Spies Capturing a Planet<br>");

				$spies_on_planet = 0;
				$spy_check = $db->Execute("SELECT COUNT(spy_id) as total FROM {$db_prefix}spies WHERE active='Y' AND ship_id = '0' AND planet_id = $spy[planet_id]");
				db_op_result($spy_check,__LINE__,__FILE__);
				$spies_on_planet = $spy_check->RecordCount();

				$new_age = floor(($display_percentage_age / 2) + mt_rand(0, $display_percentage_age));
				$capture_countdown = mt_rand(floor($capture_countdown_max / 3), $capture_countdown_max);
				$capture_quickfind = floor($spy['credits'] * ((mt_rand(floor($capture_quickfind_percentage / 2), $capture_quickfind_percentage) + $spies_on_planet) * 0.01));
				$hiddencredits = max($spy['credits'] - $capture_quickfind, 0);
				$persuasion_countdown = mt_rand(floor($persuasion_countdown_max / 3), $persuasion_countdown_max);
				$old_rating = good_neutral_evil($spy['owner']);
				$old_owner_rating = $old_rating[0];

				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET last_owner_rating = $old_owner_rating, persuasion_countdown = $persuasion_countdown, credits = $capture_quickfind, captured_countdown = $capture_countdown, hidden_credits = $hiddencredits, use_age=$new_age, cargo_hull = 0, cargo_power = 0, team=null, owner=$spy[owner_id], base='N', defeated='N' WHERE planet_id=$spy[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE from {$db_prefix}autotrades WHERE planet_id = $spy[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				//echo "ID - $spy[planet_id], OLD - $spy[owner], NEW - $spy[owner_id]<BR>";

				change_planet_ownership($spy['planet_id'], $spy['owner'], $spy['owner_id']);
				calc_ownership($spy['sector_id']);
				playerlog($spy['owner_id'], "LOG2_SPY_CPTURE", "$spy[spy_id]|$spy[name]|$spy[sector_id]");
				playerlog($spy['owner'], "LOG2_SPY_CPTURE_OWNER", "$spy[name]|$spy[sector_id]|$spy[character_name]");

				capture_planet_ships($spy['owner_id'], $spy['planet_id']);
				$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET on_planet='N' WHERE planet_id=$spy[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
		}
	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix;

		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='0', job_id='0' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>