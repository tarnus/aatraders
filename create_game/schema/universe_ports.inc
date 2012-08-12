<?php
    // Start universe_ports table
	TextFlush( "Dropping: {$db_prefix}universe_ports ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}universe_ports`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}universe_ports");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}universe_ports` (
	`data_id` bigint(20) NOT NULL auto_increment,
	`sector_id` bigint(20) NOT NULL default '0',
	`commodity_type` varchar(50) NOT NULL default 'none',
	`commodity_amount` double(32,2) NOT NULL default '0',
	`commodity_price` double(30,10) NOT NULL default '0.0000000000',
	`trade_date` datetime NOT NULL default '0000-00-00 00:00:00',
	`goodevil` int(11) NOT NULL default '1',
	PRIMARY KEY	(`data_id`),
	KEY `sector_id` (`sector_id`),
	KEY `commodity_type` (`commodity_type`),
	KEY `commodity_amount` (`commodity_amount`),
	KEY `commodity_price` (`commodity_price`),
	KEY `trade_date` (`trade_date`),
	KEY `goodevil` (`goodevil`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}universe_ports", $res,__LINE__,__FILE__);
    // End of universe_portdata table

?>