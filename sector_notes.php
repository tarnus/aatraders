<?php
// Sector Notes

include ("config/config.php");
include("languages/$langdir/lang_sector_notes.inc");

get_post_ifset("sector, command, limit, sectornum, note_id, scanfrom, stype, owner, planets, port, fighters, torps, team, note, type, search, Del, sort");

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

function addnumcheck($var1){
$addcheck=AAT_strtolower(AAT_substr($var1,-1));
	switch ($addcheck) {
		case "k":
			$var1=AAT_substr($var1,0,-1)."000";
			return $var1;
			break;
	  case "m":
	  	$var1=AAT_substr($var1,0,-1)."000000";
	  	return $var1;
			break;
		case "b":
	  	$var1=AAT_substr($var1,0,-1)."000000000";
	  	return $var1;
			break;
		case "t":
	  	$var1=AAT_substr($var1,0,-1)."000000000000";
	  	return $var1;
			break;
		case "q":
	  	$var1=AAT_substr($var1,0,-1)."000000000000000";
	  	return $var1;
			break;
		default:
		return $var1;
		break;	
	}
}

	if ($command==$l_sn_view){
		$vnote_sector_name=$sector;
		$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($vnote_sector_name), 1);
		$vsector_id = $result2->fields['sector_id'];
		
	}

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sectornum), 1);

$sectorname=$sector;
$sector = $result2->fields['sector_id'];


$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sectornum), 1);
$sectornumname=$sectornum;
$sectornum = $result2->fields['sector_id'];
$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($scanfrom), 1);
$scanfromname=$scanfrom;
$scanfrom = $result2->fields['sector_id'];
$title = "$l_sn_title $sectorid";

$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}universe WHERE sector_id='$shipinfo[sector_id]'", 1);
$shipinfosector = $result2->fields['sector_name'];


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

$time = date("Y-m-d H:i:s");

if ($limit==1){
	$limit_sectors=1;
}

if (isset($_POST["Del"]))
{
	for ($i = 0; $i < count($Del); $i++)
	{
		$get_planetinfo = $db->Execute("delete from {$db_prefix}sector_notes WHERE  note_id =$Del[$i] and note_player_id =$playerinfo[player_id]");
	}
}

if ($command==$l_sn_editnote )
{
	if (isset($team)){
		$team=$playerinfo['team'];
	}else{
		$team=0;
	}

	$fighters=str_replace(",","",$fighters);
	$fighters= addnumcheck($fighters);
	$mines=str_replace(",","",$mines);
	$mines= addnumcheck($mines);
	 
	$xsql = "UPDATE {$db_prefix}sector_notes SET note_data=" . $db->qstr($note) . ",
	note_date='$time'
	,note_team_id='$team'
	,note_stype='$stype'
	,note_sector_id='$sectornum'
	,note_sowner=" . $db->qstr($owner) . "
	,note_splanets='$planets'
	,note_sport=" . $db->qstr($port) . "
	,note_sfighters='$fighters'
	,note_storps='$mines'
	,note_scanfrom='$scanfrom'

	 WHERE note_id='$note_id'";
	$debug_query = $db->Execute($xsql);
	echo $sql;
	db_op_result($debug_query,__LINE__,__FILE__);
}

if($command == $l_sn_addnote ){
	if (isset($team)){
		$team=$playerinfo['team'];
	}else{
		$team=0;
	}

	$limit_sectors=1;
	$fighters=str_replace(",","",$fighters);
	$fighters= addnumcheck($fighters);
	$mines=str_replace(",","",$mines);
	$mines= addnumcheck($mines);
	
	$xsql = "insert into {$db_prefix}sector_notes (note_player_id, note_data,note_date,note_team_id,note_stype,note_sector_id,note_sector_name,note_sowner,note_splanets,note_sport,note_sfighters,note_storps,note_scanfrom,note_scanfrom_name) values ('$playerinfo[player_id]'," . $db->qstr($note) . ",'$time','$team','$stype','$sectornum'," . $db->qstr($sectornumname) . "," . $db->qstr($owner) . ",'$planets'," . $db->qstr($port) . ",'$fighters','$mines','$scanfrom'," . $db->qstr($scanfromname) . ")";
	//echo $xsql;
	$debug_query = $db->Execute($xsql);
	db_op_result($debug_query,__LINE__,__FILE__);
}

