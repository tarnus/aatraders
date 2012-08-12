<?php
// 2: Configuration
// This tool will allow editing of any configuration variable used in the game.  There are almost 300 configuration variables.

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

if($command == "save"){
	echo "<tr><td><table><tr><td>";
	for($i = 0; $i < $count; $i++){

		if ($name[$i] == 'enable_gzip')
		{
			if(extension_loaded("zlib"))
			{
				if (get_cfg_var('zlib.output_compression'))
				{
					$value[$i] = 0;
				}
			}
		}

		echo "Updating config variable: <b><i>$name[$i]</i></b> = <b>$value[$i]&nbsp;</b><br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='$value[$i]' WHERE name='$name[$i]'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET ticks_full='$value[$i]' WHERE sched_file='$name[$i].inc'");
	}

	echo "<br><br><b>Variable Update Complete - <i>$game_name</i></b><br><br>";
	unset($command);

	$filename = $gameroot . "support/variables" . $game_number . ".inc";
	$file = fopen($filename,"w") or die ("Failed opening file: enable write permissions for '$filename'");
	echo "<b>Saving $filename</b><br><br>";
	
	$debug_query = $db->Execute("SELECT * FROM {$db_prefix}config_values");
	db_op_result($debug_query,__LINE__,__FILE__);

	fwrite($file,"<?\n"); 
	while (!$debug_query->EOF && $debug_query)
	{
		$row = $debug_query->fields;
		$db_config_name = $row['name'];
		$db_config_value = $row['value'];
//		echo "Writing data: " . $db_config_name . "=\"" . $db_config_value . "\";<br>"; 
		fwrite($file,"$" . $db_config_name . "=\"" . $db_config_value . "\";\n"); 
		$debug_query->MoveNext();
	}
	fwrite($file,"?>\n"); 
	fclose($file);
	echo "<font color=\"lime\"><b>Completed.</b></font><br><br></td><tr></table></td><tr>";
}

if(empty($section) and $command != "save"){
	echo "<tr><td><table align=\"center\"><tr><td>Select the configuration group you would like to edit:<BR><BR>\n";
	echo "<form action=\"admin.php\" method=\"post\">\n";
	echo "  <select name=\"section\">\n";
	$debug_query = $db->Execute("SELECT distinct section FROM {$db_prefix}config_values");
	db_op_result($debug_query,__LINE__,__FILE__);
	while (!$debug_query->EOF && $debug_query)
	{
		$row = $debug_query->fields;
		echo "	<option value=\"$row[section]\">$row[section]</option>\n";
		$debug_query->MoveNext();
	}
	echo "  </select>\n";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "  <input type=\"hidden\" name=\"admin_password\" value=\"$admin_password\">\n";
	echo "  <input type=\"hidden\" name=\"menu\" value=\"Editor_Configuration\">\n";
	echo "  &nbsp;<input type=\"submit\" value=\"Select\">\n";
	echo "</form><br><br><hr><br>\n</td></tr></table></td></tr>";
}else{
	if($command != "save"){
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
		$template_object->assign('game_number', "$game_number");
		$template_object->assign('admin_password', "$admin_password");
		$template_object->assign('returnlink', "admin.php");
		$template_object->assign('menu', $menu);
		$template_object->assign('count', $count);
		$template_object->assign('db_config_name', $db_config_name);
		$template_object->assign('db_config_input_type', $db_config_input_type);
		$template_object->assign('db_config_input_selections', $db_config_input_selections);
		$template_object->assign('db_config_value', $db_config_value);
		$template_object->assign('db_config_info', $db_config_info);
		$template_object->display("admin/Configuration_Editor.tpl");
	}
}
?>
