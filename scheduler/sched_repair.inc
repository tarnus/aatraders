<?php
// 1
// 0
// 1440
// 0
// Y
// How often to check the game database and repair any damaged tables.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

if($db_type == "mysql" and $db_mysql_type == "default"){

	if($deoperror != 1)
		TextFlush ("<b>Starting Database Repair Check</b><br><br>");

	$badtables = 0;
	$ADODB_FETCH_MODE = ADODB_FETCH_NUM;
	$rs_tables = $db->Execute("SHOW TABLES");
	db_op_result($rs_tables,__LINE__,__FILE__);
	while (!$rs_tables->EOF())
	{
		$tablename = $rs_tables->fields[0];
		if($deoperror != 1)
			TextFlush ("<b>Checking Table: $tablename</b><br>");
		$debug_query = $db->Execute("CHECK TABLE $tablename FAST QUICK CHANGED");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->MoveLast();

		if(trim(AAT_strtolower($debug_query->fields[3])) != "ok" && trim(AAT_strtolower($debug_query->fields[3])) != "table is already up to date"){
			if($deoperror != 1)
				TextFlush (" - <b>Corrupted</b><br>");

			$debug_query = $db->Execute("REPAIR TABLE $tablename QUICK");
			db_op_result($debug_query,__LINE__,__FILE__);

			if($deoperror != 1)
				TextFlush ("<b>Repaired Table: $tablename</b><br>");

			scheduler_log("Corrupted Table: $tablename - Repaired & Optimized<br><br>");
			$badtables++;
		}

		$rs_tables->MoveNext();
	}
	$rs_tables->close();

	if($deoperror != 1){
		if($badtables == 0)
			TextFlush ("<br><b>Nothing to repair.</b><br>");
		TextFlush ("<br><b>Database Repair Check Complete</b><br><br>");
	}
}
$ADODB_FETCH_MODE = ADODB_FETCH_ASSOC;

$multiplier = 0;
?>

