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
<br>
</td></tr></table>
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
    <td class="footer"><div>&nbsp;&nbsp;<a href="http://www.aatraders.com">{$l_footer_title}</a></div><div>&nbsp;&nbsp;<a href="http://www.springfield.net">Springfield Net</a></div></td>
	<td align="center" class="footer" width="33%" id="OTL_clock">
			&nbsp;
	</td>
    <td class="footer" width="33%" align="right">
     <div id="smedia">
<ul id="socialicons">
<li class="facebook"> <a target="_blank" href="http://www.facebook.com/aatrade"></a> </li> 
 <li class="twitter"><a target="_blank" href="https://twitter.com/#!/aatrade"></a> </li>
</ul>
</div>
   <div style="clear:both;"> &#169; 2003-{php}echo date("Y");{/php} <a href="docs/copyright.htm">AATRADE Development Group</a>&nbsp;&nbsp;</div>
   
    </td>
 </tr>
  <tr> 
    <td class="footer">&nbsp;&nbsp;</td>
    <td  valign="top" align="center" class="footer" width="34%">{$l_footer_onlinereset} {$onlinetime_reset}</td>
    <td class="footer" width="34%" align="right" >{$query_count} queries in {$time_total} seconds&nbsp;&nbsp;</td>
  </tr>
</table>

{$banner_bottom}

{if $query_debug == true }
<SCRIPT language=javascript>
	_query_debug_console = window.open("","Query Debug","width=750,height=600,resizable,scrollbars=yes");
	_query_debug_console.document.write("<HTML><TITLE>Query Debug Console</TITLE><BODY onload='self.focus();' bgcolor=#ffffff>");
	_query_debug_console.document.write("<table border=0 width=100%>");
	_query_debug_console.document.write("<tr bgcolor=#cccccc><th colspan=2>Query Debug Console</th></tr>");
	_query_debug_console.document.write("<tr bgcolor=#cccccc><td colspan=2><b>Included page queries (load time in seconds):</b></td></tr>");
	{foreach key=key value=sql from=$query_list}
		_query_debug_console.document.write("<tr bgcolor={if $key % 2}#eeeeee{else}#fafafa{/if}>");
		_query_debug_console.document.write('<td width="75%">{$query_list[$key]|strip|addslashes }<hr><font color=\"red\"><b>{$query_list_errors[$key]|strip|addslashes}</b></font></td>');
		_query_debug_console.document.write("<td width=\"25%\"><font color=\"red\"><b><i>({$query_list_time[$key]|string_format:"%.5f"} seconds)</i></b></font></td></tr>");
	{/foreach}
	_query_debug_console.document.write("</table>");
	_query_debug_console.document.write("</BODY></HTML>");
	_query_debug_console.document.close();
</SCRIPT>
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

function goLite_change(FRM,BTN)
{
   window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0099FF";
   window.document.forms[FRM].elements[BTN].style.borderStyle = "inset";
}

function goDim_change(FRM,BTN)
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
			onMouseOver="goLite_change(this.form.name,this.name)"
			onMouseOut="goDim_change(this.form.name,this.name)"
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
			onMouseOver="goLite_change(this.form.name,this.name)"
			onMouseOut="goDim_change(this.form.name,this.name)"
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
