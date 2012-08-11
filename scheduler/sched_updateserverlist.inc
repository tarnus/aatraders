<?php
// 1
// 1100
// 60
// 0
// Y
// Update the Master Server List with information about the game.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

$server_list_key = "KEY"; // *DO NOT EDIT*

TextFlush( "\n\n<b>Updating Server List</b></br></br>\n\n");

if ($enable_profilesupport)
{
	$gm_url2 = $gameurl . $gamepath;
	$gm_speed = $sched_ports + $sched_planets + $sched_igb;
	$gm_speed_turns = 1;
	$gm_speed_turns1 = $turn_rate;

	$res = $db->Execute("SELECT COUNT(sector_id) AS n FROM {$db_prefix}universe");
	db_op_result($res,__LINE__,__FILE__);
	$gm_size_sc = $res->fields['n'];
	$res->close();

	$gm_size_un = $universe_size;
	$gm_money_igb = $ibank_interest;
	$gm_sofa_on = $sofa_on;
	if ($sofa_on === false)
	{
		$gm_sofa_on = 0;
	}

	$gm_all2 = "gm_speed=" . $sched_ticks . "\n" .
			  "gm_speed_turns=" . $gm_speed_turns1 . "\n" .
			  "gm_size_sc=" . $gm_size_sc . "\n" .
			  "gm_size_un=" . $gm_size_un . "\n" .
			  "gm_money_igb=" . $gm_money_igb . "\n" .
			  "gm_sofa_on=" . $gm_sofa_on . "\n" .
			  "gm_url=" . $gm_url2 . "\n" .
			  "gm_name=" . $game_name . "\n";

	if($showzeroranking == 1)
		$showzero = "";
	else $showzero = "{$db_prefix}players.turns_used != 0 and";

	$res = $db->Execute("SELECT * FROM {$db_prefix}players WHERE ".$showzero." destroyed!='Y' and player_id > 3 " .
						"and email NOT LIKE '%@npc' ");
	db_op_result($res,__LINE__,__FILE__);

	$dyn_players = $res->RecordCount();	   
	$res->close();

	$res = $db->Execute("SELECT score, character_name FROM {$db_prefix}players WHERE " .
						"destroyed='N' AND " .
						"email NOT LIKE '%@npc' and player_id > 3 ORDER BY score DESC");
	db_op_result($res,__LINE__,__FILE__);
	$row = $res->fields;
	$res->close();
	$dyn_top_score = $row['score'];
	$dyn_top_player = $row['character_name'];

	$res = $db->Execute("SELECT COUNT({$db_prefix}ships.ship_id) AS x FROM {$db_prefix}ships,{$db_prefix}players WHERE " .
						"{$db_prefix}ships.player_id = {$db_prefix}players.player_id AND {$db_prefix}players.destroyed='N' AND " .
						"{$db_prefix}players.email LIKE '%@npc' and {$db_prefix}players.player_id > 3");
	db_op_result($res,__LINE__,__FILE__);
	$row = $res->fields;
	$res->close();
	$dyn_kabal = $row['x'];

	$res = $db->Execute("SELECT AVG(hull) AS a1 , AVG(engines) AS a2 , AVG(power) AS a3 , AVG(fighter) AS a4 , " .
						"AVG(sensors) AS a5 , AVG(beams) AS a6 , AVG(torp_launchers) AS a7 , AVG(shields) AS a8 , " .
						"AVG(armor) AS a9 , AVG(cloak) AS a10, AVG(ecm) AS a11 FROM {$db_prefix}ships,{$db_prefix}players WHERE " .
						"{$db_prefix}ships.player_id = {$db_prefix}players.player_id AND {$db_prefix}players.destroyed='N' AND email LIKE '%@npc' and {$db_prefix}players.player_id > 3");
	db_op_result($res,__LINE__,__FILE__);
	$row = $res->fields;
	$res->close();
	$dyn_kabal_lvl = $row['a1'] + $row['a2'] + $row['a3'] + $row['a4'] + $row['a5'] + $row['a6'] + $row['a7'] + $row['a8'] + $row['a9'] + $row['a10'] + $row['a11'];
	$dyn_kabal_lvl = $dyn_kabal_lvl / 11;

	$gm_all2 .= "dyn_players=" . $dyn_players . "\n" .
			   "dyn_kabal=" . $dyn_kabal . "\n" .
			   "dyn_kabal_lvl=" . $dyn_kabal_lvl . "\n" .
			   "dyn_top_score=" . $dyn_top_score . "\n" .
			   "dyn_top_player=" . $dyn_top_player . "\n" .
			   "dyn_key=" . $server_list_key . "\n";

	if (isset($creating))
	{
		$gm_all2 = $gm_all2 . "gm_reset=1\n";
	}

	$gm_all2 .= "server_closed=$server_closed\n";
	$gm_all2 .= "account_creation_closed=$account_creation_closed\n";
	$gm_all2 .= "tournament_setup_access=$tournament_setup_access\n";
	$gm_all2 .= "tournament_mode=". $tournament_mode . "\n";
	$gm_all2 .= "profile_only_server=". $profile_only_server . "\n";

	$gm_all2 .= "reset_date=$reset_date\n";
	$gm_all2 .= "tournament_start_date=$tournament_start_date\n";
	$gm_all2 .= "scheduled_reset=$scheduled_reset\n";
	$gm_all2 .= "private=$private_server\n";
	$gm_all2 .= "ver=". $release_version . "\n";

	unlink($gameroot."templates_c/server_data" . $game_number . ".txt");
	$fs = fopen($gameroot.'templates_c/server_data' . $game_number . '.txt', 'w');
	$gm_url = $gameurl . $gamepath;
	@fwrite($fs, "server:$game_name\n");
	@fwrite($fs, "url:$gm_url\n");
	@fwrite($fs, $gm_all2);
	@fclose($fs);

	$url = "http://www.aatraders.com/aatrade_update_serverlist30.php?server=" . rawurlencode($gm_url) . "&game_number=" . $game_number;

	echo "\n\n<!--" . $url . "-->\n\n";

	if(@ini_get("allow_url_fopen") == 1)
	{
		TextFlush( "<br><br>Sending Server List data to the Profile Server through FOPEN.<br>");
		$fp = @fopen ($url,"r");
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
		TextFlush( "<br><br>Sending Server List data to the Profile Server through CURL.<br>");
		$ch=curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
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
else
{
	TextFlush( "\n\n<b>Server List Update is disabled.</b></br></br>\n\n");
}

?>
