<?php
// Step 30 - build player profile data from closed game and send to profile server, delete databases, rebuild databases and import config, language and wordcensor data to databases
include ("globals/good_neutral_evil.inc");
include ("globals/RecurseDir.inc");

include ("create_game/schema.inc");

$install_error = 0;

function ini_to_db ($ini_file, $ini_table, $config = 1)
{
	global $db_prefix, $db, $silent, $l_cu_inistored, $l_cu_storing, $l_cu_iniissue, $l_cu_inierror;

	$silent = 0;
	$cumulative = 0;												
	TextFlush("<b>Storing values in the database [$ini_table]: </b><br>\n");

	// No need to see the debug from the select and the sql generation.
	$silent = 1;
	$sql = "SELECT * FROM $ini_table WHERE id = -1";

	// Execute the query and get the empty recordset
	$debug_query_rs = $db->Execute($sql);
	if (!$db->ErrorMsg)
	{
		db_op_result($debug_query_rs,__LINE__,__FILE__);
		$lines = file ($ini_file);

		// This is a loop, that reads a config.ini file, of the type variable = value.
		// It will loop thru the list of the config.ini variables, and push them into the db
		// along with the description of the variable.
		for($i = 0; $i < count($lines); $i++){

			if(AAT_substr($lines[$i], 0, 1) == "[")
				$section = str_replace("[", "", str_replace("]", "", $lines[$i]));

			$text = AAT_eregi('^[-!#$%&\'*+\\./0-9=?A-Z^_`{|}~]+', trim($lines[$i]));

			$items = explode(";", trim($lines[$i]));
			$variable = explode("=", $items[0]);
			$variable[0] = trim($variable[0]);
			$variable[1] = str_replace("\"", "", trim($variable[1]));

			if($text)
			{
				// Set the values for the fields in the record
				$silent = 0;
				TextFlush( $l_cu_storing . stripslashes($variable[0]) . " ");
				if($config == 1)
				{
					$debug_query_insert = $db->Execute("INSERT INTO $ini_table (name, value, description, section) VALUES ('$variable[0]', '$variable[1]', " . $db->qstr(trim($items[2])) . ", '" . trim($section) . "')");
					db_op_result($debug_query_insert,__LINE__,__FILE__);
				}
				else
				{
					$debug_query_insert = $db->Execute("INSERT INTO $ini_table (name, value) VALUES ('$variable[0]', '$variable[1]')");
					db_op_result($debug_query_insert,__LINE__,__FILE__);
				}
			}
		}

		if ($cumulative == 0)
		{
			TextFlush( $l_cu_inistored);
		}
		else
		{
			TextFlush( $l_cu_iniissue);
		}
	}
	else
	{
		TextFlush( $l_cu_inierror);
	}
}

function import_setup ($ini_file, $ini_table)
{
	global $db_prefix, $db, $silent, $l_cu_inistored, $l_cu_storing, $l_cu_iniissue, $l_cu_inierror;

	$silent = 0;
	$cumulative = 0;												
	TextFlush("<b>Storing values in the database [$ini_table]: </b><br>\n");

	// No need to see the debug from the select and the sql generation.
	$silent = 1;
	$sql = "SELECT * FROM $ini_table WHERE id = -1";

	// Execute the query and get the empty recordset
	$debug_query_rs = $db->Execute($sql);
	if (!$db->ErrorMsg)
	{
		db_op_result($debug_query_rs,__LINE__,__FILE__);
		$lines = file ($ini_file);

		// This is a loop, that reads a config.ini file, of the type variable = value.
		// It will loop thru the list of the config.ini variables, and push them into the db
		// along with the description of the variable.
		for($i = 0; $i < count($lines); $i++){

			if(AAT_substr($lines[$i], 0, 1) == "[")
				$section = str_replace("[", "", str_replace("]", "", $lines[$i]));

			$text = AAT_eregi('^[-!#$%&\'*+\\./0-9=?A-Z^_`{|}~]+', trim($lines[$i]));

			$items = array();
			$items = explode(";", trim($lines[$i]));
			$variable = explode("=", $items[0]);
			$variable[0] = trim($variable[0]);
			$variable[1] = str_replace("\"", "", trim($variable[1]));

			if($text)
			{
				// Set the values for the fields in the record
				$silent = 0;
				TextFlush( $l_cu_storing . stripslashes($variable[0]) . " ");
				$debug_query_insert = $db->Execute("INSERT INTO $ini_table (name, value, input_type, input_selections, description, section) VALUES ('$variable[0]', '$variable[1]', '" . trim($items[1]) . "', " . $db->qstr(trim($items[2])) . ", " . $db->qstr(trim($items[3])) . ", '" . trim($section) . "')");
				db_op_result($debug_query_insert,__LINE__,__FILE__);
			}
		}

		if ($cumulative == 0)
		{
			TextFlush( $l_cu_inistored);
		}
		else
		{
			TextFlush( $l_cu_iniissue);
		}
	}
	else
	{
		TextFlush( $l_cu_inierror);
	}
}

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

