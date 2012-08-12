<H1>{$title}</H1>

<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
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
  </tr>
</table>
