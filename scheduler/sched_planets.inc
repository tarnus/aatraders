<?php
// 1
// 300
// 2
// 0
// Y
// How often planets will generate commodities, colonists will use organics, dignitaties and spies perform their jobs.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

function PL_playerlog($sid, $log_type, $data = '', $starvation='')
{
	global $db, $db_prefix;

	// write log_entry to the player's log - identified by player's player_id - sid.
	if ($sid != '' && !empty($log_type))
	{
		if($log_type == "LOG7_STARVATION")
		{
			list($sector_id, $amount, $name, $date)= AAT_split ("\|", $data);
			$stamp = date("Y-m-d H:i:s");
			$stamp_old = date("Y-m-d H:i:s", time() - (1 * 24 * 60 * 60)); // One day previous
			$result2 = $db->SelectLimit("SELECT log_id, data from {$db_prefix}logs WHERE time >= '$stamp_old' and player_id=$sid and type='LOG7_STARVATION' and data LIKE '" . $sector_id . "|%' order by log_id DESC", 1);
			$log_id = $result2->fields['log_id'];
			$old_data = $result2->fields['data'];
			if($result2->recordcount() == 0)
			{
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}logs (player_id, type, time, data) VALUES($sid, '$log_type', '$stamp', " . $db->qstr($data) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
			else
			{
				list($old_sector, $old_starvation, $old_name, $old_date)= AAT_split ("\|", $old_data);
				$starvation = $starvation + $old_starvation;
				$data = "$sector_id|" . $starvation . "|$name|" . $old_date;
				$debug_query = $db->Execute("UPDATE {$db_prefix}logs SET time = '$stamp', data = " . $db->qstr($data) . " WHERE log_id = $log_id");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
			}
			$result2->close();
		}
		else
		{
			$stamp = date("Y-m-d H:i:s");
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}logs (player_id, type, time, data) VALUES($sid, '$log_type', '$stamp', " . $db->qstr($data) . ")");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();
		}
	}
}

TextFlush ( "<b>PLANET UPDATE</b><br><br>\n");

// If organics plus org production minus org consumption is less then zero then there is starvation
// So set organics to zero and kill off some colonists

TextFlush ( "Calculating Starvation<br>");

$expostarvation_death_rate = 1 - mypw((1 - $starvation_death_rate ), $multiplier);  
$starvation_list = "";

$starv_log = "SELECT name, owner, sector_id, planet_id, ROUND(colonists * $starvation_death_rate * $expoprod) AS st_value FROM ".                
             "{$db_prefix}planets WHERE (organics + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) " .    
             "* $prate[colonists] * $prate[organics] * prod_organics / 100.0 * $expoprod) - " .
             "(LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $organics_consumption * $expoprod) < 0) and owner != 0";
$debug_query = $db->Execute($starv_log);
db_op_result($debug_query,__LINE__,__FILE__);

while (!$debug_query->EOF)
{
	$info = $debug_query->fields;
	if($info['st_value']>0)
	{
		$starvation_list .= "$info[planet_id],";
		$datestring = date($local_date_full_format);
		PL_playerlog($info['owner'], "LOG7_STARVATION", "$info[sector_id]|" . $info['st_value'] . "|$info[name]|$datestring", $info['st_value']);
	}
	$debug_query->MoveNext();
}
$debug_query->close();
$starvation_list .= "-1";

TextFlush ( "Calculating Ore, Goods, Organics, Energy and Credit Production: Phase 1<br>");

// if consumption of organics is higher than availible then perform starvation update

$planetupdate = "UPDATE {$db_prefix}planets SET organics=0, 
                 colonists = LEAST((colonists - (colonists * $starvation_death_rate * $expoprod) + (colonists * ($colonist_reproduction_rate * (1 - (colonists / ($colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7)))))) * $expoprod)), $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))),
                 ore=ore + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[ore] * ore_planet) * prod_ore / 100.0 * $expoprod, 
				 goods=goods + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[goods] * goods_planet) * prod_goods / 100.0 * $expoprod, 
				 energy=energy + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[energy] * energy_planet) * prod_energy / 100.0 * $expoprod
				 WHERE (organics + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $prate[organics] * prod_organics / 100.0 * $expoprod) - (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $organics_consumption * $expoprod) < 0) and owner != 0";

$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

$cargo_query2 = $db->Execute("SELECT classname, prate from {$db_prefix}class_modules_commodities where cargoport=1 and defaultcargoplanet = 0");
db_op_result($cargo_query2,__LINE__,__FILE__);

while (!$cargo_query2->EOF) 
{
	$cargotype = $cargo_query2->fields['classname'];
	$specialprate = $cargo_query2->fields['prate'];
	TextFlush ( "Calculating " . ucwords($cargotype) . " Production: Phase 2<br>");

	$planetupdate = "UPDATE {$db_prefix}planets SET 
				organics=GREATEST(organics + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * ($prate[organics] * organics_planet) * prod_organics / 100.0 * $expoprod) - (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $organics_consumption * $expoprod), 0), 
			    ore=ore + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[ore] * ore_planet) * prod_ore / 100.0 * $expoprod), 
				goods=goods + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[goods] * goods_planet) * prod_goods / 100.0 * $expoprod), 
				energy=energy + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[energy] * energy_planet) * prod_energy / 100.0 * $expoprod), 
			    colonists= LEAST((colonists + (colonists * ($colonist_reproduction_rate * (1 - (colonists / ($colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7)))))) * $expoprod)), $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))), 
				credits=LEAST(credits + (((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $credits_prate * ((100.0 - prod_special - prod_organics - prod_ore - prod_goods - prod_energy - prod_fighters - prod_torp - prod_research - prod_build) / 100.0) * $expoprod) * (1.0 + ((credits / max_credits) * $production_multiplier))), max_credits), 
			    special_amount=special_amount + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $specialprate * prod_special / 100.0 * $expoprod)" .
					"WHERE " .
                    "special_name = '$cargotype' and " .
                    "(organics + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $prate[organics] * " .
                    "prod_organics / 100.0 * $expoprod) - (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * " .
                    "$organics_consumption * $expoprod) >= 0) and owner != 0";

	$debug_query = $db->Execute($planetupdate);
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query->close();

	$cargo_query2->Movenext();
}
$cargo_query2->close();

