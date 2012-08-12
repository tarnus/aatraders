<?php
get_post_ifset("minimum, maximum, percentage, maxplanetpercent");

if ($percentage=="")
	$percentage=100;
if ($maxplanetpercent=="")
	$maxplanetpercent=0;	
$maxplanetpercent = min(100,StripNonNum($maxplanetpercent));
$minimum = StripNonNum($minimum);
$maximum = StripNonNum($maximum);
$percentage = min(100,StripNonNum($percentage));

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
//		echo $planet[$i]['planet_id'] . " - " . $planet[$i]['name'] . "<br>";
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

$template_object->assign("l_igb_planetconsolidate", $l_igb_planetconsolidate);
$template_object->assign("l_igb_transferamount", $l_igb_transferamount);
$template_object->assign("total", NUMBER($amount['total']));
$template_object->assign("l_igb_transferfee", $l_igb_transferfee);
$template_object->assign("fee", NUMBER($fee));
$template_object->assign("l_igb_plaffected", $l_igb_plaffected);
$template_object->assign("count", NUMBER($amount['count']));
$template_object->assign("l_igb_turncost", $l_igb_turncost);
$template_object->assign("tcost", NUMBER($tcost));
$template_object->assign("l_igb_amounttransferred", $l_igb_amounttransferred);
$template_object->assign("transfer", NUMBER($transfer));
$template_object->assign("minimum", $minimum);
$template_object->assign("maximum", $maximum);
$template_object->assign("percentage", $percentage);
$template_object->assign("maxplanetpercent", $maxplanetpercent);
$template_object->assign("l_igb_consolidate", $l_igb_consolidate);
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_consolidate2.tpl");
?>