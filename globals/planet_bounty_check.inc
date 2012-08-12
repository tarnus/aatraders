<?php
include ("globals/gen_score.inc");
include ("globals/get_sector_bounty_control.inc");
include ("globals/insert_news.inc");
include ("globals/good_neutral_evil.inc");
include ("globals/send_system_im.inc");

// $apply = 0 - Check for bounty
// $apply = 1 - Check for bounty and if attacker gets bounty apply it to the player and announce it
// If the return value is 0 then no bounty,  If it is anything but 0 then that is the bounty amount.
// $modifier can be used to raise or lower the default bounty amount given to a player
if (!function_exists('planet_bounty_check')) {
	function planet_bounty_check($attacker, $ship_sector, $target, $apply, $modifier = 1)
	{
		global $db, $db_prefix, $debug_attack, $planet_bounty_ratio, $bounty_minturns, $bounty_maxvalue, $bounty_multiplier_increase, $l_im_fed_bounty, $l_im_fed_bounty_title, $l_im_alliance_bounty, $l_im_alliance_bounty_title, $fed_collection_start2;

		$debug_attack = array();
		$teamtarget_score = 0;

		$returnscore = gen_score($attacker['player_id']);
		$playerscore = $returnscore[1];
		$returnscore = gen_score($target['player_id']);
		$targetscore = $returnscore[1];


		if($target['team'] != 0)
		{
			$debug_query = $db->SelectLimit("SELECT player_id FROM {$db_prefix}players WHERE team=$target[team] order by score DESC", 1);
			db_op_result($debug_query,__LINE__,__FILE__);
			$teamtarget_id = $debug_query->fields['player_id'];
			$returnscore = gen_score($teamtarget_id);
			$teamtarget_score = $returnscore[1];
			$debug_query->close();
		}
		else
		{
			$teamtarget_id = $target['player_id'];
		}

		if($teamtarget_score > $targetscore)
		{
			$targetscore = $teamtarget_score * $teamtarget_score;
		}
		else
		{
			$targetscore = $targetscore * $targetscore;
		}

		$playerscore = $playerscore * $playerscore;
		$debug_attack['attackerscore'] = NUMBER($playerscore);
		$debug_attack['targetscore'] = NUMBER($targetscore);

		if ($playerscore == 0) 
		{
			$playerscore = 1;
		}

		$debug_attack['hasbounty'] = "No Check";
		$debug_attack['isowner'] = "No Check";
		$debug_attack['isopposite'] = "No Check";
		$debug_attack['evilevil'] = "No Check";
		$dummy = ($target['player_id'] > 3 && $planet_bounty_ratio != 0 && (($targetscore / $playerscore) < $planet_bounty_ratio || ($target['turns_used'] < $bounty_minturns && (round($target['score'] / $target['turns_used']) < 100))) && !("@npc" == AAT_substr($target['email'], -4))) ? "True" : "False";
		$debug_attack['ratio'] = NUMBER($targetscore / $playerscore) . " < " . $planet_bounty_ratio . " : " . $dummy;
		$debug_attack['turns'] = $target['turns_used'] . " < " . $bounty_minturns;
		if ($target['player_id'] > 3 && $planet_bounty_ratio != 0 && (($targetscore / $playerscore) < $planet_bounty_ratio || ($target['turns_used'] < $bounty_minturns && (round($target['score'] / $target['turns_used']) < 100))) && !("@npc" == AAT_substr($target['email'], -4)))
		{
			// Check to see if there is Federation bounty on the player. If there is, people can attack regardless.
			$btyamount = 0;
			$hasbounty = $db->Execute("SELECT SUM(amount) AS btytotal FROM {$db_prefix}bounty WHERE (bounty_on = $target[player_id] OR bounty_on = $teamtarget_id) AND (placed_by = 3 or placed_by = 1)");
			if ($hasbounty)
			{
				$resx = $hasbounty->fields;
				$btyamount = (!empty($resx['btytotal'])) ? $resx['btytotal'] : 0;
			}
			$hasbounty->close();
			$debug_attack['hasbounty'] = ($btyamount != 0) ? "Yes" : "No";

			$is_owner = get_sector_bounty_control($ship_sector);
			if($is_owner)
			{
				$btyamount = 1;
			}
			$debug_attack['isowner'] = ($btyamount == 1) ? "Yes" : "No";

			$is_opposite = good_neutral_evil($attacker['rating'], $target['rating']);

			if(($target['fed_bounty_count'] + $target['alliance_bounty_count']) >= $fed_collection_start2)
			{
				$btyamount = 1;
			}

			if ($btyamount == 0)
			{
				$bounty = ROUND(($playerscore * $bounty_maxvalue * $modifier) * $attacker['bounty_multiplier']);

				if($apply == 1)
				{
					if($is_opposite[1] == 0)
					{
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}bounty (bounty_on,placed_by,amount) values ($attacker[player_id], 3 ,$bounty)");
						db_op_result($debug_query,__LINE__,__FILE__);					

						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET bounty_multiplier = bounty_multiplier+$bounty_multiplier_increase, fed_bounty_count=fed_bounty_count+1, fed_attack_date='0000-00-00 00:00:00' WHERE player_id=$attacker[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);

						playerlog($attacker['player_id'],"LOG0_BOUNTY_FEDBOUNTY","$bounty");
						insert_news("Federation|".$bounty."|".$attacker['character_name'], 1, "bounty");
						send_system_im($attacker['player_id'], $l_im_fed_bounty_title, $l_im_fed_bounty, $attacker['last_login']);
					}
					else
					{
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}bounty (bounty_on,placed_by,amount) values ($attacker[player_id], 1 ,$bounty)");
						db_op_result($debug_query,__LINE__,__FILE__);					

						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET bounty_multiplier = bounty_multiplier+$bounty_multiplier_increase, alliance_bounty_count=alliance_bounty_count+1, alliance_attack_date='0000-00-00 00:00:00' WHERE player_id=$attacker[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);

						playerlog($attacker['player_id'],"LOG0_BOUNTY_ALLIANCEBOUNTY","$bounty");
						insert_news("Alliance|".$bounty."|".$attacker['character_name'], 1, "bounty");
						send_system_im($attacker['player_id'], $l_im_alliance_bounty_title, $l_im_alliance_bounty, $attacker['last_login']);
					}
				}
				return $bounty;
			}
		}
		return 0;
	}
}
?>