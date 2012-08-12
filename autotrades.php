<?php
include("config/config.php");

include("languages/$langdir/lang_autotrade.inc");
include("languages/$langdir/lang_planets.inc");

get_post_ifset("command, dismiss");

$title=$l_autotrade_title;

if(checklogin() or $tournament_setup_access == 1)
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

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

$line_color = "#23244F";
function linecolor()
{
  global $line_color;

  if($line_color == "#3A3B6E")   
   $line_color = "#23244F"; 
  else   
   $line_color = "#3A3B6E"; 

  return $line_color;
}


switch ($command)
{

case "dismiss":

	$dismisstotal = 0;
	for($i = 0; $i <$tradecount; $i++){
		if(isset($dismiss[$i])){
			$debug_query = $db->Execute("delete from {$db_prefix}autotrades WHERE traderoute_id=$dismiss[$i] ");
			db_op_result($debug_query,__LINE__,__FILE__);
			$dismisstotal++;
		}
	}
	$template_object->assign("error_msg", "$dismisstotal $l_autotrade_dismiss2");
	$template_object->assign("gotomain", $l_global_mmenu);
	$template_object->display($templatename."autotradedie.tpl");
	include ("footer.php");
	die();

break;

	default:

		$res = $db->Execute("SELECT * FROM {$db_prefix}autotrades WHERE owner=$playerinfo[player_id] ");
		if($res->RecordCount())
		{
			$template_object->assign("l_autotrade_colonist", $l_autotrade_colonist);
			$template_object->assign("l_autotrade_report", $l_autotrade_report);
			$template_object->assign("l_autotrade_planet", $l_autotrade_planet);
			$template_object->assign("l_autotrade_hull", $l_autotrade_hull);
			$template_object->assign("l_autotrade_capacity", $l_autotrade_capacity);
			$template_object->assign("l_autotrade_energy", $l_autotrade_energy);
			$template_object->assign("l_autotrade_goods", $l_autotrade_goods);
			$template_object->assign("l_autotrade_ore", $l_autotrade_ore);
			$template_object->assign("l_autotrade_organics", $l_autotrade_organics);
			$template_object->assign("l_autotrade_energy", $l_autotrade_energy);
			$template_object->assign("l_autotrade_credits", $l_autotrade_credits);
			$template_object->assign("l_autotrade_delete", $l_autotrade_delete);

			$tradecount = 0;
			while(!$res->EOF)
			{
				$trade = $res->fields;
				$res2 = $db->SelectLimit("SELECT {$db_prefix}planets.*, {$db_prefix}universe.sector_name FROM {$db_prefix}planets, {$db_prefix}universe WHERE {$db_prefix}planets.planet_id=$trade[planet_id] and {$db_prefix}universe.sector_id = {$db_prefix}planets.sector_id", 1);
				$tradeplanet = $res2->fields;

				if($tradeplanet['name'] == '')
					$tradeplanet['name'] = $l_autotrade_unnamed;


				$color[$tradecount] = linecolor();
				$tradesector[$tradecount] = $tradeplanet['sector_name'];
				$tradename[$tradecount] = $tradeplanet['name'];
				$tradehull[$tradecount] = $tradeplanet['cargo_hull'];
				$tradeholds[$tradecount] = number(NUM_HOLDS($tradeplanet['cargo_hull']));
				$tradepower[$tradecount] = $tradeplanet['cargo_power'];
				$tradeenergy[$tradecount] = number(NUM_ENERGY($tradeplanet['cargo_power']));
				if($trade['port_id_goods'] == 0){
					$tradegoodsprice[$tradecount] = 0;
					$tradegoodsport[$tradecount] = '';
				}else{
					$tradegoodsprice[$tradecount] = $trade['goods_price'];
					$res2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id = $trade[port_id_goods]", 1);
					$tradegoodsport[$tradecount] = $res2->fields['sector_name'];
				}
				if($trade['port_id_ore'] == 0){
					$tradeoreprice[$tradecount] = 0;
					$tradeoreport[$tradecount] = '';
				}else{
					$tradeoreprice[$tradecount] = $trade['ore_price'];
					$res2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id = $trade[port_id_ore]", 1);
					$tradeoreport[$tradecount] = $res2->fields['sector_name'];
				}
				if($trade['port_id_organics'] == 0){
					$tradeorganicsprice[$tradecount] = 0;
					$tradeorganicsport[$tradecount] = '';
				}else{
					$tradeorganicsprice[$tradecount] = $trade['organics_price'];
					$res2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id = $trade[port_id_organics]", 1);
					$tradeorganicsport[$tradecount] =  $res2->fields['sector_name'];
				}
				if($trade['port_id_energy'] == 0){
					$tradeenergyprice[$tradecount] = 0;
					$tradeenergyport[$tradecount] = '';
				}else{
					$tradeenergyprice[$tradecount] = $trade['energy_price'];
					$res2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id = $trade[port_id_energy]", 1);
					$tradeenergyport[$tradecount] =  $res2->fields['sector_name'];
				}
				if($trade['port_id_colonist'] == 0){
					$tradeenergyprice[$tradecount] = 0;
					$tradecolonistport[$tradecount] = '';
				}else{
					$tradecolonistprice[$tradecount] = $trade['colonist_price'];
					$res2 = $db->SelectLimit("SELECT sector_name FROM {$db_prefix}universe WHERE sector_id = $trade[port_id_colonist]", 1);
					$tradecolonistport[$tradecount] = $res2->fields['sector_name'];
				}
				$tradecredits[$tradecount] = number($trade['current_trade']);
				$tradedismiss[$tradecount] = $trade['traderoute_id'];
				$tradecount++;
				$res->MoveNext();
			}
			$template_object->assign("color", $color);
			$template_object->assign("tradesector", $tradesector);
			$template_object->assign("tradename", $tradename);
			$template_object->assign("tradehull", $tradehull);
			$template_object->assign("tradeholds", $tradeholds);
			$template_object->assign("tradepower", $tradepower);
			$template_object->assign("tradeenergy", $tradeenergy);
			$template_object->assign("l_autotrade_noroute", $l_autotrade_noroute);
			$template_object->assign("tradegoodsprice", $tradegoodsprice);
			$template_object->assign("tradeoreprice", $tradeoreprice);
			$template_object->assign("tradeorganicsprice", $tradeorganicsprice);
			$template_object->assign("tradecolonistprice", $tradecolonistprice);
			$template_object->assign("tradeenergyprice", $tradeenergyprice);
			$template_object->assign("l_autotrade_credit2", $l_autotrade_credit2);
			$template_object->assign("l_autotrade_sector", $l_autotrade_sector);
			$template_object->assign("tradegoodsport", $tradegoodsport);
			$template_object->assign("tradeoreport", $tradeoreport);
			$template_object->assign("tradeorganicsport", $tradeorganicsport);
			$template_object->assign("tradeenergyport", $tradeenergyport);
			$template_object->assign("tradecolonistport", $tradecolonistport);
			$template_object->assign("tradecredits", $tradecredits);
			$template_object->assign("tradedismiss", $tradedismiss);
			$template_object->assign("l_autotrade_deletebutton", $l_autotrade_deletebutton);
			$template_object->assign("tradecount", $tradecount);
		}
		else
		{
			$template_object->assign("error_msg", $l_autotrade_noroute2);
			$template_object->assign("gotomain", $l_global_mmenu);
			$template_object->display($templatename."autotradedie.tpl");
			include ("footer.php");
			die();
		}

break;

}   //swich

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."autotrades.tpl");

include("footer.php");
?>
