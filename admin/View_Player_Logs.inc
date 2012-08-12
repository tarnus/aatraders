<?php
// 1: Player Logs
// This tool will allow you to view the Combined Log for any player in the game.

echo "<tr><td><br><div align=\"center\"><form action=log.php method=POST>" .
	 "<INPUT TYPE=HIDDEN NAME=menu VALUE='View_Player_logs'>" .
	 "<INPUT TYPE=HIDDEN NAME=md5admin_password VALUE=".md5($admin_password).">" .
	 "<SELECT size=\"20\" name=player>";

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

echo "</SELECT>&nbsp;&nbsp;" .
	"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n".
	 "<INPUT TYPE=SUBMIT VALUE=\"View player log\">" .
	 "</form><HR size=1 width=80%></div></td></tr>";
?>
