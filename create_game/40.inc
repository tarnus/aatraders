<?php
// Step 40 - Edit game configuration variables from config database

echo "<br><b>You should now edit any of the games Configuration Settings at this time.</b><br><br>";

if($command == "save"){
	echo "<table><tr><td>";
	for($i = 0; $i < $count; $i++){
		echo "Updating config variable: <b><i>$name[$i]</i></b> = <b>$value[$i]&nbsp;</b>";
		if($name[$i] != "silent")
	 		 $$name[$i] = $value[$i];	

		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='$value[$i]' WHERE name='$name[$i]'");
		db_op_result($debug_query,__LINE__,__FILE__);
	}

	echo "<br><br><b>Variable Update Complete - <i>$game_name</i></b><br><br></td><tr></table>";
	$command = "";
	$section = "";

	exportvariables();
}

echo "Section $section = command $command<br>";
$silent = 1;

if((empty($section) or !isset($section)) and $command != "save"){
	echo "Select the Configuration Section you would like to edit:<BR><BR>\n";
	echo "<form action=\"create_game.php\" method=\"post\" enctype=\"multipart/form-data\">\n";

	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">";
	}

	echo "	<select name=\"section\">\n";
	$debug_query = $db->Execute("SELECT distinct section FROM {$db_prefix}config_values");
	db_op_result($debug_query,__LINE__,__FILE__);
	while (!$debug_query->EOF && $debug_query)
	{
		$row = $debug_query->fields;
		echo "	<option value=\"$row[section]\">$row[section]</option>\n";
		$debug_query->MoveNext();
	}
	$debug_query->close();
	echo "	</select>\n";
	echo "<input type=hidden name=step value=39.99>";
	echo "	&nbsp;<input type=\"submit\" NAME=command value=\"Select\">\n";
	echo "</form><br><br><hr><br>\n";
	echo "<form action=create_game.php method=post enctype=\"multipart/form-data\">";

	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">";
	}

	echo "<input type=hidden name=step value=40>
		<INPUT TYPE=SUBMIT NAME=command VALUE=\"Continue Universe Creation\">
		</form>";
}else{
	// Get the config_values from the DB - silently.
	$silent = 1;
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}config_values where section='$section'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$count = 0;
	while (!$debug_query->EOF && $debug_query)
	{
		$row = $debug_query->fields;
		$db_config_name[$count] = $row['name'];
		$db_config_value[$count] = $row['value'];
		$db_config_input_type[$count] = $row['input_type'];
		$db_config_input_selections[$count] = $row['input_selections'];
		$db_config_info[$count] = $row['description'];
		$count++;
		$debug_query->MoveNext();
	}
	$debug_query->close();
?>
	<br><br>
	<form action=create_game.php method=post enctype="multipart/form-data">
<?php
	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">";
	}
?>
	<input type=hidden name=step value=39.99>
	<table border=1 cellspacing=1 cellpadding=5>
	<tr>
	<td><b>Variable Name</b></td>
	<td><b>Variable Value</b></td>
	<td><b>Variable Description</b></td>
	</tr>
<?php
	for($i = 0; $i < $count; $i++){
		echo"<tr>\n";
		echo"<td>\n";
		echo"<b>$db_config_name[$i] :</b>&nbsp;&nbsp;\n";
		echo"</td>\n";
		echo" <td>\n";
		echo"<input type=\"hidden\" name=\"name[$i]\" value=\"$db_config_name[$i]\">\n";
		if($db_config_input_type[$i] == 'list')
		{
			$selections = explode(",", $db_config_input_selections[$i]);
			$selection_count = count($selections);
			echo "<select name=\"value[$i]\">";
			for($item = 0; $item < $selection_count; $item++)
			{
				$values = explode("=", $selections[$item]);
				$value = trim($values[0]);
				if($value == $db_config_value[$i])
					$checked = "selected";
				else $checked = "";
				echo "<option value=\"$value\" $checked>" . trim($values[1]) . "</option>\n";
			}
			echo "</select>";
		}
		else
		if($db_config_input_type[$i] == 'radio')
		{
			$selections = explode(",", $db_config_input_selections[$i]);
			$selection_count = count($selections);
			for($item = 0; $item < $selection_count; $item++)
			{
				$values = explode("=", $selections[$item]);
				$value = trim($values[0]);
				if($value == $db_config_value[$i])
					$checked = "checked";
				else $checked = "";
				echo"<input type=\"radio\" name=\"value[$i]\" value=\"" . $value . "\" $checked>" . trim($values[1]) . "<br>\n";
			}
		}
		else
		{
			echo"<input type=\"text\" name=\"value[$i]\" value=\"$db_config_value[$i]\" size=\"40\">\n";
		}
		echo"</td>\n";
		echo"<td>\n";
		echo "<font color=\"#00ff00\"><i><b>$db_config_info[$i]</b></i></font>\n";
		echo"</td>\n";
		echo"</tr>\n";
	}
?>
	<tr><TD ALIGN=center colspan=3><INPUT TYPE=SUBMIT NAME=command VALUE="save">
	<input type=hidden name=count value=<?=$count;?>>
	</td></td>
	</table>
	</form><br><br><hr><br>
	<form action=create_game.php method=post enctype="multipart/form-data">
<?php
	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">";
	}
?>
	<input type=hidden name=step value=40>
	<INPUT TYPE=SUBMIT NAME=command VALUE="Continue Universe Creation">
	</form>
<?php
}
?>