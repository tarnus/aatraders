<?php
$timeparts = explode(" ",microtime());
$starttime = $timeparts[1].substr($timeparts[0],1);

require("../src/class.template.php");
$tpl = new Template_Lite;
$tpl->force_compile = true;

$tpl->assign("Name","Fred Irving Johnathan Bradley Peppergill");
$tpl->assign("FirstName",array("John","Mary","James","Henry"));
$tpl->assign("contacts", array(array("phone" => "1", "fax" => "2", "cell" => "3"),
	  array("phone" => "555-5555", "fax" => "555-4444", "cell" => "555-3333")));
$tpl->assign("bold", array("up", "down", "left", "right"));
$tpl->assign("lala", array("up" => "first entry", "down" => "last entry"));

require('../src/class.TL_MenuBuilder.php');
// we create our bottom-level submenus and work our way up.

TL_MenuBuilder::initMenu($menu_1_level_4);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 4 item 0');
TL_MenuBuilder::setItemLink($item, 'url40');
TL_MenuBuilder::setItemTarget($item, 'target');

// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_1_level_4, $item);


// first we create the submenu
TL_MenuBuilder::initMenu($menu_1_level_3);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 3 item 0');
TL_MenuBuilder::setItemLink($item, 'url30');
TL_MenuBuilder::setItemTarget($item, 'target');

// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_1_level_3, $item);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 3 item 1');
TL_MenuBuilder::setItemLink($item, 'url31');
TL_MenuBuilder::setItemTarget($item, 'target');

TL_MenuBuilder::setItemSubmenu($item, $menu_1_level_4);
// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_1_level_3, $item);

// first we create the submenu
TL_MenuBuilder::initMenu($menu_1_level_2);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 2 item 0');
TL_MenuBuilder::setItemLink($item, 'url20');
TL_MenuBuilder::setItemTarget($item, 'target');

// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_1_level_2, $item);

// repeat process for each item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 2 item 1');
TL_MenuBuilder::setItemLink($item, 'url21');
TL_MenuBuilder::setItemTarget($item, 'target');

TL_MenuBuilder::setItemSubmenu($item, $menu_1_level_3);
TL_MenuBuilder::addMenuItem($menu_1_level_2, $item);

TL_MenuBuilder::initMenu($menu);

// create and add items
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 1 item 0');
TL_MenuBuilder::setItemLink($item, 'url10');
TL_MenuBuilder::setItemTarget($item, 'target');
TL_MenuBuilder::addMenuItem($menu, $item);

TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 1 item 1');
TL_MenuBuilder::setItemLink($item, 'url11');
TL_MenuBuilder::setItemTarget($item, '_blank');
TL_MenuBuilder::setItemTarget($item, 'target');
// this one has a submenu
TL_MenuBuilder::setItemSubmenu($item, $menu_1_level_2);
TL_MenuBuilder::addMenuItem($menu, $item);

// create and add items
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 1 item 2');
TL_MenuBuilder::setItemLink($item, 'url10');
TL_MenuBuilder::setItemTarget($item, 'target');
TL_MenuBuilder::addMenuItem($menu, $item);


// first we create the submenu
TL_MenuBuilder::initMenu($menu_3_level_3);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 3 item 0');
TL_MenuBuilder::setItemLink($item, 'url30');
TL_MenuBuilder::setItemTarget($item, 'target');

// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_3_level_3, $item);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 3 item 1');
TL_MenuBuilder::setItemLink($item, 'url31');
TL_MenuBuilder::setItemTarget($item, 'target');

TL_MenuBuilder::setItemSubmenu($item, $menu_3_level_4);
// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_3_level_3, $item);

// first we create the submenu
TL_MenuBuilder::initMenu($menu_3_level_2);

// create the first submenu item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 2 item 0');
TL_MenuBuilder::setItemLink($item, 'url20');
TL_MenuBuilder::setItemTarget($item, 'target');

// attach the item to the menu
TL_MenuBuilder::addMenuItem($menu_3_level_2, $item);

// repeat process for each item
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 2 item 1');
TL_MenuBuilder::setItemLink($item, 'url21');
TL_MenuBuilder::setItemTarget($item, 'target');

TL_MenuBuilder::setItemSubmenu($item, $menu_3_level_3);
TL_MenuBuilder::addMenuItem($menu_3_level_2, $item);

// create and add items
TL_MenuBuilder::initItem($item);
TL_MenuBuilder::setItemText($item, 'Menu Level 1 item 3');
TL_MenuBuilder::setItemLink($item, 'url10');
TL_MenuBuilder::setItemTarget($item, 'target');
TL_MenuBuilder::setItemSubmenu($item, $menu_3_level_2);
TL_MenuBuilder::addMenuItem($menu, $item);

// our $menu array is now ready!
$tpl->assign('menu_list',$menu);

$tpl->display("index.tpl");

$timeparts = explode(" ",microtime());
$endtime = $timeparts[1].substr($timeparts[0],1);
echo bcsub($endtime,$starttime,6);
?>