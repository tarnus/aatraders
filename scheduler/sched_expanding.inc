<?php
// 1
// 1900
// 1440
// 0
// Y
// How often the Federation will find new sectors that are added to the game..


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/insert_news.inc");

function check_php_version () {
   $testSplit = explode ('.', '4.3.0');
   $currentSplit = explode ('.', phpversion());

   if ($testSplit[0] < $currentSplit[0])
       return True;
   if ($testSplit[0] == $currentSplit[0]) {
       if ($testSplit[1] < $currentSplit[1])
           return True;
       if ($testSplit[1] == $currentSplit[1]) {
           if ($testSplit[2] <= $currentSplit[2])
               return True;
       }
   }
   return False;
}

function create_sector_number($prefix)
{
	global $db, $db_prefix;

	$alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	$newname = $prefix . AAT_substr($alphanumeric, mt_rand(26, 35), 1) . AAT_substr($alphanumeric, mt_rand(0, 35), 1) . AAT_substr($alphanumeric, mt_rand(26, 35), 1) . AAT_substr($alphanumeric, mt_rand(0, 35), 1) . AAT_substr($alphanumeric, mt_rand(0, 35), 1);
	$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($newname), 1);
	db_op_result($sector_check,__LINE__,__FILE__);

	if($sector_check->RecordCount() != 0)
	{
		create_sector_number($prefix);
	} 
	else 
	{
		return $newname;
	}
}

if (!check_php_version ())
{
	$enable_spiral_galaxy = 0;
}

$found_planets = 0;
$new_ports = 0;
$addedsectors = 0;

$cargototal = 0;
$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where cargoport=1 order by defaultcargoplanet DESC, default_create_percent DESC");
db_op_result($cargo_query,__LINE__,__FILE__);

$default_create_ratio = 100 / $cargo_query->fields['default_create_percent'];
$default_create_ratio_new = 1;

while (!$cargo_query->EOF) 
{
	$cargo_info = $cargo_query->fields;
	$newcargotype[$cargototal] = $cargo_info['classname'];
	$limitamount[$cargototal] = $cargo_info['itemlimit'];
	$initialamount[$cargototal] = $cargo_info['itemlimit'] * $_POST['initscommod'] / 100.0;
	$fixed_start_price[$cargototal] = $cargo_info['fixed_start_price'];
	$increaserate[$cargototal] = $cargo_info['increaserate'];
	$goodevil[$cargototal] = $cargo_info['goodevil'];
	$cargosellbuy[$cargototal] = $cargo_info['cargosellbuy'];
	$default_create_percent[$cargototal] = $cargo_info['default_create_percent'] * $default_create_ratio;
	if($cargo_info['defaultcargoplanet'] == 0 && $default_create_ratio_new == 1)
	{
		$default_create_ratio_new = 200 / $cargo_info['default_create_percent'];
		echo $cargo_info['default_create_percent'] . "<br>";
	}
	$default_create_percent_new[$cargototal] = $cargo_info['default_create_percent'] * $default_create_ratio_new;
	$hold_space[$cargototal] = $cargo_info['hold_space'];
	$cargototal++;
	$cargo_query->Movenext();
}
$cargo_query->close();
echo "ratio: " . $default_create_ratio . " - " . $default_create_ratio_new . "<br>";
$defaultcargototal = 0;
$extracargototal = 0;

