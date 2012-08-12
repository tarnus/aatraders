<?
// Include code to be executed when the options_save.php is called.
if(is_file($gameroot . "templates/" . $newtemplate . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css"))
{
	unlink($gameroot . "templates/" . $newtemplate . "player_window_positions/" . $playerinfo['player_id'] . "_window_positions.css");
}
?>