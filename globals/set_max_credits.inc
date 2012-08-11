<?php
if (!function_exists('set_max_credits')) {
	function set_max_credits($planet_id){
		global $db, $db_prefix, $planet_credit_multi, $base_credits;

		$debug_query = $db->SelectLimit("SELECT * from {$db_prefix}planets WHERE planet_id = $planet_id", 1);
		db_op_result($debug_query,__LINE__,__FILE__);
		$planetinfo = $debug_query->fields;
		$debug_query->close();

		$max_credits = phpMaxCreditsDelta($planetinfo['fighter'], 0) + phpMaxCreditsDelta($planetinfo['sensors'], 0) + phpMaxCreditsDelta($planetinfo['beams'], 0) + phpMaxCreditsDelta($planetinfo['torp_launchers'], 0) + phpMaxCreditsDelta($planetinfo['shields'], 0) + phpMaxCreditsDelta($planetinfo['jammer'], 0) + phpMaxCreditsDelta($planetinfo['cloak'], 0);
		$max_credits = ($max_credits * $planet_credit_multi) + $base_credits;
		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET max_credits=$max_credits WHERE planet_id=$planet_id");
	}
}
?>
