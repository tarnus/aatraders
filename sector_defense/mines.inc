<?php
include ("languages/$langdir/lang_check_mines.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/explode_mines.inc");
include ("globals/message_defense_owner.inc");
include ("globals/cancel_bounty.inc");
// Lets blow up some mines!
$ok = 0;
$totalmines = isset($defenses['mines']) ? $defenses['mines'] : 0;

if ($totalmines > 1)
{
	$roll = mt_rand(1,$totalmines);
	if($roll < 0)
		$roll = floor($totalmines * (rand(1, 10000) * 0.0001));
}
else
{
	$roll = 1;
}
$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$destination'", 1);
if($sector_check->RecordCount()){
	$sect = $sector_check->fields;
	$sectorname = $sect['sector_name'];
}
$sector_check->close();
if($shipinfo['hull_normal'] > $mine_hullsize)
{
	echo "<table align=\"center\" bgcolor=#000000 border=1><tr><td align=center><font color=\"#ff0000\"><b>";
	$defenses['mines'] = $totalmines - $roll;
	$l_chm_youhitsomemines = str_replace("[chm_roll]", NUMBER($roll), $l_chm_youhitsomemines);
	$l_chm_youhitsomemines = str_replace("[total_mines]", "<font color=\"yellow\">" . NUMBER($totalmines) . "</font>", $l_chm_youhitsomemines);
	echo "$l_chm_youhitsomemines<br>";
	playerlog($playerinfo['player_id'], "LOG5_HIT_MINES", "$roll|$destination");

	$inputtype[0] = "[chm_playerinfo_character_name]";
	$inputdata[0] = $playerinfo['character_name'];
	$inputtype[1] = "[chm_roll]";
	$inputdata[1] = $roll;
	$inputtype[2] = "[chm_sector]";
	$inputdata[2] = "<a href=main.php?move_method=real&engage=1&destination=$sectorname>$sectorname</a>";
	message_defense_owner($destination, "l_chm_hehitminesinsector", "lang_check_mines.inc", "mines", $inputtype, $inputdata);

	if ($shipdevice['dev_minedeflector']['amount'] >= $roll)
	{
		$l_chm_youlostminedeflectors = str_replace("[chm_roll]", NUMBER($roll), $l_chm_youlostminedeflectors);
		echo "$l_chm_youlostminedeflectors<br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-$roll WHERE device_id=" . $shipdevice['dev_minedeflector']['device_id']);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
	else
	{
		if ($shipdevice['dev_minedeflector']['amount'] > 0)
		{
			echo "$l_chm_youlostallminedeflectors<br>";
		}
		else
		{
			echo "$l_chm_youhadnominedeflectors<br>";
		}

		$mines_left = $roll - $shipdevice['dev_minedeflector']['amount'];
		$playershields = NUM_SHIELDS($shipinfo['shields']);

		if ($playershields > $shipinfo['energy'])
		{
			$playershields = $shipinfo['energy'];
		}

	   if ($playershields >= $mines_left)
	   {
		   $l_chm_yourshieldshitforminesdmg = str_replace("[chm_mines_left]", NUMBER($mines_left), $l_chm_yourshieldshitforminesdmg);
		   echo "$l_chm_yourshieldshitforminesdmg<br>";
		   $debug_query = $db->Execute("UPDATE {$db_prefix}ships set energy=energy-$mines_left WHERE ship_id=$shipinfo[ship_id]");
		   db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=0 WHERE device_id=" . $shipdevice['dev_minedeflector']['device_id']);
			db_op_result($debug_query,__LINE__,__FILE__);
		   if ($playershields == $mines_left) 
		   {
			   echo "$l_chm_yourshieldsaredown<br>";
		   }
	   }
	   else
	   {
		   echo "$l_chm_youlostallyourshields<br>";
		   $mines_left = $mines_left - $playershields;
		   if ($shipinfo['armor_pts'] >= $mines_left)
		   {
			   $l_chm_yourarmorhitforminesdmg = str_replace("[chm_mines_left]", NUMBER($mines_left), $l_chm_yourarmorhitforminesdmg);
			   echo "$l_chm_yourarmorhitforminesdmg<br>";
			   $debug_query = $db->Execute("UPDATE {$db_prefix}ships SET armor_pts=armor_pts-$mines_left,energy=0 WHERE ship_id=$shipinfo[ship_id]");
			   db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=0 WHERE device_id=" . $shipdevice['dev_minedeflector']['device_id']);
				db_op_result($debug_query,__LINE__,__FILE__);
			   if ($shipinfo['armor_pts'] == $mines_left) 
			   {
				   echo "$l_chm_yourhullisbreached<br>";
			   }
		   }
		   else
		   {
			   playerlog($playerinfo['player_id'], "LOG5_SHIP_DESTROYED_MINES", "$destination|" . $shipdevice['dev_escapepod']['amount']);

				$inputtype[0] = "[chm_playerinfo_character_name]";
				$inputdata[0] = $playerinfo['character_name'];
				$inputtype[1] = "[chm_sector]";
				$inputdata[1] = "<a href=main.php?move_method=real&engage=1&destination=$sectorname>$sectorname</a>";
				message_defense_owner($destination, "l_chm_hewasdestroyedbyyourmines", "lang_check_mines.inc", "mines", $inputtype, $inputdata);

			   echo "$l_chm_yourshiphasbeendestroyed<br><br>";

				$move_failed = 1;

			   if ($shipdevice['dev_escapepod']['amount'] == 1) 
			   {
				   echo "$l_chm_luckescapepod<br><br>";
				   player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], 0, 0, "killedSDpod", "Y");

				   cancel_bounty($playerinfo['player_id']);
			   }
			   else
			   {
				   cancel_bounty($playerinfo['player_id']);
				   db_kill_player($playerinfo['player_id'], 0, 0, "killedSD", "Y");
			   }
		   }
	   }
	}
	echo "</b></font></td></tr></table>";
	explode_mines($destination,$roll);
}
else
{
	$minesfound = 0;
}
?>