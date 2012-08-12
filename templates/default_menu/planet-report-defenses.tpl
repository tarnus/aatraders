<H1>{$title}: {$l_pr_pdefense}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
		<tr><td>
		<B><A HREF=planet_report.php?PRepType=1 NAME="Planet Status">{$l_pr_planetstatus}</A></B><BR>
		 {$l_pr_comm_disp}<BR>
		 <BR>
		<B><A HREF=planet_report.php?PRepType=3 NAME="Planet Defense">{$l_pr_pdefense}</A></B><BR>
		 {$l_pr_display}<BR>
		<BR>
		<B><A HREF=planet_report.php?PRepType=2 NAME="Planet Status">{$l_pr_changeprods}</A></B> &nbsp;&nbsp; {$l_pr_baserequired} {$l_pr_prod_disp}<BR>

	{if $playerteam > 0}
		<BR>
		<B><A HREF=team_planets.php>{$l_pr_teamlink}</A></B><BR>
		 {$l_pr_team_disp}
		 <BR>
		<BR>
		<B><A HREF=team_defenses.php>{$l_pr_showtd}</A></B><BR> {$l_pr_showd}<BR>
	{/if}
		</td></tr>
		</table>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>

{if $num_planets < 1}
	<BR>{$l_pr_noplanet}
{else}
	<BR>
	{$l_pr_clicktosort}<BR><BR>
{if $totalpages > 1}
	<TABLE border=0 cellpadding=2 cellspacing=1 width="100%">
	<form action="planet_report.php" method="post">
	<TR>
		<td align="left" width="33%">
			{if $currentpage != 1}
				<a href="planet_report.php?PRepType=3&page={$previouspage}&sort={$sort}">{$l_rpt_prev}</a>
			{else}
				&nbsp;
			{/if}
		</td>
		<TD align='center' width="33%">
	{ math equation="x + y" x=1 y=$totalpages assign="forpages" }
	{$l_rpt_selectpage} <select name="page">
	{ for start=1 stop=$forpages step=1 value=i }
		<option value="{$i}"
		{if $currentpage == $i}
			selected
		{/if}
		> {$l_rpt_page} {$i} </option>
	{/for}
	</select>
	&nbsp;<input type="submit" value="{$l_submit}">
	</TD>
		<td align="right" width="33%">
			{if $currentpage != $totalpages}
				<a href="planet_report.php?PRepType=3&page={$nextpage}&sort={$sort}">{$l_rpt_next}</a>
			{else}
				&nbsp;
			{/if}
		</td>
	</tr>
	<input type="hidden" name="sort" value="{$sort}">
	<input type="hidden" name="PRepType" value="3">
	</form>
	</table>
{/if}
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=2>
	<TR BGCOLOR="#585980" VALIGN=BOTTOM>
	<TD><B><A HREF=planet_report.php?PRepType=3&sort=sector_id>{$l_pr_sector}</A></B></TD>
	<TD><B><A HREF=planet_report.php?PRepType=3&sort=name>{$l_name}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=fighter>{$l_fighter}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=sensors>{$l_sensors}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=beams>{$l_beams}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=torp_launchers>{$l_torp_launch}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=shields>{$l_shields}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=jammer>{$l_jammer}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=cloak>{$l_cloak}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=sector_defense_weapons>{$l_planetary_SD_weapons}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=sector_defense_sensors>{$l_planetary_SD_sensors}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=sector_defense_cloak>{$l_planetary_SD_cloak}</A></B></TD>
	<TD width="10%"><B><A HREF=planet_report.php?PRepType=3&sort=base>{$l_base}</a></B></TD>
	</TR>
	{php}
	$color = "#3A3B6E";
	for($i=0; $i<$num_planets; $i++)
	{
		if($planetzone_id[$i] == 4)
		{
			$rowcolor = "#440000";
		}
		else
		{
			$rowcolor = $color;
		}
		echo "<TR BGCOLOR=\"$rowcolor\">";
		echo "<TD><A HREF=main.php?move_method=real&engage=1&destination=". $planetsector[$i] . ">". $planetsector[$i] ."</A></TD>";
		echo "<TD>" . $planetname[$i] . "</TD>";
		echo "<TD>" . $planetfighter[$i] . "</TD>";
		echo "<TD>" . $planetsensors[$i] . "</TD>";
		echo "<TD>" . $planetbeams[$i] . "</TD>";
		echo "<TD>" . $planettorps[$i] . "</TD>";
		echo "<TD>" . $planetshields[$i] . "</TD>";
		echo "<TD>" . $planetjammer[$i] . "</TD>";
		echo "<TD>" . $planetcloak[$i] . "</TD>";
		echo "<TD>" . $planetsdweapons[$i] . "</TD>";
		echo "<TD>" . $planetsdsensors[$i] . "</TD>";
		echo "<TD>" . $planetsdcloak[$i] . "</TD>";

		if ($planetbase[$i] == 'Y')
			echo "<TD>$l_yes</TD>";
		elseif ($planetbaseitems[$i])
			echo "<TD><A HREF=planet_report_ce.php?buildp=" . $planetid[$i] . "&builds=" . $planetsector[$i] . ">$l_pr_build</A></TD>";
		else
			echo "<TD>$l_no</TD>";

		echo "</TR>\n";

		if($color == "#3A3B6E")
		{
			$color = "#23244F";
		}
		else
		{
			$color = "#3A3B6E";
		}
	}
	echo "<TR BGCOLOR=$color>";
	{/php}
	<TD COLSPAN=14  ALIGN=CENTER>{$l_pr_totals}: {$total_base} / {$totalplanets}</TD>
	</TR>
	</TABLE>
{/if}
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
