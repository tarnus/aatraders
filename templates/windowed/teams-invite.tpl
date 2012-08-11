<H1>{$title}</H1>

<table border="1" cellspacing="0" cellpadding="4" align="center" width="500">
	<tr>
		<td colspan=4>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td>	
						<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
							<tr bgcolor="black">
								<td valign="top" width=18><img src = "templates/{$templatename}images/spacer.gif" height="160" width="18"></TD>
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
					<td valign="top" width=18><img src = "templates/{$templatename}images/spacer.gif" height="160" width="18"></TD>
				</tr>
			</table>
		</td>
	</tr>
</table>

