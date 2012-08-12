<?php
// Step 70 - Review all game setup values before actually creating game database entries

$fedsecs = intval($_POST['sektors'] * ($_POST['fedsecs_percentage'] / 100));

if ($fedsecs > $_POST['sektors']) 
{
	echo "The number of Federation sectors must be smaller than the size of the universe!";
	break;
}

if ($_POST['linksper'] > $link_max)
{
	echo "The average number of links per sector must not be more than the max number of links per sector!<br>";
	echo "We have lowered it to the max number of links per sector.";
	$_POST['linksper'] = $link_max;
}

$portstotal = 0;
$portcount = 0;

$silent = 1;
$cargo_query = $db->Execute("SELECT classname from {$db_prefix}class_modules_commodities where cargoport=1 and cargosellbuy != 1");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['classname'];
	$ports[$portcount] = round($_POST['sektors'] * $_POST[$cargotype]/100);
	$portstotal += $ports[$portcount];
	$portcount++;
	$cargo_query->Movenext();
}
$cargo_query->close();

$upp = round($_POST['sektors'] * $_POST['devices']/100);
$spp = round($_POST['sektors'] * $_POST['upgrades']/100);
$dpp = round($_POST['sektors'] * $_POST['docks']/100);
$cpp = round($_POST['sektors'] * $_POST['casinos']/100);
$kpp = round(($upp + $spp + $dpp) * $_POST['percentkabal']/100);
$cpp = round($kpp * $_POST['casinos']/100);
$fixedtotal = round($portstotal * $_POST['percentkabal']/100);
$empty = $_POST['sektors']-$upp-$spp-$dpp-$portstotal-$enp;
$nump = round ($_POST['sektors'] * $_POST['planets']/100);
$numbp = round ($nump * $_POST['basedplanets']/100);
$nump = $nump - $numbp;
echo "So you would like your ".($_POST['sektors'])." sector universe to have:<BR><BR>";
echo "$upp device ports<BR>";
echo "$spp upgrade ports<BR>";
echo "$dpp spacedock ports<BR><br>";

$portcount = 0;
$cargo_query = $db->Execute("SELECT class, classname from {$db_prefix}class_modules_commodities where cargoport=1 and cargosellbuy != 1 order by defaultcargoplanet DESC");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$portclass = $cargo_query->fields['class'];
	$porttype = $cargo_query->fields['classname'];
	$ports[$portcount] = round($_POST['sektors'] * $_POST[$portclass]/100);
	echo $ports[$portcount] . " " . ucwords($porttype) . " Commodity ports with normal prices<BR>";
	echo "<input type=hidden name=$portclass value=$ports[$portcount]>\n";
	$portcount++;
	$cargo_query->Movenext();
}
$cargo_query->close();

echo "$kpp Alliance owned Device/Upgrade ports<BR>";
echo "$cpp Alliance owned Casino ports<BR><br>";
echo "$_POST[initscommod]% initial commodities to sell<BR>";
echo "$_POST[initbcommod]% initial commodities to buy<BR><br>";
echo "$empty empty sectors<BR>";
echo "$fedsecs Federation sectors<BR><br>";
echo "$nump planets will be unowned<BR>";
echo "$numbp planets will be based and independant<BR><br>";
echo "Initial based and independant planets will have from 1 - ".NUMBER(floor(($basedcolonists/100) * $colonist_limit))." colonists<BR>";
if($minbasedlevel < 1 * round($max_tech_level / 54))
	$minbasedlevel = 1 * round($max_tech_level / 54);
if($minbasedlevel > round(30 * ($max_tech_level / 54)))
	$minbasedlevel = round(30 * ($max_tech_level / 54));
if($maxbasedlevel < $minbasedlevel)
	$maxbasedlevel = $minbasedlevel;
if($maxbasedlevel > round(40 * ($max_tech_level / 54)))
	$maxbasedlevel = round(40 * ($max_tech_level / 54));
echo "Initial based and independant planets will have random levels from $minbasedlevel to $maxbasedlevel<BR><BR>";
echo "Maximum " . (floor($_POST['linksper'] * $_POST['sektors']) - floor(($_POST['twoways']/100) * floor($_POST['linksper'] * $_POST['sektors']))) . " One-Way and Two-Way Links<br>";
echo "Maximum " . floor(($_POST['twoways']/100) * (floor($_POST['linksper'] * $_POST['sektors']) - floor(($_POST['twoways']/100) * floor($_POST['linksper'] * $_POST['sektors'])))) . " Two-Way Links<br>";
echo "<br><br>\n";
echo "&nbsp;<input type=\"checkbox\" name=\"autorun\" value=\"1\"> Check to Enable Auto Run (no pausing between each install phase)<br><br>";
echo "<input type=hidden name=step value=70>";
echo "<input type=hidden name=basedcolonists value=$basedcolonists>";
echo "<input type=hidden name=minbasedlevel value=$minbasedlevel>";
echo "<input type=hidden name=maxbasedlevel value=$maxbasedlevel>";
echo "<input type=hidden name=numbp value=$numbp>";
echo "<input type=hidden name=fedsecs value=$fedsecs>";
echo "<input type=hidden name=upp value=$upp>";
echo "<input type=hidden name=spp value=$spp>";
echo "<input type=hidden name=dpp value=$dpp>";
echo "<input type=hidden name=cpp value=$cpp>";
echo "<input type=hidden name=kpp value=$kpp>";
echo "<input type=hidden name=portcount value=$portcount>";
echo "<input type=hidden name=fixedtotal value=$fixedtotal>";
echo "<input type=hidden name=nump value=$nump>";
echo "<FONT COLOR=RED>";
echo "WARNING: THIS WILL TAKE A LONG TIME ONCE YOU CLICK ON 'SUBMIT'!<br>DO NOT CLICK SUBMIT A SECOND TIME OR YOU MAY CAUSE PROBLEMS BUILDING THE DATABASE!</FONT>";

?>