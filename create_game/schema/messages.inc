<?php
    // Start messaging table
	TextFlush( "Dropping: {$db_prefix}messages ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}messages`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}messages ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}messages` (
	`ID` int(11) NOT NULL auto_increment,
	`sender_id` int(11) NOT NULL default '0',
	`recp_id` int(11) NOT NULL default '0',
	`subject` varchar(250) NOT NULL default '',
	`sent` varchar(19) default NULL,
	`message` text,
	`notified` char(1) NOT NULL default 'N',
	PRIMARY KEY	(`ID`),
	KEY `recp_id` (`recp_id`),
	KEY `sent` (`sent`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}messages", $res,__LINE__,__FILE__);
    // End messaging table

?>