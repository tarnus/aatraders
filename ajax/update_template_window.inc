<?php

get_post_ifset("frame_name, x, y, h, w, visible");

//echo print_r($_GET) . "<hr>";
//echo $gameroot . "templates/" . $templatename . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css\n";

if(is_file($gameroot . "templates/" . $templatename . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css"))
{
	$file_path_read = $gameroot . "templates/" . $templatename . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css";
	$file_path_write = $gameroot . "templates/" . $templatename . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css";
}
else
{
	$file_path_read = $gameroot . "templates/" . $templatename . "player_window_positions/default_window_positions.css";
	$file_path_write = $gameroot . "templates/" . $templatename . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css";
}

$lines = file ($file_path_read);
$count = count($lines);

for($i = 0; $i < $count; $i+=9)
{
//	echo "$i - $frame_name = " . $lines[$i] . "<br>";
//	flush();
	if (strstr($lines[$i], $frame_name))
	{
		$lines[$i + 3] = "	left:" . $x . "px;\n"; // left
		$lines[$i + 4] = "	top:" . $y . "px;\n"; // top
		$lines[$i + 5] = "	width:" . $w . "px;\n"; // width
		$lines[$i + 6] = "	height:" . $h . "px;\n"; // height
		break;
	}
}

$fs = fopen($file_path_write, 'w');
for($i = 0; $i < $count; $i++)
{
	fwrite($fs, $lines[$i]);
}
fclose($fs);
?> 
