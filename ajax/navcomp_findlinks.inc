<?php

get_post_ifset("target_sector, warplist");

$target_sector = urldecode($target_sector);
$warplist = urldecode($warplist);
//echo "Target: $target_sector<br>";
//echo "Warplist: $warplist<br>";

//	$db->debug=1;

$result2 = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($target_sector), 1);
db_op_result($result2,__LINE__,__FILE__);
$target_sectorid = $result2->fields['sector_id'];
$result2->close();

$checkfailed = 0;

if(!empty($warplist))
{
	$warpsectors = explode("|", $warplist);
	array_unshift($warpsectors, $sectorinfo['sector_name']);
	$targetsectoridcheck = "";

	for($i = 0; $i < count($warpsectors); $i++)
	{
		if($i == 0)
		{
			$resultcheck = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($warpsectors[$i]), 1);
			db_op_result($resultcheck,__LINE__,__FILE__);
			$sectoridcheck = $resultcheck->fields['sector_id'];
			$sectoridcount = $resultcheck->RecordCount();
			$resultcheck->close();
		}
		else
		{
			$sectoridcheck = $targetsectoridcheck;
			$sectoridcount = 1;
		}

		if($sectoridcount == 1)
		{
			if($i != (count($warpsectors) - 1))
			{
				$resultcheck = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($warpsectors[$i + 1]), 1);
				db_op_result($resultcheck,__LINE__,__FILE__);
				$targetsectoridcheck = $resultcheck->fields['sector_id'];
				$targetsectoridcount = $resultcheck->RecordCount();
				$resultcheck->close();
				if($targetsectoridcount != 1)
				{
					$checkfailed = 1;
				}
			}
			else
			{
				$targetsectoridcheck = $target_sectorid;
			}

			if($checkfailed == 0)
			{
				$linkcheck = $db->Execute("SELECT link_dest FROM {$db_prefix}links WHERE link_start='$sectoridcheck' and link_dest='$targetsectoridcheck'");
				db_op_result($linkcheck,__LINE__,__FILE__);
				$linkcount = $linkcheck->RecordCount();
				$linkcheck->close();
				if($linkcount != 1)
				{
					$checkfailed = 2;
				}
			}
		}
		else
		{
			$checkfailed = 3;
		}
	}
}
else
{
	$linkcheck = $db->Execute("SELECT link_dest FROM {$db_prefix}links WHERE link_start='" . $sectorinfo['sector_id'] . "' and link_dest='$target_sectorid'");
	db_op_result($linkcheck,__LINE__,__FILE__);
	$linkcount = $linkcheck->RecordCount();
	$linkcheck->close();
	if($linkcount != 1)
	{
		$checkfailed = 5;
	}
}

if($checkfailed == 0)
{
	$res = $db->Execute("SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.sector_id, {$db_prefix}links.link_dest FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$target_sectorid' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");
	db_op_result($res,__LINE__,__FILE__);

	$resultlist = "";
	if ($res > 0)
	{
		while (!$res->EOF)
		{
			$res_return = $db->Execute("SELECT source FROM {$db_prefix}sector_log WHERE player_id=$playerinfo[player_id] and (source='" . $res->fields['sector_id'] . "' or destination='" . $res->fields['sector_id'] . "')");
			db_op_result($res_return,__LINE__,__FILE__);
			$visitedcount = $res_return->RecordCount();
			$res_return->close();
			$visited = "";
			if($visitedcount == 0)
			{
				$visited = "`";
			}
			$resultlist .= $visited . $res->fields['sector_name'] . "|";
			$res->MoveNext();
		}
	}
	$res->close();
	echo $resultlist;
}
else
{
	echo "Stop trying to cheat! $checkfailed";
}
?> 
