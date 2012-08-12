<?php
	// Start site_activity_log table
	TextFlush( "Dropping: {$db_prefix}site_activity_log ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}site_activity_log`");
	db_op_result($res,__LINE__,__FILE__);

	TextFlush( "Creating table: {$db_prefix}site_activity_log ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}site_activity_log` (
	`log_id` int(11) NOT NULL auto_increment,
	`player_count` int(11) NOT NULL default '0',
	`time` datetime default NULL,
	`year` INT NOT NULL DEFAULT '0',
	`month` INT NOT NULL DEFAULT '0',
	`day` INT NOT NULL DEFAULT '0',
	`hour` INT NOT NULL DEFAULT '0',
	`minute` INT NOT NULL DEFAULT '0',
	PRIMARY KEY	(`log_id`),
	KEY `time` (`time`),
	KEY `year` (`year`),
	KEY `month` (`month`),
	KEY `day` (`day`),
	KEY `hour` (`hour`),
	KEY `minute` (`minute`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}site_activity_log", $res,__LINE__,__FILE__);
	// End site_activity_log table

?>