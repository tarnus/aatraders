<h1>{$title}</h1>

<table border=1 cellspacing=1 cellpadding=2 width="720" align=center bgcolor="#000000">
	<tr bgcolor="#400040">
		<td align="center" colspan=2><b>{$l_tdr_tdrres}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td width="50%"><b>{$source_port_type} {$l_tdr_portin} {$source_sector_name}</b></td>
		<td width="50%"><b>{$destination_port_type} {$l_tdr_portin} {$destination_sector_name}</b></td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td width="50%" valign="top">
			<p><b>{$l_tdr_trade} {$l_tdr_start}</b><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="4" alt="px" />
			<img src="templates/{$templatename}images/white_dot.gif" width="50%" height="1" alt="px" /><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="7" alt="px" />
			<b>{$l_tdr_selling} {$sourceport_sell_item_type} {$sourceport_sell_commodity_amount} {$l_tdr_units} @ {$sourceport_sell_item_price} {$l_tdr_credits}</b>
			</p>
			<p>
			{foreach key=key value=item from=$sourceport_buy_item_type}
				<b>{$l_tdr_buying} {$item} {$sourceport_buy_commodity_amount[$key]} {$l_tdr_units} @ {$sourceport_buy_item_price[$key]} {$l_tdr_credits}</b><br />
 			{/foreach}
			</p>
		</td>
		<td width="50%" valign="top">
			<p><b>{$l_tdr_trade} {$l_tdr_start}</b><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="4" alt="px" />
			<img src="templates/{$templatename}images/white_dot.gif" width="50%" height="1" alt="px" /><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="7" alt="px" />
			<b>{$l_tdr_selling} {$destinationport_sell_item_type} {$destinationport_sell_commodity_amount} {$l_tdr_units} @ {$destinationport_sell_item_price} credits</b>
			</p>
			<p>
			{foreach key=key value=item from=$destinationport_buy_item_type}
				<b>{$l_tdr_buying} {$item} {$destinationport_buy_commodity_amount[$key]} {$l_tdr_units} @ {$destinationport_buy_item_price[$key]} {$l_tdr_credits}</b><br />
 			{/foreach}
			</p>
		</td>
	</tr>
	<tr align=center bgcolor="#400040">
		<td width="50%" valign="top">
			<p><b>{$l_tdr_trade} {$l_tdr_finish}</b><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="4" alt="px" />
			<img src="templates/{$templatename}images/white_dot.gif" width="50%" height="1" alt="px" /><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="7" alt="px" />
			<b>{$l_tdr_selling} {$sourceport_sell_item_type} {$final_source_sell_amount} {$l_tdr_units} @ {$final_source_sell_price} {$l_tdr_credits}</b>
			</p>
			<p>
			{foreach key=key value=item from=$final_source_buy_type}
				<b>{$l_tdr_buying} {$item} {$final_source_buy_amount[$key]} {$l_tdr_units} @ {$final_source_buy_price[$key]} {$l_tdr_credits}</b><br />
 			{/foreach}
			</p>
		</td>
		<td width="50%" valign="top">
			<p><b>{$l_tdr_trade} {$l_tdr_finish}</b><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="4" alt="px" />
			<img src="templates/{$templatename}images/white_dot.gif" width="50%" height="1" alt="px" /><br>
			<img src="templates/{$templatename}images/spacer.gif" width="100%" height="7" alt="px" />
			<b>{$l_tdr_selling} {$destinationport_sell_item_type} {$final_destination_sell_amount} {$l_tdr_units} @ {$final_destination_sell_price} {$l_tdr_credits}</b>
			</p>
			<p>
			{foreach key=key value=item from=$final_destination_buy_type}
				<b>{$l_tdr_buying} {$item} {$final_destination_buy_amount[$key]} {$l_tdr_units} @ {$final_destination_buy_price[$key]} {$l_tdr_credits}</b><br />
 			{/foreach}
			</p>
		</td>
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
                <td width="50%"><b>{$l_tdr_energy} {$l_tdr_scooped}: {$total_energy_scooped}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b>{$l_tdr_turnsused}: {$total_turns_used}</b></td>
                <td width="50%" valign="top"><b>{$l_tdr_turnsleft}: {$turns_left}</b></td>
              </tr>
              <tr>
                <td width="50%" valign="top">
					{foreach key=key value=item from=$commodity_total_sold}
						{if $commodity_total_sold[$key] > 0}
							<b>{$l_tdr_sold} {$key} {$commodity_total_sold[$key]} {$l_tdr_units}: {$commodity_total_credits_made[$key]} {$l_tdr_credits}</b><br />
						{/if}
 					{/foreach}				</td>
                <td width="50%" valign="top">
					{foreach key=key value=item from=$commodity_total_bought}
						{if $commodity_total_bought[$key] > 0}
							<b>{$l_tdr_bought} {$key} {$commodity_total_bought[$key]} {$l_tdr_units}: {$commodity_total_credits_lost[$key]} {$l_tdr_credits}</b><br />
						{/if}
 					{/foreach}				</td>
              </tr>
              <tr>
                <td width="50%" valign="top"><b><font color="green">{$l_tdr_totalprofit}</font>: {$total_credits_made}</b></td>
                <td width="50%" valign="top"><b><font color="red">{$l_tdr_totalcost}</font>: {$total_credits_lost}</b></td>
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

