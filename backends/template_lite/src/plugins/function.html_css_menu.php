<?php
/**
 * Template Lite plugin
 * @package Template Lite
 * @subpackage plugins
 */

/**
 * Template Lite {html_css_menu} function plugin
 *
 * Type:	  function<br>
 * Name:	  div_menu<br>
 * Date:	  March 20, 2007<br>
 * Purpose:  make a horizontal or vertical div menu from an array of data<br>
 * Input:<br>
 *			- menu_list = array containing main menu items
 *			- menu_id = Use a menu id (alphnumeric) if you want to use multiple menus on the same page. (optional)
 *			- main_bg_color = background color of main menu (optional)
 *			- border_color = border color around menu selections (optional)
 *			- text_color = text color for all menu selections (optional)
 *			- sub_bg_color = background color for all sub menus (optional)
 *			- hover_bg_color = background color when hovering over a menu selection (optional)
 *			- hover_text_color = text color when hovering over a menu selection (optional)
 *			- newsub_bg_color = background color for selection to indicate it has sub menus (optional)
 *			- sub_down_arrow = path to down arrow image (optional)
 *			- sub_right_arrow = path to right arrow image (optional)
 *			- sub_width = fixed width for all sub menus (optional)
 *			- horizontal_width = fixed width for the main horizontal menu.  The default width is 'auto' (optional)
 *			- vertical_width = fixed width for all main vertical menu including sub menus (optional)
 *			- enable_vertical = 1 to enable a vertical menu, 0 to enable horizontal menu (default) (optional)
 *			- menu_css_file = optional CSS file for more heavily modifying the look of the CSS menu (optional)
 *			- zindex = Use the zindex to position the menu above other page elements. Default: 2000 (optional)
 *
 * Examples:
 * <pre>
 * {html_css_menu menu_list=$data}
 * {html_css_menu menu_list=$data enable_vertical=1}
 * </pre>
 * @author Mark Dickenson
 * @author credit to Dynamic Drive http://www.dynamicdrive.com/style/
 * @version  1.0
 * @param array
 * @param template_object
 * @return string
 */
