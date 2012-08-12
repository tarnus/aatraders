<?php
include ("languages/$langdir/lang_attack.inc");
include ("globals/combat_functions.inc");
include ("globals/display_this_planet.inc");
include ("globals/device_ship_tech_modify.inc");
include ("globals/planet_bounty_check.inc");

$shipinfo = device_ship_tech_modify($shipinfo, $shipdevice);

$countplanet = 0;
display_this_planet($planetinfo);
$titleimage = $planetimg[0];
$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 0);
$template_object->assign("isfedbounty", $isfedbounty);
$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);
$template_object->assign("l_by_nofedbounty", $l_by_nofedbounty);

$template_object->assign("titleimage", $titleimage);
$template_object->assign("planetname", $planetinfo['name']);

//
//
// Preview of possible attack results
//
//

if ($planetinfo['owner'] != 3)
{
	$template_object->assign("l_planet_combatpreview", $l_planet_combatpreview);
	if ($playerinfo['turns'] < 1)
	{
		$template_object->assign("error_msg", $l_cmb_atleastoneturn);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}

	$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id='$planetinfo[owner]'", 1);
	$targetinfo = $result2->fields;
	$result2->close();

	// get attacker beam, shield and armor values
	$attacker_shield_energy = floor($shipinfo['energy'] * 0.4);
	$attacker_beam_energy = $shipinfo['energy'] - $attacker_shield_energy;

	$attackershields = NUM_SHIELDS($shipinfo['shields']);

	if ($attackershields < $attacker_shield_energy)
	{
		$attacker_shield_energy = $attackershields;
	}

	$attacker_shield_hit_pts = $attacker_shield_energy * $ship_shield_hit_pts;
	$attacker_armor_hit_pts = $shipinfo['armor_pts'] * $ship_armor_hit_pts;

	$attackerbeams = NUM_BEAMS($shipinfo['beams']);

	if ($attackerbeams < $attacker_beam_energy)
	{
		$attacker_beam_energy = $attackerbeams;
	}

	$attack_beamtofighter_dmg = floor($attacker_beam_energy * 0.05);
	$attack_beamtotorp_dmg = floor($attacker_beam_energy * 0.025);
	$attacker_beam_energy_dmg = ($attacker_beam_energy - floor($attacker_beam_energy * 0.1) - floor($attacker_beam_energy * 0.1)) * $beam_damage_shields;

	$attackertorps = $shipinfo['torps'];
	$attackerarmor = $shipinfo['armor_pts'];
	$attackerfighters = $shipinfo['fighters'];

	$attackerlowpercent = ecmcheck($shipinfo['sensors'], $shipinfo['sensors'], $full_attack_modifier);

	// get target beam, shield and armor values
	$target_shield_energy = floor($planetinfo['energy'] * 0.4);
	$target_beam_energy = $planetinfo['energy'] - $target_shield_energy;

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['shields'] / $max_tech_level))) : 0;
	if ($planetinfo['shields'] == 0) 
	{
		$targetshields = 0;
	}
	else
	{
		$targetshields = NUM_SHIELDS($planetinfo['shields'] + $base_factor);
	}

	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	while (!$res->EOF)
	{
		$targetshields += NUM_SHIELDS($res->fields['shields']);
		$res->MoveNext();
	}
	$res->close();

	$full_target_shield_energy = $target_shield_energy;

	if (($targetshields * $planet_shield_multiplier) < $target_shield_energy)
	{
		$target_shield_energy = $targetshields;
	}
	else
	{
		$target_shield_energy = floor($target_shield_energy / $planet_shield_multiplier);
	}

	$target_shield_hit_pts = $target_shield_energy * $ship_shield_hit_pts;
	$target_armor_hit_pts = $planetinfo['armor_pts'] * $ship_armor_hit_pts;

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['beams'] / $max_tech_level))) : 0;
	if ($planetinfo['beams'] == 0) 
	{
		$targetbeams = 0;
	}
	else
	{
		$targetbeams = NUM_BEAMS($planetinfo['beams'] + $base_factor);
	}

	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	while (!$res->EOF)
	{
		$targetbeams += NUM_BEAMS($res->fields['beams']);
		$res->MoveNext();
	}
	$res->close();

	if ($targetbeams < $target_beam_energy)
	{
		$target_beam_energy = $targetbeams;
	}

	$target_beamtofighter_dmg = floor($target_beam_energy * 0.05);
	$target_beamtotorp_dmg = floor($target_beam_energy * 0.025);
	$target_beam_energy_dmg = ($target_beam_energy - floor($target_beam_energy * 0.1) - floor($target_beam_energy * 0.1)) * $beam_damage_shields;

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['torp_launchers'] / $max_tech_level))) : 0;
	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	$torp_launchers = NUM_TORPEDOES($planetinfo['torp_launchers'] + $base_factor) ;
	$torps = $planetinfo['torps'];
	if ($res)
	{
	   while (!$res->EOF)
		{
			$torps += $res->fields['torps'];  
			$ship_torps =  NUM_TORPEDOES($res->fields['torp_launchers']);
			$torp_launchers = $torp_launchers + $ship_torps;
			$res->MoveNext();
		}
	}
	$res->close();
	if ($torp_launchers > $torps)
	{
		$targettorps = $torps;
	}
	else
	{
		$targettorps = $torp_launchers;
	}

	$targetarmor = $planetinfo['armor_pts'];

	$base_factor = ($planetinfo['base'] == 'Y') ? round($basedefense * (1 - ($planetinfo['fighter'] / $max_tech_level))) : 0;
	$planet_comp_level = NUM_FIGHTERS($planetinfo['fighter'] + $base_factor);
	$figs = $planetinfo['fighters'];
	$res = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE planet_id=$planetinfo[planet_id] AND on_planet='Y'");
	if ($res)  
	{
		while (!$res->EOF)  
		{
			$figs += $res->fields['fighters'];  
			$ship_comp =  NUM_FIGHTERS($res->fields['fighter']);  
			$planet_comp_level = $planet_comp_level + $ship_comp;  
			$res->MoveNext();  
		}
	}
	$res->close();

	if ($planet_comp_level > $figs)
	{
		$targetfighters = $figs;
	}
	else
	{
		$targetfighters = $planet_comp_level;
	}

	$targetlowpercent = ecmcheck($shipinfo['ecm'], $planetinfo['sensors'], -$full_attack_modifier);

	$success = SCAN_SUCCESS($shipinfo['sensors'], $planetinfo['cloak']);

	$template_object->assign("start_target_beams", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_beam_energy)));
	$template_object->assign("start_target_fighters", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targetfighters)));
	$template_object->assign("start_target_shields", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $target_shield_energy)));
	$template_object->assign("start_target_torps", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targettorps)));
	$template_object->assign("start_target_armor", (mt_rand(1, 100) > $success) ? 0 : NUMBER(SCAN_ERROR($shipinfo['sensors'], $planetinfo['jammer'], $targetarmor)));

	$template_object->assign("l_cmb_attacker_beams", $l_cmb_attacker_beams);
	$template_object->assign("l_cmb_attacker_fighters", $l_cmb_attacker_fighters);
	$template_object->assign("l_cmb_attacker_shields", $l_cmb_attacker_shields);
	$template_object->assign("l_cmb_attacker_torps", $l_cmb_attacker_torps);
	$template_object->assign("l_cmb_attacker_armor", $l_cmb_attacker_armor);
	$template_object->assign("l_cmb_target_beams", $l_cmb_target_beams);
	$template_object->assign("l_cmb_target_fighters", $l_cmb_target_fighters);
	$template_object->assign("l_cmb_target_shields", $l_cmb_target_shields);
	$template_object->assign("l_cmb_target_torps", $l_cmb_target_torps);
	$template_object->assign("l_cmb_target_armor", $l_cmb_target_armor);
	$template_object->assign("l_cmb_you", $l_cmb_you);

	$template_object->assign("start_attacker_beam_energy", NUMBER($attacker_beam_energy));
	$template_object->assign("start_attackerfighters", NUMBER($attackerfighters));
	$template_object->assign("start_attacker_shield_energy", NUMBER($attacker_shield_energy));
	$template_object->assign("start_attackertorps", NUMBER($attackertorps));
	$template_object->assign("start_attackerarmor", NUMBER($attackerarmor));

	if($planetinfo['owner'] != 3)
	{
		$l_planet_att_link="<a href='planet.php?planet_id=$planet_id&command=attack'>" . $l_planet_att_link ."</a>";
		$l_planet_att=str_replace("[attack]",$l_planet_att_link,$l_planet_att);
	}
	else
	{
		$l_planet_att = "";
	}

	$l_planet_scn_link="<a href='planet.php?planet_id=$planet_id&command=scan'>" . $l_planet_scn_link ."</a>";
	$l_planet_scn=str_replace("[scan]",$l_planet_scn_link,$l_planet_scn);

	$template_object->assign("l_planet_att", $l_planet_att);
	$template_object->assign("l_planet_scn", $l_planet_scn);

	$template_object->assign("l_sofa", $l_sofa);
	$template_object->assign("sofa_on", $sofa_on);
	$template_object->assign("planetowner", $planetinfo['owner']);
	$template_object->assign("l_planet_att_sure", $l_planet_att_sure);

	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("allow_ibank", $allow_ibank);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_igb_term", $l_igb_term);
	$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
	$template_object->assign("l_by_placebounty", $l_by_placebounty);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_unowned/attack_preview.tpl");
	include ("footer.php");
	die();
}
else
{
	$template_object->assign("l_command_no", $l_command_no);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("allow_ibank", $allow_ibank);
	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_igb_term", $l_igb_term);
	$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
	$template_object->assign("l_by_placebounty", $l_by_placebounty);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_unowned/attack_preview.tpl");
	include ("footer.php");
	die();
}

?>