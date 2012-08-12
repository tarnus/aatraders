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

function mypw(one,two)
{
	return Math.exp(two * Math.log(one));
}

function changeDelta(desiredvalue,currentvalue)
{
	return (mypw({/literal}{$upgrade_factor}{literal}, desiredvalue) - mypw({/literal}{$upgrade_factor}{literal}, currentvalue)) * {/literal}{$upgrade_cost}{literal};
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

			form.total_cost.value =
			changeDelta(form.cargoshiphull.value,{/literal}{$java_hull}{literal})
			+ changeDelta(form.cargoshippower.value,{/literal}{$java_power}{literal})
			 + 116383500;

			  if (form.total_cost.value > {/literal}{$java_credits}{literal})
			  {
				form.total_cost.value = '{/literal}{$l_no_credits}{literal}';
			  }else{
				form.total_cost.value =
				Comma(changeDelta(form.cargoshiphull.value,{/literal}{$java_hull}{literal})
			+ changeDelta(form.cargoshippower.value,{/literal}{$java_power}{literal})
				+ 116383500);
			  }

			  form.total_cost.length = form.total_cost.value.length;
			
			}
			// -->
			</SCRIPT>
			{/literal}

<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
	{if $isowner == 1}
		{if $ownhull == 1}
		<table width="100%" border="0" cellspacing="0" cellpadding="6" align="center">
		  <tr> 
			<td colspan="6" align="center"><b>{$l_planet_cargoshipbuy}</b><p></td>
		  </tr>
		  <tr> 
			<td colspan="6" align="center"><font color="#00ff00"><b>{$l_planet_cargoshipbuyinfo}&nbsp;&nbsp;</b>({$l_credits}: {$playercredits})</font></td>
		  </tr>
		  <tr> 
			<td align="center"><a href="planet.php?planet_id={$planet_id}&cargoshiphull=10&cargoshippower=1&command=buycargofinal"><img src="templates/{$templatename}images/cargo/0.png" width="80" height="80" border="0" alt=""></a><br>{$l_hull}: 10<br>{$l_power}: 1<br>{$l_ship_price}: {$cargoshipcost[1]}</td>
			<td align="center"><a href="planet.php?planet_id={$planet_id}&cargoshiphull=50&cargoshippower=1&command=buycargofinal"><img src="templates/{$templatename}images/cargo/1.png" width="80" height="80" border="0" alt=""></a><br>{$l_hull}: 50<br>{$l_power}: 1<br>{$l_ship_price}: {$cargoshipcost[2]}</td>
			<td align="center"><a href="planet.php?planet_id={$planet_id}&cargoshiphull=100&cargoshippower=1&command=buycargofinal"><img src="templates/{$templatename}images/cargo/2.png" width="80" height="80" border="0" alt=""></a><br>{$l_hull}: 100<br>{$l_power}: 1<br>{$l_ship_price}: {$cargoshipcost[3]}</td>
			<td align="center"><a href="planet.php?planet_id={$planet_id}&cargoshiphull=150&cargoshippower=1&command=buycargofinal"><img src="templates/{$templatename}images/cargo/3.png" width="80" height="80" border="0" alt=""></a><br>{$l_hull}: 150<br>{$l_power}: 1<br>{$l_ship_price}: {$cargoshipcost[4]}</td>
			<td align="center"><a href="planet.php?planet_id={$planet_id}&cargoshiphull=200&cargoshippower=1&command=buycargofinal"><img src="templates/{$templatename}images/cargo/4.png" width="80" height="80" border="0" alt=""></a><br>{$l_hull}: 200<br>{$l_power}: 1<br>{$l_ship_price}: {$cargoshipcost[5]}</td>
			<td align="center"><a href="planet.php?planet_id={$planet_id}&cargoshiphull=250&cargoshippower=1&command=buycargofinal"><img src="templates/{$templatename}images/cargo/5.png" width="80" height="80" border="0" alt=""></a><br>{$l_hull}: 250<br>{$l_power}: 1<br>{$l_ship_price}: {$cargoshipcost[6]}</td>
		  </tr>
		  <tr> 
			<td colspan="6" align="center"><font color="#00ff00"><b>{$l_planet_cargoshipbuildinfo}</b></font></td>
		  </tr>
		<form action="planet.php?planet_id={$planet_id}&command=buycargofinal" method=post>
		<TR>
			<TD align="center">{$l_hull}: {$cargoshiphull}</TD>
			<TD align="center">{$l_power}: {$cargoshippower}</TD>
			<TD align="center"><INPUT TYPE=SUBMIT VALUE={$l_buy} ONCLICK="countTotal()"></TD>
			<TD align="center" colspan=3">{$l_totalcost}: <INPUT TYPE=TEXT style="text-align:right" NAME=total_cost SIZE=22 VALUE="116,384,000" ONFOCUS="countTotal()" ONBLUR="countTotal()" ONCHANGE="countTotal()" ONCLICK="countTotal()"></td>
		</TR>
		</form>
		</table>

		{else}
			{$l_planet_cargoowned}<BR>
		{/if}
	{else}
		<br><b>{$l_planet_cargonoown}</b><br>
	{/if}
		
	<BR><a href='planet.php?planet_id={$planet_id}'>{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>
	{if $allow_ibank}
		{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
	{/if}

	<A HREF ="bounty.php">{$l_by_placebounty}</A><p>

</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
