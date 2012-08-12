<?php
if (!function_exists('get_player')) {
	function get_player($player_id)
	{
		global $db, $db_prefix, $l_unknown;
		if(empty($player_id))
		{
			return $l_unknown;
		}
		$res = $db->SelectLimit("SELECT character_name from {$db_prefix}players where player_id = $player_id", 1);
		db_op_result($res,__LINE__,__FILE__);
		if ($res)
		{
			return $res->fields['character_name'];
		}
		else
		{
			return $l_unknown;
		}
	}
}
?>
