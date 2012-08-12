<?php
	// Start of Casino Forum Tables
	
    // Start forums table
	TextFlush( "Dropping: {$db_prefix}casino_forums ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}casino_forums`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}casino_forums ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}casino_forums` (
	`forum_id` int(11) NOT NULL auto_increment,
	`forum_name` varchar(150) NOT NULL default '0',
	`forum_desc` text,
	`forum_posts` int(11) NOT NULL default '0',
	`forum_topics` int(11) NOT NULL default '0',
	`lastposttime` datetime NOT NULL default '0000-00-00 00:00:00',
	`private` int(11) NOT NULL default '0',
	`casino_sector` int(11) NOT NULL default '0',
	PRIMARY KEY	(`forum_id`),
	KEY `private` (`private`),
	KEY `casino_sector` (`casino_sector`),
	KEY `lastposttime` (`lastposttime`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}casino_forums", $res,__LINE__,__FILE__);
    // End forums table

?>