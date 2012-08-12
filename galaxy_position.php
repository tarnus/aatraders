<?php 

function get_post_ifset($test_vars)
{
	if (!is_array($test_vars))
	{
		$test_vars=explode(",",$test_vars);
	}
	foreach($test_vars as $test_var)
	{
		$test_var = trim($test_var);
		if (isset($_POST[$test_var]))
		{
			global $$test_var;
			$$test_var = $_POST[$test_var];
		} else if (isset($_GET[$test_var]))
		{
			global $$test_var;
			$$test_var = $_GET[$test_var];
		}
	}
}

get_post_ifset("universe_size, sx, sy, sz, hx, hy, hz");

header("Content-type: image/png"); 

# this should be the approx max distance between 2 points
if ($universe_size < 1) { $universe_size = 200000; }

# what the mapping scale is
if ($imscale < 1) { $imscale = 300/$universe_size; };

# how much space to leave around the edge
if ($border < 1) { $border = 10; }

# how much to make vertical smaller then horizontal
if ($aspect_ratio <= 0) { $aspect_ratio = 4.0 / 5.0; }

# pi/6 radians = 30 degrees
$cos_30 = cos(pi()/6.0);
$sin_30 = sin(pi()/6.0);

# set the displayed image sizes
$imxborder = $border;
$imyborder = $border;
$imxsize = 50; 
$imysize = 35;

$imx_origin = intval(($imxsize/2) + $border + (($universe_size/4)*$sin_30*$cos_30*$imscale));
$imy_origin = intval(($imysize/2) + $border);
$myimage = @ImageCreateFromPNG ("images/navbg.png"); 

$dkgrey = imagecolorallocate($myimage, 192, 192, 192); 
$black = imagecolorallocate($myimage, 0, 0, 0); 
$red = imagecolorallocate($myimage, 255, 0, 0); 
$green = imagecolorallocate($myimage, 0, 255, 0); 
$blue = imagecolorallocate($myimage, 61, 121, 175); 



# draw the box for side projection
$sd_width = ($imxsize/1);
$sd_height = ($imysize/1/$aspect_ratio);
$sd_x = $imx_origin - ($imxsize/1.1)-10;
$sd_y = $imy_origin -25;

# draw the box for top down projection
$td_width = $sd_width;
$td_height = $sd_height;
$td_x = $imx_origin +  ($imxsize/9);  
$td_y = $imy_origin -25;

# draw coordinate in side projection
imageellipse($myimage, $sd_x+($sd_width/2)+(($sx/$universe_size)*$sd_width), $sd_y+($sd_height/2)-(($sz/$universe_size)*$sd_height), 4, 4, $red);

# draw coordinate in top down projection
imageellipse($myimage, $td_x+($td_width/2)+(($sx/$universe_size)*$td_width), $td_y+($td_height/2)+(($sy/$universe_size)*$td_height),  4, 4, $red);

// Draw in home base
if ($hx != ""){
	# draw coordinate in side projection
	imageellipse($myimage, $sd_x+($sd_width/2)+(($hx/$universe_size)*$sd_width), $sd_y+($sd_height/2)-(($hz/$universe_size)*$sd_height), 4, 4, $green);

	# draw coordinate in top down projection
	imageellipse($myimage, $td_x+($td_width/2)+(($hx/$universe_size)*$td_width), $td_y+($td_height/2)+(($hy/$universe_size)*$td_height),  4, 4, $green);
}

imagepng($myimage);

imagedestroy($myimage); 
?> 

