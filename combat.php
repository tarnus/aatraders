<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: combat.php

if (preg_match("/combat.php/i", $_SERVER['PHP_SELF'])) 
{ 
		 echo "You can not access this file directly!"; 
		 die(); 
} 
include ("globals/get_player.inc");

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Combat Start:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " (id: $playerinfo[player_id]) Attacker Score: " . $debug_attack['attackerscore'] . ", Owns Sector: " . $debug_attack['isowner'] . ",  Opposite Alignment: " . $debug_attack['isopposite'] . ", Attack Ratio: " . $debug_attack['ratio'] . ", <br>
$l_cmb_beams:<B> ".$attacker_beam_energy."</B>, $l_cmb_fighters: <B>".$attackerfighters."</B>, $l_cmb_shields: <B>$attacker_shield_energy</B>, $l_cmb_torps: <B>$attackertorps</B>. $l_cmb_armor: <B>$attackerarmor</B>
<br>Shield Tech: $shipinfo[shields] , Armor Tech: $shipinfo[armor] , Torp Tech: $shipinfo[torp_launchers] , Beam Tech: $shipinfo[beams] , Fighter Bay: $shipinfo[fighter]<br>
<br>Defender ".$targetname . " (id: $targetinfo[player_id]) Target Score: " . $debug_attack['targetscore'] . ", Has Bounty: " . $debug_attack['hasbounty'] . ", Target Turns: " . $debug_attack['turns'] . ", <br>
$l_cmb_beams=<B>".$target_beam_energy."</B>, $l_cmb_fighters: <B>".$targetfighters."</B>, $l_cmb_shields: <B>$target_shield_energy</B>, $l_cmb_torps: <B>$targettorps</B>. $l_cmb_armor: <B>$targetarmor</B>
<br>Shield Tech: $targetshipshields , Armor Tech: $targetshiparmor , Torp Tech: $targetshiptorp_launchers , Beam Tech: $targetshipbeams , Fighter Bay: $targetshipfighter , Base Factor: $base_factor");

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Combat Class Values:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " fighter_damage_shields:<B> ".$fighter_damage_shields.
"</B>, fighter_damage_all: <B>".$fighter_damage_all."</B>, fighter_hit_pts: <B>$fighter_hit_pts</B>, beam_damage_shields: <B>$beam_damage_shields</B>. $beam_damage_all: <B>$beam_damage_all</B>
<br>torp_damage_shields: <B>$torp_damage_shields</B> , torp_damage_all: <B>$torp_damage_all</B> , torp_hit_pts: <B>$torp_hit_pts</B> , ship_shield_hit_pts: <B>$ship_shield_hit_pts</B> , ship_armor_hit_pts: <B>$ship_armor_hit_pts</B><br>");

echo "
		<CENTER>
		<table width='75%' border='0' bgcolor=\"#000000\">
		<tr><td colspan=6 align=center><hr></td></tr>
		<tr ALIGN='CENTER'>
		<td width='9%' height='27'></td>
		<td width='12%' height='27'><FONT COLOR='WHITE'>$l_cmb_beams</FONT></td>
		<td width='17%' height='27'><FONT COLOR='WHITE'>$l_cmb_fighters</FONT></td>
		<td width='18%' height='27'><FONT COLOR='WHITE'>$l_cmb_shields</FONT></td>
		<td width='11%' height='27'><FONT COLOR='WHITE'>$l_cmb_torps</FONT></td>
		<td width='11%' height='27'><FONT COLOR='WHITE'>$l_cmb_armor</FONT></td>
		</tr>
		<tr ALIGN='CENTER'>
		<td width='9%'> <FONT COLOR='yellow'><B>$l_cmb_you</B></td>
		<td width='12%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_beam_energy)."&nbsp;</B></FONT></td>
		<td width='17%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attackerfighters)."&nbsp;</B></FONT></td>
		<td width='18%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_shield_energy)."&nbsp;</B></FONT></td>
		<td width='11%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attackertorps)."&nbsp;</B></FONT></td>
		<td width='11%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attackerarmor)."&nbsp;</B></FONT></td>
		</tr>";

echo "	</tr>
		<tr><td colspan=6 align=center>&nbsp;</td></tr>
		</table>
		</CENTER>
";

// Stage 1 Beam Exchange
echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_att_beams</font></b></td></tr>
	<tr>
		<td width=50%>";

