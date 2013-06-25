<?php /* V2.10 Template Lite 4 January 2007  (c) 2005-2007 Mark Dickenson. All rights reserved. Released LGPL. 2013-06-22 21:39:48 CDT */  if ($this->_vars['instantmessagecount'] > 0): ?> 
	<?php echo '
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
	'; ?>


	<div id="frame_instant_message" style="position:absolute;border:10px inset #550000;color:white;background:black;">
	<table border=0 width="100%" align="center">
	<tr>
		<td bgcolor="#990000" width="100%" height="96" align="center" valign="middle">
			<b><?php echo $this->_vars['l_instant_messages_waiting']; ?><b><br><br>
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
<?php endif; ?>
<br>
</td></tr></table>
<?php if ($this->_vars['index_page'] != 1): ?>
<?php echo '
<script language="javascript" type="text/javascript">
 var myi = ';  echo $this->_vars['seconds_until_update'];  echo ';
 setTimeout("rmyx();",1000);

  function rmyx()
   {
	myi = myi - 1;
	if (myi <= 0)
	 {
		 myi = ';  echo $this->_vars['scheduler_ticks'];  echo ' * 60;
	 }
	document.getElementById("myx").innerHTML = myi;
	setTimeout("rmyx();",1000);
   }
</script>
'; ?>

<table width="100%" border=0 cellspacing=0 cellpadding=0>
	<tr>		  
	  <td align=center class="footer"><b><span id=myx class="footer"><?php echo $this->_vars['seconds_until_update']; ?></span></b> <?php echo $this->_vars['footer_until_update']; ?> <br> 
<?php echo $this->_vars['footer_players_online']; ?> - <?php echo $this->_vars['footer_players_open']; ?><br>
<a href="news.php" class="footer"><?php echo $this->_vars['l_footer_news']; ?></a></td>
	</tr>			   
  </table>
<?php endif; ?>
		<?php if ($this->_vars['player_online_timelimit'] != 0): ?>
<?php echo '
	<SCRIPT LANGUAGE="JavaScript">
<!--

var count=';  echo $this->_vars['player_onlinetime_left'];  echo ';

function to10String(n) {
  s=""
  if(n<10) s+="0"
  return s+n.toString();
}
 
function onlinetimeleftcountdown() {
  if(count<=0)
    {document.getElementById(\'OTL_clock\').innerHTML=\'';  echo $this->_vars['l_footer_onlinecountdown'];  echo '\'+\'--:--:--\';
     return;
   }
  clockvaluesec=to10String(count%60);
  countmin=Math.floor(count/60);
  clockvaluemins=to10String(countmin%60);
  counthour=Math.floor(countmin/60);
  document.getElementById(\'OTL_clock\').innerHTML=\'';  echo $this->_vars['l_footer_onlinecountdown'];  echo '\'+to10String(counthour%24)+\':\'+clockvaluemins+\':\'+clockvaluesec;
  count--;
  setTimeout("onlinetimeleftcountdown()",1000);
}

setTimeout("onlinetimeleftcountdown()",1);
// end hiding script-->
</SCRIPT>
'; ?>

		<?php endif; ?>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td class="footer">&nbsp;&nbsp;<a href="http://www.springfield.net">Springfield Net</a></td>
	<td align="center" class="footer" width="33%" id="OTL_clock">
			&nbsp;
	</td>
    <td class="footer" width="33%" align="right">&#169; 2003-<?php extract($this->_vars, EXTR_REFS);  echo date("Y"); ?> <a href="docs/copyright.htm">AATRADE Development Group</a>&nbsp;&nbsp;</td>
 </tr>
  <tr> 
    <td class="footer">&nbsp;&nbsp;<a href="http://www.aatraders.com"><?php echo $this->_vars['l_footer_title']; ?></a></td>
    <td align="center" class="footer" width="34%"><?php echo $this->_vars['l_footer_onlinereset']; ?> <?php echo $this->_vars['onlinetime_reset']; ?></td>
    <td class="footer" width="34%" align="right" ><?php echo $this->_vars['query_count']; ?> queries in <?php echo $this->_vars['time_total']; ?> seconds&nbsp;&nbsp;</td>
  </tr>
</table>

<?php echo $this->_vars['banner_bottom']; ?>

<?php if (( ! empty ( $this->_vars['maindiv'] ) )): ?>
</div>
<?php endif; ?>

<?php if ($this->_vars['template_changed'] == 1): ?>
<?php echo '
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
'; ?>


<div id="frame_template_change" style="position:absolute;border:10px inset #4455aa;color:white;background:black;">
<table border=0 width="100%" align="center">
<tr>
	<td bgcolor="#000000" width="100%" align="center" valign="middle">
		<?php echo $this->_vars['l_templatechange']; ?><br><br>
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
<?php endif; ?>

<?php if ($this->_vars['is_adminpopup'] == 1): ?> 
	<?php echo '
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
	'; ?>


	<div id="frame_admin_popup" style="border:10px outset #005500;color:white;background:black;">
	<table border=0 width="100%" align="center">
	<tr>
		<td bgcolor="#009900" width="100%" height="96" align="center" valign="middle">
			<br><font size="4"><b><u>Notice from the Admin</u></b></font><br><br>
			<b><?php echo $this->_vars['adminpopup']; ?><b><br><br>
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
<?php endif; ?>

</body>
</html>
