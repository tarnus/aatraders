<?php
// Step 10 - get password
?>
<br><font face="verdana" size="2">
Welcome to the Alien Assault Tradewars Game Installer!<br>
This program will create the initial local game configuration files.<br>
If a master password has not been created you will be asked to create one now.<br>
<br>
<hr>
<?php
$badsetup = 0;
?>
<b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Directory Settings</font></b></b></font>
<br><hr>
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

if((bool) is_writable($gameroot ."support/log_data/russian"))
{
	echo"<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Write permissions are correctly Set for the russian directory</font><br>";
}
else
{
	echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Set <font color=\"yellow\"><b>".$gameroot."support/log_data/russian</b></font> directory write permissions to 0777.<br>IE: chmod 0777 ".$gameroot."support/log_data/russian<br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font><br>";
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

echo "<hr><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><font color=\"#40E0D0\"><b>You need to have your database created, user name and password assigned before you go any further.<b></font><br><font color=\"pink\"><b>YOU MUST DO THIS RIGHT NOW BEFORE GOING ANY FURTHER!</b></font></font>";
echo"<br>";

echo"<hr><br>";

if($badsetup == 0)
{
	$title = "Master Password"; // Enter master password
	$body = "Enter the Master Password to gain access to the installation program.";
	if(!isset($aatrade_master_password) || empty($aatrade_master_password))
	{
		echo "<table><tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Create a new Master Password: </font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is your master password for accessing the<br>installer and should be completely different<br>from the game passwords.</font></td><td valign=\"middle\" nowrap><input type=password name=new_master_password size=20 maxlength=20></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Game root</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the directory path on the server to the game.<br>Do not change this unless you know what you are doing.<br>This program will automatically determine the<br>appropriate path.</font></td><td valign=\"middle\" nowrap><input tabindex=9 type=text size=50 name=_gameroot value=\"$gameroot\"></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<input type=hidden name=step value=1>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database type<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">The game works with MySQL.</font></td>";
		echo "<td valign=\"middle\" nowrap><select tabindex=1 name=db_type>";
		foreach($dbs as $value => $name)
		{
			echo "<option value=$value " . ($v[1] == $value ? 'selected' : '') . ">$name</option>";
		}
		echo "</select></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database name<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the name of your database.<br>You should have created the database before<br>executing the installer.php program. If you haven't<br>created the database you should do so now because<br>the installer will FAIL if the database<br>isn't created before proceeding.</font></font></td><td valign=\"middle\" nowrap><input tabindex=2 type=text name=dbname value=\"\"></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database username</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the username for accessing the database.</font></td><td valign=\"middle\" nowrap><input tabindex=3 type=text name=dbuname value=\"\"></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database password<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the password for the database.</font></font></td><td valign=\"middle\" nowrap><input tabindex=4 type=password name=dbpass value=\"\"></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database host</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">If the database is on the same server the game<br>is running use <b>localhost</b> else enter the IP<br>address for the database server.</font></td><td valign=\"middle\" nowrap><input tabindex=5 type=text name=dbhost value=\"localhost\"></td></tr>";
		echo "<tr><td nowrap>&nbsp;</td><td valign=\"middle\" nowrap>&nbsp;</td></tr>";
		echo "<tr><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database port</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">Leave this blank unless you know what you are doing.<br>Most Mysql databases do not need the port designated.</font></td><td valign=\"middle\" nowrap><input size=3 tabindex=6 type=text name=dbport value=\"\"></td></tr>";
		echo "</table>";
	}
	else
	{
		echo "<table><tr onMouseover=\"ddrivetip('$title', '$body');\" onMouseout=\"hideddrivetip()\"><td nowrap><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Enter the Master Password: </font></td><td valign=\"middle\" nowrap><input type=password name=master_password size=20 maxlength=20></td></tr>";
		echo "</table>";
		echo "<input type=hidden name=step value=10>";
	}
}
echo "<input type=submit value=Continue><br><br>";
?>