<?php
/**
 * template_lite tpl_create_timestamp function
 *
 * Taken from the original Smarty
 * http://smarty.php.net
 *
 */
function tpl_make_timestamp($string)
{
	if(empty($string)) {
		// use "now":
		$time = time();
	}
	else if (preg_match('/^\d{14}$/', $string))
	{
		// it is mysql timestamp format of YYYYMMDDHHMMSS?			
		$time = mktime(substr($string, 8, 2),substr($string, 10, 2),substr($string, 12, 2),
						substr($string, 4, 2),substr($string, 6, 2),substr($string, 0, 4));
	}
	else if (is_numeric($string))
	{
		// it is a numeric string, we handle it as timestamp
		$time = (int)$string;
	}
	else
	{
		// strtotime should handle it
		$time = strtotime($string);
		if ($time == -1 || $time === false)
		{
			// strtotime() was not able to parse $string, use "now":
			$time = time();
		}
	}
	return $time;
}

?>
