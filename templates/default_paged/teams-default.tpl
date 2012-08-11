<H1>{$title}</H1>

{if $playerteamid == 0}
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	{$l_team_notmember}
	{if !$teaminvite}
		<br><br><font color=blue size=2><b>{$l_team_noinvite}</b></font><BR><br>
		{if $playerteamid == 0}
			{$l_team_ifyouwant}<BR>
			<a href="teams.php?command=6">{$l_clickme}</a> {$l_team_tocreate}<BR><BR>
		{/if}
	{else}
		<br><br><font color=blue size=2><b>{$l_team_injoin} 
		<a href=teams.php?command=1&team_id={$teaminvite}>{$inviteinfo}</A>.</b></font><BR>
		<A HREF=teams.php?command=3&team_id={$teaminvite}>{$l_clickme}</A> {$l_team_tojoin} <B>{$inviteinfo}</B> {$l_team_or} <A HREF=teams.php?command=8&team_id={$teaminvite}>{$l_clickme}</A> {$l_team_reject}<BR><BR>
	{/if}
</td><tr>
		</table>
	</td>
  </tr>
</table>
{else}
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<div align=center>
	<img src="images/icons/{$teamicon}"><br>
	<h3><font color=white><B>{$teamname}</B>
	<br><font size=2>"<i>{$teamdescription}</i>"</font></H3>
	
	{if $playerteammatch}
		<font color=white>
		{if $isplayercreator}
			{$l_team_coord}&nbsp;
		{else}
			{$l_team_member}&nbsp;
		{/if}
		{$l_options}<br><font size=2>
		{if $playerteammatch}
			[<a href='teams.php?command=9&team_id={$playerteamid}'>{$l_team_ed}</a>] - 
		{/if}
		[<a href=teams.php?command=7&team_id={$playerteamid}>{$l_team_inv}</a>] - [<a href=teams.php?command=4&team_id={$playerteamid}>{$l_team_cancelinv}</a>] - [<a href=teams.php?command=2&team_id={$playerteamid}>{$l_team_leave}</a>]</font></font>
	{/if}
	{if $teaminvite == 0}
		<br><br><font color=blue size=2><b>{$l_team_noinvite}</b></font><BR><br>
		{if $playerteamid == 0}
			{$l_team_ifyouwant}<BR>
	 		<a href="teams.php?command=6">{$l_clickme}</a> {$l_team_tocreate}<BR><BR>
		{/if}
	{else}
		<br><br><font color=blue size=2><b>{$l_team_injoin} 
		<a href=teams.php?command=1&team_id={$teaminvite}>{$inviteinfo}</A>.</b></font><BR>
		<A HREF=teams.php?command=3&team_id={$teaminvite}>{$l_clickme}</A> {$l_team_tojoin} <B>{$inviteinfo}</B> {$l_team_or} <A HREF=teams.php?command=8&team_id={$teaminvite}>{$l_clickme}</A> {$l_team_reject}<BR><BR>
	{/if}

	</div>
	</td></tr>
		</table>
	</td>
  </tr>
</table>
<br>
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr>
	<td><font color=white>{$l_team_members}</font></td>
	</tr>
	<tr bgcolor={$zonecolor}>
	<td bgcolor={$zonecolor}>&nbsp;</td>
	</tr><tr>
	{php}
	for($i = 0; $i<$teamcount; $i++) {
		echo "<td> - $teammember[$i] ($l_score $memberscore[$i]])";
		if ($memberowner[$i]) {
			echo " - <font size=2>[<a href=\"teams.php?command=5&who=$memberid[$i]\">$l_team_eject</A>]</font></td>";
		} else {
			if ($iscreator[$i])
			{
				echo " - $l_team_coord</td>";
			}
		}
		echo "</tr><tr>";
	}
	{/php}
	<td}><font color=white>{$l_team_pending} <B>{$teamname}</B></font></td>
	</tr><tr>
	{if $membercount != 0}
		</tr><tr>
	{php}
		for($i = 0; $i<$membercount; $i++) {
			echo "<td> - $membername[$i]</td>";
			echo "</tr><tr>";
		}
	{/php}
	{else}
		<td>{$l_team_noinvites} <B>{$teamname}</B>.</td>
		</tr><tr>
	{/if}
	</tr>
		</table>
	</td>
  </tr>
</table>
	
{/if}

{if $teams_count > 0}
<br>
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<TR BGCOLOR="#585980">
<TD colspan=4><font size="2" color=white>
{$l_team_galax}<BR><BR></font></td></tr>
	<tr>
	<TD><B><A HREF=teams.php?order=team_name&type={$type}>{$l_name}</A></B></TD>
	<TD><B>&nbsp;<A HREF=teams.php?order=number_of_members&type={$type}>{$l_team_members}</A></B></TD>
	<TD><B>&nbsp;<A HREF=teams.php?order=character_name&type={$type}>{$l_team_coord}</A></B></TD>
	<TD><B>&nbsp;<A HREF=teams.php?order=total_score&type={$type}>{$l_score}</A></B></TD>
	</TR>
	{php}
	$color = "#3A3B6E";
	for($i = 0; $i < $totalteamcount; $i++) {
		echo "<TR BGCOLOR=\"$color\">";
		echo "<TD><img src=\"images/icons/$teamlisticon[$i]\" width=16 height=16><a href=teams.php?command=1&team_id=".$teamlistid[$i].">".$teamlistname[$i]."</A></TD>";
		echo "<TD>&nbsp;".$teamlistnumber[$i]."</TD>";
		echo "<TD>&nbsp;<a href=message_send.php?name=".$teamlistcname[$i].">".$teamlistcname[$i]."</A></TD>";
		echo "<TD>&nbsp;" . $teamlistscore[$i] . "</TD>";
		echo "</TR>";
		if ($color == "#3A3B6E")
		{
			$color = "#23244F";
		}
		else
		{
			$color = "#3A3B6E";
		}
	}
	{/php}
			<tr>
		</table>
	</td>
  </tr>
</table>
<BR>
{else}
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	{$l_team_noteams}
</td></tr>
		</table>
	</td>
  </tr>
</table>
{/if}

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{if $team_join_count < $max_team_changes}
	{$l_team_allowedfront} 
	{php}
		echo $max_team_changes - $team_join_count;
	{/php}
	{$l_team_allowedback}<br><br>
{else}
	{$l_team_reachedlimit}<br><br>
{/if}
</td></tr>

<tr><td><BR><a href="teams.php">{$l_clickme}</a> {$l_team_menu}.<BR></td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
