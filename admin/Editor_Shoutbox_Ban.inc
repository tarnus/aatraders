<?php
// 2: Shoutbox Ban
// This tool will allow you to ban any player from posting to the shoutbox.

get_post_ifset("player, unban");

if (!empty($player))
{
	$res = $db->execute("UPDATE {$db_prefix}players SET shoutbox_ban = 1 WHERE player_id = $player");
	db_op_result($res,__LINE__,__FILE__);					
}

if (!empty($unban))
{
	$res = $db->execute("UPDATE {$db_prefix}players SET shoutbox_ban = 0 WHERE player_id = $unban");
	db_op_result($res,__LINE__,__FILE__);					
}

echo "<tr><td><div align=\"center\">";

$res = $db->execute("SELECT player_id, character_name FROM {$db_prefix}players WHERE shoutbox_ban = 1 ORDER BY character_name ASC");
db_op_result($res,__LINE__,__FILE__);					
while (!$res->EOF)
{
	echo "<form action=\"admin.php\" method=\"POST\">" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE='Editor_Shoutbox_Ban'>" .
		 "<INPUT TYPE=HIDDEN NAME=unban VALUE='" . $res->fields['player_id'] . "'>" .
		 "<INPUT TYPE=HIDDEN NAME=md5admin_password VALUE=".md5($admin_password).">";
	echo $res->fields['character_name'];
	echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n".
		 "<INPUT TYPE=SUBMIT VALUE=\"UnBan\">" .
		 "</form>";
	$res->MoveNext();
}

echo "</div></td></tr>";

echo "<tr><td><br><div align=\"center\"><form action=\"admin.php\" method=\"POST\">" .
	 "<INPUT TYPE=HIDDEN NAME=menu VALUE='Editor_Shoutbox_Ban'>" .
	 "<INPUT TYPE=HIDDEN NAME=md5admin_password VALUE=".md5($admin_password).">" .
	 "<SELECT size=\"20\" name=\"player\">";

$res = $db->execute("SELECT player_id, character_name FROM {$db_prefix}players WHERE shoutbox_ban = 0 ORDER BY character_name ASC");
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

echo "</SELECT>&nbsp;&nbsp;" .
	"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n".
	 "<INPUT TYPE=SUBMIT VALUE=\"Ban Selected player\">" .
	 "</form><HR size=1 width=80%></div></td></tr>";
?>
