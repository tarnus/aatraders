<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the     
// Free Software Foundation; either version 2 of the License, or (at your    
// option) any later version.                                                
// 
// File: translate_news_headline.inc


function translate_news_headline($entry)
{
	global $langdir;
	include ("languages/$langdir/lang_translate_news.inc");

	$entry['data'] = str_replace("\\", "", $entry['data']);

    switch($entry['news_type'])
    {
        case "creation":
            $retvalue = $l_created_universe;
        break;

        case "planetXX":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[player]", $playerdatas[0], $l_news_p_headline);
            $retvalue = str_replace("[total]", $playerdatas[1], $retvalue);
        break;

        case "planet50":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue = str_replace("[total]",'50', $retvalue);
        break;

        case "planet25":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue = str_replace("[total]",'25', $retvalue);
        break;

        case "planet10":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue = str_replace("[total]",'10', $retvalue);
        break;
            
        case "planet5":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_p_headline);
            $retvalue = str_replace("[total]",'5', $retvalue);
        break;

        case "colXX":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[player]", $playerdatas[0], $l_news_c_headline);
            $retvalue = str_replace("[total]", NUMBER($playerdatas[1]), $retvalue);
        break;

        case "col1000":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue = str_replace("[total]", '1,000', $retvalue);
        break;

        case "col500":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue = str_replace("[total]", '500', $retvalue);
        break;

        case "col100":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue = str_replace("[total]", '100', $retvalue);
        break;

        case "col25":
            $retvalue = str_replace("[player]", $entry['data'], $l_news_c_headline);
            $retvalue = str_replace("[total]", '25', $retvalue);
        break;

        case "killed":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killheadline);
        break;

        case "killedSD":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killSDheadline);
        break;

        case "killedplanet":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killplanetheadline);
        break;

        case "killedship":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killshipheadline);
        break;

        case "killedsuicide":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killsuicideheadline);
        break;

        case "killedsofa":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killsofaheadline);
        break;

        case "killednova":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killnovaheadline);
        break;

        case "killednovabackfire":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killnovabackfireheadline);
        break;

        case "killedsectormissile":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killsectormissileheadline);
        break;

        case "killedhunterprobe":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killhunterprobeheadline);
        break;

        case "killedtrapprobe":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killtrapprobeheadline);
        break;

//------------

        case "killedpod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killpodheadline);
        break;

        case "killedSDpod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killSDpodheadline);
        break;

        case "killedplanetpod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killplanetpodheadline);
        break;

        case "killedshippod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killshippodheadline);
        break;

        case "killedsofapod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killsofapodheadline);
        break;

        case "killednovapod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killnovapodheadline);
        break;

        case "killednovabackfirepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killnovabackfirepodheadline);
        break;

        case "killedsectormissilepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killedsectormissilepod);
        break;

        case "killedhunterprobepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killedhunterprobepod);
        break;

        case "killedtrapprobepod":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[target]", $playerdatas[0], $l_killedtrapprobepod);
        break;

//----------------

        case "indi":
            $retvalue = str_replace("[planets]", $entry['data'], $l_news_indi_short);
        break;

        case "nova":
            $retvalue = str_replace("[name]", $entry['data'], $l_news_nova_short);
        break;

        case "novamiss":
            $retvalue = str_replace("[name]", $entry['data'], $l_news_nova_m_short);
        break;

        case "bounty":
			$playerdatas = explode("|", $entry['data']);
            $data  = str_replace("[name]", $playerdatas[0], $l_news_bounty);
            $data  = str_replace("[amount]", number($playerdatas[1]), $data);
            $retvalue = str_replace("[name2]", $playerdatas[2], $data);
        break;

        case "pattackerpod":
            $retvalue = str_replace("[name]", $entry['data'], $l_news_attackerpod_p_short);
        break;

        case "pattackerdied":
            $retvalue = str_replace("[name]", $entry['data'], $l_news_attackerdie_p_short);
        break;

        case "planetdestroyed":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_destroyed_p_short);
        break;

        case "planetdefeated":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_defeated_p_short);
        break;

        case "planetnotdefeated":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_notdefeated_p_short);
        break;
		case "fedcolbounty":
		    $playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_fedcolbounty_short);
        break;
		case "alliancecolbounty":
		    $playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_alliancecolbounty_short);
        break;
		case "fedcol_pbounty":
		    $playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_fedcol_pbounty_short);
        break;
		case "alliancecol_pbounty":
		    $playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_alliancecol_pbounty_short);
        break;
		case "fedcol_sbounty":
		    $playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_fedcol_sbounty_short);
        break;
		case "alliancecol_sbounty":
		    $playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_alliancecol_sbounty_short);
        break;
        case "targetepod":
			$playerdatas = explode("|", $entry['data']);
            $data = str_replace("[name]", $playerdatas[0], $l_news_targetepod_short);
            $retvalue = str_replace("[owner]", $playerdatas[1], $data);
        break;

        case "targetdies":
			$playerdatas = explode("|", $entry['data']);
            $data = str_replace("[name]", $playerdatas[0], $l_news_targetdies_short);
            $retvalue = str_replace("[owner]", $playerdatas[1], $data);
        break;
        
        case "promoted":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_promotedheadline);
            $retvalue = str_replace("[rank]", $playerdatas[1], $retvalue);
        break;

        case "demoted":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[name]", $playerdatas[0], $l_news_demotedheadline);
            $retvalue = str_replace("[rank]", $playerdatas[1], $retvalue);
        break;

        case "namechange":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[oldname]", $playerdatas[0], $l_news_namechangedheadline);
            $retvalue = str_replace("[newname]", $playerdatas[1], $retvalue);
         break;


        case "found_planets":
            $retvalue = str_replace("[found_planets]", $entry['data'], $l_news_found_planets_short);
        break;

        case "new_ports":
            $retvalue = str_replace("[new_ports]", $entry['data'], $l_news_new_ports_short);
        break;

        case "addedsectors":
            $retvalue = str_replace("[addedsectors]", $entry['data'], $l_news_addedsectors_short);
        break;

        case "artifact":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[artifact]", $playerdatas[0], $l_news_artifactheadline);
            $retvalue = str_replace("[playername]", $playerdatas[1], $retvalue);
         break;

        case "artifactfound":
			$playerdatas = explode("|", $entry['data']);
            $retvalue = str_replace("[artifact]", $playerdatas[0], $l_news_artifactfoundheadline);
            $retvalue = str_replace("[playername]", $playerdatas[1], $retvalue);
         break;

    }

    return $retvalue;
}
?>
