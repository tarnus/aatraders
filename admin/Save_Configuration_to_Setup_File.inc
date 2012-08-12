<?php
// 5: Save Configuration to Setup File
// This tool will allow you to save the current game configuration over an existing setup file in the support directory or save as a new setup file.  This mainly used to creating a setup to be used when resetting a game so you are not required to reconfigure the game each time.

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

echo"<tr><td><div align=\"center\">";
if ($command=="SAVE")
{
	echo "<b>Saving setup_" . $setup_file . ".ini</b><br><br>";
}
elseif ($command=="OVERWRITE")
{
	echo "<b>Overwriting setup_" . $setup_file . ".ini</b><br><br>";
}
 
if ($command=="SAVE" || $command=="OVERWRITE")
{
	$filename = $gameroot . "support/setup_" . $setup_file . ".ini";
	$file = fopen($filename,"w") or die ("Failed opening file: enable write permissions for '$filename'");
	echo "<b>Saving setup_" . $setup_file . ".ini</b><br><br>";
	
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}config_values order by section");
	db_op_result($debug_query,__LINE__,__FILE__);

	while (!$debug_query->EOF && $debug_query)
	{
		$row = $debug_query->fields;
		$db_config_name = $row['name'];
		$db_config_value = $row['value'];
		$db_config_info = stripslashes($row['description']);
		if($db_config_section != trim($row['section']) and trim($row['section']) != ""){
			$db_config_section = trim($row['section']);
			if($db_config_section != "Reset Date"){
				echo "<font size=1><br>Writing data: [" . $db_config_section . "]</font><br>"; 
				fwrite($file,"\n[". $db_config_section . "]\n"); 
			}
		}
		if($db_config_name != "scheduled_reset" && $db_config_name != "reset_date")
		{
			echo "<font size=1>Writing data: " . $db_config_name . "=\"" . $db_config_value . "\"; ;" . $db_config_info . "</font><br>"; 
			fwrite($file,$db_config_name . "=\"" . $db_config_value . "\"; " . $row['input_type'] . " ; " . stripslashes($row['input_selections']) . " ; " . $db_config_info . "\n"); 
		}
		$debug_query->MoveNext();
	}

	fclose($file);

	echo "Success.";
}
else
{
?>
	<FORM ACTION=admin.php METHOD=POST>
	<INPUT TYPE=HIDDEN NAME=admin_password VALUE=<?=$admin_password;?>>
	<input type="hidden" name="game_number" value="<?=$game_number;?>">
	<INPUT TYPE=HIDDEN NAME=menu VALUE="Save_Configuration_to_Setup_File">
	<table>
	<TR><TD>Enter new setup filename&nbsp;<input type="text" name="setup_file" size="15" maxlength="15">&nbsp;&nbsp;<INPUT TYPE=SUBMIT NAME=command VALUE="SAVE"></TD></TR>
	</table></form>

	<FORM ACTION=admin.php METHOD=POST>
	<INPUT TYPE=HIDDEN NAME=admin_password VALUE=<?=$admin_password;?>>
	<input type="hidden" name="game_number" value="<?=$game_number;?>">
	<INPUT TYPE=HIDDEN NAME=menu VALUE="Save_Configuration_to_Setup_File">
<table>
		<tr><td>Overwrite Setup File: <select name="setup_file">
<?php
	$filelist = get_dirlist($gameroot."support/");
	$newcommands = 0;
	for ($c=0; $c<count($filelist); $c++) { 
		$filenameroot =  str_replace(".ini", "", $filelist[$c]); 
		if(strstr($filelist[$c], "setup_")){
		?>
		<option value="<?=str_replace("setup_", "", $filenameroot);?>"><?=str_replace("setup_", "", $filenameroot);?>
		<?php
		}
	}?>
		</select>&nbsp;&nbsp;<INPUT TYPE=SUBMIT NAME=command VALUE="OVERWRITE">
	</td></tr></table></form>
<?php
}
?>
</div></td></tr>