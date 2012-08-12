{literal}
<script language="javascript" type="text/javascript">
function clean_js()
{
	// Here we cycle through all form values (other than buy, or full), and regexp out all non-numerics. (1,000 = 1000)
	// Then, if its become a null value (type in just a, it would be a blank value. blank is bad.) we set it to zero.
	var form = document.forms[0];
	var i = form.elements.length;
	while (i > 0)
	{
		if ((form.elements[i-1].type == 'text') && (form.elements[i-1].name != ''))
		{
			var tmpval = form.elements[i-1].value.replace(/\D+/g, "");
			if (tmpval != form.elements[i-1].value)
			{
				form.elements[i-1].value = form.elements[i-1].value.replace(/\D+/g, "");
			}
		}
		if (form.elements[i-1].value == '')
		{
			form.elements[i-1].value ='0';
		}
		i--;
	}
}
</script>
<SCRIPT LANGUAGE="JavaScript">
<!--

function MakeMax(name, val)
{
	if (document.forms[0].elements[name].value != val)
	{
		if (val != 0)
		{
			document.forms[0].elements[name].value = val;
		}
	}
}

function Comma(number) {
	number = '' + Math.round(number);
	if (number.length > 3) {
		var mod = number.length % 3;
		var output = (mod > 0 ? (number.substring(0,mod)) : '');
		for (i=0 ; i < Math.floor(number.length / 3); i++) {
			if ((mod == 0) && (i == 0))
				output += number.substring(mod+ 3 * i, mod + 3 * i + 3);
			else
				output+= ',' + number.substring(mod + 3 * i, mod + 3 * i + 3);
		}
		return (output);
	}
	else return number;
}

// changeDelta function //
function mypw(one,two)
{
	return Math.exp(two * Math.log(one));
}

function changeDelta(desiredvalue,currentvalue)
{
	return (mypw({/literal}{$upgrade_factor}{literal}, desiredvalue) - mypw({/literal}{$upgrade_factor}{literal}, currentvalue)) * {/literal}{$upgrade_cost}{literal} * {/literal}{$alliancefactor}{literal};
}

function countTotal()
{
	// Here we cycle through all form values (other than buy, or full), and regexp out all non-numerics. (1,000 = 1000)
	// Then, if its become a null value (type in just a, it would be a blank value. blank is bad.) we set it to zero.
	clean_js()
	var newshipvalue = {/literal}{$newshipvalue1}{literal};
	var form = document.forms[0];
	var i = form.elements.length;
	while (i > 0)
	{
		if (form.elements[i-1].value == '')
		{
			form.elements[i-1].value ='0';
		}
		i--;
	}
	// Here we set all 'Max' items to 0 if they are over max - player amt.



	// Done with the bounds checking
	// Pluses must be first, or if empty will produce a javascript error
	form.total_cost.value = newshipvalue 
	+ changeDelta(form.hull_upgrade.value,{/literal}{$sship_minhull}{literal})
	+ changeDelta(form.engine_upgrade.value,{/literal}{$sship_minengines}{literal})
	+ changeDelta(form.power_upgrade.value,{/literal}{$sship_minpower}{literal})
	+ changeDelta(form.fighter_upgrade.value,{/literal}{$sship_minfighter}{literal})
	+ changeDelta(form.sensors_upgrade.value,{/literal}{$sship_minsensors}{literal})
	+ changeDelta(form.beams_upgrade.value,{/literal}{$sship_minbeams}{literal})
	+ changeDelta(form.armor_upgrade.value,{/literal}{$sship_minarmor}{literal})
	+ changeDelta(form.cloak_upgrade.value,{/literal}{$sship_mincloak}{literal})
	+ changeDelta(form.torp_launchers_upgrade.value,{/literal}{$sship_mintorp_launchers}{literal})
	+ changeDelta(form.shields_upgrade.value,{/literal}{$sship_minshields}{literal})
	+ changeDelta(form.ecm_upgrade.value,{/literal}{$sship_minecm}{literal}) 
  
	
	{/literal}
	{literal}

	form.total_cost2.value = Comma(form.total_cost.value);
	if (form.total_cost.value > {/literal}{$player_credits}{literal})
	{
		form.total_cost.value = '{/literal}{$l_no_credits}{literal}';
		form.total_cost2.value = form.total_cost.value;
	}
	form.total_cost.length = form.total_cost.value.length;

}
// -->
</SCRIPT>

{/literal}



<h1>{$title}</h1>

<center><font size=2 color=white><b>{$l_ship_welcome}</font></center><p>
  
<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
							<tr bgcolor="black">
								<td width=121 align=center><font size=2 color=white><b>{$l_ship_class}</b></font></td>
								<td colspan=2 width=* align=center><font size=2 color=white><b>{$l_ship_properties}</b></font></TD>
							</tr>
							{php}
