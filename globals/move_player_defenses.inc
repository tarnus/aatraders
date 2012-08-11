<?php
$move_failed = 0;

if($playerinfo['team'] == 0)
{
	$result3 = $db->Execute ("SELECT defense_type, SUM(quantity) as amount FROM {$db_prefix}sector_defense WHERE sector_id='$destination' and player_id != '$playerinfo[player_id]' GROUP BY defense_type");
}
else
{
	$result3 = $db->Execute ("SELECT {$db_prefix}sector_defense.defense_type, SUM({$db_prefix}sector_defense.quantity) as amount FROM {$db_prefix}sector_defense, {$db_prefix}players WHERE {$db_prefix}sector_defense.sector_id='$destination' and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]' and ({$db_prefix}players.player_id={$db_prefix}sector_defense.player_id and {$db_prefix}players.team != $playerinfo[team]) GROUP BY {$db_prefix}sector_defense.defense_type");
}
db_op_result($result3,__LINE__,__FILE__);

if ($result3 > 0)
{
	while (!$result3->EOF)
	{
		$row = $result3->fields;
		$defenses[$row['defense_type']] = $row['amount'];

		$result3->MoveNext();
	}
}
$result3->close();

if ($defenses['fighters'] > 0 && $playerinfo['player_id'] != 3)
{
	$resultSDb = $db->Execute("SELECT * from {$db_prefix}sector_defense WHERE sector_id='$destination' and player_id != '$playerinfo[player_id]' and defense_type='fighters'");
	db_op_result($resultSDb,__LINE__,__FILE__);
	$has_fighters = 0;
	$highjammer=0;
	if ($resultSDb > 0)
	{
		while (!$resultSDb->EOF)
		{
			$fm_owner = $resultSDb->fields['player_id'];
			$result_fo = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fm_owner", 1);
			db_op_result($result_fo,__LINE__,__FILE__);
			$fighters_owner = $result_fo->fields;
			$result_fo->close();

			$highcloak = 0;
			// get planet sensors
			$result4 = $db->SelectLimit("SELECT * from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$destination' order by sensors DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;
			$result4->close();
			if ($highcloak < $planets['cloak']){
				$highcloak=$planets['cloak'];
			}

			$highjammer = 0;
			$result4 = $db->SelectLimit("SELECT * from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$destination' order by jammer DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;
			$result4->close();
			if ($highjammer < $planets['jammer']){
				$highjammer=$planets['jammer'];
			}

			$success = SCAN_SUCCESS($shipinfo['sensors'], $highcloak);

			if (mt_rand(1, 100) < $success)
			{
				$mines = $resultSDb->fields['quantity'];
				$planet_comp_level = SCAN_ERROR($shipinfo['sensors'], $highjammer, $mines);

				if ($planet_comp_level > $mines)
				{
					$planetfighters = $mines;
				}
				else
				{
					$planetfighters = $planet_comp_level;
				}

				$has_fighters += $planetfighters;
			}
			$resultSDb->MoveNext();
		}

		if($has_fighters == 0){
			$has_fighters = "???";
		}
		else
		{
			$has_fighters = NUMBER($has_fighters);
		}
	}
	$resultSDb->close();
	//=========================================================================

	$_SESSION['movedefense'] = "defense_check";
	$stamp = date("Y-m-d H:i:s");
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', turns=turns-$turns_required,turns_used=turns_used+$turns_required WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$l_chf_therearetotalfightersindest = str_replace("[chf_total_sector_fighters]", $has_fighters, $l_chf_therearetotalfightersindest);
	include ("header.php");
	$template_object->assign("sector_zone_id", $sectorinfo['zone_id']);
	$template_object->assign("l_chf_therearetotalfightersindest", $l_chf_therearetotalfightersindest);
	$template_object->assign("l_chf_youcanretreat", $l_chf_youcanretreat);
	$template_object->assign("l_chf_inputfight", $l_chf_inputfight);
	$template_object->assign("l_chf_inputrun", $l_chf_inputrun);
	$template_object->assign("l_chf_inputcloak", $l_chf_inputcloak);
	$template_object->assign("l_chf_go", $l_chf_go);
	$template_object->assign("move_method", $move_method);
	$template_object->assign("destination", $destination_name);
	$template_object->assign("sector", $sector);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."move_fighters.tpl");
	include ("footer.php");
	die();
}

if ($defenses['mines'] > 0 && $playerinfo['player_id'] != 3)
{
	$minesfound = 1;
	$template_object->enable_gzip = 0;
	if($is_header == 0)
	{
		include ("header.php");
		$is_header = 1;
	}
	include("sector_defense/mines.inc");
}

// end of sector defense check
?>