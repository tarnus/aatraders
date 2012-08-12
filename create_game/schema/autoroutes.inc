<?php
    // Start of autoroute table
	TextFlush( "Dropping: {$db_prefix}autoroutes ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}autoroutes`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}autoroutes ");
 	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}autoroutes` (
	`autoroute_id` int(11) NOT NULL auto_increment,
	`start_sector` varchar(30) NOT NULL default '',
	`destination` varchar(30) NOT NULL default '',
	`warp_list` text,
	`player_id` int(11) NOT NULL default '0',
	`name` varchar(30) NOT NULL default '',
	PRIMARY KEY	(`autoroute_id`),
	KEY `player_id` (`player_id`),
	KEY `start_sector` (`start_sector`),
	KEY `destination` (`destination`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}autoroutes", $res,__LINE__,__FILE__);
    // End of autoroutes table

?>