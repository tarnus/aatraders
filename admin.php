<?php
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
// 
// File: admin.php

include ("config/config.php");

$template_object->enable_gzip = 0;

get_post_ifset("game_name, command, cmd, menu, admin_password, md5admin_password, ip");

if (!isset($game_name) || $game_name == '')
{
	$title = "Administration";
}
else
{
	$title = "Administration: " . $game_name;
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if ((!isset($menu)) || ($menu == ''))
{
	$menu = '';
}

if ((!isset($admin_password)) || ($admin_password == ''))
{
	$admin_password = '';
}

if (isset($md5admin_password) && md5($adminpass) == $md5admin_password) //md5 sent from log.php
{
	$admin_password = $adminpass;
}

function CHECKED($yesno)
{
	return(($yesno == "Y") ? "CHECKED" : "");
}

function YESNO($onoff)
{
	return(($onoff == "ON") ? "Y" : "N");
}

?>
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

<style type="text/css">
<!--
td                { font-size: 10px; color: #e0e0e0; font-family: verdana; }
TEXTAREA                { font-size: 10px; font-family: verdana; }
INPUT                { font-size: 10px; font-family: verdana; }
SELECT                { font-size: 10px; font-family: verdana; }
-->
</style>

<style type="text/css">
/*Credits: Dynamic Drive CSS Library */
/*URL: http://www.dynamicdrive.com/style/ */
.suckertreemenu ul{
	margin: 0;
	padding: 0;
	list-style-type: none;
	z-index: 100; 
}

/*Top level list items*/
.suckertreemenu ul li{
	position: relative;
	display: inline;
	float: left;
	background-color: #4455aa; /*overall menu background color*/
	z-index: 100; 
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
	background: #4455aa url(images/arrow_down.gif) no-repeat center right;
}

/*Background image for subsequent level menu list links */
.suckertreemenu .subfoldericon{
	background: #4455aa url(images/arrow_right.gif) no-repeat center right;
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
<table id="Table_01" width="772" border="0" cellpadding="0" cellspacing="0" align="center">
<?
if ($admin_password == '')
{
?>
	<tr>
		<td>
			<img src="images/admin/admin_01.gif" width="772" height="30" alt=""></td>
	</tr>
	<tr>
		<td background="images/admin/admin_02.gif">
			<div align="center">
			<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0" width="650" height="300" id="3D Solar System" align="middle">
<param name="allowScriptAccess" value="sameDomain" />
<param name="movie" value="images/aat-title.swf" />
<param name="quality" value="high" />
<param name="bgcolor" value="#000000" />
<embed src="images/aat-title.swf" quality="high" bgcolor="#000000" width="650" height="300" name="3D Solar System" align="middle" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />
</object></div></td>
	</tr>
	<tr>
		<td>
			<img src="images/admin/admin_03.gif" width="772" height="40" alt=""></td>
	</tr>
<?
}
else
{
?>
	<tr>
		<td>
			<img src="images/admin/admin_01a.gif" width="772" height="30" alt=""></td>
	</tr>
<?
}
?>
</table>
<table width="772" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td background="images/admin/admin_04.gif"><table cellspacing ="0" cellpadding ="0" border ="1" width ="667" align="center" bgcolor="#000000">
					<tr align="center">
						<td align="center">
						<table width="100%" border="0" cellspacing="0" cellpadding="3" align="center">
          <tr>
            <td>
              <div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC"><?php echo ucwords(str_replace("_", " ", $menu)); ?></font></b></div>
            </td>
          </tr>

<?php

$login_ip = getenv("REMOTE_ADDR");
if ($admin_password != $adminpass || $admin_password == md5($adminpass))
{
	adminlog("LOG0_RAW","Admin Login attempt from $login_ip");
	echo "<tr><td><div align=center><form action=\"admin.php\" method=\"post\">";
?>
					Select Game to Administer: <select name="game_number">
<?php
	$filelist = get_dirlist($gameroot."config/");
	$newcommands = 0;
	for ($c=0; $c<count($filelist); $c++) { 
		if(strstr($filelist[$c], "config_local")){
			$gamenumber =  str_replace("config_local", "", str_replace(".php", "", $filelist[$c])); 
			$fs = fopen($gameroot."config/".$filelist[$c], "r");
			$items = fgets($fs);
			$items = fgets($fs);
			$gamename = AAT_substr(trim($items), 3);
			fclose($fs);
?>
			<option value="<?=$gamenumber;?>" <?php
			?>>Admin: <?=$gamename;?></option>
<?php
		}
	}?>
					</select><br><br>
<?php
	echo "Password: <input type=password name=admin_password size=20 maxlength=20>&nbsp;&nbsp;";
	echo "<input type=submit value=Submit><input type=reset value=Reset>";
	echo "</form></div></td></tr>";
}
else
{
		$count = 0;
		$filelist = get_dirlist($gameroot."admin");
		for ($c=0; $c<count($filelist); $c++) { 
			$filenameroot =  str_replace(".inc", "", $filelist[$c]); 
			if(strstr($filelist[$c], ".inc")){
				$fs = fopen($gameroot."admin/".$filelist[$c], "r");
				$items = fgets($fs);
				$items = fgets($fs);
				$helpinfo = fgets($fs);
				$name = AAT_substr(trim($items), 3);
				$helpinfo = AAT_substr($helpinfo, 3);
				$menuselections = explode(":", $name);
				fclose($fs);
				$fileroot[$count] = $filenameroot;
				$menuselection[$count] = $menuselections[0];
				$description[$count] = trim($menuselections[1]);
				$help[$count] = addslashes(trim($helpinfo));
				$count++;
			}
		}
	array_multisort($description, SORT_ASC, SORT_STRING, $menuselection, $fileroot, $help);
	?>
	<tr><td width="100%">
<table align="center"><tr><td align="center">
	<img src="images/spacer.gif" height="1" width="530"><br>
<div class="suckertreemenu">
<ul id="treemenu">
	<li><a href="#">View</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 1)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="#">Edit</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 2)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="">Update</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 8)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="#">Message</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 3)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="#">Scheduler</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 4)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="#">Backup</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 5)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="#">Restore</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 6)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
	<li><a href="">Reset</a>
		<ul>
			<?
			for($i = 0; $i < $count; $i++)
			{
				if($menuselection[$i] == 7)
				{
					echo "<li><a href=\"admin.php?menu=$fileroot[$i]&game_number=$game_number&admin_password=$admin_password\" onMouseover=\"ddrivetip('$description[$i]', '$help[$i]');\" onMouseout=\"hideddrivetip()\">$description[$i]</a></li>";
				}
			}
			?>
		</ul>
	</li>
</ul>
</div>
</td>
</tr>
</table>
</td>
</tr>
          <tr>
          	<td>
          		<div align="center">
<?php
require ("backends/cpuloadclass/class_CPULoad.php");
$cpuload = new CPULoad();
$cpuload->get_load();
$cpuload->print_load();
 
echo "The average CPU load is: ".$cpuload->load["cpu"]."%<br>\n";
?>
</div>
</td>
</tr>
	<?
	if (empty($menu))
	{
		adminlog("LOG0_RAW","Admin Login successful from $login_ip");
		echo "<tr><td><div align=center>Welcome to the Alien Assault Traders Administration Module<BR><BR>\n";
		echo "</div></td></tr>";
	}
	else
	{
		include ("admin/". $menu . ".inc");
	}
}

echo "<tr><td colspan=\"9\"><div align=center>" . $l_global_mlogin . "</div></td></tr>";

?>
			</table>
</td>
					</tr></table></td>
  </tr>
</table>
<table width="772" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
		<td>
			<img src="images/admin/admin_05.gif" width="772" height="31" alt=""></td>
	</tr>

</table>

<?php
include ("footer.php");
?> 
