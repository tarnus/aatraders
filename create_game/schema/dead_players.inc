<?php
    // Start dead_players table
	TextFlush( "Dropping: {$db_prefix}dead_players ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}dead_players`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}dead_players ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}dead_players` (
	`dead_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) NOT NULL default '0',
	`character_name` varchar(20) NOT NULL default '',
	`credits` double(32,0) NOT NULL default '0',
	`turns_used` int(11) NOT NULL default '0',
	`signup_date` datetime default NULL,
	`last_login` datetime default NULL,
	`rating` varchar(15) NOT NULL default '',
	`score` double(24,0) NOT NULL default '0',
	`kills` int(11) NOT NULL default '0',
	`deaths` int(11) NOT NULL default '0',
	`captures` int(11) NOT NULL default '0',
	`planets_built` int(11) NOT NULL default '0',
	`planets_lost` int(11) NOT NULL default '0',
	`profile_name` varchar(250) NOT NULL default '',
	`profile_password` varchar(250) NOT NULL default '',
	`profile_id` int(11) NOT NULL default '0',
	`ip_address` varchar(20) NOT NULL default '0',
	`ship_losses` varchar(255) NOT NULL default '',
	`experience` double(24,2) NOT NULL default '0.00',
	`player_total_online` int(11) NOT NULL default '0',
	`death_type` varchar(30) NOT NULL default '',
	PRIMARY KEY	(`dead_id`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}dead_players", $res,__LINE__,__FILE__);
    // End of dead_players table

?>