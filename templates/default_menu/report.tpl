{php}
function strip_places($itemin){

$places = explode(",", $itemin);
if (count($places) <= 1){
	return $itemin;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	$placecount=count($places);

	switch ($placecount){
		case 2:
			return "$places[0].$places[1] K";
			break;
		case 3:
			return "$places[0].$places[1] M";
			break;	
		case 4:
			return "$places[0].$places[1] B";
			break;	
		case 5:
			return "$places[0].$places[1] T";
			break;
		case 6:
			return "$places[0].$places[1] Qd";
			break;		
		case 7:
			return "$places[0].$places[1] Qn";
			break;
		case 8:
			return "$places[0].$places[1] Sx";
			break;
		case 9:
			return "$places[0].$places[1] Sp";
			break;
		case 10:
			return "$places[0].$places[1] Oc";
			break;
		}		
	
}

}
{/php}
<center>

<table width="60%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
  <tr>
		{if $avatar != "default_avatar.gif"}
		<td width="64" align="center" valign=top>
			<img src="images/avatars/{$avatar}" border="1">
		</td>
		<td width="5" align="center" valign=middle>
			<img src="images/spacer.gif" width="5">
		</td>
		{/if}
	<td width=65%>
	  <font size=5 color=white><b>{$shipname}<br>
	  <font size=3>
	  {$classname}</b></font></font><p>
	  <font size=2><b>
	  {$classdescription}
	  <br><br>
	  </b></font>
	</td>
	<td width=35% align=center valign=center><img src="{$classimage}.gif"></td>
  </tr>
		</table>
	</td>
  </tr>
</table>
<br>
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr>
	<td align="center" colspan="2">
	<font size=3 color=white><b>{$l_ship_levels}</b></font>
	<br>
	</td>
  </tr>

  <tr>
	<td align="right">

	<table cellspacing=0 cellpadding=3>
	<tr>
	  <td>
	  <font size=2><b>
	  {$l_hull_normal}&nbsp;<font color=white>({$shipinfo_hull_normal} / {$classinfo_maxhull})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_hull} / {$classinfo_maxhull})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$hull_normal_bars}&nbsp;<br>{$hull_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_engines_normal}&nbsp;<font color=white>({$shipinfo_engines_normal} / {$classinfo_maxengines})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_engines} / {$classinfo_maxengines})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$engines_normal_bars}&nbsp;<br>{$engines_bars}&nbsp;</td>
	 </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_power_normal}&nbsp;<font color=white>({$shipinfo_power_normal} / {$classinfo_maxpower})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_power} / {$classinfo_maxpower})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$power_normal_bars}&nbsp;<br>{$power_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_fighter_normal}&nbsp;<font color=white>({$shipinfo_fighter_normal} / {$classinfo_maxfighter})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_fighter} / {$classinfo_maxfighter})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$fighter_normal_bars}&nbsp;<br>{$fighter_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_sensors_normal}&nbsp;<font color=white>({$shipinfo_sensors_normal} / {$classinfo_maxsensors})&nbsp;&nbsp;</font>	  
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_sensors} / {$classinfo_maxsensors})&nbsp;&nbsp;</font>	  
	  </b></font><td valign=bottom>
	  {$sensors_normal_bars}&nbsp;<br>{$sensors_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  &nbsp;<br><font size=2 color=yellow><b>
	  {$l_avg_stats}&nbsp;<font color=white>({$average_stats} / {$average_stats_max})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  &nbsp;<br>{$average_bars}&nbsp;</td>
	  </td>
	</tr>

  </table>
  </td>

  <td align="left">

  <table cellspacing=0 cellpadding=3>
	<tr>
	  <td>
	  <font size=2><b>
	  {$l_armor_normal}&nbsp;<font color=white>({$shipinfo_armor_normal} / {$classinfo_maxarmor})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_armor} / {$classinfo_maxarmor})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$armor_normal_bars}&nbsp;<br>{$armor_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_shields_normal}&nbsp;<font color=white>({$shipinfo_shields_normal} / {$classinfo_maxshields})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_shields} / {$classinfo_maxshields})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$shields_normal_bars}&nbsp;<br>{$shields_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_beams_normal}&nbsp;<font color=white>({$shipinfo_beams_normal} / {$classinfo_maxbeams})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_beams} / {$classinfo_maxbeams})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$beams_normal_bars}&nbsp;<br>{$beams_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_torp_launch_normal}&nbsp;<font color=white>({$shipinfo_torp_launchers_normal} / {$classinfo_maxtorp_launchers})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_torp_launchers} / {$classinfo_maxtorp_launchers})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$torp_launchers_normal_bars}&nbsp;<br>{$torp_launchers_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_cloak_normal}&nbsp;<font color=white>({$shipinfo_cloak_normal} / {$classinfo_maxcloak})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_cloak} / {$classinfo_maxcloak})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$cloak_normal_bars}&nbsp;<br>{$cloak_bars}&nbsp;</td>
	  </td>
	</tr>

	<tr>
	  <td>
	  <font size=2><b>
	  {$l_ecm_normal}&nbsp;<font color=white>({$shipinfo_ecm_normal} / {$classinfo_maxecm})&nbsp;&nbsp;</font>
	  </b></font><br><font size=2><b>
	  {$l_damaged}&nbsp;<font color=white>({$shipinfo_ecm} / {$classinfo_maxecm})&nbsp;&nbsp;</font>
	  </b></font><td valign=bottom>
	  {$ecm_normal_bars}&nbsp;<br>{$ecm_bars}&nbsp;</td>
	 </td>
	</tr>

  </table>
  </td></tr>
		</table>
	</td>
  </tr>
