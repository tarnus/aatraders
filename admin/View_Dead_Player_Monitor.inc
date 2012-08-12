<?php
// 1: Dead Player Monitor
// This is a smaller tool for viewing the Extended Admin Log for any Dead player without displaying any other information about the player.

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

function strip_places1($itemin)
{
	$places = explode(",", $itemin);
	if (count($places) <= 1)
	{
		return $itemin;
	}
	else
	{
		$places[1] = AAT_substr($places[1], 0, 2);
		$placecount=count($places);

		switch ($placecount)
		{
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
						echo "  <input type=\"hidden\" name=\"menu\" value=\"View_Dead_Player_Monitor\">\n";
			echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
				echo "<INPUT TYPE=HIDDEN NAME=md5admin_password VALUE=".md5($admin_password).">" ;
			if (empty($user))
			{
				$res = $db->Execute("SELECT player_id,character_name,last_login FROM {$db_prefix}dead_players ORDER BY character_name ASC, last_login ASC");
				while (!$res->EOF)
				{
					$row = $res->fields;
					$option_echo .= "	<option value=\"$row[player_id]\">$row[character_name] ($row[last_login])</option>\n";
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
				echo "  &nbsp;\n  <input type=\"submit\" value=\"View\">\n";
			}
			else
			{
				if ((empty($operation)) or ($operation=="0"))
				{
				
				// Get Player List
				$res = $db->Execute("SELECT player_id,character_name,last_login FROM {$db_prefix}dead_players ORDER BY character_name ASC, last_login ASC");
				db_op_result($res,__LINE__,__FILE__);					
				$x=0;
				while (!$res->EOF)
				{
					//echo "here";
					$row = $res->fields;
					$list_player_id[$x]=$row['player_id'];
					$list_character_name[$x]=$row['character_name'] . " (" . $row['last_login'] . ")";
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
					$res = $db->Execute("SELECT * from {$db_prefix}dead_players " .
										"WHERE {$db_prefix}dead_players.player_id=$user");
					db_op_result($res,__LINE__,__FILE__);					
					$row = $res->fields;
					$res->close();

						// Template stuff
					//Player stuff
					$template_object->assign("character_name", $row['character_name']);
					$template_object->assign("player_id", $row['player_id']);
					$template_object->assign("ip_address", $row['ip_address']);
					$res4 = $db->Execute("SELECT * from {$db_prefix}dead_players " .
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
					
					$template_object->assign("last_login", $row['last_login']);
						$template_object->assign("team_name", "N/A");

					// Get Dead Player Admin Log reverse order by time is avaialble
					// Get total # of log items
					
					$query="SELECT count(*) as acount from {$db_prefix}dead_player_admin_extended_logging " .
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
					
					$query="SELECT * from {$db_prefix}dead_player_admin_extended_logging " .
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

          $template_object->assign("menu", "View_Dead_Player_Monitor");
          $template_object->assign("md5admin_password", $md5admin_password);
          $template_object->assign("game_number", $game_number);
          $template_object->assign("enable_mass_logging", $enable_mass_logging);

				$template_object->display("admin/Dead_Player_Monitor.tpl");
				

				}
				
				else
				{
					echo "Invalid operation";
				}
			}
			echo "</form>\n</div></td></tr>";
?>