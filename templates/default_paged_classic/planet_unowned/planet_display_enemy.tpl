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
<tr><td>{if $planetowner != 3}
			{$l_planet_scn} &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{$l_planet_att}<p></p>
		{/if}
		
		{if $novaavailible == 1}
			<a href="planet.php?planet_id={$planet_id}&command=nova">{$l_planet_firenova}</a><BR>
		{/if}

		{if $sofaavailible == 1} 
			<a href="planet.php?planet_id={$planet_id}&command=sofa">{$l_sofa}</a><BR>
		{/if}
		
		{if $enable_spies == 1}
			{if $numspies != 0}
				<BR><table border=1 cellspacing=1 cellpadding=2 width="100%">
				<TR BGCOLOR="#585980"><TD colspan=99 align=center><font color=white><B>{$l_spy_yourspies} </font> ({$numspies})
				{if $addaspy == 1}
					<a href="spy.php?command=send&planet_id={$planet_id}">{$l_spy_sendnew}</a>
				{/if}
				</B></TD></TR>
				<TR BGCOLOR="#23244F">
				<TD><B><A HREF="planet.php?planet_id={$planet_id}">{$ID}</A></B></TD>
				<TD><B><A HREF="planet.php?planet_id={$planet_id}&by=job_id">{$l_spy_job}</A></B></TD>
				<TD><B><A HREF="planet.php?planet_id={$planet_id}&by=move_type">{$l_spy_move}</A></B></TD>
				<TD><font color=white><B><a href="#">{$l_spy_action}</a></B></font></TD>
				<TD><font color=white><B><a href="#">{$l_spy_changebutton}</a></B></font></TD>
				</TR>
		
				{php}
				for($i = 0; $i < $numspies; $i++){
					echo "<TR BGCOLOR=" . $color[$i] ."><TD><font size=2 color=white>$spyid[$i]</font></TD><TD><font size=2 color=white>$job[$i]</font></TD><TD><font size=2 color=white>$spymove[$i]</font></TD><TD><font size=2><a href=spy.php?command=comeback&spy_id=$spyid[$i]&planet_id=$planet_id>$l_spy_comeback</a></font></TD><TD><font size=2><a href=spy.php?command=change&spy_id=$spyid[$i]&planet_id=$planet_id>$l_spy_changejob</a></font></TD></TR>";
				}
				{/php}
				</TABLE><BR>

				<BR><TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2 width="100%">
				<TR BGCOLOR="#585980"><TD>&nbsp;</TD><TD align="center"><B>{$l_base}</B></TD><TD align="center"><B>{$l_planetary_fighter}</B></TD><TD align="center"><B>{$l_planetary_sensors}</B></TD><TD align="center"><B>{$l_planetary_beams}</B></TD><TD align="center"><B>{$l_planetary_torp_launch}</B></TD><TD align="center"><B>{$l_planetary_shields}</B></TD><TD align="center"><B>{$l_planetary_jammer}</B></TD>
				<TD align="center"><B>{$l_planetary_cloak}</B></TD></TR>
				<TR BGCOLOR="#23244F"><TD>{$l_planetary_defense_levels}&nbsp;</TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetbased}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetfighter}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetsensors}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetbeams}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetlaunchers}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetshields}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetjammer}" SIZE=3 MAXLENGTH=3 ></TD>	  
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetcloak}" SIZE=3 MAXLENGTH=3 ></TD>
				</TR>
				</TABLE><BR>
				<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2 width="100%">
				<TR BGCOLOR="#585980"><TD>&nbsp;</TD><TD align="center"><B>{$l_planetary_SD_weapons}</B></TD><TD align="center"><B>{$l_planetary_SD_sensors}</B></TD><TD align="center"><B>{$l_planetary_SD_cloak}</B></TD></TR>
				<TR BGCOLOR="#23244F"><TD>{$l_planetary_defense_levels}&nbsp;</TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$sector_defense_weapons}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$sector_defense_sensors}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$sector_defense_cloak}" SIZE=3 MAXLENGTH=3 ></TD>
				</TR>
				</TABLE><br><BR>
				<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2>
				<TR BGCOLOR="#585980"><TD>&nbsp;</TD><TD align="center"><B>{$l_ore}</B></TD><TD align="center"><B>{$l_organics}</B></TD><TD align="center"><B>{$l_goods}</B></TD><TD align="center"><B>{$l_energy}</B></TD><TD align="center"><B>{$l_colonists}</B></TD><TD align="center"><B>{$l_credits}</B></TD><TD align="center"><B>{$l_fighters}</B></TD><TD align="center"><B>{$l_torps}</B></TD>
				</TR><TR BGCOLOR="#3A3B6E">
				<TD>{$l_current_qty}</TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetore}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetorganics}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetgoods}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetenergy}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetcolonists}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetcredits}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planetfighters}" SIZE=14 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$planettorps}" SIZE=14 ></TD>
				</TR>
				<TR BGCOLOR="#23244F"><TD>{$l_planet_perc}</TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$prodore}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$prodorganics}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$prodgoods}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$prodenergy}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center">{$na}</TD><TD align="center">*</TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$prodfighters}" SIZE=3 MAXLENGTH=3 ></TD>
				<TD align="center"><INPUT TYPE=TEXT VALUE="{$prodtorp}" SIZE=3 MAXLENGTH=3 ></TD>
				</TABLE>{$l_planet_interest}<BR><BR>
			{else}
				{if $planetowner != 3}
					{$l_spy_nospieshere}. 
					<a href="spy.php?command=send&planet_id={$planet_id}">{$l_spy_sendnew}</a><BR>
				{/if}
			{/if}  
		{/if}  

		<BR><a href="planet.php?planet_id={$planet_id}">{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>

		{if $allow_ibank == 1}
			{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
		{/if}

		<A HREF ="bounty.php">{$l_by_placebounty}</A><p>
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
