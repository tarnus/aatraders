<?php
class destroy_fighters {
	var $id = "4";
	var $singlepass = 0;

	function destroy_fighters()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "purustada h&auml;vitajaid";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Destroy Fighters";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Jäger zu zerstören";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Distruggere droni";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Destroy Fighters";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Destruir Cazas";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Destroy Fighters";
				$this->description = "Spy will randomly destroy large numbers of fighters stored on the planet.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier, $spy;

		$blowup_fits = 5000;
		$blowup_fits_trigger = (int) ($blowup_fits / 2);
		$success = mt_rand(0, $blowup_fits);
		if ($success == $blowup_fits_trigger)
		{
			if ($spy['fighters'] > 0)
			{
				TextFlush ( "Spy Destroying Fighters<br>");

				$roll = myrand(2400, 9000, 4);	//8%...30%
				$blow = floor($spy['fighters'] * $roll / 30000);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=fighters-$blow WHERE planet_id=$spy[planet_id] ");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
	}

	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix;

		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='0', job_id='4' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>