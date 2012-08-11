<?php

// For this page, we DONT want SQL debug on the screen (0 is shown on screen, 1 is hidden)

function db_op2_result($table, $query, $served_line, $served_page)
{
	global $db, $silent, $_SERVER, $cumulative, $db_type, $install_error;

	if ($db->ErrorNo() == 0)
	{
		if (!$silent)
		{
			$is_there = $db->Execute("SELECT * from $table");

			if($is_there){
				TextFlush( "<font color=\"lime\">- Table Created Successfully.</font><br>\n");
			}
			else
			{
				TextFlush( "<font color=\"red\">- Table Creation Failed.</font><br>\n");
				$temp_error = $db->ErrorMsg();
				$dberror = "A Database error occurred in " . $served_page . " on line " . ($served_line-1) . " (called from: $_SERVER[PHP_SELF]): " . $temp_error . " - Original SQL: " . $db->sql;
				$dberror = AAT_ereg_replace("'","&#039;",$dberror); // Allows the use of apostrophes.
				adminlog("LOG0_ADMIN_DBERROR", $dberror);
				$cumulative = 1; // For areas with multiple actions needing status - 0 is all good so far, 1 is at least one bad.
				$install_error = 1;

				if (!$silent)
				{
					TextFlush( "<font color=\"red\">- failed to complete database operation in $served_page on line " .($served_line-1). ". Error code follows:\n");
					TextFlush( "<hr>\n");
					TextFlush( $temp_error . "<br><br>Original SQL: " . $db->sql);
					TextFlush( "<hr>\n");
					TextFlush( "</font><br>\n");
				}
			}
		}
	}
	else
	{
		TextFlush( "<font color=\"red\">- Table Creation Failed.</font><br>\n");
		$temp_error = $db->ErrorMsg();
		$dberror = "A Database error occurred in " . $served_page . " on line " . ($served_line-1) . " (called from: $_SERVER[PHP_SELF]): " . $temp_error . " - Original SQL: " . $db->sql;
		$dberror = AAT_ereg_replace("'","&#039;",$dberror); // Allows the use of apostrophes.
		adminlog("LOG0_ADMIN_DBERROR", $dberror);
		$cumulative = 1; // For areas with multiple actions needing status - 0 is all good so far, 1 is at least one bad.
		$install_error = 1;

		if (!$silent)
		{
			TextFlush( "<font color=\"red\">- failed to complete database operation in $served_page on line " .($served_line-1). ". Error code follows:\n");
			TextFlush( "<hr>\n");
			TextFlush( $temp_error . "<br><br>Original SQL: " . $db->sql);
			TextFlush( "<hr>\n");
			TextFlush( "</font><br>\n");
		}
	}
}

$silent = 0;

function create_schema()
{
	// If you add/remove a table, don't forget to update the
	// table name variables in the global_func file.

	global $maxlen_password;
	global $db_prefix;
	global $db;
	global $db_mysql_type;
	global $default_prod_fighters;
	global $default_prod_torp;
	global $silent;
	global $served_page;
	global $bigint_name;
	global $db_type;
	global $float_size;
	global $float_type;
	global $mbstring_supported;

	if($db_type == "mysql" and $db_mysql_type == "InnoDB"){
		$database_type = 'InnoDB';
	}
	else
	{
		$database_type = 'MyISAM';
	}

	if($mbstring_supported == 1)
	{
		$dbencoding = " DEFAULT CHARSET=utf8";
	}
	else
	{
		$dbencoding = "";
	}

	// Create database schema

	$cumulative = 0; // Clears the db error counter

	TextFlush( "<b>Dropping and Creating tables </b><br>");

	// Logs must go first, to catch errors. Else, its all alphabetical order.

	TextFlush( "Dropping: {$db_prefix}admin_log ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}admin_log`");
	db_op_result($res,__LINE__,__FILE__);

	// Start admin_log table
	TextFlush( "Creating table: {$db_prefix}admin_log ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}admin_log` (
	`log_id` int(11) NOT NULL auto_increment,
	`type` varchar(50) default NULL,
	`time` datetime default NULL,
	`data` text,
	PRIMARY KEY  (`log_id`),
	KEY `type` (`type`),
	KEY `time` (`time`)
	) TYPE={$database_type}{$dbencoding}");
	db_op2_result("{$db_prefix}admin_log", $res,__LINE__,__FILE__);

	// End logs table

	echo "<br>";
//
// load all of the schema files from the schema directory here
//

	$filelist = get_dirlist($gameroot."create_game/schema/");
	sort($filelist);
	reset($filelist);
	for ($c=0; $c<count($filelist); $c++) {
		if($filelist[$c] != "index.html")
		{
			include ("create_game/schema/" . $filelist[$c]);
			echo "<br>";
		}
	}

	//Finished
	if ($cumulative == 0)
	{
		TextFlush( "<b>All tables created successfully.</b><p>");
	}
	else
	{
		TextFlush( "<b><font color=\"yellow\">At least one error occured during table creation.</font></b><br>\n");
	}
}

//include_once( "backends/adodb_lite/adodb-datadict.inc.php" );
//include_once( "backends/adodb_lite/adodb-xmlschema.inc.php" );

function create_schema_xml()
{
	// If you add/remove a table, don't forget to update the
	// table name variables in the global_func file.

	global $db_prefix;
	global $db;
	global $db_mysql_type;
	global $silent;
	global $db_type;

	// Create database schema

	$cumulative = 0; // Clears the db error counter
$db->debug=1;
	$schema = new adoSchema($db);
	$schema->setPrefix($db_prefix);

	TextFlush( "<b>Dropping and Creating tables </b><br>");
	TextFlush( "Dropping: {$db_prefix}admin_log");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}admin_log`");
	db_op_result($res,__LINE__,__FILE__);
	$filelist = get_dirlist($gameroot . "support/schema_xml/");
	sort($filelist);
	reset($filelist);
	for ($c = 0; $c < count($filelist); $c++) {
		if($filelist[$c] != "index.html" && $filelist[$c] != "admin_log.xml")
		{
			TextFlush( "Dropping: {$db_prefix}" . str_replace(".xml", "", $filelist[$c]));
			$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}" . str_replace(".xml", "", $filelist[$c]) . "`");
			db_op_result($res,__LINE__,__FILE__);
		    TextFlush( "Creating table: {$db_prefix}" . str_replace(".xml", "", $filelist[$c]));
			$parsed_xml = $schema->ParseSchema("support/schema_xml/" . $filelist[$c]);
			$result = $schema->ExecuteSchema($parsed_xml, TRUE);

			if ($result == 0 || $result == 1)
			{
				TextFlush("<font color=\"red\">- Schema parse error or failure in: " . $schema_filename . "</font><br>\n");
			}
			else
			{
				if($db_type == "mysql" and $db_mysql_type == "InnoDB")
				{
					$db->Execute("ALTER TABLE " . $$db_prefix . str_replace(".xml", "", $filelist[$c]) . " TYPE=INNODB");
				}
				TextFlush("<font color=\"lime\">- Table Created Successfully.</font><br>\n");
			}
		}
	}
}
?>
