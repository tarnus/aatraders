<?php
if (!function_exists('insert_news')) {
	function insert_news($data, $user_id, $news_type, $use_total = 1)
	{
		global $db, $db_prefix;
		$total = 1;

		$result2 = $db->SelectLimit("SELECT * from {$db_prefix}news order by news_id DESC", 1);
		$newsinfo = $result2->fields;
		$result2->close();
//print "$newsinfo[data] - $data<br>$newsinfo[news_type]<br>$newsinfo[user_id]<br>";
		if(($newsinfo['data'] == $data && $newsinfo['news_type'] == $news_type && $newsinfo['user_id'] == $user_id) && $use_total == 1){
			$total = $newsinfo['total'] + 1;
			$stamp = date("Y-m-d H:i:s");
			$debug_query = $db->Execute("UPDATE {$db_prefix}news set total='$total', date='$stamp' where news_id=$newsinfo[news_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			$stamp = date("Y-m-d H:i:s");
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}news (data, total, user_id, date, news_type) VALUES (" . $db->qstr($data) . ", '$total', '$user_id', '$stamp', '$news_type')");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}
}
?>
