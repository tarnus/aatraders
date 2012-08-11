<h1>{$title}</h1>

<table width="400" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
{if $otherplayer_sector_id != $shipinfo_sector_id}
{$l_ship_the} <font color=white> {$otherplayer_name}</font>, {$l_ship_nolonger} {$shipinfo_sector_id} <br>
{else}
{$l_ship_youc} <font color=white> {$otherplayer_name}</font>, {$l_ship_owned} <font color=white> {$otherplayer_character_name}. </font><br><br>
{$l_ship_perform}<br><br>
</td></tr>
	<tr>
		<td><font color=white><a href=scan.php?player_id={$player_id}&ship_id={$ship_id}>{$l_planet_scn_link}</a></font><br><br></td>
	</tr>
	<tr>
		<td><a href=attack.php?player_id={$player_id}&ship_id={$ship_id}>{$l_planet_att_link}</a><br><br></td>
	</tr>
<tr>
	<td colspan="3"><a href=message_send.php?to={$player_id}>{$l_send_msg}</a><br><br></td>
</tr>

{/if}
<br>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