$showlistcount = 0; 
$showteamlistcount = 0;
$editid = 0;
$teameditid = 0;
$notelistcount = 0;
$teamnotelistcount = 0;

$template_object->assign("l_sn_nonotes", $l_sn_nonotes);
$template_object->assign("l_sn_title", $l_sn_title);
$template_object->assign("l_sn_tntitle", $l_sn_tntitle);
$template_object->assign("l_sn_psntitle", $l_sn_psntitle);
$template_object->assign("l_sn_tsntitle", $l_sn_tsntitle);
$template_object->assign("l_sn_editnote", $l_sn_editnote);
$template_object->assign("l_sn_deleteedit", $l_sn_deleteedit);
$template_object->assign("l_sn_addnote", $l_sn_addnote);
$template_object->assign("l_sn_list", $l_sn_list);
$template_object->assign("l_sn_listps", $l_sn_listps);
$template_object->assign("l_sn_listts", $l_sn_listts);
$template_object->assign("l_sn_addteam", $l_sn_addteam);
$template_object->assign("l_sn_deleteteam", $l_sn_deleteteam);
$template_object->assign("l_sn_saveteam", $l_sn_saveteam);
$template_object->assign("l_sn_deletepersonal", $l_sn_deletepersonal);
$template_object->assign("l_sn_addpersonal", $l_sn_addpersonal);
$template_object->assign("l_sn_savepersonal", $l_sn_savepersonal);
$template_object->assign("l_sn_editpersonal", $l_sn_editpersonal);
$template_object->assign("l_sn_hdsector", $l_sn_hdsector);
$template_object->assign("l_sn_hdtype", $l_sn_hdtype);
$template_object->assign("l_sn_hdowner", $l_sn_hdowner);
$template_object->assign("l_sn_hdplanets", $l_sn_hdplanets);
$template_object->assign("l_sn_hdport",$l_sn_hdport);
$template_object->assign("l_sn_hdfighters", $l_sn_hdfighters);
$template_object->assign("l_sn_hdmines", $l_sn_hdmines);
$template_object->assign("l_sn_hdscanfrom", $l_sn_hdscanfrom);
$template_object->assign("l_sn_hddetail", $l_sn_hddetail);
$template_object->assign("l_sn_hddelete",$l_sn_hddelete);
$template_object->assign("l_sn_hddate",$l_sn_hddate);
$template_object->assign("l_sn_hdteam",$l_sn_hdteam);
$template_object->assign("l_sn_view",$l_sn_view);
$template_object->assign("l_sn_no",$l_sn_no);
$template_object->assign("l_sn_yes",$l_sn_yes);
$template_object->assign("l_sn_editteam", $l_sn_editteam);
$template_object->assign("l_sn_delete", $l_sn_delete);

if (( $command=="viewnote") and $sectornum == $shipinfosector)
{


if ($playerinfo['team']!=0){
	$result = $db->Execute("SELECT * FROM {$db_prefix}sector_notes where ( note_sector_id=$shipinfo[sector_id] or note_scanfrom=$shipinfo[sector_id]) and ( note_player_id=$playerinfo[player_id] or  (note_team_id=$playerinfo[team])");
}else{
		$result = $db->Execute("SELECT * FROM {$db_prefix}sector_notes where ( note_sector_id=$shipinfo[sector_id] or note_scanfrom=$shipinfo[sector_id]) and ( note_player_id=$playerinfo[player_id])");
}
	$limit_sectors=0;	
	if ($result->RecordCount()==1){
		$command=$l_sn_view;
		$sector=$shipinfo['sector_id'];
	}elseif($result->RecordCount()>1){
		$limit_sectors=1;
	}
}

