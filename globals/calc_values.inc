<?php
if (!function_exists('calc_highshipvalue')) {
	function calc_highship($player_id)
	{
		
		global $db, $db_prefix;

		$res = $db->SelectLimit("SELECT count(*) as shipnum,player_id,ship_id, 
max(hull) as hull,  
max(engines) as engines,  
max(power) as power,
max(fighter) as fighter,
max(sensors) as sensors,
max(beams) as beams,
max(torp_launchers) as torp_launchers,
max(shields) as shields,
max(ecm) as ecm,
max(armor) as armor,
max(cloak) as cloak

 FROM aatrade_ships WHERE player_id=$player_id", 1);
		db_op_result($res,__LINE__,__FILE__);
        if ($result3 > 0)
        {
		$highship = $res->fields;
		$res->close();
            return $highship['ship_id'];
        }else{
            return 0;
        }

	}
}




if (!function_exists('calc_highplanet')) {
    function calc_highplanet($player_id)
    {
        
        global $db, $db_prefix;


        $res = $db->SelectLimit("
SELECT owner,planet_id, 
max(sector_defense_weapons) as sector_defense_weapons ,  
max(sector_defense_sensors) as sector_defense_sensors,  
max(sector_defense_cloak) as sector_defense_cloak ,
max(fighter) as fighter,
max(sensors) as sensors ,
max(beams) as beams,
max(torp_launchers) as torp_launchers,
max(shields) as shields,
max(jammer) as jammer,
max(armor) as armor,
max(cloak) as cloak

 FROM `aatrade_planets` WHERE owner=$player_id ORDER BY max(sector_defense_weapons)  DESC ", 1);
        db_op_result($res,__LINE__,__FILE__);
        if ($result3 > 0)
        {
        $highplanet = $res->fields;
        $res->close();
            return $highplanet['planet_id'];
        }else{
            return 0;
        }

    }
}

if (!function_exists('calc_planet_value')) {
    function calc_planet_value($planet_id)
    {
        global $db, $db_prefix;
        
    }
}
if (!function_exists('calc_ship_value')) {
    function calc_ship_value($ship_id)
    {
        global $db, $db_prefix;
        $query = "select * from {$db_prefix}ships WHERE ship_id=$player_details[currentship]";
                            $debug_query = $db->Execute("$query");
                            db_op_result($debug_query,__LINE__,__FILE__);
                            if ($debug_query->RecordCount() > 0)
                            {
                                $bounty_ship = $debug_query->fields;
        $total_cost=phpchangeDelta($bounty_ship['hull_normal'],$bounty_ship['hull'])+
                                phpchangeDelta($bounty_ship['engines_normal'],$bounty_ship['engines'])+
                                phpchangeDelta($bounty_ship['power_normal'],$bounty_ship['power'])+
                                phpchangeDelta($bounty_ship['fighter_normal'],$bounty_ship['fighter'])+
                                phpchangeDelta($bounty_ship['sensors_normal'],$bounty_ship['sensors'])+
                                phpchangeDelta($bounty_ship['beams_normal'],$bounty_ship['beams'])+
                                phpchangeDelta($bounty_ship['armor_normal'],$bounty_ship['armor'])+
                                phpchangeDelta($bounty_ship['torp_launchers_normal'],$bounty_ship['torp_launchers'])+
                                phpchangeDelta($bounty_ship['shields_normal'],$bounty_ship['shields'])+
                                phpchangeDelta($bounty_ship['cloak_normal'],$bounty_ship['cloak'])+
                                phpchangeDelta($bounty_ship['ecm_normal'],$bounty_ship['ecm']);
                                $total_cost = round($total_cost * ($repair_modifier / 100));
                                return $total_cost;
                            }else{
                                return 0;
                            }
    }
}

?>
