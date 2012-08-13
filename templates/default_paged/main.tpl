{literal}
<script type="text/javascript" language="JavaScript1.2">
var key = new Array();  // Define key launcher pages here
key['a'] = "autotrades.php";
key['b'] = "beacon.php";
key['c'] = "traderoute_create.php";
key['D'] = "dig.php";
key['d'] = "defense_report.php";
key['e'] = "emerwarp.php";
key['f'] = "long_range_scan.php";
key['G'] = "genesis.php";
key['g'] = "galaxy_map.php";
key['H'] = "templates/{/literal}{$templatename}{literal}/hotkeyhelp.php";
key['i'] = "igb.php";
key['L'] = "logout.php";
key['l'] = "log.php";
key['M'] = "message_read.php";
key['m'] = "defense_deploy.php";
key['N'] = "news.php";
key['n'] = "sector_notes.php";
key['o'] = "options.php";
{/literal}
{if $allow_probes == 1}
{literal}
key['P'] = "probes.php";
{/literal}
{/if}
{literal}
key['p'] = "planet_report.php?PRepType=1";
key['R'] = "ranking.php";
key['r'] = "report.php";
key['S'] = "message_send.php";
key['s'] = "spy.php";
key['t'] = "traderoute_listroutes.php";
key['T'] = "team_defense_report.php";
key['w'] = "warpedit.php";
key['z'] = "stored_ship_report.php";
key['['] = "device.php";
key[']'] = "sectorgenesis.php";

var newwindow = new Array();  // Define key launcher pages here
newwindow['a'] = 0;
newwindow['b'] = 0;
newwindow['c'] = 0;
newwindow['D'] = 0;
newwindow['d'] = 0;
newwindow['e'] = 0;
newwindow['f'] = 0;
newwindow['G'] = 0;
newwindow['g'] = 0;
newwindow['H'] = 1;
newwindow['i'] = 0;
newwindow['L'] = 0;
newwindow['l'] = 0;
newwindow['M'] = 0;
newwindow['m'] = 0;
newwindow['N'] = 0;
newwindow['n'] = 0;
newwindow['o'] = 0;
newwindow['P'] = 0;
newwindow['p'] = 0;
newwindow['R'] = 0;
newwindow['r'] = 0;
newwindow['S'] = 0;
newwindow['s'] = 0;
newwindow['t'] = 0;
newwindow['T'] = 0;
newwindow['w'] = 0;
newwindow['z'] = 0;
newwindow['1'] = 0;
newwindow['2'] = 0;

function getKey(e) {
if(!e) var e = window.event;
if(e.which) {
which = String.fromCharCode(e.which);
}
if(e.keyCode){
which = String.fromCharCode(e.keyCode);
}

	if(e.keyCode || e.which){
		for (var i in key){ 
		if (which == i){
			if (newwindow[i])
				window.open(key[i],'','');
			else
				window.location = key[i];
			}
		}	
	}		
	
}

document.onkeypress = getKey;

</script>

<style type="text/css">

#dhtmltooltip{
position: absolute;
width: 200px;
border: 2px solid black;
padding: 2px;
background-color: lightyellow;
visibility: hidden;
z-index: 2000;
/*Remove below line to remove shadow. Below line should always appear last within this CSS*/
filter: progid:DXImageTransform.Microsoft.Shadow(color=gray,direction=135);
}

