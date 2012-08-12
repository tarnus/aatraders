<H1>{$title}</H1>


<table border="1" cellspacing="0" cellpadding="4" align="center" width="500">
	<tr>
		<td colspan=4>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td>	
						<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
							<tr bgcolor="black">
								<td valign="top" width=18><img src = "templates/{$templatename}images/spacer.gif" height="200" width="18"></TD>
								<td valign="top">
									<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{if $isplayerteam}
	{if !$confirmed}
		{$l_team_ejectsure} {$playername}? <A HREF="teams.php?command={$command}&confirmed=1&who={$who}">{$l_yes}</A> - <a href="teams.php">{$l_no}</a><BR>
	{else}
		{$playername} {$l_team_ejected}<BR>
	{/if}
{else}
	{$l_team_cheater} <BR><BR>{$l_team_punishment}:<BR><BR>
	{$l_die_vapor}<BR><BR>
	{$l_die_please}.<BR>
{/if}
</td></tr>
<tr><td><BR><a href="teams.php">{$l_clickme}</a> {$l_team_menu}.<BR></td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td valign="top" width=18><img src = "templates/{$templatename}images/spacer.gif" height="200" width="18"></TD>
				</tr>
			</table>
		</td>
	</tr>
</table>
