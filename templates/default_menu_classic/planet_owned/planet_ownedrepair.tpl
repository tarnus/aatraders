<H1>{$title}</H1>
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
{/literal}
<table border=0 cellspacing=0 cellpadding=2 width="100%" align=center>
<tr><td>
	{literal}
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
		var output = '';
		var count = 0;
		for (i=number.length ; i > 0; i--) {
			count += 1;
			if ( count != 3)
			{
				output = number.substring(i - 1, i) + output;
			}
			else
			{
				if (i != 1)
				{
					output = ',' + number.substring(i - 1, i) + output;
				}
				else
				{
					output = number.substring(i - 1, i) + output;
				}
				count = 0;
			}
		}
		return (output);
	}
	else return number;
}

function mypw(one,two)
{
	return Math.exp(two * Math.log(one));
}

function SDchangeDelta(desiredvalue,currentvalue)
{
	return (mypw({/literal}{$upgrade_factor}{literal}, desiredvalue) - mypw({/literal}{$upgrade_factor}{literal}, currentvalue)) * {/literal}{$upgrade_cost}{literal} * {/literal}{$repairmodifier}{literal};
}

function changeDelta(desiredvalue,currentvalue)
{
	return (mypw({/literal}{$planet_upgrade_factor}{literal}, desiredvalue) - mypw({/literal}{$planet_upgrade_factor}{literal}, currentvalue)) * {/literal}{$upgrade_cost}{literal} * {/literal}{$repairmodifier}{literal};
}

	function countTotal()
	{
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
	if (form.overall_upgrade.value > {/literal}{$minoverall}{literal}){
		if (form.overall_upgrade.value > {/literal}{$java_fighter}{literal} && {/literal}{$java_fighter}{literal} != {/literal}{$java_fighter_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_fighter_normal}{literal}){
				form.fighter_upgrade.value=form.overall_upgrade.value;
			}else{
				form.fighter_upgrade.value={/literal}{$java_fighter_normal}{literal};
			}
		}else{
			form.fighter_upgrade.value={/literal}{$java_fighter}{literal};
		}
		if (form.overall_upgrade.value > {/literal}{$java_sensors}{literal} && {/literal}{$java_sensors}{literal} != {/literal}{$java_sensors_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_sensors_normal}{literal}){
				form.sensors_upgrade.value=form.overall_upgrade.value;
			}else{
				form.sensors_upgrade.value={/literal}{$java_sensors_normal}{literal};
			}
		}else{
			form.sensors_upgrade.value={/literal}{$java_sensors}{literal};
		}
		if (form.overall_upgrade.value > {/literal}{$java_beams}{literal} && form.overall_upgrade.value <= {/literal}{$java_beams_normal}{literal} && {/literal}{$java_beams}{literal} != {/literal}{$java_beams_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_beams_normal}{literal}){
				form.beams_upgrade.value=form.overall_upgrade.value;
			}else{
				form.beams_upgrade.value={/literal}{$java_beams_normal}{literal};
			}
		}else{
			form.beams_upgrade.value={/literal}{$java_beams}{literal};
		}
			
		if (form.overall_upgrade.value > {/literal}{$java_cloak}{literal} && form.overall_upgrade.value <= {/literal}{$java_cloak_normal}{literal} && {/literal}{$java_cloak}{literal} != {/literal}{$java_cloak_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_cloak_normal}{literal}){
				form.cloak_upgrade.value=form.overall_upgrade.value;
			}else{
				form.cloak_upgrade.value={/literal}{$java_cloak_normal}{literal};
			}
		}else{
			form.cloak_upgrade.value={/literal}{$java_cloak}{literal};
		}
		if (form.overall_upgrade.value > {/literal}{$java_torps}{literal} && form.overall_upgrade.value <= {/literal}{$java_torps_normal}{literal} && {/literal}{$java_torps}{literal} != {/literal}{$java_torps_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_torps_normal}{literal}){
				form.torp_launchers_upgrade.value=form.overall_upgrade.value;
			}else{
				form.torp_launchers_upgrade.value={/literal}{$java_torps_normal}{literal};
			}
		}else{
			form.torp_launchers_upgrade.value={/literal}{$java_torps}{literal};
		}
		if (form.overall_upgrade.value > {/literal}{$java_shields}{literal} && form.overall_upgrade.value <= {/literal}{$java_shields_normal}{literal} && {/literal}{$java_shields}{literal} != {/literal}{$java_shields_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_shields_normal}{literal}){
				form.shields_upgrade.value=form.overall_upgrade.value;
			}else{
				form.shields_upgrade.value={/literal}{$java_shields_normal}{literal};
			}
		}else{
			form.shields_upgrade.value={/literal}{$java_shields}{literal};
		}	
		if (form.overall_upgrade.value > {/literal}{$java_jammer}{literal} && form.overall_upgrade.value <= {/literal}{$java_jammer_normal}{literal} && {/literal}{$java_jammer}{literal} != {/literal}{$java_jammer_normal}{literal}){
			if (form.overall_upgrade.value <= {/literal}{$java_jammer_normal}{literal}){
				form.jammer_upgrade.value=form.overall_upgrade.value;
			}else{
				form.jammer_upgrade.value={/literal}{$java_jammer_normal}{literal};
			}
		}else{
			form.jammer_upgrade.value={/literal}{$java_jammer}{literal};
		}

	}
	form.total_cost.value =
	Comma(changeDelta(form.fighter_upgrade.value,{/literal}{$java_fighter}{literal})
	+ changeDelta(form.sensors_upgrade.value,{/literal}{$java_sensors}{literal})
	+ changeDelta(form.beams_upgrade.value,{/literal}{$java_beams}{literal})
	+ changeDelta(form.cloak_upgrade.value,{/literal}{$java_cloak}{literal})
	+ changeDelta(form.torp_launchers_upgrade.value,{/literal}{$java_torps}{literal})
	+ changeDelta(form.shields_upgrade.value,{/literal}{$java_shields}{literal})
	+ changeDelta(form.jammer_upgrade.value,{/literal}{$java_jammer}{literal})
	+ SDchangeDelta(form.sector_defense_weapons_upgrade.value,{/literal}{$java_sector_defense_weapons}{literal})
	+ SDchangeDelta(form.sector_defense_sensors_upgrade.value,{/literal}{$java_sector_defense_sensors}{literal})
	+ SDchangeDelta(form.sector_defense_cloak_upgrade.value,{/literal}{$java_sector_defense_cloak}{literal}))
	;
	  if (form.total_cost.value > {/literal}{$java_credits}{literal})
	  {
		form.total_cost.value = '{/literal}{$l_no_credits}{literal}';
	  }
	  form.total_cost.length = form.total_cost.value.length;
	
	form.fighter_costper.value=Comma(changeDelta(form.fighter_upgrade.value,{/literal}{$java_fighter}{literal}));
	form.sensors_costper.value=Comma(changeDelta(form.sensors_upgrade.value,{/literal}{$java_sensors}{literal}));
	form.beams_costper.value=Comma(changeDelta(form.beams_upgrade.value,{/literal}{$java_beams}{literal}));
	form.cloak_costper.value=Comma(changeDelta(form.cloak_upgrade.value,{/literal}{$java_cloak}{literal}));
	form.torp_launchers_costper.value=Comma(changeDelta(form.torp_launchers_upgrade.value,{/literal}{$java_torps}{literal}));
	form.shields_costper.value=Comma(changeDelta(form.shields_upgrade.value,{/literal}{$java_shields}{literal}));
	form.jammer_costper.value=Comma(changeDelta(form.jammer_upgrade.value,{/literal}{$java_jammer}{literal}));
	form.sector_defense_weapons_costper.value=Comma(SDchangeDelta(form.sector_defense_weapons_upgrade.value,{/literal}{$java_sector_defense_weapons}{literal}));
	form.sector_defense_sensors_costper.value=Comma(SDchangeDelta(form.sector_defense_sensors_upgrade.value,{/literal}{$java_sector_defense_sensors}{literal}));
	form.sector_defense_cloak_costper.value=Comma(SDchangeDelta(form.sector_defense_cloak_upgrade.value,{/literal}{$java_sector_defense_cloak}{literal}));
	}
	// -->
	</SCRIPT>
	{/literal}

	<FORM ACTION='planet.php?planet_id={$planet_id}&command=repairfinal' METHOD=POST>
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
	<TABLE WIDTH="99%" BORDER=0 CELLSPACING=0 CELLPADDING=0>
		<TR BGCOLOR="#585980">
			<TD align="center"><B>{$l_planetary_credits}</B></TD>
			<TD align="center"><B>{$l_max_credits}</B></TD>
			<TD align="center"><B>{$l_overallrepair}</B></TD>
		</TR>
		<TR BGCOLOR="#3A3B6E">
			<TD align="center">{$planet_creditsout}</TD>
			<TD align="center">{$planet_max_creditsout}</TD>
			<TD align="center">{$planet_overall}</TD>
		</TR>
		<TR BGCOLOR="#3A3B6E"><TD colspan="6"><img src="/images/spacer.gif" width="1" height="3"></TD></TR>
	</table>
								<table cellspacing = "0" cellpadding = "0" border = "0" width="99%">
								<tr>
									<td colspan = "2"><img src = "templates/{$templatename}images/spacer.gif" width = "1" height = "10"></td>
								</tr><TR BGCOLOR="#585980"><TD><B>{$l_planetary_defense_levels}</B></TD><TD><B>{$l_cost}</B></TD><TD><B>{$l_current_level}</B></TD><TD><B>{$l_planet_repair}</B></TD></TR>

	<TR BGCOLOR="#3A3B6E"><TD>{$l_fighter}</TD>
	<td><input type=text readonly class='portcosts1' name=fighter_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetfighter}</TD>
	<TD>
	{if $planetfighter_normal  != $planetfighter}
		{$planet_fighter}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="fighter_upgrade" value="{$planetfighter}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#23244F"><TD>{$l_sensors}</TD>
	<td><input type=text readonly class='portcosts2' name=sensors_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetsensors}</TD>
	<TD>
	{if $planetsensors_normal  != $planetsensors}
		{$planet_sensors}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="sensors_upgrade" value="{$planetsensors}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#3A3B6E"><TD>{$l_beams}</TD>
	<td><input type=text readonly class='portcosts1' name=beams_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetbeams}</TD>
	<TD>
	{if $planetbeams_normal  != $planetbeams}
		{$planet_beams}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="beams_upgrade" value="{$planetbeams}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#23244F"><TD>{$l_torp_launch}</TD>
	<td><input type=text readonly class='portcosts2' name=torp_launchers_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planettorps}</TD>
	<TD>
	{if $planettorps_normal  != $planettorps}
		{$planet_torps}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="torp_launchers_upgrade" value="{$planettorps}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#3A3B6E"><TD>{$l_shields}</TD>
	<td><input type=text readonly class='portcosts1' name=shields_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetshields}</TD>
	<TD>
	{if $planetshields_normal  != $planetshields}
		{$planet_shields}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="shields_upgrade" value="{$planetshields}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#23244F"><TD>{$l_jammer}</TD>
	<td><input type=text readonly class='portcosts1' name=jammer_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetjammer}</TD>
	<TD>
	{if $planetjammer_normal  != $planetjammer}
		{$planet_jammer}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="jammer_upgrade" value="{$planetjammer}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#3A3B6E"><TD>{$l_cloak}</TD>
	<td><input type=text readonly class='portcosts2' name=cloak_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetcloak}</TD>
	<TD>
	{if $planetcloak_normal  != $planetcloak}
		{$planet_cloak}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="cloak_upgrade" value="{$planetcloak}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#23244F"><TD>{$l_planetary_SD_weapons}</TD>
	<td><input type=text readonly class='portcosts2' name=sector_defense_weapons_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetsectordefenseweapons}</TD>
	<TD>
	{if $planetsectordefenseweapons_normal  != $planetsectordefenseweapons}
		{$planetsector_defense_weapons}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="sector_defense_weapons_upgrade" value="{$planetsectordefenseweapons}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#3A3B6E"><TD>{$l_planetary_SD_sensors}</TD>
	<td><input type=text readonly class='portcosts2' name=sector_defense_sensors_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetsectordefensesensors}</TD>
	<TD>
	{if $planetsectordefensesensors_normal  != $planetsectordefensesensors}
		{$planetsector_defense_sensors}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="sector_defense_sensors_upgrade" value="{$planetsectordefensesensors}">
	{/if}
	</TD></TR>

	<TR BGCOLOR="#23244F"><TD>{$l_planetary_SD_cloak}</TD>
	<td><input type=text readonly class='portcosts2' name=sector_defense_cloak_costper VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
	<TD>{$planetsectordefensecloak}</TD>
	<TD>
	{if $planetsectordefensecloak_normal  != $planetsectordefensecloak}
		{$planetsector_defense_cloak}
	{else}
		{$l_planet_upgrade}
		<input type="hidden" name="sector_defense_cloak_upgrade" value="{$planetsectordefensecloak}">
	{/if}
	</TD></TR>

	<tr><TD><INPUT TYPE=SUBMIT VALUE={$l_buy} {$onclick}></TD>
	<TD ALIGN=RIGHT>{$l_totalcost}: <INPUT TYPE=TEXT style="text-align:right" NAME=total_cost SIZE=27 VALUE=0 ONFOCUS="countTotal()" ONBLUR="countTotal()" ONCHANGE="countTotal()" ONCLICK="countTotal()"></td>
	<tr>
<BR>
	</FORM>
</table></td></tr>
<tr><td>
	<BR>	{$l_creds_to_spend}<BR>

	{if $allow_ibank}
		{$l_ifyouneedmore}<BR>
	{/if}

<br><a href='planet.php?planet_id={$planet_id}'>{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>
	<A HREF ="bounty.php">{$l_by_placebounty}</A>

</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

