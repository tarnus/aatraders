<?php
if (!function_exists('message_defense_owner')) {
	function message_defense_owner($sector, $messagevar, $languagefile, $defense_type, $inputtype, $inputdata)
	{
		global $db, $db_prefix;
		if ($defense_type==""){
			$defense_type="fighters";
		}
		$result3 = $db->Execute ("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sector' and  defense_type='$defense_type' ");
		db_op_result($result3,__LINE__,__FILE__);

		//Put the defense information into the array "defenseinfo"
		if ($result3 > 0)
		{
			while (!$result3->EOF)
			{
				$result2 = $db->SelectLimit("SELECT langdir FROM {$db_prefix}players WHERE player_id='" . $result3->fields['player_id'] . "'", 1);
				db_op_result($result2,__LINE__,__FILE__);

				include ("languages/" . $result2->fields['langdir'] . "/" . $languagefile);
				$message = $$messagevar;

				for($i = 0; $i < count($inputtype); $i++)
				{
					$message = str_replace($inputtype[$i], $inputdata[$i], $message);
				}

				playerlog($result3->fields['player_id'],"LOG0_RAW", $message);
				$result3->MoveNext();
			}
		}
		$result3->close();
	}
}
?>
