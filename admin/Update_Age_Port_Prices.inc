<?php
// 8: Age Port Prices
// This tool will Re-Seed all port prices as if the universe was newly created.  no new ports will be added.  Use the Age Port Prices menu item if you wish port prices to reflect game time.

get_post_ifset("command, multiplier, minutes");

	echo "
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" bgcolor=\"#000000\">
		<tr BGCOLOR=\"#585980\">
			<td><b>Sector</b></td>
			<td><B>Commodity</B></td>
			<td><B>Price</B></td>
			<td><B>Cost Per Hold</B></td>
			<td><B>Start Price</B></td>
			<td><B>Start CPH</B></td>
		</tr>";
$cargo_query = $db->Execute("SELECT classname, price, delta, itemlimit, hold_space, fixed_start_price, increaserate from {$db_prefix}class_modules_commodities where cargoport=1 order by price");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['classname'];

	$res = $db->SelectLimit("SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe_ports.commodity_type, {$db_prefix}universe_ports.commodity_price, {$db_prefix}universe_ports.commodity_amount
							FROM {$db_prefix}universe , {$db_prefix}universe_ports 
							WHERE {$db_prefix}universe_ports.commodity_type = " . $db->qstr($cargotype) . "
							AND {$db_prefix}universe_ports.sector_id = {$db_prefix}universe.sector_id
							AND {$db_prefix}universe.port_type != {$db_prefix}universe_ports.commodity_type
							AND {$db_prefix}universe.sg_sector = 0
							ORDER BY {$db_prefix}universe_ports.commodity_price DESC", 1);
	db_op_result($res,__LINE__,__FILE__);

	$offered_buy_price = max($res->fields['commodity_price'] + $cargo_query->fields['price'] + $cargo_query->fields['delta'] * $cargo_query->fields['itemlimit'] / $cargo_query->fields['itemlimit'] * $inventory_factor, 0.01);
	if($cargo_query->fields['increaserate'] == 0)
	{
		$cargo_query->fields['fixed_start_price'] /= 2;
	}
	$original_buy_price = max($cargo_query->fields['fixed_start_price'] + $cargo_query->fields['price'] + $cargo_query->fields['delta'] * $cargo_query->fields['itemlimit'] / $cargo_query->fields['itemlimit'] * $inventory_factor, 0.01);
	echo "<tr BGCOLOR=\"#3A3B6E\">
			<td><a href=\"main.php?move_method=real&engage=1&destination=" . rawurldecode($res->fields['sector_name']) . "\">" . $res->fields['sector_name'] . "</a></td>
			<TD>" . ucwords($res->fields['commodity_type']) . "</td>
			<TD>" . NUMBER(floor($offered_buy_price)) . "</td>
			<TD>" . NUMBER(floor($offered_buy_price / $cargo_query->fields['hold_space'])) . "</td>
			<TD>" . NUMBER(floor($original_buy_price)) . "</td>
			<TD>" . NUMBER(floor($original_buy_price / $cargo_query->fields['hold_space'])) . "</td>
		</tr>";
	$cargo_query->Movenext();
}
$cargo_query->close();
echo "	</table>
</div>";

