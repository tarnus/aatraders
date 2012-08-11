<?php
	 // Start probe table
	TextFlush( "Dropping: {$db_prefix}probe ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}probe`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}probe ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}probe` (
	`probe_id` int(11) NOT NULL auto_increment,
	`owner_id` int(11) NOT NULL default '0',
	`ship_id` int(11) NOT NULL default '0',
	`engines` int(11) NOT NULL default '0',
	`sensors` int(11) NOT NULL default '0',
	`cloak` int(11) NOT NULL default '0',
	`sector_id` int(11) NOT NULL default '0',
	`type` int(11) NOT NULL default '0',
	`class` varchar(100) NOT NULL default 'sentry',
	`active` char(1) NOT NULL default 'N',
	`turns` int(11) NOT NULL default '0',
	`target_sector` int(11) NOT NULL default '0',
	`prev_sector` int(11) NOT NULL default '0',
	`data` longtext,
	PRIMARY KEY	(`probe_id`),
	KEY `sector_id` (`sector_id`),
	KEY `owner_id` (`owner_id`),
	KEY `ship_id` (`ship_id`),
	KEY `active` (`active`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}probe", $res,__LINE__,__FILE__);
    // End probe table

?>