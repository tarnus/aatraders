<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
<table border=0 cellspacing=0 cellpadding=0 width=90% align="center">
  <tr>
		<td align="center" valign=top>
			 <img src="templates/{$templatename}images/planet{$planettype}.png" alt="" width="100" height="100">
		</td></tr><tr>
	<td align="center">
	{if $sc_base != "N"}
		<font size=4 color="#00ff00"><b>{$sc_base}</font><br>
	{/if}
  <font size=4 color=white><b>{$l_scan_ron} {$planetname}</font>
</td></tr>
<tr><td align="center">
	{if $scanbounty != 1}
	{$l_scan_bounty}<BR>
{/if}
{if $scanfedbounty != 1}
	{$l_scan_fedbounty}<BR>
{/if}
{$fedcheckbounty}<br><br>
</td></tr>
</table>
<p>

<table border=0 cellspacing=0 cellpadding=0 width=90% align="center">
  <tr>
	<td align="center" colspan="2">
	<font size=3 color=white><b>{$l_planetary_defense_levels}</b></font>
	<br>
	</td>
  </tr>

  <tr>
	<td align="right" width=50% valign="top">

	<table border=1 cellspacing=0 cellpadding=3>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_beams}&nbsp;<font color=white>({$planetinfo_beams_normal} / {$classinfo_maxbeams})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$beams_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_torp_launch}&nbsp;<font color=white>({$planetinfo_torp_launchers_normal} / {$classinfo_maxtorp_launchers})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$torp_launchers_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_fighter}&nbsp;<font color=white>({$planetinfo_fighter_normal} / {$classinfo_maxfighter})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$fighter_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_sensors}&nbsp;<font color=white>({$planetinfo_sensors_normal} / {$classinfo_maxsensors})&nbsp;&nbsp;</font>	  
	  </b></font><td valign=bottom>
	  {$sensors_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
<font size=2 color=#00ff00><b>
	  {$l_planetary_SD_weapons}&nbsp;<font color=white>({$planetinfo_sdweapons_normal} / {$classinfo_maxsdweapons})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$sdweapons_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
<font size=2 color=#00ff00><b>
	  {$l_planetary_SD_cloak}&nbsp;<font color=white>({$planetinfo_sdcloak_normal} / {$classinfo_maxsdcloak})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$sdcloak_normal_bars}&nbsp;</td>
	  </td>
	</tr>

  </table>
  </td>

  <td align="left" width=50% valign="top">

  <table border=1 cellspacing=0 cellpadding=3>
	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_armor}&nbsp;<font color=white>({$planetinfo_armor_normal} / {$classinfo_maxarmor})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$armor_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_shields}&nbsp;<font color=white>({$planetinfo_shields_normal} / {$classinfo_maxshields})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$shields_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_cloak}&nbsp;<font color=white>({$planetinfo_cloak_normal} / {$classinfo_maxcloak})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$cloak_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
	  <font size=2 color=#00ff00><b>
	  {$l_planetary_jammer}&nbsp;<font color=white>({$planetinfo_jammer_normal} / {$classinfo_maxjammer})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$jammer_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
<font size=2 color=#00ff00><b>
	  {$l_planetary_SD_sensors}&nbsp;<font color=white>({$planetinfo_sdsensors_normal} / {$classinfo_maxsdsensors})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$sdsensors_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td width=225>
<font size=2 color=yellow><b>
	  {$l_avg_stats}&nbsp;<font color=white>{$average_stats}&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$average_bars}&nbsp;</td>
	  </td>
	</tr>

  </table>

  </td>
</tr>
</table>

<p>

<table border=0 cellspacing=0 cellpadding=0 width=90%>
  <tr>
	<td width=50% align="center">
	<font size=3 color=white><b>{$l_holds}</b></font>
	<br>
	</td>
	<td width=50% align="center">
	<font size=3 color=white><b>{$l_arm_weap}</b></font>
	<br></td>
	</td>
  </tr>   

  <tr>
	<td valign=top width=50% align="center">

	<table border=0 cellspacing=0 cellpadding=3 >
	  <tr>
		<td>
		<font size=2><b>
		&nbsp; <img src="templates/{$templatename}images/credits.png" alt="" width="12" height="12">&nbsp;{$l_credits}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_credits}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/ports/ore.png" alt="" width="12" height="12">&nbsp;{$l_ore}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_ore}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/ports/organics.png" alt="" width="12" height="12">&nbsp;{$l_organics}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_organics}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/ports/goods.png" alt="" width="12" height="12">&nbsp;{$l_goods}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_goods}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/ports/colonists.png" alt="" width="12" height="12">&nbsp;{$l_colonists}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_colonists}
		</b></font>
		</td>
	  </tr>
	  
{if $l_specialname != ''}
	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/ports/{$l_special_image}.png" alt="" width="12" height="12">&nbsp;{$l_specialname}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_special}
		</b></font>
		</td>
	  </tr>
{/if}
	  </table>

  </td><td valign=top width=50% align="center">

	<table border=0 cellspacing=0 cellpadding=3>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/ports/energy.png" alt="" width="12" height="12">&nbsp;{$l_energy}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_energy}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/tfighter.png" alt="" width="12" height="12">&nbsp;{$l_fighters}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_fighters}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/torp.png" alt="" width="12" height="12">&nbsp;{$l_torps}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_torps}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="templates/{$templatename}images/armor.png" alt="" width="12" height="12">&nbsp;{$l_armorpts}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$planetinfo_armor_pts}
		</b></font>
		</td>
	  </tr>
		</table>

  </td></tr>

</table>

<table border=1 cellspacing=0 cellpadding=2 align="center">
  <tr>
	<td align="center">
	{if $shipcount != 0}
	{php}
	for($i = 0; $i < $shipcount; $i++){
		echo "<font size=2 color=white><b>$playeronplanet[$i] $l_planet_ison</b></font><br>";
	}
	{/php}
	{else}
		<font size=2 color=white><b>{$l_planet_noone} {$l_planet_ison}</b></font>
	{/if}
	</td>
  </tr> </table>

<tr><td>
<BR><a href='planet.php?planet_id={$planet_id}'>{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>

{if $allow_ibank}
	{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
{/if}

<A HREF ="bounty.php">{$l_by_placebounty}</A>
</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
