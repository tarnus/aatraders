<?php
if (!function_exists('MakeBars')) {

	function MakeBars($level, $max, $dialtype, $full_image = 0)
	{
		global $l_n_a, $templatename;

		$heath = ($level / max(max($max, 1), $level));
		$heath_bars = round($heath * 10);

		if($full_image == 0)
		{
			$img = '';

			for ($i=0; $i<$heath_bars; $i++)
			{
				if($i < 10)
				{
					$img .= "<img src=templates/".$templatename."images/". $dialtype . "on$i.png>";
				}
				else
				{
					$img .= "<img src=templates/".$templatename."images/". $dialtype . "on9.png>";
				}
			}

			for ($i=0; $i<(10-$heath_bars); $i++)
			{
				$img .= "<img src=templates/".$templatename."images/". $dialtype . "off.png>";
			}

			if ($img == '')
			{
				$img = "<font size=2><b>$l_n_a</b></font>";
			}
		}
		else
		{
			$img .= "<img src=templates/".$templatename."images/". $dialtype . $health_bars . ".png>";
		}

		return $img;
	}
}
?>
