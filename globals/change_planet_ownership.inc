<?php
include ("globals/gen_score.inc");
include ("globals/myrand.inc");

if (!function_exists('change_planet_ownership')) {
	function change_planet_ownership($planet_id, $old_owner, $new_owner = 0)
	{
		global $db;
		global $db_prefix, $gameroot;

		if ($new_owner)
		{
			$spy_object = array();
			$filelist = get_dirlist($gameroot."class/spies/");
			for ($c=0; $c<count($filelist); $c++) {
				if($filelist[$c] != "index.html")
				{
					$spy_classname =  str_replace(".inc", "", $filelist[$c]); 
					if(!class_exists($spy_classname)){
						include ("class/spies/" . $spy_classname . ".inc");
					}

					$store_object = new $spy_classname();
					$job_type = $store_object->id;
					$spy_object[$job_type] = $store_object;
				}
			}

			$result2 = $db->SelectLimit("SELECT cloak FROM {$db_prefix}planets WHERE planet_id=$planet_id", 1);
			db_op_result($result2,__LINE__,__FILE__);
			$planetinfo = $result2->fields;
			$result2->close();

			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET active='N', job_id='0', spy_percent='0.0', spy_cloak=$planetinfo[cloak] WHERE planet_id = $planet_id AND owner_id = $new_owner");
			db_op_result($debug_query,__LINE__,__FILE__);

			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET active='Y' WHERE planet_id = $planet_id AND owner_id <> $new_owner");
			db_op_result($debug_query,__LINE__,__FILE__);

			$r = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE active = 'Y' AND planet_id = $planet_id AND owner_id = $old_owner");
			while (!$r->EOF)
			{
				$spy = $r->fields;
				$resultinfo = $spy_object[array_rand($spy_object)]->change_spy($spy['spy_id'], $planet_id, $spy['move_type']);
				$r->MoveNext();
			}

			gen_score($new_owner);
		}  
		else
		{
			$debug_query = $db->Execute("UPDATE {$db_prefix}spies SET active='N', job_id='0', spy_percent='0.0' WHERE planet_id = $planet_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}

		if ($old_owner) 
		{
			gen_score($old_owner);
		}
	}
}
?>
