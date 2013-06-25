<?php
    // Start planet log table
	TextFlush( "Dropping: {$db_prefix}planet_log ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}planet_log`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}planet_log ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}planet_log` (
	`planetlog_id` int(11) NOT NULL auto_increment,
	`planet_id` int(11) default '0',
	`player_id` int(11) NOT NULL default '0',
	`owner_id` int(11) NOT NULL default '0',
	`ip_address` varchar(16) NOT NULL default '0',
	`action` varchar(50) default NULL,
	`time` datetime default NULL,
	PRIMARY KEY	(`planetlog_id`),
	KEY `planet_id` (`planet_id`),
	KEY `player_id` (`player_id`),
	KEY `owner_id` (`owner_id`),
	KEY `action` (`action`),
	KEY `time` (`time`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}planet_log", $res,__LINE__,__FILE__);
    // End planet_log

?>