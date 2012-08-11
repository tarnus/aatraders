<?php
// 2: Front Page News
// This tool will allow editing of the news that is displayed on the login page for the game.

get_post_ifset("id, an_text");

if ($command=="DEL")
{
	$xsql = "DELETE FROM {$db_prefix}adminnews WHERE an_id = $id";
	$result = $db->Execute($xsql);
}

if ($command=="ADD" && !empty($an_text))
{
	$xsql = "INSERT INTO {$db_prefix}adminnews (an_text) VALUES (" . $db->qstr($an_text) . ")";
	$debug_query = $db->Execute($xsql);
	db_op_result($debug_query,__LINE__,__FILE__);
}

if ($command=="SAVE" && !empty($an_text))
{
	$xsql = "UPDATE {$db_prefix}adminnews SET an_text=" . $db->qstr($an_text) . " WHERE an_id=$id";
	$debug_query = $db->Execute($xsql);
	db_op_result($debug_query,__LINE__,__FILE__);
}

echo "<tr><td><TABLE BORDER=0 CELLSPACING=0 CELLPADDING=3>";
if ($command=="EDIT")
{
	$result = $db->Execute("SELECT * FROM {$db_prefix}adminnews where an_id=$id");
	db_op_result($debug_query,__LINE__,__FILE__);
	$row = $result->fields;

	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Front_Page_News\">";
	echo "<TR nowrap><TD>Edit Admin News:</TD>";
	echo "<TD><TEXTAREA NAME=an_text ROWS=10 COLS=60>$row[an_text]</TEXTAREA></TD>";
	echo "<INPUT TYPE=HIDDEN NAME=id VALUE=$row[an_id]>";
	echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"SAVE\"></TD></TR>";
	echo "</form>";
}

echo "<FORM ACTION=admin.php METHOD=POST>";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Front_Page_News\">";
echo "<TR nowrap><TD>Add Admin News:</TD>";
echo "<TD><TEXTAREA NAME=an_text ROWS=10 COLS=60></TEXTAREA></TD>";
echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"ADD\"></TD></TR>";
echo "</form>";
$result = $db->Execute("SELECT * FROM {$db_prefix}adminnews ORDER BY an_id DESC");
while (!$result->EOF && $result)
{
	$row = $result->fields;
	echo "<FORM ACTION=admin.php METHOD=POST>";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Front_Page_News\">";
	echo "<TR nowrap><TD>Delete or Edit:</TD>";
	echo "<TD width=600>$row[an_text]</TD>";
	echo "<INPUT TYPE=HIDDEN NAME=id VALUE=$row[an_id]>";
	echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"DEL\">&nbsp;&nbsp;&nbsp;<INPUT TYPE=SUBMIT NAME=command VALUE=\"EDIT\"></TD></TR>";
	echo "</FORM>";
	$result->MoveNext();
}
echo "</TABLE></td></tr>";
?>