{literal}
<style type="text/css">
<!--
.topbar {
	font-family: Tahoma, Verdana, Arial, Helvetica, sans-serif;
	font-size: 9px;
	font-style: normal;
	font-weight: bold;
	text-align: center;
	color: #FFFFFF;
}
.shipbody {
	font-family: Tahoma, Verdana, Arial, Helvetica, sans-serif;
	font-size: 10px;
	font-style: normal;
	font-weight: normal;
	color: #ffffff;
	text-align: center;
}

.dropdown {
	font-family: Tahoma, Verdana, Arial, Helvetica, sans-serif;
	font-size: 10px;
	font-style: normal;
	font-weight: normal;
	color: #000000;
	text-align: center;
}

body {
	background-color: #000000;
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
}
body,td,th {
	font-family: Tahoma, Verdana, Arial, Helvetica, sans-serif;
	font-size: 9px;
}
-->
</style>

<script language="Javascript" type="text/javascript">

function reload1(){
document.ThisForm.offset.value=0;
 document.ThisForm.submit();
}
function reload(){
 document.ThisForm.submit();
}
function loggingchange(){
 document.ThisForm.logging1.value=document.ThisForm.logging.options[document.ThisForm.logging.selectedIndex].value;
 document.ThisForm.submit();
}
function loggingchangeb(){
 document.ThisForm.logging1.value=document.ThisForm.logginga.options[document.ThisForm.logginga.selectedIndex].value;
 document.ThisForm.submit();
}
function prev(){
if (document.ThisForm.offset.value >= '150')
{
 document.ThisForm.offset.value=Math.ceil(document.ThisForm.offset.value) - 150;
}
 document.ThisForm.submit();
}
function next(){
if (document.ThisForm.offset.value < {/literal}{$log_total}{literal})
{
 document.ThisForm.offset.value=Math.ceil(document.ThisForm.offset.value) + 150;
}
 document.ThisForm.submit();
}

function page(){
 document.ThisForm.offset.value=document.ThisForm.pagenum.options[document.ThisForm.pagenum.selectedIndex].value;
 document.ThisForm.submit();
}
</script>
{/literal}
{php}
function strip_places($itemin){

$places = explode(",", $itemin);
if (count($places) <= 1){
	return $itemin;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	$placecount=count($places);

	switch ($placecount){
		case 2:
			return "$places[0].$places[1] K";
			break;
		case 3:
			return "$places[0].$places[1] M";
			break;	
		case 4:
			return "$places[0].$places[1] B";
			break;	
		case 5:
			return "$places[0].$places[1] T";
			break;
		case 6:
			return "$places[0].$places[1] Qd";
			break;		
		case 7:
			return "$places[0].$places[1] Qn";
			break;
		case 8:
			return "$places[0].$places[1] Sx";
			break;
		case 9:
			return "$places[0].$places[1] Sp";
			break;
		case 10:
			return "$places[0].$places[1] Oc";
			break;
		}		
	
}

}
{/php}
<input type="Hidden" name="logging1" value="0">
<input type="Hidden" name="offset" value="{$offset}"> 
<br><strong>Player Info</strong>
<table width="100%"  border="1" cellspacing="0" cellpadding="2" >
  <tr class="topbar" bgcolor="#000066">
    <td>Player Name <a href="/log.php?player={$player_id}&md5admin_password={$md5admin_password}&game_number={$game_number}" target="_blank">View Log</a></td>
    <td>IP Address </td>
    <td>Last Login </td>
    <td>Score</td>
    <td>Turns</td>
    <td>Turns Used </td>
    <td>Fed Bounty </td>
    <td>IGB Credits </td>
    <td>Loan Amt</td>
    <td>Loan Date </td>
    <td>Credits</td>
  </tr>
  <tr bgcolor="#6666FF" class="shipbody">
    <td class="shipbody"><select name="user" style="text-align:left;" onchange="reload1();">
	  {for value=i start=0 stop=$player_tot step=1}
		{if $player_id==$list_player_id[$i]}
		<option value="{$list_player_id[$i]}" selected>{if  $list_admin_extended_logging[$i]==1}*{/if}{$list_character_name[$i]} {$online[i]}</option>
		{else}
		<option value="{$list_player_id[$i]}" >{if  $list_admin_extended_logging[$i]==1}*{/if}{$list_character_name[$i]}{$online[$i]}</option>
		{/if}  
	  {/for}
	
	</select>
	{if $extras!=""}
	<hr>{$extras}
	{/if}
	</td>
    <td class="shipbody">{$ip_address}</td>
    <td class="shipbody">{$last_login}</td>
    <td class="shipbody">{php}echo strip_places($score);{/php}</td>
    <td class="shipbody">{$turns}</td>
    <td class="shipbody">{$turns_used}</td>
    <td class="shipbody">{$fedtot}/{if $fedtot!=0}{php}echo strip_places($fedtotamt);{/php}{else}0{/if}</td>
    <td class="shipbody">{php}echo strip_places($balance);{/php}</td>
    <td class="shipbody">{php}echo strip_places($loan);{/php}</td>
    <td class="shipbody">{$loantime}</td>
    <td class="shipbody">{php}echo strip_places($credits);{/php}</td>
  </tr>
