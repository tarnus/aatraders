<?php
// Start NPC table

TextFlush("Dropping: {$db_prefix}npc_player ");

$res = $db->Execute("DROP TABLE IF EXISTS `{$db_prefix}npc_player`");
db_op_result($res,__LINE__,__FILE__);

TextFlush( "Creating table: {$db_prefix}npc_player ");
$res = $db->Execute("CREATE TABLE IF NOT EXISTS `{$db_prefix}npc_player` (
	`npc_id` varchar(40) NOT NULL default '',
	`active` char(1) NOT NULL default 'Y',
	`aggression` int(11) NOT NULL default '0',
	`orders` int(11) NOT NULL default '0',
	`experience` int(11) NOT NULL default '0',
	PRIMARY KEY	(`npc_id`)
) TYPE={$database_type}{$dbencoding}");
db_op2_result("{$db_prefix}npc_player", $res,__LINE__,__FILE__);
// End of Alliance table
?>
