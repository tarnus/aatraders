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

  {if $isplayer}
	<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_transfersuccessful}<br>---------------------------------</td></tr>
	<tr valign=top><td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>{$transfer} {$l_igb_creditsto} {$targetname}.</tr>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_transferamount} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$amount} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_transferfee} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$amount2} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_amounttransferred} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$transfer} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_igbaccount} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$accountbalance} C<br>
	<tr valign=bottom>
	<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php?command=login>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
	</tr>
  {else}
	<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_transfersuccessful}<br>---------------------------------</td></tr>
	<tr valign=top><td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>{$transfer} {$l_igb_ctransferredfrom} {$sourcename} {$l_igb_to} {$destname}.</tr>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_transferamount} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$amount} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_transferfee} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$amount2} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_amounttransferred} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$transfer} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_srcplanet} {$sourcename} {$l_igb_in} {$sourcesector} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$sourcecredits} C<br>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_destplanet} {$destname} {$l_igb_in} {$destsector} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$destcredits} C<br>
	<tr valign=bottom>
	<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
	</tr>
  {/if}

</table>
</td></tr>
</table>

</center>
