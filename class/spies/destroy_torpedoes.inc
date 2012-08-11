<?php
class destroy_torpedoes {
	var $id = "5";
	var $singlepass = 0;

	function destroy_torpedoes()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "purustada torpeedosid";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Destroy Torpedoes";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Torpedos zu zerstören";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Distruggere siluri";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Destroy Torpedoes";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Destruir Torpedos";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Destroy Torpedoes";
				$this->description = "Spy destroys large numbers of planetary torpedoes.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier, $spy;

		$blowup_torp = 3000;
		$blowup_torp_trigger = (int) ($blowup_torp / 2);
		$success = mt_rand(0, $blowup_torp);
		if ($success == $blowup_torp_trigger)
		{
			if ($spy['torps'] > 0)
			{
				TextFlush ( "Spy Destroying Torpedoes<br>");

				$roll = myrand(2100, 7500, 3);	//7%...25%
				$blow = floor($spy['torps'] * $roll / 30000);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET torps=torps-$blow WHERE planet_id=$spy[planet_id] ");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
		}

	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix;

		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='0', job_id='5' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>