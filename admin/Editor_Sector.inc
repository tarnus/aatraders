<?php
// 2: Sector
// This tool will allow you to change information about any sector.

get_post_ifset("sg_sector, sector, operation, sector_name, zone_id, x, y, z, beacon, port_type");

echo "<tr><td>";
echo "<FORM ACTION=\"admin.php\" METHOD=\"POST\">";
if (empty($sector))
{
	echo "<SELECT SIZE=\"20\" NAME=\"sector\">";
	$res = $db->Execute("SELECT sector_id, sector_name FROM {$db_prefix}universe ORDER BY sector_name ASC");
	while (!$res->EOF)
	{
		$row = $res->fields;
		if ($row['sector_id'] > 2)
		{
			echo "<OPTION VALUE=\"$row[sector_id]\"> $row[sector_name] </OPTION>";
		}
		$res->MoveNext();
	}
	echo "</SELECT>";
	echo "&nbsp;<INPUT TYPE=\"SUBMIT\" VALUE=\"Edit\">";
}
else
{
	if (empty($operation))
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}universe WHERE sector_id=$sector");
		$row = $res->fields;
		echo "<TABLE BORDER=\"1\" CELLSPACING=\"2\" CELLPADDING=\"2\" width=\"100%\">";
		echo "<TR><TD align=\"center\" nowrap>Sector ID</TD><TD align=\"center\"><FONT COLOR=\"#66FF00\">$sector</FONT></TD>";
		echo "<TD ALIGN=\"center\" nowrap>Sector Name</TD><TD><INPUT TYPE=\"TEXT\" SIZE=\"30\" NAME=\"sector_name\" VALUE=\"$row[sector_name]\"></TD>";
		echo "<TD ALIGN=\"center\" nowrap>Zone ID</TD><TD>";
		echo "<SELECT SIZE=\"1\" NAME=\"zone_id\">";
		$ressubb = $db->Execute("SELECT zone_id,zone_name FROM {$db_prefix}zones ORDER BY zone_name");
		while (!$ressubb->EOF)
		{
			$rowsubb = $ressubb->fields;
			if ($rowsubb['zone_id'] == $row['zone_id'])
			{ 
				echo "<OPTION VALUE=\"$rowsubb[zone_id]\" SELECTED>$rowsubb[zone_name]</OPTION>";
			} 
			else 
			{ 
				echo "<OPTION VALUE=\"$rowsubb[zone_id]\">$rowsubb[zone_name]</OPTION>";
			}

			$ressubb->MoveNext();
		}

		echo "</SELECT></TD></TR>";
		echo "<TR><TD ALIGN=\"center\">Beacon</TD><TD COLSPAN=3><INPUT TYPE=\"TEXT\" SIZE=\"55\" NAME=\"beacon\" VALUE=\"$row[beacon]\"></TD>";
		echo "<TD ALIGN=\"center\" nowrap>SG Sector</TD><TD><INPUT TYPE=\"TEXT\" SIZE=\"10\" NAME=\"sg_sector\" VALUE=\"$row[sg_sector]\"></TD></TR>";
		echo "<TR><TD ALIGN=\"center\">X</TD><TD><INPUT TYPE=\"TEXT\" SIZE=\"9\" NAME=\"x\" VALUE=\"$row[x]\"></TD>";
		echo "<TD ALIGN=\"center\">Y</TD><TD><INPUT TYPE=\"TEXT\" SIZE=\"9\" NAME=\"y\" VALUE=\"$row[y]\"></TD>";
		echo "<TD ALIGN=\"center\">Z</TD><TD><INPUT TYPE=\"TEXT\" SIZE=\"9\" NAME=\"z\" VALUE=\"$row[z]\"></TD></TR>";
		echo "</TABLE>";

		echo "<TABLE BORDER=\"1\" CELLSPACING=\"2\" CELLPADDING=\"2\" width=\"100%\">";
		echo "<TR><TD ALIGN=\"center\" nowrap>Port Type</TD><TD>";
		echo "<SELECT SIZE=\"1\" NAME=\"port_type\">";
		$oportnon = $oportcolonist = $oportorg = $oportore = $oportgoo = $oportene = $oportcasino = $oportdevices = $oportupgrades = $oportspacedock = ""; 

		if ($row['port_type'] == "none") $oportnon = "SELECTED";
		if ($row['port_type'] == "organics") $oportorg = "SELECTED";
		if ($row['port_type'] == "ore") $oportore = "SELECTED";
		if ($row['port_type'] == "goods") $oportgoo = "SELECTED";
		if ($row['port_type'] == "energy") $oportene = "SELECTED";
		if ($row['port_type'] == "upgrades") $oportupgrades = "SELECTED";
		if ($row['port_type'] == "devices") $oportdevices = "SELECTED";
		if ($row['port_type'] == "spacedock") $oportspacedock = "SELECTED";
		if ($row['port_type'] == "casino") $oportcasino = "SELECTED";
		if ($row['port_type'] == "colonist") $oportcolonist = "SELECTED";

		echo "<OPTION value=\"none\" $oportnon>none</OPTION>";
		echo "<OPTION value=\"organics\" $oportorg>organics</OPTION>";
		echo "<OPTION value=\"ore\" $oportore>ore</OPTION>";
		echo "<OPTION value=\"goods\" $oportgoo>goods</OPTION>";
		echo "<OPTION value=\"energy\" $oportene>energy</OPTION>";
		echo "<OPTION value=\"upgrades\" $oportupgrades>upgrades</OPTION>";
		echo "<OPTION value=\"devices\" $oportdevices>devices</OPTION>";
		echo "<OPTION value=\"spacedock\" $oportspacedock>spacedock</OPTION>";
		echo "<OPTION value=\"casino\" $oportcasino>casino</OPTION>";
		echo "<OPTION value=\"colonist\" $oportcolonist>colonist</OPTION>";
		echo "</SELECT></TD>";
		echo "</TABLE>";
		echo "<BR>";
		echo "<INPUT TYPE=\"HIDDEN\" NAME=\"sector\" VALUE=\"$sector\">";
		echo "<INPUT TYPE=\"HIDDEN\" NAME=\"operation\" VALUE=\"save\">";
		echo "<INPUT TYPE=\"SUBMIT\" SIZE=\"1\" VALUE=\"Save\">";
	}
	elseif ($operation == "save")
	{
		// update database
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET sector_name=" . $db->qstr($sector_name) . ",zone_id='$zone_id',beacon='$beacon',port_type='$port_type',z='$z',x='$x',y='$y', sg_sector='$sg_sector' WHERE sector_id=$sector");
		db_op_result($debug_query,__LINE__,__FILE__);
		echo "<INPUT TYPE=\"SUBMIT\" VALUE=\"Return to Sector editor\">";
		$button_main = false;
	}
	else
	{
		echo "Invalid operation";
	}
}
echo "<INPUT TYPE=\"HIDDEN\" NAME=\"menu\" VALUE=\"Editor_Sector\">";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=\"HIDDEN\" NAME=\"admin_password\" VALUE=\"$admin_password\">";
echo "</FORM></td></tr>";
?>
