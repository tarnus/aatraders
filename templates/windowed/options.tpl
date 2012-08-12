<h1>{$title}</h1>
{literal}
<style type="text/css">
<!--
.templatestyle      { border-style:none;font-family: verdana;font-size:8pt;background-color:#000000;color:#c0c0c0;}
-->
</style>
{/literal}

<form name="optiontemplate" action=options_save.php method=post>
<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">

	<tr bgcolor="#000000">
	  <td>{$l_opt_playername}</td>
	  <td align="left"><input type="text" name="newplayername" size="32" maxlength="50" value="{$playername}"> {$l_opt_playernamecost}</td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
<tr bgcolor="#000000">
	  <td colspan=2><b>{$l_opt_chpass}</b></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_curpass}</td>
	  <td align="left"><input type=password name=oldpass size=32 maxlength={$maxlen_password} value=""></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_newpass}</td>
	  <td align="left"><input type=password name=newpass1 size=32 maxlength={$maxlen_password} value=""></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_newpagain}</td>
	  <td align="left"><input type=password name=newpass2 size=32 maxlength={$maxlen_password} value=""></td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
{if $allow_shipnamechange == 1}
	<tr bgcolor="#000000">
	  <td>{$l_opt_shipname}</td>
	  <td align="left"><input type="text" name="newshipname" size="32" maxlength="50" value="{$oldshipname}"></td>
	</tr>
{/if}
	<tr bgcolor="#000000">
	  <td>{$l_home_planet}:</td>
	  <td align="left"><select name=newhomeplanet>{$planet_drop_down}</select></td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><b>{$l_opt_lang}</b></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_select}</td>
	  <td align="left"><select size="10" name=newlang>{$lang_drop_down}</select></td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><b>{$l_opt_template}</b></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_select}</td>
	  <td align="left"><select name=newtemplate ONCHANGE="showinfo()">{$template_drop_down}</select></td>
	</tr>
<tr bgcolor="#000000">
	  <td colspan="2" align="center">
	  <table width="100%" border="0" cellspacing="0" cellpadding="0" align="center"><tr><td align="center">
	  <textarea class='templatestyle' rows="10" cols="60" wrap="virtual" name="templateinfo">Author: {$template_author}

Email: {$template_email}

Website: {$template_website}

Description: {$template_description}</textarea> </td><td align="center"><a id="templatelink" href="{$template_picture}" target="_blank"><img id="templateimagesmall" src="{$template_picturesmall}" border=0 width=150 height=150></a></td>
</td></tr>
</table></td>
	</tr>
{literal}
<SCRIPT LANGUAGE="JavaScript">
<!--
var shortcut=document.optiontemplate;
var author=new Array()
{/literal}{$authorarray}{literal}

var email=new Array()
{/literal}{$emailarray}{literal}

var website=new Array()
{/literal}{$websitearray}{literal}

var descriptions=new Array()
{/literal}{$descriptionarray}{literal}

var pictures=new Array()
{/literal}{$picturearray}{literal}

var picturessmall=new Array()
{/literal}{$picturesmallarray}{literal}

function showinfo()
{
	shortcut.templateinfo.value= 'Author: ' + author[shortcut.newtemplate.selectedIndex] + '\n\nEmail: ' + email[shortcut.newtemplate.selectedIndex] + '\n\nWebsite: ' + website[shortcut.newtemplate.selectedIndex] + '\n\nDescription: ' + descriptions[shortcut.newtemplate.selectedIndex]
	shortcut.templateimagesmall.src= picturessmall[shortcut.newtemplate.selectedIndex]
	document.getElementById('templatelink').href = pictures[shortcut.newtemplate.selectedIndex]
}
// -->
</SCRIPT>
{/literal}
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
{if $allow_avatar == 1}
	<tr bgcolor="#000000">
	  <td colspan=2><b>{$l_avatar}</b></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_select}</td>
	  <td bgcolor="#000000" align="left"><img src="images/avatars/{$avatar}">&nbsp;[<a href="options_avatar.php">{$l_set}</a>]</td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
	{if $showteamicon == 1}
	<tr bgcolor="#000000">
	  <td colspan=2><b>{$l_opt_teamicon}</b></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_select}</td>
	  <td bgcolor="#000000" align="left"><img src="images/icons/{$teamicon}">&nbsp;[<a href="options_teamicon.php">{$l_set}</a>]</td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
	{/if}
{/if}
	<tr bgcolor="#000000">
	  <td>{$l_opt_mapwidth}</td>
	  <td align="left"><input type=text name=map_width size=4 maxlength=3 value="{$map_width}"></td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_showshoutbox}</td>
	  <td align="left"><input type="radio" name="show_shoutbox" value="1" 
	  {if $show_shoutbox == 1}
	  	checked
		{/if}>{$l_yes}<br>
	  <input type="radio" name="show_shoutbox" value="0" 
	  {if $show_shoutbox == 0}
	  	checked
		{/if}>{$l_no}
