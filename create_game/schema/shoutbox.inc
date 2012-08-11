<?php
    // Start Shoutbox table

	TextFlush( "Dropping: {$db_prefix}shoutbox ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}shoutbox`");
	db_op_result($res,__LINE__,__FILE__);

	TextFlush( "Creating table: {$db_prefix}shoutbox ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}shoutbox` (
	`sb_id` bigint(20) NOT NULL auto_increment,
	`player_id` bigint(20) NOT NULL default '0',
	`player_name` varchar(60) NOT NULL default '',
	`sb_date` bigint(20) NOT NULL default '0',
	`sb_text` text,
	`sb_alli` bigint(20) NOT NULL default '0',
	PRIMARY KEY	(`sb_id`),
	KEY `sb_date` (`sb_date`),
	KEY `sb_alli` (`sb_alli`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}shoutbox", $res,__LINE__,__FILE__);
    // End Shoutbox table

?>