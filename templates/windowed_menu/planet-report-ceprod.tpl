<H1>{$title}: {$l_pr_menu}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<BR>
	<A HREF=planet_report.php>{$l_pr_menulink}</A><br>
	<BR><A HREF=planet_report.php?PRepType=2>{$l_pr_changeprods}</A><br><br>
	<BR>
	{$l_pr_ppupdated}<BR><BR>
	{if $exceeded > 0}
		{$l_pr_prexeedcheck}<BR><BR>
	{/if}
	{php}
	for($i = 0; $i < $exceeded; $i++){
		echo $planetexceeded[$i]."<br>";
	}
	{/php}

</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
