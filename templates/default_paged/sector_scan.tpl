{if $ajax != 1}
<h1>{$title}</h1>
{/if}
<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="100%" BGCOLOR="{$color_header}">
	<tr>
		<td valign="top" width="49%">
			<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="100%" bgcolor="#000000">
				<TR BGCOLOR="{$color_header}">
					<TD><B>{$l_sector}  {$sector}</B></TD>
				</TR>
				<TR BGCOLOR="#23244F">
					<TD><B>{$l_links}</B></TD>
				</TR>
				<TR>
					<TD>{$link_list}</TD>
				</TR>
				<TR BGCOLOR="#23244F">
					<TD><B>{$l_ships}</B></TD>
				</TR>
				<TR>
					<TD>
						{if $sectornum == 1}
							{$l_lrs_zero}
						{else}
							{if $num_detected == 0}
								{$l_none}
							{else}
								{foreach key=key value=item from=$ship_name}
									{$ship_name[$key]} ({$player_name[$key]})
										{if $sector_zone != 2 && $sector_missile != 0}
											{if $ship_bounty[$key] > 0}
												 <font color='red'><b>{$l_by_bountyscan}</b></font>
											{/if}
											 - <a href="combat_sector_missile.php?sector={$sector|urlencode}&ship_id={$ship_id[$key]}">{$l_clickme}</a>{$l_lrs_sectormissile_question}
										{/if}
										 - 
										{if $shipratingnumber[$key] == -1}
												<font color="red">{$shiprating[$key]}</font>
										{elseif $shipratingnumber[$key] == 0}
											<font color="yellow">{$shiprating[$key]}</font>
										{else}
											<font color="lime">{$shiprating[$key]}</font>
										{/if}
										<br>
								{/foreach}
							{/if}
						{/if}
					</TD>
				</TR>
				<TR BGCOLOR="#23244F">
					<TD><B>{$l_port}</B></TD>
				</TR>
				<TR>
					<TD>
						{if $port_type != "none"}
							<img align="absmiddle" height="12" width="12" alt="{$icon_alt_text}" src="images/ports/{$icon_port_type_name}.png">
						{/if}
						{$icon_alt_text}
					</TD>
				</TR>
				<TR BGCOLOR="#23244F">
					<TD><B>{$l_planets}</B></TD>
				</TR>
				<TR>
					<TD>
						<TABLE bgcolor="#000000">
							<tr>
								{if $planetsfound == 0}
									<td>{$l_none}</td>
								{else}
									{foreach key=key value=item from=$planetid}
										<td align="center" valign="top">
											{if $planetbounty[$key] > 0}
												<font color='red' size='4'><b>{$l_by_bountyscan}</b></font></br>
											{/if}
											<A HREF="planet.php?planet_id={$planetid[$key]}">
											 <img src="templates/{$templatename}images/planet{$planetimg[$key]}.png" alt="" width="100" height="100">	
											{insert name="img" src="templates/`$templatename`images/planet`$planetimg[$key]`.png" alt="" width="100" height="100"}
											</a><BR><font size="2" color="white" face="arial">
											{$planetname[$key]}
											<br>({$planetowner[$key]})
											</font>
											<br>{if $planetratingnumber[$key] == -1}
												<font color="red">{$planetrating[$key]}</font>
											{elseif $planetratingnumber[$key] == 0}
												<font color="yellow">{$planetrating[$key]}</font>
											{else}
												<font color="lime">{$planetrating[$key]}</font>
											{/if}
										</td>
									{/foreach}
								{/if}
							</tr>
						</TABLE>
					</TD>
				</TR>
				<TR BGCOLOR="#23244F">
					<TD><B>{$l_fighters}</B></TD>
				</TR>
				<TR>
					<TD>
						{if $mines_count > 0}
							{foreach key=key value=item from=$fighter_owner}
								{$fighter_amount[$key]} ({$item})
								{if $fighter_bounty[$key] > 0}
									{$l_by_bountyscan}
								{/if}
								<br>
							{/foreach}
						{else}
							0
						{/if}
					</TD>
				</TR>
				<TR BGCOLOR="#23244F">
					<TD><B>{$l_mines}</B></TD>
				</TR>
				<TR>
					<TD>
						{if $mines_count > 0}
							{foreach key=key value=item from=$mines_owner}
								{$mines_amount[$key]} ({$item})
								{if $mines_bounty[$key] > 0}
									{$l_by_bountyscan}
								{/if}
								<br>
							{/foreach}
						{else}
							0
						{/if}
					</TD>
				</TR>
				{if $sectornum != '1'}
					<TR BGCOLOR="#23244F">
						<TD><B>{$l_lss}</B></TD>
					</TR>
					<TR>
						<TD>{$lss_info}<br><br></TD>
					</tr>
				{/if}
			</TABLE>
{if $ajax != 1}
			<BR>
			<a href="main.php?move_method=warp&destination={$sector|urlencode}">{$l_clickme}</a> {$l_lrs_moveto} {$sector}.
{/if}
			<BR><BR>
		</td>
{if $ajax != 1}
		<td width="2%">&nbsp;</td>
		<td valign="top"><b>{$l_sn_addnote}</b><br>
			<FORM ACTION="sector_notes.php" METHOD="POST">
			<input type="Hidden" name="command" value="{$l_sn_addnote}">	
			<input type="Hidden" name="sectornum" value="{$sector}">
			<input type="Hidden" name="sectornumber" value="{$sectornum}">
			<TABLE BORDER="0" CELLSPACING="0" CELLPADDING="2" BGCOLOR="#23244F">
			<TR BGCOLOR="{$color_header}" VALIGN="top">
				<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdscanfrom}&nbsp;</B></font></TD>
				<td>&nbsp;</td>
				<TD ALIGN="left"><font size="2"><input type="Text" name="scanfrom" width="10" value="{$scanfromname}">&nbsp;</font></TD>
			</tr>
			<TR BGCOLOR="{$color_header}" VALIGN="top">
				<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdtype}&nbsp;</B></font></TD>
				<td>&nbsp;</td>
				<TD ALIGN="left"><font size="2"><select name=stype>
					<option value="">N/A</option>
					<option value="Ally" >Ally</option>
					<option value="Base">Base</option>
					<option value="Enemy">Enemy</option>
					<option value="Indy">Indy</option>
					<option value="Port">Port</option>
					<option value="Team Base">Team Base</option>
					<option value="Minefield">Minefield</option>
					<option value="SG Entry">SG Entry</option>
					<option value="Spy Sector">Spy Sector</option>
					</select>
					&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdowner}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2"><input type="Text" name="owner" width="10" >&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdplanets}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2"><input type="Text" name="planets" width="10" value="{$planetsfound}">&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdport}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2"><input type="Text" name="port" width="10" value="{$port_type}">&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdfighters}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2"><input type="Text" name="fighters" width="10" value="{$has_fighters}">&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdmines}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size=2><input type="Text" name="mines" width="10" value="{$has_mines}">&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hdteam}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2">
						{if $team_note == 0}
							<input type="checkbox" name="team" disabled>
						{else}
							<input type="checkbox" name="team" >
						{/if}
						&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;{$l_sn_hddetail}&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2"><textarea name="note" cols="20" rows="5"></textarea>&nbsp;</font></TD>
				</tr>
				<TR BGCOLOR="{$color_header}" VALIGN="top">
					<TD ALIGN="left"><font size="2"><B>&nbsp;&nbsp;</B></font></TD>
					<td>&nbsp;</td>
					<TD ALIGN="left"><font size="2"><INPUT TYPE=SUBMIT VALUE="{$l_sn_addnote}">&nbsp;</font></TD>	
				</tr>
			</TABLE>
			</form>
		</td>
	{/if}
	</tr>
