<h1>{$title}</h1>

<form action=beacon.php method=post>
<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0">
			<TR>
				<TD colspan=2>
{$beacon_info}<br><br></td></tr>
<tr><td>{$l_beacon_enter}:</td><td><input type=text name=beacon_text size=40 maxlength=50><br><br></td></tr>
<tr><td align="center"><input type=submit value={$l_submit}></td><td align="center"><input type=reset value={$l_reset}>
				</td>
			</tr>
<tr><td colspan="2"><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

</form>

