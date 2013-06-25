<?php
	// Start logs table
	TextFlush( "Dropping: {$db_prefix}logs ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}logs`");
	db_op_result($res,__LINE__,__FILE__);

	TextFlush( "Creating table: {$db_prefix}logs ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}logs` (
	`log_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`type` varchar(50) default NULL,
	`time` datetime default NULL,
	`data` text,
	PRIMARY KEY	(`log_id`),
	KEY `player_id` (`player_id`),
	KEY `time` (`time`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}logs", $res,__LINE__,__FILE__);
	// End logs table

?>