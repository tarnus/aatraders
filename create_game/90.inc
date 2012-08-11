<?php
// Step 90 - Create all Sector Ports

include ("globals/calc_dist.inc");

// Locations are mapped out so now we need ports.
	$silent = 1;

TextFlush("<b>Preparing for port placement:</b>\n<br>");

// Placing Federation Sol Forum
$debug_query = $db->Execute("INSERT INTO {$db_prefix}casino_forums (forum_name, forum_desc, private, casino_sector, forum_posts, forum_topics, lastposttime) values ('Federation Bulletins and Information', 'Important Federation Information', '0', '1', '11', '11', '2007-04-03 06:00:00')");
db_op_result($debug_query,__LINE__,__FILE__);

$filename = "support/casino_topics.sql";
$fileread = fopen($filename,"r");
while(!@feof($fileread))
{
	$sql = str_replace('{$db_prefix}', $db_prefix, trim(@fgets($fileread)));
	if(!empty($sql))
	{
		$debug_query = $db->Execute($sql);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

fclose($fileread);

$filename = "support/casino_posts.sql";
$fileread = fopen($filename,"r");
while(!@feof($fileread))
{
	$sql = str_replace('{$db_prefix}', $db_prefix, trim(@fgets($fileread)));
	if(!empty($sql))
	{
		$debug_query = $db->Execute($sql);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

$filename = "support/casino_posts_text.sql";
$fileread = fopen($filename,"r");
while(!@feof($fileread))
{
	$sql = str_replace('{$db_prefix}', $db_prefix, trim(@fgets($fileread)));
	if(!empty($sql))
	{
		$debug_query = $db->Execute($sql);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

// Creating Casino Port Forum
$debug_query = $db->Execute("INSERT INTO {$db_prefix}casino_forums (forum_name, forum_desc, private, casino_sector) values ('Smugglers Den Bar', 'Welcome and have fun!', '0', '2')");
db_op_result($debug_query,__LINE__,__FILE__);

// Device port placement
TextFlush("\n<br>Placing $_POST[upp] device ports<br>\n");

$totaluports = 0;
while ($_POST['upp']-1 > 0) // subtract one for the existing device port in fed space.
{
	$sector='';
	$random_sector = mt_rand(5, $_POST['sektors']); // 3 because you cant include the first three sectors.
	$upp_sector = $db->Execute("SELECT port_type, sector_id ".
								 "FROM {$db_prefix}universe ".
								 "WHERE port_type='none' ".
								 "AND sector_id='$random_sector' LIMIT 1");
	db_op_result($upp_sector,__LINE__,__FILE__);

	if (!$upp_sector->EOF)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='devices', zone_id='1' WHERE sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$_POST['upp']--;
		$portslist[$totaluports] = $random_sector;
		$totaluports++;
	}
	$upp_sector->close();
}

// Upgrade port placement
TextFlush("\n<br>Placing $_POST[spp] upgrade ports <br>\n");

$totalsports = 0;
while ($_POST['spp']-1 > 0) // subtract one for the existing device port in fed space.
{
	$sector='';
	$random_sector = mt_rand(5, $_POST['sektors']); // 3 because you cant include the first three sectors.
	$spp_sector = $db->Execute("SELECT port_type, sector_id ".
								 "FROM {$db_prefix}universe ".
								 "WHERE port_type='none' ".
								 "AND sector_id='$random_sector' LIMIT 1");
	db_op_result($spp_sector,__LINE__,__FILE__);

	if (!$spp_sector->EOF)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='upgrades', zone_id='1' WHERE sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$_POST['spp']--;
		$portslist2[$totalsports] = $random_sector;
		$totalsports++;
	}
	$spp_sector->close();
}

// Spacedock port placement
TextFlush("\n<br>Placing $_POST[dpp] spacedock ports <br>\n");

$totalsports = 0;
while ($_POST['dpp']-1 > 0) // subtract one for the existing device port in fed space.
{
	$sector='';
	$random_sector = mt_rand(5, $_POST['sektors']); // 3 because you cant include the first three sectors.
	$dpp_sector = $db->Execute("SELECT port_type, sector_id ".
								 "FROM {$db_prefix}universe ".
								 "WHERE port_type='none' ".
								 "AND sector_id='$random_sector' LIMIT 1");
	db_op_result($dpp_sector,__LINE__,__FILE__);

	if (!$dpp_sector->EOF)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='spacedock', zone_id='1' WHERE sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$_POST['dpp']--;
		$portslist3[$totalsports] = $random_sector;
		$totalsports++;
	}
	$dpp_sector->close();
}

// Alliance Device/Upgrade port zone placement
TextFlush("\n<br>Placing $_POST[kpp] Alliance device/upgrade zones <br>\n");
$totalkpp = $_POST['kpp'];
while ($_POST['kpp'] > 0) // subtract one for the existing device port in fed space.
{
	if($_POST['kpp'] <= floor($totalkpp / 2)){
		$random_selection = mt_rand(0, $totaluports - 1);
		$random_sector = $portslist[$random_selection];
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='devices', zone_id='3', star_size='0' WHERE sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);
	}else{
		$random_selection = mt_rand(0, $totalsports - 1);
		$random_sector = $portslist2[$random_selection];
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='upgrades', zone_id='3', star_size='0' WHERE sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
	$_POST['kpp']--;
}

// Alliance Casino port placement
TextFlush("\n<br>Placing $_POST[cpp] Alliance Casino ports <br>\n");

$totalsports = 0;
while ($_POST['cpp'] > 0)
{
	$sector='';
	$random_sector = mt_rand(5, $_POST['sektors']); // 3 because you cant include the first three sectors.
	$cpp_sector = $db->Execute("SELECT port_type, sector_id ".
								 "FROM {$db_prefix}universe ".
								 "WHERE port_type='none' ".
								 "AND sector_id='$random_sector' LIMIT 1");
	db_op_result($cpp_sector,__LINE__,__FILE__);

	if (!$cpp_sector->EOF)
	{
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='casino', zone_id='3', star_size='0' WHERE sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);
		$_POST['cpp']--;
		$portslist4[$totalsports] = $random_sector;
		$totalsports++;
	}
	$cpp_sector->close();
}

$typetotal = 0;
$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where defaultcargoplanet=1 order by defaultcargoplanet DESC");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargo_info = $cargo_query->fields;
	$fedcargotype[$typetotal] = AAT_strtolower($cargo_info['classname']);
	$fedlimit[$typetotal] = $cargo_info['itemlimit'];
	$fed_start_price[$typetotal] = $cargo_info['fixed_start_price'];
	$fedgoodevil[$typetotal] = $cargo_info['goodevil'];
	$fedincreaserate[$cargototal] = $cargo_info['increaserate'];
	$typetotal++;
	$cargo_query->Movenext();
}
$cargo_query->close();

$port_query = $db->Execute("SELECT sector_id FROM {$db_prefix}universe WHERE port_type='none' and zone_id = 2");
db_op_result($port_sector,__LINE__,__FILE__);

while (!$port_query->EOF) 
{
	$port_info = $port_query->fields;
	$index = mt_rand(0, $typetotal-1);
	$query = "UPDATE {$db_prefix}universe SET port_type='" . $fedcargotype[$index] . "' WHERE sector_id='$port_info[sector_id]'";
//	echo $query . "<br>";
	$debug_query = $db->Execute($query);
	db_op_result($debug_query,__LINE__,__FILE__);

	$randompoint = mt_rand(500000, 1000000) / 1000000;
	$prices = floor($fed_start_price[$index] * $randompoint);
	if($fedincreaserate[$index] == 0)
	{
		$prices = $fed_start_price[$index];
	}
	$insertlist = "";

	for($ii = 0; $ii < 5; $ii++)
	{
		if($fedcargotype[$ii] != $fedcargotype[$index])
		{
			$randompoint = mt_rand(500000, 1000000) / 1000000;
			$startprices = floor($fed_start_price[$ii] * $randompoint) * 3;
			if($fedincreaserate[$ii] == 0)
			{
				$startprices = $fed_start_price[$ii] / 2;
			}
			$insertlist .= ", ($port_info[sector_id], '" . $fedcargotype[$ii] . "', $fedlimit[$ii], " . $startprices . ", '" . date("Y-m-d H:i:s") . "', $fedgoodevil[$ii])";
		}
	}

	$insert_query = "INSERT INTO {$db_prefix}universe_ports 
		(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
		VALUES 
		('$port_info[sector_id]', '" . $fedcargotype[$index] . "', '$fedlimit[$index]', '$prices', '" . date("Y-m-d H:i:s") . "', '$fedgoodevil[$index]') 
		$insertlist";
//	echo $insert_query . "<hr>";
	$debug_query = $db->Execute($insert_query);
	db_op_result($debug_query,__LINE__,__FILE__);
	$port_query->Movenext();
}

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
	$query2 = "SELECT sector_name, sector_id as dest_sector, port_type, zone_id, x, y, z,SQRT((($Xdistance-x) * ($Xdistance-x))+(($Ydistance-y) * ($Ydistance-y))+(($Zdistance-z) * ($Zdistance-z))) as distance FROM {$db_prefix}universe where sector_id!=1 and sg_sector = 0  ORDER BY distance DESC";
}
else
{
	$query2 = "SELECT sector_name, spiral_arm, sector_id as dest_sector, port_type, zone_id, x, y, z,SQRT(POW(($Xdistance-x),2)+POW(($Ydistance-y),2)+POW(($Zdistance-z),2)) as distance FROM {$db_prefix}universe where sector_id!=1 and sg_sector = 0  ORDER BY distance DESC";
}

$results = $db->SelectLimit($query2, 1);

$max_distance = floor($results->fields['distance']);

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
	$fixed_start_price[$cargototal] = $cargo_info['fixed_start_price'];
	$increaserate[$cargototal] = $cargo_info['increaserate'];
	$goodevil[$cargototal] = $cargo_info['goodevil'];
	$cargosellbuy[$cargototal] = $cargo_info['cargosellbuy'];
	$hold_space[$cargototal] = $cargo_info['hold_space'];
	$cargototal++;
	$cargo_query->Movenext();
}
$cargo_query->close();

