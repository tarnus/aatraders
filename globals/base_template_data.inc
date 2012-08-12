<?php

include ("globals/calc_ownership.inc");
include ("globals/player_insignia_name.inc");
include ("globals/calc_dist.inc");
include ("globals/translate_news_headline.inc");
include ("globals/add_smilies.inc");

$template_object->assign("allow_probes", $allow_probes);
$template_object->assign("l_links", $l_links);
$template_object->assign("l_planetstatus", $l_planetstatus);	
$template_object->assign("l_planetdefenses", $l_planetdefenses);	
$template_object->assign("l_changeproduction", $l_changeproduction);	
$template_object->assign("l_teamplanets", $l_teamplanets);
$template_object->assign("l_teamdefenses", $l_teamdefenses);
$template_object->assign("l_spacebeacon", $l_spacebeacon);
$template_object->assign("l_spaceprobes", $l_spaceprobes);
$template_object->assign("l_warpeditors", $l_warpeditors);
$template_object->assign("l_genesistorps", $l_genesistorps);
$template_object->assign("l_sgtorps", $l_sgtorps);
$template_object->assign("l_minesfighters", $l_minesfighters);
$template_object->assign("l_ewarp", $l_ewarp);
$template_object->assign("l_reports", $l_reports);
$template_object->assign("l_shipinfo", $l_shipinfo);
$template_object->assign("l_sectornotes", $l_sectornotes);
$template_object->assign("l_maps", $l_maps);
$template_object->assign("l_messages", $l_messages);
$template_object->assign("l_shiptype", $l_shiptype);
$template_object->assign("l_help", $l_help);
$template_object->assign("l_name", $l_name);
$template_object->assign("l_ship", $l_ship);
$template_object->assign("l_rank", $l_rank);
$template_object->assign("tournament_mode", $tournament_mode);

$template_object->assign("universe_size", $universe_size);

$home_planet_query = $db->SelectLimit("SELECT name from {$db_prefix}planets WHERE planet_id=$playerinfo[home_planet_id]", 1);
db_op_result($home_planet_query,__LINE__,__FILE__);
$template_object->assign("home_planet_name", ($home_planet_query->fields['name'] == "") ? $l_none : $home_planet_query->fields['name']);
$template_object->assign("l_home_planet", $l_home_planet);

$res = $db->Execute("SELECT * FROM {$db_prefix}sector_notes WHERE  (note_sector_id=$shipinfo[sector_id] or note_scanfrom=$shipinfo[sector_id]) and ( note_player_id=$playerinfo[player_id] or  note_team_id=$playerinfo[team])");

$template_object->assign("note_view", $res->RecordCount());
$res->close();
$template_object->assign("l_add_note", $l_add_note);
$template_object->assign("l_view_note", $l_view_note);
$template_object->assign("l_notes", $l_notes);

$res = $db->Execute("SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe.port_type, {$db_prefix}universe.zone_id, {$db_prefix}links.link_dest FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$shipinfo[sector_id]' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");

$links = array();
$links_zone = array();
$links_return = array();
$links_port_type = array();
$links_type = array();

$return_list = "(-1";
$i = 0;
if ($res > 0)
{
	calc_ownership($shipinfo['sector_id']);
	while (!$res->EOF)
	{
		$links[$i] = $res->fields['sector_name'];
		$links_zone[$i] = $res->fields['zone_id'];
		$links_port_type[$i] = $res->fields['port_type'];
		$return_list .= ", " . $res->fields['link_dest'];
		$i++;
		$res->MoveNext();
	}
}
$res->close();
$return_list .= ")";

$num_links = $i;
$template_object->assign("links_zone", $links_zone);
$template_object->assign("links_port_type", $links_port_type);

$res_return = $db->Execute("SELECT {$db_prefix}universe.sector_name FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_dest='$shipinfo[sector_id]' and {$db_prefix}links.link_start IN " . $return_list . " and {$db_prefix}universe.sector_id = {$db_prefix}links.link_start and {$db_prefix}universe.zone_id = 2");
if ($res_return > 0)
{
	while (!$res_return->EOF)
	{
		$value = $res_return->fields['sector_name'];
		$links_return[$value] = 1;
		$res_return->MoveNext();
	}
}
$res_return->close();

$res_return = $db->Execute("SELECT {$db_prefix}universe.sector_name FROM {$db_prefix}sector_log, {$db_prefix}universe WHERE {$db_prefix}sector_log.player_id=$playerinfo[player_id] and ({$db_prefix}sector_log.source IN " . $return_list . " or {$db_prefix}sector_log.destination IN " . $return_list . ") and ({$db_prefix}universe.sector_id ={$db_prefix}sector_log.source or {$db_prefix}universe.sector_id ={$db_prefix}sector_log.destination)");
if ($res_return > 0)
{
	while (!$res_return->EOF)
	{
		$value = $res_return->fields['sector_name'];
		$links_type[$value] = 1;
		$res_return->MoveNext();
	}
}
$res_return->close();

$template_object->assign("links_type", $links_type);

if($playerinfo['team'] != 0){
	$result = $db->SelectLimit("SELECT icon FROM {$db_prefix}teams WHERE id=$playerinfo[team]", 1);
	$template_object->assign("teamicon", $result->fields['icon']);
	$result->close();
}else{
	$template_object->assign("teamicon", "default_icon.gif");
}

