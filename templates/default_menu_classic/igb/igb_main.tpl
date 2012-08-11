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
	<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_welcometoigb}<br>---------------------------------</td></tr>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_accountholder} :<br><br>{$l_igb_shipaccount} :<br>{$l_igb_igbaccount}&nbsp;&nbsp;:</td>
	<td align=right><font size=2 face="courier new" color=#52ACEA>{$playername}&nbsp;&nbsp;<br><br>{$playercredits} {$l_igb_credit_symbol}<br>{$accountbalance} {$l_igb_credit_symbol}<br></td>
	</tr>
	<tr><td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>{$l_igb_operations}<br>---------------------------------<br><br><a href="igb.php?command=withdraw">{$l_igb_withdraw}</a><br><a href="igb.php?command=deposit">{$l_igb_deposit}</a><br><a href="igb.php?command=transfer">{$l_igb_transfer}</a><br><a href="igb.php?command=loans">{$l_igb_loans}</a><br>&nbsp;</td></tr>
	<tr valign=bottom>
	<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
	</tr>

</table>
</td></tr>
</table>
</center>
