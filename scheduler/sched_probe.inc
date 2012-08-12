<?php
// 1
// 1500
// 10
// 0
// Y
// How often probes move and perform actions.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

// *********************************
// ***** Probe TURN UPDATES *****
// *********************************

if($allow_probes == 1)
{
	TextFlush ( "\n<B>Probe TURNS</B>");
	include ("globals/log_move.inc");

	function PROBE_playerlog($sid, $log_type, $data = '')
	{
		global $db, $db_prefix;

		// write log_entry to the player's log - identified by player's player_id - sid.
		if ($sid != '' && !empty($log_type))
		{
			if($log_type == "LOG9_PROBE_NOTURNS")
			{
				$stamp = date("Y-m-d H:i:s");
				$result2 = $db->SelectLimit("SELECT log_id from {$db_prefix}logs WHERE player_id=$sid and type='LOG9_PROBE_NOTURNS' and data = " . $db->qstr($data) . " order by log_id DESC", 1);
				$log_id = $result2->fields['log_id'];
				if($result2->recordcount() == 0)
				{
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}logs (player_id, type, time, data) VALUES($sid, '$log_type', '$stamp', " . $db->qstr($data) . ")");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
				}
				else
				{
					$debug_query = $db->Execute("UPDATE {$db_prefix}logs SET time = '$stamp' WHERE log_id = $log_id");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
				}
				$result2->close();
			}
			else
			{
				$stamp = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}logs (player_id, type, time, data) VALUES($sid, '$log_type', '$stamp', " . $db->qstr($data) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
		}
	}

	function sched_probe_detect( $probeinfo )
	{
		global $l_probe_typen;
		include ("globals/probe_detect.inc");
		$probe_detect = probe_detect( $probeinfo['probe_id'] );

		$probe_detected = "";
		if (!empty($probe_detect['sectorlink']))
		{
			$probe_detected .= $probe_detect['sectorlink'] . "<br>";
		}
		if (!empty($probe_detect['warplinks']))
		{
			$probe_detected .= $probe_detect['warplinks'] . "<br>";
		}
		if (!empty($probe_detect['lastship']))
		{
			$probe_detected .=  $probe_detect['lastship'] . "<br>";
		}
		if (!empty($probe_detect['portinfo'])) 
		{
			$probe_detected .=  $probe_detect['portinfo'] . "<br>";
		}
		if (!empty($probe_detect['sector_def']))
		{
			$probe_detected .=  $probe_detect['sector_def'] . "<br>";
		}
		if (!empty($probe_detect['shipdetect']))
		{
			$probe_detected .=  $probe_detect['shipdetect'] . "<br>";
		}
		if (!empty($probe_detect['planetinfo']))
		{
			$probe_detected .=  $probe_detect['planetinfo'] . "<br>";
		}

		playerlog($probeinfo['owner_id'], "LOG9_PROBE_DETECTPROBE", "$probeinfo[probe_id]|$probeinfo[sector_id]|$probe_detected|" . $l_probe_typen[$probeinfo['type']] ); 
		return;
	}

	$l_probe_typen = array();
	$filelist = get_dirlist($gameroot."class/probes/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$probename =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($probename)){
				include ("class/probes/" . $probename . ".inc");
			}
			$probeobject = new $probename();
			$type = $probeobject->type;
			$l_probe_typen[$type] = $probeobject->l_probe_type;
			$probe_object[$type] = $probeobject;
		}
	}

	$res = $db->Execute("SELECT * FROM {$db_prefix}probe WHERE active='Y' AND type > 0 ORDER BY type ASC " );
	db_op_result($res,__LINE__,__FILE__);

	while (!$res->EOF)
	{
		$probeinfo = $res->fields;

		if (mt_rand(1,500) > 300 || $probeinfo['type'] == 5) 
		{
			TextFlush ( "<br>Probe $probeinfo[probe_id]: " . $l_probe_typen[$probeinfo['type']] . "<br>");
			$probe_results = $probe_object[$probeinfo['type']]->probe_scheduler_code($probeinfo);
		}
		$res->MoveNext();
	}
	$res->close();
	TextFlush ( "<br><br>\n<B>Probe TURNS Completed</B></br><br>");
}
 
?>