if($playerinfo['show_shoutbox'] == 1 && $allow_shoutbox == 1)
{
	$shoutcount = 0;
	$res = $db->Execute("SELECT sb_text, player_name FROM {$db_prefix}shoutbox WHERE sb_alli = 0 ORDER BY sb_date desc  LIMIT 0,5");

	if($res->EOF)
	{
		$shoutmessage[$shoutcount] = $l_news_none;
		$shoutposter[$shoutcount] = "";
		$shoutcount++;
	}
	else
	{
		while (!$res->EOF) 
		{
			$row = $res->fields;
			$shoutposter[$shoutcount] = $row['player_name'];
			$string = stripslashes(rawurldecode($row['sb_text']));
			$string = (AAT_strlen($string) > 70) ? trim(AAT_substr($string, 0, 70)) . "..." : $string;
			$shoutmessage[$shoutcount] = addslashes(add_smilies($string));
			$shoutcount++;
			$res->MoveNext();
		}
	}

	$template_object->assign("shoutcount", $shoutcount);
	$template_object->assign("shoutmessage", $shoutmessage);
	$template_object->assign("shoutposter", $shoutposter);
	$template_object->assign("show_shoutbox", 1);
}
else
{
	$template_object->assign("show_shoutbox", 0);
}

$res = $db->Execute("SELECT {$db_prefix}autoroutes.autoroute_id, {$db_prefix}autoroutes.start_sector, {$db_prefix}autoroutes.destination, {$db_prefix}autoroutes.name, {$db_prefix}universe.sg_sector FROM {$db_prefix}autoroutes, {$db_prefix}universe WHERE {$db_prefix}autoroutes.player_id=$playerinfo[player_id] and {$db_prefix}universe.sector_name = {$db_prefix}autoroutes.start_sector");
$autototal = $res->recordcount();

$counterlist = 0;
while(!$res->EOF)
{
	$autoroute = $res->fields;
	$autolist[$counterlist] = $autoroute['autoroute_id'];
	$autostart[$counterlist] = $autoroute['start_sector'];
	$autoend[$counterlist] = $autoroute['destination'];
	$autoname[$counterlist] = $autoroute['name'];
	$autostartsg[$counterlist] = $autoroute['sg_sector'];
	$counterlist++;
	$res->MoveNext();
}
$res->close();

$res = $db->Execute("SELECT {$db_prefix}autoroutes.autoroute_id, {$db_prefix}autoroutes.start_sector, {$db_prefix}autoroutes.destination, {$db_prefix}autoroutes.name, {$db_prefix}universe.sg_sector FROM {$db_prefix}autoroutes, {$db_prefix}universe WHERE {$db_prefix}autoroutes.player_id=$playerinfo[player_id] and {$db_prefix}universe.sector_name = {$db_prefix}autoroutes.destination");
$autototal += $res->recordcount();

$counterlist = 0;
while(!$res->EOF)
{
	$autoroute = $res->fields;
	$autodestsg[$counterlist] = $autoroute['sg_sector'];
	$counterlist++;
	$res->MoveNext();
}
$res->close();

$template_object->assign("autostart", $autostart);
$template_object->assign("autoend", $autoend);
$template_object->assign("autototal", $autototal);
$template_object->assign("autolist", $autolist);
$template_object->assign("autoname", $autoname);
$template_object->assign("autostartsg", $autostartsg);
$template_object->assign("autodestsg", $autodestsg);
$template_object->assign("sg_sector", $sectorinfo['sg_sector']);


$res = $db->Execute("SELECT cargo_name, amount FROM {$db_prefix}ship_holds WHERE ship_id=$playerinfo[currentship] ");

$cargo_items = 0;
$hold_space = 0;
while(!$res->EOF)
{
	$cargo_name[$cargo_items] = $res->fields['cargo_name'];
	$cargo_amount[$cargo_items] = NUMBER($res->fields['amount']);
	$hold_space += ($res->fields['hold_space'] * $res->fields['amount']);
	$cargo_holds[$cargo_items] = $res->fields['hold_space'];
	$cargo_items++;
	$res->MoveNext();
}
$res->close();

$template_object->assign("cargo_holds", $cargo_holds);
$template_object->assign("cargo_items", $cargo_items);
$template_object->assign("cargo_name", $cargo_name);
$template_object->assign("cargo_amount", $cargo_amount);
$template_object->assign("hold_space_used", $hold_space);
$template_object->assign("hold_space_free", NUMBER(NUM_HOLDS($shipinfo['hull']) - $hold_space));
$template_object->assign("l_hold_space_used", $l_hold_space_used);
$template_object->assign("l_hold_space_free", $l_hold_space_free);

$newposts = 0;
if($playerinfo['team'] != 0){
	$query2 = $db->Execute("select {$db_prefix}team_forum_posts.post_id from {$db_prefix}team_forum_posts, {$db_prefix}team_forums, {$db_prefix}team_forum_players where {$db_prefix}team_forums.teams=$playerinfo[team] and {$db_prefix}team_forum_posts.forum_id={$db_prefix}team_forums.forum_id and {$db_prefix}team_forum_players.player_id=$playerinfo[player_id] and {$db_prefix}team_forum_posts.post_time>={$db_prefix}team_forum_players.lastonline order by {$db_prefix}team_forum_posts.post_time");
	db_op_result($query2,__LINE__,__FILE__);
	$newposts = $query2->RecordCount();
	$query2->close();
}

$i = 0;
$num_traderoutes = 0;

$query = $db->Execute("SELECT * FROM {$db_prefix}traderoutes WHERE source_sector=$shipinfo[sector_id] AND player_id=$playerinfo[player_id]");

