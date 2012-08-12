<H1>{$title}</H1>

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
		<BR>
		<B><A HREF=team_planets.php>{$l_pr_teamlink}</A></B><BR>
		 {$l_pr_team_disp}
		 <BR>
		<BR>
		<B><A HREF=team_defenses.php>{$l_pr_showtd}</A></B><BR> {$l_pr_showd}<BR>
		</td></tr>
		</table>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>

{if $totalpages > 1}
	<TABLE border=0 cellpadding=2 cellspacing=1 width="100%">
	<form action="team_planets.php" method="post">
	<TR>
		<td align="left" width="33%">
			{if $currentpage != 1}
				<a href="team_planets.php?page={$previouspage}&sort={$sort}">{$l_rpt_prev}</a>
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
				<a href="team_planets.php?page={$nextpage}&sort={$sort}">{$l_rpt_next}</a>
			{else}
				&nbsp;
			{/if}
		</td>
	</tr>
	<input type="hidden" name="sort" value="{$sort}">
	</form>
	</table>
{/if}
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR BGCOLOR="#585980">
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=sector>{$l_sector}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=name>{$l_name}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=ore>{$l_ore}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=organics>{$l_organics}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=goods>{$l_goods}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=energy>{$l_energy}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=colonists>{$l_colonists}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=credits>{$l_credits}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=max_credits>{$l_max}<br>{$l_credits}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=fighters>{$l_fighters}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=team_planets.php?sort=torp>{$l_torps}</A>&nbsp;</B></font></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;{$l_base}?&nbsp;</B></TD>
<TD ALIGN=CENTER><font size=2><B>&nbsp;{$l_player}&nbsp;</B></TD>
</TR>

{php}
$color = "#3A3B6E";
for($i = 0; $i < $num_planets; $i++){
	echo "<TR BGCOLOR=\"$color\">";
	echo "<TD ALIGN=CENTER><font size=2>&nbsp;<A HREF=main.php?move_method=real&engage=1&destination=". $planetsector[$i] . ">". $planetsector[$i] ."</A>&nbsp;</font></TD>";
	echo "<TD ALIGN=CENTER><font size=2>&nbsp;" . $planetname[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetore[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetorganics[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetgoods[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetenergy[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetcolonists[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetcredits[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetmaxcredits[$i] . "%&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetfighters[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planettorps[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=CENTER><font size=2>&nbsp;" . $planetbase[$i] . "&nbsp;</font></TD>";
	echo "<TD ALIGN=CENTER><font size=2>&nbsp;" . $planetplayer[$i] . "&nbsp;</font></TD>";
	echo "</TR>";

	if ($color == "#3A3B6E")
	{
		$color = "#23244F";
	}
	else
	{
		$color = "#3A3B6E";
	}
}
echo "<TR BGCOLOR=\"$color\">";
{/php}

<TD ALIGN=CENTER>&nbsp;</TD>
<TD ALIGN=CENTER>&nbsp;{$l_pr_totals}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_ore}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_organics}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_goods}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_energy}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_colonists}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_credits}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_fighters}&nbsp;</TD>
<TD ALIGN=RIGHT>&nbsp;{$total_torp}&nbsp;</TD>
<TD ALIGN=CENTER>&nbsp;{$total_base}&nbsp;</TD>
<TD ALIGN=CENTER>&nbsp;</TD>
</TR>
</TABLE>

</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
