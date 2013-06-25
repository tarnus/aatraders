<?php
    // Start admin news table
	TextFlush( "Dropping: {$db_prefix}adminnews ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}adminnews`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}adminnews ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}adminnews` (
	`an_id` int(11) NOT NULL auto_increment,
	`an_text` text,
	PRIMARY KEY	(`an_id`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}adminnews", $res,__LINE__,__FILE__);
    // End admin news table
 
?>