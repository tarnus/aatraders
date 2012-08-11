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

  {if $igb_svalue}
	<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_shiptransfer}<br>---------------------------------</td></tr>
	<tr valign=top><td><font size=2 face="courier new" color=#52ACEA>{$l_igb_igbaccount} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$accountbalance} C</td></tr>

	{if $igb_svalue == 0}
	  <tr valign=top><td><font size=2 face="courier new" color=#52ACEA>{$l_igb_maxtransfer} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$l_igb_unlimited}</td></tr>
	{else}
	  <tr valign=top><td nowrap><font size=2 face="courier new" color=#52ACEA>{$l_igb_maxtransferpercent} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$maxtrans} C</td></tr>
	{/if}

	<tr valign=top><td><font size=2 face="courier new" color=#52ACEA>{$l_igb_recipient} :</td><td align=right><font size=2 face="courier new" color=#52ACEA>{$targetname}&nbsp;&nbsp;</td></tr>
	<form action=igb.php?command=transfer3 method=POST>
	<tr valign=top>
	<td><br><font size=2 face="courier new" color=#52ACEA>{$l_igb_seltransferamount} :</td>
	<td align=right><br><input class=term type=text size=15 maxlength=20 name=amount value=0><br>
	<br><input class=term type=submit value={$l_igb_transfer}></td>
	<input type=hidden name=player_id value={$player_id}>
	</form>
	<tr><td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>
	{$l_igb_transferrate}
	<tr valign=bottom>
	<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php?command=transfer>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
	</tr>
  {else}
	<tr><td colspan=2 align=center valign=top><font size=2 face="courier new" color=#52ACEA>{$l_igb_planettransfer}<br>---------------------------------</td></tr>
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_srcplanet} {$sourcename} {$l_igb_in} {$sourcesector} :
	<td align=right><font size=2 face="courier new" color=#52ACEA>{$sourcecredits} C
	<tr valign=top>
	<td><font size=2 face="courier new" color=#52ACEA>{$l_igb_destplanet} {$destname} {$l_igb_in} {$destsector} :
	<td align=right><font size=2 face="courier new" color=#52ACEA>{$destcredits} C
	<form action=igb.php?command=transfer3 method=POST>
	<tr valign=top>
	<td><br><font size=2 face="courier new" color=#52ACEA>{$l_igb_seltransferamount} :</td>
	<td align=right><br><input class=term type=text size=15 maxlength=20 name=amount value=0><br>
	<br><input class=term type=submit value={$l_igb_transfer}></td>
	<input type=hidden name=splanet_id value={$splanet_id}>
	<input type=hidden name=dplanet_id value={$dplanet_id}>
	</form>
	<tr><td colspan=2 align=center><font size=2 face="courier new" color=#52ACEA>
	{$l_igb_transferrate2}<br><br>{$l_igb_maxtransfer}: {$transfercredits} C
	<tr valign=bottom>
	<td><font size=2 face="courier new" color=#52ACEA><a href=igb.php?command=transfer>{$l_igb_back}</a></td><td align=right><font size=2 face="courier new" color=#52ACEA>&nbsp;<br><a href="main.php">{$l_igb_logout}</a></td>
	</tr>
  {/if}

</table>
</td></tr>
</table>

</center>
