<?php
// 1: Player Team History
// This will allow you to view how many times a player has changed teams, when they changes and what teams they have joined and left.

get_post_ifset("user");

$option_echo = '';
echo "<tr align=\"center\"><td><h1><b>View Player Team History</h1></b>\n";
echo "<br>\n";
echo "<form action=\"admin.php\" method=\"post\">\n";
if (empty($user))
{
	$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players ORDER BY character_name");
	while (!$res->EOF)
	{
		$row = $res->fields;
		$option_echo .= "	<option value=\"$row[player_id]\">$row[character_name]</option>\n";
		$res->MoveNext();
		$fun_temp++;
	}

	if ($fun_temp > 20)
	{
		$fun_temp = 20;
	}

	echo "  <select size=\"$fun_temp\" name=\"user\">\n";
	echo $option_echo;
	echo "  </select>\n";
	echo "  &nbsp;\n  <input type=\"submit\" value=\"View\">\n";
}
else
{
	$res = $db->Execute("SELECT {$db_prefix}player_team_history.*, {$db_prefix}players.character_name from {$db_prefix}players, {$db_prefix}player_team_history " .
						"WHERE {$db_prefix}players.player_id=$user and {$db_prefix}player_team_history.player_id=$user order by {$db_prefix}player_team_history.left_team ASC");
	if (!$res->EOF){
		$row = $res->fields;
		echo "<table border=\"1\" cellspacing=\"1\" cellpadding=\"4\" width=\"600\"><tr><td colspan=4 align=\"center\"><font color=#00ff00 size=3><b>$row[character_name]</b></font></td></tr>";
		echo "<tr><td align=\"center\"><font color=cyan><b>Team ID</b></font></td><td align=\"center\"><b><font color=cyan>Team Name</b></font></td><td align=\"center\"><b><font color=cyan>Info</b></font></td><td align=\"center\"><b><font color=cyan>Date</b></font></td></tr>\n";
		while (!$res->EOF)
		{
			$row = $res->fields;
			echo "<tr><td>$row[history_team_id]</td><td>$row[history_team_name]</td><td>$row[info]</td><td>" . date($local_date_full_format, strtotime($row['left_team'])) . "</td></tr>\n";
			$res->MoveNext();
		}
	}
	else
	{
		echo "<table border=\"1\" cellspacing=\"1\" cellpadding=\"4\"><tr><td colspan=4><font color=#00ff00 size=3>Player hasn't joined/created any teams.</font></td></tr>";
	}
	echo "</table>";
	echo "<input type=\"submit\" value=\"Return to History List\">\n";
}
echo "  <input type=\"hidden\" name=\"menu\" value=\"View_Player_Team_History\">\n";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "  <input type=\"hidden\" name=\"admin_password\" value=\"$admin_password\">\n";
echo "</form>\n</td></tr>";
?>