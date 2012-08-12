<?php
include ("languages/$langdir/lang_attack.inc");
include ("globals/combat_functions.inc");
include ("globals/planet_bounty_check.inc");
include ("globals/display_this_planet.inc");

$countplanet = 0;
display_this_planet($planetinfo);
$titleimage = $planetimg[0];
$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $ownerinfo, 0);
$template_object->assign("isfedbounty", $isfedbounty);
$template_object->assign("l_by_fedbounty2", $l_by_fedbounty2);
$template_object->assign("l_by_nofedbounty", $l_by_nofedbounty);

$template_object->assign("titleimage", $titleimage);

$template_object->assign("planetname", $planetinfo['name']);

if($planetinfo['owner'] != 3)
{
	$l_planet_att_link="<a href='planet.php?planet_id=$planet_id&command=attackpreview'>" . $l_planet_att_link ."</a>";
	$l_planet_att=str_replace("[attack]",$l_planet_att_link,$l_planet_att);
}
else
{
	$l_planet_att = "";
}

$l_planet_scn_link="<a href='planet.php?planet_id=$planet_id&command=scan'>" . $l_planet_scn_link ."</a> ";
$l_planet_scn=str_replace("[scan]",$l_planet_scn_link,$l_planet_scn);

$template_object->assign("l_planet_att", $l_planet_att);
$template_object->assign("l_planet_scn", $l_planet_scn);

$template_object->assign("l_sofa", $l_sofa);
$template_object->assign("l_planet_att_sure", $l_planet_att_sure);

$template_object->assign("l_clickme", $l_clickme);
$template_object->assign("l_toplanetmenu", $l_toplanetmenu);
$template_object->assign("allow_ibank", $allow_ibank);
$template_object->assign("planet_id", $planet_id);
$template_object->assign("l_igb_term", $l_igb_term);
$template_object->assign("l_ifyouneedplan", $l_ifyouneedplan);
$template_object->assign("l_by_placebounty", $l_by_placebounty);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."planet_unowned/sofa_preview.tpl");

include ("footer.php");
die();
?>