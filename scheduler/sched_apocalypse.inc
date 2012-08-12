<?php
// 1
// 1000
// 180
// 0
// Y
// How often planets are checked, based on the number of planets each player controls, to see if an apocalypse happens..


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

TextFlush ( "<b>Planetary apocalypse</b><br><br>");

$apocalypse_classname = array();
$class_count = 0;
$filelist = get_dirlist($gameroot."class/apocalypse/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$apocalypse_classname =  str_replace(".inc", "", $filelist[$c]); 
		if(!class_exists($apocalypse_classname)){
			include ("class/apocalypse/" . $apocalypse_classname . ".inc");
		}
		$apocalypse_object[$class_count] =  new $apocalypse_classname();
		$class_count++;
	}
}

$player_query = $db->Execute("SELECT player_id from {$db_prefix}players WHERE npc = 0 and destroyed != 'Y'");
db_op_result($player_query,__LINE__,__FILE__);

while (!$player_query->EOF)
{
	$playerid = $player_query->fields['player_id'];

	$debug_query = $db->Execute("SELECT planet_id from {$db_prefix}planets WHERE owner = $playerid");
	db_op_result($debug_query,__LINE__,__FILE__);

	$rectotal = $debug_query->RecordCount();
	if($rectotal > 0)
	{
		$findem = $db->SelectLimit("SELECT planet_id, sector_id, name, owner from {$db_prefix}planets WHERE colonists > (($colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * ($doomsday_value * 0.01)) and owner = $playerid ORDER BY rand()", 1);
		$randplanet = $findem->fields;
		$randcount = $findem->RecordCount();
		$findem->close();

		$affliction = mt_rand(0, max($class_count, (100 + $class_count) * (40/ $rectotal)));

		if ($affliction < $class_count && $rectotal > 20 && $randcount > 0)
		{
			$targetplanet = $randplanet['planet_id'];
			$targetsector = $randplanet['sector_id'];
			$targetname = $randplanet['name'];
			$targetowner = $randplanet['owner'];

			$result = $apocalypse_object[$affliction]->apocalypse($targetplanet, $targetsector, $targetname, $targetowner);
		}
		$debug_query->close();
	}
	$player_query->MoveNext();
}
$player_query->close();

TextFlush ( "<br>");

?>
