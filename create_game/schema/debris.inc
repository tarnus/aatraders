<?php
    // Start debris table
	TextFlush( "Dropping: {$db_prefix}debris ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}debris`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}debris ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}debris` (
	`debris_id` bigint(20) NOT NULL auto_increment,
	`debris_type` varchar(100) NOT NULL default '',
	`debris_data` varchar(50) NOT NULL default '',
	`sector_id` int(11) NOT NULL default '0',
	PRIMARY KEY	(`debris_id`),
	KEY `sector_id` (`sector_id`),
	KEY `debris_type` (`debris_type`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}debris", $res,__LINE__,__FILE__);
    // End debris table

?>