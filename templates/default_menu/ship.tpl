<h1>{$title}</h1>

<table width="400" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
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
  </tr>
</table>
