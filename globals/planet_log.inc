<?php
if (!function_exists('planet_log')) {
	function planet_log($planet,$owner,$player_id,$action)
	{
		global $db, $db_prefix;
		global $enhanced_logging;
		if ($enhanced_logging)
		{
			$res = $db->SelectLimit("SELECT ip_address from {$db_prefix}players WHERE player_id=$player_id" , 1);
			db_op_result($res,__LINE__,__FILE__);
			$ip_address = $res->fields['ip_address'];
			$res->close();
			$stamp = date("Y-m-d H:i:s");
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}planet_log (planet_id,player_id,owner_id,ip_address,action,time) VALUES ($planet,$player_id,$owner,'$ip_address','$action','$stamp')");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}
}
?>
