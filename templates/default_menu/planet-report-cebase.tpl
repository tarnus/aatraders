<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<BR>
	<A HREF=planet_report.php>{$l_pr_menulink}</A><br>

	<BR><A HREF=planet_report.php?PRepType=1>{$l_pr_planetstatus}</A><BR><BR>
	<BR><A HREF=planet.php?planet_id={$planet_id}>{$l_clickme}</A> {$l_toplanetmenu}<BR><BR>
	{$l_planet_bbuild}<BR><BR>

	{if $owned == 1}
		{$ownership}
	{/if}
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
