<?php
    // Start teams table
	TextFlush( "Dropping: {$db_prefix}teams ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}teams`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}teams ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}teams` (
	`id` int(11) NOT NULL auto_increment,
	`creator` int(11) NOT NULL default '0',
	`team_name` varchar(40) default NULL,
	`description` varchar(150) default NULL,
	`icon` varchar(255) default NULL,
	PRIMARY KEY	(`id`),
	KEY `creator` (`creator`),
	KEY `team_name` (`team_name`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}teams", $res,__LINE__,__FILE__);

    // End of teams table

?>