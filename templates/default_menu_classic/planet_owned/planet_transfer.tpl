<H1>{$title}</H1>

<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td><br>
{if $enable_spies == 1 && $spytotal != 0}
	{$spytotal} {$l_spy_transferred}.<BR>
{/if}
{if $enable_dignitaries == 1 && $digtotal != 0}
	{$digtotal} {$l_dig_transferred}.<BR>
{/if}
<br>
{if $s_special != ''}
{$s_special}<br>
{/if}
{if $s_ore != ''}
{$s_ore}<br>
{/if}
{if $s_goods != ''}
{$s_goods}<br>
{/if}
{if $s_organics != ''}
{$s_organics}<br>
{/if}
{if $s_colonists != ''}
{$s_colonists}<br>
{/if}
{if $s_energy != ''}
{$s_energy}<br>
{/if}
{if $s_torps != ''}
{$s_torps}<br>
{/if}
{if $s_fighters != ''}
{$s_fighters}<br>
{/if}
{if $s_credits != ''}
{$s_credits}<br>
{/if}
<br>
{if $p_special != ''}
{$p_special}<br>
{/if}
{if $p_ore != ''}
{$p_ore}<br>
{/if}
{if $p_goods != ''}
{$p_goods}<br>
{/if}
{if $p_organics != ''}
{$p_organics}<br>
{/if}
{if $p_colonists != ''}
{$p_colonists}<br>
{/if}
{if $p_energy != ''}
{$p_energy}<br>
{/if}
{if $p_torps != ''}
{$p_torps}<br>
{/if}
{if $p_fighters != ''}
{$p_fighters}<br>
{/if}
{if $p_credits != ''}
{$p_credits}<br>
{/if}
	<BR>
	{$l_planet2_compl}
	<br><BR>
{if $mineteam == 1}
	<a href=planet.php?planet_id={$planet_id}&command=transfer>{$l_clickme}</a> {$l_planet_transfer_return}<BR><BR>
	<a href=planet.php?planet_id={$planet_id}>{$l_clickme}</a> {$l_toplanetmenu}<BR>
{else}
	{$l_planet2_notowner}<BR>
{/if}
<br>
</td></tr>

<tr><td><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
