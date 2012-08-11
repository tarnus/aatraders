<?php
// 1
// 1800
// 5
// 0
// Y
// How often to move the Alliance Leader ship and attack players with an Alliance Only Bounty.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/send_system_im.inc");
include ("globals/get_player.inc");
include ("globals/insert_news.inc");

TextFlush ( "<B>Alliance Ship</B><BR>");

include ("globals/combat_functions.inc");

$curtime = TIME();

$res5 = $db->Execute("SELECT count(*) as bounty_count,bounty_on  FROM {$db_prefix}bounty WHERE placed_by = 1 group by bounty_on order by bounty_count desc");
db_op_result($res5,__LINE__,__FILE__);
$j = 0;
$attackflag=0;
if ($res5->RecordCount() > 0)
{
	while (!$res5->EOF)
	{
		$bounty_details = $res5->fields;
		if ($bounty_details['bounty_count'] >= $fed_collection_start && $bounty_details['bounty_count'] < $fed_collection_start2)
		{
			// bounty limit reached see if online.
			if ($attackflag ==0)
			{
				$variance = mt_rand(1,18000) - 9000;
				$res_play = $db->Execute("SELECT * FROM {$db_prefix}players,{$db_prefix}ships WHERE  destroyed !='Y' and currentship =ship_id and on_planet='N' and  {$db_prefix}players.player_id=$bounty_details[bounty_on] and ((($curtime - UNIX_TIMESTAMP({$db_prefix}players.last_login) )/60 ) < 5 ) and ((alliance_attack_date= '0000-00-00 00:00:00') or ((UNIX_TIMESTAMP('" . date("Y-m-d H:i:s") . "') - (UNIX_TIMESTAMP(alliance_attack_date)+$variance)) > 86400 ))");
				db_op_result($res_play,__LINE__,__FILE__);
				if ($res_play->RecordCount() > 0)
				{
					while (!$res_play->EOF)
					{
						$player_details = $res_play->fields;

						if (($player_details['alliance_bounty_count'] < $fed_collection_start2) || ($bounty_details['bounty_count'] >= $fed_collection_start))
						{
							// You have a candidate
							// Move to sector
							$query = "UPDATE {$db_prefix}ships SET  sector_id=$player_details[sector_id]  WHERE ship_id=1";
							$debug_query = $db->Execute("$query");
							db_op_result($debug_query,__LINE__,__FILE__);
							// execute an armor attack and do damage
							$perc_damage=mt_rand(10, 30)/100;
							calc_internal_damage($player_details['ship_id'], 0, $perc_damage);
							// esitmate level costs
							// reduce fed bounty by cost
							$query = "select * from {$db_prefix}ships WHERE ship_id=$player_details[currentship]";
							$debug_query = $db->Execute("$query");
							db_op_result($debug_query,__LINE__,__FILE__);
							if ($debug_query->RecordCount() > 0)
							{
								$bounty_ship = $debug_query->fields;
								$total_cost=phpchangeDelta($bounty_ship['hull_normal'],$bounty_ship['hull'])+
								phpchangeDelta($bounty_ship['engines_normal'],$bounty_ship['engines'])+
								phpchangeDelta($bounty_ship['power_normal'],$bounty_ship['power'])+
								phpchangeDelta($bounty_ship['fighter_normal'],$bounty_ship['fighter'])+
								phpchangeDelta($bounty_ship['sensors_normal'],$bounty_ship['sensors'])+
								phpchangeDelta($bounty_ship['beams_normal'],$bounty_ship['beams'])+
								phpchangeDelta($bounty_ship['armor_normal'],$bounty_ship['armor'])+
								phpchangeDelta($bounty_ship['torp_launchers_normal'],$bounty_ship['torp_launchers'])+
								phpchangeDelta($bounty_ship['shields_normal'],$bounty_ship['shields'])+
								phpchangeDelta($bounty_ship['cloak_normal'],$bounty_ship['cloak'])+
								phpchangeDelta($bounty_ship['ecm_normal'],$bounty_ship['ecm']);
								$total_cost = round($total_cost * ($repair_modifier / 100));

								$getbountyid = $db->Execute("SELECT * FROM {$db_prefix}bounty WHERE placed_by = 1  and bounty_on=$player_details[player_id] order by bounty_id ");
								db_op_result($getbountyid,__LINE__,__FILE__);
								$temptotal=$total_cost;	
								if ($getbountyid->RecordCount() > 0)
								{
									while (!$getbountyid->EOF)
									{
										$bounty = $getbountyid->fields;
										if ($bounty['amount']<= $temptotal){
											$bountyupdate = $db->Execute("delete from  {$db_prefix}bounty  where bounty_id=$bounty[bounty_id]");
											db_op_result($bountyupdate,__LINE__,__FILE__);
											$temptotal=$temptotal-$bounty['amount'];
										}else{
											$bountyupdate = $db->Execute("update {$db_prefix}bounty set amount=amount-$temptotal where bounty_id=$bounty[bounty_id]");
											$temptotal=0;
											db_op_result($bountyupdate,__LINE__,__FILE__);
										}
										$getbountyid->MoveNext();	
									}
								}
								$getbountyid->close();
							}
							$debug_query->close();
							// update attack date
							$query = "UPDATE {$db_prefix}players SET  alliance_attack_date='" . date("Y-m-d H:i:s") . "'  WHERE player_id=$player_details[player_id]";
							$debug_query = $db->Execute("$query");
							db_op_result($debug_query,__LINE__,__FILE__);
							$query = "UPDATE {$db_prefix}ships SET  armor_pts=armor_pts*(1-$perc_damage),fighters=fighters*(1-$perc_damage)  WHERE ship_id=$player_details[currentship]";
							$debug_query = $db->Execute("$query");
							db_op_result($debug_query,__LINE__,__FILE__);
							//put attack message in log
							$playername=get_player($player_details['player_id']);
							send_system_im($player_details['player_id'], "Alliance Attack!", "Your ship was attacked by Alliance Leader. You battle for a while, then the fight breaks down. You lost armor points and fighters in the skirmish.",$player_details['last_login']);
							playerlog($player_details['player_id'], "LOG5_ATTACKED_WIN", "ALLIANCE||");
							adminlog("LOG0_RAW","<font color=yellow><B>Alliance Bounty Attack:</B></font>Bountied Player " . get_player($player_details[player_id]) . " -  Bounty Reduced by:<B> " . NUMBER($total_cost) . "</B><br>Tech Damage Percentage:<B> " . ($perc_damage * 100) . "</b>");
							TextFlush ( "<B>Alliance Bounty attack on $playername  </B><BR>");

							$sector_check = $db->SelectLimit("SELECT sector_name,zone_id FROM {$db_prefix}universe WHERE sector_id='$player_details[sector_id]'", 1);
							if($sector_check->RecordCount()){
								$sect = $sector_check->fields;
								$sectorname = $sect['sector_name'];
								$player_details['zone_id'] = $sect['zone_id'];
							}
							$sector_check->close();
							if($player_details['zone_id'] == 2)
							{
								TextFlush ( "...towing $playername out of $row[sector_id] ...");
								$randplay=mt_rand(0,($sector_list_total-1));
								$player_details['sector_id'] = $sector_list[$randplay]['sector_id'];
								$sector_check = $db->SelectLimit("SELECT sector_name,zone_id FROM {$db_prefix}universe WHERE sector_id='$player_details[sector_id]'", 1);

								if($sector_check->RecordCount()){
									$sect = $sector_check->fields;
									$sectorname = $sect['sector_name'];
									$player_details['zone_id'] = $sect['zone_id'];
								}
								$sector_check->close();
								TextFlush ( " to sector $sectorname.<br>");
								$debug_query1 = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$player_details[sector_id],cleared_defenses=' ' where ship_id=$player_details[ship_id]");
								db_op_result($debug_query1,__LINE__,__FILE__);
								$debug_query1->close();

								playerlog($player_details['player_id'], "LOG0_TOW", "$player_details[sector_id]|$newsector|$player_details[max_hull]");
								log_move($player_details['player_id'],$player_details['ship_id'],$player_details['sector_id'],$newsector,$player_details['class'],$player_details['cloak'],$player_details['zone_id']);
							}
                            
                             // added 4-14-2010 for new fed stuff
                           $sectorname_old=$sectorname;
                           if ($player_details['fed_bounty_count'] < 3){
                               $sectorname="UNKNOWN";
                           }  
							$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES (1,'Alliance'," . time() . ",'Alliance bounty player $playername in sector $sectorname',0) ");

							insert_news($playername."|".$total_cost, $player_details['player_id'], "alliancecolbounty");
                             $sectorname=$sectorname_old;
							$attackflag++;
							$res_play->MoveNext();
						}
					}//end while
				}
				$res_play->close();
			}
		}
		$j++;
		
		$res5->MoveNext();
	}
}
$res5->close();

