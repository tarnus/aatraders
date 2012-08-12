<h1>{$title}</h1>

{literal}
	<style type="text/css">
		.border {
			border-collapse: collapse; 
			border: 1px solid #ccc; 
		}
		.yellow { color: yellow; }
		.white { color: white; }
	</style>
{/literal}
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>

{if $command == "send"}
	{if $executecommand}
		{$bountystatus}<BR><BR>

		<B>{$l_spy_sendtitle}</B><BR>
		<FORM ACTION=spy.php METHOD=POST>
		<INPUT TYPE=hidden name=command value=send>
		<INPUT TYPE=hidden name=doit value=1>
		<INPUT TYPE=hidden name=planet_id value={$planet_id}>
		<INPUT TYPE=RADIO NAME=mode VALUE=none>{$l_spy_type1}<BR>
		<INPUT TYPE=RADIO NAME=mode VALUE=toship CHECKED>{$l_spy_type2}<BR>
		<INPUT TYPE=RADIO NAME=mode VALUE=toplanet>{$l_spy_type3}<BR><BR>
		
		{$l_spy_trytitle}:<BR>
		{foreach key=key value=item from=$job_name}
			{if $jobid == $key}
				<INPUT TYPE="radio" name="jobid" value="{$key}" CHECKED> {$job_name[$key]} - {$description[$key]}<br>
			{else}
				<INPUT TYPE="radio" name="jobid" value="{$key}"> {$job_name[$key]} - {$description[$key]}<br>
			{/if}
		{/foreach}
			<br>
		<INPUT TYPE=submit value="{$l_spy_sendbutton}">
		</FORM>
	{else}
		{$playerbounty}<br><br>
		{$sendstatus}<br><br>
	{/if}   
	<a href=planet.php?planet_id={$planet_id}>{$l_clickme}</a> {$l_toplanetmenu}
	<a href=spy.php>{$l_clickme}</a> {$l_spy_menu}
{/if}

{if $command == "comeback"}
	{if $planetspies}
		{if $executecommand}
			<table border="0" cellpadding="2" cellspacing="0" width="100%" class="border">
			<tr><td colspan="4" align="center"><B>{$l_spy_confirm}</B><BR>
			<BR></TD>
			</TR>
			<TR BGCOLOR="#000000">
			<TD><font color=white><B>{$l_spy_codenumber}</B></font></TD>
			<TD><font color=white><B>{$l_spy_job}</B></font></TD>
			<TD><font color=white><B>{$l_spy_move}</B></font></TD>
			<TD><font color=white><B>{$l_spy_action}</B></font></TD>
			</TR>
	  
			<TR BGCOLOR="#000000">
			<TD><font size=2 color=white>{$spyid}</font></TD>
			<TD><font size=2 color=white>{$job}</font></TD>
			<TD><font size=2><a href=spy.php?command=change&spy_id={$spyid}&planet_id={$planet_id}>{$move}</a></font></TD>
			<TD><font size=2><a href=spy.php?command=comeback&spy_id={$spyid}&planet_id={$planet_id}&doit=1>{$l_yes}</a><BR><a href=planet.php?planet_id={$planet_id}>{$l_no}</a></font></TD>
			</TR></TABLE><BR>
		{else}
			{$l_spy_backonship}<BR>
		{/if}
	{else}
		{$l_spy_backfailed}<BR><BR>
	{/if}
	
	<a href=planet.php?planet_id={$planet_id}>{$l_clickme}</a> {$l_toplanetmenu}<br><br>

	<a href=spy.php>{$l_clickme}</a> {$l_spy_menu}
{/if}

