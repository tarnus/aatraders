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
	if (({/literal}{$fighter_free}{literal} < form.fighter_number.value) && (form.fighter_number.value != '{/literal}{$l_full}{literal}'))
	{
		form.fighter_number.value=0
	}
	if (({/literal}{$torpedo_free}{literal} < form.torpedo_number.value) && (form.torpedo_number.value != '{/literal}{$l_full}{literal}'))
	{
		form.torpedo_number.value=0
	}
	if (({/literal}{$armor_free}{literal} < form.armor_number.value) && (form.armor_number.value != '{/literal}{$l_full}{literal}'))
	{
		form.armor_number.value=0
	}

	// Done with the bounds checking
	// Pluses must be first, or if empty will produce a javascript error
	form.total_cost.value = changeDelta(form.hull_upgrade.value,{/literal}{$ship_hull}{literal})
	+ changeDelta(form.engine_upgrade.value,{/literal}{$ship_engines}{literal})
	+ changeDelta(form.power_upgrade.value,{/literal}{$ship_power}{literal})
	+ changeDelta(form.fighter_upgrade.value,{/literal}{$ship_fighter}{literal})
	+ changeDelta(form.sensors_upgrade.value,{/literal}{$ship_sensors}{literal})
	+ changeDelta(form.beams_upgrade.value,{/literal}{$ship_beams}{literal})
	+ changeDelta(form.armor_upgrade.value,{/literal}{$ship_armor}{literal})
	+ changeDelta(form.cloak_upgrade.value,{/literal}{$ship_cloak}{literal})
	+ changeDelta(form.torp_launchers_upgrade.value,{/literal}{$ship_torp_launchers}{literal})
	+ changeDelta(form.shields_upgrade.value,{/literal}{$ship_shields}{literal})
	+ changeDelta(form.ecm_upgrade.value,{/literal}{$ship_ecm}{literal})
	{/literal}{$fighter_form}
	{$torpedo_form}
	{$armor_form}
	{literal}

	form.total_cost2.value = Comma(form.total_cost.value);
	if (form.total_cost.value > {/literal}{$player_credits}{literal})
	{
		form.total_cost.value = '{/literal}{$l_no_credits}{literal}';
		form.total_cost2.value = form.total_cost.value;
	}
	form.total_cost.length = form.total_cost.value.length;

	form.engine_costper.value=Comma(changeDelta(form.engine_upgrade.value,{/literal}{$ship_engines}{literal}));
	form.power_costper.value=Comma(changeDelta(form.power_upgrade.value,{/literal}{$ship_power}{literal}));
	form.fighter_costper.value=Comma(changeDelta(form.fighter_upgrade.value,{/literal}{$ship_fighter}{literal}));
	form.sensors_costper.value=Comma(changeDelta(form.sensors_upgrade.value,{/literal}{$ship_sensors}{literal}));
	form.beams_costper.value=Comma(changeDelta(form.beams_upgrade.value,{/literal}{$ship_beams}{literal}));
	form.armor_costper.value=Comma(changeDelta(form.armor_upgrade.value,{/literal}{$ship_armor}{literal}));
	form.cloak_costper.value=Comma(changeDelta(form.cloak_upgrade.value,{/literal}{$ship_cloak}{literal}));
	form.torp_launchers_costper.value=Comma(changeDelta(form.torp_launchers_upgrade.value,{/literal}{$ship_torp_launchers}{literal}));
	form.hull_costper.value=Comma(changeDelta(form.hull_upgrade.value,{/literal}{$ship_hull}{literal}));
	form.shields_costper.value=Comma(changeDelta(form.shields_upgrade.value,{/literal}{$ship_shields}{literal}));
	form.ecm_costper.value=Comma(changeDelta(form.ecm_upgrade.value,{/literal}{$ship_ecm}{literal}));
}
// -->
</SCRIPT>

{/literal}

<h1>{$title}</h1>

