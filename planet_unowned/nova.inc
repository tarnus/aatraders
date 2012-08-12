<?php
include ("languages/$langdir/lang_combat.inc");
include ("languages/$langdir/lang_novabomb.inc");

include ("globals/combat_functions.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/collect_bounty.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/send_system_im.inc");
include ("globals/set_max_credits.inc");
include ("globals/log_move.inc");
include ("globals/calc_ownership.inc");
include ("globals/gen_score.inc");
include ("globals/insert_news.inc");
include ("globals/sector_defense_battle.inc");
include ("globals/get_rating_change.inc");
include ("globals/artifacts_move.inc");
include ("globals/display_this_planet.inc");
include ("globals/device_ship_tech_modify.inc");
//error_reporting(E_ALL);
$shipinfo_old = $shipinfo;
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

$countplanet = 0;
display_this_planet($planetinfo);
$titleimage = $planetimg[0];
$target_title = str_replace("[player]", $ownerinfo['character_name'], str_replace("[planet]", $planetinfo['name'], $l_cmb_title_target_planet));

$template_object->assign("titleimage", $titleimage);
$template_object->assign("target_title", $target_title);

// check sector defense
if($playerinfo['team'] == 0)
{
	$result3 = $db->Execute ("SELECT defense_type, SUM(quantity) as amount FROM {$db_prefix}sector_defense WHERE sector_id='$shipinfo[sector_id]' and player_id != '$playerinfo[player_id]' GROUP BY defense_type");
}
else
{
	$result3 = $db->Execute ("SELECT {$db_prefix}sector_defense.defense_type, SUM({$db_prefix}sector_defense.quantity) as amount FROM {$db_prefix}sector_defense, {$db_prefix}players WHERE {$db_prefix}sector_defense.sector_id='$shipinfo[sector_id]' and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]' and ({$db_prefix}players.player_id={$db_prefix}sector_defense.player_id and {$db_prefix}players.team != $playerinfo[team]) GROUP BY {$db_prefix}sector_defense.defense_type");
}
db_op_result($result3,__LINE__,__FILE__);

if ($result3 > 0)
{
	while (!$result3->EOF)
	{
		$row = $result3->fields;
		$defenses[$row['defense_type']] = $row['amount'];

		$result3->MoveNext();
	}
}
$result3->close();

$is_header = 0;

if ($defenses['fighters'] > 0 && $playerinfo['player_id'] != 3)
{
	unset($_SESSION['movedefense'], $movedefense);
	$destination=$shipinfo['sector_id'];
	include ("sector_defense/fighters.inc");
	$template_object->assign("error_msg", "");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include ("footer.php");
	die();
}

