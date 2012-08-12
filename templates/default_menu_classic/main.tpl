{literal}

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

<script type="text/javascript" language="JavaScript1.2">
var key = new Array();  // Define key launcher pages here
key['a'] = "traderoute_create.php";
key['B'] = "beacon.php";
key['c'] = "genesis.php";
key['C'] = "sectorgenesis.php";
key['D'] = "device.php";
key['d'] = "defense_report.php";
key['e'] = "emerwarp.php"; 
key['f'] = "long_range_scan.php";
key['G'] = "galaxy_local.php";
key['g'] = "galaxy_map.php";
key['i'] = "igb.php";
key['L'] = "logout.php";
key['l'] = "log.php";
key['m'] = "message_read.php";
key['M'] = "defense_deploy.php";
key['n'] = "news.php";
key['N'] = "sector_notes.php";
key['o'] = "options.php";
{/literal}
{if $allow_probes == 1}
{literal}
key['P'] = "probes.php"; 
{/literal}
{/if}
{literal}
key['p'] = "planet_report.php?PRepType=1"; 
key['r'] = "ranking.php"; 
key['R'] = "report.php"; 
key['s'] = "message_send.php";
key['t'] = "traderoute_listroutes.php";
key['T'] = "team_defense_report.php";
key['u'] = "galaxy_map3d.php";
key['w'] = "warpedit.php";
key['z'] = "stored_ship_report.php";
key['['] = "dig.php";
key[']'] = "spy.php";
key['.'] = "galaxy_local.php";

var newwindow = new Array();  // Define key launcher pages here
newwindow['a'] = 0;
newwindow['B'] = 0;
newwindow['c'] = 0;
newwindow['C'] = 0;
newwindow['D'] = 0;
newwindow['d'] = 0;
newwindow['e'] = 0;
newwindow['f'] = 0;
newwindow['G'] = 0;
newwindow['g'] = 0;
newwindow['i'] = 0;
newwindow['L'] = 0;
newwindow['l'] = 0;
newwindow['m'] = 0;
newwindow['M'] = 0;
newwindow['n'] = 0;
newwindow['N'] = 0;
newwindow['o'] = 0;
newwindow['P'] = 0;
newwindow['p'] = 0;
newwindow['R'] = 0;
newwindow['r'] = 0;
newwindow['s'] = 0;
newwindow['t'] = 0;
newwindow['T'] = 0;
newwindow['u'] = 0;
newwindow['w'] = 0;
newwindow['z'] = 0;
newwindow['['] = 0;
newwindow[']'] = 0;
newwindow['.'] = 1;

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
 {/literal}
 
<table border="0" cellspacing="0" cellpadding="0" width="100%">
  <tr>
    <td width="31" height="18"><img src="templates/{$templatename}images/topbar-tl.gif" width="31" height="18"></td>
    <td  background="templates/{$templatename}images/topbar-top-bg.gif" colspan="4"><img src="templates/{$templatename}images/topbar-top-bg.gif" width="250" height="19"></td>
    
    <td width="12" height="18"><img src="templates/{$templatename}images/topbar-tr.gif" width="12" height="18"></td>

  </tr>
  <tr>
    <td bgcolor="#000000" align="right" width="31" height="20"><img src="templates/{$templatename}images/topbar-midleft.gif" width="31" height="20"></td>
    <td background="templates/{$templatename}images/topbar-mid-bg.gif"  align="left" colspan="2" ID="IEshout1"><img src="templates/{$templatename}images/spacer.gif" width="250" height="1"><br><div style="border-style: dotted1none; border-color:white" id=scroll3 dir=rtl ;overflow:auto>
{literal}
<script language="javascript" type="text/javascript">
 	function OpenSB()
		{
			f2 = open("shoutbox.php","f2","width=700,height=400,scrollbars=yes");
		}
</script>	
<SCRIPT LANGUAGE="JavaScript1.2" TYPE="text/javascript">
<!--
prefix1=' ';

{/literal}
{php}
$stuff="";
$stuff2="";
for($i = 0; $i < $shoutcount; $i++){ 
$stuff2.="\"global_chat.php\",";
$stuff.="\"".$shoutmessage[$i]."\",";
}
$stuff.="\"End of Shouts\"";
$stuff2.="\"global_chat.php\"";
{/php}
{literal}
arURL1 = new Array({/literal}{php}echo $stuff2;{/php}{literal});
arTXT1 = new Array({/literal}{php}echo $stuff;{/php}{literal});


document.write('<LAYER ID=shout1><\/LAYER>');
NS4 = (document.layers);
IE4 = (document.all);

FDRblendInt1 = 5; // seconds between flips
FDRmaxLoops1 = 20; // max number of loops (full set of headlines each loop)
FDRendWithFirst1 = true;

FDRfinite1 = (FDRmaxLoops1 > 0);
blendTimer1 = null;

arTopNews1 = [];
for (i1=0;i1<arTXT1.length;i1++)
{
 arTopNews1[arTopNews1.length] = arTXT1[i1];
 arTopNews1[arTopNews1.length] = arURL1[i1];
}
TopPrefix1 = prefix1;

if(NS4)
{
	shout1 = document.shout1;
	shout1.visibility="hide";

	pos11 = document.images['pht1'];
	pos1E1 = document.images['ph1E1'];
	shout1.left = pos11.x;
	shout1.top = pos11.y;
	shout1.clip.width = 350;
	shout1.clip.height = pos1E1.y - shout1.top;
}
else 
{
	document.getElementById('IEshout1').style.pixelHeight = document.getElementById('IEshout1').offsetHeight;
}

function FDRredo1()
{
	if (innerWidth==origWidth1 && innerHeight==origHeight1) return;
	location.reload();
}

