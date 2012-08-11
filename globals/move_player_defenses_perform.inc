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

	switch ($response) 
	{
		case "retreat":
			$stamp = date("Y-m-d H:i:s");

			$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp',turns=greatest(turns-$turns_required, 0), turns_used=turns_used+$turns_required WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=$shipinfo[sector_id] WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
      	
			unset($_SESSION['movedefense'], $movedefense);
			include ("header.php");
			$template_object->assign("error_msg", $l_chf_youretreatback);
			$template_object->assign("error_msg2", '');
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."move.tpl");
			include ("footer.php");
			die();
			break;

		case "fight":
			unset($_SESSION['movedefense'], $movedefense);
			$template_object->enable_gzip = 0;
			include ("header.php");
			$is_header = 1;
			include ("sector_defense/fighters.inc");
			break;

		case "run":
			if($_SESSION['movedefense'] != "defense_check" || $sectorinfo['zone_id'] == 2)
			{
				$move_failed = 1;
			}
			else
			{
				$template_object->enable_gzip = 0;
				include ("header.php");
				$is_header = 1;
				$stamp = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', turns=greatest(turns-$turns_required, 0),turns_used=turns_used+$turns_required WHERE player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				include ("sector_defense/attack_and_run.inc");
				echo $l_global_mmenu;
				unset($_SESSION['movedefense'], $movedefense);
				include ("footer.php");
				die();
			}
			break;
		case "sneak":
			$resultSDb = $db->Execute("SELECT player_id from {$db_prefix}sector_defense WHERE sector_id='$destination' and player_id != '$playerinfo[player_id]' and defense_type='fighters'");
			db_op_result($resultSDb,__LINE__,__FILE__);

			$fm_owner = $resultSDb->fields['player_id'];
			$resultSDb->close();
			$result_fo = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fm_owner", 1);
			db_op_result($result_fo,__LINE__,__FILE__);
			$fighters_owner = $result_fo->fields;
			$result_fo->close();

			$highsensors=0;
			// get planet sensors
			$result4 = $db->execute("SELECT sensors from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$destination' order by sensors DESC");
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;
			$result4->close();

			if ($highsensors < $planets['sensors']){
				$highsensors=$planets['sensors'];
			}
			$success = SCAN_SUCCESS($highsensors, $shipinfo['cloak'], $shiptypes[$shipinfo['class']]['basehull']);

			unset($_SESSION['movedefense'], $movedefense);

			if (mt_rand(1, 100) < $success)
			{
				// sector defenses detect incoming ship
				$template_object->enable_gzip = 0;
				include ("header.php");
				$is_header = 1;
				include ("sector_defense/fighters.inc");
				break;
			}
			else
			{
				// sector defenses don't detect incoming ship
				$move_failed = 0;
			}
			break;
	}
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

// clean up any sectors that have used up all mines or fighters
$db->Execute("delete from {$db_prefix}sector_defense where quantity <= 0 ");

?>
