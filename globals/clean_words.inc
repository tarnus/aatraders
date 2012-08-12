<?php
function clean_words($phrase)
{
	global $db, $db_prefix, $enable_wordcensor, $enable_wordcensor_metaphone;

	if($enable_wordcensor == 0)
		return $phrase;

	$newphrase = "";
	$phrase = AAT_eregi_replace(" +", " ", $phrase);
	$words = explode(" ", $phrase);

	for($i = 0; $i<count($words); $i++){
		$fixedword = AAT_eregi_replace("-+", "-", $words[$i]);
		$fixedword = AAT_eregi_replace("=+", "=", $fixedword);
		$fixedword = AAT_eregi_replace("\++", "+", $fixedword);
		$line = "'".addslashes(AAT_strtolower($fixedword)) . "', ";
		$fixedword = AAT_eregi_replace("-+", "", $words[$i]);
		$fixedword = AAT_eregi_replace("=+", "", $fixedword);
		$fixedword = AAT_eregi_replace("\++", "", $fixedword);
		$line .= "'".addslashes(AAT_strtolower($fixedword)) . "','";
		$newword = "";
		for($count = 0; $count < AAT_strlen($fixedword); $count += 2){
			$newword .= AAT_substr(AAT_strtolower($fixedword), $count, 1);
		}
		$line .= addslashes($newword) . "','";

		$newword = "";
		for($count = 1; $count < AAT_strlen($fixedword); $count += 2){
			$newword .= AAT_substr(AAT_strtolower($fixedword), $count, 1);
		}
		$line .= addslashes($newword) . "'";

		$result3 = $db->Execute ("SELECT * FROM {$db_prefix}wordcensor WHERE name IN ($line)");
		db_op_result($result3,__LINE__,__FILE__);
		if (!$result3->EOF)
		{
			$word = $result3->fields['value'];
		}else{
			$word = $words[$i];
			$wordnew = "";
			$res2 = $db->Execute ("SELECT * FROM {$db_prefix}wordcensor");
			db_op_result($res2,__LINE__,__FILE__);

			while(!$res2->EOF)
			{
				$name = $res2->fields['name'];
				$value = $res2->fields['value'];
				$wordnew = str_replace($name, $value, AAT_strtolower($fixedword));
				if($wordnew != AAT_strtolower($fixedword)){
					$word = $wordnew;
					break;
				}

				if (metaphone($fixedword) == metaphone($name) && $enable_wordcensor_metaphone) 
				{
					$word = $value;
					break;
				}
				$res2->MoveNext();
			}
			$res2->close();
		}
		$result3->close();

		$newphrase = $newphrase . $word . " ";
	}

	return ucfirst($newphrase);
}


?>