function FDRcountLoads1() 
{
	if (NS4)
	{
		origWidth1 = innerWidth;
		origHeight1 = innerHeight;
		window.onresize = FDRredo1;
	}

	TopnewsCount1 = 0;
	TopLoopCount1 = 0;

	FDRdo1();
	blendTimer1 = setInterval("FDRdo1()",FDRblendInt1*1000)
}

function FDRdo1() 
{
	if (FDRfinite1 && TopLoopCount1>=FDRmaxLoops1) 
	{
		FDRend1();
		return;
	}
	FDRfade1();

	if (TopnewsCount1 >= arTopNews1.length) 
	{
		TopnewsCount1 = 0;
		if (FDRfinite1) TopLoopCount1++;
	}
}

function FDRfade1(){
	if(TopLoopCount1 < FDRmaxLoops1) {
		TopnewsStr1 = "";
		for (var i=0;i<1;i++)
		{
			if(TopnewsCount1 < arTopNews1.length) 
			{
				TopnewsStr1 += "<P><A CLASS=headlines HREF='#' onClick='OpenSB();'>"
							+ arTopNews1[TopnewsCount1] + "</" + "A><img src='/images/spacer.gif' width=1 height=15></" + "P>"
				TopnewsCount1 += 2;
			}
		}
		if (NS4) 
		{
			shout1.document.write(TopnewsStr1);
			shout1.document.close();
			shout1.visibility="show";
		}
		else 
		{
			document.getElementById('IEshout1').innerHTML = TopnewsStr1;
		}
	}
}

function FDRend1(){
	clearInterval(blendTimer1);
	if (FDRendWithFirst1) 
	{
		TopnewsCount1 = 0;
		TopLoopCount1 = 0;
		FDRfade1();
	}
}

window.onload = FDRcountLoads1;
//-->
</SCRIPT>
{/literal}
</td>
    <td background="templates/{$templatename}images/topbar-mid-bg.gif" ID="IEfad1" align="right" colspan="2"><img src="templates/{$templatename}images/spacer.gif" width="250" height="1"><br><div style="border-style: dotted1none; border-color:white" id=scroll3 dir=rtl ;overflow:auto>
{literal}
<SCRIPT LANGUAGE="JavaScript1.2" TYPE="text/javascript">
<!--

prefix=' ';

{/literal}
{php}
$stuff="";
$stuff2="";
for($i = 0; $i < $newscount; $i++){ 
$stuff2.="\"news.php\",";
if (AAT_strlen($newsmessage[$i])>40){
	$stuff.="\"".AAT_substr($newsmessage[$i],0,40)."...\",";
	}else{
	$stuff.="\"".$newsmessage[$i]."\",";
	}
}
$stuff.="\"End of News\"";
$stuff2.="\"news.php\"";
{/php}
{literal}
arURL = new Array({/literal}{php}echo $stuff2;{/php}{literal});
arTXT = new Array({/literal}{php}echo $stuff;{/php}{literal});

document.write('<LAYER ID=fad1><\/LAYER>');
NS4 = (document.layers);
IE4 = (document.all);

FDRblendInt = 5; // seconds between flips
FDRmaxLoops = 20; // max number of loops (full set of headlines each loop)
FDRendWithFirst = true;

FDRfinite = (FDRmaxLoops > 0);
blendTimer = null;

arTopNews = [];
for (i=0;i<arTXT.length;i++)
{
 arTopNews[arTopNews.length] = arTXT[i];
 arTopNews[arTopNews.length] = arURL[i];
}
TopPrefix = prefix;

