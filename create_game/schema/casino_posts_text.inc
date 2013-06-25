<?php
    // Start posts_text table
	TextFlush( "Dropping: {$db_prefix}casino_posts_text ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}casino_posts_text`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}casino_posts_text ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}casino_posts_text` (
	`post_id` int(11) NOT NULL auto_increment,
	`post_text` text,
	`topic_id` int(11) NOT NULL default '0',
	`forum_id` int(11) NOT NULL default '0',
	`post_player_id` int(11) NOT NULL default '0',
	PRIMARY KEY	(`post_id`),
	KEY `topic_id` (`topic_id`),
	KEY `forum_id` (`forum_id`),
	KEY `post_player_id` (`post_player_id`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}casino_posts_text", $res,__LINE__,__FILE__);
    // End posts_text table

?>