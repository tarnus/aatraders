<H1>{$title}: {$l_pr_status}</H1>

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

{if $playerteam > 0}
	<BR>
	<B><A HREF=team_planets.php>{$l_pr_teamlink}</A></B><BR>
	<BR>
{/if}

{if $num_planets < 1}
	<BR>{$l_pr_noplanet}
{else}
	<BR>
	{$l_pr_clicktosort}<BR><BR>
	{$l_pr_warning}<BR><BR>
{if $totalpages > 1}
	<TABLE border=0 cellpadding=2 cellspacing=1 width="100%">
	<form action="planet_report.php" method="post">
	<TR>
		<td align="left" width="33%">
			{if $currentpage != 1}
				<a href="planet_report.php?PRepType=1&page={$previouspage}&sort={$sort}">{$l_rpt_prev}</a>
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
				<a href="planet_report.php?PRepType=1&page={$nextpage}&sort={$sort}">{$l_rpt_next}</a>
			{else}
				&nbsp;
			{/if}
		</td>
	</tr>
	<input type="hidden" name="sort" value="{$sort}">
	<input type="hidden" name="PRepType" value="1">
	</form>
	</table>
{/if}

	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=2>
	<TR BGCOLOR="#585980" VALIGN=BOTTOM>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=sector_id>{$l_pr_sector}</A>&nbsp;</B></font></TD>
        <TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=name>{$l_name}</A>&nbsp;</B></font></TD>   
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=last_visited>LV</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=ore>{$l_ore}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=organics>{$l_organics}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=goods>{$l_goods}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=energy>{$l_energy}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=special>{$l_pr_special}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=colonists>{$l_colonists}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=credits>{$l_credits}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=max_credits>{$l_max}<br>{$l_credits}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=fighters>{$l_fighters}</A>&nbsp;</B></font></TD>
	<TD ALIGN=CENTER><font size=2><B>&nbsp;<A HREF=planet_report.php?PRepType=1&sort=torp>{$l_torps}</A>&nbsp;</B></font></TD>
	<TD ALIGN=RIGHT><font size=2><B>&nbsp;{$l_base}?&nbsp;</B></font></TD>
	{if $playerteam > 0}
		<TD ALIGN=RIGHT><font size=2><B>&nbsp;{$l_team}?&nbsp;</B></font></TD>
		<TD ALIGN=CENTER><B>&nbsp;{$l_teamcash}?&nbsp;</B></TD>
        
	{/if}
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
		echo "<TD ALIGN=CENTER><font size=2>&nbsp;<A HREF=main.php?move_method=real&engage=1&destination=". $planetsector[$i] . ">". $planetsector[$i] ."</A>&nbsp;</font></TD>";
		echo "<TD ALIGN=CENTER><font size=2>&nbsp;" . $planetname[$i] . "&nbsp;</font></TD>";
         echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetlastvisited[$i] . "&nbsp;</font></TD>"; 
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetore[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetorganics[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetgoods[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetenergy[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=center><font size=2>&nbsp;";
			if ($planetspecialname[$i] == "")
			{
						echo "&nbsp;";
			}
			else
			{
				echo $planetspecialname[$i] . "<br>" . $planetspecial[$i];
			}
		echo "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetcolonists[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetcredits[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetmaxcredits[$i] . "%&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planetfighters[$i] . "&nbsp;</font></TD>";
		echo "<TD ALIGN=RIGHT><font size=2>&nbsp;" . $planettorps[$i] . "&nbsp;</font></TD>";
           

		if ($planetbase[$i] == 'Y')
			echo "<TD ALIGN=CENTER><font size=2>&nbsp;$l_yes&nbsp;</font></TD>";
		elseif ($planetbaseitems[$i])
			echo "<TD ALIGN=CENTER><font size=2>&nbsp;<A HREF=planet_report_buildbase.php?buildp=" . $planetid[$i] . "&builds=" . $planetsector[$i] . ">$l_pr_build</A>&nbsp;</font></TD>";
		else
			echo "<TD ALIGN=CENTER><font size=2>&nbsp;$l_no&nbsp;</font></TD>";

		if ($playerteam > 0){
			echo "<TD ALIGN=CENTER><font size=2>&nbsp;" . ($planetteam[$i] > 0 ? "$l_yes" : "$l_no") . "&nbsp;</font></TD>";
			echo "<TD ALIGN=CENTER><font size=2>&nbsp;" . ($planettcash[$i] == 'Y' ? "$l_yes" : "$l_no") . "&nbsp;</font></TD>";
		}
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

	echo "<TR><TD></TD></TR><TR><TD></TD></TR><TR><TD></TD></TR><TR BGCOLOR=$color>";
	{/php}
      <TD ALIGN=RIGHT><font size=2>&nbsp;&nbsp;</font></TD>   
	<TD COLSPAN=2 ALIGN=CENTER><font size=2>&nbsp;{$l_pr_totals}&nbsp;</font></TD>
	
    <TD ALIGN=RIGHT><font size=2>&nbsp;{$total_ore}&nbsp;</font></TD>    
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_organics}&nbsp;</font></TD>
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_goods}&nbsp;</font></TD>
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_energy}&nbsp;</font></TD>
	<TD ALIGN=RIGHT>&nbsp;</TD>
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_colonists}&nbsp;</font></TD>
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_credits}&nbsp;</font></TD>
	<TD ALIGN=RIGHT>&nbsp;</TD>
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_fighters}&nbsp;</font></TD>
	<TD ALIGN=RIGHT><font size=2>&nbsp;{$total_torp}&nbsp;</font></TD>
	<TD ALIGN=CENTER><font size=2>&nbsp;{$total_base}&nbsp;</font></TD>
	{if $playerteam > 0}
		<TD ALIGN=CENTER><font size=2>&nbsp;{$total_team}&nbsp;</font></TD>
		<TD ALIGN=CENTER><font size=2>&nbsp;{$total_teamcash}&nbsp;</font></TD>
	{/if}
	</TR>
	</TABLE>
{/if}

</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
