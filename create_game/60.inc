<?php
// Step 60 - Configure ports, sectors, warp links, ect values for actually building the entire game

if($top_banner != ''){
	$fs = @fopen($gameroot.'config/banner_top.inc', 'w');
	@fwrite($fs, "<table border='0' align='center'><tr><td>". stripslashes($top_banner) . "</td></tr></table>");
	@fclose($fs);
}

if($bottom_banner != ''){
	$fs = @fopen($gameroot.'config/banner_bottom.inc', 'w');
	@fwrite($fs, "<table border='0' align='center'><tr><td>" . stripslashes($bottom_banner) . "</td></tr></table>");
	@fclose($fs);
}

$title = array();
$body = array();
$title[0] = "Percentage Upgrade";
$body[0] = "This is the percentage of sectors that may contain Upgrade Ports.";
$title[1] = "Percentage Device";
$body[1] = "This is the percentage of sectors that may contain Device Ports.";
$title[2] = "Percentage Spacedock";
$body[2] = "This is the percentage of sectors that may contain Spacedocks.";
$title[3] = "Percentage of Alliance Upgrade/Device Ports";
$body[3] = "This is the percentage of Upgrade/Device Ports that will be turned into Alliance ports.";
$title[4] = "Alliance Casino Ports";
$body[4] = "This is the percentage of Alliance Upgrade/Device Ports that will be converted into Casino Ports.";
$title[6] = "Initial Sell Percentage";
$body[6] = "This is the percentage of the maximum amount of commodities a port will start with for selling.";
$title[7] = "Initial Buy Percentage";
$body[7] = "This is the percentage of the maximum amount of commodities a port will start with for buying.";
$title[8] = "Federation Sectors";
$body[8] = "This is the percentage of sectors that will be controlled byt the Federation.";
$title[9] = "Links Per Sector";
$body[9] = "This is the maximum number of One Way links per sector.  This number can go to a maximum of 2 times the set value with Two Way links.";
$title[10] = "Two Way Links";
$body[10] = "This is the maximum percentage of sectors that can contain Two Way warp links.  The number is usually well below the maximum percentage entered.";
$title[11] = "Unowned Planets";
$body[11] = "This is the maximum percentage of sectors that can contain Unowned Planets.  The number is usually well below the maximum percentage entered.";
$title[12] = "Independent Planets";
$body[12] = "This is the maximum percentage of Unowned planets that will be changed to Independent ownership.  The planets will be populated with colonists, defenses, tech levels and sector defenses.";
$title[13] = "Colonist Percentage";
$body[13] = "This is the maximum percentage of the maximum number of colonists to place on Based Independent Planets based upon each planets overall tech level average.";
$title[14] = "Minimum Tech Level";
$body[14] = "This is the minimum tech level to be used when creating Independent Planets.  A random tech level between the Minimum and Maximum will be used when generating each tech level.";
$title[14] = "Maximum Tech Level";
$body[14] = "This is the maximum tech level to be used when creating Independent Planets.  A random tech level between the Minimum and Maximum will be used when generating each tech level.";


echo "<table>";
echo "<tr><td><br><br><b><u>Base/Planet Setup</u></b></td><td>Suggested value</td><td>Safe field range</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[0]', '$body[0]');\" onMouseout=\"hideddrivetip()\"><td>Percentage Upgrade</td><td><input type=text name=upgrades size=5 maxlength=5 value=1></td><td>[1-95]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[1]', '$body[1]');\" onMouseout=\"hideddrivetip()\"><td>Percentage Device</td><td><input type=text name=devices size=5 maxlength=5 value=1></td><td>[1-95]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[2]', '$body[2]');\" onMouseout=\"hideddrivetip()\"><td>Percentage Spacedock</td><td><input type=text name=docks size=5 maxlength=5 value=1></td><td>[1-95]</td></tr>\n";

$silent = 1;

$cargo_query = $db->Execute("SELECT class, classname, default_create_percent from {$db_prefix}class_modules_commodities where cargoport=1 and cargosellbuy != 1 order by defaultcargoplanet DESC");
db_op_result($cargo_query,__LINE__,__FILE__);
$default_create_ratio = 5 / $cargo_query->RecordCount();

