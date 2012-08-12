<?php
    // Start player presets table
	TextFlush( "Dropping: {$db_prefix}presets ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}presets`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}presets ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}presets` (
	`preset_id` int(11) NOT NULL auto_increment,
	`player_id` int(11) default '0',
	`preset` varchar(50) NOT NULL default 'Sol',
	`info` varchar(15) default NULL,
	PRIMARY KEY	(`preset_id`),
	KEY `player_id` (`player_id`),
	KEY `preset` (`preset`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}presets", $res,__LINE__,__FILE__);
    // End of players presets table

?>