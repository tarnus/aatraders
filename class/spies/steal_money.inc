<?php
class steal_money {
	var $id = "6";
	var $singlepass = 0;

	function steal_money()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "raha varastada";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Steal Money";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Geld zu stehlen";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Rubare denaro";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Steal Money";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Steal Money";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Robar dinero";
				$this->description = "Spy steals large sums of money and stores it on your ship.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier, $spy;

		$steal_money = 2000;
		$steal_money_trigger = (int) ($steal_money / 2);
		$success = mt_rand(0, $steal_money);
		if ($success == $steal_money_trigger)
		{
			if ($spy['credits'] > 0)
			{
				TextFlush ( "Spy Stealing Money<br>");

				$roll = myrand(2400, 9000, 2.5);	//8%...30%
				$sum = floor($spy['credits'] * $roll / 30000);
				$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET credits=credits-$sum WHERE planet_id=$spy[planet_id] ");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();

				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits+$sum WHERE player_id=$spy[owner_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
		}
	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix;

		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='0', job_id='6' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>