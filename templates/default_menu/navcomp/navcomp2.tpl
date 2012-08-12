<h1>{$title}</h1>
<table width="90%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
		<table border=1 cellspacing=1 cellpadding=2 width="100%">
		<TR BGCOLOR="#000000"><TD colspan=5 align=center><font color=white><B>{$l_autoroute_title}</B></font></TD></TR>
		<TR BGCOLOR="#000000">
		<TD align='center'><B><font size=2 color='#79f487'>{$l_autoroute_id}</font></B></TD>
		<TD align='center'><B><font size=2 color='#79f487'>{$l_autoroute_start}</font></B></TD>
		<TD align='center'><B><font size=2 color='#79f487'>{$l_autoroute_destination}</font></B></TD>
		<TD align='center' width="40%"><B><font size=2 color='#79f487'>{$l_autoroute_warps}</font></B></TD>
		<TD align='center'><B><font size=2 color='#79f487'>{$l_autoroute_deleteroute}</font></B></TD>
		</TR>
		
	{if $autocount != 0}
{php}
		for($i = 0; $i < $autocount; $i++){
			echo "<TR BGCOLOR=" . $autolinecolor[$i] .">";
			echo "<TD align='center'><font size=2 color='#87d8ec'><b>";
			echo "<form action='navcomp.php' enctype='multipart/form-data'>"; 
			echo "<input size='10' maxlength='30' type='text' name='name' value='" . (($autoname[$i] == "" || empty($autoname[$i])) ? $autorouteid[$i] : $autoname[$i]) . "'>";
			echo "<input type='hidden' name='state' value='editname'>";
			echo "<input type='hidden' name='autoroute_id' value='" . $autorouteid[$i] . "'>";
			echo "<input type='submit' value='" . $l_autoroute_editname . "'>";
			echo "</form>";
			
			echo "</b></font></TD>\n";
			echo "<TD align='center'><font size=2 color=yellow>{$l_nav_warp_from} <a href=navcomp.php?state=start&autoroute_id=$autorouteid[$i]&warponly=1>$autostart[$i]</a><br>
				<font size=2 color=yellow>{$l_nav_rs_from} <a href=navcomp.php?state=start&autoroute_id=$autorouteid[$i]>$autostart[$i]</a></font></TD>\n";
			echo "<TD align='center'><font size=2 color=yellow>{$l_nav_warp_from} <a href=navcomp.php?state=reverse&autoroute_id=$autorouteid[$i]&warponly=1>$autoend[$i]</a><br>
				<font size=2 color=yellow>{$l_nav_rs_from} <a href=navcomp.php?state=reverse&autoroute_id=$autorouteid[$i]>$autoend[$i]</a></font></TD>\n";
			echo "<TD align='center' width='40%'><font size=2 color=yellow>$warplist[$i]</font></TD>\n";
			echo "<td align='center'><a href=\"navcomp.php?state=dismiss&delete_id=$autorouteid[$i]\">$l_autoroute_deleteroute</a></td></TR>\n";
		}
{/php}
	{else}
		<tr BGCOLOR="#3A3B6E"><TD colspan="5" align='center'><B><font size=2 color='#79f487'><br>{$l_autoroute_noroutes}</font></b><br><br>
		</td></tr>
	{/if}
		<TR BGCOLOR="#000000">
		<TD colspan=5 align=center><font color=white size=2><B>{$l_autoroute_info}</B></font></td></tr>
		<TR BGCOLOR="#000000">
		</TABLE><BR><BR>
	</td></tr>


<tr><td>
{if $state == 0}
	<table border=0 cellspacing=1 cellpadding=2 width="100%">
		<tr><td width="50%">
			<form action="navcomp.php" method=post>
			{$l_nav_query} <input name="stop_sector" {if !$allow_navcomp}disabled{/if}>
			<input type=submit value={$l_submit} {if !$allow_navcomp}disabled{/if}><br>
			<input name=state value=1 type=hidden>
			</form>
		</td><td width="50%">
			<div align="center" ><b>{$l_nav_warplinksleaving}</b></div>
			<hr><br>
<span id="output">
{foreach key=key value=item from=$resultlist}
	{if $resultvisitedlist[$key] == 0}
		<a href="#" onclick="target_sector='{$resultlist[$key]}'; makeRequest();">{$resultlist[$key]}</a><br><br>
	{else}
		{$resultlist[$key]}<br><br> 
	{/if}
{/foreach}
</span>
<br>
			<div align="center" ><b>{$l_nav_manuallist}</b></div>
			<hr><br>

