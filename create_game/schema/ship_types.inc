<?php
    // Start ship types table

	TextFlush( "Dropping: {$db_prefix}ship_types ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ship_types`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ship_types ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ship_types` (
	`type_id` int(11) NOT NULL default '1',
	`name` varchar(20) default NULL,
	`image` varchar(20) default NULL,
	`description` varchar(255) default NULL,
	`buyable` char(1) NOT NULL default 'Y',
	`cost_ore` bigint(20) NOT NULL default '0',
	`cost_goods` bigint(20) NOT NULL default '0',
	`cost_energy` bigint(20) NOT NULL default '0',
	`cost_organics` bigint(20) NOT NULL default '0',
	`cost_tobuild` bigint(20) NOT NULL default '0',
	`turnstobuild` int(11) NOT NULL default '0',
	`basehull` int(11) NOT NULL default '0',
	`minhull` int(11) NOT NULL default '0',
	`maxhull` int(11) NOT NULL default '0',
	`minengines` int(11) NOT NULL default '0',
	`maxengines` int(11) NOT NULL default '0',
	`minpower` int(11) NOT NULL default '0',
	`maxpower` int(11) NOT NULL default '0',
	`minfighter` int(11) NOT NULL default '0',
	`maxfighter` int(11) NOT NULL default '0',
	`minsensors` int(11) NOT NULL default '0',
	`maxsensors` int(11) NOT NULL default '0',
	`minbeams` int(11) NOT NULL default '0',
	`maxbeams` int(11) NOT NULL default '0',
	`mintorp_launchers` int(11) NOT NULL default '0',
	`maxtorp_launchers` int(11) NOT NULL default '0',
	`minshields` int(11) NOT NULL default '0',
	`maxshields` int(11) NOT NULL default '0',
	`minarmor` int(11) NOT NULL default '0',
	`maxarmor` int(11) NOT NULL default '0',
	`mincloak` int(11) NOT NULL default '0',
	`maxcloak` int(11) NOT NULL default '0',
	`minecm` int(11) NOT NULL default '0',
	`maxecm` int(11) NOT NULL default '0',
	PRIMARY KEY	(`type_id`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ship_types", $res,__LINE__,__FILE__);

    // End ship types table

?>