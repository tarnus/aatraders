<?php
include ("globals/cleanjs.inc");
include ("globals/isLoanPending.inc");

$l_port_welcome = str_replace("[player]", $playerinfo['character_name'], str_replace("[sectorname]", $sectorinfo['sector_name'], $l_port_welcome));
$template_object->assign("l_port_welcome", $l_port_welcome);

if($zoneinfo['zone_id'] != 3)
{
    /*  Commented out for fed changes 4-13-2010
	$res2 = $db->Execute("SELECT SUM(amount) as total_bounty FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1) AND bounty_on = $playerinfo[player_id]");
	db_op_result($res2,__LINE__,__FILE__);
	if ($res2)
	{
		$bty = $res2->fields;
		if ($bty['total_bounty'] > 0)
		{
			if ($pay < 1)
			{
				$l_port_bounty2 = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_bounty2);
				$l_port_bounty2 .= "<br><A HREF=\"bounty.php\">$l_by_placebounty</A><BR><BR>";
				$template_object->assign("error_msg", $l_port_bounty);
				$template_object->assign("error_msg2", $l_port_bounty2);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}
			elseif($pay==2)
			{
			// Make bounty payments
				$getbountyid = $db->Execute("SELECT * FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1)  and bounty_on=$playerinfo[player_id] order by bounty_id ");
				db_op_result($getbountyid,__LINE__,__FILE__);
				$pmt_amt=StripNonNum($pmt_amt);
				if (($pmt_amt=="") or ($pmt_amt <= 0))
				{
					$pmt_amt=0;
				}
				if ($pmt_amt > $playerinfo['credits'])
				{
					$pmt_amt=$playerinfo['credits'];
				}
				$temptotal=$pmt_amt;
				if ($getbountyid->RecordCount() > 0)
				{
					while (!$getbountyid->EOF)
					{
						$bounty = $getbountyid->fields;
						if ($bounty['amount']<= $temptotal)
						{
							$bountyupdate = $db->Execute("delete from  {$db_prefix}bounty  where bounty_id=$bounty[bounty_id]");
							db_op_result($bountyupdate,__LINE__,__FILE__);
							$temptotal=$temptotal-$bounty['amount'];
						}else{
							$bountyupdate = $db->Execute("update {$db_prefix}bounty set amount=amount-$temptotal where bounty_id=$bounty[bounty_id]");
							db_op_result($bountyupdate,__LINE__,__FILE__);
							$temptotal=0;
						}
						$getbountyid->MoveNext();	
					}
				}
				$getbountyid->close();
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$pmt_amt WHERE player_id = $playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				$template_object->assign("error_msg", $l_port_bountypaid);
				$template_object->assign("error_msg2", "");
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				if ($playerinfo['credits'] < $bty['total_bounty'])
				{
					$l_port_btynotenough = str_replace("[amount]",NUMBER($bty['total_bounty']),$l_port_btynotenough);
					$l_creds_to_spend=str_replace("[credits]",NUMBER($playerinfo['credits']),$l_creds_to_spend);
					$template_object->assign("notenough", $l_port_btynotenough);
					$template_object->assign("l_pay_partial", $l_pay_partial);
					$template_object->assign("l_creds_to_spend", $l_creds_to_spend);
					$template_object->assign("l_pay_button", $l_pay_button);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."bountypay.tpl");
					include ("footer.php");
					die();
				}
				else
				{
					$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$bty[total_bounty] WHERE player_id = $playerinfo[player_id]");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query = $db->Execute("DELETE from {$db_prefix}bounty WHERE bounty_on = $playerinfo[player_id] AND (placed_by = 3 or placed_by = 1)");
					db_op_result($debug_query,__LINE__,__FILE__);
					$template_object->assign("error_msg", $l_port_bountypaid);
					$template_object->assign("error_msg2", "");
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genericdie.tpl");
					include ("footer.php");
					die();
				}
			}
		}
	}
	$res2->close();
    */
	$alliancefactor = 1;
}
/*  Commented out for fed changes 4-13-2010
else
{
	$res2 = $db->Execute("SELECT COUNT(*) as number_of_bounties FROM {$db_prefix}bounty WHERE (placed_by = 3 or placed_by = 1) AND bounty_on = $playerinfo[player_id]");
	db_op_result($res2,__LINE__,__FILE__);
	if ($res2)
	{
		$alliancefactor = $alliancefactor * max($res2->fields['number_of_bounties'], 1);
	}
	$res2->close();
}

*/
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
$deviceamount = array();
$device_form_name = array();
$deviceprice = array();
$devicemaximum = array();
$deviceclass = array();
$device_java_countTotal = array();
$device_java2_countTotal = array();
$device_java_function = array();
$device_free = array();
$device_input = array();

