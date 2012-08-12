<H1>{$title}</H1>

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
<div id="ToolTip"></div>

	<table width="600" border="1" cellspacing="0" cellpadding="4" align="center">
	<form action="galaxy_local.php" method="post">
	<TR><TD align='center'>
	{$l_glxy_select}&nbsp;
	<select name="turns">
	{php}
		echo "	<option value=0 " . ($turns == 0 ? "selected" : "") . ">0</option>\n";
		echo "	<option value=1 " . ($turns == 1 ? "selected" : "") . ">1</option>\n";
		echo "	<option value=2 " . ($turns == '2' ? "selected" : "") . ">2</option>\n";
		echo "	<option value=3 " . ($turns == '3' ? "selected" : "") . ">3</option>\n";
		echo "	<option value=4 " . ($turns == '4' ? "selected" : "") . ">4</option>\n";
		echo "	<option value=5 " . ($turns == '5' ? "selected" : "") . ">5</option>\n";
		echo "	<option value=10 " . ($turns == '10' ? "selected" : "") . ">10</option>\n";
		echo "	<option value=20 " . ($turns == '20' ? "selected" : "") . ">20</option>\n";
		echo "	<option value=30 " . ($turns == '30' ? "selected" : "") . ">30</option>\n";
		echo "	<option value=40 " . ($turns == '40' ? "selected" : "") . ">40</option>\n";
		echo "	<option value=50 " . ($turns == '50' ? "selected" : "") . ">50</option>\n";
		echo "	<option value=60 " . ($turns == '60' ? "selected" : "") . ">60</option>\n";
		echo "	<option value=70 " . ($turns == '70' ? "selected" : "") . ">70</option>\n";
		echo "	<option value=80 " . ($turns == '80' ? "selected" : "") . ">80</option>\n";
		echo "	<option value=90 " . ($turns == '90' ? "selected" : "") . ">90</option>\n";
		echo "	<option value=100 " . ($turns == '100' ? "selected" : "") . ">100</option>\n";
		echo "	<option value=120 " . ($turns == '120' ? "selected" : "") . ">120</option>\n";
		echo "	<option value=140 " . ($turns == '140' ? "selected" : "") . ">140</option>\n";
		echo "	<option value=160 " . ($turns == '160' ? "selected" : "") . ">160</option>\n";
		echo "	<option value=180 " . ($turns == '180' ? "selected" : "") . ">180</option>\n";
		echo "	<option value=200 " . ($turns == '200' ? "selected" : "") . ">200</option>\n";
		echo "	<option value=250 " . ($turns == '250' ? "selected" : "") . ">250</option>\n";
		echo "	<option value=300 " . ($turns == '300' ? "selected" : "") . ">300</option>\n";
	{/php}
	</select>
	{$l_glxy_turns}&nbsp;&nbsp;&nbsp;<input type="submit" value="{$l_submit}">
	</TD></tr>
	</form>
	</table>
	<table width="60%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
<TABLE border=0 cellpadding=2 cellspacing=0 align=center width="100%">
{if $turns == 0}
<tr><td><div align="center"><font color="lime"><b>{$l_glxy_nosectors}</b></font></div>
{/if}

{php}
for($i = 1; $i < $mapsectorcount; $i++){

	$break = $i % $map_width;
	if($i == 0)
		$break = 1;
		
	if($sectorid[$i] >= $startsector and $sectorid[$i] < $endsector){
	   	if ($break == 1)
		{
			echo "<TR><TD align=\"left\">$sectorname[$i]</TD>\n";
		}
	}

	if($sectorid[$i] >= $startsector and $sectorid[$i] < $endsector){
		echo "<TD bgcolor=$sectorzonecolor[$i]><A HREF=main.php?move_method=real&engage=1&destination=$sectorname[$i] onMouseover=\"ddrivetip('$l_sector: $altsector[$i] - $altport[$i]<br>$altturns[$i]','$l_galacticarm: $galacticarm[$i]<br>";
		$coords = explode("|", $nav_scan_coords[$i]); 
		$linklist = str_replace("|", "<br>", $link_list[$i]);
		echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_list[$i]<br><br>$l_links:<br>$linklist<br>$notelistnote[$i] $teamnotelistnote[$i]');\" onMouseout=\"hideddrivetip();\"><img src=\"images/ports/" . $sectorimage[$i] . ".png\" title=\"$sectortitle[$i]\" border=0></A></TD>\n";

		if ($break == 0)
		{
			echo "<TD align=\"right\">$sectorname[$i]</TD></TR>\n";
		}

	}
}
if($break != 0)
{
	echo"<TD align=\"right\">" . $sectorname[($i-1)] . "</TD>";
}
{/php}
				</td>
			</tr>
		</table>
	</td>
  </tr>
