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
<tr><td colspan=2>
{$linkmessage}
{if $linkcount != 0}
:&nbsp;
	{php}
			for($i = 0; $i < $linkcount; $i++){
			echo "$linklist[$i] ";
		}
	{/php}
{/if}
<br><br></td></tr>

<form action="warpedit.php" method="post">
<input type="hidden" name="confirm" value="add">
<tr><td>{$l_warp_query}</td><td><input type="text" name="target_sector" size="6" maxlength="30" value=""></td></tr>
<tr><td>{$l_warp_oneway}</td><td><input type="checkbox" name="oneway" value="oneway"></td></tr>

<tr><td><input type="submit" value="{$l_submit}" ><input type="reset" value="{$l_reset}"></td><tr>
</form>
<tr><td colspan=2><br><br>{$l_warp_dest}<br><br></td></tr>
<form action="warpedit.php" method="post">
<input type="hidden" name="confirm" value="delete">
<tr><td>{$l_warp_destquery}</td><td><input type="text" name="target_sector" size="6" maxlength="30" value=""></td></tr>
<tr><td>{$l_warp_bothway}?</td><td><input type="checkbox" name="bothway" value="bothway"></td></tr>

<tr><td><input type="submit" value="{$l_submit}" ><input type="reset" value="{$l_reset}"></td><tr>
</form>

<tr><td colspan=2><br><br>{$gotomain}<br><br></td></tr>
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
