<?php
    // Start universe table
	TextFlush( "Dropping: {$db_prefix}universe ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}universe`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}universe ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}universe` (
	`sector_id` bigint(20) NOT NULL auto_increment,
	`sector_name` varchar(30) NOT NULL default '',
	`zone_id` int(11) NOT NULL default '0',
	`star_size` int(11) NOT NULL default '0',
	`port_type` varchar(50) NOT NULL default 'none',
	`x` int(11) NOT NULL default '0',
	`y` int(11) NOT NULL default '0',
	`z` int(11) NOT NULL default '0',
	`spiral_arm` int(11) NOT NULL default '0',
	`galaxy` int(11) NOT NULL default '0',
	`beacon` varchar(50) NOT NULL default '',
	`sg_sector` bigint(20) NOT NULL default '0',
	`mission_id` int(11) NOT NULL default '0',
	`creation_date` datetime NOT NULL default '0000-00-00 00:00:00',
	`creator_id` int(11) NOT NULL default '0',
	`created_from` bigint(20) NOT NULL default '0',
	PRIMARY KEY	(`sector_id`),
	KEY `sector_name` (`sector_name`),
	KEY `spiral_arm` (`spiral_arm`),
	KEY `port_type` (`port_type`),
	KEY `zone_id` (`zone_id`),
	KEY `x` (`x`),
	KEY `y` (`y`),
	KEY `z` (`z`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}universe", $res,__LINE__,__FILE__);
    // End of universe table

?>