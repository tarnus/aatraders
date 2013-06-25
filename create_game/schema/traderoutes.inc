<?php
    // Start of traderoutes table
	TextFlush( "Dropping: {$db_prefix}traderoutes_new ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}traderoutes`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}traderoutes ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}traderoutes` (
	`traderoute_id` int(11) NOT NULL auto_increment,
	`source_sector` int(11) NOT NULL default '0',
	`source_planet_id` int(11) NOT NULL default '0',
	`source_type` varchar(15) NOT NULL default 'port',
	`source_commodity` varchar(100) NOT NULL default '',
	`destination_sector` int(11) NOT NULL default '0',
	`destination_planet_id` int(11) NOT NULL default '0',
	`destination_type` varchar(15) NOT NULL default 'port',
	`destination_commodity` varchar(100) NOT NULL default '',
	`trade_energy` char(1) NOT NULL default 'Y',
	`trade_fighters` char(1) NOT NULL default 'N',
	`trade_torps` char(1) NOT NULL default 'N',
	`move_type` char(1) NOT NULL default 'W',
	`player_id` int(11) NOT NULL default '0',
	`roundtrip` char(1) NOT NULL default 'Y',
	`autoroute_id` int(11) NOT NULL default '0',
	PRIMARY KEY	(`traderoute_id`),
	KEY `player_id` (`player_id`),
	KEY `source_commodity` (`source_commodity`),
	KEY `move_type` (`move_type`),
	KEY `destination_commodity` (`destination_commodity`),
	KEY `source_sector` (`source_sector`),
	KEY `destination_sector` (`destination_sector`),
	KEY `roundtrip` (`roundtrip`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}traderoutes", $res,__LINE__,__FILE__);
    // End of traderoutes table

?>