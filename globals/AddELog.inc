<?php
if (!function_exists('AddELog')) {

	function AddELog($d_user,$e_type,$e_status,$e_subject,$e_response)
	{
		global $username, $ip, $db_prefix, $db;

		$result = $db->SelectLimit("SELECT * from {$db_prefix}players LEFT JOIN {$db_prefix}ships " .
							   "ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE email='$username'", 1);
		$playerinfo = $result->fields;
		$result->close();

		$result2 = $db->SelectLimit("SELECT * from {$db_prefix}players LEFT JOIN {$db_prefix}ships " .
								"ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id WHERE email='$d_user'", 1);
		$targetinfo = $result2->fields;
		$result2->close();

		if ($e_type == 0) // For Normal Email, For Future Use.
		{
			$sp_id = $playerinfo['ship_id'];
			$sp_name = $playerinfo['character_name'];
			$sp_IP = $playerinfo['ip_address'];
			$dp_id = $targetinfo['ship_id'];
			$dp_name = $targetinfo['character_name'];
		}
		elseif ($e_type == 1) // For when users Register.
		{
			$sp_id = -1;
			$sp_name = "Not Logged In";
			$sp_IP = $ip;
			$dp_id = $targetinfo['ship_id'];
			$dp_name = $targetinfo['email'];
		}
		elseif ($e_type == 2) // For when users Send Feedback.
		{
			$sp_id = $playerinfo['ship_id'];
			$sp_name = $playerinfo['character_name'];
			$sp_IP = $playerinfo['ip_address'];
			$dp_id = $targetinfo['ship_id'];
			$dp_name = $targetinfo['character_name'];
		}
		elseif ($e_type == 3) // For when users Request Password.
		{
			$sp_id = -1;
			$sp_name = "Not Logged In";
			$sp_IP = $ip;
			$dp_id = $targetinfo['ship_id'];
			$dp_name = $targetinfo['email'];
		}
		elseif ($e_type == 4) // For when user fails login.
		{
			$sp_id = -1;
			$sp_name = "Not Logged In";
			$sp_IP = $ip;
			$dp_id = $targetinfo['ship_id'];
			$dp_name = $targetinfo['email'];
		}
		elseif ($e_type == 5) // For sending Global Email to all registered players
		{
			$sp_id = -1;
			$sp_name = "GameAdmin";
			$sp_IP = $ip;
			$dp_id = $targetinfo['ship_id'];
			$dp_name = $d_user;
		}

		$e_stamp = date("Y-m-d H:i:s");
		$dp_name = htmlspecialchars($dp_name,ENT_QUOTES);
		$sp_name = htmlspecialchars($sp_name,ENT_QUOTES);
		$e_subject = htmlspecialchars($e_subject,ENT_QUOTES);

		$debug_query = $db->Execute("INSERT INTO {$db_prefix}email_log VALUES('','$sp_name','$sp_IP','$dp_name','$e_subject','$e_status','$e_type','$e_stamp','$e_response')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}
?>
