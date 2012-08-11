<?php
	get_post_ifset("by");
include ("languages/$langdir/lang_spy.inc");

$spy_object = array();
$job_type = array();
$job_name = array();
$classcount = 0;

$filelist = get_dirlist($gameroot."class/spies/");
for ($c=0; $c<count($filelist); $c++) {
	if($filelist[$c] != "index.html")
	{
		$spy_classname =  str_replace(".inc", "", $filelist[$c]); 
		if(!class_exists($spy_classname)){
			include ("class/spies/" . $spy_classname . ".inc");
		}
		$store_object = new $spy_classname();
		$job_type[$classcount] = $store_object->id;
		$job_name[$job_type[$classcount]] = $store_object->classname;
		$description[$job_type[$classcount]] = $store_object->description;
		$spy_object[$job_type[$classcount]] = $store_object;
		$classcount++;
	}
}

$template_object->assign("job_name", $job_name);
$template_object->assign("l_spy_legend", $l_spy_legend);
$template_object->assign("description", $description);
$template_object->assign("l_spy_description", $l_spy_description);
$template_object->assign("l_spy_changeerror", $l_spy_changeerror);

	$template_object->assign("planetowner", $planetinfo['owner']);
	if($planetinfo['owner'] != 3){
		$l_planet_att_link="<a href='planet.php?planet_id=$planet_id&command=attackpreview'>" . $l_planet_att_link ."</a>";
		$l_planet_att=str_replace("[attack]",$l_planet_att_link,$l_planet_att);
	}
	$l_planet_scn_link="<a href='planet.php?planet_id=$planet_id&command=scan'>" . $l_planet_scn_link ."</a>";
	$l_planet_scn=str_replace("[scan]",$l_planet_scn_link,$l_planet_scn);

	if($planetinfo['owner'] != 3){
		$template_object->assign("l_planet_scn", $l_planet_scn);
		$template_object->assign("l_planet_att", $l_planet_att);
	}

	if($shipdevice['dev_nova']['amount'] != "0" and $planetinfo['owner'] != 3){
		$template_object->assign("novaavailible", 1);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_planet_firenova", $l_planet_firenova);
	}

	if ($sofa_on and $planetinfo['owner'] != 3){
		$template_object->assign("sofaavailible", 1);
		$template_object->assign("planet_id", $planet_id);
		$template_object->assign("l_sofa", $l_sofa);
	}

	$template_object->assign("enable_spies", $enable_spies);
	if ($enable_spies)
	{
		if (!isset($by)) 
		{ 
			$by = ''; 
		}
		if ($by == 'job_id')
			$by = "job_id desc, spy_id asc";
		elseif ($by == 'move_type')   
				$by = "move_type asc, spy_id asc";
		else
		   $by = "spy_id asc";

		$r = $db->Execute("SELECT * FROM {$db_prefix}spies WHERE active = 'Y' AND planet_id = $planet_id AND owner_id = $playerinfo[player_id] ORDER BY $by");
		$numspies = $r->RecordCount();
		$template_object->assign("numspies", $numspies);
		if ($numspies)
		{
			if ($numspies<$max_spies_per_planet and $planetinfo['owner'] != 3)
				$template_object->assign("addaspy", 1);

			$template_object->assign("l_spy_yourspies", $l_spy_yourspies);
			$template_object->assign("planet_id", $planet_id);
			$template_object->assign("l_spy_sendnew", $l_spy_sendnew);
			$template_object->assign("ID", "ID");
			$template_object->assign("l_spy_job", $l_spy_job);
			$template_object->assign("l_spy_changebutton", $l_spy_changebutton);
			$template_object->assign("l_spy_changejob", $l_spy_changejob);
			$template_object->assign("l_spy_move", $l_spy_move);
			$template_object->assign("l_spy_action", $l_spy_action);

			$counter = 0;
			while (!$r->EOF)
			{
				$spy = $r->fields;
				$job[$counter] = $job_name[$spy['job_id']];
				$temp = $spy['move_type'];
				$move = $l_spy_moves[$temp];

				$spyid[$counter] = $spy['spy_id'];
				$spymove[$counter] = $move;
				$counter++;
				$r->MoveNext();
			}

			$template_object->assign("job", $job);
			$template_object->assign("spyid", $spyid);
			$template_object->assign("spymove", $spymove);
			$template_object->assign("l_spy_comeback", $l_spy_comeback);
			$template_object->assign("spymove", $spymove);

			$template_object->assign("l_base", $l_base);
			$template_object->assign("l_planetary_SD_weapons", $l_planetary_SD_weapons);
			$template_object->assign("l_planetary_SD_sensors", $l_planetary_SD_sensors);
			$template_object->assign("l_planetary_SD_cloak", $l_planetary_SD_cloak);
			$template_object->assign("l_planetary_fighter", $l_planetary_fighter);
			$template_object->assign("l_planetary_sensors", $l_planetary_sensors);
			$template_object->assign("l_planetary_beams", $l_planetary_beams);
			$template_object->assign("l_planetary_torp_launch", $l_planetary_torp_launch);
			$template_object->assign("l_planetary_shields", $l_planetary_shields);
			$template_object->assign("l_planetary_jammer", $l_planetary_jammer);
			$template_object->assign("l_planetary_cloak", $l_planetary_cloak);
			$template_object->assign("l_planetary_defense_levels", $l_planetary_defense_levels);
			$template_object->assign("planetbased", ($planetinfo['base']=='Y') ? $l_yes : $l_no);
			$template_object->assign("sector_defense_weapons", NUMBER($planetinfo['sector_defense_weapons']));
			$template_object->assign("sector_defense_sensors", NUMBER($planetinfo['sector_defense_sensors']));
			$template_object->assign("sector_defense_cloak", NUMBER($planetinfo['sector_defense_cloak']));
			$template_object->assign("planetfighter", NUMBER($planetinfo['fighter']));
			$template_object->assign("planetsensors", NUMBER($planetinfo['sensors']));
			$template_object->assign("planetbeams", NUMBER($planetinfo['beams']));
			$template_object->assign("planetlaunchers", NUMBER($planetinfo['torp_launchers']));
			$template_object->assign("planetshields", NUMBER($planetinfo['shields']));
			$template_object->assign("planetjammer", NUMBER($planetinfo['jammer']));
			$template_object->assign("planetcloak", NUMBER($planetinfo['cloak']));

			$template_object->assign("l_ore", $l_ore);
			$template_object->assign("l_organics", $l_organics);
			$template_object->assign("l_goods", $l_goods);
			$template_object->assign("l_energy", $l_energy);
			$template_object->assign("l_colonists", $l_colonists);
			$template_object->assign("l_credits", $l_credits);
			$template_object->assign("l_fighters", $l_fighters);
			$template_object->assign("l_torps", $l_torps);
			$template_object->assign("l_current_qty", $l_current_qty);

			$template_object->assign("planetore", NUMBER($planetinfo['ore']));
			$template_object->assign("planetorganics", NUMBER($planetinfo['organics']));
			$template_object->assign("planetgoods", NUMBER($planetinfo['goods']));
			$template_object->assign("planetenergy", NUMBER($planetinfo['energy']));
			$template_object->assign("planetcolonists", NUMBER($planetinfo['colonists']));
			$template_object->assign("planetcredits", NUMBER($planetinfo['credits']));
			$template_object->assign("planetfighters", NUMBER($planetinfo['fighters']));
			$template_object->assign("planettorps", NUMBER($planetinfo['torps']));

			$template_object->assign("l_planet_perc", $l_planet_perc);
			$template_object->assign("l_planet_interest", $l_planet_interest);
			$template_object->assign("prodore", $planetinfo['prod_ore']);
			$template_object->assign("prodorganics", $planetinfo['prod_organics']);
			$template_object->assign("prodgoods", $planetinfo['prod_goods']);
			$template_object->assign("prodenergy", $planetinfo['prod_energy']);
			$template_object->assign("na", "n/a");
			$template_object->assign("prodfighters", $planetinfo['prod_fighters']);
			$template_object->assign("prodtorp", $planetinfo['prod_torp']);

		}
		else 
		{
			$template_object->assign("planetowner", $planetinfo['owner']);
			if($planetinfo['owner'] != 3){
				$template_object->assign("l_spy_nospieshere", $l_spy_nospieshere);
				$template_object->assign("l_spy_sendnew", $l_spy_sendnew);
				$template_object->assign("planet_id", $planet_id);
			}
		}
		$r->close();
	}  

	$template_object->assign("planet_id", $planet_id);
	$template_object->assign("l_clickme", $l_clickme);
	$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
	$template_object->assign("allow_ibank", $allow_ibank);
	$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
	$template_object->assign("l_igb_term", $l_igb_term);
	$template_object->assign("l_by_placebounty", $l_by_placebounty);

	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."planet_unowned/planet_display_enemy.tpl");
	include ("footer.php");
	die();
?>