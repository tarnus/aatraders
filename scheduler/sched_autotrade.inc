<?php
// 1
// 2400
// 5
// 0
// Y
// How often trade ships for planets will perform trade movements and actions.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

$time_between_executions = 60; // minutes between each autotrade

// ********************************
// ***** Sector Defense Check *****
// ********************************

function checksectordefense($sectorid, $player_id){

	global $db, $db_prefix;

	$hostile = 0;

	$result98 = $db->SelectLimit("SELECT player_id FROM {$db_prefix}sector_defense WHERE sector_id = $sectorid AND player_id <> $player_id", 1);
	if (!$result98->EOF)
	{
		$fighters_owner = $result98->fields;
		$nsresult = $db->SelectLimit("SELECT team from {$db_prefix}players where player_id=$fighters_owner[player_id]", 1);
		$nsfighters = $nsresult->fields;
		$nsresult->close();
		if ($nsfighters['team'] != $playerinfo['team'] || $playerinfo['team']==0)
			$hostile = 1;
	}
	$result98->close();

	return $hostile;
}

if($allow_autotrades == 1)
{
	TextFlush ( "<b>AUTO PLANETARY TRADING</b><br>\n");

	TextFlush ( "\nTrading with ports...<br>");

	$trade_date = date("Y-m-d H:i:s");
	$new_trade_date = date("Y-m-d H:i:s", strtotime($trade_date) + floor($time_between_executions * 60));
	$res = $db->Execute("SELECT * FROM {$db_prefix}autotrades WHERE trade_time<'$trade_date'");
	$tradecount = $res->recordcount();

	TextFlush ( "\nRunning ".$tradecount." trade routes.<br>");

	if($tradecount > 0)
	{
		$commodity_query = $db->Execute("SELECT * FROM {$db_prefix}class_modules_commodities");
		db_op_result($commodity_query,__LINE__,__FILE__);
		while(!$commodity_query->EOF){
			$commodity = $commodity_query->fields['classname'];
			$commodity_price[$commodity] = $commodity_query->fields['price'];
			$commodity_delta[$commodity] = $commodity_query->fields['delta'];
			$commodity_itemlimit[$commodity] = $commodity_query->fields['itemlimit'];
			$commodity_reducerate[$commodity] = $commodity_query->fields['reducerate'];
			$commodity_total_sold[$commodity] = 0;
			$commodity_total_credits_made[$commodity] = 0;
			$commodity_total_bought[$commodity] = 0;
			$commodity_total_credits_lost[$commodity] = 0;
			$commodity_query->MoveNext();
		}
		$commodity_query->close();
	}

	while(!$res->EOF){

		$tradeinfo = $res->fields;

		$res1 = $db->SelectLimit("SELECT * FROM {$db_prefix}planets where planet_id=$tradeinfo[planet_id]", 1);
		$planetinfo = $res1->fields;
		$res1->close();

		if($planetinfo['planet_id'] != '' and $planetinfo['planet_id'] != 0){
			TextFlush ( "Starting trade for planet ".$planetinfo['name']." - ".$planetinfo['planet_id']."<BR>");

			$price_array = array();

			$total_cost = 0;
			$trade_goods = 0;
			$trade_ore = 0;
			$trade_organics = 0;
			$trade_energy = 0;
			$trade_colonist = 0;

			$goods_price = 0;
			$ore_price = 0;
			$organics_price = 0;
			$energy_price = 0;
			$colonist_price = 0;

			if(checksectordefense($planetinfo['sector_id'], $tradeinfo['owner']) != 1){
				if($tradeinfo['port_id_goods'] != 0){
					$res2 = $db->Execute("SELECT * FROM {$db_prefix}universe where sector_id='$tradeinfo[port_id_goods]' and port_type!='goods'");

					if($res2->recordcount() != 0){
						$sectorinfo = $res2->fields;

						$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id] and commodity_type='goods'");
						db_op_result($debug_query,__LINE__,__FILE__);
						if($debug_query->recordcount() != 0){
							$destinationport_data_id = $debug_query->fields['data_id'];
							$destinationport_commodity_type = $debug_query->fields['commodity_type'];
							$destinationport_commodity_amount = $debug_query->fields['commodity_amount'];
							$destinationport_commodity_price = $debug_query->fields['commodity_price'];
							$destinationport_goodevil = $debug_query->fields['goodevil'];
							$debug_query->close();

							if(checksectordefense($sectorinfo['sector_id'], $tradeinfo['owner']) != 1){
								$trade_goods = NUM_HOLDS($planetinfo['cargo_hull']);

								if (($planetinfo['goods'] - 10000) - $trade_goods < 0)
								{
									$trade_goods = $planetinfo['goods'] - 10000;
								}

								if ($planetinfo['goods'] < 0 or $trade_goods < 0)
								{
									$trade_goods = 0;
								}

								$item_price = max($destinationport_commodity_price + $commodity_price[$destinationport_commodity_type] + $commodity_delta[$destinationport_commodity_type] * $commodity_itemlimit[$destinationport_commodity_type] / $commodity_itemlimit[$destinationport_commodity_type] * $inventory_factor, 0.01);
								if($destinationport_commodity_amount < $trade_goods)
									$trade_goods = $destinationport_commodity_amount;

								$goods_price = $item_price;
								$total_cost += $goods_price * $trade_goods;
								$reduce_rate = ($destinationport_commodity_price > $commodity_price[$destinationport_commodity_type]) ? ($commodity_reducerate[$destinationport_commodity_type] * ($destinationport_commodity_price / $commodity_price[$destinationport_commodity_type])) : $commodity_reducerate[$destinationport_commodity_type];
								$reduce_rate = $commodity_reducerate[$destinationport_commodity_type];
								$destinationport_commodity_price = $destinationport_commodity_price - ($commodity_reducerate[$destinationport_commodity_type] * $trade_goods);

								$destinationport_commodity_amount = max(0, $destinationport_commodity_amount - $trade_goods);
//								echo "Sell to port $destinationport_commodity_type - " . $trade_goods . " - $goods_price<br>";

								$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET commodity_price=$destinationport_commodity_price, commodity_amount=$destinationport_commodity_amount, trade_date='$trade_date' WHERE data_id=$destinationport_data_id");
								db_op_result($debug_query,__LINE__,__FILE__);

							}else{
								TextFlush ( "Trade Aborted due to enemy sector defense in sector $tradeinfo[port_id_goods].");
								playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE_ABORTED", "$planetinfo[name]|$planetinfo[sector_id]|$sectorinfo[sector_id]");
							}
						}
					}
					$res2->close();
				}

				if($tradeinfo['port_id_ore'] != 0){
					$res3 = $db->Execute("SELECT * FROM {$db_prefix}universe where sector_id='$tradeinfo[port_id_ore]' and port_type!='ore'");

					if($res3->recordcount() != 0){
						$sectorinfo = $res3->fields;

						$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id] and commodity_type='ore'");
						db_op_result($debug_query,__LINE__,__FILE__);
						if($debug_query->recordcount() != 0){
							$destinationport_data_id = $debug_query->fields['data_id'];
							$destinationport_commodity_type = $debug_query->fields['commodity_type'];
							$destinationport_commodity_amount = $debug_query->fields['commodity_amount'];
							$destinationport_commodity_price = $debug_query->fields['commodity_price'];
							$destinationport_goodevil = $debug_query->fields['goodevil'];
							$debug_query->close();

							if(checksectordefense($sectorinfo['sector_id'], $tradeinfo['owner']) != 1){
								$trade_ore = NUM_HOLDS($planetinfo['cargo_hull']);

								if (($planetinfo['ore'] - 10000) - $trade_ore < 0)
								{
									$trade_ore = $planetinfo['ore'] - 10000;
								}

								if ($planetinfo['ore'] < 0 or $trade_ore < 0)
								{
									$trade_ore = 0;
								}

								$item_price = max($destinationport_commodity_price + $commodity_price[$destinationport_commodity_type] + $commodity_delta[$destinationport_commodity_type] * $commodity_itemlimit[$destinationport_commodity_type] / $commodity_itemlimit[$destinationport_commodity_type] * $inventory_factor, 0.01);
								if($destinationport_commodity_amount < $trade_ore)
									$trade_ore = $destinationport_commodity_amount;

								$ore_price = $item_price;
								$total_cost += $ore_price * $trade_ore;
								$reduce_rate = ($destinationport_commodity_price > $commodity_price[$destinationport_commodity_type]) ? ($commodity_reducerate[$destinationport_commodity_type] * ($destinationport_commodity_price / $commodity_price[$destinationport_commodity_type])) : $commodity_reducerate[$destinationport_commodity_type];
								$reduce_rate = $commodity_reducerate[$destinationport_commodity_type];
								$destinationport_commodity_price = $destinationport_commodity_price - ($reduce_rate * $trade_ore);

								$destinationport_commodity_amount = max(0, $destinationport_commodity_amount - $trade_ore);
//								echo "Sell to port $destinationport_commodity_type - " . $trade_ore . " - $ore_price<br>";

								$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET commodity_price=$destinationport_commodity_price, commodity_amount=$destinationport_commodity_amount, trade_date='$trade_date' WHERE data_id=$destinationport_data_id");
								db_op_result($debug_query,__LINE__,__FILE__);
							}else{
								TextFlush ( "Trade Aborted due to enemy sector defense in sector $tradeinfo[port_id_ore].");
								playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE_ABORTED", "$planetinfo[name]|$planetinfo[sector_id]|$sectorinfo[sector_id]");
							}
						}
					}
					$res3->close();
				}

				if($tradeinfo['port_id_organics'] != 0){
					$res4 = $db->Execute("SELECT * FROM {$db_prefix}universe where sector_id='$tradeinfo[port_id_organics]' and port_type!='organics'");

					if($res4->recordcount() != 0){
						$sectorinfo = $res4->fields;

						$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id] and commodity_type='organics'");
						db_op_result($debug_query,__LINE__,__FILE__);
						if($debug_query->recordcount() != 0){
							$destinationport_data_id = $debug_query->fields['data_id'];
							$destinationport_commodity_type = $debug_query->fields['commodity_type'];
							$destinationport_commodity_amount = $debug_query->fields['commodity_amount'];
							$destinationport_commodity_price = $debug_query->fields['commodity_price'];
							$destinationport_goodevil = $debug_query->fields['goodevil'];
							$debug_query->close();

							if(checksectordefense($sectorinfo['sector_id'], $tradeinfo['owner']) != 1){
								$trade_organics = NUM_HOLDS($planetinfo['cargo_hull']);

								if (($planetinfo['organics'] - 10000) - $trade_organics < 0)
								{
									$trade_organics = $planetinfo['organics'] - 10000;
								}

								if ($planetinfo['organics'] < 0 or $trade_organics < 0)
								{
									$trade_organics = 0;
								}

								$item_price = max($destinationport_commodity_price + $commodity_price[$destinationport_commodity_type] + $commodity_delta[$destinationport_commodity_type] * $commodity_itemlimit[$destinationport_commodity_type] / $commodity_itemlimit[$destinationport_commodity_type] * $inventory_factor, 0.01);
								if($destinationport_commodity_amount < $trade_organics)
									$trade_organics = $destinationport_commodity_amount;

								$organics_price = $item_price;
								$total_cost += $organics_price * $trade_organics;
								$reduce_rate = ($destinationport_commodity_price > $commodity_price[$destinationport_commodity_type]) ? ($commodity_reducerate[$destinationport_commodity_type] * ($destinationport_commodity_price / $commodity_price[$destinationport_commodity_type])) : $commodity_reducerate[$destinationport_commodity_type];
								$reduce_rate = $commodity_reducerate[$destinationport_commodity_type];
								$destinationport_commodity_price = $destinationport_commodity_price - ($reduce_rate * $trade_organics);

								$destinationport_commodity_amount = max(0, $destinationport_commodity_amount - $trade_organics);
//								echo "Sell to port $destinationport_commodity_type - " . $trade_organics . " - $organics_price<br>";

								$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET commodity_price=$destinationport_commodity_price, commodity_amount=$destinationport_commodity_amount, trade_date='$trade_date' WHERE data_id=$destinationport_data_id");
								db_op_result($debug_query,__LINE__,__FILE__);
							}else{
								TextFlush ( "Trade Aborted due to enemy sector defense in sector $tradeinfo[port_id_organics].");
								playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE_ABORTED", "$planetinfo[name]|$planetinfo[sector_id]|$sectorinfo[sector_id]");
							}
						}
					}
					$res4->close();
				}

				if($tradeinfo['port_id_energy'] != 0){
					$res5 = $db->Execute("SELECT * FROM {$db_prefix}universe where sector_id='$tradeinfo[port_id_energy]' and port_type!='energy'");

					if($res5->recordcount() != 0){
						$sectorinfo = $res5->fields;

						$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id] and commodity_type='energy'");
						db_op_result($debug_query,__LINE__,__FILE__);
						if($debug_query->recordcount() != 0){
							$destinationport_data_id = $debug_query->fields['data_id'];
							$destinationport_commodity_type = $debug_query->fields['commodity_type'];
							$destinationport_commodity_amount = $debug_query->fields['commodity_amount'];
							$destinationport_commodity_price = $debug_query->fields['commodity_price'];
							$destinationport_goodevil = $debug_query->fields['goodevil'];
							$debug_query->close();

							if(checksectordefense($sectorinfo['sector_id'], $tradeinfo['owner']) != 1){
								$trade_energy = NUM_ENERGY($planetinfo['cargo_power']);

								if (($planetinfo['energy'] - 10000) - $trade_colonist < 0)
								{
									$trade_energy = $planetinfo['energy'] - 10000;
								}

								if ($planetinfo['energy'] < 0 or $trade_colonist < 0)
								{
									$trade_energy = 0;
								}

								$item_price = max($destinationport_commodity_price + $commodity_price[$destinationport_commodity_type] + $commodity_delta[$destinationport_commodity_type] * $commodity_itemlimit[$destinationport_commodity_type] / $commodity_itemlimit[$destinationport_commodity_type] * $inventory_factor, 0.01);
								if($destinationport_commodity_amount < $trade_energy)
									$trade_energy = $destinationport_commodity_amount;

								$energy_price = $item_price;
								$total_cost += $energy_price * $trade_energy;
								$reduce_rate = ($destinationport_commodity_price > $commodity_price[$destinationport_commodity_type]) ? ($commodity_reducerate[$destinationport_commodity_type] * ($destinationport_commodity_price / $commodity_price[$destinationport_commodity_type])) : $commodity_reducerate[$destinationport_commodity_type];
								$reduce_rate = $commodity_reducerate[$destinationport_commodity_type];
								$destinationport_commodity_price = $destinationport_commodity_price - ($reduce_rate * $trade_energy);

								$destinationport_commodity_amount = max(0, $destinationport_commodity_amount - $trade_energy);
//								echo "Sell to port $destinationport_commodity_type - " . $trade_energy . " - $energy_price<br>";

								$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET commodity_price=$destinationport_commodity_price, commodity_amount=$destinationport_commodity_amount, trade_date='$trade_date' WHERE data_id=$destinationport_data_id");
								db_op_result($debug_query,__LINE__,__FILE__);
							}else{
								TextFlush ( "Trade Aborted due to enemy sector defense in sector $tradeinfo[port_id_energy].");
								playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE_ABORTED", "$planetinfo[name]|$planetinfo[sector_id]|$tradeinfo[port_id_energy]");
							}
						}
					}
					$res5->close();
				}

				if($tradeinfo['port_id_colonist'] != 0){
					$res5 = $db->Execute("SELECT * FROM {$db_prefix}universe where sector_id='$tradeinfo[port_id_colonist]' and port_type!='colonists'");

					if($res5->recordcount() != 0){
						$sectorinfo = $res5->fields;

						$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$sectorinfo[sector_id] and commodity_type='colonists'");
						db_op_result($debug_query,__LINE__,__FILE__);
						if($debug_query->recordcount() != 0){
							$destinationport_data_id = $debug_query->fields['data_id'];
							$destinationport_commodity_type = $debug_query->fields['commodity_type'];
							$destinationport_commodity_amount = $debug_query->fields['commodity_amount'];
							$destinationport_commodity_price = $debug_query->fields['commodity_price'];
							$destinationport_goodevil = $debug_query->fields['goodevil'];
							$debug_query->close();

							if(checksectordefense($sectorinfo['sector_id'], $tradeinfo['owner']) != 1){
								$trade_colonist = NUM_HOLDS($planetinfo['cargo_hull']);

								if (($planetinfo['colonists'] - 10000) - $trade_colonist < 0)
								{
									$trade_colonist = $planetinfo['colonists'] - 10000;
								}

								if ($planetinfo['colonists'] < 0 or $trade_colonist < 0)
								{
									$trade_colonist = 0;
								}

								$item_price = max($destinationport_commodity_price + $commodity_price[$destinationport_commodity_type] + $commodity_delta[$destinationport_commodity_type] * $commodity_itemlimit[$destinationport_commodity_type] / $commodity_itemlimit[$destinationport_commodity_type] * $inventory_factor, 0.01);
								if($destinationport_commodity_amount < $trade_colonist)
									$trade_colonist = $destinationport_commodity_amount;

								$colonist_price = $item_price;
								$total_cost += $colonist_price * $trade_colonist;
								$destinationport_commodity_price = $destinationport_commodity_price - ($commodity_reducerate[$destinationport_commodity_type] * $trade_colonist);

								$destinationport_commodity_amount = max(0, $destinationport_commodity_amount - $trade_colonist);
//								echo "Sell to port $destinationport_commodity_type - " . $trade_colonist . " - $colonist_price - $destinationport_commodity_amount<br>";

								$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET commodity_price=$destinationport_commodity_price, commodity_amount=$destinationport_commodity_amount, trade_date='$trade_date' WHERE data_id=$destinationport_data_id");
								db_op_result($debug_query,__LINE__,__FILE__);
							}else{
								TextFlush ( "Trade Aborted due to enemy sector defense in sector $tradeinfo[port_id_energy].");
								playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE_ABORTED", "$planetinfo[name]|$planetinfo[sector_id]|$sectorinfo[sector_id]");
							}
						}
					}
					$res5->close();
				}
			}
			else
			{
				TextFlush ( "Trade Aborted due to enemy sector defense in planet sector.");
				playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE_ABORTED", "$planetinfo[name]|$planetinfo[sector_id]|$planetinfo[sector_id]");
			}

			$total_cost = floor($total_cost);
