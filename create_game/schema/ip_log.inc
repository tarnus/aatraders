<?php
    // Start ip log table
	TextFlush( "Dropping: {$db_prefix}ip_log ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ip_log`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ip_log ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ip_log` (
	`log_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`ip_address` varchar(16) NOT NULL default '',
	`time` datetime default NULL,
	PRIMARY KEY	(`log_id`),
	KEY `player_id` (`player_id`),
	KEY `ip_address` (`ip_address`),
	KEY `time` (`time`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ip_log", $res,__LINE__,__FILE__);
    // End ip_log

?>