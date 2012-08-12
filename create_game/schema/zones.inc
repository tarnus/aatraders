<?php
    // Start zones table
	TextFlush( "Dropping: {$db_prefix}zones ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}zones`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}zones ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}zones` (
	`zone_id` int(11) NOT NULL auto_increment,
	`zone_name` varchar(40) default NULL,
	`owner` int(11) NOT NULL default '0',
	`team_zone` char(1) NOT NULL default 'N',
	`allow_beacon` char(1) NOT NULL default 'Y',
	`allow_attack` char(1) NOT NULL default 'Y',
	`allow_planetattack` char(1) NOT NULL default 'Y',
	`allow_warpedit` char(1) NOT NULL default 'Y',
	`allow_planet` char(1) NOT NULL default 'Y',
	`allow_trade` char(1) NOT NULL default 'Y',
	`allow_defenses` char(1) NOT NULL default 'Y',
	`max_hull` int(11) NOT NULL default '0',
	`zone_color` varchar(8) NOT NULL default '#000000',
	PRIMARY KEY	(`zone_id`),
	KEY `owner` (`owner`),
	KEY `team_zone` (`team_zone`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}zones", $res,__LINE__,__FILE__);
    // End of zones table

?>