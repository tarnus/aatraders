<?php
if (!function_exists('calc_ownership')) {
	function calc_ownership($sector)
	{
		global $min_bases_to_own;
		global $l_global_warzone, $l_global_nzone, $l_global_team, $l_global_player;
		global $l_global_nochange;
		global $db, $db_prefix;

		$res = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=$sector", 1);
		db_op_result($res,__LINE__,__FILE__);
		$zone = $res->fields;
		$res->close();

		if($zone['zone_id'] == 3 or $zone['zone_id'] == 2)
				return $l_global_nzone;

		$result3 = $db->Execute ("SELECT plr.player_id, plr.team FROM {$db_prefix}sector_defense as sd, {$db_prefix}players as plr WHERE sd.sector_id=$sector and plr.player_id=sd.player_id ");
		db_op_result($result3,__LINE__,__FILE__);

		$defense_player_id = array();
		$defense_team_id = array();
		$is_sector_defense = 0;
		if ($result3 > 0)
		{
			while (!$result3->EOF)
			{
				$defense_player_id[$i] = $result3->fields['player_id'];
				$defense_team_id[$i] = ($result3->fields['team'] == 0) ? $result3->fields['player_id'] : $result3->fields['team'];
				$is_sector_defense++;
				$i++;
				$result3->MoveNext();
			}
			$result3->close();
		}

		$sectordefense_no_match = 0;
		$res = $db->Execute("SELECT owner, team, base FROM {$db_prefix}planets WHERE sector_id=$sector");
		db_op_result($res,__LINE__,__FILE__);

		$num_bases = 0;
		while (!$res->EOF)
		{
			if($res->fields['base'] == "Y")
			{
				$bases[$num_bases] = $res->fields;
				$num_bases++;
			}
			if(!in_array($res->fields['owner'], $defense_player_id) && !in_array($res->fields['team'], $defense_team_id))
			{
				$sectordefense_no_match = 1;
			}
			$res->MoveNext();
		}
		$res->close();

		if(($num_bases == 0 && $sectordefense_no_match == 0) || $is_sector_defense == 0)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=1 WHERE sector_id=$sector AND zone_id > '2' ");
			db_op_result($debug_query,__LINE__,__FILE__);
			return $l_global_nzone;
		}

		if($sectordefense_no_match == 1 && $is_sector_defense != 0)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=4 WHERE sector_id=$sector");
			db_op_result($debug_query,__LINE__,__FILE__);

			return $l_global_warzone;
		}

		$owner_num = 0;
		foreach ($bases as $curbase)
		{
			$curteam = -1;
			$curship = -1;
			$loop = 0;
			while ($loop < $owner_num)
			{
				if ($curbase['team'] != 0)
				{
					if ($owners[$loop]['type'] == 'C')
					{
						if ($owners[$loop]['id'] == $curbase['team'])
						{
							$curteam = $loop;
							$owners[$loop]['num']++;
						}
					}
				}

				if ($owners[$loop]['type'] == 'S')
				{
					if ($owners[$loop]['id'] == $curbase['owner'])
					{
						$curship=$loop;
						$owners[$loop]['num']++;
					}
				}
				$loop++;
			}

			if ($curteam == -1)
			{
				if ($curbase['team'] != 0)
				{
					$curteam = $owner_num;
					$owner_num++;
					$owners[$curteam]['type'] = 'C';
					$owners[$curteam]['num'] = 1;
					$owners[$curteam]['id'] = $curbase['team'];
				}
			}

			if ($curship == -1)
			{
				if ($curbase['owner'] != 0)
				{
					$curship = $owner_num;
					$owner_num++;
					$owners[$curship]['type'] = 'S';
					$owners[$curship]['num'] = 1;
					$owners[$curship]['id'] = $curbase['owner'];
				}
			}
		}

		// We've got all the contenders with their bases.
		// Time to test for conflict

		$loop = 0;
		$nbteams = 0;
		$nbships = 0;

		while ($loop < $owner_num)
		{
			if ($owners[$loop]['type'] == 'C')
			{
				$nbteams++;
			}
			else
			{
				$res = $db->Execute("SELECT team FROM {$db_prefix}players WHERE player_id=" . $owners[$loop]['id']);
				db_op_result($res,__LINE__,__FILE__);		 
				if ($res && $res->RecordCount() != 0)
				{
					$curship = $res->fields;
					$ships[$nbships]=$owners[$loop]['id'];
					$steams[$nbships]=$curship['team'];
					$nbships++;
				}
				$res->close();
			}
			$loop++;
		}

		// More than one team, war
		if ($nbteams > 1)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=4 WHERE sector_id=$sector");
			db_op_result($debug_query,__LINE__,__FILE__);

			return $l_global_warzone;
		}

		// More than one unallied ship, war
		$numunallied = 0;
		foreach ($steams as $team)
		{
			if ($team == 0)
			{
				$numunallied++;
			}
		}

		if ($numunallied > 1)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=4 WHERE sector_id=$sector");
			db_op_result($debug_query,__LINE__,__FILE__);
			return $l_global_warzone;
		}

		// Unallied ship, another team present, war
		if ($numunallied > 0 && $nbteams > 0)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=4 WHERE sector_id=$sector");
			db_op_result($debug_query,__LINE__,__FILE__);
			return $l_global_warzone;
		}

		// Unallied ship, another ship in a team, war
		if ($numunallied > 0)
		{
			$query = "SELECT team FROM {$db_prefix}players WHERE (";
			$i = 0;
			foreach ($ships as $ship)
			{
				$query = $query . "player_id=$ship";
				$i++;

				if ($i != $nbships)
				{
					$query = $query . " OR ";
				}
				else
				{
					$query = $query . ")";
				}
			}

			$query = $query . " AND team!=0";
			$res = $db->Execute($query);
			db_op_result($res,__LINE__,__FILE__);

			if ($res->RecordCount() != 0)
			{
				$res->close();
				$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=4 WHERE sector_id=$sector");
				db_op_result($debug_query,__LINE__,__FILE__);
				return $l_global_warzone;
			}
			$res->close();
		}

		// Ok, all bases are allied at this point. Let's make a winner.
		$winner = 0;
		$i = 1;
		while ($i < $owner_num)
		{
			if ($owners[$i]['num'] > $owners[$winner]['num'])
			{
				$winner = $i;
			}
			elseif ($owners[$i]['num'] == $owners[$winner]['num'])
			{
				if ($owners[$i]['type'] == 'C')
				{
					$winner = $i;
				}
			}
			$i++;
		}

		$res = $db->Execute("SELECT COUNT(planet_id) AS total FROM {$db_prefix}planets WHERE sector_id='$sector'");
		db_op_result($res,__LINE__,__FILE__);
		$num_planets = $res->fields['total'];
		$res->close();

		$min_bases_to_own = round (($num_planets+1)/2);

		if ($owners[$winner]['num'] < $min_bases_to_own)
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=1 WHERE sector_id=$sector");
			db_op_result($debug_query,__LINE__,__FILE__);
			return $l_global_nzone;
		}

		if ($owners[$winner]['type'] == 'C')
		{
			$res = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}zones WHERE team_zone='Y' && owner=" . $owners[$winner]['id'], 1);
			db_op_result($res,__LINE__,__FILE__);
			$zone = $res->fields;
			$res->close();

			$res = $db->SelectLimit("SELECT team_name FROM {$db_prefix}teams WHERE id=" . $owners[$winner]['id'], 1);
			db_op_result($res,__LINE__,__FILE__);
			$team = $res->fields;
			$res->close();

			$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=$zone[zone_id] WHERE sector_id=$sector");
			db_op_result($debug_query,__LINE__,__FILE__);
			return "$l_global_team $team[team_name]!";
		}
		else
		{
			$onpar = 0;
			foreach ($owners as $curowner)
			{
				if ($curowner['type'] == 'S' && $curowner['id'] != $owners[$winner]['id'] && $curowner['num'] == $owners[$winner]['num'])
				$onpar = 1;
				break;
			}

			// Two allies have the same number of bases
			if ($onpar == 1)
			{
				$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=1 WHERE sector_id=$sector");
				db_op_result($debug_query,__LINE__,__FILE__);
				return $l_global_nzone;
			}
			else
			{
				$res = $db->SelectLimit("SELECT zone_id FROM {$db_prefix}zones WHERE team_zone='N' && owner=" . $owners[$winner]['id'], 1);
				db_op_result($res,__LINE__,__FILE__);
				$zone = $res->fields;
				$res->close();

				$res = $db->SelectLimit("SELECT character_name FROM {$db_prefix}players WHERE player_id=" . $owners[$winner]['id'], 1);
				db_op_result($res,__LINE__,__FILE__);
				$ship = $res->fields;
				$res->close();

				if($zone['zone_id'] == '' or $zone['zone_id'] == 0)
					$zone['zone_id'] = 1;

				$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET zone_id=$zone[zone_id] WHERE sector_id=$sector");
				db_op_result($debug_query,__LINE__,__FILE__);
				return "$l_global_player $ship[character_name]!";
			}
		}
	}
}
?>