.tooltiptitle{COLOR: #FFFFFF; TEXT-DECORATION: none; CURSOR: Default; font-family: arial; font-weight: bold; font-size: 8pt}
.tooltipcontent{COLOR: #000000; TEXT-DECORATION: none; CURSOR: Default; font-family: arial; font-size: 8pt}
</style>

<div id="dhtmltooltip"></div>

<script type="text/javascript">

/***********************************************
* Cool DHTML tooltip script- © Dynamic Drive DHTML code library (www.dynamicdrive.com)
* This notice MUST stay intact for legal use
* Visit Dynamic Drive at http://www.dynamicdrive.com/ for full source code
***********************************************/

var offsetxpoint=-60 //Customize x offset of tooltip
var offsetypoint=40 //Customize y offset of tooltip

var ie=document.all
var ns6=document.getElementById && !document.all
var enabletip=false
if (ie||ns6)
var tipobj=document.all? document.all["dhtmltooltip"] : document.getElementById? document.getElementById("dhtmltooltip") : ""

function ietruebody(){
return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
}


function ddrivetip(thetitle, thetext, thecolor, thewidth){
if (ns6||ie){
if (typeof thewidth!="undefined") tipobj.style.width=thewidth+"px"
if (typeof thecolor!="undefined" && thecolor!="") tipobj.style.backgroundColor=thecolor

	topColor = "#7D92A9"
	subColor = "#A5B4C4"
	ContentInfo = '<table border="0" width="200" cellspacing="0" cellpadding="0">'+
	'<tr><td width="100%" bgcolor="#000000">'+

	'<table border="0" width="100%" cellspacing="1" cellpadding="0">'+
	'<tr><td width="100%" bgcolor='+topColor+'>'+

	'<table border="0" width="90%" cellspacing="0" cellpadding="0" align="center">'+
	'<tr><td width="100%" align="center">'+

	'<font class="tooltiptitle">'+thetitle+'</font>'+

	'</td></tr>'+
	'</table>'+

	'</td></tr>'+

	'<tr><td width="100%" bgcolor='+subColor+'>'+

	'<table border="0" width="90%" cellpadding="0" cellspacing="1" align="center">'+

	'<tr><td width="100%">'+

	'<font class="tooltipcontent">'+thetext+'</font>'+

	'</td></tr>'+
	'</table>'+

	'</td></tr>'+
	'</table>'+

	'</td></tr>'+
	'</table>';

tipobj.innerHTML=ContentInfo
enabletip=true
return false
}
}

function positiontip(e){
if (enabletip){
var curX=(ns6)?e.pageX : event.clientX+ietruebody().scrollLeft;
var curY=(ns6)?e.pageY : event.clientY+ietruebody().scrollTop;
//Find out how close the mouse is to the corner of the window
var rightedge=ie&&!window.opera? ietruebody().clientWidth-event.clientX-offsetxpoint : window.innerWidth-e.clientX-offsetxpoint-20
var bottomedge=ie&&!window.opera? ietruebody().clientHeight-event.clientY-offsetypoint : window.innerHeight-e.clientY-offsetypoint-20

var leftedge=(offsetxpoint<0)? offsetxpoint*(-1) : -1000

//if the horizontal distance isn't enough to accomodate the width of the context menu
if (rightedge<tipobj.offsetWidth)
//move the horizontal position of the menu to the left by it's width
tipobj.style.left=ie? ietruebody().scrollLeft+event.clientX-tipobj.offsetWidth+"px" : window.pageXOffset+e.clientX-tipobj.offsetWidth+"px"
else if (curX<leftedge)
tipobj.style.left="5px"
else
//position the horizontal position of the menu where the mouse is positioned
tipobj.style.left=curX+offsetxpoint+"px"

//same concept with the vertical position
if (bottomedge<tipobj.offsetHeight)
tipobj.style.top=ie? ietruebody().scrollTop+event.clientY-tipobj.offsetHeight-offsetypoint+"px" : window.pageYOffset+e.clientY-tipobj.offsetHeight-offsetypoint+"px"
else
tipobj.style.top=curY+offsetypoint+"px"
tipobj.style.visibility="visible"
}
}

function hideddrivetip(){
if (ns6||ie){
enabletip=false
tipobj.style.visibility="hidden"
tipobj.style.left="-1000px"
tipobj.style.backgroundColor=''
tipobj.style.width=''
}
}

document.onmousemove=positiontip

//-->
</script>

<script language="javascript" type="text/javascript">
 	function OpenSB()
		{
			f2 = open("shoutbox.php","f2","width=700,height=400,scrollbars=yes");
		}
</script>	
<SCRIPT LANGUAGE="JavaScript1.2" TYPE="text/javascript">
<!--
var delay=1000 //set delay between message change (in miliseconds)
var fcontent=new Array()

{/literal}
{php}
	for($i = 0; $i < $shoutcount; $i++) 
		echo "fcontent[$i]=\"<A CLASS=headlines HREF='#' onClick='OpenSB();'>" . $shoutmessage[$i] . "</a>\"\n"; 
{/php}
{literal}

var fadescheme=1 //set 0 to fade text color from (white to black), 1 for (black to white)
var fadelinks=1  //should links inside scroller content also fade like text? 0 for no, 1 for yes.

///No need to edit below this line/////////////////

var hex=(fadescheme==0)? 255 : 0
var startcolor=(fadescheme==0)? "rgb(255,255,255)" : "rgb(0,0,0)"
var endcolor=(fadescheme==0)? "rgb(0,0,0)" : "rgb(255,255,255)"

var ie4=document.all&&!document.getElementById
var ns4=document.layers
var DOM2=document.getElementById
var faderdelay=0
var index=0

if (DOM2)
	faderdelay=2000

//function to change content
function changecontent(){
	if (index>=fcontent.length)
		index=0
	if (DOM2){
		document.getElementById("IEshout").style.color=startcolor
		document.getElementById("IEshout").innerHTML=fcontent[index]
		linksobj=document.getElementById("IEshout").getElementsByTagName("A")
		if (fadelinks)
			linkcolorchange(linksobj)
		colorfade()
	}
	else if (ie4)
		document.all.IEshout.innerHTML=fcontent[index]
	else if (ns4){
		document.shout.document.write(fcontent[index])
		document.shout.document.close()
	}
	index++
	setTimeout("changecontent()",delay+faderdelay)
}

// colorfade() partially by Marcio Galli for Netscape Communications.  ////////////
// Modified by Dynamicdrive.com

frame=20;

function linkcolorchange(obj){
	if (obj.length>0){
		for (i=0;i<obj.length;i++)
			obj[i].style.color="rgb("+hex+","+hex+","+hex+")"
	}
}

function colorfade() {	         	
// 20 frames fading process
	if(frame>0) {	
		hex=(fadescheme==0)? hex-12 : hex+12 // increase or decrease color value depd on fadescheme
		document.getElementById("IEshout").style.color="rgb("+hex+","+hex+","+hex+")"; // Set color value.
		if (fadelinks)
			linkcolorchange(linksobj)
		frame--;
		setTimeout("colorfade()",20);	
	}
	else
	{
		document.getElementById("IEshout").style.color=endcolor;
		frame=20;
		hex=(fadescheme==0)? 255 : 0
	}   
}
//-->
</SCRIPT>
{/literal}

{if $show_shoutbox == 1}
<table cellspacing = "0" cellpadding = "0" border = "1" width = "600" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr>
	<td bgcolor="#000000" background="templates/{$templatename}images/spacer.gif" width="100%" height="20" ID="IEshout" align="center" valign="middle">
<layer id="shout"</layer>
	</td>
</tr>
</table>
{/if}
<table width="100%" border=0 align=center cellpadding=0 cellspacing=0>
<tr>
<td valign=top>
<table border="0" cellpadding="4" cellspacing="0" align="left">
<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table  border="0" cellspacing="0" cellpadding="0" align="center" >
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0">
{if $avatar != "default_avatar.gif"}
<TR align="center"><TD><img src="images/avatars/{$avatar}"></td></tr>
		{/if}
<tr><td class=normal>{$l_rank}: <img src="templates/{$templatename}images/rank/{$insignia}"></td></tr>
<tr><td class=normal>{$l_name}: <span class=mnu>{$player_name}</font></span></td></tr>
<tr><td class=normal>{$l_ship} {$l_name}:<span class=mnu><a href="report.php">{$shipname}</a></span></td></tr>
<tr><td class=normal>{$l_shiptype}:<span class=mnu>{$classname}</span></td></tr>
<tr><td class=normal>{$l_turns_have}<span class=mnu>{$turns}</span></td></tr>
<tr><td class=normal>{$l_turns_used}<span class=mnu>{$turnsused}</span></td></tr>
<tr><td class=normal>{$l_score}<span class=mnu>
{php}
$places = explode(",", $score);
if (count($places) <= 3){
	echo $score;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	if(count($places) == 4){
		echo "$places[0].$places[1] B";
	}
	if(count($places) == 5){
		echo "$places[0].$places[1] T";
	}
	if(count($places) == 6){
		echo "$places[0].$places[1] Qd";
	}
	if(count($places) == 7){
		echo "$places[0].$places[1] Qn";
	}
	if(count($places) == 8){
		echo "$places[0].$places[1] Sx";
	}
	if(count($places) == 9){
		echo "$places[0].$places[1] Sp";
	}
	if(count($places) == 10){
		echo "$places[0].$places[1] Oc";
	}
}
{/php}</span></td></tr>
<tr><td class=normal>{$l_home_planet}: <span class=mnu>{$home_planet_name}</span></td></tr>
</table>
</td>
  </tr>
</table>
</td></tr>
</table>
</td></tr>
<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table  border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellpadding="0" align="left" cellspacing="0"><TR><TD  ID="commandblock" NOWRAP>
<div class=mnu>
{$commanddevices}<br>
{$commandplanetreport}<br>
{$commanddefensereport}<br>
{$commandstoredships}<br>
{$commandreadmail}<br>
{$commandsendmail}<br>
{$commandblockmail}<br>
{$commandlobby}<br>
{$commandnav}<br>

{$commandautotrade}<br>
{if $allow_probes == 1}
{$commandprobe}<br>
{/if}
{if $galaxy_map_enabled == true}
	{$commandmap}<br>
	{$commandlocalmap}<br>
{/if}
{if $enable_spies != 0}
	{$commandspy}<br>
{/if}

{if $enable_dignitaries != 0}
	{$commanddig}<br>
{/if}
{$commandlog}<br>

{$commandranking}<br>
{$commandteams}<br>
{if $team_id != 0}
	{$commandteamdefensereport}<br>
	{$commandteamforum}<br>
	{$commandteamship}<br>
	{$commandteamshoutbox}<br>
{/if}
{$commanddestruct}<br>
{$commandoptions}<br>
{$commandsectornotes}<br>
{if $galaxy_map_enabled == true and $gd_enabled == true and $enable_spiral_galaxy == 1}
	{$command3dmap}<br>
{/if}
&nbsp;<a class=mnu href="#" onClick="window.open('templates/{$templatename}hotkeyhelp.php','help','height=300,width=420,scrollbars=yes,resizable=no');">Hotkey Help</a><br>
{$commandfeedback}<br>
{if $link_forums != 0}
	{$commandforums}<br>
{/if}
{php}
	for($i = 0; $i < $newcommands; $i++){
		echo $newcommandfull[$i]."<br>";
	}
{/php}
{if $tournament_mode == 0}
	{$commandlogout}
{/if}
<br></div>
</td></tr>
</table>
	</td>
  </tr>
</table>
</td></tr>
</table>
</td></tr>
<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table  border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellpadding="0" align="left" cellspacing="0">
<tr><td align="center" colspan=2><span class=mnu>{$shoutboxtitle}</span><br><br></td></tr>
	<tr><td>
	<form method="post" action="shoutbox_save.php">
	<input type="Hidden" name="" value="1"><td NOWRAP class="shoutform">
	<textarea class="shoutform" wrap cols="18" rows="3" readonly>{$quickshout}</textarea><br>
	<input type="Text" name="sbt"  class="shoutform" size="14" maxlength="250" ONBLUR="document.onkeypress = getKey;" ONFOCUS="document.onkeypress = null;"><input type="submit" name="go" value="Go" class="shoutform"><br>Public?&nbsp;
	<input type="Hidden" name="returntomain" value="1">
{if $team_id > 0}
	<INPUT TYPE=CHECKBOX NAME=SBPB class="shoutform" >
{else}
	<INPUT TYPE=CHECKBOX NAME=SBPB class="shoutform" checked>
{/if}
</td></form></tr></table>
	</td>
  </tr>
</table>
</td></tr>
</table>
</td></tr>
</table>
</td>

<td valign=top align="center">
<table border=0 width="100%" align="center">
<tr><td align=left class=nav_title_12 width="33%">&nbsp;{if $sg_sector}
SG&nbsp;
{/if}{$l_sector}: <b>{$sector}</b><br>
&nbsp;{$l_planetmax} <b>{$starsize}</b></td>
<td align=center class=nav_title_12 width="33%"><b>{$beacon}</b></td>
<td align=right width="33%"><a class=nav_title_14b href="zoneinfo.php"><b>{$zonename}</b></a>&nbsp;</td>
</tr>
{if $sectorzero != 1}
<tr>
	{if $lss_sensorlevel == 0}
		<td colspan="3" valign="top" align="center" class="normal"><span class=mnu>{$l_lss}: <font color=#33ff00>{$lss_playername}</font></span></td>
	{/if}
	{if $lss_sensorlevel == 3}
		<td colspan="3" valign="top" align="center" class="normal"><span class=mnu>{$l_lss}: <font color=cyan>{$lss_playername}</font>(<font color=#33ff00>{$lss_shipclass}</font>) <font color=#52ACEA>{$l_traveled}</font> <font color=yellow><a class="mnu" href="main.php?move_method=real&engage=1&destination={$lss_destination|urlencode}">{$lss_destination}</a></font></span></td>
	{/if}
	{if $lss_sensorlevel == 2}
		<td colspan="3" valign="top" align="center" class="normal"><span class=mnu>{$l_lss}: <font color=cyan>{$lss_playername}</font>(<font color=#33ff00>{$lss_shipclass}</font>)</span></td>
	{/if}
	{if $lss_sensorlevel == 1}
		<td colspan="3" valign="top" align="center" class="normal"><span class=mnu>{$l_lss}: <font color=cyan>{$lss_playername}</font>(<font color=#33ff00>{$lss_shipclass}</font>)</span></td>
	{/if}
</tr>
{/if}
</table>
<table width="75%" border="0" cellspacing="3" cellpadding="3">
  <tr>
    <td> 
      <table width="50%" border="0" cellspacing="3" cellpadding="3" align="{php} echo ($countplanet > 0) ? "right" : "center";{/php}">
        <tr> 
          <td colspan="2" rowspan="2" align="center" valign="middle" class=nav_title_12>
		  {if $countplanet > 3}
			<A HREF=planet.php?planet_id={$planetid[3]}>
<img src="templates/{$templatename}images/planet{$planetimg[3]}.png" alt="" width="100" height="100">
			</a><BR>
			<b>{$planetname[3]}
			<br>(<font color=cyan>{$planetowner[3]}</font>)</b>
				<br>{if $planetratingnumber[3] == -1}
					<font color="red">{$planetrating[3]}</font>
					{elseif $planetratingnumber[3] == 0}
					<font color="yellow">{$planetrating[3]}</font>
					{else}
					<font color="lime">{$planetrating[3]}</font>
					{/if}
		  {/if}
          </td>
          <td colspan="2" rowspan="2">&nbsp;</td>
          <td align="center" class=nav_title_14b>
		  {if $port_type != "none"}
<b>{$l_tradingport}</b>
{/if}</td>
          <td colspan="2" align="center">&nbsp;</td>
        </tr>
        <tr> 
          <td rowspan="2" align="center" valign="middle" class=nav_title_12>
		  {if $port_type != "none"}
		  <a href=port.php><img src="images/ports/port_{$port_type}.gif" border="0" alt=""></a><br><br><b><font color=#33ff00>{$portname}</font></b></td>
          <td colspan="2" rowspan="3" align="center" valign="middle" class=nav_title_12>
	{/if}
		  {if $sector_location == 1}
		  <a href="casino.php?casinogame=casino_forums"><img src="images/ports/port_fedinfo.gif" border="0" alt=""></a><br><br><b><font color=#33ff00>{$l_fedinfo}</font></b></td>
          <td colspan="2" rowspan="3" align="center" valign="middle" class=nav_title_12>
	{/if}
		</td>
        </tr>
        <tr> 
          <td>&nbsp;</td>
          <td colspan="2" align="center" valign="middle" class=nav_title_12>
		  {if $countplanet > 1}
			<A HREF=planet.php?planet_id={$planetid[1]}>
<img src="templates/{$templatename}images/planet{$planetimg[1]}.png" alt="" width="100" height="100"></a><BR>
			<b>{$planetname[1]}
			<br>(<font color=cyan>{$planetowner[1]}</font>)</b>
				<br>{if $planetratingnumber[1] == -1}
					<font color="red">{$planetrating[1]}</font>
					{elseif $planetratingnumber[1] == 0}
					<font color="yellow">{$planetrating[1]}</font>
					{else}
					<font color="lime">{$planetrating[1]}</font>
					{/if}
		  {/if}
          </td>
          <td>&nbsp;</td>
        </tr>
        <tr> 
          <td colspan="2" rowspan="4">&nbsp;</td>
          <td colspan="2" rowspan="2" align="center" valign="middle" class=nav_title_12>
		  {if $countplanet > 0}
			<A HREF=planet.php?planet_id={$planetid[0]}>
<img src="templates/{$templatename}images/planet{$planetimg[0]}.png" alt="" width="100" height="100">
			</a><BR>
			<b>{$planetname[0]}
			<br>(<font color=cyan>{$planetowner[0]}</font>)</b>
				<br>{if $planetratingnumber[0] == -1}
					<font color="red">{$planetrating[0]}</font>
					{elseif $planetratingnumber[0] == 0}
					<font color="yellow">{$planetrating[0]}</font>
					{else}
					<font color="lime">{$planetrating[0]}</font>
					{/if}
		  {/if}
</td>
          <td>&nbsp;</td>
          <td colspan="2" rowspan="2">&nbsp;</td>
        </tr>
        <tr> 
          <td rowspan="2" align="center" valign="middle" class=nav_title_12>
		  {if $countplanet > 2}
			<A HREF=planet.php?planet_id={$planetid[2]}>
<img src="templates/{$templatename}images/planet{$planetimg[2]}.png" alt="" width="100" height="100">
			</a><BR>
			<b>{$planetname[2]}
			<br>(<font color=cyan>{$planetowner[2]}</font>)</b>
				<br>{if $planetratingnumber[2] == -1}
					<font color="red">{$planetrating[2]}</font>
					{elseif $planetratingnumber[2] == 0}
					<font color="yellow">{$planetrating[2]}</font>
					{else}
					<font color="lime">{$planetrating[2]}</font>
					{/if}
		  {/if}
		  </td>
          <td colspan="2" rowspan="2" align="center" valign="middle" class=nav_title_12>
		  {if $countplanet > 4}
			<A HREF=planet.php?planet_id={$planetid[4]}>
<img src="templates/{$templatename}images/planet{$planetimg[4]}.png" alt="" width="100" height="100">			</a><BR>
			<b>{$planetname[4]}
			<br>(<font color=cyan>{$planetowner[4]}</font>)</b>
				<br>{if $planetratingnumber[4] == -1}
					<font color="red">{$planetrating[4]}</font>
					{elseif $planetratingnumber[4] == 0}
					<font color="yellow">{$planetrating[4]}</font>
					{else}
					<font color="lime">{$planetrating[4]}</font>
					{/if}
		  {/if}
		  </td>
        </tr>
      </table>
</td>
  </tr>
</table>
<br>
<table border=0 width="100%" align="center">
<tr>

	{if $sector_location != 1}
		{if $playercount != 0}
			{for start=0 stop=$playercount-1 step=1 value=myLoop}
   				{if $shipprobe[$myLoop] == "ship"}
					<td align=center valign=top class=nav_title_12>
					<a href="ship.php?player_id={$player_id[$myLoop]}&ship_id={$ship_id[$myLoop]}">
					<img src="templates/{$templatename}images/{$shipimage[$myLoop]}.gif" border=0></a><BR>
					{$shipnames[$myLoop]}
					<br><b>(<font color=cyan>{$playername[$myLoop]}</font>)</b>
					{if $teamname[$myLoop] != ""}
						&nbsp;<b>(<font color=#33ff00>{$teamname[$myLoop]}</font>)</b>
					{/if}
					<br>
					{if $shipratingnumber[$myLoop] == -1}
						<font color="red">{$shiprating[$myLoop]}</font>
					{elseif $shipratingnumber[$myLoop] == 0}
						<font color="yellow">{$shiprating[$myLoop]}</font>
					{else}
						<font color="lime">{$shiprating[$myLoop]}</font>
					{/if}
					</td>
				{/if}
   				{if $shipprobe[$myLoop] == "probe"}
					<td align=center valign=top class=nav_title_12>
					<a href="probes_upgrade.php?probe_id={$player_id[$myLoop]}">
					<img src="templates/{$templatename}images/{$shipimage[$myLoop]}.gif" border=0></a><BR>
					{if $shipnames[$myLoop] != ""}
						{$shipnames[$myLoop]}
					{/if}
					<br><b>(<font color=cyan>{$playername[$myLoop]}</font>)</b>
					{if $teamname[$myLoop] != ""}
						&nbsp;<b>(<font color=#33ff00>{$teamname[$myLoop]}</font>)</b>
					{/if}
					</td>
				{/if}
   				{if $shipprobe[$myLoop] == "debris"}
					<td align=center valign=top class=nav_title_12>
					<a href="showdebris.php?debris_id={$player_id[$myLoop]}">
					<img src="templates/{$templatename}images/{$shipimage[$myLoop]}.gif" border=0></a><BR>
					<br><b>(<font color=#33ff00>{$playername[$myLoop]}</font>)</b>
					</td>
				{/if}
   				{if $shipprobe[$myLoop] == "artifact"}
					<td align=center valign=top class=nav_title_12>
					<a href="artifact_grab.php?artifact_id={$player_id[$myLoop]}" onMouseover="ddrivetip('{$playername[$myLoop]}','{$artifact_description[$myLoop]}');" onMouseout="hideddrivetip()">
					<img src="images/artifacts/{$shipimage[$myLoop]}.gif" border=0></a><BR>
					<br><b>(<font color=#33ff00>{$playername[$myLoop]}</font>)</b>
					</td>
				{/if}

				{if $myLoop == 4 or $myLoop == 9 or $myLoop == 14 or $myLoop == 19 or $myLoop == 2}
					</tr></table><table border=0 width="100%"><tr>
				{/if}
			{/for}
		{/if}
	{else}
		<td valign=top align=center class=nav_title_12><b>{$l_sector_0}</b></td>
	{/if}

</tr>
</table>
{if $defensecount != 0}
<br>
<table border=0 width="100%" align="center">
<tr>
{php}
	$count = 0;
	for($i = 0; $i < $defensecount; $i++){
		if($defensetype[$i] == "fighters"){
			if($count == 0){
				echo "<td align=center valign=top><img src=templates/" . $templatename . "images/fighters.gif><br>";
			}
			echo "<font class=normal>";
			echo "<a class=mnu href=defense_modify.php?defense_id=" . $defenseid[$i] . "><b>";
			echo $defplayername[$i];
			echo "</a></b><br>";
			echo " <b>(<font color=yellow>$defenseqty[$i]</font> <font color=#33ff00>$defensemode[$i]</font>)</b>";
			echo "</font><br>";

			if ($sdratingnumber[$i] == -1)
			{
				echo "<font color=\"red\">$sdrating[$i]</font><br>";
			}
			else if ($sdratingnumber[$i] == 0)
			{
				echo "<font color=\"yellow\">$sdrating[$i]</font><br>";
			}
			else
			{
				echo "<font color=\"lime\">$sdrating[$i]</font><br>";
			}

			$count++;
		}
	}
	if($count != 0)
		echo "</td>";
{/php}
{php}
	$count = 0;
	for($i = 0; $i < $defensecount; $i++){
		if($defensetype[$i] == "mines"){
			if($count == 0){
				echo "<td align=center valign=top><img src=templates/" . $templatename . "images/mines.gif><br>";
			}
			echo " <font class=normal>";
			echo "<a class=mnu href=defense_modify.php?defense_id=" . $defenseid[$i] . "><b>";
			echo $defplayername[$i];
			echo "</a></b><br>";
			echo " <b>(<font color=yellow>$defenseqty[$i]</font> <font color=#33ff00>$defensemode[$i]</font>)</b>";
			echo "</font><br>";

			if ($sdratingnumber[$i] == -1)
			{
				echo "<font color=\"red\">$sdrating[$i]</font><br>";
			}
			else if ($sdratingnumber[$i] == 0)
			{
				echo "<font color=\"yellow\">$sdrating[$i]</font><br>";
			}
			else
			{
				echo "<font color=\"lime\">$sdrating[$i]</font><br>";
			}

			$count++;
		}
	}
	if($count != 0)
		echo "</td>";

{/php}

</tr>
</td></tr></table>
{/if}<td valign=top>
<table border="0" cellspacing="0" cellpadding="4" align="right" >

<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table border="0" cellspacing="0" cellpadding="0" align="right">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" width="100%" ><table cellspacing = "0" cellpadding = "0" border = "0" width="100%" >
<tr><td align="center" colspan=2><span class=mnu>{$l_cargo}</span><br><br></td></tr>
{if $cargo_items > 0}
{php}
	for($i = 0; $i < $cargo_items; $i++)
	{
		if ($cargo_amount[$i] != "0")
		{
			echo "<tr><td width=\"50%\" nowrap align='left' class=normal><img height=12 width=12 alt=\"$cargo_name[$i]\" src=\"images/ports/" . $cargo_name[$i] . ".png\">&nbsp;" . ucfirst($cargo_name[$i]) . "</td><td width=\"50%\" nowrap align='right'><span class=mnu>&nbsp;";

			$places = explode(",", $cargo_amount[$i]);
			if (count($places) <= 3){
				echo $cargo_amount[$i];
			}
			else
			{
				$places[1] = AAT_substr($places[1], 0, 2);
				if(count($places) == 4){
					echo "$places[0].$places[1] B";
				}
				if(count($places) == 5){
					echo "$places[0].$places[1] T";
				}
				if(count($places) == 6){
					echo "$places[0].$places[1] Qd";
				}
				if(count($places) == 7){
					echo "$places[0].$places[1] Qn";
				}
			}
			echo "</span></td></tr>";
		}
	}
{/php}
{/if}

{if $shipinfo_energy != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_energy}" src="templates/{$templatename}images/energy.png">&nbsp;{$l_energy}</td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
$places = explode(",", $shipinfo_energy);
if (count($places) <= 3){
	echo $shipinfo_energy;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	if(count($places) == 4){
		echo "$places[0].$places[1] B";
	}
	if(count($places) == 5){
		echo "$places[0].$places[1] T";
	}
	if(count($places) == 6){
		echo "$places[0].$places[1] Qd";
	}
	if(count($places) == 7){
		echo "$places[0].$places[1] Qn";
	}
}
{/php}
</span></td></tr>
{/if}

{if $shipinfo_fighters != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_fighters}" src="templates/{$templatename}images/tfighter.png">&nbsp;{$l_fighters}</td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
$places = explode(",", $shipinfo_fighters);
if (count($places) <= 3){
	echo $shipinfo_fighters;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	if(count($places) == 4){
		echo "$places[0].$places[1] B";
	}
	if(count($places) == 5){
		echo "$places[0].$places[1] T";
	}
	if(count($places) == 6){
		echo "$places[0].$places[1] Qd";
	}
	if(count($places) == 7){
		echo "$places[0].$places[1] Qn";
	}
}
{/php}
</span></td></tr>
{/if}

{if $shipinfo_torps != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_torps}" src="templates/{$templatename}images/torp.png">&nbsp;{$l_torps}</td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
$places = explode(",", $shipinfo_torps);
if (count($places) <= 3){
	echo $shipinfo_torps;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	if(count($places) == 4){
		echo "$places[0].$places[1] B";
	}
	if(count($places) == 5){
		echo "$places[0].$places[1] T";
	}
	if(count($places) == 6){
		echo "$places[0].$places[1] Qd";
	}
	if(count($places) == 7){
		echo "$places[0].$places[1] Qn";
	}
}
{/php}
</span></td></tr>
{/if}

{if $shipinfo_armor != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_armorpts}" src="templates/{$templatename}images/armor.png">&nbsp;{$l_armor}</td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
$places = explode(",", $shipinfo_armor);
if (count($places) <= 3){
	echo $shipinfo_armor;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	if(count($places) == 4){
		echo "$places[0].$places[1] B";
	}
	if(count($places) == 5){
		echo "$places[0].$places[1] T";
	}
	if(count($places) == 6){
		echo "$places[0].$places[1] Qd";
	}
	if(count($places) == 7){
		echo "$places[0].$places[1] Qn";
	}
}
{/php}
</span></td></tr>
{/if}

<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_credits}" src="templates/{$templatename}images/credits.png">&nbsp;{$l_credits}</td><td width="50%" nowrap align='right' colspan=2><span class=mnu>&nbsp;
{php}
$places = explode(",", $playerinfo_credits);
if (count($places) <= 3){
	echo $playerinfo_credits;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	if(count($places) == 4){
		echo "$places[0].$places[1] B";
	}
	if(count($places) == 5){
		echo "$places[0].$places[1] T";
	}
	if(count($places) == 6){
		echo "$places[0].$places[1] Qd";
	}
	if(count($places) == 7){
		echo "$places[0].$places[1] Qn";
	}
	if(count($places) == 8){
		echo "$places[0].$places[1] Sx";
	}
	if(count($places) == 9){
		echo "$places[0].$places[1] Sp";
	}
	if(count($places) == 10){
		echo "$places[0].$places[1] Oc";
	}
}
{/php}
</span></td></tr>
	
	</td></tr></table>
</td>
  </tr>
</table>
</td></tr>
</table>
</td></tr>

{if $num_traderoutes != 0}
<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0"><TR align="center"><TD NOWRAP>
<tr><td align="center" colspan=2><span class=mnu>{$l_traderoutes}</span><br><br></td></tr>

{if $num_traderoutes == 1}
	<tr><td class="nav_title_12" align=center nowrap>
		<a class=mnu href="traderoute_engage.php?engage={$traderoute_links[0]}">{$traderoute_display[0]}</a><br>
	<br></td></tr>
{/if}

{if $num_traderoutes > 1}
{php}
	echo "<form name=\"traderoutes\"><tr><td class=\"nav_title_12\" align=center>\n";
	echo "<select name=\"menu\" onChange=\"location=document.traderoutes.menu.options[document.traderoutes.menu.selectedIndex].value;\" value=\"GO\" class=\"rsform\"><option value=\"\">Select Traderoute</option>\n";
	for($i = 0; $i < count($traderoute_links); $i++){
		echo "<option value=\"traderoute_engage.php?engage=" . $traderoute_links[$i] . "\">$traderoute_display[$i]</option>\n";
	}
	echo "</select>";
	echo "<br></td></tr></form>\n";
{/php}

{/if}
<tr><td nowrap align="center">
<div class=mnu>
[<a class=mnu href=traderoute_create.php>{$l_add}</a>]&nbsp;&nbsp;<a class=mnu href=traderoute_listroutes.php>{$l_trade_control}</a><br>

</div></td></tr></table>
</td>
  </tr>
</table>
</td></tr>
</table>
</tr></td>
{/if}

<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0">
<TR align="center"><TD NOWRAP><div class=mnu align=center>{$l_sector} {$sector} {$l_notes}<br>
{php}
if ($note_view != 0){
	echo "<a class=dis href=\"sector_notes.php?command=viewnote\">[".$l_view_note."]</a>";
}
echo "<a class=dis href=\"sector_notes.php?command=addnote&sector=".$sector."&sector_planets=".count($planetid)."&sector_port=".$portname."&sector_fighters=".$tmp_fighters."&sector_torps=".$tmp_torps."\">[".$l_add_note."]</a>";
{/php}
<br><br>
</div></td></tr>
<tr><td align="center" colspan=2><span class=mnu>{$l_realspace}</span><br><br></td></tr>

<tr><td nowrap="" align=center colspan=2>
<TABLE BORDER=0 CELLPADDING=1 CELLSPACING=0 BGCOLOR="#000000" align=center>
<form name="lastsector"><tr><td class="nav_title_12" align=center>
<select name="menu" onChange="location=document.lastsector.menu.options[document.lastsector.menu.selectedIndex].value;" value="GO" class="rsform"><option value="">RS to Last Sector</option>
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[0]|urlencode}">{$lastsectors[0]} - ({$lastsectorsdist[0]})</option>
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[1]|urlencode}">{$lastsectors[1]} - ({$lastsectorsdist[1]})</option>
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[2]|urlencode}">{$lastsectors[2]} - ({$lastsectorsdist[2]})</option>
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[3]|urlencode}">{$lastsectors[3]} - ({$lastsectorsdist[3]})</option>
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[4]|urlencode}">{$lastsectors[4]} - ({$lastsectorsdist[4]})</option>
</select></td></tr></form>

{php}
	echo "<form name=\"presets\"><tr><td class=\"nav_title_12\" align=center>\n";
	echo "<select name=\"menu\" onChange=\"location=document.presets.menu.options[document.presets.menu.selectedIndex].value;\" value=\"GO\" class=\"rsform\"><option value=\"\">RS to Sector</option>\n";
	for($i = 0; $i < count($preset_display); $i++){
		echo "<option value=\"main.php?move_method=real&engage=1&amp;destination=" . urlencode($preset_display[$i]) . "\">$preset_display[$i] - $preset_info[$i] ($preset_dist[$i])</option>\n";
	}
	echo "</select></td></tr>\n";
	
{/php}

<tr><td class="nav_title_12" align=center><a class=dis href="preset.php?name=set">[{$l_set}]</a>&nbsp;&nbsp;-&nbsp;&nbsp;<a class=dis href="preset.php?name=add">[{$l_add}]</a></td></tr></form>
<form method="post" action="main.php"><tr><td class="nav_title_12" align=center>
<input type="hidden" name="move_method" value="real">
<input type="text" name="destination" class="rsform" maxlength="30" size="8" ONBLUR="document.onkeypress = getKey;" ONFOCUS="document.onkeypress = null;"><br>
<input type="submit" name="explore" value="&nbsp;?&nbsp;" class="rsform">
<input type="submit" name="go" value="Go" class="rsform">
</td></tr></form>
</table></td></tr>

<TR align="center">
	<TD NOWRAP colspan=2><div id="ToolTip"></div>
{if $gd_enabled}
<table align="center"><tr><td align="center" valign="top"><a href="galaxy_map3d.php">{php}
 $coords = explode("|", $ship_coordinates); 
echo "
<img align=\"middle\" src=\"galaxy_position.php?universe_size=$universe_size&sx=$coords[0]&sy=$coords[1]&sz=$coords[2]\" border=\"0\" >";
{/php}</a>

</td></tr></table>
{/if}
<TABLE border=0 cellpadding=1 cellspacing=0 align=center>
<tr>
{if $xyminusp[8] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[8]);{/php}
		<TD bgcolor={$sectorzonecolorx3[8]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[8]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[8]} - {$altportx3[8]}<br>{$altturnsx3[8]}','{$l_galacticarm}: {$galacticarmx3[8]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[8]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[8]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[8]}.png" title="{$sectortitlex3[8]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}
{if $xyminusp[6] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[6]);{/php}
		<TD bgcolor={$sectorzonecolorx3[6]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[6]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[6]} - {$altportx3[6]}<br>{$altturnsx3[6]}','{$l_galacticarm}: {$galacticarmx3[6]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[6]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[6]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[6]}.png" title="{$sectortitlex3[6]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}
{if $xyminusp[4] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[4]);{/php}
		<TD bgcolor={$sectorzonecolorx3[4]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[4]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[4]} - {$altportx3[4]}<br>{$altturnsx3[4]}','{$l_galacticarm}: {$galacticarmx3[4]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[4]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[4]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[4]}.png" title="{$sectortitlex3[4]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
	<TD bgcolor=black rowspan="3" valign="bottom"><img src="templates/{$templatename}images/nav_vert.gif"  border=0 width = "12" height = "36"></td>
{if $xyplus[4] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[4]);{/php}
		<TD bgcolor={$sectorzonecolorx1[4]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[4]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[4]} - {$altportx1[4]}<br>{$altturnsx1[4]}','{$l_galacticarm}: {$galacticarmx1[4]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[4]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[4]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[4]}.png" title="{$sectortitlex1[4]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}
{if $xyplus[6] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[6]);{/php}
		<TD bgcolor={$sectorzonecolorx1[6]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[6]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[6]} - {$altportx1[6]}<br>{$altturnsx1[6]}','{$l_galacticarm}: {$galacticarmx1[6]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[6]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[6]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[6]}.png" title="{$sectortitlex1[6]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyplus[8] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[8]);{/php}
		<TD bgcolor={$sectorzonecolorx1[8]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[8]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[8]} - {$altportx1[8]}<br>{$altturnsx1[8]}','{$l_galacticarm}: {$galacticarmx1[8]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[8]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[8]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[8]}.png" title="{$sectortitlex1[8]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
</tr>
<tr>
{if $xyminusp[7] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[7]);{/php}
		<TD bgcolor={$sectorzonecolorx3[7]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[7]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[7]} - {$altportx3[7]}<br>{$altturnsx3[7]}','{$l_galacticarm}: {$galacticarmx3[7]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[7]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[7]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[7]}.png" title="{$sectortitlex3[7]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}
{if $xyminusp[3] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[3]);{/php}
		<TD bgcolor={$sectorzonecolorx3[3]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[3]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[3]} - {$altportx3[3]}<br>{$altturnsx3[3]}','{$l_galacticarm}: {$galacticarmx3[3]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[3]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[3]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[3]}.png" title="{$sectortitlex3[3]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyminusp[1] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[1]);{/php}
		<TD bgcolor={$sectorzonecolorx3[1]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[1]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[1]} - {$altportx3[1]}<br>{$altturnsx3[1]}','{$l_galacticarm}: {$galacticarmx3[1]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[1]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[1]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[1]}.png" title="{$sectortitlex3[1]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	

{if $xyplus[1] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[1]);{/php}
		<TD bgcolor={$sectorzonecolorx1[1]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[1]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[1]} - {$altportx1[1]}<br>{$altturnsx1[1]}','{$l_galacticarm}: {$galacticarmx1[1]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[1]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[1]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[1]}.png" title="{$sectortitlex1[1]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyplus[3] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[3]);{/php}
		<TD bgcolor={$sectorzonecolorx1[3]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[3]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[3]} - {$altportx1[3]}<br>{$altturnsx1[3]}','{$l_galacticarm}: {$galacticarmx1[3]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[3]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[3]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[3]}.png" title="{$sectortitlex1[3]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}			
{if $xyplus[7] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[7]);{/php}
		<TD bgcolor={$sectorzonecolorx1[7]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[7]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[7]} - {$altportx1[7]}<br>{$altturnsx1[7]}','{$l_galacticarm}: {$galacticarmx1[7]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[7]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[7]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[7]}.png" title="{$sectortitlex1[7]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}			
</tr>
<tr>
{if $xyminusp[5] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[5]);{/php}
		<TD bgcolor={$sectorzonecolorx3[5]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[5]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[5]} - {$altportx3[5]}<br>{$altturnsx3[5]}','{$l_galacticarm}: {$galacticarmx3[5]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[5]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[5]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[5]}.png" title="{$sectortitlex3[5]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}
{if $xyminusp[2] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[2]);{/php}
		<TD bgcolor={$sectorzonecolorx3[2]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[2]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[2]} - {$altportx3[2]}<br>{$altturnsx3[2]}','{$l_galacticarm}: {$galacticarmx3[2]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[2]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[2]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[2]}.png" title="{$sectortitlex3[2]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyminusp[0] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx3[0]);{/php}
		<TD bgcolor={$sectorzonecolorx3[0]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx3[0]} onMouseover="ddrivetip('{$l_sector}: {$xyminusp[0]} - {$altportx3[0]}<br>{$altturnsx3[0]}','{$l_galacticarm}: {$galacticarmx3[0]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx3[0]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx3[0]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex3[0]}.png" title="{$sectortitlex3[0]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	

{if $xyplus[0] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[0]);{/php}
		<TD bgcolor={$sectorzonecolorx1[0]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[0]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[0]} - {$altportx1[0]}<br>{$altturnsx1[0]}','{$l_galacticarm}: {$galacticarmx1[0]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[0]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[0]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[0]}.png" title="{$sectortitlex1[0]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
{if $xyplus[2] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[2]);{/php}
		<TD bgcolor={$sectorzonecolorx1[2]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[2]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[2]} - {$altportx1[2]}<br>{$altturnsx1[2]}','{$l_galacticarm}: {$galacticarmx1[2]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[2]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[2]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[2]}.png" title="{$sectortitlex1[2]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyplus[5] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx1[5]);{/php}
		<TD bgcolor={$sectorzonecolorx1[5]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx1[5]} onMouseover="ddrivetip('{$l_sector}: {$xyplus[5]} - {$altportx1[5]}<br>{$altturnsx1[5]}','{$l_galacticarm}: {$galacticarmx1[5]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx1[5]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx1[5]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex1[5]}.png" title="{$sectortitlex1[5]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
</tr>
<tr bgcolor=black><td colspan="3" valign="middle" align="right"><img src="templates/{$templatename}images/nav_horz.gif"  border=0 width = "48" height = "12"></td><td border=1 valign="middle" align="center"><A HREF="#" onMouseover="ddrivetip('{$l_sector}: {$sector}','{$l_galacticarm}: {$ship_galacticarm}<br><br>{php} $coords = explode("|", $ship_coordinates); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/yourhere.gif" border="0"></a></td><td colspan="3" align="left" valign="middle"><img src="templates/{$templatename}images/nav_horz.gif"  border=0 width = "48" height = "12"></td></tr>
<tr>
{if $xyminus[4] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[4]);{/php}
		<TD bgcolor={$sectorzonecolorx2[4]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[4]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[4]} - {$altportx2[4]}<br>{$altturnsx2[4]}','{$l_galacticarm}: {$galacticarmx2[4]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[4]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[4]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[4]}.png" title="{$sectortitlex2[4]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyminus[2] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[2]);{/php}
		<TD bgcolor={$sectorzonecolorx2[2]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[2]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[2]} - {$altportx2[2]}<br>{$altturnsx2[2]}','{$l_galacticarm}: {$galacticarmx2[2]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[2]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[2]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[2]}.png" title="{$sectortitlex2[2]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}
{if $xyminus[0] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[0]);{/php}
		<TD bgcolor={$sectorzonecolorx2[0]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[0]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[0]} - {$altportx2[0]}<br>{$altturnsx2[0]}','{$l_galacticarm}: {$galacticarmx2[0]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[0]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[0]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[0]}.png" title="{$sectortitlex2[0]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
	<TD bgcolor=black rowspan="3" valign="top"><img src="templates/{$templatename}images/nav_vert.gif"  border=0 width = "12" height = "36"></td>
{if $xyplusm[0] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[0]);{/php}
		<TD bgcolor={$sectorzonecolorx4[0]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[0]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[0]} - {$altportx4[0]}<br>{$altturnsx4[0]}','{$l_galacticarm}: {$galacticarmx4[0]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[0]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[0]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[0]}.png" title="{$sectortitlex4[0]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
{if $xyplusm[2] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[2]);{/php}
		<TD bgcolor={$sectorzonecolorx4[2]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[2]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[2]} - {$altportx4[2]}<br>{$altturnsx4[2]}','{$l_galacticarm}: {$galacticarmx4[2]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[2]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[2]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[2]}.png" title="{$sectortitlex4[2]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
{if $xyplusm[4] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[4]);{/php}
		<TD bgcolor={$sectorzonecolorx4[4]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[4]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[4]} - {$altportx4[4]}<br>{$altturnsx4[4]}','{$l_galacticarm}: {$galacticarmx4[4]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[4]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[4]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[4]}.png" title="{$sectortitlex4[4]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
</tr>
<tr>
{if $xyminus[6] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[6]);{/php}
		<TD bgcolor={$sectorzonecolorx2[6]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[6]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[6]} - {$altportx2[6]}<br>{$altturnsx2[6]}','{$l_galacticarm}: {$galacticarmx2[6]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[6]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[6]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[6]}.png" title="{$sectortitlex2[6]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyminus[1] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[1]);{/php}
		<TD bgcolor={$sectorzonecolorx2[1]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[1]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[1]} - {$altportx2[1]}<br>{$altturnsx2[1]}','{$l_galacticarm}: {$galacticarmx2[1]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[1]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[1]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[1]}.png" title="{$sectortitlex2[1]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	

{if $xyminus[3] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[3]);{/php}
		<TD bgcolor={$sectorzonecolorx2[3]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[3]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[3]} - {$altportx2[3]}<br>{$altturnsx2[3]}','{$l_galacticarm}: {$galacticarmx2[3]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[3]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[3]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[3]}.png" title="{$sectortitlex2[3]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		

{if $xyplusm[3] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[3]);{/php}
		<TD bgcolor={$sectorzonecolorx4[3]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[3]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[3]} - {$altportx4[3]}<br>{$altturnsx4[3]}','{$l_galacticarm}: {$galacticarmx4[3]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[3]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[3]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[3]}.png" title="{$sectortitlex4[3]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
{if $xyplusm[1] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[1]);{/php}
		<TD bgcolor={$sectorzonecolorx4[1]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[1]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[1]} - {$altportx4[1]}<br>{$altturnsx4[1]}','{$l_galacticarm}: {$galacticarmx4[1]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[1]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[1]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[1]}.png" title="{$sectortitlex4[1]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
{if $xyplusm[6] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[6]);{/php}
		<TD bgcolor={$sectorzonecolorx4[6]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[6]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[6]} - {$altportx4[6]}<br>{$altturnsx4[6]}','{$l_galacticarm}: {$galacticarmx4[6]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[6]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[6]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[6]}.png" title="{$sectortitlex4[6]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}				
</tr>
<tr>
{if $xyminus[8] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[8]);{/php}
		<TD bgcolor={$sectorzonecolorx2[8]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[8]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[8]} - {$altportx2[8]}<br>{$altturnsx2[8]}','{$l_galacticarm}: {$galacticarmx2[8]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[8]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[8]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[8]}.png" title="{$sectortitlex2[8]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
{if $xyminus[7] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[7]);{/php}
		<TD bgcolor={$sectorzonecolorx2[7]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[7]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[7]} - {$altportx2[7]}<br>{$altturnsx2[7]}','{$l_galacticarm}: {$galacticarmx2[7]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[7]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[7]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[7]}.png" title="{$sectortitlex2[7]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}		
{if $xyminus[5] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx2[5]);{/php}
		<TD bgcolor={$sectorzonecolorx2[5]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx2[5]} onMouseover="ddrivetip('{$l_sector}: {$xyminus[5]} - {$altportx2[5]}<br>{$altturnsx2[5]}','{$l_galacticarm}: {$galacticarmx2[5]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx2[5]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx2[5]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex2[5]}.png" title="{$sectortitlex2[5]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	

{if $xyplusm[5] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[5]);{/php}
		<TD bgcolor={$sectorzonecolorx4[5]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[5]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[5]} - {$altportx4[5]}<br>{$altturnsx4[5]}','{$l_galacticarm}: {$galacticarmx4[5]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[5]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[5]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[5]}.png" title="{$sectortitlex4[5]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	

{if $xyplusm[7] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[7]);{/php}
		<TD bgcolor={$sectorzonecolorx4[7]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[7]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[7]} - {$altportx4[7]}<br>{$altturnsx4[7]}','{$l_galacticarm}: {$galacticarmx4[7]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[7]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[7]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[7]}.png" title="{$sectortitlex4[7]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}	
	
{if $xyplusm[8] != ""}
		{php}$warp_links = str_replace("|", "<br>", $link_listx4[8]);{/php}
		<TD bgcolor={$sectorzonecolorx4[8]}><A HREF=main.php?move_method=real&engage=1&destination={$altsectorx4[8]} onMouseover="ddrivetip('{$l_sector}: {$xyplusm[8]} - {$altportx4[8]}<br>{$altturnsx4[8]}','{$l_galacticarm}: {$galacticarmx4[8]}<br><br>{php} $coords = explode("|", $nav_scan_coordsx4[8]); echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_listx4[8]<br><br>$l_links:<br>$warp_links"{/php}');" onMouseout="hideddrivetip()"><img src="images/ports/{$sectorimagex4[8]}.png" title="{$sectortitlex4[8]}" border=0 width = "12" height = "12"></A></TD>
	{else}
		<TD bgcolor="#585858"><img src="templates/{$templatename}images/spacer.gif"  border=0 width = "12" height = "12"></td>
	{/if}				
		
</tr>
		</table>
	</td>
</tr>

</table></td>
  </tr>
</table>
</td></tr>
</table>
</td></tr>

<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table  border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellpadding="0" align="left" cellspacing="0"><tr><td NOWRAP>
<tr><td align="center" colspan=2><span class=mnu>{$l_main_warpto}</span><br><br></td></tr>
<div class=mnu>
{php}
	if(count($links) == 0)
		echo "<tr><td width=100 class=\"nav_title_12\">&nbsp;<b>$linklist<b>&nbsp;</td></tr>\n";

	for($i = 0; $i < count($links); $i++){
		if($links_zone[$i] == "2")
			$zone_type = "F&gt;";
		else $zone_type = "=&gt;";
		if($sg_sector_linkback == $links[$i])
		{
			$zone_type = "<" . $zone_type;
		}
		if($links_type[$links[$i]] == 1)
			$link_image = "<img src=\"images/ports/" . $links_port_type[$i] . ".png\" border=0 width = \"12\" height = \"12\">";
		else $link_image = "";
		if($links_return[$links[$i]] == 1)
			echo "<tr><td width=100 class=\"nav_title_12\">&nbsp;<a class=\"mnu2\" href=\"main.php?move_method=warp&destination=" . urlencode($links[$i]) . "\">$zone_type&nbsp;$link_image&nbsp;$links[$i]</a>&nbsp;<a class=dis href=\"sector_scan.php?command=scan&sector=" . urlencode($links[$i]) . "\">[$l_scan]</a>&nbsp;</td></tr>\n";
		else echo "<tr><td width=100 class=\"nav_title_12\">&nbsp;<a class=\"mnu\" href=\"main.php?move_method=warp&destination=" . urlencode($links[$i]) . "\">$zone_type&nbsp;$link_image&nbsp;$links[$i]</a>&nbsp;<a class=dis href=\"sector_scan.php?command=scan&sector=" . urlencode($links[$i]) . "\">[$l_scan]</a>&nbsp;</td></tr>\n";
	}
{/php}
</div>
</td></tr>

<tr><td colspan=2 align=center class=dis><a href="long_range_scan.php" class=dis>[{$l_fullscan}]</a></td></tr>

{if $autototal != 0}
<tr>
<td NOWRAP align="center">
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0  align="center">
{php}
	echo "<form name=\"autoroutes\"><tr><td width=100 class=\"nav_title_12\" align=center>\n";
	echo "<select name=\"menu\" onChange=\"location=document.autoroutes.menu.options[document.autoroutes.menu.selectedIndex].value;\" value=\"GO\" class=\"rsform\"><option value=\"\">Select Autoroute</option>\n";
	for($i = 0; $i < count($autolist); $i++){
		$sgstart = ($autostartsg[$i] == 0) ? "" : "SG:";
		$sgdest = ($autodestsg[$i] == 0) ? "" : "SG:";

		if($sg_sector < 1 and $autostartsg[$i] < 1)
			echo "<option value=\"navcomp.php?state=start&autoroute_id=$autolist[$i]\">" . (($autoname[$i] == "" || empty($autoname[$i])) ? "$sgstart$autostart[$i]&nbsp;=&gt;&nbsp;$sgdest$autoend[$i]" : "(" . $autoname[$i] . ") ") . "</option>\n";

		if($sg_sector < 1 and $autodestsg[$i] < 1)
			echo "<option value=\"navcomp.php?state=reverse&autoroute_id=$autolist[$i]\">" . (($autoname[$i] == "" || empty($autoname[$i])) ? "$sgdest$autoend[$i]&nbsp;=&gt;&nbsp;$sgstart$autostart[$i]" : "(" . $autoname[$i] . ") ") . "</option>\n";

		if($sg_sector > 0 and $autostart[$i] == $sector)
			echo "<option value=\"navcomp.php?state=start&autoroute_id=$autolist[$i]\">" . (($autoname[$i] == "" || empty($autoname[$i])) ? "$sgdest$autoend[$i]&nbsp;=&gt;&nbsp;$sgstart$autostart[$i]" : "(" . $autoname[$i] . ") ") . "</option>\n";

		if($sg_sector > 0 and $autoend[$i] == $sector)
			echo "<option value=\"navcomp.php?state=reverse&autoroute_id=$autolist[$i]\">" . (($autoname[$i] == "" || empty($autoname[$i])) ? "$sgdest$autoend[$i]&nbsp;=&gt;&nbsp;$sgstart$autostart[$i]" : "(" . $autoname[$i] . ") ") . "</option>\n";

		if($sg_sector > 0 and (($autostart[$i] - 1) == $sector or ($autostart[$i] + 1) == $sector))
			echo "<option value=\"navcomp.php?state=start&autoroute_id=$autolist[$i]\">" . (($autoname[$i] == "" || empty($autoname[$i])) ? "$sgstart$autostart[$i]&nbsp;=&gt;&nbsp;$sgdest$autoend[$i]" : "(" . $autoname[$i] . ") ") . "</option>\n";

		if($sg_sector > 0 and (($autoend[$i] - 1) == $sector or ($autoend[$i] + 1) == $sector))
			echo "<option value=\"navcomp.php?state=reverse&autoroute_id=$autolist[$i]\">" . (($autoname[$i] == "" || empty($autoname[$i])) ? "$sgdest$autoend[$i]&nbsp;=&gt;&nbsp;$sgstart$autostart[$i]" : "(" . $autoname[$i] . ") ") . "</option>\n";
	}
	echo "</select>";
	echo "</td></tr></form>\n";
{/php}

</td></tr>
</table>
{/if}</td></tr></table>
	</td>
  </tr>
</table>
</td></tr>
</table>
</td></tr>

{if $num_traderoutes == 0}
<tr><td>
<table bgcolor="#000000" border="1" cellpadding="4" cellspacing="0" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr><td>
<table border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0"><TR align="center"><TD NOWRAP>
<tr><td align="center" colspan=2><span class=mnu>{$l_traderoutes}</span><br><br></td></tr>
<tr><td nowrap align="center">
<div class=mnu>
[<a class=mnu href=traderoute_create.php>{$l_add}</a>]&nbsp;&nbsp;<a class=mnu href=traderoute_listroutes.php>{$l_trade_control}</a>&nbsp;<br>

</div></td></tr></table>
</td>
  </tr>
</table>
</tr></td>
</table>
</td></tr>
{/if}
</table>
				</tr>
				</table>

{if $show_newscrawl == 1}
<table cellspacing = "0" cellpadding = "0" border = "1" width = "492" align="center" bordercolor="#52ACEA" style="border-color: 52ACEA; border-right-width: thin; border-left-width: thin; border-bottom-width: thin; border-top-width: thin;">
<tr>
	<TD valign="middle" align="center" bgcolor="#000000" bgcolor="templates/{$templatename}images/spacer.gif" width="100%" height="20" width="100%" ID="IEnews">
<layer id="news"</layer>
{literal}
<SCRIPT LANGUAGE="JavaScript1.2" TYPE="text/javascript">
<!--
arTXT = new Array({/literal}{php}for($i = 0; $i < $newscount; $i++) echo "\"" . $newsmessage[$i] . "\", "; {/php}{literal}"End of News");

NS4 = (document.layers);
IE4 = (document.all);

FDRblendInt = 3; // seconds between flips
FDRmaxLoops = 200; // max number of loops (full set of headlines each loop)
FDRendWithFirst = true;

FDRfinite = (FDRmaxLoops > 0);
blendTimer = null;

arTopNews = [];
for (i1=0;i1<arTXT.length;i1++)
{
 arTopNews[arTopNews.length] = arTXT[i1];
}

if(NS4)
{
	news = document.news;
	news.visibility="hide";

	pos1 = document.images['pht'];
	pos1E = document.images['ph1E'];
	news.left = pos1.x;
	news.top = pos1.y;
	news.clip.width = 350;
	news.clip.height = pos1E.y - news.top;
}
else 
{
	document.getElementById('IEnews').style.pixelHeight = document.getElementById('IEnews').offsetHeight;
}

function FDRredo()
{
	if (innerWidth==origWidth && innerHeight==origHeight) return;
	location.reload();
}

function FDRcountLoads() 
{
	if (NS4)
	{
		origWidth = innerWidth;
		origHeight = innerHeight;
		window.onresize = FDRredo;
	}

	TopnewsCount = 0;
	TopLoopCount = 0;

	FDRdo();
	blendTimer = setInterval("FDRdo()",FDRblendInt*1000)
}

function FDRdo() 
{
	if (FDRfinite && TopLoopCount>=FDRmaxLoops) 
	{
		FDRend();
		return;
	}
	FDRfade();

	if (TopnewsCount >= arTopNews.length) 
	{
		TopnewsCount = 0;
		if (FDRfinite) TopLoopCount++;
	}
}

function FDRfade(){
	if(TopLoopCount < FDRmaxLoops) {
		TopnewsStr = "";
		for (var i=0;i<1;i++)
		{
			if(TopnewsCount < arTopNews.length) 
			{
				TopnewsStr += "<P><A CLASS=headlines TARGET=_new HREF='news.php'>"
							+ arTopNews[TopnewsCount] + "</" + "A><img src='/images/spacer.gif' width=1 height=15></" + "P>"
				TopnewsCount += 1;
			}
		}
		if (NS4) 
		{
			news.document.write(TopnewsStr);
			news.document.close();
			news.visibility="show";
		}
		else 
		{
			document.getElementById('IEnews').innerHTML = TopnewsStr;
		}
	}
}

function FDRend(){
	clearInterval(blendTimer);
	if (FDRendWithFirst) 
	{
		TopnewsCount = 0;
		TopLoopCount = 0;
		FDRfade();
	}
}

function loadall(){
	changecontent();
	FDRcountLoads();
}

window.onload = loadall;
//-->
</SCRIPT>
{/literal}
	</td>
</tr>
</table>
{/if}
<img src="{php}
$startypes[0] = "templates/" . $templatename . "images/spacer.gif";
$startypes[1] = "templates/" . $templatename . "images/redstar.gif";
$startypes[2] = "templates/" . $templatename . "images/orangestar.gif";
$startypes[3] = "templates/" . $templatename . "images/yellowstar.gif";
$startypes[4] = "templates/" . $templatename . "images/greenstar.gif";
$startypes[5] = "templates/" . $templatename . "images/bluestar.gif";
echo "$startypes[$starsize]";
{/php}" border="0" alt="" style="position: absolute; z-index:-1; left: 70%; top: 30%; width: 480px; height: 480px; margin-left: -240px; margin-top: -240px;">

