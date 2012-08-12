<?php
    // Start team_forum_players table
	TextFlush( "Dropping: {$db_prefix}team_forum_players ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}team_forum_players`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}team_forum_players ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}team_forum_players` (
	`rec_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`playername` varchar(250) NOT NULL default '0',
	`signupdate` datetime NOT NULL default '0000-00-00 00:00:00',
	`lastonline` datetime NOT NULL default '0000-00-00 00:00:00',
	`currenttime` datetime NOT NULL default '0000-00-00 00:00:00',
	`postcount` int(11) NOT NULL default '0',
	`admin` int(11) NOT NULL default '0',
	PRIMARY KEY	(`rec_id`),
	KEY `player_id` (`player_id`),
	KEY `lastonline` (`lastonline`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}team_forum_players", $res,__LINE__,__FILE__);
    // End team_forum_players table

?>