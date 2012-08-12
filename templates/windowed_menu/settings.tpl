<center>
<h1>{$title}</h1>
<table width="650" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$version}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$release_version}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_time_since_reset}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$totaltime}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_allowpl}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_allowplresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_allownewpl}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_allownewplresponse}</font></td>
  </tr>
		</table>
	</td>
  </tr>
</table>


<h1>{$title2}</h1>
<table width="650" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_allowteamplcreds}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_allowteamplcredsresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_allowfullscan}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_allowfullscanresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_sofa}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_sofaresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_showpassword}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_showpasswordresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_genesisdestroy}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_genesisdestroyresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_igb}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_igbresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_ksm}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_ksmresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_navcomp}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_navcompresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_newbienice}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_newbieniceresponse}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_spies}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_spiesresponse}</font></td>
  </tr>
  {if $enable_spies}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_spycapture}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$l_s_spycaptureresponse}</font></td>
  </tr>
  {/if}
		</table>
	</td>
  </tr>
</table>


<h1>{$title3}</h1>
<table width="650" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_gameversion}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$game_name}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_averagetechewd}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$ewd_maxavgtechlevel}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_numsectors}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$sector_max}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_maxwarpspersector}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$link_max}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_averagetechfed}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$fed_max_avg_tech}</font></td>
  </tr>
  {if $allow_ibank}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_igbirateperupdate}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$bankinterest}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_igblrateperupdate}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$loaninterest}</font></td>
  </tr>
  {/if}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_techupgradebase}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$basedefense}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_collimit}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$colonist_limit}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_maxturns}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$max_turns}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_maxplanetssector}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$max_planets_sector}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_maxtraderoutes}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$max_traderoutes_player}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_colreprodrate}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$colonist_reproduction_rate}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_energyperfighter}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$energy_per_fighter}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_secfighterdegrade}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$defense_degrade_rate}</font></td>
  </tr>
  {if $enable_spies}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_spiesperplanet}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$max_spies_per_planet}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_spysuccessfactor}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$enable_spies2}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_spykillfactor}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$spy_kill_factor}</font></td>
  </tr>
  {/if}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_colsperfighter}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$fighter_prate}</font></td>
  </tr>
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_colspertorp}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$torpedo_prate}</font></td>
  </tr>
  {foreach key=key value=item from=$cargoproductionname}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$cargoproductionname[$key]}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$cargoprate[$key]}</font></td>
  </tr>
  {/foreach}
  <tr bgcolor="#000000">
	<td width="500"><font size="2" color="#FFFFFF">{$l_s_colspercreds}</font></td>
	<td align="right" width="150"><font size="2" color="#00ff00">{$credits_prate}</font></td>
  </tr>
		</table>
	</td>
  </tr>
</table>


{php}
for($i = 0; $i < $listcount; $i++)
{
	$variables = explode("|", $variablelist[$i]);
	if($variables[0] == "section")
	{
		if($i != 0)
		{
		{/php}
<tr><td><br><br>{$l_global_mlogin}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
		{php}
		}
		echo "<h1>$variables[1]</h1>";
		$i++;
		$variables = explode("|", $variablelist[$i]);
{/php}
<table width="650" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
{php}
	}
	echo "<tr bgcolor=\"#000000\">
	<td align=\"center\" width=\"200\"><font size=\"2\" color=\"#FFFFFF\">$variables[0]</font></td>
	<td align=\"center\" width=\"100\"><font size=\"2\" color=\"#00ff00\">$variables[1]</font></td>
	<td align=\"left\" width=\"300\"><font size=\"2\" color=\"#00ff00\">$variables[2]</font></td>
  </tr>
  <tr><td colspan=3><img src = \"templates/" . $templatename . "images/spacer.gif\" height=8></td></tr>
";
}
{/php}
<tr><td><br><br>{$l_global_mlogin}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
