<?php
function AAT_strlen($string)
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		return mb_strlen($string);
	}
	else
	{
		return strlen($string);
	}
}

function AAT_strpos($haystack, $needle, $offset='')
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		if ($offset == '')
		{
			return mb_strpos($haystack, $needle);
		}
		else
		{
			return mb_strpos($haystack, $needle, $offset);
		}
	}
	else
	{
		if ($offset == '')
		{
			return strpos($haystack, $needle);
		}
		else
		{
			return strpos($haystack, $needle, $offset);
		}
	}
}

function AAT_strrpos($haystack, $needle, $offset='')
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		if ($offset == '')
		{
			return mb_strrpos($haystack, $needle);
		}
		else
		{
			return mb_strrpos($haystack, $needle, $offset);
		}
	}
	else
	{
		if ($offset == '')
		{
			return strrpos($haystack, $needle);
		}
		else
		{
			return strrpos($haystack, $needle, $offset);
		}
	}
}

function AAT_substr($string, $start, $length='')
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		if ($length == '')
		{
			return mb_substr($string, $start);
		}
		else
		{
			return mb_substr($string, $start, $length);
		}
	}
	else
	{
		if ($length == '')
		{
			return substr($string, $start);
		}
		else
		{
			return substr($string, $start, $length);
		}
	}
}

function AAT_strtolower($string)
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		return mb_strtolower($string);
	}
	else
	{
		return strtolower($string);
	}
}

function AAT_strtoupper($string)
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		return mb_strtoupper($string);
	}
	else
	{
		return strtoupper($string);
	}
}

function AAT_substr_count($haystack, $needle)
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		return mb_substr_count($haystack, $needle);
	} else {
		return substr_count($haystack, $needle);
	}
}

function AAT_ereg($pattern, $string, $regs='')
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		if ($regs == '')
		{
			return mb_ereg($pattern, $string);
		}
		else
		{
			return mb_ereg($pattern, $string, $regs);
		}
	}
	else
	{
		if ($length == '')
		{
			return ereg($pattern, $string);
		}
		else
		{
			return ereg($pattern, $string, $regs);
		}
	}
}

function AAT_eregi($pattern, $string, $regs='')
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		if ($regs == '')
		{
			return mb_eregi($pattern, $string);
		}
		else
		{
			return mb_eregi($pattern, $string, $regs);
		}
	}
	else
	{
		if ($length == '')
		{
			return eregi($pattern, $string);
		}
		else
		{
			return eregi($pattern, $string, $regs);
		}
	}
}

function AAT_ereg_replace($pattern, $replacement, $string)
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		return mb_ereg_replace($pattern, $replacement, $string);
	}
	else
	{
		return ereg_replace($pattern, $replacement, $string);
	}
}

function AAT_eregi_replace($pattern, $replacement, $string)
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		return mb_eregi_replace($pattern, $replacement, $string);
	}
	else
	{
		return eregi_replace($pattern, $replacement, $string);
	}
}

function AAT_split($pattern, $string, $limit='')
{
	global $mbstring_supported;
	if ($mbstring_supported) {
		if ($limit == '')
		{
			return mb_split($pattern, $string);
		}
		else
		{
			return mb_split($pattern, $string, $limit);
		}
	}
	else
	{
		if ($limit == '')
		{
			return explode($pattern, $string);
		}
		else
		{
			return explode($pattern, $string, $limit);
		}
	}
}
?>
