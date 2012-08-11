{literal}
	<style type="text/css">

body {
	color: #2d2e2e;
	font-family: Arial, Helvetica, sans-serif;
	font-size: 11px;
	line-height: 14px;
	margin: 0 0 0 0; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	padding: 0 0 0 0; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Centers the page content container in IE 5 browsers. */
}
	h3 {
	margin:0;
	text-align: center;
	color: #000;
    }
	.header {
    	padding:5px 10px;
		background:#ddd;
	}
.rightColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	width: 200px;
	color: #000;
}
.rightBuyColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	width: 200px;
	color: #000;
}
.leftColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.portfooter {
	background-color: #eef6ed;
	border-top: solid 1px #8ab573; /* Sets the top border properties for an element using shorthand notation */
	padding: 10px 10px 10px 10px; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	color: #000;
}
	.inputcss {
		font-family: Verdana, Geneva, sans-serif;
		font-size: 10px;
	}

	a:link {
		color: #542764;
	}
	
input.groovybutton
{
   font-size:13px;
   font-family:Arial,sans-serif;
   font-weight: bold;
   height:23px;
   background-color:#779999;
   background-image:url(templates/{/literal}{$templatename}{literal}images/back03.gif);
   border-style:solid;
   border-color:#DDDDDD;
   border-width:1px;
}
    </style>

<script type="text/javascript">

function goLite(FRM,BTN)
{
   window.document.forms[FRM].elements[BTN].style.backgroundImage = "url(templates/{/literal}{$templatename}{literal}images/back02.gif)";
}

function goDim(FRM,BTN)
{
   window.document.forms[FRM].elements[BTN].style.backgroundImage = "url(templates/{/literal}{$templatename}{literal}images/back03.gif)";
}
</script>
<style type="text/css">

#dhtmltooltip{
position: absolute;
width: 150px;
border: 2px solid black;
padding: 2px;
background-color: white;
visibility: hidden;
z-index: 2000;
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

	topColor = "#dddddd"
	subColor = "#eef6ed"
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

<SCRIPT LANGUAGE="JavaScript">
	<!--

function MakeMax(name, val)
{
 if (document.forms[0].elements[name].value != val)
 {
	if (val != 0)
	{
	document.forms[0].elements[name].value = val;
	}
 }
}

function Comma(number) {
number = '' + Math.round(number);
if (number.length > 3) {
var mod = number.length % 3;
var output = (mod > 0 ? (number.substring(0,mod)) : '');
for (i=0 ; i < Math.floor(number.length / 3); i++) {
if ((mod == 0) && (i == 0))
output += number.substring(mod+ 3 * i, mod + 3 * i + 3);
else
output+= ',' + number.substring(mod + 3 * i, mod + 3 * i + 3);
}
return (output);
}
else return number;
}

// changeDelta function //
function mypw(one,two)
{
	return Math.exp(two * Math.log(one));
}

function changeDelta(desiredvalue,currentvalue)
{
	return (mypw({/literal}{$upgrade_factor}{literal}, desiredvalue) - mypw({/literal}{$upgrade_factor}{literal}, currentvalue)) * {/literal}{$upgrade_cost}{literal} * {/literal}{$alliancefactor}{literal};
}

