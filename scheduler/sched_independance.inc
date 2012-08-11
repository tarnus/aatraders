<?php
// 1
// 1300
// 1440
// 0
// Y
// How often planets will try to become independent.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/insert_news.inc");
include ("globals/calc_ownership.inc");
include ("globals/artifacts_move.inc");

TextFlush ( "<b>Planetary Independance</b><br><br>");

$debug_query = $db->Execute("SELECT count(planet_id) as planetcount, owner from {$db_prefix}planets WHERE owner != 0 group by owner");
db_op_result($debug_query,__LINE__,__FILE__);

while (!$debug_query->EOF)
{
	$ownerid = $debug_query->fields['owner'];
	$planetcount[$ownerid] = $debug_query->fields['planetcount'];
	$debug_query->MoveNext();
}
$debug_query->close();

$lastvisited = strtotime(date("Y-m-d H:i:s")) - ($last_visited_days * 86400);

$debug_query = $db->Execute("SELECT * from {$db_prefix}planets WHERE owner != '0' and owner != '2' and owner != '3'");
db_op_result($debug_query,__LINE__,__FILE__);

$reccount = $debug_query->RecordCount();
$totalupdates = 0;
$totalindi = 0;

if ($debug_query && $reccount > 0)
{
	while (!$debug_query->EOF)
	{
		$targetinfo = $debug_query->fields;
		$averagetechlvl = ($targetinfo['fighter'] + $targetinfo['sensors'] + $targetinfo['beams'] + $targetinfo['torp_launchers'] + $targetinfo['shields'] + $targetinfo['jammer'] + $targetinfo['cloak']) / 7;
		$toomanyplanets = ($planetcount[$targetinfo['owner']] <= 50) ? 2 : mt_rand(1, max(1, 20 - floor($planetcount[$targetinfo['owner']] / 6)));

		$overage = isset($planetary_overage) ? $planetary_overage : 2.5;
		$substraction = floor(($last_visited_days * 86400) / 65);
		$scaling = max(0, floor(($planetcount[$targetinfo['owner']] - 50) / $overage));
		$newvisited = $lastvisited - strtotime($targetinfo['last_visited']);

// echo "<br>\$toomanyplanets($toomanyplanets) < 2 -- \$newvisited($newvisited) > 0 -- \$scaling = $scaling -- \$substraction = $substraction -- scaledvisited = " . ($newvisited + ($substraction * $scaling)) . " -- planettotals = " . $planetcount[$targetinfo['owner']] . "<br>";

		if ($targetinfo['base'] == "N" || ($toomanyplanets < 2 && ($newvisited + ($substraction * $scaling)) > 0))
		{
			if($targetinfo['base'] == "N")
			{
				$randomlevel = 20;
				$averagetechlvl2 = "Non-Based - Avg Tech = ".$averagetechlvl." in sector ".$targetinfo['sector_id'];
			}
			else
			{
				$randomlevel = 1;
				$basedav = ($baseav + $averagetechlvl)/2;
				$averagetechlvl2 = "Based - Avg Tech = " . $averagetechlvl . " in sector " . $targetinfo['sector_id'];
			}

			if($newvisited > 0)
			{
				$randomlevel += floor($newvisited / 43200);
			}

			// add 1 percentage point for every ?? planets over the 50 planet safe zone
			$randomlevel += max(0, floor(($planetcount[$targetinfo['owner']] - 50) / $overage));

			$random_pick = mt_rand(0, 100);
			TextFlush ( "Rec: $totalrec, Picked: $random_pick, RandLvl: $randomlevel (" . floor($newvisited / 43200) . "), avgtech: $averagetechlvl, planetoverage: " . max(0, floor(($planetcount[$targetinfo['owner']] - 50) / $overage)) . "(" . $planetcount[$targetinfo['owner']] . ")<br>");
			if($random_pick < $randomlevel)
			{
				$planetcount[$targetinfo['owner']] -= 1;
				TextFlush ( "Planet $targetinfo[planet_id] ($targetinfo[name]) (Owner: $targetinfo[owner], Planet Count: " . $planetcount[$targetinfo['owner']] . ") became independant.<BR>");
				if($targetinfo['base'] == "N")
				{
					$totalnon++;
				}
				else
				{
					$totalbased++;
					TextFlush ( "----- $averagetechlvl2<br><br>");
				}

				$indiexperience[$totalupdates] = ($targetinfo['base'] == 'N') ? 0 : $independent_planet;
				$indiplanet[$totalupdates] = $targetinfo['planet_id'];
				$indiowner[$totalupdates] = $targetinfo['owner'];
				$indisector[$totalupdates] = $targetinfo['sector_id'];
				$indiadmin[$totalupdates] = "$targetinfo[name]|$targetinfo[planet_id]|$targetinfo[sector_id]|$averagetechlvl|$targetinfo[owner]";
				$indycomp[$totalupdates] = floor($targetinfo['fighter'] * (rand(75, 100) * 0.01));
				$indysens[$totalupdates] = floor($targetinfo['sensors'] * (rand(75, 100) * 0.01));
				$indybeam[$totalupdates] = floor($targetinfo['beams'] * (rand(75, 100) * 0.01));
				$indytorp[$totalupdates] = floor($targetinfo['torp_launchers'] * (rand(75, 100) * 0.01));
				$indyshield[$totalupdates] = floor($targetinfo['shields'] * (rand(75, 100) * 0.01));
				$indyjammer[$totalupdates] = floor($targetinfo['jammer'] * (rand(75, 100) * 0.01));
				$indycloak[$totalupdates] = floor($targetinfo['cloak'] * (rand(75, 100) * 0.01));
				$totalupdates++;
			}
			else
			{
				if($targetinfo['base'] == "N")
				{
					$totalnon2++;
				}
				else
				{
					$totalbased2++;
				}
			}
		}
		$debug_query->MoveNext();
		$totalrec++;
	}
	$debug_query->close();

	if($totalupdates != 0)
	{
		$lastvisited_date = date("Y-m-d H:i:s");
		for($indi = 0; $indi < $totalupdates; $indi++)
		{
			$debug_query = $db->Execute("SELECT * from {$db_prefix}ships WHERE planet_id=$indiplanet[$indi] and on_planet='Y'");
			db_op_result($debug_query,__LINE__,__FILE__);
			if($debug_query->RecordCount() == 0)
			{
				$debug_query2 = $db->Execute("UPDATE {$db_prefix}players SET planets_lost=planets_lost+1, experience=GREATEST(experience + $indiexperience[$indi], 0) WHERE player_id=$indiowner[$indi]");
				db_op_result($debug_query2,__LINE__,__FILE__);
				$debug_query2 = $db->Execute("DELETE from {$db_prefix}dignitary WHERE planet_id = $indiplanet[$indi]");
				db_op_result($debug_query2,__LINE__,__FILE__);
				$debug_query2 = $db->Execute("UPDATE {$db_prefix}planets SET last_visited='$lastvisited_date', cargo_hull = 0, cargo_power = 0, owner = 2, team=0, fighter=$indycomp[$indi], sensors=$indysens[$indi], beams=$indybeam[$indi] ,torp_launchers=$indytorp[$indi] ,shields=$indyshield[$indi] ,jammer=$indyjammer[$indi] ,cloak=$indycloak[$indi] WHERE planet_id = $indiplanet[$indi]");
				db_op_result($debug_query2,__LINE__,__FILE__);
				$debug_query2 = $db->Execute("delete from {$db_prefix}autotrades WHERE planet_id=$indiplanet[$indi]");
				db_op_result($debug_query2,__LINE__,__FILE__);
				change_planet_ownership($indiplanet[$indi], $indiowner[$indi], 2);
				calc_ownership($indisector[$indi]);
				capture_planet_ships(2, $indiplanet[$indi]);
				adminlog("LOG0_ADMIN_PLANETIND", $indiadmin[$indi]);
				$totalindi++;
			}
			$debug_query->close();
		}
	}
}