if(NS4)
{
	fad1 = document.fad1;
	fad1.visibility="hide";

	pos1 = document.images['pht'];
	pos1E = document.images['ph1E'];
	fad1.left = pos1.x;
	fad1.top = pos1.y;
	fad1.clip.width = 300;
	fad1.clip.height = pos1E.y - fad1.top;
}
else 
{
	document.getElementById('IEfad1').style.pixelHeight = document.getElementById('IEfad1').offsetHeight;
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
		if (NS4)
	{
		origWidth1 = innerWidth;
		origHeight1 = innerHeight;
		window.onresize = FDRredo1;
	}

	TopnewsCount1 = 0;
	TopLoopCount1 = 0;

	FDRdo1();
	blendTimer1 = setInterval("FDRdo1()",FDRblendInt1*1000)
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
				TopnewsStr += "<P><A CLASS=headlines "
							+ "HREF='" + TopPrefix + arTopNews[TopnewsCount+1] + "'>"
							+ arTopNews[TopnewsCount] + "</" + "A></" + "P>"
				TopnewsCount += 2;
			}
		}
		if (NS4) 
		{
			fad1.document.write(TopnewsStr);
			fad1.document.close();
			fad1.visibility="show";
		}
		else 
		{
			document.getElementById('IEfad1').innerHTML = TopnewsStr;
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

window.onload = FDRcountLoads;
//-->
</SCRIPT>
{/literal}
	</td>
    <td><img src="templates/{$templatename}images/topbar-midright.gif" width="12" height="20"></td>
  </tr>
  <tr>
    <td bgcolor="3A3A3A">&nbsp;</td>
    <td bgcolor="3A3A3A" valign="middle" colspan="3">{literal}
<style type="text/css">
/*Credits: Dynamic Drive CSS Library */
/*URL: http://www.dynamicdrive.com/style/ */
.suckertreemenu ul{
	margin: 0;
	padding: 0;
	list-style-type: none;
	z-index: 2000; 
}

/*Top level list items*/
.suckertreemenu ul li{
	position: relative;
	display: inline;
	float: left;
	background-color: #3a3a3a; /*overall menu background color*/
	z-index: 2000; 
}

/*Top level menu link items style*/
.suckertreemenu ul li a{
	display: block;
	width: auto; /*Width of top level menu link items*/
	padding: 3px 15px 3px 10px;
	text-decoration: none;
	color: white;
	font-family: Verdana, Arial, sans-serif;
	font-size: 12px;
}
	
/*1st sub level menu*/
.suckertreemenu ul li ul{
	left: 0;
	position: absolute;
	top: 1em; /* no need to change, as true value set by script */
	display: block;
	visibility: hidden;
}

/*Sub level menu list items (undo style from Top level List Items)*/
.suckertreemenu ul li ul li{
	display: list-item;
	float: none;
}

/*All subsequent sub menu levels offset after 1st level sub menu */
.suckertreemenu ul li ul li ul{ 
	left: auto; /* no need to change, as true value set by script */
	top: 0;
}

/* Sub level menu links style */
.suckertreemenu ul li ul li a{
	display: block;
	width: 160px; /*width of sub menu levels*/
	color: white;
	text-decoration: none;
	padding: 3px 15px 3px 10px;
}

.suckertreemenu ul li a:hover{
	background-color: #000000;
	color: white;
}

/*Background image for top level menu list links */
.suckertreemenu .mainfoldericon{
	background: #3a3a3a url(templates/{/literal}{$templatename}{literal}images/arrow_down.gif) no-repeat center right;
}

/*Background image for subsequent level menu list links */
.suckertreemenu .subfoldericon{
	background: #3a3a3a url(templates/{/literal}{$templatename}{literal}images/arrow_right.gif) no-repeat center right;
}

/* Holly Hack for IE \*/
* html .suckertreemenu ul li { float: left; height: 1%; }
* html .suckertreemenu ul li a { height: 1%; width: 1px;}
* html .suckertreemenu ul li ul li { float: left;}
/* End */

</style>

<script type="text/javascript">

//SuckerTree Horizontal Menu (Sept 14th, 06)
//By Dynamic Drive: http://www.dynamicdrive.com/style/

var menuid="treemenu"

function buildsubmenus_horizontal()
{
	var ultags=document.getElementById(menuid).getElementsByTagName("ul")
	for (var t=0; t<ultags.length; t++)
	{
		if (ultags[t].parentNode.parentNode.id==menuid)
		{ //if this is a first level submenu
			ultags[t].style.top=ultags[t].parentNode.offsetHeight+"px" //dynamically position first level submenus to be height of main menu item
			ultags[t].parentNode.getElementsByTagName("a")[0].className="mainfoldericon"
		}
		else
		{ //else if this is a sub level menu (ul)
			ultags[t].style.left=ultags[t-1].getElementsByTagName("a")[0].offsetWidth+"px" //position menu to the right of menu item that activated it
			ultags[t].parentNode.getElementsByTagName("a")[0].className="subfoldericon"
		}
		ultags[t].parentNode.onmouseover=function()
		{
			this.getElementsByTagName("ul")[0].style.visibility="visible"
		}
		ultags[t].parentNode.onmouseout=function()
		{
			this.getElementsByTagName("ul")[0].style.visibility="hidden"
		}
	}
}

if (window.addEventListener)
	window.addEventListener("load", buildsubmenus_horizontal, false)
else if (window.attachEvent)
	window.attachEvent("onload", buildsubmenus_horizontal)


</script>
{/literal}
<div class="suckertreemenu">
<ul id="treemenu">
	<li><a href="device.php">{$l_device_ports}</a>
		<ul>
			<li><a href="navcomp.php">{$l_navcomp}</a></li>
			<li><a href="beacon.php">{$l_spacebeacon}</a></li>
{if $allow_probes == 1}
			<li><a href="probes.php?command=drop">{$l_spaceprobes}</a></li>
{/if}
			<li><a href="warpedit.php">{$l_warpeditors}</a></li>
			<li><a href="genesis.php">{$l_genesistorps}</a></li>
			<li><a href="sectorgenesis.php">{$l_sgtorps}</a></li>
			<li><a href="defense_deploy.php">{$l_minesfighters}</a></li>
			<li><a href="emerwarp.php">{$l_ewarp}</a></li>
		</ul>
	</li>
	<li><a href="report.php">{$l_reports}</a>
		<ul>
			<li><a href="report.php">{$l_shipinfo}</a></li>
			<li><a href="ranking.php">{$l_rankings}</a></li>
			<li><a href="igb.php">IGB</a></li>
			<li><a href="planet_report.php">{$planets}</a>
			<ul>
				<li><a href="planet_report.php?PRepType=1">{$l_planetstatus}</a></li>
				<li><a href="planet_report.php?PRepType=3">{$l_planetdefenses}</a></li>
				<li><a href="planet_report.php?PRepType=2">{$l_changeproduction}</a></li>
			</ul>
			</li>
			<li><a href="stored_ship_report.php">{$l_storedshipreport}</a></li>
{if $enable_spies == 1}
			<li><a href="spy.php">{$l_spy}</a></li>
{/if}
{if $enable_dignitaries == 1}
			<li><a href="dig.php">{$l_dig}</a></li>
{/if}
{if $allow_probes == 1}
			<li><a href="probes.php">{$l_probe}</a></li>
{/if}
			<li><a href="autotrades.php">{$l_autotrade}</a></li>
			<li><a href="defense_report.php">{$l_sector_def}</a></li>
			<li><a href="sector_notes.php">{$l_sectornotes}</a></li>
			<li><a href="log.php">{$l_log}</a></li>
		</ul>
	</li>
	<li><a href="#">{$l_maps}</a>
		<ul>
			<li><a href="galaxy_map.php">{$l_map}</a></li>
			<li><a href="galaxy_local.php">{$l_localmap}</a></li>
{if $galaxy_map_enabled == true and $gd_enabled == true and $enable_spiral_galaxy == 1}
			<li><a href="galaxy_map3d.php">{$l_3dmap}</a></li>
{/if}
		</ul>
	</li>
	<li><a href="#">{$l_teams}</a>
		<ul>
			<li><a href="teams.php">{$l_teams}</a></li>
{if $team_id != 0}
			<li><a href="team_forum.php?command=showtopics">{$l_teamforum} - New:{$newposts}</a></li>
			<li><a href="team_report.php">{$l_teamships}</a></li>
			<li><a href="team_defenses.php">{$l_teamdefenses}</a></li>
			<li><a href="team_defense_report.php">{$l_teams} {$l_sector_def}</a></li>
			<li><a href="team_planets.php">{$l_teamplanets}</a></li>
			<li><a href="shoutbox_team.php" target="team_shoutbox">{$l_team_shoutbox}</a></li>
{/if}
		</ul>
	</li>
	<li><a href="#">{$l_messages}</a>
		<ul>
			<li><a href="message_read.php">{$l_read_msg}</a></li>
			<li><a href="message_send.php">{$l_send_msg}</a></li>
			<li><a href="messageblockmanager.php">{$l_block_msg}</a></li>
			<li><a href="main.php?lobby_mode=start">{$l_lobby}</a></li>
		</ul>
	</li>
	<li><a href="options.php">{$l_options}</a>
		<ul>
			<li><a href="options.php">{$l_options}</a></li>
			<li><a href="self_destruct.php">{$l_ohno}</a></li>
		</ul>
	</li>
	<li><a href="#">{$l_help}</a>
		<ul>
			<li><a href="#">Hotkey Help #1</a>
				<ul>
					<li><a href="#">The following Hotkeys will execute the following commands:</a></li>
					<li><a href="#"></a></li>
					<li><a href="#">a = Add a traderoutes</a></li>
					<li><a href="#">B = Beacon</a></li>
					<li><a href="#">c = Genesis Device</a></li>
					<li><a href="#">C = Sector Genesis</a></li>
					<li><a href="#">D = Device Menu</a></li>
					<li><a href="#">d = Sector defense Report</a></li>
					<li><a href="#">e = Emergency Warp</a></li>
					<li><a href="#">f = Full Long Range Scan</a></li>
					<li><a href="#">g = Galaxy Map</a></li>
					<li><a href="#">G = Local Galaxy Map</a></li>
				</ul>
			</li>
			<li><a href="#">Hotkey Help #2</a>
				<ul>
					<li><a href="#">The following Hotkeys will execute the following commands:</a></li>
					<li><a href="#"></a></li>
					<li><a href="#">i = IGB</a></li>
					<li><a href="#">l = Log</a></li>
					<li><a href="#">L = Logout</a></li>
					<li><a href="#">m = Read Messages</a></li>
					<li><a href="#">M = Deploy Mines</a></li>
					<li><a href="#">n = News</a></li>
					<li><a href="#">N = Sector Notes</a></li>
					<li><a href="#">o = Options</a></li>
					<li><a href="#">p = Planet Report</a></li>
					<li><a href="#">P = Probe Menu</a></li>
					<li><a href="#">r = Rankings</a></li>
				</ul>
			</li>
			<li><a href="#">Hotkey Help #3</a>
				<ul>
					<li><a href="#">The following Hotkeys will execute the following commands:</a></li>
					<li><a href="#"></a></li>
					<li><a href="#">R = Ship Report</a></li>
					<li><a href="#">s = Send Message</a></li>
					<li><a href="#">t = List Trade Routes</a></li>
					<li><a href="#">T = Team Sector defenses</a></li>
					<li><a href="#">u = 3D Galaxy Map</a></li>
					<li><a href="#">w = Warp Editor</a></li>
					<li><a href="#">z = Stored Ship Report</a></li>
					<li><a href="#">[ = Dignitary Menu</a></li>
					<li><a href="#">] = Spy Menu<br></a></li>
					<li><a href="#">. = Galaxy Local (new window)<br></a></li>
				</ul>
			</li>
			<li><a href="feedback.php" target="_blank">{$l_feedback}</a></li>
			<li><a href="{$forum_link}" target="_blank"">{$l_forums}</a></li>
			<li><a href="http://www.aatraders.com" target="_blank">Profiles</a></li>
		</ul>
	</li>
{if $newcommands != 0}
	<li><a href="#">{$l_commands}</a>
		<ul>
			{for start=0 stop=$newcommands step=1 value=current}
				<li><a href="{$newcommandlink[$current]}">{$newcommandname[$current]}</a></li>
			{/for}
		</ul>
	</li>
{/if}
{if $tournament_mode == 0}
	<li><a href="logout.php">{$l_logout}</a>
		<ul>
			<li><a href="logout.php">{$l_logout}</a></li>
		</ul>
	</li>
{/if}
</ul>
</div>
</td>
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

    <td bgcolor="3A3A3A" valign="middle" align="right">{$l_shiptype}:<a href="report.php"><b>{$classname}</b></a></td>
    <td bgcolor="3A3A3A"></td>
	
	
  </tr>

</table>
<table width="100%" cellpadding=0 cellspacing=0 border=0 align=center>

<tr>
    <td width="31" height="15" ><img src="templates/{$templatename}images/topbar-ll.gif" width="31" height="15"></td>
    <td background="templates/{$templatename}images/topbar-low-bg.gif" colspan="3">&nbsp;</td>
    <td width="12" height="15"><img src="templates/{$templatename}images/topbar-lr.gif" width="12" height="15"></td>
  </tr>
</table>
<div style="background: no-repeat top  right url({php}

$startypes[0] = "templates/" . $templatename . "images/spacer.gif";
$startypes[1] = "templates/" . $templatename . "images/redstar.gif";
$startypes[2] = "templates/" . $templatename . "images/orangestar.gif";
$startypes[3] = "templates/" . $templatename . "images/yellowstar.gif";
$startypes[4] = "templates/" . $templatename . "images/greenstar.gif";
$startypes[5] = "templates/" . $templatename . "images/bluestar.gif";
 echo  $startypes[$starsize]; {/php}) ;vertical-align: top; text-align: left; /*border: 1px solid white;*/">