while (!$query->EOF)
{
	$traderoutes = $query->fields;

	$traderoute_links[$num_traderoutes] = $traderoutes['traderoute_id'];
	if ($traderoutes['source_planet_id'] == 0)
	{
		$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$l_port&nbsp;" . ucfirst($traderoutes['source_commodity']);
	}
	else
	{
		$planet_query = $db->Execute("SELECT name FROM {$db_prefix}planets WHERE planet_id=" . $traderoutes['source_planet_id']);
		if (!$planet_query || $planet_query->RecordCount() == 0)
		{
			$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes] . "$l_unknown " . ucfirst($traderoutes['source_commodity']);
		}
		else
		{
			$planet = $planet_query->fields;
			if ($planet['name'] == "")
			{
				$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$l_unnamed " . ucfirst($traderoutes['source_commodity']);
			}
			else
			{
				$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$planet[name] " . ucfirst($traderoutes['source_commodity']);
			}
		}
		$planet_query->close();
	}

	if ($traderoutes['roundtrip'] != 'Y')
	{
		$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "&nbsp;=&gt;&nbsp;";
	}
	else
	{
		$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "&nbsp;&lt;=&gt;&nbsp;";
	}

	if ($traderoutes['destination_planet_id'] == 0)
	{
		$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$l_port&nbsp;" . ucfirst($traderoutes['destination_commodity']);
	}
	else
	{
		$planet_query = $db->Execute("SELECT name FROM {$db_prefix}planets WHERE planet_id=" . $traderoutes['destination_planet_id']);
		if (!$planet_query || $planet_query->RecordCount() == 0)
		{
			$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$l_unknown " . ucfirst($traderoutes['destination_commodity']);
		}
		else
		{
			$planet = $planet_query->fields;
			if ($planet['name'] == "")
			{
				$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$l_unnamed " . ucfirst($traderoutes['destination_commodity']);
			}
			else
			{
				$traderoute_display[$num_traderoutes]  = $traderoute_display[$num_traderoutes]  . "$planet[name] " . ucfirst($traderoutes['destination_commodity']);
			}
		}
		$planet_query->close();
	}

	$num_traderoutes++;
	$query->MoveNext();
}
$query->close();

$template_object->assign("l_traderoutes", $l_traderoutes);
$template_object->assign("traderoute_display", $traderoute_display);
$template_object->assign("traderoute_links", $traderoute_links);
$template_object->assign("num_traderoutes", $num_traderoutes);
$template_object->assign("l_trade_control", $l_trade_control);

$quickshout = "";
$res2 = $db->Execute("SELECT sb_text FROM {$db_prefix}shoutbox WHERE sb_alli = " . (($playerinfo['team']<=0)?-1:$playerinfo['team']) . " ORDER BY sb_date DESC LIMIT 0,5");
$countflag=0;
if (!$res2 || $res2->RecordCount() != 0){
	$countflag++;
}
if ($countflag > 0){
	for ( $i = 0 ; $i < 5 ; $i++ )
	{
		if (!$res2->EOF)
		{
			$row2 = $res2->fields;
			$quickshout .= strip_tags(stripslashes(rawurldecode($row2['sb_text'])))."\n";
			if (!$res2->EOF)
			{
				$quickshout .= "---------------------------------\n";
				$res2->MoveNext();
			}
		}
	}
}
$res2->close();


if($playerinfo['show_newscrawl'] == 1 && $allow_newscrawl == 1)
{
	$startdate = date("Y-m-d");
	$newscount = 0;

	$res = $db->Execute("SELECT * from {$db_prefix}news where LEFT(date,10) = '$startdate' order by news_id desc");
	if($res->EOF)
	{
		$newsmessage[$newscount] = $l_news_none;
		$newscount++;
	}
	else
	{
		while (!$res->EOF) 
		{
			$row = $res->fields;
			$newsheadline = translate_news_headline($row);
			$newsmessage[$newscount] = $newsheadline;
			$newscount++;
			$res->MoveNext();
		}
	}
	$res->close();
	$template_object->assign("newscount", $newscount);
	$template_object->assign("newsmessage", $newsmessage);
	$template_object->assign("show_newscrawl", 1);
}
else
{
	$template_object->assign("show_newscrawl", 0);
}

/*
	Add in 6 X 6 map element.
*/