if($is_safe_mode)
	$max_sectors = 15000;
else
	$max_sectors = 50000;

$sektors = StripNonNum($sektors);

if($sektors < 100)
	$sektors = 100;

if($sektors > $max_sectors)
	$sektors = $max_sectors;

if($galaxies < 1)
	$galaxies = 1;

if($galaxies > 5)
	$galaxies = 5;

$lines = file ("support/$setup_file");
for($i = 0; $i < count($lines); $i++){

	$text = AAT_eregi('^[-!#$%&\'*+\\./0-9=?A-Z^_`{|}~]+', trim($lines[$i]));

	$items = explode(";", trim($lines[$i]));
	$variable = explode("=", $items[0]);
	$variable[0] = trim($variable[0]);
	$variable[1] = str_replace("\"", "", trim($variable[1]));

	if($text){
		$$variable[0] = $variable[1];
	}
}

$silent = 0;

// Create the new schema.
create_schema();

import_setup("support/$setup_file", "{$db_prefix}config_values");

if (!check_php_version ())
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0' WHERE name='enable_spiral_galaxy'");
	db_op_result($debug_query,__LINE__,__FILE__);
}

if (@ini_get("allow_url_fopen") != 1 && function_exists('curl_init') != true)
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='0' WHERE name='enable_profilesupport'");
	db_op_result($debug_query,__LINE__,__FILE__);
}

if(extension_loaded("zlib"))
{
	if (get_cfg_var('zlib.output_compression'))
	{
		$setvalue = 0;
	}
	else
	{
		$setvalue = 1;
	}
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='$setvalue' WHERE name='enable_gzip'");
	db_op_result($debug_query,__LINE__,__FILE__);
}

ini_to_db("support/wordcensor.ini", "{$db_prefix}wordcensor", 0);

$thedate = date("Y-m-d");
$yr=strval(AAT_substr($thedate,0,4)); 
$mo=strval(AAT_substr($thedate,5,2)); 
$da=strval(AAT_substr($thedate,8,2));	

$resetdescription = "Date server scheduled to reset game";

if(($reset_month < $mo && $reset_year == $yr) || ($reset_month == $mo && $reset_year == $yr && $reset_day < $da)){
	$reset_year == "0000";
	$reset_month == "00";
	$reset_day == "00";
}

$scheduled_reset = $reset_year."-".$reset_month."-".$reset_day;
$debug_query = $db->Execute("INSERT INTO {$db_prefix}config_values (name,value, input_type, input_selections, description, section) VALUES ('scheduled_reset','$scheduled_reset', 'text', '', '$resetdescription', 'Reset Date')");
db_op_result($debug_query,__LINE__,__FILE__);

$tournamentstartdescription = "Date server will change from Tournament Setup Mode to Full Tournament Mode.";

if(($tournament_month < $mo && $tournament_year == $yr) || ($tournament_month == $mo && $tournament_year == $yr && $tournament_day < $da)){
	$tournament_year == "0000";
	$tournament_month == "00";
	$tournament_day == "00";
}

$tournament_start_date = $tournament_year."-".$tournament_month."-".$tournament_day;
$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='$tournament_start_date' WHERE name='tournament_start_date'");
db_op_result($debug_query,__LINE__,__FILE__);

if($tournament_start_date != "0000-00-00")
{
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='tournament_mode'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='tournament_setup_access'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='profile_only_server'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='240' WHERE name='player_online_timelimit'");
	db_op_result($debug_query,__LINE__,__FILE__);
	$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='1' WHERE name='enable_profilesupport'");
	db_op_result($debug_query,__LINE__,__FILE__);
}

