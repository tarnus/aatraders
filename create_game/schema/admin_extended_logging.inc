<?php
	// Start admin_extended_logging table
	TextFlush( "Dropping: {$db_prefix}admin_extended_logging ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}admin_extended_logging`");
	db_op_result($res,__LINE__,__FILE__);

	TextFlush( "Creating table: {$db_prefix}admin_extended_logging ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}admin_extended_logging` (
	`log_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`time` datetime default NULL,
	`request_uri` text,
	`get_data` text,
	`post_data` text,
	`score` double(24,0) NOT NULL default '0',
	`ip_address` varchar(20) NOT NULL default '0',
	`currentship` int(11) NOT NULL default '0',
	`credits` double(32,0) NOT NULL default '0',
	`turns` int(11) NOT NULL default '0',
	`player_online_time` int(11) NOT NULL default '0',
	PRIMARY KEY	(`log_id`),
	KEY `player_id` (`player_id`),
	KEY `time` (`time`)
) TYPE={$database_type}{$dbencoding}");
	db_op2_result("{$db_prefix}admin_extended_logging", $res,__LINE__,__FILE__);

	// End logs table

?>