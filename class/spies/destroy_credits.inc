<?php
class destroy_credits {
	var $id = "2";
	var $singlepass = 1;

	function destroy_credits()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Destroy Credits";
				$this->description = "Spy will blow up major banks and financial intitutions causing massive amounts of credits to be lost.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier;

		TextFlush ( "Spies Destroying Credits<br>");

		$query = $db->Execute("UPDATE {$db_prefix}planets as p, {$db_prefix}spies as s SET " .
									"p.credits=GREATEST(p.credits-(p.credits * ($multiplier * s.spy_percent)), 0)
									WHERE s.job_id='2' AND s.active='Y' and p.planet_id=s.planet_id");
		db_op_result($query,__LINE__,__FILE__);
		$query->close();
	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix;

		$r1 = $db->Execute("SELECT SUM(spy_percent) as i_total FROM {$db_prefix}spies WHERE active='Y' AND planet_id=$planet_id AND job_id='2' ");
		$total = $r1->fields['i_total'];
		$r1->close();
		$total = floor(("1.0003" - $total - 1) * 30000);
		$new_percent = myrand(floor($total * 0.15), floor($total * 0.35), 1.3);	//15%...35%
		$new_percent /= 30000.0;
		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='$new_percent', job_id='2' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>