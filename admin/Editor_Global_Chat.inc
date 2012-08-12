<?php
// 2: Global Chat
// This tool will allow editing all any text from the in-game Chat system.

get_post_ifset("sb_id, sb_text");

echo "<tr><td>";
if ($command=="DEL")
{
	$chat_path = $gameroot."/backends/phpfreechat/data/private/chat/".preg_replace("/[^a-z0-9]*/","",AAT_strtolower($game_name));
	$content = file($chat_path . "/messages.data");
	$count = count($content);

	$content_save = "";
	for($i = 0; $i < $count; $i++)
	{
		$shout_message = explode("\t", $content[$i]);

		if(trim($shout_message[0]) != $sb_id)
		{
			$content_save .= trim($content[$i]) . "\n";
		}
	}
    $fp = fopen($chat_path . "/messages.data","w+");
    flock ($fp, LOCK_EX); // lock
    fwrite($fp, $content_save);
    flock ($fp, LOCK_UN); // unlock
    fclose($fp);
}

if ($command=="ADD")
{
	$chat_path = $gameroot."/backends/phpfreechat/data/private/chat/".preg_replace("/[^a-z0-9]*/","",AAT_strtolower($game_name));
    $fp = fopen($chat_path . "/messages.index", "rw+");
    flock ($fp, LOCK_EX);
    $msg_id = fread($fp, filesize($chat_path . "/messages.index"));
    if (!is_numeric($msg_id)) $msg_id = 0;
    // increment message id and save it
    $msg_id++;
    ftruncate($fp, 0);
    fseek($fp, 0);
    fwrite($fp, $msg_id);
    flock ($fp, LOCK_UN);
    fclose($fp);

    $fp = fopen($chat_path . "/messages.data", "a+");
    flock ($fp, LOCK_EX); // lock

    // format message
    $line = "\n";
    $line .= $msg_id."\t";
    $line .= date("d/m/Y")."\t";
    $line .= date("H:i:s")."\t";
    $line .= "Webmaster\t";
    $line .= $sb_text;

    // write it to file
    fwrite($fp, $line);
    flock ($fp, LOCK_UN); // unlock
    fclose($fp);
}

echo "<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=3>";

echo "<FORM ACTION=admin.php METHOD=POST>";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Global_Chat\">";
echo "<TR><TD>Add Global Chat Message:</TD>";
echo "<TD><TEXTAREA NAME=sb_text ROWS=10 COLS=50></TEXTAREA></TD>";
echo "<TD ALIGN=center><INPUT TYPE=SUBMIT NAME=command VALUE=\"ADD\"></TD></TR>";
echo "</form>";

$chat_path = $gameroot."/backends/phpfreechat/data/private/chat/".preg_replace("/[^a-z0-9]*/","",AAT_strtolower($game_name));
$content = file($chat_path . "/messages.data");
$content = array_slice($content, -50);
rsort($content);
$count = count($content);

for($i = 0; $i < $count; $i++)
{
	$shout_message = explode("\t", $content[$i]);

	if(trim($shout_message[3]) != "*notice*")
	{
        $patterns = array(
   	        '`\[b\](.+?)\[/b\]`is',
       	    '`\[i\](.+?)\[/i\]`is',
           	'`\[u\](.+?)\[/u\]`is',
            '`\[s\](.+?)\[/s\]`is',
   	        '`\[color=#([a-f0-9]{6})\](.+?)\[/color\]`is',
       	    '`\[email\](.+?)\[/email\]`is',
        );

        $replaces =  array(
   	        '\\1',
       	    '\\1',
           	'\\1',
            '\\1',
   	        '\2',
       	    '\1'
        );

        $prev_string = "";
		$string = trim($shout_message[4]);
       	while ($prev_string != $string) {
           	$prev_string = $string;
            $string = preg_replace($patterns, $replaces , $string);
   	    }

		echo "<FORM ACTION=admin.php METHOD=POST>";
		echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
		echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
		echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Global_Chat\">";
		$date = explode("/", $shout_message[1]);
		$time = explode(":", $shout_message[2]);
		echo "<TR><TD width=200 align=\"center\">" .  str_replace(" - ", "<br>", date($local_date_full_format, mktime ( $time[0], $time[1], $time[2], $date[1], $date[0], $date[2] ))) . "</TD>";
		echo "<TD>". $string ."</TD>";
		echo "<TD width=150 align=\"center\"><font color=\"lime\"><b>". $shout_message[3] . "</b></font><br>";
		echo "<INPUT TYPE=HIDDEN NAME=sb_id VALUE=" . trim($shout_message[0]) . ">";
		echo "<br><INPUT TYPE=SUBMIT NAME=command VALUE=\"DEL\"></TD></TR>";
		echo "</FORM>";
		echo "<tr><td colspan=3><hr></td></tr>";
	}
}

echo "</TABLE></td></tr>";
?>