{if $instantmessagecount > 0} 
	{literal}
	<style type="text/css">
	#frame_instant_message {
		z-index: 2500;
		position:absolute;
		left: 25%; 
		top: 25%;
		width: 300px;
		height: 100px;
		margin-top: -75px; /* half of the height */
		margin-left: -100px; /* half of the width */
		height:100px;
	}
	</style>

	<style type="text/css">
	input.instant_message_button
	{
		font-family:Arial,sans-serif;
		font-weight:bold;
		color:#FFFFFF;
		background-color:#0099FF;
		border-style:outset;
	}
	</style>

	<script language="javascript">
	function goLite_message(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0099FF";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "inset";
	}

	function goDim_message(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0033CC";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "outset";
	}
	</script>
	{/literal}

	<div id="frame_instant_message" style="position:absolute;border:10px inset #550000;color:white;background:black;">
	<table border=0 width="100%" align="center">
	<tr>
		<td bgcolor="#990000" width="100%" height="96" align="center" valign="middle">
			<b>{$l_instant_messages_waiting}<b><br><br>
			<form name="template_change_later">
			<input
				type="button"
				name="instant_message_btn1"
				class="instant_message_button"
				value="Read Later"
				title="Read Later"
				onMouseOver="goLite_message(this.form.name,this.name)"
				onMouseOut="goDim_message(this.form.name,this.name)"
				onClick="frame_instant_message.style.visibility = 'hidden';"
				>
			</form>
			<form name="template_change_read" ACTION="message_read.php">
			<input
				type="button"
				name="instant_message_btn2"
				class="instant_message_button"
				value="Read Messages Now"
				title="Read Messages Now"
				onMouseOver="goLite_message(this.form.name,this.name)"
				onMouseOut="goDim_message(this.form.name,this.name)"
				onClick="template_change_read.submit();"
				>
			</form>
			<br>
		</td>
	</tr>
	</table>
	</div>
{/if}
{if $currentprogram != "main.inc"}
<br>
</td></tr></table>
{/if}

{if $currentprogram == "main.inc"}
{literal}
<style type="text/css">
<!--
#footer_div {
	font-family: Arial, Helvetica, sans-serif;
	font-size: 10px;
	font-style: normal;
	line-height: normal;
	font-weight: normal;
	font-variant: normal;
	text-transform: none;
	text-decoration: none;
	position: absolute;
	bottom: 0px;
	z-index: -1;
	color: #ffffff;
	background: #222222;
	border-bottom-color: #FFFFFF;
	border-bottom-style: solid;
	border-bottom-width: thin;
	border-top-color: #FFFFFF;
	border-top-style: solid;
	border-top-width: thin;
	border-left-color: #FFFFFF;
	border-left-style: solid;
	border-left-width: thin;
	border-right-color: #FFFFFF;
	border-right-style: solid;
	border-right-width: thin;
	width: 99%;
	left: 5px;
}
-->
</style>
{/literal}

<div class="footer_div" id="footer_div">
{/if}

{if $index_page != 1}
{literal}
<script language="javascript" type="text/javascript">
 var myi = {/literal}{$seconds_until_update}{literal};
 setTimeout("rmyx();",1000);

  function rmyx()
   {
	myi = myi - 1;
	if (myi <= 0)
	 {
		 myi = {/literal}{$scheduler_ticks}{literal} * 60;
	 }
	document.getElementById("myx").innerHTML = myi;
	setTimeout("rmyx();",1000);
   }
</script>
{/literal}
<table width="100%" border=0 cellspacing=0 cellpadding=0>
	<tr>		  
	  <td align=center class="footer"><b><span id=myx class="footer">{$seconds_until_update}</span></b> {$footer_until_update} <br> 
{$footer_players_online} - {$footer_players_open}<br>
<a href="news.php" class="footer">{$l_footer_news}</a></td>
	</tr>			   
  </table>
{/if}
		{if $player_online_timelimit != 0}
{literal}
	<SCRIPT LANGUAGE="JavaScript">
<!--

var count={/literal}{$player_onlinetime_left}{literal};

function to10String(n) {
  s=""
  if(n<10) s+="0"
  return s+n.toString();
}
 
function onlinetimeleftcountdown() {
  if(count<=0)
    {document.getElementById('OTL_clock').innerHTML='{/literal}{$l_footer_onlinecountdown}{literal}'+'--:--:--';
     return;
   }
  clockvaluesec=to10String(count%60);
  countmin=Math.floor(count/60);
  clockvaluemins=to10String(countmin%60);
  counthour=Math.floor(countmin/60);
  document.getElementById('OTL_clock').innerHTML='{/literal}{$l_footer_onlinecountdown}{literal}'+to10String(counthour%24)+':'+clockvaluemins+':'+clockvaluesec;
  count--;
  setTimeout("onlinetimeleftcountdown()",1000);
}