if($shipinfo['class'] >= $dev_nova_shiplimit)
{
	if($shipdevice['dev_nova']['amount'] != "0")
	{
		if($planetinfo['owner'] != 3)
		{
			if($playerinfo['turns'] > $dev_nova_turnsused)
			{
				if($targetinfo['player_id'] <= 3)
				{
					$rating_nova_planet = 0;
				}
				$rating_change=get_rating_change($playerinfo['rating'], $ownerinfo['rating'], $rating_nova_planet, $ownerinfo['player_id']);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET rating=rating+$rating_change, turns_used=turns_used+$dev_nova_turnsused, turns=turns-$dev_nova_turnsused WHERE player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=0 WHERE device_id=" . $shipdevice['dev_nova']['device_id']);
				db_op_result($debug_query,__LINE__,__FILE__);
				$novarand = rand(1, 100);

				if(rand(1, 100) > $dev_nova_explode)
				{
					$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 1);
					$template_object->assign("isfedbounty", $isfedbounty);
					$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);
					$template_object->assign("l_by_nofedbounty", $l_by_nofedbounty);

					$res = $db->SelectLimit("SELECT last_login FROM {$db_prefix}players WHERE player_id = $planetinfo[owner]", 1);
					$last_login = $res->fields['last_login'];
					$res->close();
					send_system_im($planetinfo['owner'], $l_planet_imtitleattack, $playerinfo['character_name'] . " $l_planet_imnova $planetinfo[name] $l_planet_iminsector $planetinfo[sector_name].", $last_login);

					if(rand(1, 100) <= ($dev_nova_percent + $shipdevice['dev_nova']['amount']))
					{
						// nova destroys the planet and some ships on the planet

						$attacker_exchange_result = array();
						$target_exchange_result = array();
						$attacker_exchange_result[] = $l_novabomb_destroyed_planet;
						if($enable_spies)
						{
							$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}planets.sector_id FROM {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id = {$db_prefix}planets.planet_id WHERE {$db_prefix}spies.planet_id = '$planet_id' ");
							while (!$res->EOF)
							{
								$owners = $res->fields;
								playerlog($owners[owner_id], "LOG2_SPY_CATACLYSM", "$owners[spy_id]|$owners[name]|$owners[sector_id]");
								$res->MoveNext();
							}
							$res->close();
							$db->Execute("DELETE FROM {$db_prefix}spies WHERE planet_id = '$planet_id' ");
						}

						$debug_query = $db->Execute("DELETE from {$db_prefix}planets where planet_id=$planet_id");
						db_op_result($debug_query,__LINE__,__FILE__);

						$averagetechlvl = floor((($planetinfo['fighter'] + $planetinfo['sensors'] + $planetinfo['beams'] + $planetinfo['torp_launchers'] + $planetinfo['shields'] + $planetinfo['jammer'] + $planetinfo['cloak']) / 7) / 600 * 100);
						if($targetinfo['player_id'] <= 3)
						{
							$rating_nova_destroy_planet = 0;
						}
						$rating_change=get_rating_change($playerinfo['rating'], $ownerinfo['rating'], $rating_nova_destroy_planet * $averagetechlvl, $ownerinfo['player_id']);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET rating=rating+$rating_change, planets_destroyed=planets_destroyed+1 WHERE player_id=$playerinfo[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
// check for ships and destroy them
						$result4 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planet_id AND on_planet='Y'");
						$shipsonplanet = $result4->RecordCount();

						if ($shipsonplanet > 0)
						{
							$l_cmb_ships_are_landed = str_replace("[cmb_shipsonplanet]", $shipsonplanet, $l_cmb_ships_are_landed);
							$attacker_exchange_result[] = $l_cmb_ships_are_landed;
							while (!$result4->EOF)
							{
								$onplanet = $result4->fields;
								$ship_id = stripnum($onplanet['ship_id']);

								$result2 = $db->Execute ("SELECT * FROM {$db_prefix}players WHERE currentship=$onplanet[ship_id]");
								$targetinfo = $result2->fields;
								$result2->close();

								$result = $db->Execute ("SELECT * FROM {$db_prefix}ships WHERE ship_id='$ship_id'");
								$targetship = $result->fields;
								$result->close();

								$targetshipdevice = $db->GetToFieldArray("SELECT * FROM {$db_prefix}ship_devices WHERE ship_id=$ship_id", '', 'class');
								$targetship_old = $targetship;
								$targetship = device_ship_tech_modify($targetship, $targetshipdevice);

								/* determine percent chance of success in detecting target ship - based on player's sensors and opponent's cloak */
								$targetcloak = floor($targetship['cloak'] * 0.75);

								$success = SCAN_SUCCESS($shipinfo['sensors'], $targetcloak, $shiptypes[$targetship['class']]['basehull']);

								$targetengines = floor($targetship['engines'] * 0.50);

								$flee = SCAN_SUCCESS($shipinfo['engines'], $targetengines, $shiptypes[$targetship['class']]['basehull']);
								$roll = mt_rand(1, 100);
								$roll2 = mt_rand(1, 100);

								if ($flee < $roll2)
								{
									$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_outmanuvered);
									$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
									playerlog($targetinfo['player_id'], "LOG5_ATTACK_OUTMAN", "$playerinfo[character_name]");
									$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET on_planet='N' WHERE ship_id=$ship_id");
									db_op_result($debug_query,__LINE__,__FILE__);
								}
								else if ($roll > $success)
								{
									/* if scan fails - inform both player and target. */
									$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_attacker_scan_fail);
									$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
									db_op_result($debug_query,__LINE__,__FILE__);
									playerlog($targetinfo['player_id'], "LOG5_ATTACK_OUTSCAN", "$playerinfo[character_name]");
									$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET on_planet='N' WHERE ship_id=$ship_id");
									db_op_result($debug_query,__LINE__,__FILE__);
								}
								else
								{
									/* if scan succeeds, show results and inform target. */
									$shipavg = $targetship['basehull'] + ($targetship['hull'] + $targetship['engines'] + $targetship['power'] + $targetship['fighter'] + $targetship['sensors'] + $targetship['beams'] + $targetship['torp_launchers'] + $targetship['shields'] + $targetship['cloak'] + $targetship['armor'] + $targetship['ecm']) / 11;
									if ($shipavg > $ewd_maxavgtechlevel)
									{
										$chance = round($shipavg / $max_tech_level) * 100;
									}
									else
									{
										$chance = 0;
									}

									$random_value = mt_rand(1,100);
									if ($targetshipdevice['dev_emerwarp']['amount'] > 0 && $random_value > $chance)
									{
										/* need to change warp destination to random sector in universe */
										if($targetinfo['player_id'] <= 3)
										{
											$rating_attack_ship = 0;
										}
										$rating_change=get_rating_change($playerinfo['rating'], $targetinfo['rating'], $rating_attack_ship, $targetinfo['player_id']);
										$source_sector = $shipinfo['sector_id'];
										$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe where sg_sector = 0 and sector_id > 3 ORDER BY rand()", 1);
										$dest_sector = $findem->fields['sector_id'];

										$debug_query = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$source_sector", 1);
										db_op_result($debug_query,__LINE__,__FILE__);
										$zones = $debug_query->fields;
										$debug_query->close();

										$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1,turns_used=turns_used+1,rating=rating+$rating_change WHERE player_id=$playerinfo[player_id]");
										db_op_result($debug_query,__LINE__,__FILE__);

										playerlog($targetinfo['player_id'], "LOG5_ATTACK_EWD", "$playerinfo[character_name]");

										$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET sector_id=$dest_sector, cleared_defenses=' ', on_planet='N' WHERE ship_id=$ship_id");
										db_op_result($debug_query,__LINE__,__FILE__);
										$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $targetshipdevice['dev_emerwarp']['device_id']);
										db_op_result($debug_query,__LINE__,__FILE__);

										log_move($targetinfo['player_id'],$targetship['ship_id'],$source_sector,$dest_sector,$shipinfo['class'],$shipinfo['cloak'],$zones['zone_id']);
										$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_ewd_engaged);
									}
									else
									{
										if ($targetshipdevice['dev_escapepod']['amount'] == 1)
										{
											$target_exchange_result[] = $l_cmb_escapepod_launched;
											player_ship_destroyed($ship_id, $targetinfo['player_id'], $targetinfo['rating'], $playerinfo['player_id'], $playerinfo['rating'], "killednovapod");
											playerlog($targetinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|Y");
											collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
										}
										else
										{
											$target_exchange_result[] = str_replace("[player]", $targetinfo['character_name'], $l_cmb_escapepod_failure);
											playerlog($targetinfo['player_id'], "LOG5_ATTACK_LOSE", "$playerinfo[character_name]|N");
											db_kill_player($targetinfo['player_id'], $playerinfo['player_id'], $playerinfo['rating'], "killednova");
											collect_bounty($playerinfo['player_id'],$targetinfo['player_id']);
										}
									}
								}
								$result4->MoveNext();
							}
							$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE storage_planet_id = $planet_id");
							db_op_result($debug_query,__LINE__,__FILE__);
							if ($debug_query > 0)
							{
								while (!$debug_query->EOF)
								{
									$ship_id = $debug_query->fields['ship_id'];
									$delete_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id = $ship_id");
									db_op_result($delete_query,__LINE__,__FILE__);
									$delete_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id = $ship_id");
									db_op_result($delete_query,__LINE__,__FILE__);
									$delete_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id = $ship_id");
									db_op_result($delete_query,__LINE__,__FILE__);
									$debug_query->MoveNext();
								}
							}
							$debug_query->close();
						}
						else
						{
							$target_exchange_result[] = $l_cmb_noshipslanded;
						}
						$result4->close();
						calc_ownership($shipinfo[sector_id]);
						playerlog($ownerinfo['player_id'], "LOG4_PLANET_novaED_D", "$planetinfo[name]|$shipinfo[sector_id]|$playerinfo[character_name]");
						gen_score($ownerinfo['player_id']);

						$playernames = $playerinfo['character_name'];
						insert_news($playernames, 1, "nova");
						artifacts_move($planet_id, 0, 0);
						close_database();

						$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
						$template_object->assign("target_exchange_result", $target_exchange_result);

						$template_object->assign("l_cmb_attack_exchange_results", $l_cmb_attack_exchange_results);
						$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
						$template_object->assign("l_igb_term", $l_igb_term);
						$template_object->assign("l_by_placebounty", $l_by_placebounty);
						$template_object->assign("gotomain", $l_global_mmenu);
						$template_object->assign("allow_ibank", $allow_ibank);
						$template_object->display($templatename."planet_unowned/nova_attack.tpl");
						include ("footer.php");
						die();
					}
					else
					{
						// damage planet and firing ship as nova was a miss

						$attacker_exchange_result = array();
						$target_exchange_result = array();

						$afteractionplanettech['sector_defense_weapons'] = floor($planetinfo['sector_defense_weapons'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['sector_defense_sensors'] = floor($planetinfo['sector_defense_sensors'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['sector_defense_cloak'] = floor($planetinfo['sector_defense_cloak'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['fighter'] = floor($planetinfo['fighter'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['sensors'] = floor($planetinfo['sensors'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['beams'] = floor($planetinfo['beams'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['torp_launchers'] = floor($planetinfo['torp_launchers'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['shields'] = floor($planetinfo['shields'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['jammer'] = floor($planetinfo['jammer'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['cloak'] = floor($planetinfo['cloak'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['torps'] = floor($planetinfo['torps'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['fighters'] = floor($planetinfo['fighters'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['colonists'] = floor($planetinfo['colonists'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['credits'] = floor($planetinfo['credits'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));
						$afteractionplanettech['energy'] = floor($planetinfo['energy'] * (rand(($dev_nova_damage - $shipdevice['dev_nova']['amount']), 100) * 0.01));

						$build_log_entry = $l_cmb_planet_tech_drop;
						$build_log_entry=str_replace("[sector_defense_weapons]","<font color=\"#00ff00\">". $planetinfo['sector_defense_weapons'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sector_defense_weapons_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_weapons'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sector_defense_sensors]","<font color=\"#00ff00\">". $planetinfo['sector_defense_sensors'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sector_defense_sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_sensors'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sector_defense_cloak]","<font color=\"#00ff00\">". $planetinfo['sector_defense_cloak'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sector_defense_cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_cloak'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $planetinfo['fighter'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionplanettech['fighter'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $planetinfo['sensors'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sensors'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $planetinfo['beams'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionplanettech['beams'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $planetinfo['torp_launchers'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionplanettech['torp_launchers'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $planetinfo['shields'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionplanettech['shields'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $planetinfo['cloak'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['cloak'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[jammer]","<font color=\"#00ff00\">". $planetinfo['jammer'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[jammer_new]","<font color=\"#ff0000\">". $afteractionplanettech['jammer'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $planetinfo['armor'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionplanettech['armor'] . "</font>",$build_log_entry);
						playerlog($planetinfo['owner'], "LOG5_AFTER_ACTION", $build_log_entry);

						$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET torps=$afteractionplanettech[torps], fighters=$afteractionplanettech[fighters], colonists=$afteractionplanettech[colonists], credits=$afteractionplanettech[credits], energy=$afteractionplanettech[energy], fighter=$afteractionplanettech[fighter], sensors=$afteractionplanettech[sensors], beams=$afteractionplanettech[beams], torp_launchers=$afteractionplanettech[torp_launchers], shields=$afteractionplanettech[shields], jammer=$afteractionplanettech[jammer], cloak=$afteractionplanettech[cloak] WHERE planet_id=$planet_id");
						db_op_result($debug_query,__LINE__,__FILE__);

						set_max_credits($planet_id);

						$target_exchange_result[] = $l_novabomb_novamiss;

						$playernames = $playerinfo['character_name'];
						insert_news($playernames, 1, "novamiss");

						if(rand(1, 100) <= $dev_nova_explode)
						{
							$averagetechlvl = ($shipinfo['hull'] + $shipinfo['engines'] + $shipinfo['power'] + $shipinfo['fighter'] + $shipinfo['sensors'] + $shipinfo['beams'] + $shipinfo['torp_launchers'] + $shipinfo['shields'] + $shipinfo['cloak'] + $shipinfo['armor'] + $shipinfo['ecm']) / 11;
							if($averagetechlvl > $dev_nova_destroylevel)
							{
								$attacker_exchange_result[] = "<font color='#ff0000' size='4'><B>$l_novabomb_novaexplode</B></font>";
								$afteractionshiptech = array();
								$afteractionshiptech['hull'] = max(0, floor($shipinfo_old['hull'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['engines'] = max(0, floor($shipinfo_old['engines'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['power'] = max(0, floor($shipinfo_old['power'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['fighter'] = max(0, floor($shipinfo_old['fighter'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['sensors'] = max(0, floor($shipinfo_old['sensors'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['beams'] = max(0, floor($shipinfo_old['beams'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['torp_launchers'] = max(0, floor($shipinfo_old['torp_launchers'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['shields'] = max(0, floor($shipinfo_old['shields'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['cloak'] = max(0, floor($shipinfo_old['cloak'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['armor'] = max(0, floor($shipinfo_old['armor'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['armor_pts'] = max(0, floor($shipinfo_old['armor_pts'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['torps'] = max(0, floor($shipinfo_old['torps'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['fighters'] = max(0, floor($shipinfo_old['fighters'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['credits'] = max(0, floor($shipinfo_old['credits'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['energy'] = max(0, floor($shipinfo_old['energy'] * (rand(50, 75) * 0.01)));
								$afteractionshiptech['ecm'] = max(0, floor($shipinfo_old['ecm'] * (rand(50, 75) * 0.01)));

								$build_log_entry = $l_cmb_attacker_tech_drop;
								$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
								$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
								playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

								if($afteractionshiptech['hull'] < $shipinfo_old['hull'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['engines'] < $shipinfo_old['engines'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['power'] < $shipinfo_old['power'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['fighter'] < $shipinfo_old['fighter'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['sensors'] < $shipinfo_old['sensors'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['beams'] < $shipinfo_old['beams'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['torp_launchers'] < $shipinfo_old['torp_launchers'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['shields'] < $shipinfo_old['shields'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['cloak'] < $shipinfo_old['cloak'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['ecm'] < $shipinfo_old['ecm'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}

								if($afteractionshiptech['armor'] < $shipinfo_old['armor'])
								{
									$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$l_cmb_attacker_tech_drop);
								}
								else
								{
									$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
									$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
								}
								$attacker_exchange_result[] = $l_cmb_attacker_tech_drop;

								$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET engines=$afteractionshiptech[engines], power=$afteractionshiptech[power], armor=$afteractionshiptech[armor], armor_pts=$afteractionshiptech[armor_pts], torps=$afteractionshiptech[torps], fighters=$afteractionshiptech[fighters], hull=$afteractionshiptech[hull], energy=$afteractionshiptech[energy], fighter=$afteractionshiptech[fighter], sensors=$afteractionshiptech[sensors], beams=$shipinfo[beams], torp_launchers=$afteractionshiptech[torp_launchers], shields=$afteractionshiptech[shields], cloak=$afteractionshiptech[cloak], ecm=$afteractionshiptech[ecm] WHERE ship_id=$shipinfo[ship_id]");
								db_op_result($debug_query,__LINE__,__FILE__);
							}
							else
							{
								$attacker_exchange_result[] = "<font color='#ff0000' size='4'><B>$l_planet_novaexplode2</B></font>";
								if ($shipdevice['dev_escapepod']['amount'] == 1) 
								{
									$attacker_exchange_result[] = $l_cmb_escapepod_launched;
									player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], 0, 0, "killednovabackfirepod");
									playerlog($shipinfo['player_id'],"LOG4_SHIP_novaED_D", "$playerinfo[character_name]|Y");
									$playernames = $playerinfo['character_name']."|".$playerinfo['character_name'];
									insert_news($playernames, 1, "targetepod");
								}
								else
								{
									$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
									playerlog($playerinfo['player_id'], "LOG4_SHIP_novaED_D", "$playerinfo[character_name]|N");
									db_kill_player($playerinfo['player_id'], 0, 0, "killednovabackfire");
									$playernames = $playerinfo['character_name']."|".$playerinfo['character_name'];
									insert_news($playernames, 1, "targetdies");
								}
							}
						}
						else
						{
							$attacker_exchange_result[] = $l_novabomb_ship_survived;
						}

						$max_sector_defense_fighters = 0;
						$max_defense = $db->Execute("SELECT sector_defense_weapons from {$db_prefix}planets where owner = 2 and sector_id = $planetinfo[sector_id] and base = 'Y'");
						db_op_result($max_defense,__LINE__,__FILE__);
						while (!$max_defense->EOF)
						{
							$max_sector_defense_fighters += NUM_PER_LEVEL($max_defense->fields['sector_defense_weapons']) * $sector_fighter_multiplier;
							$max_defense->MoveNext();
						}
						$max_defense->close();

						// move fighters and toprs from planet to sector defense
						$res = $db->SelectLimit("SELECT * from {$db_prefix}sector_defense where defense_type = 'fighters' and player_id=$planetinfo[owner] and sector_id=$shipinfo[sector_id]", 1);
						$row = $res->fields;
						$res->close();
						$energy_required = ROUND($row['quantity'] * $energy_per_fighter);
						$res4 = $db->Execute("SELECT IFNULL(SUM(energy),0) as energy_available from {$db_prefix}planets where owner = $planetinfo[owner] and sector_id = $shipinfo[sector_id]"); 
						$energy_available = $res4->fields['energy_available'];
						$res4->close();
						$availiblefighters = max(0, (NUM_FIGHTERS($planetinfo['sector_defense_weapons']) - $row['quantity']));
						$maxfighters = min(min(floor(($energy_available - $energy_required) / $energy_per_fighter), $availiblefighters), $max_sector_defense_fighters);
						if($planetinfo['fighters'] < $maxfighters)
						{
							$maxfighters = $planetinfo['fighters'];
						}
						$addfighters = floor($maxfighters * (rand(10, 30) * 0.01));

						$res = $db->SelectLimit("SELECT * from {$db_prefix}sector_defense where defense_type = 'mines' and player_id=$planetinfo[owner] and sector_id=$shipinfo[sector_id]", 1);
						$row = $res->fields;
						$res->close();
						$maxmines = max(0, (NUM_TORPEDOES($planetinfo['sector_defense_weapons']) - $row['quantity']));
						if($planetinfo['torps'] < $maxmines)
						{
							$maxmines = $planetinfo['torps'];
						}
						$addmines = floor($maxmines * (rand(10, 20) * 0.01));

// Start of quick hack until sector_defense_battle() function finished
// Whomever had the most fighters wins.  And the winner has a ratio of what attacked them removed from both fighters and mines.
// The loser has everything wiped.

						$resultSDb = $db->Execute("SELECT SUM({$db_prefix}sector_defense.quantity) as total from {$db_prefix}sector_defense, {$db_prefix}players WHERE 
								{$db_prefix}sector_defense.sector_id=$shipinfo[sector_id] and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]'
								and (({$db_prefix}players.player_id = {$db_prefix}sector_defense.player_id) and ({$db_prefix}players.team != $playerinfo[team] or $playerinfo[team] = 0)) and {$db_prefix}sector_defense.defense_type = 'fighters'");
						db_op_result($resultSDb,__LINE__,__FILE__);

						if($resultSDb->recordcount() > 0)
						{
							$total_fighters += $resultSDb->fields['quantity'];
							if($total_fighters > $addfighters)
							{
								$ratio_left = 1 - ($addfighters / $total_fighters);
								$addfighters = 0;
								$addmines = 0;
								$resultSDb = $db->Execute("UPDATE {$db_prefix}sector_defense, {$db_prefix}players SET {$db_prefix}sector_defense.quantity = {$db_prefix}sector_defense.quantity * $ratio_left WHERE 
										{$db_prefix}sector_defense.sector_id=$shipinfo[sector_id] and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]'
										and (({$db_prefix}players.player_id = {$db_prefix}sector_defense.player_id) and ({$db_prefix}players.team != $playerinfo[team] or $playerinfo[team] = 0))");
								db_op_result($resultSDb,__LINE__,__FILE__);
							}
							else
							{
								$resultSDb = $db->Execute("SELECT {$db_prefix}sector_defense.defense_id from {$db_prefix}sector_defense, {$db_prefix}players WHERE 
										{$db_prefix}sector_defense.sector_id=$shipinfo[sector_id] and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]'
										and (({$db_prefix}players.player_id = {$db_prefix}sector_defense.player_id) and ({$db_prefix}players.team != $playerinfo[team] or $playerinfo[team] = 0))");
								db_op_result($resultSDb,__LINE__,__FILE__);
								while (!$resultSDb->EOF)
								{
									$defense_id = $resultSDb->fields['defense_id'];
									$res2 = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE defense_id = $defense_id");
									$resultSDb->MoveNext();
								}
								$ratio_left = 1 - ($total_fighters / $addfighters);
								$addfighters *= $ratio_left;
								$addmines *= $ratio_left;
							}
						}

						if ($addfighters > 0)
						{
							if ($fighter_id != 0)
							{
								$fighter_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $addfighters " .
															"where defense_id = $fighter_id");
								db_op_result($fighter_query,__LINE__,__FILE__);
							}
							else
							{
								$fighter_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
															"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
															"($planetinfo[owner], $shipinfo[sector_id], 'fighters',$addfighters, 'Sector_Fighter')");
								db_op_result($fighter_query,__LINE__,__FILE__);
							}
						}

						if ($addmines > 0)
						{
							$res = $db->Execute("SELECT * from {$db_prefix}sector_defense where defense_type = 'mines' and player_id=$planetinfo[owner] and sector_id=$shipinfo[sector_id]");
							$row = $res->fields;
							$res->close();
							if ($row['defense_id'] != 0)
							{
								$mines_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $addmines " .
															"where defense_id = $row[defense_id]");
								db_op_result($mines_query,__LINE__,__FILE__);
							}
							else
							{
								$mines_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
															"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
															"($planetinfo[owner], $shipinfo[sector_id], 'mines',$addmines, 'Sector_Mine')");
								db_op_result($mines_query,__LINE__,__FILE__);
							}
						}
// End of quick hack until sector_defense_battle() function finished

//						sector_defense_battle($fighter_id, $addfighters, $addmines);
						$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
						$template_object->assign("target_exchange_result", $target_exchange_result);

						$template_object->assign("l_cmb_attack_exchange_results", $l_cmb_attack_exchange_results);
						$template_object->assign("planet_id", $planet_id);
						$template_object->assign("l_clickme", $l_clickme);
						$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
						$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
						$template_object->assign("l_igb_term", $l_igb_term);
						$template_object->assign("l_by_placebounty", $l_by_placebounty);
						$template_object->assign("gotomain", $l_global_mmenu);
						$template_object->assign("allow_ibank", $allow_ibank);
						$template_object->display($templatename."planet_unowned/nova_miss.tpl");
						include ("footer.php");
						die();
					}
				}
				else
				{
					// nova backfires damaging or destroying attackers ship 
					$attacker_exchange_result = array();
					$averagetechlvl = ($shipinfo['hull'] + $shipinfo['engines'] + $shipinfo['power'] + $shipinfo['fighter'] + $shipinfo['sensors'] + $shipinfo['beams'] + $shipinfo['torp_launchers'] + $shipinfo['shields'] + $shipinfo['cloak'] + $shipinfo['armor'] + $shipinfo['ecm']) / 11;
					if($averagetechlvl > $dev_nova_destroylevel)
					{
						$attacker_exchange_result[] = "<font color=\"#ff0000\" size=\"4\"><B>$l_novabomb_novaexplode</B></font>";

						$afteractionshiptech = array();
						$afteractionshiptech['hull'] = max(0, floor($shipinfo_old['hull'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['engines'] = max(0, floor($shipinfo_old['engines'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['power'] = max(0, floor($shipinfo_old['power'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['fighter'] = max(0, floor($shipinfo_old['fighter'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['sensors'] = max(0, floor($shipinfo_old['sensors'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['beams'] = max(0, floor($shipinfo_old['beams'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['torp_launchers'] = max(0, floor($shipinfo_old['torp_launchers'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['shields'] = max(0, floor($shipinfo_old['shields'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['cloak'] = max(0, floor($shipinfo_old['cloak'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['armor'] = max(0, floor($shipinfo_old['armor'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['armor_pts'] = max(0, floor($shipinfo_old['armor_pts'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['torps'] = max(0, floor($shipinfo_old['torps'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['fighters'] = max(0, floor($shipinfo_old['fighters'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['credits'] = max(0, floor($shipinfo_old['credits'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['energy'] = max(0, floor($shipinfo_old['energy'] * (rand(50, 75) * 0.01)));
						$afteractionshiptech['ecm'] = max(0, floor($shipinfo_old['ecm'] * (rand(50, 75) * 0.01)));

						$build_log_entry = $l_cmb_attacker_tech_drop;
						$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$build_log_entry);
						$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
						playerlog($playerinfo['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

						if($afteractionshiptech['hull'] < $shipinfo_old['hull'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[hull]","<font color=\"#00ff00\">". $shipinfo_old['hull'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[hull_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['engines'] < $shipinfo_old['engines'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[engines]","<font color=\"#00ff00\">". $shipinfo_old['engines'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[engines_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['power'] < $shipinfo_old['power'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[power]","<font color=\"#00ff00\">". $shipinfo_old['power'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[power_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['fighter'] < $shipinfo_old['fighter'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[fighter]","<font color=\"#00ff00\">". $shipinfo_old['fighter'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[fighter_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['sensors'] < $shipinfo_old['sensors'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[sensors]","<font color=\"#00ff00\">". $shipinfo_old['sensors'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[sensors_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['beams'] < $shipinfo_old['beams'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[beams]","<font color=\"#00ff00\">". $shipinfo_old['beams'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[beams_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['torp_launchers'] < $shipinfo_old['torp_launchers'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[torps]","<font color=\"#00ff00\">". $shipinfo_old['torp_launchers'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[torps_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['shields'] < $shipinfo_old['shields'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[shields]","<font color=\"#00ff00\">". $shipinfo_old['shields'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[shields_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['cloak'] < $shipinfo_old['cloak'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[cloak]","<font color=\"#00ff00\">". $shipinfo_old['cloak'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[cloak_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['ecm'] < $shipinfo_old['ecm'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[ecm]","<font color=\"#00ff00\">". $shipinfo_old['ecm'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[ecm_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}

						if($afteractionshiptech['armor'] < $shipinfo_old['armor'])
						{
							$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$l_cmb_attacker_tech_drop);
						}
						else
						{
							$l_cmb_attacker_tech_drop=str_replace("[armor]","<font color=\"#00ff00\">". $shipinfo_old['armor'] . "</font>",$l_cmb_attacker_tech_drop);
							$l_cmb_attacker_tech_drop=str_replace("[armor_new]","<font color=\"#ff0000\">". $l_none . "</font>",$l_cmb_attacker_tech_drop);
						}
						$attacker_exchange_result[] = $l_cmb_attacker_tech_drop;

						$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET engines=$afteractionshiptech[engines], power=$afteractionshiptech[power], armor=$afteractionshiptech[armor], armor_pts=$afteractionshiptech[armor_pts], torps=$afteractionshiptech[torps], fighters=$afteractionshiptech[fighters], hull=$afteractionshiptech[hull], energy=$afteractionshiptech[energy], fighter=$afteractionshiptech[fighter], sensors=$afteractionshiptech[sensors], beams=$afteractionshiptech[beams], torp_launchers=$afteractionshiptech[torp_launchers], shields=$afteractionshiptech[shields], cloak=$afteractionshiptech[cloak], ecm=$afteractionshiptech[ecm] WHERE ship_id=$shipinfo[ship_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
					else
					{
						$attacker_exchange_result[] = "<font color='#ff0000' size='4'><B>$l_novabomb_novaexplode2</B></font>";
						if ($shipdevice['dev_escapepod']['amount'] == 1) 
						{
							$attacker_exchange_result[] = $l_cmb_escapepod_launched;
							player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], 0, 0, "killednovabackfirepod");
							playerlog($shipinfo['player_id'],"LOG4_SHIP_novaED_D", "$playerinfo[character_name]|Y");
							$playernames = $playerinfo['character_name']."|".$playerinfo['character_name'];
							insert_news($playernames, 1, "targetepod");
						}
						else
						{
							$attacker_exchange_result[] = $l_cmb_attacker_escapepod_failure;
							playerlog($playerinfo['player_id'], "LOG4_SHIP_novaED_D", "$playerinfo[character_name]|N");
							db_kill_player($playerinfo['player_id'], 0, 0, "killednovabackfire");
							$playernames = $playerinfo['character_name']."|".$playerinfo['character_name'];
							insert_news($playernames, 1, "targetdies");
						}
					}

					$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 0);
					$template_object->assign("isfedbounty", $isfedbounty);
					$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);
					$template_object->assign("l_by_nofedbounty", $l_by_nofedbounty);

					$template_object->assign("attacker_exchange_result", $attacker_exchange_result);
					$template_object->assign("l_cmb_attack_exchange_results", $l_cmb_attack_exchange_results);
					$template_object->assign("planet_id", $planet_id);
					$template_object->assign("l_clickme", $l_clickme);
					$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
					$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
					$template_object->assign("l_igb_term", $l_igb_term);
					$template_object->assign("l_by_placebounty", $l_by_placebounty);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->assign("allow_ibank", $allow_ibank);
					$template_object->display($templatename."planet_unowned/nova_backfire.tpl");
					include ("footer.php");
					die();
				}
			}
			else
			{
				$template_object->assign("error_msg", str_replace("[turns]", $dev_nova_turnsused, $l_novabomb_turns));
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."attackdie.tpl");
				include("footer.php");
				die();
			}
		}
		else
		{
			$template_object->assign("error_msg", $l_novabomb_notfedsec);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."attackdie.tpl");
			include("footer.php");
			die();
		}
	}
	else
	{
		$template_object->assign("error_msg", $l_novabomb_nonova);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."attackdie.tpl");
		include("footer.php");
		die();
	}
}
else
{
	$template_object->assign("error_msg", $l_novabomb_wrongclass);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."attackdie.tpl");
	include("footer.php");
	die();
}

?>