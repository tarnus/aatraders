<?php
// Step 20 - Set universe tot number of sectors, game end date and select setup file to use.
$title = array();
$body = array();

$title[0] = "Number of Galaxies";
$body[0] = "You can select the number of Galaxies to create for the game.  There are single wormholes that connect each galaxy.<br><br>This option is disabled at this time.";
$title[1] = "Number of Sectors";
$body[1] = "You can select the number of Sectors to be used in the game.  If you have selected more than one Galaxy the total number of sectors will be evenly distributed between each Galaxy.  If you have 5 Galaxies and a total of 5,000 sectors then each Galaxy will contain 1000 sectors.";
$title[2] = "Alliance Password";
$body[2] = "Password to access the Alliance player ship.  The password defaults to the admin password for this game.";
$title[3] = "Federation Password";
$body[3] = "Password to access the Federation player ship.  The password defaults to the admin password for this game.";
$title[4] = "Independent Password";
$body[4] = "Password to access the Independent player ship.  The password defaults to the admin password for this game.";
$title[5] = "Game Reset Date";
$body[5] = "This is the date you would like the game to reset.  When the date is reached the server will close the server.  New player and Player Login will be disabled.<br><br>The scheduler will be disabled so nothing will be updated.  The server will continue to report to the server list.<br><br>Any profiles on the server will be sent to the profile server signifying a completed game.";
$title[6] = "Tournament Start Date";
$body[6] = "When Tournament Mode is enabled players can create new accounts and will be taken to a special screen that will allow them to use the shoutbox, change options, create teams, use both chat rooms and team forums.  When the date is reached Tournament Mode is disabled, new user signups are disabled and regular gameplay is enabled.";
$title[7] = "Setup File";
$body[7] = "These are setup files that will allow different configurations for each game.";

echo "<table>";
echo "<tr><td><b><u>Base/Planet Setup</u></b></td><td>Suggested value &nbsp;</td><td>Safe field range</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[0]', '$body[0]');\" onMouseout=\"hideddrivetip()\"><td>Number of Galaxies &nbsp;</td><td><input type=text name=galaxies size=2 maxlength=2 value=1></td><td>[1-5]</td></tr>";
if($is_safe_mode)
	$max_sectors = "15,000";
else
	$max_sectors = "50,000";
echo "<tr onMouseover=\"ddrivetip('$title[1]', '$body[1]');\" onMouseout=\"hideddrivetip()\"><td>Number of Sectors &nbsp;</td><td><input type=text name=sektors size=5 maxlength=6 value=5000></td><td>[100-$max_sectors]</td></tr>";

echo "<tr><td colspan=3><hr></td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[2]', '$body[2]');\" onMouseout=\"hideddrivetip()\"><td>Alliance Password &nbsp;</td><td><input type=text name=alliance_password size=16 maxlength=16 value=$adminpass></td><td>&nbsp;</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[3]', '$body[3]');\" onMouseout=\"hideddrivetip()\"><td>Federation Password &nbsp;</td><td><input type=text name=federation_password size=16 maxlength=16 value=$adminpass></td><td>&nbsp;</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[4]', '$body[4]');\" onMouseout=\"hideddrivetip()\"><td>Independent Password &nbsp;</td><td><input type=text name=independent_password size=16 maxlength=16 value=$adminpass></td><td>&nbsp;</td></tr>";

echo "</table><br><br><table>";
echo "<tr onMouseover=\"ddrivetip('$title[5]', '$body[5]');\" onMouseout=\"hideddrivetip()\"><td align=\"center\">Set the date you would like to schedule a game reset.	Set to all zeros for no reset date.<br><br>";
$thedate = date("Y-m-d");
$yr=strval(AAT_substr($thedate,0,4)); 
?>
Month: <select name="reset_month">
<option value="00">00
<?php
for($x=1;$x <=12;$x++){
	if (AAT_strlen($x) < 2){
		$x="0".$x;
	}
?>
	<option value="<?=$x;?>"><?=$x;?>
<?php
}?>
</select>
&nbsp;&nbsp;&nbsp;Day: </select><select name="reset_day">
<option value="00">00
<?php
for($x=1;$x <=31;$x++){
	if (AAT_strlen($x) < 2){
		$x="0".$x;
	}
?>
	<option value="<?=$x;?>"><?=$x;?>
<?php
}?>
</select>
&nbsp;&nbsp;&nbsp;Year: </select><select name="reset_year">
<option value="0000">0000
<?php
for($x=$yr;$x <=$yr+5;$x++){?>
	<option value="<?=$x;?>"><?=$x;?>
<?php
}
?>
</select> 
<br><br>
</td><tr>
<tr onMouseover="ddrivetip('<?php echo $title[6]; ?>', '<?php echo $body[6]; ?>');" onMouseout="hideddrivetip()"><td align="center">If you are running a Tournament set the starting date for the Tournament.  If you are not running a tournament leave the date set to zeros.<br><br>
Month: <select name="tournament_month">
<option value="00">00
<?php
for($x=1;$x <=12;$x++){
	if (AAT_strlen($x) < 2){
		$x="0".$x;
	}
?>
	<option value="<?=$x;?>"><?=$x;?>
<?php
}?>
</select>
&nbsp;&nbsp;&nbsp;Day: </select><select name="tournament_day">
<option value="00">00
<?php
for($x=1;$x <=31;$x++){
	if (AAT_strlen($x) < 2){
		$x="0".$x;
	}
?>
	<option value="<?=$x;?>"><?=$x;?>
<?php
}?>
</select>
&nbsp;&nbsp;&nbsp;Year: </select><select name="tournament_year">
<option value="0000">0000
<?php
for($x=$yr;$x <=$yr+5;$x++){?>
	<option value="<?=$x;?>"><?=$x;?>
<?php
}
?>
</select> 
<br><br>
</td><tr>
<tr onMouseover="ddrivetip('<?php echo $title[7]; ?>', '<?php echo $body[7]; ?>');" onMouseout="hideddrivetip()"><td align="center">Setup File: <select name="setup_file">
<?php
$filelist = get_dirlist($gameroot."support/");
$newcommands = 0;
for ($c=0; $c<count($filelist); $c++) { 
	$filenameroot =  str_replace(".ini", "", $filelist[$c]); 
	if(strstr($filelist[$c], "setup_")){
?>
		<option value="<?=$filelist[$c];?>" <?php
		if($filelist[$c] == "setup_default")
			echo " selected";
		?>><?=str_replace("setup_", "", $filenameroot);?>
<?php
	}
}?>
</select><br><br>
</td></tr></table>
<?php
echo "<input type=hidden name=step value=20>";
echo "<input type=reset value=Reset>";
echo "<BR><BR><FONT COLOR=RED>";
echo "WARNING: ALL TABLES WILL BE DROPPED AND THE GAME WILL BE RESET WHEN YOU CLICK 'CONTINUE'!</FONT></font>";
?>