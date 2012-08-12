<?php
if (!function_exists('isLoanPending')) {
	function isLoanPending($player_id)
	{
    	global $db, $db_prefix, $igb_lrate;

		$unixstamp = time();
	    $debug_query = $db->Execute("SELECT loan, loantime from {$db_prefix}ibank_accounts WHERE player_id=$player_id and (loan != 0) and ((($unixstamp - UNIX_TIMESTAMP(loantime)) / 60) > $igb_lrate) ");
    	db_op_result($debug_query,__LINE__,__FILE__);
	    if (!$debug_query->EOF)
    	{
        	return true;
    	}
	    else
    	{
        	return false;
    	}
	}
}
?>