TextFlush ("<br>Based: $totalbased - $basedav<br>Non-Based: $totalnon");
TextFlush ("<br>Based bypassed: $totalbased2<br>Non-Based bypassed: $totalnon2");
TextFlush ( "<br>");

if($totalindi > 0)
{
	insert_news($totalindi, 1, "indi");
}

$lastvisited = date("Y-m-d H:i:s", strtotime(date("Y-m-d H:i:s")) - ($indy_planet_purge * 86400));

$debug_query = $db->Execute("SELECT * from {$db_prefix}planets WHERE owner = '2' and last_visited < '$lastvisited'");
db_op_result($debug_query,__LINE__,__FILE__);

$reccount = $debug_query->RecordCount();
$totalpurged = 0;

if ($debug_query && $reccount > 0)
{
	while (!$debug_query->EOF)
	{
		if(mt_rand(1,100) < 20)
		{
			$planetinfo = $debug_query->fields;
			if ($enable_spies)
			{
				$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}planets.sector_id FROM {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id = {$db_prefix}planets.planet_id WHERE {$db_prefix}spies.planet_id = '$planet_id' ");
				while (!$res->EOF)
				{
					$owners = $res->fields;
					playerlog($owners['owner_id'], "LOG2_SPY_CATACLYSM", "$owners[spy_id]|$owners[name]|$owners[sector_id]");
					$res->MoveNext();
				}
				$res->close();
				$db->Execute("DELETE FROM {$db_prefix}spies WHERE planet_id = '$planetinfo[planet_id]' ");
			}

			$debug_query2 = $db->Execute("DELETE from {$db_prefix}planets where planet_id=$planetinfo[planet_id]");
			db_op_result($debug_query2,__LINE__,__FILE__);
			$debug_query2 = $db->Execute("DELETE from {$db_prefix}dignitary where planet_id=$planetinfo[planet_id]");
			db_op_result($debug_query2,__LINE__,__FILE__);
			$debug_query2=$db->Execute("UPDATE {$db_prefix}ships SET on_planet='N', planet_id=0, storage_planet_id = 0 WHERE planet_id=$planetinfo[planet_id] and on_planet='Y'");
			db_op_result($debug_query2,__LINE__,__FILE__);

			$debug_query2 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE storage_planet_id = $planetinfo[planet_id]");
			db_op_result($debug_query2,__LINE__,__FILE__);
			if ($debug_query2 > 0)
			{
				while (!$debug_query2->EOF)
				{
					$ship_id = $debug_query2->fields['ship_id'];
					$delete_query3 = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id = $ship_id");
					db_op_result($delete_query3,__LINE__,__FILE__);
					$delete_query3 = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id = $ship_id");
					db_op_result($delete_query3,__LINE__,__FILE__);
					$delete_query3 = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id = $ship_id");
					db_op_result($delete_query3,__LINE__,__FILE__);
					$debug_query2->MoveNext();
				}
			}
			$debug_query2->close();

			calc_ownership($planetinfo['sector_id']);
			artifacts_move($planetinfo['planet_id'], 0, 0);
			TextFlush ("<br>Independent Planet Purged: " . $planetinfo['name']);
			$averagetechlvl = ($planetinfo['fighter'] + $planetinfo['sensors'] + $planetinfo['beams'] + $planetinfo['torp_launchers'] + $planetinfo['shields'] + $planetinfo['jammer'] + $planetinfo['cloak']) / 7;
			$indipurge = "$planetinfo[name]|$planetinfo[planet_id]|$planetinfo[sector_id]|$averagetechlvl|$planetinfo[owner]";
			adminlog("LOG0_ADMIN_INDYPURGE", $indipurge);
			$totalpurged++;
		}
		$debug_query->MoveNext();
	}
	$debug_query->close();
}
TextFlush ("<br>Total Independent Planets Purged: $totalpurged");

