<?php
    // Start ibank accounts table
	TextFlush( "Dropping: {$db_prefix}ibank_accounts ");
	$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}ibank_accounts`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: {$db_prefix}ibank_accounts ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}ibank_accounts` (
	`player_id` int(11) NOT NULL auto_increment,
	`balance` bigint(20) NOT NULL default '0',
	`loan` bigint(20) NOT NULL default '0',
	`loantime` datetime default NULL,
	PRIMARY KEY	(`player_id`),
	KEY `balance` (`balance`),
	KEY `loan` (`loan`),
	KEY `loantime` (`loantime`)
) Engine={$database_type}{$dbencoding}");
    db_op2_result("{$db_prefix}ibank_accounts", $res,__LINE__,__FILE__);
    // End of ibank accounts table

?>