if($command == "Age Prices")
{
	$number = $multiplier;

	if($minutes == 1)
	{
		$multiplier *= 288;
		$offset = 1;
	}
	else
	{
		$offset = 288;
	}

	echo "<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" bgcolor=\"#000000\">
<tr>
<td>";
flush();
$cargo_query = $db->Execute("SELECT classname, increaserate, price from {$db_prefix}class_modules_commodities where cargoport=1");
db_op_result($cargo_query,__LINE__,__FILE__);
while (!$cargo_query->EOF) 
{
	$cargotype = $cargo_query->fields['classname'];
	$increaserate = $cargo_query->fields['increaserate'];

	if($increaserate != 0)
	{
		echo "\nAging " . $cargotype . " Ports by $number days.<br>";
		flush();
		for($i = 0; $i < $multiplier; $i++)
		{
//			echo "\nUpdating " . $cargotype . " Buy Port Prices...<br>";
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports, {$db_prefix}universe SET 
								{$db_prefix}universe_ports.commodity_price={$db_prefix}universe_ports.commodity_price+((RAND()*$increaserate * $offset) * $port_price_control)
								WHERE {$db_prefix}universe.port_type != {$db_prefix}universe_ports.commodity_type
								AND {$db_prefix}universe.sector_id = {$db_prefix}universe_ports.sector_id
								AND {$db_prefix}universe_ports.commodity_type = " . $db->qstr($cargotype));
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();
//			echo "\nUpdating " . $cargotype . " Sell Port Prices...<br>";
			$debug_query = $db->Execute("UPDATE {$db_prefix}universe_ports, {$db_prefix}universe SET 
								{$db_prefix}universe_ports.commodity_price={$db_prefix}universe_ports.commodity_price+((RAND() * ($increaserate/2) * $offset) * $port_price_control)
								WHERE {$db_prefix}universe.port_type = {$db_prefix}universe_ports.commodity_type
								AND {$db_prefix}universe.sector_id = {$db_prefix}universe_ports.sector_id
								AND {$db_prefix}universe_ports.commodity_type = " . $db->qstr($cargotype));
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query->close();
		}
	}
	$cargo_query->Movenext();
}

	$cargo_query->close();
	echo"</td>
</tr>	</table>
</div>";

	echo "
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" bgcolor=\"#000000\">
		<tr BGCOLOR=\"#585980\">
			<td><b>Sector</b></td>
			<td><B>Commodity</B></td>
			<td><B>Price</B></td>
			<td><B>Cost Per Hold</B></td>
			<td><B>Start Price</B></td>
			<td><B>Start CPH</B></td>
		</tr>";
	$cargo_query = $db->Execute("SELECT classname, price, delta, itemlimit, hold_space, fixed_start_price,increaserate from {$db_prefix}class_modules_commodities where cargoport=1 order by price");
	db_op_result($cargo_query,__LINE__,__FILE__);
	while (!$cargo_query->EOF) 
	{
		$cargotype = $cargo_query->fields['classname'];

		$res = $db->SelectLimit("SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe_ports.commodity_type, {$db_prefix}universe_ports.commodity_price, {$db_prefix}universe_ports.commodity_amount
								FROM {$db_prefix}universe , {$db_prefix}universe_ports 
								WHERE {$db_prefix}universe_ports.commodity_type = " . $db->qstr($cargotype) . "
								AND {$db_prefix}universe_ports.sector_id = {$db_prefix}universe.sector_id
								AND {$db_prefix}universe.port_type != {$db_prefix}universe_ports.commodity_type
								AND {$db_prefix}universe.sg_sector = 0
								ORDER BY {$db_prefix}universe_ports.commodity_price DESC", 1);
		db_op_result($res,__LINE__,__FILE__);

		$offered_buy_price = max($res->fields['commodity_price'] + $cargo_query->fields['price'] + $cargo_query->fields['delta'] * $cargo_query->fields['itemlimit'] / $cargo_query->fields['itemlimit'] * $inventory_factor, 0.01);
		if($cargo_query->fields['increaserate'] == 0)
		{
			$cargo_query->fields['fixed_start_price'] /= 2;
		}
		$original_buy_price = max($cargo_query->fields['fixed_start_price'] + $cargo_query->fields['price'] + $cargo_query->fields['delta'] * $cargo_query->fields['itemlimit'] / $cargo_query->fields['itemlimit'] * $inventory_factor, 0.01);

		echo "<tr BGCOLOR=\"#3A3B6E\">
			<td><a href=\"main.php?move_method=real&engage=1&destination=" . rawurldecode($res->fields['sector_name']) . "\">" . $res->fields['sector_name'] . "</a></td>
			<TD>" . ucwords($res->fields['commodity_type']) . "</td>
			<TD>" . NUMBER(floor($offered_buy_price)) . "</td>
			<TD>" . NUMBER(floor($offered_buy_price / $cargo_query->fields['hold_space'])) . "</td>
			<TD>" . NUMBER(floor($original_buy_price)) . "</td>
			<TD>" . NUMBER(floor($original_buy_price / $cargo_query->fields['hold_space'])) . "</td>
		</tr>";
		$cargo_query->Movenext();
	}
	$cargo_query->close();
	echo "	</table>
</div>";
}

?>
<form action=admin.php method=post>
<tr align="center" >
<td>Age ports<br><SELECT size="12" NAME="multiplier">
	<OPTION VALUE="1"> 1 Day </OPTION>
	<OPTION VALUE="2"> 2 Days </OPTION>
	<OPTION VALUE="3"> 3 Days </OPTION>
	<OPTION VALUE="4"> 4 Days </OPTION>
	<OPTION VALUE="5"> 5 Days </OPTION>
	<OPTION VALUE="6"> 6 Days </OPTION>
	<OPTION VALUE="7"> 1 Week </OPTION>
	<OPTION VALUE="14"> 2 Weeks </OPTION>
	<OPTION VALUE="21"> 3 Weeks </OPTION>
	<OPTION VALUE="28"> 1 Month </OPTION>
	<OPTION VALUE="56"> 2 Months </OPTION>
	<OPTION VALUE="84"> 3 Months </OPTION>
	</SELECT>
	<br>
</td>
</tr>
<?php
echo "<tr><td colspan=\"2\" align=\"center\"><INPUT TYPE=HIDDEN NAME=menu VALUE=\"Update_Age_Port_Prices\">";
echo "<INPUT TYPE=HIDDEN NAME=\"admin_password\" VALUE=\"$admin_password\">";
echo "<input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "<INPUT TYPE=SUBMIT NAME=command VALUE=\"Age Prices\"></td></tr>"
?>
</form>


