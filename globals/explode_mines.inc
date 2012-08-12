<?php
if (!function_exists('explode_mines')) {
	function explode_mines($sector, $num_mines)
	{
		global $db, $db_prefix, $playerinfo;

		if($playerinfo['team'] == 0)
		{
			$result3 = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sector' and defense_type ='mines' and player_id != '$playerinfo[player_id]' order by quantity ASC");
		}
		else
		{
			$result3 = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense,{$db_prefix}players WHERE {$db_prefix}sector_defense.sector_id='$sector' and {$db_prefix}sector_defense.defense_type ='mines' and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]' and ({$db_prefix}players.player_id={$db_prefix}sector_defense.player_id and {$db_prefix}players.team != $playerinfo[team]) order by quantity ASC");
		}
		db_op_result($result3,__LINE__,__FILE__);

		//Put the defense information into the array "defenseinfo"
		if ($result3 > 0)
		{ 
			while (!$result3->EOF && $num_mines > 0)
			{
				$row = $result3->fields;
				if ($row['quantity'] > $num_mines)
				{
					$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=GREATEST(0, quantity - $num_mines) where defense_id = $row[defense_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$num_mines = 0;
				}
				else
				{
					$debug_query = $db->Execute("DELETE FROM {$db_prefix}sector_defense WHERE defense_id = $row[defense_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$num_mines -= $row['quantity'];
				}

				$result3->MoveNext();
			}
		}
		$result3->close();
	}
}
?>
