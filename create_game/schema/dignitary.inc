<?php
    // Start digitary table
	TextFlush( "Dropping: {$db_prefix}dignitary ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}dignitary`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}dignitary ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}dignitary` (
	`dig_id` bigint(20) NOT NULL auto_increment,
	`active` char(1) NOT NULL default 'N',
	`owner_id` int(11) NOT NULL default '0',
	`planet_id` int(11) NOT NULL default '0',
	`ship_id` int(11) NOT NULL default '0',
	`job_id` tinyint(4) NOT NULL default '0',
	`percent` double(8,6) NOT NULL default '0.000000',
	`active_date` datetime default NULL,
	`reactive_date` datetime default NULL,
	`embezzler` tinyint(4) NOT NULL default '0',
	PRIMARY KEY	(`dig_id`),
	KEY `planet_id` (`planet_id`),
	KEY `owner_id` (`owner_id`),
	KEY `ship_id` (`ship_id`),
	KEY `active` (`active`),
	KEY `percent` (`percent`),
	KEY `active_date` (`active_date`),
	KEY `reactive_date` (`reactive_date`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}dignitary", $res,__LINE__,__FILE__);
    // End Dignitary table

?>