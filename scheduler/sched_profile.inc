<?php
// 1
// 2300
// 60
// 0
// Y
// How often cached profiles will be sent to the profile server.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/good_neutral_evil.inc");
include ("globals/gen_score.inc");

$res = $db->Execute("SELECT * FROM {$db_prefix}ship_types order by type_id");
while (!$res->EOF)
{
	$ship_id = $res->fields['type_id'];
	$ship_name[$ship_id] = $res->fields['name'];
	$res->MoveNext();
}
$res->close();

if($enable_profilesupport == 1){
	@unlink($gameroot."templates_c/current_profile_data" . $game_number . ".txt");
	$fs = @fopen($gameroot.'templates_c/current_profile_data' . $game_number . '.txt', 'w');
	$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
	@fwrite($fs, "server:$game_name\n");
	$gm_url = $gameurl . $gamepath;
	@fwrite($fs, "url:$gm_url\n");
	@fwrite($fs, "version:$release_version\n");

	@fwrite($fs, "page_size:22\n"); // this is the total number of lines for each block of player data

	@unlink($gameroot."templates_c/dead_profile_data" . $game_number . ".txt");
	$fs2 = @fopen($gameroot.'templates_c/dead_profile_data' . $game_number . '.txt', 'w');
	$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
	@fwrite($fs2, "server:$game_name\n");
	$gm_url = $gameurl . $gamepath;
	@fwrite($fs2, "url:$gm_url\n");
	@fwrite($fs2, "version:$release_version\n");

	@fwrite($fs2, "page_size:23\n"); // this is the total number of lines for each block of player data
}