{if $command == "change"}
	{if $spycount}
		{if $executecommand}
			<B>{$l_spy_changetitle}</B><BR>
			<FORM ACTION=spy.php METHOD=POST>
			<INPUT TYPE=hidden name=command value=change>
			<INPUT TYPE=hidden name=doit value=1>
			<INPUT TYPE=hidden name=spy_id value={$spy_id}>
			<INPUT TYPE=hidden name=planet_id value={$planet_id}>
			<INPUT TYPE=RADIO NAME=mode VALUE=none {$set_1}> {$l_spy_type1}<BR>
			<INPUT TYPE=RADIO NAME=mode VALUE=toship {$set_2}> {$l_spy_type2}<BR>
			<INPUT TYPE=RADIO NAME=mode VALUE=toplanet {$set_3}> {$l_spy_type3}<BR><BR>
	  
			{$l_spy_trytitle}:<BR>
		{foreach key=key value=item from=$job_name}
			{if $jobid == $key}
				<INPUT TYPE="radio" name="jobid" value="{$key}" CHECKED> {$job_name[$key]} - {$description[$key]}<br>
			{else}
				<INPUT TYPE="radio" name="jobid" value="{$key}"> {$job_name[$key]} - {$description[$key]}<br>
			{/if}
		{/foreach}
			<br>
			<INPUT TYPE=submit value="{$l_spy_changebutton}">
			</FORM>
			{if $planet_id != -1}
				<a href=planet.php?planet_id={$planet_id}>{$l_clickme}</a> {$l_toplanetmenu}
			{/if}
		{else}
			{$spystatus}<BR>
	  
			{if $planet_id != -1}
				<a href=planet.php?planet_id={$planet_id}>{$l_clickme}</a> {$l_toplanetmenu}
			{/if}
		{/if}
	{else}
		{$l_spy_changefailed}<br>
	{/if}

	<a href=spy.php>{$l_clickme}</a> {$l_spy_menu}
{/if}

{if $command == "cleanup_planet"}
  <B>{$l_spy_cleanupplanettitle}</B><BR>
  {if $executecommand} 
	<FORM ACTION=spy.php METHOD=POST>
	<INPUT TYPE=hidden name=command value=cleanup_planet>
	<INPUT TYPE=hidden name=planet_id value={$planet_id}>
	<INPUT TYPE=hidden name=doit value=1>
	<INPUT TYPE=RADIO NAME=type VALUE=1 {$set1}> {$l_spy_cleanuptext1}<BR>
	<INPUT TYPE=RADIO NAME=type VALUE=2 {$set2}> {$l_spy_cleanuptext2}<BR>
	<INPUT TYPE=RADIO NAME=type VALUE=3 {$set3}> {$l_spy_cleanuptext3}<BR><BR>
	
	{if $disabled}
		{$cleanupstatus}
	{else}
		<INPUT TYPE=submit value="{$cleanupstatus}">
	{/if}
	
	</FORM>
  {else}
	<B>{$l_spy_cleanupplanettitle2}</B><BR>

	{if $disabled != "DISABLED"}
		{php}
	  	for($i = 0; $i < $spycount; $i++)
		{
			echo "$spyinfo[$i]<BR>";
		}
   		{/php}
		
	  {if !$found}
		{$l_spy_spynotfoundonplanet}<BR>
	  {/if}
	{else}
		<BR>{$l_spy_notenough}<BR>
	{/if}
  {/if}
  <BR><a href=planet.php?planet_id={$planet_id}>{$l_clickme}</a> {$l_toplanetmenu}<BR><br>
	<a href=spy.php>{$l_clickme}</a> {$l_spy_menu}
{/if}

{if $command == "cleanup_ship"}
  <B>{$l_spy_cleanupshiptitle}</B><BR>
  {if $executecommand} 
	<FORM ACTION=spy.php METHOD=POST>
	<INPUT TYPE=hidden name=command value=cleanup_ship>
	<INPUT TYPE=hidden name=doit value=1>
	<INPUT TYPE=RADIO NAME=type VALUE=1 {$set1}> {$l_spy_cleanupshiptext1}<BR>
	<INPUT TYPE=RADIO NAME=type VALUE=2 {$set2}> {$l_spy_cleanupshiptext2}<BR>
	<INPUT TYPE=RADIO NAME=type VALUE=3 {$set3}> {$l_spy_cleanupshiptext3}<BR><BR>
	
	{if $disabled}
		{$cleanupstatus}
	{else}
		<INPUT TYPE=submit value="{$cleanupstatus}">
	{/if}
	
	</FORM>
  {else}
	<B>{$l_spy_cleanupshiptitle2}</B><BR>

	{if $disabled != "DISABLED"}
		{php}
	  	for($i = 0; $i < $spycount; $i++)
		{
			echo "$spyinfo[$i]<BR>";
		}
   		{/php}
		
	  {if !$found}
		{$l_spy_spynotfoundonship}<BR>
	  {/if}
	{else}
		<BR>{$l_spy_notenough}<BR>
	{/if}
  {/if}
	<a href=spy.php>{$l_clickme}</a> {$l_spy_menu}
{/if}

