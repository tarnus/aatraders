<?php
/**
 * template_lite array_reverse modifier plugin
 *
 * Type:	 modifier
 * Name:	 array_reverse
 * @param boolean preserve the array keys
 * Purpose:  Reverse the order of an array
 */
function tpl_modifier_array_reverse($array, $preserve_keys = false)
{
	return array_reverse($array, $preserve_keys);
}
?>