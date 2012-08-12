<?php
// Step 10 - get password to start universe creation
?>
<br><font face="verdana" size="2">
Welcome to the Alien Assault Tradewars Game Creation Program!<br>
This program will create a game based upon the parameters you provide.<br>
A default setup file has been provided and you may change these values to fit your needs.<br>
<br>
We have included what we think are safe ranges for most selections.<br>
If you ignore those ranges default values will be used instead.<br><br>
<hr>
<b><font color="#ff0000">WARNING: If you are resetting an exisiting game all player profiles will be lost.  End of Game player profiles can only be sent when the Admin uses the "Close Game and Send Profiles" selection in the Admin area or by setting a date for the game to end.  If you haven't closed your game using either of these methods you should do so now before resetting the game.</font></b>
<br><br>
<hr>
<?php
$badsetup = 0;
?>
<b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Directory 
                Settings</font></b><br><hr>
<?php
if((bool) is_writable($gameroot ."config"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the Config directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."config</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."config<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."images/avatars/uploads"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the Avatar Upload directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."images/avatars/uploads</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."images/avatars/uploads<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."images/icons/uploads"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the Icon Upload directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."images/icons/uploads</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."images/icons/uploads<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."backup"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the Backup directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."backup</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."backup<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the support directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support/log_data"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the log_data directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."templates_c"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the templates_c directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."templates_c</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."templates_c<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."backends/phpfreechat/data/private/chat"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the chat directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."backends/phpfreechat/data/private/chat</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."backends/phpfreechat/data/private/chat<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."backends/phpfreechat/data/public"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the public directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."backends/phpfreechat/data/public</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."backends/phpfreechat/data/public<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."backends/pseudo-cron/cronjobs"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the cronjobs directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."backends/pseudo-cron/cronjobs</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."pseudo-cron/cronjobs<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

//

if((bool) is_writable($gameroot ."support/log_data/english"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the english directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/english</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/english<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support/log_data/estonian"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the estonian directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/estonian</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/estonian<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support/log_data/french"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the french directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/french</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/french<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support/log_data/german"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the german directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/german</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/german<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support/log_data/italian"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the italian directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/italian</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/italian<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

if((bool) is_writable($gameroot ."support/log_data/spanish"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the spanish directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/spanish</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/spanish<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
	$badsetup++;
}

//

echo"<hr><br>";

if($badsetup == 0)
{
?>
					Select Game to Create: <select name="game_number">
<?php
	$totalgames = 0;
	$gameroot  = isset($gameroot) ? $gameroot : str_replace(basename(__FILE__),"",$_SERVER["PATH_TRANSLATED"]);
	$filelist = get_dirlist($gameroot."config/");
	$newcommands = 0;
	for ($c=0; $c<count($filelist); $c++) { 
		if(strstr($filelist[$c], "config_local")){
			$gamenumber =  str_replace("config_local", "", str_replace(".php", "", $filelist[$c])); 
			$fs = fopen($gameroot."config/".$filelist[$c], "r");
			$items = fgets($fs);
			$items = fgets($fs);
			$gamename = AAT_substr(trim($items), 3);
			fclose($fs);
?>
			<option value="<?=$gamenumber;?>" <?php
			?>>Create: <?=$gamename;?></option>
<?php
			$totalgames++;
		}
	}?>
					</select><br><br>
<?php
	echo "Enter the admin password to begin: <input type=password name=admin_password size=20 maxlength=20>&nbsp;&nbsp;";
	echo "<input type=hidden name=step value=10>";
	echo "<input type=reset value=Reset>";
}
?>