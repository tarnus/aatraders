<H1>{$title}</H1>
<FORM ACTION=message_send.php METHOD=POST>
<table width="500" border="0" cellspacing="0" cellpadding="0" align="center">
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
{$l_mt_to}</TD><TD><SELECT NAME=to>
{php}
	for($i = 0; $i < $count; $i++){
		echo "<OPTION value=\"$sendid[$i]\" $selected[$i]>$sendname[$i]</OPTION>\n";
	}
{/php}

</SELECT></TD></TR>
<TR><TD>{$l_mt_from}</TD><TD><INPUT DISABLED TYPE=TEXT NAME=dummy SIZE=40 MAXLENGTH=40 VALUE="{$playername}"></TD></TR>
<TR><TD>{$l_mt_subject}</TD><TD><INPUT TYPE=TEXT NAME=subject SIZE=50 MAXLENGTH=80 VALUE="{$subject}"></TD></TR>
<TR><TD>{$l_mt_message}</TD><TD><TEXTAREA NAME=content ROWS=10 COLS=50>{$message}</TEXTAREA></TD></TR>
<TR><TD></TD><TD><INPUT TYPE=SUBMIT VALUE={$l_mt_send}><INPUT TYPE=RESET VALUE={$l_reset}></TD>
				</td>
			</tr>
<tr><td colspan="2"><br><br>{$gotomain}<br><br></td></tr>
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
</FORM>