$curtime = TIME();

$variance = mt_rand(1,18000) - 9000;
$res_play = $db->Execute("SELECT * FROM {$db_prefix}players,{$db_prefix}ships WHERE  destroyed !='Y' and currentship =ship_id and on_planet='N' and (({$db_prefix}players.fed_bounty_count + {$db_prefix}players.alliance_bounty_count) >= $fed_collection_start2 and ({$db_prefix}players.fed_bounty_count + {$db_prefix}players.alliance_bounty_count) < $fed_collection_start3 and ({$db_prefix}players.fed_bounty_count < {$db_prefix}players.alliance_bounty_count)) and ((($curtime - UNIX_TIMESTAMP({$db_prefix}players.last_login) )/60 ) < 5 ) and ((alliance_attack_date= '0000-00-00 00:00:00') or ((UNIX_TIMESTAMP('" . date("Y-m-d H:i:s") . "') - (UNIX_TIMESTAMP(alliance_attack_date)+$variance)) > 86400 ))");
db_op_result($res_play,__LINE__,__FILE__);
if ($res_play->RecordCount() > 0)
{
	while (!$res_play->EOF)
	{
		$player_details = $res_play->fields;
		// You have a candidate
		// Move to sector
		$query = "UPDATE {$db_prefix}ships SET  sector_id=$player_details[sector_id] WHERE ship_id=3";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);
		// execute an armor attack and do damage
		$perc_damage=mt_rand(20, 50)/100;
		calc_internal_damage($player_details['ship_id'], 0, $perc_damage);
		// esitmate level costs
		// reduce fed bounty by cost
		$query = "select * from {$db_prefix}ships WHERE ship_id=$player_details[currentship]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);
		if ($debug_query->RecordCount() > 0)
		{
			$bounty_ship = $debug_query->fields;
			$total_cost=phpchangeDelta($bounty_ship['hull_normal'],$bounty_ship['hull'])+
			phpchangeDelta($bounty_ship['engines_normal'],$bounty_ship['engines'])+
			phpchangeDelta($bounty_ship['power_normal'],$bounty_ship['power'])+
			phpchangeDelta($bounty_ship['fighter_normal'],$bounty_ship['fighter'])+
			phpchangeDelta($bounty_ship['sensors_normal'],$bounty_ship['sensors'])+
			phpchangeDelta($bounty_ship['beams_normal'],$bounty_ship['beams'])+
			phpchangeDelta($bounty_ship['armor_normal'],$bounty_ship['armor'])+
			phpchangeDelta($bounty_ship['torp_launchers_normal'],$bounty_ship['torp_launchers'])+
			phpchangeDelta($bounty_ship['shields_normal'],$bounty_ship['shields'])+
			phpchangeDelta($bounty_ship['cloak_normal'],$bounty_ship['cloak'])+
			phpchangeDelta($bounty_ship['ecm_normal'],$bounty_ship['ecm']);
			$total_cost = round($total_cost * ($repair_modifier / 100));

			$getbountyid = $db->Execute("SELECT * FROM {$db_prefix}bounty WHERE placed_by = 1  and bounty_on=$player_details[player_id] order by bounty_id ");
			db_op_result($getbountyid,__LINE__,__FILE__);
			$temptotal=$total_cost;	
			if ($getbountyid->RecordCount() > 0)
			{
				while (!$getbountyid->EOF)
				{
					$bounty = $getbountyid->fields;
					if ($bounty['amount']<= $temptotal){
						$bountyupdate = $db->Execute("delete from  {$db_prefix}bounty  where bounty_id=$bounty[bounty_id]");
						db_op_result($bountyupdate,__LINE__,__FILE__);
						$temptotal=$temptotal-$bounty['amount'];
					}else{
						$bountyupdate = $db->Execute("update {$db_prefix}bounty set amount=amount-$temptotal where bounty_id=$bounty[bounty_id]");
						$temptotal=0;
						db_op_result($bountyupdate,__LINE__,__FILE__);
					}
					$getbountyid->MoveNext();	
				}
			}
			$getbountyid->close();
		}
		$debug_query->close();
		// update attack date
		$query = "UPDATE {$db_prefix}players SET  alliance_attack_date='" . date("Y-m-d H:i:s") . "' WHERE player_id=$player_details[player_id]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);
		$query = "UPDATE {$db_prefix}ships SET  armor_pts=armor_pts*(1-$perc_damage),fighters=fighters*(1-$perc_damage)  WHERE ship_id=$player_details[currentship]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);
		//put attack message in log
		$playername=get_player($player_details['player_id']);

		send_system_im($player_details['player_id'], "Alliance Attack!", "Your ship was attacked by Alliance Leader. You battle for a while, then the fight breaks down. You lost armor points and fighters in the skirmish.",$player_details['last_login']);
		playerlog($player_details['player_id'], "LOG5_ATTACKED_WIN", "ALLIANCE||");
		adminlog("LOG0_RAW","<font color=yellow><B>ALLIANCE Bounty Attack:</B></font>Bountied Player " . get_player($player_details[player_id]) . " -  Bounty Reduced by:<B> " . NUMBER($total_cost) . "</B><br>Tech Damage Percentage:<B> " . ($perc_damage * 100) . "</b>");
		TextFlush ( "<B>ALLIANCE Bounty attack on $playername  </B><BR>");
		$sector_check = $db->SelectLimit("SELECT sector_name,zone_id FROM {$db_prefix}universe WHERE sector_id='$player_details[sector_id]'", 1);
		if($sector_check->RecordCount()){
			$sect = $sector_check->fields;
			$sectorname = $sect['sector_name'];
			$player_details['zone_id'] = $sect['zone_id'];
		}
		$sector_check->close();
		if($player_details['zone_id'] == 2)
		{
			TextFlush ( "...towing $playername out of $row[sector_id] ...");
			$randplay=mt_rand(0,($sector_list_total-1));
			$player_details['sector_id'] = $sector_list[$randplay]['sector_id'];
			$sector_check = $db->SelectLimit("SELECT sector_name,zone_id FROM {$db_prefix}universe WHERE sector_id='$player_details[sector_id]'", 1);

			if($sector_check->RecordCount()){
				$sect = $sector_check->fields;
				$sectorname = $sect['sector_name'];
				$player_details['zone_id'] = $sect['zone_id'];
			}
			$sector_check->close();
			TextFlush ( " to sector $sectorname.<br>");
			$debug_query1 = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$player_details[sector_id],cleared_defenses=' ' where ship_id=$player_details[ship_id]");
			db_op_result($debug_query1,__LINE__,__FILE__);
			$debug_query1->close();

			playerlog($player_details['player_id'], "LOG0_TOW", "$player_details[sector_id]|$newsector|$player_details[max_hull]");
			log_move($player_details['player_id'],$player_details['ship_id'],$player_details['sector_id'],$newsector,$player_details['class'],$player_details['cloak'],$player_details['zone_id']);
		}
		$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES (1,'ALLIANCE'," . time() . ",'Fed bounty player $playername in sector $sectorname',0) ");

		insert_news($playername."|".$total_cost, $player_details['player_id'], "alliancecolbounty");
		$attackflag++;
		$res_play->MoveNext();
	}//end while
}
$res_play->close();


