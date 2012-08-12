<h1>{$title}</h1>

<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	<FORM ACTION=profile.php METHOD=POST>
	{$l_profile_name} <input type="text" name="profilename" size="30" maxlength="150"><br>
	{$l_profile_password} <input type="password" name="profilepassword" size="20" maxlength="20">&nbsp;&nbsp;
	<input type="hidden" name="command" value="Register">
	<input type="hidden" name="url" value="{$url}">
	<input type="hidden" name="game" value="{$game}">
	<INPUT TYPE=SUBMIT VALUE="Register">
	</form>
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
