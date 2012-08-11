<?php
if (!function_exists('good_neutral_evil')) {
	function good_neutral_evil($player_rating, $compare_rating = 'none')
	{
		global $db, $db_prefix, $l_ranks_evil, $l_ranks_good, $l_ranks_neutral, $neutral_neg_percent, $neutral_pos_percent, $neutral_safezone;

		$debug_query = $db->SelectLimit("SELECT rating FROM {$db_prefix}players order by rating DESC", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$top_rating = $debug_query->fields['rating'];
		$debug_query->close();
		$debug_query = $db->SelectLimit("SELECT rating FROM {$db_prefix}players order by rating ASC", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$bottom_rating = $debug_query->fields['rating'];
		$debug_query->close();

		$lowend_neutral = floor($bottom_rating * ($neutral_neg_percent / 100));
		$highend_neutral = floor($top_rating * ($neutral_pos_percent / 100));

		if($compare_rating == 'none')
		{
			if($player_rating < $lowend_neutral && $player_rating < (($neutral_safezone / 2) - $neutral_safezone))
			{
				$rating[0] = -1;
				$rating[1] = $l_ranks_evil;
			}
			else
			if($player_rating > $highend_neutral && $player_rating > ($neutral_safezone / 2))
			{
				$rating[0] = 1;
				$rating[1] = $l_ranks_good;
			}
			else
			{
				$rating[0] = 0;
				$rating[1] = $l_ranks_neutral;
			}
		}
		else
		{
			if($player_rating < $lowend_neutral && $player_rating < (($neutral_safezone / 2) - $neutral_safezone))
			{
				$attacker = -1; // evil attacker
			}
			else
			if($player_rating > $highend_neutral && $player_rating > ($neutral_safezone / 2))
			{
				$attacker = 1; // good attacker
			}
			else
			{
				$attacker = 0; // neutral attacker
			}

			if($compare_rating < $lowend_neutral && $compare_rating < (($neutral_safezone / 2) - $neutral_safezone))
			{
				$defender = -1; // evil defender
			}
			else
			if($compare_rating > $highend_neutral && $compare_rating > ($neutral_safezone / 2))
			{
				$defender = 1; // good defender
			}
			else
			{
				$defender = 0; // neutral defender
			}

			// if the attacker and defender are opposite alignments then set to 1 to indicate a bounty free attack
			if(($attacker == -1 && $defender == 1) || ($attacker == 1 && $defender == -1))
			{
				$rating[0] = 1; // Bounty free attack
			}
			else
			{
				$rating[0] = 0;
			}

			// if this is an evil upon evil or neutral on evil attack set to 1.  This is used to determine if this is an Alliance bounty.
			if($attacker == -1 && $defender == -1 || $attacker == 0 && $defender == -1 )
			{
				$rating[1] = 1; // Alliance Bounty
			}
			else
			{
				$rating[1] = 0;
			}
		}

		return $rating;
	}
}
?>
