<?php
require_once("class_CPULoad.php");

// NOTE: Calling $cpuload->get_load() requires that your webserver has
// write access to the /tmp directory!  If it does not have access, you
// need to edit class_CPULoad.php and change the temporary directory.
$cpuload = new CPULoad();
$cpuload->get_load();
$cpuload->print_load();

echo "<br>$cpuload->cached The average CPU load is: ".$cpuload->load["cpu"]."%<br>\n";

/*
// This is an alternate way to get the CPU load.  This may return more
// accurate CPU load averages than the previous method (especially if
// your site isn't very busy), but it will cause your script to pause
// for 1 full second while processing.

$cpuload = new CPULoad();
$cpuload->sample_load();
$cpuload->print_load();
*/

?>