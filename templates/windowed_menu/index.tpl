<body bgcolor="#000000" text="darkred" marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 link="#52ACEA" vlink="#52ACEA" alink="#52ACEA">
{literal}
<style type="text/css">

#dhtmltooltip{
position: absolute;
width: 150px;
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

var offsetxpoint=30 //Customize x offset of tooltip
var offsetypoint=0 //Customize y offset of tooltip

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
	ContentInfo = '<table border="0" width="150" cellspacing="0" cellpadding="0">'+
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
{/literal}

<table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
<tr>
	<td align="center">
{literal}
<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="650" height="300" id="3D Solar System" align="middle">
<param name="allowScriptAccess" value="sameDomain" />
<param name="movie" value="templates/{/literal}{$templatename}{literal}images/aat-title.swf" />
<param name="quality" value="high" />
<param name="bgcolor" value="#000000" />
<embed src="templates/{/literal}{$templatename}{literal}images/aat-title.swf" quality="high" bgcolor="#000000" width="650" height="300" name="3D Solar System" align="middle" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />
</object>
{/literal}
	</td>
</tr>

		</table>

	
		<table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
		<tr>
<td><p align="center">

	
    <td colspan="2" align="center" class='pageheader' valign='bottom'>
<font color="#49A7DD" size="1" face="Verdana, Arial, Helvetica, sans-serif"><b>[Version {$version}]</b></font><br><br></td>


	</tr>
		</table>
<center>
<form method="post" action="login_process.php" style="background:black; border-style:none;" name="clock">

<table border="0" align="center">
  <tr onMouseover="ddrivetip('Player Name', 'Enter your Ship Captain\'s name for the selected game to take command of your ship.<br><br>If you are a new player click on the New Player button to be assigned a ship.');" onMouseout="hideddrivetip()">
	<td width="200" height="23"><img border="0" src="templates/{$templatename}images/playername.gif"></td>
	<td width="250" background="templates/{$templatename}images/loginbox.png">
		<p align="center">
		<input type="text" name="character_name" value="{$character_name}" size="32" maxlength="30" style="color:#52ACEA; font-weight: bold; background-color:black; text-align:left; border-style:none;">
		</p>
	</td>
  </tr>
  <tr onMouseover="ddrivetip('Player Password', 'Enter your Ship Captain\'s password to login to your ships computer systems.');" onMouseout="hideddrivetip()">
	<td width="200" height="23"><img border="0" src="templates/{$templatename}images/password.gif"></td>
	<td width="250" background="templates/{$templatename}images/loginbox.png">
		<p align="center">
		<input type="password" name="pass" value="{$password}" size="32" maxlength="{$maxlen_password}" style="color:#52ACEA; font-weight:bold; background-color:black; text-align:left; border-style:none;">
		</p>
	</td>
  </tr>
 </table>

<table border="0" align="center">
  <tr>
	<td colspan="3" align="center"><br><img border="0" src="templates/{$templatename}images/gameselection.gif" alt="Select Game"></td>
	</tr>
	<tr>
	<td width="220" align="center" valign="top" class="footer">

{literal}
<SCRIPT LANGUAGE="JavaScript">
<!--
var newhref=0;

function changehrefs(newhref)
{
	document.getElementById('newplayer').href = 'new_player.php?game_number='+newhref;
}
// -->
</SCRIPT>
{/literal}

