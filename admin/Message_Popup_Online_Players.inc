<?php
// 3: Send Popup Message to all Online Players
// This tool will allow you to send an message to all players currently online. The message will be a popup the players will have to click to remove.

get_post_ifset("content");

if (!empty($content)) 
{
	@unlink($gameroot.'support/adminpopup.inc');
	$fs = @fopen($gameroot.'support/adminpopup.inc', 'w');
	@fwrite($fs, nl2br(htmlspecialchars($content)));
	@fclose($fs);
	echo "<tr><td><br><div align=\"center\"><font color=\"lime\" size=\"4\">Messages sent</font><BR></div></td></tr>"; 
}

$selfpath = basename($_SERVER['PHP_SELF']); 
echo "<div align=\"center\"><tr><td>\n"; 
echo "<FORM ACTION=admin.php METHOD=POST>"; 
echo "<table align=\"center\">"; 
echo "  <tr>"; 
echo "	<td colspan=\"2\" align=\"center\">This will cause a popup message to appear on every page of everyone player online for 1 minute.<br><br></td>"; 
echo "  </tr>"; 
echo "  <tr>"; 
echo "	<td valign=\"top\"><font size=\"2\">MESSAGE:</font></td>"; 
echo "	<td><textarea name=\"content\" rows=\"5\" cols=\"40\">$content</textarea></td>"; 
echo "  </tr>"; 
echo "  <tr>"; 
echo "	<td colspan=\"2\" align=\"center\"><input type=\"submit\" value=\"Submit\"><input type=\"reset\" value=\"Reset\"></td>"; 
echo "  </tr>"; 
echo "</table>"; 
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=HIDDEN NAME=\"admin_password\" VALUE=\"$admin_password\">"; 
echo "<INPUT TYPE=HIDDEN NAME=\"menu\" VALUE=\"Message_Popup_Online_Players\">"; 
echo "</FORM></td></tr>";	 
echo "</div>\n"; 
?>
