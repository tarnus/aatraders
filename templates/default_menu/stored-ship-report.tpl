<H1>{$title}</H1>

<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<div align=center>
	<h3><font color="white"><B>{$team_name}</B>
	<br><font size=2><i>{$description}</i></font></H3>
	</div> 
	<table border=1 cellspacing=0 cellpadding=0 width="100%" align=center>
	<tr bgcolor="#585980">
	<td align="center"><font color="white"><B><a href="stored_ship_report.php">{$l_ships}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=hull&direction=desc">{$l_hull}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=engines&direction=desc">{$l_engines}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=power&direction=desc">{$l_power}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=fighter&direction=desc">{$l_fighter}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=sensors&direction=desc">{$l_sensors}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="ship-report.php?orderby=armor&direction=desc">{$l_armor}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=shields&direction=desc">{$l_shields}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=beams&direction=desc">{$l_beams}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=torp_launchers&direction=desc">{$l_torp_launch}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=cloak&direction=desc">{$l_cloak}</a></b></font></td>
	<td align="center"><font color="white"><B><a href="stored_ship_report.php?orderby=ecm&direction=desc">{$l_ecm}</a></b></font></td>
	<td align="center"><font color="white"><b><a href="stored_ship_report.php">{$l_planets}</a></b></font></td>
	<td align="center"><font color="white"><b><a href="stored_ship_report.php">{$l_sector}</a></b></font></td>
	
	
	</tr><tr bgcolor=#000000>
	{php}
	for($i = 0; $i < $shipcount; $i++){
	  if ($ship_id[$i]!=$currentship[$i]){
		echo "<td align=\"center\"><font face=\"verdana\" size=\"2\" color=\"#0CD616\">";

		echo "<br><font face=\"verdana\" size=\"1\" color=\"#9ff4f8\"><b>SS $shipname[$i]</b></font><br>
		<font face=\"verdana\" size=\"1\" color=\"#FFD161\"><b>$shipclassname[$i]</b></font>
		<font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b> - </b></font>
		<font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b>$memberclass[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorhull[$i]\"><b>$hull[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorengines[$i]\"><b>$engines[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorpower[$i]\"><b>$power[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorfighter[$i]\"><b>$fighter[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorsensors[$i]\"><b>$sensors[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorarmor[$i]\"><b>$armor[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorshields[$i]\"><b>$shields[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorbeams[$i]\"><b>$beams[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colortorps[$i]\"><b>$torps[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorcloak[$i]\"><b>$cloak[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorecm[$i]\"><b>$ecm[$i]</b></font></td>";
		if ($planetname[$i]==""){
		echo "<td align=\"center\"><font face=\"verdana\" size=\"2\" color=\"#0CD616\">N/A</td>";
		}else{
		echo "<td align=\"center\"><font face=\"verdana\" size=\"2\" color=\"#0CD616\"><a href=\"main.php?move_method=real&engage=1&destination=$sector_name[$i]\">$planetname[$i]</a></td>";
		}
		if ($sector_name[$i]==""){
		echo "<td align=\"center\"><font face=\"verdana\" size=\"2\" color=\"#0CD616\">N/A</td>";
		}else{
		echo "<td align=\"center\"><font face=\"verdana\" size=\"2\" color=\"#0CD616\"><a href=\"main.php?move_method=real&engage=1&destination=$sector_name[$i]\">$sector_name[$i]</a></td>";
		}

	

		echo "</tr><tr bgcolor=#000000>";
	}
	}
	{/php}
	</tr></table>

</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>


