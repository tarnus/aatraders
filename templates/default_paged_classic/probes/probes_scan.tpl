<h1>{$title}</h1>

<table border="1" cellspacing="1" cellpadding="2" width="100%">
	<TR BGCOLOR="#585980">
		<TD colspan="8" align="center"><font color="white"><B>{$l_probe_scn_report}</B></font></TD>
	</TR>
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
</TABLE>
<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
	<tr>
		<td><br><br><a href="probes.php">{$l_clickme}</a> {$l_probe_linkback}.
		</td>
	</tr>
	<tr><td><br><br>{$gotomain}<br><br></td></tr>
</table>
