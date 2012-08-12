<?php
include ("languages/$langdir/lang_casino.inc");

$title = $l_casino_title;

if($sectorinfo['port_type'] != "casino")
{
	close_database();
	echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
	die();
}

$template_object->assign("l_casino_welcome", $l_casino_welcome);
$template_object->assign("color_line", $color_line);
$template_object->assign("l_casino_option", $l_casino_option);
$template_object->assign("l_casino_detail", $l_casino_detail);

// Get casino links

$casinodata = file("support/casino.ini");
$j=0;
for($i = 0; $i < count($casinodata); $i += 6){
	$fields = "";
	$fielddata = "";
	$j++;
	for($element = 0; $element < 5; $element++){
		$variable = explode("=", $casinodata[$i + $element], 2);
		$variable[0] = trim($variable[0]);
		$variable[1] = trim($variable[1]);
		$$variable[0] = $variable[1];

		if($element == 3)
		{
			if(trim($variable[1],"'") == "main")
			{
				$variable[1] = "main.php";
			}
			else
			{
				$variable[1] = "casino.php?casinogame=" . trim($variable[1],"'");
			}
		}
		$fields .= $variable[0];
		$fielddata .= trim($variable[1],"'");
		if($element != 5){
			$fields .= ", ";
			$fielddata .= "|";
		}
		list($name_array[$j],$image_array[$j],$description_array[$j],$casino_link_array[$j],$online_status_array[$j])=explode("|",$fielddata);

		//echo "name: ".$name_array[$j]."<br>";
		//echo $variable[0] . " = " . $variable[1] . "<br>";
	}
}

$template_object->assign("item_count",$j);		
$template_object->assign("name_array",$name_array);	
$template_object->assign("image_array",$image_array);		
$template_object->assign("description_array",$description_array);		
$template_object->assign("casino_link_array",$casino_link_array);		
$template_object->assign("online_status_array",$online_status_array);			
$template_object->assign("title",$title);
$template_object->assign("gotomain", $l_global_mmenu);

$template_object->display($templatename."casino.tpl");

include ("footer.php");

?>		