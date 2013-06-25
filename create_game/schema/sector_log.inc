<?php
    // Start sector log table
	TextFlush( "Dropping: {$db_prefix}sector_log ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}sector_log`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}sector_log ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}sector_log` (
	`event_id` int(11) NOT NULL auto_increment,
	`ship_id` int(11) NOT NULL default '0',
	`player_id` int(11) default '0',
	`source` int(11) default '0',
	`destination` int(11) default '0',
	`ship_class` int(11) default '0',
	`ship_cloak` int(11) default '0',
	`time` datetime default NULL,
	`zone_id` int(11) default '0',
	`warp_links` text,
	`port_buys` text,
	PRIMARY KEY	(`event_id`),
	KEY `ship_id` (`ship_id`),
	KEY `source` (`source`),
	KEY `destination` (`destination`),
	KEY `time` (`time`),
	KEY `player_id` (`player_id`),
	KEY `ship_class` (`ship_class`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}sector_log", $res,__LINE__,__FILE__);
    // End sector log table

?>