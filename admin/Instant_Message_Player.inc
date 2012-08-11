<?php
// 3: Send Instant Message Message
// This tool will allow you to send an Instant Message to All Players or a Single Player.

include ("globals/send_system_im.inc");

get_post_ifset("player_id, content");

$selfpath = basename($_SERVER['PHP_SELF']); 
echo "<tr><td><div align=\"center\">\n"; 
echo "<FORM ACTION=admin.php METHOD=POST>"; 
echo "<table align=\"center\">"; 
echo "  <tr>"; 
echo "	<td><font size=\"2\">TO:</font></td>"; 
echo "	<td><SELECT name=player_id>"; 
echo "<OPTION value=0>All Players</OPTION>";
$res = $db->execute("SELECT player_id, character_name FROM {$db_prefix}players ORDER BY character_name ASC");
db_op_result($res,__LINE__,__FILE__);					
while (!$res->EOF)
{
	$players[] = $res->fields;
	$res->MoveNext();
}

foreach ($players as $player)
{
	echo "<OPTION value=$player[player_id]>$player[character_name]</OPTION>";
}
echo "  </SELECT>&nbsp;&nbsp;</td></tr>"; 
echo "  <tr>"; 
echo "	<td valign=\"top\"><font size=\"2\">MESSAGE:</font></td>"; 
echo "	<td><textarea name=\"content\" rows=\"5\" cols=\"40\"></textarea></td>"; 
echo "  </tr>"; 
echo "  <tr>"; 
echo "	<td colspan=\"2\" align=\"center\"><input type=\"submit\" value=\"Submit\"><input type=\"reset\" value=\"Reset\"></td>"; 
echo "  </tr>"; 
echo "</table>"; 
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=HIDDEN NAME=\"admin_password\" VALUE=\"$admin_password\">"; 
echo "<INPUT TYPE=HIDDEN NAME=\"menu\" VALUE=\"Instant_Message_Player\">"; 
echo "</FORM></td></tr>";	 
echo "</div>\n"; 

if (!empty($content)) 
{ 
	echo "<tr><td><div align=\"center\">\n"; 
	if($player_id == 0)
	{
		$res = $db->Execute("select last_login, player_id, character_name from {$db_prefix}players WHERE email != '$admin_mail' AND email NOT LIKE '%@npc' ORDER BY character_name ASC"); 
		db_op_result($res,__LINE__,__FILE__);
	}
	else
	{
		$res = $db->Execute("select last_login, player_id, character_name from {$db_prefix}players WHERE player_id = '$player_id'"); 
		db_op_result($res,__LINE__,__FILE__);
	}
	// New lines to prevent SQL injection. Bad stuff.
	$content = htmlspecialchars($content);

	while (!$res->EOF) 
	{
		$temp = $silent;
		$silent = 0;
		echo "Sending Instant Message to <B>". $res->fields["character_name"] . "</B> ";
		flush();
		send_system_im($res->fields["player_id"], "Message from the Admin", $content, $res->fields['last_login'], 1);
		$silent = $temp;
		$res->MoveNext(); 
	} 
	echo "</td></tr>";	 
	echo "</div>\n"; 
} 
?>

