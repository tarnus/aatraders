<?php
    // Start artifacts table
	TextFlush( "Dropping: {$db_prefix}artifacts ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}artifacts`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}artifacts ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}artifacts` (
	`artifact_id` int(11) NOT NULL auto_increment,
	`artifact_type` varchar(50) NOT NULL,
	`artifact_piece` int(11) NOT NULL default '0',
	`on_port` tinyint(4) NOT NULL default '0',
	`on_planet_id` int(11) NOT NULL default '0',
	`sector_id` int(11) NOT NULL default '0',
	`player_id` int(11) NOT NULL default '0',
	`cloak` int(11) NOT NULL default '0',
	`scoremax` int(11) NOT NULL default '0',
	PRIMARY KEY	(`artifact_id`),
	KEY `sector_id` (`sector_id`),
	KEY `player_id` (`player_id`),
	KEY `on_planet_id` (`on_planet_id`),
	KEY `artifact_type` (`artifact_type`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}artifacts", $res,__LINE__,__FILE__);
    // End artifacts table

?>