for($i = 0; $i < $cargototal; $i++)
{
	$cargoleft = $_POST[$newcargoclass[$i]];

	if($cargosellbuy[$i] != 1)
	{
		TextFlush("\n<br>Placing $cargoleft " . ucwords($newcargotype[$i]) . " ports <br>\n");
		while ($_POST[$newcargoclass[$i]] > 0)
		{

			$port_sector='';
			$random_sector='';
			$random_sector = mt_rand(5, $_POST['sektors']); // 5 because you cant include the first 5 sectors.
			if($enable_spiral_galaxy != 1)
			{
				$port_sector = $db->SelectLimit("SELECT zone_id, ".
											 "SQRT((($Xdistance-x) * ($Xdistance-x))+(($Ydistance-y) * ($Ydistance-y))+(($Zdistance-z) * ($Zdistance-z))) as distance ".
											 "FROM {$db_prefix}universe ".
											 "WHERE port_type='none' and sg_sector = 0 ".
											 "AND sector_id='$random_sector'", 1);
				db_op_result($port_sector,__LINE__,__FILE__);
			}
			else
			{
				$port_sector = $db->SelectLimit("SELECT zone_id, ".
											 "SQRT(POW(($Xdistance-x),2)+POW(($Ydistance-y),2)+POW(($Zdistance-z),2)) as distance " .
											 "FROM {$db_prefix}universe ".
											 "WHERE port_type='none' and sg_sector = 0 ".
											 "AND sector_id='$random_sector'", 1);
				db_op_result($port_sector,__LINE__,__FILE__);
			}

			if (!$port_sector->EOF)
			{
				$ratio = $port_sector->fields['distance'] / $max_distance;
				$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET port_type='" . $newcargotype[$i] . "' WHERE sector_id='$random_sector'");
				db_op_result($debug_query,__LINE__,__FILE__);

				$randompoint = mt_rand(500000, 1000000) / 1000000;
				$prices = floor($fixed_start_price[$i] * $randompoint);
				if($increaserate[$i] == 0)
				{
					$prices = $fixed_start_price[$i];
				}
				$maxcommodities = $max_port_buy_commodities;
				$insertlist = "";

				if ($port_sector->fields['zone_id'] == 2) 
				{
					for($ii = 0; $ii < 5; $ii++)
					{
						if($newcargotype[$ii] != $newcargotype[$i])
						{
							$randompoint = mt_rand(500000, 1000000) / 1000000;
							$startprices = floor($fixed_start_price[$ii] * $randompoint) * 3;
							$startprices += $fixed_start_price[$ii] * $ratio;
							if($increaserate[$ii] == 0)
							{
								$startprices = $fixed_start_price[$ii] / 2;
							}
							$insertlist .= ", ($random_sector, '" . $newcargotype[$ii] . "', $limit[$ii], " . $startprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
						}
					}
				}
				else
				{
					for($ii = 0; $ii < $cargototal; $ii++)
					{
						if($maxcommodities > 0)
						{
							if($ii != $i && mt_rand(1, 100) < 50 && $cargosellbuy[$ii] != 2)
							{
								$randompoint = mt_rand(500000, 1000000) / 1000000;
								$startprices = floor($fixed_start_price[$ii] * $randompoint) * 3;
								$startprices += $fixed_start_price[$ii] * $ratio;
								if($increaserate[$ii] == 0)
								{
									$startprices = $fixed_start_price[$ii] / 2;
								}
								$insertlist .= ", ($random_sector, '" . $newcargotype[$ii] . "', $limit[$ii], " . $startprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
								$maxcommodities--;
							}
						}
					}
				}

				$port_query = "INSERT INTO {$db_prefix}universe_ports 
					(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
					VALUES 
					('$random_sector', '" . $newcargotype[$i] . "', '$limit[$i]', '$prices', '" . date("Y-m-d H:i:s") . "', '$goodevil[$i]') 
					$insertlist";
//				echo $port_query . "<br>";
				$debug_query = $db->Execute($port_query);
				db_op_result($debug_query,__LINE__,__FILE__);
				$_POST[$newcargoclass[$i]]--;
				$fixed--;
			}
			$port_sector->close();
		}
	}
}

echo "<input type=hidden name=step value=90>";

?>