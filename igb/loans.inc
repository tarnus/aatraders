<?php
$template_object->assign("l_igb_loanstatus", $l_igb_loanstatus);
$template_object->assign("l_igb_shipaccount", $l_igb_shipaccount);
$template_object->assign("l_igb_currentloan", $l_igb_currentloan);
$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
$template_object->assign("accountloan", NUMBER($account['loan']));

if ($account['loan'] != 0)
{
	$curtime = time();
	$res = $db->SelectLimit("SELECT UNIX_TIMESTAMP(loantime) as time FROM {$db_prefix}ibank_accounts WHERE player_id=$playerinfo[player_id]", 1);
	if (!$res->EOF)
	{
		$time = $res->fields;
	}
	$res->close();

	$difftime = ($curtime - $time['time']) / 60;

	$template_object->assign("l_igb_loantimeleft", $l_igb_loantimeleft);
	$template_object->assign("isloanlate", ($difftime > $igb_lrate));
	$template_object->assign("l_igb_loanlate", $l_igb_loanlate);

	if ($difftime <= $igb_lrate)
	{
		$difftime=$igb_lrate - $difftime;
		$hours = $difftime / 60;
		$hours = (int) $hours;
		$mins = $difftime % 60;
		$template_object->assign("hours", $hours);
		$template_object->assign("mins", $mins);
	}

	$hours2 = $igb_lrate / 60;
	$hours2 = (int) $hours2;
	$mins2 = $igb_lrate % 60;

	$factor = $ibank_loanfactor *=100;
	$interest = $ibank_loaninterest *=100;

	$l_igb_loanrates = str_replace("[factor]", $factor, $l_igb_loanrates);
	$l_igb_loanrates = str_replace("[interest]", $interest, $l_igb_loanrates);

	$template_object->assign("l_igb_repayamount", $l_igb_repayamount);
	$template_object->assign("amount", NUMBER(MIN($playerinfo['credits'],$account['loan'])));
	$template_object->assign("l_igb_repay", $l_igb_repay);
	$template_object->assign("l_igb_loanrates", $l_igb_loanrates);
}
else
{
	$percent = $ibank_loanlimit * 100;
	$returnscore = gen_score($playerinfo['player_id']);
	$score = $returnscore[0];
	$maxloan = $score * $score * $ibank_loanlimit;

	$l_igb_maxloanpercent = str_replace("[igb_percent]", $percent, $l_igb_maxloanpercent);
	$template_object->assign("l_igb_maxloanpercent", $l_igb_maxloanpercent);
	$template_object->assign("maxloan", NUMBER($maxloan));

	$hours2 = $igb_lrate / 60;
	$hours2 = (int) $hours2;
	$mins2 = $igb_lrate % 60;

	$l_igb_loanrepaytime = str_replace("[hours]", $hours2, $l_igb_loanrepaytime);
	$l_igb_loanrepaytime = str_replace("[mins]", $mins2, $l_igb_loanrepaytime);

	$factor = $ibank_loanfactor *=100;
	$interest = $ibank_loaninterest *=100;

	$l_igb_loanrates = str_replace("[factor]", $factor, $l_igb_loanrates);
	$l_igb_loanrates = str_replace("[interest]", $interest, $l_igb_loanrates);

	$debug_query = $db->Execute("SELECT * from {$db_prefix}planets WHERE owner=$playerinfo[player_id] and base='Y'");
	db_op_result($debug_query,__LINE__,__FILE__);

	$reccount = $debug_query->RecordCount();
	$debug_query->close();

	$template_object->assign("iscollateral", ($reccount >= $ibank_collateral_level));
	$template_object->assign("l_igb_loanamount", $l_igb_loanamount);
	$template_object->assign("l_igb_borrow", $l_igb_borrow);
	$template_object->assign("l_igb_loanrates", $l_igb_loanrates);
	$template_object->assign("l_igb_loanrepaytime", $l_igb_loanrepaytime);
	$template_object->assign("l_igb_nocollateral", $l_igb_nocollateral);
}

$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_loans.tpl");
?>