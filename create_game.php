<?php
// This program is free software; you can redistribute it and/or modify it	
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: create_game.php

$create_game = 1;
$default_lang = "english";
$_SESSION['langdir'] = $default_lang;
$langdir = $_SESSION['langdir'];

include ("config/config.php");

if (!$game_installed)
{
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<META HTTP-EQUIV="Refresh" CONTENT="0;URL=installer.php">
		<title>Running Installer</title>
	</head>
	<body marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 bgcolor="#000000">
	</body>
</html>
<?php
	die();
}

if(@ini_get("register_globals") != 1)
{
	if (!empty($_GET))
	{
		extract($_GET);
	}

	if (!empty($_POST))
	{
		extract($_POST);
	}
}

$silent = 1;

//foreach($_POST as $key=>$value){ 
//	print "[" . $key . "] => " . $value . "<br>";
//}

connectdb();

// Manually set step var if info isn't correct.
if (!isset($step))
{
	$step = 0;
}

if($step > 30)
{
	@include("support/variables" . $game_number . ".inc");
}

include("languages/$default_lang/lang_create_game.inc");

$template_object->enable_gzip = 0;

$silent = 0;

function exportvariables($silent = 0){
	global $gameroot, $game_number;
	global $db, $db_prefix;
	$filename = $gameroot . "support/variables" . $game_number . ".inc";
	$file = fopen($filename,"w") or die ("Failed opening file: enable write permissions for '$filename'");
	if($silent == 0)
		echo "<b>Saving $filename</b><br><br>";
	
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}config_values");
	db_op_result($debug_query,__LINE__,__FILE__);

	fwrite($file,"<?\n"); 
	while (!$debug_query->EOF)
	{
		$row = $debug_query->fields;
		$db_config_name = $row['name'];
		$db_config_value = $row['value'];
//		echo "Writing data: " . $db_config_name . "=\"" . $db_config_value . "\";<br>"; 
		fwrite($file,"$" . $db_config_name . "=\"" . $db_config_value . "\";\n"); 
		$debug_query->MoveNext();
	}
	fwrite($file,"?>\n"); 
	fclose($file);
}

function TextFlush($Text="") 
{
	echo "$Text\n";
	flush();
}

class c_Timer
{
	var $t_start = 0;
	var $t_stop = 0;
	var $t_elapsed = 0;

	function start()
	{
		$this->t_start = microtime();
	}

	function stop()
	{
		$this->t_stop	= microtime();
	}

	function elapsed()
	{
		$start_u = AAT_substr($this->t_start,0,10); $start_s = AAT_substr($this->t_start,11,10);
		$stop_u	= AAT_substr($this->t_stop,0,10);	$stop_s	= AAT_substr($this->t_stop,11,10);
		$start_total = doubleval($start_u) + $start_s;
		$stop_total	= doubleval($stop_u) + $stop_s;
		$this->t_elapsed = $stop_total - $start_total;
		return (float)$this->t_elapsed;
	}
}

$filelist = get_dirlist($gameroot."create_game/");
$modulecount = 0;
$cargolist = "";
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$module[$modulecount] =  str_replace(".inc", "", $filelist[$c]); 
		$modulecount++;
	}
}

sort($module);
reset($module);

for($nextstep = 0; $nextstep < count($module); $nextstep++)
{
//	echo "$module[$nextstep] > $step<br>";
	if($module[$nextstep] > $step)
		break;
}

// Start Timer
$BenchmarkTimer = new c_Timer;
$BenchmarkTimer->start();

// Set timelimit

$is_safe_mode = (bool) ini_get('safe_mode');
if (!$is_safe_mode)
{
	set_time_limit(300);
}

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

$title = "Create Game";

$header = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">
		<html>
		 <head>
		  <meta http-equiv=\"Pragma\" content=\"no-cache\">
		  <META HTTP-EQUIV=\"Expires\" CONTENT=\"-1\">
		  <title>$title</title>
			<style type=\"text/css\">
			<!--
			body             { font-family: Verdana, Arial, sans-serif; font-size: x-small;}
