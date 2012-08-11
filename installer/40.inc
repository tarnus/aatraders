<?php
// Step 40 - 

//If the file config/config_local.php does not allow writing, admin gets the download form
function docheck($time_error)
{
	global $rawdata, $windowsroot, $windowsserver, $game_number;
?>
 <table bgcolor="#000000" width="667" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
          <td>
<?php
	@include ("config/config_local" . $game_number . ".php");   //Checking just created config file

	$encoded_schedule = ord_crypt_encode("AADATA&admin_password=$_POST[_adminpass]&game_number=$game_number"); 
	if ($gamepath == "/")
	{
		$slash="";
	}
	else
	{
		$slash="/";
	}
	$psuedo_cron = "0,5,10,15,20,25,30,35,40,45,50,55	*	*	*	*	http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule";
	$fs = @fopen('backends/pseudo-cron/cronjobs/crontab.txt', 'w');
	@fwrite($fs, $psuedo_cron);
	@fclose($fs);

	echo "If you are going to run the game on Linux/Unix you need to set up your crontab (if you haven't done it yet). The entry in crontab should look like this:<BR><HR>";
	echo "<font color=\"yellow\">*/$sched_ticks * * * * /usr/bin/wget --tries=1 --timeout=10 --post-data 'admin_password=$_POST[_adminpass]&game_number=$game_number' -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php</font>";
	echo "<HR><BR>";
	echo "or you would like secure access<br><br><HR>";
	echo "<font color=\"yellow\">*/$sched_ticks * * * * /usr/bin/wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule</font>";
	echo "<HR><BR>";
	echo "or use this if the above doesn't work<br><br><HR>";
	echo "<font color=\"yellow\">*/$sched_ticks * * * * /usr/bin/lynx http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule &gt; /dev/null</font>";
	echo "<HR><BR>";

	$windowsroot = str_replace("\\\\", "\\", $windowsroot);
	$data = "0,5,10,15,20,25,30,35,40,45,50,55 * * * * " . $windowsroot . "windows-cron\wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule";
	echo "If you are going to run the game on Windows NT/2000/XP you can use the icronservice.exe in the windows-cron directory.<br>";
	echo "The following information will be placed in a file called windowscron.txt in the config directory: <br><br>";
	echo "<font color=\"yellow\">$data</font><br><br>";
	echo "Make sure the path to the wget program is correct (<font color=\"yellow\">" . $windowsroot . "windows-cron\wget</font>).  If it isn't<br>";
	echo "you will need to edit this file and change the path to reflect where the wget program is located.<br><br>";
	echo "How to use it<br><br>Execute the Command Prompt program in Accessories.<br>CD to the windows-cron directory and install it as a service with:<br><br>";
	echo "icronservice /install /silent<br><br>";
	echo "While the service is installed, start it with:<br><br>";
	echo "example: <font color=\"yellow\">net start icron /filename=" . $windowsroot . "config\windowscron.txt</font><br><br>";
	echo "The filename is the complete path to the windowscron.txt file located in the config directory.<br><br>";
	echo "You should read the icronreadme.txt file located in the windows-cron\SRC\icron directory on how to<br>";
	echo "start the icronservice. An .htaccess file should have been written to the config directory.<br>";
	echo "You need to verify that this has happened.  This will prevent the downloading of your windowscron.txt file.<br><br>";
	$fs = @fopen('config/windowscron.txt', 'w');
	@fwrite($fs, $data);
	@fclose($fs);

	echo "<HR><BR>";
	echo "If you are going to run the game on Windows 98/ME you can use the sinc32.exe in the windows-cron directory.<br>
		Cut the following text and paste it into the sinctab.stf file.<br><br><HR><br>";
	echo "0 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "5 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "10 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "15 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "20 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "25 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "30 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "35 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "40 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "45 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "50 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "55 * * * * wget --tries=1 --timeout=10 -q -o /dev/null -O /dev/null http://" . $_SERVER['HTTP_HOST'] . $gamepath . $slash . "scheduler.php?encoded=$encoded_schedule<br>";
	echo "<HR><BR>";

	$gamebase  = isset($gamebase) ? $gamebase : str_replace("installer.php","",$_SERVER["PATH_TRANSLATED"]);
	if(!is_dir($gamebase."templates_c"))
		echo "You need to create a <font color=\"yellow\"><b>templates_c</b></font> directory in the game directory and set write permissions.<br><br>";

	if (isset($game_installed) && $game_installed == 1 && !$time_error)
	{
		echo "<font color=lime>Local settings successfully saved.</font><BR><BR>";
		echo "If you would like to add more player avatars and team icons check out the download directories at our website. <a href=\"http://www.aatraders.com\" target=\"_blank\">Alien Assault Traders</a><br><br>";
		echo "Everything looks great! Feel free to run the <a href=\"./create_game.php\">Create Universe</a> script now!";
		echo "<BR><BR>If you have already done it, you can login <a href=\"index.php\">here</a>.<BR><BR>";
	}
	else
	{
		echo "<font color=red><B>ERROR:</B><BR>Local settings could <B>NOT</B> be saved to the config directory.</font>";

		echo "<BR><BR><form action=\"installer.php\" target=\"_blank\" method=\"post\" enctype=\"multipart/form-data\"><input type=\"hidden\" name=\"rawdata\" value=\"$rawdata\">";
		echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">";
		echo "<input type=hidden name=\"step\" value=\"40\"><input type=submit value=\"Download\" onclick=\"enablebutton()\"> ";
		echo "the file 'config_local" . $game_number . ".php' and upload it manually to <B>/config</B> subdir (overwrite the current one).<br></form>";
		echo "Once uploaded run the <a href=\"./create_game.php\">Create Universe</a> script.";
		echo "<BR><BR>If you have already done it, you can login <a href=\"index.php\">here</a>.<BR><BR>";
	}
?>
		</td>
	</tr>
</table>
<?php
}

