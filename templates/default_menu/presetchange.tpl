<H1>{$title}</H1>

<table width="400" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{php}
	for($totals = 0; $totals < $presettotal; $totals++){
		if ($presettype[$totals] == 1)
		{
			echo $presetjunk[$totals]."<br>";
		}else{
			echo "$l_pre_set $totals: <a href=main.php?move_method=real&engage=1&destination=".$preset[$totals].">".$preset[$totals]."</a> - $l_pre_info: $presetjunk[$totals]<br>";
		}
	}
{/php}
</td></tr>

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
