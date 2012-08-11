<?php
// This program is free software; you can redistribute it and/or modify it   
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: ajax_processor.php

include ("config/config.php");
$template_object->enable_gzip = 0;

get_post_ifset("command");

if(!checklogin() && !empty($command))
{
	if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
		$templatename = $default_template;
	}else{
		$templatename = $playerinfo['template'];
	}
	@include ("ajax/" . $command . ".inc");
}

unset($_SESSION['currentprogram'], $currentprogram);
unset ($template_object);
?> 
