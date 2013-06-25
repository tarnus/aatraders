<?php
    // Start email log table
	TextFlush( "Dropping: {$db_prefix}email_log ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}email_log`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}email_log  ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}email_log` (
	`log_id` int(11) NOT NULL auto_increment,
	`sp_name` varchar(50) NOT NULL default '',
	`sp_IP` varchar(16) NOT NULL default '',
	`dp_name` varchar(50) NOT NULL default '',
	`e_subject` varchar(250) default NULL,
	`e_status` char(1) NOT NULL default 'N',
	`e_type` int(11) NOT NULL default '0',
	`e_stamp` varchar(20) default NULL,
	`e_response` varchar(250) default NULL,
	PRIMARY KEY	(`log_id`),
	KEY `sp_IP` (`sp_IP`),
	KEY `dp_name` (`dp_name`),
	KEY `e_stamp` (`e_stamp`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}email_log", $res,__LINE__,__FILE__);
    // End email log

?>