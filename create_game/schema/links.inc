<?php
    // Start of links table
	TextFlush( "Dropping: {$db_prefix}links ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}links`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}links ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}links` (
	`link_id` int(11) NOT NULL auto_increment,
	`link_start` int(11) NOT NULL default '0',
	`link_dest` int(11) NOT NULL default '0',
	PRIMARY KEY	(`link_id`),
	KEY `link_start` (`link_start`),
	KEY `link_dest` (`link_dest`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}links", $res,__LINE__,__FILE__);
    // End of links table

?>