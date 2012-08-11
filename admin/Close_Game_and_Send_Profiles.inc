<?php
// 7: Close Game and Send Profiles
// WARNING!!!!<br><br>This tool will close out the game and send all player profiles to the Master Profile Server.  Do not execute this unless you are going to reset the game.

include ("globals/end_of_game.inc");

get_post_ifset("action");

echo "<B>Close Game and Send Profiles</B>";
echo "<BR>Expand or Contract the Universe <BR>";
if (empty($action))
{
	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "Are you sure you want to close the game and send final player profiles to the Profile Server?<br><br>
	If you click on <b>Close Game</b> the server will be closed and player profiles<br>
	of all registered players will be compiled and sent to the Profile Server.  The<br>
	Profile Server will only accept closed game updates <b>ONCE EVERY TWO WEEKS<b> from<br>
	a server.  Any futher game closings or game resets will be ignored.<br><br>";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Close_Game_and_Send_Profiles\">";
	echo "<INPUT TYPE=HIDDEN NAME=action VALUE=\"closegame\"> ";
	echo "<INPUT TYPE=SUBMIT VALUE=\"Close Game\">";
	echo "</FORM>";
}
elseif ($action == "closegame")
{
	echo "<br><B>Your game has been closed and player profiles have been sent to the Profile Server.</B><br>";
	flush();

	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=0 WHERE name='enable_scheduler'");
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=1 WHERE name='server_closed'");
	db_op_result($debug_query,__LINE__,__FILE__);

	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value=1 WHERE name='account_creation_closed'");
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

	end_of_game();
}
?>
