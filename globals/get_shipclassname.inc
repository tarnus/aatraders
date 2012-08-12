<?php
if (!function_exists('get_shipclassname')) {
	function get_shipclassname($ship_class_id)
	{
		global $db, $db_prefix, $l_unknown;

		if(empty($ship_class_id))
		{
			return $l_unknown;
		}

		$res = $db->SelectLimit("SELECT name from {$db_prefix}ship_types WHERE type_id = $ship_class_id", 1);
		db_op_result($res,__LINE__,__FILE__);
		if ($res)
		{
			return $res->fields['name'];
		}
		else
		{
			return $l_unknown;
		}
	}
}
?>
