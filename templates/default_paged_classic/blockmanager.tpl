<H1>{$title}</H1>
<table width="50%" border="0" cellspacing="0" cellpadding="0" align="center">
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
				<TD colspan=2>
<img src = "templates/{$templatename}images/spacer.gif" width = "1" height = "10"></td>
								</tr><FORM ACTION=messageblockmanager.php METHOD=POST>
<TD align="center">{$l_block_receivefrom}<br><br>
{if $unblockcount != 0}
	<SELECT NAME=to2 size="10">
	{php}
		for($i = 0; $i < $unblockcount; $i++){
			echo "<OPTION>$unblockedplayers[$i]</OPTION>\n";
		}
	{/php}
	</SELECT>
	<br><br>
	<input type="submit" name="{$l_block_block}" value="{$l_block_block}">
{else}
	{$l_block_empty}
{/if}
</TD>
<input type="hidden" name="command" value="block">
</FORM>
<FORM ACTION=messageblockmanager.php METHOD=POST>
<TD align="center">{$l_block_blockfrom}<br><br>
{if $blockcount != 0}
	<SELECT NAME=to size="10">
	{php}
		for($i = 0; $i < $blockcount; $i++){
			echo "<OPTION>$blockedplayers[$i]</OPTION>\n";
		}
	{/php}
	</SELECT><br><br>
	<input type="submit" name="{$l_block_unblock}" value="{$l_block_unblock}">
{else}
	{$l_block_empty}
{/if}
</TD>
<input type="hidden" name="command" value="unblock">
</FORM>
</TR>
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

