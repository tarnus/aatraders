<?php
// 1: Player Planet Totals
// This will display every player in the game and how many planets they own.

echo "<tr align=\"center\"><td><h1><b>View Player Planet Totals</h1></b>\n";
echo "<br>\n";
$res = $db->Execute("SELECT count( * ) as total FROM aatrade_planets WHERE owner = 0");
echo "Never Owned: " . $res->fields['total'] . "<br>\n";

$res = $db->Execute("SELECT character_name, count( * ) as total FROM aatrade_planets, aatrade_players WHERE aatrade_planets.owner = aatrade_players.player_id GROUP BY owner ORDER BY character_name ASC");
while (!$res->EOF)
{
	$row = $res->fields;
	echo "$row[character_name]: $row[total]<br>\n";
	$res->MoveNext();
}

echo "<hr>\n";
$res = $db->Execute("SELECT count( * ) as total FROM aatrade_planets WHERE owner = 0");
echo "Never Owned: " . $res->fields['total'] . "<br>\n";

$res = $db->Execute("SELECT character_name, count( * ) as total FROM aatrade_planets, aatrade_players WHERE aatrade_planets.owner = aatrade_players.player_id GROUP BY owner ORDER BY total DESC");
while (!$res->EOF)
{
	$row = $res->fields;
	echo "$row[character_name]: $row[total]<br>\n";
	$res->MoveNext();
}
echo "</td></tr>";

?>