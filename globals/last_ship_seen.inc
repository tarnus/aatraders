<?php
include ("globals/get_shipclassname.inc");

if (!function_exists('last_ship_seen')) {

	function last_ship_seen($sector_id, $player_id, $sensors)
	{
		global $lss_decay_time, $db, $db_prefix, $l_none, $lssd_level_three, $lssd_level_two;
		global $l_player, $l_onboard, $l_classship, $l_traveled, $l_unknown, $l_sector_0, $template_object;

		$lss_info = "";
		if ($sector_id != '1')
		{
			$oldstamp = strtotime(date("Y-m-d H:i:s")) - ($lss_decay_time * 86400);
			$decaydate = date("Y-m-d H:i:s", $oldstamp);
			$resx = $db->SelectLimit("SELECT {$db_prefix}universe.sector_name, {$db_prefix}sector_log.* from {$db_prefix}sector_log, {$db_prefix}universe WHERE {$db_prefix}sector_log.player_id <> $player_id AND {$db_prefix}sector_log.source = $sector_id and {$db_prefix}sector_log.time > '$decaydate' and {$db_prefix}sector_log.destination!=0  and {$db_prefix}universe.sector_id ={$db_prefix}sector_log.destination ORDER BY {$db_prefix}sector_log.time DESC", 1);
			db_op_result($resx,__LINE__,__FILE__);
			$myrow = $resx->fields;

			$success = SCAN_SUCCESS($sensors, $myrow['ship_cloak']);
			$roll = mt_rand(1, 100);

			if (!$myrow || $success <= $roll)
			{
				$lss_info = "$l_none";
				$template_object->assign("lss_playername", $l_none);
				$template_object->assign("lss_shipclass", "");
				$template_object->assign("lss_destination", "");
				$template_object->assign("lss_sensorlevel", 0);
			}
			else
			{
				if ($sensors >= $lssd_level_three)
				{
					$lss_info = "$l_player " . get_player($myrow['player_id']) . " $l_onboard " . get_shipclassname($myrow['ship_class']) . " $l_classship $l_traveled " . $myrow['sector_name'];
					$template_object->assign("lss_playername", get_player($myrow['player_id']));
					$template_object->assign("lss_shipclass", get_shipclassname($myrow['ship_class']));
					$template_object->assign("lss_destination", $myrow['sector_name']);
					$template_object->assign("lss_sensorlevel", 3);
				}
				elseif ($sensors >= $lssd_level_two)
				{
					$lss_info = "$l_player " . get_player($myrow['player_id']) . " $l_onboard " . get_shipclassname($myrow['ship_class']) . " $l_classship.";
					$template_object->assign("lss_playername", get_player($myrow['player_id']));
					$template_object->assign("lss_shipclass", get_shipclassname($myrow['ship_class']));
					$template_object->assign("lss_destination", "");
					$template_object->assign("lss_sensorlevel", 2);
				}
				else
				{
					$lss_info .= "$l_unknown " . get_shipclassname($myrow['ship_class']) . " $l_classship.";
					$template_object->assign("lss_playername", $l_unknown);
					$template_object->assign("lss_shipclass", get_shipclassname($myrow['ship_class']));
					$template_object->assign("lss_destination", "");
					$template_object->assign("lss_sensorlevel", 1);
				}
			}
		}
		else
		{
			$lss_info = "$l_sector_0";
			$template_object->assign("lss_playername", $l_sector_0);
			$template_object->assign("lss_shipclass", "");
			$template_object->assign("lss_destination", "");
			$template_object->assign("lss_sensorlevel", 0);
		}

		$template_object->assign("l_player", $l_player);
		$template_object->assign("l_onboard", $l_onboard);
		$template_object->assign("l_classship", $l_classship);
		$template_object->assign("l_traveled", $l_traveled);
		return $lss_info;
	}
}
?>