<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: probes_upgrade.php

include ("config/config.php");
include ("languages/$langdir/lang_probes.inc");
include ("languages/$langdir/lang_combat.inc");
include ("languages/$langdir/lang_report.inc");
include ("languages/$langdir/lang_ports.inc");
include ("languages/$langdir/lang_bounty.inc");
include ("languages/$langdir/lang_shipyard.inc");
include ("globals/cleanjs.inc");

get_post_ifset("probe_id, command, destroy, type, target_sector, new_type");

if (checklogin() || $tournament_setup_access == 1 || $allow_probes == 0)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

$title = $l_probe_title;

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}

$probe_id = stripnum($probe_id);

$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}probe WHERE probe_id=$probe_id and active='Y'", 1);
if ($result3)
	$probeinfo=$result3->fields;

mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);

if (!empty($probeinfo))
{
	if ($shipinfo['sector_id'] == $probeinfo['sector_id'])
	{
		$l_probe_typen = array();
		$probetypeinfo = array();
		$probeclass = array();
		$probedescription = array();
		$probeobjectarray = array();
		$filelist = get_dirlist($gameroot."class/probes/");
		for ($c=0; $c<count($filelist); $c++) {
			if($filelist[$c] != "index.html")
			{
				$probename =  str_replace(".inc", "", $filelist[$c]); 
				if(!class_exists($probename)){
					include ("class/probes/" . $probename . ".inc");
				}
				$probeobject = new $probename();
				$type = $probeobject->type;
				$probeobjectarray[$type] = $probeobject;
				$probetypeinfo[$type] = $probeobject->l_probe_type;
				$probeclass[$type] = $probeobject->class;
				$probedescription[$type] = $probeobject->l_probe_description;

				$lines = $probeobject->probe_orders_code();

				$count = 0;
				for($i = 0; $i < count($lines); $i++){
					$items = array();
					$items = explode(";", trim($lines[$i]));
					$variable = explode("=", $items[0]);
					$variable[0] = trim($variable[0]);
					$variable[1] = str_replace("\"", "", trim($variable[1]));

					// $variable[0] = HTML input variable name
					// $variable[1] = default value for the variable
					// $items[1] = input type
					// $items[2] = input_selections
					// $items[3] = description
					$variable_name[$type . $count] = $variable[0];
					$variable_value[$type . $count] = $variable[1];
					$input_type[$type . $count] = trim($items[1]);
					$input_selections[$type . $count] = trim($items[2]);
					$info[$type . $count] = trim($items[3]);
					$count++;
				}
				$probeordercount[$type] = $count;
			}
		}

		if ($probeinfo['owner_id'] != 0)
		{
			$result3 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=$probeinfo[owner_id]", 1);
			$ownerinfo = $result3->fields;

			$res = $db->SelectLimit("SELECT * FROM {$db_prefix}ships WHERE player_id=$probeinfo[owner_id] AND ship_id=$ownerinfo[currentship]", 1);
			$ownershipinfo = $res->fields;
		}

		if (empty($command))
		{
			/* ...if there is no probe command already */
			$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probeinfo['sector_id'], 1);
			db_op_result($resx,__LINE__,__FILE__);
			$sector_name = $resx->fields['sector_name'];
			$l_probe_named=str_replace("[name]",$ownerinfo['character_name'],$l_probe_named);
			$l_probe_named=str_replace("[probename]",$probeinfo['probe_id'],$l_probe_named);
			$l_probe_named=str_replace("[sector]","<a href=main.php?move_method=real&engage=1&destination=" . urlencode($sector_name) . ">$sector_name</a>",$l_probe_named);

			if ($playerinfo['player_id'] == $probeinfo['owner_id'])
			{
				if ($destroy==1)
				{
					include ("header.php");
					$template_object->assign("title", $title);
					$template_object->assign("error_msg", "<font color=red>$l_probe_confirm</font><br><A HREF='probes_upgrade.php?probe_id=$probe_id&destroy=2'>$l_yes</A>");
					$template_object->assign("error_msg2", "<A HREF='probes_upgrade.php?probe_id=$probe_id'>$l_no!</A>");
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genericdie.tpl");
					include ("footer.php");
					die();
				}
				elseif ($destroy==2)
				{
					if ($playerinfo['turns'] > 0)
					{
						$debug_query = $db->Execute("DELETE from {$db_prefix}probe where probe_id=$probe_id");
						db_op_result($debug_query,__LINE__,__FILE__);
						$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns_used=turns_used+1, turns=turns-1 WHERE player_id=$playerinfo[player_id]");
						db_op_result($debug_query,__LINE__,__FILE__);
						close_database();
						echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
						die();
					}
					else
					{
						include ("header.php");
						$template_object->assign("title", $title);
						$template_object->assign("error_msg", $l_probe2_turn);
						$template_object->assign("gotomain", $l_global_mmenu);
						$template_object->display($templatename."genericdie.tpl");
						include ("footer.php");
						die();
					}
				}
				else
				{
				}
			}
			include ("header.php");
			$template_object->assign("title", $title);

			if ($probeinfo['owner_id'] == $playerinfo['player_id'] && $probeinfo['owner_id'] > 0)
			{
				/* owner menu */
				$ptype=$probetypeinfo[$probeinfo['type']];
				$sector_name = $resx->fields['sector_name'];
				$l_probe_ordersout =str_replace("[type]",$ptype,$l_probe_order2);
				if(!empty($probeinfo['target_sector']))
				{
					$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probeinfo['target_sector'], 1);
					db_op_result($resx,__LINE__,__FILE__);
					$l_probe_ordersout =str_replace("[target]", "<a href=main.php?move_method=real&engage=1&destination=" . urlencode($sector_name) . ">$sector_name</a>.", $l_probe_ordersout);
				}
				else
				{
					$l_probe_ordersout =str_replace("[target]", "none.", $l_probe_ordersout);
				}
				$l_probe_name =str_replace("[name]",$l_probe_name_link,$l_probe_name2);
				$l_probe_pickup_link="<a href='probes_upgrade.php?probe_id=$probe_id&command=pickup'>" . $l_probe_pickup_link . "</a>";
				$l_probe_pickup=str_replace("[pickup]",$l_probe_pickup_link,$l_probe_pickup);
				$l_probe_orders_link="<a href='probes_upgrade.php?probe_id=$probe_id&command=orders'>" . $l_probe_orders_link . "</a>";
				$l_probe_orders=str_replace("[orders]",$l_probe_orders_link,$l_probe_orders);
				$l_probe_upgrade_link="<a href='probes_upgrade.php?probe_id=$probe_id&command=defenses'>" . $l_probe_upgrade_link . "</a>";
				$l_probe_upgrade=str_replace("[upgrade]",$l_probe_upgrade_link,$l_probe_upgrade);

				$template_object->assign("l_turns_have", $l_turns_have);
				$template_object->assign("player_turns", $playerinfo['turns']);
				$template_object->assign("l_probe_ordersout", $l_probe_ordersout);
				$template_object->assign("l_probe_name", $l_probe_name);
				$template_object->assign("l_probe_orders", $l_probe_orders);
				$template_object->assign("l_probe_pickup", $l_probe_pickup);
				$template_object->assign("l_probe_upgrade", $l_probe_upgrade);
				$template_object->assign("probe_engines", NUMBER($probeinfo['engines']));
				$template_object->assign("probe_sensors", NUMBER($probeinfo['sensors']));
				$template_object->assign("probe_cloak", NUMBER($probeinfo['cloak']));
				$template_object->assign("l_probe_engine", $l_probe_engine);
				$template_object->assign("l_probe_sensors", $l_probe_sensors);
				$template_object->assign("l_probe_cloak", $l_probe_cloak);
				$template_object->assign("l_probe_defense_levels", $l_probe_defense_levels);
			}
			else
			{
				/* visitor menu */
				if($probeinfo['owner_id'] != 3){
					$l_probe_att_link="<a href='probes_upgrade.php?probe_id=$probe_id&command=attack'>" . $l_probe_att_link ."</a>";
					$l_probe_att=str_replace("[attack]",$l_probe_att_link,$l_probe_att);
				}
				$l_probe_scn_link="<a href='probes_upgrade.php?probe_id=$probe_id&command=scan'>" . $l_probe_scn_link ."</a>";
				$l_probe_scn=str_replace("[scan]",$l_probe_scn_link,$l_probe_scn);

				$template_object->assign("l_probe_att", $l_probe_att);
				$template_object->assign("l_probe_scn", $l_probe_scn);
			}
			$template_object->assign("player_id", $playerinfo['player_id']);
			$template_object->assign("probe_owner_id", $probeinfo['owner_id']);
			$template_object->assign("l_probe_warning", $l_probe_warning);
			$template_object->assign("destroy", $destroy);
			$template_object->assign("l_probe_named", $l_probe_named);
			$template_object->assign("probe_id", $probe_id);
			$template_object->assign("l_probe_destroyprobe", $l_probe_destroyprobe);

			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."probes/probes_display.tpl");
			include ("footer.php");
			die();
		}
		elseif ($command == "attack" && $probeinfo['owner'] != 3)
		{
			if ($playerinfo['turns'] > 0)
			{
				playerlog($ownerinfo['player_id'], "LOG9_PROBE_ATTACKED", $probetypeinfo[$probeinfo['type']] . "|$probeinfo[sector_id]|$playerinfo[character_name]");
				$debug_query = $db->Execute("DELETE from {$db_prefix}probe where probe_id=$probe_id");
				db_op_result($debug_query,__LINE__,__FILE__);
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns_used=turns_used+1, turns=turns-1 WHERE player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);
				close_database();
				echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			}
			else
			{
				include ("header.php");
				$template_object->assign("title", $title);
				$template_object->assign("error_msg", $l_probe2_turn);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}
		}
		elseif ($probeinfo['owner_id'] == $playerinfo['player_id']  && $probeinfo['owner_id'] > 0)
		{
			/* player owns probe and there is a command */
			if ($command == "defenses"){
				include ("header.php");
				$template_object->assign("title", $title);
				/* defenses menu */
				$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probeinfo['sector_id'], 1);
				db_op_result($resx,__LINE__,__FILE__);
				$sector_name = $resx->fields['sector_name'];
				$l_probe_named=str_replace("[name]",$ownerinfo['character_name'],$l_probe_named);
				$l_probe_named=str_replace("[probename]",$probeinfo['probe_id'],$l_probe_named);
				$l_probe_named=str_replace("[sector]","<a href=main.php?move_method=real&engage=1&destination=" . urlencode($sector_name) . ">$sector_name</a>",$l_probe_named);

				$template_object->assign("l_probe_named", $l_probe_named);

				cleanjs('');

				$template_object->assign("upgrade_factor", $upgrade_factor);
				$template_object->assign("upgrade_cost", $upgrade_cost);
				$template_object->assign("probe_sensors", $probeinfo['sensors']);
				$template_object->assign("probe_cloak", $probeinfo['cloak']);
				$template_object->assign("probe_engines", $probeinfo['engines']);
				$template_object->assign("player_credits", $playerinfo['credits']);
				$template_object->assign("l_no_credits", $l_no_credits);
				$template_object->assign("l_probe_named", $l_probe_named);

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

				$l_creds_to_spend=str_replace("[credits]",NUMBER($playerinfo['credits']),$l_creds_to_spend);
				$template_object->assign("l_creds_to_spend", $l_creds_to_spend);
				$igblink = "\n<A HREF=igb.php>$l_igb_term</a>";
				$l_ifyouneedmore=str_replace("[igb]",$igblink,$l_ifyouneedmore);
				$template_object->assign("allow_ibank", $allow_ibank);
				$template_object->assign("l_ifyouneedmore", $l_ifyouneedmore);

				$template_object->assign("probe_id", $probe_id);
				$template_object->assign("l_probe_defense_levels", $l_probe_defense_levels);
				$template_object->assign("l_cost", $l_cost);
				$template_object->assign("l_current_level", $l_current_level);
				$template_object->assign("l_upgrade", $l_upgrade);
				$template_object->assign("l_engine", $l_probe_engine);
				$template_object->assign("l_sensors", $l_sensors);
				$template_object->assign("l_cloak", $l_cloak);
				$template_object->assign("l_buy", $l_buy);
				$template_object->assign("l_totalcost", $l_totalcost);
				$template_object->assign("dropdown_engines", dropdown("engines_upgrade",$probeinfo['engines'], $max_tech_level));
				$template_object->assign("dropdown_sensors", dropdown("sensors_upgrade",$probeinfo['sensors'], $max_tech_level));
				$template_object->assign("dropdown_cloak", dropdown("cloak_upgrade",$probeinfo['cloak'], $max_tech_level));
				$template_object->assign("l_clickme", $l_clickme);

				$template_object->assign("l_probe_linkback", $l_probe_linkback);
				$template_object->assign("l_clickme", $l_clickme);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."probes/probes_defenses.tpl");
				include ("footer.php");
				die();
			}
			elseif ($command == "orders")
			{
				include ("header.php");
				$template_object->assign("title", $title);
				if ($playerinfo['turns'] < 1)
				{
					$template_object->assign("error_msg", $l_plant_scn_turn);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genericdie.tpl");
					include ("footer.php");
					die();
				}
				// Order probe to do something
				cleanjs('');

				$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probeinfo['sector_id'], 1);
				db_op_result($resx,__LINE__,__FILE__);
				$sector_name = $resx->fields['sector_name'];
				$l_probe_named=str_replace("[name]",$ownerinfo['character_name'],$l_probe_named);
				$l_probe_named=str_replace("[probename]",$probeinfo['probe_id'],$l_probe_named);
				$l_probe_named=str_replace("[sector]","<a href=main.php?move_method=real&engage=1&destination=" . urlencode($sector_name) . ">$sector_name</a>",$l_probe_named);
				$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $probeinfo['target_sector'], 1);
				db_op_result($resx,__LINE__,__FILE__);
				$sector_name = $resx->fields['sector_name'];

				$template_object->assign("l_probe_named", $l_probe_named);
				$template_object->assign("probe_id", $probe_id);
				$template_object->assign("l_probe_type", $l_probe_type);
				$template_object->assign("l_probe_target", $l_probe_target);
				$template_object->assign("l_submit", $l_submit);
				$template_object->assign("target_sector", $sector_name);
				$template_object->assign("l_reset", $l_reset);
				$template_object->assign("probe_type", $probeinfo['type']);
				$template_object->assign("probetypeinfo", $probetypeinfo);
				$template_object->assign("probedescription", $probedescription);
				$template_object->assign("variable_name", $variable_name);
				$template_object->assign("variable_value", $variable_value);
				$template_object->assign("input_type", $input_type);
				$template_object->assign("input_selections", $input_selections);
				$template_object->assign("info", $info);
				$template_object->assign("probeordercount", $probeordercount);

				$template_object->assign("l_probe_linkback", $l_probe_linkback);
				$template_object->assign("l_clickme", $l_clickme);

				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."probes/probes_orders.tpl");
				include ("footer.php");
				die();
			}
			elseif ($command == "orders_finish")
			{
				if ($playerinfo['turns'] < 1)
				{
					include ("header.php");
					$template_object->assign("title", $title);
					$template_object->assign("error_msg", $l_plant_scn_turn);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genericdie.tpl");
					include ("footer.php");
					die();
				}
				$probeobject = $probeobjectarray[$new_type];
				$result = $probeobject->probe_finishorders_code();
				die();
			}
			elseif ($command == "pickup")
			{
				if ($playerinfo['turns'] < 1)
				{
					include ("header.php");
					$template_object->assign("title", $title);
					$template_object->assign("error_msg", $l_plant_scn_turn);
					$template_object->assign("gotomain", $l_global_mmenu);
					$template_object->display($templatename."genericdie.tpl");
					include ("footer.php");
					die();
				}
				$debug_query = $db->Execute("UPDATE {$db_prefix}probe SET active='P', data='' WHERE probe_id=$probe_id");
				db_op_result($debug_query,__LINE__,__FILE__);
				echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=probes.php\">";
				die();
			}
			else
			{
				header("location: main.php\r\n");
				die();
			}
			include ("footer.php");
		}
		elseif ($command == "scan")
		{
			include ("header.php");
			$template_object->assign("title", $title);
			/* scan menu */
			if ($playerinfo['turns'] < 1)
			{
				$template_object->assign("error_msg", $l_plant_scn_turn);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}

			/* determine per cent chance of success in scanning target ship - based on player's sensors and opponent's probe's cloak */
			$success = SCAN_SUCCESS($shipinfo['sensors'], $probeinfo['cloak'], $shiptypes['1']['basehull']);
			$roll = mt_rand(1, 100);
			if ($roll > $success)
			{
				/* if scan fails - inform both player and target. */
				playerlog($ownerinfo['player_id'], "LOG9_PROBE_SCAN_FAIL", $probetypeinfo[$probeinfo['type']] . "|$probeinfo[sector_id]|$playerinfo[character_name]");
				$template_object->assign("error_msg", $l_probe_noscan);
				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."genericdie.tpl");
				include ("footer.php");
				die();
			}
			else
			{
				playerlog($ownerinfo['player_id'], "LOG9_PROBE_SCAN", $probetypeinfo[$probeinfo['type']] . "|$probeinfo[sector_id]|$playerinfo[character_name]");
				/* scramble results by scan error factor. */
				if (empty($probeinfo['name']))
					$probeinfo['name'] = $l_unnamed;
				$l_probe_scn_report=str_replace("[name]",$probetypeinfo[$probeinfo['type']],$l_probe_scn_report);
				$l_probe_scn_report=str_replace("[owner]",$ownerinfo['character_name'],$l_probe_scn_report);
				$roll = mt_rand(1, 100);
				if ($roll < $success)
				{
					$sc_probe_engines=NUMBER(SCAN_ERROR($shipinfo['sensors'], $probeinfo['cloak'], $probeinfo['engines']));
				}
				else
				{
					$sc_probe_engines = "0";
				}
				if ($roll < $success)
				{
					$sc_probe_sensors=NUMBER(SCAN_ERROR($shipinfo['sensors'], $probeinfo['cloak'], $probeinfo['sensors']));
				}
				else
				{
					$sc_probe_sensors = "0";
				}
				if ($roll < $success)
				{
					$sc_probe_cloak=NUMBER(SCAN_ERROR($shipinfo['sensors'], $probeinfo['cloak'], $probeinfo['cloak']));
				}
				else
				{
					$sc_probe_cloak = "0";
				}
				$debug_query = $db->Execute("UPDATE {$db_prefix}players SET turns=turns-1, turns_used=turns_used+1 WHERE player_id=$playerinfo[player_id]");
				db_op_result($debug_query,__LINE__,__FILE__);

				$template_object->assign("l_probe_scn_report", $l_probe_scn_report);
				$template_object->assign("probe_engines", $sc_probe_engines);
				$template_object->assign("probe_sensors", $sc_probe_sensors);
				$template_object->assign("probe_cloak", $sc_probe_cloak);
				$template_object->assign("l_probe_engine", $l_probe_engine);
				$template_object->assign("l_probe_sensors", $l_probe_sensors);
				$template_object->assign("l_probe_cloak", $l_probe_cloak);

				$template_object->assign("gotomain", $l_global_mmenu);
				$template_object->display($templatename."probes/probes_scan.tpl");
				include ("footer.php");
				die();
			}
		}
		else
		{
			header("location: main.php\r\n");
		}
	}
	else
	{
		header("location: main.php\r\n");
	}
}
else
{
	header("location: main.php\r\n");
}

?>