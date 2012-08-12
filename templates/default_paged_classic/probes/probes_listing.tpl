<h1>{$title}</h1>

{ assign var="line_color" value="#23244F" }
{ assign var="color_line1" value="#23244F" }
{ assign var="color_line2" value="#3A3B6E" }

<table border="1" cellspacing="1" cellpadding="2" width="100%">
	<TR BGCOLOR="#585980">
		<TD colspan="8" align="center"><font color="white"><B>{$l_probe_defaulttitle1}</B></font></TD>
	</TR>
	<TR BGCOLOR="#23244F">
		<TD><B><A HREF="probes.php">{$l_probe_codenumber}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=type">{$l_probe_type}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=sector">{$l_probe_sector}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=tsector">{$l_probe_tsector}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=engines">{$l_probe_engine}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=sensors">{$l_probe_sensors}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=cloak">{$l_probe_cloak}</A></B></TD>
		<TD><B>{$l_probe_detect}</B></TD>
	</TR>
	{if $probes_in_space == 0}
		<TR BGCOLOR="#3A3B6E">
			<td colspan="8">{$l_probe_no1}</td>
		<tr>
	{else}
		{foreach key=key value=item from=$probe_id}
			<TR BGCOLOR="{$line_color}">
				<TD><font size=2 color=white>{$probe_id[$key]}</font></TD>
				<TD><font size=2 color=white>{$probe_type[$key]}</font>
					{if $probe_display[$key] != ""}
						<br><br><font size=2 color=white>{$probe_display[$key]}</font>
					{/if}
				</TD>
				<TD><font size=2 color=white><a href=main.php?move_method=real&engage=1&destination={$probe_current_sector[$key]|urlencode}>{$probe_current_sector[$key]}</a></font></TD>
				<TD><font size=2 color=white><a href=main.php?move_method=real&engage=1&destination={$probe_target_sector[$key]|urlencode}>{$probe_target_sector[$key]}</a></font></TD>
				<TD><font size=2 color=white>{$probe_engines[$key]}</font></TD>
				<TD><font size=2 color=white>{$probe_sensors[$key]}</font></TD>
				<TD><font size=2 color=white>{$probe_cloak[$key]}</font></TD>
				<TD><font size=2><a href="probes.php?command=detect&probe_id={$probe_id[$key]}">{$l_probe_view}</a></font></TD>
			</TR>
			{if $line_color == $color_line1}
				{ assign var="line_color" value=$color_line2 }
			{else}
				{ assign var="line_color" value=$color_line1 }
			{/if}
		{/foreach}
	{/if}
</TABLE>
<BR><BR>

{ assign var="line_color" value="#23244F" }
<table border="1" cellspacing="1" cellpadding="2" width="100%">
	<TR BGCOLOR="#585980">
		<TD colspan="8" align="center"><font color=white><B>{$l_probe_defaulttitle2}</B></font></TD>
	</TR>
	<TR BGCOLOR="#23244F">
		<TD><B><A HREF="probes.php">{$l_probe_codenumber}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=type">{$l_probe_type}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=engines">{$l_probe_engine}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=sensors">{$l_probe_sensors}</A></B></TD>
		<TD><B><A HREF="probes.php?by1=cloak">{$l_probe_cloak}</A></B></TD>
		<TD><B>{$l_probe_launch}</B></TD>
	</TR>
	{if $probes_in_ship == 0}
		<TR BGCOLOR="#3A3B6E">
			<td colspan="6">{$l_probe_no2}</td>
		<tr>
	{else}
		{foreach key=key value=item from=$ship_probe_id}
			<TR BGCOLOR="{$line_color}">
				<TD><font size=2 color=white>{$ship_probe_id[$key]}</font></TD>
				<TD><font size=2 color=white>{$ship_probe_type[$key]}</font></TD>
				<TD><font size=2 color=white>{$ship_probe_engines[$key]}</font></TD>
				<TD><font size=2 color=white>{$ship_probe_sensors[$key]}</font></TD>
				<TD><font size=2 color=white>{$ship_probe_cloak[$key]}</font></TD>
				<TD><font size=2><a href="probes.php?command=drop&probe_id={$ship_probe_id[$key]}">{$l_probe_launch}</a></font></TD>
			</TR>
			{if $line_color == $color_line1}
				{ assign var="line_color" value=$color_line2 }
			{else}
				{ assign var="line_color" value=$color_line1 }
			{/if}
		{/foreach}
	{/if}
</TABLE>

<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
	<tr><td><br><br>{$gotomain}<br><br></td></tr>
</table>
 