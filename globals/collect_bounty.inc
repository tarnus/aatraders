<?php
if (!function_exists('collect_bounty')) {
	function collect_bounty($attacker,$bounty_on)
	{
		global $db, $db_prefix;
		global $l_by_thefeds, $fed_bounty_count, $l_by_thealliance;
		$res = $db->Execute("SELECT * FROM {$db_prefix}bounty,{$db_prefix}players WHERE bounty_on = $bounty_on AND bounty_on = player_id ");
		db_op_result($res,__LINE__,__FILE__);
		if ($res)
		{
			while (!$res->EOF)
			{
				$bountydetails = $res->fields;

				$res2 = $db->SelectLimit("SELECT character_name, score FROM {$db_prefix}players WHERE player_id = $bountydetails[placed_by]", 1);
	   			db_op_result($res2,__LINE__,__FILE__);
		   		$placed = $res2->fields['character_name'];
		   		$placed_score = $res2->fields['score'] * $res2->fields['score'];
				$res2->close();

				$res2 = $db->SelectLimit("SELECT score FROM {$db_prefix}players WHERE player_id = $attacker", 1);
	   			db_op_result($res2,__LINE__,__FILE__);
		   		$attacker_score = $res2->fields['score'] * $res2->fields['score'];
				$res2->close();
		   		$ratio = min(1, ($attacker_score / $placed_score));

				$fedtot=round($bountydetails['amount']*$ratio);
				$tax=$bountydetails['amount']-$fedtot;

				if ($bountydetails['placed_by'] == 3)
   				{
					if ($bountydetails['fed_bounty_count'] < $fed_bounty_count)
					{
						$placed = $l_by_thefeds;
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits = credits + $fedtot WHERE player_id = $attacker");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($attacker, "LOG0_BOUNTY_CLAIMED", "$fedtot|$bountydetails[character_name]|$placed");
						playerlog($attacker,"LOG0_BOUNTY_TAX_PAID","$tax|$bountydetails[character_name]");
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bountydetails[bounty_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($bountydetails['placed_by'],"LOG0_BOUNTY_PAID","$bountydetails[amount]|$bountydetails[character_name]");
					}
				}else
				if ($bountydetails['placed_by'] == 1)
   				{
					if ($bountydetails['alliance_bounty_count'] < $fed_bounty_count)
					{
						$placed = $l_by_thealliance;
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits = credits + $fedtot WHERE player_id = $attacker");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($attacker, "LOG0_BOUNTY_CLAIMED", "$fedtot|$bountydetails[character_name]|$placed");
						playerlog($attacker,"LOG0_BOUNTY_TAX_PAID","$tax|$bountydetails[character_name]");
						$debug_query = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bountydetails[bounty_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						playerlog($bountydetails['placed_by'],"LOG0_BOUNTY_PAID","$bountydetails[amount]|$bountydetails[character_name]");
					}
				}else{
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits = credits + $fedtot WHERE player_id = $attacker");
					db_op_result($debug_query,__LINE__,__FILE__);
					playerlog($attacker, "LOG0_BOUNTY_CLAIMED", "$fedtot|$bountydetails[character_name]|$placed");
					playerlog($attacker,"LOG0_BOUNTY_TAX_PAID","$tax|$bountydetails[character_name]");
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bountydetails[bounty_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					playerlog($bountydetails[placed_by],"LOG0_BOUNTY_PAID","$bountydetails[amount]|$bountydetails[character_name]");
	   			}
				$res->MoveNext();
			}
		}
		$res->close();
	}
}
?>
