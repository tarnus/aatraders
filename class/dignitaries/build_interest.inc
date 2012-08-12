<?php
class build_interest {
	var $id = "2";
	var $dig_interest_max = 0.000005; //Max interest percentage interest dignitaries will make
	var $max_digs = 1;

	function build_interest()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Credit Booster";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Credit Booster";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Credit Booster";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Incrementatore crediti";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Credit Booster";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Credit Booster";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			default:
				$this->classname = "Credit Booster";
				$this->description = "Dignitary slightly boosts credit production of the Colonists by increasing moral.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;
		}
	}

	function sched_process_dignitary()
	{
		global $db, $db_prefix, $multiplier, $colonist_tech_add, $expoprod, $colonist_limit, $organics_consumption, $prate, $credits_prate;

		TextFlush ( "Dignitaries boosting credits<br>");

	    $planetupdate = "UPDATE {$db_prefix}planets as p, {$db_prefix}dignitary as d SET 
					p.credits = p.credits + (((LEAST(p.colonists, $colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7))) * $prate[colonists]) * $credits_prate * ((100.0 - p.prod_organics - p.prod_ore - p.prod_goods - p.prod_energy - p.prod_fighters - p.prod_torp - p.prod_research - p.prod_build) / 100.0) * $expoprod * (pow((d.percent + 1) * 1, $multiplier * 1) - 1)))" .
					"WHERE " .
                    "(p.organics + (LEAST(p.colonists, $colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7))) * (pow((d.percent + 1) * 1, $multiplier * 1) - 1) * $prate[organics] * " .
                    "p.prod_organics / 100.0 * $expoprod) - (LEAST(p.colonists, $colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7))) * (pow((d.percent + 1) * 1, $multiplier * 1) - 1) * " .
                    "$organics_consumption * $expoprod) >= 0) AND d.job_id='2' AND d.active='Y' and d.embezzler = 0 and p.planet_id=d.planet_id";

	    $debug_query = $db->Execute($planetupdate);
    	db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();

	}

	function change_dignitary($dig_id, $planet_id, $job_id)
	{
		global $db, $db_prefix, $dig_embezzlerdelay;

		$res = $db->Execute("SELECT dig_id FROM {$db_prefix}dignitary WHERE planet_id=$planet_id and job_id=$job_id ");
    	db_op_result($res,__LINE__,__FILE__);

		if($res->RecordCount() < $this->max_digs)
		{
			$stamp = date("Y-m-d H:i:s");
			$reactive_date = date("Y-m-d H:i:s", strtotime($stamp) + mt_rand(floor($dig_embezzlerdelay * 86400 / 2), $dig_embezzlerdelay * 86400));
			$new_percent = (mt_rand(1, 100) / 100) * $this->dig_interest_max;
			$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET percent='$new_percent', job_id='2', active_date='$stamp', reactive_date='$reactive_date' WHERE dig_id=$dig_id ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();
			return $this->success;
		}
		else
		{
			return $this->toomany;
		}
	}
}

?>