<h1>{$title}</h1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
{if !$allow_navcomp}
$l_nav_nocomp<br><br>
{else}
	{if $state == 0}
		<form action="navcomp.php" method=post>
		{$l_nav_query} <input name=stop_sector>
		<input type=submit value={$l_submit}><br>
		<input name=state value=1 type=hidden>
		</form>
	{else}
		{if $found > 0}
			<h3>{$l_nav_pathfnd}</h3>
			{$start_sector} {$search_results_echo}<br>
			{$l_nav_answ1} {$search_depth} {$l_nav_answ2}<br><br>
		{else}
			{if $found == 0}
				{$l_nav_proper}<br><br>
			{else}
				({$sectorname}) : {$l_nav_notinlogs}<br><br>
			{/if}
		{/if}
	{/if}
{/if}

{if $found > 0}
	<form action='navcomp.php' enctype='multipart/form-data'>
	{$l_nav_autoroutename} <input type='text' name='name' value=''>
	<input type='hidden' name='state' value='create'>
	<input type='hidden' name='start_sector' value='{$start_sector}'>
	<input type='hidden' name='destination' value='{$destination}'>
	<input type='hidden' name='warp_list' value='{$warp_list}'>
	<input type='submit' value='{$l_autoroute_createroute}'>
	</form>
{/if}
</td></tr>
<tr><td colspan=3>{$l_autoroute_return} <a href='navcomp.php'>{$l_clickme}</a>.</td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

