<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: scheduler.php

/******************************************************************
* Explanation of the scheduler									*
*																 *
* Here are the scheduler DB fields, and what they are used for :  *
*  - sched_id : Unique ID. Before calling the file responsible	*
*	for the event, the variable $sched_var_id will be set to	 *
*	this value, so the called file can modify the triggering	 *
*	scheduler entry if it needs to.							  *
*																 *
*  - is_loop : Set this to 'Y' if you want the event to be looped	*
*	endlessly. If this value is set to 'Y', the 'spawn' field is *
*	not used.													*
*																 *
*  - loop_count : If you want your event to be run a certain number *
*	of times only, set this to the number of times. For this to	 *
*	work, loop must be set to 'N'. When the event has been run   *
*	spawn number of times, it is deleted from the scheduler.	 *
*																 *
*  - ticks_left : Used internally by the scheduler. It represents *
*	the number of mins elapsed since the last call. ALWAYS set   *
*	this to 0 when scheduling a new event.					   *
*																 *
*  - ticks_full : This is the interval in minutes between		 *
*	different runs of your event. Set this to the frenquency	 *
*	you wish the event to happen. For example, if you want your  *
*	event to be run every three minutes, set this to 3.		  *
*																 *
*  - file : This is the file that will be called when an event	*
*	has been trigerred.										  *
*																 *
*  - extra_info : This is a text variable that can be used to	 *
*	store any extra information concerning the event triggered.  *
*	It will be made available to the called file through the	 *
*	variable $sched_var_extrainfo.							   *
*																 *
* If you are including files in your trigger file, it is important*
* to use include_once() instead of include(), as your file might  *
* be called multiple times in a single execution. If you need to  *
* define functions, you can put them in your own				  *
* include file, with an include statement. THEY CANNOT BE		 *
* DEFINED IN YOUR MAIN FILE BODY. This would cause PHP to issue a *
* multiple function declaration error.							*
*																 *
* End of scheduler explanation									*
******************************************************************/

// AADATA&admin_password=password&game_number=0

require_once ("config/config_sched.php");

scheduler_log("Scheduler Started","\n");

$template_object->enable_gzip = 0;

$langdir = $default_lang;

include ("languages/$langdir/lang_common.inc");

$title = "System Update";

