<?php
	// Start dead_player_logs table
	TextFlush( "Dropping: {$db_prefix}dead_player_logs ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}dead_player_logs`");
	db_op_result($res,__LINE__,__FILE__);

	TextFlush( "Creating table: {$db_prefix}dead_player_logs ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}dead_player_logs` (
	`log_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`type` varchar(50) default NULL,
	`time` datetime default NULL,
	`data` text,
	PRIMARY KEY	(`log_id`),
	KEY `player_id` (`player_id`),
	KEY `time` (`time`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}dead_player_logs", $res,__LINE__,__FILE__);
	// End logs table

?>