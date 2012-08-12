<?php
/**
 * template_lite string_format modifier plugin
 *
 * Type:	 modifier
 * Name:	 string_format
 * Purpose:  Wrapper for the PHP 'vsprintf' function
 */
function tpl_modifier_string_format($string, $format)
{
	return sprintf($format, $string);
}
?>