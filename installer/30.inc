<?php
// Step 30 - 
?>
<script language="JavaScript" type="text/javascript">
	function checkform ( form )
	{
	  // ** START **
	  if (form._dbname.value == "") {
			alert("Database name cannot be empty!");
	    form._dbname.focus();
	    return false ;
	  }

	  if (form._gamepath.value == "") {
			alert("Game path cannot be empty!");
	    form._gamepath.focus();
	    return false ;
	  }

	  if (form._admin_mail.value == "") {
			alert("Admin email cannot be empty!");
	    form._admin_mail.focus();
	    return false ;
	  }

	  if (form._adminpass.value == "") {
			alert("Admin password cannot be empty!");
	    form._adminpass.focus();
	    return false ;
	  }

	  if (form._sched_ticks.value == "") {
			alert("Cron interval cannot be empty!");
	    form._sched_ticks.focus();
	    return false ;
	  }

	  if (form._gameurl.value == "") {
			alert("Game URL cannot be empty!");
	    form._gameurl.focus();
	    return false ;
	  }

	  if (form._adminpass.value != form.adminpass2.value) {
			alert("Admin passwords don't match!");
	    form._adminpass.focus();
	    return false ;
	  }

  // ** END **
  return true ;
}

	function validatestart()
	{
		if (document.forms[0].dbuname.value == "" && document.forms[0].dbhost.value != "localhost")
		{
			alert("Database username cannot be empty!");
			return false;
		}
		if (document.forms[0].dbpass.value == "" && document.forms[0].dbhost.value != "localhost")
		{
			alert("Database password cannot be empty!");
			return false;
		}
		document.forms[0].submit();
	}
	
</script>
<?php
$showit = 1;
define('TEMPLATE_CLASS', $gameroot. "backends/template_lite/src/class.template.php");  // Because config.php is not installed yet...

$template_object_exists = file_exists(TEMPLATE_CLASS);

function check_php_version () {
	global $dbhost, $dbport, $dbuname, $dbpass, $yourphpversion;
	$testSplit = explode ('.', '4.3.0');
	$currentSplit = explode ('.', phpversion());
	$yourphpversion = phpversion();

	if ($testSplit[0] < $currentSplit[0])
	{
		$yourphpversion .= " - <font color=lime><b>GREAT</b> Version - Best versions are 4.3.9 or higher</font>";
		return True;
	}
	if ($testSplit[0] == $currentSplit[0])
	{
		if ($testSplit[1] < $currentSplit[1])
		{
			$yourphpversion .= " - <font color=lime><b>GREAT</b> Version - Best versions are 4.3.9 or higher</font>";
			return True;
		}
		if ($testSplit[1] == $currentSplit[1])
		{
			if ($currentSplit[2] >= 9)
			{
				$yourphpversion .= " - <font color=lime><b>GREAT</b> Version - Best versions are 4.3.9 or higher</font>";
				return True;
			}
			if ($testSplit[2] <= $currentSplit[2])
			{
				$yourphpversion .= " - <font color=lime>GOOD Version - Best versions are 4.3.9 or higher</font>";
				return True;
			}
		}
	}
	$yourphpversion .= " - <font color=red>Too Old upgrade PHP to 4.3.0 or higher (Best versions are 4.3.9 or higher).</font>";
	return False;
}

function check_mysql_version () {
	global $dbhost, $dbport, $dbuname, $dbpass, $version;

	if($dbhost == "localhost")
	{
		$version = @mysql_get_client_info();
		$versioncheck = AAT_ereg_replace("[^0-9.]","", $version);
		$currentSplit = explode ('.', $versioncheck);
	}
	else
	{
		$link = mysql_connect($dbhost, $dbuname, $dbpass);
		if (!$link) {
			die('Could not connect: ' . mysql_error());
		}
		$version = @mysql_get_server_info();
		$versioncheck = AAT_ereg_replace("[^0-9.]","", $version);
		$currentSplit = explode ('.', $versioncheck);
	}

	$testSplit = explode ('.', '4.1.0');

	if ($testSplit[0] < $currentSplit[0])
	{
		$version .= " - <font color=lime>GOOD Version</font>";
    	return True;
	}

	if ($testSplit[0] == $currentSplit[0])
	{
		if ($testSplit[1] < $currentSplit[1])
		{
			$version .= " - <font color=lime>GOOD Version</font>";
			return True;
		}
		if ($testSplit[1] == $currentSplit[1])
		{
			if ($testSplit[2] <= $currentSplit[2])
			{
				$version .= " - <font color=lime>GOOD Version</font>";
				return True;
			}
		}
	}
	$version .= " - <font color=red>Too Old upgrade MySql</font>";
	return False;
}

