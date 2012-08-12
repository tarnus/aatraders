<H1>{$title}</H1>
<table width="750" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
		<form action=main.php method=post>
		{$l_chf_therearetotalfightersindest}<br>
		<INPUT TYPE=RADIO NAME=response CHECKED VALUE=retreat>{$l_chf_youcanretreat}<BR>
		<INPUT TYPE=RADIO NAME=response VALUE=fight>{$l_chf_inputfight}<BR>
{if $sector_zone_id != 2}
		<INPUT TYPE=RADIO NAME=response VALUE=run>{$l_chf_inputrun}<BR>
{/if}
		<INPUT TYPE=RADIO NAME=response VALUE=sneak>{$l_chf_inputcloak}<br><BR>
		<input type=submit value={$l_chf_go}><br><br>
		<input type=hidden name=move_method value={$move_method}>
		<input type=hidden name=move_defense_type value='perform'>
		<input type=hidden name=destination value={$destination|urlencode}>
		</form>
</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
