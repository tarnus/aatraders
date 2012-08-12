<?php
// 1
// 1600
// 1440
// 0
// Y
// How often to prune logs, news and players.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("languages/$langdir/lang_mail.inc");
include ("globals/cancel_bounty.inc");
include ("globals/artifacts_move.inc");

function cancel_fed_bounty($bounty_on)
{
	global $db, $db_prefix;
	$res = $db->Execute("SELECT * FROM {$db_prefix}bounty,{$db_prefix}players WHERE bounty_on = $bounty_on AND bounty_on = player_id");
	db_op_result($res,__LINE__,__FILE__);
	if ($res)
	{
		while (!$res->EOF)
		{
			$bountydetails = $res->fields;
			if ($bountydetails['placed_by'] == 1 || $bountydetails['placed_by'] == 3)
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits = credits + $bountydetails[amount] WHERE player_id = $bountydetails[placed_by]");
				db_op_result($debug_query,__LINE__,__FILE__);
				playerlog($bountydetails['placed_by'],"LOG0_BOUNTY_CANCELLED","$bountydetails[amount]|$bountydetails[character_name]");
				$debug_query = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bountydetails[bounty_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
			$res->MoveNext();
		}
		$res->close();
	}
}

function delete_player($player_id){

	global $db_prefix, $db;
	TextFlush (" Deleting player: $player_id<br>");

	artifacts_move(0, $player_id, 0);
	TextFlush ("DELETE FROM {$db_prefix}zones WHERE owner = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}zones WHERE owner = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}zones WHERE owner=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}traderoutes WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}traderoutes WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}traderoutes WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}shoutbox WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}shoutbox WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}shoutbox WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}sector_defense WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}sector_defense WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}message_block WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}message_block WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}message_block WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}probe WHERE owner_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}probe WHERE owner_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}probe WHERE owner_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}planet_log WHERE player_id = $player_id or owner_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}planet_log WHERE player_id = $player_id or owner_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}planet_log WHERE player_id = $player_id or owner_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}sector_log WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_log WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}sector_log WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}players WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}players WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}players WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}ships WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}ships WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}spies WHERE owner_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}spies WHERE owner_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE owner_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}dignitary WHERE owner_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}dignitary WHERE owner_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}dignitary WHERE owner_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}autotrades WHERE owner = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}autotrades WHERE owner = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}autotrades WHERE owner = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}detect WHERE owner_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}detect WHERE owner_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}detect WHERE owner_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}igb_transfers WHERE source_id = $player_id or dest_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}igb_transfers WHERE source_id = $player_id or dest_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}igb_transfers WHERE source_id = $player_id or dest_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}sector_notes WHERE note_player_id  = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_notes WHERE note_player_id  = $player_id ");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}sector_notes WHERE note_player_id = $player_id ");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}logs WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}logs WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}logs WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}ibank_accounts WHERE player_id = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}ibank_accounts WHERE player_id = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}ibank_accounts WHERE player_id = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("DELETE FROM {$db_prefix}bounty WHERE placed_by = $player_id<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE placed_by = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}bounty WHERE placed_by = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("UPDATE {$db_prefix}planets set owner=2, team=0, cargo_hull=0, cargo_power=0 WHERE owner = $player_id<br>");
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets set owner=2, team=0, cargo_hull=0, cargo_power=0 WHERE owner = $player_id");
//	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE owner = $player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
//	echo $debug_query->recordcount()."<br>";

	TextFlush ("SELECT * FROM {$db_prefix}teams WHERE creator = $player_id<br>");
	$debug_query2 = $db->Execute("SELECT * FROM {$db_prefix}teams WHERE creator = $player_id");
	db_op_result($debug_query2,__LINE__,__FILE__);
	TextFlush ( "Created Team: ".$debug_query2->recordcount()."<br>");

	$debug_query = $db->Execute("DELETE FROM {$db_prefix}casino_topics WHERE post_player_id=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}casino_posts WHERE post_player_id=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}casino_posts_text WHERE post_player_id=$player_id");
	db_op_result($debug_query,__LINE__,__FILE__);

	while(!$debug_query2->EOF){

		TextFlush ("UPDATE {$db_prefix}players set team=0 WHERE team = $player_id<br>");
		$query2 = $db->Execute("UPDATE {$db_prefix}players set team=0 WHERE team = $player_id");
//		$query2 = $db->Execute("SELECT * FROM {$db_prefix}players WHERE team = $player_id");
		db_op_result($query2,__LINE__,__FILE__);
//		echo $query2->recordcount()."<br>";

		TextFlush ("UPDATE {$db_prefix}players set team_invite=0 WHERE team_invite = $player_id<br>");
		$query2 = $db->Execute("UPDATE {$db_prefix}players set team_invite=0 WHERE team_invite = $player_id");
//		$query2 = $db->Execute("SELECT * FROM {$db_prefix}players WHERE team_invite = $player_id");
		db_op_result($query2,__LINE__,__FILE__);
//		echo $query2->recordcount()."<br>";

		TextFlush ("UPDATE {$db_prefix}planets set team=0 WHERE team = $player_id<br>");
		$query2 = $db->Execute("UPDATE {$db_prefix}planets set team=0 WHERE team = $player_id");
//		$query2 = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE team = $player_id");
		db_op_result($query2,__LINE__,__FILE__);
//		echo $query2->recordcount()."<br>";

		$debug_query2->MoveNext();
	}
	TextFlush ("<br>");

	TextFlush ("delete FROM {$db_prefix}teams WHERE creator = $player_id<br>");
	$debug_query2 = $db->Execute("delete FROM {$db_prefix}teams WHERE creator = $player_id");
	db_op_result($debug_query2,__LINE__,__FILE__);

	TextFlush ("delete FROM {$db_prefix}zones WHERE owner = $player_id<br>");
	$debug_query2 = $db->Execute("delete FROM {$db_prefix}zones WHERE owner = $player_id");
	db_op_result($debug_query2,__LINE__,__FILE__);

	TextFlush ("delete FROM {$db_prefix}sector_log WHERE player_id = $player_id<br>");
	$debug_query2 = $db->Execute("delete FROM {$db_prefix}sector_log WHERE player_id = $player_id");
	db_op_result($debug_query2,__LINE__,__FILE__);
}