if($sectorinfo['sg_sector'] == 0){
	$isnewnav = 0;
	$query2 = "SELECT spiral_arm, dest_sector, port_type, zone_id, x, y, z, distance, dest_sector_name as sector_name FROM {$db_prefix}navmap, {$db_prefix}universe where {$db_prefix}navmap.start_sector=$shipinfo[sector_id] and {$db_prefix}universe.sector_id = {$db_prefix}navmap.dest_sector ORDER BY {$db_prefix}navmap.distance, {$db_prefix}navmap.dest_sector ASC";
	$result = $db->Execute ($query2);
	db_op_result($result,__LINE__,__FILE__);

	if($result->RecordCount() == 0){
		$result->close();
		$distance = $universe_size;
		if($enable_spiral_galaxy != 1){
			$query2 = "SELECT sector_name, sector_id as dest_sector, port_type, zone_id, x, y, z,SQRT((($sectorinfo[x]-x) * ($sectorinfo[x]-x))+(($sectorinfo[y]-y) * ($sectorinfo[y]-y))+(($sectorinfo[z]-z) * ($sectorinfo[z]-z))) as distance FROM {$db_prefix}universe where SQRT((($sectorinfo[x]-x) * ($sectorinfo[x]-x))+(($sectorinfo[y]-y) * ($sectorinfo[y]-y))+(($sectorinfo[z]-z) * ($sectorinfo[z]-z))) < $distance and sector_id!=$shipinfo[sector_id]  and sg_sector = 0  ORDER BY distance ASC,sector_id DESC limit 0,40";
		}
		else
		{
			$query2 = "SELECT sector_name, spiral_arm, sector_id as dest_sector, port_type, zone_id, x, y, z,SQRT(POW(($sectorinfo[x]-x),2)+POW(($sectorinfo[y]-y),2)+POW(($sectorinfo[z]-z),2)) as distance FROM {$db_prefix}universe where SQRT(POW(($sectorinfo[x]-x),2)+POW(($sectorinfo[y]-y),2)+POW(($sectorinfo[z]-z),2)) < $distance and sector_id!=$shipinfo[sector_id]  and sg_sector = 0  ORDER BY distance ASC,sector_id DESC limit 0,40";
		}

		$result = $db->Execute ($query2);
		db_op_result($result,__LINE__,__FILE__);
		$isnewnav = 1;
	}

	$mapsectorcount2 = $result->RecordCount();
	$movement_where = "(";
	$scan_where = "(";
	$row = $result->GetArray();
	$result->close();
	for ($nav = 0; $nav < $mapsectorcount2; $nav++)
	{
		$movement_where .= "source = " . $row[$nav]['dest_sector'] . " or ";
		$scan_where .= "sector_id = " . $row[$nav]['dest_sector'] . " or ";
	}

	$movement_where .= "source = -1)";
	$scan_where .= "sector_id = -1)";

	$result2 = $db->Execute("SELECT distinct source, zone_id, warp_links, port_buys FROM {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] and $movement_where order by source ASC, time DESC");
	db_op_result($result2,__LINE__,__FILE__);
	$zone_where = "";
	while (!$result2->EOF) 
	{
		$row2 = $result2->fields;
		$temp = $row2['source'];
		$sectorzone[$temp] = $row2['zone_id'];
		$sectorlist[$temp] = $row2['warp_links'];
		$port_buys[$temp] = $row2['port_buys'];
		$zone_where .= "zone_id = " . $row2['zone_id'] . " or ";
		$result2->Movenext();
	}
	$result2->close();

	$zone_where .= "zone_id = -1";

	$result4 = $db->Execute ("SELECT distinct zone_id, zone_color, zone_name FROM {$db_prefix}zones WHERE $zone_where ORDER BY zone_name ASC");
	$totalzones = 0;

	while (!$result4->EOF) 
	{
		$row4 = $result4->fields;
		$temp = $row4['zone_id'];
		$zoneinfo[$temp] = $row4['zone_color'];
		$zonename[$temp] = $row4['zone_name'];
		$zonenumber[$totalzones] = $temp;
		$totalzones++;
		$result4->Movenext();
	}
	$result4->close();

	$x1=0;
	$x2=0;
	$x3=0;
	$x4=0;
	$value_list = '';
	for ($nav = 0; $nav < $mapsectorcount2; $nav++)
	{
		if($isnewnav == 1)
		{
//			$storetriptime2 = round(calc_dist($shipinfo['sector_id'], $row[$nav]['dest_sector']));
			$storetriptime = round($row[$nav]['distance']);
			$value_list .= "($shipinfo[sector_id], " . $row[$nav]['dest_sector'] . ", '" . $row[$nav]['sector_name'] . "', $storetriptime),";
		}

		$shipspeed = mypw($level_factor, $shipinfo['engines']);
		$triptime = round($row[$nav]['distance'] / $shipspeed);

		if ($triptime == 0)
		{
			$triptime = 1;
		}

		$link_list = $l_unknown;
		$zonecolor = "#000000";
		$port= "unknown";
		$alt = $row[$nav]['sector_name'] . " - $l_unknown - " . round($triptime) . " realspace turns";

		$tempsector = $row[$nav]['dest_sector'];

		if ($sectorzone[$tempsector] > 0 )
		{
			$temp = $sectorzone[$tempsector];
			$link_list = empty($sectorlist[$tempsector]) ? $l_none : $sectorlist[$tempsector];
			$buy_list = empty($port_buys[$tempsector]) ? $l_none : str_replace("|", "<br>", $port_buys[$tempsector]);
			$zonecolor = $zoneinfo[$temp];
			$port = $row[$nav]['port_type'];
			$alt  = $row[$nav]['sector_name'] . " - " . ucfirst($port) . " - ". $zonename[$temp] . " - " . round($triptime) . " realspace turns";
		}

		$sectorplaced = 0;
		if ($row[$nav]['x'] >  $sectorinfo['x'] && $row[$nav]['y'] <=  $sectorinfo['y']){
			$xyplus[$x1]=$row[$nav]['sector_name'];
			$link_listx1[$x1] = $link_list;
			$buy_listx1[$x1] = $buy_list;
			$sectorzonecolorx1[$x1] = $zonecolor;
			$sectorimagex1[$x1] = $port;
			$sectortitlex1[$x1] = $alt;
			$positionx1[$x1]= $row[$nav]['x']."|".$row[$nav]['y']."|".$row[$nav]['z'];
			$galacticarmx1[$x1]= $row[$nav]['spiral_arm'];
			$altsectorx1[$x1]  = rawurlencode($row[$nav]['sector_name']);
			$altportx1[$x1]  = ucfirst($port);
			$altturnsx1[$x1]  = round($triptime) . " realspace turns";
			$sectorplaced = 1;
			$x1++;
		}

		if ($row[$nav]['x'] <=  $sectorinfo['x'] && $row[$nav]['y'] >  $sectorinfo['y'] && $sectorplaced == 0){
			$xyminus[$x2]=$row[$nav]['sector_name'];
			$link_listx2[$x2] = $link_list;
			$buy_listx2[$x2] = $buy_list;
			$sectorzonecolorx2[$x2] = $zonecolor;
			$sectorimagex2[$x2] = $port;
			$sectortitlex2[$x2] = $alt;
			$positionx2[$x2]= $row[$nav]['x']."|".$row[$nav]['y']."|".$row[$nav]['z'];
			$galacticarmx2[$x2]= $row[$nav]['spiral_arm'];
			$altsectorx2[$x2]  = rawurlencode($row[$nav]['sector_name']);
			$altportx2[$x2]  = ucfirst($port);
			$altturnsx2[$x2]  = round($triptime) . " realspace turns";
			$sectorplaced = 1;
			$x2++;
		}

		if ($row[$nav]['x'] <  $sectorinfo['x'] && $row[$nav]['y'] <=  $sectorinfo['y'] && $sectorplaced == 0){
			$xyminusp[$x3]=$row[$nav]['sector_name'];
			$link_listx3[$x3] = $link_list;
			$buy_listx3[$x3] = $buy_list;
			$sectorzonecolorx3[$x3] = $zonecolor;
			$sectorimagex3[$x3] = $port;
			$sectortitlex3[$x3] = $alt;
			$positionx3[$x3]= $row[$nav]['x']."|".$row[$nav]['y']."|".$row[$nav]['z'];
			$galacticarmx3[$x3]= $row[$nav]['spiral_arm'];
			$altsectorx3[$x3]  = rawurlencode($row[$nav]['sector_name']);
			$altportx3[$x3]  = ucfirst($port);
			$altturnsx3[$x3]  = round($triptime) . " realspace turns";
			$sectorplaced = 1;
			$x3++;
		}

		if (($row[$nav]['x'] >=  $sectorinfo['x'] && $row[$nav]['y'] > $sectorinfo['y'] && $sectorplaced == 0) || ($row[$nav]['x'] ==  $sectorinfo['x'] && $row[$nav]['y'] == $sectorinfo['y'] && $sectorplaced == 0)){
			$xyplusm[$x4]=$row[$nav]['sector_name'];
			$link_listx4[$x4] = $link_list;
			$buy_listx4[$x4] = $buy_list;
			$sectorzonecolorx4[$x4] = $zonecolor;
			$sectorimagex4[$x4] = $port;
			$sectortitlex4[$x4] = $alt;
			$positionx4[$x4]= $row[$nav]['x']."|".$row[$nav]['y']."|".$row[$nav]['z'];
			$galacticarmx4[$x4]= $row[$nav]['spiral_arm'];
			$altsectorx4[$x4]  = rawurlencode($row[$nav]['sector_name']);
			$altportx4[$x4]  = ucfirst($port);
			$altturnsx4[$x4]  = round($triptime) . " realspace turns";
			$x4++;
		}
	}
	if($isnewnav == 1)
	{
		$debug_query3 = $db->Execute("INSERT INTO {$db_prefix}navmap (start_sector, dest_sector, dest_sector_name, distance) VALUES " . AAT_substr($value_list, 0, -1) );
	}
}

