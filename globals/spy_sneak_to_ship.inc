<?php
if (!function_exists('spy_sneak_to_ship')) {

	function spy_sneak_to_ship($planet_id, $ship_id)
	{
		global $db;
		global $db_prefix;
		global $sneak_toship_success;

		mt_srand((double)microtime()*1000000);  
		$i=0;
		$res = $db->Execute("SELECT {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}planets.sector_id, {$db_prefix}players.character_name, {$db_prefix}ships.name AS ship_name FROM {$db_prefix}players INNER JOIN {$db_prefix}ships ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id INNER JOIN {$db_prefix}planets ON {$db_prefix}players.player_id = {$db_prefix}planets.owner INNER JOIN {$db_prefix}spies ON {$db_prefix}planets.planet_id = {$db_prefix}spies.planet_id WHERE {$db_prefix}spies.planet_id = $planet_id AND {$db_prefix}spies.active = 'Y' AND {$db_prefix}spies.move_type <> 'none' "); 
		while (!$res->EOF)
		{
			$spy = $res->fields;
			$flag=1;
			for($j=1; $j<=$i; $j++)
			{
				if ($spy['owner_id'] == $changers[$j])
				{
					$flag = 0;
				}
			}

			if ($flag)
			{
				$k = mt_rand(1,100);
				if ($k <= $sneak_toship_success)
				{
					$res2 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE ship_id = '$ship_id' AND active = 'Y' AND owner_id = $spy[owner_id] "); 
					if ($res2->EOF) //No spies on ship
					{
						$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET planet_id = '0', ship_id = '$ship_id' WHERE spy_id = $spy[spy_id] "); 
						db_op_result($debug_query,__LINE__,__FILE__);

						playerlog($spy['owner_id'], "LOG2_SPY_TOSHIP", "$spy[spy_id]|$spy[name]|$spy[sector_id]|$spy[character_name]|$spy[ship_name]");
						$i++;
						$changers[$i] = $spy['owner_id'];
					}
					$res2->close();
				}
			}
			$res->MoveNext();
		}
		$res->close();
	}
}
?>