</table>

<br>
<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr>
	<td width=33%><font size=3 color=white><b>{$l_holds}</b></font>
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
		{php}echo strip_places($shipinfo_credits); {/php}
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
		{php}echo strip_places($hold_space); {/php} / {php}echo strip_places($holds_max); {/php}
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
		{php}echo strip_places($shipinfo_energy); {/php} / {php}echo strip_places($energy_max); {/php}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/tfighter.png>&nbsp;<a href=defense_deploy.php>{$l_fighters}</a>&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{php}echo strip_places($shipinfo_fighters); {/php} / {php}echo strip_places($ship_fighters_max); {/php}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=templates/{$templatename}images/torp.png>&nbsp;<a href=defense_deploy.php>{$l_torps}</a>&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{php}echo strip_places($shipinfo_torps); {/php} / {php}echo strip_places($torps_max); {/php}
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
		{php}echo strip_places($shipinfo_armor_pts); {/php} / {php}echo strip_places($armor_pts_max); {/php}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="images/spacer.gif" width="12">&nbsp;{$l_beams} {$l_class}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_beams_class}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="images/spacer.gif" width="12">&nbsp;{$l_fighters} {$l_class}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_fighter_class}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="images/spacer.gif" width="12">&nbsp;{$l_torps} {$l_class}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_torp_launchers_class}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="images/spacer.gif" width="12">&nbsp;{$l_shields} {$l_class}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_shields_class}
		</b></font>
		</td>
	  </tr>

	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src="images/spacer.gif" width="12">&nbsp;{$l_armor} {$l_class}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{$shipinfo_armor_class}
		</b></font>
		</td>
	  </tr>

	</table>

  <td valign=top>

	<table border=0 cellspacing=0 cellpadding=3>
{php}
for($i = 0; $i < count($deviceclass); $i++)
{
echo"
	  <tr>
		<td>
		<font size=2><b>";
		if($deviceprogram[$i] != '')
			echo "<a href=" . $deviceprogram[$i] . ">";
		echo $devicename[$i] . "</a>&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		$deviceamount[$i]$deviceinfo[$i]
		</b></font>
		</td>
	  </tr>";
}
{/php}


	</table>
</td></tr>
{if $spycheck}
	<tr><td><BR><a href=spy.php>{$l_clickme}</a> {$l_spy_linkback}<BR></td></tr>
{/if}
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
