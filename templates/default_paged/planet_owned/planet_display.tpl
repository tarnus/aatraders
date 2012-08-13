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

<FORM ACTION=planet.php?planet_id={$planet_id}&command=production METHOD=POST>
  
<table width="800" border="1" cellspacing="0" cellpadding="4" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td colspan="2" align="right"><table border="1" width="250" cellspacing="0" cellpadding="0" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td>
      <table width="250" height="42" border="0" cellspacing="0" cellpadding="0" >
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_fighter}</font></td>
        </tr>
        <tr valign="top"> 
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetfighter_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
          <td>{$fighterbar_normal}</td>
        </tr>
        <tr valign="top"> 
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetfighter}</font></td>
          <td>{$fighterbar}</td>
        </tr>
      </table></td></tr></table>
    </td>
    <td rowspan="4" align="center" valign="middle"> 
      <table width="100%" border="0" cellspacing="0" cellpadding="0" height="100%" align="center">
        <tr> 
          <td align="center"> 
            <img src="templates/{$templatename}images/planet{$planettype}.png" alt="" width="100" height="100"><br>
            <font color="white" style="font-size:11px; font-weight:bold;">{$planetname}</font><br><br>
          </td>
        </tr>
		<tr>
		<td align="center">
		<font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$l_planet_name}</font><br>
		  <font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{if $allow_genesis_destroy == 1}
			<A onclick="javascript: alert ('alert:{$l_planet_warning}');" HREF='planet.php?planet_id={$planet_id}&destroy=1&command=destroy'>{$l_planet_destroyplanet}</a><br>
			{/if}
			</font>
		</td>
		</tr>
      </table>
    </td>
    <td colspan="3" height="50"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td>
      <table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_sensors}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$sensorbar_normal}</td>
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsensors_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$sensorbar}</td>
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsensors}</font></td>
        </tr>
      </table></td></tr></table>
    </td>
  </tr>
  <tr> 
    <td height="50"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td><table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_beams}</font></td>
        </tr>
        <tr valign="top"> 
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetbeams_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
          <td>{$beambar_normal}</td>
        </tr>
        <tr valign="top"> 
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetbeams}</font></td>
          <td>{$beambar}</td>
        </tr>
      </table></td></tr></table>
    </td>
    <td rowspan="2" width="55" height="100"> 
      <table width="55" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td align="center">
<font color="#FFFFFF" style="font-size:11px; font-weight:bold;">&nbsp;{$l_planet_transfer_link}</font>
</td>
        </tr>
      </table>
    </td>
    <td rowspan="2" width="55" height="100"> 
      <table width="55" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td align="center">
		  	{if $planetbased == "Y"}	 
				<font color="#FFFFFF" style="font-size:11px; font-weight:bold;"><a href="planet.php?planet_id={$planet_id}&command=upgrade">{$l_planet_upgrade}</a></font><br><br>
				<font color="#FFFFFF" style="font-size:11px; font-weight:bold;"><a href="planet.php?planet_id={$planet_id}&command=repair">{$l_planet_repair}</a></font>
			{else}
				&nbsp;
			{/if}
