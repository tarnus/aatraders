<?php
    // Start bounty table
	TextFlush( "Dropping: {$db_prefix}bounty ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}bounty`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}bounty");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}bounty` (
	`bounty_id` int(11) NOT NULL auto_increment,
	`amount` double(32,0) NOT NULL default '0',
	`bounty_on` int(11) NOT NULL default '0',
	`placed_by` int(11) NOT NULL default '0',
	PRIMARY KEY	(`bounty_id`),
	KEY `placed_by` (`placed_by`),
	KEY `bounty_on` (`bounty_on`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}bounty", $res,__LINE__,__FILE__);
    // End bounty table

?>