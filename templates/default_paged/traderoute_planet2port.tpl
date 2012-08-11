<h1>{$title}</h1>

<table border=1 cellspacing=1 cellpadding=2 width="720" align=center bgcolor="#000000">
	<tr bgcolor="#400040">
		<td align="center" colspan=2><b>{$l_tdr_tdrres}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td width="50%"><b>{$l_tdr_planet} {$source_planet_name} {$l_tdr_within} {$source_sector_name}</b></td>
		<td width="50%"><b>{$destination_port_type} {$l_tdr_portin} {$destination_sector_name}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td colspan="2">
			<p><b>{$l_tdr_trade} {$l_tdr_start}</b>
		</td>
	</tr>

	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_start} {$source_commodity}: {$source_commodity_start}</b><br>
                	<b>{$l_tdr_start} {$destination_commodity}: {$source_commodity2_start}</b></td>
		<td width="50%" valign="top">
			<b>{$l_tdr_selling} {$destinationport_sell_item_type} {$destinationport_sell_commodity_amount} {$l_tdr_units} @ {$destinationport_sell_item_price} credits</b>
			</p>
			<p>
			{foreach key=key value=item from=$destinationport_buy_item_type}
				<b>{$l_tdr_buying} {$item} {$destinationport_buy_commodity_amount[$key]} {$l_tdr_units} @ {$destinationport_buy_item_price[$key]} {$l_tdr_credits}</b><br />
 			{/foreach}
			</p>
		</td>
              </tr>
            </table>
		</td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td colspan="2">
			<p><b>{$l_tdr_trade} {$l_tdr_finish}</b>
		</td>
	</tr>
	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_finish} {$source_commodity}: {$source_commodity_total}</b><br>
                	<b>{$l_tdr_finish} {$destination_commodity}: {$source_commodity2_total}</b></td>
		<td width="50%" valign="top">
			<b>{$l_tdr_selling} {$destinationport_sell_item_type} {$final_destination_sell_amount} {$l_tdr_units} @ {$final_destination_sell_price} {$l_tdr_credits}</b>
			</p>
			<p>
			{foreach key=key value=item from=$final_destination_buy_type}
				<b>{$l_tdr_buying} {$item} {$final_destination_buy_amount[$key]} {$l_tdr_units} @ {$final_destination_buy_price[$key]} {$l_tdr_credits}</b><br />
 			{/foreach}
			</p>
		</td>
              </tr>
            </table>
		</td>
	</tr>

	<tr bgcolor="#400040">
		<td colspan=2 align="center" valign="top">
			<table width="100%" border="0" cellspacing="3">
              <tr>
                <td width="50%"><b>{$l_tdr_runscompleted}: {$tr_repeat}</b></td>
                <td width="50%"><b><b>{$l_tdr_energy} {$l_tdr_scooped}: {$total_energy_scooped}</b></b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_turnsused}: {$total_turns_used}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_turnsleft}: {$turns_left}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$source_commodity} {$l_tdr_loaded}: {$source_commodity_loaded}</b></td>
                <td width="50%" valign="top">
					{foreach key=key value=item from=$commodity_total_sold}
						{if $commodity_total_sold[$key] > 0}
							<b>{$l_tdr_sold} {$key} {$commodity_total_sold[$key]} {$l_tdr_units}: {$commodity_total_credits_made[$key]} {$l_tdr_credits}</b><br />
						{/if}
 					{/foreach}				</td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$destination_commodity} {$l_tdr_dumped}: {$destination_commodity_dumped}</b></td>
                <td width="50%" valign="top">
					{foreach key=key value=item from=$commodity_total_bought}
						{if $commodity_total_bought[$key] > 0}
							<b>{$l_tdr_bought} {$key} {$commodity_total_bought[$key]} {$l_tdr_units}: {$commodity_total_credits_lost[$key]} {$l_tdr_credits}</b><br />
						{/if}
 					{/foreach}				</td>
              </tr>
              <tr>
                <td valign="top"><b>{$l_tdr_totalprofit}: 
                	{if $is_profit}
                		<font color="lime">{$total_profit}</font>
               		{else}
                		<font color="red">{$total_profit}</font>
           			{/if}</b></td>
                <td width="50%" valign="top">&nbsp;</td>
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

