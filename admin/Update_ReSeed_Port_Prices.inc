<?php
// 8: Re-Seed Port Prices
// This tool will Re-Seed all port prices as if the universe was newly created.  no new ports will be added.  Use the Age Port Prices menu item if you wish port prices to reflect game time.

get_post_ifset("command");
?>

<form action=admin.php method=post>
<tr>
<td>Would you like to reseed all port prices without updating?
</td>
</tr>
<?php
echo "<tr><td colspan=\"2\" align=\"center\"><INPUT TYPE=HIDDEN NAME=menu VALUE=\"Update_ReSeed_Port_Prices\">";
echo "<INPUT TYPE=HIDDEN NAME=\"admin_password\" VALUE=\"$admin_password\">";
echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=SUBMIT NAME=command VALUE=\"ReSeed No Update\"></td></tr>"
?>
</form>

<?php
if($command == "ReSeed" || $command == "ReSeed No Update")
{
	echo "<tr>
<td>Reseeding Started:<br><br>";
	$stamp = date("Y-m-d H:i:s");

// cargo port placement
$cargototal = 0;
$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where cargoport=1 order by defaultcargoplanet DESC");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargo_info = $cargo_query->fields;
	$index = str_replace(" ", "_", $cargo_info['classname']);
	$cargoindex[$index] = $cargototal;
	$newcargotype[$cargototal] = AAT_strtolower($cargo_info['classname']);
	$newcargoclass[$cargototal] = AAT_strtolower($cargo_info['class']);
	$limit[$cargototal] = $cargo_info['itemlimit'];
	$initialamount[$cargototal] = $cargo_info['itemlimit'];
	$fixed_start_price[$cargototal] = $cargo_info['fixed_start_price'];
	$increaserate[$cargototal] = $cargo_info['increaserate'];
	$goodevil[$cargototal] = $cargo_info['goodevil'];
	$cargosellbuy[$cargototal] = $cargo_info['cargosellbuy'];
	$hold_space[$cargototal] = $cargo_info['hold_space'];
	$cargototal++;
	$cargo_query->Movenext();
}
$cargo_query->close();

$earth_sector = $db->SelectLimit("SELECT x, y, z ".
							 "FROM {$db_prefix}universe ".
							 "WHERE ".
							 "sector_id='1'", 1);
db_op_result($earth_sector,__LINE__,__FILE__);

$Xdistance = floor($earth_sector->fields['x']);
$Ydistance = floor($earth_sector->fields['y']);
$Zdistance = floor($earth_sector->fields['z']);

if($enable_spiral_galaxy != 1)
{
	$query2 = "SELECT SQRT((($Xdistance-x) * ($Xdistance-x))+(($Ydistance-y) * ($Ydistance-y))+(($Zdistance-z) * ($Zdistance-z))) as distance FROM {$db_prefix}universe where sector_id!=1 and sg_sector = 0  ORDER BY distance DESC";
}
else
{
	$query2 = "SELECT SQRT(POW(($Xdistance-x),2)+POW(($Ydistance-y),2)+POW(($Zdistance-z),2)) as distance FROM {$db_prefix}universe where sector_id!=1 and sg_sector = 0  ORDER BY distance DESC";
}

$results = $db->SelectLimit($query2, 1);

$max_distance = floor($results->fields['distance']);

if($enable_spiral_galaxy != 1)
{
	$query2 = "SELECT *, SQRT((($Xdistance-x) * ($Xdistance-x))+(($Ydistance-y) * ($Ydistance-y))+(($Zdistance-z) * ($Zdistance-z))) as distance FROM {$db_prefix}universe where sector_id!=1 and port_type != 'casino' and port_type != 'none' and port_type != 'upgrades' and port_type != 'devices' and port_type != 'spacedock' ORDER BY distance DESC";
}
else
{
	$query2 = "SELECT *, SQRT(POW(($Xdistance-x),2)+POW(($Ydistance-y),2)+POW(($Zdistance-z),2)) as distance FROM {$db_prefix}universe where sector_id!=1 and port_type != 'casino' and port_type != 'none' and port_type != 'upgrades' and port_type != 'devices' and port_type != 'spacedock' ORDER BY distance DESC";
}

$port_sector = $db->Execute($query2);

while(!$port_sector->EOF)
{
	$ratio = $port_sector->fields['distance'] / $max_distance;
	$randomsector = $port_sector->fields['sector_id'];
	$commodity_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=" . $randomsector . " order by data_id ASC");
	db_op_result($commodity_query,__LINE__,__FILE__);
	$first = 0;
	echo "Updating Sector: " . $port_sector->fields['sector_name'] . " - Ratio: " . $ratio . "<br><br>";
	while(!$commodity_query->EOF)
	{
		$commodity_data = $commodity_query->fields;
		$index = str_replace(" ", "_", $commodity_data['commodity_type']);
		$i = $cargoindex[$index];
		echo $commodity_data['commodity_type'] . " Cost Per Hold: " . ($commodity_data['commodity_price']/$hold_space[$i]) . "<br>Old Prices: " . $commodity_data['commodity_price'] . " / " . $commodity_data['fixed_commodity_price'] . " - ";

		$randompoint = mt_rand(500000, 1000000) / 1000000;
		$prices = floor($fixed_start_price[$i] * $randompoint);

		if($increaserate[$i] == 0)
		{
			$prices = $fixed_start_price[$i];
		}
		if($first == 1)
		{
			$randompoint = mt_rand(500000, 1000000) / 1000000;
			$startprices = floor($fixed_start_price[$i] * $randompoint) * 3;
			$startprices += $fixed_start_price[$i] * $ratio;
			if($increaserate[$i] == 0)
			{
				$startprices = $prices / 2;
			}
			echo " New Prices: " . $startprices . " / 0<br>";
			if($command == "ReSeed")
			{
				$update_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET trade_date='$stamp', 
											commodity_price=$startprices 
											WHERE data_id = $commodity_data[data_id]");
				db_op_result($update_query,__LINE__,__FILE__);
				$update_query->close();
			}
		}

		if($first == 0)
		{
			echo "New Prices: " . $prices . "<br>";
			if($command == "ReSeed")
			{
				$update_query = $db->Execute("UPDATE {$db_prefix}universe_ports SET trade_date='$stamp', 
											commodity_price=$prices 
											WHERE data_id = $commodity_data[data_id]");
				db_op_result($update_query,__LINE__,__FILE__);
				$update_query->close();
			}
			$first = 1;
		}
		echo"<br>";
		$commodity_query->Movenext();
	}
	if($first == 0)
	{
		echo "<font color=\"lime\">universeports empty<br><br></font>";
	}
	echo "<hr>";
	$port_sector->Movenext();
}
$port_sector->close();
	echo"</td>
</tr>";
}

?>
<form action=admin.php method=post>
<tr>
<td>Would you like to reseed all port prices?
</td>
</tr>
<?php
echo "<tr><td colspan=\"2\" align=\"center\"><INPUT TYPE=HIDDEN NAME=menu VALUE=\"Update_ReSeed_Port_Prices\">";
echo "<INPUT TYPE=HIDDEN NAME=\"admin_password\" VALUE=\"$admin_password\">";
echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=SUBMIT NAME=command VALUE=\"ReSeed\"></td></tr>"
?>
</form>