</table>
<table width="100%"  border="1" cellspacing="0" cellpadding="2" >
  <tr class="topbar" bgcolor="#000066">
    <td>Team</td>
    <td>Current Sector </td>
    <td>On Planet </td>
    <td>Kills</td>
    <td>Deaths</td>
    <td>Captures</td>
    <td>Planets Built </td>
    <td>Planets Lost </td>
    <td>Experience</td>
    <td>Rating</td>
	<td>Tot Planets</td>
	<td>Tot Planet<br> Credits</td>
    <td>Extend<br>
	 Logging
    </td>
  </tr>
  <tr bgcolor="#6666FF" class="shipbody">
    <td class="shipbody">{$team_name}</td>
    <td class="shipbody">{$sector_id}</td>
    <td class="shipbody">{$on_planet}</td>
    <td class="shipbody">{$kills}</td>
    <td class="shipbody">{$deaths}</td>
    <td class="shipbody">{$captures}</td>
    <td class="shipbody">{$planets_built}</td>
    <td class="shipbody">{$planets_lost}</td>
    <td class="shipbody">{php}echo strip_places($experience);{/php}</td>
    <td class="shipbody">{php}echo strip_places($rating);{/php}</td>
	<td class="shipbody">{$tot_planets}</td>
	<td class="shipbody">{php}echo strip_places($tot_planet_credits);{/php}</td>
	{if $enable_mass_logging == 1}
	    <td class="shipbody">MASS Logging</td>
	{else}
	    <td class="shipbody"><select name="logging" onchange="loggingchange();">
		{if $admin_extended_logging==1}
		<option value="ext_off">Off
		<option value="ext_on" selected>On
		{else}
		<option value="ext_off" selected>Off
		<option value="ext_on">On	
		{/if}
		</select>
		</td>
	{/if}
  </tr>
</table>
<br><strong>Ships</strong>
<table width="100%"  border="1" cellspacing="0" cellpadding="2" >
  <tr class="topbar" bgcolor="#000066">
    <td>Ship ID </td>
    <td>Type</td>
    <td>Hull</td>
    <td>Engines</td>
    <td>Power</td>
    <td>FB</td>
    <td>Sensors</td>
    <td>Beams</td>
    <td>Torps</td>
    <td>Shields</td>
    <td>Amour</td>
    <td>Cloak</td>
    <td>ECM</td>

  </tr>
  {for value="i" start="0" stop="$ship_count" step="1"}
  <tr bgcolor="#6666FF" class="shipbody">
    <td class="shipbody">{$ship_id[$i]}</td>
	{if $currentship==$ship_id[$i]}
    <td class="shipbody"  style="color:lime"><b>{$ship_type[$i]}<b></td>
	{else}
	<td class="shipbody">{$ship_type[$i]}</td>
	{/if}
    <td class="shipbody">{$hull_normal[$i]}/{$hull[$i]}</td>
    <td class="shipbody">{$engines_normal[$i]}/{$engines[$i]}</td>
    <td class="shipbody">{$power_normal[$i]}/{$power[$i]}</td>
    <td class="shipbody">{$computer_normal[$i]}/{$computer[$i]}</td>
    <td class="shipbody">{$sensors_normal[$i]}/{$sensors[$i]}</td>
    <td class="shipbody">{$beams_normal[$i]}/{$beams[$i]}</td>
    <td class="shipbody">{$torp_launchers_normal[$i]}/{$torp_launchers[$i]}</td>
    <td class="shipbody">{$shields_normal[$i]}/{$shields[$i]}</td>
    <td class="shipbody">{$armour_normal[$i]}/{$armour[$i]}</td>
    <td class="shipbody">{$cloak_normal[$i]}/{$cloak[$i]}</td>
    <td class="shipbody">{$ecm_normal[$i]}/{$ecm[$i]}</td>
    
  </tr>
  {/for}
</table>
	

