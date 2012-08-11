<?php
include ("languages/$langdir/lang_attack.inc");
include ("languages/$langdir/lang_combat.inc");
include ("languages/$langdir/lang_sector_fighters.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/explode_mines.inc");
include ("globals/message_defense_owner.inc");
include ("globals/cancel_bounty.inc");
include ("globals/destroy_fighters.inc");
$sector_combat=0;
$title = $l_sf_attacking;

echo "<H1>$title</H1>\n";

if ($move_type == 'real')
{
	$shipinfo['energy'] += $energy_collected;
}

///  start new combat

// get target beam, shield and armor values

$attacker_armor_left = $shipinfo['armor_pts'];
$attacker_torps_left = $shipinfo['torps'];
$attacker_fighters_left = $shipinfo['fighters'];

$target_torps_left = isset($defenses['mines']) ? $defenses['mines'] : 0;
$target_fighters_left = isset($defenses['fighters']) ? $defenses['fighters'] : 0;

echo "
		<CENTER>
		<table width='75%' border='0' bgcolor=\"#000000\">
		<tr><td colspan=6 align=center><hr></td></tr>
		<tr ALIGN='CENTER'>
		<td width='25%' height='27'></td>
		<td width='25%' height='27'><FONT COLOR='WHITE'>$l_cmb_fighters</FONT></td>
		<td width='25%' height='27'><FONT COLOR='WHITE'>$l_cmb_torps</FONT></td>
		<td width='25%' height='27'><FONT COLOR='WHITE'>$l_cmb_armor</FONT></td>
		</tr>
		<tr ALIGN='CENTER'>
		<td width='25%'> <FONT COLOR='yellow'><B>$l_cmb_you</B></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_fighters_left)."&nbsp;</B></FONT></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_torps_left)."&nbsp;</B></FONT></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_armor_left)."&nbsp;</B></FONT></td></tr>
		<tr ALIGN='CENTER'>
		<td width='25%'> <FONT COLOR='yellow'><B>Sector Defense</B></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($target_fighters_left)."&nbsp;</B></FONT></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($target_torps_left)."&nbsp;</B></FONT></td><td width='25%'>&nbsp;</td>
		</tr>
		<tr><td colspan=3 align=center>&nbsp;</td></tr>
		</table>
		</CENTER>
";

	$has_fighters = 0;
$highjammer=0;
$highcloak = 0;
$highsensor = 0;
$highfighter = 0;
$hightorps = 0;
$high_player_id = 0;
$high_player_score = 0;

$energy_required = ROUND($target_fighters_left * $energy_per_fighter * 2);
$energy_available = 0;

