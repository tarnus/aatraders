<H1>{$title}</H1>

<table width="300" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
<table width="1" border="0" cellspacing="1" cellpadding="1" align="center" width=600>
<form action="options_teamicon.php" METHOD=POST enctype="multipart/form-data">
<input type="hidden" name="action" value="uploadgraphic">
<tr><td align=center width=600><span class=mnu>{$l_opt_currentavatar}</span></td></tr><tr><td align=center width=600><img src="images/icons/{$currenticon}"><br><br></td></tr>
{if $allow_icon_upload == 1}
	<tr><td align=center width=600><span class=mnu>{$l_opt_uploadavatar}</span></td></tr>
	<tr><td align=center width=600><INPUT TYPE="file" NAME="img_src" ></td></tr>
	<tr><td align=center width=600><span class=mnu>{$l_opt_uploadtypes}</span></td></tr>
	<tr><td align=center width=600><input type="submit" value="{$l_opt_uploadavatar}"><br><br></td></tr>
{/if}
</form>
</table>
				</td>
			</tr>
		</table>
	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>

<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<form action="options_teamicon.php" METHOD=POST enctype="multipart/form-data">
<tr><td align=center width=600><span class=mnu>{$l_opt_directory}</span><select name=gallery>
{php}
for($i = 0; $i < $directorycount; $i++) { 
	echo "<option value=\"" . $directoryitem[$i] . "\" $directoryselect[$i]>" . $directoryitem[$i] . "</option>\n";
}
{/php}
</select>
<br><br><input type="submit" value="{$l_opt_change}"><br><br></td><tr>
</form></table>

<form action="options_teamicon.php" METHOD=POST enctype="multipart/form-data">
<input type="hidden" name="action" value="selectgraphic">
<input type="hidden" name="gallery" value="{$gallery}">
<table width="1" border="0" cellspacing="1" cellpadding="1" align="center">
<tr>
{php}
$rowcount = 0;
for ($c=0; $c<$itemcount; $c++) { 
	echo "<td align=center><img src='images/icons/$gallery/$galleryimage[$c]'><br>";
	echo "<input type=\"radio\" name=\"galleryimage\" value=\"$galleryfile[$c]\" $gallerychecked[$c]></td>";
	$rowcount++;
	if($rowcount == 10){
		echo "</tr><tr>";
		$rowcount = 0;
	}
}

if($rowcount != 0){
	for($i = $rowcount; $i < 10; $i++){
		echo "<td width=64><img src='images/spacer.gif' width=64></td>";
	}
}
if($itemcount == 0){
	echo "<td width=600><img src='images/spacer.gif' width=600 height=1><td></tr>";
	echo "<tr><td width=600 align=center>$l_opt_inuse</td></tr>";
	echo "<tr><td width=600><img src='images/spacer.gif' width=600 height=1><td>";
}
echo "</tr>";

if($itemcount != 0){
	echo"<tr><td colspan=10 align=\"center\"><input type=\"submit\" value=\"{$l_opt_select}\"></td><tr></form>";
}else{
	echo "</table></form>";
}
{/php}

<tr><td colspan=10><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
