<?php
// 2: Player and Ship
// You can edit the current players name, ship name, password, ship, avatar and many other attributes.  You can also destroy a player or kill them from the game.

get_post_ifset("user, operation");

include ("languages/$langdir/lang_report.inc");
include ("globals/db_kill_player.inc");
include ("globals/player_ship_destroyed.inc");
include ("globals/ord_crypt_encode.inc");
include ("globals/ord_crypt_decode.inc");

if(@ini_get("register_globals") != 1)
{
	if (!empty($_GET))
	{
		extract($_GET);
	}

	if (!empty($_POST))
	{
		extract($_POST);
	}
}

$fun_temp = 0;
$option_echo = '';
echo "</tr><td><div align=\"center\">\n";
echo "<br>\n";
echo "<form action=\"admin.php\" method=\"post\">\n";
if (empty($user))
{
	$res = $db->Execute("SELECT player_id,character_name FROM {$db_prefix}players ORDER BY character_name");
	while (!$res->EOF)
	{
		$row = $res->fields;
		$option_echo .= "	<option value=\"$row[player_id]\">$row[character_name]</option>\n";
		$res->MoveNext();
		$fun_temp++;
	}

	if ($fun_temp > 20)
	{
		$fun_temp = 20;
	}

	echo "  <select size=\"$fun_temp\" name=\"user\">\n";
	echo $option_echo;
	echo "  </select>\n";
	echo "  &nbsp;\n  <input type=\"submit\" value=\"Edit\">\n";
}
else
{
	if (empty($operation))
	{
		$res = $db->Execute("SELECT * from {$db_prefix}players LEFT JOIN {$db_prefix}ships " .
							"ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id and  {$db_prefix}players.currentship ={$db_prefix}ships.ship_id " .
							"WHERE {$db_prefix}players.player_id=$user");
		$row = $res->fields;

		$res = $db->Execute("SELECT * from {$db_prefix}ship_types WHERE type_id=$row[class]");
		$shiptypeinfo = $res->fields;

		$res = $db->Execute("SELECT cargo_name, amount, hold_space FROM {$db_prefix}ship_holds WHERE ship_id=$row[currentship] ");
		db_op_result($res,__LINE__,__FILE__);

		$cargo_items = 0;
		$hold_space = 0;
		while(!$res->EOF)
		{
			$cargo_name[$cargo_items] = $res->fields['cargo_name'];
			$cargo_amount[$cargo_items] = NUMBER($res->fields['amount']);
			$hold_space += ($res->fields['hold_space'] * $res->fields['amount']);
			$cargo_holds[$cargo_items] = $res->fields['hold_space'];
			$cargo_items++;
			$res->MoveNext();
		}
 

		$template_object->assign("l_total_cargo", $l_total_cargo);
		$template_object->assign("cargo_holds", $cargo_holds);
		$template_object->assign("cargo_items", $cargo_items);
		$template_object->assign("cargo_name", $cargo_name);
		$template_object->assign("cargo_amount", $cargo_amount);
		$template_object->assign("hold_space_used", NUMBER($hold_space));
		$template_object->assign("l_total_cargo", $l_total_cargo);
		$template_object->assign("l_hold_space_used", $l_hold_space_used);
		$template_object->assign("l_hold_space_free", $l_hold_space_free);

		$template_object->assign("hold_space", NUMBER($hold_space));

		$res2 = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE player_id=$user and ship_id=$row[currentship]");
		$row2 = $res2->fields;
		$template_object->assign("holds_max", NUMBER(NUM_HOLDS($row2['hull'])));

		// Template stuff
		$template_object->assign("character_name", $row['character_name']);
		$template_object->assign("admin_extended_logging", $row['admin_extended_logging']);
		$template_object->assign("password", ord_crypt_decode($row['password']));
		$template_object->assign("email", $row['email']);
		$template_object->assign("user", $user);
		$template_object->assign("shipname", $row2['name']);
		$template_object->assign("ship_class", $shiptypeinfo['type_id']);
		$template_object->assign("destroyed", $row['destroyed']);
		$template_object->assign("hull", $row2['hull']);
		$template_object->assign("engines", $row2['engines']);
		$template_object->assign("power", $row2['power']);
		$template_object->assign("fighter", $row2['fighter']);
		$template_object->assign("sensors", $row2['sensors']);
		$template_object->assign("armor", $row2['armor']);
		$template_object->assign("shields", $row2['shields']);
		$template_object->assign("beams", $row2['beams']);
		$template_object->assign("torp_launchers", $row2['torp_launchers']);
		$template_object->assign("cloak", $row2['cloak']);
		$template_object->assign("ecm", $row2['ecm']);

		$template_object->assign("hull_normal", $row2['hull_normal']);
		$template_object->assign("engines_normal", $row2['engines_normal']);
		$template_object->assign("power_normal", $row2['power_normal']);
		$template_object->assign("fighter_normal", $row2['fighter_normal']);
		$template_object->assign("sensors_normal", $row2['sensors_normal']);
		$template_object->assign("armor_normal", $row2['armor_normal']);
		$template_object->assign("shields_normal", $row2['shields_normal']);
		$template_object->assign("beams_normal", $row2['beams_normal']);
		$template_object->assign("torp_launchers_normal", $row2['torp_launchers_normal']);
		$template_object->assign("cloak_normal", $row2['cloak_normal']);
		$template_object->assign("ecm_normal", $row2['ecm_normal']);

		$template_object->assign("energy", NUMBER($row2['energy']));
		$template_object->assign("fighters", NUMBER($row2['fighters']));
		$template_object->assign("torps", NUMBER($row2['torps']));
		$template_object->assign("armor_pts", NUMBER($row2['armor_pts']));
		$template_object->assign("credits", NUMBER($row['credits']));
		$template_object->assign("turns", NUMBER($row['turns']));
		$template_object->assign("turns_used", NUMBER($row['turns_used']));
		$template_object->assign("sector_id", $row['sector_id']);
		$template_object->assign("currentship_id", $row['currentship']);
		$template_object->assign("dev_nova", $row2['dev_nova']);

		$template_object->assign("fed_bounty_count", $row['fed_bounty_count']);
		$template_object->assign("alliance_bounty_count", $row['alliance_bounty_count']);
		$template_object->assign("template", $row['template']);
		$template_object->assign("avatar", $row['avatar']);
		$template_object->assign("last_team", $row['last_team']);
		$template_object->assign("left_team_time", $row['left_team_time']);

		$res3 = $db->Execute("SELECT * FROM {$db_prefix}ibank_accounts WHERE player_id=$user");
		$row3 = $res3->fields;

		$template_object->assign("igb_balance", $row3['balance']);
		$template_object->assign("igb_loan", $row3['loan']);
		$template_object->assign("igb_loantime", $row3['loantime']);

		$res = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE owner=$user");

		$stuff = array();

		while (!$res->EOF)
		{
			$row = $res->fields;

			$name = ($row['name']=="")?("UnNamed"):($row['name']);
			// $id[] = $row[planet_id];
			$sector = $row['sector_id'];
			$stuff[] = "'$name' in sector $sector";

			$res->MoveNext();
		}

		$template_object->assign("stuff", $stuff);

		$template_object->display("admin/Player_and_Ship_Editor.tpl");
	}
	elseif ($operation == "Update")
	{
		if ((!isset($turns_used)) || ($turns_used == ''))
		{
			$turns_used = '';
		}

		if ((!isset($ship_class)) || ($ship_class == ''))
		{
			$ship_class = '';
		}

		if ((!isset($igb_balance)) || ($igb_balance == ''))
		{
			$igb_balance = '';
		}

		if ((!isset($igb_loan)) || ($igb_loan == ''))
		{
			$igb_loan = '';
		}

		if ((!isset($igb_loantime)) || ($igb_loantime == ''))
		{
			$igb_loantime = '';
		}

		$character_name = preg_replace ("/[^\w\d\s\.\'\@]/","",$character_name);
		$ship_name = preg_replace ("/[^\w\d\s\.\'\@]/","",$ship_name);

		$character_name = htmlspecialchars($character_name,ENT_QUOTES);
		$ship_name = htmlspecialchars($ship_name,ENT_QUOTES);

		$silent = 0;
		echo "Updating PLAYERS table "; 
		$query = "UPDATE {$db_prefix}players SET destroyed='$destroyed', last_login=last_login,character_name=" . $db->qstr($character_name) . ",email='$email',credits='" . stripnum($credits) . "',turns='" . stripnum($turns) . "',turns_used='" . stripnum($turns_used) . "',password='" . ord_crypt_encode($password2) . "',fed_bounty_count='$fed_bounty_count',alliance_bounty_count='$alliance_bounty_count',template='$template',avatar='$avatar',last_team='$last_team',left_team_time='$left_team_time', admin_extended_logging='$admin_extended_logging' WHERE player_id=$user";
		$debug_query = $db->Execute($query); 
		db_op_result($debug_query,__LINE__,__FILE__);
		$query = "SELECT rating FROM {$db_prefix}players WHERE player_id=$user";
		$debug_query = $db->Execute($query); 
		db_op_result($debug_query,__LINE__,__FILE__);
		$rating = $debug_query->fields['rating'];

		echo "Updating SHIPS table "; 

		$query = "UPDATE {$db_prefix}ships SET ";
		$query .= "class='$ship_class',name=" . $db->qstr($ship_name) . ",hull='$hull',engines='$engines',power='$power',fighter='$fighter',sensors='$sensors',beams='$beams',torp_launchers='$torp_launchers',torps='" . stripnum($torps) . "',shields='$shields',armor='$armor',armor_pts='" . stripnum($armor_pts) . "',cloak='$cloak', ecm='$ecm',sector_id='$sector',fighters='" . stripnum($ship_fighters) . "', energy='" . stripnum($ship_energy) . "', ";
		$query .= "hull_normal='$hull_normal',engines_normal='$engines_normal',power_normal='$power_normal',fighter_normal='$fighter_normal',sensors_normal='$sensors_normal',beams_normal='$beams_normal',torp_launchers_normal='$torp_launchers_normal',shields_normal='$shields_normal',armor_normal='$armor_normal',ecm_normal='$ecm_normal',cloak_normal='$cloak_normal' WHERE ship_id=$currentship_id"; 
		$debug_query = $db->Execute($query); 
		db_op_result($debug_query,__LINE__,__FILE__);

		$res = $db->Execute("SELECT cargo_name, hold_id FROM {$db_prefix}ship_holds WHERE ship_id=$currentship_id ");
		db_op_result($res,__LINE__,__FILE__);
		$prefix = "commodity_";
		while(!$res->EOF)
		{
			$cargo_name = "commodity_" . str_replace(" ", "_", $res->fields['cargo_name']);
			$hold_id = $res->fields['hold_id'];
			$query = "UPDATE {$db_prefix}ship_holds SET amount=" . stripnum($$cargo_name) . " WHERE hold_id=$hold_id";
			$debug_query = $db->Execute($query); 
			db_op_result($debug_query,__LINE__,__FILE__);
			$res->MoveNext();
		}

		//store igb data in db
		echo "Updating IBANK_ACCOUNTS table "; 
		$query = "UPDATE {$db_prefix}ibank_accounts SET balance='" . stripnum($igb_balance) . "',loan='" . stripnum($igb_loan) . "',loantime='$igb_loantime' WHERE player_id='$user'"; 
		$debug_query = $db->Execute($query); 
		db_op_result($debug_query,__LINE__,__FILE__);

		if($destroyed == "Y")
			db_kill_player($user, 0, 0);

		if($destroyed == "K")
			player_ship_destroyed($currentship_id, $user, $rating, 3, 0, "killedpod");

		echo "<br><INPUT TYPE=SUBMIT VALUE=\"Return to User editor\">";
		$silent = 0;
		$button_main = false;
	}
	else
	{
		echo "Invalid operation";
	}
}
echo "  <input type=\"hidden\" name=\"menu\" value=\"Editor_Player_and_Ship\">\n";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "  <input type=\"hidden\" name=\"admin_password\" value=\"$admin_password\">\n";
echo "</form>\n</div></td></tr>";
?>