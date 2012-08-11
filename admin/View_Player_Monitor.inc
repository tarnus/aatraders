<?php
// 1: Player Monitor
// This is a very powerful player monitoring program.  You can view and edit most of the players information.  It can be used to track multiple players using the same IP address.  You can enable Enhanced Admin Logging for any player.  Enhanced Admin Logging will record a large amount of information about every activity a player performs in the game.  It will even record all POST and GET variables sent by the players browser.  This is a great tool for tracking down cheaters.

if(@ini_get("register_globals") != 1)
{
	if (!empty($_GET))
	{
		extract($_GET);
	}

	if (!empty($_POST))
	{
		extract($_POST);
	}
}

echo"<tr><td><br><div align=\"center\">";

function strip_places1($itemin){

$places = explode(",", $itemin);
if (count($places) <= 1){
	return $itemin;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	$placecount=count($places);

	switch ($placecount){
		case 2:
			return "$places[0].$places[1] K";
			break;
		case 3:
			return "$places[0].$places[1] M";
			break;	
		case 4:
			return "$places[0].$places[1] B";
			break;	
		case 5:
			return "$places[0].$places[1] T";
			break;
		case 6:
			return "$places[0].$places[1] Qd";
			break;		
		case 7:
			return "$places[0].$places[1] Qn";
			break;
		case 8:
			return "$places[0].$places[1] Sx";
			break;
		case 9:
			return "$places[0].$places[1] Sp";
			break;
		case 10:
			return "$places[0].$places[1] Oc";
			break;
		}		
	
}
}

			$fun_temp = 0;
			$option_echo = '';
			echo "<form action=\"admin.php\" method=\"post\" name=\"ThisForm\">\n";
						echo "  <input type=\"hidden\" name=\"menu\" value=\"View_Player_Monitor\">\n";
			echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
				echo "<INPUT TYPE=HIDDEN NAME=md5admin_password VALUE=".md5($admin_password).">" ;
			if (empty($user))
			{
				$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players ORDER BY character_name");
				while (!$res->EOF)
				{
					$row = $res->fields;
					$option_echo .= "	<option value=\"$row[player_id]\">$row[character_name]</option>\n";
					$res->MoveNext();
					$fun_temp++;
				}
				$res->close();

				if ($fun_temp > 20)
				{
					$fun_temp = 20;
				}

				echo "  <select size=\"$fun_temp\" name=\"user\">\n";
				echo $option_echo;
				echo "  </select>\n";
				echo "  &nbsp;\n  <input type=\"submit\" value=\"Edit\">\n";
			}
			else
			{
				if ((empty($operation)) or ($operation=="0"))
				{
				
				if ($logging1 == "ext_on")
				{
					

					$query = "update {$db_prefix}players Set admin_extended_logging = 1 WHERE player_id=$user";
					$debug_query = $db->Execute($query); 
					
					
				}
				elseif ($logging1 == "ext_off")
				{
					
					
					$query = "update {$db_prefix}players Set admin_extended_logging = 0 WHERE player_id=$user";
					$debug_query = $db->Execute($query); 
					
					
				}elseif ($logging1 == "clearall")
				{
					
					
					$query = "delete from  {$db_prefix}admin_extended_logging  WHERE player_id=$user";
					$debug_query = $db->Execute($query); 
					
					
				}elseif ($logging1 == "cleartoday")
				{
				$now=date("Y-m-d 00:00:00");	
					
					$query = "delete from  {$db_prefix}admin_extended_logging  WHERE player_id=$user and time < '$now'";
					$debug_query = $db->Execute($query); 
					
					
				}
				
					// Get Player List
				//echo "SELECT player_id,character_name,last_login,admin_extended_logging FROM {$db_prefix}players ORDER BY admin_extended_logging DESC,last_login DESC, character_name";
				$res = $db->Execute("SELECT player_id,character_name,last_login,admin_extended_logging FROM {$db_prefix}players ORDER BY admin_extended_logging DESC, character_name ASC");
				$x=0;
				while (!$res->EOF)
				{
					//echo "here";
					$row = $res->fields;
					$list_player_id[$x]=$row['player_id'];
					$list_character_name[$x]=$row['character_name'];
					$list_admin_extended_logging[$x]=$row['admin_extended_logging'];
					$curtime = TIME();
					$dt=$row['last_login'];
					$yr=strval(AAT_substr($dt,0,4));
                	$mo=strval(AAT_substr($dt,5,2));
                	$da=strval(AAT_substr($dt,8,2));
                	$hr=strval(AAT_substr($dt,11,2));
                	$mi=strval(AAT_substr($dt,14,2));
                	$se=strval(AAT_substr($dt,17,2));

                	$list_last_login[$x]= mktime($hr,$mi,$se,$mo,$da,$yr); 
	
					$difftime[$x]=(($curtime - $list_last_login[$x] )/60 );
					//echo "[".$curtime." ".$list_last_login[$x]." ".$difftime[$x]." ".$list_character_name[$x]."]<br>";
					
					if ($difftime[$x] <= 5) 
					{
						$online[$x] = " - [Online]";
					}else{
						$online[$x] = "";
					}

					$x++;
					$res->MoveNext();
					
				}
				$res->close();
					$player_tot=$x;
					$template_object->assign("player_tot",$player_tot );
					$template_object->assign("list_admin_extended_logging",$list_admin_extended_logging );
					$template_object->assign("list_character_name", $list_character_name);
					$template_object->assign("list_player_id", $list_player_id);
					$template_object->assign("online", $online);
					// Get Player Data
					$res = $db->Execute("SELECT * from {$db_prefix}players " .
										"WHERE {$db_prefix}players.player_id=$user");
					db_op_result($res,__LINE__,__FILE__);					
					$row = $res->fields;
					$res->close();

						// Template stuff
					//Player stuff
					$template_object->assign("character_name", $row['character_name']);
					$template_object->assign("player_id", $row['player_id']);
					$template_object->assign("ip_address", $row['ip_address']);
					$res4 = $db->Execute("SELECT * from {$db_prefix}players " .
					"WHERE  ip_address='$row[ip_address]' and player_id != $row[player_id]  order by   character_name");
					db_op_result($res4,__LINE__,__FILE__);					
					$extras="";
					while (!$res4->EOF)
					{
						$row4 = $res4->fields;
						$extras= $extras." [".$row4['character_name']."]";
						$res4->MoveNext();
					}
					$res4->close();

					$md5fish=md5($swordfish);
					$template_object->assign("md5fish", $md5fish);
					$template_object->assign("extras", $extras);					
					$template_object->assign("last_login", $row['last_login']);
					$template_object->assign("score", NUMBER($row['score']));
					$template_object->assign("turns", NUMBER($row['turns']));
					$template_object->assign("turns_used", NUMBER($row['turns_used']));
					$template_object->assign("credits", NUMBER($row['credits']));
					// Get IGB Info
					
					$res4 = $db->Execute("SELECT * from {$db_prefix}ibank_accounts " .
										"WHERE {$db_prefix}ibank_accounts.player_id=$user");
					db_op_result($res4,__LINE__,__FILE__);					
					$row4 = $res4->fields;
					$res4->close();

					$template_object->assign("balance", NUMBER($row4['balance']));
					$template_object->assign("loan", NUMBER($row4['loan']));
					$template_object->assign("loantime", $row4['loantime']);
					// Get Fed Bouties
					$res6 = $db->Execute("SELECT count(*) as count, sum(amount) as total from {$db_prefix}bounty " .
										"WHERE {$db_prefix}bounty.bounty_on=$user and placed_by = 3");
					db_op_result($res6,__LINE__,__FILE__);
					$row6 = $res6->fields;
					$res6->close();

					$template_object->assign("fedtot", $row6['count']);
					$template_object->assign("fedtotamt", NUMBER($row6['total']));
					$template_object->assign("last_login", $row['last_login']);
					if ($row['team']!=0){
						$res7 = $db->Execute("SELECT team_name from {$db_prefix}teams " .
											"WHERE {$db_prefix}teams.creator=$row[team]");
						$row7 = $res7->fields;
						db_op_result($res7,__LINE__,__FILE__);
						$template_object->assign("team_name", $row7['team_name']);
						$res7->close();

					}else{
						$template_object->assign("team_name", "N/A");
					}
					$template_object->assign("last_login", $row['last_login']);
					$res7 = $db->Execute("SELECT * from {$db_prefix}ships " .
										"WHERE {$db_prefix}ships.ship_id =$row[currentship]");
					$row7 = $res7->fields;
					db_op_result($res7,__LINE__,__FILE__);
					$res7->close();
					$res7a = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$row7[sector_id]'", 1);
					$row7a = $res7a->fields;
					$res7a->close();

					$template_object->assign("sector_id", $row7a['sector_name']);
					$template_object->assign("on_planet", $row7['on_planet']);
					
					$template_object->assign("currentship", $row['currentship']);
					$template_object->assign("kills", $row['kills']);
					$template_object->assign("deaths", $row['deaths']);
		 			$template_object->assign("captures", $row['captures']);
					$template_object->assign("planets_built", $row['planets_built']);
					$template_object->assign("planets_lost", $row['planets_lost']);
					$template_object->assign("ship_losses", $row['ship_losses']);
					$template_object->assign("experience", NUMBER($row['experience']));
					$template_object->assign("rating", NUMBER($row['rating']));
					$template_object->assign("admin_extended_logging", $row['admin_extended_logging']);
						// Get total of all planet credits
					$query="SELECT count(*) as pcount,sum(credits) as tot_credits from {$db_prefix}planets " .
										"WHERE owner=$user";
					$res3 = $db->execute($query);
					db_op_result($res3,__LINE__,__FILE__);
					
					if ($res3->RecordCount() > 0)
					{	
						$row3 = $res3->fields;
						$template_object->assign("tot_planet_credits", NUMBER($row3[tot_credits]));
						$template_object->assign("tot_planets", NUMBER($row3[pcount]));
					}else{
						$template_object->assign("tot_planet_credits", "0");
						$template_object->assign("tot_planets", "0");
					}
					$res3->close();
					// get top 10 planets
				
					$query="SELECT *,( fighter  + sensors + beams + jammer + torp_launchers + shields + cloak + armor/8) as top_planet  from {$db_prefix}planets " .
										"WHERE owner=$user order by top_planet DESC";
					$res3 = $db->SelectLimit($query,10);
					db_op_result($res3,__LINE__,__FILE__);

					if ($res3->RecordCount() > 0)
					{	
						$x=0;
						while (!$res3->EOF)
						{
							
							$row3 = $res3->fields;
							$planetname[$x]=$row3['name'];
							if ($planetname[$x]==""){
								$planetname[$x]="Unnamed";
							}
							$res3a = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$row3[sector_id]'", 1);
						    $row3a = $res3a->fields;
							$res3a->close();
							$psector_id[$x]=$row3a['sector_name'];
							$pjammer[$x]=$row3['jammer'];
							$pjammer_normal[$x]=$row3['jammer_normal'];
							$pcomputer[$x]=$row3['fighter'];
							$pcomputer_normal[$x]=$row3['fighter_normal'];
							$psensors[$x]=$row3['sensors'];
							$psensors_normal[$x]=$row3['sensors_normal'];
							$pbeams[$x]=$row3['beams'];
							$pbeams_normal[$x]=$row3['beams_normal'];
							$ptorp_launchers[$x]=$row3['torp_launchers'];
							$ptorp_launchers_normal[$x]=$row3['torp_launchers_normal'];
							$pshields[$x]=$row3['shields'];
							$pshields_normal[$x]=$row3['shields_normal'];
							$parmour[$x]=$row3['armor'];
							$parmour_normal[$x]=$row3['armor_normal'];
							$pcloak[$x]=$row3['cloak'];
							$pcloak_normal[$x]=$row3['cloak_normal'];
							$pcredits[$x]=strip_places1(NUMBER($row3['credits']));
							$pmax_credits[$x]=strip_places1(NUMBER($row3['max_credits']));
							$penergy[$x]=strip_places1(NUMBER($row3['energy']));
							$pcolonists[$x]=strip_places1(NUMBER($row3['colonists']));
							$x++;
							$res3->MoveNext();
						}
						$res3->close();
						$planet_count=$x;
					}else{
						$planet_count=0;
					}
			
					$template_object->assign("planetname", $planetname);
					$template_object->assign("psector_id", $psector_id);
					$template_object->assign("pjammer", $pjammer);
					$template_object->assign("planet_count", $planet_count);
					$template_object->assign("pjammer_normal", $pjammer_normal);
					$template_object->assign("pcomputer", $pcomputer);
					$template_object->assign("pcomputer_normal", $pcomputer_normal);
					$template_object->assign("psensors", $psensors);
					$template_object->assign("psensors_normal", $psensors_normal);
					$template_object->assign("pbeams", $pbeams);
					$template_object->assign("pbeams_normal", $pbeams_normal);
					$template_object->assign("ptorp_launchers", $ptorp_launchers);
					$template_object->assign("ptorp_launchers_normal", $ptorp_launchers_normal);
					$template_object->assign("pshields", $pshields);
					$template_object->assign("pshields_normal", $pshields_normal);
					$template_object->assign("parmour", $parmour);
					$template_object->assign("parmour_normal", $parmour_normal);
					$template_object->assign("pcloak", $pcloak);
					$template_object->assign("pcloak_normal", $pcloak_normal);
					$template_object->assign("pcredits", $pcredits);
					$template_object->assign("pmax_credits", $pmax_credits);
					$template_object->assign("penergy", $penergy);
					$template_object->assign("pcolonists", $pcolonists);
									
					// Get Ship Data
					$res2 = $db->Execute("SELECT * from {$db_prefix}ships " .
										"WHERE {$db_prefix}ships.player_id=$user order by class DESC");
					db_op_result($res2,__LINE__,__FILE__);					
					$x=0;					
					while (!$res2->EOF)
					{
						
						$row2 = $res2->fields;
						// Get Ship names
						$res = $db->Execute("SELECT * from {$db_prefix}ship_types where type_id=$row2[class]");
						db_op_result($res,__LINE__,__FILE__);
						$shiptypeinfo = $res->fields;
						$ship_type[$x]=$shiptypeinfo['name'];
						$ship_id[$x]=$row2['ship_id'];
						$hull[$x]=$row2['hull'];
						$hull_normal[$x]=$row2['hull_normal'];
						$engines[$x]=$row2['engines'];
						$engines_normal[$x]=$row2['engines_normal'];
						$power[$x]=$row2['power'];
						$power_normal[$x]=$row2['power_normal'];
						$computer[$x]=$row2['fighter'];
						$computer_normal[$x]=$row2['fighter_normal'];
						$sensors[$x]=$row2['sensors'];
						$sensors_normal[$x]=$row2['sensors_normal'];
						$beams[$x]=$row2['beams'];
						$beams_normal[$x]=$row2['beams_normal'];
						$torp_launchers[$x]=$row2['torp_launchers'];
						$torp_launchers_normal[$x]=$row2['torp_launchers_normal'];
						$shields[$x]=$row2['shields'];
						$shields_normal[$x]=$row2['shields_normal'];
						$armour[$x]=$row2['armor'];
						$armour_normal[$x]=$row2['armor_normal'];
						$cloak[$x]=$row2['cloak'];
						$cloak_normal[$x]=$row2['cloak_normal'];
						$ecm[$x]=$row2['ecm'];
						$ecm_normal[$x]=$row2['ecm_normal'];
						$x++;
						$res2->MoveNext();
					}
					$res2->close();
					$ship_count=$x;
					$template_object->assign("ship_count", $ship_count);
					$template_object->assign("ship_id", $ship_id);
					$template_object->assign("hull", $hull);
					$template_object->assign("hull_normal", $hull_normal);
					$template_object->assign("engines", $engines);
					$template_object->assign("engines_normal", $engines_normal);
					$template_object->assign("ship_type", $ship_type);
					$template_object->assign("power", $power);
					$template_object->assign("power_normal", $power_normal);
					$template_object->assign("computer", $computer);
					$template_object->assign("computer_normal", $computer_normal);
					$template_object->assign("sensors", $sensors);
					$template_object->assign("sensors_normal", $sensors_normal);
					$template_object->assign("beams", $beams);
					$template_object->assign("beams_normal", $beams_normal);
					$template_object->assign("torp_launchers", $torp_launchers);
					$template_object->assign("torp_launchers_normal", $torp_launchers_normal);
					$template_object->assign("shields", $shields);
					$template_object->assign("shields_normal", $shields_normal);
					$template_object->assign("armour", $armour);
					$template_object->assign("armour_normal", $armour_normal);
					$template_object->assign("cloak", $cloak);
					$template_object->assign("cloak_normal", $cloak_normal);
					$template_object->assign("ecm", $ecm);
					$template_object->assign("ecm_normal", $ecm_normal);

					// Get Admin Log reverse order by time is avaialble
					// Get total # of log items
					
					$query="SELECT count(*) as acount from {$db_prefix}admin_extended_logging " .
										"WHERE player_id=$user order by time DESC";
					$logcount = $db->Execute($query);				

					if ($logcount->RecordCount() > 0)
					{	
						$getitems = $logcount->fields;
	 					$log_total=$getitems['acount'];
 					}else{
						$log_total=0;
					}
					$logcount->close();
					if ((!isset($offset)) or ($offset==0))
					{
						$offset=0;
					}
					if ($log_total >= 150){
						$pages=ceil($log_total/150);
						
					}else{
						$pages=1;
					}
					if ($offset >= 150)
					{
						$current_page=floor($offset/150);
					}else{
						$current_page=0;
					}
					
					$template_object->assign("pages", $pages);
					$template_object->assign("pages", $pages);
					$template_object->assign("current_page", $current_page);
					$template_object->assign("offset", $offset);
					$template_object->assign("log_total", $log_total);
					
					$query="SELECT * from {$db_prefix}admin_extended_logging " .
										"WHERE player_id=$user order by time DESC";
					$res5 = $db->SelectLimit($query,150,$offset);
					db_op_result($res5,__LINE__,__FILE__);
					if ($res5->RecordCount() > 0)
					{	
						$x=0;
					while (!$res5->EOF)
					{
						$row5 = $res5->fields;

						$ltime[$x]=$row5['time'];
						$lurl_path[$x]=$row5['request_uri'];
						$lget_data[$x]=nl2br(str_replace(" ", "&nbsp;", $row5['get_data']));
						if ($lget_data[$x]==""){
							$lget_data[$x]="N/A";
						}
						$lpost_data[$x]=nl2br(str_replace(" ", "&nbsp;", $row5['post_data']));
						if ($lpost_data[$x]==""){
							$lpost_data[$x]="N/A";
						}
						$lscore[$x]=strip_places1(NUMBER($row5['score']));
						$lip_address[$x]=$row5['ip_address'];
						$lcredits[$x]=strip_places1(NUMBER($row5['credits']));
						$lturns[$x]=NUMBER($row5['turns']);
						$lcurrentship[$x]=$row5['currentship'];
						$lplayer_online_time[$x]=($player_online_timelimit == 0) ? "Unlimited" : floor($row5['player_online_time']/60);
						if ($x > 0)
						{
							$lcreditdiff[$x]=abs((($lcredits[$x-1] / $lcredits[$x])-1))*100;
							$lscorediff[$x]=abs((($lscore[$x-1] / $lscore[$x])-1))*100;
							if ($x > 0)
							{
								if ($lcreditdiff[$x] > 20)
								{
								$lcreditdiff[$x-1]=100;
								}
								
								if ($lscorediff[$x] > 15)
								{
								$lscorediff[$x-1]=100;
								
								}
							}
						}else{
							$lcreditdiff[$x]=0;
							$lscorediff[$x]=0;
						}
						$x++;
						$res5->MoveNext();
					}
					$res5->close();
					$log_count=$x;
					}else{
					$log_count=0;
					}

					$template_object->assign("log_count", $log_count);
					$template_object->assign("lscorediff", $lscorediff);
					$template_object->assign("lplayer_online_time", $lplayer_online_time);
					$template_object->assign("lcreditdiff", $lcreditdiff);
					$template_object->assign("ltime", $ltime);
					$template_object->assign("lturns", $lturns);
					$template_object->assign("lurl_path", $lurl_path);
					$template_object->assign("lget_data", $lget_data);
					$template_object->assign("lpost_data", $lpost_data);
					$template_object->assign("lscore", $lscore);
					$template_object->assign("lip_address", $lip_address);
					$template_object->assign("lcredits", $lcredits);
					$template_object->assign("lcurrentship", $lcurrentship);
          $template_object->assign("menu", $menu);
          $template_object->assign("md5admin_password", $md5admin_password);
          $template_object->assign("game_number", $game_number);
          $template_object->assign("enable_mass_logging", $enable_mass_logging);

				$template_object->display("admin/Player_Monitor.tpl");
				

					
				}
				
				else
				{
					echo "Invalid operation";
				}
			}
						echo "  <input type=\"hidden\" name=\"menu\" value=\"View_Player_Monitor\">\n";
			echo "  <input type=\"hidden\" name=\"swordfish\" value=\"$swordfish\">\n";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
			echo "</form>\n</div></td></tr>";
?>