if (($command==$l_sn_view or $command=="addnote"))
{
	if ($command==$l_sn_view){
	if ($playerinfo['team']!=0){
		$result = $db->Execute("SELECT * FROM {$db_prefix}sector_notes where (note_sector_id='$vsector_id' or note_scanfrom='$vsector_id') and ( note_player_id='$playerinfo[player_id]' or  note_team_id='$playerinfo[team]')");
		}else{
	$result = $db->Execute("SELECT * FROM {$db_prefix}sector_notes where (note_sector_id='$vsector_id' or note_scanfrom='$vsector_id') and ( note_player_id='$playerinfo[player_id]' )");
		
		}
		
		db_op_result($result,__LINE__,__FILE__);
		if ($result->RecordCount()){
			$notelistid = $result->fields['note_id'];
			$notelistnote = $result->fields['note_data'];
			$noteplayerid = $result->fields['note_player_id'];
			$notelistdate = $result->fields['note_date'];
			$notes_team = $result->fields['note_team_id'];
			$sector_type = $result->fields['note_stype'];
			$sector_id = $result->fields['note_sector_name'];
			
			$sector_owner = $result->fields['note_sowner'];
			$sector_planets = $result->fields['note_splanets'];
			$sector_port = $result->fields['note_sport'];
			$sector_fighters = NUMBER($result->fields['note_sfighters']);
			$sector_mines = NUMBER($result->fields['note_storps']);
			$sector_scanfrom = $result->fields['note_scanfrom_name'];
		
			$command=$l_sn_editnote;
			$notecount=$result->RecordCount();
		}
	}else{
		$command=$l_sn_addnote;
		$notecount=1;
		$sector_id=$sector;
	}

	$template_object->assign("limit", $limit);
	$template_object->assign("command", $command);
	$template_object->assign("count", $notecount);
	$template_object->assign("sectorlist", $sectorlist);
	$template_object->assign("playerteam", $playerinfo['team']);
	$template_object->assign("showlistcount", $showlistcount);
	$template_object->assign("showteamlistcount", $showteamlistcount);
	$template_object->assign("editid", $editid);
	$template_object->assign("editnoteid", $editnoteid);
	$template_object->assign("teameditid", $teameditid);
	$template_object->assign("teameditnoteid", $teameditnoteid);
	$template_object->assign("sectorid", $sectorid);
	$template_object->assign("shipsectorid", $shipinfo['sector_id']);
	$template_object->assign("num_notes", $notelistcount);
	$template_object->assign("search", $search);
	$template_object->assign("type", $type);
	$template_object->assign("sector", $sectorname);
	$template_object->assign("sector_type", $sector_type);
	$template_object->assign("sector_owner", $sector_owner);
	$template_object->assign("sector_planets", $sector_planets);
	$template_object->assign("sector_port", $sector_port);
	$template_object->assign("sector_fighters", $sector_fighters);
	$template_object->assign("sector_mines", $sector_mines);
	$template_object->assign("sector_scanfrom", $sector_scanfrom);
	$template_object->assign("notes_team", $notes_team);
	$template_object->assign("notelistid", $notelistid);
	$template_object->assign("notelistnote", $notelistnote);
	$template_object->assign("noteplayerid", $noteplayerid);
	$template_object->assign("teamid", $playerinfo['team']);
	$template_object->assign("playerid", $playerinfo['player_id']);
	$template_object->assign("notelistdate", $notelistdate);
	$template_object->assign("teamnotelistcount", $teamnotelistcount);
	$template_object->assign("teamnotelistid", $teamnotelistid);
	$template_object->assign("teamnotelistnote", $teamnotelistnote);
	$template_object->assign("teamnotelistdate", $teamnotelistdate);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."sector_notes_view.tpl");
}else{
	if ($playerinfo[team] > 0){
		$query="SELECT * FROM {$db_prefix}sector_notes WHERE  (note_player_id=$playerinfo[player_id] or note_team_id=$playerinfo[team]) ";
	}else{
		$query="SELECT * FROM {$db_prefix}sector_notes WHERE  note_player_id=$playerinfo[player_id] ";
	}

	if ($type!=""){
		$query.=" and note_stype='$type' ";
	}

	if ($search!=""){
		$query.=" and note_sowner like '%$search%' ";
	}

	if ($limit_sectors==1){
		if ($lrscan > 0){
			$query.=" and ( note_sector_id=$lrscan or note_scanfrom=$lrscan) ";
		}else{
			$query.=" and ( note_sector_id=$shipinfo[sector_id] or note_scanfrom=$shipinfo[sector_id]) ";
		}
	}

	if(!empty($sort))
	{
		$query .= " ORDER BY";
		if($sort == "type")
		{
			$query .= " note_stype ASC";
		}
		elseif($sort == "owner")
		{
			$query .= " note_sowner ASC, note_sector_name ASC";
		}
		elseif($sort == "planets")
		{
			$query .= " note_splanets ASC, note_sector_name ASC";
		}
		elseif($sort == "port")
		{
			$query .= " note_sport ASC, note_sector_name ASC";
		}
		elseif($sort == "fighters")
		{
			$query .= " note_sfighters ASC, note_sector_name ASC";
		}
		elseif($sort == "mines")
		{
			$query .= " note_storps ASC, note_sector_name ASC";
		}
		elseif($sort == "scanfrom")
		{
			$query .= " note_scanfrom_name ASC, note_sector_name ASC";
		}
		else
		{
			$query .= " note_sector_name ASC";
		}
	}
	else
	{
		$query .= " ORDER BY note_sector_name ASC";
	}

	$result = $db->Execute($query);
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
		$notesectorname[$notelistcount] = $result->fields['note_sector_name'];
		$sector_owner[$notelistcount] = $result->fields['note_sowner'];
		$sector_planets[$notelistcount] = $result->fields['note_splanets'];
		$sector_port[$notelistcount] = $result->fields['note_sport'];
		$sector_fighters[$notelistcount] = NUMBER($result->fields['note_sfighters']);
		$sector_mines[$notelistcount] = NUMBER($result->fields['note_storps']);
		$sector_scanfrom[$notelistcount] = $result->fields['note_scanfrom_name'];
		$notelistcount++;
		$result->MoveNext();
	}

	$template_object->assign("playerid", $playerinfo['player_id']);
	$template_object->assign("command", $command);
	$template_object->assign("count", $count);
	$template_object->assign("sectorlist", $sectorlist);
	$template_object->assign("playerteam", $playerinfo['team']);
	$template_object->assign("showlistcount", $showlistcount);
	$template_object->assign("showteamlistcount", $showteamlistcount);
	$template_object->assign("editid", $editid);
	$template_object->assign("editnoteid", $editnoteid);
	$template_object->assign("teameditid", $teameditid);
	$template_object->assign("teameditnoteid", $teameditnoteid);
	$template_object->assign("sectorid", $sectorid);
	$template_object->assign("shipsectorid", $shipinfo['sector_id']);
	$template_object->assign("num_notes", $notelistcount);
	$template_object->assign("num_notes", $notelistcount);
	$template_object->assign("search", $search);
	$template_object->assign("type", $type);
	$template_object->assign("sector", $notesectorname);
	$template_object->assign("sector_type", $sector_type);
	$template_object->assign("sector_owner", $sector_owner);
	$template_object->assign("sector_planets", $sector_planets);
	$template_object->assign("sector_port", $sector_port);
	$template_object->assign("sector_fighters", $sector_fighters);
	$template_object->assign("sector_mines", $sector_mines);
	$template_object->assign("sector_scanfrom", $sector_scanfrom);
	$template_object->assign("notes_team", $notes_team);
	$template_object->assign("notelistid", $notelistid);
	$template_object->assign("notelistnote", $notelistnote);
	$template_object->assign("notelistdate", $notelistdate);
	$template_object->assign("note_player_id", $note_player_id);
	$template_object->assign("teamnotelistcount", $teamnotelistcount);
	$template_object->assign("teamnotelistid", $teamnotelistid);
	$template_object->assign("teamnotelistnote", $teamnotelistnote);
	$template_object->assign("teamnotelistdate", $teamnotelistdate);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."sector_notes_all.tpl");
}

include ("footer.php");
?>