setTimeout("onlinetimeleftcountdown()",1);
// end hiding script-->
</SCRIPT>
{/literal}
		{/if}
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td class="footer">&nbsp;&nbsp;<a href="http://www.springfield.net">Springfield Net</a></td>
	<td align="center" class="footer" width="33%" id="OTL_clock">
			&nbsp;
	</td>
    <td class="footer" width="33%" align="right">&#169; 2003-{php}echo date("Y");{/php} <a href="docs/copyright.htm">AATRADE Development Group</a>&nbsp;&nbsp;</td>
 </tr>
  <tr> 
    <td class="footer">&nbsp;&nbsp;<a href="http://www.aatraders.com">{$l_footer_title}</a></td>
    <td align="center" class="footer" width="34%">{$l_footer_onlinereset} {$onlinetime_reset}</td>
    <td class="footer" width="34%" align="right" >{$query_count} queries in {$time_total} seconds&nbsp;&nbsp;</td>
  </tr>
</table>

{$banner_bottom}

{if (!empty($maindiv))}
</div>
{/if}

{if $currentprogram == "main.inc"}
	</div>
{/if}

{if $template_changed == 1}
{literal}
<style type="text/css">
#frame_template_change {
	z-index: 2500;
	position:absolute;
	left: 50%; 
	top: 50%;
	width: 300px;
	height: 100px;
	margin-top: -75px; /* half of the height */
	margin-left: -175px; /* half of the width */
	height:100px;
}
</style>
<style type="text/css">

input.template_change_button
{
   font-family:Arial,sans-serif;
   font-weight:bold;
   color:#FFFFFF;
   background-color:#0033CC;
   border-style:outset;
}
</style>

<script language="javascript">

function goLite(FRM,BTN)
{
   window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0099FF";
   window.document.forms[FRM].elements[BTN].style.borderStyle = "inset";
}

function goDim(FRM,BTN)
{
   window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0033CC";
   window.document.forms[FRM].elements[BTN].style.borderStyle = "outset";
}
</script>
{/literal}

<div id="frame_template_change" style="position:absolute;border:10px inset #4455aa;color:white;background:black;">
<table border=0 width="100%" align="center">
<tr>
	<td bgcolor="#000000" width="100%" align="center" valign="middle">
		{$l_templatechange}<br><br>
		<form name="template_change_keep">
		<input
			type="button"
			name="template_change_btn1"
			class="template_change_button"
			value="Keep Template"
			title="Keep Template"
			onMouseOver="goLite(this.form.name,this.name)"
			onMouseOut="goDim(this.form.name,this.name)"
			onClick="frame_template_change.style.visibility = 'hidden';"
			>
		</form>
		<form name="template_change_discard" ACTION="options.php">
		<input
			type="button"
			name="template_change_btn2"
			class="template_change_button"
			value="Return to Options"
			title="Return to Options"
			onMouseOver="goLite(this.form.name,this.name)"
			onMouseOut="goDim(this.form.name,this.name)"
			onClick="template_change_discard.submit();"
			>
		</form>
	</td>
</tr>
</table>
	</div>
{/if}

{if $is_adminpopup == 1} 
	{literal}
	<style type="text/css">
	#frame_admin_popup {
		z-index: 2500;
		position:absolute;
		left: 50%; 
		top: 50%;
		width: 300px;
		height: 100px;
		margin-top: -75px; /* half of the height */
		margin-left: -100px; /* half of the width */
		height:100px;
	}
	</style>

	<style type="text/css">
	input.instant_admin_popup_button
	{
		font-family:Arial,sans-serif;
		font-weight:bold;
		color:#FFFFFF;
		background-color:#0033CC;
		border-style:outset;
	}
	</style>

	<script language="javascript">
	function goLite_admin_popup(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0099FF";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "inset";
	}

	function goDim_admin_popup(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0033CC";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "outset";
	}
	</script>
	{/literal}

	<div id="frame_admin_popup" style="border:10px outset #005500;color:white;background:black;">
	<table border=0 width="100%" align="center">
	<tr>
		<td bgcolor="#009900" width="100%" height="96" align="center" valign="middle">
			<br><font size="4"><b><u>Notice from the Admin</u></b></font><br><br>
			<b>{$adminpopup}<b><br><br>
			<form name="admin_popup_message">
			<input
				type="button"
				name="instant_admin_popup_btn1"
				class="instant_admin_popup_button"
				value="Close Window"
				title="Close Window"
				onMouseOver="goLite_admin_popup(this.form.name,this.name)"
				onMouseOut="goDim_admin_popup(this.form.name,this.name)"
				onClick="frame_admin_popup.style.visibility = 'hidden';"
				>
			</form>
			<br>
		</td>
	</tr>
	</table>
	</div>
{/if}

</body>
</html>
