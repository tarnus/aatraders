<?php
    // Start ship_devices table

	TextFlush( "Dropping: {$db_prefix}ship_devices ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ship_devices`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ship_devices ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ship_devices` (
	`device_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`ship_id` int(11) NOT NULL default '0',
	`class` varchar(100) default NULL,
	`device_name` varchar(100) default NULL,
	`cargo_class` varchar(100) default NULL,
	`program` varchar(100) default NULL,
	`techmodify` varchar(100) NOT NULL default '',
	`amount` double(32,0) NOT NULL default '0',
	PRIMARY KEY	(`device_id`),
	KEY `ship_id` (`ship_id`),
	KEY `player_id` (`player_id`),
	KEY `device_name` (`device_name`),
	KEY `cargo_class` (`cargo_class`),
	KEY `amount` (`amount`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ship_devices", $res,__LINE__,__FILE__);
    // End ship_devices table

?>