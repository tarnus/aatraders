<?php
if (!function_exists('get_sector_bounty_control')) {
	// Check the sector to see who is in control ignoring War Zone Status
	// If a team or player controls the sector they will not get a bounty attacking
	// lower ranked players or planets in the sector.
	// Function returns the team number of the team owning the most planets.
	// When checking if the player doesn't have a team use their player id instead.
	// If the sector can have 5 planets you must own 3 based planets to control it.
	// If the sector can have 4 planets you must own 3 based planets to control it.
	// If the sector can have 3 planets you must own 2 based planets to control it.
	// If the sector can have 2 planets you must own 2 based planets to control it.
	// If the sector can have 1 planets you must own 1 based planets to control it.
	// If the player is the owner of the sector or the player is the fenderation
	// return a 1 for true.  If the player doesn't own the sector return a 0 for false.

	function get_sector_bounty_control($sector){

		global $db, $db_prefix, $playerinfo;

		if($playerinfo['player_id'] == 3) // if Fed ship let the feds do anything
			return 1;

		$res = $db->SelectLimit("SELECT star_size FROM {$db_prefix}universe WHERE sector_id='$sector'", 1);
		db_op_result($res,__LINE__,__FILE__);
		$max_planets = $res->fields['star_size'];
		$res->close();

		$res = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE sector_id='$sector' and base='Y' and use_age=0");
		db_op_result($res,__LINE__,__FILE__);
		$num_planets = $res->RecordCount();

		if($num_planets == 0 or $max_planets == 0)
			return 0;

		$min_bases_to_own =  round(($max_planets+1)/2);
		$totalowners = 0;

		while(!$res->EOF){
			$owners = $res->fields;

			$res2 = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$owners[owner]", 1);
			db_op_result($res,__LINE__,__FILE__);
			$playerteam = $res2->fields['team'];
			$res2->close();

			if($playerteam == 0){
				$ownernumber = $owners['owner'];
			}else{
				$ownernumber = $playerteam;
			}

			if($ownertotal[$ownernumber] == 0){
				$ownerlist[$totalowners] = $ownernumber;
				$totalowners++;
			}
			$ownertotal[$ownernumber]++;
			$res->MoveNext();
		}
		$res->close();

		$selected = 0;
		$selectedcount = 0;
		for($i = 0; $i < $totalowners; $i++){
			$ownernumber = $ownerlist[$i];
			$count = $ownertotal[$ownernumber];
			if($selectedcount < $count){
				$selectedcount = $count;
				if ($selectedcount >= $min_bases_to_own){
					$selected = $ownernumber;
				}
			}
		}

		if($selected == $playerinfo['player_id'] or ($playerinfo['team'] != 0 and $selected == $playerinfo['team']))
			return 1;
		else return 0;
	}
}
?>
