<H1>{$title}</H1>
<table width="50%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
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
  </tr>
</table>

