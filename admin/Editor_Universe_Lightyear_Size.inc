<?php
// 2: Universe Lightyear Size
// This tool will allow changing the size of the galaxy's diameter in lightyears.  The higher the diameter of the galaxy the further the distance between sectors requiring higher engine tech to travel in a shorting time period.

get_post_ifset("action, radius");

echo "<tr><td><div align=\"center\"><B>Universe Lightyear Size Editor</B>";
$title = "Expand/Contract the Universe";
echo "<BR>Expand or Contract the Universe <BR>";
if (empty($action))
{
	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "Universe Size: <INPUT TYPE=TEXT NAME=radius VALUE=\"$universe_size\">";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Universe_Lightyear_Size\">";
	echo "<INPUT TYPE=HIDDEN NAME=action VALUE=doexpand><br><br>";
	echo "<INPUT TYPE=SUBMIT VALUE=\"Change Universe Size\">";
	echo "</FORM>";
}
elseif ($action == "doexpand")
{
//	 echo "<BR><FONT SIZE='+2'>Be sure to update your config.php file with the new universe_size value</FONT><BR>";

	$radius = max( 1, abs(round($radius)) );
	$diff = $radius / $universe_size;

	$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET x=ROUND(x*$diff), y=ROUND(y*$diff), z=ROUND(z*$diff) WHERE zone_id <> 2 ");
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=$radius WHERE name='universe_size'");
	db_op_result($debug_query,__LINE__,__FILE__);

	$filename = $gameroot . "support/variables.inc";
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
	echo "Success.";

	if ($diff > 1)
	{
		echo "<BR>Universe successfully Expanded. New universe radius is $radius.";
	}
	else
	{
		echo "<BR>Universe successfully Contracted. New universe radius is $radius.";
	}
}
?>
</div></td></tr>