<?php 
include ("config/config.php");

get_post_ifset("shipsector, arm, distance");

header("Content-type: image/png"); 

$distance = (float)str_replace(",", "", $distance);

# this should be the approx max distance between 2 points
if ($universe_size < 1) { $universe_size = 20000; }

# number of arms the galaxy should have
if ($spiral_galaxy_arms < 1) { $spiral_galaxy_arms = 3; };

# what the mapping scale is
if ($imscale < 1) { $imscale = 500/$universe_size; };

# how much space to leave around the edge
if ($border < 1) { $border = 10; }

# how much to make vertical smaller then horizontal
if ($aspect_ratio <= 0) { $aspect_ratio = 4.0 / 5.0; }

# step size for axis and grid
if ($step < 1) { $step = intval($universe_size/50); }
if ($step < 5) { $step = 5; }

# pi/6 radians = 30 degrees
$cos_30 = cos(pi()/6.0);
$sin_30 = sin(pi()/6.0);

# set the displayed image sizes
$imxborder = $border;
$imyborder = $border;
$imxsize = intval($universe_size*$imscale); 
$imysize = intval($universe_size*$imscale*$aspect_ratio);

$imx_origin = intval(($imxsize/2) + $border + (($universe_size/2)*$sin_30*$cos_30*$imscale));
$imy_origin = intval(($imysize/2) + $border);

if (function_exists('gd_info'))
	$gd_array = gd_info();

//$myimage = imagecreate ($imx_origin*2, $imy_origin*2) or die ("Cannot Initialize new GD image stream");
if($gd_array['GIF Read Support'])
	$myimage = @ImageCreateFromGIF ("images/3dgalaxybase.gif");
elseif($gd_array['PNG Support'])
	$myimage = @imagecreatefrompng ("images/3dgalaxybase.png");
elseif($gd_array['JPG Support'])
	$myimage = @imagecreatefromjpeg ("images/3dgalaxybase.jpg");

$dkgrey = imagecolorallocate($myimage, 192, 192, 192); 
$black = imagecolorallocate($myimage, 0, 0, 0); 
$red = imagecolorallocate($myimage, 255, 0, 0); 
$green = imagecolorallocate($myimage, 0, 255, 0); 
$blue = imagecolorallocate($myimage, 0, 0, 255); 

//imageinterlace($myimage, 0); 

//imagefill($myimage, 0, 0, $black); 

# draw the axis
imageline($myimage, $imx_origin, $imy_origin, $imx_origin+($imxsize/2), $imy_origin, $green);  # x
$ix = $imx_origin - (($imxsize/2)*$cos_30);
$iy = $imy_origin + (($imysize/2)*$sin_30);
imageline($myimage, $imx_origin, $imy_origin, $ix, $iy, $green);                          # y
imageline($myimage, $imx_origin, $imy_origin, $imx_origin, $imy_origin-($imysize/2), $green);           # z

# draw the scale
for ($x = 0; $x <= $universe_size/2; $x+=$step) {
   $dx = (($x/$universe_size)*$imxsize);
   $dy = (($x/$universe_size)*$imysize);
   imagesetpixel($myimage, $imx_origin+$dx, $imy_origin+1, $green);
   imagesetpixel($myimage, $imx_origin+1, $imy_origin-$dy, $green);
   $ix = ((($x*$cos_30)/$universe_size)*$imxsize);
   $iy = ((($x*$sin_30)/$universe_size)*$imysize);
   imageline($myimage, $imx_origin-$ix, $imy_origin+$iy, $imx_origin-$ix+8, $imy_origin+$iy, $green);
}

# draw the box for side projection
$sd_width = ($imxsize/5.0);
$sd_height = ($imysize/5.0/$aspect_ratio);
$sd_x = $imx_origin - ($imxsize/2);
$sd_y = $imy_origin - ($imysize/2);
imagerectangle($myimage, $sd_x, $sd_y, $sd_x+$sd_width, $sd_y+$sd_height, $green);

# draw the box for top down projection
$td_width = $sd_width;
$td_height = $sd_height;
$td_x = $imx_origin + ($imxsize/2) - $td_width;
$td_y = $imy_origin + ($imysize/2) - $td_height;
imagerectangle($myimage, $td_x, $td_y, $td_x+$td_width, $td_y+$td_height, $green);

function HexToDecimal($hex) {

	$PJHex = "0123456789ABCDEF";
    $hex = AAT_strtoupper($hex);
    
    $number = AAT_strpos($PJHex, AAT_substr($hex, 0, 1)) * 16;
    $number = $number + AAT_strpos($PJHex, AAT_substr($hex, 1, 1));

    return $number;
}

$result4 = $db->Execute ("SELECT distinct zone_id, zone_color, zone_name FROM {$db_prefix}zones ORDER BY zone_name ASC");

while (!$result4->EOF) 
{
	$row4 = $result4->fields;
	$temp = $row4['zone_id'];
	$tempcolor = $row4['zone_color'];
	$tempcolor = str_replace("#", "", $tempcolor);
	$red2 = AAT_substr($tempcolor, 0, 2);
	$green2 = AAT_substr($tempcolor, 2, 2);
	$blue2 = AAT_substr($tempcolor, 4, 2);
	$zonecolor[$temp] = imagecolorallocate($myimage, HexToDecimal($red2), HexToDecimal($green2), HexToDecimal($blue2)); 
	$zonecolorbase[$temp] = $row4['zone_color']; 
	$result4->Movenext();
}


