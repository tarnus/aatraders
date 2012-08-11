<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td><font color="lime"><b>{$l_planet_team}</b><font><br>
		<BR><a href="planet.php?planet_id={$planet_id}">{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>

		{if $allow_ibank == 1}
			{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
		{/if}

		<A HREF ="bounty.php">{$l_by_placebounty}</A><p>
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
