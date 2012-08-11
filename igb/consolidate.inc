<?php
$percent = $ibank_paymentfee * 100;

$l_igb_transferrate3 = str_replace("[igb_num_percent]", NUMBER($percent,1), $l_igb_transferrate3);
$l_igb_transferrate3 = str_replace("[nbplanets]", $igb_tconsolidate, $l_igb_transferrate3);

$destplanetcreds  = $dest['credits'];

$template_object->assign("l_igb_planetconsolidate", $l_igb_planetconsolidate);
$template_object->assign("l_igb_consolrates", $l_igb_consolrates);
$template_object->assign("l_igb_minimum", $l_igb_minimum);
$template_object->assign("l_igb_maximum", $l_igb_maximum);
$template_object->assign("l_igb_compute", $l_igb_compute);
$template_object->assign("l_igb_transferrate3", $l_igb_transferrate3);
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);
$template_object->assign("l_credits", $l_credits);
$template_object->assign("l_minplanetpercent", $l_minplanetpercent);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_consolidate.tpl");
?>