{if $command == "detect"}
	{if !$isinfoid}
		{if $infocount}
			<font color=red size='4'>{$l_spy_infodeleted}<BR><BR></font>
		{else}
			<B>{$l_spy_infonotyours}</B><BR><BR>
		{/if}
	{/if}

	{if !$isinfoidall}
		<font color=red size='4'>{$l_spy_messagesdeleted}<br><br></font>
	{/if}
	
	<br>
	<table border="0" cellpadding="2" cellspacing="0" width="100%" class="border">
		<tr>
			<td bgcolor="#585980" colspan="4" align=center><font color=white><b>{$l_spy_infotitle}</b></font></td>
		</tr>
		<tr>
			<td bgcolor="#23244F"><b><a href="spy.php?command=detect">{$l_spy_time}</a></b></td>
			<td bgcolor="#23244F"><b><a href="spy.php?command=detect&by=type">{$l_spy_type}</a></b></td>
			<td bgcolor="#23244F"><b><a href="spy.php?command=detect&by=data">{$l_spy_info}</a></b></td>
			<td bgcolor="#23244F" align="right"><b><a href="spy.php?command=detect&info_id_all=1">{$l_spy_deleteall}</a></b></td>
		</tr>
		{php}
		$line_color = "#23244F";
		for($i = 0; $i < $detectcount; $i++)
		{
			if($line_color == "#3A3B6E")   
				$line_color = "#23244F"; 
			else
				$line_color = "#3A3B6E"; 

			echo "<tr><td bgcolor=" . $line_color . "class=\"white\">$det_time[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\">$datatype[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\">$datainfo[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\" align=\"right\">
						<a href=\"spy.php?command=detect&info_id=$det_id[$i]&by=$by\">$l_spy_delete</a></td>
					</tr>";
		}
		{/php}
  </table>&nbsp;<br>
	<a href=spy.php>{$l_clickme}</a> {$l_spy_menu}
{/if}

