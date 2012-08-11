<?php
if (!function_exists('spy_sneak_to_planet')) {
	function spy_sneak_to_planet($planet_id, $ship_id)
	{
		global $db;
		global $db_prefix;
		global $max_spies_per_planet;
		global $sneak_toplanet_success;

		mt_srand((double)microtime()*1000000);
		$res = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE ship_id = '$ship_id' AND active = 'Y' AND move_type = 'toplanet' "); 
		while (!$res->EOF)
		{
			$spy = $res->fields;

			$i = mt_rand(1,100);
			if ($i <= $sneak_toplanet_success)
			{
				$res2 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '$planet_id' AND owner_id = '$spy[owner_id]' "); 
				if ($res2->RecordCount() < $max_spies_per_planet)
				{
					$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET planet_id = '$planet_id', ship_id = '0', move_type = 'none' WHERE spy_id = '$spy[spy_id]' "); 
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->SelectLimit("SELECT {$db_prefix}spies.*, {$db_prefix}planets.name, {$db_prefix}planets.sector_id, {$db_prefix}players.character_name, {$db_prefix}ships.name as ship_name FROM {$db_prefix}spies INNER JOIN {$db_prefix}planets ON {$db_prefix}spies.planet_id = {$db_prefix}planets.planet_id INNER JOIN {$db_prefix}players ON {$db_prefix}planets.owner = {$db_prefix}players.player_id  INNER JOIN {$db_prefix}ships ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE {$db_prefix}spies.spy_id = $spy[spy_id] ", 1);
					db_op_result($debug_query,__LINE__,__FILE__);
					$info = $debug_query->fields;
					$debug_query->close();
					playerlog($info['owner_id'], "LOG2_SPY_TOPLANET", "$info[spy_id]|$info[name]|$info[sector_id]|$info[character_name]|$info[ship_name]");
				}
			}
			$res->MoveNext();
		}
		$res->close();
	}
}
?>
