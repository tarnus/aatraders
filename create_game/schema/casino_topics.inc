<?php
    // Start topics table
	TextFlush( "Dropping: {$db_prefix}casino_topics ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}casino_topics`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}casino_topics ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}casino_topics` (
	`topic_id` int(11) NOT NULL auto_increment,
	`topic_title` varchar(60) NOT NULL default '0',
	`topic_poster` varchar(250) NOT NULL default '0',
	`topic_time` datetime NOT NULL default '0000-00-00 00:00:00',
	`lastpostdate` datetime NOT NULL default '0000-00-00 00:00:00',
	`topic_views` int(11) NOT NULL default '0',
	`topic_replies` int(11) NOT NULL default '0',
	`forum_id` int(11) NOT NULL default '0',
	`topic_status` int(11) NOT NULL default '0',
	`post_player_id` int(11) NOT NULL default '0',
	PRIMARY KEY	(`topic_id`),
	KEY `forum_id` (`forum_id`),
	KEY `topic_status` (`topic_status`),
	KEY `topic_time` (`topic_time`),
	KEY `post_player_id` (`post_player_id`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}casino_topics", $res,__LINE__,__FILE__);
    // End topics table

?>