<?php
    // Start Message Block table
	TextFlush( "Dropping: {$db_prefix}message_block ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}message_block`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}message_block ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}message_block` (
	`mb_id` bigint(20) NOT NULL auto_increment,
	`blocked_player_id` int(11) NOT NULL default '0',
	`player_id` int(11) NOT NULL default '0',
	PRIMARY KEY	(`mb_id`),
	KEY `blocked_player_id` (`blocked_player_id`),
	KEY `player_id` (`player_id`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}message_block", $res,__LINE__,__FILE__);
    // End Message Block table

?>