$debris_max = max(50, floor($sektors/1000) * 100);
echo "Setting debris_max to ". $debris_max ."<br><br>";
$debug_query = $db->Execute("UPDATE {$db_prefix}config_values SET value='". $debris_max ."' WHERE name='debris_max'");
db_op_result($debug_query,__LINE__,__FILE__);

exportvariables();

function import_class_modules($class)
{
	global $db, $db_prefix, $silent;

	TextFlush("<br><b>Storing values in the database [class_modules_$class]: </b><br>\n");
	$silent = 0;
	$filelist = get_dirlist($gameroot."class/$class/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$cargoname =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($cargoname)){
				include ("class/$class/" . $cargoname . ".inc");
			}
			echo $cargoname;
			$cargoobject = new $cargoname();
			$classname = $cargoobject->classname;
			$cargoclass = $cargoobject->cargoclass;
			$upgradeport = $cargoobject->upgradeport;
			$deviceport = $cargoobject->deviceport;
			$cargoport = $cargoobject->cargoport;
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

			$enable = $debrisobject->enable;

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}class_modules_$class (program, class, classname, cargoclass, upgradeport,
			deviceport, cargoport, cargoplanet, defaultcargoplanet, defaultcargoship, 
			shipdevice, planetdevice, shipdevicemax, planetdevicemax, researchonly, 
			goodevil, price, delta, rate,
			reducerate, increaserate, itemlimit, prate, default_prod, default_indy_prod, fixed_start_price,
			damage_shields, damage_all, deflector_damage, hit_pts, price_modifier, energy_usage, researchcredits,
			researchore, researchorganics, researchgoods, researchenergy, researchticks, 
			buildcredits, buildore, buildorganics, buildgoods, buildenergy, buildticks, hold_space, 
			default_create_percent, enable) 
			VALUES 
			('$program', '$cargoname','$classname', '$cargoclass', '$upgradeport', 
			'$deviceport', '$cargoport', '$cargoplanet', '$defaultcargoplanet', '$defaultcargoship', 
			'$shipdevice', '$planetdevice', '$shipdevicemax', '$planetdevicemax', '$researchonly', 
			'$goodevil', '$price', '$delta', '$rate',
			'$reducerate', '$increaserate', '$itemlimit', '$prate', '$default_prod', '$default_indy_prod', '$fixed_start_price',
			'$damage_shields', '$damage_all', '$deflector_damage', '$hit_pts', '$price_modifier', '$energy_usage', '$researchcredits',
			'$researchore', '$researchorganics', '$researchgoods', '$researchenergy', '$researchticks',
			'$buildcredits', '$buildore', '$buildorganics', '$buildgoods', '$buildenergy', '$buildticks', '$hold_space',
			'$default_create_percent', '$enable')");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}
	$silent = 1;
	TextFlush( $l_cu_inistored . "<br>");
}

function import_commodity_modules($class)
{
	global $db, $db_prefix, $silent;

	TextFlush("<br><b>Storing values in the database [class_modules_$class]: </b><br>\n");
	$silent = 0;
	$filelist = get_dirlist($gameroot."class/$class/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$cargoname =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($cargoname)){
				include ("class/$class/" . $cargoname . ".inc");
			}
			echo $cargoname;
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

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}class_modules_$class (program, class, classname, cargoclass, upgradeport,
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
		}
	}
	$silent = 1;
	TextFlush( $l_cu_inistored . "<br>");
}

function import_debris_modules($class)
{
	global $db, $db_prefix, $silent;

	TextFlush("<br><b>Storing values in the database [class_modules_$class]: </b><br>\n");
	$silent = 0;
	$filelist = get_dirlist($gameroot."class/$class/");
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			$debrisname =  str_replace(".inc", "", $filelist[$c]); 
			if(!class_exists($debrisname)){
				include ("class/$class/" . $debrisname . ".inc");
			}
			echo $debrisname;
			$debrisobject = new $debrisname();
			$classname = $debrisobject->classname;
			$success = $debrisobject->success;
			$trigger = $debrisobject->trigger;
			$enable = $debrisobject->enable;
			$autoadd_debris = $debrisobject->autoadd_debris;
			$destroyship_debris = $debrisobject->destroyship_debris;

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}class_modules_$class (
			classname, success, trigger_value, enable, destroyship_debris, 
			autoadd_debris) 
			VALUES 
			('$classname', '$success','$trigger', '$enable', '$destroyship_debris', 
			'$autoadd_debris')");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}
	$silent = 1;
	TextFlush( $l_cu_inistored . "<br>");
}