$template_object->assign("xyplus", $xyplus);
$template_object->assign("xyplusm", $xyplusm);
$template_object->assign("xyminus", $xyminus);
$template_object->assign("xyminusp", $xyminusp);

$template_object->assign("l_port_buys", $l_port_buys);
$template_object->assign("link_listx1", $link_listx1);
$template_object->assign("link_listx2", $link_listx2);
$template_object->assign("link_listx3", $link_listx3);
$template_object->assign("link_listx4", $link_listx4);
$template_object->assign("buy_listx1", $buy_listx1);
$template_object->assign("buy_listx2", $buy_listx2);
$template_object->assign("buy_listx3", $buy_listx3);
$template_object->assign("buy_listx4", $buy_listx4);
$template_object->assign("sectorzonecolorx1", $sectorzonecolorx1);
$template_object->assign("sectorimagex1", $sectorimagex1);
$template_object->assign("sectortitlex1", $sectortitlex1);
$template_object->assign("altsectorx1", $altsectorx1);
$template_object->assign("altportx1", $altportx1);
$template_object->assign("altturnsx1", $altturnsx1);
$template_object->assign("galacticarmx1", $galacticarmx1);
$template_object->assign("nav_scan_coordsx1", $positionx1);
$template_object->assign("sectorzonecolorx2", $sectorzonecolorx2);
$template_object->assign("sectorimagex2", $sectorimagex2);
$template_object->assign("sectortitlex2", $sectortitlex2);
$template_object->assign("altsectorx2", $altsectorx2);
$template_object->assign("altportx2", $altportx2);
$template_object->assign("altturnsx2", $altturnsx2);
$template_object->assign("galacticarmx2", $galacticarmx2);
$template_object->assign("nav_scan_coordsx2", $positionx2);
$template_object->assign("sectorzonecolorx3", $sectorzonecolorx3);
$template_object->assign("sectorimagex3", $sectorimagex3);
$template_object->assign("sectortitlex3", $sectortitlex3);
$template_object->assign("altsectorx3", $altsectorx3);
$template_object->assign("altportx3", $altportx3);
$template_object->assign("altturnsx3", $altturnsx3);
$template_object->assign("galacticarmx3", $galacticarmx3);
$template_object->assign("nav_scan_coordsx3", $positionx3);
$template_object->assign("sectorzonecolorx4", $sectorzonecolorx4);
$template_object->assign("sectorimagex4", $sectorimagex4);
$template_object->assign("sectortitlex4", $sectortitlex4);
$template_object->assign("altsectorx4", $altsectorx4);
$template_object->assign("altportx4", $altportx4);
$template_object->assign("altturnsx4", $altturnsx4);
$template_object->assign("galacticarmx4", $galacticarmx4);
$template_object->assign("nav_scan_coordsx4", $positionx4);

$template_object->assign("l_galacticarm", $l_galacticarm);
$template_object->assign("galacticarm", $galacticarm);
$template_object->assign("nav_scan_coords", $position);
$template_object->assign("ship_coordinates", $sectorinfo['x']."|".$sectorinfo['y']."|".$sectorinfo['z']);
$template_object->assign("ship_galacticarm", $sectorinfo['spiral_arm']);

// End Map element

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}zones WHERE zone_id=$sectorinfo[zone_id]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$zoneinfo = $debug_query->fields;
$debug_query->close();

if ($zoneinfo['zone_id'] < 5)
{
	$zoneinfo['zone_name'] = $l_zname[$zoneinfo['zone_id']];
}

$template_object->assign("sector", $sectorinfo['sector_name']);
$template_object->assign("l_sector", $l_sector);
$template_object->assign("zoneid", $zoneinfo['zone_id']);
$template_object->assign("zonename", stripslashes($zoneinfo['zone_name']));
$template_object->assign("beacon", stripslashes($sectorinfo['beacon']));

$template_object->assign("title", $title);

$player_insignia = player_insignia_name($playerinfo['player_id'], $playerinfo['score']);
$template_object->assign("insignia", $player_insignia[0]);
$template_object->assign("insignia_name", $player_insignia[1]);
$template_object->assign("avatar", $playerinfo['avatar']);
$template_object->assign("player_name", $playerinfo['character_name']);
$template_object->assign("team_id", $playerinfo['team']);
$template_object->assign("shipname", $shipinfo['name']);
$template_object->assign("score", NUMBER($playerinfo['score']));
$template_object->assign("turns", NUMBER($playerinfo['turns']));
$template_object->assign("turnsused", NUMBER($playerinfo['turns_used']));
$template_object->assign("main", "Main");
$template_object->assign("galaxy_map_enabled", $galaxy_map_enabled);