TextFlush ( "Calculating Ore, Goods, Organics, Energy and Credit Production: Phase 3<br>");
// if consumption of organics is less than production perform normal update
$planetupdate = "UPDATE {$db_prefix}planets SET 
				organics=GREATEST(organics + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * ($prate[organics] * organics_planet) * prod_organics / 100.0 * $expoprod) - (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $organics_consumption * $expoprod), 0), 
			    ore=ore + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[ore] * ore_planet) * prod_ore / 100.0 * $expoprod), 
				goods=goods + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[goods] * goods_planet) * prod_goods / 100.0 * $expoprod), 
				energy=energy + ((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * ($prate[energy] * energy_planet) * prod_energy / 100.0 * $expoprod), 
			    colonists= LEAST((colonists + (colonists * ($colonist_reproduction_rate * (1 - (colonists / ($colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7)))))) * $expoprod)), $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))), 
				credits=LEAST(credits + (((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $credits_prate * ((100.0 - prod_organics - prod_ore - prod_goods - prod_energy - prod_fighters - prod_torp - prod_research - prod_build) / 100.0) * $expoprod) * (1.0 + ((credits / max_credits) * $production_multiplier))), max_credits) " .
					"WHERE " .
                    "special_name = '' and " .
                    "(organics + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * $prate[organics] * " .
                    "prod_organics / 100.0 * $expoprod) - (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists] * " .
                    "$organics_consumption * $expoprod) >= 0) and owner != 0";

$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

TextFlush ( "Calculating Fighter and Torpedo Production<br>");

$planetupdate = "UPDATE {$db_prefix}planets SET fighters=fighters + " .
                "(LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $prate[Planet_Fighter] * prod_fighters / 100.0 * " .
                "$expoprod, torps=torps + (LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $prate[Planet_Torpedo] * " .
                "prod_torp / 100.0 * $expoprod WHERE owner!=0";

$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

TextFlush ( "Updating Planet Armor<br>");
// Update armor level
$planetupdate = "UPDATE {$db_prefix}planets SET armor =((beams+fighter+sensors+jammer+cloak+shields+torp_launchers)/7),
 ore=GREATEST(ore-(((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $prate[ore] * .05 / 100.0 * $expoprod)),0),
 goods=GREATEST(goods - (((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $prate[goods] * 05 / 100.0 * $expoprod)),0),
 armor_pts=armor_pts+(((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $prate[ore] * 05 / 100.0 * $expoprod)/8)+(((LEAST(colonists, $colonist_limit + ($colonist_tech_add * ((fighter + sensors + beams + torp_launchers + shields + jammer + cloak) / 7))) * $prate[colonists]) * $prate[goods] * 05 / 100.0 * $expoprod)/8)
 where  armor_pts < ((POW($level_factor ,(((beams+fighter+sensors+jammer+cloak+shields+torp_launchers)/7)+5))*10)*$armor_prod_multiplier) and base='Y' and goods >=10000 and ore >= 10000 AND owner!=0";
//echo  $planetupdate;
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

//Deplete armor 
$planetupdate = "UPDATE {$db_prefix}planets SET armor_pts=GREATEST(armor_pts-(armor_pts*.05),1) where base='Y' AND owner!=0 and (goods < 10000 or ore < 10000) ";
//echo  $planetupdate;
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

 //freshen armor points 
$planetupdate = "UPDATE {$db_prefix}planets SET 
 armor_pts=GREATEST(1, ((POW($level_factor ,(((beams+fighter+sensors+jammer+cloak+shields+torp_launchers)/7)+5))*10)*$armor_prod_multiplier))
 where armor_pts > ((POW($level_factor ,(((beams+fighter+sensors+jammer+cloak+shields+torp_launchers)/7)+5))*10)*$armor_prod_multiplier) and owner != 0";
//echo  $planetupdate;
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

TextFlush ( "Safety Check<br>");
//Make sure no planets never go below 0.
$planetupdate = "UPDATE {$db_prefix}planets SET credits=LEAST(GREATEST(credits, 0), max_credits), armor_normal=armor, organics=GREATEST(organics,0), ore=GREATEST(ore,0), goods=GREATEST(goods,0), energy=GREATEST(energy,0), colonists=GREATEST(colonists,0), torps=GREATEST(torps,0), armor_pts=GREATEST(armor_pts,0), fighters=GREATEST(fighters,0) WHERE owner != 0";
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);

$planetupdate = "UPDATE {$db_prefix}planets SET use_age=GREATEST(0, use_age-1) WHERE base='Y' and use_age > 0 and owner != 0";
$debug_query = $db->Execute($planetupdate);
db_op_result($debug_query,__LINE__,__FILE__);
$debug_query->close();

TextFlush ( "Planets updated ($multiplier times).<BR><BR>\n");
$multiplier = 0;

?>