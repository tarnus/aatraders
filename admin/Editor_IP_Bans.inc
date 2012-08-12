<?php
// 2: IP Bans
// This tool will allow banning of different IP's and logging attempts to enter the game.  A list of all players in the game along with their IP addresses can also be viewed.  IP addresses with multiple accounts will be grouped together.

get_post_ifset("ban, ip, class, ipaddress, emailaddress");

function user_ipwhois($ip)
{
	$ipwhois = '';

	// Check IP
	// Only supporting IPv4 at the moment...
	if (empty($ip) || !preg_match('#^(?:(?:\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(?:\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$#', $ip))
	{
		return '';
	}

	$match = array(
		'#whois\.apnic\.net#is'		=> 'whois.apnic.net',
		'#RIPE\.NET#is'				=> 'whois.ripe.net',
		'#nic\.ad\.jp#is'			=> 'whois.nic.ad.jp',
		'#whois\.registro\.br#is'	=> 'whois.registro.br'
	);

	if (($fsk = fsockopen('whois.arin.net', 43)))
	{
		fputs($fsk, "$ip\n");
		while (!feof($fsk))
		{
			$ipwhois .= fgets($fsk, 1024);
		}
		fclose($fsk);
	}

	foreach (array_keys($match) as $server)
	{
		if (preg_match($server, $ipwhois))
		{
			$ipwhois = '';
			if (($fsk = fsockopen($match[$server], 43)))
			{
				fputs($fsk, "$ip\n");
				while (!feof($fsk))
				{
					$ipwhois .= fgets($fsk, 1024);
				}
				fclose($fsk);
			}
			break;
		}
	}

	$ipwhois = htmlspecialchars($ipwhois);

	return trim(nl2br($ipwhois));
}

