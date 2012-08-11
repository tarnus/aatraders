<h1>{$title}</h1>

{$l_lrs_used} {$fullscan_cost} {$l_lrs_turns}, {$turnsleft} {$l_lrs_left}.
<BR><BR>
{$l_lrs_reach}
<BR><BR>

<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="100%" bgcolor="#000000">
	<TR BGCOLOR="#585980">
		<TD width="10%" align="center"><B>{$l_sector}</B></TD>
		<td width="10%" align="center"><B>{$l_scan}</B></td>
		<TD width="10%" align="center"><B>{$l_lrs_links}</B></TD>
		<TD width="10%" align="center"><B>{$l_lrs_ships}</B></TD>
		<TD colspan="2" width="10%" align="center"><B>{$l_port}</B></TD>
		<TD width="10%" align="center"><B>{$l_planets}</B></TD>
		<TD width="10%" align="center"><B>{$l_mines}</B></TD>
		<TD width="10%" align="center"><B>{$l_fighters}</B></TD>
		<TD width="10%" align="center"><B>{$l_lss}</B></TD>
	</TR>
	{ assign var="color" value="#3A3B6E" }

	{foreach key=key value=item from=$lr_sector}
		<TR BGCOLOR="{$color}">
			<TD align="center"><A HREF="main.php?move_method=warp&destination={$lr_sector[$key]|urlencode}">{$lr_zonetype[$key]}{$lr_sector[$key]}</A></TD>
			<TD align="center"><A HREF="sector_scan.php?command=scan&sector={$lr_sector[$key]|urlencode}">{$l_scan}</A></TD>
			<TD align="center">{$lr_links[$key]}</TD>
			<TD align="center">{$lr_ships[$key]}</TD>
			<TD align="right" WIDTH=12><img align=absmiddle height=12 width=12 alt="{$lr_image_alt[$key]}" src="images/ports/{$lr_image[$key]}.png">&nbsp;</TD>
			<TD align="left">{$lr_port[$key]}</TD>
			<TD align="center">{$lr_planets[$key]}</TD>
			<TD align="center">{$lr_mines[$key]}</TD>
			<TD align="center">{$lr_fighters[$key]}</TD>
			<TD align="center">{$lr_lss[$key]}</TD>
		</tr>

		{if $color == "#3A3B6E"}
			{ assign var="color" value="#23244F" }
		{else}
			{ assign var="color" value="#3A3B6E" }
		{/if}
	{/foreach}

	<tr>
		<td colspan="10"><BR>{$l_lrs_click}<br><br>{$gotomain}<br><br></td>
	</tr>
</table>


