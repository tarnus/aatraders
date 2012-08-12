<?php
if (!function_exists('send_system_im')) {
	function send_system_im($target_id, $subject, $content, $targetonline, $admin = 0)
	{
		global $db, $db_prefix;

		$difftime = (TIME() - strtotime($targetonline)) / 60;

		if ($difftime <= 5 || $admin == 1) 
		{
			$result2 = $db->SelectLimit("SELECT * from {$db_prefix}messages where recp_id = $target_id order by ID DESC", 1);
//			db_op_result($result2,__LINE__,__FILE__);
			$iminfo = $result2->fields;
			$result2->close();

			$timestamp = date("Y-m-d H:i:s");
			if(($iminfo['subject'] != $subject && $iminfo['message'] != $content) || $admin == 1){
				$debug_query = $db->Execute("INSERT INTO {$db_prefix}messages (sender_id, recp_id, sent, subject, message) VALUES " .
											"('0', '" . $target_id . "', '" . $timestamp . "', " .
											$db->qstr($subject) . ", " . $db->qstr($content) . ")");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}
	}
}
?>
