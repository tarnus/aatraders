<?php
    // Start scheduler table
	TextFlush( "Dropping: {$db_prefix}scheduler ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}scheduler`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}scheduler ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}scheduler` (
	`sched_id` int(11) NOT NULL auto_increment,
	`enable_schedule` int(11) NOT NULL default '1',
	`execution_order` int(11) NOT NULL default '0',
	`is_loop` char(1) NOT NULL default 'N',
	`loop_count` int(11) NOT NULL default '0',
	`ticks_left` int(11) NOT NULL default '0',
	`ticks_full` int(11) NOT NULL default '0',
	`sched_file` varchar(50) NOT NULL default '',
	`extra_info` varchar(250) NOT NULL default '',
	`last_run` datetime default NULL,
	PRIMARY KEY	(`sched_id`),
	KEY `enable_schedule` (`enable_schedule`),
	KEY `execution_order` (`execution_order`),
	KEY `is_loop` (`is_loop`),
	KEY `last_run` (`last_run`),
	KEY `ticks_left` (`ticks_left`),
	KEY `ticks_full` (`ticks_full`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}scheduler", $res,__LINE__,__FILE__);
    // End scheduler table

?>