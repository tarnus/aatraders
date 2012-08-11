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
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
{if $pages != 0}
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
										<form action="galaxy_map.php" method="post">
								<tr>
	<TD align="right">
	{$l_common_selectpage}:
	</td><td align="left"><select name="startsector">
	{php}
	for($i = 0; $i <= $pages; $i++){
		if(($i * $divider) + 1 == $startsector)
			$selected = "selected";
		else $selected = "";
		if($i == 0)
			$page = 1;
		else $page = ($i * $divider) + 1;
		
		echo "	<option value=\"". $page ."\" $selected>".  ($i+1) ."</option>\n";
	}
	{/php}
	<option value="-1" {$allselected}>{$l_all}</option>
	</select>
	&nbsp;<input type="submit" value="{$l_submit}">
	</TD></tr>
	</form>
	</table>
{/if}

{php}
if($startsector != 1)
	$prevlink = "<a href='galaxy_map.php?startsector=".($startsector - $divider)."'>$l_common_prev</a>";
else $prevlink = "&nbsp;";

if($endsector < $sector_max )
	$nextlink = "<a href='galaxy_map.php?startsector=".($startsector + $divider)."'>$l_common_next</a>";
else $nextlink = "&nbsp;";

echo "<TABLE border=0 cellpadding=2 cellspacing=1 width=\"100%\" align=center>\n";
echo "<TR><TD align='left'>$prevlink</td>\n";
echo "<TD align='right'>$nextlink</td></tr>\n";
echo "</table>";
{/php}
</td></tr></table>
<table width="600" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
<TABLE border=0 cellpadding=2 cellspacing=0 align="center" width="100%">
{if $mapsectorcount == 0}
<tr><td><div align="center"><font color="lime"><b>{$l_glxy_nosectors}</b></font></div>
{/if}
{php}
for($i = 0; $i < $mapsectorcount; $i++){

	$break = ($i + 1) % $map_width;
	if($sectorid[$i] >= $startsector and $sectorid[$i] < $endsector){
	   	if ($break == 1)
		{
			echo "<TR><TD align=\"left\">$sectorname[$i]</TD>\n";
		}
	}

	if($sectorid[$i] >= $startsector and $sectorid[$i] < $endsector){
		echo "<TD width=12 height=12 bgcolor=$sectorzonecolor[$i]><A HREF=main.php?move_method=real&engage=1&destination=$sectorname[$i] onMouseover=\"ddrivetip('$l_sector: $altsector[$i] - $altport[$i]<br>$altzone[$i]','$l_galacticarm: $galacticarm[$i]<br>";
		$coords = explode("|", $nav_scan_coords[$i]); 
		$linklist = str_replace("|", "<br>", $link_list[$i]);
		echo "X: $coords[0]<br>Y: $coords[1]<br>Z: $coords[2]<br><br>$l_port_buys<br>$buy_list[$i]<br><br>$l_links:<br>$linklist<br>$notelistnote[$i] $teamnotelistnote[$i]'); \" onMouseout=\"hideddrivetip();\"><img src=\"images/ports/" . $sectorimage[$i] . ".png\" title=\"$sectortitle[$i]\" border=0></A></TD>\n";

		if ($break == 0)
		{
			echo "<TD>$sectorname[$i]</TD></TR>\n";
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
