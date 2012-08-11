<?php
class birth_increaser {
	var $id = "4";
	var $dig_birthinc_max="0.00003"; // Max birthrate increase percentage production dignitaries will make
	var $max_digs = 5;

	function birth_increaser()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Birthrate Increaser";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Birthrate Increaser";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Geburtenraten steigern";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Incrementatore nascite";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Birthrate Increaser";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Birthrate Increaser";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			default:
				$this->classname = "Birthrate Increaser";
				$this->description = "Dignitary dispenses fertility drugs to the planets water supply to increase the colonists birth rate.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->hit_col_limit = "Too many colonists a Birthrate Increaser can't be assigned.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;
		}
	}

	function sched_process_dignitary()
	{
		global $db, $db_prefix, $multiplier, $colonist_tech_add, $expoprod, $colonist_limit, $organics_consumption, $prate;

		TextFlush ( "Dignitaries increasing birthrate<br>");

	    $planetupdate = "UPDATE {$db_prefix}planets as p, {$db_prefix}dignitary as d SET 
    				p.colonists= LEAST((p.colonists + (p.colonists * ((pow((d.percent + 1) * 1, $multiplier * 1) - 1) * (1 - (p.colonists / ($colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7)))))) * $expoprod)), $colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7))) " .
					"WHERE " .
                    "(p.organics + (LEAST(p.colonists, $colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7))) * (pow((d.percent + 1) * 1, $multiplier * 1) - 1) * $prate[organics] * " .
                    "p.prod_organics / 100.0 * $expoprod) - (LEAST(p.colonists, $colonist_limit + ($colonist_tech_add * ((p.fighter + p.sensors + p.beams + p.torp_launchers + p.shields + p.jammer + p.cloak) / 7))) * (pow((d.percent + 1) * 1, $multiplier * 1) - 1) * " .
                    "$organics_consumption * $expoprod) >= 0) AND d.job_id='4' AND d.active='Y' and d.embezzler = 0 and p.planet_id=d.planet_id";

	    $debug_query = $db->Execute($planetupdate);
    	db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}

	function change_dignitary($dig_id, $planet_id, $job_id)
	{
		global $db, $db_prefix, $dig_embezzlerdelay, $colonist_limit;

		$res = $db->Execute("SELECT dig_id FROM {$db_prefix}dignitary WHERE planet_id=$planet_id and job_id=$job_id ");
    	db_op_result($res,__LINE__,__FILE__);

		if($res->RecordCount() < $this->max_digs)
		{
			$stamp = date("Y-m-d H:i:s");
			$reactive_date = date("Y-m-d H:i:s", strtotime($stamp) + mt_rand(floor($dig_embezzlerdelay * 86400 / 2), $dig_embezzlerdelay * 86400));
			$doom_query = $db->SelectLimit("SELECT colonists from {$db_prefix}planets WHERE planet_id=$planet_id", 1);
	    	db_op_result($doom_query,__LINE__,__FILE__);
			$doomcheck = $doom_query->fields;
			$doom_query->close();
			if($doomcheck['colonists'] < ($colonist_limit*0.5))
			{
				$new_percent = (mt_rand(1, 100) / 100) * $this->dig_birthinc_max;
  				$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET percent='$new_percent', job_id='4', active_date='$stamp', reactive_date='$reactive_date' WHERE dig_id=$dig_id ");
		   		db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
				return $this->success;
			}
			else
			{
				return $this->hit_col_limit;
			}
		}
		else
		{
			return $this->toomany;
		}
	}
}

?>