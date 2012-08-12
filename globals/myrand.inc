<?php
if (!function_exists('myrand')) {
	function myrand($lower, $upper, $distribution_const = 1) // Used for spies.
	{
		$max_random = mt_getrandmax();

		if ($distribution_const == 1)
		{
			return floor($lower + ($upper-$lower+1)*MT_RAND(0,$max_random)/($max_random+1));
		}
		elseif ($distribution_const > 1)
		{
			return floor($lower + ($upper-$lower+1)*POW(MT_RAND(0,$max_random)/($max_random+1),$distribution_const));
		}
		else
		{
			return floor($lower + ($upper-$lower+1)*POW(MT_RAND(1,$max_random)/($max_random+1),$distribution_const));  //it might be 0..$max_random, but for example, POW(0, 0.8) returns error
		}
	}
}
?>
