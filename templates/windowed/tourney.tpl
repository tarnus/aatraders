{if $new_posts > 0} 
	{literal}
	<style type="text/css">
	#frame_infoport_message {
		z-index: 850;
		position:absolute;
		left: 50%; 
		top: 25%;
		width: 300px;
		height: 100px;
		margin-top: -75px; /* half of the height */
		margin-left: -100px; /* half of the width */
		height:100px;
	}
	input.instant_infoport_button
	{
		font-family:Arial,sans-serif;
		font-weight:bold;
		color:#FFFFFF;
		background-color:#00CC33;
		border-style:outset;
	}
	</style>

	<script language="javascript">
	function infoportgoLite_message(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#00FF99";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "inset";
	}

	function infoportgoDim_message(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#00CC33";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "outset";
	}
	</script>
	{/literal}

	<div id="frame_infoport_message" style="position:absolute;border:10px inset #925725;color:white;background:black;">
	<table border=0 width="100%" align="center">
	<tr>
		<td bgcolor="#528768" width="100%" height="96" align="center" valign="middle">
			<b>{$l_forums_new} {$forumname}
				<hr>
				{for start=0 stop=$count step=1 value=current}
					{if $newpost[$current] > 0}
						<a href="infoport.php?topic_id={$topicid[$current]}#{$postid[$current]}" target="_blank">{$topictitle[$current]}</a><br>
					{/if}
				{/for}
			<b><br><br>
			<form name="template_change_later">
			<input
				type="button"
				name="instant_infoport_btn1"
				class="instant_infoport_button"
				value="Read Later"
				title="Read Later"
				onMouseOver="infoportgoLite_message(this.form.name,this.name)"
				onMouseOut="infoportgoDim_message(this.form.name,this.name)"
				onClick="frame_infoport_message.style.visibility = 'hidden';"
				>
			</form>
			<br>
		</td>
	</tr>
	</table>
	</div>
{/if}


{literal}
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
	background-color: #4455aa; /*overall menu background color*/
	z-index: 800; 
}

/*Top level menu link items style*/
.suckertreemenu ul li a{
	display: block;
	width: auto; /*Width of top level menu link items*/
	padding: 3px 15px 3px 10px;
	border: 1px solid #dddddd;
	border-left-width: 1;
	text-decoration: none;
	color: white;
	font-weight: bold;
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
	border: 1px solid #dddddd;
}

.suckertreemenu ul li a:hover{
	background-color: #000000;
	color: white;
}

/*Background image for top level menu list links */
.suckertreemenu .mainfoldericon{
	background: #4455aa url(templates/{/literal}{$templatename}{literal}images/arrow_down.gif) no-repeat center right;
}

