<?php
get_post_ifset("amount");

$amount = StripNonNum($amount);
if (($amount * 1) != $amount)
	igb_error($l_igb_invalidamount, "igb.php?command=loans");

if ($amount <= 0)
	igb_error($l_igb_invalidamount, "igb.php?command=loans");

if ($account['loan'] != 0)
	igb_error($l_igb_notwoloans, "igb.php?command=loans");

$returnscore = gen_score($playerinfo['player_id']);
$score = $returnscore[0];
$maxtrans = $score * $score * $ibank_loanlimit;

if ($amount > $maxtrans)
	igb_error($l_igb_loantoobig, "igb.php?command=loans");

$amount2 = $amount * $ibank_loanfactor;
$amount3= $amount + $amount2;

$hours = $igb_lrate / 60;
$mins = $igb_lrate % 60;

$l_igb_loanreminder = str_replace("[hours]", $hours, $l_igb_loanreminder);
$l_igb_loanreminder = str_replace("[mins]", $mins, $l_igb_loanreminder);

$template_object->assign("l_igb_takenaloan", $l_igb_takenaloan);
$template_object->assign("l_igb_loancongrats", $l_igb_loancongrats);
$template_object->assign("l_igb_loantransferred", $l_igb_loantransferred);
$template_object->assign("amount", NUMBER($amount));
$template_object->assign("l_igb_loanfee", $l_igb_loanfee);
$template_object->assign("amount2", NUMBER($amount2));
$template_object->assign("l_igb_amountowned", $l_igb_amountowned);
$template_object->assign("amount3", NUMBER($amount3));
$template_object->assign("l_igb_loanreminder", $l_igb_loanreminder);
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$stamp = date("Y-m-d H:i:s");
$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET loan=$amount3, loantime='$stamp' WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits+$amount WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_borrow.tpl");
?>