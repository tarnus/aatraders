<?php
// Step 999 - Download Config File

$data = rawurldecode($rawdata);
if (!empty($_SERVER['HTTP_USER_AGENT'])) 
{
	$HTTP_USER_AGENT = $_SERVER['HTTP_USER_AGENT'];
} 
else if (!empty($HTTP_SERVER_VARS['HTTP_USER_AGENT'])) 
{
	$HTTP_USER_AGENT = $HTTP_SERVER_VARS['HTTP_USER_AGENT'];
}
else if (!isset($HTTP_USER_AGENT))
{
	$HTTP_USER_AGENT = '';
}

if (AAT_ereg('Opera(/| )([0-9].[0-9]{1,2})', $HTTP_USER_AGENT)) 
{
	$browser_agent = 'opera';
} 
else if (AAT_ereg('MSIE ([0-9].[0-9]{1,2})', $HTTP_USER_AGENT)) 
{
	$browser_agent = 'ie';
} 
else if (AAT_ereg('OmniWeb/([0-9].[0-9]{1,2})', $HTTP_USER_AGENT)) 
{
	$browser_agent = 'omniweb';
} 
else if (AAT_ereg('Netscape([0-9]{1})', $HTTP_USER_AGENT)) 
{
	$browser_agent = 'netscape';
} 
else if (AAT_ereg('Mozilla/([0-9].[0-9]{1,2})', $HTTP_USER_AGENT)) 
{
	$browser_agent = 'mozilla';
} 
else if (AAT_ereg('Konqueror/([0-9].[0-9]{1,2})', $HTTP_USER_AGENT)) 
{
	$browser_agent = 'konqueror';
} 
else 
{
	$browser_agent = 'other';
}

// Correct the mime type - we force text/x-delimtext for the php file
// Please do not change this, it is a security precaution
$attachment = ($browser_agent == 'ie' || $browser_agent == 'opera') ? 'text/x-delimtext' : 'text/x-delimtext';

header('Pragma: public');
header('Content-Transfer-Encoding: none');

header('Content-Type: ' . $attachment . '; name="config_local' . $game_number . '.php"');
header('Content-Disposition: inline; filename="config_local' . $game_number . '.php"');

//
// Now send the File Contents to the Browser
//
$size = AAT_strlen($data);
header("Content-length: $size");
print "$data";
?>