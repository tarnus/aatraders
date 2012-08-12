<?php
get_post_ifset("minimum, maximum, percentage, maxplanetpercent");

$minimum = StripNonNum($minimum);
$maximum = StripNonNum($maximum);
if ($percentage=="")
	$percentage=100;
$percentage = min(100,StripNonNum($percentage));

if ($maxplanetpercent=="")
	$maxplanetpercent=0;	
$maxplanetpercent = min(100,StripNonNum($maxplanetpercent)); 

//-------------------
$query = "SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.zone_id, {$db_prefix}universe.sg_sector, {$db_prefix}planets.* FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.owner=$playerinfo[player_id] and {$db_prefix}universe.sector_id ={$db_prefix}planets.sector_id";
if ($minimum != 0)
	$query .= " AND {$db_prefix}planets.credits >= $minimum";

if ($maximum != 0)
	$query .= " AND {$db_prefix}planets.credits <= $maximum";

if ($maxplanetpercent != 0 )	
	$query .= " AND (({$db_prefix}planets.credits/{$db_prefix}planets.max_credits)*100)  >= $maxplanetpercent";

$res = $db->Execute($query);

$planet_sg_zone = array();
$i = 0;
if ($res)
{
	while (!$res->EOF)
	{
		$planet[$i] = $res->fields;
		if($planet[$i]['sg_sector'] == 0)
		{
			$planet_sg_zone[$planet[$i]['sector_id']] = $planet[$i]['zone_id'];
		}
		else
		{
			if(!isset($planet_sg_zone[$planet[$i]['sg_sector']]))
			{
				$query = "SELECT zone_id FROM {$db_prefix}universe WHERE sector_id=" . $planet[$i]['sg_sector'];
				$getzone = $db->SelectLimit($query, 1);
				$planet_sg_zone[$planet[$i]['sg_sector']] = $getzone->fields['zone_id'];
			}
		}
//echo $planet[$i]['sector_id'] . " - " . $planet[$i]['sg_sector'] . " - " . $planet[$i]['zone_id'] . " - " . $planet_sg_zone[$planet[$i]['sector_id']] . "<br>";
		$i++;
		$res->MoveNext();
	}
}

$num_planets = $i;
$planet_list = "";

for($i=0; $i < $num_planets; $i++)
{
//echo $planet[$i]['sg_sector'] . " - " . $planet_sg_zone[$planet[$i]['sg_sector']] . "<br>";

	$planetzone_id = ($planet[$i]['sg_sector'] == 0) ? $planet[$i]['zone_id'] : $planet_sg_zone[$planet[$i]['sg_sector']];
	if($planetzone_id != 4)
	{
		$planet_list .= $planet[$i]['planet_id'] . ",";
	}
}
$planet_list .= "-1";
//echo "Credits: $total_credits - PLanets: $total_collection<br>";

//--------------------
$query = "SELECT SUM(credits*($percentage/100)) as total, COUNT(*) as count from {$db_prefix}planets WHERE credits != 0 and planet_id IN ($planet_list)";

if ($minimum != 0)
	$query .= " AND credits >= $minimum";

if ($maximum != 0)
	$query .= " AND credits <= $maximum";

if ($maxplanetpercent != 0 )	
	$query .= " AND ((credits/max_credits)*100)  >= $maxplanetpercent";	

$res = $db->Execute($query);
$amount = $res->fields;
$res->close();

$fee = $ibank_paymentfee * $amount['total'];

$tcost = ceil($amount['count'] / $igb_tconsolidate);
$transfer = $amount['total'] - $fee;

if ($tcost > $playerinfo['turns'])
	igb_error($l_igb_notenturns, "igb.php?command=transfer");

$template_object->assign("l_igb_transfersuccessful", $l_igb_transfersuccessful);
$template_object->assign("l_igb_currentpl", $l_igb_currentpl);
$template_object->assign("l_igb_turncost", $l_igb_turncost);
$template_object->assign("transfer", NUMBER($transfer));
$template_object->assign("tcost", NUMBER($tcost));
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$query = "UPDATE {$db_prefix}planets SET credits=credits-(credits*($percentage/100)) WHERE credits != 0 and planet_id IN ($planet_list)";

if ($minimum != 0)
	$query .= " AND credits >= $minimum";

if ($maximum != 0)
	$query .= " AND credits <= $maximum";
if ($maxplanetpercent != 0 )	
	$query .= " AND ((credits/max_credits)*100)  >= $maxplanetpercent";	

$debug_query = $db->Execute($query);
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns - $tcost, credits=credits + $transfer WHERE player_id = $playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_consolidate3.tpl");
?>