function countTotal()
{
// Here we cycle through all form values (other than buy, or full), and regexp out all non-numerics. (1,000 = 1000)
// Then, if its become a null value (type in just a, it would be a blank value. blank is bad.) we set it to zero.
clean_js()
var form = document.forms[0];
var i = form.elements.length;
while (i > 0)
	{
 if (form.elements[i-1].value == '')
	{
	form.elements[i-1].value ='0';
	}
 i--;
}
	// Here we set all 'Max' items to 0 if they are over max - player amt.
	if (({/literal}{$fighter_free}{literal} < form.fighter_number.value) && (form.fighter_number.value != '{/literal}{$l_full}{literal}'))
	{
		form.fighter_number.value=0
	}
	if (({/literal}{$torpedo_free}{literal} < form.torpedo_number.value) && (form.torpedo_number.value != '{/literal}{$l_full}{literal}'))
	{
		form.torpedo_number.value=0
	}
	if (({/literal}{$armor_free}{literal} < form.armor_number.value) && (form.armor_number.value != '{/literal}{$l_full}{literal}'))
	{
		form.armor_number.value=0
	}

// Done with the bounds checking
// Pluses must be first, or if empty will produce a javascript error
form.total_cost.value =
changeDelta(form.hull_upgrade.value,{/literal}{$shipinfo.hull}{literal})
+ changeDelta(form.engine_upgrade.value,{/literal}{$shipinfo.engines}{literal})
+ changeDelta(form.power_upgrade.value,{/literal}{$shipinfo.power}{literal})
+ changeDelta(form.fighter_upgrade.value,{/literal}{$shipinfo.fighter}{literal})
+ changeDelta(form.sensors_upgrade.value,{/literal}{$shipinfo.sensors}{literal})
+ changeDelta(form.beams_upgrade.value,{/literal}{$shipinfo.beams}{literal})
+ changeDelta(form.armor_upgrade.value,{/literal}{$shipinfo.armor}{literal})
+ changeDelta(form.cloak_upgrade.value,{/literal}{$shipinfo.cloak}{literal})
+ changeDelta(form.torp_launchers_upgrade.value,{/literal}{$shipinfo.torp_launchers}{literal})
+ changeDelta(form.shields_upgrade.value,{/literal}{$shipinfo.shields}{literal})
+ changeDelta(form.ecm_upgrade.value,{/literal}{$shipinfo.ecm}{literal})
{/literal}{$fighter_form}
{$torpedo_form}
{$armor_form}
{literal};

form.total_cost2.value = Comma(form.total_cost.value);
		if (form.total_cost.value > {/literal}{$playerinfo.credits}{literal})
		{
		form.total_cost.value = '{/literal}{$l_no_credits}{literal}';
		form.total_cost2.value = form.total_cost.value;
//		form.total_cost.value = 'You are short '+(form.total_cost.value - {/literal}{$playerinfo.credits}{literal}) +' credits';
		}
		form.total_cost.length = form.total_cost.value.length;

	form.engine_costper.value=Comma(changeDelta(form.engine_upgrade.value,{/literal}{$shipinfo.engines}{literal}));
	form.power_costper.value=Comma(changeDelta(form.power_upgrade.value,{/literal}{$shipinfo.power}{literal}));
	form.fighter_costper.value=Comma(changeDelta(form.fighter_upgrade.value,{/literal}{$shipinfo.fighter}{literal}));
	form.sensors_costper.value=Comma(changeDelta(form.sensors_upgrade.value,{/literal}{$shipinfo.sensors}{literal}));
	form.beams_costper.value=Comma(changeDelta(form.beams_upgrade.value,{/literal}{$shipinfo.beams}{literal}));
	form.armor_costper.value=Comma(changeDelta(form.armor_upgrade.value,{/literal}{$shipinfo.armor}{literal}));
	form.cloak_costper.value=Comma(changeDelta(form.cloak_upgrade.value,{/literal}{$shipinfo.cloak}{literal}));
	form.torp_launchers_costper.value=Comma(changeDelta(form.torp_launchers_upgrade.value,{/literal}{$shipinfo.torp_launchers}{literal}));
	form.hull_costper.value=Comma(changeDelta(form.hull_upgrade.value,{/literal}{$shipinfo.hull}{literal}));
	form.shields_costper.value=Comma(changeDelta(form.shields_upgrade.value,{/literal}{$shipinfo.shields}{literal}));
	form.ecm_costper.value=Comma(changeDelta(form.ecm_upgrade.value,{/literal}{$shipinfo.ecm}{literal}));
	}
	// -->
	</SCRIPT>

{/literal}
{$cleanjs}

<FORM name="upgtradesview" ACTION=port_purchase.php METHOD=POST>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="header"><h3>{$l_port_welcome}</h3></td>
  </tr>
  <tr>
    <td class="leftColumn"><div align="center"><img src="images/ports/port_upgrades.gif" alt="upgrade" /><br><b>{$l_upgrade}</b></div></td>
</td>
  </tr>
  <tr>
    <td align="center" class="portfooter">{$l_creds_to_spend}
    	{if $allow_ibank}
    		<br>{$l_ifyouneedmore}
    	{/if}
    </td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
		<TR>
		<TD class="leftBuyColumn"><B>{$l_item}</B></TD>
		<TD class="centerColumn"><B>{$l_cost}</B></TD>
		<TD class="rightBuyColumn"><B>{$l_current}/{$l_max}</B></TD>
		<TD class="centerColumn"><B>{$l_buy} {$l_max}</B></TD>
		<TD class="rightBuyColumn"><B>{$l_buy} {$l_qty}</B></TD>
		</tr>
		<TR>
		<TD class="leftBuyColumn">{$l_fighters}</TD>
		<TD class="centerColumn">{$fighter_cost}</TD>
		<TD class="rightBuyColumn">{$fighter_current}</TD>
	{if $total_fighters != $fighter_max}
		<td class="centerColumn"><a href="#" onClick="MakeMax('fighter_number', {$fighter_free});countTotal();return false;"; ONBLUR="countTotal()">{$number_fighter_free}</a></TD>
		<TD class="rightBuyColumn"><INPUT TYPE="TEXT" class="inputcss" NAME="fighter_number" SIZE="6" VALUE="0" ONBLUR="countTotal()"></td>
	{else}
		<td class="centerColumn">At Max</td>
		<TD class="rightBuyColumn"><input type="text" readonly class="inputcss" NAME="fighter_number" VALUE="{$l_full}" ONBLUR="countTotal()" tabindex="-1"></td>
	{/if}
		</tr>
		<tr>
		<TD class="leftBuyColumn">{$l_torps}</TD>
		<TD class="centerColumn">{$torp_cost}</TD>
		<TD class="rightBuyColumn">{$torp_current}</TD>
	{if $total_torps != $torpedo_max}
		<td class="centerColumn"><a href="#" onClick="MakeMax('torpedo_number', {$torpedo_free});countTotal();return false;"; ONBLUR="countTotal()">{$number_torpedo_free}</a></TD>
		<TD class="centerColumn"><INPUT TYPE="TEXT" class="inputcss" NAME="torpedo_number" SIZE="6" VALUE="0" ONBLUR="countTotal()"></td>
	{else}
		<td class="centerColumn">At Max</td>
		<TD class="centerColumn"><input type="text" readonly class="inputcss" NAME="torpedo_number" VALUE="{$l_full}" ONBLUR="countTotal()" tabindex="-1"></td>
	{/if}
		</TR>
		<TR>
		<TD class="leftBuyColumn">{$l_armorpts}</TD>
		<TD class="centerColumn">{$armor_cost}</TD>
		<TD class="rightBuyColumn">{$armor_current}</TD>
	{if $total_armor != $armor_max}
		<td class="centerColumn"><a href="#" onClick="MakeMax('armor_number', {$armor_free});countTotal();return false;"; ONBLUR="countTotal()">{$number_armor_free}</a></TD>
		<TD class="centerColumn"><INPUT TYPE="TEXT" class="inputcss" NAME="armor_number" SIZE="6" VALUE="0" ONBLUR="countTotal()"></td>
	{else}
		<td class="centerColumn">At Max</td>
		<TD class="centerColumn"><input type="text" readonly class="inputcss" NAME="armor_number" VALUE="{$l_full}" tabindex="-1" ONBLUR="countTotal()"></td>
	{/if}
		</TR>
	 </TABLE>