</td>
        </tr>
      </table>
    </td>
    <td colspan="2" height="50" align="right"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td>
      <table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_jammer}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$jammerbar_normal}</td>
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetjammer_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$jammerbar}</td>
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetjammer}</font></td>
        </tr>
      </table></td></tr></table>
    </td>
  </tr>
  <tr> 
    <td height="50"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td><table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_torp_launch}</font></td>
        </tr>
        <tr valign="top"> 
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planettorps_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
          <td>{$torpbar_normal}</td>
        </tr>
        <tr valign="top"> 
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planettorps}</font></td>
          <td>{$torpbar}</td>
        </tr>
      </table></td></tr></table>
    </td>
    <td colspan="2" height="50" align="right"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td><table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_cloak}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$cloakbar_normal}</td>
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetcloak_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$cloakbar}</td>
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetcloak}</font></td>
        </tr>
      </table></td></tr></table>
    </td>
  </tr>
  <tr> 
    <td colspan="2" align="right"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td><table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_armor}</font></td>
        </tr>
        <tr valign="top"> 
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetarmor_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
          <td>{$armorbar_normal}</td>
        </tr>
        <tr valign="top"> 
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetarmor}</font></td>
          <td>{$armorbar}</td>
        </tr>
      </table></td></tr></table>
    </td>
    <td colspan="3" height="50"><table border="1" width="250" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td>
      <table width="250" height="42" border="0" cellspacing="0" cellpadding="0">
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_shields}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$shieldbar_normal}</td>
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetshields_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$shieldbar}</td>
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetshields}</font></td>
        </tr>
      </table></td></tr></table>
    </td>
  </tr>

  <tr> 
    <td colspan="1">
      <table width="250" height="42" border="1" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
        <tr align="center" valign="top"> 
          <td>
	      <table width="100%" border="0" cellspacing="0" cellpadding="0" >
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_SD_weapons}</font></td>
        </tr>
        <tr valign="top"> 
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsector_defense_weapons_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
          <td>{$sector_defense_weaponsbar_normal}</td>
        </tr>
        <tr valign="top"> 
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsector_defense_weapons}</font></td>
          <td>{$sector_defense_weaponsbar}</td>
        </tr>
      </table>
	  </td>
	  </tr>
	  </table>
    </td>
    <td colspan="3" height="50" align="center">
      <table width="250" height="42" border="1" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
        <tr align="center" valign="top"> 
          <td>
	      <table width="100%" border="0" cellspacing="0" cellpadding="0" >
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_SD_sensors}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$sector_defense_sensorsbar_normal}</td>
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsector_defense_sensors_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$sector_defense_sensorsbar}</td>
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsector_defense_sensors}</font></td>
        </tr>
      </table>
	  </td>
	  </tr>
	  </table>
    </td>
    <td colspan="1" height="50">
      <table width="250" height="42" border="1" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
        <tr align="center" valign="top"> 
          <td>
	      <table width="100%" border="0" cellspacing="0" cellpadding="0" >
        <tr align="center" valign="top"> 
          <td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_SD_cloak}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$sector_defense_cloakbar_normal}</td>
          <td width="150" align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_normal}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsector_defense_cloak_normal}</font><font color="white" style="font-size:11px; font-weight:bold;"> - {$l_max} {$max_tech_level}</font></td>
        </tr>
        <tr valign="top"> 
          <td align="right">{$sector_defense_cloakbar}</td>
          <td align="center"><font color="white" style="font-size:11px; font-weight:bold;">{$l_damaged}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetsector_defense_cloak}</font></td>
        </tr>
      </table>
	  </td>
	  </tr>
	  </table>
    </td>
  </tr>

  <tr> 
    <td colspan="6">
&nbsp;
    </td>
  </tr>
  
  <tr> 
    <td colspan="6">
&nbsp;
    </td>
  </tr>
  <tr> 
    <td colspan="6">
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
	  <tr>
	  	<td width="40%"><table border="1" align="center" cellspacing="0" cellpadding="0"  bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;"><tr><td><table align="center" border="1" cellspacing="0" cellpadding="0" bgcolor="#000000" bordercolorlight="#010101" bordercolordark="silver">
		<tr>
			<td colspan="2"><font color="white" style="font-size:11px; font-weight:bold;">{$l_max_credits}: <font color="#87d8ec" style="font-size:11px; font-weight:bold;">{$planet_ratio}%</font> - </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$max_credits}</font></td>
</tr><tr>
<td><font color="white" style="font-size:11px; font-weight:bold;">{$l_planetary_armorpts}: </font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$planetarmorpts}</font></td>
</tr><tr>
<td><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">{$l_colonists}: </font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$colonisttotal}</font>
</td>
		</tr>
		<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=pfighters VALUE="{$fighterprod}" SIZE=3 MAXLENGTH=3><font color="white" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_fighters}:&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$fightertotal}</font></td></tr>
<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=ptorp VALUE="{$torpprod}" SIZE=3 MAXLENGTH=3><font color="white" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_torps}:&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$torptotal}</font></td></tr>
<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=penergy VALUE="{$energyprod}" SIZE=3 MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_energy} {$energypercent} :&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$energytotal}</font></td></tr>
		<tr><td>
		<INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=pore VALUE="{$oreprod}" SIZE=3 MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_ore} {$orepercent} :&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$oretotal}</font>
		</td></tr><tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=pgoods VALUE="{$goodsprod}" SIZE=3 MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_goods} {$goodspercent} :&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$goodstotal}</font></td></tr>
<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=porganics VALUE="{$organicsprod}" SIZE=3 MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_organics} {$organicspercent} :&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$organicstotal}</font></td></tr>

{if $special_name != ""}
	<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=pspecial VALUE="{$prod_special}" SIZE=3 MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$special_name} :&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$special_amount}</font></td></tr>
{/if}