<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
	<P>
	{$l_creds_to_spend}<BR>
	{$l_ifyouneedmore}<BR>
	
	<A HREF="bounty.php">{$l_by_placebounty}</A><BR>
	 <FORM ACTION=port_purchase.php METHOD=POST>
		<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0 bgcolor="#000000">
		 <TR BGCOLOR="#585980">
		<TD><B>{$l_ship_levels}</B></TD>
		<TD><B>{$l_cost}</B></TD>
		<TD><B>{$l_current_level}</B></TD>
		<TD><B>{$l_upgrade}</B></TD>
		 </TR>
		 <TR BGCOLOR="#3A3B6E">
		<TD>{$l_hull}</TD>
		<TD><input type=text readonly class='portcosts1' name=hull_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></TD>
		<TD>{$ship_hull}</TD>
		<TD>{$ship_hull_dropdown}
		</TD>
		 </TR>
		 <TR BGCOLOR="#23244F">
		<TD>{$l_engines}</TD>
		<TD><input type=text readonly class='portcosts2' name=engine_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></TD>
		<TD>{$ship_engines}</TD>
		<TD>{$ship_engines_dropdown}
		</TD>
		 </TR>
		 <TR BGCOLOR="#3A3B6E">
		<TD>{$l_power}</TD>
		<TD><input type=text readonly class='portcosts1' name=power_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
		<TD>{$ship_power}</TD>
		<TD>{$ship_power_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#23244F">
		<TD>{$l_fighter}</TD>
		<TD><input type=text readonly class='portcosts2' name=fighter_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></TD>
		<TD>{$ship_fighter}</TD>
		<TD>{$ship_fighter_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#3A3B6E">
		<TD>{$l_sensors}</TD>
		<TD><input type=text readonly class='portcosts1' name=sensors_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
		<TD>{$ship_sensors}</TD>
		<TD>{$ship_sensors_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#23244F">
		<TD>{$l_beams}</TD>
		<TD><input type=text readonly class='portcosts2' name=beams_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
		<TD>{$ship_beams}</TD>
		<TD>{$ship_beams_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#3A3B6E">
		<TD>{$l_armor}</TD>
		<TD><input type=text readonly class='portcosts1' name=armor_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></TD>
		<TD>{$ship_armor}</TD>
		<TD>{$ship_armor_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#23244F">
		<TD>{$l_cloak}</TD>
		<TD><input type=text readonly class='portcosts2' name=cloak_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()" ONFOCUS="countTotal()"></TD>
		<TD>{$ship_cloak}</TD>
		<TD>{$ship_cloak_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#3A3B6E">
		<TD>{$l_ecm}</TD>
		<TD><input type=text readonly class='portcosts2' name=ecm_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()" ONFOCUS="countTotal()"></TD>
		<TD>{$ship_ecm}</TD>
		<TD>{$ship_ecm_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#23244F">
		<TD>{$l_torp_launch}</TD>
		<TD><input type=text readonly class='portcosts1' name=torp_launchers_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></TD>
		<TD>{$ship_torp_launchers}</TD>
		<TD>{$ship_torp_launchers_dropdown}
		</TD>
		</TR>
		<TR BGCOLOR="#3A3B6E">
		<TD>{$l_shields}</TD>
		<TD><input type=text readonly class='portcosts2' name=shields_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></TD>
		<TD>{$ship_shields}</TD>
		<TD>{$ship_shields_dropdown}
		</TD>
		</TR>
	 </TABLE>
	 <BR>
	 <TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0 bgcolor="#000000">
		<TR BGCOLOR="#585980">
		<TD><B>{$l_item}</B></TD>
		<TD><B>{$l_cost}</B></TD>
		<TD><B>{$l_current}</B></TD>
		<TD><B>{$l_max}</B></TD>
		<TD><B>{$l_qty}</B></TD>
		<TD><B>{$l_item}</B></TD>
		<TD><B>{$l_cost}</B></TD>
		<TD><B>{$l_current}</B></TD>
		<TD><B>{$l_max}</B></TD>
		<TD><B>{$l_qty}</B></TD>
		</TR>
		<TR BGCOLOR="#3A3B6E">
		<TD>{$l_fighters}</TD>
		<TD>{$fighter_cost}</TD>
		<TD>{$fighter_current}</TD>
		<TD>
	{if $total_fighters != $fighter_max}
		<a href='#' onClick="MakeMax('fighter_number', {$fighter_free});countTotal();return false;"; ONBLUR="countTotal()">{$number_fighter_free}</a></TD>
		<TD><INPUT TYPE=TEXT class='portcosts5' NAME=fighter_number SIZE=6 MAXLENGTH=10 VALUE=0 ONBLUR="countTotal()">
	{else}
		0<TD><input type=text readonly class='portcosts4' NAME=fighter_number MAXLENGTH=10 VALUE='{$l_full}' ONBLUR="countTotal()" tabindex='-1'>
	{/if}
		</TD>
		<TD>{$l_torps}</TD>
		<TD>{$torp_cost}</TD>
		<TD>{$torp_current}</TD>
		<TD>
	{if $total_torps != $torpedo_max}
		<a href='#' onClick="MakeMax('torpedo_number', {$torpedo_free});countTotal();return false;"; ONBLUR="countTotal()">{$number_torpedo_free}</a></TD>
		<TD><INPUT TYPE=TEXT class='portcosts5' NAME=torpedo_number SIZE=6 MAXLENGTH=10 VALUE=0 ONBLUR="countTotal()">
	{else}
		0<TD><input type=text readonly class='portcosts4' NAME=torpedo_number MAXLENGTH=10 VALUE='{$l_full}' ONBLUR="countTotal()" tabindex='-1'>
	{/if}
	</TD>
		</TR>
		<TR BGCOLOR="#23244F">
		<TD>{$l_armorpts}</TD>
		<TD>{$armor_cost}</TD>
		<TD>{$armor_current}</TD>
		<TD>
	{if $total_armor != $armor_max}
		<a href='#' onClick="MakeMax('armor_number', {$armor_free});countTotal();return false;"; ONBLUR="countTotal()">{$number_armor_free}</a></TD>
		<TD><INPUT TYPE=TEXT class='portcosts5' NAME=armor_number SIZE=6 MAXLENGTH=10 VALUE=0 ONBLUR="countTotal()">
	{else}
		0<TD><input type=text readonly class='portcosts5' NAME=armor_number MAXLENGTH=10 VALUE='{$l_full}' tabindex='-1' ONBLUR="countTotal()">
	{/if}
	</tr>
	 </TABLE><BR>
	<input type='hidden' name='total_cost' value='0'>
	 <TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0 bgcolor="#000000">
		<TR>
		<TD><INPUT TYPE=SUBMIT VALUE={$l_buy} ONCLICK="countTotal()"></TD>
		<TD ALIGN=RIGHT>{$l_totalcost}: <INPUT TYPE=TEXT style="text-align:right" NAME=total_cost2 SIZE=32 VALUE=0 ONFOCUS="countTotal()" ONBLUR="countTotal()" ONCHANGE="countTotal()" ONCLICK="countTotal()"></td>
		</TR>
	 </TABLE>
	</FORM>

</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
