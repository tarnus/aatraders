<?php
	// Start smilies table
	TextFlush( "Dropping: {$db_prefix}smilies ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}smilies`");
	db_op_result($res,__LINE__,__FILE__);

	TextFlush( "Creating table: {$db_prefix}smilies ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}smilies` (
  `smilies_id` smallint(5) unsigned NOT NULL auto_increment,
  `code` varchar(50) default NULL,
  `smile_image` varchar(100) default NULL,
  `emoticon` varchar(75) default NULL,
  PRIMARY KEY  (`smilies_id`)
) Engine={$database_type}{$dbencoding}");
	db_op2_result("{$db_prefix}smilies", $res,__LINE__,__FILE__);

	// End smilies table
?>