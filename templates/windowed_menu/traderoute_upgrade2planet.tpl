<h1>{$title}</h1>

<table border=1 cellspacing=1 cellpadding=2 width="720" align=center bgcolor="#000000">
	<tr bgcolor="#400040">
		<td align="center" colspan=2><b>{$l_tdr_tdrres}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td width="50%"><b>{$source_port_type} {$l_tdr_portin} {$source_sector_name}</b></td>
		<td width="50%"><b>{$l_tdr_planet} {$destination_planet_name} {$l_tdr_within} {$destination_sector_name}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
        <td width="50%" valign="top"><b><font color="green">{$l_tdr_starting_credits}</font>: {$starting_player_credits}</b></td>
        <td width="50%" valign="top"><b><font color="red">{$l_tdr_ending_credits}</font>: {$ending_player_credits}</b></td>
	</tr>
	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%"><b>{$l_tdr_runscompleted}: {$tr_repeat}</b></td>
                <td width="50%"><b>&nbsp;</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_turnsused}: {$total_turns_used}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_turnsleft}: {$turns_left}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$total_fighters_bought} {$l_fighters} @ {$fighter_price} {$l_tdr_credits}</b></td>
                <td width="50%" valign="top"><b>{$l_fighters} {$l_tdr_dumped}: {$total_fighters_dumped}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$total_torps_bought} {$l_torps} @ {$torpedo_price} {$l_tdr_credits}</b></td>
                <td width="50%" valign="top"><b>{$l_torps} {$l_tdr_dumped}: {$total_torps_dumped}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_energy} {$l_tdr_scooped}: {$total_energy_scooped}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_energy} {$l_tdr_dumped}: {$total_energy_dumped}</b></td>
              </tr>
            </table>
		</td>
	</tr>
	<tr align=center bgcolor="#400040">
        <td colspan="2"><div align="center"><b>
			{if $profit_loss}
				<font color="red">{$l_tdr_totalcost}</font>
			{else}
				<font color="green">{$l_tdr_totalprofit}</font>
			{/if}: {$final_credits} </b></div></td>
        </tr>
	</tr>
	<tr bgcolor="#400040">
		<td align="center" colspan=2><b>
			{$l_tdr_engageagain}
			<form action="traderoute_engage.php?engage={$engage}" method=post>
			{$l_tdr_timestorep} <input type=text name=tr_repeat value=1 size=3> <input type=submit value={$l_submit}>
			</form>
			{$l_global_mmenu}
			</b>
		</td>
	</tr>
</table>