if($disable_pruning != 1){
	TextFlush ( "<br>Current: ".date("Y-m-d H:i:s"));
	$stamp = strtotime(date("Y-m-d H:i:s")) - ($retaindataduration * 86400);
	$pruneshoutdate = $stamp;
	$prune_date = date("Y-m-d H:i:s", $stamp);
	TextFlush ( "<br>Prune News: $prune_date<br>");

	$stamp = strtotime(date("Y-m-d H:i:s")) - ($retainnonplayers * 86400);
	$nonplayer_date = date("Y-m-d H:i:s", $stamp);
	TextFlush ( "Delete Non Player Date: $nonplayer_date<br><br>");

//$stamp = strtotime(date("Y-m-d H:i:s")) - (($retainnonplayers - 3) * 86400);
//$warning_date = date("Y-m-d H:i:s", $stamp);
//echo "Warning Date: $warning_date<br>";

	$stamp = strtotime(date("Y-m-d H:i:s")) - ($retaindestroyedplayers * 86400);
	$delay_date = date("Y-m-d H:i:s", $stamp);
	TextFlush ( "Destroy Delay Date: $delay_date<br><br>");

	$stamp = strtotime(date("Y-m-d H:i:s")) - ($retainlogsduration * 86400);
	$log_date = date("Y-m-d H:i:s", $stamp);
	TextFlush ( "Delete Log Date: $log_date<br><br>");

	$stamp = strtotime(date("Y-m-d H:i:s")) - ($retainextendedlogsduration * 86400);
	$extended_log_date = date("Y-m-d H:i:s", $stamp);
	TextFlush ( "Delete Extended Admin Log Date: $log_date<br><br>");

// Prune all news past the data retention period
	TextFlush ("DELETE FROM {$db_prefix}news WHERE date < '$prune_date'<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}news WHERE date < '$prune_date'");
	db_op_result($debug_query,__LINE__,__FILE__);
//echo $debug_query->recordcount()."<br><br>";

// Prune all shouts past the data retention period
	TextFlush ("DELETE FROM {$db_prefix}shoutbox WHERE sb_date < '$pruneshoutdate'<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}shoutbox WHERE sb_date < '$pruneshoutdate'");
	db_op_result($debug_query,__LINE__,__FILE__);
//echo $debug_query->recordcount()."<br><br>";

// Prune all logs past the data retention period
	TextFlush ("DELETE FROM {$db_prefix}logs WHERE time < '$log_date'<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}logs WHERE time < '$log_date'");
	db_op_result($debug_query,__LINE__,__FILE__);
//echo $debug_query->recordcount()."<br><br>";

// Prune all logs past the data retention period
	TextFlush ("DELETE FROM {$db_prefix}admin_extended_logging WHERE time < '$extended_log_date'<br>");
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}admin_extended_logging WHERE time < '$extended_log_date'");
	db_op_result($debug_query,__LINE__,__FILE__);
