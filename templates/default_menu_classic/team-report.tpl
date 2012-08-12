<H1>{$title}</H1>

<table width="90%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<div align=center>
	<h3><font color=white><B>{$team_name}</B>
	<br><font size=2><i>{$description}</i></font></H3>
	</div>
	<table border=1 cellspacing=0 cellpadding=0 width="100%" align=center>
	<tr>
	<td align='center'><font color=white><b>{$l_avatar}</b></font></h3></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=p.character_name">{$l_team_members}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.hull&direction=desc">{$l_hull}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.engines&direction=desc">{$l_engines}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.power&direction=desc">{$l_power}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.fighter&direction=desc">{$l_fighter}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.sensors&direction=desc">{$l_sensors}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.armor&direction=desc">{$l_armor}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.shields&direction=desc">{$l_shields}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.beams&direction=desc">{$l_beams}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.torp_launchers&direction=desc">{$l_torp_launch}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.cloak&direction=desc">{$l_cloak}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=s.ecm&direction=desc">{$l_ecm}</a></b></font></td>
	<td align='center'><font color=white><B><a href="team_report.php?orderby=p.score&direction=desc">{$l_team_score}</a></b></font></td>
	</tr><tr bgcolor=#000000>
	{php}
	for($i = 0; $i < $shipcount; $i++){
		echo "<td align='center'><font face=\"verdana\" size=\"2\" color=\"#0CD616\"><img src=\"images/avatars/$playeravatar[$i]\"></td>";
		echo "<td align='center'><font face=\"verdana\" size=\"2\" color=\"#0CD616\"><b>$playername[$i]</b></font>";
		if ($coordinator[$i] != "")
		{
			echo "<br><font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b>$l_team_coord</b></font>";
		}
		echo "<br><font face=\"verdana\" size=\"1\" color=\"#9ff4f8\"><b>SS $shipname[$i]</b></font><br>
		<font face=\"verdana\" size=\"1\" color=\"#FFD161\"><b>$shipclassname[$i]</b></font>
		<font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b> - </b></font>
		<font face=\"verdana\" size=\"1\" color=\"#61DFFF\"><b>$l_team_class </b></font>
		<font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b>$memberclass[$i]</b></font></td>
		<td align='center'><font color=\"$colorhull[$i]\"><b>$hull[$i]</b></font></td>
		<td align='center'><font color=\"$colorengines[$i]\"><b>$engines[$i]</b></font></td>
		<td align='center'><font color=\"$colorpower[$i]\"><b>$power[$i]</b></font></td>
		<td align='center'><font color=\"$colorfighter[$i]\"><b>$fighter[$i]</b></font></td>
		<td align='center'><font color=\"$colorsensors[$i]\"><b>$sensors[$i]</b></font></td>
		<td align='center'><font color=\"$colorarmor[$i]\"><b>$armor[$i]</b></font></td>
		<td align='center'><font color=\"$colorshields[$i]\"><b>$shields[$i]</b></font></td>
		<td align='center'><font color=\"$colorbeams[$i]\"><b>$beams[$i]</b></font></td>
		<td align='center'><font color=\"$colortorps[$i]\"><b>$torps[$i]</b></font></td>
		<td align='center'><font color=\"$colorcloak[$i]\"><b>$cloak[$i]</b></font></td>
		<td align='center'><font color=\"$colorecm[$i]\"><b>$ecm[$i]</b></font></td>
		<td align='center'><font face=\"verdana\" size=\"2\" color=\"#0CD616\"><b>$l_score</b></font> <font face=\"verdana\" size=\"2\" color=\"#ffffff\"><b>$score[$i]</b></font></td>";

		echo "</tr><tr bgcolor=#000000>";
	}
	{/php}
	</tr></table>

</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>


