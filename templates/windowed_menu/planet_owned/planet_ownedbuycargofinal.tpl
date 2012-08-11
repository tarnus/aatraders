<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	{if $isowner == 1}
		{if $nomoney == 1}
			{$l_planet_nocredits1} {$cargoshipcost} {$l_planet_nocredits2} {$playercredits} {$l_credits}.
		{else}
		<table cellspacing = "0" cellpadding = "0" width="799" border = "0" align="center">
				<tr>
					<td >
						<table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
						<tr>
							<td><img src = "templates/{$templatename}images/spacer.gif" width = "10" height = "1"></td>
							<td>	
								<table cellspacing = "0" cellpadding = "0" border = "0" width="99%">
								<tr>
									<td colspan = "2"><img src = "templates/{$templatename}images/spacer.gif" width = "1" height = "10"></td>
								</tr><TR>
				<TD colspan=99 align=center bgcolor=#300030><font size=3 color=white><b>{$l_trade_result}</b></font></TD>
			 </TR>
			 <TR>
				<TD colspan=99 align=center><b><font color=red>{$l_cost}: {$trade_credits} {$l_credits}</font></b></TD>
			 </TR>

			{if $tempvar != 0}
				<TR><TD colspan=99 align=center><b>{$l_hull} {$l_trade_upgraded} {$cargoshiphull}</b></TD></TR>
			{/if}
			{if $tempvar2 != 0}
				<TR><TD colspan=99 align=center><b>{$l_power} {$l_trade_upgraded} {$cargoshippower}</b></TD></TR>
			{/if}
			</table>
		{/if}
	{/if}
	
</td><tr>
				<tr>
									<td colspan = "2">
	<BR><a href='planet.php?planet_id={$planet_id}'>{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>
	{if $allow_ibank}
		{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
	{/if}

	<A HREF ="bounty.php">{$l_by_placebounty}</A><p>

</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
