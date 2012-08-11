<?php
// Step 50 - Save top and bottom banner code and setup shoutbox.

echo "<b>Creating IP/EMail Ban List<b><br><br>";
$fs = fopen($gameroot."support/banned_ip.ini", "r");
while(!feof($fs)){
	$items = fgets($fs);
	$ipaddress = trim($items);
	if(AAT_strlen($ipaddress) > 8){
		echo "Banned IP Address: $ipaddress ";
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans VALUES('', '$ipaddress', '')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}
fclose($fs);

$fs = fopen($gameroot."support/banned_email.ini", "r");
while(!feof($fs)){
	$items = fgets($fs);
	$emailname = trim($items);
	if(AAT_strlen($emailname) > 5){
		echo "Banned Email: $emailname ";
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans VALUES('', '', '$emailname')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}
fclose($fs);

echo "<br><br>Inserting Shoutbox Welcome message from Webmaster.<br>";

$chat_path = $gameroot."/backends/phpfreechat/data/private/chat/".preg_replace("/[^a-z0-9]*/","",AAT_strtolower($game_name));
mkdir($chat_path, 0777);

$fp = fopen($chat_path . "/messages.data", "w");
flock ($fp, LOCK_EX); // lock
fwrite($fp, "1\t" . date("d/m/Y") . "\t" . date("H:i:s") . "\t*notice*\tWelcome to " . $game_name);
flock ($fp, LOCK_UN); // unlock
fclose($fp);

$fp = fopen($chat_path . "/messages.index", "w");
flock ($fp, LOCK_EX); // lock
fwrite($fp, "1");
flock ($fp, LOCK_UN); // unlock
fclose($fp);
$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES ('1','Webmaster','" . time() . "'," . $db->qstr("Welcome to $game_name") . ",'0') ");
db_op_result($res,__LINE__,__FILE__);

echo "<br><br><table align=\"center\">";

$silent = 1;
if($tournament_start_date != "0000-00-00")
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='tournament_mode'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='tournament_setup_access'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='profile_only_server'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='240' WHERE name='player_online_timelimit'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='enable_profilesupport'");
	db_op_result($debug_query,__LINE__,__FILE__);
}

exportvariables(1);

$silent = 0;

@unlink($gameroot."config/banner_top.inc");
@unlink($gameroot."config/banner_bottom.inc");

echo "<TR nowrap align=\"center\"><TD width=\"100%\"><b>Insert Top Banner Code:</b><br>This is just raw banner code.	Do not include any table, tr or td tags.<br><br><font color=#00ff00><i>Leave this blank if you do not want to place a banner at the top of the page.</i></font></TD>";
echo "<TD ><TEXTAREA NAME=top_banner ROWS=10 COLS=60></TEXTAREA></TD></tr>";
echo "<TR nowrap align=\"center\"><TD width=\"100%\"><b>Insert Bottom Banner Code:</b><br>This is just raw banner code.	Do not include any table, tr or td tags.<br><br><font color=#00ff00><i>Leave this blank if you do not want to place a banner at the bottom of the page.</i></font></TD>";
echo "<TD ><TEXTAREA NAME=bottom_banner ROWS=10 COLS=60></TEXTAREA></TD></tr>";

echo "<tr><td></td><td><input type=hidden name=step value=50></td><td></td></tr>";
echo "</table>";
echo "<input type=reset value=Reset>";

?>