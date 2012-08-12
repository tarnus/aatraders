<?php
get_post_ifset("amount");

$amount = StripNonNum($amount);
if (($amount * 1) != $amount)
	igb_error($l_igb_invalidamount, "igb.php?command=loans");

if ($amount == 0)
	igb_error($l_igb_invalidamount, "igb.php?command=loans");

if ($account['loan'] == 0)
	igb_error($l_igb_notrepay, "igb.php?command=loans");

if ($amount > $account['loan'])
	$amount = $account['loan'];

if ($amount > $playerinfo['credits'])
	igb_error($l_igb_notenoughrepay, "igb.php?command=loans");

$playerinfo['credits']-=$amount;
$account['loan']-=$amount;

$template_object->assign("l_igb_payloan", $l_igb_payloan);
$template_object->assign("l_igb_loanthanks", $l_igb_loanthanks);
$template_object->assign("l_igb_shipaccount", $l_igb_shipaccount);
$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
$template_object->assign("l_igb_payloan", $l_igb_payloan);
$template_object->assign("amount", NUMBER($amount));
$template_object->assign("l_igb_currentloan", $l_igb_currentloan);
$template_object->assign("accountloan", NUMBER($account['loan']));
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET loan=loan-$amount WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$amount WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_repay.tpl");
?>