<br><strong>Top 10 Planets</strong>
<table width="100%"  border="1" cellspacing="0" cellpadding="2" >
  <tr class="topbar" bgcolor="#000066">
    <td>Planet</td>
    <td>Sector</td>
    <td>Computer</td>
    <td>Sensors</td>
    <td>Beams</td>
    <td>Torps</td>
    <td>Shields</td>
    <td>Jammer</td>
    <td>Cloak</td>
	<td>Amour</td>
    <td>Colonists</td>
    <td>Energy</td>
    <td>Max Credits </td>
    <td>Credits</td>
  </tr>

  {for value="myLoop" start=0 stop=$planet_count step=1}

  <tr bgcolor="#6666FF" class="shipbody">
    <td class="shipbody">{$planetname[$myLoop]}</td>
    <td class="shipbody">{$psector_id[$myLoop]}</td>
    <td class="shipbody">{$pcomputer_normal[$myLoop]}/{$pcomputer[$myLoop]}</td>
    <td class="shipbody">{$psensors_normal[$myLoop]}/{$psensors[$myLoop]}</td>
    <td class="shipbody">{$pbeams_normal[$myLoop]}/{$pbeams[$myLoop]}</td>
    <td class="shipbody">{$ptorp_launchers_normal[$myLoop]}/{$ptorp_launchers[$myLoop]}</td>
    <td class="shipbody">{$pshields_normal[$myLoop]}/{$pshields[$myLoop]}</td>
    <td class="shipbody">{$pjammer_normal[$myLoop]}/{$pjammer[$myLoop]}</td>
    <td class="shipbody">{$pcloak_normal[$myLoop]}/{$pcloak[$myLoop]}</td>
 	<td class="shipbody">{$parmour[$myLoop]}</td>
    <td class="shipbody">{$pcolonists[$myLoop]}</td>
    <td class="shipbody">{$penergy[$myLoop]}</td>
    <td class="shipbody">{$pmax_credits[$myLoop]}</td>
    <td class="shipbody">{$pcredits[$myLoop]}</td>
  </tr>
  {/for}

</table><br>
<div align="center"><input type="Button" value="  Refresh  " onclick="reload();">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<select name="logginga" class="dropdown" onchange="loggingchangeb();">
<option value="">Select Log Purge Option</option>
<option value="cleartoday">Purge older than today</option>
<option value="clearall">Clearall</option>
</select>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="Button" value="  Prev Page  " onclick="prev();">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="Button" value="  Next Page  " onclick="next();">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div>

{if $log_count!=0}
<br><strong>Admin Log - Page <select name="pagenum" onchange="page();">
{php} 	for ($y=0;$y < $pages;$y++)
		{
			$pval=$y*150;
			if ($current_page==$y)
			{
				echo "<option value=\"$pval\" selected>".$y."</option>";
			}else{
				echo "<option value=\"$pval\" >".$y."</option>";
			}
		}
{/php}			

</select> of {$pages}</strong><div align="center">
<div style="width: 650px; align: center; height: 250px; background-color: black; overflow: auto;">
<table width="100%"  border="1" cellspacing="0" cellpadding="2" >
  <tr class="topbar" bgcolor="#000066">
    <td>IP Address </td>
    <td>Score</td>
    <td>Turns</td>	
    <td>Credits</td>
	<td>date/time</td>
    <td>Cur Command</td>
    <td>Get Data </td>
    <td>Post Data </td>
    <td>Player Time Left </td>
  </tr>

   {for value="myLoop" start=0 stop=$log_count step=1}
   
   {if $lcreditdiff[$myLoop] > 20 or $lscorediff[$myLoop] > 15}
  <tr bgcolor="#AAAAFF" class="shipbody">
  	{else}
	  <tr bgcolor="#6666FF" class="shipbody">
	{/if}
    <td class="shipbody" >{$lip_address[$myLoop]}</td>
	{if $lscorediff[$myLoop] > 50}
    <td class="shipbody"  style="color: red;">{$lscore[$myLoop]}</td>
	{elseif $lscorediff[$myLoop] > 15}
	<td class="shipbody" style="color: yellow;">{$lscore[$myLoop]}</td>
	{else}
	<td class="shipbody">{$lscore[$myLoop]}</td>
	{/if}
	
    <td class="shipbody">{$lturns[$myLoop]} </td>	
	{if $lcreditdiff[$myLoop] > 50}
    <td class="shipbody"  style="color: red;">{$lcredits[$myLoop]}</td>
	{elseif $lcreditdiff[$myLoop] > 20}
	<td class="shipbody" style="color: yellow;">{$lcredits[$myLoop]}</td>
	{else}
	<td class="shipbody">{$lcredits[$myLoop]} </td>
	{/if}
    <td class="shipbody">{$ltime[$myLoop]}</td>
    <td class="shipbody">{$lurl_path[$myLoop]}</td>
    <td class="shipbody" style="text-align:left;">{$lget_data[$myLoop]}</td>
	<td class="shipbody" style="text-align:left;">{$lpost_data[$myLoop]}</td>
	<td class="shipbody" style="text-align:left;">{$lplayer_online_time[$myLoop]}</td>
  </tr>
    {/for}
</table>
</div>
</div>
{/if}