<table width="100%" cellpadding=0 cellspacing=0 border=0 align=center>
<tr>
<td>&nbsp;</td>
<td>
<font color="silver" size=2 face="arial">&nbsp;{if $sg_sector}
SG&nbsp;
{/if}{$l_sector}: </font><font color="white"><b>{$sector}</b></font><br>
{$l_planetmax} <b>{$starsize}</b><br><span class=mnu>{$ship_coordinates}</span>
</td><td align=center>
<font color="white" size="2" face="arial"><b>{$beacon}</b></font>
</td><td align=right>
<a href="zoneinfo.php"><b><font size=2 face="arial">{$zonename}</font></b></a>&nbsp;</td>
<td>&nbsp;</td>
</tr>
</table>
<table width="100%" border=0 align=center cellpadding=0 cellspacing=0>

<tr>
<td valign=top>

<table border="0" cellpadding="0" cellspacing="0" align="left"><tr valign="top">
<td>
<tr><td>
<table width="195" border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-lt1.gif" width="23" height="13"></td>
    <td align="right" background="templates/{$templatename}images/b-tbar-bg.gif"><img src="templates/{$templatename}images/b-tbar-cnt.gif" width="143" height="13"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rt.gif" width="29" height="13"></td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-ls.gif" width="23" height="21"></td>
    <td bgcolor="#000000"><img src="templates/{$templatename}images/spacer.gif" width="143" height="21"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rs.gif" width="29" height="21"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/b-lbar-bg.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0"><TR align="center"><TD NOWRAP>
{if $avatar != "default_avatar.gif"}
<p align="center"><img src="images/avatars/{$avatar}"></p>
		{/if}