<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="leftBuyColumn" nowrap><b>{$l_ship_levels}</b></td>
    <td class="rightBuyColumn"><b>{$l_cost}</b></td>
    <td class="centerColumn" nowrap><b>{$l_current_level}</b></td>
    <td class="rightBuyColumn"><b>{$l_ports_needrepair}</b></td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_hull}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="hull_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.hull}</td>
    <td class="rightBuyColumn">{$hull_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_engines}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="engine_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.engines}</td>
    <td class="rightBuyColumn">{$engine_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_power}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="power_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.power}</td>
    <td class="rightBuyColumn">{$power_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_fighter}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="fighter_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.fighter}</td>
    <td class="rightBuyColumn">{$fighter_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_sensors}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="sensors_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.sensors}</td>
    <td class="rightBuyColumn">{$sensors_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_beams}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="beams_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.beams}</td>
    <td class="rightBuyColumn">{$beams_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_armor}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="armor_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.armor}</td>
    <td class="rightBuyColumn">{$armor_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_cloak}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="cloak_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.cloak}</td>
    <td class="rightBuyColumn">{$cloak_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_ecm}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="ecm_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.ecm}</td>
    <td class="rightBuyColumn">{$ecm_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_torp_launch}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="torp_launchers_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.torp_launchers}</td>
    <td class="rightBuyColumn">{$torp_launchers_dropdown}</td>
  </tr>

  <tr>
    <td class="leftBuyColumn" nowrap>{$l_shields}</td>
    <td class="rightBuyColumn">	 
		<input type="text" readonly class="inputcss" style="text-align:right" size="32" name="shields_costper" VALUE="0" tabindex="-1" {$onblur}>
	</td>
    <td class="centerColumn">{$shipinfo.shields}</td>
    <td class="rightBuyColumn">{$shields_dropdown}</td>
  </tr>
  <tr><td colspan="4" align="center" class="portfooter">{$l_totalcost} <input type="text" class="inputcss" style="text-align:right" name="total_cost2" size="32" value="0" {$onfocus} {$onblur} {$onchange} {$onclick}><br><br>
	<input type="hidden" name="total_cost" value="0">
  	<input name="perform" type="submit" class="groovybutton" value="{$l_buy}" {$onclick} onMouseOver="goLite(this.form.name,this.name)" onMouseOut="goDim(this.form.name,this.name)"/>
  	<br><br>{$gotomain}</td></tr>
</table>

{if $artifactcount > 0}
	<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
		<tr>
		{foreach key=key value=item from=$artifactname}
			<td align="center" class="portfooter">
			<a href="artifact_grab.php?artifact_id={$artifact_id[$key]}" onMouseover="ddrivetip('{$artifactname[$key]}','{$artifact_description[$key]}');" onMouseout="hideddrivetip()">
			<img src="images/artifacts/{$artifactimage[$key]}.gif" border=0></a><BR>
			<br><b>({$artifactname[$key]})</b>
			{if $key == 2 or $key == 5 or $key == 8 or $key == 11 or $key == 14}
			</td></tr>
				{if $key != $artifactcount - 1}
					<tr>
				{/if}
			{else}
			</td>
			{/if}
		{/foreach}
		<tr>
	</table>
{/if}
</form>
</td></tr></table>
