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

<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_planetconsolidate}<br>---------------------------------</td></tr>
<tr valign=top>
<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_transferamount} :</td>
<td align=right><font size=2 face="courier new" color=#52ACEA>{$total} C</td>
<tr valign=top>
<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_transferfee} :</td>
<td align=right><font size=2 face="courier new" color=#52ACEA>{$fee} C </td>
<tr valign=top>
<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_plaffected} :</td>
<td align=right><font size=2 face="courier new" color=#52ACEA>{$count}</td>
<tr valign=top>
<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_turncost} :</td>
<td align=right><font size=2 face="courier new" color=#52ACEA>{$tcost}</td>
<tr valign=top>
<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_amounttransferred} :</td>
<td align=right><font size=2 face="courier new" color=#52ACEA>{$transfer} C</td>
<tr valign=top><td colspan=2 align=right>
<form action=igb.php?command=consolidate3 method=POST>
<input type=hidden name=minimum value={$minimum}>
<input type=hidden name=maximum value={$maximum}>
<input type=hidden name=percentage value={$percentage}>
<input type=hidden name=maxplanetpercent value={$maxplanetpercent}>
<input class=term type=submit value="{$l_igb_consolidate}"></td>
</form>
<tr valign=bottom>
<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php?command=transfer>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
</tr>

</table>
</td></tr>
</table>

</center>
