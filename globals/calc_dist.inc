<?php
if (!function_exists('calc_dist')) {
	// Calculate the distance between two sectors.
	// We even run the queries ourselves.
	function calc_dist($src,$dst) 
	{
		global $db, $db_prefix, $enable_spiral_galaxy;
		if ($dst == '' or $src == '')
		{
			return 0;
		}

		$results = $db->SelectLimit("SELECT x,y,z FROM {$db_prefix}universe WHERE sector_id=$src OR sector_id=$dst", 2);
		db_op_result($results,__LINE__,__FILE__);

		// Make sure you check for this when calling this function.
		if (!$results)
		{
			return 0;
		}

		$x = $results->fields['x'];
		$y = $results->fields['y'];
		$z = $results->fields['z'];

		$results->MoveNext();

		$x -= $results->fields['x'];
		$y -= $results->fields['y'];
		$z -= $results->fields['z'];
		$results->close();

		if($enable_spiral_galaxy != 1){
			$x = sqrt(($x*$x) + ($y*$y) + ($z*$z));
		}else{
    		$x = sqrt(pow($x,2.0)+pow($y,2.0)+pow($z,2.0));
		}

		// Make sure it's never less than 1.
		if ($x < 1) 
		{
			return 1;
		}

		return $x;
	}
}
?>
