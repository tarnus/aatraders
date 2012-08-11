<?php
class decrease_birthrate {
	var $id = "3";
	var $singlepass = 1;

	function decrease_birthrate()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "s&uuml;ndivust v&auml;hendada";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Birthrate Decreaser";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "die Geburtenrate zu senken";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Limitatore nascite";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Birthrate Decreaser";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Reducir natalidad";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Birthrate Decreaser";
				$this->description = "Spy kills large amounts of the planets population in a covert manner.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier;

	TextFlush ( "Spies Killing Enemy Colonists<br>");

	$query = $db->Execute("UPDATE {$db_prefix}planets as p, {$db_prefix}spies as s SET " .
								"p.colonists=GREATEST(p.colonists-(p.colonists * ($multiplier * s.spy_percent)), 0)
								WHERE s.job_id='3' AND s.active='Y' and p.planet_id=s.planet_id");
	db_op_result($query,__LINE__,__FILE__);
	$query->close();

	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix, $colonist_reproduction_rate;

		$r1 = $db->Execute("SELECT SUM(spy_percent) as b_total FROM {$db_prefix}spies WHERE active='Y' AND planet_id=$planet_id AND job_id='3' ");
		$total = $r1->fields['b_total'];
		$r1->close();
		$total = floor(($colonist_reproduction_rate - $total) * 500000);
		$new_percent = myrand(floor($total * 0.1), floor($total * 0.3), 1.3);	//10%...30%
		$new_percent /= 500000.0;
		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='$new_percent', job_id='3' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>