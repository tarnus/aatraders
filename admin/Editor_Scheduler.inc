<?php
// 2: Scheduler
// This tool will allow you to disable/enable any schedule and change the execution frequency.

get_post_ifset("command, name, value, ticks_full, ticks_left, execution_order");

if($command == "save"){
	$count = count($name);
	for($i = 0; $i < $count; $i++){
//		echo "Updating: <b><i>$name[$i]</i></b> = <b>$value[$i]&nbsp;</b><br>";
//		echo "Updating: <b><i>ticks_full</i></b> = <b>$ticks_full[$i]&nbsp;</b><br>";
//		echo "Updating: <b><i>ticks_left</i></b> = <b>$ticks_left[$i]&nbsp;</b><br>";
//		echo "Updating: <b><i>execution_order</i></b> = <b>$execution_order[$i]&nbsp;</b><hr>";
//$db->debug=1;
		$set = "";
		if(is_numeric($ticks_full[$i]))
		{
			$set = "ticks_full='$ticks_full[$i]', ";
		}
		if(is_numeric($ticks_left[$i]))
		{
			$set .= "ticks_left='$ticks_left[$i]', ";
		}
		if(is_numeric($execution_order[$i]))
		{
			$set .= "execution_order='$execution_order[$i]', ";
		}

		$debug_query = $db->Execute("UPDATE {$db_prefix}scheduler SET " . $set . "enable_schedule='$value[$i]' WHERE sched_file='$name[$i]'");
		db_op_result($debug_query,__LINE__,__FILE__);
//$db->debug=0;
	}
}

?>
<tr>
<td>
<table align="center" border="1" cellpadding="5" cellspacing=0>
	<form action=admin.php method=post>
<?php

$scheduler_query = $db->Execute("SELECT * from {$db_prefix}scheduler order by execution_order");
db_op_result($scheduler_query,__LINE__,__FILE__);

$i = 0;
$value = array();
$name = array();
$ticks_full = array();
$ticks_left = array();
$execution_order = array();
$color = "#000000";
$color1 = "#000000";
$color2 = "#222222";

echo "<tr bgcolor=\"#007733\"><td align=\"center\">Execution Order</td>";
echo "<td align=\"center\">Scheduler File</td>";
echo "<td align=\"center\">Enable/Disable</td>";
echo "<td align=\"center\">Minutes Passed</td>";
echo "<td align=\"center\">Execution Minutes</td>";
echo "<td align=\"center\">Information</td>";
echo "<td align=\"center\">Last Run</td>";
echo "</tr>\n";

while (!$scheduler_query->EOF)
{
	$sched_file = $scheduler_query->fields['sched_file'];
	$enable = $scheduler_query->fields['enable_schedule'];
	$execution_order = $scheduler_query->fields['execution_order'];
	$ticks_left = $scheduler_query->fields['ticks_left'];
	$ticks_full = $scheduler_query->fields['ticks_full'];
	$extra_info = $scheduler_query->fields['extra_info'];
	$last_run = $scheduler_query->fields['last_run'];
	$checked = array();

	$newcolor = $color;
	if($enable == 1)
	{
		$checked[1] = "checked";
	}
	else
	{
		$checked[0] = "checked";
		$newcolor = "#330000";
	}

	echo "<tr bgcolor=\"$newcolor\"><td align=\"center\"><input size=\"5\" type=\"text\" name=\"execution_order[$i]\" value=\"$execution_order\"></td>";
	echo "<td align=\"center\">" . $sched_file . "</td>";
	echo "<td><input type=\"radio\" name=\"value[$i]\" value=\"1\" $checked[1]><font color=\"#00ff00\">Enabled</font><br>";
	echo "<input type=\"radio\" name=\"value[$i]\" value=\"0\" $checked[0]><font color=\"#ff0000\">Disabled</font></td>";
	echo "<td align=\"center\"><input size=\"7\" type=\"text\" name=\"ticks_left[$i]\" value=\"$ticks_left\"></td>";
	echo "<td align=\"center\"><input size=\"7\" type=\"text\" name=\"ticks_full[$i]\" value=\"$ticks_full\"></td>";
	echo "<td>" . $extra_info . "</td>";
	echo "<td>" . $last_run . "</td>";
	if($color == $color1)
	{
		$color = $color2;
	}
	else
	{
		$color = $color1;
	}
	echo "</tr>\n";
	echo"<input type=\"hidden\" name=\"name[$i]\" value=\"$sched_file\">\n";
	$i++;
	$scheduler_query->Movenext();
}
?>
</table>
</td>
</tr>
<?php
echo "<tr><td colspan=\"2\" align=\"center\"><INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Scheduler\">";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=SUBMIT NAME=command VALUE=\"save\"></td></tr>"
?>
</form>


