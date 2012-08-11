<?php
if((!isset($_SESSION['session_player_id'])) && $create_game != 1)
{
	session_start();
}


	require_once "backends/phpfreechat/src/phpfreechat.class.php";
	$params=array();
	$params["nick"]=$_SESSION['character_name'];
	$params["frozen_nick"]=true;
	$params["title"]=$_SESSION['game_name'];
	$params["timeout"]=3600000;
	$params["theme"]="blune";
	$params["serverid"]=$_SESSION['session_player_id'];
	$params["channel"]=$_SESSION['game_name'];
	$params["height"]="175px";
	$params["max_nick_len"]=25;
	$params["quit_on_closedwindow"]=true;
	$params["focus_on_connect"]=false;
	switch($_SESSION['langdir'])
	{
		case"estonian":
			$params["language"]="en_US";
		break;

		case"french":
			$params["language"]="fr_FR";
		break;

		case"german":
			$params["language"]="de_DE-informal";
		break;

		case"italian":
			$params["language"]="it_IT";
		break;

		case"russian":
			$params["language"]="ru_RU";
		break;

		case"spanish":
			$params["language"]="es_ES";
		break;

		default:
			$params["language"]="en_US";
		break;
	}
	$chat=new phpFreeChat($params);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTDXHTML1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html;charset=utf-8" />
<title>phpFreeChat sources index</title>
<?php $chat->printJavascript();?>
<?php $chat->printStyle();?>
</head>

<body onload="self.focus();">
<?php $chat->printChat();?>
</body>
</html>
 