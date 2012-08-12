<H1>{$title}</H1>

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
{php}
for ($i=0;$i<$count;$i++)
{
		echo "<TD width=100 height=50 align=center valign=middle><B>$smile_text[$i]</B></TD>\n";
		echo "<TD width=50 height=50 align=center valign=middle>" . $image[$i] . "</TD>\n";
		if (($i+1) % 3 == 0) echo "</TR><TR>\n";
}
{/php}
</TR>
<tr><td colspan="6" align="center">
{$l_shout_return} <a href="shoutbox.php">{$l_shout_title}</a>&nbsp;&nbsp;&nbsp;<a href="javascript:window.close();">{$l_shout_close}</a>
</td></tr>
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
