<?php
class sabotage_production {
	var $id = "1";
	var $singlepass = 1;

	function sabotage_production()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "saboteerida tootlust";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Sabotage Production";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Sabotage zu betreiben";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Sabotare la produzione";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Sabotage Production";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Sabotear producción";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;

			default:
				$this->classname = "Sabotage Production";
				$this->description = "Spy sabotages all planetary production except for credit production.";
				$this->success = "Spy Job Successfully Changed.";
			break;
		}
	}

	function sched_process_spy()
	{
		global $db, $db_prefix, $multiplier, $spy;

		TextFlush ( "Spies Sabotaging Planet Production<br>");

		$query = $db->Execute("UPDATE {$db_prefix}planets as p, {$db_prefix}spies as s SET p.organics=GREATEST(p.organics-(p.organics * ($multiplier * s.spy_percent)), 0), " .
									"p.ore=GREATEST(p.ore-(p.ore * ($multiplier * s.spy_percent)), 0), 
									 p.goods=GREATEST(p.goods-(p.goods * ($multiplier * s.spy_percent)), 0), 
									 p.energy=GREATEST(p.energy-(p.energy * ($multiplier * s.spy_percent)), 0), " .
									"p.torps=GREATEST(p.torps-(p.torps * ($multiplier * s.spy_percent)), 0), " .
									"p.fighters=GREATEST(p.fighters-(p.fighters * ($multiplier * s.spy_percent)), 0)
									WHERE s.job_id='1' AND s.active='Y' and p.planet_id=s.planet_id");
		db_op_result($query,__LINE__,__FILE__);
		$query->close();
	}

	function change_spy($spy_id, $planet_id, $mode)
	{
		global $db, $db_prefix;

		$r1 = $db->Execute("SELECT SUM(spy_percent) as s_total FROM {$db_prefix}spies WHERE active='Y' AND planet_id=$planet_id AND job_id='1' ");
		$total = $r1->fields['s_total'];
		$r1->close();

		$r1 = $db->Execute("SELECT prate FROM {$db_prefix}class_modules_commodities WHERE class='colonists' ");
		$colonist_production_rate = $r1->fields['prate'];
		$r1->close();

		$total = floor(($colonist_production_rate - $total) * 30000);
		$new_percent = myrand(floor($total * 0.1), floor($total * 0.3), 1.3);	//10%...30%
		$new_percent /= 30000.0;
		$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET move_type='$mode', spy_percent='$new_percent', job_id='1' WHERE spy_id=$spy_id ");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>