$ship_ix = 0;
$ship_iy = 0;
$ship_x = 0;
$ship_y = 0;
$ship_z = 0;

$debug_query = $db->SelectLimit("SELECT * from {$db_prefix}universe where sector_id = $shipsector", 1);
db_op_result($debug_query,__LINE__,__FILE__);

$ship_x = $debug_query->fields['x'];
$ship_y = $debug_query->fields['y'];
$ship_z = $debug_query->fields['z'];
$is_sg = $debug_query->fields['sg_sector'];

$sql = "SELECT * from {$db_prefix}universe order by sector_id DESC";
if($arm != ''){
	$sql = "SELECT * from {$db_prefix}universe where spiral_arm = $arm order by sector_id DESC";
}

$debug_query = $db->Execute($sql);
db_op_result($debug_query,__LINE__,__FILE__);

# now set pixels for all the coords
while (!$debug_query->EOF){
	$x = $debug_query->fields['x'];
	$y = $debug_query->fields['y'];
	$z = $debug_query->fields['z'];

	$s_x = $ship_x - $x;
	$s_y = $ship_y - $y;
	$s_z = $ship_z - $z;
   	$sector_distance = sqrt(pow($s_x,2.0)+pow($s_y,2.0)+pow($s_z,2.0));

	if($sector_distance <= $distance || $distance == '')
	{
		$sector_id = $debug_query->fields['sector_id'];
		$zone_id = $debug_query->fields['zone_id'];

		if($zonecolorbase[$zone_id] == "#000000"){
			$color = $dkgrey;
		}
		else
		{
			$color = $zonecolor[$zone_id];
		}

		# calculate the othrographic projection of the 3d pt onto 2d space
		$ix = $x - ($y*$cos_30);
		$iy = $z + ($y*$sin_30);
		$ix = $imx_origin + (($ix/$universe_size)*$imxsize);
		$iy = $imy_origin + (($iy/$universe_size)*$imysize);

		# draw the coordinate
		imagesetpixel($myimage, $ix, $iy, $color);

		# draw coordinate in side projection
		imagesetpixel($myimage, $sd_x+($sd_width/2)+(($x/$universe_size)*$sd_width), $sd_y+($sd_height/2)-(($z/$universe_size)*$sd_height), $color);

		# draw coordinate in top down projection
		imagesetpixel($myimage, $td_x+($td_width/2)+(($x/$universe_size)*$td_width), $td_y+($td_height/2)+(($y/$universe_size)*$td_height), $color);

		if($sector_id == $shipsector){
			$ship_ix = $ix;
			$ship_iy = $iy;
			$ship_x = $x;
			$ship_y = $y;
			$ship_z = $z;
		}
	}

	$debug_query->MoveNext();
}

if($is_sg != 0)
{
	$shiplocation = "Location SG Sector";
}
else
{
	$shiplocation = "You are here";
}

if($ship_ix != 0 and  $ship_iy != 0){
	imagestring($myimage, 3, $imx_origin+15, ($imysize-15), $shiplocation, $red); 
	imageline($myimage, $imx_origin+10, ($imysize-10), $imx_origin+5, ($imysize-10), $red);
	imageline($myimage, $imx_origin+5, ($imysize-10), $ship_ix, $ship_iy, $red);
	imageellipse($myimage, $ship_ix, $ship_iy, 4, 4, $red);
}
else
{
	imagestring($myimage, 3, $imx_origin-80, ($imysize), "You are not in this arm.", $red); 
}

$debug_query = $db->SelectLimit("SELECT x, y, z from {$db_prefix}universe where sector_id = 1", 1);
db_op_result($debug_query,__LINE__,__FILE__);

$earth_x = $debug_query->fields['x'];
$earth_y = $debug_query->fields['y'];
$earth_z = $debug_query->fields['z'];

$ix = $earth_x - ($earth_y*$cos_30);
$iy = $earth_z + ($earth_y*$sin_30);
$ix = $imx_origin + (($ix/$universe_size)*$imxsize);
$iy = $imy_origin + (($iy/$universe_size)*$imysize);

imagestring($myimage, 3, $imx_origin-60, ($imysize-15), "Earth", $green); 
imageline($myimage, $imx_origin-20, ($imysize-10), $imx_origin-15, ($imysize-10), $green);
imageline($myimage, $imx_origin-15, ($imysize-10), $ix, $iy, $green);
imageellipse($myimage, $ix, $iy, 4, 4, $green);

if($ship_ix != 0 and  $ship_iy != 0){
	# set it as red in side down
	imageellipse($myimage, $sd_x+($sd_width/2)+(($ship_x/$universe_size)*$sd_width), $sd_y+($sd_height/2)-(($ship_z/$universe_size)*$sd_height), 4, 4, $red);

	# set it as red in top down
	imageellipse($myimage, $td_x+($td_width/2)+(($ship_x/$universe_size)*$td_width), $td_y+($td_height/2)+(($ship_y/$universe_size)*$td_height), 4, 4, $red);
}

if($gd_array['GIF Read Support'])
	imagegif($myimage);
elseif($gd_array['PNG Support'])
	imagepng($myimage);
elseif($gd_array['JPG Support'])
	imagejpeg($myimage);

imagedestroy($myimage); 
?> 