</td></tr>
<tr><td class=normal>{$l_rank}: <img src="templates/{$templatename}images/rank/{$insignia}"></td></tr>
<tr><td class=normal>{$l_name}: <span class=mnu>{$player_name}</font></span></td></tr>
<tr><td class=normal>{$l_ship} {$l_name}:<span class=mnu><a href="report.php">{$shipname}</a></span></td></tr>
<tr><td class=normal>{$l_shiptype}:<span class=mnu>{$classname}</span></td></tr>
<tr><td class=normal>{$l_turns_have}<span class=mnu>{$turns}</span></td></tr>
<tr><td class=normal>{$l_turns_used}<span class=mnu>{$turnsused}</span></td></tr>
<tr><td class=normal>{$l_score}<span class=mnu>{php}
echo strip_places($score);
{/php}
</span></td></tr>
<tr><td class=normal>{$l_home_planet}: <span class=mnu>{$home_planet_name}</span></td></tr>
</table>
</td>
    <td background="templates/{$templatename}images/b-rbar.gif">&nbsp;</td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-bar-ls_01.gif" width="23" height="12"></td>
    <td background="templates/{$templatename}images/b-bar-bg.gif"></td>
    <td><img src="templates/{$templatename}images/b-bar-rs_03.gif" width="29" height="12"></td>
  </tr>
</table>
</td></tr>
<tr><td><br>

		
<table width="195" border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-lt1.gif" width="23" height="13"></td>
    <td align="right" background="templates/{$templatename}images/b-tbar-bg.gif"><img src="templates/{$templatename}images/b-tbar-cnt.gif" width="143" height="13"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rt.gif" width="29" height="13"></td>
  </tr>

  <tr>
    <td background="templates/{$templatename}images/b-lbar-bg.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0"><TR align="center"><TD NOWRAP><img src="templates/{$templatename}images/spacer.gif" width="165" height="1">
<table border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" width="100%" ><table cellspacing = "0" cellpadding = "0" border = "0" width="100%" >
<tr><td align="left" colspan=2><span class=mnu>&nbsp;&nbsp;&nbsp;{$l_cargo}</span><br><br></td></tr>
{if $cargo_items > 0}
{php}
	for($i = 0; $i < $cargo_items; $i++)
	{
		if ($cargo_amount[$i] != "0")
		{
			echo "<tr><td width=\"50%\" nowrap align='left' class=normal><img height=12 width=12 alt=\"$cargo_name[$i]\" src=\"images/ports/" . $cargo_name[$i] . ".png\">&nbsp;" . ucfirst($cargo_name[$i]) . "</td><td width=\"50%\" nowrap align='right'><span class=mnu>&nbsp;";
            echo strip_places($cargo_amount[$i]);
			
			echo "</span></td></tr>";
		}
	}
{/php}
{/if}

{if $shipinfo_energy != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_energy}" src="templates/{$templatename}images/energy.png">&nbsp;{$l_energy}</td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
echo strip_places($shipinfo_energy);
{/php}
</span></td></tr>
{/if}

{if $shipinfo_fighters != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_fighters}" src="templates/{$templatename}images/tfighter.png">&nbsp;<a href=defense_deploy.php>{$l_fighters}</a></td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
echo strip_places($shipinfo_fighters);
{/php}
</span></td></tr>
{/if}

