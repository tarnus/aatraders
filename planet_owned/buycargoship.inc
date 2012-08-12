<?php
if($allow_autotrades == 0)
{
	die();
}

// Create dropdowns when called
function dropdown($element_name,$current_value, $max_value)
{
	global $onchange;
	$i = $current_value;
	$dropdownvar = "<select size='1' name='$element_name'";
	$dropdownvar = "$dropdownvar ONCHANGE=\"countTotal()\">\n";
	while ($i <= $max_value)
	{
		if ($current_value == $i)
		{
			$dropdownvar = "$dropdownvar		<option value='$i' selected>$i</option>\n";
		}
		else
		{
			$dropdownvar = "$dropdownvar		<option value='$i'>$i</option>\n";
		}
		$i++;
	}
	$dropdownvar = "$dropdownvar	   </select>\n";
	return $dropdownvar;
}

function phpTrueDelta($futurevalue,$shipvalue)
{
	$tempval = $futurevalue - $shipvalue;
	return $tempval;
}

		if($planetinfo['owner'] == $playerinfo['player_id'])
		{
			$isowner = 1;

			if($planetinfo['cargo_hull'] == 0 or $planetinfo['cargo_hull'] == '')
			{
				$ownhull = 1;
			}
		}

		$cargoshipcost[1] = NUMBER(phpChangeDelta(10, 0) + phpChangeDelta(1, 0) + 116383500);
		$cargoshipcost[2] = NUMBER(phpChangeDelta(50, 0) + phpChangeDelta(1, 0) + 116383500);
		$cargoshipcost[3] = NUMBER(phpChangeDelta(100, 0) + phpChangeDelta(1, 0) + 116383500);
		$cargoshipcost[4] = NUMBER(phpChangeDelta(150, 0) + phpChangeDelta(1, 0) + 116383500);
		$cargoshipcost[5] = NUMBER(phpChangeDelta(200, 0) + phpChangeDelta(1, 0) + 116383500);
		$cargoshipcost[6] = NUMBER(phpChangeDelta(250, 0) + phpChangeDelta(1, 0) + 116383500);

		$template_object->assign("cargoshipcost", $cargoshipcost);
		$template_object->assign("max_tech_level", floor($max_tech_level * 0.53));
		$template_object->assign("upgrade_cost", $upgrade_cost);
		$template_object->assign("java_credits", $playerinfo['credits']);
		$template_object->assign("java_hull", $planetinfo['cargo_hull']);
		$template_object->assign("java_power", $planetinfo['cargo_power']);
		$template_object->assign("l_no_credits", $l_no_credits);
		$template_object->assign("upgrade_factor", $upgrade_factor);
		$template_object->assign("cargoshiphull", dropdown("cargoshiphull",0, floor($max_tech_level * 0.53)));
		$template_object->assign("cargoshippower", dropdown("cargoshippower",1, floor($max_tech_level * 0.53)));
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("isowner", $isowner);
		$template_object->assign("ownhull", $ownhull);
		$template_object->assign("l_planet_cargoshipbuy", $l_planet_cargoshipbuy);
		$template_object->assign("l_planet_cargonoown", $l_planet_cargonoown);
		$template_object->assign("l_planet_cargoowned", $l_planet_cargoowned);
		$template_object->assign("l_planet_cargoshipbuyinfo", $l_planet_cargoshipbuyinfo);
		$template_object->assign("l_credits", $l_credits);
		$template_object->assign("playercredits", number($playerinfo['credits']));
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_hull", $l_hull);
		$template_object->assign("l_power", $l_power);
		$template_object->assign("l_ship_price", $l_ship_price);
		$template_object->assign("l_planet_cargoshipbuildinfo", $l_planet_cargoshipbuildinfo);
		$template_object->assign("l_buy", $l_buy);
		$template_object->assign("onclick", $onclick);
		$template_object->assign("l_totalcost", $l_totalcost);
		$template_object->assign("templatename", $templatename);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedbuycargo.tpl");
		include ("footer.php");
		die();

?>