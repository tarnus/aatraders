<?php
include ("globals/isLoanPending.inc");

$l_port_welcome = str_replace("[player]", $playerinfo['character_name'], str_replace("[sectorname]", $sectorinfo['sector_name'], $l_port_welcome));
$template_object->assign("l_port_welcome", $l_port_welcome);
$template_object->assign("l_device", $l_device_ports);

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_trade_turnneed);
	$template_object->assign("error_msg2", "<A HREF=port.php>$l_clickme</A> $l_port_returntospecial");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."genericdie.tpl");
	include ("footer.php");
	die();
}

if ($sectorinfo['port_type'] == "devices")
{
	if (isLoanPending($playerinfo['player_id']))
	{
		$template_object->assign("error_msg", $l_port_loannotrade);
		$template_object->assign("error_msg2", "<A HREF=igb.php>$l_igb_term</a>");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}

	$devicename = array();
	$devicetotalcost = array();
	$device_object = array();
	$device_amount = array();

	foreach ($shipdevice as $key => $data) 
	{
		$device_type = $data['class'];
		if(!class_exists($device_type)){
			include ("class/devices/" . $device_type . ".inc");
		}
		$tempobject = new $device_type();
		$device_object[] = $tempobject;
		$devicetotalcost[] = $tempobject->get_device_totalcost();
		$devicename[] = $tempobject->classname;
		$device_amount[] = $tempobject->device_amount;
		if($tempobject->deviceport == 0 || $tempobject->device_amount == 0)
		{
			array_pop($device_object);
			array_pop($devicename);
			array_pop($devicetotalcost);
			array_pop($device_amount);
		}
	}
	$template_object->assign("devicename", $devicename);
	$template_object->assign("device_amount", $device_amount);

	$total_cost = 0;
	foreach($devicename as $key => $data)
	{
		$total_cost += $devicetotalcost[$key];
	}
	$total_cost = $total_cost * $alliancefactor;
	$template_object->assign("total_cost", NUMBER($total_cost));

	if ($total_cost > $playerinfo['credits'])
	{
		$template_object->assign("error_msg", "$l_ports_needcredits " . NUMBER($total_cost) . " $l_ports_needcredits1 " . NUMBER($playerinfo['credits']) . " $l_credits.");
		$template_object->assign("error_msg2", "<A HREF=port.php>$l_clickme</A> $l_port_returntospecial");
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		foreach($devicename as $key => $data)
		{
			$device_object[$key]->complete_purchase();
			$device_total_cost[$key] = NUMBER($devicetotalcost[$key] * $alliancefactor);
		}
		$template_object->assign("device_total_cost", $device_total_cost);
		$template_object->assign("l_trade_result", $l_trade_result);
		$template_object->assign("l_cost", $l_cost);
		$template_object->assign("l_credits", $l_credits);
		$template_object->assign("l_amount", $l_amount);

		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$total_cost,turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

$template_object->assign("l_trade_complete", $l_trade_complete);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_port_returntospecial", $l_port_returntospecial);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ports/devices_purchase.tpl");

include ("footer.php");

?>