$lastvisited = date("Y-m-d H:i:s", strtotime(date("Y-m-d H:i:s")) - ($indy_planet_purge * 86400));

$debug_query = $db->Execute("SELECT * from {$db_prefix}planets WHERE owner = '0' and creation_date < '$lastvisited'");
db_op_result($debug_query,__LINE__,__FILE__);

$reccount = $debug_query->RecordCount();
$totalpurged = 0;

if ($debug_query && $reccount > 0)
{
	while (!$debug_query->EOF)
	{
		if(mt_rand(1,100) < 20)
		{
			$planetinfo = $debug_query->fields;
			$debug_query2 = $db->Execute("DELETE from {$db_prefix}planets where planet_id=$planetinfo[planet_id]");
			db_op_result($debug_query2,__LINE__,__FILE__);

			artifacts_move($planetinfo['planet_id'], 0, 0);
			TextFlush ("<br>Never Owned Planet Purged: " . $planetinfo['name']);
			$averagetechlvl = ($planetinfo['fighter'] + $planetinfo['sensors'] + $planetinfo['beams'] + $planetinfo['torp_launchers'] + $planetinfo['shields'] + $planetinfo['jammer'] + $planetinfo['cloak']) / 7;
			$indipurge = "$planetinfo[name]|$planetinfo[planet_id]|$planetinfo[sector_id]|$averagetechlvl|$planetinfo[creation_date]";
			adminlog("LOG0_ADMIN_NEVEROWNEDPURGE", $indipurge);
			$totalpurged++;
		}
		$debug_query->MoveNext();
	}
	$debug_query->close();
}
TextFlush ("<br>Total Never Owned Planets Purged: $totalpurged");
$new_ticks = 1440 + (mt_rand(0, 288) * 5);
TextFlush ("<br><br>Next Tick: $new_ticks<br><br>");
$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET ticks_full=$new_ticks WHERE sched_file='sched_independance.inc'");
db_op_result($debug_query,__LINE__,__FILE__);

$multiplier = 0;
?>
