<H1>{$title}</H1>

<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
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
<FORM ACTION=defense_deploy.php METHOD=POST>
{$l_defense_deploy_max_fighters}<BR><BR>
{$l_defense_deploy_info1}<BR><BR>
{$l_defense_deploy_info2}<BR>
{$l_defense_deploy_deploy} <INPUT TYPE=TEXT NAME=nummines SIZE=10 MAXLENGTH=10 VALUE={$shiptorps}> {$l_mines}.<BR>
{$l_defense_deploy_deploy} <INPUT TYPE=TEXT NAME=numfighters SIZE=10 MAXLENGTH=10 VALUE={$shipfighters}> {$l_fighters}.<BR>
<INPUT TYPE=SUBMIT VALUE={$l_submit}></INPUT><INPUT TYPE=RESET VALUE={$l_reset}></INPUT><BR><BR>
</FORM>
</td></tr>

<tr><td><br><br>{$gotomain}<br><br>				</td>
			</tr>
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
