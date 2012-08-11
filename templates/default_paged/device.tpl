<h1>{$title}</h1>

<table width="650" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
  <tr ">
	<td colspan="3" align="center">{$l_device_expl}<br><br></td>
  </tr>
  <tr">
	<td><b>{$l_device}</b></td>
	<td><b>{$l_qty}</b></td>
  </tr>

<!-- mines/torpedoes section -->
  <tr>
	<td><a href=defense_deploy.php>{$l_mines}/ {$l_fighters}</a></td>
	<td>{$dev_torps} / {$dev_fighters}</td>
  </tr>
<!-- mines/torpedoes section end -->
{php}
for($i = 0; $i < count($deviceclass); $i++)
{
echo"
  <tr>
	<td>";
	if($deviceprogram[$i] != '')
		echo "<a href=" . $deviceprogram[$i] . ">";
	echo $devicename[$i] . "</a></td>
	<td>" . $deviceamount[$i] . "</td>
  </tr>";
}
{/php}
										<tr><td colspan="3"><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