$resultSDb = $db->Execute("SELECT * from {$db_prefix}sector_defense WHERE sector_id='$destination' and player_id != '$playerinfo[player_id]' and defense_type='fighters'");
db_op_result($resultSDb,__LINE__,__FILE__);
if ($resultSDb > 0)
{
	while (!$resultSDb->EOF)
	{
		$fm_owner = $resultSDb->fields['player_id'];
		$resultSDc = $db->Execute("SELECT * from {$db_prefix}players WHERE player_id='$fm_owner'");
		db_op_result($resultSDc,__LINE__,__FILE__);
		if ($resultSDc > 0)
		{
		   	$fighterowner= $resultSDc->fields['team'];
		}

		if($high_player_score < $resultSDc->fields['score'])
		{
			$high_player_score = $resultSDc->fields['score'];
			$high_player_id = $resultSDc->fields['player_id'];
		}

		$result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner=$fm_owner or (team > 0 and team=$fighterowner)) and base='Y' and sector_id='$destination' order by sector_defense_cloak DESC", 1);
		db_op_result($result4,__LINE__,__FILE__);
		$planets = $result4->fields;
		if ($highcloak < $planets['sector_defense_cloak']){
			$highcloak=$planets['sector_defense_cloak'] + $basedefense;
		}
		$result4->close();

		$result4 = $db->SelectLimit("SELECT sector_defense_sensors from {$db_prefix}planets where (owner=$fm_owner or (team > 0 and team=$fighterowner)) and base='Y' and sector_id='$destination' order by sector_defense_sensors DESC", 1);
		db_op_result($result4,__LINE__,__FILE__);
		$planets = $result4->fields;
		if ($highsensor < $planets['sector_defense_sensors']){
			$highsensor=$planets['sector_defense_sensors'] + $basedefense;
		}
		$result4->close();

		$result4 = $db->SelectLimit("SELECT sector_defense_weapons, owner from {$db_prefix}planets where (owner=$fm_owner or (team > 0 and team=$fighterowner)) and base='Y' and sector_id='$destination' order by sector_defense_weapons DESC", 1);
		db_op_result($result4,__LINE__,__FILE__);
		$planets = $result4->fields;
		if ($highfighter < $planets['sector_defense_weapons']){
			$highfighter=$planets['sector_defense_weapons'] + $basedefense;
			$hightorps=$planets['sector_defense_weapons'] + $basedefense;
		}
		$result4->close();

		$resultSDb->MoveNext();
	}
	$res4 = $db->Execute("SELECT SUM(energy) as energy_available from {$db_prefix}planets where (owner = $fm_owner or (team = $fighterowner AND $fighterowner <> 0)) and sector_id = '$destination' and energy > 0 and base='Y'"); 
	$energy_available = $res4->fields['energy_available'];
}

$target_fighters_unused = 0;

$result5 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=". $high_player_id . "", 1);
db_op_result($result5,__LINE__,__FILE__);
$planet_owner = $result5->fields;

// If the attacker would get a bounty by attacking the most powerful planet in the sector then their A&R is useless.
$isfedbounty = planet_bounty_check($playerinfo, $destination, $planet_owner, 0);

if($isfedbounty > 0)
{
$energy_available=$energy_required*3;
}
 
if ($energy_available < $energy_required)
{
	$target_fighters_unused = $target_fighters_left - round($energy_available / ($energy_per_fighter * 2));
	$target_fighters_left = round($energy_available / ($energy_per_fighter * 2));
	$energy_required = $energy_available;
}

$attackerlowpercent = ecmcheck($highcloak, $shipinfo['sensors'], $full_attack_modifier);
$targetlowpercent = ecmcheck($shipinfo['ecm'], $highsensor, -$full_attack_modifier);

$targetshiptorp_launchers = $targetship['torp_launchers'];
$targetshipfighter = $targetship['fighter'];
$targetname = "Sector Defense";

if(!class_exists($shipinfo['fighter_class'])){
	include ("class/" . $shipinfo['fighter_class'] . ".inc");
}

$attackobject = new $shipinfo['fighter_class']();
$fighter_damage_shields = $attackobject->fighter_damage_shields;
$fighter_damage_all = $attackobject->fighter_damage_all;
$fighter_hit_pts = $attackobject->fighter_hit_pts;

if(!class_exists($shipinfo['torp_class'])){
	include ("class/" . $shipinfo['torp_class'] . ".inc");
}

$attackobject = new $shipinfo['torp_class']();
$torp_damage_shields = $attackobject->torp_damage_shields;
$torp_damage_all = $attackobject->torp_damage_all;
$torp_hit_pts = $attackobject->torp_hit_pts;

if(!class_exists($shipinfo['armor_class'])){
	include ("class/" . $shipinfo['armor_class'] . ".inc");
}

$attackobject = new $shipinfo['armor_class']();
$ship_armor_hit_pts = $attackobject->ship_armor_hit_pts;

if(!class_exists("Ship_Fighter")){
	include ("class/Ship_Fighter.inc");
}

$targetobject = new Ship_Fighter();
$fighter_damage_shields = $targetobject->fighter_damage_shields;
$fighter_damage_all = $targetobject->fighter_damage_all;
$fighter_hit_pts = $targetobject->fighter_hit_pts;

