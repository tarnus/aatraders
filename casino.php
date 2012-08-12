<?php
// This program is free software; you can redistribute it and/or modify it	 
// under the terms of the GNU General Public License as published by the	 
// Free Software Foundation; either version 2 of the License, or (at your	
// option) any later version.												
// 
// File: casino.php

include ("config/config.php");

get_post_ifset("casinogame");

$template_object->enable_gzip = 0;

$title = $l_title_port;

if (checklogin() or $tournament_setup_access == 1)
{
	$template_object->enable_gzip = 0;
	include ("footer.php");
	die();
}

include ("casino/" . $casinogame . ".inc");

?>
