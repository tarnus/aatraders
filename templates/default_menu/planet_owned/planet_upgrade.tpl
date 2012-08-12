<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
	<td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
<TABLE BORDER=0 CELLSPACING=1 CELLPADDING=6 WIDTH="100%" ALIGN=CENTER>
<TR>
<TD align=center><font size=3 color=white><b>{$l_trade_result}</b></font></TD>
</TR>
<TR>
<TD align=center><b><font color=red>{$l_cost} : {$trade_credits} {$l_credits}</font></b></TD>
</TR>

{if $upgradefighter == 1}
<TR><TD align=left>{$l_fighter} {$l_trade_upgraded} {$fighter_upgrade}.</TD></TR>
{/if}
{if $upgradesensors == 1}
<TR><TD align=left>{$l_sensors} {$l_trade_upgraded} {$sensors_upgrade}.</TD></TR>
{/if}
{if $upgradebeams == 1}
<TR><TD align=left>{$l_beams} {$l_trade_upgraded} {$beams_upgrade}.</TD></TR>
{/if}
{if $upgradetorps == 1}
<TR><TD align=left>{$l_torp_launch} {$l_trade_upgraded} {$torp_launchers_upgrade}.</TD></TR>
{/if}
{if $upgradeshields == 1}
<TR><TD align=left>{$l_shields} {$l_trade_upgraded} {$shields_upgrade}.</TD></TR>
{/if}
{if $upgradejammer == 1}
<TR><TD align=left>{$l_jammer} {$l_trade_upgraded} {$jammer_upgrade}.</TD></TR>
{/if}
{if $upgradecloak == 1}
<TR><TD align=left>{$l_cloak} {$l_trade_upgraded} {$cloak_upgrade}.</TD></TR>
{/if}

{if $upgradesdweapons == 1}
<TR><TD align=left>{$l_planetary_SD_weapons} {$l_trade_upgraded} {$sector_defense_weapons_upgrade}.</TD></TR>
{/if}
{if $upgradesdsensors == 1}
<TR><TD align=left>{$l_planetary_SD_sensors} {$l_trade_upgraded} {$sector_defense_sensors_upgrade}.</TD></TR>
{/if}
{if $upgradesdcloak == 1}
<TR><TD align=left>{$l_planetary_SD_cloak} {$l_trade_upgraded} {$sector_defense_cloak_upgrade}.</TD></TR>
{/if}

</table>
<BR><BR>
<A HREF=planet.php?planet_id={$planet_id}>{$l_clickme}</A> {$l_toplanetmenu}
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
