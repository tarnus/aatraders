<?php
    // Start class_modules_debris table

	TextFlush( "Dropping: {$db_prefix}class_modules_debris ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}class_modules_debris`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}class_modules_debris ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}class_modules_debris` (
	`module_id` int(11) NOT NULL auto_increment,
	`classname` varchar(100) default NULL,
	`success` int(11) NOT NULL default '0',
	`trigger_value` int(11) NOT NULL default '0',
	`autoadd_debris` int(11) NOT NULL default '0',
	`destroyship_debris` int(11) NOT NULL default '0',
	`enable` char(1) NOT NULL default 'Y',
	PRIMARY KEY	(`module_id`),
	KEY `classname` (`classname`),
	KEY `autoadd_debris` (`autoadd_debris`),
	KEY `destroyship_debris` (`destroyship_debris`),
	KEY `enable` (`enable`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}class_modules_debris", $res,__LINE__,__FILE__);
    // End class_modules_commodities table
?>