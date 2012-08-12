<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: bounty.php

include ("config/config.php");
include ("languages/$langdir/lang_ports.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("globals/gen_score.inc");
include ("globals/insert_news.inc");

get_post_ifset("response, bounty_on, bid, amount");

$title = $l_by_title;

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

if ((!isset($response)) || ($response == ''))
{
	$response = '';
}
//-------------------------------------------------------------------------------------------------


switch ($response) 
{
	case "display":
		$res5 = $db->Execute("SELECT * FROM {$db_prefix}players,{$db_prefix}bounty WHERE bounty_on = player_id AND bounty_on = $bounty_on");
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
				$details = $someres->fields;
				$someres2 = $db->SelectLimit("SELECT character_name, fed_bounty_count, alliance_bounty_count FROM {$db_prefix}players WHERE player_id = " . $bounty_details[$j]['bounty_on'], 1);
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
				if ($bounty_details[$j]['placed_by'] == $playerinfo['player_id'])
				{
					$bountyid[$j] = $bounty_details[$j]['bounty_id'];
				}
			}
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
	$template_object->display($templatename."bountydisplay.tpl");
	include ("footer.php");
	die();
		break;

	case "cancel":
		if ($playerinfo['turns'] <1 )
		{
			$template_object->assign("error_msg", $l_by_noturn);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

		$res = $db->SelectLimit("SELECT * from {$db_prefix}bounty WHERE bounty_id = $bid", 1);
		if (!$res)
		{
			$template_object->assign("error_msg", $l_by_nobounty);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}
		$bty = $res->fields;

		if ($bty['placed_by'] <> $playerinfo['player_id'])
		{
			$template_object->assign("error_msg", $l_by_notyours);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

		$del = $db->Execute("DELETE FROM {$db_prefix}bounty WHERE bounty_id = $bid");
		$stamp = date("Y-m-d H:i:s");
		$refund = $bty['amount'];
        if ($bty['bounty_on'] < 4){
            $refund = 0;
        } 
		$debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp',turns=turns-1, turns_used=turns_used+1, credits=credits+$refund where player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("error_msg", $l_by_canceled);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;

		break;

	case "place":
		$bounty_on = stripnum($bounty_on);
		$ex = $db->SelectLimit("SELECT * from {$db_prefix}players " .
						   "WHERE destroyed='N' AND player_id = $bounty_on", 1);
		if (!$ex)
		{
			$template_object->assign("error_msg", $l_by_notexists);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

		$bty = $ex->fields;
		if ($bty['destroyed'] == "Y")
		{
			$template_object->assign("error_msg", $l_by_destroyed);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

		if ($playerinfo['turns']<1 )
		{
			$template_object->assign("error_msg", $l_by_noturn);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

		$amount = stripnum($amount);
		if ($amount <= 0)
		{
			$template_object->assign("error_msg", $l_by_zeroamount);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;

		}

		if ($bounty_on == $playerinfo['player_id'])
		{
			$template_object->assign("error_msg", $l_by_yourself);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

		if ($amount > $playerinfo['credits'])
		{
			$template_object->assign("error_msg", $l_by_notenough);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;
		}

	   if ($bounty_maxvalue != 0)
	   {
			$percent = $bounty_maxvalue * 100;
			$returnscore = gen_score($playerinfo['player_id']);
			$score = $returnscore[1];
			$maxtrans = floor($score * $score * $bounty_maxvalue);
			$l_by_placed = "Maximum bounty available to place would be: ". NUMBER($maxtrans) . "<br>".$l_by_placed;
			$previous_bounty = 0;
			$pb = $db->Execute("SELECT SUM(amount) AS totalbounty FROM {$db_prefix}players WHERE bounty_on = $bounty_on AND placed_by = $playerinfo[player_id]");
			if ($pb)
			{
				$prev = $pb->fields;
				$previous_bounty = $prev[totalbounty];
			}
			if ($amount + $previous_bounty > $maxtrans)
			{
				$l_by_toomuch = str_replace("[percent]", $percent, $l_by_toomuch);
				$template_object->assign("error_msg", "Maximum bounty available to place would be: $maxtrans<br>".$l_by_toomuch);
				$template_object->assign("gotobounty", $l_gotobounty);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."bountydie.tpl");
				include ("footer.php");
				die();
				break;
			}

	  }

	  $mystuff = $playerinfo['character_name']."|".$amount."|";

	  $debug_query = $db->Execute("INSERT INTO {$db_prefix}bounty (bounty_on,placed_by,amount) values ($bounty_on, $playerinfo[player_id] ,$amount)");
	  db_op_result($debug_query,__LINE__,__FILE__);
	  $stamp = date("Y-m-d H:i:s");
	  $debug_query = $db->Execute("UPDATE {$db_prefix}players SET last_login='$stamp',turns=turns-1, turns_used=turns_used+1, credits=credits-$amount where player_id=$playerinfo[player_id]");
	  db_op_result($debug_query,__LINE__,__FILE__);

	  $res = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id = $bounty_on", 1);
		$mystuff2 = $res->fields['character_name'];
	  $mystuff = $mystuff.$mystuff2;

		insert_news($mystuff, 1, "bounty");

			$template_object->assign("error_msg", $l_by_placed);
			$template_object->assign("gotobounty", $l_gotobounty);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."bountydie.tpl");
			include ("footer.php");
			die();
			break;

	default:
		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}players " .
									"WHERE destroyed='N' AND player_id <> $playerinfo[player_id] ORDER BY character_name ASC");
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
			$playername[$playerlist] = $charname;
			$playerlist++;
			$debug_query->MoveNext();
		}

		$result3 = $db->Execute ("SELECT bounty_on, SUM(amount) as total_bounty FROM {$db_prefix}bounty GROUP BY bounty_on");

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
	$template_object->assign("playername", $playername);
	$template_object->assign("playerlist", $playerlist);
	$template_object->assign("l_amount", $l_amount);
	$template_object->assign("l_by_moredetails", $l_by_moredetails);
	$template_object->assign("color_header", $color_header);
	$template_object->assign("l_by_nobounties", $l_by_nobounties);
	$template_object->assign("l_by_place", $l_by_place);
	$template_object->assign("l_by_amount", $l_by_amount);
	$template_object->assign("l_by_bountyon", $l_by_bountyon);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."bountydefault.tpl");
	include ("footer.php");
	die();
	break;
}

close_database();
?>
