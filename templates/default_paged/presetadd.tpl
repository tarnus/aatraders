<H1>{$title}</H1>

<table width="400" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<form action=preset.php method=post>
	{$l_pre_set} {$presettotal}: <INPUT TYPE=TEXT NAME=preset SIZE=6 MAXLENGTH=30 VALUE=Sol> - {$l_pre_info}: <INPUT TYPE=TEXT NAME=presetstuff SIZE=15 MAXLENGTH=15 VALUE=""><BR>
	<input type=hidden name=name value=addcomplete>
	<br><input type=submit value={$l_pre_save}>
	</form>
</td></tr>

<tr><td><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