//echo"UPDATE {$db_prefix}planets SET goods=goods-$trade_goods, ore=ore-$trade_ore, organics=organics-$trade_organics, energy=energy-$trade_energy, colonists=colonists-$trade_colonist, credits=credits+$total_cost WHERE planet_id=$planetinfo[planet_id]<br>";
			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET goods=goods-$trade_goods, ore=ore-$trade_ore, organics=organics-$trade_organics, energy=energy-$trade_energy, colonists=colonists-$trade_colonist, credits=credits+$total_cost WHERE planet_id=$planetinfo[planet_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$goods_price = floor($goods_price);
			$ore_price = floor($ore_price);
			$organics_price = floor($organics_price);
			$energy_price = floor($energy_price);

//echo"UPDATE {$db_prefix}autotrades SET goods_price=$goods_price, ore_price=$ore_price, organics_price=$organics_price, energy_price=$energy_price, colonist_price=$colonist_price current_trade=$total_cost, trade_time='$new_trade_date' WHERE traderoute_id=$tradeinfo[traderoute_id]<br>";
			$debug_query = $db->Execute("UPDATE {$db_prefix}autotrades SET goods_price=$goods_price, ore_price=$ore_price, organics_price=$organics_price, energy_price=$energy_price, colonist_price=$colonist_price, current_trade=$total_cost, trade_time='$new_trade_date' WHERE traderoute_id=$tradeinfo[traderoute_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			if($planetinfo['name'] == '')
				$planetinfo['name'] = $l_unnamed;

//			TextFlush ( "$tradeinfo[owner], LOG10_AUTOTRADE, $planetinfo[name]|$planetinfo[sector_id]|$total_cost|$trade_goods|$trade_ore|$trade_organics|$trade_energy|$trade_colonist|$goods_price|$ore_price|$organics_price|$energy_price|$colonist_price<br>");

			playerlog($tradeinfo['owner'], "LOG10_AUTOTRADE", "$planetinfo[name]|$planetinfo[sector_id]|$total_cost|$trade_goods|$trade_ore|$trade_organics|$trade_energy|$trade_colonist|$goods_price|$ore_price|$organics_price|$energy_price|$colonist_price");

			TextFlush ( "Trade Complete for planet ".$planetinfo['name']." - ".$planetinfo['planet_id']." - Total Amount of Trade: " . $total_cost . "<BR><br>");
		}else{
			$debug_query = $db->Execute("DELETE FROM {$db_prefix}autotrades WHERE traderoute_id=$tradeinfo[traderoute_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
		$res->MoveNext();
	}
	$res->close();

// end of trading

TextFlush ( "<br>\n");
}

$multiplier = 0; //no use to run this again
$db->debug=0;
?>
