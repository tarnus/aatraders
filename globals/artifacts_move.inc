<?php
if (!function_exists('artifacts_move')) {

	function artifacts_move($planet_id = 0, $player_id = 0, $killer_id = 0)
	{
		global $db, $db_prefix;

		if($planet_id != 0)
		{
			$result4 = $db->Execute("DELETE FROM {$db_prefix}artifacts where on_planet_id=$planet_id");
			db_op_result($result4,__LINE__,__FILE__);
		}
		else
		{
			$pickup_array = array(); // Set to 1 if player can pickup, set to 0 if player can't
			$res = $db->SelectLimit("SELECT score from {$db_prefix}players where player_id = $killer_id", 1);
			db_op_result($res,__LINE__,__FILE__);
			$score = $res->fields['score'];
			$filelist = get_dirlist($gameroot."class/artifacts/");
			for ($c=0; $c<count($filelist); $c++) 
			{
				if($filelist[$c] != "index.html")
				{
					$artifacts_classname = str_replace(".inc", "", $filelist[$c]); 
					if(!class_exists($artifacts_classname)){
						include ("class/artifacts/" . $artifacts_classname . ".inc");
					}
					$artifacts_object = new $artifacts_classname();
					if($artifacts_object->delayedprocess == 0)
					{
						if($artifacts_object->scoremax == 0 || $playerinfo['score'] <= $artifacts_object->scoremax)
						{
							$res = $db->Execute("SELECT count(artifact_id) as total FROM {$db_prefix}artifacts WHERE artifact_type='$artifacts_classname' and player_id=$killer_id");
							db_op_result($res,__LINE__,__FILE__);
							
							if($artifacts_object->pieces == $res->fields['total'])
							{
								$pickup_array[$artifacts_classname] = 0;
							}
							else
							{
								$pickup_array[$artifacts_classname] = 1;
							}
						}
						else
						{
							$pickup_array[$artifacts_classname] = 0;
						}
					}
					else
					{
						$pickup_array[$artifacts_classname] = 0;
					}
		    	}
			}

			$result4 = $db->Execute(" SELECT artifact_id, artifact_type FROM {$db_prefix}artifacts where player_id=$player_id");
			db_op_result($result4,__LINE__,__FILE__);
			while (!$result4->EOF)
			{
				$artifact_id = $result4->fields['artifact_id'];
				$artifacts_classname = $result4->fields['artifact_type'];

				if($pickup_array[$artifacts_classname] == 1 && mt_rand(1, 100) < 50 && $killer_id > 3)
				{
				    $debug_query = $db->Execute("UPDATE {$db_prefix}artifacts SET player_id=$killer_id WHERE artifact_id=$artifact_id"); 
				    db_op_result($debug_query,__LINE__,__FILE__);
					$debug_query->close();
				}
				$result4->MoveNext();
			}
			$result4 = $db->Execute("DELETE FROM {$db_prefix}artifacts where player_id=$player_id");
			db_op_result($result4,__LINE__,__FILE__);
		}
	}
}

?>