{if $shipinfo_torps != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_torps}" src="templates/{$templatename}images/torp.png">&nbsp;<a href=defense_deploy.php>{$l_torps}</a></td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
echo strip_places($shipinfo_torps);
{/php}
</span></td></tr>
{/if}

{if $shipinfo_armor != "0"}
<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_armorpts}" src="templates/{$templatename}images/armor.png">&nbsp;{$l_armor}</td><td width="50%" nowrap align='right'><span class=mnu>&nbsp;
{php}
echo strip_places($shipinfo_armor);
{/php}
</span></td></tr>
{/if}

<tr><td width="50%" nowrap align='left' class=normal><img height=12 width=12 alt="{$l_credits}" src="templates/{$templatename}images/credits.png">&nbsp;{$l_credits}</td><td width="50%" nowrap align='right' colspan=2><span class=mnu>&nbsp;
{php}
echo strip_places($playerinfo_credits);
{/php}
</span></td></tr>
	
	</td></tr></table>
</td>
  </tr>
</table>



</td></tr></table>
</td>
    <td background="templates/{$templatename}images/b-rbar.gif">&nbsp;</td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-bar-ls_01.gif" width="23" height="12"></td>
    <td background="templates/{$templatename}images/b-bar-bg.gif"></td>
    <td><img src="templates/{$templatename}images/b-bar-rs_03.gif" width="29" height="12"></td>
  </tr>
</table>
</td></tr>
<tr><td><br>
				
<table width="195" border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-lt1.gif" width="23" height="13"></td>
    <td align="right" background="templates/{$templatename}images/b-tbar-bg.gif"><img src="templates/{$templatename}images/b-tbar-cnt.gif" width="143" height="13"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rt.gif" width="29" height="13"></td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-ls.gif" width="23" height="21"></td>
    <td bgcolor="#000000"><img src="templates/{$templatename}images/b-tbar-tr-title.gif" width="143" height="21"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rs.gif" width="29" height="21"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/b-lbar-bg.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0"><TR align="center"><TD NOWRAP>

{if $num_traderoutes == 0}
<TR><TD NOWRAP>
<div class=mnu><center><div class=dis>&nbsp;{$l_none} &nbsp;</div></center><br>
</div>
</td></tr>
{elseif $num_traderoutes == 1}
{php}
echo "<tr><td class=\"nav_title_12\">&nbsp;<a class=mnu href=traderoute_engage.php?engage=" . $traderoute_links[0] . ">" . $traderoute_display[0] . "</a><br>&nbsp;</td><tr>";
{/php}
{else}
{php}
	echo "<tr><td class=\"nav_title_12\" align=center>\n";
	echo "<form name=\"traderoutes\"><select name=\"menu\" onChange=\"location=document.traderoutes.menu.options[document.traderoutes.menu.selectedIndex].value;\" value=\"GO\" class=\"rsform\"><option value=\"\">Select Traderoute</option>\n";
	for($i = 0; $i < count($traderoute_links); $i++){
		echo "<option value=\"traderoute_engage.php?engage=" . $traderoute_links[$i] . "\">$traderoute_display[$i]</option>\n";
	}
	echo "</select></form>";
	echo "</td></tr>\n";
{/php}

{/if}
<tr><td nowrap align="center">
<div class=mnu>
[<a class=mnu href=traderoute_create.php>{$l_add}</a>]&nbsp;&nbsp;<a class=mnu href=traderoute_listroutes.php>{$l_trade_control}</a>&nbsp;<br>

</div></td></tr></table>
</td>
    <td background="templates/{$templatename}images/b-rbar.gif">&nbsp;</td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-bar-ls_01.gif" width="23" height="12"></td>
    <td background="templates/{$templatename}images/b-bar-bg.gif"></td>
    <td><img src="templates/{$templatename}images/b-bar-rs_03.gif" width="29" height="12"></td>
  </tr>
</table>
</td></tr>

<tr><td><br><table  border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-lt1.gif" width="23" height="13"></td>
    <td align="right" background="templates/{$templatename}images/b-tbar-bg.gif"><img src="templates/{$templatename}images/b-tbar-cnt.gif" width="143" height="13"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rt.gif" width="29" height="13"></td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-ls.gif" width="23" height="21"></td>
    <td bgcolor="#000000"><img src="templates/{$templatename}images/b-tbar-sbtitle.gif" width="143" height="21"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rs.gif" width="29" height="21"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/b-lbar-bg.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center"><table cellpadding="0" align="left" cellspacing="0"><tr></tr>
	<form method="post" action="shoutbox_save.php">
	<input type="Hidden" name="" value="1"><td NOWRAP class="shoutform">
	<textarea class="shoutform" wrap cols="26" rows="3">{$quickshout}</textarea><br>
	<input type="Text" name="sbt"  class="shoutform" size="20" maxlength="250" ONBLUR="document.onkeypress = getKey;" ONFOCUS="document.onkeypress = null;" ><input type="submit" name="go" value="Go" class="shoutform"><br>Public?&nbsp;
	<input type="Hidden" name="returntomain" value="1">
{if $team_id > 0}
	<INPUT TYPE=CHECKBOX NAME=SBPB class="shoutform" >
{else}
	<INPUT TYPE=CHECKBOX NAME=SBPB class="shoutform" checked>
{/if}
</td></form></tr></table>
	</td>
    <td background="templates/{$templatename}images/b-rbar.gif">&nbsp;</td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-bar-ls_01.gif" width="23" height="12"></td>
    <td background="templates/{$templatename}images/b-bar-bg.gif"></td>
    <td><img src="templates/{$templatename}images/b-bar-rs_03.gif" width="29" height="12"></td>
  </tr>
</table>
</td></tr>

</table>
</td>

<td valign=top align="center">
&nbsp;<br>

