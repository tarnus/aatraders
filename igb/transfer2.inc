<?php
get_post_ifset("player_id, shipt, splanet_id, dplanet_id");

$template_object->assign("isplayer", isset($player_id));

if (isset($player_id)) //ship transfer
{
	$res = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$player_id", 1);

	if ($playerinfo['player_id'] == $player_id)
		igb_error($l_igb_sendyourself, "igb.php?command=transfer");

	if (!$res || $res->EOF)
		igb_error($l_igb_unknowntargetship, "igb.php?command=transfer");

	$target = $res->fields;
	$res->close();

	if ($target['turns_used'] < $igb_min_turns)
	{
		$l_igb_min_turns = str_replace("[igb_min_turns]", $igb_min_turns, $l_igb_min_turns);
		$l_igb_min_turns = str_replace("[igb_target_char_name]", $target['character_name'], $l_igb_min_turns);
		igb_error($l_igb_min_turns, "igb.php?command=transfer");
	}

	if ($playerinfo['turns_used'] < $igb_min_turns)
	{
		$l_igb_min_turns2 = str_replace("[igb_min_turns]", $igb_min_turns, $l_igb_min_turns2);
		igb_error($l_igb_min_turns2, "igb.php?command=transfer");
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
			$l_igb_mustwait = str_replace("[igb_target_char_name]", $target['character_name'], $l_igb_mustwait);
			$l_igb_mustwait = str_replace("[igb_trate]", NUMBER($igb_trate), $l_igb_mustwait);
			$l_igb_mustwait = str_replace("[igb_difftime]", NUMBER($difftime), $l_igb_mustwait);
			igb_error($l_igb_mustwait, "igb.php?command=transfer");
		}
		$res->close();
	}

	$template_object->assign("l_igb_shiptransfer", $l_igb_shiptransfer);
	$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
	$template_object->assign("accountbalance", NUMBER($account['balance']));
	$template_object->assign("igb_svalue", $igb_svalue);

	if ($igb_svalue == 0){
		$template_object->assign("l_igb_maxtransfer", $l_igb_maxtransfer);
		$template_object->assign("l_igb_unlimited", $l_igb_unlimited);
	}
	else
	{
		$percent = $igb_svalue * 100;
		$returnscore = gen_score($playerinfo['player_id']);
		$score = $returnscore[0];
		$maxtrans = $score * $score * $igb_svalue;

		$l_igb_maxtransferpercent = str_replace("[igb_percent]", $percent, $l_igb_maxtransferpercent);
		$template_object->assign("l_igb_maxtransferpercent", $l_igb_maxtransferpercent);
		$template_object->assign("maxtrans", NUMBER($maxtrans));
	}

	$percent = $ibank_paymentfee * 100;

	$l_igb_transferrate = str_replace("[igb_num_percent]", NUMBER($percent,1), $l_igb_transferrate);

	$template_object->assign("l_igb_recipient", $l_igb_recipient);
	$template_object->assign("targetname", $target['character_name']);
	$template_object->assign("l_igb_seltransferamount", $l_igb_seltransferamount);
	$template_object->assign("l_igb_transfer", $l_igb_transfer);
	$template_object->assign("player_id", $player_id);
	$template_object->assign("l_igb_transferrate", $l_igb_transferrate);
	$template_object->assign("l_igb_back", $l_igb_back);
	$template_object->assign("l_igb_logout", $l_igb_logout);
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

	$res = $db->SelectLimit("SELECT pl.name, pl.max_credits, pl.credits, pl.owner, pl.sector_id, pl.base, un.sector_name, un.zone_id, un.sg_sector FROM {$db_prefix}planets as pl, {$db_prefix}universe as un WHERE pl.planet_id=$dplanet_id and un.sector_id=pl.sector_id", 1);
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
	if ($dest['base'] == 'N')
		igb_error($l_igb_errnobase, "igb.php?command=transfer");

	if ($source['owner'] != $playerinfo['player_id'] || $dest['owner'] != $playerinfo['player_id'])
		igb_error($l_igb_errnotyourplanet, "igb.php?command=transfer");

	$percent = $ibank_paymentfee * 100;

	$l_igb_transferrate2 = str_replace("[igb_num_percent]", NUMBER($percent,1), $l_igb_transferrate2);
	$template_object->assign("l_igb_planettransfer", $l_igb_planettransfer);
	$template_object->assign("l_igb_srcplanet", $l_igb_srcplanet);
	$template_object->assign("sourcename", $source['name']);
	$template_object->assign("l_igb_in", $l_igb_in);
	$template_object->assign("sourcesector", $source['sector_name']);
	$template_object->assign("sourcecredits", NUMBER($source['credits']));
	$template_object->assign("l_igb_destplanet", $l_igb_destplanet);
	$template_object->assign("destname", $dest['name']);
	$template_object->assign("destsector", $dest['sector_name']);
	$template_object->assign("destcredits", NUMBER($dest['credits']));
	$template_object->assign("l_igb_seltransferamount", $l_igb_seltransferamount);
	$template_object->assign("l_igb_transfer", $l_igb_transfer);
	$template_object->assign("splanet_id", $splanet_id);
	$template_object->assign("dplanet_id", $dplanet_id);
	$template_object->assign("l_igb_transferrate2", $l_igb_transferrate2);
	$template_object->assign("l_igb_maxtransfer", $l_igb_maxtransfer);
	$template_object->assign("transfercredits", (NUMBER($dest['max_credits'] - $dest['credits'])));
	$template_object->assign("l_igb_back", $l_igb_back);
	$template_object->assign("l_igb_logout", $l_igb_logout);
}

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_transfer2.tpl");
?>