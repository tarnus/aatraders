<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: genesis.php

include ("config/config.php");
include ("languages/$langdir/lang_genesis.inc");
include ("globals/myrand.inc");

get_post_ifset("sectorname, sglink, target_sector, rslink");

$title = $l_sgns_title;

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template']; 
}
include ("header.php");

$result3 = $db->Execute("SELECT planet_id FROM {$db_prefix}planets WHERE sector_id='$shipinfo[sector_id]'");
$num_planets = $result3->RecordCount();

$res = $db->SelectLimit("SELECT {$db_prefix}universe.zone_id, {$db_prefix}zones.allow_planet, {$db_prefix}zones.team_zone, " .
					"{$db_prefix}zones.owner FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
					"{$db_prefix}zones.zone_id=$sectorinfo[zone_id] AND {$db_prefix}universe.sector_id = $shipinfo[sector_id]", 1);
$query97 = $res->fields;

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$max_query = $db->SelectLimit("SELECT sector_id from {$db_prefix}universe order by sector_id DESC", 1);
db_op_result($max_query,__LINE__,__FILE__);

$sector_max = $max_query->fields['sector_id'];

$gateway_sector = ($sectorinfo['sg_sector'] == 0) ? $sectorinfo['sector_id'] : $sectorinfo['sg_sector'];

function getsgcost($sector_id){

	global $db, $db_prefix, $playerinfo, $shipinfo, $sector_max, $level_factor, $max_sglinks;

	if(!class_exists("dev_sectorgenesis")){
		include ("class/devices/dev_sectorgenesis.inc");
	}
	$deviceobject = new dev_sectorgenesis();
	$dev_sectorgenesis_price = $deviceobject->price;

	$sgcost = $dev_sectorgenesis_price * 2;
	$searching = 1;
	$count = 0;

	$sector_res = $db->SelectLimit("SELECT sg_sector, created_from FROM {$db_prefix}universe WHERE sector_id=$sector_id", 1);
	$sector_type = $sector_res->fields['sg_sector'];
	$created_from = $sector_res->fields['created_from'];

	if($sector_type == 0)
	{
		return $dev_sectorgenesis_price;
	}

	if($created_from == $sector_type)
	{
		return $sgcost;
	}

	while($searching == 1){
		$search_query = "SELECT created_from FROM {$db_prefix}universe WHERE sector_id=$created_from";
   		$debug_query = $db->SelectLimit($search_query, 1);
		$created_from = $debug_query->fields['created_from'];

		if ($created_from != 0)
		{
			$count++;
			if($count == 50 or $sector_type == 0){
				$searching = 0;
				break;
			}
  			$sgcost = $sgcost * 2;
		}else{
			$searching = 0;
			break;
		}
	}
	return $sgcost;
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

if ($playerinfo['turns'] < 1)
{
	$template_object->assign("error_msg", $l_gns_turn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."sectorgenesisdie.tpl");
	include ("footer.php");
	die();
}

if ($shipinfo['on_planet'] == 'Y')
{
	$template_object->assign("error_msg", $l_gns_onplanet);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."sectorgenesisdie.tpl");
	include ("footer.php");
	die();
}

if ($shipdevice['dev_sectorgenesis']['amount'] < 1)
{
	$template_object->assign("error_msg", $l_sgns_nogenesis);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."sectorgenesisdie.tpl");
	include ("footer.php");
	die();
}

$sector_res = $db->SelectLimit("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($target_sector), 1);
$sectorid = $sector_res->fields['sector_id'];

if ($query97['allow_planet'] == 'N' || $sectorid == $shipinfo['sector_id'])
{
	$template_object->assign("error_msg", $l_sgns_forbid);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."sectorgenesisdie.tpl");
	include ("footer.php");
	die();
}

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);
//check sector and make sure its not past total sector total
$res = $db->Execute("SELECT * from {$db_prefix}links where  link_start=$shipinfo[sector_id] ");
$tlinks = $res->RecordCount();

// if past sector total make sure there are less that 2 warp links
// select chain or select loop point.
$sgcost = getsgcost($shipinfo['sector_id']);

