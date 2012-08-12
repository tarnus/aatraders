<?php
if (!function_exists('sector_defense_battle')) {

	function sector_defense_battle($fighter_id, $addfighters, $addmines)
	{
		global $db_prefix, $db, $playerinfo, $shipinfo, $planetinfo;

		$resultSDb = $db->Execute("SELECT {$db_prefix}sector_defense.* from {$db_prefix}sector_defense, {$db_prefix}players WHERE 
		{$db_prefix}sector_defense.sector_id=$shipinfo[sector_id] and {$db_prefix}sector_defense.player_id != '$playerinfo[player_id]'
		and (({$db_prefix}players.player_id = {$db_prefix}sector_defense.player_id) and ({$db_prefix}players.team != $playerinfo[team] or $playerinfo[team] = 0))");
		db_op_result($resultSDb,__LINE__,__FILE__);

		if($resultSDb->recordcount() > 0)
		{
			$has_fighters = 0;
			$attacker_highjammer=0;
			$attacker_highcloak = 0;
			$attacker_highsensor = 0;
			$attacker_highfighter = 0;
			$attacker_hightorps = 0;

			$fm_owner = $planetinfo['owner'];
			$resultSDc = $db->Execute("SELECT * from {$db_prefix}players  WHERE player_id='$fm_owner'");
			db_op_result($resultSDc,__LINE__,__FILE__);
			if ($resultSDc > 0)
			{
			   	$attacker_fighterowner= $resultSDc->fields['team'];
			}

			$result4 = $db->SelectLimit("SELECT sector_defense_cloak from {$db_prefix}planets where (owner=$fm_owner or (team > 0 and team=$attacker_fighterowner)) and base='Y' and sector_id=$shipinfo[sector_id] order by sector_defense_cloak DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;
			if ($attacker_highcloak < $planets['sector_defense_cloak']){
				$attacker_highcloak=$planets['sector_defense_cloak'];
			}
			$result4->close();

			$result4 = $db->SelectLimit("SELECT sector_defense_sensors from {$db_prefix}planets where (owner=$fm_owner or (team > 0 and team=$attacker_fighterowner)) and base='Y' and sector_id=$shipinfo[sector_id] order by sector_defense_sensors DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;
			if ($attacker_highsensor < $planets['sector_defense_sensors']){
				$attacker_highsensor=$planets['sector_defense_sensors'];
			}
			$result4->close();

			$result4 = $db->SelectLimit("SELECT sector_defense_weapons, owner from {$db_prefix}planets where (owner=$fm_owner or (team > 0 and team=$attacker_fighterowner)) and base='Y' and sector_id=$shipinfo[sector_id] order by sector_defense_weapons DESC", 1);
			db_op_result($result4,__LINE__,__FILE__);
			$planets = $result4->fields;
			if ($attacker_highfighter < $planets['sector_defense_weapons']){
				$attacker_highfighter=$planets['sector_defense_weapons'];
				$attacker_hightorps=$planets['sector_defense_weapons'];
			}
			$result4->close();

			$resultSDb->MoveNext();

			//$attackerlowpercent = ecmcheck($highcloak, $shipinfo['sensors'], $attack_run_modifier);
			//$targetlowpercent = ecmcheck($shipinfo['ecm'], $highsensor, -$attack_run_modifier);
			$attackerlowpercent = ecmcheck($defender_highcloak, $attacker_highsensor, $attack_run_modifier + floor(($attacker_highfighter - $defender_highfighter) * $attack_run_engine_modifier));
			$targetlowpercent = ecmcheck($attacker_highcloak, $defender_highsensor, -($attack_run_modifier + floor(($attacker_highfighter - $defender_highfighter) * $attack_run_engine_modifier)));

			$targetshiptorp_launchers = $targetship['torp_launchers'];
			$targetshipfighter = $targetship['fighter'];
			$targetname = "Sector Defense";

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

			// The closer the number of sector fighters get to what is needed to possibly destroy the attacking
			// ship the less effective the attacking ship fighters and torps.  The attacker will then be required
			// to do a normal attack because A&R will have become useless.
			$max_fighters = max(NUM_FIGHTERS($shipinfo['fighter']), $attacker_fighters_left);
			$max_torps = max(NUM_TORPEDOES($shipinfo['torp_launchers']), $attacker_torps_left);
			$max_armor = max(NUM_armor($shipinfo['armor']), $attacker_armor_left);

			$low_end_scale = round((($max_fighters * $fighter_hit_pts) + ($max_torps * $torp_hit_pts) + ($max_armor * $ship_armor_hit_pts)) / $fighter_damage_all);

			if($low_end_scale < $target_fighters_left)
			{
				$attacker_ratio = 1 - ($low_end_scale / $target_fighters_left);
				if($attacker_ratio <= 0.5)
				{
					$attacker_torps_left = round($attacker_torps_left * $attacker_ratio);
					$attacker_fighters_left = round($attacker_fighters_left * $attacker_ratio);
				}
			}
			else
			{
				$attacker_torps_left = 0;
				$attacker_fighters_left = 0;
			}

			$result5 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=". $fm_owner . "", 1);
			db_op_result($result5,__LINE__,__FILE__);
			$planet_owner = $result5->fields;

			// If the attacker would get a bounty by attacking the most powerful planet in the sector then their A&R is useless.
			$isfedbounty = planet_bounty_check($playerinfo, $destination, $planet_owner, 0);

			if($isfedbounty > 0)
			{
				$attacker_torps_left = 0;
				$attacker_fighters_left = 0;
			}

			// Stage 1 fighter to fighter Exchange

			echo "<table width=\"75%\" border=\"1\" cellspacing=\"1\" cellpadding=\"4\" align=center bgcolor=\"#000000\">
			<tr><td colspan=2 align=center><b><font  color=#00ff00>$l_att_fighters</font></b><tr><td width=50%>";

			if($target_fighters_left != 0)
			{
				$target_fighter_damage = calc_damage($target_fighters_left, $fighter_damage_all, $targetlowpercent, $defender_highfighter, $attacker_highfighter);

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
				$attack_fighter_damage = calc_damage($attacker_fighters_left, $fighter_damage_all, $attackerlowpercent, $attacker_highfighter, $defender_highfighter);

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
				$target_fighter_damage = calc_damage($target_fighters_left2, $fighter_damage_all, $targetlowpercent, $defender_highfighter, $attacker_hightorps);

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
				$attack_fighter_damage = calc_damage($attacker_fighters_left2, $fighter_damage_all, $attackerlowpercent, $attacker_highfighter, $defender_hightorps);

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
				$attack_torp_damage = calc_damage($attacker_torps_left, $torp_damage_all, $attackerlowpercent, $attacker_hightorps, $defender_highfighter);

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

			$total_sector_mines_lost = $total_sector_mines - $target_torps_left;
			$defenses['mines'] = $target_torps_left;
			explode_mines($destination,$total_sector_mines_lost);
			$fighterslost = $defenses['fighters'] - $target_fighters_left;


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

			playerlog($playerinfo['player_id'], "LOG5_DEFS_DESTROYED_F", "$fighterslost|$destination");

			$armor_lost = max(($shipinfo['armor_pts'] - $attacker_armor_left), 0);
			$fighters_lost = max(($shipinfo['fighters'] - $attacker_fighters_left2), 0);
			$playertorpnum = max(($shipinfo['torps'] - $attacker_torps_left), 0);

			calc_internal_damage($shipinfo['ship_id'], 0, $armor_lost / $shipinfo['armor_pts']);
			$debug_query = $db->Execute ("UPDATE {$db_prefix}ships SET fighters=$attacker_fighters_left2, armor_pts=$attacker_armor_left, torps=$attacker_torps_left WHERE ship_id=$shipinfo[ship_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$l_sf_lreport = str_replace("[armor]", "<font color=#ffffff>" . NUMBER($armor_lost) . "</font>", $l_sf_lreport);
			$l_sf_lreport = str_replace("[fighters]", "<font color=#ffffff>" . NUMBER($fighters_lost) . "</font>", $l_sf_lreport);
			$l_sf_lreport = str_replace("[torps]", "<font color=#ffffff>" . NUMBER($playertorpnum) . "</font>", $l_sf_lreport);

			echo "<table align=\"center\"><tr><td><font color=\"#ff0000\"><b>$l_sf_lreport<b></font></td></tr></table>";
		}
		else
		{
			if ($addfighters > 0)
			{
				if ($fighter_id != 0)
				{
					$fighter_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $addfighters " .
												"where defense_id = $fighter_id");
					db_op_result($fighter_query,__LINE__,__FILE__);
				}
				else
				{
					$fighter_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
												"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
												"($planetinfo[owner], $shipinfo[sector_id], 'fighters',$addfighters, 'Sector_Fighter')");
					db_op_result($fighter_query,__LINE__,__FILE__);
				}
			}

			if ($addmines > 0)
			{
				$res = $db->Execute("SELECT * from {$db_prefix}sector_defense where defense_type = 'mines' and player_id=$planetinfo[owner] and sector_id=$shipinfo[sector_id]");
				$row = $res->fields;
				$res->close();
				if ($row['defense_id'] != 0)
				{
					$mines_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $addmines " .
												"where defense_id = $row[defense_id]");
					db_op_result($mines_query,__LINE__,__FILE__);
				}
				else
				{
					$mines_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
												"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
												"($planetinfo[owner], $shipinfo[sector_id], 'mines',$addmines, 'Sector_Mine')");
					db_op_result($mines_query,__LINE__,__FILE__);
				}
			}
		}
	}
}
?>
