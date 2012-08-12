<h1>{$title}</h1>

<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "2" border = "1" width="100%">
<TR BGCOLOR="#585980"><TD colspan=10 align=center><font color=white><B>{$l_autotrade_report}</B></font></TD></TR>
<TR BGCOLOR="#23244F">
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_planet}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_hull}<br>{$l_autotrade_capacity}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_energy}<br>{$l_autotrade_capacity}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_goods}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_ore}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_organics}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_energy}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_colonist}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_credits}</font></B></TD>
<TD align='center'><B><font size=2 color='#79f487'>{$l_autotrade_delete}</font></B></TD>

</TR>
<FORM ACTION=autotrades.php METHOD=POST>
<INPUT TYPE=hidden name=command value=dismiss>

{if $tradecount != 0}
	{php}
		for($i = 0; $i < $tradecount; $i++){
			echo "<TR BGCOLOR=$color[$i]>";
			echo "<TD align='center'><font size=2 color='#87d8ec'><b><a href='main.php?move_method=real&engage=1&destination=$tradesector[$i]'>$tradename[$i]</a></b></font></TD>";
			echo "<TD align='center'><font size=2 color=yellow>$tradehull[$i]<br></font><font size=2 color=white>".$tradeholds[$i]."</font></TD>";
			echo "<TD align='center'><font size=2 color=yellow>$tradepower[$i]<br></font><font size=2 color=white>".$tradeenergy[$i]."</font></TD>";
			if($tradegoodsport[$i] == ''){
				echo "<TD align='center'><font size=2 color=white>$l_autotrade_noroute</font></TD>";
			}else{
				echo "<TD align='center'><font size=2 color=yellow>$tradegoodsprice[$i]</font> <font size=2 color=white>$l_autotrade_credit2<br>$l_autotrade_sector</font> <font size=2 color=yellow>$tradegoodsport[$i]</font></TD>";
			}
			if($tradeoreport[$i] == ''){
				echo "<TD align='center'><font size=2 color=white>$l_autotrade_noroute</font></TD>";
			}else{
				echo "<TD align='center'><font size=2 color=yellow>$tradeoreprice[$i]</font> <font size=2 color=white>$l_autotrade_credit2<br>$l_autotrade_sector</font> <font size=2 color=yellow>$tradeoreport[$i]</font></TD>";
			}
			if($tradeorganicsport[$i] == ''){
				echo "<TD align='center'><font size=2 color=white>$l_autotrade_noroute</font></TD>";
			}else{
				echo "<TD align='center'><font size=2 color=yellow>$tradeorganicsprice[$i]</font> <font size=2 color=white>$l_autotrade_credit2<br>$l_autotrade_sector</font> <font size=2 color=yellow>$tradeorganicsport[$i]</font></TD>";
			}
			if($tradeenergyport[$i] == ''){
				echo "<TD align='center'><font size=2 color=white>$l_autotrade_noroute</font></TD>";
			}else{
				echo "<TD align='center'><font size=2 color=yellow>$tradeenergyprice[$i]</font> <font size=2 color=white>$l_autotrade_credit2<br>$l_autotrade_sector</font> <font size=2 color=yellow>$tradeenergyport[$i]</font></TD>";
			}
			if($tradecolonistport[$i] == ''){
				echo "<TD align='center'><font size=2 color=white>$l_autotrade_noroute</font></TD>";
			}else{
				echo "<TD align='center'><font size=2 color=yellow>$tradecolonistprice[$i]</font> <font size=2 color=white>$l_autotrade_credit2<br>$l_autotrade_sector</font> <font size=2 color=yellow>$tradecolonistport[$i]</font></TD>";
			}
			echo "<TD align='center'><font size=2 color='#79f487'><b>".$tradecredits[$i]."</b></font></TD>";
			echo "<td align='center'><INPUT TYPE=CHECKBOX NAME=dismiss[$i] value=$tradedismiss[$i]></td></TR>";
		}
	{/php}
{/if}

<INPUT TYPE=hidden name=tradecount value={$tradecount}>
<TR BGCOLOR="#23244F">
<TD colspan=10 align=center><INPUT TYPE=submit value="{$l_autotrade_deletebutton}"></td></tr>
</FORM>
<tr><td align="center" colspan=10><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