function getConIP() {
	if (isset($_SERVER["HTTP_X_FORWARDED_FOR"]))
	{ 
		return $_SERVER["HTTP_X_FORWARDED_FOR"];
	}
	else
	{
		return $_SERVER["REMOTE_ADDR"];
	}
}

function TRUEFALSE($truefalse,$Stat,$True,$False){
	return(($truefalse == $Stat) ? $True : $False);
}

function md5_filecheck ($ini_file)
{
	global $gameroot;
?>
 <table width="667" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
     <td>
<?php
	echo "<b>Scanning Game Files: </b><br>\n";
	flush();
	$lines = @file ($ini_file);
	$good_md5 = true;
	for($i = 0; $i < count($lines); $i++){
		$variable = explode("=", trim($lines[$i]));
		$variable[0] = trim($variable[0]);
		$variable[1] = trim($variable[1]);

		if(AAT_eregi('^[-!#$%&\'*+\\./0-9=?A-Z^_`{|}~]+', trim($lines[$i])))
		{
			if(is_file($gameroot . $variable[0]))
			{
			   	if($variable[1] != @md5_file($gameroot . $variable[0]))
				{
					echo "<font color=00ff00><b>" . $variable[0] . "</b></font> - <font color=pink><b>WRONG CHECKSUM</font> - <font color=cyan>File has changed and game may not function correctly.</b></font><br>";
					flush();
				}
			}
			else
			{
				echo "<font color=00ff00><b>" . $variable[0] . "</b></font> - <font color=pink><b>MISSING FILE</font> - <font color=yellow>You must install this file before you can complete the install.</b></font><br>";
				flush();
				$good_md5 = false;
			}
		}
	}
?>
    </td>
  </tr>
</table>
<?php
	return $good_md5;
}

