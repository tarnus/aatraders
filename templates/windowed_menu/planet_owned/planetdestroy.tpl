<H1>{$title}</H1>

<table width="400" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
		{if $destroy==1 and $allow_genesis_destroy == 1}
			{$planetname}<br><font color=red>{$l_planet_confirm}</font><br><A HREF="planet.php?planet_id={$planet_id}&destroy=2&command=destroy">{$l_yes}</A><br>
			<A HREF="planet.php?planet_id={$planet_id}">{$l_no}!</A><BR><br>
		{else}
			{if $destroy==2 and $allow_genesis_destroy == 1}
				{if $shipgenesis < 1}
					{$l_gns_nogenesis}<br>
				{/if}
				{if $turns < 1}
					{$l_gns_turn}<br>
				{/if}
			{/if}
		{/if}
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
