<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the     
// Free Software Foundation; either version 2 of the License, or (at your    
// option) any later version.                                                
// 
// File: translate_news.inc

// newstypes

// general
// bounty
// promoted
// demoted

// indi
// planet
// colonist

// killed
// killedpod
// suicide

// planetattack
// shipattack
// 

function translate_news($entry)
{
	global $langdir;
	include ("languages/$langdir/lang_translate_news.inc");


    switch($entry['news_type'])
    {
        case "creation":
            $retvalue['headline']  = $l_created_universe;
            $retvalue['newstext'] = $l_created_universe_full;
            $retvalue['newstype'] = "general";
        break;

        case "planetXX":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[player]", $playerdatas[0], $l_news_p_headline);
            $retvalue['headline'] = str_replace("[total]", $playerdatas[1], $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $playerdatas[0], $l_news_p_textXX);
            $retvalue['newstext'] = str_replace("[total]", $playerdatas[1],  $retvalue['newstext']);
            $retvalue['newstype'] = "planet";
        break;

        case "planet50":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue['headline'] = str_replace("[total]",'50', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_p_text50);
            $retvalue['newstype'] = "planet";
        break;

        case "planet25":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue['headline'] = str_replace("[total]",'25', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_p_text25);
            $retvalue['newstype'] = "planet";
        break;

        case "planet10":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue['headline'] = str_replace("[total]",'10', $retvalue['headline']);
            $retvalue['newstype'] = "planet";
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_p_text10);
        break;

        case "planet5":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue['headline'] = str_replace("[total]",'5', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_p_text5);
            $retvalue['newstype'] = "planet";
        break;

        case "colXX":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[player]", $playerdatas[0], $l_news_c_headline);
            $retvalue['headline'] = str_replace("[total]", NUMBER($playerdatas[1]), $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $playerdatas[0], $l_news_c_textXX);
            $retvalue['newstext'] = str_replace("[total]", NUMBER($playerdatas[1]),  $retvalue['newstext']);
            $retvalue['newstype'] = "colonist";
        break;

        case "col1000":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue['headline'] = str_replace("[total]", '1,000', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_c_text1000);
            $retvalue['newstype'] = "colonist";
        break;

        case "col500":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue['headline'] = str_replace("[total]", '500', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_c_text500);
            $retvalue['newstype'] = "colonist";
        break;

        case "col100":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue['headline'] = str_replace("[total]", '100', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_c_text100);
            $retvalue['newstype'] = "colonist";
        break;

        case "col25":
            $retvalue['headline'] = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue['headline'] = str_replace("[total]", '25', $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_c_text25);
            $retvalue['newstype'] = "colonist";
        break;

        case "killed":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killed);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedSD":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killSDheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedSD);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedplanet":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killplanetheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedplanet);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedship":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killshipheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedship);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedsuicide":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killsuicideheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedsuicide);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "suicide";
        break;

        case "killedsofa":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killsofaheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedsofa);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killednova":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killnovaheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killednova);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killednovabackfire":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killnovabackfireheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killednovabackfire);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedsectormissile":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killsectormissileheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedsectormissile);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedhunterprobe":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killhunterprobeheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedhunterprobe);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

        case "killedtrapprobe":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killtrapprobeheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedtrapprobe);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killed";
        break;

//------------

        case "killedpod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killpodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedpod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedSDpod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killSDpodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedSDpod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedplanetpod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killplanetpodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedplanetpod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedshippod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killshippodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedshippod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedsofapod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killsofapodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedsofapod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killednovapod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killnovapodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killednovapod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killednovabackfirepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killnovabackfirepodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killednovabackfirepod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedsectormissilepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killsectormissilepodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedsectormissilepod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedhunterprobepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killhunterprobepodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedhunterprobepod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

        case "killedtrapprobepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[target]", $playerdatas[0], $l_killtrapprobepodheadline);
            $data  = str_replace("[target]", $playerdatas[0], $l_news_killedtrapprobepod);
            $retvalue['newstext'] = str_replace("[killer]", $playerdatas[1], $data);
            $retvalue['newstype'] = "killedpod";
        break;

