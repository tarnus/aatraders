<?php
// 2: Bounties
// This tool will allow editing of any bounties placed in the game.

include ("languages/$langdir/lang_ports.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("globals/gen_score.inc");
include ("globals/insert_news.inc");

get_post_ifset("response, bounty_on, bid, amount");

$template_object->assign("menu", "Editor_Bounties");
$template_object->assign("md5admin_password", md5($admin_password));
$template_object->assign("game_number", $game_number);

if($response == "cancel")
{
	$res5 = $db->Execute("SELECT * FROM {$db_prefix}bounty WHERE bounty_id = $bid");
	db_op_result($res5,__LINE__,__FILE__);					
	$placed_by = $res5->fields['placed_by'];
	$refund = $res5->fields['amount'];
	$bounty_on = $res5->fields['bounty_on'];
	$del = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bid");
	$stamp = date("Y-m-d H:i:s");
	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp', credits=credits+$refund where player_id=$placed_by");
	db_op_result($debug_query,__LINE__,__FILE__);
}

if($response == "display" || $response == "cancel")
{
	$template_object->assign("bounty_on", $bounty_on);
	$res5 = $db->Execute("SELECT * FROM {$db_prefix}players,{$db_prefix}bounty WHERE bounty_on = player_id AND bounty_on = $bounty_on");
	db_op_result($res5,__LINE__,__FILE__);					
	$j = 0;
	if ($res5)
	{
		while (!$res5->EOF)
		{
			$bounty_details[$j] = $res5->fields;
			$j++;
			$res5->MoveNext();
		}
	}

	$num_details = $j;
	if ($num_details > 0)
	{
		$playername = $bounty_details[0]['character_name'];
		for ($j=0; $j<$num_details; $j++)
		{
			$someres = $db->SelectLimit("SELECT character_name, fed_bounty_count, alliance_bounty_count FROM {$db_prefix}players WHERE player_id = " . $bounty_details[$j]['placed_by'], 1);
			db_op_result($someres,__LINE__,__FILE__);					
			$details = $someres->fields;
			$someres2 = $db->SelectLimit("SELECT character_name, fed_bounty_count, alliance_bounty_count FROM {$db_prefix}players WHERE player_id = " . $bounty_details[$j]['bounty_on'], 1);
			db_op_result($someres2,__LINE__,__FILE__);					
			$moredetails = $someres2->fields;
			$bountyamount[$j] = number($bounty_details[$j]['amount']);
			$bountyby[$j] = $bounty_details[$j]['placed_by'];
			if ($bounty_details[$j]['placed_by'] == 3 || $bounty_details[$j]['placed_by'] == 1)
			{
				if ($fed_bounty_count <= $moredetails['fed_bounty_count'] && $bounty_details[$j]['placed_by'] == 3)
					$bountydetails[$j] = $moredetails['fed_bounty_count'];
				if ($fed_bounty_count <= $moredetails['alliance_bounty_count'] && $bounty_details[$j]['placed_by'] == 1)
					$bountydetails[$j] = $moredetails['alliance_bounty_count'];
			}
			else
			{
				$bountydetails[$j] = $details['character_name'];
			}

			$bountyid[$j] = $bounty_details[$j]['bounty_id'];
		}

		$template_object->assign("l_none", $l_none);
		$template_object->assign("bountyid", $bountyid);
		$template_object->assign("l_by_cancel", $l_by_cancel);
		$template_object->assign("playername", $playername);
		$template_object->assign("playerid", $playerinfo['player_id']);
		$template_object->assign("bountydetails", $bountydetails);
		$template_object->assign("fed_bounty_count", $fed_bounty_count);
		$template_object->assign("alliance_bounty_count", $alliance_bounty_count);
		$template_object->assign("l_by_fedcollectonly", $l_by_fedcollectonly);
		$template_object->assign("l_by_thefeds", $l_by_thefeds);
		$template_object->assign("bountyby", $bountyby);
		$template_object->assign("bountyamount", $bountyamount);
		$template_object->assign("num_details", $num_details);
		$template_object->assign("l_by_action", $l_by_action);
		$template_object->assign("l_by_nobounties", $l_by_nobounties);
		$template_object->assign("l_by_placedby", $l_by_placedby);
		$template_object->assign("l_by_amount", $l_by_amount);
		$template_object->assign("l_amount", $l_amount);
		$template_object->assign("l_by_bountyon", $l_by_bountyon);
		$template_object->assign("gotobounty", $l_gotobounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display("admin/bountydisplay.tpl");
	}
}

$debug_query = $db->Execute("SELECT * FROM {$db_prefix}players " .
							"WHERE destroyed='N' ORDER BY character_name ASC");
db_op_result($debug_query,__LINE__,__FILE__);

$playerlist = 0;
while (!$debug_query->EOF)
{
	if (isset($bounty_on) && $bounty_on == $debug_query->fields['player_id'])
	{
		$selected = "selected";
	}
	else
	{
		$selected = "";
	}

	$charname = $debug_query->fields['character_name'];
	$player_id = $debug_query->fields['player_id'];
	$playerid[$playerlist] = $player_id;
	$playerselect[$playerlist] = $selected;
	$playernamelist[$playerlist] = $charname;
	$playerlist++;
	$debug_query->MoveNext();
}

$result3 = $db->Execute ("SELECT bounty_on, SUM(amount) as total_bounty FROM {$db_prefix}bounty GROUP BY bounty_on");
db_op_result($result3,__LINE__,__FILE__);					

$i = 0;
if ($result3)
{
	while (!$result3->EOF)
	{
		$bounties[$i] = $result3->fields;
		$i++;
		$result3->MoveNext();
	}
}

$num_bounties = $i;
if ($num_bounties > 0)
{
	for ($i=0; $i<$num_bounties; $i++)
	{
		$someres = $db->execute("SELECT character_name FROM {$db_prefix}players WHERE player_id = " . $bounties[$i]['bounty_on']);
		db_op_result($someres,__LINE__,__FILE__);					
		$details = $someres->fields;
		$bountyon[$i] = $bounties[$i]['bounty_on'];
		$bountyname[$i] = $details['character_name'];
		$bountyamount[$i] = number($bounties[$i]['total_bounty']);
	}
}

$template_object->assign("bountyon", $bountyon);
$template_object->assign("bountyname", $bountyname);
$template_object->assign("bountyamount", $bountyamount);
$template_object->assign("num_bounties", $num_bounties);
$template_object->assign("playerid", $playerid);
$template_object->assign("playerselect", $playerselect);
$template_object->assign("playernamelist", $playernamelist);
$template_object->assign("playerlist", $playerlist);
$template_object->assign("l_amount", $l_amount);
$template_object->assign("l_by_moredetails", $l_by_moredetails);
$template_object->assign("color_header", $color_header);
$template_object->assign("l_by_nobounties", $l_by_nobounties);
$template_object->assign("l_by_place", $l_by_place);
$template_object->assign("l_by_amount", $l_by_amount);
$template_object->assign("l_by_bountyon", $l_by_bountyon);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display("admin/bountydefault.tpl");

?>