<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=presearch VALUE="{$researchprod}" SIZE=3 MAXLENGTH=3 readonly><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_pr_research}</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">&nbsp;</font></td></tr>
<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" NAME=pbuild VALUE="{$buildprod}" SIZE=3 readonly MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_pr_build}</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">&nbsp;</font></td></tr>
<tr><td><INPUT TYPE=TEXT style="color:#52ACEA; font-size:10px; font-weight:bold; background-color:black; align:right;" readonly NAME=pcredits VALUE="{$creditprod}" SIZE=3 MAXLENGTH=3><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">%&nbsp;{$l_credits}:&nbsp;</font></td><td><font color="yellow" style="font-size:11px; font-weight:bold;">{$credittotal}</font></td></tr>
{if $captured_countdown !=0}
<tr><td colspan="2" align="center" bgcolor="yellow"><font color="ff0000" style="font-size:11px; font-weight:bold;">{$l_planet_hidden_credits}</font></td></tr>
{/if}
<tr><td align="center"><INPUT TYPE=SUBMIT VALUE={$l_planet_update} ONCLICK="clean_js()"></td> <td>&nbsp;</td></tr>
</table></td></tr></table>
</td><td width="60%" valign="middle">

<table width="100%" border="0" cellspacing="0" cellpadding="0">
<tr>
	<td><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">{$l_turns_have} </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$playerturns}</font></td><td><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">{$l_dig}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$digtotal}</font></td>
<td><font color="#FFFFFF" style="font-size:11px; font-weight:bold;">{$l_spy}: </font><font color="yellow" style="font-size:11px; font-weight:bold;">{$spytotal}</font></td></tr>
</table>
<br>
<table width="100%" border="1" cellspacing="0" cellpadding="3" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
		<tr>
			<td colspan="2">
			<table border="1" cellspacing="0" cellpadding="1" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
				<tr>
					<td align="center"><font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$l_planet_land}
			{if $onplanet == 1}
			&nbsp;&nbsp;{$logout_link}
			{/if}
		</font></td><td align="center"><font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$l_planet_readlog}</font></td>{if $igbplanet != 0}<td align="center">
			<font color="#FFFFFF" style="font-size:11px; font-weight:bold;"><A HREF="igb.php?planet_id={$igbplanet}">{$l_igb_term}</A></font>
			</td>{/if}<td align="center"><font color="#FFFFFF" style="font-size:11px; font-weight:bold;"><A HREF ="bounty.php">{$l_by_placebounty}</A></font></td>
				</tr>
			</table>
<br>
		  <font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$l_planet_bbase}</font><br>
		  <font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$l_planet_mteam}</font><br>
		  <font color="#FFFFFF" style="font-size:10px; font-weight:bold;"> 
			{if $spycleaner != 0}
				<a href="spy.php?command=cleanup_planet&planet_id={$spycleaner}">{$l_clickme}</a> {$l_spy_cleanupplanet}
			{else}
				&nbsp;
			{/if}
			</font><br>
			<font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$cashstatus} {$l_planet_tcash}</font><br>
		{if $planetbased == "Y"}
			<font color="#FFFFFF" style="font-size:10px; font-weight:bold;">
			{$l_main_shipyard2}<a href="planet.php?planet_id={$planet_id}&command=shipyard">{$l_main_shipyard1}</a></font><br>
		{/if}
			<br>
			<font color="#FFFFFF" style="font-size:10px; font-weight:bold;">{$l_planet_lastvisited}</a></font><br>
			</td></tr>
        <tr>
          <td width="80" height="80" align="center">{if $allow_autotrades == 1 && $sg_sector == 0}{$cargoimage}{/if}</td>
          <td align="center">{if $allow_autotrades == 1 && $sg_sector == 0}<font color="#FFFFFF" style="font-size:11px; font-weight:bold;">{$l_planet_autotrade}</font>{/if}</td>
        </tr>
		</table>
		
		</td>
	  </tr>
       
      </table>
		<table align="center">
			        <tr>
			{for start=0 stop=$artifactcount-1 step=1 value=myLoop}
					<td align=center valign=top class=nav_title_12>
					<a href="artifact_grab.php?artifact_id={$artifact_id[$myLoop]}" onMouseover="ddrivetip('{$artifactname[$myLoop]}','{$artifact_description[$myLoop]}');" onMouseout="hideddrivetip()">
					<img src="images/artifacts/{$artifactimage[$myLoop]}.gif" border=0></a><BR>
					<br><b>(<font color=#33ff00>{$artifactname[$myLoop]}</font>)</b>
					</td>
				{if $myLoop == 4 or $myLoop == 9 or $myLoop == 14 or $myLoop == 19 or $myLoop == 24}
					</tr><tr>
				{/if}
			{/for}
</tr>
</table>
    </td>
  </tr>
</table>
</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
</FORM>