<center><font size=3 face="arial" color="white"><b>{$l_tradingport}:</b></font></center>
<table border=0 width="100%" align="center">
<tr align="center"><td>
<a href=port.php><img src="images/ports/port_{$port_type}.gif" border="0" alt=""><br></a>{$portname}
</td>
	{if $sector_location == 1}
		<td><a href="casino.php?casinogame=casino_forums"><img src="images/ports/port_fedinfo.gif" border="0" alt=""></a><br><br><b><font color=#33ff00>{$l_fedinfo}</font></b></td>
	{/if}
</tr>
</table>

<center><b><font size=3 face="arial" color="white">{$l_planet_in_sec} {$sector}:</font></b></center>
<table border=0 width="100%" align="center">
<tr align="center">

{if $countplanet != 0}
{ for start=0 stop=$countplanet step=1 value=i }
	<td align=center valign=top>
	<A HREF=planet.php?planet_id={$planetid[$i]}>
		<img src="templates/{$templatename}images/planet{$planetimg[$i]}.png" alt="" width="100" height="100">
 
	<BR><font size=2 color="white" face="arial">
	{$planetname[$i]}
	<br>({$planetowner[$i]})
				<br>{if $planetratingnumber[$i] == -1}
					<font color="red">{$planetrating[$i]}</font>
					{elseif $planetratingnumber[$i] == 0}
					<font color="yellow">{$planetrating[$i]}</font>
					{else}
					<font color="lime">{$planetrating[$i]}</font>
					{/if}
	</font></td>
{/for}
{else}
		<td valign=top><font color="white" size=2>{$l_none}</font></td>
{/if}

</tr>
</table>

<center><b><font size=3 face="arial" color="white"><br>{$l_ships_in_sec} {$sector}:</font><br></b></center>
<table border=0 width="100%">
<tr align="center">

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

