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

		if($planetinfo['owner'] == $playerinfo['player_id'])
		{
			$isowner = 1;
			if($planetinfo['cargo_hull'] <= floor($max_tech_level * 0.53))
			{
				$ownhull = 1;
			}
		}

		$template_object->assign("max_tech_level", floor($max_tech_level * 0.53));
		$template_object->assign("java_credits", $playerinfo['credits']);
		$template_object->assign("java_hull", $planetinfo['cargo_hull']);
		$template_object->assign("java_power", $planetinfo['cargo_power']);
		$template_object->assign("l_no_credits", $l_no_credits);
		$template_object->assign("upgrade_cost", $upgrade_cost);
		$template_object->assign("upgrade_factor", $upgrade_factor);
		$template_object->assign("ownhull", $ownhull);
		$template_object->assign("cargohull", number($planetinfo['cargo_hull']));
		$template_object->assign("cargopower", number($planetinfo['cargo_power']));
		$template_object->assign("cargo_hull", dropdown("cargoshiphull",$planetinfo['cargo_hull'], floor($max_tech_level * 0.53)));
		$template_object->assign("cargo_power", dropdown("cargoshippower",$planetinfo['cargo_power'], floor($max_tech_level * 0.53)));
		$template_object->assign("l_planet_cargoshipupgradeinfo", $l_planet_cargoshipupgradeinfo);
		$template_object->assign("l_credits", $l_credits);
		$template_object->assign("playercredits", number($playerinfo['credits']));
		$template_object->assign("l_hull", $l_hull);
		$template_object->assign("l_power", $l_power);
		$template_object->assign("l_buy", $l_buy);
		$template_object->assign("l_totalcost", $l_totalcost);
		$template_object->assign("l_planet_cargoatmax", $l_planet_cargoatmax);
		$template_object->assign("l_planet_cargonoown", $l_planet_cargonoown);
		$template_object->assign("l_planet_cargoshipupgrade", $l_planet_cargoshipupgrade);
		$template_object->assign("nomoney", $nomoney);
		$template_object->assign("isowner", $isowner);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_clickme", $l_clickme);
		$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
		$template_object->assign("l_igb_term", $l_igb_term);
		$template_object->assign("allow_ibank", $allow_ibank);
		$template_object->assign("l_by_placebounty", $l_by_placebounty);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."planet_owned/planet_ownedupgradecargo.tpl");
		include ("footer.php");
		die();

?>