if (empty($command))
{
	echo "<tr><td><FORM ACTION=admin.php METHOD=POST>";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=command VALUE=showips>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">";
	echo "<INPUT TYPE=SUBMIT VALUE=\"Show player's ips\">";
	echo "</form>";

	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "Enter IP Address: <input type=text name=ipaddress value='' size=32 maxlength=25>&nbsp;&nbsp;";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=command VALUE=banipaddress>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">";
	echo "<INPUT TYPE=SUBMIT VALUE=\"Ban this IP\">";
	echo "</form>";

	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "Enter Email Address: <input type=text name=emailaddress value='' size=32 maxlength=150>&nbsp;&nbsp;";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=command VALUE=banemail>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">";
	echo "<INPUT TYPE=SUBMIT VALUE=\"Ban this Email\">";
	echo "</form><br>";

	$res = $db->Execute("SELECT * FROM {$db_prefix}ip_bans");
	while (!$res->EOF)
	{
		$ipaddress=$res->fields['ban_mask'];
		if($ipaddress != ''){
			$bans[]=$ipaddress;
		}
		else
		{
			$bansemail[]=$res->fields['email'];
		}
		$res->MoveNext();
	}

	if (empty($bans) and empty($bansemail))
	{
		echo "<b>No IP bans are currently active.</b>";
	}
	else
	{
		echo "<table border=1 cellspacing=1 cellpadding=2 width=100% align=center>" .
			 "<tr bgcolor=#23244F><td align=center colspan=7><b><font color=white>" .
			 "Active IP Bans" .
			 "</font></b>" .
			 "</td></tr>" .
			 "<tr align=center bgcolor=#23244F>" .
			 "<td><font size=2 color=white><b>Ban Mask</b></font></td>" .
			 "<td><font size=2 color=white><b>Affected Players</b></font></td>" .
			 "<td><font size=2 color=white><b>E-mail</b></font></td>" .
			 "<td><font size=2 color=white><b>Operations</b></font></td>" .
			 "</tr>";

		$curcolor = "#3A3B6E";

		foreach ($bans as $ban)
		{
			echo "<tr bgcolor=$curcolor>";
			if ($curcolor == "#3A3B6E")
			{
				$curcolor = "#23244F"; 
			}
			else
			{
				$curcolor = "#3A3B6E";
			}

			$printban = str_replace("%", "*", $ban);

			echo "<td align=center><font size=2 color=white>$printban</td>" .
				 "<td align=center><font size=2 color=white>";

			$res = $db->Execute("SELECT character_name, player_id, email FROM {$db_prefix}players WHERE ip_address LIKE '$ban'");
			unset($players);
			while (!$res->EOF)
			{
				$players[] = $res->fields;
				$res->MoveNext();
			}

			if (empty($players))
			{
				echo "None";
			}
			else
			{
				foreach ($players as $player)
				{
					echo "<b>$player[character_name]</b><br>";
				}
			}

			echo "<td align=center><font size=2 color=white>";
			if (empty($players))
			{
				echo "N/A";
			}
			else
			{
				foreach ($players as $player)
				{
					echo "$player[email]<br>";
				}
			}

			echo "<td align=center nowrap valign=center><font size=2 color=white>" .
				 "<form action=admin.php method=POST>" .
				 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
				 "<INPUT TYPE=HIDDEN NAME=command VALUE=unbanip>" .
				 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
				 "<INPUT TYPE=HIDDEN NAME=ban VALUE=$ban>" .
				 "<INPUT TYPE=SUBMIT VALUE=Remove>" .
				"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
				 "</form>";
		}
		foreach ($bansemail as $ban)
		{
			echo "<tr bgcolor=$curcolor>";
			if ($curcolor == "#3A3B6E")
			{
				$curcolor = "#23244F"; 
			}
			else
			{
				$curcolor = "#3A3B6E";
			}

			$printban = $ban;

			echo "<td align=center><font size=2 color=white>N/A</td>" .
				 "<td align=center><font size=2 color=white>";

			echo "None</td>";

			echo "<td align=center><font size=2 color=white>";
			echo "$printban</td>";

			echo "<td align=center nowrap valign=center><font size=2 color=white>" .
				 "<form action=admin.php method=POST>" .
				 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
				 "<INPUT TYPE=HIDDEN NAME=command VALUE=unbanemail>" .
				 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
				 "<INPUT TYPE=HIDDEN NAME=ban VALUE=$ban>" .
				"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
				 "<INPUT TYPE=SUBMIT VALUE=Remove>" .
				 "</form>";
		}
		echo "</table><p></td></tr>";
	}
}
elseif ($command== 'showips')
{
	$res = $db->Execute("SELECT DISTINCT ip_address FROM {$db_prefix}players order by ip_address");
	while (!$res->EOF)
	{
		$ips[]=$res->fields['ip_address'];
		$res->MoveNext();
	}
	echo "<tr><td><table border=1 cellspacing=1 cellpadding=2 width=100% align=center>" .
		 "<tr bgcolor=#23244F><td align=center colspan=7><b><font color=white>" .
		 "Players sorted by IP address" .
		 "</font></b>" .
		 "</td></tr>" .
		 "<tr align=center bgcolor=#23244F>" .
		 "<td><font size=2 color=white><b>IP address</b></font></td>" .
		 "<td><font size=2 color=white><b>Players</b></font></td>" .
		 "<td><font size=2 color=white><b>E-mail</b></font></td>" .
		 "<td><font size=2 color=white><b>Operations</b></font></td>" .
		 "</tr>";

	$curcolor = "#3A3B6E";

	foreach ($ips as $ip)
	{
		echo "<tr bgcolor=$curcolor>";
		if ($curcolor == "#3A3B6E")
		{
			$curcolor = "#23244F"; 
		}
		else
		{
			$curcolor = "#3A3B6E";
		}

		echo "<td align=center><form action=admin.php method=POST>" .
			 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
			"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
			 "<INPUT TYPE=HIDDEN NAME=command VALUE='whois'>" .
			 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
			 "<INPUT TYPE=HIDDEN NAME=\"ip\" VALUE=\"$ip\">" .
			 "<INPUT TYPE=SUBMIT VALUE=\"WhoIs: $ip\">" .
			 "</form></td>" .
			 "<td align=center><font size=2 color=white>";

		$res = $db->Execute("SELECT character_name, player_id, email FROM {$db_prefix}players WHERE ip_address='$ip'");
		unset($players);
		while (!$res->EOF)
		{
			$players[] = $res->fields;
			$res->MoveNext();
		}

		foreach ($players as $player)
		{
			echo "<b>$player[character_name]</b><br>";
		}

		echo "<td align=center><font size=2 color=white>";

		foreach($players as $player)
		{
			echo "$player[email]<br>";
		}

		echo "<td align=center nowrap valign=center><font size=2 color=white>" .
			 "<form action=admin.php method=POST>" .
			 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
			"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
			 "<INPUT TYPE=HIDDEN NAME=command VALUE=banip>" .
			 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
			 "<INPUT TYPE=HIDDEN NAME=ip VALUE=$ip>" .
			 "<INPUT TYPE=SUBMIT VALUE=Ban>" .
			 "</form>" .
			 "<form action=admin.php method=POST>" .
			"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
			 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
			 "<INPUT TYPE=HIDDEN NAME=command VALUE=unbanip>" .
			 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
			 "<INPUT TYPE=HIDDEN NAME=ip VALUE=$ip>" .
			 "<INPUT TYPE=SUBMIT VALUE=Unban>" .
			 "</form>";
	}

	echo "</table><p>" .
		 "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command == 'banip')
{
	echo "<b>Banning ip : $ip<p>";
	echo "<font size=2 color=white>Please select ban type :<p>";
	$ipparts = explode(".", $ip);

	echo "<tr><td><table border=0>" .
		 "<tr><td align=right>" .
		 "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=HIDDEN NAME=command VALUE=banip2>" .
		 "<INPUT TYPE=HIDDEN NAME=ip VALUE=$ip>" .
		 "<input type=radio name=class value=I checked>" .
		 "<td><font size=2 color=white>IP only : $ip</td>" .
		 "<tr><td>" .
		 "<input type=radio name=class value=A>" .
		 "<td><font size=2 color=white>Class A : $ipparts[0].$ipparts[1].$ipparts[2].*</td>" .
		 "<tr><td>" .
		 "<input type=radio name=class value=B>" .
		 "<td><font size=2 color=white>Class B : $ipparts[0].$ipparts[1].*</td>" .
		 "<tr><td><td><br><input type=submit value=Ban>" .
		 "</table>" .
		 "</form>";

	echo "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command == 'banip2')
{
	$ipparts = explode(".", $ip);

	if ($class == 'A')
	{
		$banmask = "$ipparts[0].$ipparts[1].$ipparts[2].%";
	}
	elseif ($class == 'B')
	{
		$banmask = "$ipparts[0].$ipparts[1].%";
	}
	else
	{
		$banmask = $ip;
	}

	$printban = str_replace("%", "*", $banmask);
	echo "<tr><td><font size=2 color=white><b>Successfully banned $printban</b>.<p>";

	$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans (ban_mask, email)VALUES('$banmask', '')");
	db_op_result($debug_query,__LINE__,__FILE__);

	$res = $db->Execute("SELECT DISTINCT {$db_prefix}players.character_name, {$db_prefix}players.email FROM {$db_prefix}players, {$db_prefix}ip_bans WHERE {$db_prefix}players.ip_address LIKE '$banmask'");
	echo "Affected players :<p>";
	while (!$res->EOF)
	{
		echo " - " . $res->fields['character_name'] . "<br>";
		$emailban = $res->fields['email'];
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans (ban_mask, email)VALUES('', '$emailban')");
		db_op_result($debug_query,__LINE__,__FILE__);
		$res->MoveNext();
	}

	echo "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command == 'unbanip')
{
	if (!empty($ban))
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}ip_bans WHERE ban_mask='$ban'");
	}
	else
	{
		$res = $db->Execute("SELECT * FROM {$db_prefix}ip_bans WHERE '$ip' LIKE ban_mask");
	}

	$nbbans = $res->RecordCount();
	while (!$res->EOF)
	{
		$res->fields[print_mask] = str_replace("%", "*", $res->fields[ban_mask]);
		$bans[]=$res->fields;
		$res->MoveNext();
	}

	if (!empty($ban))
	{
		$db->Execute("DELETE FROM {$db_prefix}ip_bans WHERE ban_mask='$ban'");
	}
	else
	{
		$db->Execute("DELETE FROM {$db_prefix}ip_bans WHERE '$ip' LIKE ban_mask");
	}

	$query_string = "ip_address LIKE '" . $bans[0][ban_mask] ."'";
	for ($i = 1; $i < $nbbans ; $i++)
	{
		$query_string = $query_string . " OR ip_address LIKE '" . $bans[$i][ban_mask] . "'";
	}

	$res = $db->Execute("SELECT DISTINCT character_name FROM {$db_prefix}players WHERE $query_string");
	$nbplayers = $res->RecordCount();

	while (!$res->EOF)
	{
		$players[]=$res->fields[character_name];
		$res->MoveNext();
	}

	echo "<tr><td><font size=2 color=white><b>Successfully removed $nbbans bans</b> :<p>";
	foreach ($bans as $ban)
	{
		echo " - $ban[print_mask]<br>";
	}

	echo "<p><b>Affected players :</b><p>";
	if (empty($players))
	{
		echo " - None<br>";
	}
	else
	{
		foreach($players as $player)
		{
			echo " - $player<br>";
		}
	}

	echo "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command== 'banipaddress')
{
	echo "<tr><td>Banned IP Address: $ipaddress<br>";
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans VALUES('', '$ipaddress', '')");
	db_op_result($debug_query,__LINE__,__FILE__);
	echo "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command== 'banemail')
{
	echo "<tr><td>Banned Email Address: $emailaddress<br>";
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}ip_bans VALUES('', '', '$emailaddress')");
	db_op_result($debug_query,__LINE__,__FILE__);
	echo "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command== 'unbanemail')
{
	echo "<tr><td><font size=2 color=white><b>Successfully removed ban for $ban</b><p>";
	$debug_query = $db->Execute("DELETE FROM {$db_prefix}ip_bans WHERE email='$ban'");
	db_op_result($debug_query,__LINE__,__FILE__);
	echo "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
elseif ($command== 'whois')
{

	$res = $db->Execute("SELECT character_name, player_id, email FROM {$db_prefix}players WHERE ip_address='$ip'");
	unset($players);
	while (!$res->EOF)
	{
		$players[] = $res->fields;
		$res->MoveNext();
	}

	echo "<tr><td align=\"center\"><font size=\"3\" color=\"lime\">";

	foreach ($players as $player)
	{
		echo "<b>$player[character_name]</b><br>";
		echo "$player[email]<br><br>";
	}

	echo"IP Address: $ip<br><hr></font><font size=2 color=white><b>" . user_ipwhois($ip) . "</b></font><td></tr>";

	$res = $db->Execute("SELECT DISTINCT ip_address FROM {$db_prefix}players order by ip_address");
	while (!$res->EOF)
	{
		$ips[]=$res->fields['ip_address'];
		$res->MoveNext();
	}
	echo "<tr><td><table border=1 cellspacing=1 cellpadding=2 width=100% align=center>" .
		 "<tr bgcolor=#23244F><td align=center colspan=7><b><font color=white>" .
		 "Players sorted by IP address" .
		 "</font></b>" .
		 "</td></tr>" .
		 "<tr align=center bgcolor=#23244F>" .
		 "<td><font size=2 color=white><b>IP address</b></font></td>" .
		 "<td><font size=2 color=white><b>Players</b></font></td>" .
		 "<td><font size=2 color=white><b>E-mail</b></font></td>" .
		 "<td><font size=2 color=white><b>Operations</b></font></td>" .
		 "</tr>";

	$curcolor = "#3A3B6E";

	foreach ($ips as $ip)
	{
		echo "<tr bgcolor=$curcolor>";
		if ($curcolor == "#3A3B6E")
		{
			$curcolor = "#23244F"; 
		}
		else
		{
			$curcolor = "#3A3B6E";
		}

		echo "<td align=center><form action=admin.php method=POST>" .
			 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
			"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
			 "<INPUT TYPE=HIDDEN NAME=command VALUE='whois'>" .
			 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
			 "<INPUT TYPE=HIDDEN NAME=\"ip\" VALUE=\"$ip\">" .
			 "<INPUT TYPE=SUBMIT VALUE=\"WhoIs: $ip\">" .
			 "</form></td>" .
			 "<td align=center><font size=2 color=white>";

		$res = $db->Execute("SELECT character_name, player_id, email FROM {$db_prefix}players WHERE ip_address='$ip'");
		unset($players);
		while (!$res->EOF)
		{
			$players[] = $res->fields;
			$res->MoveNext();
		}

		foreach ($players as $player)
		{
			echo "<b>$player[character_name]</b><br>";
		}

		echo "<td align=center><font size=2 color=white>";

		foreach($players as $player)
		{
			echo "$player[email]<br>";
		}

		echo "<td align=center nowrap valign=center><font size=2 color=white>" .
			 "<form action=admin.php method=POST>" .
			 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
			"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
			 "<INPUT TYPE=HIDDEN NAME=command VALUE=banip>" .
			 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
			 "<INPUT TYPE=HIDDEN NAME=ip VALUE=$ip>" .
			 "<INPUT TYPE=SUBMIT VALUE=Ban>" .
			 "</form>" .
			 "<form action=admin.php method=POST>" .
			"  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
			 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
			 "<INPUT TYPE=HIDDEN NAME=command VALUE=unbanip>" .
			 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
			 "<INPUT TYPE=HIDDEN NAME=ip VALUE=$ip>" .
			 "<INPUT TYPE=SUBMIT VALUE=Unban>" .
			 "</form>";
	}

	echo "</table><p>" .
		 "<form action=admin.php method=POST>" .
		 "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n" .
		 "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>" .
		 "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_IP_Bans\">" .
		 "<INPUT TYPE=SUBMIT VALUE=\"Return to IP bans menu\">" .
		 "</form></td></tr>";
}
?>
