<H1>{$title}</H1>

<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
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
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
