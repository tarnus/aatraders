<h1>{$title}</h1>


<table border="1" cellspacing="1" cellpadding="2" width="80%" align="center">
	<TR BGCOLOR="#585980">
		<TD align="center"><font color="white"><B>{$l_probe_named}</B></font></TD>
	</TR>
	<TR BGCOLOR="#23244F">
		<TD align="center">
			<form action="probes_upgrade.php?probe_id={$probe_id}&command=orders_finish" method="post">
			<table border="1" cellspacing="0" cellpadding="0" align="center">
				<tr>
					<td colspan="2"><div align="center">{$l_probe_type}</div></td><td colspan="10"><div align="center">Probe Settings</div></td>
				</tr>
					{foreach key=key value=item from=$probetypeinfo}
<tr><td colspan="2"><div align="left">
<input type="radio" name="new_type" value="{$key}" 
	{if $probe_type == $key}
		checked
	{/if}
> {$probetypeinfo[$key]}<br><hr>
{$probedescription[$key]} 
</div></td>
{php}

for($i = 0; $i < $probeordercount[$key]; $i++){
	$newkey = $key . $i;
    echo"<td>\n";
         echo"<b><font color=\"#00ff00\"><i><b>$info[$newkey]</b></i></font> :</b>&nbsp;&nbsp;<br>\n";
		if($input_type[$newkey] == 'list')
		{
			$selections = explode(",", $input_selections[$newkey]);
			$selection_count = count($selections);
			echo "<select name=\"$variable_name[$newkey]\">";
			for($item = 0; $item < $selection_count; $item++)
			{
				$values = explode("=", $selections[$item]);
				$value = trim($values[0]);
				if($value == $variable_value[$newkey])
					$checked = "selected";
				else $checked = "";
				echo "<option value=\"$value\" $checked>" . trim($values[1]) . "</option>\n";
			}
			echo "</select>";
		}
		else
		if($input_type[$newkey] == 'radio')
		{
			$selections = explode(",", $input_selections[$newkey]);
			$selection_count = count($selections);
			for($item = 0; $item < $selection_count; $item++)
			{
				$values = explode("=", $selections[$item]);
				$value = trim($values[0]);
				if($value == $variable_value[$newkey])
					$checked = "checked";
				else $checked = "";
				echo"<input type=\"radio\" name=\"$variable_name[$newkey]\" value=\"" . $value . "\" $checked>" . trim($values[1]) . "<br>\n";
			}
		}
		else
		{
	      echo"<input type=\"text\" name=\"$variable_name[$newkey]\" value=\"$variable_value[$newkey]\" size=\"40\">\n";
		}
   echo" </td>\n";
}
{/php}
</tr>
<tr><td colspan="10">
	<hr>
</td>
</tr>
{/foreach}

				<tr>
					<td><input type="reset" value="{$l_reset}"></td>
					<td colspan="4">&nbsp;</td>
					<td align="right"><input type="submit" value="{$l_submit}"></td>
				</tr>
			</table>
			</form>
		</TD>
	</TR>
</TABLE>
<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
	<tr>
		<td><a href="probes_upgrade.php?probe_id={$probe_id}">{$l_clickme}</a> {$l_probe_linkback}.
		</td>
	</tr>
	<tr><td><br><br>{$gotomain}<br><br></td></tr>
</table>
