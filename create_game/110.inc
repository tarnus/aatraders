<?php
// Step 110 - Create all One and Two Way warp links

TextFlush("<br><b>Generating two way Federation warp links for sector 1 to $_POST[fedsecs]</b><br>\n");
$silent = 1;

$onewaylist = array();
$twowaylist = array();
$federationwaylist = array();
$federationstartlist = array();
// Put in the sector 1, 2, 3 and 4 warp loop.
$federationwaylist[1] = "1|2";
$federationwaylist[2] = "1|3";
$federationwaylist[3] = "1|4";
$federationwaylist[4] = "1|5";
$federationwaylist[5] = "2|1";
$federationwaylist[6] = "2|3";
$federationwaylist[7] = "2|4";
$federationwaylist[8] = "2|5";
$federationwaylist[9] = "3|1";
$federationwaylist[10] = "3|2";
$federationwaylist[11] = "3|4";
$federationwaylist[12] = "3|5";
$federationwaylist[13] = "4|1";
$federationwaylist[14] = "4|2";
$federationwaylist[15] = "4|3";
$federationwaylist[16] = "4|5";
$federationwaylist[17] = "5|1";
$federationwaylist[18] = "5|2";
$federationwaylist[19] = "5|3";
$federationwaylist[20] = "5|4";

$federationstartlist[1] = 1;
$federationstartlist[2] = 1;
$federationstartlist[3] = 1;
$federationstartlist[4] = 1;
$federationstartlist[5] = 2;
$federationstartlist[6] = 2;
$federationstartlist[7] = 2;
$federationstartlist[8] = 2;
$federationstartlist[9] = 3;
$federationstartlist[10] = 3;
$federationstartlist[11] = 3;
$federationstartlist[12] = 3;
$federationstartlist[13] = 4;
$federationstartlist[14] = 4;
$federationstartlist[15] = 4;
$federationstartlist[16] = 4;
$federationstartlist[17] = 5;
$federationstartlist[18] = 5;
$federationstartlist[19] = 5;
$federationstartlist[20] = 5;

$totalfederationways = 21;
for ($i=1; $i<=$_POST['fedsecs']; $i++)
{
	$numlinks = mt_rand(0,$_POST['linksper']);
	for ($j=0; $j<$numlinks; $j++)
	{
		$destination = mt_rand(1,$_POST['fedsecs']);
		$federationstartarraylist = array_count_values($federationstartlist);

		if($i != $destination && $federationstartarraylist[$federationstartlist[$i]] < ($_POST['linksper'] / 2))
		{
			$federationwaylist[$totalfederationways] = $i . "|" . $destination;
			$federationstartlist[$totalfederationways] = $i;
			$totalfederationways++;
			$federationwaylist[$totalfederationways] = $destination . "|" . $i;
			$totalfederationways++;
		}
	}
}

$newfederationways = array_unique($federationwaylist);
unset($federationwaylist);
unset($federationstartlist);

$valuelist = "";
$totalfederationways = 1;
$totalcount = count($newfederationways);
$start_end = ($totalcount < 999) ? $totalcount: 999;
TextFlush("<br>Exporting links 1 to $start_end to the database (" . $totalcount . " total).<br>\n");
foreach ($newfederationways as $v) { 
	if(!($totalfederationways % 1000)){
		if($totalfederationways + 999 > $totalcount)
			$end = $totalcount - $totalfederationways;
		else
			$end = 999;
		TextFlush("Exporting links $totaloneways to " . ($totalfederationways + $end) . " to the database (" . $totalcount . " total).<br>\n");
	}
	$links = explode("|", $v);

	if(!($totalfederationways % 100)){
		$valuelist .= "($links[0],$links[1]),";
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES " .  AAT_substr($valuelist, 0, -1) );
		$valuelist = "";
	}
	else
	{
		$valuelist .= "($links[0],$links[1]),";
	}
	$totalfederationways++;
}
unset($newfederationways);

if($valuelist != "")
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES " .  AAT_substr($valuelist, 0, -1) );

TextFlush("<br><b>Generating warp links for sector 1 to $_POST[sektors]</b><br>\n");

$silent = 1;
$result4 = $db->Execute("SELECT link_start FROM {$db_prefix}links order by link_id");
$total = $result4->RecordCount();

for($i = 1; $i <= $total; $i++)
{
	$federationstart[$i] = $result4->fields['link_start'];
	$result4->MoveNext();	
}
$result4->close();

