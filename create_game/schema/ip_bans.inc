<?php
    // Start ip bans table
	TextFlush( "Dropping: {$db_prefix}ip_bans ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ip_bans`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ip_bans ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ip_bans` (
	`ban_id` int(11) NOT NULL auto_increment,
	`ban_mask` varchar(16) NOT NULL default '',
	`email` varchar(150) NOT NULL default '',
	PRIMARY KEY	(`ban_id`),
	KEY `ban_mask` (`ban_mask`),
	KEY `email` (`email`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ip_bans", $res,__LINE__,__FILE__);
    // End ip bans table

?>