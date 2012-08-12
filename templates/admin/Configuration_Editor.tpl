<tr><td><FORM ACTION="{$returnlink}" METHOD="POST"  enctype="multipart/form-data">
<table border=1 cellspacing=1 cellpadding=5>
<tr>
<td><b>Variable Name</b></td>
<td><b>Variable Value</b></td>
<td><b>Variable Description</b></td>
</tr>
{php}
for($i = 0; $i < $count; $i++){
  echo"<tr>\n";
    echo"<td>\n";
      echo"<b>$db_config_name[$i] :</b>&nbsp;&nbsp;\n";
    echo"</td>\n";
   echo" <td>\n";
      echo"<input type=\"hidden\" name=\"name[$i]\" value=\"$db_config_name[$i]\">\n";
		if($db_config_input_type[$i] == 'list')
		{
			$selections = explode(",", $db_config_input_selections[$i]);
			$selection_count = count($selections);
			echo "<select name=\"value[$i]\">";
			for($item = 0; $item < $selection_count; $item++)
			{
				$values = explode("=", $selections[$item]);
				$value = trim($values[0]);
				if($value == $db_config_value[$i])
					$checked = "selected";
				else $checked = "";
				echo "<option value=\"$value\" $checked>" . trim($values[1]) . "</option>\n";
			}
			echo "</select>";
		}
		else
		if($db_config_input_type[$i] == 'radio')
		{
			$selections = explode(",", $db_config_input_selections[$i]);
			$selection_count = count($selections);
			for($item = 0; $item < $selection_count; $item++)
			{
				$values = explode("=", $selections[$item]);
				$value = trim($values[0]);
				if($value == $db_config_value[$i])
					$checked = "checked";
				else $checked = "";
				echo"<input type=\"radio\" name=\"value[$i]\" value=\"" . $value . "\" $checked>" . trim($values[1]) . "<br>\n";
			}
		}
		else
		{
	      echo"<input type=\"text\" name=\"value[$i]\" value=\"$db_config_value[$i]\" size=\"40\">\n";
		}
    echo"</td>\n";
    echo"<td>\n";
      echo "<font color=\"#00ff00\"><i><b>$db_config_info[$i]</b></i></font>\n";
    echo"</td>\n";
  echo"</tr>\n";
}
{/php}

<tr><TD ALIGN=center colspan=3><INPUT TYPE=SUBMIT NAME=command VALUE="save">
<input type=hidden name=count value={$count}>
<input type="hidden" name="game_number" value="{$game_number}">
<input type=hidden name=admin_password value={$admin_password}>
<input type="hidden" name="menu" value="Editor_Configuration"></td></tr>
</table>
</form>
</td></tr>