//----------------
        case "indi":
            $retvalue['headline']  = str_replace("[planets]", $entry['data'], $l_news_indi_short);
            $retvalue['newstext'] = str_replace("[planets]", $entry['data'], $l_news_indi);
            $retvalue['newstype'] = "indi";
        break;

        case "nova":
            $retvalue['headline']  = str_replace("[name]", $entry['data'], $l_news_nova_short);
			$total = str_replace("[total]", $entry['total'], $l_news_nova);
			if($entry['total'] == 1)
				$total = str_replace("(s)", "", $total);
			else $total = str_replace("(s)", "s", $total);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $total);
            $retvalue['newstype'] = "planetattack";
        break;

        case "novamiss":
            $retvalue['headline']  = str_replace("[name]", $entry['data'], $l_news_nova_m_short);
			$total = str_replace("[total]", $entry['total'], $l_news_nova_m);
			if($entry['total'] == 1)
				$total = str_replace("(s)", "", $total);
			else $total = str_replace("(s)", "s", $total);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $total);
            $retvalue['newstype'] = "planetattack";
        break;

        case "bounty":
			$playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_bounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $retvalue['headline']  = str_replace("[name2]", $playerdatas[2], $data);
            $retvalue['newstext'] = str_replace("[name2]", $playerdatas[2], $data);
            $retvalue['newstype'] = "bounty";
        break;

        case "pattackerpod":
            $retvalue['headline']  = str_replace("[name]", $entry['data'], $l_news_attackerpod_p_short);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_attackerpod_P);
            $retvalue['newstype'] = "planetattack";
        break;

        case "pattackerdied":
            $retvalue['headline']  = str_replace("[name]", $entry['data'], $l_news_attackerdie_p_short);
            $retvalue['newstext'] = str_replace("[name]", $entry['data'], $l_news_attackerdie_p);
            $retvalue['newstype'] = "planetattack";
        break;

        case "planetdestroyed":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_destroyed_p_short);
            $data = str_replace("[name]", $playerdatas[0], $l_news_destroyed_p);
			$total = str_replace("[total]", $entry['total'], $data);
			if($entry['total'] == 1)
				$total = str_replace("(s)", "", $total);
			else $total = str_replace("(s)", "s", $total);
            $retvalue['newstext'] = str_replace("[owner]", $playerdatas[1], $total);
            $retvalue['newstype'] = "planetattack";
        break;

        case "planetdefeated":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_defeated_p_short);
            $data = str_replace("[name]", $playerdatas[0], $l_news_defeated_p);
			$total = str_replace("[total]", $entry['total'], $data);
			if($entry['total'] == 1)
				$total = str_replace("(s)", "", $total);
			else $total = str_replace("(s)", "s", $total);
            $retvalue['newstext'] = str_replace("[owner]", $playerdatas[1], $total);
            $retvalue['newstype'] = "planetattack";
        break;

        case "planetnotdefeated":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_notdefeated_p_short);
            $data = str_replace("[name]", $playerdatas[0], $l_news_notdefeated_p);
			$total = str_replace("[total]", $entry['total'], $data);
			if($entry['total'] == 1)
				$total = str_replace("(s)", "", $total);
			else $total = str_replace("(s)", "s", $total);
            $retvalue['newstext'] = str_replace("[owner]", $playerdatas[1], $total);
            $retvalue['newstype'] = "planetattack";
        break;

		case "fedcolbounty":
	    $playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_fedcolbounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_fedcolbounty_short);
            $retvalue['newstext'] = $data;
            $retvalue['newstype'] = "bounty";
        break;

		case "alliancecolbounty":
	    $playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_alliancecolbounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_alliancecolbounty_short);
            $retvalue['newstext'] = $data;
            $retvalue['newstype'] = "bounty";
        break;

		case "fedcol_pbounty":
	    $playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_fedcol_pbounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $data  = str_replace("[planetname]", $playerdatas[2], $data);
            $data  = str_replace("[sector]", $playerdatas[3], $data);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_fedcol_pbounty_short);
            $retvalue['newstext'] = $data;
            $retvalue['newstype'] = "bounty";
        break;

		case "alliancecol_pbounty":
	    $playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_alliancecol_pbounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $data  = str_replace("[planetname]", $playerdatas[2], $data);
            $data  = str_replace("[sector]", $playerdatas[3], $data);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_alliancecol_pbounty_short);
            $retvalue['newstext'] = $data;
            $retvalue['newstype'] = "bounty";
        break;

		case "fedcol_sbounty":
	    $playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_fedcol_sbounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $data  = str_replace("[sector]", $playerdatas[3], $data);
            $data  = str_replace("[shiptype]", number($playerdatas[1]), $data);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_fedcol_sbounty_short);
            $retvalue['newstext'] = $data;
            $retvalue['newstype'] = "bounty";
        break;

		case "alliancecol_sbounty":
	    $playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_alliancecol_sbounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $data  = str_replace("[sector]", $playerdatas[3], $data);
            $data  = str_replace("[shiptype]", number($playerdatas[1]), $data);
            $retvalue['headline']  = str_replace("[name]", $playerdatas[0], $l_news_alliancecol_sbounty_short);
            $retvalue['newstext'] = $data;
            $retvalue['newstype'] = "bounty";
        break;

        case "targetepod":
			$playerdatas = explode("|", $entry['data']);
            $data = str_replace("[name]", $playerdatas[0], $l_news_targetepod_short);
            $retvalue['headline']  = str_replace("[owner]", $playerdatas[1], $data);
            $data = str_replace("[name]", $playerdatas[0], $l_news_targetepod);
            $retvalue['newstext'] = str_replace("[owner]", $playerdatas[1], $data);
            $retvalue['newstype'] = "shipattack";
        break;

        case "targetdies":
			$playerdatas = explode("|", $entry['data']);
            $data = str_replace("[name]", $playerdatas[0], $l_news_targetdies_short);
            $retvalue['headline']  = str_replace("[owner]", $playerdatas[1], $data);
            $data = str_replace("[name]", $playerdatas[0], $l_news_targetdies);
            $retvalue['newstext'] = str_replace("[owner]", $playerdatas[1], $data);
            $retvalue['newstype'] = "shipattack";
        break;

        case "promoted":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[name]", $playerdatas[0], $l_news_promotedheadline);
            $retvalue['headline'] = str_replace("[rank]", $playerdatas[1], $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $playerdatas[0], $l_news_promoted);
            $retvalue['newstext'] = str_replace("[rank]", $playerdatas[1],  $retvalue['newstext']);
            $retvalue['newstype'] = "promoted";
        break;

        case "demoted":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[name]", $playerdatas[0], $l_news_demotedheadline);
            $retvalue['headline'] = str_replace("[rank]", $playerdatas[1], $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[name]", $playerdatas[0], $l_news_demoted);
            $retvalue['newstext'] = str_replace("[rank]", $playerdatas[1],  $retvalue['newstext']);
            $retvalue['newstype'] = "demoted";
        break;

        case "namechange":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[oldname]", $playerdatas[0], $l_news_namechangedheadline);
            $retvalue['headline'] = str_replace("[newname]", $playerdatas[1], $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[oldname]", $playerdatas[0], $l_news_namechanged);
            $retvalue['newstext'] = str_replace("[newname]", $playerdatas[1],  $retvalue['newstext']);
            $retvalue['newstype'] = "general";
        break;


        case "found_planets":
            $retvalue['headline']  = str_replace("[found_planets]", $entry['data'], $l_news_found_planets_short);
            $retvalue['newstext'] = str_replace("[found_planets]", $entry['data'], $l_news_found_planets);
            $retvalue['newstype'] = "found_planets";
        break;

        case "new_ports":
            $retvalue['headline']  = str_replace("[new_ports]", $entry['data'], $l_news_new_ports_short);
            $retvalue['newstext'] = str_replace("[new_ports]", $entry['data'], $l_news_new_ports);
            $retvalue['newstype'] = "new_ports";
        break;

        case "addedsectors":
            $retvalue['headline']  = str_replace("[addedsectors]", $entry['data'], $l_news_addedsectors_short);
            $retvalue['newstext'] = str_replace("[addedsectors]", $entry['data'], $l_news_addedsectors);
            $retvalue['newstype'] = "addedsectors";
        break;

        case "artifact":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[artifact]", $playerdatas[0], $l_news_artifactheadline);
            $retvalue['headline'] = str_replace("[playername]", $playerdatas[1], $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[artifact]", $playerdatas[0], $l_news_artifact);
            $retvalue['newstext'] = str_replace("[playername]", $playerdatas[1],  $retvalue['newstext']);
            $retvalue['newstype'] = "general";
        break;

        case "artifactfound":
			$playerdatas = explode("|", $entry['data']);
            $retvalue['headline'] = str_replace("[artifact]", $playerdatas[0], $l_news_artifactfoundheadline);
            $retvalue['headline'] = str_replace("[playername]", $playerdatas[1], $retvalue['headline']);
            $retvalue['newstext'] = str_replace("[artifact]", $playerdatas[0], $l_news_artifactfound);
            $retvalue['newstext'] = str_replace("[playername]", $playerdatas[1],  $retvalue['newstext']);
            $retvalue['newstext'] = str_replace("[pieces]", $playerdatas[2],  $retvalue['newstext']);
            $retvalue['newstext'] = str_replace("[piece]", $playerdatas[3],  $retvalue['newstext']);
            $retvalue['newstype'] = "general";
        break;

    }

    return $retvalue;
}
?>
