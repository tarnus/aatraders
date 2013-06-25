<?php
    // Start sector defense table
	TextFlush( "Dropping: {$db_prefix}sector_defense ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}sector_defense`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}sector_defense ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}sector_defense` (
	`defense_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`sector_id` int(11) NOT NULL default '0',
	`defense_type` varchar(100) NOT NULL default 'mines',
	`firing_order` int(11) NOT NULL default '0',
	`damage_type` varchar(10) NOT NULL default 'A',
	`weapon_class` varchar(99) NOT NULL default '',
	`quantity` bigint(20) NOT NULL default '0',
	PRIMARY KEY	(`defense_id`),
	KEY `sector_id` (`sector_id`),
	KEY `player_id` (`player_id`),
	KEY `defense_type` (`defense_type`),
	KEY `quantity` (`quantity`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}sector_defense", $res,__LINE__,__FILE__);
    // End of sector defense table

?>