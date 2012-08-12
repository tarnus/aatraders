<?php
if (!function_exists('spy_detect_planet')) {
	function spy_detect_planet($shipowner_ship_id, $planet_id, $succ)
	{
		global $db;
		global $db_prefix;
		global $l_unnamed;

		mt_srand((double)microtime()*1000000);
		$res0 = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE ship_id='$shipowner_ship_id' AND active='Y'"); //// AND owner_id <> ship_id ///MITTE kasutada!
		while (!$res0->EOF)
		{
			$spyowners = $res0->fields;

			$i = mt_rand(1,100);
			if ($i <= $succ)
			{
				$res = $db->Execute("SELECT * FROM {$db_prefix}detect WHERE unique_value = '$planet_id' AND owner_id=$spyowners[owner_id] AND det_type = '0'");
				if (!$res->RecordCount())
				{
					$res = $db->Execute("SELECT {$db_prefix}planets.planet_id, {$db_prefix}planets.sector_id, {$db_prefix}planets.name, {$db_prefix}players.character_name FROM {$db_prefix}planets LEFT JOIN {$db_prefix}players ON {$db_prefix}planets.owner={$db_prefix}players.player_id WHERE {$db_prefix}planets.planet_id = '$planet_id' AND {$db_prefix}planets.owner <> $spyowners[owner_id]");
					if ($res->RecordCount())
					{
						$planet = $res->fields;
						if (!$planet['name']) 
						{ 
							$planet['name'] = $l_unnamed; 
						}
						$stamp = date("Y-m-d H:i:s");
						$planet['name'] = addslashes($planet['name']);;
						$debug_query = $db->Execute("INSERT INTO {$db_prefix}detect values('', '$spyowners[owner_id]', '0', '$stamp'," . $db->qstr("$planet[sector_id]|$planet[character_name]|$planet[name]") . ", '$planet[planet_id]' ) ");
						db_op_result($debug_query,__LINE__,__FILE__);
					}
					$res->close();
				}
			}
			$res0->MoveNext();
		}
		$res0->close();
	}
}
?>