while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['classname'];
	$cargoclass = $cargo_query->fields['class'];
	$default_create_percent = $cargo_query->fields['default_create_percent'] * $default_create_ratio;
	echo "<tr onMouseover=\"ddrivetip('Percentage " . ucwords($cargotype) . "', 'This is the percentage of sectors that may contain " . ucwords($cargotype) . ".');\" onMouseout=\"hideddrivetip()\"><td>Percentage " . ucwords($cargotype) . "</td><td><input type=text name=\"$cargoclass\" size=\"5\" value=\"$default_create_percent\"></td><td>[0.0001-95.0001]</td></tr>\n";
	$cargo_query->Movenext();
}

echo "<tr onMouseover=\"ddrivetip('$title[3]', '$body[3]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of Upgrade/Device ports Alliance Owned</td><td><input type=text name=percentkabal size=5 maxlength=5 value=10></td><td>[1-95]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[4]', '$body[4]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of Alliance Sectors with Casino Ports</td><td><input type=text name=casinos size=5 maxlength=5 value=25></td><td>[1-95]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[6]', '$body[6]');\" onMouseout=\"hideddrivetip()\"><td>Initial Commodities to Sell<br><td><input type=text name=initscommod size=6 maxlength=6 value=100.00> % of max&nbsp;&nbsp;</td><td></td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[7]', '$body[7]');\" onMouseout=\"hideddrivetip()\"><td>Initial Commodities to Buy<br><td><input type=text name=initbcommod size=6 maxlength=6 value=100.00> % of max&nbsp;</td><td></td></tr>";
echo "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
echo "<tr><td><b><u>Sector/Link Setup</u></b></td><td></td><td></td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[8]', '$body[8]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of sectors as Federation sectors</TD><TD><INPUT TYPE=TEXT NAME=fedsecs_percentage SIZE=3 MAXLENGTH=3 VALUE=10></TD><td>[1-100]</td></TR>";
echo "<tr onMouseover=\"ddrivetip('$title[9]', '$body[9]');\" onMouseout=\"hideddrivetip()\"><td>Maximum number of links per sector &nbsp;</td><td><input type=text name=linksper size=2 maxlength=2 value=5></td><td>[1-10]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[10]', '$body[10]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of sectors with two-way links &nbsp;</td><td><input type=text name=twoways size=3 maxlength=3 value=40></td><td>[1-100]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[11]', '$body[11]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of sectors with unowned planets &nbsp;</td><td><input type=text name=planets size=3 maxlength=3 value=3></td><td>[1-100]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[12]', '$body[12]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of based independant planets from unowned planets &nbsp;</td><td><input type=text name=basedplanets size=3 maxlength=3 value=10></td><td>[1-100]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[13]', '$body[13]');\" onMouseout=\"hideddrivetip()\"><td>Percentage of max colonists to place on based planets&nbsp;</td><td><input type=text name=basedcolonists size=3 maxlength=3 value=1></td><td>[1-100]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[14]', '$body[14]');\" onMouseout=\"hideddrivetip()\"><td>Min tech level on based planets&nbsp;</td><td><input type=text name=minbasedlevel size=3 maxlength=3 value=" . round(15 * ($max_tech_level / 54)) . "></td><td>[1-" . round(30 * ($max_tech_level / 54)) . "]</td></tr>";
echo "<tr onMouseover=\"ddrivetip('$title[14]', '$body[14]');\" onMouseout=\"hideddrivetip()\"><td>Max tech level on based planets&nbsp;</td><td><input type=text name=maxbasedlevel size=3 maxlength=3 value=" . round(25 * ($max_tech_level / 54)) . "></td><td>[1-" . round(40 * ($max_tech_level / 54)) . "]</td></tr>";
echo "<tr><td></td><td><input type=hidden name=step value=60></td><td></td></tr>";
echo "</table>";
echo "<input type=reset value=Reset>";

?>