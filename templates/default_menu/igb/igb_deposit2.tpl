<H1>{$title}</H1>
{literal}
<STYLE TYPE="text/css">
<!--
	input.term {background-color: #000000; color: #52ACEA; font-family:Courier New; font-size:10pt; border-color:#52ACEA;}
	select.term {background-color: #000000; color: #52ACEA; font-family:Courier New; font-size:10pt; border-color:#52ACEA;}

-->
</STYLE>
{/literal}
<center>
<table width=604 height=354 border=1>
<tr><td align=center bgcolor="#000000">
<table width=520 height=300 border=0>

<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_operationsuccessful}<br>---------------------------------</td></tr>
<tr valign=top>
<td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>{$amount} {$l_igb_creditstoyou}</td>
<tr><td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>{$l_igb_accounts}<br>---------------------------------</td></tr>
<tr valign=top>
<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_shipaccount} :<br>{$l_igb_igbaccount} :</td>
<td align=right><font size=2 face="courier new" color=#52ACEA>{$playercredits} C<br>{$accountbalance} C</tr>
<tr valign=bottom>
<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
</tr>

</table>
</td></tr>
</table>

</center>