if(!class_exists("Ship_Torpedo")){
	include ("class/Ship_Torpedo.inc");
}

$targetobject = new Ship_Torpedo();
$torp_damage_shields = $targetobject->torp_damage_shields;
$torp_damage_all = $targetobject->torp_damage_all;
$torp_hit_pts = $targetobject->torp_hit_pts;

$result5 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=". $high_player_id . "", 1);
db_op_result($result5,__LINE__,__FILE__);
$planet_owner = $result5->fields;

// If the attacker would get a bounty by attacking the most powerful planet in the sector then their A&R is useless.
$isfedbounty = planet_bounty_check($playerinfo, $destination, $planet_owner, 0);

if($isfedbounty > 0)
{
	$attacker_torps_left = 0;
	$attacker_fighters_left = 0;
	echo "
		<CENTER>
		<table width='75%' border='0' bgcolor=\"#000000\">
		<tr><td align=center><hr></td></tr>
		<tr ALIGN='CENTER'>
		<td><font color='red' size='4'><b>$l_sf_bountysd</b></font></td>
		</tr>
		</table>
		</CENTER>
	";
}

// Stage 1 fighter to fighter Exchange

echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" align=center bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_att_fighters</font></b><tr><td width=50%>";

if($target_fighters_left != 0)
{
	$target_fighter_damage = calc_damage($target_fighters_left, $fighter_damage_all, $targetlowpercent, $highfighter, $shipinfo['fighter']);

	if($target_fighter_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_sf_fnoattack</b></font><br><br>";
	}

	$attack_fighter_hit_pts = $attacker_fighters_left * $fighter_hit_pts;
	if($target_fighter_damage[0] > $attack_fighter_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_fighter_hit_pts;
		if($attacker_fighters_left > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attacker_fighters_left) . "</font> $l_att_yfhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ylostf</b></font><br><br>";
		$attacker_fighters_left2 = 0;
	}
	else
	{
		$attack_fighter_hit_pts = $attack_fighter_hit_pts - $target_fighter_damage[0];
		$attack_fighters_used = floor($target_fighter_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attack_fighters_used) . "</font> $l_att_yfhit</b></font><br>";
		$attacker_fighters_left2 = $attacker_fighters_left - $attack_fighters_used;
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tfnoattack</font><b><br><br>";
	$attacker_fighters_left2 = $attacker_fighters_left;
}

echo "</td><td width=50%>";

if($attacker_fighters_left != 0)
{
	$attack_fighter_damage = calc_damage($attacker_fighters_left, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $highfighter);

	if($attack_fighter_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_sf_flaunchmalf1</font><br>$l_sf_flaunchmalf2<font color='#ffffff'>" . (100 - $attack_fighter_damage[2]) . "</font>$l_sf_flaunchmalf3</b></font><br><br>";
	}

	$target_fighter_hit_pts = $target_fighters_left * $fighter_hit_pts;
	if($attack_fighter_damage[0] > $target_fighter_hit_pts)
	{
		$attack_fighter_damage[0] = $attack_fighter_damage[0] - $target_fighter_hit_pts;
		if($target_fighters_left > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_left) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostf</b></font><br><br>";
		$target_fighters_left2 = 0;
	}
	else
	{
		$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_fighter_damage[0];
		$target_fighters_used = floor($attack_fighter_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		$target_fighters_left2 = $target_fighters_left - $target_fighters_used;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anofighters</font><b><br><br>";
	$target_fighters_left2 = $target_fighters_left;
}

echo "</td></tr></table><br><br>";

// Stage 2 fighter to torp/mine Exchange torps

echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" align=center bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_sf_fightertorpexg</font></b><tr><td width=50%>";

if($target_fighters_left2 != 0)
{
	$target_fighter_damage = calc_damage($target_fighters_left2, $fighter_damage_all, $targetlowpercent, $highfighter, $shipinfo['torp_launchers']);

	if($target_fighter_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_sf_fnoattackt</b></font><br><br>";
	}

	$attack_torp_hit_pts = $attacker_torps_left * $torp_hit_pts;
	if($target_fighter_damage[0] > $attack_torp_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_torp_hit_pts;
		if($attacker_torps_left > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attacker_torps_left) . "</font> $l_att_ythit</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ylostt</b></font><br><br>";
		$attacker_torps_left = 0;
	}
	else
	{
		$attack_torp_hit_pts = $attack_torp_hit_pts - $target_fighter_damage[0];
		$attack_fighters_used = floor($target_fighter_damage[0] / $torp_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attack_fighters_used) . "</font> $l_att_ythit</b></font><br>";
		$attacker_torps_left = $attacker_torps_left - $attack_fighters_used;
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tfnoattack</font><b><br><br>";
}

echo "</td><td width=50%>";

if($attacker_fighters_left2 != 0)
{
	$attack_fighter_damage = calc_damage($attacker_fighters_left2, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $hightorps);

	if($attack_fighter_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_sf_flaunchmalf1</font><br>$l_sf_flaunchmalf2<font color='#ffffff'>" . (100 - $attack_fighter_damage[2]) . "</font>$l_sf_flaunchmalf3</b></font><br><br>";
	}

	$target_torp_hit_pts = $target_torps_left * $torp_hit_pts;
	if($attack_fighter_damage[0] > $target_torp_hit_pts)
	{
		$attack_fighter_damage[0] = $attack_fighter_damage[0] - $target_torp_hit_pts;
		if($target_torps_left > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_torps_left) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_ethit</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostt</b></font><br><br>";
		$target_torps_left = 0;
	}
	else
	{
		$target_torp_hit_pts = $target_torp_hit_pts - $attack_fighter_damage[0];
		$target_fighters_used = floor($attack_fighter_damage[0] / $torp_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_ethit</b></font><br>";
		$target_torps_left = $target_torps_left - $target_fighters_used;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anofighters</font><b><br><br>";
}

echo "</td></tr></table><br><br>";

// Stage 3 ship torp to sector fighter Exchange

echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" align=center bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_sf_torpfighterexg</font></b><tr><td width=50%>";
echo "&nbsp;</td><td width=50%>";

if($attacker_torps_left != 0)
{
	$attack_torp_damage = calc_damage($attacker_torps_left, $torp_damage_all, $attackerlowpercent, $shipinfo['torp_launchers'], $highfighter);

	if($attack_torp_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_sf_tlaunchmalf1</font><br>$l_sf_tlaunchmalf2<font color='#ffffff'>" . (100 - $attack_fighter_damage[2]) . "</font>$l_sf_tlaunchmalf3</b></font><br><br>";
	}

	$target_fighter_hit_pts = $target_fighters_left2 * $fighter_hit_pts;
	if($attack_torp_damage[0] > $target_fighter_hit_pts)
	{
		$attack_torp_damage[0] = $attack_torp_damage[0] - $target_fighter_hit_pts;
		if($target_fighters_left2 > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_left2) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostf</b></font><br><br>";
		$attacker_torps_left = floor($attack_torp_damage[0] / $torp_damage_all);
		$target_fighters_left = 0;
	}
	else
	{
		$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_torp_damage[0];
		$target_fighters_used = floor($attack_torp_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		$target_fighters_left = $target_fighters_left2 - $target_fighters_used;
		$attacker_torps_left = 0;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anotorps</font><b><br><br>";
	$target_fighters_left = $target_fighters_left2;
}

echo "</td></tr></table><br><br>";

// Stage 4 sector fighter to ship armor Exchange

echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" align=center bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_sf_fighterarmorexg</font></b><tr><td width=50%>";

if($target_fighters_left != 0)
{
	$target_fighter_damage = calc_damage($target_fighters_left, $fighter_damage_all, $targetlowpercent, $highfighter, $shipinfo['armor']);

	if($target_fighter_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_sf_fnoattacka</b></font><br><br>";
	}

	$attack_armor_hit_pts = $attacker_armor_left * $ship_armor_hit_pts;
	if($target_fighter_damage[0] > $attack_armor_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_armor_hit_pts;
		if($attacker_armor_left > 0)
			echo "<font color='#00ff00'><b>$l_att_ayhit <FONT COLOR='yellow'>" . NUMBER($attacker_armor_left) . "</font> $l_att_dmg.</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_yarm</b></font><br><br>";
		$attacker_armor_left = 0;
	}
	else
	{
		$attack_armor_hit_pts = $attack_armor_hit_pts - $target_fighter_damage[0];
		$attacker_armor_used = $attacker_armor_left - floor($attack_armor_hit_pts / $ship_armor_hit_pts);
		echo "<font color='#00ff00'><b>$l_att_ayhit <FONT COLOR='yellow'>" . NUMBER($attacker_armor_used) . "</font> $l_att_dmg.</b></font><br>";
		$attacker_armor_left = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tfnoattack</font><b><br><br>";
}
echo "</td><td width=50%>&nbsp;";

echo "</td></tr></table>";
/// end new combat

echo "
		<CENTER>
		<table width='75%' border='0' bgcolor=\"#000000\">
		<tr><td colspan=6 align=center><hr></td></tr>
		<tr ALIGN='CENTER'>
		<td width='25%' height='27'></td>
		<td width='25%' height='27'><FONT COLOR='WHITE'>$l_cmb_fighters</FONT></td>
		<td width='25%' height='27'><FONT COLOR='WHITE'>$l_cmb_torps</FONT></td>
		<td width='25%' height='27'><FONT COLOR='WHITE'>$l_cmb_armor</FONT></td>
		</tr>
		<tr ALIGN='CENTER'>
		<td width='25%'> <FONT COLOR='yellow'><B>$l_cmb_you</B></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_fighters_left2)."&nbsp;</B></FONT></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_torps_left)."&nbsp;</B></FONT></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_armor_left)."&nbsp;</B></FONT></td></tr><tr ALIGN='CENTER'>
		<td width='25%'> <FONT COLOR='yellow'><B>Sector Defense</B></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($target_fighters_left)."&nbsp;</B></FONT></td>
		<td width='25%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($target_torps_left)."&nbsp;</B></FONT></td><td width='25%'>&nbsp;</td>
		</tr>";

echo "	</tr>
		<tr><td colspan=6 align=center>&nbsp;</td></tr>
		</table>
		</CENTER>
";

$total_sector_mines_lost = $defenses['mines'] - $target_torps_left;
$defenses['mines'] = $target_torps_left;
explode_mines($destination,$total_sector_mines_lost);
$target_fighters_random = mt_rand(0, $target_fighters_unused);
if($target_fighters_random < floor($target_fighters_unused * 0.10) || $target_fighters_unused < 1000)
{
	$target_fighters_random = 0;
}
$fighterslost = $defenses['fighters'] - ($target_fighters_left + $target_fighters_random);

$energy_required = ($fighterslost * $energy_per_fighter * 2) + round(($target_fighters_left + $target_fighters_random) * (($energy_per_fighter * 2) * 0.01));

if ($energy_available < $energy_required)
{
	$energy_required = $energy_available;
}

$where = "";
$res2 = $db->Execute("SELECT planet_id from {$db_prefix}planets where (owner = $fm_owner or (team = $fighterowner AND $fighterowner <> 0)) and sector_id = $destination and energy > 0 and base='Y'"); 
while (!$res2->EOF)
{
	$where .= "planet_id=" . $res2->fields['planet_id'] . " or ";
	$res2->MoveNext();
}

if($where != "")
{
	$where .= "planet_id=-1";
	$debug_query = $db->Execute("UPDATE {$db_prefix}planets set energy = energy - " .
    	            "GREATEST(ROUND($energy_required * (energy / $energy_available)),1)  where $where");
	db_op_result($debug_query,__LINE__,__FILE__);
}

$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id='$destination'", 1);

if($sector_check->RecordCount()){
	$sect = $sector_check->fields;
	$sectorname = $sect['sector_name'];
}
$sector_check->close();

$inputtype[0] = "[player]";
$inputdata[0] = $playerinfo['character_name'];
$inputtype[1] = "[lost]";
$inputdata[1] = NUMBER($fighterslost);
$inputtype[2] = "[sector]";
$inputdata[2] = "<a href=main.php?move_method=real&engage=1&destination=$sectorname>$sectorname</a>";
message_defense_owner($destination, "l_sf_sendlog", "lang_sector_fighters.inc", "fighters", $inputtype, $inputdata);

destroy_fighters($destination,$fighterslost);
$defenses['fighters'] = $target_fighters_left;
if ($target_fighters_left > 0){
	$move_failed=1;
}
$sector_combat=1;
playerlog($playerinfo['player_id'], "LOG5_DEFS_DESTROYED_F", "$fighterslost|$destination");
$armor_lost = max(($shipinfo['armor_pts'] - $attacker_armor_left), 0);
$fighters_lost = max(($shipinfo['fighters'] - $attacker_fighters_left2), 0);
$playertorpnum = max(($shipinfo['torps'] - $attacker_torps_left), 0);

if($shipinfo['armor_pts'] != 0)
	calc_internal_damage($shipinfo['ship_id'], 0, ($shipinfo['armor_pts']-$attacker_armor_left) / $shipinfo['armor_pts']);

$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET fighters=$attacker_fighters_left2, armor_pts=$attacker_armor_left, torps=$attacker_torps_left WHERE ship_id=$shipinfo[ship_id]");
db_op_result($debug_query,__LINE__,__FILE__);

$l_sf_lreport = str_replace("[armor]", "<font color=#ffffff>" . NUMBER($armor_lost) . "</font>", $l_sf_lreport);
$l_sf_lreport = str_replace("[fighters]", "<font color=#ffffff>" . NUMBER($fighters_lost) . "</font>", $l_sf_lreport);
$l_sf_lreport = str_replace("[torps]", "<font color=#ffffff>" . NUMBER($playertorpnum) . "</font>", $l_sf_lreport);

echo "<table align=\"center\"><tr><td><font color=\"#ff0000\"><b>$l_sf_lreport<b></font></td></tr></table>";

if ($attacker_armor_left < 1)
{
	echo $l_sf_shipdestroyed;

	$inputtype[0] = "[player]";
	$inputdata[0] = $playerinfo['character_name'];
	$inputtype[1] = "[sector]";
	$inputdata[1] = "<a href=main.php?move_method=real&engage=1&destination=$sectorname>$sectorname</a>";
	message_defense_owner($sector, "l_sf_sendlog2", "lang_sector_fighters.inc", "fighters", $inputtype, $inputdata);

	if ($shipdevice['dev_escapepod']['amount'] == 1) 
	{
		playerlog($playerinfo['player_id'], "LOG5_DEFS_KABOOM", "$destination|1");

		echo $l_sf_escape;
		player_ship_destroyed($shipinfo['ship_id'], $playerinfo['player_id'], $playerinfo['rating'], $planet_owner['player_id'], $planet_owner['rating'], "killedSDpod", "Y");

		cancel_bounty($playerinfo['player_id']);
		echo $l_global_mmenu;
		include ("footer.php");
		die();
		
	}
	else
	{ 
		playerlog($playerinfo['player_id'], "LOG5_DEFS_KABOOM", "$destination|0");
		cancel_bounty($playerinfo['player_id']);
		db_kill_player($playerinfo['player_id'], $planet_owner['player_id'], $planet_owner['rating'], "killedSD", "Y");
		echo $l_global_mmenu;
		include ("footer.php");
		die();
		
	}		 
}