TextFlush("<br><b>Building Log Data: </b><br>\n");

TextFlush( "Copying master log_switch_data.inc to support/log_data directory" );
@unlink($gameroot."support/log_data/log_switch_data.inc");
$file = @copy($gameroot."support/master_log_data/log_switch_data.inc", $gameroot."support/log_data/log_switch_data.inc");
if($file === false)
{
	TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
	$install_error = 1;
}
else
{
	TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
}

$dirlist=RecurseDir($gameroot."languages"); 
chdir($gameroot);

$language_array = array();
foreach ($dirlist as $key=>$val) { 
	$languagename = str_replace($gameroot."languages/", "", $val);
	$language_array[] = $languagename;
	TextFlush( "Copying master " . $languagename . " lang_log.inc to support/log_data/" . $languagename . " directory" );
	@mkdir($gameroot."support/log_data/" . $languagename);
	@unlink($gameroot."support/log_data/" . $languagename . "/lang_log.inc");
	$file = @copy($gameroot."languages/" . $languagename . "/lang_log.inc", $gameroot."support/log_data/" . $languagename . "/lang_log.inc");
	if($file === false)
	{
		TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
		$install_error = 1;
	}
	else
	{
		TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
	}
}

TextFlush("<br><b>Building Apocalypse Data: </b><br>\n");
$filelist = get_dirlist($gameroot."class/apocalypse/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$apocalypse_classname =  str_replace(".inc", "", $filelist[$c]); 
		TextFlush( "<br>\nLoading " . $apocalypse_classname . " class<br>\n" );
		if(!class_exists($apocalypse_classname)){
			include ("class/apocalypse/" . $apocalypse_classname . ".inc");
		}
		$apocalypse_object =  new $apocalypse_classname();

		$log_switch_data = $apocalypse_object->log_switch_data();
		TextFlush( "Adding " . $apocalypse_classname . " log switch data to support/log_data/log_switch_data.inc" );
		$file = @fopen($gameroot."support/log_data/log_switch_data.inc", "a");
		if($file === false)
		{
			TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
			$install_error = 1;
		}
		else
		{
			fwrite($file, $log_switch_data); 
			fclose($file);
			TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
		}

		$log_language_data = $apocalypse_object->log_language_data();
		foreach ($language_array as $languagename) { 
			TextFlush( "Adding " . $apocalypse_classname . " log language data to support/log_data/" . $languagename . "/lang_log.inc" );
			$file = @fopen($gameroot."support/log_data/" . $languagename . "/lang_log.inc", "a");
			if($file === false)
			{
				TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
				$install_error = 1;
			}
			else
			{
				if(!isset($log_language_data[$languagename]["title"]))
				{
					$l_log_title = $log_language_data["english"]["title"];
					$l_log_text = $log_language_data["english"]["text"];
				}
				else
				{
					$l_log_title = $log_language_data[$languagename]["title"];
					$l_log_text = $log_language_data[$languagename]["text"];
				}
				fwrite($file, "<?php\n\$l_log_title[\"" . $apocalypse_object->tag . "\"] = \"" . $l_log_title . "\";\n"); 
				fwrite($file, "\$l_log_text[\"" . $apocalypse_object->tag . "\"] = \"" . $l_log_text . "\";\n?>\n"); 
				fclose($file);
				TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
			}
		}
	}
}

TextFlush( "Closing support/log_data/log_switch_data.inc" );
$file = @fopen($gameroot."support/log_data/log_switch_data.inc", "a");
if($file === false)
{
	TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
	$install_error = 1;
}

