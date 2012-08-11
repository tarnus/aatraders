<H1>{$title}: {$l_pr_menu}</H1>

<table width="600" border="0" cellspacing="0" cellpadding="0" align="center">
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
										<tr><td><br>{$gotomain}<br></td></tr>
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

