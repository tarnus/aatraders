<?php
// 3: Popup Message for New Players
// This tool will allow you to send a popup message to all new players as soon as they join the game on the Options Screen.

get_post_ifset("content, command");

if($command == "Submit")
{
	@unlink($gameroot.'support/newuserpopup.inc');
	$fs = @fopen($gameroot.'support/newuserpopup.inc', 'w');
	@fwrite($fs, nl2br(htmlspecialchars($content)));
	@fclose($fs);
	echo "<tr><td><br><div align=\"center\"><font color=\"lime\" size=\"4\">New User Popup Saved</font><BR></div></td></tr>"; 
}

$content = "";
$lines = @file ("support/newuserpopup.inc");
for($i=0; $i<count($lines); $i++){
	$content .= $lines[$i];
}
$selfpath = basename($_SERVER['PHP_SELF']); 
echo "<div align=\"center\"><tr><td>\n"; 
echo "<FORM ACTION=admin.php METHOD=POST>"; 
echo "<table align=\"center\">"; 
echo "  <tr>"; 
echo "	<td colspan=\"2\" align=\"center\">This will cause a popup message to appear on the Options Page when a new user logs in for the first time.<br><br></td>"; 
echo "  </tr>"; 
echo "  <tr>"; 
echo "	<td valign=\"top\"><font size=\"2\">MESSAGE:</font></td>"; 
echo "	<td><textarea name=\"content\" rows=\"5\" cols=\"40\">$content</textarea></td>"; 
echo "  </tr>"; 
echo "  <tr>"; 
echo "	<td colspan=\"2\" align=\"center\"><input type=\"submit\" name=\"command\" value=\"Submit\"><input type=\"reset\" value=\"Reset\"></td>"; 
echo "  </tr>"; 
echo "</table>"; 
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=HIDDEN NAME=\"admin_password\" VALUE=\"$admin_password\">"; 
echo "<INPUT TYPE=HIDDEN NAME=\"menu\" VALUE=\"Message_New_Player_Popup\">"; 
echo "</FORM></td></tr>";	 
echo "</div>\n"; 
?>
