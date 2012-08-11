<H1>{$title}</H1>
<center>

<table width="50%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
  <tr align="center">
		{if $avatar != "default_avatar.gif"}
		<td width="64" align="center" valign=top>
			<img src="images/avatars/{$avatar}" border="1">
		</td>
		<td width="5" align="center" valign=middle>
			<img src="images/spacer.gif" width="5">
		</td>
		{/if}
	<td width=65%>
  <font size=4 color=white><b>{$l_scan_ron} {$shipname}<br>{$l_scan_capt}  {$targetinfoname}</font>
	</td>
  </tr>
<tr><td colspan="3" align="center"><br>
	{if $scanbounty != 1}
	{$l_scan_bounty}<BR>
{/if}
{if $scanfedbounty != 1}
	{$l_scan_fedbounty}<BR>
{/if}
{$fedcheckbounty}<br>
</td></tr>
		</table>
	</td>
    <td >&nbsp;</td>
  </tr>
</table>
<br>
<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td >&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr>
	<td align="center" colspan="2">
	<font size=3 color=white><b>{$l_ship_levels}</b></font>
	<br>
	</td>
  </tr>
			<TR>
				<TD>
  <table border=0 cellspacing=0 cellpadding=3>
								<tr>
	  <td>
	  <font size=2><b>
	  {$l_hull_normal}&nbsp;<font color=white>({$shipinfo_hull_normal} / {$classinfo_maxhull})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$hull_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_engines_normal}&nbsp;<font color=white>({$shipinfo_engines_normal} / {$classinfo_maxengines})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$engines_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_power_normal}&nbsp;<font color=white>({$shipinfo_power_normal} / {$classinfo_maxpower})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$power_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_fighter_normal}&nbsp;<font color=white>({$shipinfo_fighter_normal} / {$classinfo_maxfighter})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$fighter_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_sensors_normal}&nbsp;<font color=white>({$shipinfo_sensors_normal} / {$classinfo_maxsensors})&nbsp;&nbsp;</font>	  
	  </b></font><td valign=bottom>
	  {$sensors_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
<font size=2 color=yellow><b>
	  {$l_avg_stats}&nbsp;<font color=white>{$average_stats}&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$average_bars}&nbsp;</td>
	  </td>
	</tr>

  </table>
  </td>

  <td align="left">

  <table border=0 cellspacing=0 cellpadding=3>
	<tr>
	  <td>
	  <font size=2><b>
	  {$l_armor_normal}&nbsp;<font color=white>({$shipinfo_armor_normal} / {$classinfo_maxarmor})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$armor_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_shields_normal}&nbsp;<font color=white>({$shipinfo_shields_normal} / {$classinfo_maxshields})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$shields_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_beams_normal}&nbsp;<font color=white>({$shipinfo_beams_normal} / {$classinfo_maxbeams})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$beams_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_torp_launch_normal}&nbsp;<font color=white>({$shipinfo_torp_launchers_normal} / {$classinfo_maxtorp_launchers})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$torp_launchers_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_cloak_normal}&nbsp;<font color=white>({$shipinfo_cloak_normal} / {$classinfo_maxcloak})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$cloak_normal_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_ecm_normal}&nbsp;<font color=white>({$shipinfo_ecm_normal} / {$classinfo_maxecm})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$ecm_normal_bars}&nbsp;</td>
	  </td>
	</tr>
</table>
				</td>
			</tr>
		</table>
	</td>
  </tr>
</table>
<br>
<table width="90%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr>
	<td width=33%>
	<font size=3 color=white><b>{$l_holds}</b></font>
	<br>
	</td>
	<td width=33%>
	<font size=3 color=white><b>{$l_arm_weap}</b></font>
	<br></td>
	</td>
	<td width=33%>
	<font size=3 color=white><b>{$l_devices}</b></font>
	<br></td>
	</td>
  </tr>   

  <tr>
	<td valign=top>

	<table border=0 cellspacing=0 cellpadding=3>
	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/credits.png>&nbsp;{$l_credits}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_credits}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		{$l_total_cargo}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$holds_used} / {$holds_max}
		</b></font>
		</td>
	  </tr>

{if $cargo_items > 0}
{php}
	for($i = 0; $i < $cargo_items; $i++)
	{
		if ($cargo_amount[$i] != "0")
		{
			echo "	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=\"images/ports/" . $cargo_name[$i] . ".png\">&nbsp;" . ucfirst($cargo_name[$i]) . "&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>";
			$places = explode(",", $cargo_amount[$i]);
			if (count($places) <= 3){
				echo $cargo_amount[$i];
			}
			else
			{
				$places[1] = AAT_substr($places[1], 0, 2);
				if(count($places) == 4){
					echo "$places[0].$places[1] B";
				}
				if(count($places) == 5){
					echo "$places[0].$places[1] T";
				}
				if(count($places) == 6){
					echo "$places[0].$places[1] Qd";
				}
				if(count($places) == 7){
					echo "$places[0].$places[1] Qn";
				}
			}
			echo " x $cargo_holds[$i]</b></font>
		</td>
	  </tr>";
		}
	}
{/php}
{/if}

	  </table>

  </td><td valign=top>

	<table border=0 cellspacing=0 cellpadding=3>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/energy.png>&nbsp;{$l_energy}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_energy} / {$energy_max}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/tfighter.png>&nbsp;{$l_fighters}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_fighters} / {$ship_fighters_max}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/torp.png>&nbsp;{$l_torps}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_torps} / {$torps_max}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/armor.png>&nbsp;{$l_armorpts}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_armor_pts} / {$armor_pts_max}
		</b></font>
		</td>
	  </tr>
		</table>

  <td valign=top>

	<table border=0 cellspacing=0 cellpadding=3>

	</table>

  </td></tr>

<tr><td colspan=4><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
