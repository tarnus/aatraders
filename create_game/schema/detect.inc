<?php
    // Start detect table
	TextFlush( "Dropping: {$db_prefix}detect ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}detect`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}detect ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}detect` (
	`det_id` bigint(20) NOT NULL auto_increment,
	`owner_id` int(11) NOT NULL default '0',
	`det_type` int(11) NOT NULL default '0',
	`det_time` datetime default NULL,
	`data` varchar(255) default NULL,
	`unique_value` bigint(20) default NULL,
	PRIMARY KEY	(`det_id`),
	KEY `owner_id` (`owner_id`),
	KEY `det_time` (`det_time`),
	KEY `unique_value` (`unique_value`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}detect", $res,__LINE__,__FILE__);
    // End detect table

?>