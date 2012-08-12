<?php
// 8: Add Commodity
// This tool will add a new Commodity to an already running game..

get_post_ifset("command, cargoname");
 
if($command == "add" && !empty($cargoname))
{
	if(!class_exists($cargoname)){
		include ("class/commodities/" . $cargoname . ".inc");
	}

	$cargoobject = new $cargoname();
	$classname = $cargoobject->classname;
	$cargoclass = $cargoobject->cargoclass;
	$upgradeport = $cargoobject->upgradeport;
	$deviceport = $cargoobject->deviceport;
	$cargoport = $cargoobject->cargoport;
	$cargosellbuy = $cargoobject->cargosellbuy;
	$cargoplanet = $cargoobject->cargoplanet;
	$defaultcargoplanet = $cargoobject->defaultcargoplanet;
	$defaultcargoship = $cargoobject->defaultcargoship;
	$shipdevice = $cargoobject->shipdevice;
	$planetdevice = $cargoobject->planetdevice;
	$shipdevicemax = $cargoobject->shipdevicemax;
	$planetdevicemax = $cargoobject->planetdevicemax;
	$researchonly = $cargoobject->researchonly;
	$goodevil = $cargoobject->goodevil;
	$price = $cargoobject->price;
	$delta = $cargoobject->delta;
	$rate = $cargoobject->rate;
	$reducerate = $cargoobject->reducerate;
	$increaserate = $cargoobject->increaserate;
	$itemlimit = $cargoobject->limit;
	$prate = $cargoobject->prate;
	$default_prod = $cargoobject->default_prod;
	$default_indy_prod = $cargoobject->default_indy_prod;
	$fixed_start_price = $cargoobject->fixed_start_price;
	$damage_shields = $cargoobject->damage_shields;
	$damage_all = $cargoobject->damage_all;
	$deflector_damage = $cargoobject->deflector_damage;
	$hit_pts = $cargoobject->hit_pts;
	$price_modifier = $cargoobject->price_modifier;
	$energy_usage = $cargoobject->energy_usage;
	$default_create_percent = $cargoobject->default_create_percent;
	$researchcredits = $cargoobject->researchcredits;
	$researchore = $cargoobject->researchore;
	$researchorganics = $cargoobject->researchorganics;
	$researchgoods = $cargoobject->researchgoods;
	$researchenergy = $cargoobject->researchenergy;
	$researchticks = $cargoobject->researchticks;
	$buildcredits = $cargoobject->buildcredits;
	$buildore = $cargoobject->buildore;
	$buildorganics = $cargoobject->buildorganics;
	$buildgoods = $cargoobject->buildgoods;
	$buildenergy = $cargoobject->buildenergy;
	$buildticks = $cargoobject->buildticks;
	$program = $cargoobject->program;
	$hold_space = $cargoobject->hold_space;
	$image_location = $cargoobject->image_location;
	$enable = $debrisobject->enable;
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}class_modules_commodities (program, class, classname, cargoclass, upgradeport,
			deviceport, cargoport, cargosellbuy, cargoplanet, defaultcargoplanet, defaultcargoship, 
			shipdevice, planetdevice, shipdevicemax, planetdevicemax, researchonly, 
			goodevil, price, delta, rate,
			reducerate, increaserate, itemlimit, prate, default_prod, default_indy_prod, fixed_start_price,
			damage_shields, damage_all, deflector_damage, hit_pts, price_modifier, energy_usage, researchcredits,
			researchore, researchorganics, researchgoods, researchenergy, researchticks, 
			buildcredits, buildore, buildorganics, buildgoods, buildenergy, buildticks, hold_space, 
			default_create_percent, image_location, enable) 
			VALUES 
			('$program', '$cargoname','$classname', '$cargoclass', '$upgradeport', 
			'$deviceport', '$cargoport', '$cargosellbuy', '$cargoplanet', '$defaultcargoplanet', '$defaultcargoship', 
			'$shipdevice', '$planetdevice', '$shipdevicemax', '$planetdevicemax', '$researchonly', 
			'$goodevil', '$price', '$delta', '$rate',
			'$reducerate', '$increaserate', '$itemlimit', '$prate', '$default_prod', '$default_indy_prod', '$fixed_start_price',
			'$damage_shields', '$damage_all', '$deflector_damage', '$hit_pts', '$price_modifier', '$energy_usage', '$researchcredits',
			'$researchore', '$researchorganics', '$researchgoods', '$researchenergy', '$researchticks',
			'$buildcredits', '$buildore', '$buildorganics', '$buildgoods', '$buildenergy', '$buildticks', '$hold_space',
			'$default_create_percent', '$image_location', '$enable')");
	db_op_result($debug_query,__LINE__,__FILE__);

	$result2 = $db->Execute("SELECT ship_id FROM {$db_prefix}ships");
	db_op_result($result2,__LINE__,__FILE__);
	while (!$result2->EOF) 
	{
		$ship_id = $result2->fields['ship_id'];
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ship_holds (".
									"ship_id, class, cargo_name, cargo_class, hold_space,".
									"amount) VALUES(" .
									"'$ship_id'," .
									"'$cargoname'," .
									"'$classname'," .
									"'$cargoclass'," .
									"'$hold_space'," .
									"'0'" .
									")"); 
		db_op_result($debug_query,__LINE__,__FILE__);
		$result2->Movenext();
	}
	$result2->close();

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

	if($cargosellbuy != 1)
	{
		$cargo_query = $db->Execute("SELECT default_create_percent from {$db_prefix}class_modules_commodities where cargoport=1 order by defaultcargoplanet DESC");
		db_op_result($cargo_query,__LINE__,__FILE__);
		$default_create_ratio = 5 / $cargo_query->RecordCount();
		$default_create_percent = $default_create_percent * $default_create_ratio;
		$cargo_query->close();

		$result2 = $db->SelectLimit("SELECT count(sector_id) as sektors FROM {$db_prefix}universe WHERE zone_id != 2 and sg_sector = 0", 1);
		db_op_result($result2,__LINE__,__FILE__);
		$sector_avail = $result2->fields['sektors'];
		$result2->close();
		$portcount = round($sector_avail * $default_create_percent/100);

		$result2 = $db->SelectLimit("SELECT count(sector_id) as maxsector FROM {$db_prefix}universe", 1);
		db_op_result($result2,__LINE__,__FILE__);
		$maxsector = $result2->fields['maxsector'];
		$result2->close();

		echo "<tr><td align=\"center\"><br><br><b>Creating " . $portcount . " new " . ucwords($classname) . " ports.</b><br><br></td></tr>";

		// cargo port placement
		$cargototal = 0;
		$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where cargoport=1 order by defaultcargoplanet DESC");
		db_op_result($cargo_query,__LINE__,__FILE__);
		while (!$cargo_query->EOF) 
		{
			$cargo_info = $cargo_query->fields;
			$index = str_replace(" ", "_", $cargo_info['classname']);
			$newcargotype[$cargototal] = AAT_strtolower($cargo_info['classname']);
			$newcargoclass[$cargototal] = AAT_strtolower($cargo_info['class']);
			$limit[$cargototal] = $cargo_info['itemlimit'];
			$initialamount[$cargototal] = $cargo_info['itemlimit'] * $_POST['initscommod'] / 100.0;
			$fixed_start_prices[$cargototal] = $cargo_info['fixed_start_price'];
			$increaserate[$cargototal] = $cargo_info['increaserate'];
			$good_evil[$cargototal] = $cargo_info['goodevil'];
			$cargosell_buy[$cargototal] = $cargo_info['cargosellbuy'];
			$hold_space[$cargototal] = $cargo_info['hold_space'];
			$cargototal++;
			$cargo_query->Movenext();
		}
		$cargo_query->close();

		while ($portcount > 0)
		{
			$port_sector='';
			$random_sector='';
			$random_sector = mt_rand(5, $maxsector); // 5 because you cant include the first 5 sectors.

			if($enable_spiral_galaxy != 1)
			{
				$port_sector = $db->SelectLimit("SELECT zone_id, ".
											 "SQRT((($Xdistance-x) * ($Xdistance-x))+(($Ydistance-y) * ($Ydistance-y))+(($Zdistance-z) * ($Zdistance-z))) as distance ".
											 "FROM {$db_prefix}universe ".
											 "WHERE port_type='none' and zone_id != 2 and sg_sector = 0 ".
											 "AND sector_id='$random_sector'", 1);
				db_op_result($port_sector,__LINE__,__FILE__);
			}
			else
			{
				$port_sector = $db->SelectLimit("SELECT zone_id, ".
											 "SQRT(POW(($Xdistance-x),2)+POW(($Ydistance-y),2)+POW(($Zdistance-z),2)) as distance " .
											 "FROM {$db_prefix}universe ".
											 "WHERE port_type='none' and zone_id != 2 and sg_sector = 0 ".
											 "AND sector_id='$random_sector'", 1);
				db_op_result($port_sector,__LINE__,__FILE__);
			}

			if (!$port_sector->EOF)
			{
				$ratio = $port_sector->fields['distance'] / $max_distance;
				$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='" . $classname . "' WHERE sector_id='$random_sector'");
				db_op_result($debug_query,__LINE__,__FILE__);

				$prices = (mt_rand(500, $fixed_start_price * 1000) / 1000) * 2;
				$maxcommodities = $max_port_buy_commodities;
				$insertlist = "";

				for($ii = 0; $ii < $cargototal; $ii++)
				{
					if($maxcommodities > 0)
					{
						if($newcargotype[$ii] != $classname && mt_rand(1, 100) < 50 && $cargosell_buy[$ii] != 2)
						{
							$startprices = (mt_rand(500, $fixed_start_prices[$ii] * 1000) / 1000) * 2;
							$startprices += $fixed_start_prices[$ii] * $ratio;
							if($increaserate[$ii] == 0)
							{
									$startprices = $fixed_start_prices[$ii] / 2;
							}
							$insertlist .= ", ($random_sector, '" . $newcargotype[$ii] . "', $limit[$ii], " . $startprices . ", '" . date("Y-m-d H:i:s") . "', $good_evil[$ii])";
							$maxcommodities--;
						}
					}
				}

				$port_query = "INSERT INTO {$db_prefix}universe_ports 
					(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
					VALUES 
					('$random_sector', '" . $classname . "', '$itemlimit', '$prices', '" . date("Y-m-d H:i:s") . "', '$goodevil') 
					$insertlist";
//				echo $port_query . "<br>";
				$debug_query = $db->Execute($port_query);
				db_op_result($debug_query,__LINE__,__FILE__);
				$portcount--;
			}
			$port_sector->close();
		}
	}
}

