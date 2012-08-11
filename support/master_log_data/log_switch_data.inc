<?
function log_parse($entry)
{
  global $l_log_title;
  global $l_log_text;
  global $l_log_pod;
  global $l_log_nopod;
  global $db, $db_prefix;
	global $probetypeinfo;

  $entry['data'] = stripslashes($entry['data']);
  switch($entry['type'])
  {
	case "LOG_LOGIN": //data args are : [ip]
	case "LOG_LOGOUT":
	case "LOG0_BADLOGIN":
	case "LOG0_HARAKIRI":
	$retvalue['text'] = str_replace("[ip]", "<font color=white><b>$entry[data]</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_ATTACK_OUTMAN": //data args are : [player]
	case "LOG5_ATTACK_OUTSCAN":
	case "LOG5_ATTACK_EWD":
	case "LOG5_ATTACK_EWDFAIL":
	case "LOG6_SHIP_SCAN":
	case "LOG6_SHIP_SCAN_FAIL":
	case "LOG5_KABAL_ATTACK":
	case "LOG0_TEAM_NOT_LEAVE":
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$entry[data]</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_ATTACK_LOSE": //data args are : [player] [pod]
	list($name, $pod)= AAT_split ("\|", $entry['data']);

	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	if ($pod == 'Y' || $pod == 1)
	  $retvalue['text'] = $retvalue['text'] . $l_log_pod;
	else
	  $retvalue['text'] = $retvalue['text'] . $l_log_nopod;
	break;

	case "LOG5_ATTACKED_WIN": //data args are : [player] [armor] [fighters]
	list($name, $armor, $fighters)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[armor]", "<font color=white><b>$armor</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[fighters]", "<font color=white><b>$fighters</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_CONFISCATION": //data args are : [player] [ship]
	list($name, $ship)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[ship]", "<font color=white><b>$ship</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_PLANET_CONFISCATION": //data args are : [player] [ship]
	list($name, $planet_name, $sectorname, $score)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$planet_name</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sectorname</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[score]", "<font color=white><b>" . NUMBER($score) . "</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_HIT_MINES": //data args are : [mines] [sector]
	list($mines, $sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[mines]", "<font color=white><b>$mines</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_SHIP_DESTROYED_MINES": //data args are : [sector] [pod]
	case "LOG5_DEFS_KABOOM":
	list($sector, $pod)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	if ($pod == 'Y' || $pod == 1)
	  $retvalue['text'] = $retvalue['text'] . $l_log_pod;
	else
	  $retvalue['text'] = $retvalue['text'] . $l_log_nopod;
	break;

	case "LOG5_PLANET_DEFEATED_D": //data args are :[planet_name] [sector] [name]
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG4_PLANET_novaED_D": //data args are :[planet_name] [sector] [name]
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	case "LOG4_SHIP_novaED_D": //data args are :[planet_name] [sector] [name]
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_PLANET_DEFEATED":
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	case "LOG6_PLANET_SCAN":
	case "LOG6_PLANET_SCAN_FAIL":
	case "LOG5_PLANET_YOUR_CAPTURED":
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	case "LOG2_SPY_SEND_FAIL":///
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	case "LOG2_SPY_CPTURE_OWNER":
	case "LOG2_SPY_KILLED":
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG1_DIG_KILLED_SPY":
	list($planet_name, $sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	case "LOG2_SPY_FOUND_EMBEZZLER": //data args are : [DIG] [PLANET]
	list($dig, $name)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[DIG]", "<font color=#00FFFF><b>$dig</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[PLANET]", "<font color=#00FF00><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_PLANET_NOT_DEFEATED": //data args are : [planet_name] [sector] [name] [ore] [organics] [goods] [salvage] [credits]
	list($planet_name, $sector, $name, $ore, $organics, $goods, $salvage, $credits)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[ore]", "<font color=white><b>$ore</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[goods]", "<font color=white><b>$goods</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[organics]", "<font color=white><b>$organics</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[salvage]", "<font color=white><b>$salvage</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[credits]", "<font color=white><b>$credits</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_RAW": //data is stored as a message
	case "LOG0_ADMIN_DBERROR": //data is stored as a message
	case "LOG0_ADMIN_COMBAT": //data is stored as a message
	case "LOG5_AFTER_ACTION":
	$retvalue['title'] = $l_log_title[$entry['type']];
	$retvalue['text'] = $entry['data'];
	break;

	case "LOG5_DEFS_DESTROYED": //data args are : [quantity] [type] [sector]
	list($quantity, $type, $sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[quantity]", "<font color=white><b>$quantity</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[type]", "<font color=white><b>$type</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	
	case "LOG0_PLANET_EJECT": //data args are : [sector] [player]
	list($sector, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG7_STARVATION": //data args are : [sector] [starvation]
	list($sector, $starvation, $name, $date)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[starvation]", "<font color=white><b>" . NUMBER($starvation) . "</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>" . $name . "</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[date]", "<font color=white><b>" . $date . "</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_TOW": //data args are : [sector] [newsector] [hull]
	list($sector, $newsector, $hull)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $newsector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$newsector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[newsector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$newsector>$newsector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[hull]", "<font color=white><b>$hull</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_DEFS_DESTROYED_F": //data args are : [fighters] [sector]
	list($fighters, $sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[fighters]", "<font color=white><b>$fighters</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_TEAM_REJECT": //data args are : [player] [teamname]
	list($player, $teamname)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[teamname]", "<font color=white><b>$teamname</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_TEAM_RENAME": //data args are : [team]
	case "LOG0_TEAM_M_RENAME":
	case "LOG0_TEAM_KICK":
	case "LOG0_TEAM_CREATE":
	case "LOG0_TEAM_LEAVE":
	case "LOG0_TEAM_LEAD":
	case "LOG0_TEAM_JOIN":
	case "LOG0_TEAM_INVITE":
	$retvalue['text'] = str_replace("[team]", "<font color=white><b>$entry[data]</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_TEAM_CANCEL":
	$retvalue['text'] = str_replace("[team]", "<font color=white><b>$entry[data]</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_TEAM_NEWLEAD": //data args are : [team] [name]
	case "LOG0_TEAM_NEWMEMBER":
	list($team, $name)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[team]", "<font color=white><b>$team</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_ADMIN_HARAKIRI": //data args are : [player] [ip]
	list($player, $ip)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[ip]", "<font color=white><b>$ip</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_ADMIN_ILLEGVALUE": //data args are : [player] [quantity] [type] [holds]
	list($player, $quantity, $type, $holds)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[quantity]", "<font color=white><b>$quantity</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[type]", "<font color=white><b>$type</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[holds]", "<font color=white><b>$holds</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_ADMIN_PLANETDEL": //data args are : [attacker] [defender] [sector]
	list($attacker, $defender, $sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[attacker]", "<font color=white><b>$attacker</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[defender]", "<font color=white><b>$defender</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_ADMIN_PLANETIND": //data args are : [planetname] [planetid] [sector] [avgtech]
	case "LOG0_ADMIN_INDYPURGE": //data args are : [planetname] [planetid] [sector] [avgtech]
	list($planetname, $planetid, $sector, $avgtech,$owner)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$resx = $db->SelectLimit("SELECT character_name from {$db_prefix}players WHERE player_id =" . $owner, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$owner = $resx->fields['character_name'];
	$retvalue['text'] = str_replace("[planetname]", "<font color=#00FFFF><b>$planetname</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[planetid]", "<font color=#FF0000><b>$planetid</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=#00FF00><b>$sector</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[avgtech]", "<font color=#00FF00><b>$avgtech</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[owner]", "<font color=#00FF00><b>$owner</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_ADMIN_NEVEROWNEDPURGE": //data args are : [planetname] [planetid] [sector] [avgtech]
	list($planetname, $planetid, $sector, $avgtech,$creation_date)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planetname]", "<font color=#00FFFF><b>$planetname</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[planetid]", "<font color=#FF0000><b>$planetid</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=#00FF00><b>$sector</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[avgtech]", "<font color=#00FF00><b>$avgtech</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[date]", "<font color=#00FF00><b>$creation_date</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_defense_DEGRADE": //data args are : [sector] [degrade]
	list($sector, $degrade)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[degrade]", "<font color=white><b>$degrade</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_PLANET_CAPTURED": //data args are : [cols] [credits] [owner]
	list($cols, $credits, $owner)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[cols]", "<font color=white><b>$cols</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[credits]", "<font color=white><b>$credits</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[owner]", "<font color=white><b>$owner</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	case "LOG0_BOUNTY_CLAIMED":
	list($amount,$bounty_on,$placed_by) = AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[amount]", "<font color=white><b>".number($amount)."</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[bounty_on]", "<font color=white><b>$bounty_on</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[placed_by]", "<font color=white><b>$placed_by</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
 case "LOG0_BOUNTY_TAX_PAID":
 case "LOG0_BOUNTY_PAID":
	list($amount,$bounty_on) = AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[amount]", "<font color=white><b>".number($amount)."</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[bounty_on]", "<font color=white><b>$bounty_on</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
 case "LOG0_BOUNTY_CANCELLED":
	list($amount,$bounty_on) = AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[amount]", "<font color=white><b>".number($amount)."</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[bounty_on]", "<font color=white><b>$bounty_on</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
case "LOG0_BOUNTY_ALLIANCEBOUNTY":
case "LOG0_BOUNTY_FEDBOUNTY":
	$retvalue['text'] = str_replace("[amount]", "<font color=white><b>".number($entry['data'])."</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

 case "LOG5_PLANET_BOMBED":
	list($planet_name, $sector, $name, $beams, $torps, $figs)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[beams]", "<font color=white><b>$beams</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[torps]", "<font color=white><b>$torps</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[figs]", "<font color=white><b>$figs</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
 case "LOG0_CHEAT_TEAM": //data args are : [player] [ip]
	list($name, $ip)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[ip]", "<font color=white><b>$ip</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG1_DIG_MONEY":
	case "LOG1_DIG_PRODUCTION": //data args are :[id] [planet_name] [sector] [data]
	case "LOG1_DIG_BIRTHDEC":
	case "LOG1_DIG_BIRTHINC":
	case "LOG1_DIG_SPYHUNT":
	case "LOG1_DIG_INTEREST":
	case "LOG1_DIG_TORPS":
	case "LOG1_DIG_FITS":
	list($id, $planet_name, $sector, $data)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[data]", "<font color=white><b>$data</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

case "LOG9_PROBE_DETECTED_SHIP":

	list($id,$sector,$ship_name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[ship_name]", "<font color=white><b>$ship_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
case "LOG9_PROBE_SCAN_SHIP":

 list($id,$sector,$ship_name,$sc_hull,$sc_engines,$sc_power,$sc_fighter,$sc_sensors,$sc_beams,$sc_torp_launchers,$sc_armor,$sc_shields,$sc_cloak,$sc_armor_pts,$sc_ship_fighters,$sc_torps,$sc_credits,$sc_ship_energy,$sc_dev_minedeflector,$sc_dev_emerwarp,$sc_dev_pod,$sc_ecm)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[ship_name]", "<font color=white><b>$ship_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[hull]", "<font color=white><b>$sc_hull</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[engines]", "<font color=white><b>$sc_engines</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[power]", "<font color=white><b>$sc_power</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[fighter]", "<font color=white><b>$sc_fighter</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[sensors]", "<font color=white><b>$sc_sensors</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[beams]", "<font color=white><b>$sc_beams</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[torps]", "<font color=white><b>$sc_torp_launchers</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[armor]", "<font color=white><b>$sc_armor</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[shields]", "<font color=white><b>$sc_shields</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[cloak]", "<font color=white><b>$sc_cloak</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[armor_pts]", "<font color=white><b>$sc_armor_pts</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[fighters]", "<font color=white><b>$sc_ship_fighters</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[avail_torps]", "<font color=white><b>$sc_torps</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[credits]", "<font color=white><b>$sc_credits</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[energy]", "<font color=white><b>$sc_ship_energy</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[deflectors]", "<font color=white><b>$sc_dev_minedeflector</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[ewd]", "<font color=white><b>$sc_dev_emerwarp</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[pod]", "<font color=white><b>$sc_dev_pod</b></font>", $retvalue['text']);
 $retvalue['text'] = str_replace("[ecm]", "<font color=white><b>$sc_ecm</b></font>", $retvalue['text']);

	$retvalue['title'] = $l_log_title[$entry['type']];
	break;	
//end
	case "LOG2_SPY_SABOTAGE": //data args are :[id] [planet_name] [sector] [data]
	case "LOG2_SPY_BIRTH":
	case "LOG2_SPY_INTEREST":
	case "LOG2_SPY_MONEY":
	case "LOG2_SPY_TORPS":
	case "LOG2_SPY_FITS":
	list($id, $planet_name, $sector, $data)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[data]", "<font color=white><b>$data</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG2_SPY_CPTURE": //data args are :[id] [planet_name] [sector]
	case "LOG2_SPY_KILLED_SPYOWNER":
	case "LOG2_SPY_CATACLYSM":
	list($id, $planet_name, $sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG2_SHIPSPY_KILLED": //data args are :[id] [name] [shipname]
	case "LOG2_SHIPSPY_CATACLYSM":
	case "LOG2_SPY_NEWSHIP":
	list($id, $name, $shipname)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[shipname]", "<font color=white><b>$shipname</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG2_SPY_TOSHIP": //data args are :[id] [planet_name] [sector] [playername] [shipname]
	case "LOG2_SPY_TOPLANET":
	list($id, $planet_name, $sector, $playername, $shipname)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planet_name]", "<font color=white><b>$planet_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[id]", "<font color=white><b>$id</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[playername]", "<font color=white><b>$playername</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[shipname]", "<font color=white><b>$shipname</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG0_IGB_TRANSFER1": //data args are : [name] [sum]
	case "LOG0_IGB_TRANSFER2":
	list($name, $sum)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sum]", "<font color=white><b>$sum</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG10_AUTOTRADE":
	list($planetname,$sector,$totalcost,$goodsamount,$oreamount,$organicsamount,$energyamount,$colonistamount,$goodsprice,$oreprice,$organicsprice,$energyprice,$colonistprice)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planetname]", "<font color=white><b>$planetname</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[totalcost]", "<font color=white><b>".number($totalcost)."</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[goodsamount]", "<font color=white><b>$goodsamount</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[oreamount]", "<font color=white><b>$oreamount</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[organicsamount]", "<font color=white><b>$organicsamount</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[energyamount]", "<font color=white><b>$energyamount</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[colonistamount]", "<font color=white><b>$colonistamount</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[goodsprice]", "<font color=white><b>$goodsprice</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[oreprice]", "<font color=white><b>$oreprice</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[organicsprice]", "<font color=white><b>$organicsprice</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[energyprice]", "<font color=white><b>$energyprice</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[colonistprice]", "<font color=white><b>$colonistprice</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG10_AUTOTRADE_ABORTED":
	list($planetname, $sector, $destsector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $destsector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$destsector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[planetname]", "<font color=white><b>$planetname</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[destsector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$destsector>$destsector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG9_PROBE_DESTROYED":
	list($sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG9_PROBE_NOTURNS":
	list($probe_id, $sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[probe_id]", "<font color=white><b>$probe_id</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG9_PROBE_INVALIDSECTOR":
	list($sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[target_sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG9_PROBE_DETECTPROBE":
	list($probe_id, $sector, $probe_detect,$probe_type)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[probe_id]", "<font color=white><b>$probe_id</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[probe_detect]", "<br><font color=white><b>$probe_detect</b></font>", $retvalue['text']);
	$probe_type2 = "";

	if($probe_type == "Real Space")
	{
		$probe_type2 = "<br><font color='#79f487'><b>$probe_type</b></font>";
	}
	else
	{
		$probe_type2 = "<br><font color='#87d8ec'><b>$probe_type</b></font>";
	}
	$retvalue['title'] = str_replace("[probe_type]", $probe_type2, $l_log_title[$entry['type']]);
	break;

	case "LOG5_STORAGE_EWD":
	list($player_name, $sector, $planet_name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[planet]", "<font color=white><b>$planet_name</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_STORAGE_SUICIDE":
	case "LOG5_STORAGE_CAPTURED":
	case "LOG5_STORAGE_EWDFAIL":
	list($player_name)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_SM_ATTACK":
	list($player_name, $sector_id)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector_id, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;
	
	case "LOG5_SM_OUTMAN": //data args are : [player]
	case "LOG5_SM_OUTSCAN":
	case "LOG5_SM_EWD":
	case "LOG5_SM_EWDFAIL":
	case "LOG5_SM_LOSE":
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$entry[data]</b></font>", $l_log_text[$entry['type']]);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_SM_WIN":
	list($player_name, $armor, $energy)= AAT_split ("\|", $entry['data']);
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[armor]", "<font color=white><b>$armor</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[energy]", "<font color=white><b>$energy</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG9_PROBE_SCAN_FAIL": //data args are : [team] [name]
	case "LOG9_PROBE_SCAN":
	case "LOG9_PROBE_ATTACKED":
	list($probe_type, $sector_id, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector_id, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue['text']);
	$retvalue['title'] = str_replace("[probe_type]", "<font color=white><b>$probe_type</b></font>", $l_log_title[$entry['type']]);
	break;

	case "LOG9_PROBE_DETECTED_GATEWAY":
	list($id,$sector)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[probe_id]", "<font color=white><b>$id</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_PROBE_ATTACK_FAILED": //data args are : [team] [name]
	case "LOG5_PROBE_ATTACK_SUCCEEDED":
	case "LOG5_DESTROYED_PROBE_ATTACK":
	list($name, $sector_id)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector_id, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG5_SURVIVE_PROBE_ATTACK":
	list($player_name, $armor, $energy, $destination)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $destination, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$retvalue['text'] = str_replace("[player]", "<font color=white><b>$player_name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[armor]", "<font color=white><b>$armor</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[energy]", "<font color=white><b>$energy</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue['text']);
	$retvalue['title'] = $l_log_title[$entry['type']];
	break;

	case "LOG9_PROBEHUNTER_SUCCEED":
	case "LOG9_PROBEHUNTER_DESTROYED":
	case "LOG9_PROBEHUNTER_EXPLODED":
	list($probe_type, $sector_id, $name)= AAT_split ("\|", $entry['data']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector_id, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields['sector_name'];
	$probe_type_name = $probetypeinfo[$probe_type];
	$retvalue['text'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry['type']]);
	$retvalue['text'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue['text']);
	$retvalue['text'] = str_replace("[probe_type]", "<font color=white><b>$probe_type_name</b></font>", $retvalue['text']);
	$retvalue['title'] = str_replace("[probe_type]", "<font color=white><b>$probe_type_name</b></font>", $l_log_title[$entry['type']]);
	break;
	}
?>
