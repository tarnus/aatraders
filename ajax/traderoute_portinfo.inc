<?php
include ("languages/$langdir/lang_traderoute.inc");

get_post_ifset("sectorname");

$query = $db->SelectLimit("SELECT sector_id, port_type FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($sectorname), 1);
db_op_result($query,__LINE__,__FILE__);
if (!$query->EOF)
{
	$source=$query->fields;
	// ensure that they have been in the sector for the first port, but only if its a valid port type.
	$res1 = $db->SelectLimit("SELECT * from {$db_prefix}sector_log WHERE player_id = $playerinfo[player_id] AND (source = $source[sector_id] or destination = $source[sector_id])", 1);
	db_op_result($res1,__LINE__,__FILE__);
	if (!$res1->EOF)
	{
		echo $l_tdr_selling . ": " . ucwords($source['port_type']) . "\n<hr>";
		$debug_query = $db->Execute("SELECT * FROM {$db_prefix}universe_ports WHERE sector_id=$source[sector_id] ORDER BY data_id ASC");
		db_op_result($debug_query,__LINE__,__FILE__);
		$sourceport_commodity_count = 0;
		while(!$debug_query->EOF){
			if($sourceport_commodity_count > 0)
			{
				echo $l_tdr_buying . ": " . ucwords($debug_query->fields['commodity_type']) . "\n<br>";
			}
			$sourceport_commodity_count++;
			$debug_query->MoveNext();
		}
		$debug_query->close();
	}
	else
	{
		echo $l_tdr_explorefirst;
	}
}
else
{
	echo $l_tdr_invalidsector;
}
?> 
