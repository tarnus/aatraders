<?php
include ("globals/good_neutral_evil.inc");
include ("globals/gen_score.inc");
include ("globals/player_insignia_name.inc");

if (!function_exists('end_of_game')) {

	function end_of_game()
	{
		global $db, $db_prefix, $gameroot, $gamepath, $game_number, $game_name, $release_version, $local_date_full_format;
		global $enable_profilesupport, $neutral_neg_percent, $neutral_safezone, $tournament_mode , $scheduled_reset, $reset_date;

		$res = $db->Execute("SELECT * FROM {$db_prefix}ship_types order by type_id");
		while (!$res->EOF)
		{
			$ship_id = $res->fields['type_id'];
			$ship_name[$ship_id] = $res->fields['name'];
			$res->MoveNext();
		}

		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}players, {$db_prefix}ships WHERE {$db_prefix}players.turns_used != 0 and {$db_prefix}players.player_id = {$db_prefix}ships.player_id and {$db_prefix}players.currentship={$db_prefix}ships.ship_id and {$db_prefix}players.destroyed!='Y' " .
 		 						 "and email NOT LIKE '%@npc' AND {$db_prefix}players.player_id > 3 and {$db_prefix}players.profile_name != '' ORDER BY score DESC,character_name ASC");
		db_op_result($debug_query,__LINE__,__FILE__);

		if ($debug_query)
		{
			$num_players = $debug_query->RecordCount();
			echo "<br><font color=\"yellow\"><B>Compiling $num_players profiles for the Profile Server.</b></font><br>";
			if($num_players > 0)
			{
				$rank = 0;
				@unlink($gameroot."templates_c/profile_eog" . $game_number . ".txt");
				$fs = @fopen($gameroot.'templates_c/profile_eog' . $game_number . '.txt', 'w');
				$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
				@fwrite($fs, "server:$game_name\n");
				@fwrite($fs, "url:$gm_url\n");
				@fwrite($fs, "version:$release_version\n");

				@fwrite($fs, "page_size:22\n"); // this is the total number of lines for each block of player data
				while (!$debug_query->EOF)
				{
					$playerinfo = $debug_query->fields;
					if ((isset($playerinfo['profile_name'])) && ($playerinfo['profile_name'] != ''))
					{
						echo "<br>Adding player: $playerinfo[character_name] ($playerinfo[player_id])";

					    $rank_query = $db->Execute("SELECT {$db_prefix}players.player_id FROM {$db_prefix}players, {$db_prefix}ships WHERE {$db_prefix}players.turns_used != 0 and {$db_prefix}players.player_id = {$db_prefix}ships.player_id and {$db_prefix}players.currentship={$db_prefix}ships.ship_id and {$db_prefix}players.destroyed!='Y' " .
		   			    	                "and email NOT LIKE '%@npc' AND {$db_prefix}players.player_id > 3 ORDER BY score DESC");
   						db_op_result($rank_query,__LINE__,__FILE__);

						$num_players = $rank_query->RecordCount();
						$rank = 0;
						if ($rank_query)
						{
							while (!$rank_query->EOF)
							{
								$row = $rank_query->fields;
								$rank++;
								if($playerinfo['player_id'] == $row['player_id'])
								{
									break;
								}
								$rank_query->MoveNext();
							}
							$rank_query->close();
						}

						$resavg = $db->Execute("SELECT SUM({$db_prefix}planets.credits) AS a1 , AVG(fighter_normal) AS a4 , " .
											"AVG(sensors_normal) AS a5 , AVG(beams_normal) AS a6 , AVG(torp_launchers_normal) AS a7 , AVG(shields_normal) AS a8 , " .
											"AVG(armor_normal) AS a9 , AVG(cloak_normal) AS a10, AVG(jammer_normal) AS a11 FROM {$db_prefix}planets,{$db_prefix}players WHERE " .
											"{$db_prefix}planets.owner = {$db_prefix}players.player_id AND {$db_prefix}players.player_id = $playerinfo[player_id]");
						$row = $resavg->fields;
						$resavg->close();
						$dyn_avg_lvl = $row['a4'] + $row['a5'] + $row['a6'] + $row['a7'] + $row['a8'] + $row['a9'] + $row['a10'] + $row['a11'];
						$dyn_avg = $dyn_avg_lvl / 8;
						$rating = good_neutral_evil($playerinfo['rating']);
						$losses = explode("|", $playerinfo['ship_losses']);
						$losslist = "";
						if(!empty($playerinfo['ship_losses']))
						{
							for($ii=0; $ii<count($losses); $ii++){
								$classinfo = explode("-", $losses[$ii]);
								$classname = $ship_name[$classinfo[0]];
								$losslist .= $classname . ":" . $classinfo[1];
								if($ii != (count($losses) - 1))
									$losslist .= "|";
							}
						}
						else
						{
							$losslist = "None";
						}

						$returnscore = gen_score($playerinfo['player_id']);
						$score = $returnscore[0];
						$gm_all = 	"player_name=" . $playerinfo['character_name'] . "\n" .
								"planets_built=" . $playerinfo['planets_built'] . "\n" .
								"planets_based=" . $playerinfo['planets_based'] . "\n" .
								"planets_destroyed=" . $playerinfo['planets_destroyed'] . "\n" .
								"planets_lost=" . $playerinfo['planets_lost'] . "\n" .
								"captures=" . $playerinfo['captures'] . "\n" .
								"deaths=" . $playerinfo['deaths'] . "\n" .
								"kills=" . $playerinfo['kills'] . "\n";
								if($playerinfo['kills'] == 0)
								{
									$gm_all .= 	"kill_efficiency=0\n";
								}
								else
								{
									$gm_all .= 	"kill_efficiency=" . round($playerinfo['kill_efficiency'] / $playerinfo['kills']) . "\n";
								}
						$gm_all .= 	"rating=" . $rating[0] . "\n" .
								"turns_used=" . $playerinfo['turns_used'] . "\n" .
								"credits=" . rawurlencode($playerinfo['credits'] + $row['a1']) . "\n" .
								"score=" . rawurlencode($score) . "\n" .
								"max_defense=" . $dyn_avg . "\n" .
								"rank=" . $rank . "\n" .
								"ptotal=" . $num_players . "\n" .
								"ship_losses=" . $losslist . "\n" .
								"self_destruct=0\n" .
								"name=" . $playerinfo['profile_name'] . "\n" .
								"password=" . $playerinfo['profile_password'] . "\n" .
								"player_total_online=" . $playerinfo['player_total_online'] . "\n\n";

							@fwrite($fs, $gm_all);
					}
					$debug_query->MoveNext();
				}
				@fclose($fs);
				$debug_query->close();
			}
			else
			{
				echo "<br><font color=\"yellow\"><B>Nothing to send to the Profile Server.</b></font><br>";
			}
		}

		$debug_query = $db->SelectLimit("SELECT rating FROM {$db_prefix}players order by rating DESC", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$top_rating = $debug_query->fields['rating'];

		$debug_query = $db->SelectLimit("SELECT rating FROM {$db_prefix}players order by rating ASC", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$bottom_rating = $debug_query->fields['rating'];

		$lowend_neutral = floor($bottom_rating * ($neutral_neg_percent / 100));
		$highend_neutral = floor($top_rating * ($neutral_pos_percent / 100));

		$res = $db->Execute("SELECT count({$db_prefix}players.player_id) as total FROM {$db_prefix}players, {$db_prefix}ships " .
							" WHERE ".$showzero." {$db_prefix}players.player_id = {$db_prefix}ships.player_id and {$db_prefix}players.destroyed!='Y' and {$db_prefix}players.player_id > 3 and  {$db_prefix}players.currentship={$db_prefix}ships.ship_id " .
							"and email NOT LIKE '%@npc' ". $query);

		$num_players = $res->fields['total'];

		$res = $db->Execute("SELECT ({$db_prefix}players.kill_efficiency / {$db_prefix}players.kills) as kill_efficiency2, {$db_prefix}players.kill_efficiency, {$db_prefix}players.experience, {$db_prefix}players.email, {$db_prefix}players.score, {$db_prefix}players.attackscore, {$db_prefix}players.player_id, " .
        		                "{$db_prefix}players.character_name, {$db_prefix}players.avatar, {$db_prefix}players.kills, {$db_prefix}players.deaths, 
								{$db_prefix}players.captures, {$db_prefix}players.planets_lost, {$db_prefix}players.planets_built, {$db_prefix}players.planets_based, {$db_prefix}players.planets_destroyed, 
								{$db_prefix}players.profile_id, {$db_prefix}players.team, " .
		                        "{$db_prefix}players.turns_used, {$db_prefix}players.last_login, " .
        		                "{$db_prefix}players.rating, {$db_prefix}players.logged_out, " .
                		        "{$db_prefix}teams.team_name, " .
                        		"IF({$db_prefix}players.turns_used<150,0,ROUND({$db_prefix}players.score/{$db_prefix}players.turns_used)) " .
		                        "AS efficiency FROM {$db_prefix}players LEFT JOIN {$db_prefix}teams ON {$db_prefix}players.team " .
        		                "= {$db_prefix}teams.id LEFT JOIN {$db_prefix}ships ON " .
                		        "{$db_prefix}players.player_id={$db_prefix}ships.player_id WHERE {$db_prefix}players.turns_used != 0 and {$db_prefix}players.currentship={$db_prefix}ships.ship_id and {$db_prefix}players.destroyed!='Y' " .
		                        "and email NOT LIKE '%@npc' AND {$db_prefix}players.player_id > 3  ORDER BY score DESC,character_name ASC");
		db_op_result($res,__LINE__,__FILE__);

		@unlink($gameroot."templates_c/ranking_eog" . $game_number . ".txt");
		$file = fopen($gameroot . "templates_c/ranking_eog" . $game_number . ".txt","w") or die ("Failed opening file: enable write permissions for '" . $gameroot . "templates_c/ranking_eog" . $game_number . ".txt'");
		$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
		@fwrite($file, "server:$game_name\n");
		@fwrite($file, "url:$gm_url\n");
		@fwrite($file, "version:$release_version\n");
		@fwrite($file, "tournament:$tournament_mode\n");
		@fwrite($file, "start_date:$reset_date\n");
		@fwrite($file, "finish_date:$scheduled_reset\n");
		@fwrite($file, "total_players:" . $res->RecordCount() . "\n");
		@fwrite($file, "page_size:22\n"); // this is the total number of lines for each block of player data

		while (!$res->EOF)
		{
			$row = $res->fields;

			$player_insignia = player_insignia_name($row['player_id']);
			$lastlogin = date($local_date_full_format, strtotime($row['last_login']));
			$rating = good_neutral_evil($row['rating']);

			fwrite($file, "score=" . NUMBER($row['score']) . "\n");
			fwrite($file, "rankimg=" . $player_insignia[0] . "\n");
			fwrite($file, "rankname=" . $player_insignia[1] . "\n");
			fwrite($file, "avatar=" . "avatars/".$row['avatar'] . "\n");
			fwrite($file, "playername=" . $row['character_name'] . "\n");
			fwrite($file, "turnsused=" . NUMBER($row['turns_used']) . "\n");
			fwrite($file, "lastlogin=" . $lastlogin . "\n");
			fwrite($file, "rating=" . $rating[0] . "\n");
			fwrite($file, "teamname=" . $row['team_name'] . "\n");
			fwrite($file, "team_id=" . $row['team'] . "\n");
			fwrite($file, "kills=" . NUMBER($row['kills']) . "\n");
			if($row['kills'] == 0)
			{
				fwrite($file, "killeff=" . "0\n");
			}
			else
			{
				fwrite($file, "killeff=" . NUMBER(round($row['kill_efficiency'] / $row['kills'])) . "\n");
			}
			fwrite($file, "deaths=" . NUMBER($row['deaths']) . "\n");
			fwrite($file, "captures=" . NUMBER($row['captures']) . "\n");
			fwrite($file, "planets_lost=" . NUMBER($row['planets_lost']) . "\n");
			fwrite($file, "planets_built=" . NUMBER($row['planets_built']) . "\n");
			fwrite($file, "planets_based=" . NUMBER($row['planets_based']) . "\n");
			fwrite($file, "planets_destroyed=" . NUMBER($row['planets_destroyed']) . "\n");
			fwrite($file, "experience=" . NUMBER(floor($row['experience'])) . "\n");
			fwrite($file, "efficiency=" . $row['efficiency'] . "\n");
			fwrite($file, "profileid=" . $row['profile_id'] . "\n");
			fwrite($file, "\n");
			$res->MoveNext();
		}
		fclose($file);

		$sql_query = "SELECT {$db_prefix}players.character_name,
					COUNT(*) as number_of_members,
					ROUND(SUM({$db_prefix}players.score) / COUNT(*)) as total_score,
					{$db_prefix}teams.id,
					{$db_prefix}teams.team_name,
					{$db_prefix}teams.icon,
					{$db_prefix}teams.creator
					FROM {$db_prefix}players, {$db_prefix}ships, {$db_prefix}teams
					WHERE {$db_prefix}players.team = {$db_prefix}teams.id AND {$db_prefix}ships.ship_id = {$db_prefix}players.currentship
					AND {$db_prefix}players.destroyed != 'Y'
					GROUP BY {$db_prefix}teams.team_name ORDER BY total_score DESC";
		$res = $db->Execute($sql_query);
		db_op_result($res,__LINE__,__FILE__);

		@unlink($gameroot."templates_c/teams_eog" . $game_number . ".txt");
		$file = fopen($gameroot . "templates_c/teams_eog" . $game_number . ".txt","w") or die ("Failed opening file: enable write permissions for '" . $gameroot . "templates_c/teams_eog" . $game_number . ".txt'");
		$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
		@fwrite($file, "server:$game_name\n");
		@fwrite($file, "url:$gm_url\n");
		@fwrite($file, "version:$release_version\n");
		@fwrite($file, "page_size:7\n"); // this is the total number of lines for each block of player data

		while (!$res->EOF)
		{
			$row = $res->fields;
			$sql_query_2 = "SELECT character_name FROM {$db_prefix}players WHERE player_id = $row[id]";
			$res2 = $db->SelectLimit($sql_query_2, 1);
			$teamlistcname[$count] = $res2->fields['character_name'];
			$teamlistscore[$count] = NUMBER($row['total_score']);

			fwrite($file, "icon=" . $row['icon'] . "\n");
			fwrite($file, "team_id=" . $row['id'] . "\n");
			fwrite($file, "team_name=" . $row['team_name'] . "\n");
			fwrite($file, "number_of_members=" . $row['number_of_members'] . "\n");
			fwrite($file, "coordinator=" . $res2->fields['character_name'] . "\n");
			fwrite($file, "total_score=" . NUMBER($row['total_score']) . "\n");
			fwrite($file, "\n");
			$res->MoveNext();
		}
		fclose($file);

		$url = "http://www.aatraders.com/update_end_of_game.php?server=" . rawurlencode($gm_url) . "&game_number=" . $game_number;
		echo "\n\n<!--" . $url . "-->\n\n";
		if($enable_profilesupport)
		{
			if(function_exists('curl_init'))
			{
				echo "<br><br>Sending compiled profile data to the Profile Server through CURL.<br>";
				$ch=curl_init();
				curl_setopt($ch, CURLOPT_URL, $url);
				curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
				$var = curl_exec ($ch);
				curl_close ($ch);
				echo trim($var) . "<br>\n";
			}
			else
			if(@ini_get("allow_url_fopen") == 1)
			{
				echo "<br><br>Sending compiled profile data to the Profile Server through FOPEN.<br>";
				$fp = fopen ($url,"r");
				if($fp)
				{
					while(!feof($fp)){
						echo trim(fgets($fp)) . "<br>\n";
					}
					fclose ($fp);
				}
			}
			else
			{
				echo "\n\n<b>Server List Failed Update because allow_url_fopen PHP configuration not enabled or CURL doesn't exist on this server.</b></br></br>\n\n";
			}
		}
		else
		{
			echo "<br><br>Sending compiled profile data to the Profile Server has been <font color=yellow><b>DISABLED</b></font>.<br>";
		}
	}
}

?>
