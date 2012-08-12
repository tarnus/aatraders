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

<tr><td colspan=3 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_planetconsolidate}<br>---------------------------------</td></tr>
<form action=igb.php?command=consolidate2 method=POST>
<tr valign=top>
<td colspan=3><font size=2 face="courier new" color=#52ACEA>{$l_igb_consolrates} :</td>
</tr>
<tr valign=top>
<td colspan=2><font size=2 face="courier new" color=#52ACEA>{$l_igb_minimum} :</font></td><td align=right><font size=2 face="courier new" color=#52ACEA>
<input class=term type=text size=15 maxlength=20 name=minimum value=0></font></td></tr>
<tr>
<td colspan=2><font size=2 face="courier new" color=#52ACEA>{$l_igb_maximum} :</font></td><td align=right><font size=2 face="courier new" color=#52ACEA><input class=term type=text size=15 maxlength=20 name=maximum value=0></font></td>
</tr>
<tr>
<td colspan=2><font size=2 face="courier new" color=#52ACEA>{$l_credits} % :</font></td><td align=right><font size=2 face="courier new" color=#52ACEA><input class=term type=text size=15 maxlength=3 name=percentage value=100></font></td>
</tr>
<tr>
<td colspan=2><font size=2 face="courier new" color=#52ACEA>{$l_minplanetpercent} % :</font></td><td align=right><font size=2 face="courier new" color=#52ACEA><input class=term type=text size=15 maxlength=3 name=maxplanetpercent value=0></font></td>
</tr>
<tr>
<td colspan=2>&nbsp;</td><td align=right><font size=2 face="courier new" color=#52ACEA><input class=term type=submit value="{$l_igb_compute}"></font></font></td>
</tr>

</form>
<tr><td colspan=3 align=center><font size=2 face="courier new" color=#52ACEA>
{$l_igb_transferrate3}
<tr valign=bottom>
<td colspan="2"><font size=2 face="courier new" color=#52ACEA><a href=igb.php?command=transfer>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
</tr>

</table>
</td></tr>
</table>

</center>