<span id="output2">None</span>
<br>
<br>
	<form id="manualroute" action='navcomp.php' enctype='multipart/form-data'>
	{$l_nav_autoroutename} <input type='text' name='name' value=''>
	<input type='hidden' name='state' value='create'>
	<input type='hidden' name='start_sector' value='{$start_sector}'>
	<input type='hidden' name='destination' id="destination" value=''>
	<input type='hidden' name='warp_list' id='warp_list' value=''><br>
	<br><br>
	<input onclick='populate();'  type='submit' value='{$l_autoroute_createroute}'>
	</form>
		</td></tr>
	</table>
{else}
	<table border=0 cellspacing=1 cellpadding=2 width="100%">
	{if $found > 0}
		<tr><td colspan=3><h3>{$l_nav_pathfnd}</h3>
		{$start_sector} {$search_results_echo}<br>
		{$l_nav_answ1} {$search_depth} {$l_nav_answ2}<br><br></td></tr>
	{else}
		<tr><td colspan=3>{$l_nav_proper}<br><br></td></tr>
	{/if}
	</table>
{/if}


<tr><td colspan=3>{$l_autoroute_return} <a href='navcomp.php'>{$l_clickme}</a>.</td></tr>
</td>
				<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

{literal}
<script type="text/javascript">
<!--
var xmlDoc = null ;
var target_sector = '' ;
var start_sector = '' ;
var warplist_stored = '' ;
var warplist_last = '' ;
var returndata = '' ;

function populate()
{
	document.getElementById('destination').value = target_sector
	if(target_sector == warplist_stored)
	{
		document.getElementById('warp_list').value = ''
	}
	else
	{
		document.getElementById('warp_list').value = warplist_last
	}
}


function clearvariables()
{
	target_sector = '' ;
	start_sector = '' ;
	warplist_stored = '' ;
	warplist_last = '' ;
	returndata = '' ;
}

function makeRequest()
{
	if ( xmlDoc == null )
	{
		if (typeof window.ActiveXObject != 'undefined' ) {
			var XMLHTTP_IDS = new Array('MSXML2.XMLHTTP.5.0',
				 'MSXML2.XMLHTTP.4.0',
				 'MSXML2.XMLHTTP.3.0',
				 'MSXML2.XMLHTTP',
				 'Microsoft.XMLHTTP');
			var success = false;
			for (var i=0;i < XMLHTTP_IDS.length && !success; i++)
			{
				try
				{
					xmlDoc = new ActiveXObject
					(XMLHTTP_IDS[i]);
					success = true;
				}
				catch (e)
				{}
			}
		}
		else
		{
			xmlDoc = new XMLHttpRequest();
		}
	}
	
	warplist_last = warplist_stored;
	
	xmlDoc.onreadystatechange = process;
	xmlDoc.open( "GET", "{/literal}{$full_url}{literal}ajax_processor.php?command=navcomp_findlinks&target_sector=" + target_sector + "&warplist=" + warplist_stored, true );
	xmlDoc.send( null );
}

function process() {
	if ( xmlDoc.readyState != 4 )
	{
		return ;
	}
	returndata = xmlDoc.responseText
	var sectorlist=returndata.split('|');
	var returnmessage = '';
//	document.write(returndata)
	if(warplist_stored != '')
	{
		warplist_stored = warplist_stored + '|' + target_sector;
	}
	else
	{
		warplist_stored = warplist_stored + target_sector;
		start_sector = target_sector;
	}
	
	if(sectorlist.length == 1)
	{
		returnmessage = '[' + target_sector + '] {/literal}{$l_nav_nowarplinksleaving}{literal}'
	}
	else
	{
		for (var x = 0; x < sectorlist.length - 1; x++)
		{
			var sectorname = sectorlist[x];
			var visitedsector=sectorname.split('`');
			if(visitedsector.length > 1)
			{
				returnmessage = returnmessage + visitedsector[1] + '{/literal} : {$l_nav_notinlogs}{literal}<br><br>'
			}
			else
			{
				returnmessage = returnmessage + '<a href="#" onclick="target_sector=\'' + sectorname + '\'; makeRequest();">' + sectorname + '</a><br><br>'
			}
		}
	}

	document.getElementById('output').innerHTML = returnmessage;
	document.getElementById('output2').innerHTML = warplist_stored.replace(/\|/g, " >> ");
}

clearvariables();


//-->
</script>
{/literal}

