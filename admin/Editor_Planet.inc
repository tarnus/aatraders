<?php
// 2: Planet
// This tool will allow editing any planet in the game.

include ("globals/cleanjs.inc");

get_post_ifset("sector_defense_cloak_normal, sector_defense_sensors_normal, sector_defense_weapons_normal, cloak_normal, armor_normal, shields_normal, torp_launchers_normal, beams_normal, sensors_normal, fighter_normal, sector_defense_weapons, sector_defense_sensors, sector_defense_cloak, planet, operation, sector_id, defeated, name, base, owner, organics, ore, goods, energy, team, colonists, credits, fighters, torps, prod_organics, prod_ore, prod_goods, prod_energy, prod_fighters, prod_torp, fighter, sensors, beams, torp_launchers, shields, armor, armor_pts, cloak");

cleanjs('name');
echo $cleanjs;
echo "<tr><td><div align=\"center\">";
echo "<FORM ACTION=admin.php METHOD=POST>";
if (empty($planet))
{
	echo "<SELECT SIZE=15 NAME=planet>";
	$res = $db->Execute("SELECT planet_id, name, sector_id, character_name FROM {$db_prefix}planets LEFT JOIN {$db_prefix}players ON {$db_prefix}planets.owner = {$db_prefix}players.player_id ORDER BY name, sector_id");
	while (!$res->EOF)
	{
		$row = $res->fields;
		if ($row['name'] == "")
		{
			$row['name'] = "Unnamed";
		}

		if ($row['character_name'] == NULL)
		{
			$row['character_name'] = "No one";
		}

		echo "<OPTION VALUE=$row[planet_id]> $row[name] in sector $row[sector_id], owned by $row[character_name]</OPTION>\n";
		$res->MoveNext();
	}

	echo "</SELECT>";
	echo "&nbsp;<INPUT TYPE=\"submit\" NAME=command VALUE=\"Edit\">";
}
else
{
	if (empty($operation))
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE planet_id=$planet");
		$row = $res->fields;

		echo "<TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2 width=\"100%\">";
		echo "<TR><TD>			  Planet ID  	</TD><TD><FONT COLOR=#66FF00>$planet</FONT></TD>";
		echo "<TD ALIGN=Right>	  Sector ID  	<INPUT TYPE=TEXT SIZE=5 NAME=sector_id VALUE=\"$row[sector_id]\"></TD>";
		echo "<TD ALIGN=Right>	  Defeated   	<INPUT TYPE=CHECKBOX NAME=defeated VALUE=ON " . CHECKED($row['defeated']) . "></TD>
		<TD>			  Planet Owner	</TD><TD>";
		echo "<SELECT SIZE=1 NAME=owner>";
		$ressuba = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players ORDER BY character_name");
		echo "<OPTION VALUE=0>No One</OPTION>";
		while (!$ressuba->EOF)
		{
			$rowsuba = $ressuba->fields;
			if ($rowsuba[player_id] == $row[owner])
			{ 
				echo "<OPTION SELECTED=$rowsuba[player_id] VALUE=$rowsuba[player_id]>$rowsuba[character_name]</OPTION>";
			} 
			else 
			{  
				echo "<OPTION VALUE=$rowsuba[player_id]>$rowsuba[character_name]</OPTION>";
			}

			$ressuba->MoveNext();
		}

		echo "</SELECT></TD></TR>";
		echo "<TR><TD>			  Planet Name	</TD><TD><INPUT TYPE=TEXT SIZE=15 NAME=name VALUE=\"$row[name]\"></TD>";
		echo "<TD ALIGN=Right>	  Base	   	<INPUT TYPE=CHECKBOX NAME=base VALUE=ON " . CHECKED($row['base']) . "></TD>";
		echo "<TD colspan=\"2\">			  Planet Team	</TD><TD><INPUT TYPE=TEXT SIZE=5 NAME=team VALUE=\"$row[team]\"></TD></tr></TABLE>";
		echo "<br><TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2 width=\"100%\">";
		echo "<TR>";
		echo "<TD ALIGN=Right>	  Organics   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=organics VALUE=\"$row[organics]\"></TD>";
		echo "<TD ALIGN=Right>	  Ore			</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=ore VALUE=\"$row[ore]\"></TD>";
		echo "<TD ALIGN=Right>	  Goods	  	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=goods VALUE=\"$row[goods]\"></TD>";
		echo "<TD ALIGN=Right>	  Energy	 	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=energy VALUE=\"$row[energy]\"></TD></TR>";
		echo "<TR>";
		echo "<TD ALIGN=Right>	  Colonists  	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=colonists VALUE=\"$row[colonists]\"></TD>";
		echo "<TD ALIGN=Right>	  Credits		</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=credits VALUE=\"$row[credits]\"></TD>";
		echo "<TD ALIGN=Right>	  Fighters   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=fighters VALUE=\"$row[fighters]\"></TD>";
		echo "<TD ALIGN=Right>	  Torpedoes  	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=torps VALUE=\"$row[torps]\"></TD></TR></table>";
		echo "<br><TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2 width=\"100%\"><TR><TD COLSPAN=8>	Planet Production	</TD></tr>";
		echo "<tr><TD ALIGN=Right>	  Organics   	</TD><TD><INPUT TYPE=TEXT SIZE=3 NAME=prod_organics VALUE=\"$row[prod_organics]\"></TD>";
		echo "<TD ALIGN=Right>	  Ore			</TD><TD><INPUT TYPE=TEXT SIZE=3 NAME=prod_ore VALUE=\"$row[prod_ore]\"></TD>";
		echo "<TD ALIGN=Right>	  Goods	  	</TD><TD><INPUT TYPE=TEXT SIZE=3 NAME=prod_goods VALUE=\"$row[prod_goods]\"></TD>";
		echo "<TD ALIGN=Right>	  Energy	 	</TD><TD><INPUT TYPE=TEXT SIZE=3 NAME=prod_energy VALUE=\"$row[prod_energy]\"></TD></TR>";
		echo "<TR>";
		echo "<TD ALIGN=Right>	  Fighters   	</TD><TD><INPUT TYPE=TEXT SIZE=3 NAME=prod_fighters VALUE=\"$row[prod_fighters]\"></TD>";
		echo "<TD ALIGN=Right>	  Torpedoes  	</TD><TD><INPUT TYPE=TEXT SIZE=3 NAME=prod_torp VALUE=\"$row[prod_torp]\"></TD>";
		$credits = 100 - ($row['prod_organics'] + $row['prod_ore'] + $row['prod_goods'] + $row['prod_energy'] + $row['prod_fighters'] + $row['prod_torp']);
		echo "<TD ALIGN=Right colspan=\"2\">	  Credits  	</TD><TD colspan=\"2\"><FONT COLOR=#66FF00>$credits%</FONT></TD></TR></table>";
		echo "<br><TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2 width=\"100%\"><TR><TD COLSPAN=8>	Damaged Planet Tech Levels	</TD></tr>";
		echo "<TD ALIGN=Right>	  Fighter Bay   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=fighter VALUE=\"$row[fighter]\"></TD>";
		echo "<TD ALIGN=Right>	  Sensors   	</TD> <TD><INPUT TYPE=TEXT SIZE=9 NAME=sensors VALUE=\"$row[sensors]\"></TD>";
		echo "<TD ALIGN=Right>	  Beams   	</TD>   <TD><INPUT TYPE=TEXT SIZE=9 NAME=beams VALUE=\"$row[beams]\"></TD>";
		echo "<TD ALIGN=Right>	  Torp Launchers   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=torp_launchers VALUE=\"$row[torp_launchers]\"></TD></tr>";
		echo "<tr><TD ALIGN=Right>	  Shields   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=shields VALUE=\"$row[shields]\"></TD>";
		echo "<TD ALIGN=Right>	  armor   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=armor VALUE=\"$row[armor]\"></TD>";
		echo "<TD ALIGN=Right>	  armor Points   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=armor_pts VALUE=\"$row[armor_pts]\"></TD>";
		echo "<TD ALIGN=Right>	  Cloak   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=cloak VALUE=\"$row[cloak]\"></TD>";
		echo "<tr><TD ALIGN=Right>	  SD Weapons   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=sector_defense_weapons VALUE=\"$row[sector_defense_weapons]\"></TD>";
		echo "<TD ALIGN=Right>	  SD Sensors   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=sector_defense_sensors VALUE=\"$row[sector_defense_sensors]\"></TD>";
		echo "<TD ALIGN=Right>	  SD Cloak   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=sector_defense_cloak VALUE=\"$row[sector_defense_cloak]\"></TD>";
		echo "<TD ALIGN=Right></TD><TD></TD>";
		echo "</TABLE>";
		echo "<br><TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2 width=\"100%\"><TR><TD COLSPAN=8>	Normal Planet Tech Levels	</TD></tr>";
		echo "<TD ALIGN=Right>	  Fighter Bay   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=fighter_normal VALUE=\"$row[fighter_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  Sensors   	</TD> <TD><INPUT TYPE=TEXT SIZE=9 NAME=sensors_normal VALUE=\"$row[sensors_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  Beams   	</TD>   <TD><INPUT TYPE=TEXT SIZE=9 NAME=beams_normal VALUE=\"$row[beams_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  Torp Launchers   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=torp_launchers_normal VALUE=\"$row[torp_launchers_normal]\"></TD></tr>";
		echo "<tr><TD ALIGN=Right>	  Shields   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=shields_normal VALUE=\"$row[shields_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  armor   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=armor_normal VALUE=\"$row[armor_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  Cloak   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=cloak_normal VALUE=\"$row[cloak_normal]\"></TD>";
		echo "<tr><TD ALIGN=Right>	  SD Weapons   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=sector_defense_weapons_normal VALUE=\"$row[sector_defense_weapons_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  SD Sensors   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=sector_defense_sensors_normal VALUE=\"$row[sector_defense_sensors_normal]\"></TD>";
		echo "<TD ALIGN=Right>	  SD Cloak   	</TD><TD><INPUT TYPE=TEXT SIZE=9 NAME=sector_defense_cloak_normal VALUE=\"$row[sector_defense_cloak_normal]\"></TD>";
		echo "<TD ALIGN=Right></TD><TD></TD>";
		echo "</TABLE>";
		echo "<BR>";
		echo "<INPUT TYPE=HIDDEN NAME=planet VALUE=$planet>";
		echo "<INPUT TYPE=HIDDEN NAME=operation VALUE=save>";
		echo "<INPUT TYPE=SUBMIT SIZE=1 VALUE=Save ONCLICK=\"clean_js()\">";
	}
	elseif ($operation == "save")
	{
		// update database
		$_defeated = empty($defeated) ? "N" : "Y";
		$_base = empty($base) ? "N" : "Y";
		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET sector_defense_cloak_normal='$', sector_defense_sensors_normal='$sector_defense_sensors_normal', sector_defense_weapons_normal='$sector_defense_weapons_normal', cloak_normal='$cloak_normal', armor_normal='$armor_normal', shields_normal='$shields_normal', torp_launchers_normal='$torp_launchers_normal', beams_normal='$beams_normal', sensors_normal='$sensors_normal', fighter_normal='$fighter_normal', sector_defense_cloak='$sector_defense_cloak', sector_defense_sensors='$sector_defense_sensors', sector_defense_weapons='$sector_defense_weapons', sector_id='$sector_id',defeated='$_defeated',name='$name',base='$_base',owner='$owner',organics='$organics',ore='$ore',goods='$goods',energy='$energy',team='$team',colonists='$colonists',credits='$credits',fighter='$fighter',sensors='$sensors',beams='$beams',torp_launchers='$torp_launchers',shields='$shields',armor='$armor',armor_pts='$armor_pts',cloak='$cloak',fighters='$fighters',torps='$torps',prod_organics='$prod_organics',prod_ore='$prod_ore',prod_goods='$prod_goods',prod_energy='$prod_energy',prod_fighters='$prod_fighters',prod_torp='$prod_torp' WHERE planet_id=$planet");
		db_op_result($debug_query,__LINE__,__FILE__);
		echo "<INPUT TYPE=SUBMIT VALUE=\"Return to Planet editor\">";
		$button_main = false;
	}
	else
	{
		echo "Invalid operation";
	}
}
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Planet\">";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "</form></div></td></tr>";
?>