$first = 1;
for($i = 0; $i < $countship; $i++)
{
	echo "<tr bgcolor=\"black\"><td height=100 width=121 align=center valign=middle background = templates/{$templatename}images/spacer.gif>" .
		 "<a style=\"text-decoration: none\" href=\"planet.php?planet_id=$planet_id&command=shipyard&stype=$currentshipid[$i]\"><img style=\"border: none\" src=\"$currentshipimage[$i].gif\"><br>" .
		 "<font size=2 color=white>&nbsp;<b>$currentshipname[$i]</a></b></font>"; 
	if($currentship[$i] != "")
		echo "<font size=2 color=white><br>($currentship[$i])</font>";
	if($storedship[$i] != "")
		echo "<font size=2 color=white><br>($storedship[$i])</font>";
	echo "<font size=2 color=white><br>&nbsp;<b>$l_ship_basehull $currentshipbasehull[$i]</a></b></font><br><br>";
	if ($first == 1)
	{
		$first = 0;
		echo "</td><td rowspan=100 valign=top>";
		if($currentstorage == "0")
		{
			echo "<form action=planet.php method=POST name=\"pship\">";
			echo "<table border=0 cellpadding=0 bgcolor=\"black\" width=\"100%\">" .
				 "<tr><td valign=top>" .
				 "<font size=4 color=white><b>$name</b></font><p>" .
				 "<font size=2 color=silver><b>$description</b></font><p>" .
				 "</td><td width=215 height=191 background = templates/{$templatename}images/spacer.gif align=center ><img src=\"$sship_img.gif\"></td><td>&nbsp;&nbsp;</td></tr>" .
				 "</table>" .
				 "<table border=0 cellpadding=0>" .
				 "<tr><td colspan=3 valign=top><font size=4 color=white><b>$l_ship_levels</b></font><br>&nbsp;</td></tr>" .
				 "<tr><td width=300><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minhull / $l_ship_max: $sship_maxhull)&nbsp;&nbsp;</font>" .
				 "$l_hull&nbsp;</b></font>" .
				 "</td><TD>{$ship_hull_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$hull_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minengines / $l_ship_max: $sship_maxengines)&nbsp;&nbsp;</font>" .
				 "$l_engines&nbsp;</b></font>" .
				 "</td><TD>{$ship_engines_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$engines_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minpower / $l_ship_max: $sship_maxpower)&nbsp;&nbsp;</font>" .
				 "$l_power&nbsp;</b></font>" .
				 "</td><TD>{$ship_power_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$power_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minfighter / $l_ship_max: $sship_maxfighter)&nbsp;&nbsp;</font>" .
				 "$l_fighter&nbsp;</b></font>" .
				 "</td><TD>{$ship_fighter_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$fighter_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minsensors / $l_ship_max: $sship_maxsensors)&nbsp;&nbsp;</font>" .
				 "$l_sensors&nbsp;</b></font>" .
				 "</td><TD>{$ship_sensors_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$sensors_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minarmor / $l_ship_max: $sship_maxarmor)&nbsp;&nbsp;</font>" .
				 "$l_armor&nbsp;</b></font>" .
				 "</td><TD>{$ship_armor_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$armor_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minshields / $l_ship_max: $sship_maxshields)&nbsp;&nbsp;</font>" .
				 "$l_shields&nbsp;</b></font>" .
				 "</td><TD>{$ship_shields_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$shields_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minbeams / $l_ship_max: $sship_maxbeams)&nbsp;&nbsp;</font>" .
				 "$l_beams&nbsp;&nbsp;</b></font>" .
				 "</td><TD>{$ship_beams_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$beams_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_mintorp_launchers / $l_ship_max: $sship_maxtorp_launchers)&nbsp;&nbsp;</font>" .
				 "$l_torp_launch&nbsp;</b></font>" .
				 "</td><TD>{$ship_torp_launchers_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$torp_launchers_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_mincloak / $l_ship_max: $sship_maxcloak)&nbsp;&nbsp;</font>" .
				 "$l_cloak&nbsp;</b></font>" .
				 "</td><TD>{$ship_cloak_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$cloak_bars</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minecm / $l_ship_max: $sship_maxecm)&nbsp;&nbsp;</font>" .
				 "$l_ecm&nbsp;</b></font>" .
				 "</td><TD>{$ship_ecm_dropdown}&nbsp;&nbsp;</TD><td valign=bottom align=left>$ecm_bars</td></tr>" .
				 "<tr><td><font color=white size=4><b><br>$l_ship_price: </b></td>" .
				 "<td colspan=2><font color=red size=4><b><br><input type='hidden' name='total_cost' value='0'> <INPUT TYPE=TEXT style=\"text-align:right\" NAME=total_cost2 SIZE=32 VALUE=$newshipvalue ONFOCUS=\"countTotal()\" ONBLUR=\"countTotal()\" ONCHANGE=\"countTotal()\" ONCLICK=\"countTotal()\">C</b></td>" .
				 "</tr>" .
				 "<tr><td><font color=white size=4><b><br>$l_ship_turns: </b></td>" .
				 "<td colspan=2><font color=red size=4><b><br>$sship_turnstobuild</b></td>" .
				 "</tr>" .
				 "</table><p>";
			if ($stype != $shipinfo_class) 
			{
				echo "<input type=hidden name=stype value=$stype>" .
					 "<input type=hidden name=newshipvalue value=$newshipvalue1>" .
				 	 "<input type=hidden name=planet_id value=$planet_id>" .
					 "<input type=hidden name=command value=shipyard_purchase>" .
					 "&nbsp;<input type=submit value=$l_ship_purchase>" .
					 "</form>";
			}
		}else{
			for($loop = 0; $loop < $totalshipsstored; $loop++)
			{
			echo "<table border=0 cellpadding=0 bgcolor=\"black\">" .
				 "<tr><td valign=top>" .
				 "<font size=4 color=white><b>$loop. $name</b></font><p>" .
				 "<font size=2 color=silver><b>$description</b></font><p>" .
				 "</td><td valign=top><img src=$sship_img.gif></td></tr>" .
				 "</table>";
			echo "<table border=0 cellpadding=0>" .
				 "<tr><td valign=top><font size=4 color=white><b>$l_ship_levels</b></font><br>&nbsp;</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minhull / $l_ship_max: $sship_maxhull)&nbsp;&nbsp;</font>" .
				 "$l_hull&nbsp;</b></font>" .
				 "<td valign=bottom>$shull_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minengines / $l_ship_max: $sship_maxengines)&nbsp;&nbsp;</font>" .
				 "$l_engines&nbsp;</b></font>" .
				 "<td valign=bottom>$sengines_bars[$loop]</td></td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minpower / $l_ship_max: $sship_maxpower)&nbsp;&nbsp;</font>" .
				 "$l_power&nbsp;</b></font>" .
				 "<td valign=bottom>$spower_bars[$loop]</td></td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minfighter / $l_ship_max: $sship_maxfighter)&nbsp;&nbsp;</font>" .
				 "$l_fighter&nbsp;</b></font>" .
				 "<td valign=bottom>$sfighter_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minsensors / $l_ship_max: $sship_maxsensors)&nbsp;&nbsp;</font>" .
				 "$l_sensors&nbsp;</b></font>" .
				 "<td valign=bottom>$ssensors_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minarmor / $l_ship_max: $sship_maxarmor)&nbsp;&nbsp;</font>" .
				 "$l_armor&nbsp;</b></font>" .
				 "<td valign=bottom>$sarmor_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minshields / $l_ship_max: $sship_maxshields)&nbsp;&nbsp;</font>" .
				 "$l_shields&nbsp;</b></font>" .
				 "<td valign=bottom>$sshields_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minbeams / $l_ship_max: $sship_maxbeams)&nbsp;&nbsp;</font>" .
				 "$l_beams&nbsp;&nbsp;</b></font>" .
				 "<td valign=bottom>$sbeams_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_mintorp_launchers / $l_ship_max: $sship_maxtorp_launchers)&nbsp;&nbsp;</font>" .
				 "$l_torp_launch&nbsp;</b></font>" .
				 "<td valign=bottom>$storp_launchers_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_minecm / $l_ship_max: $sship_maxecm)&nbsp;&nbsp;</font>" .
				 "$l_ecm&nbsp;</b></font>" .
				 "<td valign=bottom>$secm_bars[$loop]</td></tr>" .
				 "<tr><td><font size=2><b><font color=white>" .
				 "($l_ship_min: $sship_mincloak / $l_ship_max: $sship_maxcloak)&nbsp;&nbsp;</font>" .
				 "$l_cloak&nbsp;</b></font>" .
				 "<td valign=bottom>$scloak_bars[$loop]</td></tr>";
			echo "<tr><td colspan=2><hr><br></td></tr>" ;
			echo "<tr><td colspan=2>$l_ship_averagemaxtech $average_stats_max<br></td></tr>" ;
			echo "<tr><td colspan=2>$l_ship_averagenormaltech $average_stats[$loop]<br></td></tr>" ;
			echo "<tr><td colspan=2>$l_ship_averagecurrenttech $average_current_stats[$loop]<br></td></tr>" ;
			echo "<tr><td colspan=2><br>" ;
			if (($stype != $shipinfo_class) or ($ships2id != $shipsid))
			{
				echo "<form action=planet.php method=POST>" .
					 "<input type=hidden name=stype value=$stype>" .
					 "<input type=hidden name=switch value=yes>" .
					 "<input type=hidden name=confirm value=yes>" .
					 "<input type=hidden name=shipid1 value=$ships2id[$loop]>" .
					 "<input type=hidden name=planet_id value=$planet_id>" .
					 "<input type=hidden name=command value=shipyard_purchase>" .
					 "&nbsp;<input type=submit value='$l_ship_outstorage'>" .
					 "</form>";
				if (($stype ==1) and ($shipinfo_class==1) and ($ships2id != $shipsid))
				{
					echo"<p><b><font color=\"red\">$l_ship_storagewarn</font></b></p>";
				}
			}
			echo "</td></tr>" ;
			echo "<tr><td colspan=2><hr><br><br></td></tr>" ;
			echo "</table><p>";
			}
		}
		echo "</td></tr>";
	}
	else
	{
		echo "</td></tr>";
	}
}
{/php}
<tr><td align="center" colspan=9><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
