<?php
    // Start word censor table
	TextFlush( "Dropping: {$db_prefix}wordcensor ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}wordcensor`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}wordcensor ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}wordcensor` (
	`id` int(11) NOT NULL auto_increment,
	`name` varchar(50) NOT NULL default '0',
	`value` varchar(50) NOT NULL default '0',
	PRIMARY KEY	(`id`),
	KEY `name` (`name`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}wordcensor", $res,__LINE__,__FILE__);
    // End wordcensor table

?>