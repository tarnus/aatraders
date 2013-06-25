<?php
    // Start posts table
	TextFlush( "Dropping: {$db_prefix}casino_posts ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}casino_posts`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}casino_posts ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}casino_posts` (
	`post_id` int(11) NOT NULL auto_increment,
	`topic_id` int(11) NOT NULL default '0',
	`forum_id` int(11) NOT NULL default '0',
	`post_time` datetime NOT NULL default '0000-00-00 00:00:00',
	`post_edit_time` datetime NOT NULL default '0000-00-00 00:00:00',
	`post_edit_count` int(11) NOT NULL default '0',
	`post_username` varchar(250) NOT NULL default '0',
	`post_player_id` int(11) NOT NULL default '0',
	PRIMARY KEY	(`post_id`),
	KEY `topic_id` (`topic_id`),
	KEY `forum_id` (`forum_id`),
	KEY `post_player_id` (`post_player_id`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}casino_posts", $res,__LINE__,__FILE__);
    // End posts table

?>