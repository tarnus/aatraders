<?php
    // Start navmap table
	TextFlush( "Dropping: {$db_prefix}navmap ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}navmap`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}navmap ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}navmap` (
	`nav_id` bigint(20) NOT NULL auto_increment,
	`start_sector` int(11) NOT NULL default '0',
	`dest_sector` int(11) NOT NULL default '0',
	`dest_sector_name` varchar(50) NOT NULL default '',
	`distance` int(11) NOT NULL default '0',
	PRIMARY KEY	(`nav_id`),
	KEY `start_sector` (`start_sector`),
	KEY `dest_sector` (`dest_sector`),
	KEY `dest_sector_name` (`dest_sector_name`),
	KEY `distance` (`distance`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}navmap", $res,__LINE__,__FILE__);
    // End of navmap table

?>