if($adminexecuted == 1){
	TextFlush("<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
		<html>
		 <head>
		  <meta http-equiv=\"Pragma\" content=\"no-cache\">
		  <META HTTP-EQUIV=\"Expires\" CONTENT=\"-1\">
		  <title>$title</title>
<style type=\"text/css\">
<!--
body             { font-family: Verdana, Arial, sans-serif; font-size: x-small;}
td                { font-size: 12px; color: #e0e0e0; font-family: verdana; }
-->
</style>
		 </head>
			<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 background=\"templates/default_paged/images/bgoutspace1.png\" bgcolor=\"#000000\" text=\"#c0c0c0\" link=\"#52ACEA\" vlink=\"#52ACEA\" alink=\"#52ACEA\">
		<table><tr><td>
	");

	TextFlush( "<H1>$title</H1>\n");
}

$BenchmarkTimer = new c_Timer;

$sf = (bool) ini_get('safe_mode');
if (!$sf)
{
	set_time_limit(600);
}

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if ($admin_password == $adminpass)
{
	$sched_res = $db->SelectLimit("SELECT last_run FROM {$db_prefix}scheduler where enable_schedule = 1 order by execution_order ASC", 1);
	$startschedtime = $sched_res->fields['last_run'];
	$sched_res->close();
	$sched_res = $db->SelectLimit("SELECT last_run FROM {$db_prefix}scheduler where enable_schedule = 1 order by execution_order DESC", 1);
	$endschedtime = $sched_res->fields['last_run'];
	$sched_res->close();
	$unixdate = strtotime($startschedtime);

	$numberofticks = 3;
	$daylightsavingstimelimit = ($numberofticks * $sched_ticks) * 60; // How many seconds outside normal before reset (3 * 5) * 60 = 900 (15 minutes)
	$unixdatecheck = strtotime(date("Y-m-d H:i:s")) - $daylightsavingstimelimit; // Spring forward check
	$unixdatecheck2 = strtotime(date("Y-m-d H:i:s")) + $daylightsavingstimelimit; // Fall back check

	$startschedtime = $endschedtime;
	if($startschedtime == $endschedtime || $unixdate < $unixdatecheck || $unixdate > $unixdatecheck2)
	{
		$starttime = time();

		$findem = $db->Execute("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 3");
		$sector_list_total=$findem->RecordCount(); 
		$sector_list=$findem->GetArray();
		$findem->close();

		$cargo_query = $db->Execute("SELECT class, prate from {$db_prefix}class_modules_commodities where cargoport=1");
		db_op_result($cargo_query,__LINE__,__FILE__);

		while (!$cargo_query->EOF) 
		{
			$cargotype = $cargo_query->fields['class'];
			$prate[$cargotype] = $cargo_query->fields['prate'];
			$cargo_query->Movenext();
		}
		$cargo_query->close();

		$cargo_query = $db->Execute("SELECT class, prate from {$db_prefix}class_modules_planet where class = 'Planet_Torpedo' or class = 'Planet_Fighter'");
		db_op_result($cargo_query,__LINE__,__FILE__);

		while (!$cargo_query->EOF) 
		{
			$cargotype = $cargo_query->fields['class'];
			$prate[$cargotype] = $cargo_query->fields['prate'];
			$cargo_query->Movenext();
		}
		$cargo_query->close();

		$runstamp = date("Y-m-d H:i:s");
		$sched_res = $db->Execute("SELECT * FROM {$db_prefix}scheduler where enable_schedule = 1 order by execution_order ASC");
		if ($sched_res)
		{
			while (!$sched_res->EOF)
			{
				$event = $sched_res->fields;
				$multiplier = ($sched_ticks / $event['ticks_full']) + ($event['ticks_left'] / $event['ticks_full']);
				$multiplier = (int) $multiplier * $scheduler_passes;
				$ticks_left = ($sched_ticks + $event['ticks_left']) % $event['ticks_full'];
				$expoprod = mypw($colonist_reproduction_rate + 1, $multiplier) * $multiplier;

				if ($event['is_loop'] == 'N')
				{
					if ($multiplier > $event['loop_count'])
					{
						$multiplier = $event['loop_count'];
					}

					if ($event['loop_count'] == 0)
					{
						$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET enable_schedule='0' WHERE sched_id=$event[sched_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
					else
					{
						$sched_var_id = $event['sched_id'];
						$sched_var_extrainfo = $event['extra_info'];

						$sched_i = 0;
						while ($sched_i < $multiplier)
						{
							if($enable_scheduler == 1 or $event['sched_file'] == "sched_updateserverlist.inc"){
								$BenchmarkTimer->start();
								TextFlush();
								$querycountstart = $db->query_count;
								scheduler_log("Starting $event[sched_file]","");
								include ("scheduler/$event[sched_file]");
								$objectexecution = new scheduler();
								
								scheduler_log("Ending $event[sched_file]","\n");
								$StopTime = $BenchmarkTimer->stop();
								$Elapsed = $BenchmarkTimer->elapsed();
								$Elapsed = sprintf("%01.2f", $Elapsed);
								$querycountend = $db->query_count - $querycountstart;
								TextFlush("<br>\nElapsed Time: $Elapsed seconds, Queries Executed: $querycountend<br>");
								TextFlush ("<hr>");
							}
							else
							{
								TextFlush();
								TextFlush ("Scheduler Disabled $event[sched_file]<br><hr><br>");
							}
							$sched_i++;
						}
						$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET last_run='$runstamp', ticks_left=$ticks_left, loop_count=loop_count-$multiplier WHERE sched_id=$event[sched_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
				}
				else
				{   
					$sched_var_id = $event['sched_id'];
					$sched_var_extrainfo = $event['extra_info'];

					$sched_i = 0;
					while ($sched_i < $multiplier)
					{
						if($enable_scheduler == 1 or $event['sched_file'] == "sched_updateserverlist.inc"){
							$BenchmarkTimer->start();
							TextFlush();
							$querycountstart = $db->query_count;
							scheduler_log("Starting $event[sched_file]","");
							include ("scheduler/$event[sched_file]");
							scheduler_log("Ending $event[sched_file]","\n");
							$StopTime = $BenchmarkTimer->stop();
							$Elapsed = $BenchmarkTimer->elapsed();
							$Elapsed = sprintf("%01.2f", $Elapsed);
							$querycountend = $db->query_count - $querycountstart;
							TextFlush("<br>\nElapsed Time: $Elapsed seconds, Queries Executed: $querycountend<br>");
							TextFlush ("<hr>");
						}
						else
						{
							TextFlush();
							TextFlush ("Scheduler Disabled $event[sched_file]<br><hr><br>");
						}
						$sched_i++;
					}
					$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET last_run='$runstamp', ticks_left=$ticks_left WHERE sched_id=$event[sched_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
				}

				$sched_res->MoveNext();
			}
		}
		$sched_res->close();
	}
	else
	{
		TextFlush ("Previous schedule has not finished executing.<br><br>");
	}
	
	$runtime = time() - $starttime;
	TextFlush ("<p>The scheduler took $runtime seconds to execute.<br>" . $db->query_count . " queries in " . sprintf("%01.4f", $db->query_time_total) . " seconds<p>");
	scheduler_log("The scheduler took $runtime seconds to execute.\n" . $db->query_count . " queries in " . sprintf("%01.4f", $db->query_time_total) . " seconds<p>","\n");

	scheduler_log("Scheduler Ended","\n\n");
	if($adminexecuted == 1){
		unset ($template_object);
		TextFlush ("<br><br></td></tr></table>");
		TextFlush( "</body></html>\n");
	}
}
else
{
	if($adminexecuted == 1){
		unset ($template_object);
		TextFlush ("Scheduler Failed<br><br></td></tr></table>");
		TextFlush( "</body></html>\n");
	}
	scheduler_log("Scheduler Failed","\n");
}

$db->close();
?>
