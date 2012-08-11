<?php
$res = $db->Execute("SELECT character_name, player_id FROM {$db_prefix}players WHERE destroyed!='Y' and player_id > 3 and email NOT LIKE '%@npc' ORDER BY character_name ASC");
while (!$res->EOF)
{
	$ships[]=$res->fields;
	$res->MoveNext();
}
$res->close();

$res = $db->Execute("SELECT pl.name, pl.planet_id, pl.sector_id, un.sector_name, un.zone_id FROM {$db_prefix}planets as pl, {$db_prefix}universe as un WHERE pl.owner=$playerinfo[player_id] and un.sector_id=pl.sector_id ORDER BY pl.sector_id ASC");
$i = 0;
while (!$res->EOF)
{
	$planets[$i]=$res->fields;
	$planet_sg_zone[$planets[$i]['sector_id']] = $planets[$i]['zone_id'];
	$i++;
	$res->MoveNext();
}
$res->close();

$template_object->assign("l_igb_transfertype", $l_igb_transfertype);
$template_object->assign("l_igb_toanothership", $l_igb_toanothership);

$shipcount = 0;
foreach($ships as $ship)
{
	$shipid[$shipcount] = $ship['player_id'];
	$playername[$shipcount] = $ship['character_name'];
	$shipcount++;
}

$template_object->assign("shipcount", $shipcount);
$template_object->assign("shipid", $shipid);
$template_object->assign("playername", $playername);

$template_object->assign("l_igb_shiptransfer", $l_igb_shiptransfer);
$template_object->assign("l_igb_fromplanet", $l_igb_fromplanet);
$template_object->assign("l_igb_source", $l_igb_source);

$planetcount = 0;
$template_object->assign("isplanets", isset($planets));
if (isset($planets))
{
	foreach($planets as $planet)
	{
		if (empty($planet['name']))
			$planet['name'] = $l_igb_unnamed;
		$planetzone_id = ($planets[$i]['sg_sector'] == 0) ? $planets[$i]['zone_id'] : $planet_sg_zone[$planets[$i]['sg_sector']];
		if($planetzone_id != 4 || $planets[$i]['sg_sector'] == 0)
		{
			$planetid[$planetcount] = $planet['planet_id'];
			$planetname[$planetcount] = $planet['name'];
			$planetsector[$planetcount] = $planet['sector_name'];
			$planetcount++;
		}
	}
}
else
{
	$template_object->assign("l_igb_none", $l_igb_none);
}

$template_object->assign("planetcount", $planetcount);
$template_object->assign("l_igb_in", $l_igb_in);
$template_object->assign("planetid", $planetid);
$template_object->assign("planetname", $planetname);
$template_object->assign("planetsector", $planetsector);
$template_object->assign("l_igb_destination", $l_igb_destination);

$template_object->assign("l_igb_planettransfer", $l_igb_planettransfer);

$template_object->assign("l_igb_conspl", $l_igb_conspl);
$template_object->assign("l_igb_consolidate", $l_igb_consolidate);
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_transfer.tpl");
?>