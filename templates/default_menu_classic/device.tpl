<h1>{$title}</h1>

<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
  <tr bgcolor="#000000">
	<td colspan="3" align="center">{$l_device_expl}<br><br></td>
  </tr>
  <tr bgcolor="#000000">
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
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
