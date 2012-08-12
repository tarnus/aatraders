<?php
if (!function_exists('cancel_bounty')) {
	function cancel_bounty($bounty_on)
	{
		global $db, $db_prefix;
		$res = $db->Execute("SELECT * FROM {$db_prefix}bounty,{$db_prefix}players WHERE bounty_on = $bounty_on AND bounty_on = player_id");
		db_op_result($res,__LINE__,__FILE__);
		if ($res)
		{
			while (!$res->EOF)
			{
				$bountydetails = $res->fields;
				if ($bountydetails['placed_by'] != 1 && $bountydetails['placed_by'] != 3)
				{
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits = credits + $bountydetails[amount] WHERE player_id = $bountydetails[placed_by]");
					db_op_result($debug_query,__LINE__,__FILE__);
					playerlog($bountydetails['placed_by'],"LOG0_BOUNTY_CANCELLED","$bountydetails[amount]|$bountydetails[character_name]");
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bountydetails[bounty_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
				}
				$res->MoveNext();
			}
		}
		$res->close();
	}
}
?>
