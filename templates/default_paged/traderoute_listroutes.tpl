<h1>{$title}</h1>

<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
<FORM ACTION=traderoute_delete.php METHOD=POST>
<table border=1 cellspacing=1 cellpadding=2 width="100%" align=center bgcolor="#000000">
<tr bgcolor="#585980"><td align="center" colspan=8><b>{$l_tdr_curtdr}</b></td></tr>
<tr align=center bgcolor="#585980">
<td><b>{$l_tdr_src}</b></td>
<td><b>{$l_tdr_srctype}</b></td>
<td><b>{$l_tdr_dest}</b></td>
<td><b>{$l_tdr_desttype}</b></td>
<td><b>{$l_tdr_move}</b></td>
<td><b>{$l_tdr_circuit}</b></td>
<td><b>{$l_tdr_change}</b></td>
<td><b>{$l_tdr_del}</b></td>
</tr>

{php}
	$curcolor = "#3A3B6E";
	for ($i=0; $i < $num_traderoutes; $i++)
	{
		echo "<tr bgcolor=$curcolor>";

		if ($tradesource_planet_id[$i] == 0)
		{
			echo "<td align=center>&nbsp;" . $tradesource_name[$i] . "&nbsp;$l_tdr_portin $l_sector <a href=main.php?move_method=real&engage=1&destination=" . $tradesource_sector[$i] . ">" . $tradesource_sector[$i] . "</a>&nbsp;<br>&nbsp;<font color=\"lime\"><b>$tradesource_zone[$i]</b></font>&nbsp;</td>";
			echo "<td align=center>&nbsp;" . $tradesource_commodity[$i] . "&nbsp;</td>";
		}else{
			echo "<td align=center>&nbsp;$l_tdr_planet <b>$tradesource_name[$i]</b>$l_tdr_within$l_sector <a href=\"main.php?move_method=real&engage=1&destination=$tradesource_sector[$i]\">$tradesource_sector[$i]</a>&nbsp;<br>&nbsp;<font color=\"lime\"><b>$tradesource_zone[$i]</b></font>&nbsp;</td>";
			echo "<td align=center>&nbsp;" . $tradesource_commodity[$i] . "&nbsp;</td>";
		}

		if ($tradedestination_planet_id[$i] == 0)
		{
			echo "<td align=center>&nbsp;" . $tradedestination_name[$i] . "&nbsp;$l_tdr_portin $l_sector <a href=\"main.php?move_method=real&engage=1&destination=" . $trade_destination_sector[$i] . "\">". $trade_destination_sector[$i] . "</a>&nbsp;<br>&nbsp;<font color=\"lime\"><b>$trade_destination_zone[$i]</b></font>&nbsp;</td>";
			echo "<td align=center>&nbsp;" . $tradedestination_commodity[$i] . "&nbsp;</td>";
		}else{
			echo "<td align=center>&nbsp;$l_tdr_planet <b>$tradedestination_name[$i]</b>$l_tdr_within$l_sector <a href=\"main.php?move_method=real&engage=1&destination=$trade_destination_sector[$i]\">$trade_destination_sector[$i]</a>&nbsp;<br>&nbsp;<font color=\"lime\"><b>$trade_destination_zone[$i]</b></font>&nbsp;</td>";
			echo "<td align=center>&nbsp;" . $tradedestination_commodity[$i] . "&nbsp;</td>";
		}

		if ($trademove_type[$i] == 'R')
		{
			echo "<td align=center>RS, ";
			echo $trade_energyscoop[$i];
			echo "</td>";
		}else{
			echo "<td align=center>$l_tdr_warp";
			if ($trade_roundtrip[$i] != 'Y')
			{
				echo ", $trade_energyscoop[$i] $l_tdr_turns<br>&nbsp;";
			}else{
				echo ", $trade_energyscoop[$i] $l_tdr_turns<br>&nbsp;";
			}
			echo "</td>";
		}

		if ($trade_roundtrip[$i] != 'Y')
		{
			echo "<td align=center>1 $l_tdr_way</td>";
		}else{
			echo "<td align=center>2 $l_tdr_ways</td>";
		}
		echo "<td align=center rowspan=2>";
		echo "<a href=\"traderoute_edit.php?traderoute_id=" . $traderoute_id[$i] . "\">";
		echo "$l_tdr_edit</a><br></td>";
		echo "<TD ALIGN=CENTER rowspan=2><font size=2>&nbsp;<INPUT TYPE=CHECKBOX NAME=TRDel[] VALUE=\"" . $traderoute_id[$i] . "\">" . "&nbsp;</font></TD>";
		echo "</tr>";
		echo "<tr bgcolor=$curcolor><td colspan=6 align=center>$l_tdr_trade $l_tdr_energy: <b>";
		if ($trademove_energy[$i] == "Y")
			echo "<font color=#00ff00>Y</font>";
		else echo "<font color=#ff0000>N</font>";
		echo "</b> - $l_tdr_trade $l_tdr_torps: <b>";
		if ($trademove_torps[$i] == "Y")
			echo "<font color=#00ff00>Y</font>";
		else echo "<font color=#ff0000>N</font>";
		echo "</b> - $l_tdr_trade $l_tdr_fighters: <b>";
		if ($trademove_fighters[$i] == "Y")
			echo "<font color=#00ff00>Y</font>";
		else echo "<font color=#ff0000>N</font>";
		echo "</b></td></tr>";
		if ($curcolor == "#3A3B6E")
		{
			$curcolor = "#23244F";
		}else{
			$curcolor = "#3A3B6E";
		}
	}
{/php}
<tr bgcolor="#23244F">
	<td colspan="7">&nbsp;</td><td align="center"><INPUT TYPE=SUBMIT VALUE="{$l_tdr_del}"></td>
</tr>
</table></FORM>
</td></tr>
<tr><td><br>{$l_tdr_newtdr}
</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>