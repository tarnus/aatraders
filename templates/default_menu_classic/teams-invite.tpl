<H1>{$title}</H1>

<table  cellspacing = "0" cellpadding = "0" border = "0" align="center" width="500">
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
								<td valign="top" width=18><img src = "templates/{$templatename}images/g-mid-left.gif" height="160" width="18"></TD>
								<td valign="top">
									<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{if $notteamlimit}
	{if $invited}
		<FORM ACTION='teams.php' METHOD=POST>
		<TABLE><INPUT TYPE=hidden name=command value={$command}>
		<INPUT TYPE=hidden name=invited value=1>
		<INPUT TYPE=hidden name=team_id value={$team_id}>
		<TR><TD>{$l_team_selectp}:</TD><TD>
		<SELECT NAME=who>
		{php}
		for($i = 0; $i < $count; $i++){
			echo "<OPTION VALUE=$playerid[$i]>$playername[$i]";
		}
		{/php}
		</SELECT></TD></TR>
		<TR><TD><INPUT TYPE=SUBMIT VALUE={$l_submit}></TD></TR>
		</TABLE>
		</FORM>
	{else}
		{if $team_join_count < $max_team_changes}
			{if $issameteam}
				{if $team_invite}
					{$l_team_isorry}<BR><BR>
				{else}
					{$l_team_plinvted}<BR>
				{/if}
			{else}
				{$l_team_notyours}<BR>
			{/if}
		{else}
			{$l_team_cantinvite}
		{/if}
	{/if}
{else}
	{$l_team_full}<BR>
{/if}
</td></tr>
<tr><td><BR><a href="teams.php">{$l_clickme}</a> {$l_team_menu}.<BR></td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td valign="top" width=18><img src = "templates/{$templatename}images/g-mid-right.gif" height="160" width="18"></TD>
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

