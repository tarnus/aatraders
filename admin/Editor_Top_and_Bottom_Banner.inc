<?php
// 2: Top and Bottom Banner
// You can add HTML banners to the top and/or bottom of every page using this tool.

get_post_ifset("top_banner, bottom_banner, command");

if($command != "SUBMIT"){
	$banner_top = "";
	$lines = @file ("config/banner_top.inc");
	for($i=0; $i<count($lines); $i++){
		$banner_top .= $lines[$i];
	}

	$banner_bottom = "";
	$lines = @file ("config/banner_bottom.inc");
	for($i=0; $i<count($lines); $i++)
		$banner_bottom .= $lines[$i];

	echo "<tr><td><table width=\"100%\"><form action=admin.php method=post>";
	echo "<tr><td colspan=2>$banner_top</td></tr>";
	$banner_top = str_replace("<table border='0' align='center'><tr><td>", "", $banner_top);
	$banner_top = str_replace("</td></tr></table>", "", $banner_top);
	echo "<TR nowrap><TD width=\"250\"><b>Insert Top Banner Code:</b><br>This is just raw banner code.  Do not include any table, tr or td tags.<br><br><font color=#00ff00><i>Leave this blank if you do not want to place a banner at the top of the page.</i></font></TD>";
	echo "<TD><TEXTAREA NAME=top_banner ROWS=10 COLS=60>$banner_top</TEXTAREA></TD></tr>";
	echo "<tr><td colspan=2>$banner_bottom</td></tr>";
	$banner_bottom = str_replace("<table border='0' align='center'><tr><td>", "", $banner_bottom);
	$banner_bottom = str_replace("</td></tr></table>", "", $banner_bottom);
	echo "<TR nowrap><TD width=\"250\"><b>Insert Bottom Banner Code:</b><br>This is just raw banner code.  Do not include any table, tr or td tags.<br><br><font color=#00ff00><i>Leave this blank if you do not want to place a banner at the bottom of the page.</i></font></TD>";
	echo "<TD><TEXTAREA NAME=bottom_banner ROWS=10 COLS=60>$banner_bottom</TEXTAREA></TD></tr>";

	echo "<tr><td colspan=2 align=center><input type=hidden name=admin_password value=$admin_password>";
	echo "<INPUT TYPE=HIDDEN NAME=menu VALUE=\"Editor_Top_and_Bottom_Banner\">";
	echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
	echo "<input type=submit NAME=command value=SUBMIT><input type=reset value=Reset></td></tr>";
	echo "</form></table></td></tr>";
}else{
	@unlink($gameroot."config/banner_top.inc");
	@unlink($gameroot."config/banner_bottom.inc");
	echo "<tr><td>";
	if(trim($top_banner) != ''){
		$fs = @fopen('config/banner_top.inc', 'w');
		@fwrite($fs, "<table border='0' align='center'><tr><td>". stripslashes($top_banner) . "</td></tr></table>");
		@fclose($fs);
		echo "<br><b>Top Banner Saved.</b><br>";
	}else{
		echo "<br><b>Top Banner deleted.</b><br>";
	}

	if(trim($bottom_banner) != ''){
		$fs = @fopen('config/banner_bottom.inc', 'w');
		@fwrite($fs, "<table border='0' align='center'><tr><td>". stripslashes($bottom_banner) . "</td></tr></table>");
		@fclose($fs);
		echo "<br><b>Bottom Banner Saved.</b><br>";
	}else{
		echo "<br><b>Bottom Banner deleted.</b><br>";
	}
	echo "</td></tr>";
}
?>