?>
<tr>
<td>
<table align="center" border="1" cellpadding="5" cellspacing=0>
	<form action=admin.php method=post>
<?php
$color = "#000000";
$color1 = "#000000";
$color2 = "#222222";
$i = 0;

$filelist = get_dirlist($gameroot."class/commodities/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$cargoname =  str_replace(".inc", "", $filelist[$c]); 
		$result2 = $db->Execute("SELECT class FROM {$db_prefix}class_modules_commodities where class='$cargoname'");
		db_op_result($result2,__LINE__,__FILE__);
		if($result2->RecordCount() == 0)
		{
			echo "<tr bgcolor=\"$color\">";
			echo "<td align=\"center\">" . $cargoname . "</td>";
			echo "<td><input type=\"radio\" name=\"cargoname\" value=\"$cargoname\"><font color=\"#00ff00\">Add</font></td>";
			if($color == $color1)
			{
				$color = $color2;
			}
			else
			{
				$color = $color1; 
			}
			echo "</tr>\n";
			$i++;
		}
	}
}
if($i == 0)
{
	echo "<tr bgcolor=\"$color\">";
	echo "<td align=\"center\">All Commodites have been installed.</td>";
	echo "</tr>\n";
}
?>
</table>
</td>
</tr>
<?php
echo "<tr><td colspan=\"2\" align=\"center\"><INPUT TYPE=HIDDEN NAME=menu VALUE=\"Update_Add_Commodity\">";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=SUBMIT NAME=command VALUE=\"add\"></td></tr>"
?>
</form>


