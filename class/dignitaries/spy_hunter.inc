<?php
class spy_hunter {
	var $id = "5";
	var $dig_spyhunter_max="0.00100"; // Max spy hunter effectiveness percentage production dignitaries will make
	var $max_digs = 5;

	function spy_hunter()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Spy Hunter";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "french":
				$this->classname = "Spy Hunter";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "german":
				$this->classname = "Spionen-Jagd";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "italian":
				$this->classname = "Cacciatore di spie";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "russian":
				$this->classname = "Spy Hunter";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			case "spanish":
				$this->classname = "Spy Hunter";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;

			default:
				$this->classname = "Spy Hunter";
				$this->description = "Dignitary hunts for enemy spies and kills them.  More hunters are more effective in finding spies.";
				$this->toomany = "Maximum number of " . $this->classname . " Dignitaries reached for this planet.";
				$this->success = "Dignitary Job Successfully Changed.";
			break;
		}
	}

	function sched_process_dignitary()
	{
		global $db, $db_prefix;

		TextFlush ( "Dignitaries looking for spies<br>");

		$res = $db->Execute("SELECT SUM(d.percent) as chancetotal, d.*, p.* FROM {$db_prefix}dignitary as d, {$db_prefix}planets as p WHERE d.job_id='5' AND d.active='Y' and d.embezzler = 0 and p.planet_id=d.planet_id group by d.planet_id");
		db_op_result($res,__LINE__,__FILE__);
		while (!$res->EOF)
		{
			$row = $res->fields;

			if (mt_rand(1, 100) < (5+($row['chancetotal']*10000)))
			{
				$result_sf = $db->Execute("SELECT * FROM {$db_prefix}spies,{$db_prefix}players WHERE {$db_prefix}spies.owner_id={$db_prefix}players.player_id and {$db_prefix}spies.planet_id=$row[planet_id] AND {$db_prefix}spies.active='Y' "); 
				db_op_result($result_sf,__LINE__,__FILE__);
				if ($result_sf->RecordCount() > 0){
					while(!$result_sf->EOF)
					{
						$spy1 = $result_sf->fields;
						$result_sf->MoveNext();
					}
				}
				if ($result_sf->RecordCount() > 0){
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE spy_id=$spy1[spy_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					playerlog($row['owner_id'], "LOG1_DIG_KILLED_SPY", "$row[name]|$row[sector_id]|$spy1[character_name]");
					playerlog($spy1['player_id'], "LOG2_SPY_KILLED_SPYOWNER", "$spy1[spy_id]|$row[name]|$row[sector_id]");
					TextFlush ( "$row[planet_id] - Spy hunter Dig - found and killed enemy spy<br>");
				}
				$result_sf->close();
			}
			$res->MoveNext();
		}
		$res->close();
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
			$new_percent = (mt_rand(1, 100) / 100) * $this->dig_spyhunter_max;

			$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET percent='$new_percent', job_id='5', active_date='$stamp', reactive_date='$reactive_date' WHERE dig_id=$dig_id ");
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