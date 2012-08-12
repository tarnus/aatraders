<?php
    // Start sessions table
	TextFlush( "Dropping: sessions ");
	$res = $db->Execute("DROP TABLE IF EXISTS `sessions`");
	db_op_result($res,__LINE__,__FILE__);

    TextFlush( "Creating table: sessions ");
	$res = $db->Execute("CREATE TABLE IF NOT EXISTS `sessions` (
  `SessionID` varchar(64) default NULL,
  `session_data` text,
  `expiry` int(11) default NULL,
  `expireref` varchar(64) default '',
  KEY `SessionID` (`SessionID`),
  KEY `expiry` (`expiry`)
) TYPE={$database_type}{$dbencoding}");
    db_op2_result("sessions", $res,__LINE__,__FILE__);
    // End sessions table

?>