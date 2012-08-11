<?php
    // Start news table
	TextFlush( "Dropping: {$db_prefix}news ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}news`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}news ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}news` (
	`news_id` int(11) NOT NULL auto_increment,
	`data` varchar(90) NOT NULL default '',
	`total` int(11) default NULL,
	`user_id` int(11) default NULL,
	`date` datetime default NULL,
	`news_type` varchar(50) default NULL,
	PRIMARY KEY	(`news_id`),
	KEY `date` (`date`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}news", $res,__LINE__,__FILE__);
    // End of news table

?>