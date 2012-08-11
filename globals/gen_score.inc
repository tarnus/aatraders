<?php
include ("globals/player_insignia_name.inc");
include ("globals/insert_news.inc");

if (!function_exists('gen_score')) {
	function gen_score($sid)
	{
		if ($sid != '')
		{
			global $dev_emerwarp_price, $dev_warpedit_price;
			global $dev_minedeflector_price, $dev_escapepod_price,$dev_nova_price, $dev_fuelscoop_price;
			global $fighter_price, $torpedo_price, $armor_price, $colonist_price;
			global $base_ore, $base_goods, $base_organics, $base_credits, $torpedo_price, $fighter_price;
			global $ore_price, $organics_price, $goods_price, $energy_price, $dig_price, $dev_probe;
			global $upgrade_cost, $upgrade_factor, $planet_SD_upgrade_factor, $planet_upgrade_factor, $cargotype;
			global $db, $db_prefix;
			global $spy_price; // Used by spies.

			$score="";
			$calc_hull = "SUM(exp(hull * log(GREATEST($upgrade_factor, 1))))";
			$calc_engines = "SUM(exp(engines * log(GREATEST($upgrade_factor, 1))))";
			$calc_power = "SUM(exp(power * log(GREATEST($upgrade_factor, 1))))";
			$calc_fighter = "SUM(exp(fighter * log(GREATEST($upgrade_factor, 1))))";
			$calc_sensors = "SUM(exp(sensors * log(GREATEST($upgrade_factor, 1))))";
			$calc_beams = "SUM(exp(beams * log(GREATEST($upgrade_factor, 1))))";
			$calc_torp_launchers = "SUM(exp(torp_launchers * log(GREATEST($upgrade_factor, 1))))";
			$calc_shields = "SUM(exp(shields * log(GREATEST($upgrade_factor, 1))))";
			$calc_armor = "SUM(exp(armor * log(GREATEST($upgrade_factor, 1))))";
			$calc_cloak = "SUM(exp(cloak * log(GREATEST($upgrade_factor, 1))))";
			$calc_ecm = "SUM(exp(ecm * log(GREATEST($upgrade_factor, 1))))";
			$calc_levels = "($calc_hull + $calc_engines + $calc_power + $calc_fighter + $calc_sensors + $calc_beams + $calc_torp_launchers + $calc_shields + $calc_armor + $calc_cloak + $calc_ecm) * $upgrade_cost";

			$calc_ship = '';
			$calc_planets = '';

			$cargo_query = $db->Execute("SELECT classname, price from {$db_prefix}class_modules_commodities where defaultcargoplanet=1");
			db_op_result($cargo_query,__LINE__,__FILE__);
			while (!$cargo_query->EOF) 
			{
				$cargotype = $cargo_query->fields['classname'];
				$cargoprice = $cargo_query->fields['price'];
				$calc_planets .= " + (SUM(" . $cargotype . ") * " . $cargoprice . ")";
				$cargo_query->Movenext();
			}

			$calc_ship_equip = " (SUM(torps) * $torpedo_price) + (SUM(armor_pts) * $armor_price) + (SUM(fighters) * $fighter_price) ";

			$calc_planet_defense = "(SUM(fighters) * $fighter_price) + (SUM(torps) * $torpedo_price) + SUM(if (base='Y', $base_credits, 0))";
			$calc_planet_credits = "SUM(credits) + SUM(hidden_credits)";

			$calc_planet_fighter = "SUM(exp(fighter * log(GREATEST($planet_upgrade_factor, 1))))";
			$calc_planet_sensors = "SUM(exp(sensors * log(GREATEST($planet_upgrade_factor, 1))))";
			$calc_planet_beams = "SUM(exp(beams * log(GREATEST($planet_upgrade_factor, 1))))";
			$calc_planet_torp_launchers = "SUM(exp(torp_launchers * log(GREATEST($planet_upgrade_factor, 1))))";
			$calc_planet_shields = "SUM(exp(shields * log(GREATEST($planet_upgrade_factor, 1))))";
			$calc_planet_jammer = "SUM(exp(jammer * log(GREATEST($planet_upgrade_factor, 1))))";
			$calc_planet_cloak = "SUM(exp(cloak * log(GREATEST($planet_upgrade_factor, 1))))";

			$calc_planet_sector_defense_weapons = "SUM(exp(sector_defense_weapons * log(GREATEST($planet_SD_upgrade_factor, 1))))";
			$calc_planet_sector_defense_sensors = "SUM(exp(sector_defense_sensors * log(GREATEST($planet_SD_upgrade_factor, 1))))";
			$calc_planet_sector_defense_cloak = "SUM(exp(sector_defense_cloak * log(GREATEST($planet_SD_upgrade_factor, 1))))";
			 //Add $calc_planet_armor if necessary
			$calc_planet_def_levels = "($calc_planet_fighter + $calc_planet_sensors + $calc_planet_beams + $calc_planet_torp_launchers + $calc_planet_shields + $calc_planet_jammer + $calc_planet_cloak + $calc_planet_sector_defense_weapons + $calc_planet_sector_defense_sensors + $calc_planet_sector_defense_cloak)*$upgrade_cost";

			$debug_query = $db->Execute("SELECT $calc_planet_defense + $calc_planet_credits + $calc_planet_def_levels " . $calc_planets . " AS score1 FROM {$db_prefix}planets WHERE owner=$sid ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score = $row['score1'];
//echo "Score1 = $score<br>";

			$planet_score_total = 0;
			$cargo_query2 = $db->Execute("SELECT classname, price from {$db_prefix}class_modules_commodities where cargoport=1 and defaultcargoplanet = 0");
			db_op_result($cargo_query2,__LINE__,__FILE__);
//echo $cargo_query2->RecordCount() . "<br>";
			while (!$cargo_query2->EOF) 
			{
				$cargotype = $cargo_query2->fields['classname'];
				$specialprice = $cargo_query2->fields['price'];

				$query = "SELECT SUM(special_amount) as total FROM {$db_prefix}planets WHERE owner=$sid and special_name=" . $db->qstr($cargotype);
				$debug_query = $db->Execute($query);
				$special_number = (isset($debug_query->fields['total'])) ? floor($debug_query->fields['total']) : 0;
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
				$planet_score_total += ($special_number * $specialprice);

//echo "$cargotype:  $special_number * $specialprice = " . ($special_number * $specialprice) . "<br>";
				$cargo_query2->Movenext();
			}
			$cargo_query2->close();
//echo $planet_score_total . "<br>";
			$score += $planet_score_total;
//echo "Score1 = $score<br>";

			// Loop through all ships for total ranking
			$res2 = $db->Execute("SELECT $calc_levels + $calc_ship_equip AS score2 FROM {$db_prefix}ships WHERE player_id=$sid");
			db_op_result($res2,__LINE__,__FILE__);
			$row2 = $res2->fields;
			$res2->close();
			$score += $row2['score2'];

//echo "Score2 = $row2[score2]<br>";

			$debug_query = $db->Execute("SELECT credits, rank_tab, character_name FROM {$db_prefix}players where player_id = $sid");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score += $row['credits'];
			$rank_tab = $row['rank_tab'];
			$player_name =  $row['character_name'];
//echo "Score3 = $row[credits]<br>";

			$res2 = $db->Execute("SELECT SUM(amount) AS amount, class FROM {$db_prefix}ship_devices WHERE player_id=$sid group by class");
			db_op_result($res2,__LINE__,__FILE__);

			while (!$res2->EOF) 
			{
				$row2 = $res2->fields;

				$deviceamount = $row2['amount'];

				if(!class_exists($row2['class'])){
					include ("class/devices/" . $row2['class'] . ".inc");
				}
				$deviceobject = new $row2['class']();
				$deviceamount = $deviceobject->devices_score_code($sid);

				$score += $deviceamount * $deviceobject->price;
//echo "Score4 = $deviceamount - " . ($deviceamount * $deviceobject->price) . "<br>";
				$res2->Movenext();
			}
			$res2->close();
//echo "Score5 = $row2[score2]<br>";

			$debug_query = $db->Execute("SELECT balance, loan FROM {$db_prefix}ibank_accounts where player_id = $sid");
			db_op_result($debug_query,__LINE__,__FILE__);

			$loan = 0;
			if ($debug_query)
			{
				$row = $debug_query->fields;
				$score += ($row['balance'] - $row['loan']);
//echo "Score6 = " . ($row['balance'] - $row['loan']) . "<br>";
				$loan = $row['loan'];
			}
			$debug_query->close();

			// Add in Sector Defense values
			$debug_query = $db->Execute("SELECT (SUM(quantity)*$fighter_price) AS score6 FROM {$db_prefix}sector_defense WHERE player_id=$sid and defense_type='fighters'");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score += $row['score6'];
//echo "Score7 = " . $row['score6'] . "<br>";

			$debug_query = $db->Execute("SELECT (SUM(quantity)*$torpedo_price) AS score7 FROM {$db_prefix}sector_defense WHERE player_id=$sid and defense_type='mines'");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score += $row['score7'];
//echo "Score8 = " . $row['score7'] . "<br>";

			// Add in Cargo Hull values
			$calc_levels = "((SUM(exp(cargo_hull * log(GREATEST($upgrade_factor, 1)))) + SUM(exp(cargo_power * log(GREATEST($upgrade_factor, 1)))))*$upgrade_cost)";
			$calc_cargo_ship = "SUM(IF(cargo_hull!=0, 116383500, 0))";
			$debug_query = $db->Execute("SELECT $calc_levels+$calc_cargo_ship AS score3 FROM {$db_prefix}planets WHERE owner=$sid");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score += $row['score3'];
//echo "Score9 = " . $row['score3'] . "<br>";

			// Add in Probe values
			$calc_levels = "((SUM(exp(engines * log(GREATEST($upgrade_factor, 1)))) + SUM(exp(cloak * log(GREATEST($upgrade_factor, 1)))) + SUM(exp(sensors * log(GREATEST($upgrade_factor, 1)))))*$upgrade_cost)";
			$debug_query = $db->Execute("SELECT $calc_levels AS score4 FROM {$db_prefix}probe WHERE owner_id=$sid");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score += $row['score4'];
//echo "Score10 = " . $row['score4'] . "<br>";

			$debug_query = $db->Execute("SELECT SUM(amount) AS score7 FROM {$db_prefix}bounty WHERE placed_by=$sid");
			db_op_result($debug_query,__LINE__,__FILE__);
			$row = $debug_query->fields;
			$debug_query->close();
			$score += $row['score7'];
//echo "Score11 = " . $row['score7'] . "<br>";
//echo "Score final = " . $score . "<br>";

			$returnscore = array();
			// ranking display score
			$returnscore[0] = sign($score) * ROUND(SQRT(ABS($score)));
//echo "Score final = " . $score . "<hr>";
			// attack/bounty check score
			$returnscore[1] = sign($score + $loan) * ROUND(SQRT(ABS($score + $loan)));

			$player_insignia = player_insignia_name($sid, $returnscore[0]);

			if((int)$rank_tab < (int)$player_insignia[2])
			{
				// Promoted
				insert_news("$player_name|" . $player_insignia[1] . "|" . $player_insignia[2] . "|" . $player_insignia[3] . "|" . $player_insignia[4] . "|" . $player_insignia[5] . "|" . $player_insignia[6], $sid, "promoted");
			}
			else if((int)$rank_tab > (int)$player_insignia[2])
			{
				// Demoted
				insert_news("$player_name|" . $player_insignia[1] . "|" . $player_insignia[2], $sid, "demoted");
			}

			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET score=$returnscore[0], attackscore=$returnscore[1], rank_tab='$player_insignia[2]' WHERE player_id=$sid");
			db_op_result($debug_query,__LINE__,__FILE__);

			return $returnscore;
		}
		else
		{
			return 0;
		}
	}
}
?>
