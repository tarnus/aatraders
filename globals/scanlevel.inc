<?php
if (!function_exists('scanlevel')) {

	function scanlevel($techlevel){
		global $playerinfo, $shipinfo, $techjammer, $techowner;

		if($playerinfo['player_id'] == $techowner or $techowner == 3)
			return $techlevel;

		$sc_error = SCAN_ERROR($shipinfo['sensors'], $techjammer, $techlevel);
		return $sc_error;
	}
}
?>
