<H1>{$title}</H1>

<form action=feedback.php method=post>
<table width="50%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
{$l_feedback_to}</td><td><input readonly type=text name=dummy size=40 maxlength=40 value=GameAdmin></td></tr>
<tr><td>{$l_feedback_from}</td><td><input readonly type=text name=dummy size=40 maxlength=40 value="{$playername} - {$playeremail}"></td></tr>
<tr><td>{$l_feedback_topi}</td><td><input readonly type=text name=subject size=40 maxlength=40 value={$l_feedback_feedback}></td></tr>
<tr><td>{$l_feedback_message}</td><td><textarea name=content rows=5 cols=40></textarea></td></tr>
<tr><td><input type=submit value={$l_submit}></td><td><input type=reset value={$l_reset}></td></tr>
<tr><td colspan=2><br>{$l_feedback_info}<br></td><td>
				</td>
			</tr>
<tr><td colspan=2><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

</form>