TextFlush("<br><b>Building Probe Data: </b><br>\n");
$filelist = get_dirlist($gameroot."class/probes/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$probe_classname =  str_replace(".inc", "", $filelist[$c]); 
		TextFlush( "<br>\nLoading " . $probe_classname . " class<br>\n" );
		if(!class_exists($probe_classname)){
			include ("class/probes/" . $probe_classname . ".inc");
		}
		$probe_object =  new $probe_classname();

		$log_switch_data = $probe_object->log_switch_data();
		TextFlush( "Adding " . $probe_classname . " log switch data to support/log_data/log_switch_data.inc" );
		$file = @fopen($gameroot."support/log_data/log_switch_data.inc", "a");
		if($file === false)
		{
			TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
			$install_error = 1;
		}
		else
		{
			fwrite($file, $log_switch_data); 
			fclose($file);
			TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
		}

		$log_language_data = $probe_object->log_language_data();
		foreach ($language_array as $languagename) { 
			TextFlush( "Adding " . $probe_classname . " log language data to support/log_data/" . $languagename . "/lang_log.inc" );
			$file = @fopen($gameroot."support/log_data/" . $languagename . "/lang_log.inc", "a");
			if($file === false)
			{
				TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
				$install_error = 1;
			}
			else
			{
				if(!isset($log_language_data[$languagename]["title"]))
				{
					$l_log_title = $log_language_data["english"]["title"];
					$l_log_text = $log_language_data["english"]["text"];
				}
				else
				{
					$l_log_title = $log_language_data[$languagename]["title"];
					$l_log_text = $log_language_data[$languagename]["text"];
				}
				fwrite($file, "<?php\n\$l_log_title[\"" . $probe_object->tag . "\"] = \"" . $l_log_title . "\";\n"); 
				fwrite($file, "\$l_log_text[\"" . $probe_object->tag . "\"] = \"" . $l_log_text . "\";\n?>\n"); 
				fclose($file);
				TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
			}
		}
	}
}

TextFlush( "Closing support/log_data/log_switch_data.inc" );
$file = @fopen($gameroot."support/log_data/log_switch_data.inc", "a");
if($file === false)
{
	TextFlush( "<font color=\"red\"> - Fail</font><br>\n" );
	$install_error = 1;
}
else
{
	$close_tag = "<?  return \$retvalue;
}
?>";
	fwrite($file, $close_tag); 
	fclose($file);
	TextFlush( "<font color=\"lime\"> - Ok</font><br>\n" );
}

import_commodity_modules("commodities");
import_class_modules("planet");
import_class_modules("ship");
import_debris_modules("debris");

TextFlush("<b>Building Casino Module List: </b><br>\n");

$casinolist = "";
$filelist = get_dirlist($gameroot."casino/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$fs = fopen($gameroot . "casino/" . $filelist[$c], "r");
		$head = fgets($fs);
		$name = AAT_substr(trim(fgets($fs)), 3);
		$image = AAT_substr(trim(fgets($fs)), 3);
		$description = AAT_substr(trim(fgets($fs)), 3);
		$casino_link = AAT_substr(trim(fgets($fs)), 3);
		$online_status = AAT_substr(trim(fgets($fs)), 3);
		fclose($fs);
		$casinolist .= "name='" . $name . "'\n";
		$casinolist .= "image='" . $image . "'\n";
		$casinolist .= "description='" . $description . "'\n";
		$casinolist .= "casino_link='" . $casino_link . "'\n";
		$casinolist .= "online_status='" . $online_status . "'\n";
		$casinolist .= "\n";
		TextFlush( "Casino Module $name installed <font color=\"lime\">- operation completed successfully.</font><br>\n");
	}
}

$casinolist .= "name='Exit'
image='exit.gif'
description='Exit the Casino'
casino_link='main'
online_status='Y'
";

TextFlush( "Casino Module main installed <font color=\"lime\">- operation completed successfully.</font><br><br>\n");

$fs = @fopen('support/casino.ini', 'w');
@fwrite($fs, $casinolist);
@fclose($fs);

TextFlush( "<b>Creating Smilie Database<b><br>\n");
$fs = fopen($gameroot."support/smilies.ini", "r");
$silent = 0;
while(!feof($fs)){
	$items = fgets($fs);
	$selections = explode(",", $items);
	$selections[0] = trim($selections[0]);
	$selections[1] = trim($selections[1]);
	$selections[2] = trim($selections[2]);
	if(!empty($selections[0]))
	{
		TextFlush( "Adding Smilie: $selections[0] - <img src=\"images/smiles/" . $selections[1] . "\"> " );
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}smilies (code, smile_image, emoticon) VALUES ('$selections[0]', '$selections[1]', '$selections[2]')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}
fclose($fs);
$silent = 1;

if($install_error == 1)
{
		TextFlush( "<br><font color='red' size='4'><b>There was an error during your installation.  Scroll up the page and look for any error reports.  Fix any errors and run the <a href='create_game.php'>create_game.php</a> program again.</b></font><br>" );
}
echo "<input type=hidden name=sektors value=$sektors>";
echo "<input type=hidden name=step value=30>";
echo "<input type=hidden name=count value=$count>";

?>