$federationarraylist = array_count_values($federationstart);

$totaloneways = 0;
for ($i=1; $i<=$_POST['sektors']; $i++)
{
	$max_links_left = $_POST['linksper'] - $federationarraylist[$federationstart[$i]];

	$numlinks = mt_rand(0, $max_links_left);
	for ($j=0; $j<$numlinks; $j++)
	{
		$destination = mt_rand(1,$_POST['sektors']);
		if($i != $destination)
		{
			$onewaylist[$totaloneways] = $i . "|" . $destination;
			$totaloneways++;
		}
	}
}

$newoneways = array_unique($onewaylist);
unset($onewaylist);

$valuelist = "";
$totaloneways = 1;
$totalcount = count($newoneways);
$start_end = ($totalcount < 999) ? $totalcount: 999;
TextFlush("<br>Exporting links 1 to $start_end to the database (" . $totalcount . " total).<br>\n");
foreach ($newoneways as $v) { 
	if(!($totaloneways % 1000)){
		if($totaloneways + 999 > $totalcount)
			$end = $totalcount - $totaloneways;
		else
			$end = 999;
		TextFlush("Exporting links $totaloneways to " . ($totaloneways + $end) . " to the database (" . $totalcount . " total).<br>\n");
	}
	$links = explode("|", $v);

	if(!($totaloneways % 100)){
		$valuelist .= "($links[0],$links[1]),";
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES " .  AAT_substr($valuelist, 0, -1) );
		$valuelist = "";
	}
	else
	{
		$valuelist .= "($links[0],$links[1]),";
	}
	$totaloneways++;
}

if($valuelist != "")
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES " .  AAT_substr($valuelist, 0, -1) );

TextFlush("<br><b>Generating two way warp links from link 1 to $total links</b><br>\n");

$silent = 1;
$result4 = $db->Execute("SELECT link_start, link_dest FROM {$db_prefix}links order by link_id");
$total = $result4->RecordCount();

for($i = 1; $i <= $total; $i++)
{
	$onewaystart[$i] = $result4->fields['link_start'];
	$onewayend[$i] = $result4->fields['link_dest'];
	$checkvalue = $onewaystart[$i] . "a" . $onewayend[$i];
	$returncheck[$checkvalue] = 1;
	$result4->MoveNext();	
}
$result4->close();

$arraylist = array_count_values($onewaystart);
$totaltwoways = 0;

for ($i=1; $i<=$total; $i++)
{
	if (mt_rand(0,100) < $_POST['twoways'])
	{
		if($arraylist[$onewaystart[$i]] < $_POST['linksper'])
		{
			$checkvalue = $onewayend[$i] . "a" . $onewaystart[$i];
			if($returncheck[$checkvalue] != 1)
			{
				$twowaylist[$totaltwoways] = $onewayend[$i] . "|" . $onewaystart[$i];
				$totaltwoways++;
			}
		}
	}
}

$newtwoways = array_unique($twowaylist);
unset($twowaylist);

$valuelist = "";
$totaltwoways = 1;
$totalcount = count($newtwoways);
$start_end = ($totalcount < 999) ? $totalcount: 999;

TextFlush("<br>Exporting links 1 to $start_end to the database (" . $totalcount . " total).<br>\n");

foreach ($newtwoways as $v) { 
	if(!($totaltwoways % 1000)){
		if($totaltwoways + 999 > $totalcount)
			$end = $totalcount - $totaltwoways;
		else
			$end = 999;
		TextFlush("Exporting links $totaltwoways to " . ($totaltwoways + $end) . " to the database (" . $totalcount . " total).<br>\n");
	}
	$links = explode("|", $v);

	if(!($totaltwoways % 100)){
		$valuelist .= "($links[0],$links[1]),";
		$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES " .  AAT_substr($valuelist, 0, -1) );
		$valuelist = "";
	}
	else
	{
		$valuelist .= "($links[0],$links[1]),";
	}

	$totaltwoways++;
}

if($valuelist != "")
	$debug_query = $db->Execute("INSERT INTO {$db_prefix}links (link_start, link_dest) VALUES " .  AAT_substr($valuelist, 0, -1) );

$silent = 0;
db_op_result($debug_query,__LINE__,__FILE__);

echo "<input type=hidden name=step value=110>";

?>