<?php
if (!function_exists('player_insignia_name')) {
	function player_insignia_name($player_id, $score = -1) 
	{
		global $db, $db_prefix;
		global $l_insignia, $l_insignia_name, $langdir;

		if($score == -1)
		{
			$res = $db->SelectLimit("SELECT score FROM {$db_prefix}players WHERE player_id=$player_id", 1);
			db_op_result($res,__LINE__,__FILE__);

			$player_score = $res->fields['score'];
			$res->close();
		}
		else
		{
			$player_score = $score;
		}

		$i = round((log($player_score / 4000)) / log(1.83 ));

		$i = min($i, 19);

		if ($i < 0 || $player_score < 0)
		{
			$i = 0;
		}

		$player_insignia = array();
		$player_insignia[0] = $l_insignia[$i];
		$player_insignia[1] = $l_insignia_name[$i];
		$player_insignia[2] = $i;
		$player_insignia[3] = $player_id;
		$player_insignia[4] = $score;
		$player_insignia[5] = $player_score;
		$player_insignia[6] = $i;

		if (!isset($player_insignia[0]))
		{
			$player_insignia[0] = end($l_insignia);
			$player_insignia[1] = end($l_insignia_name);
			$player_insignia[2] = 19;
		}

		return $player_insignia;
	}
}
?>
