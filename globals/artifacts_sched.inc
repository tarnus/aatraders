<?php
if (!function_exists('artifacts_sched')) {

	function artifacts_sched($artifact_type, $min_cloak, $max_cloak, $scoremax, $piece)
	{
		global $db, $db_prefix, $sector_list_count, $sector_list_array, $planet_list_count, $planet_list_array;

		$cloak = mt_rand($min_cloak, $max_cloak);
		$on_planet_id = 0;
   		$on_port = 0;

		if(mt_rand(1, 100) < 50)
		{
			$randplay=mt_rand(0,($planet_list_count-1));
			$sector_id = $planet_list_array[$randplay]['sector_id'];
			$on_planet_id = $planet_list_array[$randplay]['planet_id'];
			$result4 = $db->Execute(" SELECT artifact_id FROM {$db_prefix}artifacts where on_planet_id=$on_planet_id");
			db_op_result($result4,__LINE__,__FILE__);
			if($result4->RecordCount() > 0)
			{
				$on_planet_id = 0;
   				$on_port = 0;
   			}
		}

		if($on_planet_id == 0)
		{
			$randplay=mt_rand(0,($sector_list_count-1));
			$sector_id = $sector_list_array[$randplay]['sector_id'];
			$res = $db->Execute("SELECT port_type FROM {$db_prefix}universe WHERE sector_id=$sector_id");
	   		db_op_result($res,__LINE__,__FILE__);
   			if($res->fields['port_type'] != "none")
   			{
	   			$on_port = 1;
   			}
   			else
	   		{
				$res = $db->SelectLimit("SELECT planet_id FROM {$db_prefix}planets WHERE sector_id='$sector_id'", 5);
    			db_op_result($res,__LINE__,__FILE__);
				while (!$res->EOF)
				{
					$on_planet_id = $res->fields['planet_id'];
					if(mt_rand(1, 100) < 70)
					{
						$on_planet_id = $res->fields['planet_id'];
					}
					$res->MoveNext();
				}
	   		}
		}
	    $debug_query = $db->Execute("INSERT INTO {$db_prefix}artifacts (artifact_type, artifact_piece, on_port, on_planet_id, sector_id, cloak, scoremax) 
    								values 
    								('$artifact_type','$piece', $on_port, $on_planet_id, $sector_id, $cloak, " .  $scoremax . ")");
   		db_op_result($debug_query,__LINE__,__FILE__);
		$debug_query->close();
	}
}

?>