{php}
	for($i = 0; $i < $totalgames; $i++)
	{
		echo "<input onMouseover=\"ddrivetip('Game Selection', 'Click on the Radio Button to select <font color=white><b>" . addslashes($gamename[$i]) . "</b></font>.');\" onMouseout=\"hideddrivetip()\" onClick=\"changehrefs('$i')\" type=\"radio\" name=\"game_number\" value=\"$i\"";
		if($i == 0)
			echo "checked";
		echo "><b><font color=\"#00ffff\" onMouseover=\"ddrivetip('Game Selection', 'Click on the Radio Button to select <font color=white><b>" . addslashes($gamename[$i]) . "</b></font>.');\" onMouseout=\"hideddrivetip()\">$gamename[$i]</font></b><br>";
echo "<script language=\"javascript\" type=\"text/javascript\">
<!--
 var myi$i = $index_seconds_until_update[$i];
 setTimeout(\"rmyx$i();\",1000);

  function rmyx$i()
   {
	myi$i = myi$i - 1;
	if (myi$i <= 0)
	 {
		 myi$i = $index_scheduler_ticks[$i] * 60;
	 }
	document.getElementById(\"myx$i\").innerHTML = myi$i;
	setTimeout(\"rmyx$i();\",1000);
   }
// end hiding script-->
</SCRIPT>
<table width=\"100%\" border=0 cellspacing=0 cellpadding=0>
	<tr>		  
	  <td align=center class=\"footer\"><b><span id=myx$i class=\"footer\">$index_seconds_until_update[$i]</span></b> $index_footer_until_update <br> 
$index_players_online[$i]<br>$index_players_open[$i]<br><br>
<a onMouseover=\"ddrivetip('Player Ranking', 'Click to view the player rankings for the <font color=white><b>" . addslashes($gamename[$i]) . "</b></font> game.');\" onMouseout=\"hideddrivetip()\" href=\"ranking.php?game_number=$i\"><img border=\"0\" src=\"templates/" . $templatename . "images/ranking_small.gif\"></a>&nbsp;&nbsp;&nbsp;
	<a onMouseover=\"ddrivetip('Game Settings', 'Click to view the game settings for the <font color=white><b>" . addslashes($gamename[$i]) . "</b></font> game.');\" onMouseout=\"hideddrivetip()\" href=\"settings.php?game_number=$i\"><img border=\"0\" src=\"templates/" . $templatename . "images/setting_small.gif\"></a><br>
	<a onMouseover=\"ddrivetip('FNN News', 'Click to view the latest FNN News broadcast for the <font color=white><b>" . addslashes($gamename[$i]) . "</b></font> game.');\" onMouseout=\"hideddrivetip()\" href=\"news.php?game_number=$i\" class=\"footer\"><img border=\"0\" src=\"templates/" . $templatename . "images/fnnnews_small.gif\"></a></td>
	</tr>
  </table>
<br>  ";
		if($server_closed[$i] == 1)
		{
			echo "<b><font size=\"4\" color=\"#ff0000\">$l_login_sclosed</font></b><br>";
		}
		else
		{
			if($tournament_setup_access[$i] == 1)
			{
echo "<SCRIPT LANGUAGE=\"JavaScript\">
<!--
var eventdate$i = new Date(\"$tournament_start_date[$i] 00:00:00 $scheduled_resetdatezone\");

function toSt$i(n) {
  s=\"\"
  if(n<10) s+=\"0\"
  return s+n.toString();
}
 
function tourneycountdown$i() {
  cl=document.clock;
  d=new Date();
  count=Math.floor((eventdate$i.getTime()-d.getTime())/1000);

  if(count<=0)
    {cl.days$i.value =\"----\";
     cl.hours$i.value=\"--\";
     cl.mins$i.value=\"--\";
     cl.secs$i.value=\"--\";
     return;
   }
  cl.secs$i.value=toSt$i(count%60);
  count=Math.floor(count/60);
  cl.mins$i.value=toSt$i(count%60);
  count=Math.floor(count/60);
  cl.hours$i.value=toSt$i(count%24);
  count=Math.floor(count/24);
  cl.days$i.value=count;    
  
  setTimeout(\"tourneycountdown$i()\",500);
}
// end hiding script-->

</SCRIPT>
<div align=\"center\">

<table style=\"border: thin solid #3FA9FC;\" cellpadding=\"0\" cellspacing=\"0\"><tr bgcolor=\"#000000\" align=\"center\"><td>
<TABLE BORDER=0 CELLSPACING=5 CELLPADDING=0 BGCOLOR=\"#000000\">
<TR>
<TD ALIGN=CENTER WIDTH=\"31%\" BGCOLOR=\"#000080\"><FONT COLOR=\"#FFFFFF\" face=\"verdana,arial,helvetica\"><B>Days:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH=\"23%\" BGCOLOR=\"#000080\"><FONT COLOR=\"#FFFFFF\" face=\"verdana,arial,helvetica\"><B>Hours:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH=\"23%\" BGCOLOR=\"#000080\"><FONT COLOR=\"#FFFFFF\" face=\"verdana,arial,helvetica\"><B>Mins:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH=\"23%\" BGCOLOR=\"#000080\"><FONT COLOR=\"#FFFFFF\"><B>Secs:</B></FONT></TD>
</TR>
<TR>
<TD ALIGN=CENTER><INPUT name=\"days$i\" size=4></TD>
<TD ALIGN=CENTER><INPUT name=\"hours$i\" size=2></TD>
<TD ALIGN=CENTER><INPUT name=\"mins$i\" size=2></TD>
<TD ALIGN=CENTER><INPUT name=\"secs$i\" size=2></TD>
</TR>
<TR>
<TD COLSPAN=\"4\" BGCOLOR=\"#000000\">
<CENTER><FONT COLOR=\"#00FF00\" SIZE=1 face=\"verdana,arial,helvetica\">
<SCRIPT LANGUAGE=\"JavaScript\">
<!--
document.write(\" \"+eventdate$i.toLocaleString()+\" \");
tourneycountdown$i();
// end hiding script-->
</SCRIPT>
</FONT>
</CENTER>
</TD>
</TR>
<TR>
<TD COLSPAN=\"4\" BGCOLOR=\"#000080\">
<CENTER><FONT face=\"verdana,arial,helvetica\" SIZE=\"1\" COLOR=\"#FFFF00\">$l_login_tourney_signup</FONT></CENTER>
</TD>
</TR>
</TABLE></td></tr></table>
</div>
";
			}
			if($account_creation_closed[$i] == 1)
			{
				echo "<b><font color=\"#FFFFFF\">$l_login_newclosed_message</font></b><br>";
			}
			if($profile_only_server[$i] == 1)
			{
				echo "<b><font color=\"#00ff00\">$l_login_profile_only</font></b><br>";
			}
			if($tournament_mode[$i] == 1)
			{
				echo "<b><font color=\"#ffff00\">$l_login_tourneymode</font></b><br>";
				if($profile_only_server[$i] != 1)
				{
					echo "<b><font color=\"#00ff00\">$l_login_profile_only</font></b><br>";
				}
			}
		}

		if($totalgames > 1)
		{
			if((($i + 1) / 2) == (int)(($i + 1) / 2))
			{
				echo "</td></tr><tr><td colspan=3><hr></td></tr><tr><td width=\"220\" align=\"center\" valign=\"top\">";
			}
			else
			{
				echo "</td><td background=\"templates/" . $templatename . "images/index_divider.png\">&nbsp;</td><td width=\"220\" align=\"center\" valign=\"top\">";
			}
		}
			if($scheduled_reset_set[$i] == 1)
			{
echo "<SCRIPT LANGUAGE=\"JavaScript\">
<!--
var reseteventdate$i = new Date(\"$scheduled_resetdate[$i] 00:00:00 $scheduled_resetdatezone\");

function resettoSt$i(n) {
  s=\"\"
  if(n<10) s+=\"0\"
  return s+n.toString();
}
 
function resetcountdown$i() {
  cl=document.clock;
  d=new Date();
  count=Math.floor((reseteventdate$i.getTime()-d.getTime())/1000);

  if(count<=0)
    {cl.rdays$i.value =\"----\";
     cl.rhours$i.value=\"--\";
     cl.rmins$i.value=\"--\";
     cl.rsecs$i.value=\"--\";
     return;
   }
  cl.rsecs$i.value=resettoSt$i(count%60);
  count=Math.floor(count/60);
  cl.rmins$i.value=resettoSt$i(count%60);
  count=Math.floor(count/60);
  cl.rhours$i.value=resettoSt$i(count%24);
  count=Math.floor(count/24);
  cl.rdays$i.value=count;    
  
  setTimeout(\"resetcountdown$i()\",500);
}
// end hiding script-->

</SCRIPT>
<div align=\"center\">

<table style=\"border: thin solid #3FA9FC;\" cellpadding=\"0\" cellspacing=\"0\"><tr bgcolor=\"#000000\" align=\"center\"><td>
<TABLE BORDER=0 CELLSPACING=5 CELLPADDING=0 BGCOLOR=\"#000000\">
<TR>
<TD ALIGN=CENTER WIDTH=\"31%\" BGCOLOR=\"#800000\"><FONT COLOR=\"#FFFFFF\" face=\"verdana,arial,helvetica\"><B>Days:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH=\"23%\" BGCOLOR=\"#800000\"><FONT COLOR=\"#FFFFFF\" face=\"verdana,arial,helvetica\"><B>Hours:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH=\"23%\" BGCOLOR=\"#800000\"><FONT COLOR=\"#FFFFFF\" face=\"verdana,arial,helvetica\"><B>Mins:</B></FONT></TD>
<TD ALIGN=CENTER WIDTH=\"23%\" BGCOLOR=\"#800000\"><FONT COLOR=\"#FFFFFF\"><B>Secs:</B></FONT></TD>
</TR>
<TR>
<TD ALIGN=CENTER><INPUT name=\"rdays$i\" size=4></TD>
<TD ALIGN=CENTER><INPUT name=\"rhours$i\" size=2></TD>
<TD ALIGN=CENTER><INPUT name=\"rmins$i\" size=2></TD>
<TD ALIGN=CENTER><INPUT name=\"rsecs$i\" size=2></TD>
</TR>
<TR>
<TD COLSPAN=\"4\" BGCOLOR=\"#000000\">
<CENTER><FONT COLOR=\"#00FF00\" SIZE=1 face=\"verdana,arial,helvetica\">
<b>$l_login_reset2<br>$scheduled_resetdate[$i]</b>
<SCRIPT LANGUAGE=\"JavaScript\">
<!--
resetcountdown$i();
// end hiding script-->
</SCRIPT>
</FONT>
</CENTER>
</TD>
</TR>
</TABLE></td></tr></table>
</div>
";
		}
		else
		{
				echo "<b>$scheduled_resetdate[$i]</b><br>";
			}
	}
{/php}
	</td>
  </tr>
 </table>
<br>
<table border="0" align="center">
  <tr>
	{if $total_signupclosed != $totalgames && $total_closed != $totalgames}
	<td width="255" onMouseover="ddrivetip('New Player Signup', 'Welcome new recruit.  By clicking this button you will be accepting a new ship provided by the Federation for exploration and conquest.  Fill out the required forms and your new ship will be ready and waiting.');" onMouseout="hideddrivetip()">
	<a id="newplayer" href="new_player.php"><img border="0" src="templates/{$templatename}images/newplayer.gif" align="left"></a>
	</td>
	{/if}
	<td width="134" onMouseover="ddrivetip('Ship Login', 'Make sure you have entered your Ship Captain\'s name, password and selected the game you would like to play before requesting login.');" onMouseout="hideddrivetip()">
	<input type="image" name="login" src="templates/{$templatename}images/login.gif" value="{$l_login_title}">
	</td>
</tr>
</table>
<br>

<table border="0" align="center">
  <tr>
	<td width="118" align="right"><a onMouseover="ddrivetip('Forum Access', 'Click here to view the Forums provided for this game.');" onMouseout="hideddrivetip()" href="{$link_forums}" target="_blank"><img border="0" src="templates/{$templatename}images/forums.gif"></a></td>
{if $main_site != ''}
	 <td width="134" align="right">
	  <a onMouseover="ddrivetip('Web Site', 'Click here to be taken to the Web Site for this game.');" onMouseout="hideddrivetip()" href="{$main_site}" target="_blank"><img border="0" src="templates/{$templatename}images/returntosite.gif"></a>
	 </td>
{/if}

{if $serverlist != ''}
	 <td width="134" align="right">
	  <a onMouseover="ddrivetip('Server List', 'Click here to view a list of all servers running Alien Assault Traders games.');" onMouseout="hideddrivetip()" href="{$serverlist}servers" target="_blank"><img border="0" src="templates/{$templatename}images/serverlist.gif"></a>
	 </td>
{/if}
	<td width="70" align="right"><a onMouseover="ddrivetip('FAQ', 'Click here to view a simple F.A.Q. about the game.');" onMouseout="hideddrivetip()" href="http://wiki.aatraders.com/tiki-index.php?page=Playing+the+Game" target="_blank"><img border="0" src="templates/{$templatename}images/faq.gif"></a></td>
  </tr>
<tr>
		<td colspan="4" align="center"><a onMouseover="ddrivetip('Contact Admin', 'Click here to send an Email to the Admin of this game.');" onMouseout="hideddrivetip()" href="contact_admin.php" target="_blank"><img border="0" src="templates/{$templatename}images/contact.gif"><img border="0" src="templates/{$templatename}images/contact_admin.gif"></a></td>
</tr>
</table>
</form>
</center>

{if $showserverlist == 1 && $servercount > 0}
	<table style="border: thin solid #3FA9FC;" width="800" border="1" cellspacing="1" cellpadding="1" align="center">
	{php}
	for($i = 0; $i < $servercount; $i++){
		echo "<tr><td class=mnu><a href=\"http://$serverurl[$i]\" class=mnu>$servername[$i]</a></td><td align=\"center\"><span class=mnu>$serversectors[$i] Sectors</span></td><td align=\"center\"><span class=mnu>$serverplayers[$i] Players</span></td><td align=\"center\"><span class=mnu>$servertop[$i]</span></td><td align=\"center\"><span class=mnu>$serverreset[$i]</span></td></tr>";
	}
	{/php}
	</table>
{/if}

{if $newscount}
{literal}
<SCRIPT LANGUAGE="JavaScript1.2" TYPE="text/javascript">
<!--

{/literal}
{php}
if ($newscount == 1)
	echo "var delay=1000000 //set delay between message change (in miliseconds)";
else
	echo "var delay=7000 //set delay between message change (in miliseconds)";
{/php}
{literal}

var fcontent=new Array()

{/literal}
{php}
	for($i = 0; $i < $newscount; $i++) 
		echo "fcontent[$i]=\"<br><font color=#00ff00><b>$l_login_notice</b></font>&nbsp;" . $newsdata[$i] . "\"\n"; 
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
		document.getElementById("adminnews").style.color=startcolor
		document.getElementById("adminnews").innerHTML=fcontent[index]
		linksobj=document.getElementById("adminnews").getElementsByTagName("A")
		if (fadelinks)
			linkcolorchange(linksobj)
		colorfade()
	}
	else if (ie4)
		document.all.adminnews.innerHTML=fcontent[index]
	else if (ns4){
		document.anews.document.write(fcontent[index])
		document.anews.document.close()
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
		document.getElementById("adminnews").style.color="rgb("+hex+","+hex+","+hex+")"; // Set color value.
		if (fadelinks)
			linkcolorchange(linksobj)
		frame--;
		setTimeout("colorfade()",20);	
	}
	else
	{
		document.getElementById("adminnews").style.color=endcolor;
		frame=20;
		hex=(fadescheme==0)? 255 : 0
	}   
}

window.onload = changecontent;
//-->
</SCRIPT>
{/literal}

<table border=0 cellpadding=2 cellspacing=0 align="center" width=650>
  <tr>
	<td ID="adminnews" class="News" align=center><layer id="anews"</layer>
</td>
  </tr>
</table>
{/if}

