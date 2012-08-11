<?php
// 1
// 1648
// 1440
// 0
// Y
// Adding artifacts as the game progresses

// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minutes between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

if($adminexecuted == 1){
	TextFlush ( "<b>Artifact Rebuild Started</b><br>");
}

$findem = $db->Execute("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and zone_id !=2");
$sector_list_count=$findem->RecordCount(); 
$sector_list_array=$findem->GetArray();
$findem->close();

$res = $db->Execute("SELECT {$db_prefix}planets.planet_id, {$db_prefix}planets.sector_id
					FROM {$db_prefix}planets , {$db_prefix}universe 
					WHERE {$db_prefix}universe.sector_id = {$db_prefix}planets.sector_id
					AND aatrade_universe.zone_id !=2
					AND {$db_prefix}universe.sg_sector =0");
db_op_result($res,__LINE__,__FILE__);
$planet_list_count=$res->RecordCount(); 
$planet_list_array=$res->GetArray();

$filelist = get_dirlist($gameroot."class/artifacts/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$artifacts_classname = str_replace(".inc", "", $filelist[$c]); 
		if(!class_exists($artifacts_classname)){
			include ("class/artifacts/" . $artifacts_classname . ".inc");
		}
		$artifacts_object = new $artifacts_classname();
		$res = $db->Execute("SELECT artifact_id FROM {$db_prefix}artifacts WHERE artifact_type='$artifacts_classname'");
    	db_op_result($res,__LINE__,__FILE__);
    	if($res->RecordCount() < ($artifacts_object->pieces * $artifacts_object->maximum_in_galaxy))
    	{
			$artifacts_object->sched_process_artifact($artifacts_classname);
		}
	}
}

if($adminexecuted == 1){
	TextFlush ( "<b>Artifact Rebuild Finished</b><br><br>");
}

$multiplier = 0;

?>