$curtime = TIME();

$variance = mt_rand(1,18000) - 9000;
$res_play = $db->Execute("SELECT * FROM {$db_prefix}players WHERE destroyed != 'Y' and ((fed_bounty_count + alliance_bounty_count) >= $fed_collection_start3 and (fed_bounty_count < alliance_bounty_count)) and ((alliance_attack_date= '0000-00-00 00:00:00') or ((UNIX_TIMESTAMP('" . date("Y-m-d H:i:s") . "') - (UNIX_TIMESTAMP(alliance_attack_date)+$variance)) > 86400 ))");
db_op_result($res_play,__LINE__,__FILE__);
if ($res_play->RecordCount() > 0)
{
	while (!$res_play->EOF)
	{
		$player_details = $res_play->fields;
		// You have a candidate
		// Move to sector
		$res_ship = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id = $player_details[player_id] order by class desc", 1);
		db_op_result($res_ship,__LINE__,__FILE__);

		$ship_info = $res_ship->fields;

		if($ship_info['class'] > $start_ship_class)
		{
			$total_cost=phpchangeDelta($ship_info['hull_normal'],0)+
				phpchangeDelta($ship_info['engines_normal'],0)+
				phpchangeDelta($ship_info['power_normal'],0)+
				phpchangeDelta($ship_info['fighter_normal'],0)+
				phpchangeDelta($ship_info['sensors_normal'],0)+
				phpchangeDelta($ship_info['beams_normal'],0)+
				phpchangeDelta($ship_info['armor_normal'],0)+
				phpchangeDelta($ship_info['torp_launchers_normal'],0)+
				phpchangeDelta($ship_info['shields_normal'],0)+
				phpchangeDelta($ship_info['cloak_normal'],0)+
				phpchangeDelta($ship_info['ecm_normal'],0);

			if ($player_details['currentship'] == $ship_info['ship_id'])
			{
				$res = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id = $start_ship_class", 1);
				db_op_result($res,__LINE__,__FILE__);
				$shipdata = $res->fields;
				$res->close();
				$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET class=$start_ship_class, basehull=$shipdata[basehull], hull=$shipdata[minhull],engines=$shipdata[minengines],
										power=$shipdata[minpower],sensors=$shipdata[minsensors],fighter=$shipdata[minfighter],beams=$shipdata[minbeams],torp_launchers=$shipdata[mintorp_launchers],torps=0,armor=$shipdata[minarmor],armor_pts=$start_armor,cloak=$shipdata[mincloak],
										shields=$shipdata[minshields],ecm=$shipdata[minecm],sector_id=1,energy=$start_energy,fighters=$start_fighters, on_planet='N', planet_id=0, storage_planet_id=0,
										hull_normal=$shipdata[minhull],engines_normal=$shipdata[minengines],power_normal=$shipdata[minpower],sensors_normal=$shipdata[minsensors],fighter_normal=$shipdata[minfighter],beams_normal=$shipdata[minbeams],
										torp_launchers_normal=$shipdata[mintorp_launchers],armor_normal=$shipdata[minarmor],cloak_normal=$shipdata[mincloak],shields_normal=$shipdata[minshields], ecm_normal=$shipdata[minecm] 
										WHERE ship_id=$ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
//
				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount = 0 WHERE ship_id=$ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_holds SET amount = 0 WHERE ship_id=$ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
//
			}
			else
			{
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_holds WHERE ship_id=$ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("DELETE FROM {$db_prefix}ship_devices WHERE ship_id=$ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE ship_id=$ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE ship_id = $ship_info[ship_id]"); 
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE ship_id = $ship_info[ship_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			//put attack message in log
			$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$ship_info[sector_id]'", 1);

			if($sector_check->RecordCount()){
				$sect = $sector_check->fields;
				$sectorname = $sect['sector_name'];
			}
			$sector_check->close();

			$res_ship = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$ship_info[class]", 1);
			db_op_result($res_ship,__LINE__,__FILE__);
			$shiptype = $res_ship->fields['name'];
			$total_cost += $res_ship->fields['cost_tobuild'];

			send_system_im($player_details['player_id'], "Alliance Confiscation!", "Your ship was confiscated by the Alliance Leader. You lost the following ship: " . $shiptype, $player_details['last_login']);
			playerlog($player_details['player_id'], "LOG5_CONFISCATION", "the Alliance|$shiptype");
			adminlog("LOG0_RAW","<font color=yellow><B>Alliance Bounty Confiscation:</B></font>Bountied Player " . $player_details['character_name'] . " -  $shiptype Ship Confiscated!</b>");
			TextFlush ( "<B>Alliance Bounty Ship Confiscation on $player_details[character_name]</B><BR>");
			$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES (1,'Alliance'," . time() . ",'The Alliance confiscated a ship ($shiptype) from " . $player_details['character_name'] . " in sector $sectorname for too many bounty attacks.',0) ");

			insert_news($player_details['character_name']."|".$total_cost."|".$shiptype."|".$sectorname, $player_details['player_id'], "alliancecol_sbounty");
		}
		else
		{
			$calc_planet_defense = "(fighters * $fighter_price) + (torps * $torpedo_price) + if (base='Y', $base_credits, 0)";
			$calc_planet_credits = "credits + hidden_credits";

			$calc_planet_fighter = "exp(fighter * log(GREATEST($planet_upgrade_factor, 1)))";
			$calc_planet_sensors = "exp(sensors * log(GREATEST($planet_upgrade_factor, 1)))";
			$calc_planet_beams = "exp(beams * log(GREATEST($planet_upgrade_factor, 1)))";
			$calc_planet_torp_launchers = "exp(torp_launchers * log(GREATEST($planet_upgrade_factor, 1)))";
			$calc_planet_shields = "exp(shields * log(GREATEST($planet_upgrade_factor, 1)))";
			$calc_planet_jammer = "exp(jammer * log(GREATEST($planet_upgrade_factor, 1)))";
			$calc_planet_cloak = "exp(cloak * log(GREATEST($planet_upgrade_factor, 1)))";

			$calc_planet_sector_defense_weapons = "exp(sector_defense_weapons * log(GREATEST($planet_SD_upgrade_factor, 1)))";
			$calc_planet_sector_defense_sensors = "exp(sector_defense_sensors * log(GREATEST($planet_SD_upgrade_factor, 1)))";
			$calc_planet_sector_defense_cloak = "exp(sector_defense_cloak * log(GREATEST($planet_SD_upgrade_factor, 1)))";
			 //Add $calc_planet_armor if necessary
			$calc_planet_def_levels = "($calc_planet_fighter + $calc_planet_sensors + $calc_planet_beams + $calc_planet_torp_launchers + $calc_planet_shields + $calc_planet_jammer + $calc_planet_cloak + $calc_planet_sector_defense_weapons + $calc_planet_sector_defense_sensors + $calc_planet_sector_defense_cloak)*$upgrade_cost";

			$res_planet = $db->SelectLimit("SELECT planet_id, sector_id, name, $calc_planet_defense + $calc_planet_credits + $calc_planet_def_levels " . $calc_planets . " AS score FROM {$db_prefix}planets WHERE owner=$player_details[player_id] order by score desc", 1);
			db_op_result($res_planet,__LINE__,__FILE__);
			$planet_info = $res_planet->fields;
			$planet_count = $res_planet->RecordCount();
			$res_planet->close();

			if($planet_count != 0 )
			{
				//put attack message in log
				$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$planet_info[sector_id]'", 1);

				if($sector_check->RecordCount()){
					$sect = $sector_check->fields;
					$sectorname = $sect['sector_name'];
				}
				$sector_check->close();
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE planet_id = '$planet_info[planet_id]' ");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE from {$db_prefix}planets where planet_id=$planet_info[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("DELETE from {$db_prefix}dignitary where planet_id=$planet_info[planet_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query=$db->Execute("UPDATE {$db_prefix}ships SET on_planet='N', planet_id=0, storage_planet_id = 0 WHERE planet_id=$planet_info[planet_id] and on_planet='Y'");
				db_op_result($debug_query,__LINE__,__FILE__);

				$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE storage_planet_id = $planet_info[planet_id]");
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

				calc_ownership($planet_info['sector_id']);

				send_system_im($player_details['player_id'], "Alliance Confiscation!", "Your planet was confiscated by the Alliance Leader. You lost the following planet named " . $planet_info['name'] . " in sector " . $sectorname, $player_details['last_login']);
				playerlog($player_details['player_id'], "LOG5_PLANET_CONFISCATION", "the Alliance|$planet_info[name]|$sectorname|$planet_info[score]");
				adminlog("LOG0_RAW","<font color=yellow><B>Alliance Bounty Confiscation:</B></font>Bountied Player " . $player_details['character_name'] . " -  planet named " . $planet_info['name'] . " in sector " . $sectorname . " worth " . NUMBER($planet_info['score']) . " credits.</b>");
				TextFlush ( "<B>Alliance Bounty Planet Confiscation on $player_details[character_name]</B><BR>");
				$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES (1,'Alliance'," . time() . ",'The Alliance confiscated a planet (" . $planet_info['name'] . ") from " . $player_details['character_name'] . " in sector " . $sectorname . " worth " . NUMBER($planet_info['score']) . " credits for too many bounty attacks.',0) ");

				insert_news($player_details['character_name']."|".$planet_info['score']."|".$planet_info['name']."|".$sectorname, $player_details['player_id'], "alliancecol_pbounty");
			}
		}

		// update attack date
		$query = "UPDATE {$db_prefix}players SET alliance_attack_date='" . date("Y-m-d H:i:s") . "', alliance_bounty_count=alliance_bounty_count-1  WHERE player_id=$player_details[player_id]";
		$debug_query = $db->Execute("$query");
		db_op_result($debug_query,__LINE__,__FILE__);

		$attackflag++;
		$res_play->MoveNext();
	}//end while
}
$res_play->close();

if($attackflag == 0){
	if(mt_rand(1, 10000) < 2500)
	{
		$randplay=mt_rand(0,($sector_list_total-1));
		$sector_id = $sector_list[$randplay]['sector_id'];
	}else{
		$findem = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}planets ORDER BY rand()", 1);
		$sector_id = $findem->fields['sector_id'];
	}

	$query = "UPDATE {$db_prefix}ships SET class='99', hull=hull_normal, engines=engines_normal, power=power_normal, fighter=fighter_normal,
			  sensors=sensors_normal, beams=beams_normal, armor=armor_normal, cloak=0, torp_launchers=torp_launchers_normal, shields=shields_normal, ecm=ecm_normal,
			  fighters='21202551848303', torps='21202551848303', armor_pts='21202551848303', energy='106012759241513', sector_id=$sector_id WHERE ship_id='1'";
	$debug_query = $db->Execute("$query");
	db_op_result($debug_query,__LINE__,__FILE__);

	if(mt_rand(1, 10000) < 2500)
	{
		$get_planet = $db->SelectLimit("SELECT owner, name FROM {$db_prefix}planets WHERE sector_id = $sector_id ORDER BY rand()", 1);
		db_op_result($get_planet,__LINE__,__FILE__);
		if($get_planet->RecordCount() == 1)
		{
			$planetname = $get_planet->fields['name'];
			TextFlush ( "<br>Alliance Leader Ship Scanning Planet " . $planetname . " in sector $sector_id.<BR>");
			playerlog($get_planet->fields['owner'], "LOG6_PLANET_SCAN", $planetname . "|$sector_id|Alliance Leader");
		}
	}

	TextFlush ( "<br>Alliance Leader Ship Moved<BR>");
}

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET alliance_bounty_count=GREATEST(alliance_bounty_count-$fed_bounty_delay, 0), bounty_multiplier=GREATEST(bounty_multiplier-($fed_bounty_delay/2), 1)");
db_op_result($debug_query,__LINE__,__FILE__);

$multiplier = 0;
TextFlush ( "<BR>\n");
?>
