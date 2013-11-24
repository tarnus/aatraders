<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the     
// Free Software Foundation; either version 2 of the License, or (at your    
// option) any later version.                                                
// 
// File: lrscan.php

include ("config/config.php");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_lrscan.inc");
include ("languages/$langdir/lang_sector_notes.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/ship_bounty_check.inc");
include ("globals/log_scan.inc");
include ("globals/get_shipclassname.inc");
include ("globals/get_player.inc");
include ("globals/scanlevel.inc");
include ("globals/last_ship_seen.inc");
include ("globals/display_this_planet.inc");
include ("globals/device_ship_tech_modify.inc");
$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

get_post_ifset("command, game_number, ajax");

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

if($ajax != 1)
{
    include ("header.php");
}
else
{

    $template_object->assign("templatename", $templatename);
    $template_object->assign("full_url", "http://" . $gameurl . $gamepath . ($gamepath == "/" ? "" : "/") );

    $template_object->assign("player_id", $playerinfo['player_id']);
    $template_object->assign("gameroot", $gameroot);

    function insert_img($params, &$tpl) {

        $class = (isset($params['class']) ? " class=\"iehax " . $params['class'] . "\" " : " class=\"iehax\" ");
        $id    = (isset($params['id']) ? " id=\"" . $params['id'] . "\" " : "");
        $style = (isset($params['style']) ? " style=\"" . $params['style'] . "\" " : " ");
        $border = (isset($params['border']) ? $params['border'] : 0);
        $alt = (isset($params['alt']) ? $params['alt'] : "image");

        static $firsttime = 0;

        $str = '';
        if($firsttime == 0)
        {
            $firsttime = 1;
            $str = '
<style type="text/css">
<!--
    span.iehax { display: none; }
    img.iehaxblank { display: none; }
-->
</style>
<!--[if IE]>
    <style type="text/css">
    <!--
        img.iehaxblank { display: inline ! important }
        img.iehaximg { display: none ! important }
    -->
    </style>
<![endif]-->
        ';
        }

        $str .= '
<!--[if IE]>
    <span ' . $id . $class . '
        style="height: ' . $params['height'] . 'px; 
            width: ' . $params['width'] . 'px; 
            filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(src=\'' .
                $params['src'] . '\',sizingMethod=\'scale\'); 
            display:inline; position:absolute; ">
    </span>
<![endif]-->
<img class="iehaxblank" width="' . $params['width'] . '" height="' . $params['height'] . '" 
    src="images/spacer.gif" alt="."  border="' . $border . '"/>
<img class="iehaximg" src="' . $params['src'] . '" alt="' . $params['alt'] . '" 
    width="' . $params['width'] . '" height="' . $params['height'] . '" border="' . $border . '"/>';

        return $str;
    }
}

$template_object->assign("title", $l_lrs_title);
$template_object->assign("ajax", $ajax);

$sector = urldecode($_GET['sector']);

if ((!isset($sector)) || ($sector == ''))
{
    $sector = '';
}

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

    // get scanned sector information
    $result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sector), 1);
    $query96 = $result2->fields;

    // get sectors which can be reached through scanned sector
    $result3 = $db->Execute("SELECT sector_name FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$query96[sector_id]' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");

    $i=0;

    if ($result3 > 0)
    {
        while (!$result3->EOF)
        {
            $links[$i] = $result3->fields['sector_name'];
            $i++;
            $result3->MoveNext();
        }
    }
    $num_links=$i;

    // get sectors which can be reached from the player's current sector
    $result3a = $db->Execute("SELECT sector_name FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$shipinfo[sector_id]' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");

    $i=0;
    $flag=0;

    if ($result3a > 0)
    {
        while (!$result3a->EOF)
        {
            if ($result3a->fields['sector_name'] == $sector)
            {
                $flag=1;
            }
           $i++;
           $result3a->MoveNext();
        }
    }

    if ($flag == 0)
    {
        $template_object->assign("error_msg", $l_lrs_cantscan);
        $template_object->assign("error_msg2", "");
        $template_object->assign("gotomain", $l_global_mmenu);
        $template_object->display($templatename."genericdie.tpl");
        include ("footer.php");
        die();
    }

    log_scan($playerinfo['player_id'], $query96['sector_id'], $query96['zone_id']);

$template_object->assign("color_header", $color_header);
$template_object->assign("l_sector", $l_sector);
$template_object->assign("sector", $sector);
$template_object->assign("l_links", $l_links);

