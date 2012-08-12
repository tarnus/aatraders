<?php
// Step 999 - Setup Scheduler and finalize game

include ("globals/insert_news.inc");

TextFlush ("<B><BR>Configuring game scheduler<BR></B>");

echo "<BR>Update ticks will occur every $sched_ticks minutes<BR>";
$filevar = "sched_file";

$stamp = date("Y-m-d H:i:s");

$filelist = get_dirlist($gameroot."scheduler/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$fs = fopen($gameroot . "scheduler/" . $filelist[$c], "r");
		$head = fgets($fs);
		$enable_schedule = AAT_substr(trim(fgets($fs)), 3);
		$execution_order = AAT_substr(trim(fgets($fs)), 3);
		$ticks_full = AAT_substr(trim(fgets($fs)), 3);
		$loop_count = AAT_substr(trim(fgets($fs)), 3);
		$loop = AAT_substr(trim(fgets($fs)), 3);
		$extra_info = AAT_substr(trim(fgets($fs)), 3);
		fclose($fs);
		echo "$ticks_full minutes - $extra_info<br>";
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}scheduler (enable_schedule, execution_order, is_loop, ticks_left, ticks_full, loop_count, sched_file, extra_info, last_run) VALUES('$enable_schedule', '$execution_order', '$loop', '0', '$ticks_full', '$loop_count', '$filelist[$c]', '$extra_info', '$stamp')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

$creating = 1;
$reset_date = date("Y-m-d");
$debug_query = $db->Execute("INSERT INTO {$db_prefix}config_values (name, value, input_type, input_selections, description, section) VALUES ('reset_date','$reset_date', 'text', '', 'Date the server was last reset', 'Reset Date')");

exportvariables();

//include ("scheduler/sched_updateserverlist.inc");

echo "<br>Inserting news of Universe Creation ";
$stamp = date("Y-m-d H:i:s");
insert_news("", 1, "creation");

$password = AAT_substr($adminpass, 0, $maxlen_password);
echo "<BR><BR><center><B>Your admin login Password: $password<BR>";

TextFlush("<BR>Enter this URL to access Admin Functions <a href=\"http://" . $_SERVER['HTTP_HOST'] . $gamepath . "/admin.php\">http://" . $_SERVER['HTTP_HOST'] . $gamepath . "/admin.php</a>");
TextFlush("<br><BR><center><BR><B>Congratulations! Universe created successfully.<BR>");
TextFlush("Click <A HREF=index.php>here</A> to return to the login screen.</B></center>");
?>