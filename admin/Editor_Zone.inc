<?php
// 2: Zone
// This will allow editing of all Zone properties for any Zone in the game.

get_post_ifset("zone, operation, zone_name, zone_attack, zone_warpedit, zone_planet, zone_hull");

echo "<tr><td><div align=\"center\">";
echo "<FORM ACTION=admin.php METHOD=POST>";
if (empty($zone))
{
	echo "<SELECT SIZE=20 NAME=zone>";
	$res = $db->Execute("SELECT zone_id,zone_name FROM {$db_prefix}zones ORDER BY zone_name");
	while (!$res->EOF)
	{
		$row = $res->fields;
		echo "<OPTION VALUE=$row[zone_id]>$row[zone_name]</OPTION>";
		$res->MoveNext();
	}
	$res->close();

	echo "</SELECT>";
	echo "<INPUT TYPE=HIDDEN NAME=operation VALUE=editzone>";
	echo "&nbsp;<INPUT TYPE=SUBMIT VALUE=Edit>";
}
else
{
	if ($operation == "editzone")
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}zones WHERE zone_id=$zone");
		$row = $res->fields;
		$res->close();
		echo "<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=5 align=center>";
		echo "<TR><TD>Zone ID</TD><TD>$row[zone_id]</TD></TR>";
		echo "<TR><TD>Zone Name</TD><TD><INPUT TYPE=TEXT NAME=zone_name VALUE=\"$row[zone_name]\"></TD></TR>";
		echo "<TR><TD>Allow Attack</TD><TD><INPUT TYPE=CHECKBOX NAME=zone_attack VALUE=ON " . CHECKED($row['allow_attack']) . "></TD></TR>";
		echo "<TR><TD>Allow WarpEdit</TD><TD><INPUT TYPE=CHECKBOX NAME=zone_warpedit VALUE=ON " . CHECKED($row['allow_warpedit']) . "></TD></TR>";
		echo "<TR><TD>Allow Planet</TD><TD><INPUT TYPE=CHECKBOX NAME=zone_planet VALUE=ON " . CHECKED($row['allow_planet']) . "></TD></TR>";
		echo "<TR><TD>Max Hull</TD><TD><INPUT TYPE=TEXT NAME=zone_hull VALUE=\"$row[max_hull]\"></TD></TR>";
		echo "<TR><TD align=center colspan=2><BR>";
		echo "<INPUT TYPE=HIDDEN NAME=zone VALUE=$zone>";
		echo "<INPUT TYPE=HIDDEN NAME=operation VALUE=savezone>";
		echo "<INPUT TYPE=SUBMIT VALUE=Save>";
		echo "</TD></TR></TABLE>";
	}
	elseif ($operation == "savezone")
	{
		// update database
		$_zone_attack = empty($zone_attack) ? "N" : "Y";
		$_zone_warpedit = empty($zone_warpedit) ? "N" : "Y";
		$_zone_planet = empty($zone_planet) ? "N" : "Y";
		$debug_query = $db->Execute("UPDATE {$db_prefix}zones SET zone_name='$zone_name',allow_attack='$_zone_attack' ,allow_warpedit='$_zone_warpedit' ,allow_planet='$_zone_planet', max_hull='$zone_hull' WHERE zone_id=$zone");
		db_op_result($debug_query,__LINE__,__FILE__);
		echo "<INPUT TYPE=SUBMIT VALUE=\"Return to Zone Editor \">";
		$button_main = false;
	}
	else
	{
		echo "Invalid operation";
	}
}
echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Zone\">";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "</FORM></div></td></tr>";
?>