</table>
{if $notelistcount > 0}
	{ assign var="color_line1" value="#000000" }
	{ assign var="color_line2" value="#454560" }
	{ assign var="color_header" value="#454560" }

	<b>{$l_sn_title}</b><br>
	<FORM ACTION="sector_notes.php" METHOD="POST">
	<input type="hidden" name="limit" value="1">
	<input type="hidden" name="lrscan" value="{$sector}">
	<TABLE WIDTH="100%" BORDER="0" CELLSPACING="0" CELLPADDING="2">
		<TR BGCOLOR="{$color_header}" VALIGN="BOTTOM">
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdsector}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdtype}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdowner}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdplanets}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdport}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdfighters}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdmines}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hdscanfrom}&nbsp;</B></font></TD>
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hddetail}&nbsp;</B></font></TD>
			{if $team_note > 0}
				<TD ALIGN="RIGHT"><font size="2"><B>&nbsp;{$l_sn_hdteam}&nbsp;</B></font></TD>
			{/if}
			<TD ALIGN="CENTER"><font size="2"><B>&nbsp;{$l_sn_hddelete}&nbsp;</B></font></TD>	
		</TR>
		{ assign var="color" value=$color_line1 }
		{foreach key=key value=item from=$sectorlist}
			<TR BGCOLOR="{$color}">
				<TD ALIGN="CENTER"><font size="2">&nbsp;<A HREF="main.php?move_method=real&engage=1&destination={$sectorlist[$key]|urlencode}">{$sectorlist[$key]}</A>&nbsp;</font></TD>
				<TD ALIGN="CENTER"><font size="2">&nbsp;{$sector_type[$key]}&nbsp;</font></TD>
				<TD ALIGN="center"><font size="2">&nbsp;{$sector_owner[$key]}&nbsp;</font></TD>
				<TD ALIGN="center"><font size="2">&nbsp;{$sector_planets[$key]}&nbsp;</font></TD>
				<TD ALIGN="center"><font size="2">&nbsp;{$sector_port[$key]}&nbsp;</font></TD>
				<TD ALIGN="center"><font size="2">&nbsp;{$sector_fighters[$key]}&nbsp;</font></TD>
				<TD ALIGN="center"><font size="2">&nbsp;{$sector_mines[$key]}&nbsp;</font></TD>
				{if $sector_scanfrom[$key] != ""}
					<TD ALIGN="CENTER"><font size="2">&nbsp;<A HREF="main.php?move_method=real&engage=1&destination={$sector_scanfrom[$key]|urlencode}">{$sector_scanfrom[$key]}</A>&nbsp;</font></TD>
				{else}
					<TD ALIGN="CENTER"><font size="2">&nbsp;N/A&nbsp;</font></TD>
				{/if}
				<TD ALIGN="CENTER"><font size="2">&nbsp;<A HREF="sector_notes.php?command={$l_sn_view}&sector={$sectorlist[$key]|urlencode}">{$l_sn_view}</a>&nbsp;</font></TD>
				{if $team_note > 0}
					<TD ALIGN="CENTER"><font size="2">&nbsp;
						{if $notes_team[$key] > 0}
							{$l_sn_yes}
						{else}
							{$l_sn_no}
						{/if}
					&nbsp;</font></TD>";
				{/if}
				{if $note_player_id[$key] == $player_id || $player_id == $team_note}
					<TD ALIGN="CENTER"><font size="2">&nbsp;<INPUT TYPE=CHECKBOX NAME=Del[] VALUE="{$notelistid[$key]}">&nbsp;</font></TD>
				{else}
					<TD ALIGN="CENTER"><font size="2">&nbsp;<INPUT TYPE=CHECKBOX NAME=Del[] VALUE="{$notelistid[$key]}" disabled>&nbsp;</font></TD>
				{/if}
			</TR>
			{if $color == $color_line1}
				{ assign var="color" value=$color_line2 }
			{else}
				{ assign var="color" value=$color_line1 }
			{/if}
		{/foreach}
		<tr bgcolor="{$color}">
			<td colspan="9">&nbsp;</td>
				{if $team_note > 0}
					<TD ALIGN="CENTER">&nbsp;</TD>
				{/if}

				<td align="center"><INPUT TYPE="SUBMIT" VALUE="{$l_sn_delete}"></td>
			</tr>
		</TABLE>
	{/if}
	</form>
{if $ajax != 1}
	<tr>
		<td colspan="10"><BR>{$l_lrs_click}<br><br>{$gotomain}<br><br></td>
	</tr>
{/if}
</table>
