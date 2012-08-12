<?php
    // Start player team history table
	TextFlush( "Dropping: {$db_prefix}player_team_history ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}player_team_history`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}player_team_history ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}player_team_history` (
	`history_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`history_team_id` int(11) NOT NULL default '0',
	`history_team_name` varchar(250) default NULL,
	`info` varchar(30) default NULL,
	`left_team` datetime default NULL,
	PRIMARY KEY	(`history_id`),
	KEY `player_id` (`player_id`),
	KEY `left_team` (`left_team`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}player_team_history", $res,__LINE__,__FILE__);
    // End player team history

?>