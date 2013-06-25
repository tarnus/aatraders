<?php
    // Start spies table
	TextFlush( "Dropping: {$db_prefix}spies ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}spies`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}spies ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}spies` (
	`spy_id` bigint(20) NOT NULL auto_increment,
	`active` char(1) NOT NULL default 'N',
	`owner_id` int(11) NOT NULL default '0',
	`planet_id` int(11) NOT NULL default '0',
	`ship_id` int(11) NOT NULL default '0',
	`job_id` int(11) NOT NULL default '0',
	`spy_percent` double(8,6) NOT NULL default '0.000000',
	`move_type` varchar(10) NOT NULL default 'toship',
	`spy_cloak` int(11) NOT NULL default '0',
	PRIMARY KEY	(`spy_id`),
	KEY `planet_id` (`planet_id`),
	KEY `owner_id` (`owner_id`),
	KEY `active` (`active`),
	KEY `ship_id` (`ship_id`),
	KEY `job_id` (`job_id`),
	KEY `spy_percent` (`spy_percent`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}spies", $res,__LINE__,__FILE__);
    // End Spy table

?>