//echo $debug_query->recordcount()."<br><br>";

// Prune all players who haven't played in the data retention period
	TextFlush ("SELECT * FROM {$db_prefix}players WHERE last_login < '$nonplayer_date'<br>");
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}players WHERE last_login < '$nonplayer_date' and player_id > 3 order by player_id");
	db_op_result($debug_query,__LINE__,__FILE__);
	TextFlush ( "Total Players Date Pruned: ".$debug_query->recordcount()."<br><br>");

	while(!$debug_query->EOF){

		if($enable_profilesupport == 1){
			if ((isset($debug_query->fields['profile_name'])) && ($debug_query->fields['profile_name'] != ''))
			{
				$gm_url = $_SERVER['HTTP_HOST'] . $gamepath;
				$gm_all = "&name=" . $debug_query->fields['profile_name'] .
					  "&password=" . $debug_query->fields['profile_password'] .
					  "&server_url=" . rawurlencode($gm_url);

				$url = "http://www.aatraders.com/delete_current.php?" . $gm_all;

				TextFlush ( "\n\n<!--" . $url . "-->\n\n");

				if(@ini_get("allow_url_fopen") == 1)
				{
					TextFlush( "<br><br>Sending Player Deletion data to the Profile Server through FOPEN.<br>");
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
					TextFlush( "<br><br>Sending Player Deletion data to the Profile Server through CURL.<br>");
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
		}
		cancel_bounty($debug_query->fields['player_id']);
		cancel_fed_bounty($debug_query->fields['player_id']);
		delete_player($debug_query->fields['player_id']);

		$junkold = explode("/", $debug_query->fields['avatar']);
		$galleryold = $junkold[0];
		$pictureold = $junkold[1];
		if($galleryold == "uploads"){
			@unlink($gameroot."images/avatars/uploads/$pictureold");
		}

		$debug_query->MoveNext();
	}
	$debug_query->close();

// Prune all players who have died completely
	TextFlush ("SELECT {$db_prefix}dead_players.player_id FROM {$db_prefix}dead_players, {$db_prefix}players WHERE {$db_prefix}players.player_id={$db_prefix}dead_players.player_id and {$db_prefix}dead_players.last_login < '$delay_date'");
	$debug_query = $db->Execute("SELECT {$db_prefix}dead_players.player_id FROM {$db_prefix}dead_players, {$db_prefix}players WHERE {$db_prefix}players.player_id={$db_prefix}dead_players.player_id and {$db_prefix}dead_players.last_login < '$delay_date'");
	db_op_result($debug_query,__LINE__,__FILE__);
	TextFlush ( "Total Players Destroyed Pruned: ".$debug_query->recordcount()."<br><br>");

	while(!$debug_query->EOF){
		cancel_bounty($debug_query->fields['player_id']);
		cancel_fed_bounty($debug_query->fields['player_id']);
		delete_player($debug_query->fields['player_id']);

		$junkold = explode("/", $debug_query->fields['avatar']);
		$galleryold = $junkold[0];
		$pictureold = $junkold[1];
		if($galleryold == "uploads"){
			@unlink($gameroot."images/avatars/uploads/$pictureold");
		}

		$debug_query->MoveNext();
	}
	$debug_query->close();
}else{
	TextFlush ( "Auto Pruning Disabled.");
}

$multiplier = 0; //no use to run this again

//include ("footer.php");
?>
