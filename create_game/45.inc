<?php
// Step 45 - Configure Debris
$silent = 1;

if($command == "save"){
	$count = count($name);
	for($i = 0; $i < $count; $i++){
//		echo "Updating config variable: <b><i>$name[$i]</i></b> = <b>$value[$i]&nbsp;</b><br>";
		$debug_query = $db->Execute("UPDATE {$db_prefix}class_modules_debris SET enable='$value[$i]' WHERE classname='$name[$i]'");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
}

?>
<br>
<b>Enable and Disable the different Debris types used in the game.</b>
<br><br>
	<table border=1 cellspacing=1 cellpadding=5>
	<form action=create_game.php method=post enctype="multipart/form-data">
<?php
	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">";
	}
?>
	<input type="hidden" name="step" value="44.99">
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
	echo"<input type=\"hidden\" name=\"name[$i]\" value=\"$debristype\">\n";
	echo"<td><input type=\"radio\" name=\"value[$i]\" value=\"1\" $checked[1]><font color=\"#00ff00\">Enabled</font>&nbsp;&nbsp;&nbsp;&nbsp;";
	echo"<input type=\"radio\" name=\"value[$i]\" value=\"0\" $checked[0]><font color=\"#ff0000\">Disabled</font></td></tr>\n";
	$i++;
	$debris_query->Movenext();
}
?>
<table>

<tr><td></td><td><INPUT TYPE=SUBMIT NAME=command VALUE="save"></td><td></td></tr>
</form>
</table>

	<form action=create_game.php method=post enctype="multipart/form-data">
<?php
	foreach($_POST as $key=>$value){ 
		echo "<input type=\"hidden\" name=\"$key\" value=\"$value\">";
	}
?>
	<input type=hidden name=step value=45>
	<INPUT TYPE=SUBMIT NAME=command VALUE="Continue Universe Creation">
	</form>
