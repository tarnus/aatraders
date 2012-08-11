<?php
if (!function_exists('RecurseDir')) {

	function RecurseDir($basedir, $AllDirectories=array()) { 
		#Create array for current directories contents 
		$ThisDir=array(); 
		if ($handle = @opendir($basedir)) {
    		while (false !== ($file = readdir($handle))) { 
				if ($file != "." && $file != "..") { 
					if (is_dir($basedir."/".$file)) {
						array_push($ThisDir,$file);     
					}
				}
			}
			closedir($handle); 
		}
		#Loop through each directory,  run RecurseDir function on each one 
		foreach ($ThisDir as $key=>$var) { 
			array_push($AllDirectories, $var); 
			$AllDirectories=RecurseDir($var, $AllDirectories); 
		} 
		return $AllDirectories; 
	}
}
?>
