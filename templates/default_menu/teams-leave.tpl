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
{if $confirmleave == 0}
	{$l_team_confirmleave} <B>{$teamname}</B>? <a href="teams.php?command={$command}&confirmleave=1&team_id={$team_id}">{$l_yes}</a> - <A HREF="teams.php">{$l_no}</A><BR><BR>
{else}
	{if $confirmleave == 1}
		{if $number_of_members == 1}
			{$l_team_onlymember}<BR><BR>
		{else}
			{if $iscreator}
				{$l_team_youarecoord} <B>{$teamname}</B>. {$l_team_relinq}<BR><BR>
	 			<FORM ACTION='teams.php' METHOD=POST>
		  		<TABLE><INPUT TYPE=hidden name=command value={$command}>
				<INPUT TYPE=hidden name=confirmleave value=2>
				<INPUT TYPE=hidden name=team_id value={$team_id}>
				<TR><TD>{$l_team_newc}</TD><TD><SELECT NAME=newcreator>
				{php}
				for($i = 0; $i<$count; $i++){
					echo "<OPTION VALUE=$playerid[$i]>$playername[$i]</option>";
	 			}
				{/php}
		  		</SELECT></TD></TR>
				<TR><TD><INPUT TYPE=SUBMIT VALUE={$l_submit}></TD></TR>
				</TABLE>
				</FORM>
			{else}
				{$l_team_youveleft} <B>{$teamname}</B>.<BR><BR>
			{/if}
		{/if}
	{/if}

	{if $confirmleave == 2}
		{$l_team_youveleft} <B>{$teamname}</B> {$l_team_relto} {$newcreator}.<BR><BR>
	{/if}
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

