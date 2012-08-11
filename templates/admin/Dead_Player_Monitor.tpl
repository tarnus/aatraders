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
    <td>Player Name </td>
    <td>IP Address </td>
    <td>Last Login </td>
    <td>Score</td>
    <td>Turns Used </td>
    <td>Credits</td>
  </tr>
  <tr bgcolor="#6666FF" class="shipbody">
    <td class="shipbody"><select name="user" style="text-align:left;" onchange="reload1();">
	  {for value=i start=0 stop=$player_tot step=1}
		{if $player_id==$list_player_id[$i]}
		<option value="{$list_player_id[$i]}" selected>{$list_character_name[$i]} {$online[i]}</option>
		{else}
		<option value="{$list_player_id[$i]}" >{$list_character_name[$i]}{$online[$i]}</option>
		{/if}  
	  {/for}
	
	</select>
	</td>
    <td class="shipbody">{$ip_address}</td>
    <td class="shipbody">{$last_login}</td>
    <td class="shipbody">{php}echo strip_places($score);{/php}</td>
    <td class="shipbody">{$turns_used}</td>
    <td class="shipbody">{php}echo strip_places($credits);{/php}</td>
  </tr>
</table>
<br>
<div align="center"><input type="Button" value="  Prev Page  " onclick="prev();">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="Button" value="  Next Page  " onclick="next();"></div>

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