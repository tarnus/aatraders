<?php
    // Start Config values table
	TextFlush( "Dropping: {$db_prefix}config_values ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}config_values`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}config_values ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}config_values` (
	`id` int(11) NOT NULL auto_increment,
	`name` varchar(30) default NULL,
	`value` varchar(250) default NULL,
	`input_type` varchar(10) default NULL,
	`input_selections` varchar(250) default NULL,
	`description` text,
	`section` varchar(100) default NULL,
	PRIMARY KEY	(`id`),
	KEY `name` (`name`),
	KEY `section` (`section`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}config_values", $res,__LINE__,__FILE__);
    // End Config values table

?>