<tr><td><div align="center">{$gotomain}<div></td></tr>
</table>
<br>
	<table width="600" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
<table width="600" border="1" cellspacing="0" cellpadding="4" align="center" bgcolor="#000000">
<tr><td colspan="3"><div align="center"><b><font size="2" color="lime">{$l_commodities}</font></b></div></td></tr>
<TR>
{php}
	for($i = 0; $i < $typecount; $i++)
	{
echo "<td class=\"footer\"><img src=\"images/ports/" . $porttypes[$i] . ".png\"> - " . ucwords($porttypes[$i]) . "</td>";
		if(($i+1)/3 == floor(($i+1)/3) && ($i+1) != $typecount)
			echo"</tr><tr>";
	}
if(($i-1)/3 != floor(($i-1)/3) && $i == $typecount)
{
	for($finish = 0; $finish < 2; $finish++)
	{
		echo "<td>&nbsp;</td>";
		$i++;
		if($i/3 == floor($i/3))
			break;
	}		
}
echo"</tr>";
{/php}
<tr><td colspan="3"><div align="center">{$gotomain}<div></td></tr>
</table>
<br>
<table width="600" border="1" cellspacing="0" cellpadding="4" align="center" bgcolor="#000000">
<tr><td colspan="6"><div align="center"><b><font size="2" color="lime">{$l_player}</font></b></div></td></tr>
<tr>
{php}
for($i = 1; $i < $player_count; $i++){
	echo "<td class=\"footer\" bgcolor=".$playerzonecolor[$i]."><img src = \"templates/{$templatename}images/spacer.gif\" width=12></td><td class=\"footer\">".$playerzone[$i]."&nbsp;</td>";
	if($i/3 == floor($i/3) && ($i+1) != $player_count)
		echo"</tr><tr>";
}
if(($i-1)/3 != floor(($i-1)/3) && $i == $player_count)
{
	for($finish = 0; $finish < 2; $finish++)
	{
		echo "<td>&nbsp;</td>";
		$i++;
		if($i/3 == floor($i/3))
			break;
	}		
}
	echo"</tr>";
{/php}
<tr><td colspan=6><div align="center">{$gotomain}<div></td></tr>

</table>
<br>
<table width="600" border="1" cellspacing="0" cellpadding="4" align="center" bgcolor="#000000">
<tr><td colspan="6"><div align="center"><b><font size="2" color="lime">{$l_teams}</font></b></div></td></tr>
<tr>
{php}
for($i = 1; $i < $teamzonecount; $i++){
	echo "<td class=\"footer\" bgcolor=".$namezonecolor[$i]."><img src = \"templates/{$templatename}images/spacer.gif\" width=12></td><td class=\"footer\">".$namezone[$i]."&nbsp;</td>";
	if($i/3 == floor($i/3) && ($i+1) != $teamzonecount)
		echo"</tr><tr>";
}
if(($i-1)/3 != floor(($i-1)/3) && $i == $teamzonecount)
{
	for($finish = 0; $finish < 2; $finish++)
	{
		echo "<td>&nbsp;</td>";
		$i++;
		if($i/3 == floor($i/3))
			break;
	}		
}
	echo"</tr>";
{/php}

<tr><td colspan=6><div align="center">{$gotomain}<div></td></tr>
		</table>
