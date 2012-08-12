<?php
if (!function_exists('new_preg_quote')) {

	function new_preg_quote($str, $delimiter)
	{
		$text = preg_quote($str);
		$text = str_replace($delimiter, '\\' . $delimiter, $text);
		return $text;
	}
}

if (!function_exists('add_smilies')) {

	function add_smilies($message)
	{
		global $db, $db_prefix;
		static $orig = array();
		static $repl = array();

		if(count($orig) == 0)
		{
			$result = $db->Execute("SELECT * FROM {$db_prefix}smilies");
			$smilies = $result->GetArray();

			for ($i = 0; $i < count($smilies); $i++)
			{
				$orig[] = "/(?<=.\W|\W.|^\W)" . new_preg_quote($smilies[$i]['code'], "/") . "(?=.\W|\W.|\W$)/";
				$repl[] = '<img src="images/smiles/' . $smilies[$i]['smile_image'] . '" alt="' . $smilies[$i]['emoticon'] . '" border="0" />';
			}
		}

		if (count($orig))
		{
			$message = preg_replace($orig, $repl, ' ' . $message . ' ');
			$message = AAT_substr($message, 1, -1);
		}
		return $message;
	}
}

?>