if(!is_file("config/config_local" . $game_number . ".php") && $set_db != 1)
{
?>

<table width="667" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
      <td>
        <table bgcolor="#000000" width="80%" border="1" cellspacing="0" cellpadding="0" align="center">
          <tr>
            <td>
              <div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Database Server Location for Game Number <?php echo $game_number; ?></font></b></div>
            </td>
          </tr>
          <tr>
            <td>
              <table width="100%" border="1" cellspacing="0" cellpadding="3">
<?php
if($game_number == 0)
{
	$dbhost = $ADODB_SESSION_CONNECT;
	$dbuname = $ADODB_SESSION_USER;
	$dbpass = $ADODB_SESSION_PWD;
	$dbport = $ADODB_SESSION_PORT;
}
else
{
	$dbhost = "localhost";
	$dbuname = '';
	$dbpass = '';
	$dbport = '';
}
		echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database username</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the username for accessing the database.</font></td><td valign=\"middle\" ><input tabindex=3 type=text name=dbuname value=\"$dbuname\"></td></tr>";
		echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database password<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the password for the database.</font></font></td><td valign=\"middle\" ><input tabindex=4 type=password name=dbpass value=\"$dbpass\"></td></tr>";
		echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database host</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">If the database is on the same server the game<br>is running use <b>localhost</b> else enter the IP<br>address for the database server.</font></td><td valign=\"middle\" ><input tabindex=5 type=text name=dbhost value=\"$dbhost\"></td></tr>";
		echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database port</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">Leave this blank unless you know what you are doing.<br>Most Mysql databases do not need the port designated.</font></td><td valign=\"middle\" ><input size=3 tabindex=6 type=text name=dbport value=\"$dbport\"></td></tr>";

			?>
                </table>
</td></tr>
  <tr> 
      <td colspan="2"> 
        <div align="center"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><br><br>
		<input type="hidden" name="game_number" value="<?=$game_number;?>">
		<input type="hidden" name="step" value="20">
		<input type="hidden" name="set_db" value="1">
          <input tabindex=19 type="button" value="Submit" onclick="validatestart()">
		  </font>
        </div>
      </td>
    </tr>
</table>
</td>
</tr>
</table>
<?php
}
else
{
	@include ("config/config_local" . $game_number . ".php");
	$sf = @ini_get("safe_mode");
	$allow_url_fopen = @ini_get("allow_url_fopen"); // should equal 1
	$mqg = @ini_get("magic_quotes_gpc");
	$register_globals = @ini_get("register_globals");
	$adodb_exists = file_exists($gameroot . "backends/adodb_lite/adodb.inc.php");
	include ($gameroot . "backends/adodb_lite/adodb.inc.php");

	$is_curl = function_exists('curl_init');

	$mbstring_supported = 0;

	if (@extension_loaded('mbstring'))
	{
		$mbstring_supported = 1;
	}

	if (strnatcmp($versioncheck, '4.2.3') == 1)
	{
		$mbstring_supported = 0;
	}

	$bad_config = '0';

	$SERVER_SOFTWARE = $_SERVER["SERVER_SOFTWARE"];
	$GATEWAY_ADDR = $_SERVER["REMOTE_ADDR"];
	$LOCAL_ADDR = getConIP();

	$pos=AAT_strpos(getConIP(),",");
	$REMOTE_ADDR=$LOCAL_ADDR;
	if(is_integer($pos))
	{
		$GATEWAY_ADDR=AAT_substr($LOCAL_ADDR,$pos+1);
		$LOCAL_ADDR=AAT_substr($LOCAL_ADDR,0,$pos);
	}

	if (function_exists('zend_version'))
		$Zend_Version = zend_version();

	$SERVER_ADDR = $_SERVER["SERVER_ADDR"];
	$SERVER_PORT = $_SERVER["SERVER_PORT"];
	$REMOTE_PORT = $_SERVER["REMOTE_PORT"];

	if (function_exists('php_sapi_name'))
	{
		$sapi_type = php_sapi_name();
		if (preg_match ("/cgi/", $sapi_type)) $PHP_Interface = "CGI PHP";
		else if (preg_match ("/apache/", $sapi_type)) $PHP_Interface = "mod_PHP";
		else $PHP_Interface = "Unknown ($sapi_type)";
	}
	else
	{
		$PHP_Interface = "Unknown (Function Not found.)";
	}

	if (function_exists('gd_info'))
		$gd_array = gd_info();

	$PHP_VERSION = PHP_VERSION;
	if (is_integer(AAT_strpos($SERVER_SOFTWARE, "Apache")))
		$PlatOS = "Apache"; else $PlatOS = "IIS";

	$ar = AAT_split("[/ ]",$_SERVER['SERVER_SOFTWARE']);
	for ($i=0;$i<(count($ar));$i++){
		switch(AAT_strtoupper($ar[$i])){
			case 'APACHE': $i++;if(empty($APACHE_VERSION)) $APACHE_VERSION = $ar[$i];break;
			case 'PHP': $i++;if(empty($PHP_VERSION)) $PHP_VERSION = $ar[$i];break;
			case 'MOD_SSL':$i++;if(empty($MOD_SSL_VERSION)) $MOD_SSL_VERSION = $ar[$i];break;
			case 'OPENSSL':$i++;if(empty($OPENSSL_VERSION)) $OPENSSL_VERSION = $ar[$i];break;
		}
	}

	if(function_exists('php_uname'))
		$php_sapi =php_uname();
	if(function_exists('apache_get_version'))
		$apache_version =apache_get_version();

	$Spos = AAT_strpos($SERVER_SOFTWARE, "(")+1; 
	$Epos = AAT_strpos($SERVER_SOFTWARE, ")",(int)$Spos);

	if (is_integer($Spos) && is_integer($Epos)) {
		$Lpos = $Epos-$Spos; $Platform = AAT_substr($SERVER_SOFTWARE, $Spos, $Lpos);
		if($Platform=="Win32") {
			$OS_TYPE = "Windows";
			if (function_exists('exec'))
				$OS_TYPE = exec("ver");}
		Else If($Platform=="Red Hat Linux"||$Platform=="Unix"||$Platform=="UNIX") 
			$OS_TYPE = "Linux / Unix";
		Else If($Platform=="Gentoo/Linux")
			$OS_TYPE = "Gentoo Linux";
		Else 
			$OS_TYPE = "Unknown OS [<B>Tell Author to add Platform = $Platform</B>]"; 
	}
?>

<table width="667" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
      <td>
        <table bgcolor="#000000" width="100%" border="1" cellspacing="0" cellpadding="0" align="center">
          <tr>
            <td>
              <div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Server 
                Settings</font></b></div>
            </td>
          </tr>
          <tr>
            <td>
              <table width="100%" border="1" cellspacing="0" cellpadding="3">
                <?php
$leftside = "";
$rightside = "";
	if(!empty($php_sapi)){
		echo "<tr><td valign=\"middle\" nowrap><b>System</b></td><td valign=\"top\" ><font color=yellow><b>".$php_sapi."</b></font></td></tr>\n";
	}
	if(!empty($OS_TYPE)){
		echo "<tr><td valign=\"middle\" nowrap><b>Operating System</b></td><td valign=\"top\" ><font color=yellow><b>".$OS_TYPE."</b></font></td></tr>\n";
	}
	if(defined('PHP_OS')){
		echo "<tr><td valign=\"middle\" nowrap><b>OS Type</b></td><td valign=\"top\" ><font color=yellow><b>".PHP_OS."</b></font></td></tr>\n";
	}
	if(!empty($PlatOS)){
		echo "<tr><td valign=\"middle\" nowrap><b>Platform System</b></td><td valign=\"top\" ><font color=yellow><b>".$PlatOS."</b></font></td></tr>\n";
	}
	if(!empty($APACHE_VERSION)){
		echo "<tr><td valign=\"middle\" nowrap><b>Apache Version</b></td><td valign=\"top\" ><font color=yellow><b>".$APACHE_VERSION."</b></font></td></tr>\n";
	}
	if(!empty($Zend_Version)){
		echo "<tr><td valign=\"middle\" nowrap><b>Zend Version</b></td><td valign=\"top\" ><font color=yellow><b>".$Zend_Version."</b></font></td></tr>\n";
	}

	check_php_version ();
	echo "<tr><td valign=\"middle\" nowrap><b>PHP Version (4.3.0 or higher needed)</b></td><td valign=\"top\" ><font color=yellow><b>" . $yourphpversion . "</b></font></td></tr>\n";

	check_mysql_version ();
	echo "<tr><td valign=\"middle\" nowrap><b>MySql Version (4.1.0 or higher needed)</b></td><td valign=\"top\" ><font color=yellow><b>". $version ."</b></font></td></tr>\n";

	if(!empty($PHP_Interface)){
		echo "<tr><td valign=\"middle\" nowrap><b>PHP Interface</b></td><td valign=\"top\" ><font color=yellow><b>".$PHP_Interface."</b></font></td></tr>\n";
	}
	echo "<tr><td valign=\"middle\" nowrap><b>Adodb Lite Installed</b></td><td valign=\"top\" >".(($adodb_exists == 1) ? "<font color=00ff00><b>Yes</b></font>" : "<font color=pink><b>No - AATrade needs Adodb installed.</b></font>")."</td></tr>\n";
	if($adodb_exists == 1){
		if(empty($ADODB_vers))
			$ADODB_vers = "4.53";
		if(!empty($ADODB_vers)){
			echo "<tr><td valign=\"middle\" nowrap><b>Adodb Lite Version</b></td><td valign=\"top\" ><font color=yellow><b>".$ADODB_vers."</b></font></td></tr>\n";
		}
	}

	echo "<tr><td valign=\"middle\" nowrap><b>Template Lite Installed</b></td><td valign=\"top\" >".(($template_object_exists == 1) ? "<font color=00ff00><b>Yes</b></font>" : "<font color=pink><b>No - AATrade needs Template Lite installed.</b></font>")."</td></tr>\n";
	if($template_object_exists == 1){
		require_once (TEMPLATE_CLASS);
		$template_object = new Template_Lite;
		$template_object->template_dir = "./templates/";
		$template_object->compile_dir = "./templates_c/";
		$template_object->left_tag = "{";
		$template_object->right_tag = "}";
		$template_object->encode_file_name = 0;
		$template_object->assign("version", $template_object->_version);
		$template_object->send_now = 0;
		$template_object->display("admin/templateversion.tpl");
	}

	echo "<tr><td valign=\"middle\" nowrap><b>Zend Optimizer Installed</b></td><td valign=\"top\" >".(($is_zend_optimizer) ? "<font color=00ff00><b>Yes</b></font>" : "<font color=pink><b>No - AATrade will run faster and use less CPU if <a href=\"http://www.zend.com/store/products/zend-optimizer.php\">Zend Optimizer</a> is installed.</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>MMCache Installed</b></td><td valign=\"top\" >".((function_exists("mmcache")) ? "<font color=00ff00><b>Yes - do not install eAccelerator</b></font>" : "<font color=pink><b>No - AATrade will run faster and use less CPU if <a href=\"http://turck-mmcache.sourceforge.net/index_old.html\">MMCache</a> is installed.  PHP 4 Only</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>eAccelerator Installed</b></td><td valign=\"top\" >".((function_exists("eaccelerator")) ? "<font color=00ff00><b>Yes - do not install MMCache</b></font>" : "<font color=pink><b>No - AATrade will run faster and use less CPU if <a href=\"http://sourceforge.net/projects/eaccelerator/\">eAccelerator</a> is installed.  PHP 4/5 Only</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>GD Version</b></td><td valign=\"top\" ><font color=yellow><b>".$gd_array['GD Version']."</b></font></td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>JPG Support</b></td><td valign=\"top\" >".TRUEFALSE($gd_array['JPG Support'],True,"<font color=00ff00><b>Enabled</b></font>","<font color=pink><b>Disabled</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>PNG Support</b></td><td valign=\"top\" >".TRUEFALSE($gd_array['PNG Support'],True,"<font color=00ff00><b>Enabled</b></font>","<font color=pink><b>Disabled</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>GIF Read Support</b></td><td valign=\"top\" >".TRUEFALSE($gd_array['GIF Read Support'],True,"<font color=00ff00><b>Enabled</b></font>","<font color=pink><b>Disabled</b></font>")."</td></tr>\n";

	echo "<tr><td valign=\"middle\" nowrap><b>zlib Installed</b></td><td valign=\"top\" >".(extension_loaded("zlib") ? (get_cfg_var('zlib.output_compression') ? "<font color=00ff00><b>Enabled - <font color=pink>Don't enable AATrade gZip</font> - Automatic zlib Output Compression Enabled</b></font>" : "<font color=00ff00><b>Enabled - You can enable AATraders gZip output option.</b></font>") : "<font color=pink><b>No - Don't enable AATrade gZip</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>Automatic zlib Output Compression</b></td><td valign=\"top\" >".(get_cfg_var('zlib.output_compression') ? "<font color=00ff00><b>Enabled - Don't enable AATrade gZip</b></font>" : "<font color=pink><b>Disabled</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>Safe Mode</b></td><td valign=\"top\" >".(($sf == 1) ? "<font color=00ff00><b>Enabled</b></font>" : "<font color=pink><b>Disabled - Safe Mode should be enabled for better security.</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>Register Globals</b></td><td valign=\"top\" >".(($register_globals == 1) ? "<font color=pink><b>Enabled - This should be disabled. The game will still execute but there are no guarantees.</b></font>" : "<font color=00ff00><b>Disabled</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>Magic_quotes_gpc</b></td><td valign=\"top\" >".(($mqg == 1) ? "<font color=pink><b>Enabled - Auto Backslash Stripping enabled for \$_GET, \$_POST, \$_COOKIE and \$_FILES global variables. (Magic_quotes_gpc should be disabled for better variable handling)</b></font>" : "<font color=00ff00><b>Disabled</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>Allow FOPEN to open URLs</b></td><td valign=\"top\" >".(($allow_url_fopen == 1) ? "<font color=00ff00><b>Enabled - Serverlist/Profile System will be enabled and updated</b></font>" : "<font color=pink><b>Disabled</b></font>")."</td></tr>\n";
	echo "<tr><td valign=\"middle\" nowrap><b>CURL Library Installed</b></td><td valign=\"top\" >".(($is_curl == true) ? "<font color=00ff00><b>Enabled - Serverlist/Profile System will be enabled and updated</b></font>" : "<font color=pink><b>Disabled</b></font>")."</td></tr>\n";
	if($allow_url_fopen != 1 && $is_curl != true)
	{
		echo "<tr><td valign=\"middle\" nowrap><b>CURL and FOPEN Diabled</b></td><td valign=\"top\" ><font color=pink><b>Disabled - AATrade needs allow_url_fopen enabled for profiles and server list updates to function.  Profile System will be disabled.</b></font></td></tr>\n";
	}
	echo "<tr><td valign=\"middle\" nowrap><b>Multi-Byte Library Installed</b></td><td valign=\"top\" >".(($mbstring_supported == 1) ? "<font color=00ff00><b>Enabled - Multi-Byte Fonts Supported</b></font>" : "<font color=pink><b>Disabled</b></font>")."</td></tr>\n";
?>
              </table>
<?php
	if (!check_php_version ())
	{
?>
 <table width="100%" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
     <td>
<?php
		echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><b>You are installing this game on a server running a version of PHP that is older than 4.3.0.<br><br>";
		echo "Current Version: " . $yourphpversion . "<br><br>";
		echo "This game will not work properly on older versions of PHP.</b></font><br><hr>";
		$bad_config++;
?>
    </td>
  </tr>
</table>
<?php
	}

	if (!check_mysql_version ())
	{
?>
 <table width="100%" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
     <td>
<?php
		echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><b>You are installing this game on a server running a version of MySql that is older than 4.0.3 or MySql isn't installed.<br><br>";
		echo "Current Version: " . $version . "<br><br>";
		echo "This game will not work properly on older versons of MySql or other databases.</b></font><br><hr>";
		$bad_config++;
?>
    </td>
  </tr>
</table>
<?php
		$db_mysql_valid = "no";
	}
	else
	{
		$db_mysql_valid = "yes";
	}

//	if (!$mqg)
//	{
//		$bad_config++;
//	}

	if (!$adodb_exists)
	{
		$bad_config++;
	}

	if (!$template_object_exists)
	{
		$bad_config++;
	}

	TextFlush();

	if(!md5_filecheck("support/md5_list.inc"))
	{
?>
 <table width="100%" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
     <td>
<?php
		echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><b>The standard game files are either incomplete or have been modified.<br><br>";
		echo "This game will not work properly unless you have uploaded all game files and you are using standard game files.</b></font><br><hr>";
?>
    </td>
  </tr>
</table>
<?php
		$bad_config++;
	}
	else
	{
?>
 <table width="100%" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
     <td>
<?php
		echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\"><b>The standard game files are complete.</b></font><br><hr>";
?>
    </td>
  </tr>
</table>
<?php
	}
?>
           </td>
          </tr>
        </table>
		<br>
<?php
	if ($bad_config)
	{
?>
<table bgcolor="#000000" width="80%" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
    <td> 
<div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">There were issues with your install. Please do as we advised above, and it should resolve the problem for you.</font></b></div>
    </td>
  </tr>
</table>
      </td>
    </tr>
  </table>
<br>
<?php
	}
	else
	{
		if ($game_installed && $admin_password != $adminpass)
		{
?>
<table bgcolor="#000000" width="667" border="1" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td> 
<div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Previous Install Detected</font></b></div>
    </td>
  </tr>
</table>
 <table bgcolor="#000000" width="667" border="1" cellspacing="0" cellpadding="3" align="center">
  <tr>
          <td>
<?php
			echo "<font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">It seems that you have already installed the AATrade. If you want to edit your 'config_local" . $game_number . ".php' in /config/ dir, enter your admin password: ";
			echo "<input type=password name=admin_password value=\"\">&nbsp;";
			echo "<input type=hidden name=\"step\" value=\"20\">";
			echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">";
			echo "<input type=submit value=\"Submit\"><br>";
			echo "Everything looks great! Feel free to run the <a href=\"./create_game.php\">Create Universe</a> script now!</font>";
			$showit = 0;
?>
          </td>
  </tr>
</table>
      </td>
    </tr>
  </table>
<br>
<?php
		}

		if (!$game_installed)
		{
?>
<table bgcolor="#000000" width="667" border="1" cellspacing="0" cellpadding="0" align="center">
  <tr>
      <td>
<table width="100%" border="1" cellspacing="0" cellpadding="0" align="center">
  <tr>
    <td> 
<div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Directory 
                Settings</font></b></div>
    </td>
  </tr>
</table>
      </td>
    </tr>
  </table>
<br>
<?php
		}
		else
		{
?>
</td>
</tr>
</table>
<?php
		}
		if ($showit == 1)	 // Preparing values for the form
		{
			if($game_number == 0)
			{
				$v[2]  = isset($dbname) ? $dbname : $ADODB_SESSION_DB;
			}
			else
			{
				$v[2]  = isset($dbname) ? $dbname : '';
			}
			$v[1]  = isset($db_type) ? $db_type : 'mysql';
			$v[3]  = isset($dbuname) ? $dbuname : '';
			$v[4]  = isset($dbpass) ? $dbpass : '';
			$v[5]  = isset($dbhost) ? $dbhost : 'localhost';
			$v[6]  = isset($dbport) ? $dbport : '';
			$v[8]  = isset($db_prefix) ? $db_prefix : 'aatrade_';
//			$v[9]  = isset($gameroot) ? $gameroot : str_replace("installer.php","",$_SERVER["PATH_TRANSLATED"]);
			$v[10] = isset($gamepath) ? $gamepath : dirname($_SERVER['PHP_SELF']);

			if ($v[10] ==="\\")
				$v[10]="/";

			$v[10] =str_replace("\\", "/", stripcslashes($v[10]));

			$v[13] = isset($admin_mail) ? $admin_mail : '';
			$v[14] = isset($adminpass) ? $adminpass : '';
			$v[16] = isset($sched_ticks) ? $sched_ticks : "5";

			$v[17] = isset($gameurl) ? $gameurl : $_SERVER['HTTP_HOST'];

			$pos = AAT_strpos($v[17],"http://");
			if (is_integer($pos))
				$v[17] = AAT_substr($v[17],$pos+7);
			$pos = AAT_strpos($v[17],":");
			if (is_integer($pos))
				$v[17] = AAT_substr($v[17],0,$pos);

			$v[18]  = isset($db_mysql_typename) ? $db_mysql_type : 'default';
			$v[19]  = isset($game_name) ? $game_name : 'Enter the name of your game here';


			echo "<form onSubmit=\"return checkform(this)\" action=\"installer.php\"  method=\"POST\" enctype=\"multipart/form-data\"  name=\"configure\" id=\"configure\">";
?>

<table bgcolor="#000000" width="667" border="1" cellspacing="0" cellpadding="0" align="center">
  <tr>
      <td>
        <table width="100%" border="1" cellspacing="0" cellpadding="0" align="center">
          <tr>
            <td>
              <div align="center"><b><font face="Verdana, Arial, Helvetica, sans-serif" size="3" color="#66FFCC">Game Settings</font></b></div>
            </td>
          </tr>
		</table>
<?			echo "<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"3\" align=\"center\">\n";

			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Game Title<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the title to use for the game.</font></font></td><td valign=\"middle\" nowrap><input tabindex=2 type=text name=_game_name value=\"$v[19]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">* Database type<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">The game works with MySQL.</font></td>";
			echo "<td valign=\"middle\" nowrap><select tabindex=1 name=_db_type>";
			foreach($dbs as $value => $name)
			{
				echo "<option value=$value " . ($v[1] == $value ? 'selected' : '') . ">$name</option>";
			}
			echo "</select></td></tr>";

			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database name<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the name of your database.<br>You should have created the database before<br>executing the installer.php program. If you haven't<br>created the database you should do so now because<br>the installer will FAIL if the database<br>isn't created before proceeding.</font></font></td><td valign=\"middle\" nowrap><input tabindex=2 type=text name=_dbname value=\"$v[2]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">* MySql Database Type</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">Default = Standard Database<br>InnoDB = Slower but more secure database type for MySql. You need a database server with a lot of memory to use INNODB.  Do not use unless you have the memory available.</font></td>";
			echo "<td valign=\"middle\" ><select tabindex=18 name=_db_mysql_type>";
			echo "<option value=\"default\" " . ($v[18] == "default" ? 'selected' : '') . ">Default</option>";
			echo "<option value=\"InnoDB\" " . ($v[18] == "InnoDB" ? 'selected' : '') . ">InnoDB</option>";
			echo "</select></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database username</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the username of the database.</font></td><td valign=\"middle\" nowrap><input tabindex=3 type=text name=_dbuname value=\"$v[3]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database password<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the password for the database.</font></font></td><td valign=\"middle\" nowrap><input tabindex=4 type=password name=_dbpass value=\"$v[4]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database host</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">If the database is on the same server the game<br>is running use <b>localhost</b> else enter the IP<br>address for the database server.</font></td><td valign=\"middle\" nowrap><input tabindex=5 type=text name=_dbhost value=\"$v[5]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Database port</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">Leave this blank unless you know what you are doing.<br>Most Mysql databases do not need the port designated.</font></td><td valign=\"middle\" nowrap><input size=3 tabindex=6 type=text name=_dbport value=\"$v[6]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">* Database table prefix<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">If you want to use only one database you can use a different prefix for each game.  This will allow you to use only a single database for all games instead of a different database for each game.  Make sure the prefix is different for each game.</font></font></td><td valign=\"middle\" nowrap><input tabindex=8 type=text name=_db_prefix value=\"$v[8]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">* Game URL</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the URL for your game.<br>IE: <b>www.mygame.com</b> from http://www.mygame.com/aatrade<br><br>The installer will determine the URL for you.  This is the BASE URL without any directory paths.  Do not change this unless it is different from the URL you will be using.</font></td><td valign=\"middle\" nowrap><input tabindex=18 type=text name=_gameurl value=\"$v[17]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">* Game path<br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the directory path for your URL.<br>IE: <b>/aatrade</b> from http://www.mygame.com/aatrade<br><br>This is the directory path used with the base URL.  This is determined by the installer.  Do not change this unless it is incorrect.</font></font></td><td valign=\"middle\" nowrap><input tabindex=10 type=text size=50 name=_gamepath value=\"$v[10]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Windows Game root</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the Windows directory path (IE: D:\aatrade) on the server to the game.<br>Ignore this if you are not installing on a Windows server.</font></td><td valign=\"middle\" nowrap><input tabindex=9 type=text size=50 name=windowsroot value=\"" . str_replace("installer", "", dirname(__FILE__)) . "\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Admin email</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the default email address.<br>All ingame Feedback will be sent there.</font></td><td valign=\"middle\" nowrap><input tabindex=13 type=text name=_admin_mail size=50 value=\"$v[13]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Admin password</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is the password for accessing the admin.php and <br>logging in as Fed, Indy or Alliance.</font></td><td valign=\"middle\" nowrap><input tabindex=14 type=password name=_adminpass value=\"$v[14]\"></td></tr>";
			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">Confirm admin password</font></td><td valign=\"middle\" nowrap><input tabindex=15 type=password name=adminpass2 value=\"$v[14]\"></td></tr>";

			echo "<tr><td ><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"2\">* Cron interval</font><br><font face=\"Verdana, Arial, Helvetica, sans-serif\" size=\"1\">This is how often the scheduler should run.  Do not set this below 5 or the scheduler may fail.</font></td><td valign=\"middle\" nowrap><input size=3 tabindex=17 type=text name=_sched_ticks value=\"$v[16]\"> minutes</td></tr>";

			echo "<input type=hidden name=\"step\" value=\"30\">";
			echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">";
			echo "<input type=hidden name=\"admin_password\" value=\"$admin_password\">";
?>
    <tr> 
      <td colspan="2"> 
        <div align="center"><font face="Verdana, Arial, Helvetica, sans-serif" size="2">
		* = You should use the default settings. Don't change them unless you know what you are doing.<br><br>
          <input tabindex=19 type="submit" name="Save Profile" value="Save Profile">
		  </font>
        </div>
      </td>
    </tr>
</table>
</td>
</tr>
</table>
</form>
<?php
		}
	}
}

?>