$template_object->assign("basefontsize", $basefontsize);
$template_object->assign("l_turns_have", $l_turns_have);
$template_object->assign("l_turns_used", $l_turns_used);
$template_object->assign("l_score", $l_score);
$template_object->assign("l_abord", $l_abord);

$armor_pts_max = NUM_armor($shipinfo['armor']);
$ship_fighters_max = NUM_FIGHTERS($shipinfo['fighter']);
$torps_max = NUM_TORPEDOES($shipinfo['torp_launchers']);
$template_object->assign("shipinfo_fighters", NUMBER($shipinfo['fighters']));
$template_object->assign("ship_fighters_max", NUMBER($ship_fighters_max));
$template_object->assign("shipinfo_torps", NUMBER($shipinfo['torps']));
$template_object->assign("torps_max", NUMBER($torps_max));
$template_object->assign("shipinfo_armor_pts", NUMBER($shipinfo['armor_pts']));
$template_object->assign("armor_pts_max", NUMBER($armor_pts_max));

$template_object->assign("commandplanetreport", "&nbsp;<a class=mnu href=\"planet_report.php\">$l_planets</a>&nbsp;");
$template_object->assign("planets", $l_planets);

$template_object->assign("commanddevices", "&nbsp;<a class=mnu href=\"device.php\">$l_device_ports</a>&nbsp;");
$template_object->assign("l_device_ports", $l_device_ports);

$template_object->assign("commanddefensereport", "&nbsp;<a class=mnu href=\"defense_report.php\">$l_sector_def</a>&nbsp;");
$template_object->assign("commandteamdefensereport", "&nbsp;<a class=mnu href=\"team_defense_report.php\">$l_teams $l_sector_def</a>&nbsp;");
$template_object->assign("l_sector_def", $l_sector_def);

$template_object->assign("commandnav", "&nbsp;<a class=mnu href=\"navcomp.php\">$l_navcomp</a>&nbsp;");
$template_object->assign("l_navcomp", $l_navcomp);

$template_object->assign("commandmap", "&nbsp;<a class=mnu href=\"galaxy_map.php\">$l_map</a>&nbsp;");
$template_object->assign("l_map", $l_map);

$template_object->assign("commandlocalmap", "&nbsp;<a class=mnu href=\"galaxy_local.php\">$l_localmap</a>&nbsp;");
$template_object->assign("l_localmap", $l_localmap);

$template_object->assign("command3dmap", "&nbsp;<a class=mnu href=\"galaxy_map3d.php\">$l_3dmap</a>&nbsp;");
$template_object->assign("l_3dmap", $l_3dmap);
$template_object->assign("gd_enabled", extension_loaded("gd"));
$template_object->assign("enable_spiral_galaxy", $enable_spiral_galaxy);

$template_object->assign("commandlog", "&nbsp;<a class=mnu href=\"log.php\">$l_log</a>&nbsp;");
$template_object->assign("l_log", $l_log);

$template_object->assign("commandreadmail", "&nbsp;<a class=mnu href=\"message_read.php\">$l_read_msg</A>&nbsp;");
$template_object->assign("l_read_msg", $l_read_msg);

$template_object->assign("commandsendmail", "&nbsp;<a class=mnu href=\"message_send.php\">$l_send_msg</a>&nbsp;");
$template_object->assign("l_send_msg", $l_send_msg);

$template_object->assign("commandblockmail", "&nbsp;<a class=mnu href=\"messageblockmanager.php\">$l_block_msg</a>&nbsp;");
$template_object->assign("l_block_msg", $l_block_msg);

$template_object->assign("commandranking", "&nbsp;<a class=mnu href=\"ranking.php\">$l_rankings</a>&nbsp;");
$template_object->assign("l_rankings", $l_rankings);

$template_object->assign("commandteams", "&nbsp;<a class=mnu href=\"teams.php\">$l_teams</a>&nbsp;");
$template_object->assign("l_teams", $l_teams);

$template_object->assign("commandteamforum", "&nbsp;<a class=mnu href=\"team_forum.php?command=showtopics\">$l_teamforum<font size=\"1\"> - New: $newposts</font></a>&nbsp;");
$template_object->assign("l_teamforum", $l_teamforum);
$template_object->assign("newposts", $newposts);

$template_object->assign("commandteamship", "&nbsp;<a class=mnu href=\"team_report.php\">$l_teamships</a>&nbsp;");
$template_object->assign("l_teamships", $l_teamships);

$template_object->assign("commanddestruct", "&nbsp;<a class=mnu href=\"self_destruct.php\">$l_ohno</a>&nbsp;");
$template_object->assign("l_ohno", $l_ohno);

$template_object->assign("commandoptions", "&nbsp;<a class=mnu href=\"options.php\">$l_options</a>&nbsp;");
$template_object->assign("l_options", $l_options);

$template_object->assign("commandautotrade", "&nbsp;<a class=mnu href=\"autotrades.php\">$l_autotrade</a>&nbsp;");
$template_object->assign("l_autotrade", $l_autotrade);

$template_object->assign("commandprobe", "&nbsp;<a class=mnu href=\"probes.php\">$l_probe</a>&nbsp;");
$template_object->assign("l_probe", $l_probe);

$template_object->assign("commandfeedback", "&nbsp;<a class=mnu href=\"feedback.php\">$l_feedback</a>&nbsp;");
$template_object->assign("l_feedback", $l_feedback);

$template_object->assign("commandsectornotes", "&nbsp;<a class=mnu href=\"sector_notes.php\">$l_sectornotes</a>&nbsp;");
$template_object->assign("l_sectornotes", $l_sectornotes);

$template_object->assign("commandstoredships", "&nbsp;<a class=mnu href=\"stored_ship_report.php\">$l_storedshipreport</a>&nbsp;");
$template_object->assign("l_storedshipreport", $l_storedshipreport);

