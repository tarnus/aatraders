<?php
// Step 100 - Create Earth, default NPC players, unowned planets and independent planets

include ("globals/calc_ownership.inc");
include ("globals/myrand.inc");
include ("globals/newplayer.inc");
include ("globals/ord_crypt_encode.inc");

$max_credits = ((phpMaxCreditsDelta((90 * ($max_tech_level / 54)), 0) * 7) * $planet_credit_multi) + $base_credits;
$max_levels = round(90 * ($max_tech_level / 54));
TextFlush("Inserting Federation homeworld: Earth "); //Fed homeworld - Earth
$debug_query = $db->Execute("INSERT INTO {$db_prefix}planets 
				(planet_id, 
				sector_id, 
				name, 
				credits,
				fighter,
				sensors,
				beams,
				torp_launchers,
				torps,
				shields,
				jammer,
				armor,
				armor_pts,
				cloak,
				fighters,
				owner,
				team,
				base,
				team_cash,
				defeated,
				prod_fighters,
				prod_torp,
				prod_organics,
				cargo_power,
				cargo_hull,
				fighter_normal,
				sensors_normal,
				beams_normal,
				torp_launchers_normal,
				shields_normal,
				jammer_normal,
				armor_normal,
				cloak_normal,
				max_credits,
				colonists
				)
				VALUES (" .
				"'1', " .				//planet_id
				"'1', " .				//sector_id
				"'Earth', " .			//name
				"'0', " .				//credits
				"'" . $max_levels . "', " .				//fighter
				"'" . $max_levels . "', " .				//sensors
				"'" . $max_levels . "', " .				//beams
				"'" . $max_levels . "', " .				//torp_launchers
				"'10000000', " .				//torps
				"'" . $max_levels . "', " .				//shields
				"'" . $max_levels . "', " .				//jammer
				"'" . $max_levels . "', " .				//armor
				"'10000000', " .				//armor_pts
				"'0', " .				//cloak
				"'10000000', " .				//fighters
				"'3', " .				//owner
				"'0', " .				//team
				"'Y', " .				//base
				"'Y', " .				//team cash
				"'N', " .				//defeated
				"'25', " .				//prod_fighters
				"'25', " .				//prod_torp
				"'25', " .				//prod_organics
				"'0','0', " .				//cargo stuff
				"'" . $max_levels . "', " .				//fighter
				"'" . $max_levels . "', " .				//sensors
				"'" . $max_levels . "', " .				//beams
				"'" . $max_levels . "', " .				//torp_launchers
				"'" . $max_levels . "', " .				//shields
				"'" . $max_levels . "', " .				//jammer
				"'" . $max_levels . "', " .				//armor
				"'0', " .				//cloak
				"'$max_credits', 100000000000 " .				//max_credits
				")");
db_op_result($debug_query,__LINE__,__FILE__);

$defaultcargototal = 0;
$extracargototal = 0;

$cargo_query = $db->SelectLimit("SELECT * from {$db_prefix}class_modules_commodities where defaultcargoplanet!=1 and cargoplanet=1 order by default_create_percent DESC", 1);
db_op_result($cargo_query,__LINE__,__FILE__);

$p_create_ratio = 100 / $cargo_query->fields['default_create_percent'];

$newcargotype = array();
$cargoclass = array();
$default_prod = array();
$default_indy_prod = array();
$is_prod = array();
$goodevil = array();
$p_create_percent = array();

$cargo_query = $db->Execute("SELECT default_create_percent, classname, cargoclass, default_prod, default_indy_prod, goodevil, defaultcargoplanet, cargoplanet from {$db_prefix}class_modules_commodities where defaultcargoplanet=1 or cargoplanet=1");
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
		$dis_prod[$defaultcargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
		$dgoodevil[$defaultcargototal] = $cargo_info['goodevil'];
		$defaultcargototal++;
	}
	else
	{
		if($cargo_info['cargoplanet'] == 1)
		{
			$newcargotype[$extracargototal] = $cargo_info['classname'];
			$cargoclass[$extracargototal] = $cargo_info['cargoclass'];
			$default_prod[$extracargototal] = $cargo_info['default_prod'];
			$default_indy_prod[$extracargototal] = $cargo_info['default_indy_prod'];
			$is_prod[$extracargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
			$goodevil[$extracargototal] = $cargo_info['goodevil'];
			$p_create_percent[$extracargototal] = $cargo_info['default_create_percent'] * $p_create_ratio;
			$extracargototal++;
		}
	}
	$cargo_query->Movenext();
}
$cargo_query->close();

$success = array_multisort($p_create_percent, $newcargotype, $cargoclass, $default_prod, $default_indy_prod, $is_prod, $goodevil);

TextFlush("Creating $_POST[nump] planets <br>");

while ($_POST['nump'] >0)
{
	$random_sector = mt_rand(2, $_POST['sektors']);
	$planetary_sector = $db->Execute("SELECT {$db_prefix}universe.sector_id, {$db_prefix}universe.star_size, ".
										"{$db_prefix}universe.zone_id, {$db_prefix}zones.allow_planet ".
										"FROM {$db_prefix}universe, {$db_prefix}zones ".
										"WHERE {$db_prefix}universe.sector_id='$random_sector' AND ".
										"{$db_prefix}zones.allow_planet='Y' AND {$db_prefix}universe.zone_id!='2' AND {$db_prefix}universe.zone_id!='3' AND ".
										"{$db_prefix}universe.star_size!='0' LIMIT 1");
	$silent=1;
	db_op_result($planetary_sector,__LINE__,__FILE__);
	if (!$planetary_sector->EOF)
	{
		$debug_query = $db->Execute("SELECT COUNT(planet_id) AS total from {$db_prefix}planets where sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);

		$num_planets_in_sector = $debug_query->fields['total'];
		$debug_query->close();
		$num_ok_planets = $planetary_sector->fields['star_size'] - $num_planets_in_sector;

		if ($num_ok_planets > $_POST['nump'])
		{
			$num_ok_planets = $_POST['nump'];
		}

		if ($num_ok_planets > 0)
		{
			$random_num_planets = mt_rand(0, $num_ok_planets);

			while ($random_num_planets > 0)
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
//					echo "adding special cargo: ";
					$specialcargo = mt_rand(0, 10000);
					for($checkcargo = $extracargototal - 1; $checkcargo >= 0; $checkcargo--)
					{
						if($specialcargo < floor($p_create_percent[$checkcargo] * 100))
						{
//							echo $specialcargo . " < " . floor($p_create_percent[$checkcargo] * 100) . " : " . $newcargotype[$checkcargo] . "<br>";
							$special_cargo = $newcargotype[$checkcargo];
							$special_goodevil = $goodevil[$checkcargo];
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
				(sector_id, max_credits, prod_fighters, prod_torp, special_name, special_goodevil, organics_planet, ore_planet, goods_planet, energy_planet, use_age, creation_date" . $insertlist . ") 
				VALUES 
				('$random_sector', '$base_credits', '$default_prod_fighters', '$default_prod_torp', '$special_cargo', '$special_goodevil', '$organics_planet', '$ore_planet', '$goods_planet', '$energy_planet', '$new_age', '$creation_date'" . $insertlistprod . ")");
				db_op_result($debug_query,__LINE__,__FILE__);

				if ($_POST['nump'] > 1)
				{
					$silent = 1;
				}
				else
				{
					$silent = 0;
				}

				db_op_result($debug_query,__LINE__,__FILE__);
				$_POST['nump']--;
				$random_num_planets--;
			}
		}
	}
	$planetary_sector->close();
}

$password = AAT_substr($adminpass, 0, $maxlen_password);
$silent = 1;

echo "<B><BR>Configuring ship types<p></B>";

if(!is_file("support/shiptypes_" . str_replace("setup_", "", $setup_file)))
{
	$setup_file = "setup_default";
}

$shipdata = file("support/shiptypes_" . str_replace("setup_", "", $setup_file));

for($i = 0; $i < count($shipdata); $i += 35){
	$fields = "";
	$fielddata = "";
	for($element = 0; $element < 34; $element++){
		$variable = explode("=", $shipdata[$i + $element], 2);
		$variable[0] = trim($variable[0]);
		$variable[1] = trim($variable[1]);
		$$variable[0] = $variable[1];
		$fields .= $variable[0];
		$fielddata .= $variable[1];
		if($element != 33){
			$fields .= ", ";
			$fielddata .= ", ";
		}
		if($variable[0] == "type_id"){
			$shipclass = $variable[1];
		}
		if($variable[0] == "maxhull"){
			$shipmax = $variable[1];
		}
//		echo $variable[0] . " = " . $variable[1] . "<br>";
	}
//	echo "<br>";

	echo "Inserting ship type: $name ";
	$silent = 0;
	$server_query = $db->Execute("INSERT INTO {$db_prefix}ship_types ($fields) VALUES ($fielddata)");
	db_op_result($server_query,__LINE__,__FILE__);
	$silent = 1;

	if($shipclass == 99)
	{
		$alliance_query = "UPDATE {$db_prefix}ships SET class='99', basehull='$shipmax', hull=$shipmax, engines=$shipmax, power=$shipmax, fighter=$shipmax,
					sensors=$shipmax, beams=$shipmax, armor=$shipmax, cloak=0, torp_launchers=$shipmax, shields=$shipmax, ecm=$shipmax,
					hull_normal=$shipmax, engines_normal=$shipmax, power_normal=$shipmax, fighter_normal=$shipmax, ecm_normal=$shipmax,
					sensors_normal=$shipmax, beams_normal=$shipmax, armor_normal=$shipmax, cloak_normal=0, torp_launchers_normal=$shipmax, shields_normal=$shipmax, fighters='21202551848303',
					torps='21202551848303', armor_pts='21202551848303', energy='106012759241513' WHERE ship_id='1'";
	}

	if($shipclass == 100)
	{
		$federation_query = "UPDATE {$db_prefix}ships SET class='100', basehull='$shipmax', hull='$shipmax', engines=$shipmax, power=$shipmax, fighter=$shipmax,
						sensors=$shipmax, beams=$shipmax, armor=$shipmax, cloak=0, torp_launchers=$shipmax, shields=$shipmax, ecm=$shipmax,
						hull_normal=$shipmax, engines_normal=$shipmax, power_normal=$shipmax, fighter_normal=$shipmax, ecm_normal=$shipmax,
						sensors_normal=$shipmax, beams_normal=$shipmax, armor_normal=$shipmax, cloak_normal=0, torp_launchers_normal=$shipmax, shields_normal=$shipmax, 
						fighters='70503928228430688',
						torps='70503928228430688', armor_pts='70503928228430688', energy='352519641142153472' WHERE ship_id='3'";
	}

	if($shipclass == 80)
	{
		$independent_query = "UPDATE {$db_prefix}ships SET class='80', basehull='$shipmax', hull=$shipmax * 1.25, engines=$shipmax * 1.25, power=$shipmax * 1.25, fighter=$shipmax * 1.25,
						sensors=$shipmax * 1.25, beams=$shipmax * 1.25, armor=$shipmax * 1.25, cloak=0, torp_launchers=$shipmax * 1.25, shields=$shipmax, ecm=$shipmax * 1.25,
						hull_normal=$shipmax * 1.25, engines_normal=$shipmax * 1.25, power_normal=$shipmax * 1.25, fighter_normal=$shipmax, ecm_normal=$shipmax * 1.25,
						sensors_normal=$shipmax * 1.25, beams_normal=$shipmax * 1.25, armor_normal=$shipmax * 1.25, cloak_normal=0, torp_launchers_normal=$shipmax * 1.25, shields_normal=$shipmax * 1.25, 
						fighters='503928228430688',
						torps='503928228430688', armor_pts='503928228430688', energy='2519641142153472' WHERE ship_id='2'";
	}
}

echo "<BR>Creating Alliance Leader Player";
$max_levels = round(70 * ($max_tech_level / 54));
newplayer('Alliance Leader', 'Alliance Leader', ord_crypt_encode($alliance_password), "Bane of the Federation", $max_levels, 1, 1);
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET avatar='alliance.jpg' WHERE player_id=1");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("$alliance_query");
db_op_result($debug_query,__LINE__,__FILE__);

echo "<BR>Creating Independent Player ";
newplayer('Independent', 'Independent', ord_crypt_encode($independent_password), "Independent", 0, 2, 1);
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET avatar='independent.jpg' WHERE player_id=2");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("$independent_query");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("INSERT INTO {$db_prefix}zones (zone_name, ".
							"owner, team_zone, allow_attack, ".
							"allow_planetattack, allow_warpedit, ".
							"allow_planet, allow_trade, allow_defenses, ".
							"max_hull, zone_color) VALUES(" .
//							"''," .			 //zone_id		-	not needed
							"'Independent Territory'," .	//zone_name
							"'2'," .	 //owner
							"'N'," .			//team_zone
							"'Y'," .			//allow_attack
							"'Y'," .			//allow_planetattack
							"'Y'," .			//allow_warpedit
							"'Y'," .			//allow_planet
							"'Y'," .			//allow_trade
							"'L'," .			//allow_defenses
							"'0'," .				//max_hull
							"'#ff00ff'" .				//indy color
							")");
db_op_result($debug_query,__LINE__,__FILE__);

echo "<BR>Creating Federation Player <BR></B></center>";
$max_levels = round(90 * ($max_tech_level / 54));
newplayer('Federation', 'Federation', ord_crypt_encode($federation_password), "Federation", $max_levels, 3, 1);
$debug_query = $db->Execute("UPDATE {$db_prefix}players SET avatar='federation.jpg' WHERE player_id=3");
db_op_result($debug_query,__LINE__,__FILE__);

$debug_query = $db->Execute("$federation_query");
db_op_result($debug_query,__LINE__,__FILE__);

$silent = 0;

$Sylable1 = array("Ak","Al","Ar","B","Br","D","F","Fr","G","Gr","K","Kr","N","Ol","Om","P","Qu","R","S","Z","Ah","At","As","Bh","Bl","Dh","Fl","Fh","Gh","Gl","Kl","Ks","Nr","Oh","Ok","Pu","Qh","Rl","Ss","Zl","C","Cr","Ch","Cl","E","El","Er","H","I","J","L","M","T","Tl","Th","U","Ur","V","Vl","W","Wl","Wr","X","Y");
$Sylable2 = array("a","ar","aka","aza","e","el","i","in","int","ili","ish","ido","ir","o","oi","or","os","ov","u","un");
$Sylable3 = array("ag","al","ak","ba","dar","g","ga","k","ka","kar","kil","l","n","nt","ol","r","s","ta","til","x");
$Sylable4 = array("a","ar","aka","aza","e","el","i","in","int","ili","ish","ido","ir","o","oi","or","os","ov","u","un");

TextFlush("<br>Creating $_POST[numbp] based and independant planets <br>");
$silent = 1;
while ($_POST['numbp'] >0)
{
	$random_sector = mt_rand(2, $_POST['sektors']);
	$planetary_sector = $db->Execute("SELECT {$db_prefix}universe.sector_id, {$db_prefix}universe.star_size, ".
										"{$db_prefix}universe.zone_id, {$db_prefix}zones.allow_planet ".
										"FROM {$db_prefix}universe, {$db_prefix}zones ".
										"WHERE {$db_prefix}universe.sector_id='$random_sector' AND ".
										"{$db_prefix}zones.allow_planet='Y' AND {$db_prefix}universe.zone_id!='2' AND {$db_prefix}universe.zone_id!='3' AND ".
										"{$db_prefix}universe.star_size!='0' LIMIT 1");
	$silent=1;
	db_op_result($planetary_sector,__LINE__,__FILE__);
	if (!$planetary_sector->EOF)
	{
		$debug_query = $db->Execute("SELECT COUNT(planet_id) AS total from {$db_prefix}planets where sector_id='$random_sector'");
		db_op_result($debug_query,__LINE__,__FILE__);

		$num_planets_in_sector = $debug_query->fields['total'];
		$debug_query->close();
		$num_ok_planets = $planetary_sector->fields['star_size'] - $num_planets_in_sector;

		if ($num_ok_planets > $_POST['numbp'])
		{
			$num_ok_planets = $_POST['numbp'];
		}

		if ($num_ok_planets > 0)
		{
			$random_num_planets = mt_rand(0, $num_ok_planets);

			while ($random_num_planets > 0)
			{
				// Create Planet Name
				$sy1roll = mt_rand(0,63);
				$sy2roll = mt_rand(0,19);
				$sy3roll = mt_rand(0,19);
				$sy4roll = mt_rand(0,19);

				$name = $Sylable1[$sy1roll] . $Sylable2[$sy2roll] . $Sylable3[$sy3roll] . $Sylable4[$sy4roll];

				$fighter = mt_rand($minbasedlevel, $maxbasedlevel);
				$sensors = mt_rand($minbasedlevel, $maxbasedlevel);
				$beams = mt_rand($minbasedlevel, $maxbasedlevel);
				$torp_launchers = mt_rand($minbasedlevel, $maxbasedlevel);
				$shields = mt_rand($minbasedlevel, $maxbasedlevel);
				$jammer = mt_rand($minbasedlevel, $maxbasedlevel);
				$cloak = mt_rand($minbasedlevel, $maxbasedlevel);
				$sd_weapons = mt_rand($minbasedlevel, $maxbasedlevel);
				$sd_sensors = mt_rand($minbasedlevel, $maxbasedlevel);
				$sd_cloak = mt_rand($minbasedlevel, $maxbasedlevel);

				$torps = NUM_TORPEDOES($torp_launchers) + mt_rand(1, NUM_TORPEDOES($torp_launchers));
				$fighters = NUM_FIGHTERS($fighter) + mt_rand(1, NUM_FIGHTERS($fighter));
				$armor_pts = NUM_armor(floor(($fighter + $sensors + $beams + $torp_launchers + $shields + $jammer + $cloak) / 7));
				$armor = floor(($fighter + $sensors + $beams + $torp_launchers + $shields + $jammer + $cloak) / 7);

				$max_credits = phpMaxCreditsDelta($fighter, 0) + phpMaxCreditsDelta($sensors, 0) + phpMaxCreditsDelta($beams, 0) + phpMaxCreditsDelta($torp_launchers, 0) + phpMaxCreditsDelta($shields, 0) + phpMaxCreditsDelta($jammer, 0) + phpMaxCreditsDelta($cloak, 0);
				$base_credits = ($max_credits * $planet_credit_multi) + $base_credits;

				$amount = floor((($basedcolonists/100) * $colonist_limit) * 0.75);

				$insertlist = "";
				$insertlistprod = "";
				for($ii = 0; $ii < $defaultcargototal; $ii++)
				{
					if($ddefault_indy_prod[$ii] > 0)
					{
						$insertlist .= ", prod_" . $dnewcargotype[$ii];
						$insertlistprod .= ", '$ddefault_indy_prod[$ii]'";
					}
				}
				$energystart = NUM_BEAMS($beams) + NUM_SHIELDS($shields) + mt_rand(1, NUM_BEAMS($beams) + NUM_SHIELDS($shields));

				$specialcargo = mt_rand(0, $extracargototal - 1);
				if(mt_rand(0, 100) < 10 && $extracargototal != 0)
				{
					$special_cargo = $newcargotype[$specialcargo];
					$special_goodevil = $goodevil[$specialcargo];
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

				$debug_query = $db->Execute("INSERT INTO {$db_prefix}planets 
				(sector_id, max_credits, prod_fighters, prod_torp, name, owner, base, fighter, fighter_normal,
				sensors, sensors_normal, beams, beams_normal, torp_launchers, torp_launchers_normal,
				shields, shields_normal, jammer, jammer_normal, cloak, cloak_normal, torps, fighters, armor_pts, armor, colonists, special_name, special_goodevil, organics_planet, ore_planet, goods_planet, energy_planet,
				sector_defense_weapons, sector_defense_weapons_normal, sector_defense_sensors, sector_defense_sensors_normal,
				sector_defense_cloak, sector_defense_cloak_normal " . $insertlist . ",  energy) 
				VALUES 
				('$random_sector', '$base_credits', '$default_prod_fighters', '$default_prod_torp', '$name', '2', 'Y', '$fighter', '$fighter', 
				'$sensors', '$sensors', '$beams', '$beams', '$torp_launchers', '$torp_launchers',
				'$shields', '$shields', '$jammer', '$jammer', '$cloak', '$cloak', '$torps', '$fighters', '$armor_pts', '$armor', '$amount', '$special_cargo', '$special_goodevil', '$organics_planet', '$ore_planet', '$goods_planet', '$energy_planet',
				'$sd_weapons', '$sd_weapons', '$sd_sensors', '$sd_sensors', '$sd_cloak', '$sd_cloak' " . $insertlistprod . ", '$energystart')");
				db_op_result($debug_query,__LINE__,__FILE__);
				$planet_id = $db->insert_id();

				$amount = 0;
				$record["colonists"] = floor((($basedcolonists/100) * $colonist_limit) * 0.75);

				if(mt_rand(1, 10000) < 5000){
					$fighter_query = $db->Execute ("SELECT defense_id FROM {$db_prefix}sector_defense WHERE sector_id='$random_sector' and defense_type='fighters'");
					$fighter_id = $fighter_query->fields['defense_id'];

					$numfighters = mt_rand(1, NUM_FIGHTERS($record["sector_defense_weapons"]));
					if ($fighter_id > 0)
					{
						$fighter_query->close();
						$fighter_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $numfighters " .
													"where defense_id = '$fighter_id'");
						db_op_result($fighter_query,__LINE__,__FILE__);
					}
					else
					{
						$fighter_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
													"(player_id, sector_id, defense_type, quantity, weapon_class) values " .
													"('2', '$random_sector', 'fighters', '$numfighters', 'Sector_Fighter')");
						db_op_result($fighter_query,__LINE__,__FILE__);
					}

					if(mt_rand(1, 10000) < 5000){
						$mine_query = $db->Execute ("SELECT defense_id FROM {$db_prefix}sector_defense WHERE sector_id='$random_sector' and defense_type = 'mines'");
						$mine_id = $mine_query->fields['defense_id'];

						$nummines = mt_rand(1, NUM_TORPEDOES($record["sector_defense_weapons"]));
						if ($mine_id > 0)
						{
							$mine_query->close();
							$mine_query = $db->Execute("UPDATE {$db_prefix}sector_defense set quantity=quantity + $nummines " .
														"where defense_id = '$mine_id'");
							db_op_result($mine_query,__LINE__,__FILE__);
						}
						else
						{
							$mine_query = $db->Execute("INSERT INTO {$db_prefix}sector_defense " .
														"(player_id,sector_id,defense_type,quantity, weapon_class) values " .
														"('2', '$random_sector', 'mines', '$nummines', 'Sector_Mine')");
							db_op_result($mine_query,__LINE__,__FILE__);
						}
					}
				}

				$stamp = "2100-01-01 10:00:00";
				$embezzel_delay = "2200-01-01 10:00:00";
				$new_percet = (mt_rand(1, 100) / 100) * $dig_birthinc_max;
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}dignitary (dig_id, active, owner_id, planet_id, ship_id, job_id, percent, active_date, reactive_date) values ('','Y','2','$planet_id','2','4','$new_percet', '$stamp', '$embezzel_delay')");
				db_op_result($debug_query,__LINE__,__FILE__);
				calc_ownership($random_sector);

				if ($_POST['numbp'] > 1)
				{
					$silent = 1;
				}
				else
				{
					$silent = 0;
				}

				db_op_result($debug_query,__LINE__,__FILE__);
				$_POST['numbp']--;
				$random_num_planets--;
			}
		}
	}
}

echo "<input type=hidden name=step value=100>";

?>