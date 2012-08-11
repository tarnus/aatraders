<H1>{$title}</H1>


<table  cellspacing = "0" cellpadding = "0" border = "0" align="center" width="600">
	<tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
	</tr>
	<tr>
		<td colspan=4>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td>	
						<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
							<tr bgcolor="black">
								<td valign="top" width=18><img src = "templates/{$templatename}images/g-mid-left.gif" height="200" width="18"></TD>
								<td valign="top">
									<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{if $team_join_count < $max_team_changes}
	{if $playerteam == 0}
		{if $isteamname}
			<FORM ACTION="teams.php" METHOD=POST>
	 		{$l_team_entername}: 
			<INPUT TYPE=hidden name=command value={$command}>
			<INPUT TYPE=TEXT NAME=teamname SIZE=40 MAXLENGTH=40><BR>
			{$l_team_enterdesc}: 
	 		<INPUT TYPE=TEXT NAME=teamdesc SIZE=40 MAXLENGTH=254><BR>
		  	<INPUT TYPE=SUBMIT VALUE={$l_submit}><INPUT TYPE=RESET VALUE={$l_reset}>
			</FORM>
			<BR><BR>
	 	{else}
			{if $count == 0}
				{$l_team} <B>{$teamname}</B> {$l_team_hcreated}.<BR><BR>
			{else}
				{$l_team_nocreatesamename}<br>
			{/if}
		{/if}
	{else}
		<br>{$l_team_leavefirst}<br><br>
	{/if}
{else}
	{$l_team_cantcreate}
{/if}
</td></tr>
<tr><td><BR><a href="teams.php">{$l_clickme}</a> {$l_team_menu}.<BR></td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td valign="top" width=18><img src = "templates/{$templatename}images/g-mid-right.gif" height="200" width="18"></TD>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
	</tr>
</table>