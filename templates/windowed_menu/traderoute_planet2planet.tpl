<h1>{$title}</h1>

<table border=1 cellspacing=1 cellpadding=2 width="720" align=center bgcolor="#000000">
	<tr bgcolor="#400040">
		<td align="center" colspan=2><b>{$l_tdr_tdrres}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td width="50%"><b>{$l_tdr_planet} {$source_planet_name} {$l_tdr_within} {$source_sector_name}</b></td>
		<td width="50%"><b>{$l_tdr_planet} {$destination_planet_name} {$l_tdr_within} {$destination_sector_name}</b></td>
	</tr>
	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$source_commodity}: {$source_commodity_start}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$source_commodity}: {$destination_commodity_start}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$destination_commodity}: {$source_commodity2_start}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$destination_commodity}: {$destination_commodity2_start}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$l_fighters}: {$source_start_fighters}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$l_fighters}: {$destination_start_fighters}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$l_torps}: {$source_start_torps}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$l_torps}: {$destination_start_torps}</b></td>
              </tr>
            </table>
		</td>
	</tr>
	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%" valign="top"><b>{$source_commodity} {$l_tdr_loaded}: {$source_commodity_loaded}</b></td>
                <td width="50%" valign="top"><b>{$source_commodity} {$l_tdr_dumped}: {$source_commodity_dumped}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$destination_commodity} {$l_tdr_dumped}: {$destination_commodity_dumped}</b></td>
                <td width="50%" valign="top"><b>{$destination_commodity} {$l_tdr_loaded}: {$destination_commodity_loaded}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_fighters} {$l_tdr_loaded}: {$total_fighters_bought}</b></td>
                <td width="50%" valign="top"><b>{$l_fighters} {$l_tdr_dumped}: {$total_fighters_dumped}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_torps} {$l_tdr_loaded}: {$total_torps_bought}</b></td>
                <td width="50%" valign="top"><b>{$l_torps} {$l_tdr_dumped}: {$total_torps_dumped}</b></td>
              </tr>
            </table>
		</td>
	</tr>
	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$source_commodity}: {$source_commodity_total}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$source_commodity}: {$destination_commodity_total}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$destination_commodity}: {$source_commodity2_total}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$destination_commodity}: {$destination_commodity2_total}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$l_fighters}: {$source_total_fighters}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$l_fighters}: {$destination_total_fighters}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$l_torps}: {$source_total_torps}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$l_torps}: {$destination_total_torps}</b></td>
              </tr>
            </table>
		</td>
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
                <td width="50%" valign="top"><b>{$l_tdr_energy} {$l_tdr_scooped}: {$total_energy_scooped}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_energy} {$l_tdr_dumped}: {$total_energy_dumped}</b></td>
              </tr>
            </table>
		</td>
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