</td>
	</tr>
	<tr bgcolor="#000000">
	  <td>{$l_opt_shownewscrawl}</td>
	  <td align="left"><input type="radio" name="show_newscrawl" value="1" 
	  {if $show_newscrawl == 1}
	  	checked
		{/if}>{$l_yes}<br>
	  <input type="radio" name="show_newscrawl" value="0" 
	  {if $show_newscrawl == 0}
	  	checked
		{/if}>{$l_no}
</td>
	</tr>
	{if $enable_profilesupport == 1}
	<tr bgcolor="#000000">
	  <td colspan=2><br><hr><br></td>
	</tr>
	<tr bgcolor="#000000">
	  <td colspan=2><b>{$l_opt_profiletitle}</b></td>
	</tr>
	<tr bgcolor="#000000">
		{if $registeredprofile == 0}
		  <td colspan=2>{$l_opt_profile}<a href="profile.php">{$l_here}</a>.</td>
		{else}
		  <td colspan=2>{$l_opt_profilereg} - {$l_opt_profilerereg}<a href="profile.php">{$l_here}</a>.<br>
		  {$l_opt_profileupdate}<a href="profile_update.php">{$l_here}</a><br>
		  {$l_opt_profileupdate2}</td>
		{/if}
	</tr>
	{/if}
			<tr>
<td colspan=2>
<input type=submit value={$l_opt_save}>

</form>
</td>
</tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
{if $is_newuserpopup == 1} 
	{literal}
	<style type="text/css">
	#frame_newuser_popup {
		z-index: 5000;
		position:absolute;
		left: 50%; 
		top: 10%;
		width: 600px;
		height: auto;
		margin-left: -300px; /* half of the width  */
		height:100px;
	}
	</style>

	<style type="text/css">
	input.instant_newuser_popup_button
	{
		font-family:Arial,sans-serif;
		font-weight:bold;
		color:#FFFFFF;
		background-color:#0033CC;
		border-style:outset;
	}
	</style>

	<script language="javascript">
	function goLite_newuser_popup(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0099FF";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "inset";
	}

	function goDim_newuser_popup(FRM,BTN)
	{
	window.document.forms[FRM].elements[BTN].style.backgroundColor = "#0033CC";
	window.document.forms[FRM].elements[BTN].style.borderStyle = "outset";
	}
	</script>
	{/literal} 

	<div id="frame_newuser_popup" style="border:10px outset #6da6b1;color:white;background:black;">
	<table border=0 width="100%" align="center">
	<tr>
		<td bgcolor="#5F9FAB" width="100%" height="96" align="center" valign="middle">
			<br><font size="4"><b><u>Notice from the Admin for New Users</u></b></font><br><br>
			<b>{$newuserpopup}<b><br><br>
			<form name="newuser_popup_message">
			<input
				type="button"
				name="instant_newuser_popup_btn1"
				class="instant_newuser_popup_button"
				value="Close Window"
				title="Close Window"
				onMouseOver="goLite_newuser_popup(this.form.name,this.name)"
				onMouseOut="goDim_newuser_popup(this.form.name,this.name)"
				onClick="frame_newuser_popup.style.visibility = 'hidden';"
				>
			</form>
			<br>
		</td>
	</tr>
	</table>
	</div>
{/if}
