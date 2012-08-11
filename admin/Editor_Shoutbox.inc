<?
// 2: Shoutbox
// This tool will display all shouts in the game, most recent first.  You can edit or add new shouts.

get_post_ifset("player_id, sb_text, player_name, sb_date, sb_id, page");

include ("globals/clean_words.inc");
include ("globals/add_smilies.inc");
include ("languages/$langdir/lang_shoutbox.inc");

if ($command=="DEL")
{
	$xsql = "DELETE FROM {$db_prefix}shoutbox WHERE sb_id = $sb_id";
	$result = $db->Execute($xsql);
}

if ($command=="ADD")
{
	$sb_text = htmlspecialchars(clean_words($sb_text));

	// Check double post!
	$result = $db->SelectLimit("SELECT * FROM {$db_prefix}shoutbox ORDER BY sb_date DESC", 1);
	db_op_result($result,__LINE__,__FILE__);
	$lastshout = $result->fields;
	if ($lastshout['sb_text'] != $sb_text)
	{
		$sb_text = $db->qstr($sb_text);
		$xsql = "INSERT INTO {$db_prefix}shoutbox (player_id, sb_text, player_name, sb_date) VALUES (3, $sb_text, 'Webmaster'," . time() . ")";
		$debug_query = $db->Execute($xsql);
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

if ($command=="SAVE")
{
	$sb_text = str_replace("\n", " ", str_replace("\t", " ", htmlspecialchars(clean_words($sb_text))));

	$sb_text = $db->qstr($sb_text );
	$xsql = "UPDATE {$db_prefix}shoutbox SET sb_text=$sb_text WHERE sb_id=$sb_id";
	$debug_query = $db->Execute($xsql);
	db_op_result($debug_query,__LINE__,__FILE__);
}

echo "<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=3>";
if ($command=="EDIT")
{
	$result = $db->Execute("SELECT * FROM {$db_prefix}shoutbox where sb_id=$sb_id");
	db_op_result($debug_query,__LINE__,__FILE__);
	$row = $result->fields;

	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Shoutbox\">";
	echo "<TR nowrap><TD>Edit Shoutbox Message:</TD>";
	echo "<TD><TEXTAREA NAME=sb_text ROWS=10 COLS=60>". stripslashes(stripslashes(rawurldecode($row['sb_text']))) ."</TEXTAREA></TD>";
	echo "<INPUT TYPE=HIDDEN NAME=sb_id VALUE=$row[sb_id]>";
	echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"SAVE\"></TD></TR>";
	echo "</form>";
}

echo "<FORM ACTION=admin.php METHOD=POST>";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Shoutbox\">";
echo "<TR nowrap><TD>Add Shoutbox Message:</TD>";
echo "<TD><TEXTAREA NAME=sb_text ROWS=10 COLS=60></TEXTAREA></TD>";
echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"ADD\"></TD></TR>";
echo "</form>";

if(empty($page))
{
	$page = 1;
}

$entries_per_page = 25;

$res1 = $db->SelectLimit("SELECT count(sb_alli) as total FROM {$db_prefix}shoutbox WHERE sb_alli = 0", 1);
$totalshouts = $res1->fields['total'];
$res1->close();

$start = ($page - 1) * $entries_per_page;
$totalpages = ceil($totalshouts / $entries_per_page);
$currentpage = $page;
if($page < $totalpages)
{
	$nextpage = $page + 1;
}
else
{
	$nextpage = $page;
}

if($page > 1)
{
	$previouspage = $page - 1;
}
else
{
	$previouspage = 1;
}

if ($totalpages > 1)
{
	echo "<tr><td colspan=\"4\"><TABLE border=0 cellpadding=2 cellspacing=1 width=\"100%\">";
	echo "<tr><td colspan=\"3\"><hr></td></tr><TR>";
	echo "	<td align=\"left\" width=\"33%\">";
		if ($currentpage != 1){
	echo "<form action=\"admin.php\" method=\"post\">";
	echo "<input type=\"hidden\" name=\"page\" value=\"$previouspage\">\n";
	echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Shoutbox\">";
	echo "<input type=\"submit\" value=\"$l_shout_prev\">";
	echo "</form>";
		}else{
	echo "			&nbsp;";
		}
	echo "	</td>";
	echo "	<TD align=\"center\" width=\"33%\">";
	echo "<form action=\"admin.php\" method=\"post\">";
	echo "$l_shout_selectpage <select name=\"page\">";
	for($pagenumber=1; $pagenumber <= $totalpages; $pagenumber++)
	{
	echo "	<option value=\"$pagenumber\"";
		if ($currentpage == $pagenumber){
	echo "		selected";
		}
	echo "	> $l_shout_page $pagenumber </option>";
	}
	echo "</select>";
	echo "&nbsp;<input type=\"submit\" value=\"$l_submit\">";
	echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Shoutbox\">";
	echo "</form>";
	echo "</TD>";
	echo "	<td align=\"right\" width=\"33%\">";
		if ($currentpage != $totalpages){
	echo "<form action=\"admin.php\" method=\"post\">";
	echo "<input type=\"hidden\" name=\"page\" value=\"$nextpage\">\n";
	echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Shoutbox\">";
	echo "<input type=\"submit\" value=\"$l_shout_next\">";
	echo "</form>";
		}else{
	echo "			&nbsp;";
		}
	echo "	</td>";
	echo "</tr>";
	echo "<tr><td colspan=\"3\"><hr></td></tr></table></td></tr>";
}
$query = "SELECT * FROM {$db_prefix}shoutbox WHERE sb_alli = 0 ORDER BY sb_date desc ";
$result = $db->SelectLimit($query, $entries_per_page, $start);

while (!$result->EOF && $result)
{
	$row = $result->fields;
	$avatarresult = $db->SelectLimit("SELECT avatar FROM {$db_prefix}players WHERE player_id=$row[player_id]", 1);
	$avatar = $avatarresult->fields['avatar'];
	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Shoutbox\">";
	echo "<TR nowrap><TD><b>Delete or Edit:</b></TD>";
	$date = date("m/d/Y G:i",$row['sb_date']);
	echo "<TD width=450><font color=\"yellow\"><b>". add_smilies(stripslashes(stripslashes(rawurldecode($row['sb_text'])))) ."</b></font></TD>";
	echo "<TD width=150 align=\"center\" valign=\"middle\"><img src=\"images/avatars/$avatar\" width=\"20\" height=\"20\">&nbsp;&nbsp;<b>". $row['player_name'] ."</b><br><font color=\"lime\">$date</font></TD>";
	echo "<INPUT TYPE=HIDDEN NAME=sb_id VALUE=$row[sb_id]>";
	echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"DEL\">&nbsp;&nbsp;&nbsp;<INPUT TYPE=SUBMIT NAME=command VALUE=\"EDIT\"></TD></TR>";
	echo "</FORM>";
	$result->MoveNext();
}
echo "</TABLE>";

?>