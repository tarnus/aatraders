<?php
get_post_ifset("amount");

$amount = StripNonNum($amount);
if (($amount * 1) != $amount)
	igb_error($l_igb_invaliddepositinput, "igb.php?command=deposit");

if ($amount == 0)
	igb_error($l_igb_nozeroamount2, "igb.php?command=deposit");

if ($amount > $playerinfo['credits'])
	igb_error($l_igb_notenoughcredits, "igb.php?command=deposit");

if ($account['balance'] + $amount > $max_igb_storage and $max_igb_storage != 0)
	igb_error($l_igb_invaliddepositinput, "igb.php?command=deposit");

$account['balance'] += $amount;
$playerinfo['credits'] -= $amount;

$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET loantime=loantime,balance=$account[balance] WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=$playerinfo[credits] WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);


$template_object->assign("l_igb_operationsuccessful", $l_igb_operationsuccessful);
$template_object->assign("amount", NUMBER($amount));
$template_object->assign("l_igb_creditstoyou", $l_igb_creditstoyou);
$template_object->assign("l_igb_accounts", $l_igb_accounts);
$template_object->assign("l_igb_shipaccount", $l_igb_shipaccount);
$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
$template_object->assign("accountbalance", NUMBER($account['balance']));
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_deposit2.tpl");
?>