$template_object->assign("title", $l_lrs_title);

    if ($num_links == 0)
    {
        $link_list = $l_none;
    }
    else
    {
        for($i = 0; $i < $num_links; $i++)
        {
            $link_list .= $links[$i];
            if ($i + 1 != $num_links)
            {
                $link_list .= ", ";
            }
        }
    }

$template_object->assign("link_list", $link_list);
$template_object->assign("l_ships", $l_ships);
$template_object->assign("l_none", $l_none);
$template_object->assign("l_lrs_zero", $l_lrs_zero);
$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_lrs_sectormissile_question", $l_lrs_sectormissile_question);

$ship_name = array();
$player_name = array();
$ship_id = array();
$ship_bounty = array();
$num_detected = 0;

$nameresult = $db->Execute("SELECT sector_id, zone_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sector));
//$sector = $nameresult->fields['sector_id'];
$sectornum = $nameresult->fields['sector_id'];    
$sector_zone = $nameresult->fields['zone_id'];    
$template_object->assign("sectornum", $sectornum);
$template_object->assign("sector_zone", $sector_zone);
$template_object->assign("sector_missile", $shipdevice['dev_sectormissile']['amount']);
    if ($sectornum != 1)
    {
        // get ships located in the scanned sector

    $result4 = $db->Execute(" SELECT DISTINCT
                              {$db_prefix}ships.*,
                              {$db_prefix}players.*,
                              {$db_prefix}teams.team_name,
                              {$db_prefix}teams.id
                              FROM {$db_prefix}ships
                              LEFT JOIN {$db_prefix}players ON {$db_prefix}ships.player_id={$db_prefix}players.player_id
                              LEFT JOIN {$db_prefix}teams
                              ON {$db_prefix}players.team = {$db_prefix}teams.id
                              WHERE {$db_prefix}ships.player_id<>$playerinfo[player_id]
                              AND {$db_prefix}ships.sector_id=$query96[sector_id]
                              AND {$db_prefix}ships.on_planet='N' AND  {$db_prefix}players.currentship={$db_prefix}ships.ship_id");

        if (!$result4->EOF)
        {
            $num_detected = 0;
            while (!$result4->EOF)
            {
                $row = $result4->fields;
                // display other ships in sector - unless they are successfully cloaked
                $success = SCAN_SUCCESS($shipinfo['sensors'], $row['cloak'], $shiptypes[$row['class']]['basehull']);

                $roll = mt_rand(1, 100);
                if ($roll < $success)
                {
                    $num_detected++;
                    $ship_name[] = $row['name'];
                    $player_name[] = $row['character_name'];
                    $ship_id[] = $row['ship_id'];
                    $result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=" . $row['player_id'], 1);
                    $ownerinfo = $result3->fields;
                    $ship_bounty[] = ship_bounty_check($playerinfo, $query96['sector_id'], $ownerinfo, 0);

                    $rating = good_neutral_evil($row['rating']);
                    $shiprating[] = $rating[1];
                    $shipratingnumber[] = $rating[0];

                }
                $result4->MoveNext();
            }
        }
    }

$template_object->assign("shiprating", $shiprating);
$template_object->assign("shipratingnumber", $shipratingnumber);

$template_object->assign("ship_bounty", $ship_bounty);
$template_object->assign("ship_name", $ship_name);
$template_object->assign("player_name", $player_name);
$template_object->assign("ship_id", $ship_id);
$template_object->assign("num_detected", $num_detected);
$template_object->assign("l_port", $l_port);

  
    if ($query96['port_type'] == "none")
    {
        $port_type = "none";
        $icon_alt_text = ucfirst($l_none);
        $icon_port_type_name = $port_type;
    }
    else
    {
        $port_type = $query96['port_type'];
        $icon_alt_text = ucfirst($port_type);
        $icon_port_type_name = $port_type;
    }
$template_object->assign("port_type", $port_type);
$template_object->assign("icon_alt_text", $icon_alt_text);
$template_object->assign("icon_port_type_name", $icon_port_type_name);

$template_object->assign("l_planets", $l_planets);

    $res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE sector_id='$query96[sector_id]'", 5);

    $countplanet = 0;
    $planetsfound = 0;
    while (!$res->EOF)
    {
        $uber = 0;
        $success = 0;
        $hiding_planet[$i] = $res->fields;

        if ($hiding_planet[$i]['owner'] == $playerinfo['player_id'])
        {
            $uber = 1;
        }

        if ($hiding_planet[$i]['team'] != 0)
        {
            if ($hiding_planet[$i]['team'] == $playerinfo['team'])
            {
                $uber = 1;
            }
        }

        if ($shipinfo['sensors'] >= $hiding_planet[$i]['cloak'])
        {
            $uber = 1;
        }

        if ($uber == 0) //Not yet 'visible'
        {
            $success = SCAN_SUCCESS($shipinfo['sensors'], $hiding_planet[$i]['cloak']);

            $roll = mt_rand(1, 100);
            if ($roll <= $success) // If able to see the planet
            {
                $uber = 1; //confirmed working
            }

            if ($uber == 0 && $enable_spies)  // Still not yet 'visible'
            {
                $res_s = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE planet_id = '" . $hiding_planet[$i]['planet_id'] . "' AND owner_id = '$playerinfo[player_id]'");
                if ($res_s->RecordCount())
                {
                    $uber = 1;
                }
            }
        }

        if ($uber == 1)
        {
            $planets[$i] = $res->fields;
            display_this_planet($planets[$i]);
            $result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=" . $planets[$i]['owner'], 1);
            $ownerinfo = $result3->fields;
            $result3->close();
            $isfedbounty = planet_bounty_check($playerinfo, $query96['sector_id'], $ownerinfo, 0);
            $display_count = $countplanet - 1;
//            echo "<td align=center valign=top>";
//            if($isfedbounty > 0)
//            {
//                echo $l_by_fedbounty . "</br>";
//            }
//            echo "<A HREF=planet.php?planet_id=" . $planetid[$display_count] . ">";
//            echo "<img src=\"templates/" . $templatename . "images/planet" . $planetimg[$display_count] . ".png\" border=0></a><BR><font size=2 color=\"white\" face=\"arial\">";
//            echo $planetname[$display_count];
//            echo "<br>($planetowner[$display_count])";
//            echo "</font></td>";
            $planetbounty[$display_count] = $isfedbounty;
            $planetsfound++;
        }
        $i++;
        $res->MoveNext();
    }

    if ($planetsfound == 0)
    {
        $countplanet = 0;
//        echo "<td>";
//        echo "$l_none";
//        echo "</td>";
    }

$template_object->assign("l_by_bountyscan", $l_by_bountyscan);
$template_object->assign("planetsfound", $planetsfound);
$template_object->assign("countplanet", $countplanet);
$template_object->assign("planetid", $planetid);
$template_object->assign("planetimg", $planetimg);
$template_object->assign("planetname", $planetname);
$template_object->assign("planetowner", $planetowner);
$template_object->assign("planetbounty", $planetbounty);
$template_object->assign("planetrating", $planetrating);
$template_object->assign("planetratingnumber", $planetratingnumber);

    $resultSDa = $db->Execute("SELECT * from {$db_prefix}sector_defense WHERE sector_id='$query96[sector_id]' and defense_type='mines'");
    $resultSDb = $db->Execute("SELECT * from {$db_prefix}sector_defense WHERE sector_id='$query96[sector_id]' and defense_type='fighters'");
    //==================================================================
    $fighter_owner = array();
    $fighter_bounty = array();
    $fighter_amount = array();
    $has_fighters = 0;
    $highjammer=0;
    if ($resultSDb > 0)
    {
        while (!$resultSDb->EOF)
        {
            $fm_owner = $resultSDb->fields['player_id'];
            $result_fo = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$fm_owner", 1);
            $fighters_owner = $result_fo->fields;
            $result3 = $db->SelectLimit("SELECT * from {$db_prefix}ships where player_id=$fighters_owner[player_id] and ship_id=$fighters_owner[currentship]", 1);
            db_op_result($result3,__LINE__,__FILE__);
            $ship_owner = $result3->fields;

            // get planet sensors
            $result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$sectornum' order by sector_defense_cloak DESC", 1);
            db_op_result($result4,__LINE__,__FILE__);
            $planets = $result4->fields;
            if ($highcloak < $planets['sector_defense_cloak']){
                $highcloak=$planets['sector_defense_cloak'];
            }
            $result4 = $db->SelectLimit("SELECT jammer from {$db_prefix}planets where (owner=$fm_owner or  (team > 0 and team=$fighters_owner[team])) and base='Y' and sector_id='$sectornum' order by jammer DESC", 1);
            db_op_result($result4,__LINE__,__FILE__);
            $planets = $result4->fields;
            if ($highjammer < $planets['jammer']){
                $highjammer=$planets['jammer'];
            }

            $success = SCAN_SUCCESS($shipinfo['sensors'], $highcloak);

            $roll = mt_rand(1, 100);
            if ($roll < $success)
            {
                $fighters = $resultSDb->fields['quantity'];
                $planet_comp_level = SCAN_ERROR($shipinfo['sensors'], $highjammer, $fighters);

                if ($planet_comp_level > $fighters)
                {
                    $planetfighters = $fighters;
                }
                else
                {
                    $planetfighters = $planet_comp_level;
                }

                $result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=" . $fm_owner, 1);
                $ownerinfo = $result3->fields;
                $result3->close();
                $isfedbounty = planet_bounty_check($playerinfo, $query96['sector_id'], $ownerinfo, 0);

                if($planetfighters > 0)
                {
                    $fighter_amount[] = NUMBER($planetfighters);
                    $fighter_owner[] = $ownerinfo['character_name'];
                    $fighter_bounty[] = $isfedbounty;
                    $has_fighters += $planetfighters;
                }
            }
            $resultSDb->MoveNext();
        }
    }
    //=========================================================================
    //==================================================================
    $has_mines = 0;
    $mines_owner = array();
    $mines_bounty = array();
    $mines_amount = array();
    $highjammer=0;
    if ($resultSDa > 0)
    {
        while (!$resultSDa->EOF)
        {
            $mn_owner = $resultSDa->fields['player_id'];
            $result_mn = $db->SelectLimit("SELECT * from {$db_prefix}players where player_id=$mn_owner", 1);
            $mine_owner = $result_mn->fields;
            $result3 = $db->SelectLimit("SELECT * from {$db_prefix}ships where player_id=$mine_owner[player_id] and ship_id=$mine_owner[currentship]", 1);
            db_op_result($result3,__LINE__,__FILE__);
            $ship_owner = $result3->fields;

            // get planet sensors
            $result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner=$mn_owner or  (team > 0 and team=$mine_owner[team])) and base='Y' and sector_id='$sectornum' order by sector_defense_cloak DESC", 1);
            db_op_result($result4,__LINE__,__FILE__);
            $planets = $result4->fields;
            if ($highcloak < $planets['sector_defense_cloak']){
                $highcloak=$planets['sector_defense_cloak'];
            }
            $result4 = $db->SelectLimit("SELECT jammer from {$db_prefix}planets where (owner=$mn_owner or  (team > 0 and team=$mine_owner[team])) and base='Y' and sector_id='$sectornum' order by jammer DESC", 1);
            db_op_result($result4,__LINE__,__FILE__);
            $planets = $result4->fields;
            if ($highjammer < $planets['jammer']){
                $highjammer=$planets['jammer'];
            }

            $success = SCAN_SUCCESS($shipinfo['sensors'], $highcloak);

            $roll = mt_rand(1, 100);
            if ($roll < $success)
            {
                $mines = $resultSDa->fields['quantity'];
                $planet_comp_level = SCAN_ERROR($shipinfo['sensors'], $highjammer, $mines);

                if ($planet_comp_level > $mines)
                {
                    $planetmines = $mines;
                }
                else
                {
                    $planetmines = $planet_comp_level;
                }

                $result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=" . $mn_owner, 1);
                $ownerinfo = $result3->fields;
                $result3->close();
                $isfedbounty = planet_bounty_check($playerinfo, $query96['sector_id'], $ownerinfo, 0);

                if($planetmines > 0)
                {
                    $mines_amount[] = NUMBER($planetmines);
                    $mines_owner[] = $ownerinfo['character_name'];
                    $mines_bounty[] = $isfedbounty;
                    $has_mines += $planetmines;
                }
            }
            $resultSDa->MoveNext();
        }
    }
    //=========================================================================

$template_object->assign("l_mines", $l_mines);
$template_object->assign("mines_owner", $mines_owner);
$template_object->assign("mines_amount", $mines_amount);
$template_object->assign("mines_bounty", $mines_bounty);
$template_object->assign("mines_count", count($mines_owner));


$template_object->assign("l_fighters", $l_fighters);
$template_object->assign("fighter_owner", $fighter_owner);
$template_object->assign("fighter_amount", $fighter_amount);
$template_object->assign("fighter_bounty", $fighter_bounty);
$template_object->assign("mines_count", count($fighter_owner));

$lss_info = last_ship_seen($sectornum, $playerinfo['player_id'], $shipinfo['sensors']);
$template_object->assign("l_lss", $l_lss);
$template_object->assign("lss_info", $lss_info);
$template_object->assign("l_lrs_moveto", $l_lrs_moveto);


$template_object->assign("l_sn_addnote", $l_sn_addnote);
$template_object->assign("sectornumber", $sectornum);
$template_object->assign("l_sn_hdscanfrom", $l_sn_hdscanfrom);
$template_object->assign("l_sn_hdtype", $l_sn_hdtype);
$template_object->assign("l_sn_hdowner", $l_sn_hdowner);
$template_object->assign("l_sn_hdplanets", $l_sn_hdplanets);
$template_object->assign("l_sn_hdport", $l_sn_hdport);
$template_object->assign("l_sn_hdfighters", $l_sn_hdfighters);
$template_object->assign("l_sn_hdmines", $l_sn_hdmines);
$template_object->assign("l_sn_hdteam", $l_sn_hdteam);

$template_object->assign("has_fighters", $has_fighters);
$template_object->assign("has_mines", $has_mines);
$template_object->assign("team_note", $playerinfo['team']);
$template_object->assign("l_sn_hddetail", $l_sn_hddetail);
$template_object->assign("l_sn_addnote", $l_sn_addnote);
$template_object->assign("l_sn_hddelete", $l_sn_hddelete);

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$shipinfo[sector_id]'", 1);
$scanfromname = $result2->fields['sector_name'];
$template_object->assign("scanfromname", $scanfromname);


// get sector notes
if ($playerinfo['team']==0){
    $result = $db->Execute("SELECT * FROM {$db_prefix}sector_notes where ( note_sector_id=$shipinfo[sector_id] or note_scanfrom=$shipinfo[sector_id]) and ( note_player_id=$playerinfo[player_id] )");
}else{
    $result = $db->Execute("SELECT * FROM {$db_prefix}sector_notes where ( note_sector_id=$shipinfo[sector_id] or note_scanfrom=$shipinfo[sector_id]) and ( note_player_id=$playerinfo[player_id] or  note_team_id=$playerinfo[team])");
}

if ($result->RecordCount() > 0){
    $notelistcount=0;
    while (!$result->EOF && $result) 
    {
        $row = $result->fields;

        $notelistid[$notelistcount] = $result->fields['note_id'];
        $notelistnote[$notelistcount] = $result->fields['note_data'];
        $notelistdate[$notelistcount] = $result->fields['note_date'];
        $note_player_id[$notelistcount] = $result->fields['note_player_id'];
        $notes_team[$notelistcount] = $result->fields['note_team_id'];
        $sector_type[$notelistcount] = $result->fields['note_stype'];
        if ($sector_type[$notelistcount]==""){
            $sector_type[$notelistcount]="N/A";
        }
        $sectorlist[$notelistcount] = $result->fields['note_sector_id'];
        $result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$sectorlist[$notelistcount]'",1);
        $sectorlist[$notelistcount] = $result2->fields['sector_name'];
        $sector_owner[$notelistcount] = $result->fields['note_sowner'];
        $sector_planets[$notelistcount] = $result->fields['note_splanets'];
        $sector_port[$notelistcount] = $result->fields['note_sport'];
        $sector_fighters[$notelistcount] = NUMBER($result->fields['note_sfighters']);
        $sector_mines[$notelistcount] = NUMBER($result->fields['note_storps']);
        $sector_scanfrom[$notelistcount] = $result->fields['note_scanfrom'];
        $result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$sector_scanfrom[$notelistcount]'", 1);
        $sector_scanfrom[$notelistcount] = $result2->fields['sector_name'];

        $notelistcount++;
        $result->MoveNext();
    }
    $template_object->assign("notelistcount", $notelistcount);
    $template_object->assign("notelistid", $notelistid);
    $template_object->assign("notelistnote", $notelistnote);
    $template_object->assign("notelistdate", $notelistdate);
    $template_object->assign("note_player_id", $note_player_id);
    $template_object->assign("notes_team", $notes_team);
    $template_object->assign("sector_type", $sector_type);
    $template_object->assign("sectorlist", $sectorlist);
    $template_object->assign("sector_owner", $sector_owner);
    $template_object->assign("sector_planets", $sector_planets);
    $template_object->assign("sector_port", $sector_port);
    $template_object->assign("sector_fighters", $sector_fighters);
    $template_object->assign("sector_mines", $sector_mines);
    $template_object->assign("sector_scanfrom", $sector_scanfrom);

    $template_object->assign("player_id", $playerinfo['player_id']);
    $template_object->assign("l_sn_yes", $l_sn_yes);
    $template_object->assign("l_sn_no", $l_sn_no);
    $template_object->assign("l_sn_delete", $l_sn_delete);
    $template_object->assign("l_sn_view", $l_sn_view);
}

$template_object->assign("l_lrs_click", $l_lrs_click);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."sector_scan.tpl");

if($ajax != 1)
{
    include ("footer.php");
}
else
{
    unset($_SESSION['currentprogram'], $currentprogram);
    unset ($template_object);
}
?>
