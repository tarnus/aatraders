<?php
    // Start sector_notes table
	TextFlush( "Dropping: {$db_prefix}sector_notes ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}sector_notes`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}sector_notes ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}sector_notes` (
	`note_id` int(11) NOT NULL auto_increment,
	`note_player_id` int(11) NOT NULL default '0',
	`note_team_id` int(11) NOT NULL default '0',
	`note_sector_id` int(11) NOT NULL default '0',
	`note_sector_name` varchar(30) NOT NULL default '',
	`note_data` text,
	`note_date` datetime NOT NULL default '0000-00-00 00:00:00',
	`note_stype` varchar(50) NOT NULL default '',
	`note_sowner` varchar(50) NOT NULL default '',
	`note_sport` varchar(50) NOT NULL default '',
	`note_splanets` tinyint(4) NOT NULL default '0',
	`note_scanfrom` int(11) NOT NULL default '0',
	`note_scanfrom_name` varchar(30) NOT NULL default '',
	`note_sfighters` bigint(20) NOT NULL default '0',
	`note_storps` bigint(20) NOT NULL default '0',
	PRIMARY KEY	(`note_id`),
	KEY `note_player_id` (`note_player_id`),
	KEY `note_team_id` (`note_team_id`),
	KEY `note_date` (`note_date`),
	KEY `note_sector_id` (`note_sector_id`),
	KEY `note_scanfrom_name` (`note_scanfrom_name`),
	KEY `note_sector_name` (`note_sector_name`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}sector_notes", $res,__LINE__,__FILE__);
   // End sector_notes table

 ?>