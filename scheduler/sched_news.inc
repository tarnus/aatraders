<?php
// 1
// 200
// 30
// 0
// Y
// How often population and planet news is generated.


// enable schedule - 0 disable schedule, 1 enable schedule
// execution order - the order of execution
// ticks full - how many minues between each execution
// loop_count - the number of times to execute schedule before deleting
// is_loop - "Y" loop enlessly, "N" - execute the number of times indocated by spawn value
// extra info - description of the schedule

include ("globals/get_player.inc");

function insert_scheduled_news($data, $user_id, $news_type)
{
	global $db, $db_prefix;

	$result2 = $db->SelectLimit("SELECT news_id from {$db_prefix}news WHERE user_id=$user_id and news_type='$news_type' order by news_id DESC", 1);

	$stamp = date("Y-m-d H:i:s");

	if($result2->recordcount() == 0)
	{
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}news (data, total, user_id, date, news_type) VALUES (" . $db->qstr($data) . ", '1', '$user_id', '$stamp', '$news_type')");
		db_op_result($debug_query,__LINE__,__FILE__);
	}
	$result2->close();
}

global $default_lang;
TextFlush ( "<b>POSTING NEWS</b><br>\n");

// generation of planet amount
$sql = $db->Execute("SELECT count(pl.owner) as planet_count, sum(pl.colonists) as colonist_count, pl.owner, plr.character_name from {$db_prefix}planets as pl, {$db_prefix}players as plr where pl.owner !='0' and plr.player_id=pl.owner and plr.planet_update='Y' group by pl.owner");
db_op_result($sql,__LINE__,__FILE__);

if($sql){
	while (!$sql->EOF)
	{
		$row = $sql->fields;
		if ($row['planet_count'] >= 60) 
		{
			if(($row['planet_count'] % 10) == 0)
			{
				insert_scheduled_news($row['character_name'] . "|" . $row['planet_count'], $row['owner'], "planetXX");
			}
		}
		elseif ($row['planet_count'] >= 50) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "planet50");
		}
		elseif ($row['planet_count'] >= 25) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "planet25");
		}
		elseif ($row['planet_count'] >= 10) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "planet10");
		}
		elseif ($row['planet_count'] >= 5) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "planet5");
		}

		if ($row['colonist_count'] >= 5000000000) 
		{
			if((floor($row['colonist_count'] / 100000000) % 50) == 0)
			{
				insert_scheduled_news($row['character_name'] . "|" . floor($row['colonist_count'] / 1000000), $row['owner'], "colXX");
			}
		}
		elseif ($row['colonist_count'] >= 1000000000) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "col1000");
		}
		elseif ($row['colonist_count'] >= 500000000) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "col500");
		}
		elseif ($row['colonist_count'] >= 100000000) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "col100");
		}
		elseif ($row['colonist_count'] >= 25000000) 
		{
			insert_scheduled_news($row['character_name'], $row['owner'], "col25");
		}
		$sql->MoveNext();
	} // while
	$sql->close();

	$debug_query = $db->Execute("UPDATE {$db_prefix}players SET planet_update='N' WHERE planet_update='Y'");
	db_op_result($debug_query,__LINE__,__FILE__);
}
// end generation of colonist amount

$multiplier = 0; //no use to run this more than once per tick
TextFlush ( "<br>\n");
?>
