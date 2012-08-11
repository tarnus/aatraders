<h1>{$title}</h1>

<table width="50%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>

<td align="center">{$l_g3d_wait}</td></tr>
<tr><td align="center">
<img src="galaxy_map3dimage.php?shipsector={$shipsector}&arm={$arm}&distance={$distance}" border="0" alt="{$l_g3d_wait}">
</td></tr>
<tr><td align="center"><br>
<form action="galaxy_map3d.php" method="post" enctype="multipart/form-data">
<select name="arm">
{$armdropdown}
</select><br><br>
<input type="submit" name="view" value="View Arm">
</form>
</td></tr>

	<form action="galaxy_map3d.php" method="post" enctype="multipart/form-data">
	<TR><TD align='center'><br>
	{$l_glxy_select}&nbsp;
	<select name="turns">
	{php}
		echo "	<option value=\"\" " . ($turns == 0 ? "selected" : "") . ">All</option>\n";
		echo "	<option value=1 " . ($turns == 1 ? "selected" : "") . ">1</option>\n";
		echo "	<option value=2 " . ($turns == '2' ? "selected" : "") . ">2</option>\n";
		echo "	<option value=3 " . ($turns == '3' ? "selected" : "") . ">3</option>\n";
		echo "	<option value=4 " . ($turns == '4' ? "selected" : "") . ">4</option>\n";
		echo "	<option value=5 " . ($turns == '5' ? "selected" : "") . ">5</option>\n";
		echo "	<option value=10 " . ($turns == '10' ? "selected" : "") . ">10</option>\n";
		echo "	<option value=20 " . ($turns == '20' ? "selected" : "") . ">20</option>\n";
		echo "	<option value=30 " . ($turns == '30' ? "selected" : "") . ">30</option>\n";
		echo "	<option value=40 " . ($turns == '40' ? "selected" : "") . ">40</option>\n";
		echo "	<option value=50 " . ($turns == '50' ? "selected" : "") . ">50</option>\n";
		echo "	<option value=60 " . ($turns == '60' ? "selected" : "") . ">60</option>\n";
		echo "	<option value=70 " . ($turns == '70' ? "selected" : "") . ">70</option>\n";
		echo "	<option value=80 " . ($turns == '80' ? "selected" : "") . ">80</option>\n";
		echo "	<option value=90 " . ($turns == '90' ? "selected" : "") . ">90</option>\n";
		echo "	<option value=100 " . ($turns == '100' ? "selected" : "") . ">100</option>\n";
		echo "	<option value=120 " . ($turns == '120' ? "selected" : "") . ">120</option>\n";
		echo "	<option value=140 " . ($turns == '140' ? "selected" : "") . ">140</option>\n";
		echo "	<option value=160 " . ($turns == '160' ? "selected" : "") . ">160</option>\n";
		echo "	<option value=180 " . ($turns == '180' ? "selected" : "") . ">180</option>\n";
		echo "	<option value=200 " . ($turns == '200' ? "selected" : "") . ">200</option>\n";
		echo "	<option value=250 " . ($turns == '250' ? "selected" : "") . ">250</option>\n";
		echo "	<option value=300 " . ($turns == '300' ? "selected" : "") . ">300</option>\n";
	{/php}
	</select>
	{$l_glxy_turns}&nbsp;&nbsp;&nbsp;<input type="submit" value="{$l_submit}">
	</TD></tr>
	</form>	

<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>

