<h1>{$title}</h1>

<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	{if $isprobe}
		{if $total_cost > $playercredits}
			{$l_probe2_nocredits}
		{else}
			<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=3 WIDTH="100%" ALIGN=CENTER>
			 <TR>
				<TD align=center ><font size=3 color=white><b>{$l_trade_result}</b></font></TD>
			 </TR>
			 <TR>
				<TD align=center><b><font color=red>{$l_cost}: {$trade_credits} {$l_credits}</font></b></TD>
			 </TR>

			{if $isengineupgrade}
				<TR><TD align=left>{$l_engines} {$l_trade_upgraded} {$engines_upgrade}.</TD></TR>
			{/if}

			{if $issensorupgrade}
				<TR><TD align=left>{$l_sensors} {$l_trade_upgraded} {$sensors_upgrade}.</TD></TR>
			{/if}

			{if $iscloakupgrade}
				<TR><TD align=left>{$l_cloak} {$l_trade_upgraded} {$cloak_upgrade}.</TD></TR>
			{/if}

			</table>
			<BR><BR>
			<A HREF=probes_upgrade.php?probe_id={$probe_id}>{$l_clickme}</A> {$l_toprobemenu}<BR><BR>
		{/if}
	{else}
		<A HREF=probes_upgrade.php?probe_id={$probe_id}>{$l_clickme}</A> {$l_toprobemenu}<BR><BR>
	{/if}
</td></tr>

<tr><td>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
