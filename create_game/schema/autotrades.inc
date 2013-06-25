<?php
    // Start of traderoutes table
	TextFlush( "Dropping: {$db_prefix}autotrades ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}autotrades`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}autotrades ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}autotrades` (
	`traderoute_id` int(11) NOT NULL auto_increment,
	`planet_id` int(11) NOT NULL default '0',
	`port_id_goods` int(11) NOT NULL default '0',
	`goods_price` int(11) NOT NULL default '0',
	`port_id_ore` int(11) NOT NULL default '0',
	`ore_price` int(11) NOT NULL default '0',
	`port_id_organics` int(11) NOT NULL default '0',
	`organics_price` int(11) NOT NULL default '0',
	`port_id_energy` int(11) NOT NULL default '0',
	`energy_price` int(11) NOT NULL default '0',
	`port_id_colonist` int(11) NOT NULL default '0',
	`colonist_price` int(11) NOT NULL default '0',
	`current_trade` bigint(20) NOT NULL default '0',
	`owner` int(11) NOT NULL default '0',
	`trade_time` datetime NOT NULL default '0000-00-00 00:00:00',
	PRIMARY KEY	(`traderoute_id`),
	KEY `owner` (`owner`),
	KEY `trade_time` (`trade_time`),
	KEY `planet_id` (`planet_id`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}autotrades", $res,__LINE__,__FILE__);

    // End of autotrades table

?>