foreach ($shipdevice as $key => $data) 
{
	$device_type = $data['class'];
	$deviceclass[] = $data['class'];
	if(!class_exists($device_type)){
		include ("class/devices/" . $device_type . ".inc");
	}
	$tempobject = new $device_type();
	$tempobject->ship_amount = $data['amount'];
	$deviceprice[] = NUMBER($tempobject->price * $alliancefactor);
	$devicemaximum[] = $tempobject->shipdevicemax;
	$devicename[] = $tempobject->classname;
	$device_form_name[] = $tempobject->form_name;
	$device_java_countTotal[] = $tempobject->get_device_java_countTotal($alliancefactor);
	$device_java2_countTotal[] = $tempobject->get_device_java2_countTotal();
	$device_java_function[] = $tempobject->get_device_java_function($alliancefactor);
	$device_free[] = $tempobject->device_free;
	$deviceamount[] = NUMBER($tempobject->ship_amount);

	$device_input[] = $tempobject->get_device_input();
	if($tempobject->deviceport == 0)
	{
		array_pop($devicename);
		array_pop($deviceamount);
		array_pop($device_form_name);
		array_pop($deviceprice);
		array_pop($devicemaximum);
		array_pop($deviceclass);
		array_pop($device_java_countTotal);
		array_pop($device_java2_countTotal);
		array_pop($device_java_function);
		array_pop($device_free);
		array_pop($device_input);
	}
}
$template_object->assign("devicename", $devicename);
$template_object->assign("deviceamount", $deviceamount);
$template_object->assign("deviceprice", $deviceprice);
$template_object->assign("devicemaximum", $devicemaximum);
$template_object->assign("device_form_name", $device_form_name);
$template_object->assign("deviceclass", $deviceclass);
$template_object->assign("device_java_countTotal", $device_java_countTotal);
$template_object->assign("device_java2_countTotal", $device_java2_countTotal);
$template_object->assign("device_java_function", $device_java_function);
$template_object->assign("device_free", $device_free);
$template_object->assign("device_input", $device_input);

cleanjs('');
$template_object->assign("cleanjs", $cleanjs);
$template_object->assign("alliancefactor", $alliancefactor);
$template_object->assign("l_device", $l_device);

$onblur = "ONBLUR=\"countTotal();\"";
$onfocus =	"ONFOCUS=\"countTotal();\"";
$onchange =	"ONCHANGE=\"countTotal();\"";
$onclick =	"ONCLICK=\"countTotal();\"";
$template_object->assign("onblur", $onblur);
$template_object->assign("onfocus", $onfocus);
$template_object->assign("onchange", $onchange);
$template_object->assign("onclick", $onclick);

$template_object->assign("l_device", $l_device);
$template_object->assign("l_cost", $l_cost);
$template_object->assign("l_current", $l_current);
$template_object->assign("l_max", $l_max);
$template_object->assign("l_qty", $l_qty);
$template_object->assign("l_no_credits", $l_no_credits);

$template_object->assign("l_unlimited", $l_unlimited);

$template_object->assign("enable_dignitaries", $enable_dignitaries);
$template_object->assign("zone_id", $zoneinfo['zone_id']);
$template_object->assign("shipinfo", $shipinfo);
$template_object->assign("playerinfo", $playerinfo);
$template_object->assign("l_none", $l_none);
$template_object->assign("l_level", $l_level);
$template_object->assign("l_n_a", $l_n_a);
$template_object->assign("l_equipped", $l_equipped);
$template_object->assign("l_totalcost", $l_totalcost);
$template_object->assign("l_spy_cleanupship", $l_spy_cleanupship);
$template_object->assign("l_here", $l_here);
$template_object->assign("l_buy", $l_buy);
$template_object->assign("alliancefactor", $alliancefactor);
$template_object->assign("upgrade_cost", $upgrade_cost);
$template_object->assign("upgrade_factor", $upgrade_factor);

$l_creds_to_spend=str_replace("[credits]",NUMBER($playerinfo['credits']),$l_creds_to_spend);
$template_object->assign("l_creds_to_spend", $l_creds_to_spend);
$template_object->assign("allow_ibank", $allow_ibank);

if ($allow_ibank)
{
	$igblink = "\n<A HREF=igb.php>$l_igb_term</a>";
	$l_ifyouneedmore=str_replace("[igb]",$igblink,$l_ifyouneedmore);
	$template_object->assign("l_ifyouneedmore", $l_ifyouneedmore);
}

$template_object->assign("enable_spies", $enable_spies);
$template_object->assign("l_spy_cleanupship", $l_spy_cleanupship);
$template_object->assign("l_here", $l_here);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_port_returntospecial", $l_port_returntospecial);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."ports/devices_view.tpl");

include ("footer.php");

?>