if($attacker_beam_energy != 0)
{
	$attack_fire_damage = calc_damage($attacker_beam_energy, $beam_damage_shields, $attackerlowpercent, $shipinfo['beams'], $targetshipshields);

	if($attack_fire_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourbeamfail1</font><br>$l_cmb_yourbeamfail2<font color='#ffffff'>" . (100 - $attack_fire_damage[2]) . "</font>$l_cmb_yourbeamfail3</b></font><br><br>";
	}

	//
	$target_shields = calc_failure($target_shield_energy, $targetshipshields, $shipinfo['beams']);

	$target_shield_hit_pts = $target_shield_energy * $ship_shield_hit_pts;

	//
	$target_armor = calc_failure($targetarmor, $targetshiparmor, $shipinfo['beams']);

	$target_armor_hit_pts = $targetarmor * $ship_armor_hit_pts;

	$attacker_energy_left = $attack_fire_damage[1];

	if($attack_fire_damage[0] > $target_shield_hit_pts)
	{
		$attack_fire_damage[0] = $attack_fire_damage[0] - $target_shield_hit_pts;
		if($target_shield_energy > 0)
			echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_shits <FONT COLOR='yellow'>" . NUMBER($target_shield_energy) . "</font> $l_att_dmg.</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_att_sdown</b></font><br><br>";
		$target_shields_left = 0;
		$attacker_energy_left = floor($attack_fire_damage[0] / $beam_damage_shields);
		$attack_fire2_damage = calc_damage($attacker_energy_left, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $targetshiparmor);
		$attacker_energy_left += $attack_fire2_damage[1];

		if($attack_fire2_damage[2] > 0){
			echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourbeamfail1</font><br>$l_cmb_yourbeamfail2<font color='#ffffff'>" . (100 - $attack_fire2_damage[2]) . "</font>$l_cmb_yourbeamfail3</b></font><br><br>";
		}

		if($attack_fire2_damage[0] > $target_armor_hit_pts)
		{
			$attack_fire2_damage[0] = $attack_fire2_damage[0] - $target_armor_hit_pts;
			$attack_damage = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
				echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_ashit <FONT COLOR='yellow'>" . NUMBER($attack_damage) . "</font> $l_att_dmg.</b></font><br>";
			echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_att_sarm</b></font><br><br>";
			$attacker_energy_left += floor($attack_fire2_damage[0] / $beam_damage_all);
			$target_armor_left = 0;
		}
		else
		{
			$target_armor_hit_pts = $target_armor_hit_pts - $attack_fire2_damage[0];
			$target_armor_used = floor($attack_fire2_damage[0] / $ship_armor_hit_pts);
			echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_ashit <FONT COLOR='yellow'>" . NUMBER($target_armor_used) . "</font> $l_att_dmg.</b></font><br>";
			$target_armor_left = floor($target_armor_hit_pts / $ship_armor_hit_pts);
		}
	}
	else
	{
		$target_shield_hit_pts = $target_shield_hit_pts - $attack_fire_damage[0];
		$target_shields_used = floor($attack_fire_damage[0] / $ship_shield_hit_pts);
		echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_shits <FONT COLOR='yellow'>" . NUMBER($target_shields_used) . "</font> $l_att_dmg.</b></font><br>";
		$target_shields_left = floor($target_shield_hit_pts / $ship_shield_hit_pts);
		$target_armor_left = $targetarmor;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anobeams</font><b><br><br>";
	$target_shields_left = $target_shield_energy;
	$target_armor_left = $targetarmor;
	$attacker_energy_left = 0;
}

if($attack_beamtofighter_dmg != 0)
{
	$attack_fighter_damage = calc_damage($attack_beamtofighter_dmg, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $targetshipfighter);

	if($attack_fighter_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourbeamfail1</font><br>$l_cmb_yourbeamfail2<font color='#ffffff'>" . (100 - $attack_fighter_damage[2]) . "</font>$l_cmb_yourbeamfail3</b></font><br><br>";
	}

	$attacker_energy_left += $attack_fighter_damage[1];

	$target_fighter_hit_pts = $targetfighters * $fighter_hit_pts;
	if($attack_fighter_damage[0] > $target_fighter_hit_pts)
	{
		$attack_fighter_damage[0] = $attack_fighter_damage[0] - $target_fighter_hit_pts;
		if($targetfighters > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($targetfighters) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostf</b></font><br><br>";
		$attacker_energy_left += floor($attack_fighter_damage[0] / $beam_damage_all);
		$target_fighters_left = 0;
	}
	else
	{
		$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_fighter_damage[0];
		$target_fighters_used = floor($attack_fighter_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		$target_fighters_left = floor($target_fighter_hit_pts / $fighter_hit_pts);
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anobeamsf</font><b><br><br>";
	$target_fighters_left = $targetfighters;
}

if($attack_beamtotorp_dmg != 0)
{
	$attack_torp_damage = calc_damage($attack_beamtotorp_dmg, $beam_damage_all, $attackerlowpercent, $shipinfo['beams'], $targetshiptorp_launchers);

	if($attack_torp_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourbeamfail1</font><br>$l_cmb_yourbeamfail2<font color='#ffffff'>" . (100 - $attack_torp_damage[2]) . "</font>$l_cmb_yourbeamfail3</b></font><br><br>";
	}

	$attacker_energy_left += $attack_torp_damage[1];

	$target_torp_hit_pts = $targettorps * $torp_hit_pts;
	if($attack_torp_damage[0] > $target_torp_hit_pts)
	{
		$attack_torp_damage[0] = $attack_torp_damage[0] - $target_torp_hit_pts;
		if($targettorps > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($targettorps) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_ethit</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostt</b></font><br><br>";
		$attacker_energy_left += floor($attack_torp_damage[0] / $beam_damage_all);
		$target_torps_left = 0;
	}
	else
	{
		$target_torp_hit_pts = $target_torp_hit_pts - $attack_torp_damage[0];
		$target_torps_used = floor($attack_torp_damage[0] / $torp_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_torps_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_ethit</b></font><br>";
		$target_torps_left = floor($target_torp_hit_pts / $torp_hit_pts);
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anobeamst</font><b><br><br>";
	$target_torps_left = $targettorps;
}

echo "</td><td width=50%>";

if($target_beam_energy != 0)
{
	$target_fire_damage = calc_damage($target_beam_energy, $beam_damage_shields, $targetlowpercent, $targetshipbeams, $shipinfo['shields']);

	if($target_fire_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemybeamfailshield</b></font><br><br>";
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_fire_damage[0] = $target_fire_damage[0] * $defender_lucky_multiplier;
		echo "<br><font color='yellow' ><b>$l_att_luckybeams $defender_lucky_multiplier $l_att_luckytimes</b></font><br><br>";
	}

	$target_energy_left = $target_fire_damage[1];

	//
	$attacker_shields = calc_failure($attacker_shield_energy, $shipinfo['shields'], $targetshipbeams);

	$attack_shield_hit_pts = $attacker_shield_energy * $ship_shield_hit_pts;

	//
	$attacker_armor = calc_failure($attackerarmor, $shipinfo['armor'], $targetshipbeams);

	$attack_armor_hit_pts = $attackerarmor * $ship_armor_hit_pts;
	if($target_fire_damage[0] > $attack_shield_hit_pts)
	{
		$target_fire_damage[0] = $target_fire_damage[0] - $attack_shield_hit_pts;
		if($attacker_shield_energy > 0)
			echo "<font color='#00ff00'><b>$l_att_yhits <FONT COLOR='yellow'>" . NUMBER($attacker_shield_energy) . "</font> $l_att_dmg.</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ydown</b></font><br><br>";
		$attacker_shields_left = 0;
		$target_energy_left += floor($target_fire_damage[0] / $beam_damage_shields);
		$target_fire2_damage = calc_damage($target_energy_left, $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['armor']);
		$target_energy_left += $target_fire2_damage[1];

		if($target_fire2_damage[2] == 100){
			echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemybeamfailarmor</b></font><br><br>";
		}

		if($target_fire2_damage[0] > $attack_armor_hit_pts)
		{
			$target_fire2_damage[0] = $target_fire2_damage[0] - $attack_armor_hit_pts;
			$attack_damage = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
				echo "<font color='#00ff00'><b>$l_att_ayhit <FONT COLOR='yellow'>" . NUMBER($attack_damage) . "</font> $l_att_dmg.</b></font><br>";
			echo "<br><font color='#ff0000' ><b>$l_att_yarm</b></font><br><br>";
			$target_energy_left += floor($target_fire2_damage[0] / $beam_damage_all);
			$attacker_armor_left = 0;
		}
		else
		{
			$attack_armor_hit_pts = $attack_armor_hit_pts - $target_fire2_damage[0];
			$attacker_armor_used = floor($target_fire2_damage[0] / $ship_armor_hit_pts);
			echo "<font color='#00ff00'><b>$l_att_ayhit <FONT COLOR='yellow'>" . NUMBER($attacker_armor_used) . "</font> $l_att_dmg.</b></font><br>";
			$attacker_armor_left = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
		}
	}
	else
	{
		$attack_shield_hit_pts = $attack_shield_hit_pts - $target_fire_damage[0];
		$attacker_shields_used = floor($target_fire_damage[0] / $ship_shield_hit_pts);
		echo "<font color='#00ff00'><b>$l_att_yhits <FONT COLOR='yellow'>" . NUMBER($attacker_shields_used) . "</font> $l_att_dmg.</b></font><br>";
		$attacker_shields_left = floor($attack_shield_hit_pts / $ship_shield_hit_pts);
		$attacker_armor_left = $attackerarmor;
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tnobeams</font><b><br><br>";
	$attacker_shields_left = $attacker_shield_energy;
	$attacker_armor_left = $attackerarmor;
	$target_energy_left = 0;
}

if($target_beamtofighter_dmg != 0)
{
	$target_fighter_damage = calc_damage($target_beamtofighter_dmg, $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['fighters']);

	if($target_fighter_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemybeamfailfighter</b></font><br><br>";
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] * $defender_lucky_multiplier;
		echo "<br><font color='yellow' ><b>$l_att_luckybeams $defender_lucky_multiplier $l_att_luckytimes</b></font><br><br>";
	}

	$target_energy_left += $target_fighter_damage[1];

	$attack_fighter_hit_pts = $attackerfighters * $fighter_hit_pts;
	if($target_fighter_damage[0] > $attack_fighter_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_fighter_hit_pts;
		if($attackerfighters > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attackerfighters) . "</font> $l_att_yfhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ylostf</b></font><br><br>";
		$attacker_fighters_left = 0;
	}
	else
	{
		$attack_fighter_hit_pts = $attack_fighter_hit_pts - $target_fighter_damage[0];
		$attacker_fighters_used = floor($target_fighter_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attacker_fighters_used) . "</font> $l_att_yfhit</b></font><br>";
		$attacker_fighters_left = floor($attack_fighter_hit_pts / $fighter_hit_pts);
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tnobeamsf</font><b><br><br>";
	$attacker_fighters_left = $attackerfighters;
}

if($target_beamtotorp_dmg != 0)
{
	$target_torp_damage = calc_damage($target_beamtotorp_dmg, $beam_damage_all, $targetlowpercent, $targetshipbeams, $shipinfo['torp_launchers']);

	if($target_torp_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemybeamfailtorp</b></font><br><br>";
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_torp_damage[0] = $target_torp_damage[0] * $defender_lucky_multiplier;
		echo "<br><font color='yellow' ><b>$l_att_luckybeams $defender_lucky_multiplier $l_att_luckytimes</b></font><br><br>";
	}

	$target_energy_left += $target_torp_damage[1];

	$attack_torp_hit_pts = $attackertorps * $torp_hit_pts;
	if($target_torp_damage[0] > $attack_torp_hit_pts)
	{
		$target_torp_damage[0] = $target_torp_damage[0] - $attack_torp_hit_pts;
		if($attackertorps > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attackertorps) . "</font> $l_att_ythit.</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ylostt</b></font><br><br>";
		$attacker_torps_left = 0;
	}
	else
	{
		$attack_torp_hit_pts = $attack_torp_hit_pts - $target_torp_damage[0];
		$attacker_torps_used = floor($target_torp_damage[0] / $torp_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attacker_torps_used) . "</font> $l_att_ythit</b></font><br>";
		$attacker_torps_left = floor($attack_torp_hit_pts / $torp_hit_pts);
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tnobeamst</font><b><br><br>";
	$attacker_torps_left = $attackertorps;
}

echo "</td></tr></table>";


echo "
			<CENTER>
			<table width='75%' border='0' bgcolor=\"#000000\">
			<tr><td colspan=6 align=center><hr></td></tr>
			<tr ALIGN='CENTER'>
			<td width='9%' height='27'></td>
			<td width='12%' height='27'><FONT COLOR='WHITE'>$l_cmb_beams</FONT></td>
			<td width='17%' height='27'><FONT COLOR='WHITE'>$l_cmb_fighters</FONT></td>
			<td width='18%' height='27'><FONT COLOR='WHITE'>$l_cmb_shields</FONT></td>
			<td width='11%' height='27'><FONT COLOR='WHITE'>$l_cmb_torps</FONT></td>
			<td width='11%' height='27'><FONT COLOR='WHITE'>$l_cmb_armor</FONT></td>
			</tr>
			<tr ALIGN='CENTER'>
			<td width='9%'> <FONT COLOR='yellow'><B>$l_cmb_you</B></td>
			<td width='12%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_energy_left)."&nbsp;</B></FONT></td>
			<td width='17%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_fighters_left)."&nbsp;</B></FONT></td>
			<td width='18%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_shields_left)."&nbsp;</B></FONT></td>
			<td width='11%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_torps_left)."&nbsp;</B></FONT></td>
			<td width='11%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_armor_left)."&nbsp;</B></FONT></td>
			</tr>";

echo "			<tr><td colspan=6 align=center>&nbsp;</td></tr>
			</table>
			</CENTER>
	";

// Stage 2 fighter Exchange

echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_att_fighters</font></b><tr><td width=50%>";

if($attacker_fighters_left != 0)
{
	$attack_fighter_damage = calc_damage($attacker_fighters_left, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $targetshipfighter);

	if($attack_fighter_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourfighterfail1</font><br>$l_cmb_yourfighterfail2<font color='#ffffff'>" . (100 - $attack_fighter_damage[2]) . "</font>$l_cmb_yourfighterfail3</b></font><br><br>";
	}

	$target_fighter_hit_pts = $target_fighters_left * $fighter_hit_pts;
	if($attack_fighter_damage[0] > $target_fighter_hit_pts)
	{
		$attack_fighter_damage[0] = $attack_fighter_damage[0] - $target_fighter_hit_pts;
		if($target_fighters_left > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_left) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostf</b></font><br><br>";
		$target_fighters_left2 = 0;
		$attacker_fighters_left2 = floor($attack_fighter_damage[0] / $fighter_damage_all);
		$attack_fighter2_damage = calc_damage($attacker_fighters_left2, $fighter_damage_all, $attackerlowpercent, $shipinfo['fighter'], $targetshiptorp_launchers);

		if($attack_fighter2_damage[2] > 0){
			echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourfighterfail1</font><br>$l_cmb_yourfighterfail2<font color='#ffffff'>" . (100 - $attack_fighter2_damage[2]) . "</font>$l_cmb_yourfighterfail3</b></font><br><br>";
		}

		$target_torp_hit_pts = $target_torps_left * $torp_hit_pts;
		if($attack_fighter2_damage[0] > $target_torp_hit_pts)
		{
			$attack_fighter2_damage[0] = $attack_fighter2_damage[0] - $target_torp_hit_pts;
			$attack_damage = floor($target_torp_hit_pts / $torp_hit_pts);
			if($attack_damage > 0)
				echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attack_damage) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_ethit</b></font><br>";
			echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font> $l_att_lostt</b></font><br><br>";
			$target_torps_left2 = 0;
		}
		else
		{
			$target_torp_hit_pts = $target_torp_hit_pts - $attack_fighter2_damage[0];
			$target_torps_used = floor($attack_fighter2_damage[0] / $torp_hit_pts);
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_torps_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_ethit</b></font><br>";
			$target_torps_left2 = floor($target_torp_hit_pts / $torp_hit_pts);
		}
	}
	else
	{
		$target_fighter_hit_pts = $target_fighter_hit_pts - $attack_fighter_damage[0];
		$target_fighters_used = floor($attack_fighter_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($target_fighters_used) . "</font> $l_att_of <font color=white>" . $targetname . "</font>$l_att_efhit</b></font><br>";
		$target_fighters_left2 = floor($target_fighter_hit_pts / $fighter_hit_pts);
		$target_torps_left2 = $target_torps_left;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anofighters</font><b><br><br>";
	$target_fighters_left2 = $target_fighters_left;
	$target_torps_left2 = $target_torps_left;
}

echo "</td><td width=50%>";

if($target_fighters_left != 0)
{
	$target_fighter_damage = calc_damage($target_fighters_left, $fighter_damage_all, $targetlowpercent, $targetshipfighter, $shipinfo['fighter']);

	if($target_fighter_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemyfighterfailfighter</b></font><br><br>";
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] * $defender_lucky_multiplier;
		echo "<br><font color='yellow' ><b>$l_att_luckyfighters $defender_lucky_multiplier $l_att_luckytimes</b></font><br><br>";
	}

	$attack_fighter_hit_pts = $attacker_fighters_left * $fighter_hit_pts;
	if($target_fighter_damage[0] > $attack_fighter_hit_pts)
	{
		$target_fighter_damage[0] = $target_fighter_damage[0] - $attack_fighter_hit_pts;
		if($attacker_fighters_left > 0)
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attacker_fighters_left) . "</font> $l_att_yfhit</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ylostf</b></font><br><br>";
		$attacker_fighters_left2 = 0;
		$target_fighters_left3 = floor($target_fighter_damage[0] / $fighter_damage_all);
		$target_fighter2_damage = calc_damage($target_fighters_left3, $fighter_damage_all, $targetlowpercent, $targetshipfighter, $shipinfo['torp_launchers']);

		if($target_fighter2_damage[2] == 100){
			echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemyfighterfailtorp</b></font><br><br>";
		}

		$attack_torp_hit_pts = $attacker_torps_left * $torp_hit_pts;
		if($target_fighter2_damage[0] > $attack_torp_hit_pts)
		{
			$target_fighter2_damage[0] = $target_fighter2_damage[0] - $attack_torp_hit_pts;
			$attack_damage = floor($attack_torp_hit_pts / $torp_hit_pts);
			if($attack_damage > 0)
				echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attack_damage) . "</font> $l_att_ythit</b></font><br>";
			echo "<br><font color='#ff0000' ><b>$l_att_ylostt</b></font><br><br>";
			$attacker_torps_left2 = 0;
		}
		else
		{
			$attack_torp_hit_pts = $attack_torp_hit_pts - $target_fighter2_damage[0];
			$attack_torps_used = floor($target_fighter2_damage[0] / $torp_hit_pts);
			echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attack_torps_used) . "</font> $l_att_ythit</b></font><br>";
			$attacker_torps_left2 = floor($attack_torp_hit_pts / $torp_hit_pts);
		}
	}
	else
	{
		$attack_fighter_hit_pts = $attack_fighter_hit_pts - $target_fighter_damage[0];
		$attack_fighters_used = floor($target_fighter_damage[0] / $fighter_hit_pts);
		echo "<font color='#00ff00'><b><FONT COLOR='yellow'>" . NUMBER($attack_fighters_used) . "</font> $l_att_yfhit</b></font><br>";
		$attacker_fighters_left2 = floor($attack_fighter_hit_pts / $fighter_hit_pts);
		$attacker_torps_left2 = $attacker_torps_left;
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tfnoattack</font><b><br><br>";
	$attacker_fighters_left2 = $attacker_fighters_left;
	$attacker_torps_left2 = $attacker_torps_left;
}

echo "</td></tr></table>";

echo "
			<CENTER>
			<table width='75%' border='0' bgcolor=\"#000000\">
			<tr><td colspan=6 align=center><hr></td></tr>
			<tr ALIGN='CENTER'>
			<td width='9%' height='27'></td>
			<td width='12%' height='27'><FONT COLOR='WHITE'>$l_cmb_beams</FONT></td>
			<td width='17%' height='27'><FONT COLOR='WHITE'>$l_cmb_fighters</FONT></td>
			<td width='18%' height='27'><FONT COLOR='WHITE'>$l_cmb_shields</FONT></td>
			<td width='11%' height='27'><FONT COLOR='WHITE'>$l_cmb_torps</FONT></td>
			<td width='11%' height='27'><FONT COLOR='WHITE'>$l_cmb_armor</FONT></td>
			</tr>
			<tr ALIGN='CENTER'>
			<td width='9%'> <FONT COLOR='yellow'><B>$l_cmb_you</B></td>
			<td width='12%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_energy_left)."&nbsp;</B></FONT></td>
			<td width='17%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_fighters_left2)."&nbsp;</B></FONT></td>
			<td width='18%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_shields_left)."&nbsp;</B></FONT></td>
			<td width='11%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_torps_left2)."&nbsp;</B></FONT></td>
			<td width='11%'><FONT COLOR='RED'><B>&nbsp;".NUMBER($attacker_armor_left)."&nbsp;</B></FONT></td>
			</tr>";

echo "			<tr><td colspan=6 align=center>&nbsp;</td></tr>
			</table>
			</CENTER>
	";

// Stage 3 torp Exchange

echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" bgcolor=\"#000000\">
<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_att_torps</font></b><tr><td width=50%>";

if($attacker_torps_left2 != 0)
{
	$attack_torp_damage = calc_damage($attacker_torps_left2, $torp_damage_shields, $attackerlowpercent, $shipinfo['torp_launchers'], $targetshipshields);

	if($attack_torp_damage[2] > 0){
		echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourtorpfail1</font><br>$l_cmb_yourtorpfail2<font color='#ffffff'>" . (100 - $attack_torp_damage[2]) . "</font>$l_cmb_yourtorpfail3</b></font><br><br>";
	}

	//
	$target_shields = calc_failure($target_shields_left, $targetshipshields, $shipinfo['torp_launchers']);

	$target_shield_hit_pts = $target_shields_left * $ship_shield_hit_pts;

	//
	$target_armor = calc_failure($target_armor_left, $targetshiparmor, $shipinfo['torp_launchers']);

	$target_armor_hit_pts = $target_armor_left * $ship_armor_hit_pts;
	if($attack_torp_damage[0] > $target_shield_hit_pts)
	{
		$attack_torp_damage[0] = $attack_torp_damage[0] - $target_shield_hit_pts;
		if($target_shields_left > 0)
			echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_shits <FONT COLOR='yellow'>" . NUMBER($target_shields_left) . "</font> $l_att_dmg.</b></font><br>";
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_att_sdown</b></font><br><br>";
		$target_shields_left = 0;
		$attacker_torps_left2 = floor($attack_torp_damage[0] / $torp_damage_shields);
		$attack_torp2_damage = calc_damage($attacker_torps_left2, $torp_damage_all, $attackerlowpercent, $shipinfo['torp_launchers'], $targetshiparmor);

		if($attack_torp2_damage[2] > 0){
			echo "<br><font color='#00ff00'><b><font color='#ff0000'>$l_cmb_yourtorpfail1</font><br>$l_cmb_yourtorpfail2<font color='#ffffff'>" . (100 - $attack_torp2_damage[2]) . "</font>$l_cmb_yourtorpfail3</b></font><br><br>";
		}

		if($attack_torp2_damage[0] > $target_armor_hit_pts)
		{
			$attack_torp2_damage[0] = $attack_torp2_damage[0] - $target_armor_hit_pts;
			$attack_damage = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
				echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_ashit <FONT COLOR='yellow'>" . NUMBER($attack_damage) . "</font> $l_att_dmg.</b></font><br>";
			echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_att_sarm</b></font><br><br>";
			$attacker_torps_left = floor($attack_torp2_damage[0] / $torp_damage_all);
			$target_armor_left = 0;
		}
		else
		{
			$target_armor_hit_pts = $target_armor_hit_pts - $attack_torp2_damage[0];
			$target_armor_used = floor($attack_torp2_damage[0] / $ship_armor_hit_pts);
			echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_ashit <FONT COLOR='yellow'>" . NUMBER($target_armor_used) . "</font> $l_att_dmg.</b></font><br>";
			$target_armor_left = floor($target_armor_hit_pts / $ship_armor_hit_pts);
			$attacker_torps_left = 0;
		}
	}
	else
	{
		$target_shield_hit_pts = $target_shield_hit_pts - $attack_torp_damage[0];
		$target_shields_used = floor($attack_torp_damage[0] / $ship_shield_hit_pts);
		echo "<font color='#00ff00'><b><font color=white>" . $targetname . "</font>$l_att_shits <FONT COLOR='yellow'>" . NUMBER($target_shields_used) . "</font> $l_att_dmg.</b></font><br>";
		$target_shields_left = floor($target_shield_hit_pts / $ship_shield_hit_pts);
		$attacker_torps_left = 0;
	}
}
else
{
	echo "<br><b><font color='#ff0000'>$l_att_anotorps</font><b><br><br>";
	$attacker_torps_left = 0;
	$attack_torp_damage[1] = 0;
	$attack_torp2_damage[1] = 0;
}

$attacker_torps_left += ($attack_torp_damage[1] + $attack_torp2_damage[1]);

echo "</td><td width=50%>";

if($target_torps_left2 != 0)
{
	$target_torp_damage = calc_damage($target_torps_left2, $torp_damage_shields, $targetlowpercent, $targetshiptorp_launchers, $shipinfo['shields']);

	if($target_torp_damage[2] == 100){
		echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemytorpfailshields</b></font><br><br>";
	}

	if(mt_rand(1, 100) <= $defender_lucky_percentage)
	{
		$target_torp_damage[0] = $target_torp_damage[0] * $defender_lucky_multiplier;
		echo "<br><font color='yellow' ><b>$l_att_luckytorps $defender_lucky_multiplier $l_att_luckytimes</b></font><br><br>";
	}

	//
	$attacker_shields = calc_failure($attacker_shields_left, $shipinfo['shields'], $targetshiptorp_launchers);

	$attack_shield_hit_pts = $attacker_shields_left * $ship_shield_hit_pts;

	//
	$attacker_armor = calc_failure($attacker_armor_left, $shipinfo['shields'], $targetshiptorp_launchers);

	$attack_armor_hit_pts = $attacker_armor_left * $ship_armor_hit_pts;
	if($target_torp_damage[0] > $attack_shield_hit_pts)
	{
		$target_torp_damage[0] = $target_torp_damage[0] - $attack_shield_hit_pts;
		if($attacker_shields_left > 0)
			echo "<font color='#00ff00'><b>$l_att_yhits <FONT COLOR='yellow'>" . NUMBER($attacker_shields_left) . "</font> $l_att_dmg.</b></font><br>";
		echo "<br><font color='#ff0000' ><b>$l_att_ydown</b></font><br><br>";
		$attacker_shields_left = 0;
		$target_torps_left2 = floor($target_torp_damage[0] / $torp_damage_shields);
		$target_torp2_damage = calc_damage($target_torps_left2, $torp_damage_all, $targetlowpercent, $targetshiptorp_launchers, $shipinfo['armor']);

		if($target_torp2_damage[2] == 100){
			echo "<br><font color='#ff0000' ><b><font color=white >" . $targetname . "</font>$l_cmb_enemytorpfailarmor</b></font><br><br>";
		}

		if($target_torp2_damage[0] > $attack_armor_hit_pts)
		{
			$target_torp2_damage[0] = $target_torp2_damage[0] - $attack_armor_hit_pts;
			$attack_damage = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
			if($attack_damage > 0)
				echo "<font color='#00ff00'><b>$l_att_ayhit <FONT COLOR='yellow'>" . NUMBER($attack_damage) . "</font> $l_att_dmg.</b></font><br>";
			echo "<br><font color='#ff0000' ><b>$l_att_yarm</b></font><br><br>";
			$target_torps_left = floor($target_torp2_damage[0] / $torp_damage_all);
			$attacker_armor_left = 0;
		}
		else
		{
			$attack_armor_hit_pts = $attack_armor_hit_pts - $target_torp2_damage[0];
			$attacker_armor_used = floor($target_torp2_damage[0] / $ship_armor_hit_pts);
			echo "<font color='#00ff00'><b>$l_att_ayhit <FONT COLOR='yellow'>" . NUMBER($attacker_armor_used) . "</font> $l_att_dmg.</b></font><br>";
			$attacker_armor_left = floor($attack_armor_hit_pts / $ship_armor_hit_pts);
			$target_torps_left = 0;
		}
	}
	else
	{
		$attack_shield_hit_pts = $attack_shield_hit_pts - $target_torp_damage[0];
		$attacker_shields_used = floor($target_torp_damage[0] / $ship_shield_hit_pts);
		echo "<font color='#00ff00'><b>$l_att_yhits <FONT COLOR='yellow'>" . NUMBER($attacker_shields_used) . "</font> $l_att_dmg.</b></font><br>";
		$attacker_shields_left = floor($attack_shield_hit_pts / $ship_shield_hit_pts);
		$target_torps_left = 0;
	}
}
else
{
	echo "<br><b><font color='#ff0000'><font color=white>" . $targetname . "</font> $l_att_tnotorps</font><b><br><br>";
	$target_torps_left = 0;
	$target_torp_damage[1] = 0;
	$target_torp2_damage[1] = 0;
}

$target_torps_left += ($target_torp_damage[1] + $target_torp2_damage[1]);

echo "</td></tr></table>";

adminlog("LOG0_ADMIN_COMBAT","<font color=yellow><B>Combat End:</B></font><BR>Attacker " . get_player($playerinfo['player_id']) . " $l_cmb_beams=<B>".$attacker_energy_left.
"</B>, $l_cmb_fighters=<B>".$attacker_fighters_left2."</B>, $l_cmb_shields: <B>$attacker_shields_left</B>, $l_cmb_torps: <B>$attacker_torps_left</B>. $l_cmb_armor=<B>$attacker_armor_left</B><br>Defender ".$targetname . " $l_cmb_beams=<B>".$target_energy_left.
"</B>, $l_cmb_fighters=<B>".$target_fighters_left2."</B>, $l_cmb_shields: <B>$target_shields_left</B>, $l_cmb_torps: <B>$target_torps_left</B>. $l_cmb_armor=<B>$target_armor_left</B>");

?>
