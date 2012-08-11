<?php
    // Start ships table
	TextFlush( "Dropping: {$db_prefix}ships ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ships`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ships ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ships` (
	`ship_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`class` int(11) NOT NULL default '1',
	`name` varchar(50) default NULL,
	`basehull` int(11) NOT NULL default '0',
	`hull` int(11) NOT NULL default '0',
	`hull_normal` int(11) NOT NULL default '0',
	`engines` int(11) NOT NULL default '0',
	`engines_normal` int(11) NOT NULL default '0',
	`power` int(11) NOT NULL default '0',
	`power_normal` int(11) NOT NULL default '0',
	`fighter` int(11) NOT NULL default '0',
	`fighter_normal` int(11) NOT NULL default '0',
	`fighter_class` varchar(99) default 'Ship_Fighter',
	`sensors` int(11) NOT NULL default '0',
	`sensors_normal` int(11) NOT NULL default '0',
	`beams` int(11) NOT NULL default '0',
	`beams_normal` int(11) NOT NULL default '0',
	`beam_class` varchar(99) default 'Ship_Beam',
	`torp_launchers` int(11) NOT NULL default '0',
	`torp_launchers_normal` int(11) NOT NULL default '0',
	`torp_class` varchar(99) default 'Ship_Torpedo',
	`shields` int(11) NOT NULL default '0',
	`shields_normal` int(11) NOT NULL default '0',
	`shield_class` varchar(99) default 'Ship_Shield',
	`armor` int(11) NOT NULL default '0',
	`armor_normal` int(11) NOT NULL default '0',
	`armor_class` varchar(99) default 'Ship_Armor',
	`cloak` int(11) NOT NULL default '0',
	`cloak_normal` int(11) NOT NULL default '0',
	`ecm` int(11) NOT NULL default '0',
	`ecm_normal` int(11) NOT NULL default '0',
	`sector_id` int(11) NOT NULL default '0',
	`energy` bigint(20) NOT NULL default '0',
	`armor_pts` bigint(20) NOT NULL default '0',
	`fighters` bigint(20) NOT NULL default '0',
	`torps` bigint(20) NOT NULL default '0',
	`on_planet` char(1) NOT NULL default 'N',
	`planet_id` int(11) NOT NULL default '0',
	`storage_planet_id` int(11) NOT NULL default '0',
	`cleared_defenses` varchar(99) default NULL,
	PRIMARY KEY	(`ship_id`),
	KEY `sector_id` (`sector_id`),
	KEY `player_id` (`player_id`),
	KEY `planet_id` (`planet_id`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ships", $res,__LINE__,__FILE__);
    // End ships table

?>