$res = $db->Execute("SELECT * from {$db_prefix}players WHERE profile_cached='Y'");
db_op_result($res,__LINE__,__FILE__);
while (!$res->EOF)
{
	$playerinfo = $res->fields;
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET profile_cached='N', sessionid='' WHERE player_id = $playerinfo[player_id]");

	if($enable_profilesupport == 1){
		if ((isset($playerinfo['profile_name'])) && ($playerinfo['profile_name'] != ''))
		{
			if(empty($playerinfo['death_type']) || $playerinfo['death_type'] == "")
			{
			    $debug_query = $db->Execute("SELECT player_id FROM {$db_prefix}players WHERE turns_used != 0 and destroyed!='Y' " .
   			    	                "and email NOT LIKE '%@npc' AND player_id > 3 ORDER BY score DESC");
    			db_op_result($debug_query,__LINE__,__FILE__);

				$num_players = $debug_query->RecordCount();
				$rank = 0;
				if ($debug_query)
				{
					while (!$debug_query->EOF)
					{
						$row = $debug_query->fields;
						$rank++;
						if($playerinfo['player_id'] == $row['player_id']){
							break;
						}
						$debug_query->MoveNext();
					}
					$debug_query->close();
				}
			}
			else
			{
			    $debug_query = $db->Execute("SELECT player_id FROM {$db_prefix}players WHERE turns_used != 0 and destroyed!='Y' " .
   			    	                "and email NOT LIKE '%@npc' AND player_id > 3 ORDER BY score DESC");
    			db_op_result($debug_query,__LINE__,__FILE__);

				$num_players = $debug_query->RecordCount();
				$rank = 9999;
			}

			$resavg = $db->Execute("SELECT SUM(credits) AS a1 , AVG(fighter_normal) AS a4 , " .
								"AVG(sensors_normal) AS a5 , AVG(beams_normal) AS a6 , AVG(torp_launchers_normal) AS a7 , AVG(shields_normal) AS a8 , " .
								"AVG(armor_normal) AS a9 , AVG(cloak_normal) AS a10, AVG(jammer_normal) AS a11 FROM {$db_prefix}planets,{$db_prefix}players WHERE " .
								"{$db_prefix}planets.owner = {$db_prefix}players.player_id AND {$db_prefix}players.player_id = $playerinfo[player_id]");
			$row = $resavg->fields;
			if($resavg)
			{
				$resavg->close();
			}
			$dyn_avg_lvl = $row['a4'] + $row['a5'] + $row['a6'] + $row['a7'] + $row['a8'] + $row['a9'] + $row['a10'] + $row['a11'];
			$dyn_avg = $dyn_avg_lvl / 8;

			$rating = good_neutral_evil($playerinfo['rating']);

			if(!empty($playerinfo['ship_losses']))
			{
				$losses = explode("|", $playerinfo['ship_losses']);
				$losslist = "";
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

			$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;

		    $deathtype_query = $db->SelectLimit("SELECT * FROM {$db_prefix}dead_players WHERE player_id = $playerinfo[player_id]", 1);
   			db_op_result($deathtype_query,__LINE__,__FILE__);

			$deathtype_result = $deathtype_query->fields;

			if($deathtype_result['death_type'] != "killedsuicide" && $deathtype_query->RecordCount() == 1)
			{
				$gm_all = 	"player_name=" . $deathtype_result['character_name'] . "\n" .
							"planets_built=" . $deathtype_result['planets_built'] . "\n" .
							"planets_based=" . $playerinfo['planets_based'] . "\n" .
							"planets_destroyed=" . $playerinfo['planets_destroyed'] . "\n" .
							"planets_lost=" . $deathtype_result['planets_lost'] . "\n" .
							"captures=" . $deathtype_result['captures'] . "\n" .
							"deaths=" . $deathtype_result['deaths'] . "\n" .
							"kills=" . $deathtype_result['kills'] . "\n";
							if($deathtype_result['kills'] == 0)
							{
								$gm_all .= 	"kill_efficiency=0\n";
							}
							else
							{
								$gm_all .= 	"kill_efficiency=" . round($deathtype_result['kill_efficiency'] / $deathtype_result['kills']) . "\n";
							}
				$gm_all .= 	"rating=" . $rating[0] . "\n" .
							"turns_used=" . $deathtype_result['turns_used'] . "\n" .
							"credits=" . rawurlencode($playerinfo['credits'] + $row['a1']) . "\n" .
							"score=" . rawurlencode($deathtype_result['score']) . "\n" .
							"max_defense=" . $dyn_avg . "\n" .
							"rank=" . $rank . "\n" .
							"ptotal=" . $num_players . "\n" .
							"ship_losses=" . $losslist . "\n" .
							"self_destruct=0\n" .
							"name=" . $deathtype_result['profile_name'] . "\n" .
							"password=" . $deathtype_result['profile_password'] . "\n" .
							"player_total_online=" . $playerinfo['player_total_online'] . "\n";
			}
			else
			{
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
							"player_total_online=" . $playerinfo['player_total_online'] . "\n";
			}

			if(empty($playerinfo['death_type']) || $playerinfo['death_type'] == "")
			{
				@fwrite($fs, "$gm_all\n");
			}
			else
			{
				$gm_all .= 	"death_type=" . $playerinfo['death_type'] . "\n";
				@fwrite($fs2, "$gm_all\n");
			}
		}
	}
	$res->MoveNext();
}
$res->close();

if($enable_profilesupport == 1){
	@fclose($fs);
	@fclose($fs2);
	$url = "http://www.aatraders.com/update_currentgames30.php?server=" . rawurlencode($gm_url) . "&game_number=" . $game_number;

	echo "\n\n<!--" . $url . "-->\n\n";

	$url2 = "http://www.aatraders.com/update_deadplayers30.php?server=" . rawurlencode($gm_url) . "&game_number=" . $game_number;

	echo "\n\n<!--" . $url2 . "-->\n\n";

	if($enable_profilesupport)
	{
		if(@ini_get("allow_url_fopen") == 1)
		{
			TextFlush( "<br><br>Sending Player profile data to the Profile Server through FOPEN.<br>");
			$fp = @fopen ($url,"r");
			if($fp)
			{
				while(!@feof($fp)){
					TextFlush(trim(@fgets($fp)) . "<br>\n");
				}
				fclose ($fp);
			}

			$fp = @fopen ($url2,"r");
			if($fp)
			{
				while(!@feof($fp)){
					TextFlush(trim(@fgets($fp)) . "<br>\n");
				}
				fclose ($fp);
			}
		}
		else
		if(function_exists('curl_init'))
		{
			TextFlush( "<br><br>Sending Player profile data to the Profile Server through CURL.<br>");
			$ch=curl_init();
			curl_setopt($ch, CURLOPT_URL, $url);
			curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
			$var = curl_exec ($ch);
			curl_close ($ch);
			TextFlush(trim($var) . "<br>\n");

			$ch=curl_init();
			curl_setopt($ch, CURLOPT_URL, $url2);
			curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1);
			$var = curl_exec ($ch);
			curl_close ($ch);
			TextFlush(trim($var) . "<br>\n");
		}
		else
		{
			TextFlush( "\n\n<b>Server List Failed Update because allow_url_fopen PHP configuration not enabled or CURL doesn't exist on this server.</b></br></br>\n\n");
		}
	}
}

if($adminexecuted == 1){
	TextFlush ( "<b>Profiles Sent to Profile Server</b><br><br>");
}

$multiplier = 0;

?>