$template_object->assign("commandlobby", "&nbsp;<a class=mnu href=\"main.php?lobby_mode=start\">$l_lobby</a>&nbsp;");
$template_object->assign("l_lobby", $l_lobby);

$template_object->assign("enable_spies", $enable_spies);
if ($enable_spies)
{
	$template_object->assign("commandspy", "&nbsp;<a class=mnu href=\"spy.php\">$l_spy</a>&nbsp;");
	$template_object->assign("l_spy", $l_spy);
}

$template_object->assign("enable_dignitaries", $enable_dignitaries);
if ($enable_dignitaries)
{
	$template_object->assign("commanddig", "&nbsp;<a class=mnu href=\"dig.php\">$l_dig</a>&nbsp;");
	$template_object->assign("l_dig", $l_dig);
}

$template_object->assign("forum_link", $link_forums);
if (!empty($link_forums))
{
	$template_object->assign("commandforums", "&nbsp;<a class=\"mnu\" href=\"$link_forums\" TARGET=\"_blank\">$l_forums</a>&nbsp;");
	$template_object->assign("l_forums", $l_forums);
	$template_object->assign("link_forums", 1);
}

$template_object->assign("commandlogout", "&nbsp;<a class=mnu href=\"logout.php\">$l_logout</a>&nbsp;");
$template_object->assign("l_logout", $l_logout);

$template_object->assign("commandteamshoutbox", "&nbsp;<a class=mnu href=\"#\" onClick=\"window.open('shoutbox_team.php','team_shoutbox','toolbar=no,width=600, height=450');\">$l_team_shoutbox</a>&nbsp;");
$template_object->assign("l_team_shoutbox", $l_team_shoutbox);

$template_object->assign("l_set", $l_set);
$template_object->assign("l_add", $l_add);

$template_object->assign("l_main_warpto", $l_main_warpto);
$template_object->assign("linklist", $l_no_warplink);
$template_object->assign("links", $links);
$template_object->assign("links_return", $links_return);
$template_object->assign("l_fullscan", $l_fullscan);
$template_object->assign("l_main_autoroute", $l_main_autoroute);
$template_object->assign("l_realspace", $l_realspace);

if($enable_spiral_galaxy != 1){
	$debug_query = $db->Execute("SELECT sector_id, preset, info, SQRT((($sectorinfo[x]-{$db_prefix}universe.x) * ($sectorinfo[x]-{$db_prefix}universe.x))+(($sectorinfo[y]-{$db_prefix}universe.y) * ($sectorinfo[y]-{$db_prefix}universe.y))+(($sectorinfo[z]-{$db_prefix}universe.z) * ($sectorinfo[z]-{$db_prefix}universe.z))) as distance FROM {$db_prefix}presets, {$db_prefix}universe WHERE {$db_prefix}presets.player_id=$playerinfo[player_id] and {$db_prefix}universe.sector_name ={$db_prefix}presets.preset order by {$db_prefix}presets.info, {$db_prefix}presets.preset");
}
else
{
	$debug_query = $db->Execute("SELECT sector_id, preset, info, SQRT(POW(($sectorinfo[x]-{$db_prefix}universe.x),2)+POW(($sectorinfo[y]-{$db_prefix}universe.y),2)+POW(($sectorinfo[z]-{$db_prefix}universe.z),2)) as distance FROM {$db_prefix}presets, {$db_prefix}universe WHERE {$db_prefix}presets.player_id=$playerinfo[player_id] and {$db_prefix}universe.sector_name ={$db_prefix}presets.preset order by {$db_prefix}presets.info, {$db_prefix}presets.preset");
}

db_op_result($debug_query,__LINE__,__FILE__);
$presettotal = $debug_query->RecordCount();
$total = 0;

while(!$debug_query->EOF){
	$presetinfo[$total] = $debug_query->fields['preset'];
	$presettext[$total] = $debug_query->fields['info'];
	$presetdist[$total] = round(max(1, $debug_query->fields['distance'] / mypw($level_factor, $shipinfo['engines'])));
	$debug_query->MoveNext();
	$total++;
}
$debug_query->close();

$template_object->assign("preset_display", $presetinfo);
$template_object->assign("preset_info", $presettext);
$template_object->assign("preset_dist", $presetdist);

$template_object->assign("shipinfo_sector_id", $shipinfo['sector_id']);

$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
db_op_result($max_query,__LINE__,__FILE__);

$sector_max = $max_query->fields['sector_id'];
$max_query->close();

if($sectorinfo['created_from'] != 0)
{
	$created_from_query = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id=$sectorinfo[created_from]", 1);
	db_op_result($created_from_query,__LINE__,__FILE__);

	$template_object->assign("sg_sector_linkback", $created_from_query->fields['sector_name']);
	$created_from_query->close();
}
else
{
	$template_object->assign("sg_sector_linkback", "");
}

$template_object->assign("sector_max", $sector_max);
$template_object->assign("l_commands", $l_commands);
$template_object->assign("l_none", $l_none);
$template_object->assign("quickshout", $quickshout);
$template_object->assign("shoutboxtitle", "Shout Box");

$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$shipinfo[class]", 1);
db_op_result($debug_query,__LINE__,__FILE__);
$classinfo = $debug_query->fields;
$debug_query->close();

$template_object->assign("classname", $classinfo['name']);
$template_object->assign("maxhull", $classinfo['maxhull']);
$template_object->assign("maxengines", $classinfo['maxengines']);
$template_object->assign("maxpower", $classinfo['maxpower']);
$template_object->assign("maxfighter", $classinfo['maxfighter']);
$template_object->assign("maxsensors", $classinfo['maxsensors']);
$template_object->assign("maxbeams", $classinfo['maxbeams']);
$template_object->assign("maxtorp_launchers", $classinfo['maxtorp_launchers']);
$template_object->assign("maxshields", $classinfo['maxshields']);
$template_object->assign("maxarmor", $classinfo['maxarmor']);
$template_object->assign("maxcloak", $classinfo['maxcloak']);
$template_object->assign("maxecm", $classinfo['maxecm']);

