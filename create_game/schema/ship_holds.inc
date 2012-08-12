<?php
    // Start ship holds table

	TextFlush( "Dropping: {$db_prefix}ship_holds ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ship_holds`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ship_holds ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ship_holds` (
	`hold_id` int(11) NOT NULL auto_increment,
	`ship_id` int(11) NOT NULL default '0',
	`class` varchar(100) default NULL,
	`cargo_name` varchar(100) default NULL,
	`cargo_class` varchar(100) default NULL,
	`hold_space` int(11) NOT NULL default '0',
	`amount` double(32,0) NOT NULL default '0',
	PRIMARY KEY	(`hold_id`),
	KEY `ship_id` (`ship_id`),
	KEY `cargo_name` (`cargo_name`),
	KEY `cargo_class` (`cargo_class`),
	KEY `amount` (`amount`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ship_holds", $res,__LINE__,__FILE__);
    // End ship holds table

?>