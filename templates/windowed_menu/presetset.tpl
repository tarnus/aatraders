<H1>{$title}</H1>

<table width="400" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<form action=preset.php method=post>
	{php}
	for($totals = 0; $totals < $presettotal; $totals++){
		echo "$l_pre_set $totals: <INPUT TYPE=TEXT NAME=preset[$totals] SIZE=6 MAXLENGTH=30 VALUE=$presetinfo[$totals]> - Info: <INPUT TYPE=TEXT NAME=presetstuff[$totals] SIZE=15 MAXLENGTH=15 VALUE=\"$presettext[$totals]\"><BR>";
	}
	{/php}
	<input type=hidden name=name value=change>
	<br><input type=submit value={$l_pre_save}>
	</form>
</td></tr>

<tr><td><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