/*Background image for subsequent level menu list links */
.suckertreemenu .subfoldericon{
	background: #4455aa url(templates/{/literal}{$templatename}{literal}images/arrow_right.gif) no-repeat center right;
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

<table cellspacing = "0" cellpadding = "0" border = "0" width = "700" align="center">
<tr>
	<td><img src="templates/{$templatename}images/topnav-left.gif" width="41" height="55"></td>
	<td background="templates/{$templatename}images/topnav-bg.gif" width="100%" height="55" ID="IEshout" align="center">
<layer id="shout"</layer>
	</td>
	<td><img src="templates/{$templatename}images/topnav-right.gif" width="22" height="55"></td>
</tr>
</table>

<br>

<table width="700" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2 align="center">


		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%" align="center">
<tr><td align="center">
<div class="suckertreemenu" align="center">
<ul id="treemenu">
	{if $lobby_mode == 1}
		<li><a href="main.php?lobby_mode=end">{$l_main_title}</a>
			<ul>
				<li><a href="main.php?lobby_mode=end">{$l_main_title}</a></li>
				<li><a href="main.php?lobby_mode=end" target="_blank">{$l_main_title} in New Window</a></li>
			</ul>
		</li>
	{/if}
	<li><a href="ranking.php">{$l_rankings}</a></li>
	<li><a href="log.php">{$l_log}</a></li>
	{if $galaxy_map_enabled == true and $gd_enabled == true and $enable_spiral_galaxy == 1}
	<li><a href="#">{$l_maps}</a>
		<ul>
			<li><a href="galaxy_map3d.php">{$l_3dmap}</a></li>
		</ul>
	</li>
	{/if}
	<li><a href="#">{$l_teams}</a>
		<ul>
			<li><a href="teams.php">{$l_teams}</a></li>
{if $team_id != 0}
			<li><a href="team_forum.php?command=showtopics">{$l_teamforum} - New:{$newposts}</a></li>
			<li><a href="team_report.php">{$l_teamships}</a></li>
			<li><a href="shoutbox_team.php" target="team_shoutbox">{$l_team_shoutbox}</a></li>
{/if}
		</ul>
	</li>
	<li><a href="#">{$l_messages}</a>
		<ul>
			<li><a href="#">{$forumname}</a>
				<ul>
				{for start=0 stop=$count step=1 value=current}
					<li><a href="infoport.php?topic_id={$topicid[$current]}#{$postid[$current]}" target="_blank">{if $newpost[$current] > 0}
							<font color="lime">*</font>
						{/if}
						{$topictitle[$current]}</a></li>
				{/for}
				</ul>
			</li>
			<li><a href="message_read.php">{$l_read_msg}</a></li>
			<li><a href="message_send.php">{$l_send_msg}</a></li>
			<li><a href="messageblockmanager.php">{$l_block_msg}</a></li>
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
					<li><a href="#">b = Global Chat</a></li>
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
	<li><a href="logout.php">{$l_logout}</a>
		<ul>
			<li><a href="logout.php">{$l_logout}</a></li>
		</ul>
	</li>
</ul>
</div>

</td></tr>
		</table>
<br>

<table border=0 align=center cellpadding=0 cellspacing=0>
<tr>
<td valign=top align="right">
		{if $avatar != "default_avatar.gif"}
			<table BORDER=1 CELLPADDING=0 CELLSPACING=0 align="center">
			<tr><td>
			<img src="images/avatars/{$avatar}">
			</td></tr></table>
		{/if}
		{if $teamicon != "default_icon.gif"}
			</td><td align="center">&nbsp;&nbsp;<=-=>&nbsp;&nbsp;</td><td align="left">
			<table BORDER=1 CELLPADDING=0 CELLSPACING=0 align="center">
			<tr><td>
			<img src="images/icons/{$teamicon}">
			</td></tr></table>
		{/if}
</td></tr></table>
<table cellspacing = "0" cellpadding = "0" border = "0" width = "650" align="center">
<tr>
	<td width="100%" align="center">
   <font color="silver" size=3 face="arial"><img src="templates/{$templatename}images/rank/{$insignia}" height="18">
	<b>
	 <font color="white">{$player_name}
	 </font>
	</b>
   </font>
  <font color=silver size=3 face=arial>
  {$l_abord}
   <b>
	<font color="white">
	 <a href="report.php">{$shipname}</a> ({$classname})
	</font>
   </b></font></td>
</tr>
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


<table width="170" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>

<table cellspacing = "0" cellpadding = "0" border = "0" width = "600" align="center">
<tr>
	<td>
<iframe width="600px" height="300px" style="width:600px;height:300px" name="view1" src="global_chat.php"></iframe>

</td>
</tr>
</table>	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>

{php}
	if($_SESSION['team_id']>0)
{
{/php}
<table width="170" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>

<table cellspacing = "0" cellpadding = "0" border = "0" width = "600" align="center">
<tr>
	<td>
<iframe width="600px" height="300px" style="width:600px;height:300px" name="view2" src="team_chat.php"></iframe>

</td>
</tr>
</table>	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
{php}
}
{/php}
<table cellspacing = "0" cellpadding = "0" border = "0" width = "600" align="center">
<tr>
	<td><img src="templates/{$templatename}images/topnav-left.gif" width="41" height="55"></td>
	<td background="templates/{$templatename}images/topnav-bg.gif" width="100%" height="55" ID="IEnews" align="center">
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
	<td><img src="templates/{$templatename}images/topnav-right.gif" width="22" height="55"></td>
</tr>
</table>
