<?php
// 3: Send Global Email or Message to All Players or a Single Player
// This tool will allow you to send and In-Game message or an E-Mail to every player in the game or any single player.

include ("globals/AddELog.inc");

get_post_ifset("player_id, content, messagetype, subject");

$selfpath = basename($_SERVER['PHP_SELF']); 
echo "<tr><td><div align=\"center\">\n"; 
echo "<FORM ACTION=admin.php METHOD=POST>"; 
echo "<input type=\"radio\" name=\"messagetype\" value=\"email\" checked>Email &nbsp;&nbsp;&nbsp;<input type=\"radio\" name=\"messagetype\" value=\"message\">Internal Message<BR><BR>"; 
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
echo "	<td><font size=\"2\">FROM:</font></td>"; 
echo "	<td><input disabled maxLength=\"40\" size=\"40\" value=\"GameAdmin\" name=\"dummy\"></td>"; 
echo "  </tr>"; 
echo "  <tr>"; 
echo "	<td><font size=\"2\">SUBJECT:</font></td>"; 
echo "	<td><input maxLength=\"40\" size=\"40\" name=\"subject\"></td>"; 
echo "  </tr>"; 
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
echo "<INPUT TYPE=HIDDEN NAME=\"menu\" VALUE=\"Send_Global_Email_or_Message\">"; 
echo "</FORM></td></tr>";	 
echo "</div>\n"; 

if (!empty($content)) 
{ 
	echo "<tr><td><div align=\"center\">\n"; 
	if($player_id == 0)
	{
		$res = $db->Execute("select * from {$db_prefix}players WHERE email != '$admin_mail' AND email NOT LIKE '%@npc' ORDER BY character_name ASC"); 
		db_op_result($res,__LINE__,__FILE__);
	}
	else
	{
		$res = $db->Execute("select * from {$db_prefix}players WHERE player_id = '$player_id'"); 
		db_op_result($res,__LINE__,__FILE__);
	}

	$row = $res->fields; 

	if ($messagetype=='email')
	{
		$headers = "From: GameAdmin <$admin_mail>\r\n"; 
		$content .= "\r\n\r\nhttp://$SERVER_NAME$gamepath\r\n"; 
		$content = AAT_ereg_replace("\r\n.\r\n","\r\n. \r\n",$content);
	}
	elseif ($messagetype=='message')
	{
		$timestamp = date("Y-m-d H:i:s");
		$r2 = $db->Execute("SELECT player_id FROM {$db_prefix}players  WHERE email = '$admin_mail'");
		$admin_id = $r2->fields["player_id"];
	}

	// New lines to prevent SQL injection. Bad stuff.
	$content = htmlspecialchars($content);
	$subject = htmlspecialchars($subject);

	while (!$res->EOF) 
	{
		if ($messagetype=='email')
		{
			if($SMTP_Enabled == 0)
			{
				$e_response = mail($res->fields["email"],$subject,$content,$headers); 
			}
			else
			{
				require_once "backends/SwiftMailer/lib/Swift.php";
				require_once "backends/SwiftMailer/lib/Swift/Connection/SMTP.php";

				@set_time_limit(60);

				$smtp =& new Swift_Connection_SMTP($SMTP_Server_Address, $SMPT_Server_Port);
				$smtp->setUsername($SMTP_User_Name);
				$smtp->setPassword($SMTP_User_Password);

				$swift =& new Swift($smtp);

				//Create the message
				$message =& new Swift_Message($subject, $content);
				$e_response = $swift->send($message, $res->fields["email"], $SMTP_Email_Address);
			}
			if ($e_response > 0) 
			{ 
				echo "<font color=\"lime\">Global Message sent to ".$res->fields["email"]."</font><br>\n";
				flush();
				AddELog($res->fields["email"],5,'Y',$subject,$e_response); 
			} 
			else 
			{ 
				echo "<font color=\"Red\">Message failed to send to ".$res->fields["email"]."</font><br>\n";
				flush();
				AddELog($res->fields["email"],5,'N',$subject,$e_response); 
			} 
		}
		elseif ($messagetype=='message')
		{
			$temp = $silent;
			$silent = 0;
			echo "Sending Global Message to <B>". $res->fields["character_name"] . "</B> ";
			flush();
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}messages (sender_id, recp_id, subject, sent, message) VALUES ('$admin_id', '" . $res->fields["player_id"] . "', " . $db->qstr($subject) . ", '$timestamp', " . $db->qstr($content) . ")");
			db_op_result($debug_query,__LINE__,__FILE__);
			$silent = $temp;
		}
		$res->MoveNext(); 
	} 
	echo "</td></tr>";	 
	echo "</div>\n"; 
} 
?>
