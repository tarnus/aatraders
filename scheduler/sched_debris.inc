<?php
// 1
// 2000
// 10
// 0
// Y
// How often to move debris packages and create new debis packages.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

TextFlush ( "<B>Create and Move New Debris Around</B><BR>");

TextFlush ( "<br>Moving Debris around the Universe.<br>");

$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe order by sector_id DESC", 1);
$sector_max = $findem->fields['sector_id'];
$findem->close();

$res=$db->Execute("UPDATE {$db_prefix}debris SET sector_id = FLOOR(RAND() * $sector_max)");
db_op_result($res,__LINE__,__FILE__);

TextFlush ( "<br>Finished Moving Debris around the Universe.<br>");

$result4 = $db->Execute(" SELECT classname, success, trigger_value, enable  FROM {$db_prefix}class_modules_debris WHERE enable=1 and autoadd_debris=1");
db_op_result($result4,__LINE__,__FILE__);
$debris_info = $result4->GetArray();
$debris_count = count($debris_info);
$result4->close();

$result4 = $db->Execute(" SELECT COUNT(sector_id) AS total FROM {$db_prefix}debris");
db_op_result($result4,__LINE__,__FILE__);

$totalcount = $result4->fields['total'];
$result4->close();

if($totalcount < $debris_max){
	TextFlush ( "<br>Adding new Debris to the Universe.<br>");

	$result4 = $db->SelectLimit("SELECT AVG(sh.hull) AS hull_max, AVG(sh.ecm) AS ecm_max, AVG(sh.cloak) AS cloak_max, AVG(sh.armor) AS armor_max, AVG(sh.shields) AS shields_max, AVG(sh.engines) AS engines_max, AVG(sh.power) AS power_max, AVG(sh.fighter) AS fighter_max, AVG(sh.sensors) AS sensors_max, AVG(sh.beams) AS beams_max, AVG(sh.torp_launchers) AS torp_launchers_max FROM {$db_prefix}ships as sh,  {$db_prefix}players as pl where pl.player_id=sh.player_id and pl.npc=0", 1);
	db_op_result($result4,__LINE__,__FILE__);
	$max_list = $result4->fields;
	$result4->close();

//	TextFlush ( nl2br(print_r($max_list, true)) . "<br>");

	for($i = $totalcount; $i < $debris_max; $i++){

		$flag = 1;

		for($ii = 0; $ii < $debris_count; $ii++)
		{
			$success = mt_rand(0, $debris_info[$ii]['success']);
			if ($success == $debris_info[$ii]['trigger_value'] && $debris_info[$ii]['enable'] != 0)
			{
				$debris_type = $debris_info[$ii]['classname'];
				if(!class_exists($debris_type)){
					include ("class/debris/" . $debris_type . ".inc");
				}
				$debrisobject = new $debris_type();
				$debris_data = $debrisobject->autoadd_debris_code($max_list);
				$flag = 0;
				$ii = $debris_count;
			}
		}

		if($flag == 0){
			if ($sector_list_total > 0){
				$randplay=mt_rand(0,($sector_list_total-1));
				$targetlink = $sector_list[$randplay]['sector_id'];
				TextFlush ( "ADDED debris_type: $debris_type, debris_data: $debris_data, debris_sector: $targetlink<br>");
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}debris (debris_type, debris_data, sector_id) values ('$debris_type','$debris_data', $targetlink)");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}
	}
}

$multiplier = 0;
TextFlush ( "<br><B>Create and Move New Debris Finished</B><BR>");
TextFlush ( "<BR>\n");
?>
