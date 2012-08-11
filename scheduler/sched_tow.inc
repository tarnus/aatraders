<?php
// 1
// 700
// 5
// 0
// Y
// How often ships are checked to be towed.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/log_move.inc");

TextFlush ( "<b>TOWING</b><br>\n");
TextFlush ( "Towing bigger players out of restricted zones...<BR>");

$debug_query = $db->Execute("SELECT {$db_prefix}ships.ship_id, {$db_prefix}players.player_id, {$db_prefix}players.character_name, {$db_prefix}ships.hull, {$db_prefix}ships.cloak, " .
							"{$db_prefix}ships.class, {$db_prefix}ships.sector_id, {$db_prefix}universe.zone_id, {$db_prefix}zones.max_hull " .
							"FROM {$db_prefix}ships, {$db_prefix}universe, {$db_prefix}zones, " .
							"{$db_prefix}players WHERE {$db_prefix}ships.player_id={$db_prefix}players.player_id and " .
							"{$db_prefix}ships.sector_id={$db_prefix}universe.sector_id AND " .
							"{$db_prefix}universe.zone_id={$db_prefix}zones.zone_id AND {$db_prefix}zones.max_hull<>0 " .
							"AND ROUND((({$db_prefix}ships.hull_normal + {$db_prefix}ships.engines_normal + {$db_prefix}ships.fighter_normal +" .
							" {$db_prefix}ships.beams_normal + {$db_prefix}ships.torp_launchers_normal + {$db_prefix}ships.shields_normal +" .
							" {$db_prefix}ships.ecm_normal + {$db_prefix}ships.sensors_normal + {$db_prefix}ships.cloak_normal + {$db_prefix}ships.power_normal " .
							"+ {$db_prefix}ships.armor_normal)/11)) > {$db_prefix}zones.max_hull AND {$db_prefix}players.destroyed='N' and {$db_prefix}ships.ship_id={$db_prefix}players.currentship and {$db_prefix}ships.player_id > 3");
db_op_result($debug_query,__LINE__,__FILE__);

if ($debug_query)
{
	$num_to_tow = $debug_query->RecordCount();
	$count = 0;
	TextFlush ( "$num_to_tow players to tow:<br>");
	while (!$debug_query->EOF)
	{
		$row = $debug_query->fields;
		TextFlush ( "...towing $row[character_name] out of $row[sector_id] ...");
		$randplay=mt_rand(0,($sector_list_total-1));
		$newsector = $sector_list[$randplay]['sector_id'];
		TextFlush ( " to sector $newsector.<br>");
		$debug_query1 = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$newsector,cleared_defenses=' ' where ship_id=$row[ship_id]");
		db_op_result($debug_query1,__LINE__,__FILE__);
		$debug_query1->close();

		playerlog($row['player_id'], "LOG0_TOW", "$row[sector_id]|$newsector|$row[max_hull]");
		log_move($row['player_id'],$row['ship_id'],$row['sector_id'],$newsector,$row['class'],$row['cloak'],$row['zone_id']);
		$count++;
		$debug_query->MoveNext();
	}
	$debug_query->close();
	TextFlush ( "$count players towed<br><br>");
}

$debug_query = $db->Execute("SELECT {$db_prefix}players.player_id, COUNT( {$db_prefix}ships.ship_id ) AS total_ships
														FROM {$db_prefix}ships, {$db_prefix}players
														WHERE {$db_prefix}ships.player_id = {$db_prefix}players.player_id
														AND {$db_prefix}players.destroyed = 'N'
														AND {$db_prefix}ships.player_id >3
														GROUP BY {$db_prefix}ships.player_id");
db_op_result($debug_query,__LINE__,__FILE__);

$player_list = "";

while (!$debug_query->EOF)
{
	$row = $debug_query->fields;
	if($row['total_ships'] > 1)
	{
		$player_list .= " $row[player_id],";
	}
	$debug_query->MoveNext();
}
$debug_query->close();

$check_list = "";
if(!empty($player_list))
{
	$check_list = " and {$db_prefix}players.player_id IN (" . AAT_substr($player_list, 0, -1) . ")";
}
else
{
	$check_list = " and {$db_prefix}players.player_id IN (1)";
}

$debug_query = $db->Execute("SELECT {$db_prefix}ships.ship_id, {$db_prefix}players.player_id, {$db_prefix}players.character_name, {$db_prefix}ships.hull, {$db_prefix}ships.cloak, " .
							"{$db_prefix}ships.class, {$db_prefix}ships.sector_id, {$db_prefix}universe.zone_id, {$db_prefix}zones.max_hull " .
							"FROM {$db_prefix}ships, {$db_prefix}universe, {$db_prefix}zones, " .
							"{$db_prefix}players WHERE {$db_prefix}ships.player_id={$db_prefix}players.player_id and " .
							"{$db_prefix}ships.sector_id={$db_prefix}universe.sector_id AND " .
							"{$db_prefix}universe.zone_id={$db_prefix}zones.zone_id AND {$db_prefix}universe.zone_id = 2 and " .
							"{$db_prefix}ships.ship_id={$db_prefix}players.currentship" . $check_list);
db_op_result($debug_query,__LINE__,__FILE__);

if ($debug_query)
{
	$num_to_tow2 = $debug_query->RecordCount();
	$count = 0;
	TextFlush ( "$num_to_tow2 players to tow with stored ships:<br>");
	while (!$debug_query->EOF)
	{
		$row = $debug_query->fields;
		TextFlush ( "...towing $row[character_name] out of $row[sector_id] ...");
		$randplay=mt_rand(0,($sector_list_total-1));
		$newsector = $sector_list[$randplay]['sector_id'];
		TextFlush ( " to sector $newsector.<br>");
		$debug_query1 = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$newsector,cleared_defenses=' ' where ship_id=$row[ship_id]");
		db_op_result($debug_query1,__LINE__,__FILE__);
		$debug_query1->close();

		playerlog($row['player_id'], "LOG0_TOW", "$row[sector_id]|$newsector|$row[max_hull]");
		log_move($row['player_id'],$row['ship_id'],$row['sector_id'],$newsector,$row['class'],$row['cloak'],$row['zone_id']);
		$debug_query->MoveNext();
	}
	$debug_query->close();
}

TextFlush ( "<br>\n");
$multiplier = 0; //no use to run this again

?>