if ($sglink==1){
	if ($playerinfo['credits'] < $sgcost){
		$template_object->assign("error_msg", $l_sgns_nocredits);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."sectorgenesisdie.tpl");
		include ("footer.php");
		die();
	}

	if ($tlinks >= $link_max){
		$template_object->assign("error_msg", str_replace("[limit]", "<font color=#00ff00><b>$link_max</b></font>", $l_sgns_forbid3));
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."sectorgenesisdie.tpl");
		include ("footer.php");
		die();
	}

	$sector_res = $db->SelectLimit("SELECT sg_sector, x, y, z FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
	db_op_result($sector_res,__LINE__,__FILE__);
	$sector_type = $sector_res->fields['sg_sector'];

	if (($sector_type == 0) or (($sector_type != 0) and ($tlinks < $max_sglinks))){
		$initsore = $ore_limit ;
		$initsorganics = $organics_limit ;
		$initsgoods = $goods_limit ;
		$initsenergy = $energy_limit ;
		$initbore = $ore_limit;
		$initborganics = $organics_limit ;
		$initbgoods = $goods_limit ;
		$initbenergy = $energy_limit ;
		$random_star = mt_rand(0,$max_sector_size);

		if($sector_type == 0)
		{
			$base_x = $sector_res->fields['x'];
			$base_y = $sector_res->fields['y'];
			$base_z = $sector_res->fields['z'];
		}
		else
		{
			$sector_res = $db->SelectLimit("SELECT x, y, z FROM {$db_prefix}universe WHERE sector_id=$sector_type", 1);
			db_op_result($sector_res,__LINE__,__FILE__);
			$base_x = $sector_res->fields['x'];
			$base_y = $sector_res->fields['y'];
			$base_z = $sector_res->fields['z'];
		}

		$cargototal = 0;

		$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where cargoport=1 order by defaultcargoplanet DESC, default_create_percent DESC");
		db_op_result($cargo_query,__LINE__,__FILE__);

		$default_create_ratio = 100 / $cargo_query->fields['default_create_percent'];
		$default_create_ratio_new = 1;

		while (!$cargo_query->EOF) 
		{
			$newcargotype[$cargototal] = $cargo_query->fields['classname'];
			$limitamount[$cargototal] = $cargo_query->fields['itemlimit'];
			$initialamount[$cargototal] = $cargo_query->fields['itemlimit'] * $_POST['initscommod'] / 100.0;
			$fixed_start_price[$cargototal] = $cargo_query->fields['fixed_start_price'];
			$increaserate[$cargototal] = $cargo_info['increaserate'];
			$goodevil[$cargototal] = $cargo_query->fields['goodevil'];
			$cargosellbuy[$cargototal] = $cargo_info['cargosellbuy'];
			$default_create_percent[$cargototal] = $cargo_info['default_create_percent'] * $default_create_ratio;
			if($cargo_info['defaultcargoplanet'] == 0 && $default_create_ratio_new == 1)
			{
				$default_create_ratio_new = 200 / $cargo_info['default_create_percent'];
			}
			$default_create_percent_new[$cargototal] = $cargo_info['default_create_percent'] * $default_create_ratio_new;
			$hold_space[$cargototal] = $cargo_info['hold_space'];
			$cargototal++;
			$cargo_query->Movenext();
		}

		$defaultcargototal = 0;
		$extracargototal = 0;

		$cargo_query = $db->SelectLimit("SELECT * from {$db_prefix}class_modules_commodities where defaultcargoplanet!=1 and cargoplanet=1 order by default_create_percent DESC", 1);
		db_op_result($cargo_query,__LINE__,__FILE__);

		$p_create_ratio = 100 / $cargo_query->fields['default_create_percent'];

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
					$p_default_indy_prod[$extracargototal] = $cargo_info['default_indy_prod'];
					$p_is_prod[$extracargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
					$p_goodevil[$extracargototal] = $cargo_info['goodevil'];
					$p_create_percent[$extracargototal] = $cargo_info['default_create_percent'] * $p_create_ratio;
					$extracargototal++;
				}
			}
			$cargo_query->Movenext();
		}
		$cargo_query->close();

		array_multisort($p_create_percent, $p_newcargotype, $p_cargoclass, $p_default_prod, $p_default_indy_prod, $p_is_prod, $p_goodevil);

		if($enable_spiral_galaxy != 1){
			// Lot of shortcuts here. Basically we generate a spherical coordinate and convert it to cartesian.
			// Why? Cause random spherical coordinates tend to be denser towards the center.
			// Should really be like a spiral arm galaxy but this'll do for now.
			$radius = mt_rand(100,$universe_size*100)/100;

			$temp_a = deg2rad(mt_rand(0,36000)/100-180);
			$temp_b = deg2rad(mt_rand(0,18000)/100-90);
			$temp_c = $radius*sin($temp_b);

			$sectorx = round(cos($temp_a)*$temp_c);
			$sectory = round(sin($temp_a)*$temp_c);
			$sectorz = round($radius*cos($temp_b));
			$sectorspiral_arm = 0;
		}
		else
		{
			//The Spiral Galaxy Code was proviced by "Kelly Shane Harrelson" <shane@mo-ware.com> 

			# calculate the scale to use such that 
			# the max distance between 2 points will be
			# approx $universe_size.
			$scale = ($universe_size / 10) / (4.0*pi());

			# compute the angle between arms
			$angle = deg2rad(360/$spiral_galaxy_arms);

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

//			if($sector_type == 0)
//			{
//				$sectorx = $base_x;
//				$sectory = $base_y;
//			}
//			else
//			{
				$sectorx = $x + $base_x;
				$sectory = $y + $base_y;
//			}
			$sectorz = $z + $base_z;
			$sectorspiral_arm = $arm;
		}

		$stamp = date("Y-m-d H:i:s");
		// Build Sector
		$port_type= mt_rand(0,100);
		if ($port_type > 30){
			$port="none";
			$debug_query = $db->Execute ("insert into {$db_prefix}universe (zone_id ,star_size,port_type,x,y,z,beacon, sg_sector, creation_date, creator_id, spiral_arm, created_from)
			values
			(1,$random_star,'$port',$sectorx,$sectory,$sectorz,'', $gateway_sector, '$stamp', $playerinfo[player_id], $sectorspiral_arm, $shipinfo[sector_id]) ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$target_sector = $db->insert_id();
		}elseif ($port_type > 5){
			$random_port = mt_rand(5, $cargototal - 1);
			$port = $newcargotype[$random_port];

			if($cargosellbuy[$random_port] != 1)
			{
				$random_value = mt_rand(0, 100);
				if($random_value < $default_create_percent_new[$random_port])
				{
					$debug_query = $db->Execute ("insert into {$db_prefix}universe (zone_id ,star_size,port_type,x,y,z,beacon, sg_sector, creation_date, creator_id, spiral_arm, created_from)
					values
					(1,$random_star,'$port',$sectorx,$sectory,$sectorz,'', $gateway_sector, '$stamp', $playerinfo[player_id], $sectorspiral_arm, $shipinfo[sector_id]) ");
					db_op_result($debug_query,__LINE__,__FILE__);
					$target_sector = $db->insert_id();

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
								$insertlist .= ", ($target_sector, '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
								$maxcommodities--;
							}
						}
					}

					$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
						(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
						VALUES 
						($target_sector, '" . $newcargotype[$random_port] . "', $limitamount[$random_port], $prices, '" . date("Y-m-d H:i:s") . "', $goodevil[$random_port]) 
						$insertlist");
					db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
				}
				else
				{
					$random_port = mt_rand(0, $defaultcargototal - 1);
					$port = $dnewcargotype[$random_port];

					$debug_query = $db->Execute ("insert into {$db_prefix}universe (zone_id ,star_size,port_type,x,y,z,beacon, sg_sector, creation_date, creator_id, spiral_arm, created_from)
					values
					(1,$random_star,'$port',$sectorx,$sectory,$sectorz,'', $gateway_sector, '$stamp', $playerinfo[player_id], $sectorspiral_arm, $shipinfo[sector_id]) ");
					db_op_result($debug_query,__LINE__,__FILE__);
					$target_sector = $db->insert_id();

					$randompoint = mt_rand(500000, 1000000) / 1000000;
					$prices = floor($dfixed_start_price[$random_port] * $randompoint);
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
								$insertlist .= ", ($target_sector, '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
								$maxcommodities--;
							}
						}
					}

					$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
						(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
						VALUES 
						($target_sector, '" . $dnewcargotype[$random_port] . "', $dlimitamount[$random_port], $prices, '" . date("Y-m-d H:i:s") . "', $dgoodevil[$random_port]) 
						$insertlist");
					db_op_result($debug_query,__LINE__,__FILE__);
				}
			}
			else
			{
				$random_port = mt_rand(0, $defaultcargototal - 1);
				$port = $dnewcargotype[$random_port];

				$debug_query = $db->Execute ("insert into {$db_prefix}universe (zone_id ,star_size,port_type,x,y,z,beacon, sg_sector, creation_date, creator_id, spiral_arm, created_from)
				values
				(1,$random_star,'$port',$sectorx,$sectory,$sectorz,'', $gateway_sector, '$stamp', $playerinfo[player_id], $sectorspiral_arm, $shipinfo[sector_id]) ");
				db_op_result($debug_query,__LINE__,__FILE__);
				$target_sector = $db->insert_id();

				$randompoint = mt_rand(500000, 1000000) / 1000000;
				$prices = floor($dfixed_start_price[$random_port] * $randompoint);
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
							$insertlist .= ", ($target_sector, '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
							$maxcommodities--;
						}
					}
				}

				$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
					(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
					VALUES 
					($target_sector, '" . $dnewcargotype[$random_port] . "', $dlimitamount[$random_port], $prices, '" . date("Y-m-d H:i:s") . "', $dgoodevil[$random_port]) 
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
			$debug_query = $db->Execute ("insert into {$db_prefix}universe (zone_id ,star_size,port_type,x,y,z,beacon, sg_sector, creation_date, creator_id, spiral_arm, created_from)
			values
			(1,$random_star,'$port',$sectorx,$sectory,$sectorz,'', $gateway_sector, '$stamp', $playerinfo[player_id], $sectorspiral_arm, $shipinfo[sector_id]) ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$target_sector = $db->insert_id();
		}

		$newsectorname = create_sector_number(chr(80 + $sectorspiral_arm) . (string)$random_star);

		$sectorname = trim(urldecode($sectorname));
       
		if(empty($sectorname) || !isset($sectorname) || AAT_strlen(trim($sectorname)) < 6)
		{
			$sectorname = $newsectorname;
		}
		else
		{
			$sector_check = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sectorname), 1);
			db_op_result($sector_check,__LINE__,__FILE__);

			if($sector_check->RecordCount())
			{
				$sectorname = $newsectorname;
			}
		}

		$debug_query = $db->Execute ("UPDATE {$db_prefix}universe SET sector_name=" . $db->qstr($sectorname) . " WHERE sector_id=$target_sector");
		db_op_result($debug_query,__LINE__,__FILE__);

		for($star = 0; $star < $random_star; $star++)
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

				if(mt_rand(0, 100) < 10 && $extracargototal != 0)
				{
					$specialcargo = mt_rand(0, 10000);
					for($checkcargo = $extracargototal - 1; $checkcargo >= 0; $checkcargo--)
					{
						if($specialcargo < floor($p_create_percent[$checkcargo] * 100))
						{
							$special_cargo = $p_newcargotype[$checkcargo];
							$special_goodevil = $p_goodevil[$checkcargo];
						}
					}
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
				$creation_date = date("Y-m-d H:i:s");
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}planets 
				(sector_id, max_credits, prod_fighters, prod_torp, special_name, special_goodevil, organics_planet, ore_planet, goods_planet, energy_planet, use_age, creation_date, creator_id" . $insertlist . ") 
				VALUES 
				('$target_sector', '$base_credits', '$default_prod_fighters', '$default_prod_torp', '$special_cargo', '$special_goodevil', '$organics_planet', '$ore_planet', '$goods_planet', '$energy_planet', '$new_age', '$creation_date', $playerinfo[player_id]" . $insertlistprod . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}

		// Build warp link
		$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links SET link_start=$target_sector, " .
									 "link_dest=$shipinfo[sector_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links SET link_start=$shipinfo[sector_id], link_dest=$target_sector");

		$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_sectorgenesis']['device_id']);
		db_op_result($debug_query,__LINE__,__FILE__);

		$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, " .
									 "turns_used=turns_used+1, credits=credits-$sgcost WHERE player_id=$playerinfo[player_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$template_object->assign("error_msg", str_replace("[name]", $sectorname, $l_sgns_pcreate));
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."sectorgenesisdie.tpl");
		include ("footer.php");
		die();
	}else{
		$template_object->assign("error_msg", str_replace("[limit]", "<font color=#00ff00><b>$max_sglinks</b></font>", $l_sgns_forbid2));
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."sectorgenesisdie.tpl");
		include ("footer.php");
		die();
	}
}else{
	$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
	$sector_type = $sector_res->fields['sg_sector'];
	if(($sector_type != 0)and ($rslink==1)){

		$res = $db->Execute("SELECT * from {$db_prefix}links where  link_start=$shipinfo[sector_id] ");
		$tlinks = $res->RecordCount();
		$res1 = $db->SelectLimit("SELECT * from {$db_prefix}universe where sector_name =" . $db->qstr($target_sector), 1);
		db_op_result($res1,__LINE__,__FILE__);

		if($res1->recordcount() == 0){
			$template_object->assign("error_msg", $l_sgns_forbid1);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."sectorgenesisdie.tpl");
			include ("footer.php");
			die();
		}

		$row1 = $res1->fields;
        $target_sector_id=$row1['sector_id'];

        $sector_type=0;
		$res = $db->Execute("SELECT u.sg_sector, l.* from {$db_prefix}universe u, {$db_prefix}links l where u.sector_id=$target_sector_id and l.link_start=$target_sector_id and u.sg_sector > 0");
		db_op_result($res,__LINE__,__FILE__);
		$destlinks = $res->RecordCount();
		if (($tlinks < $max_sglinks) and ($destlinks < $max_sglinks) and ($row1['zone_id'] !=2) and ($sector_type == 0) and ($sector_res->recordcount() != 0)){
			
		// Build warp link
			$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links (link_start,link_dest) values ($target_sector_id ,$shipinfo[sector_id]) ");
			
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links (link_start,link_dest) values ($shipinfo[sector_id],$target_sector_id)");

			$debug_query = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=amount-1 WHERE device_id=" . $shipdevice['dev_sectorgenesis']['device_id']);
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute ("UPDATE {$db_prefix}players SET turns=turns-1, " .
										 "turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$template_object->assign("error_msg", $l_sgns_complete);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."sectorgenesisdie.tpl");
			include ("footer.php");
			die();
		}elseif($row1['zone_id'] == 2 || $sector_res->recordcount() == 0){
			$template_object->assign("error_msg", $l_sgns_forbid1);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."sectorgenesisdie.tpl");
			include ("footer.php");
			die();
		}else{
			$template_object->assign("error_msg", str_replace("[limit]", "<font color=#00ff00><b>$max_sglinks</b></font>", $l_sgns_forbid2));
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."sectorgenesisdie.tpl");
			include ("footer.php");
			die();
		}
	}else{
		if($sgcost != 0){
			$sector_res = $db->SelectLimit("SELECT sg_sector FROM {$db_prefix}universe WHERE sector_id=$shipinfo[sector_id]", 1);
			$sector_type = $sector_res->fields['sg_sector'];
			$template_object->assign("sector_type", $sector_type);
			$template_object->assign("l_sgns_shipcredits", $l_sgns_shipcredits);
			$template_object->assign("credits", NUMBER($playerinfo['credits']));
			$template_object->assign("l_sgns_createcost", $l_sgns_createcost);
			$template_object->assign("sgcostnumber", NUMBER($sgcost));
			$template_object->assign("sgcost", $sgcost);
			$template_object->assign("l_sgcreate", $l_sgcreate);
			$template_object->assign("l_submit", $l_submit);
			$template_object->assign("l_reset", $l_reset);
			$template_object->assign("sector_max", $sector_max);
			$template_object->assign("shipsector", $shipinfo['sector_id']);
			$template_object->assign("l_sgcreatens", $l_sgcreatens);
			$template_object->assign("l_sgns_sectorname", $l_sgns_sectorname);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."sectorgenesis.tpl");
			include ("footer.php");
			die();
		}else{
			$template_object->assign("error_msg", str_replace("[limit]", "<font color=#00ff00><b>$max_sglinks</b></font>", $l_sgns_forbid2));
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."sectorgenesisdie.tpl");
			include ("footer.php");
			die();
		}
	}
}

close_database();
?>
