<h1>{$title}</h1>

<table border="1" cellspacing="1" cellpadding="2" width="500" align="center">
	<TR BGCOLOR="#585980">
		<TD align="center"><font color="white"><B>{$l_probe_named}</B></font></TD>
	</TR>
	{if $player_id == $probe_owner_id && $probe_owner_id > 0}
		<TR BGCOLOR="#23244F">
			<TD>
				{$l_probe_ordersout}<p>
				{$l_probe_pickup}<p>
				{$l_probe_orders}<p>
				{$l_probe_upgrade}</p>
				{$l_turns_have} {$player_turns}
			</td>
		</tr>
		<tr>
			<td BGCOLOR="#000000">
				<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="2" align="center">
					<TR BGCOLOR="#3A3B6E">
						<td>&nbsp;</td>
						<td>&nbsp;</td>
						<TD><B>{$l_probe_engine}</B></TD>
						<TD><B>{$l_probe_sensors}</B></TD>
						<TD><B>{$l_probe_cloak}</B></TD>
					</TR>
					<TR BGCOLOR="#23244F">
						<TD>{$l_probe_defense_levels}</TD>
						<td>&nbsp;</td>
						<TD>{$probe_engines}</TD>
						<TD>{$probe_sensors}</TD>
						<TD>{$probe_cloak}</TD>
					</TR>
				</TABLE>
			</td>
		</tr>
	{else}
		{if $probe_owner_id != 3}
			<tr BGCOLOR="#23244F">
				<td>
					{$l_probe_att}
				</td>
			</tr>
		{/if}
		<tr BGCOLOR="#3A3B6E">
			<td>
				{$l_probe_scn}
			</td>
		</tr>
	{/if}
	{if $player_id == $probe_owner_id }
		<TR BGCOLOR="#23244F">
			<TD><A onclick="javascript: alert ('alert:{$l_probe_warning}');" HREF="probes_upgrade.php?probe_id={$probe_id}&destroy=1">{$l_probe_destroyprobe}</a></td>
		</tr>
	{/if}
</TABLE>
<BR><BR>

<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
	<tr><td><br><br>{$gotomain}<br><br></td></tr>
</table>
 