<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: planet2.php

include ("config/config.php");
if($allow_probes == 1)
{
	include ("languages/$langdir/lang_probes.inc");
	include ("languages/$langdir/lang_report.inc");
	include ("languages/$langdir/lang_ports.inc");

	get_post_ifset("probe_id, probeinfo, probeupgrade, engines_upgrade, sensors_upgrade, cloak_upgrade");

	$title = $l_probe2_title;

	if (checklogin() or $tournament_setup_access == 1)
	{
		$template_object->enable_gzip = 0;
		include ("footer.php");
		die();
	}

	if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
		$templatename = $default_template;
	}else{
		$templatename = $playerinfo['template'];
	}
	include ("header.php");

	$result2 = $db->SelectLimit("SELECT * FROM {$db_prefix}probe WHERE probe_id=$probe_id", 1);
	if ($result2)
	{
		$probeinfo = $result2->fields;
	}

	if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
		include ("globals/base_template_data.inc");
	}
	else
	{
		$template_object->assign("title", $title);
		$template_object->assign("templatename", $templatename);
	}

	if ($probeinfo['sector_id'] <> $shipinfo['sector_id'])
	{
		$template_object->assign("error_msg", $l_probe2_sector);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}

	if ($playerinfo['turns'] < 1)
	{
		$template_object->assign("error_msg", $l_probe2_noturn);
		$template_object->assign("gotomain", $l_global_mmenu);
		$template_object->display($templatename."genericdie.tpl");
		include ("footer.php");
		die();
	}
	else
	{
		$template_object->assign("isprobe", (!empty($probeinfo) && !empty($probeupgrade)));

		if (!empty($probeinfo) && !empty($probeupgrade))
		{
			$engines_upgrade_cost = 0;
			if ($engines_upgrade > $max_tech_level)
			  $engines_upgrade = $max_tech_level;

			if ($engines_upgrade < 0)
			  $engines_upgrade = 0;

			if ($engines_upgrade > $probeinfo['engines'])
			{
				$engines_upgrade_cost = phpChangeDelta($engines_upgrade, $probeinfo['engines']);
			}

			$sensors_upgrade_cost = 0;
			if ($sensors_upgrade > $max_tech_level)
				$sensors_upgrade = $max_tech_level;

			if ($sensors_upgrade < 0)
				$sensors_upgrade = 0;

			if ($sensors_upgrade > $probeinfo['sensors'])
			{
				$sensors_upgrade_cost = phpChangeDelta($sensors_upgrade, $probeinfo['sensors']);
			}

			$cloak_upgrade_cost = 0;
			if ($cloak_upgrade > $max_tech_level)
				$cloak_upgrade = $max_tech_level;

			if ($cloak_upgrade < 0)
				$cloak_upgrade = 0;

			if ($cloak_upgrade > $probeinfo['cloak'])
			{
				$cloak_upgrade_cost = phpChangeDelta($cloak_upgrade, $probeinfo['cloak']);
			}

			$total_cost = $engines_upgrade_cost + $sensors_upgrade_cost + $cloak_upgrade_cost;

			$template_object->assign("total_cost", $total_cost);
			$template_object->assign("playercredits", $playerinfo['credits']);
			if ($total_cost > $playerinfo['credits'])
			{
				$l_probe2_nocredits = str_replace("[total]", NUMBER($total_cost), $l_probe2_nocredits);
				$l_probe2_nocredits = str_replace("[credits]", NUMBER($playerinfo['credits']), $l_probe2_nocredits);
				$template_object->assign("l_probe2_nocredits", $l_probe2_nocredits);
				$template_object->assign("l_credits", $l_credits);
			}
			else
			{
				$trade_credits = NUMBER(abs($total_cost));
				$template_object->assign("trade_credits", $trade_credits);
				$template_object->assign("l_trade_result", $l_trade_result);
				$template_object->assign("l_cost", $l_cost);

				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=credits-$total_cost,turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$query = "UPDATE {$db_prefix}probe SET probe_id=$probe_id ";

				$template_object->assign("l_trade_upgraded", $l_trade_upgraded);
				$template_object->assign("isengineupgrade", ($engines_upgrade > $probeinfo['engines']));
				if ($engines_upgrade > $probeinfo['engines'])
				{
					$query = $query . ", engines=$engines_upgrade";
					$template_object->assign("l_engines", $l_engines);
					$template_object->assign("engines_upgrade", $engines_upgrade);
				}

				$template_object->assign("issensorupgrade", ($sensors_upgrade > $probeinfo['sensors']));
				if ($sensors_upgrade > $probeinfo['sensors'])
				{
					$query = $query . ", sensors=$sensors_upgrade";
					$template_object->assign("l_sensors", $l_sensors);
					$template_object->assign("sensors_upgrade", $sensors_upgrade);
				}

				$template_object->assign("iscloakupgrade", ($cloak_upgrade > $probeinfo['cloak']));
				if ($cloak_upgrade > $probeinfo['cloak'])
				{
					$query = $query . ", cloak=$cloak_upgrade";
					$template_object->assign("l_cloak", $l_cloak);
					$template_object->assign("cloak_upgrade", $cloak_upgrade);
				}

				$query = $query . " WHERE probe_id=$probe_id";
				$debug_query = $db->Execute("$query");
				db_op_result($debug_query,__LINE__,__FILE__);
			}
		}
	}

	$template_object->assign("probe_id", $probe_id);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toprobemenu", $l_toprobemenu);

	$template_object->assign("error_msg", $l_probe2_noturn);
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."probes/probes_upgrade_finish.tpl");

	include ("footer.php");
}
?>