{if $sectorzero != 1}
<table border=0 width="100%">
<tr>
	{if $lss_sensorlevel == 0}
		<td valign="top" align="center"><b><font size=3 face="arial" color="white">{$l_lss}:</font></b><br><span class=mnu><font color=#33ff00>{$lss_playername}</font></span></td>
	{/if}
	{if $lss_sensorlevel == 3}
		<td valign="top" align="center"><b><font size=3 face="arial" color="white">{$l_lss}:</font></b><br><span class=mnu><font color=cyan>{$lss_playername}</font>(<font color=#33ff00>{$lss_shipclass}</font>) <font color=#52ACEA>{$l_traveled}</font> <font color=yellow><a class="mnu" href="main.php?move_method=real&engage=1&destination={$lss_destination|urlencode}">{$lss_destination}</a></font></span></td>
	{/if}
	{if $lss_sensorlevel == 2}
		<td valign="top" align="center"><b><font size=3 face="arial" color="white">{$l_lss}:</font></b><br><span class=mnu><font color=cyan>{$lss_playername}</font>(<font color=#33ff00>{$lss_shipclass}</font>)</span></td>
	{/if}
	{if $lss_sensorlevel == 1}
		<td valign="top" align="center"><b><font size=3 face="arial" color="white">{$l_lss}:</font></b><br><span class=mnu><font color=cyan>{$lss_playername}</font>(<font color=#33ff00>{$lss_shipclass}</font>)</span></td>
	{/if}
</tr>
</table>
{/if}

<center><b><font size=3 face="arial" color="white"><br><br>{$l_sector_def}:</font><br></b></center>
<table border=0 width="100%"><tr>
{php}
	$count = 0;
	for($i = 0; $i < $defensecount; $i++){
		if($defensetype[$i] == "fighters"){
			if($count == 0){
				echo "<td align=center valign=top><img src=templates/" . $templatename . "images/fighters.gif><br>";
			}
			echo "<font class=normal>";
			echo "<a class=mnu href=defense_modify.php?defense_id=" . $defenseid[$i] . ">";
			echo $defplayername[$i];
			echo "</a><br>";
			echo " (<font color=yellow>".strip_places($defenseqty[$i])."</font> <font color=#33ff00>$defensemode[$i]</font>)";
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
			echo "<a class=mnu href=defense_modify.php?defense_id=" . $defenseid[$i] . ">";
			echo $defplayername[$i];
			echo "</a><br>";
			echo " (<font color=yellow>".strip_places($defenseqty[$i])."</font> <font color=#33ff00>$defensemode[$i]</font>)";
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


</tr></table>
<td valign=top>
<br>
				
				
<table  border="0" cellspacing="0" cellpadding="0" align="right">


<tr><td><table width="195" border="0" cellspacing="0" cellpadding="0" align="right">
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-lt1.gif" width="23" height="13"></td>
    <td align="right" background="templates/{$templatename}images/b-tbar-bg.gif"><img src="templates/{$templatename}images/b-tbar-cnt.gif" width="143" height="13"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rt.gif" width="29" height="13"></td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-ls.gif" width="23" height="21"></td>
    <td bgcolor="#000000"><img src="templates/{$templatename}images/b-tbar-rstitle.gif" width="143" height="21"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rs.gif" width="29" height="21"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/b-lbar-bg.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center"><table cellspacing = "0" cellpadding = "0" border = "0"><TR align="center"><TD NOWRAP><div id="ToolTip"></div>
{if $gd_enabled}
<table align="center"><tr><td align="center" valign="top"><a href="galaxy_map3d.php">{php}
 $coords = explode("|", $ship_coordinates); 
echo "
<img align=\"middle\" src=\"galaxy_position.php?universe_size=$universe_size&sx=$coords[0]&sy=$coords[1]&sz=$coords[2]\" border=\"0\" >";
{/php}</a>

</td></tr></table>
{/if}
<table border="0" cellspacing="0" cellpadding="0" align="center"  style="border: thin inset #444444;"><tr><td>
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
</td></tr></table><br></td></tr>
<TR align="center"><TD NOWRAP><div class=mnu align=center>{$l_sector} {$sector} {$l_notes}<br>
{php}
if ($note_view != 0){
	echo "<a class=dis href=\"sector_notes.php?command=viewnote\">[".$l_view_note."]</a>";
}
echo "<a class=dis href=\"sector_notes.php?command=addnote&sector=".$sector."&sector_planets=".count($planetid)."&sector_port=".$portname."&sector_fighters=".$tmp_fighters."&sector_torps=".$tmp_torps."\">[".$l_add_note."]</a>";
{/php}
<br><br>
</div></td></tr>
<tr><td nowrap=""><div class=mnu>
<TABLE BORDER=0 CELLPADDING=1 CELLSPACING=0 BGCOLOR="#000000" >
<form name="lastsector"><tr><td class="nav_title_12" align=center>
<select name="menu" onChange="location=document.lastsector.menu.options[document.lastsector.menu.selectedIndex].value;" value="GO" class="rsform"><option value="">RS to Last Sector</option>
{if $lastsectors[0] != ""}
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[0]|urlencode}">{$lastsectors[0]}({$lastsectorsdist[0]})</option>
{/if}
{if $lastsectors[1] != ""}
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[1]|urlencode}">{$lastsectors[1]}({$lastsectorsdist[1]})</option>
{/if}
{if $lastsectors[2] != ""}
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[2]|urlencode}">{$lastsectors[2]}({$lastsectorsdist[2]})</option>
{/if}
{if $lastsectors[3] != ""}
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[3]|urlencode}">{$lastsectors[3]}({$lastsectorsdist[3]})</option>
{/if}
{if $lastsectors[4] != ""}
<option value="main.php?move_method=real&engage=1&destination={$lastsectors[4]|urlencode}">{$lastsectors[4]}({$lastsectorsdist[4]})</option>
{/if}
</select></form></td></tr>

{php}
	echo "<form name=\"presets\"><tr><td class=\"nav_title_12\" align=center>\n";
	echo "<select  name=\"menu\" onChange=\"location=document.presets.menu.options[document.presets.menu.selectedIndex].value;\" value=\"GO\" class=\"rsform\"><option value=\"\">RS to Sector</option>\n";
	for($i = 0; $i < count($preset_display); $i++){
		echo "<option value=\"main.php?move_method=real&engage=1&amp;destination=" . urlencode($preset_display[$i]) . "\">$preset_display[$i] - $preset_info[$i] ($preset_dist[$i])</option>\n";
	}
	echo "</select></td></tr>\n";
	
{/php}

<tr><td class="nav_title_12" align=center>&nbsp;<a class=dis href="preset.php?name=set">[{$l_set}]</a>&nbsp;&nbsp;-&nbsp;&nbsp;<a class=dis href="preset.php?name=add">[{$l_add}]</a>&nbsp;</td></tr></form>
<form method="post" action="main.php"><input type="hidden" name="move_method" value="real"><tr><td class="nav_title_12" align=center>

<input type="text" name="destination" class="rsform" maxlength="30" size="8" onfocus="document.onkeypress=null" ONBLUR="document.onkeypress = getKey;" ><br>
<input type="submit" name="explore" value="&nbsp;?&nbsp;" class="rsform">
<input type="submit" name="go" value="Go" class="rsform">
</td></tr></form>
</table></td></tr></table></td>
    <td background="templates/{$templatename}images/b-rbar.gif">&nbsp;</td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-bar-ls_01.gif" width="23" height="12"></td>
    <td background="templates/{$templatename}images/b-bar-bg.gif"></td>
    <td><img src="templates/{$templatename}images/b-bar-rs_03.gif" width="29" height="12"></td>
  </tr>
</table>
</td></tr>


<tr><td><br>
<table  border="0" cellspacing="0" cellpadding="0" align="left">
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-lt1.gif" width="23" height="13"></td>
    <td align="right" background="templates/{$templatename}images/b-tbar-bg.gif"><img src="templates/{$templatename}images/b-tbar-cnt.gif" width="143" height="13"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rt.gif" width="29" height="13"></td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-tbar-ls.gif" width="23" height="21"></td>
    <td bgcolor="#000000"><img src="templates/{$templatename}images/b-tbar-wttitle.gif" width="143" height="21"></td>
    <td><img src="templates/{$templatename}images/b-tbar-rs.gif" width="29" height="21"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/b-lbar-bg.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center"><table cellpadding="0" align="left" cellspacing="0"><tr><td NOWRAP>
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
	echo "<tr><td width=100 class=\"nav_title_12\" align=center><br>\n";
	echo "<form name=\"autoroutes\"><select name=\"menu\" onChange=\"location=document.autoroutes.menu.options[document.autoroutes.menu.selectedIndex].value;\" value=\"GO\" class=\"rsform\"><option value=\"\">Select Autoroute</option>\n";
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
	echo "</select></form>";
	echo "</td></tr>\n";
{/php}

</td></tr>
</table>
{/if}</td></tr></table>
	</td>
    <td background="templates/{$templatename}images/b-rbar.gif">&nbsp;</td>
  </tr>
  <tr>
    <td><img src="templates/{$templatename}images/b-bar-ls_01.gif" width="23" height="12"></td>
    <td background="templates/{$templatename}images/b-bar-bg.gif"></td>
    <td><img src="templates/{$templatename}images/b-bar-rs_03.gif" width="29" height="12"></td>
  </tr>
</table>
</td></tr>

</table>
<center>
				</tr>
				</table>
			
</center>

