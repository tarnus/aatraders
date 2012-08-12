<?php
if (!function_exists('log_scan')) {
	function log_scan($player_id,$sector_id,$zone_id)
	{
		global $db, $db_prefix, $l_none;

		$res = $db->Execute("SELECT sector_name FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$sector_id' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");
		db_op_result($res,__LINE__,__FILE__);

		$links = "";
		if ($res > 0)
		{
			$count = 0;
			$total = $res->recordcount();
			while (!$res->EOF)
			{
				$links .= $res->fields['sector_name'];
				if($count < $total)
					$links .= "|";
				$count++;
				$res->MoveNext();
			}
		}
		$res->close();

		// Check if the player has already scanned that sector - no need to double the db record
		$debug_query = $db->Execute("SELECT event_id, port_buys FROM {$db_prefix}sector_log WHERE player_id = '$player_id' and source = '$sector_id' and destination=0");
		db_op_result($debug_query,__LINE__,__FILE__);

		$stamp = date("Y-m-d H:i:s");
		if ($debug_query->EOF)
		{
			$res = $db->Execute("SELECT commodity_type FROM {$db_prefix}universe_ports WHERE sector_id='$sector_id' ORDER BY data_id ASC");
			db_op_result($res,__LINE__,__FILE__);

			$port_buys = "";
			if ($res > 0)
			{
				$count = 1;
				$total = $res->recordcount();
				while (!$res->EOF)
				{
					if($count > 1)
					{
						$port_buys .= ucwords($res->fields['commodity_type']);
						if($count < $total)
							$port_buys .= "|";
					}
					$count++;
					$res->MoveNext();
				}
			}
			$res->close();
			if($port_buys == "")
			{
				$port_buys = $l_none;
			}

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}sector_log (player_id, source, zone_id, time, warp_links, port_buys) VALUES ($player_id, $sector_id, $zone_id, '$stamp', " . $db->qstr($links) . ", " . $db->qstr($port_buys) . ")");
			db_op_result($debug_query,__LINE__,__FILE__);
		}else{
			$event_id = $debug_query->fields['event_id'];

			if($debug_query->fields['port_buys'] == '')
			{
				$res = $db->Execute("SELECT commodity_type FROM {$db_prefix}universe_ports WHERE sector_id='$source' ORDER BY data_id ASC");
				db_op_result($res,__LINE__,__FILE__);

				$port_buys = "";
				if ($res > 0)
				{
					$count = 1;
					$total = $res->recordcount();
					while (!$res->EOF)
					{
						if($count > 1)
						{
							$port_buys .= ucwords($res->fields['commodity_type']);
							if($count < $total)
								$port_buys .= "|";
						}
						$count++;
						$res->MoveNext();
					}
				}
				$res->close();
				if($port_buys == "")
				{
					$port_buys = $l_none;
				}
			}
			else
			{
				$port_buys = $debug_query->fields['port_buys'];
			}

			$debug_query->close();
			$debug_query = $db->Execute("UPDATE {$db_prefix}sector_log SET zone_id=$zone_id, time='$stamp', warp_links=" . $db->qstr($links) . ", port_buys=" . $db->qstr($port_buys) . " WHERE event_id=$event_id");
			db_op_result($debug_query,__LINE__,__FILE__);
		}
	}
}
?>
