<H1>{$title}</H1>

<table border="1" cellspacing="0" cellpadding="4" align="center" width="300">
	<tr>
		<td colspan=4>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td>	
						<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
							<tr bgcolor="black">
								<td valign="top" width=18><img src = "templates/{$templatename}images/spacer.gif" height="220" width="18"></TD>
								<td valign="top">
									<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{if $teammatch}
	{if $update}
		<FORM ACTION="teams.php" METHOD=POST>
		{$l_team_edname}: <BR>
		<INPUT TYPE=hidden name=command value={$command}>
		<INPUT TYPE=hidden name=team_id value={$team_id}>
		<INPUT TYPE=hidden name=update value=true>
		<INPUT TYPE=TEXT NAME=teamname SIZE=40 MAXLENGTH=40 VALUE="{$team_name}"><BR>
		{$l_team_eddesc}: <BR>
		<INPUT TYPE=TEXT NAME=teamdesc SIZE=40 MAXLENGTH=254 VALUE="{$description}"><BR>
		<INPUT TYPE=SUBMIT VALUE={$l_submit}><INPUT TYPE=RESET VALUE={$l_reset}>
		</FORM>
		<BR>
	{else}
		{if $count == 0}
			{$l_team} <B>{$teamname}</B> {$l_team_hasbeenr}<BR>
		{else}
			{$l_team_noupdatesamename}<br>
		{/if}
	{/if}
{else}
	{$l_team_error}
{/if}
</td></tr>
<tr><td><BR><a href="teams.php">{$l_clickme}</a> {$l_team_menu}.</td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td valign="top" width=18><img src = "templates/{$templatename}images/spacer.gif" height="220" width="18"></TD>
				</tr>
			</table>
		</td>
	</tr>
</table>

