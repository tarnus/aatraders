<?php
$template_object->assign("l_igb_depositfunds", $l_igb_depositfunds);
$template_object->assign("l_igb_accountholder", $l_igb_accountholder);
$template_object->assign("l_igb_shipaccount", $l_igb_shipaccount);
$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
$template_object->assign("playername", $playerinfo['character_name']);
$template_object->assign("playercredits", NUMBER($playerinfo['credits']));
$template_object->assign("accountbalance", NUMBER($account['balance']));
$template_object->assign("l_igb_credit_symbol", $l_igb_credit_symbol);
$template_object->assign("l_igb_seldepositamount", $l_igb_seldepositamount);
$template_object->assign("max_igb_storage", $max_igb_storage);
$template_object->assign("l_igb_deposit", $l_igb_deposit);
$template_object->assign("l_igb_maximum", $l_igb_maximum);
$template_object->assign("l_igb_igbaccount", $l_igb_igbaccount);
$template_object->assign("l_credits", $l_credits);
$template_object->assign("max_igb_storage", NUMBER($max_igb_storage));
$template_object->assign("l_igb_back", $l_igb_back);
$template_object->assign("l_igb_logout", $l_igb_logout);

$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."igb/igb_deposit.tpl");
?>