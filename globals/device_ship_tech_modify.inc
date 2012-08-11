<?php
if (!function_exists('device_ship_tech_modify')) {

	function device_ship_tech_modify($shipinfo, $shipdevice)
	{
		foreach ($shipdevice as $key => $data) 
		{
			switch ($data['techmodify'])
			{
				case "ship_hull";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['hull'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_engines";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['engines'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_power";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['power'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_fighter";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['fighter'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_sensors";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['sensors'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_beams";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['beams'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_torp_launchers";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['torp_launchers'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_shields";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['shields'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_armor";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['armor'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_cloak";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['cloak'] = $device_object->modify_tech_code($shipinfo);
					}
				break;

				case "ship_ecm";
					if($data['amount'] > 0)
					{
						if(!class_exists($data['class'])){
							include ("class/devices/" . $data['class'] . ".inc");
						}
						$device_object = new $data['class']();
						$shipinfo['ecm'] = $device_object->modify_tech_code($shipinfo);
					}
				break;
			}
		}
		return $shipinfo;
	}
}

?>
