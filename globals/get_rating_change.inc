<?php
if (!function_exists('get_rating_change')) {
	function get_rating_change($attacker_rating, $defender_rating, $rating_amount, $target_id = 0)
	{
		if ($target_id > 0 && $target_id < 4)
		{
			return 0;
		}
		if($attacker_rating >= 0 && $defender_rating >= 0)
		{
			return -$rating_amount;
		}
		if($attacker_rating >= 0 && $defender_rating < 0)
		{
			return $rating_amount;
		}
		if($attacker_rating < 0 && $defender_rating < 0)
		{
			return $rating_amount;
		}
		if($attacker_rating < 0 && $defender_rating >= 0)
		{
			return -$rating_amount;
		}
	}
}
?>