if ($_POST['_dbname'] == '')
{
	echo "
 <table bgcolor=\"#000000\" width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Database name cannot be empty! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
elseif ($_POST['_gamepath'] == '')
{
	echo "
 <table width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Game path cannot be empty! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
elseif ($_POST['_admin_mail'] == '')
{
	echo "
 <table bgcolor=\"#000000\" width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Admin email cannot be empty! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
elseif ($_POST['_adminpass'] == '')
{
	echo "
 <table bgcolor=\"#000000\" width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Admin password cannot be empty! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
elseif ($_POST['_adminpass'] != $_POST['adminpass2'])
{
	echo "
 <table bgcolor=\"#000000\" width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Admin passwords don't match! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
elseif ($_POST['_sched_ticks'] == '')
{
	echo "
 <table bgcolor=\"#000000\" width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Cron interval cannot be empty! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
elseif ($_POST['_gameurl'] == '')
{
	echo "
 <table bgcolor=\"#000000\" width=\"667\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">
  <tr>
          <td><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><B>Game URL cannot be empty! Click <a href=\"installer.php\">here</a>.</B></font></td>
	</tr>
</table>";
}
else
{
	clearstatcache();
	$old_time = @filemtime('config/config_local' . $game_number . '.php');
	//Writing the config file directly
	$fs = @fopen('config/config_local' . $game_number . '.php', 'w');

	$_game_name = stripslashes($_game_name);
	$data = '';
	$data .= "<?\n";
	$data .= "// $_game_name\n\n";
	$data .= "// Automatically created configuration file. Do not change!\n";
	$data .= "\nif (basename(\$_SERVER['PHP_SELF']) == \"config_local" . $game_number . ".php\")";
	$data .= "\n{";
	$data .= "\n  echo \"You can not access this file directly!\";";
	$data .= "\n  die();";
	$data .= "\n}\n";
	foreach($_POST as $key => $value)
	{
		if (AAT_substr($key, 0, 1) == '_' )
		{
			$key = AAT_substr($key, 1);
			$data .= "\$$key = \"" . stripslashes($value) . "\";\n";
		}
	}

	$data .= '$game_installed = "1";' . "\n";
	$data .= '$default_lang = "english"; ' . "\n";

	$data .= "?>\n";
	@fwrite($fs, $data);
	@fclose($fs);
	
	clearstatcache();

	$fs = @fopen('backup/.htaccess', 'w');
	@fwrite($fs, "Deny from all\n");
	@fclose($fs);

	$fs = @fopen('config/.htaccess', 'w');
	@fwrite($fs, "Deny from all\n");
	@fclose($fs);

	$fs = @fopen('support/.htaccess', 'w');
	@fwrite($fs, "Deny from all\n");
	@fclose($fs);

	$new_time = @filemtime('config/config_local' . $game_number . '.php');
	if ($old_time == $new_time)   //The file is not changed automatically -- error
	{
		$rawdata = rawurlencode($data);
		docheck($old_time);
	}
	else
	{
		docheck(0);
	}
}
?>