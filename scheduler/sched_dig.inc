<?php
// 1
// 450
// 2
// 0
// Y
// How often the dignitaries without a job will look for a job on a planet.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/myrand.inc");

TextFlush ( "<b>DIGNITARIES</b><br>\n");

if ($enable_dignitaries){
	$steal_money = 3000;//Embezel Funds
	$build_torp = 4000;//Build Torps
	$build_fighters = 5000;// Build Fighters

	$steal_money_trigger = (int) ($steal_money / 2);
	$build_torp_trigger = (int) ($build_torp / 2);
	$build_fighters_trigger = (int) ($build_fighters / 2);
	$stamp = date("Y-m-d H:i:s");

	$i = 0;

	// Getting all possibly needed information about the dig, the planet, the dig owner and his ship
	$dignitaries = $db->Execute("SELECT {$db_prefix}planets.*, {$db_prefix}dignitary.*, {$db_prefix}players.character_name FROM {$db_prefix}planets INNER JOIN {$db_prefix}dignitary ON {$db_prefix}planets.planet_id = {$db_prefix}dignitary.planet_id INNER JOIN {$db_prefix}players ON {$db_prefix}dignitary.owner_id = {$db_prefix}players.player_id INNER JOIN {$db_prefix}ships ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE {$db_prefix}dignitary.embezzler = '0' AND {$db_prefix}dignitary.active='Y' AND {$db_prefix}dignitary.ship_id = '0' and {$db_prefix}planets.base='Y' ");
	TextFlush ( $db->ErrorMsg());

	$num_dignitaries = $dignitaries->RecordCount();
	TextFlush ("Processing " . $num_dignitaries . " dignitaries.<br>");

	while(!$dignitaries->EOF){
		$dig = $dignitaries->fields;
		$flag = 0;

		if (!$dig['name']) {
			$dig['name'] = $l_unnamed;
		}

		$multiplier_count = $multiplier;

		while($multiplier_count > 0)
		{
			$success = mt_rand(0, $steal_money);
			if ($success == $steal_money_trigger && $dig['job_id'] != 0)
   			{
				TextFlush ( "Dignitary turned into an Imbezzeler<br>");
		   		if ($dig['credits'] > 0)
				{
					$reactive_date = date("Y-m-d H:i:s", strtotime($stamp) + mt_rand(floor($dig_embezzlerdelay * 86400 / 2), $dig_embezzlerdelay * 86400));
					$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET active_date='$stamp', reactive_date='$reactive_date', embezzler = 1 WHERE dig_id=$dig[dig_id] ");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
			   		$flag = 1;
				}
 			}

			$success = mt_rand(0, $build_torp);
			if ($success == $build_torp_trigger && $flag)
			{
				TextFlush ( "Build Torps<br>");
				if ($dig['torps'] > 0)
				{
					$roll = myrand(2100, 7500, 3);	//7%...25%
					$blow = floor($dig['torps'] * $roll / 30000);
					$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET torps=torps+$blow WHERE planet_id=$dig[planet_id] ");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
					$temp = NUMBER($blow);
					playerlog($dig['owner_id'], "LOG1_DIG_TORPS", "$dig[dig_id]|$dig[name]|$dig[sector_id]|$temp");
					$flag = 1; 
				}  
			}

			$success = mt_rand(0, $build_fighters);
			if ($success == $build_fighters_trigger && $flag)
			{
				TextFlush ( "Build Fighters<br>");
				if ($dig['fighters'] > 0)
				{
					$roll = myrand(2400, 9000, 4);	//8%...30%
					$blow = floor($dig['fighters'] * $roll / 30000);
					$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET fighters=fighters+$blow WHERE planet_id=$dig[planet_id] ");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
					$temp = NUMBER($blow);
					playerlog($dig['owner_id'], "LOG1_DIG_FITS", "$dig[dig_id]|$dig[name]|$dig[sector_id]|$temp");
					$flag = 1; 
				}  
			}

			$multiplier_count--;
		}
		$dignitaries->MoveNext();
	} //while
	$dignitaries->close();

	$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET embezzler=2 WHERE embezzler = 0 and reactive_date < '$stamp'");
	db_op_result($debug_query,__LINE__,__FILE__);
	TextFlush ( "New Dignitaries Immune to Embezzling: " . $db->Affected_Rows() . "<br>");
	$debug_query->close();

	$filelist = get_dirlist($gameroot."class/dignitaries/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$dignitary_classname =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($dignitary_classname)){
				include ("class/dignitaries/" . $dignitary_classname . ".inc");
			}
			$dignitary_object = new $dignitary_classname();
			$dignitary_object->sched_process_dignitary();
		}
	}

	TextFlush ( "Dignitaries Embezzling credits<br>");

	$res = $db->Execute("SELECT d.*, p.* FROM {$db_prefix}dignitary as d, {$db_prefix}planets as p WHERE d.embezzler = 1 AND d.active='Y' and p.planet_id=d.planet_id and d.reactive_date<='$stamp'");
	db_op_result($res,__LINE__,__FILE__);

	while(!$res->EOF)
	{
		$row = $res->fields;

		// Imbezzeler
		if (mt_rand(0,100) <= $dig_embezzler_success and $row['credits'] > 0){
			$sum = floor((mt_rand(1, $dig_embezzler_amount) / 100) * $row['credits']);
			TextFlush ( "$row[planet_id] - Embezzler Dig - amount embezzled = ".NUMBER($sum)." - ");
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET credits=credits-$sum WHERE planet_id=$row[planet_id] ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();
			$ownerdude=$row['owner'];
			$findem = $db->SelectLimit("SELECT player_id FROM {$db_prefix}players WHERE destroyed ='N' AND player_id <> $ownerdude and player_id > 3 and turns_used > $dig_embezzlerturns ORDER BY rand()", 1);
			$playergift = $findem->fields['player_id'];
			$recordtotal = $findem->RecordCount();
			$findem->close();

			if ($recordtotal > 0){
				TextFlush ( "PlayerID:".$playergift);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits+$sum WHERE player_id=$playergift");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
				$temp = NUMBER($sum);
				playerlog($playergift, "LOG1_DIG_MONEY", "$row[dig_id]|$row[name]|$row[sector_id]|$temp");
			}
			else
			{
				$randplay=mt_rand(0,($sector_list_total-1));
				$targetlink = $sector_list[$randplay]['sector_id'];
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}debris (debris_type, debris_data, sector_id) values ('shipcredits','$sum', $targetlink)");
				db_op_result($debug_query,__LINE__,__FILE__);
				TextFlush ( "Debris");
			}
			TextFlush ( "<br>");

			$stamp = date("Y-m-d H:i:s");
			$reactive_date = date("Y-m-d H:i:s", strtotime($stamp) + mt_rand(floor($dig_embezzlerdelay * 86400 / 2), $dig_embezzlerdelay * 86400));
			$debug_query = $db->Execute("UPDATE {$db_prefix}dignitary SET active_date='$stamp', reactive_date='$reactive_date' WHERE dig_id=$row[dig_id] ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();

			$result_s = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id=$row[planet_id] and owner_id=$row[owner_id]");
			$reccount = $result_s->RecordCount();
			$result_s->close();
			for($spycheck = 0; $spycheck < $reccount; $spycheck++){
				$success=mt_rand(1,1000);
				if($success < ($dig_spy_embezzler * 10)){
					playerlog($row['owner_id'], "LOG2_SPY_FOUND_EMBEZZLER", "$row[dig_id]|$row[name]");
					TextFlush ( "$row[planet_id] - Embezzler Dig - found by spy<br>");
					$spycheck = $reccount;
				}
			}
		}
		$res->MoveNext();
	}
	$res->close();
	TextFlush ("<br>");

	TextFlush ( "dignitaries updated.<BR><BR>");
}
else
{
	TextFlush ( "dignitaries are disabled in this game.<BR><br>");
}
$multiplier = 0;
?>