$template_object->assign("shipinfo_hull", $shipinfo['hull']);
$template_object->assign("shipinfo_engines", $shipinfo['engines']);
$template_object->assign("shipinfo_power", $shipinfo['power']);
$template_object->assign("shipinfo_fighter", $shipinfo['fighter']);
$template_object->assign("shipinfo_sensors", $shipinfo['sensors']);
$template_object->assign("shipinfo_beams", $shipinfo['beams']);
$template_object->assign("shipinfo_torp_launchers", $shipinfo['torp_launchers']);
$template_object->assign("shipinfo_armor", $shipinfo['armor']);
$template_object->assign("shipinfo_shields", $shipinfo['shields']);
$template_object->assign("shipinfo_cloak", $shipinfo['cloak']);
$template_object->assign("shipinfo_ecm", $shipinfo['ecm']);

$template_object->assign("shipinfo_dev_minedeflector", NUMBER($shipdevice['dev_minedeflector']['amount']));
$template_object->assign("shipinfo_emerwarp", NUMBER($shipdevice['dev_emerwarp']['amount']));
$template_object->assign("shipinfo_goods", NUMBER($shipinfo['goods']));
$template_object->assign("shipinfo_ore", NUMBER($shipinfo['ore']));
$template_object->assign("shipinfo_organics", NUMBER($shipinfo['organics']));
$template_object->assign("shipinfo_energy", NUMBER($shipinfo['energy']));
$template_object->assign("shipinfo_colonists", NUMBER($shipinfo['colonists']));
$template_object->assign("shipinfo_fighters", NUMBER($shipinfo['fighters']));
$template_object->assign("shipinfo_armor", NUMBER($shipinfo['armor_pts']));
$template_object->assign("shipinfo_torps", NUMBER($shipinfo['torps']));
$template_object->assign("playerinfo_credits", NUMBER($playerinfo['credits']));
$template_object->assign("l_credits", $l_credits);
$template_object->assign("l_cargo", $l_cargo);
$template_object->assign("l_energy", $l_energy);
$template_object->assign("weapons_armor", $l_arm_weap);
$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("l_torps", $l_torps);
$template_object->assign("l_armorpts", $l_armorpts);
$template_object->assign("l_armor", $l_armor);
$template_object->assign("l_logout", $l_logout);

$template_object->assign("l_scan", $l_scan);

$sectorcount = 0;
if($enable_spiral_galaxy != 1){
	$query2 = "SELECT sector_name, source, SQRT((($sectorinfo[x]-{$db_prefix}universe.x) * ($sectorinfo[x]-{$db_prefix}universe.x))+(($sectorinfo[y]-{$db_prefix}universe.y) * ($sectorinfo[y]-{$db_prefix}universe.y))+(($sectorinfo[z]-{$db_prefix}universe.z) * ($sectorinfo[z]-{$db_prefix}universe.z))) as distance FROM {$db_prefix}sector_log, {$db_prefix}universe where {$db_prefix}sector_log.player_id=$playerinfo[player_id] and {$db_prefix}sector_log.destination!=0 and {$db_prefix}universe.sector_id ={$db_prefix}sector_log.source order by {$db_prefix}sector_log.time DESC";
}
else
{
	$query2 = "SELECT sector_name, source, SQRT(POW(($sectorinfo[x]-{$db_prefix}universe.x),2)+POW(($sectorinfo[y]-{$db_prefix}universe.y),2)+POW(($sectorinfo[z]-{$db_prefix}universe.z),2)) as distance FROM {$db_prefix}sector_log, {$db_prefix}universe where {$db_prefix}sector_log.player_id=$playerinfo[player_id] and {$db_prefix}sector_log.destination!=0 and {$db_prefix}universe.sector_id ={$db_prefix}sector_log.source order by {$db_prefix}sector_log.time DESC";
}
$result = $db->SelectLimit ($query2, 5);
db_op_result($res,__LINE__,__FILE__);		 

while(!$result->EOF)
{
	$lastsectors[$sectorcount] = $result->fields['sector_name'];
	$lastsectorsdist[$sectorcount] = round(max(1, $result->fields['distance'] / mypw($level_factor, $shipinfo['engines'])));
	$sectorcount++;
	$result->Movenext();
}
$result->close();
$template_object->assign("lastsectors", $lastsectors);
$template_object->assign("lastsectorsdist", $lastsectorsdist);

$template_object->assign("l_planetmax", $l_planetmax);
$template_object->assign("l_onlinetimeleft", $l_onlinetimeleft);
$template_object->assign("onlinetime_left", $onlinetime_left);
$template_object->assign("spiral_arm", $sectorinfo['spiral_arm']);
$template_object->assign("enable_spiral_galaxy", $enable_spiral_galaxy);
$template_object->assign("templatename", $templatename);

$filelist = get_dirlist($gameroot);
$newcommands = 0;
for ($c=0; $c<count($filelist); $c++) { 
	$filenameroot =  str_replace(".php", "", $filelist[$c]); 
	if(AAT_substr($filelist[$c], 0, 8) == "command_"){
		$fs = fopen($gameroot.$filelist[$c], "r");
		$items = fgets($fs);
		$items = fgets($fs);
		fclose($fs);
		$name = AAT_substr(trim($items), 3);
		$newcommandfull[$newcommands] = "&nbsp;<a class=mnu href=\"$filenameroot.php\">$name</a>&nbsp;";
		$newcommandname[$newcommands] = $name;
		$newcommandlink[$newcommands] = "$filenameroot.php";
		$newcommands++;
	}
}

$template_object->assign("newcommandfull", $newcommandfull);
$template_object->assign("newcommandname", $newcommandname);
$template_object->assign("newcommandlink", $newcommandlink);
$template_object->assign("newcommands", $newcommands);
$template_object->assign("language", $langdir);


?>