{if $command == ""}

  <a href=spy.php?command=detect>{$l_clickme}</a> {$l_spy_messages}<BR><BR>
  
	{if $spycount}
		<table border="0" cellpadding="0" cellspacing="0" width="100%" class="border">
			<tr>
				<td bgcolor="#585980"><font color=white><b>&nbsp;
					{if $shipspycount}
						{$l_spy_defaulttitle4}: <span class="yellow">{$shipspytotal}</span>
					{else} 
						{$l_spy_no4} 
					{/if}
					</b></font>
				</td>
			</tr>
		</table>
		&nbsp;<br>
		{if $enemyshipspycount}
			<table border="0" cellpadding="2" cellspacing="0" width="100%" class="border">
				<tr>
					<td bgcolor="#585980" colspan=6 align=center><font color=white><b>{$l_spy_defaulttitle1}</b></font></td>
				</tr>
				<tr>
					<td bgcolor="#23244F"><b><a href="spy.php?by2={$by2}&by3={$by3}">{$l_spy_codenumber}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by1=character_name&by2={$by2}&by3={$by3}">{$l_spy_shipowner}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by1=ship_name&by2={$by2}&by3={$by3}">{$l_spy_shipname}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by1=ship_type&by2={$by2}&by3={$by3}">{$l_spy_shiptype}</a></b></td>
					<td bgcolor="#23244F"><span class="white"><b>{$l_spy_shiplocation}</b></span></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by1=move_type&by2={$by2}&by3={$by3}">{$l_spy_move}</a></b></td>
				</tr>
			{php}
			for ($i = 0; $i < $enemyshipcount; $i++)
			{
				if($line_color == "#3A3B6E")   
					$line_color = "#23244F"; 
				else
					$line_color = "#3A3B6E"; 
				echo "<tr>
					<td bgcolor=" . $line_color . " class=\"white\">$spy_id[$i]</td>
					<td bgcolor=" . $line_color . " class=\"white\">$playername[$i]</td>
					<td bgcolor=" . $line_color . " class=\"white\"><a href=report.php?sid=$shipid[$i]>$shipname[$i]</a></td>
					<td bgcolor=" . $line_color . " class=\"white\">$shipclass[$i]</td>
					<td bgcolor=" . $line_color . " class=\"white\">$spysector[$i]</td>
					<td bgcolor=" . $line_color . " class=\"white\"><a href=spy.php?command=change&spy_id=$spy_id[$i]>$movetype[$i]</a></td>
				</tr>";
			}
			{/php}
			</table>&nbsp;<br>
		{else}
			<b>{$l_spy_no1}</b><br><br>
		{/if}

		{if $planetspycount}
			<table border="0" cellpadding="2" cellspacing="0" width="100%" class="border">
				<tr>
					<td bgcolor="#585980" colspan=7 align=center><font color=white><b>{$l_spy_defaulttitle2}</b></font></td>
				</tr>
				<tr>
					<td bgcolor="#23244F"><b><a href="spy.php?by2=id&by1={$by1}&by3={$by3}">{$l_spy_codenumber}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by2=owner&by1={$by1}&by3={$by3}">{$l_spy_planetowner}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by1={$by1}&by3={$by3}">{$l_spy_planetname}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by2=sector&by1={$by1}&by3={$by3}">{$l_spy_sector}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by2=job_id&by1={$by1}&by3={$by3}">{$l_spy_job}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by2=move_type&by1={$by1}&by3={$by3}">{$l_spy_move}</a></b></td>
					<td bgcolor="#23244F"><b><a href="#">{$l_spy_changebutton}</a></b></td>
				</tr>
			{php}
			for ($i = 0; $i < $enemyplanetcount; $i++)
			{
				if($line_color == "#3A3B6E")   
					$line_color = "#23244F"; 
				else
					$line_color = "#3A3B6E"; 
				echo "<tr>
						<td bgcolor=" . $line_color . " class=\"white\">$pspy_id[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\">$pplayername[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\">$pname[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\"><a href=\"main.php?move_method=real&engage=1&destination=$psector[$i]\">$psector[$i]</a></td>
						<td bgcolor=" . $line_color . " class=\"white\">$pjob[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\">$pmovetype[$i]</td>
						<td bgcolor=" . $line_color . " class=\"white\"><a href=\"spy.php?command=change&spy_id=$pspy_id[$i]\">$l_spy_changejob</a></td>
				</tr>";
			}
			{/php}
		  </table>&nbsp;<br>
		{else}
			<B>{$l_spy_no2}</B><BR><BR>
		{/if}

		{if $myplanetspycount}
			<table border="0" cellpadding="2" cellspacing="0" width="100%" class="border">
				<tr>
					<td bgcolor="#585980" colspan=3 align=center><font color=white><b>{$l_spy_defaulttitle3}</b></font></td>
				</tr>
				<tr>
					<td bgcolor="#23244F"><b><a href="spy.php?by3=sector">{$l_spy_sector}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by3=plnname">{$l_spy_planetname}</a></b></td>
					<td bgcolor="#23244F"><b><a href="spy.php?by3=spycnt">{$l_spy_onplanet}</a></b></td>
				</tr>
			{php}
			for ($i = 0; $i < $ownplanetspycount; $i++)
			{
				if($line_color == "#3A3B6E")   
					$line_color = "#23244F"; 
				else
					$line_color = "#3A3B6E"; 
				echo "<tr>
					<td bgcolor=" . $line_color . " class=\"white\"><a href=\"main.php?move_method=real&engage=1&destination=$mpsector[$i]\">$mpsector[$i]</a></td>
					<td bgcolor=" . $line_color . " class=\"white\">$mpname[$i]</td>
					<td bgcolor=" . $line_color . " class=\"white\"><b>$mpcount[$i]</b></td>
				</tr>";
			}
			{/php}
		 	</table>&nbsp;<BR>
		{else}
		  <B>{$l_spy_no3}</B><BR><BR>
		{/if}
	{else}
		{$l_spy_nospiesatall}<BR>
	{/if}
{/if}


</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
