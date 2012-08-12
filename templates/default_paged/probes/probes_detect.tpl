<h1>{$title}</h1>

<table border="1" cellspacing="1" cellpadding="2" width="600" align="center">
	<TR BGCOLOR="#585980">
		<TD align="center"><font color="white"><B>{$l_probe_scan}</B></font></TD>
	</TR>
	<TR BGCOLOR="#23244F">
		<TD>
		{if $warplinks !=""}
			{$warplinks}
		{/if}
		{if $lastship !=""}
			{$lastship}
		{/if}
		{if $portinfo !=""}
			{$portinfo}
		{/if}
		{if $sector_def !=""}
			{$sector_def}
		{/if}
		{if $shipdetect !=""}
			{$shipdetect}
		{/if}
		{if $planetinfo !=""}
			{$planetinfo}
		{/if}
		{if $nothing_detected}
			{$l_probe2_nothing}
		{/if}

		</TD>
	</TR>
</TABLE>
<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
	<tr>
		<td><br><br><a href="probes.php">{$l_clickme}</a> {$l_probe_linkback}.
		</td>
	</tr>
	<tr><td><br><br>{$gotomain}<br><br></td></tr>
</table>
