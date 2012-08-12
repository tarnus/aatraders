<?php
include ("languages/$langdir/lang_move.inc");
include ("languages/$langdir/lang_check_fighters.inc");
include ("languages/$langdir/lang_check_mines.inc");
include ("globals/combat_functions.inc");
include ("globals/log_move.inc");
include ("globals/calc_dist.inc");
include ("globals/device_ship_tech_modify.inc");
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

get_post_ifset("destination, explore, response");

if ($destination == '') {
	include ("header.php");
	$template_object->assign("error_msg", $l_move_failed);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."movedie.tpl");
	include ("footer.php");
	die();
}

$destination = urldecode($destination);
$destination_name = $destination;

$energy_collected = 0;

switch ($move_method)
{
	case "real":
		$result = $db->Execute("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($destination) . " and sg_sector=0");
		$destination = $result->fields['sector_id'];

		if($result)
		{
			if($result->RecordCount() == 0 || $sectorinfo['sg_sector'] != 0)
			{
				include ("header.php");
				$move_failed = 1;
				$template_object->assign("error_msg", $l_rs_invalid);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."movedie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				$distance = calc_dist($shipinfo['sector_id'],$destination);
				$shipspeed = mypw($level_factor, $shipinfo['engines']);
				$turns_required = round($distance / $shipspeed);
				if ($turns_required == 0)
				{
					$turns_required = 1;
				}
				$linkback = true;

				if($shipdevice['dev_fuelscoop']['amount'] == 1)
				{
					if((NUM_ENERGY($shipinfo['power']) - $shipinfo['energy']) < $distance * 10)
					{
						$energy_collected = max(NUM_ENERGY($shipinfo['power']) - $shipinfo['energy'],0);
					}
					else
					{
						$energy_collected = $distance * 10;
					}
				}
			}
			$result->close();
		}
		else
		{
			include ("header.php");
			$move_failed = 1;
			$template_object->assign("error_msg", "DB Failure");
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."movedie.tpl");
			include ("footer.php");
			die();
		}

		break;

	case "warp":
		$result = $db->Execute("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($destination));
		$destination = $result->fields['sector_id'];

		if($destination != $shipinfo['sector_id'])
		{
			$result = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start='$shipinfo[sector_id]' AND link_dest=" . $db->qstr($destination));
			if($result)
			{
				if($result->RecordCount() == 0)
				{
					include ("header.php");
					$move_failed = 1;
					$template_object->assign("error_msg", $l_warp_invalid);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."movedie.tpl");
					include ("footer.php");
					die();
				}
				else
				{
					$turns_required = 1;

					$linkback = $db->Execute ("SELECT * FROM {$db_prefix}links WHERE link_start=" . $db->qstr($destination) . " AND link_dest'$shipinfo[sector_id]'");
					if($linkback) {
						if($linkback->recordCount() > 0)
							$linkback = true;
						else
							$linkback = false;
					}
					else
						$linkback = false;
				}
				$result->close();
			}
			else
			{
				include ("header.php");
				$move_failed = 1;
				$template_object->assign("error_msg", "DB Failure");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."movedie.tpl");
				include ("footer.php");
				die();
			}
		}
		else
		{
			$turns_required = 0;
		}

		break;

	default:
		include ("header.php");
		$move_failed = 1;
		$template_object->assign("error_msg", $l_move_unknown . ": " . $move_method);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."movedie.tpl");
		include ("footer.php");
		die();
		break;
}

// Check to see if the player has less than one turn available
// and if so return to the main menu
if($turns_required > $playerinfo['turns'])
{
	include ("header.php");
	$l_rs_movetime=str_replace("[triptime]",NUMBER($turns_required),$l_rs_movetime);
	$template_object->assign("error_msg", $l_rs_movetime);
	$template_object->assign("error_msg2", $l_rs_noturns);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."move.tpl");
	include ("footer.php");
	die();
}

if(isset($explore))
{
	include ("header.php");
	$move_failed = 1;
	$l_rs_movetime=str_replace("[triptime]",NUMBER($turns_required),$l_rs_movetime);
	$l_rs_energy=str_replace("[energy]",NUMBER($energy_collected),$l_rs_energy);
	$l_rs_engage_link= "<A HREF=\"main.php?move_method=real&engage=1&destination=" . $destination_name . "\">" . $l_rs_engage_link . "</A>";
	$l_rs_engage=str_replace("[turns]",NUMBER($playerinfo['turns']),$l_rs_engage);
	$l_rs_engage=str_replace("[engage]",$l_rs_engage_link,$l_rs_engage);
	$template_object->assign("error_msg", "$l_rs_movetime $l_rs_energy");
	$template_object->assign("error_msg2", $l_rs_engage);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."move.tpl");
	include ("footer.php");
	die();
}


?>
