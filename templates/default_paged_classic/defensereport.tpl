<h1>{$title}</h1>

<table width="400" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
    	{if $totalpages > 1}
	<TABLE border=0 cellpadding=2 cellspacing=1 width="100%">
	<form action="defense_report.php" method="post">
	<TR>
		<td align="left" width="33%">
			{if $currentpage != 1}
				<a href="defense_report.php?page={$previouspage}&sort={$sort}">{$l_rpt_prev}</a>
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
				<a href="defense_report.php?page={$nextpage}&sort={$sort}">{$l_rpt_next}</a>
			{else}
				&nbsp;
			{/if}
		</td>
	</tr>
	<input type="hidden" name="sort" value="{$sort}">
	</form>
	</table>
{/if}

		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
<TD align="center"><B><A HREF=defense_report.php?sort=sector>{$l_sector}</A></B></TD>
<TD align="center"><B><A HREF=defense_report.php?sort=quantity>{$l_qty}</A></B></TD>
<TD align="center"><B><A HREF=defense_report.php?sort=type>{$l_sdf_type}</A></B></TD>
</TR>
{php}
	$curcolor = "#3A3B6E";
	for($i=0; $i<$num_sectors; $i++)
	{
		echo "<TR BGCOLOR=\"$curcolor\">";
		echo "<TD align=\"center\"><A HREF=main.php?move_method=real&engage=1&destination=". $dsector[$i] . ">". $dsector[$i] ."</A></TD>";
		echo "<TD align=\"center\">" . $dquantity[$i] . "</TD>";
		echo "<TD align=\"center\"> $defense_type[$i] </TD>";
		echo "</TR>";
		if ($curcolor == "#3A3B6E")
		{
			$curcolor = "#23244F";
		}else{
			$curcolor = "#3A3B6E";
		}
	}
{/php}
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

