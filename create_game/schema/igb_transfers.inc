<?php
    // Start ibank transfers table
	TextFlush( "Dropping: {$db_prefix}igb_transfers ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}igb_transfers`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}igb_transfers ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}igb_transfers` (
	`transfer_id` int(11) NOT NULL auto_increment,
	`source_id` int(11) NOT NULL default '0',
	`dest_id` int(11) NOT NULL default '0',
	`time` datetime default NULL,
	PRIMARY KEY	(`transfer_id`),
	KEY `source_id` (`source_id`),
	KEY `dest_id` (`dest_id`),
	KEY `time` (`time`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}igb_transfers", $res,__LINE__,__FILE__);
    // End of ibank accounts table

?>