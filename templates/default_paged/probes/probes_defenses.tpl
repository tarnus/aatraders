<h1>{$title}</h1>

{$clean_javascript}
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

// changeDelta function //
function mypw(one,two)
{
	return Math.exp(two * Math.log(one));
}

function changeDelta(desiredvalue,currentvalue)
{
	return (mypw({/literal}{$upgrade_factor}{literal}, desiredvalue) - mypw({/literal}{$upgrade_factor}{literal}, currentvalue)) * {/literal}{$upgrade_cost}{literal};
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
	// Pluses must be first, or if empty will produce a javascript error
	form.total_cost.value = Comma(changeDelta(form.sensors_upgrade.value,{/literal}{$probe_sensors}{literal})
	+ changeDelta(form.cloak_upgrade.value,{/literal}{$probe_cloak}{literal})
	+ changeDelta(form.engines_upgrade.value,{/literal}{$probe_engines}{literal}));

	if (form.total_cost.value > {/literal}{$player_credits}{literal})
	{
		form.total_cost.value = '{/literal}{$l_no_credits}{literal}';
	}

	form.sensors_costper.value=Comma(changeDelta(form.sensors_upgrade.value,{/literal}{$probe_sensors}{literal}));
	form.cloak_costper.value=Comma(changeDelta(form.cloak_upgrade.value,{/literal}{$probe_cloak}{literal}));
	form.engines_costper.value=Comma(changeDelta(form.engines_upgrade.value,{/literal}{$probe_engines}{literal}));
}
// -->
</SCRIPT>
{/literal}

<table border="1" cellspacing="0" cellpadding="0" width="500" align="center">
	<TR BGCOLOR="#585980">
		<TD colspan="8" align="center"><font color="white"><B>{$l_probe_named}</B></font></TD>
	</TR>
	<TR BGCOLOR="#23244F">
		<TD>
			{$l_creds_to_spend}<br>
			{if $allow_ibank}
				{$l_ifyouneedmore}
			{/if}
		</TD>
	</TR>
	<TR BGCOLOR="#23244F">
		<TD>
			<FORM ACTION='probes_upgrade_finish.php?probe_id={$probe_id}&probeupgrade=yes' METHOD=POST>
			<TABLE WIDTH="100%" BORDER="0" CELLSPACING="0" CELLPADDING="0">
				<TR BGCOLOR="#585980">
					<TD><B>{$l_probe_defense_levels}</B></TD>
					<TD><B>{$l_cost}</B></TD>
					<TD><B>{$l_current_level}</B></TD>
					<TD><B>{$l_upgrade}</B></TD>
				</TR>
				<TR BGCOLOR="#3A3B6E">
					<TD>{$l_engine}</TD>
					<td><input type="text" readonly class='portcosts1' name="engines_costper"  VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
					<TD>{$probe_engines}</TD>
					<TD>{$dropdown_engines}</TD>
				</TR>

				<TR BGCOLOR="#23244F">
					<TD>{$l_sensors}</TD>
					<td><input type="text" readonly class='portcosts2' name="sensors_costper"  VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
					<TD>{$probe_sensors}</TD>
					<TD>{$dropdown_sensors}</TD>
				</TR>

				<TR BGCOLOR="#3A3B6E">
					<TD>{$l_cloak}</TD>
					<td><input type="text" readonly class='portcosts1' name="cloak_costper"  VALUE='0' tabindex='-1' ONBLUR="countTotal()"></td>
					<TD>{$probe_cloak}</TD>
					<TD>{$dropdown_cloak}</TD>
				</TR>
				<tr>
					<TD><INPUT TYPE="SUBMIT" VALUE="{$l_buy}" ONCLICK="countTotal()"></TD>
					<TD ALIGN="RIGHT">{$l_totalcost}: <INPUT TYPE="TEXT" style="text-align:right" NAME="total_cost" SIZE="28" VALUE="0" ONFOCUS="countTotal()" ONBLUR="countTotal()" ONCHANGE="countTotal()" ONCLICK="countTotal()"></td>
				</tr>
			</TABLE>
			</FORM>
		</TD>
	</TR>
</TABLE>
<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
	<tr>
		<td><br><a href="probes_upgrade.php?probe_id={$probe_id}">{$l_clickme}</a> {$l_probe_linkback}.
		</td>
	</tr>
	<tr><td><br><br>{$gotomain}<br><br></td></tr>
</table>
