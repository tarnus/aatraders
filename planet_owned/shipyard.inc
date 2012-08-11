<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: shipyard.inc

include ("languages/$langdir/lang_shipyard.inc");
include ("languages/$langdir/lang_report.inc");

// Create dropdowns when called
function dropdown($element_name,$current_value, $max_value)
{
	$i = $current_value;
	$dropdownvar = "<select size='1' name='$element_name'";
	$dropdownvar = "$dropdownvar ONCHANGE=\"countTotal()\">\n";
	while ($i <= $max_value)
	{
		if ($current_value == $i)
		{
			$dropdownvar = "$dropdownvar		<option value='$i' selected>$i</option>\n";
		}
		else
		{
			$dropdownvar = "$dropdownvar		<option value='$i'>$i</option>\n";
		}
	 $i++;
	}
	$dropdownvar = "$dropdownvar		 </select>\n";
	return $dropdownvar;
}

$title = $l_shipyard_title;

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id=$sectorinfo[zone_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$zoneinfo = $debug_query->fields;
$debug_query->close();
$template_object->assign("planet_id",$planet_id);
$template_object->assign("l_clickme",$l_clickme);
$template_object->assign("l_toplanetmenu",$l_toplanetmenu);

/*  Commented out for fed changes 4-13-2010
$res2 = $db->Execute("SELECT SUM(amount) as total_bounty FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1) AND bounty_on = $shipinfo[player_id]");
if ($res2)
{
	$bty = $res2->fields;
	if ($bty['total_bounty'] > 0)
	{
		if ($pay <> 1)
		{
			$l_port_bounty2 = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_bounty2);
			$template_object->assign("l_port_bounty", $l_port_bounty);
			$template_object->assign("l_port_bounty2", $l_port_bounty2);
			$template_object->assign("l_by_placebounty", $l_by_placebounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."planet_owned/shipyardbounty.tpl");
			include ("footer.php");
			die();
		}
		else
		{
			if ($playerinfo['credits'] < $bty['total_bounty'])
			{
				$l_port_btynotenough = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_btynotenough);
				$template_object->assign("error_msg", $l_port_btynotenough);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/shipyarddie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$bty[total_bounty] WHERE player_id = $shipinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE from {$db_prefix}bounty WHERE bounty_on = $shipinfo[player_id] AND (placed_by = 3 or placed_by = 1)");
				db_op_result($debug_query,__LINE__,__FILE__);

				$template_object->assign("error_msg", $l_port_bountypaid);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."planet_owned/shipyarddie.tpl");
				include ("footer.php");
				die();
			}
		}
	}
}
$res2->close();
*/
if($zoneinfo['zone_id'] != 3){
	$alliancefactor = 1;
}

$res = $db->Execute("SELECT * FROM {$db_prefix}ship_types WHERE buyable = 'Y' order by type_id");
while (!$res->EOF)
{
	$ships[] = $res->fields;
	$res->MoveNext();
}
$res->close();

$lastship = end($ships);

$price_modifier_base = explode("|", $playerinfo['ship_losses']);

for($i = 0; $i < count($price_modifier_base); $i++){
	$items = explode("-", $price_modifier_base[$i]);
	$element = $items[0];
	$price_modifier[$element] = $items[1];
	if($price_modifier[$element] < 1)
		$price_modifier[$element] = 0;
}

$res = $db->Execute("SELECT type_id FROM {$db_prefix}ship_types WHERE buyable = 'Y'");
$type_count = $res->RecordCount(); 

$new_losses = "";
for($i = 0; $i < $type_count; $i++){
	$element = $res->fields['type_id'];
	if($price_modifier[$element] < 1)
		$price_modifier[$element] = 0;
	$res->MoveNext();
}
$res->close();

$template_object->assign("l_ship_welcome", $l_ship_welcome);
$template_object->assign("color_line", $color_line);
$template_object->assign("l_ship_class", $l_ship_class);
$template_object->assign("l_ship_properties", $l_ship_properties);

$first = 1;

$countship = 0;

foreach ($ships as $curship)
{
	if (!isset($_GET['stype']))
	{
		$_GET['stype'] = $curship['type_id'];
	}
	$currentshipid[$countship] = $curship['type_id'];
	$currentshipimage[$countship] = "templates/".$templatename."images/$curship[image]";
	$currentshipname[$countship] = $curship['name'];
	$currentshipbasehull[$countship] = $curship['basehull'];

	if ($curship['type_id'] == $shipinfo['class'])
	{
		$currentship[$countship] = $l_ship_current;
	}else{
		$currentship[$countship] = "";
	}

	$res2 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE class = ". $curship['type_id']." and ship_id!=".$shipinfo['ship_id']."  and player_id=".$shipinfo['player_id']." and storage_planet_id='$planet_id'");
	$totalstored = $res2->RecordCount();
	$res2->close();
	if($totalstored != 0)
	{
		$storedship[$countship] = $l_ship_stored . " " . $totalstored;
	}
	else
	{
		$storedship[$countship] = '';
	}

	if ($first == 1)
	{
		$first = 0;

		if (isset($_GET['stype']))
		{
			//get info for selected ship class
			foreach ($ships as $testship)
			{
				if ($testship['type_id'] == $_GET['stype'])
				{
					$sship = $testship;
					break;
				}
			}
			$ship_price = ($price_modifier[$_GET['stype']] * ($sship['cost_tobuild'] * ($ship_cost_increase / 100))) + $sship['cost_tobuild'];

			$storageflag=0;
			$res2 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE class = ". $_GET['stype']." and ship_id!=".$shipinfo['ship_id']."  and player_id=".$shipinfo['player_id']." and storage_planet_id='$planet_id'");
			$totships = $res2->RecordCount(); 
			if($totships != 0)
			{
				$storageflag=1;
				$shull_bars = array();
				$sengines_bars = array();
				$sfighter_bars = array();
				$ssensors_bars = array();
				$sarmor_bars = array();
				$sshields_bars = array();
				$sbeams_bars = array();
				$storp_launchers_bars = array();
				$scloak_bars = array();
				$secm_bars = array();
				$stechvalue = array();
				$ships2id = array();
				$average_stats_max = floor(($sship['maxhull'] + $sship['maxcloak'] + $sship['maxsensors'] + $sship['maxpower'] + $sship['maxengines'] + $sship['maxfighter'] + $sship['maxarmor'] + $sship['maxshields'] + $sship['maxbeams'] + $sship['maxtorp_launchers'] + $sship['maxecm'] ) / 11 );

				for($loop = 0; $loop < $totships; $loop++)
				{
					$ships2 = $res2->fields;
					$shull_bars[] = MakeBars($ships2['hull'], $sship['maxhull'], "normal");
					$sengines_bars[] = MakeBars($ships2['engines'], $sship['maxengines'], "normal");
					$spower_bars[] = MakeBars($ships2['power'], $sship['maxpower'], "normal");
					$sfighter_bars[] = MakeBars($ships2['fighter'], $sship['maxfighter'], "normal");
					$ssensors_bars[] = MakeBars($ships2['sensors'], $sship['maxsensors'], "normal");
					$sarmor_bars[] = MakeBars($ships2['armor'], $sship['maxarmor'], "normal");
					$sshields_bars[] = MakeBars($ships2['shields'], $sship['maxshields'], "normal");
					$sbeams_bars[] = MakeBars($ships2['beams'], $sship['maxbeams'], "normal");
					$storp_launchers_bars[] = MakeBars($ships2['torp_launchers'], $sship['maxtorp_launchers'], "normal");
					$scloak_bars[] = MakeBars($ships2['cloak'], $sship['maxcloak'], "normal");
					$secm_bars[] = MakeBars($ships2['ecm'], $sship['maxecm'], "normal");

					$calc_nhull = phpChangeDelta($sship['minhull'], 0);
					$calc_nengines = phpChangeDelta($sship['minengines'], 0);
					$calc_npower = phpChangeDelta($sship['minpower'], 0);
					$calc_nfighter = phpChangeDelta($sship['minfighter'], 0);
					$calc_nsensors = phpChangeDelta($sship['minsensors'], 0);
					$calc_nbeams = phpChangeDelta($sship['minbeams'], 0);
					$calc_ntorp_launchers = phpChangeDelta($sship['mintorp_launchers'], 0);
					$calc_nshields = phpChangeDelta($sship['minshields'], 0);
					$calc_narmor = phpChangeDelta($sship['minarmor'], 0);
					$calc_ncloak = phpChangeDelta($sship['mincloak'], 0);
					$calc_necm = phpChangeDelta($sship['minecm'], 0);

					$average_stats[] = floor(($ships2['hull_normal'] + $ships2['cloak_normal'] + $ships2['sensors_normal'] + $ships2['power_normal'] + $ships2['engines_normal'] + $ships2['fighter_normal'] + $ships2['armor_normal'] + $ships2['shields_normal'] + $ships2['beams_normal'] + $ships2['torp_launchers_normal'] + $ships2['ecm_normal'] ) / 11 );
					$average_current_stats[] = floor(($ships2['hull'] + $ships2['cloak'] + $ships2['sensors'] + $ships2['power'] + $ships2['engines'] + $ships2['fighter'] + $ships2['armor'] + $ships2['shields'] + $ships2['beams'] + $ships2['torp_launchers'] + $ships2['ecm'] ) / 11 );

					$ships2id[] = $ships2['ship_id'];

					$stechvalue[] = $calc_nhull+$calc_nengines+$calc_npower+$calc_nfighter+$calc_nsensors+$calc_nbeams+$calc_ntorp_launchers+$calc_nshields+$calc_narmor+$calc_ncloak+$calc_necm;
					$res2->MoveNext();
				}
				$template_object->assign("l_ship_averagemaxtech", $l_ship_averagemaxtech);
				$template_object->assign("l_ship_averagenormaltech", $l_ship_averagenormaltech);
				$template_object->assign("l_ship_averagecurrenttech", $l_ship_averagecurrenttech);
				$template_object->assign("average_stats_max", $average_stats_max);
				$template_object->assign("average_stats", $average_stats);
				$template_object->assign("average_current_stats", $average_current_stats);
				$template_object->assign("totalshipsstored", $totships);
				$template_object->assign("currentstorage", "1");
				$template_object->assign("ships2id",$ships2id);

			}else{
				$ship_hull_dropdown = dropdown("hull_upgrade",$sship['minhull'], $sship['maxhull']);
				$template_object->assign("ship_hull_dropdown", $ship_hull_dropdown);
				$ship_engines_dropdown = dropdown("engine_upgrade",$sship['minengines'], $sship['maxengines']);
				$template_object->assign("ship_engines_dropdown", $ship_engines_dropdown);
				$ship_power_dropdown = dropdown("power_upgrade",$sship['minpower'], $sship['maxpower']);
				$template_object->assign("ship_power_dropdown", $ship_power_dropdown);
				$ship_fighter_dropdown = dropdown("fighter_upgrade",$sship['minfighter'], $sship['maxfighter']);
				$template_object->assign("ship_fighter_dropdown", $ship_fighter_dropdown);
				$ship_sensors_dropdown = dropdown("sensors_upgrade",$sship['minsensors'], $sship['maxsensors']);
				$template_object->assign("ship_sensors_dropdown", $ship_sensors_dropdown);
				$ship_armor_dropdown = dropdown("armor_upgrade",$sship['minarmor'], $sship['maxarmor']);
				$template_object->assign("ship_armor_dropdown", $ship_armor_dropdown);
				$ship_shields_dropdown = dropdown("shields_upgrade",$sship['minshields'], $sship['maxshields']);
				$template_object->assign("ship_shields_dropdown", $ship_shields_dropdown);
				$ship_beams_dropdown = dropdown("beams_upgrade",$sship['minbeams'], $sship['maxbeams']);
				$template_object->assign("ship_beams_dropdown", $ship_beams_dropdown);
				$ship_torp_launchers_dropdown = dropdown("torp_launchers_upgrade",$sship['mintorp_launchers'], $sship['maxtorp_launchers']);				
				$template_object->assign("ship_torp_launchers_dropdown", $ship_torp_launchers_dropdown);
				$ship_cloak_dropdown = dropdown("cloak_upgrade",$sship['mincloak'], $sship['maxcloak']);
				$template_object->assign("ship_cloak_dropdown", $ship_cloak_dropdown);
				$ship_ecm_dropdown = dropdown("ecm_upgrade",$sship['minecm'], $sship['maxecm']);
				$template_object->assign("ship_ecm_dropdown", $ship_ecm_dropdown);
				$template_object->assign("upgrade_cost", $upgrade_cost);
				$template_object->assign("alliancefactor", $alliancefactor);
				$template_object->assign("upgrade_factor", $upgrade_factor);
				$template_object->assign("player_credits", $playerinfo[credits]);
				$template_object->assign("l_no_credits", $l_no_credits);
				$hull_bars = MakeBars($sship['maxhull'], $max_tech_level, "normal");
				$engines_bars = MakeBars($sship['maxengines'], $max_tech_level, "normal");
				$power_bars = MakeBars($sship['maxpower'], $max_tech_level, "normal");
				$fighter_bars = MakeBars($sship['maxfighter'], $max_tech_level, "normal");
				$sensors_bars = MakeBars($sship['maxsensors'], $max_tech_level, "normal");
				$armor_bars = MakeBars($sship['maxarmor'], $max_tech_level, "normal");
				$shields_bars = MakeBars($sship['maxshields'], $max_tech_level, "normal");
				$beams_bars = MakeBars($sship['maxbeams'], $max_tech_level, "normal");
				$torp_launchers_bars = MakeBars($sship['maxtorp_launchers'], $max_tech_level, "normal");
				$cloak_bars = MakeBars($sship['maxcloak'], $max_tech_level, "normal");
				$ecm_bars = MakeBars($sship['maxecm'], $max_tech_level, "normal");

				$calc_nhull = phpChangeDelta($sship['minhull'], 0);
				$calc_nengines = phpChangeDelta($sship['minengines'], 0);
				$calc_npower = phpChangeDelta($sship['minpower'], 0);
				$calc_nfighter = phpChangeDelta($sship['minfighter'], 0);
				$calc_nsensors = phpChangeDelta($sship['minsensors'], 0);
				$calc_nbeams = phpChangeDelta($sship['minbeams'], 0);
				$calc_ntorp_launchers = phpChangeDelta($sship['mintorp_launchers'], 0);
				$calc_nshields = phpChangeDelta($sship['minshields'], 0);
				$calc_narmor = phpChangeDelta($sship['minarmor'], 0);
				$calc_ncloak = phpChangeDelta($sship['mincloak'], 0);
				$calc_necm = phpChangeDelta($sship['minecm'], 0);

				$techvalue = $calc_nhull+$calc_nengines+$calc_npower+$calc_nfighter+$calc_nsensors+$calc_nbeams+$calc_ntorp_launchers+$calc_nshields+$calc_narmor+$calc_ncloak+$calc_necm;
				$template_object->assign("currentstorage", "0");
			}
			$res2->close();
			$template_object->assign("sship_img", "templates/".$templatename."images/$sship[image]");
			$template_object->assign("name", $sship['name']);
			$template_object->assign("description", $sship['description']);
		}
	}
	$countship++;
}

$template_object->assign("countship", $countship);
$template_object->assign("currentshipid", $currentshipid);
$template_object->assign("currentshipimage", $currentshipimage);
$template_object->assign("currentshipname", $currentshipname);
$template_object->assign("currentshipbasehull", $currentshipbasehull);
$template_object->assign("l_ship_basehull",$l_ship_basehull);
$template_object->assign("currentship", $currentship);
$template_object->assign("storedship", $storedship);

$template_object->assign("sship_minhull", $sship['minhull']);
$template_object->assign("sship_maxhull", $sship['maxhull']);
$template_object->assign("l_hull", $l_hull);
$template_object->assign("hull_bars", $hull_bars);
$template_object->assign("shull_bars", $shull_bars);
$template_object->assign("sship_minengines", $sship['minengines']);
$template_object->assign("sship_maxengines", $sship['maxengines']);
$template_object->assign("l_engines", $l_engines);
$template_object->assign("engines_bars", $engines_bars);
$template_object->assign("sengines_bars", $sengines_bars);
$template_object->assign("sship_minpower", $sship['minpower']);
$template_object->assign("sship_maxpower", $sship['maxpower']);
$template_object->assign("l_power", $l_power);
$template_object->assign("power_bars", $power_bars);
$template_object->assign("spower_bars", $spower_bars);
$template_object->assign("sship_minfighter", $sship['minfighter']);
$template_object->assign("sship_maxfighter", $sship['maxfighter']);
$template_object->assign("l_fighter", $l_fighter);
$template_object->assign("fighter_bars", $fighter_bars);
$template_object->assign("sfighter_bars", $sfighter_bars);
$template_object->assign("sship_minsensors", $sship['minsensors']);
$template_object->assign("sship_maxsensors", $sship['maxsensors']);
$template_object->assign("l_sensors", $l_sensors);
$template_object->assign("sensors_bars", $sensors_bars);
$template_object->assign("ssensors_bars", $ssensors_bars);
$template_object->assign("sship_minarmor", $sship['minarmor']);
$template_object->assign("sship_maxarmor", $sship['maxarmor']);
$template_object->assign("l_armor", $l_armor);
$template_object->assign("armor_bars", $armor_bars);
$template_object->assign("sarmor_bars", $sarmor_bars);
$template_object->assign("sship_minshields", $sship['minshields']);
$template_object->assign("sship_maxshields", $sship['maxshields']);
$template_object->assign("l_shields", $l_shields);
$template_object->assign("shields_bars", $shields_bars);
$template_object->assign("sshields_bars", $sshields_bars);
$template_object->assign("sship_minbeams", $sship['minbeams']);
$template_object->assign("sship_maxbeams", $sship['maxbeams']);
$template_object->assign("l_beams", $l_beams);
$template_object->assign("beams_bars", $beams_bars);
$template_object->assign("sbeams_bars", $sbeams_bars);
$template_object->assign("sship_mintorp_launchers", $sship['mintorp_launchers']);
$template_object->assign("sship_maxtorp_launchers", $sship['maxtorp_launchers']);
$template_object->assign("l_torp_launch", $l_torp_launch);
$template_object->assign("torp_launchers_bars", $torp_launchers_bars);
$template_object->assign("storp_launchers_bars", $storp_launchers_bars);
$template_object->assign("sship_mincloak", $sship['mincloak']);
$template_object->assign("sship_maxcloak", $sship['maxcloak']);
$template_object->assign("l_cloak", $l_cloak);
$template_object->assign("cloak_bars", $cloak_bars);
$template_object->assign("scloak_bars", $scloak_bars);
$template_object->assign("sship_minecm", $sship['minecm']);
$template_object->assign("sship_maxecm", $sship['maxecm']);
$template_object->assign("l_ecm", $l_ecm);
$template_object->assign("ecm_bars", $ecm_bars);
$template_object->assign("secm_bars", $secm_bars);
$template_object->assign("newshipvalue", NUMBER(($techvalue + $ship_price) * $alliancefactor));
$template_object->assign("newshipvalue1", ($techvalue + $ship_price) * $alliancefactor);
$template_object->assign("sship_turnstobuild", NUMBER($sship['turnstobuild']));


$template_object->assign("stype",$_GET['stype']);
$template_object->assign("shipinfo_class", $shipinfo['class']);
$template_object->assign("shipsid",$shipinfo['ship_id']);

$template_object->assign("l_ship_outstorage",$l_ship_outstorage);
$template_object->assign("l_ship_storagecost",$l_ship_storagecost);
$template_object->assign("l_ship_storagewarn",$l_ship_storagewarn);
$template_object->assign("l_ship_levels",$l_ship_levels);
$template_object->assign("l_ship_min",$l_ship_min);
$template_object->assign("l_ship_max",$l_ship_max);
$template_object->assign("l_ship_price",$l_ship_price);
$template_object->assign("l_ship_turns",$l_ship_turns);
$template_object->assign("l_ship_purchase",$l_ship_purchase);
$template_object->assign("title",$title);
$template_object->assign("gotomain", $l_global_mmenu);

$template_object->display($templatename."planet_owned/shipyard.tpl");

include ("footer.php");
die();
?>