td                { font-size: 10px; color: #e0e0e0; font-family: verdana; }
TEXTAREA                { font-size: 10px; font-family: verdana; }
INPUT                { font-size: 10px; font-family: verdana; }
SELECT                { font-size: 10px; font-family: verdana; }
			-->
			</style>
<style type=\"text/css\">

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

<div id=\"dhtmltooltip\"></div>

<script type=\"text/javascript\">

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
var tipobj=document.all? document.all[\"dhtmltooltip\"] : document.getElementById? document.getElementById(\"dhtmltooltip\") : \"\"

function ietruebody(){
return (document.compatMode && document.compatMode!=\"BackCompat\")? document.documentElement : document.body
}


function ddrivetip(thetitle, thetext, thecolor, thewidth){
if (ns6||ie){
if (typeof thewidth!=\"undefined\") tipobj.style.width=thewidth+\"px\"
if (typeof thecolor!=\"undefined\" && thecolor!=\"\") tipobj.style.backgroundColor=thecolor

	topColor = \"#7D92A9\"
	subColor = \"#A5B4C4\"
	ContentInfo = '<table border=\"0\" width=\"150\" cellspacing=\"0\" cellpadding=\"0\">'+
	'<tr><td width=\"100%\" bgcolor=\"#000000\">'+

	'<table border=\"0\" width=\"100%\" cellspacing=\"1\" cellpadding=\"0\">'+
	'<tr><td width=\"100%\" bgcolor='+topColor+'>'+

	'<table border=\"0\" width=\"90%\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\">'+
	'<tr><td width=\"100%\" align=\"center\">'+

	'<font class=\"tooltiptitle\">'+thetitle+'</font>'+

	'</td></tr>'+
	'</table>'+

	'</td></tr>'+

	'<tr><td width=\"100%\" bgcolor='+subColor+'>'+

	'<table border=\"0\" width=\"90%\" cellpadding=\"0\" cellspacing=\"1\" align=\"center\">'+

	'<tr><td width=\"100%\">'+

	'<font class=\"tooltipcontent\">'+thetext+'</font>'+

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
tipobj.style.left=ie? ietruebody().scrollLeft+event.clientX-tipobj.offsetWidth+\"px\" : window.pageXOffset+e.clientX-tipobj.offsetWidth+\"px\"
else if (curX<leftedge)
tipobj.style.left=\"5px\"
else
//position the horizontal position of the menu where the mouse is positioned
tipobj.style.left=curX+offsetxpoint+\"px\"

//same concept with the vertical position
if (bottomedge<tipobj.offsetHeight)
tipobj.style.top=ie? ietruebody().scrollTop+event.clientY-tipobj.offsetHeight-offsetypoint+\"px\" : window.pageYOffset+e.clientY-tipobj.offsetHeight-offsetypoint+\"px\"
else
tipobj.style.top=curY+offsetypoint+\"px\"
tipobj.style.visibility=\"visible\"
}
}

function hideddrivetip(){
if (ns6||ie){
enabletip=false
tipobj.style.visibility=\"hidden\"
tipobj.style.left=\"-1000px\"
tipobj.style.backgroundColor=''
tipobj.style.width=''
}
}

document.onmousemove=positiontip

//-->
</script>
			 </head>
			<body ";
if($autorun == 1 && $module[$nextstep] != 999)
	$header .= "onLoad=\"document.AutoRun.submit()\"";

$header .= "marginheight=0 marginwidth=0 topmargin=0 leftmargin=0 background=\"images/bgspace.jpg\" bgcolor=\"#000000\" text=\"#c0c0c0\" link=\"#52ACEA\" vlink=\"#52ACEA\" alink=\"#52ACEA\">";

TextFlush($header);

if($module[$nextstep] <= 10)
{
	$bannertitle = "<table id=\"Table_01\" width=\"772\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
	<tr>
		<td>
			<img src=\"images/admin/admin_01.gif\" width=\"772\" height=\"30\" alt=\"\"></td>
	</tr>
	<tr>
		<td background=\"images/admin/admin_02.gif\">
			<div align=\"center\">
			<object classid=\"clsid:d27cdb6e-ae6d-11cf-96b8-444553540000\" codebase=\"http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,0,0\" width=\"650\" height=\"300\" id=\"3D Solar System\" align=\"middle\">
<param name=\"allowScriptAccess\" value=\"sameDomain\" />
<param name=\"movie\" value=\"images/aat-title.swf\" />
<param name=\"quality\" value=\"high\" />
<param name=\"bgcolor\" value=\"#000000\" />
<embed src=\"images/aat-title.swf\" quality=\"high\" bgcolor=\"#000000\" width=\"650\" height=\"300\" name=\"3D Solar System\" align=\"middle\" allowScriptAccess=\"sameDomain\" type=\"application/x-shockwave-flash\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" />
</object></div></td>
	</tr>
	<tr>
		<td>
			<img src=\"images/admin/admin_03.gif\" width=\"772\" height=\"40\" alt=\"\"></td>
	</tr>
</table>
";

	TextFlush($bannertitle);
}
else
{
	$bannertitle = "<table id=\"Table_01\" width=\"772\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
		<tr>
		<td>
			<img src=\"images/admin/admin_01a.gif\" width=\"772\" height=\"30\" alt=\"\"></td>
	</tr>
</table>
";
	TextFlush($bannertitle);
}

$containerbox = "<table width=\"772\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"0\">
  <tr>
    <td background=\"images/admin/admin_04.gif\"><table cellspacing =\"0\" cellpadding =\"0\" border =\"1\" width =\"667\" align=\"center\" bgcolor=\"#000000\">
					<tr align=\"center\">
						<td align=\"center\">";

TextFlush($containerbox);

if (!isset($_POST['admin_password']))
{
	$_POST['admin_password'] = '';
}

if ($_POST['admin_password'] != $adminpass) 
{
	$nextstep = 0;
}

global $silent;
global $maxlen_password;

// Main switch statement.
if($module[$nextstep] != 40 && $module[$nextstep] != 45 && $module[$nextstep] != 999){
	echo "<form name=AutoRun action=create_game.php method=post enctype=\"multipart/form-data\">";
	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">\n";
	}
}

$containerbox = "
";

TextFlush($containerbox);

if($module[$nextstep] == 40 && $resetgame == 1 && $autorun == 1)
{
	$module[$nextstep] = 60;
	echo "<form name=AutoRun action=create_game.php method=post enctype=\"multipart/form-data\">";
	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">\n";
	}
}

include ("create_game/" . $module[$nextstep] . ".inc");

$containerbox = "<br><br>
";

TextFlush($containerbox);

if($module[$nextstep] != 40 && $module[$nextstep] != 45){
	$StopTime = $BenchmarkTimer->stop();
	$totaltime += (float)sprintf("%01.2f", $BenchmarkTimer->elapsed());
}

if($module[$nextstep] != 40 && $module[$nextstep] != 45 && $module[$nextstep] != 999){
	echo "<input type=hidden name=totaltime value=$totaltime>";
	echo "<input type=submit value=Continue>";
	echo "</form>";
}

$StopTime = $BenchmarkTimer->stop();
$Elapsed = $BenchmarkTimer->elapsed();
$Elapsed = sprintf("%01.2f", $Elapsed);
TextFlush("<br>\nElapsed Time - $Elapsed seconds<br>");
TextFlush( "Total Elapsed Time to create game - " . $totaltime . " seconds<br><br>\n");
$containerbox = "</td>
					</tr></table></td>
  </tr>
</table>";

TextFlush($containerbox);
$endtitle = "<table width=\"772\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"0\">
	<tr>
		<td>
			<img src=\"images/admin/admin_05.gif\" width=\"772\" height=\"31\" alt=\"\"></td>
	</tr>

</table>";
TextFlush($endtitle);
TextFlush("</body></html>");

?>