$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where defaultcargoplanet=1 or cargoplanet=1 order by defaultcargoplanet DESC");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargo_info = $cargo_query->fields;
	if($cargo_info['defaultcargoplanet'] == 1)
	{
		$dnewcargotype[$defaultcargototal] = $cargo_info['classname'];
		$dcargoclass[$defaultcargototal] = $cargo_info['cargoclass'];
		$ddefault_prod[$defaultcargototal] = $cargo_info['default_prod'];
		$ddefault_indy_prod[$defaultcargototal] = $cargo_info['default_indy_prod'];
		$dfixed_start_price[$defaultcargototal] = $cargo_info['fixed_start_price'];
		$dlimitamount[$defaultcargototal] = $cargo_info['itemlimit'];
		$dincreaserate[$defaultcargototal] = $cargo_info['increaserate'];
		$dis_prod[$defaultcargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
		$dgoodevil[$defaultcargototal] = $cargo_info['goodevil'];
		$defaultcargototal++;
	}
	else
	{
		if($cargo_info['cargoplanet'] == 1)
		{
			$p_newcargotype[$extracargototal] = $cargo_info['classname'];
			$p_cargoclass[$extracargototal] = $cargo_info['cargoclass'];
			$p_default_prod[$extracargototal] = $cargo_info['default_prod'];
			$p_default_indy_prod[$defaultcargototal] = $cargo_info['default_indy_prod'];
			$p_is_prod[$extracargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
			$p_goodevil[$extracargototal] = $cargo_info['goodevil'];
			$extracargototal++;
		}
	}
	$cargo_query->Movenext();
}
$cargo_query->close();

if($allow_expanding_universe == 1){
	TextFlush ( "<b>Expanding Universe</b><br><br>\n");

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

	$max_distance = max(floor($results->fields['distance']), 1);

	$debug_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
	db_op_result($debug_query,__LINE__,__FILE__);

	$endsector = $debug_query->fields['sector_id'];

	$debug_query->close();
	$stamp = date("Y-m-d H:i:s");

	$collisions = 0;
	# calculate the scale to use such that 
	# the max distance between 2 points will be
	# approx $universe_size.
	$scale = $universe_size / (4.0*pi());

	# compute the angle between arms
	$angle = deg2rad(360/$spiral_galaxy_arms);
	$addedsectors = mt_rand(1, $universe_expansion_rate);
	$found_planets = 0;
	$new_ports = 0;

	TextFlush ("Creating ". $addedsectors ." New Sectors <br><br>");
	for ($i=0; $i<$addedsectors; $i++) 
	{
		$sector = '';
		$collision = FALSE;
		while (TRUE) 
		{
			if($enable_spiral_galaxy != 1){
				// Lot of shortcuts here. Basically we generate a spherical coordinate and convert it to cartesian.
				// Why? Cause random spherical coordinates tend to be denser towards the center.
				// Should really be like a spiral arm galaxy but this'll do for now.
				$radius = mt_rand(100,$universe_size*100)/100;

				$temp_a = deg2rad(mt_rand(0,36000)/100-180);
				$temp_b = deg2rad(mt_rand(0,18000)/100-90);
				$temp_c = $radius*sin($temp_b);

				$sector['x'] = round(cos($temp_a)*$temp_c);
				$sector['y'] = round(sin($temp_a)*$temp_c);
				$sector['z'] = round($radius*cos($temp_b));
				$sector['spiral_arm'] = 0;

				// Collision check
				$debug_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe WHERE x=$sector[x] and y=$sector[y] and z=$sector[z] ", 1);
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();

				if ($debug_query->RecordCOunt() != 0) 
				{
					$collisions++;
				} 
				else 
				{
					break;
				}
			}
			else
			{
				//The Spiral Galaxy Code was proviced by "Kelly Shane Harrelson" <shane@mo-ware.com> 
				# need to randomly assign this point to an arm.
				$arm = mt_rand(0,$spiral_galaxy_arms-1);
				$arm_offset = $arm * $angle;

				# generate the logical position on the spiral (0 being closer to the center).
				# the double rand puts more towards the center.
				$u = deg2rad(mt_rand(0, mt_rand(0, 360)));

				# generate the base x,y,z location in cartesian form
				$bx = $u*cos($u+$arm_offset);
				$by = $u*sin($u+$arm_offset);
				$bz = 0.0;

				# generate a max delta from the base x, y, z.
				# this will be larger closer to the center,
				# tapering off the further out you are. 
				# this will create the bulge like effect in 
				# the center.	this is just a rough function
				# and there are probably better ones out there.
				$d = ($u<0.3) ? 1.5 : (log($u,10)*-1.0)+1.0;	# log base 10

				# generate random angles and distance for offsets from base x,y,z
				$dt = deg2rad(mt_rand(0, 360)); # angle theta 0-360
				$dp = deg2rad(mt_rand(0, 360)); # angle phi	0-360
				$dd = $d*mt_rand(1,100)/100;	 # distance	 0-$d

				# based on random angles and distance, generate cartesian offsets for base x,y,z
				$dx = $dd*sin($dt)*cos($dp);
				$dy = $dd*sin($dt)*sin($dp);
				$dz = $dd*cos($dt);

				# we want the arms to flatten out away from center
				$dz *= ($d/1.5);	

				# calcuate final cartesian coordinate 
				$x = $bx + $dx;
				$y = $by + $dy;
				$z = $bz + $dz;

				# now scale them to fit $universe_size
				$x *= $scale;
				$y *= $scale;
				$z *= $scale;

				$sector['x'] = $x;
				$sector['y'] = $y;
				$sector['z'] = $z;
				$sector['spiral_arm'] = $arm;

				// Collision check
				$debug_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe WHERE x=$sector[x] and y=$sector[y] and z=$sector[z] ", 1);
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();

				if ($debug_query->RecordCOunt() != 0) 
				{
					$collisions++;
				}
				else 
				{
					break;
				}
			}
		}

		$port_type= mt_rand(0,100);
		if($max_sector_size > 5)
			$max_sector_size = 5;
		$star_size = mt_rand(0, $max_sector_size);

		if ($port_type > 30){
			$port="none";
			$res = $db->Execute("INSERT INTO {$db_prefix}universe (zone_id, star_size, x, y, z, spiral_arm, port_type, creation_date) VALUES (1, " . $star_size . ", $sector[x], $sector[y], $sector[z], $sector[spiral_arm], '$port', '$stamp') ");
			db_op_result($res,__LINE__,__FILE__);
			$sector_id = $db->insert_id();
			$res->close();
		}elseif ($port_type >5){
			$random_port = mt_rand(5, $cargototal - 1);
			$port = $newcargotype[$random_port];

			if($cargosellbuy[$random_port] != 1)
			{
				$random_value = mt_rand(0, 100);
				echo $random_value . " - " . $default_create_percent_new[$random_port] . "<br>";
				if($random_value < $default_create_percent_new[$random_port])
				{
					TextFlush ("Creating New ". ucwords($newcargotype[$random_port]) ." Port <br>");
					$res = $db->Execute("INSERT INTO {$db_prefix}universe (zone_id, star_size, x, y, z, spiral_arm, port_type, creation_date) VALUES (1, " . $star_size . ", $sector[x], $sector[y], $sector[z], $sector[spiral_arm], '$port', '$stamp') ");
					db_op_result($res,__LINE__,__FILE__);

					if($enable_spiral_galaxy != 1){
						$new_distance = sqrt(($sector['x']*$sector['x']) + ($sector['y']*$sector['y']) + ($sector['z']*$sector['z']));
					}else{
		    			$new_distance = sqrt(pow($sector['x'],2.0)+pow($sector['y'],2.0)+pow($sector['z'],2.0));
					}
					$ratio = $new_distance / $max_distance;
					$sector_id = $db->insert_id();
					$res->close();

					$randompoint = mt_rand(500000, 1000000) / 1000000;
					$prices = floor($fixed_start_price[$random_port] * $randompoint);
					if($increaserate[$random_port] == 0)
					{
						$prices = $fixed_start_price[$random_port];
					}

					$maxcommodities = $max_port_buy_commodities;
					$insertlist = "";
					for($ii = 0; $ii < $cargototal; $ii++)
					{
						if($maxcommodities > 0)
						{
							if($ii != $random_port && mt_rand(1, 100) < 50 && $cargosellbuy[$ii] != 2)
							{
								$randompoint = mt_rand(500000, 1000000) / 1000000;
								$buyprices = floor($fixed_start_price[$ii] * $randompoint) * 3;
								$buyprices += $fixed_start_price[$ii] * $ratio;
								if($increaserate[$ii] == 0)
								{
									$buyprices = $fixed_start_price[$ii] / 2;
								}
								$insertlist .= ", ($sector_id, '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
								$maxcommodities--;
							}
						}
					}

					$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
						(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
						VALUES 
						($sector_id, '" . $newcargotype[$random_port] . "', $limitamount[$random_port], $prices, '" . date("Y-m-d H:i:s") . "', $goodevil[$random_port]) 
						$insertlist");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
					$new_ports++;
				}
				else
				{
					$random_port = mt_rand(0, $defaultcargototal - 1);
					$port = $dnewcargotype[$random_port];

					TextFlush ("Creating New ". ucwords($dnewcargotype[$random_port]) ." Port <br>");
					$res = $db->Execute("INSERT INTO {$db_prefix}universe (zone_id, star_size, x, y, z, spiral_arm, port_type, creation_date) VALUES (1, " . $star_size . ", $sector[x], $sector[y], $sector[z], $sector[spiral_arm], '$port', '$stamp') ");
					db_op_result($res,__LINE__,__FILE__);

					if($enable_spiral_galaxy != 1){
						$new_distance = sqrt(($sector['x']*$sector['x']) + ($sector['y']*$sector['y']) + ($sector['z']*$sector['z']));
					}else{
		    			$new_distance = sqrt(pow($sector['x'],2.0)+pow($sector['y'],2.0)+pow($sector['z'],2.0));
					}
					$ratio = $new_distance / $max_distance;
					$sector_id = $db->insert_id();
					$res->close();

					$randompoint = mt_rand(500000, 1000000) / 1000000;
					$prices = floor($fixed_start_price[$random_port] * $randompoint);
					if($dincreaserate[$random_port] == 0)
					{
						$prices = $dfixed_start_price[$random_port];
					}

					$maxcommodities = $max_port_buy_commodities;
					$insertlist = "";
					for($ii = 0; $ii < $cargototal; $ii++)
					{
						if($maxcommodities > 0)
						{
							if($port != $newcargotype[$ii] && mt_rand(1, 100) < 50 && $cargosellbuy[$ii] != 2)
							{
								$randompoint = mt_rand(500000, 1000000) / 1000000;
								$buyprices = floor($fixed_start_price[$ii] * $randompoint) * 3;
								$buyprices += $fixed_start_price[$ii] * $ratio;
								if($increaserate[$ii] == 0)
								{
									$buyprices = $fixed_start_price[$ii] / 2;
								}
								$insertlist .= ", ($sector_id, '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
								$maxcommodities--;
							}
						}
					}

					$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
						(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
						VALUES 
						($sector_id, '" . $dnewcargotype[$random_port] . "', $dlimitamount[$random_port], $prices, '" . date("Y-m-d H:i:s") . "', $dgoodevil[$random_port]) 
						$insertlist");
					db_op_result($debug_query,__LINE__,__FILE__);
				}
			}
			else
			{
				$random_port = mt_rand(0, $defaultcargototal - 1);
				$port = $dnewcargotype[$random_port];

				TextFlush ("Creating New ". ucwords($dnewcargotype[$random_port]) ." Port <br>");
				$res = $db->Execute("INSERT INTO {$db_prefix}universe (zone_id, star_size, x, y, z, spiral_arm, port_type, creation_date) VALUES (1, " . $star_size . ", $sector[x], $sector[y], $sector[z], $sector[spiral_arm], '$port', '$stamp') ");
				db_op_result($res,__LINE__,__FILE__);

				if($enable_spiral_galaxy != 1){
					$new_distance = sqrt(($sector['x']*$sector['x']) + ($sector['y']*$sector['y']) + ($sector['z']*$sector['z']));
				}else{
	    			$new_distance = sqrt(pow($sector['x'],2.0)+pow($sector['y'],2.0)+pow($sector['z'],2.0));
				}
				$ratio = $new_distance / $max_distance;
				$sector_id = $db->insert_id();
				$res->close();

				$randompoint = mt_rand(500000, 1000000) / 1000000;
				$prices = floor($fixed_start_price[$random_port] * $randompoint);
				if($dincreaserate[$random_port] == 0)
				{
					$prices = $dfixed_start_price[$random_port];
				}

				$maxcommodities = $max_port_buy_commodities;
				$insertlist = "";
				for($ii = 0; $ii < $cargototal; $ii++)
				{
					if($maxcommodities > 0)
					{
						if($port != $newcargotype[$ii] && mt_rand(1, 100) < 50 && $cargosellbuy[$ii] != 2)
						{
							$randompoint = mt_rand(500000, 1000000) / 1000000;
							$buyprices = floor($fixed_start_price[$ii] * $randompoint) * 3;
							$buyprices += $fixed_start_price[$ii] * $ratio;
							if($increaserate[$ii] == 0)
							{
								$buyprices = $fixed_start_price[$ii] / 2;
							}
							$insertlist .= ", ($sector_id, '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
							$maxcommodities--;
						}
					}
				}

				$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
					(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
					VALUES 
					($sector_id, '" . $dnewcargotype[$random_port] . "', $dlimitamount[$random_port], $prices, '" . date("Y-m-d H:i:s") . "', $dgoodevil[$random_port]) 
					$insertlist");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}else{
			$random_port = mt_rand(1,3);
			if ($random_port==1){
				$port="upgrades";
			}elseif ($random_port==2){
				$port="devices";
			}else{
				$port="spacedock";
			}
			TextFlush ("Creating New ". ucwords($port) ." Port<br>");
			$res = $db->Execute("INSERT INTO {$db_prefix}universe (zone_id, star_size, x, y, z, spiral_arm, port_type, creation_date) VALUES (1, " . $star_size . ", $sector[x], $sector[y], $sector[z], $sector[spiral_arm], '$port', '$stamp') ");
			db_op_result($res,__LINE__,__FILE__);
			$sector_id = $db->insert_id();
			$res->close();
			$new_ports++;
		}
		$sectorname = create_sector_number(chr(80 + $sector['spiral_arm']) . (string)$star_size);
		$debug_query = $db->Execute("UPDATE {$db_prefix}universe SET sector_name = " . $db->qstr($sectorname) . " WHERE sector_id = $sector_id");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();

		for($star = 0; $star < $star_size; $star++)
		{
			if(mt_rand(0, 10000) < 1000)
			{
				$new_age = ($display_percentage_age / 2) + mt_rand(0, $display_percentage_age);
				$insertlist = "";
				$insertlistprod = "";
				for($ii = 0; $ii < $defaultcargototal; $ii++)
				{
					if($ddefault_prod[$ii] > 0)
					{
						$insertlist .= ", prod_" . AAT_strtolower($dnewcargotype[$ii]);
						$insertlistprod .= ", '$ddefault_prod[$ii]'";
					}
				}

				$specialcargo = mt_rand(0, $extracargototal - 1);
				if(mt_rand(0, 100) < 50 && $extracargototal != 0)
				{
					$special_cargo = $p_newcargotype[$specialcargo];
					$special_goodevil = $p_goodevil[$specialcargo];
				}
				else
				{
					$special_cargo = '';
					$special_goodevil = 0;
				}

				if(mt_rand(1, 100) <= $planet_production_skew)
				{
					$organics_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
				}
				else
				{
					$organics_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
				}

				if(mt_rand(1, 100) <= $planet_production_skew)
				{
					$ore_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
				}
				else
				{
					$ore_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
				}

				if(mt_rand(1, 100) <= $planet_production_skew)
				{
					$goods_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
				}
				else
				{
					$goods_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
				}

				if(mt_rand(1, 100) <= $planet_production_skew)
				{
					$energy_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
				}
				else
				{
					$energy_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
				}
				TextFlush ("<font color=\"green\">A planet has been found in sector</font> <font color=\"yellow\">$sectorname</font><br>");
				$creation_date = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}planets 
				(sector_id, max_credits, prod_fighters, prod_torp, special_name, special_goodevil, organics_planet, ore_planet, goods_planet, energy_planet, use_age, creation_date" . $insertlist . ") 
				VALUES 
				('$sector_id', '$base_credits', '$default_prod_fighters', '$default_prod_torp', '$special_cargo', '$special_goodevil', '$organics_planet', '$ore_planet', '$goods_planet', '$energy_planet', '$new_age', '$creation_date'" . $insertlistprod . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query->close();
				$found_planets++;
			}
		}

		unset($sector);
	}

	if ($collisions) 
	{
		TextFlush ("<font color=\"yellow\">$collisions sector collisions repaired</font> ");
	} 
	else 
	{
		TextFlush ("No sector collisions detected ");
	}

	$debug_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
	db_op_result($debug_query,__LINE__,__FILE__);

	$newendsector = $debug_query->fields['sector_id'];
	$debug_query->close();

	TextFlush ( "<br>Generating warp links <br>\n");
	for ($i=$endsector+1; $i<=$newendsector; $i++) 
	{
		$numlinks = mt_rand(0,5);
		for ($j=0; $j<$numlinks; $j++)
		{
			$randplay=mt_rand(0,($sector_list_total-1));
			$destination = $sector_list[$randplay]['sector_id'];

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES ($i,$destination);");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();
			$link_odds = mt_rand(0,100);
			if ($link_odds < 50)
			{
				$result4 = $db->Execute(" SELECT * FROM {$db_prefix}links where link_start=$destination");
				db_op_result($result4,__LINE__,__FILE__);

				$totalcount = $result4->RecordCount();
				$result4->close();
				if($totalcount <= 5){
					$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES ($destination,$i);");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
				}
			}
		}
	}
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}navmap");
	db_op_result($debug_query,__LINE__,__FILE__);
	TextFlush ( "<br><font color=\"lime\">- operation completed successfully.</font><br><br>");
}

if($found_planets > 0)
{
	insert_news($found_planets, 1, "found_planets", 0);
}
if($new_ports > 0)
{
	insert_news($new_ports, 1, "new_ports", 0);
}
if($addedsectors > 0)
{
	insert_news($addedsectors, 1, "addedsectors", 0);
}

TextFlush ( "<br>\n");
$multiplier = 0; //no use to run this again

$new_ticks = 1440 + ((mt_rand(0, 288) - 144) * 5);
TextFlush ("<br><br>Next Tick: $new_ticks<br><br>");
$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET ticks_full=$new_ticks WHERE sched_file='sched_expanding.inc'");
db_op_result($debug_query,__LINE__,__FILE__);
TextFlush ( "<br>\n");
TextFlush ( "<br>\n");

?>