function tpl_function_html_css_menu($params, &$template_object)
{
	 $menu_id = '1';
	 $main_bg_color = '#F3F3F3';
	 $border_color = 'black';
	 $text_color = 'black';
	 $sub_bg_color = '#A3A3A3';
	 $hover_bg_color = '#838383';
	 $hover_text_color = 'white';
	 $newsub_bg_color = '#d2d7d3';
	 $sub_down_arrow = '';
	 $sub_right_arrow = '';
	 $horizontal_width = 'auto';
	 $vertical_width = '160px';
	 $sub_width = '160px';
	 $enable_vertical = 0;
	 $menu_css_file = '';
	 $zindex = '2000';

	 foreach ($params as $_key=>$_value) {
		  switch ($_key) {
				case 'menu_list':
					 $$_key = (array)$_value;
					 break;

				case 'enable_vertical':
				case 'zindex':
					 $$_key = (int)$_value;
					 break;

				case 'menu_id':
				case 'horizontal_width':
				case 'menu_css_file':
				case 'sub_width':
				case 'vertical_width':
				case 'main_bg_color':
				case 'border_color':
				case 'text_color':
				case 'sub_bg_color':
				case 'hover_bg_color':
				case 'newsub_bg_color':
				case 'sub_down_arrow':
				case 'sub_right_arrow':
					 $$_key = (string)$_value;
					 break;
		  }
	 }

	if($enable_vertical == 0)
	{
		if(!empty($menu_css_file))
		{
			$output = implode('', file($menu_css_file));
		}
		else
		{
			$output = "<style type=\"text/css\">

/*Credits: Dynamic Drive CSS Library */
/*URL: http://www.dynamicdrive.com/style/ */

.suckertreemenu$menu_id ul{
	margin: 0;
	padding: 0;
	list-style-type: none;
	z-index: $zindex; 
}

/*Top level list items*/
.suckertreemenu$menu_id ul li{
	position: relative;
	display: inline;
	float: left;
	background-color: $main_bg_color; /*overall menu background color*/
	z-index: $zindex; 
}

/*Top level menu link items style*/
.suckertreemenu$menu_id ul li a{
	display: block;
	width: $horizontal_width; /*Width of top level menu link items*/
	padding: 1px 10px;
	border: 1px solid $border_color;
	border-left-width: 1;
	text-decoration: none;
	color: $text_color;
	";

			if(strtolower($horizontal_width) == "auto")
			{
				$output .= "white-space: nowrap;";
			}

			$output .= "
}
	
/*1st sub level menu*/
.suckertreemenu$menu_id ul li ul{
	left: 0;
	position: absolute;
	top: 1em; /* no need to change, as true value set by script */
	display: block;
	visibility: hidden;
}

/*Sub level menu list items (undo style from Top level List Items)*/
.suckertreemenu$menu_id ul li ul li{
	display: list-item;
	float: none;
}

/*All subsequent sub menu levels offset after 1st level sub menu */
.suckertreemenu$menu_id ul li ul li ul{ 
	left: auto; /* no need to change, as true value set by script */
	top: 0;
}

/* Sub level menu links style */
.suckertreemenu$menu_id ul li ul li a{
	display: block;
	width: $sub_width; /*width of sub menu levels*/
	color: $text_color;
	text-decoration: none;
	padding: 1px 10px;
	border: 1px solid $border_color;
	white-space: normal;
}

.suckertreemenu$menu_id ul li a:hover{
	background-color: $hover_bg_color;
	color: $hover_text_color;
}

/*Background image for top level menu list links */
.suckertreemenu$menu_id .mainfoldericon{
	background: $newsub_bg_color url($sub_down_arrow) no-repeat center right;
}

/*Background image for subsequent level menu list links */
.suckertreemenu$menu_id .subfoldericon{
	background: $newsub_bg_color url($sub_right_arrow) no-repeat center right;
}

/* Holly Hack for IE \*/
* html .suckertreemenu$menu_id ul li { float: left; height: 1%; }
* html .suckertreemenu$menu_id ul li a { height: 1%; width: 1px;}
* html .suckertreemenu$menu_id ul li ul li { float: left;}
/* End */

</style>";
		}

		$output .= "<script type=\"text/javascript\">

//SuckerTree Horizontal Menu (Sept 14th, 06)
//By Dynamic Drive: http://www.dynamicdrive.com/style/

var menuid$menu_id=\"treemenu$menu_id\"

function buildsubmenus_horizontal$menu_id()
{
	var ultags=document.getElementById(menuid$menu_id).getElementsByTagName(\"ul\")
	for (var t=0; t<ultags.length; t++)
	{
		if (ultags[t].parentNode.parentNode.id==menuid$menu_id)
		{ //if this is a first level submenu
			ultags[t].style.top=ultags[t].parentNode.offsetHeight+\"px\" //dynamically position first level submenus to be height of main menu item
			ultags[t].parentNode.getElementsByTagName(\"a\")[0].className=\"mainfoldericon\"
		}
		else
		{ //else if this is a sub level menu (ul)
			ultags[t].style.left=ultags[t-1].getElementsByTagName(\"a\")[0].offsetWidth+\"px\" //position menu to the right of menu item that activated it
			ultags[t].parentNode.getElementsByTagName(\"a\")[0].className=\"subfoldericon\"
		}
		ultags[t].parentNode.onmouseover=function()
		{
			this.getElementsByTagName(\"ul\")[0].style.visibility=\"visible\"
		}
		ultags[t].parentNode.onmouseout=function()
		{
			this.getElementsByTagName(\"ul\")[0].style.visibility=\"hidden\"
		}
	}
}

if (window.addEventListener)
	window.addEventListener(\"load\", buildsubmenus_horizontal$menu_id, false)
else if (window.attachEvent)
	window.attachEvent(\"onload\", buildsubmenus_horizontal$menu_id)

</script>
";
	}
	else
	{
		if(!empty($menu_css_file))
		{
			$output = implode('', file($menu_css_file));
		}
		else
		{
			$output = "<style type=\"text/css\">

/*Credits: Dynamic Drive CSS Library */
/*URL: http://www.dynamicdrive.com/style/ */

.suckertreemenu$menu_id ul{
	margin: 0;
	padding: 0;
	list-style-type: none;
	width: $vertical_width; /* Width of Menu Items */
	z-index: $zindex; 
}

.suckertreemenu$menu_id ul li{
	position: relative;
	background-color: $main_bg_color; /*overall menu background color*/
	z-index: $zindex; 
}

/*Sub level menu items */
.suckertreemenu$menu_id ul li ul{
	position: absolute;
	width: $sub_width; /*sub menu width*/
	top: 0;
	visibility: hidden;
}

/* Sub level menu links style */
.suckertreemenu$menu_id ul li a{
	display: block;
	overflow: auto; /*force hasLayout in IE7 */
	color: $text_color;
	text-decoration: none;
	padding: 1px 10px;
	border: 1px solid $border_color;
}

.suckertreemenu$menu_id ul li a:hover{
	background-color: $hover_bg_color;
	color: $hover_text_color;
}

/*Background image for subsequent level menu list links */
.suckertreemenu$menu_id .subfoldericon{
	background: $newsub_bg_color url($sub_right_arrow) no-repeat center right;
}

/* Holly Hack for IE \*/
* html .suckertreemenu$menu_id ul li { float: left; height: 1%; }
* html .suckertreemenu$menu_id ul li a { height: 1%; }
* html .suckertreemenu$menu_id ul li ul li { float: left;}
/* End */

</style>";
		}


		$output .= "<script type=\"text/javascript\">

//SuckerTree Vertical Menu 1.1 (Nov 8th, 06)
//By Dynamic Drive: http://www.dynamicdrive.com/style/

var menuid$menu_id=\"treemenu$menu_id\" //Enter id(s) of SuckerTree UL menus, separated by commas

function buildsubmenus$menu_id(){
	var ultags=document.getElementById(menuid$menu_id).getElementsByTagName(\"ul\")
	for (var t=0; t<ultags.length; t++){
		ultags[t].parentNode.getElementsByTagName(\"a\")[0].className=\"subfoldericon\"
		if (ultags[t].parentNode.parentNode.id==menuid$menu_id) //if this is a first level submenu
			ultags[t].style.left=ultags[t].parentNode.offsetWidth+\"px\" //dynamically position first level submenus to be width of main menu item
		else //else if this is a sub level submenu (ul)
			ultags[t].style.left=ultags[t-1].getElementsByTagName(\"a\")[0].offsetWidth+\"px\" //position menu to the right of menu item that activated it
		ultags[t].parentNode.onmouseover=function(){
			this.getElementsByTagName(\"ul\")[0].style.display=\"block\"
		}
		ultags[t].parentNode.onmouseout=function(){
			this.getElementsByTagName(\"ul\")[0].style.display=\"none\"
		}
	}
	for (var t=ultags.length-1; t>-1; t--){ //loop through all sub menus again, and use \"display:none\" to hide menus (to prevent possible page scrollbars
		ultags[t].style.visibility=\"visible\"
		ultags[t].style.display=\"none\"
	}
}

if (window.addEventListener)
	window.addEventListener(\"load\", buildsubmenus$menu_id, false)
else if (window.attachEvent)
	window.attachEvent(\"onload\", buildsubmenus$menu_id)

</script>
";
	}

	if(empty($params['menu_list'])) {
		$tpl->trigger_error("menu_init: missing 'data' parameter");
		return false;
	}

	$output .= "<div class=\"suckertreemenu$menu_id\">\n<ul id=\"treemenu$menu_id\">\n";

	foreach($params['menu_list'] as $_element) {
		$output .= tpl_function_menu_render_element($_element, 1);	
	}

	$output .= "</ul>\n</div>\n";

	return $output;
}

function tpl_function_menu_render_element($element,$level) {
	 
	 $_output = '';

	 if(isset($element['link']))
	 {
			$target = "";
			if(isset($element['target']))
			{
				$target = "target=\"" . htmlspecialchars($element['target']) . "\"";
			}
		  $_text = "<a href=\"" . htmlspecialchars($element['link']) . "\" $target>" . htmlspecialchars($element['text']) . "</a>";
	 }
	 else
	 {
		  $_text = '<span class="nolink">' . htmlspecialchars($element['text']). '</span>';
	 }
	 
	 if(isset($element['submenu'])) {
	 
		  $_class = isset($element['class']) ? $element['class'] : 'nav_parent';
		  
		  $_output .= str_repeat('	', $level) . "<li class=\"$_class\">" . $_text . "\n";
		  $_output .= str_repeat('	', $level) . "<ul>\n";

		  foreach($element['submenu'] as $_submenu) {
				$_output .=  tpl_function_menu_render_element($_submenu, $level + 1);
		  }

		  $_output .= str_repeat('	', $level) . "</ul>\n";
		  $_output .= str_repeat('	', $level) . "</li>\n";

	 } else {
		  $_class = isset($element['class']) ? $element['class'] : 'nav_child';
		  $_output .= str_repeat('	', $level) . "<li class=\"$_class\">" . $_text . "</li>\n";		  
	 }
	 
	 return $_output;
}

?>
