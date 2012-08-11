<?php
get_post_ifset("amount, player_id, splanet_id, dplanet_id");

$amount = StripNonNum($amount);

if ($amount < 0)
	$amount = 0;

$template_object->assign("isplayer", isset($player_id));

if (isset($player_id)) //ship transfer
{
	//Need to check again to prevent cheating by manual posts

	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$player_id", 1);

	if ($playerinfo['player_id'] == $player_id)
		igb_error($l_igb_errsendyourself, "igb.php?command=transfer");

	if (!$res || $res->EOF)
		igb_error($l_igb_unknowntargetship, "igb.php?command=transfer");

	$target = $res->fields;
	$res->close();

	if ($target['turns_used'] < $igb_min_turns)
	{
		$l_igb_min_turns3 = str_replace("[igb_min_turns]", $igb_min_turns, $l_igb_min_turns3);
		$l_igb_min_turns3 = str_replace("[igb_target_char_name]", $target[character_name], $l_igb_min_turns3);
		igb_error($l_igb_min_turns3, "igb.php?command=transfer");
	}

	if ($playerinfo['turns_used'] < $igb_min_turns)
	{
		$l_igb_min_turns4 = str_replace("[igb_min_turns]", $igb_min_turns, $l_igb_min_turns4);
		igb_error($l_igb_min_turns4, "igb.php?command=transfer");
	}

	if ($igb_trate > 0)
	{
		$curtime = time();
		$curtime -= $igb_trate * 60;
		$res = $db->Execute("SELECT UNIX_TIMESTAMP(time) as time FROM {$db_prefix}igb_transfers WHERE UNIX_TIMESTAMP(time) > $curtime AND source_id=$playerinfo[player_id] AND dest_id=$target[player_id]");
		if (!$res->EOF)
		{
			$time = $res->fields;
			$difftime = ($time['time'] - $curtime) / 60;
			$l_igb_mustwait2 = str_replace("[igb_target_char_name]", $target['character_name'], $l_igb_mustwait2);
			$l_igb_mustwait2 = str_replace("[igb_trate]", NUMBER($igb_trate), $l_igb_mustwait2);
			$l_igb_mustwait2 = str_replace("[igb_difftime]", NUMBER($difftime), $l_igb_mustwait2);
			igb_error($l_igb_mustwait2, "igb.php?command=transfer");
		}
		$res->close();
	}


	if (($amount * 1) != $amount)
		igb_error($l_igb_invalidtransferinput, "igb.php?command=transfer");

	if ($amount == 0)
		igb_error($l_igb_nozeroamount, "igb.php?command=transfer");

	if ($amount > $account['balance'])
		igb_error($l_igb_notenoughcredits, "igb.php?command=transfer");

	$result = $db->SelectLimit("SELECT balance FROM {$db_prefix}ibank_accounts WHERE player_id=$target[player_id]", 1);
	$targetaccount = $result->fields;
	if ($targetaccount['balance'] + $amount > $max_igb_storage and $max_igb_storage != 0)
		igb_error($l_igb_invalidtransferinput, "igb.php?command=transfer");

	if ($igb_svalue != 0)
	{
		$percent = $igb_svalue * 100;
		$returnscore = gen_score($playerinfo['player_id']);
		$score = $returnscore[1];
		$maxtrans = $score * $score * $igb_svalue;

		if ($amount > $maxtrans)
			igb_error($l_igb_amounttoogreat, "igb.php?command=transfer");
	}

	$account['balance'] -= $amount;
	$amount2 = $amount * $ibank_paymentfee;
	$transfer = $amount - $amount2;

	$template_object->assign("l_igb_transfersuccessful", $l_igb_transfersuccessful);
	$template_object->assign("transfer", NUMBER($transfer));
	$template_object->assign("l_igb_creditsto", $l_igb_creditsto);
	$template_object->assign("targetname", $target['character_name']);
	$template_object->assign("l_igb_transferamount", $l_igb_transferamount);
	$template_object->assign("amount", NUMBER($amount));
	$template_object->assign("l_igb_transferfee", $l_igb_transferfee);
	$template_object->assign("amount2", NUMBER($amount2));
	$template_object->assign("l_igb_amounttransferred", $l_igb_amounttransferred);
	$template_object->assign("transfer", NUMBER($transfer));
	$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
	$template_object->assign("accountbalance", NUMBER($account['balance']));
	$template_object->assign("l_igb_back", $l_igb_back);
	$template_object->assign("l_igb_logout", $l_igb_logout);

	$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET loantime=loantime,balance=balance-$amount WHERE player_id=$playerinfo[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}ibank_accounts SET loantime=loantime,balance=balance+$transfer WHERE player_id=$target[player_id]");
	db_op_result($debug_query,__LINE__,__FILE__);

	$stamp = date("Y-m-d H:i:s");
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}igb_transfers VALUES('', $playerinfo[player_id], $target[player_id], '$stamp')");
	db_op_result($debug_query,__LINE__,__FILE__);

	$temp = NUMBER($transfer);
	playerlog($target['player_id'], "LOG0_IGB_TRANSFER1", "$playerinfo[character_name]|$temp");
	playerlog($playerinfo['player_id'], "LOG0_IGB_TRANSFER2", "$target[character_name]|$temp");
}
else
{
	if ($splanet_id == $dplanet_id)
		igb_error($l_igb_errplanetsrcanddest, "igb.php?command=transfer");

	$res = $db->Execute("SELECT pl.name, pl.planet_id, pl.sector_id, un.sector_name, un.zone_id, un.sg_sector FROM {$db_prefix}planets as pl, {$db_prefix}universe as un WHERE pl.owner=$playerinfo[player_id] and un.sector_id=pl.sector_id ORDER BY pl.sector_id ASC");
	$i = 0;
	while (!$res->EOF)
	{
		$planets=$res->fields;
		if($planets['sg_sector'] == 0)
		{
			$planet_sg_zone[$planets['sector_id']] = $planets['zone_id'];
		}
		else
		{
			if(!isset($planet_sg_zone[$planets['sg_sector']]))
			{
				$query = "SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=" . $planets['sg_sector'];
				$getzone = $db->SelectLimit($query, 1);
				$planet_sg_zone[$planets['sg_sector']] = $getzone->fields['zone_id'];
			}
		}
		$i++;
		$res->MoveNext();
	}
	$res->close();

	$res = $db->SelectLimit("SELECT pl.name, pl.credits, pl.owner, pl.sector_id, un.sector_name, un.zone_id, un.sg_sector FROM {$db_prefix}planets as pl, {$db_prefix}universe as un WHERE pl.planet_id=$splanet_id and un.sector_id=pl.sector_id", 1);
	if (!$res || $res->EOF)
		igb_error($l_igb_errunknownplanet, "igb.php?command=transfer");
	$source = $res->fields;
	$res->close();

	$planetzone_id = ($source['sg_sector'] == 0) ? $source['zone_id'] : $planet_sg_zone[$source['sg_sector']];
	if($planetzone_id == 4 && $source['sg_sector'] != 0)
	{
		$l_igb_errblockadedplanet = str_replace("[planet]", $source['name'], $l_igb_errblockadedplanet);
		igb_error($l_igb_errblockadedplanet, "igb.php?command=transfer");
	}

	if (empty($source['name']))
		$source['name']=$l_igb_unnamed;

	$res = $db->SelectLimit("SELECT pl.name, pl.credits, pl.owner, pl.sector_id, pl.max_credits, un.sector_name, un.zone_id, un.sg_sector FROM {$db_prefix}planets as pl, {$db_prefix}universe as un WHERE pl.planet_id=$dplanet_id and un.sector_id=pl.sector_id", 1);
	if (!$res || $res->EOF)
		igb_error($l_igb_errunknownplanet, "igb.php?command=transfer");
	$dest = $res->fields;
	$res->close();

	$planetzone_id = ($dest['sg_sector'] == 0) ? $dest['zone_id'] : $planet_sg_zone[$dest['sg_sector']];
	if($planetzone_id == 4 && $dest['sg_sector'] != 0)
	{
		$l_igb_errblockadedplanet = str_replace("[planet]", $dest['name'], $l_igb_errblockadedplanet);
		igb_error($l_igb_errblockadedplanet, "igb.php?command=transfer");
	}

	if (empty($dest['name']))
		$dest['name']=$l_igb_unnamed;

	if ($source['owner'] != $playerinfo['player_id'] || $dest['owner'] != $playerinfo['player_id'])
		igb_error($l_igb_errnotyourplanet, "igb.php?command=transfer");

	if ($amount > $source['credits'])
		igb_error($l_igb_notenoughcredits2, "igb.php?command=transfer");

	$percent = $ibank_paymentfee * 100;

	if($dest['credits'] + $amount > $dest['max_credits']){
		$amount = $dest['max_credits'] - $dest['credits'];
	}

	if($amount < 0)
		$amount = 0;

	$source['credits'] -= $amount;
	$amount2 = $amount * $ibank_paymentfee;
	$transfer = $amount - $amount2;
	$dest['credits'] += $transfer;

	$template_object->assign("l_igb_transfersuccessful", $l_igb_transfersuccessful);
	$template_object->assign("transfer", NUMBER($transfer));
	$template_object->assign("l_igb_ctransferredfrom", $l_igb_ctransferredfrom);
	$template_object->assign("sourcename", $source['name']);
	$template_object->assign("l_igb_to", $l_igb_to);
	$template_object->assign("destname", $dest['name']);
	$template_object->assign("l_igb_transferamount", $l_igb_transferamount);
	$template_object->assign("amount", NUMBER($amount));
	$template_object->assign("l_igb_transferfee", $l_igb_transferfee);
	$template_object->assign("amount2", NUMBER($amount2));
	$template_object->assign("l_igb_amounttransferred", $l_igb_amounttransferred);
	$template_object->assign("transfer", NUMBER($transfer));
	$template_object->assign("l_igb_srcplanet", $l_igb_srcplanet);
	$template_object->assign("sourcename", $source['name']);
	$template_object->assign("l_igb_in", $l_igb_in);
	$template_object->assign("sourcesector", $source['sector_name']);
	$template_object->assign("sourcecredits", NUMBER($source['credits']));
	$template_object->assign("l_igb_destplanet", $l_igb_destplanet);
	$template_object->assign("destname", $dest['name']);
	$template_object->assign("destsector", $dest['sector_name']);
	$template_object->assign("destcredits", NUMBER($dest['credits']));
	$template_object->assign("l_igb_back", $l_igb_back);
	$template_object->assign("l_igb_logout", $l_igb_logout);

	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET credits=credits-$amount WHERE planet_id=$splanet_id");
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET credits=credits+$transfer WHERE planet_id=$dplanet_id");
	db_op_result($debug_query,__LINE__,__FILE__);
}

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_transfer3.tpl");
?>