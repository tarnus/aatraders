<?php
if (!function_exists('capture_planet_ships')) {

	function capture_planet_ships($attacker_player_id, $target_planet_id, $destroyed_planet = 0)
	{
		global $db_prefix, $db, $max_tech_level, $ewd_maxavgtechlevel;

		$debug_query = $db->Execute("SELECT character_name, currentship FROM {$db_prefix}players WHERE player_id = $attacker_player_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		$character_name = $debug_query->fields['character_name'];
		$currentship = $debug_query->fields['currentship'];
		$debug_query->close();

		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE ship_id = $currentship");
		db_op_result($debug_query,__LINE__,__FILE__);
		$shipinfo = $debug_query->fields;
		$debug_query->close();
		$attacker_shipavg = floor($shipinfo['basehull'] + ($shipinfo['hull'] + $shipinfo['engines'] + $shipinfo['power'] + $shipinfo['fighter'] + $shipinfo['sensors'] + $shipinfo['beams'] + $shipinfo['torp_launchers'] + $shipinfo['shields'] + $shipinfo['cloak'] + $shipinfo['armor'] + $shipinfo['ecm']) / 11);

		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE storage_planet_id = $target_planet_id");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($debug_query > 0)
		{
			while (!$debug_query->EOF)
			{
				$row = $debug_query->fields;
				$shipavg = $row['basehull'] + ($row['hull'] + $row['engines'] + $row['power'] + $row['fighter'] + $row['sensors'] + $row['beams'] + $row['torp_launchers'] + $row['shields'] + $row['cloak'] + $row['armor'] + $row['ecm']) / 11;

				if( floor($shipavg * ($min_ship_value_capture / 100)) > $attacker_shipavg )
				{
					$ship_query = $db->Execute("SELECT currentship FROM {$db_prefix}players WHERE currentship = $row[ship_id]");
					db_op_result($ship_query,__LINE__,__FILE__);
					$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]", '', 'class');
					if($ship_query->RecordCount() == 0 || $targetshipdevice['dev_emerwarp']['amount'] == 0)
					{
						playerlog($row['player_id'], "LOG5_STORAGE_SUICIDE", $character_name);
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id=$row[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id=$row[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $row[ship_id]"); 
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
					else
					{
						$findem = $db->Execute("SELECT sector_id, planet_id, name FROM {$db_prefix}planets where owner = " . $row['player_id']);
						$totrecs=$findem->RecordCount(); 
						if($totrecs != 0)
						{
							$findem = $db->SelectLimit("SELECT sector_id, planet_id, name FROM {$db_prefix}planets where owner = " . $row['player_id'] . " ORDER BY rand()", 1);
							$dest_sector = $findem->fields['sector_id'];
							$dest_planet_id = $findem->fields['planet_id'];
							$dest_planet_name = $findem->fields['name'];

							playerlog($row['player_id'], "LOG5_STORAGE_EWD", "$character_name|$dest_sector|$dest_planet_name");
							$update_query = $db->Execute ("UPDATE {$db_prefix}ships SET storage_planet_id=$dest_planet_id, sector_id=$dest_sector WHERE ship_id=$row[ship_id]");
							db_op_result($update_query,__LINE__,__FILE__);
							$update_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
							db_op_result($update_query,__LINE__,__FILE__);
						}
					}
				}
				else
				{
					$ship_query = $db->Execute("SELECT currentship FROM {$db_prefix}players WHERE currentship = $row[ship_id]");
					db_op_result($ship_query,__LINE__,__FILE__);
					$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]", '', 'class');
					if($ship_query->RecordCount() == 0)
					{
						if($targetshipdevice['dev_emerwarp']['amount'] == 0)
						{
							if($destroyed_planet == 0)
							{
								playerlog($row['player_id'], "LOG5_STORAGE_CAPTURED", $character_name);
								$update_query = $db->Execute ("UPDATE {$db_prefix}spies SET active='Y' WHERE ship_id=$row[ship_id] and owner_id=$row[player_id]");
								db_op_result($update_query,__LINE__,__FILE__);
								$update_query = $db->Execute ("UPDATE {$db_prefix}ships SET player_id=$attacker_player_id WHERE ship_id=$row[ship_id]");
								db_op_result($update_query,__LINE__,__FILE__);
								$update_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET player_id=$attacker_player_id WHERE ship_id=$row[ship_id]");
								db_op_result($update_query,__LINE__,__FILE__);
								$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
								db_op_result($debug_query,__LINE__,__FILE__);
							}
							else
							{
								playerlog($row['player_id'], "LOG5_STORAGE_SUICIDE", $character_name);
								$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id=$row[ship_id]");
								db_op_result($debug_query,__LINE__,__FILE__);
								$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]");
								db_op_result($debug_query,__LINE__,__FILE__);
								$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id=$row[ship_id]");
								db_op_result($debug_query,__LINE__,__FILE__);
								$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $row[ship_id]"); 
								db_op_result($debug_query,__LINE__,__FILE__);
								$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
								db_op_result($debug_query,__LINE__,__FILE__);
							}
						}
						else
						{
							if ($shipavg > $ewd_maxavgtechlevel)
							{
								$chance = round($shipavg / $max_tech_level) * 100;
							}
							else
							{
								$chance = 0;
							}

							$random_value = mt_rand(1,100);
							if ($random_value > $chance)
							{
								$findem = $db->Execute("SELECT sector_id, planet_id, name FROM {$db_prefix}planets where owner = " . $row['player_id']);
								$totrecs=$findem->RecordCount(); 
								if($totrecs != 0)
								{
									$findem = $db->SelectLimit("SELECT sector_id, planet_id, name FROM {$db_prefix}planets where owner = " . $row['player_id'] . " ORDER BY rand()", 1);
									$dest_sector = $findem->fields['sector_id'];
									$dest_planet_id = $findem->fields['planet_id'];
									$dest_planet_name = $findem->fields['name'];

									playerlog($row['player_id'], "LOG5_STORAGE_EWD", "$character_name|$dest_sector|$dest_planet_name");

									$update_query = $db->Execute ("UPDATE {$db_prefix}ships SET storage_planet_id=$dest_planet_id, sector_id=$dest_sector WHERE ship_id=$row[ship_id]");
									db_op_result($update_query,__LINE__,__FILE__);
									$update_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
									db_op_result($update_query,__LINE__,__FILE__);
								}
								else
								{
									if($destroyed_planet == 0)
									{
										playerlog($row['player_id'], "LOG5_STORAGE_CAPTURED", $character_name);
										$update_query = $db->Execute ("UPDATE {$db_prefix}spies SET active='Y' WHERE ship_id=$row[ship_id] and owner_id=$row[player_id]");
										db_op_result($update_query,__LINE__,__FILE__);
										$update_query = $db->Execute ("UPDATE {$db_prefix}ships SET player_id=$attacker_player_id WHERE ship_id=$row[ship_id]");
										db_op_result($update_query,__LINE__,__FILE__);
										$update_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET player_id=$attacker_player_id WHERE ship_id=$row[ship_id]");
										db_op_result($update_query,__LINE__,__FILE__);
										$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
										db_op_result($debug_query,__LINE__,__FILE__);
									}
									else
									{
										playerlog($row['player_id'], "LOG5_STORAGE_SUICIDE", $character_name);
										$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id=$row[ship_id]");
										db_op_result($debug_query,__LINE__,__FILE__);
										$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]");
										db_op_result($debug_query,__LINE__,__FILE__);
										$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id=$row[ship_id]");
										db_op_result($debug_query,__LINE__,__FILE__);
										$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $row[ship_id]"); 
										db_op_result($debug_query,__LINE__,__FILE__);
										$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
										db_op_result($debug_query,__LINE__,__FILE__);
									}
								}
							}
							else
							{
								if($destroyed_planet == 0)
								{
									playerlog($row['player_id'], "LOG5_STORAGE_EWDFAIL", $character_name);
									$update_query = $db->Execute ("UPDATE {$db_prefix}spies SET active='Y' WHERE ship_id=$row[ship_id] and owner_id=$row[player_id]");
									db_op_result($update_query,__LINE__,__FILE__);
									$update_query = $db->Execute ("UPDATE {$db_prefix}ships SET player_id=$attacker_player_id WHERE ship_id=$row[ship_id]");
									db_op_result($update_query,__LINE__,__FILE__);
									$update_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
									db_op_result($update_query,__LINE__,__FILE__);
									$update_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET player_id=$attacker_player_id WHERE ship_id=$row[ship_id]");
									db_op_result($update_query,__LINE__,__FILE__);
									$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
								}
								else
								{
									playerlog($row['player_id'], "LOG5_STORAGE_SUICIDE", $character_name);
									$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id=$row[ship_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
									$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id=$row[ship_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
									$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id=$row[ship_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
									$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $row[ship_id]"); 
									db_op_result($debug_query,__LINE__,__FILE__);
									$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $row[ship_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
								}
							}
						}
					}
				}
				$ship_query->close();
				$debug_query->MoveNext();
			}
		}
		$debug_query->close();
	}
}
?>
