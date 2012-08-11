<?php
// 2: Debris
// This tool will enable/disable any Debris used in the game.

get_post_ifset("command, name, value");

if($command == "save"){
	$count = count($name);
	for($i = 0; $i < $count; $i++){
//		echo "Updating config variable: <b><i>$name[$i]</i></b> = <b>$value[$i]&nbsp;</b><br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}class_modules_debris SET enable='$value[$i]' WHERE classname='$name[$i]'");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

?>
<tr>
<td>
<table align="center" border="1" cellpadding="5" cellspacing=0>
	<form action=admin.php method=post>
<?php

$debris_query = $db->Execute("SELECT classname, enable from {$db_prefix}class_modules_debris");
db_op_result($debris_query,__LINE__,__FILE__);

$i = 0;
$value = array();
$name = array();

while (!$debris_query->EOF) 
{
	$debristype = $debris_query->fields['classname'];
	$enable = $debris_query->fields['enable'];
	$checked = array();

	if($enable == 1)
		$checked[1] = "checked";
	else $checked[0] = "checked";

	echo "<tr><td>Debris Type: " . $debristype . "</td>";
	echo"<td><input type=\"radio\" name=\"value[$i]\" value=\"1\" $checked[1]><font color=\"#00ff00\">Enabled</font>&nbsp;&nbsp;&nbsp;&nbsp;";
	echo"<input type=\"radio\" name=\"value[$i]\" value=\"0\" $checked[0]><font color=\"#ff0000\">Disabled</font></td></tr>\n";
	echo"<input type=\"hidden\" name=\"name[$i]\" value=\"$debristype\">\n";
	$i++;
	$debris_query->Movenext();
}
?>
</table>
</td>
</tr>
<?php
echo "<tr><td colspan=\"2\" align=\"center\"><INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Debris\">";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=SUBMIT NAME=command VALUE=\"save\"></td></tr>"
?>
</form>


