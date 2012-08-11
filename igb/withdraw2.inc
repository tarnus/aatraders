<?php
get_post_ifset("amount");

$amount = StripNonNum($amount);
if (($amount * 1) != $amount)
	igb_error($l_igb_invalidwithdrawinput, "igb.php?command=withdraw");

if ($amount == 0)
	igb_error($l_igb_nozeroamount3, "igb.php?command=withdraw");

if ($amount > $account['balance'])
	igb_error($l_igb_notenoughcredits, "igb.php?command=withdraw");

$account['balance'] -= $amount;
$playerinfo['credits'] += $amount;

$template_object->assign("l_igb_operationsuccessful", $l_igb_operationsuccessful);
$template_object->assign("amount", NUMBER($amount));
$template_object->assign("l_igb_creditstoyourship", $l_igb_creditstoyourship);
$template_object->assign("l_igb_accounts", $l_igb_accounts);
$template_object->assign("l_igb_shipaccount", $l_igb_shipaccount);
$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
$template_object->assign("accountbalance", NUMBER($account['balance']));
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET loantime=loantime,balance=balance-$amount WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits+$amount WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_withdraw2.tpl");
?>