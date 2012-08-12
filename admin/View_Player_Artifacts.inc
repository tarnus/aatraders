<?php
// 1: Player Artifact Totals
// This will display every player and how many artifacts they have found.

$res = $db->Execute("SELECT {$db_prefix}artifacts.artifact_type, count( {$db_prefix}artifacts.artifact_id ) AS total, {$db_prefix}players.character_name
					FROM {$db_prefix}artifacts, {$db_prefix}players 
					WHERE {$db_prefix}artifacts.player_id !=0 and {$db_prefix}artifacts.player_id = {$db_prefix}players.player_id
					GROUP BY {$db_prefix}artifacts.artifact_type, {$db_prefix}artifacts.player_id order by {$db_prefix}players.character_name, {$db_prefix}artifacts.artifact_type");
db_op_result($res,__LINE__,__FILE__);

if($res->RecordCount() == 0)
{
	$output = "<tr><td><div align=\"center\"><font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font></div><br>";
}
else
{
	$output = "<tr><td><div align=\"center\"><table cellspacing = \"0\" cellpadding = \"0\" border = \"0\"><tr><td><font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font></td></tr></table></div><br>\n";
	$output .= "<div align=\"center\"><table cellspacing = \"0\" cellpadding = \"2\" border = \"1\">\n";

	$oldname = "";
	while (!$res->EOF)
	{
		$msg = $res->fields;
		if($res->fields['character_name'] != $oldname && $oldname !="")
		{
			$output .= "</table></div><br><div align=\"center\"><table cellspacing = \"0\" cellpadding = \"2\" border = \"1\">\n";
			$output .= "<tr><td><b><div align=\"center\"><font color=\"white\">" . $res->fields['character_name'] . "</font></div></b></td><tr>\n";
		}
		if($oldname == "")
		{
			$output .= "<tr><td><b><div align=\"center\"><font color=\"white\">" . $res->fields['character_name'] . "</font></div></b></td><tr>\n";
		}
		$oldname = $res->fields['character_name'];
		if($res->fields['total'] == 1)
		{
			$pieces = "piece";
		}
		else
		{
   			$pieces = "pieces";
		}
		if(!class_exists($res->fields['artifact_type'])){
			include ("class/artifacts/" . $res->fields['artifact_type'] . ".inc");
		}
		$artifacts_object = new $res->fields['artifact_type']();
		if($res->fields['total'] >= $artifacts_object->pieces)
		{
			$completed = "<font color=\"yellow\">Completed</font>";
		}
		else
		{
			$completed = "<font color=\"yellow\">" . $res->fields['total'] . "</font> <font color=\"lime\">$pieces</font> - ";
			if(($artifacts_object->pieces - $res->fields['total']) == 1)
			{
				$pieces = "piece";
			}
			else
			{
   				$pieces = "pieces";
			}
			$completed .= "<font color=\"lime\">Needs</font> <font color=\"yellow\">" . ($artifacts_object->pieces - $res->fields['total']) . "</font> <font color=\"lime\">$pieces</font>";
		}

		$output .= "<tr><td><b><font color=\"#52ACEA\">" . $artifacts_object->classname . "</font> <font color=\"white\">(</font>$completed<font color=\"white\">)</font></b></td><tr>\n";
		$res->MoveNext();
	}
	$output .= "</table></div></td></tr>\n";
}

$res = $db->Execute("SELECT artifact_type, count( artifact_id ) AS total
					FROM {$db_prefix}artifacts
					WHERE player_id = 0 GROUP BY artifact_type order by artifact_type");
db_op_result($res,__LINE__,__FILE__);

$output2 = "<tr><td><div align=\"center\"><table cellspacing = \"0\" cellpadding = \"0\" border = \"0\"><tr><td><font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font></td></tr></table></div><br>\n";
$output2 .= "<div align=\"center\"><table cellspacing = \"0\" cellpadding = \"2\" border = \"1\">\n";

$total = 0;

while (!$res->EOF)
{
	$msg = $res->fields;
	if(!class_exists($res->fields['artifact_type'])){
		include ("class/artifacts/" . $res->fields['artifact_type'] . ".inc");
	}
	$artifacts_object = new $res->fields['artifact_type']();

	$total += $res->fields['total'];
	if($res->fields['total'] == 1)
	{
		$pieces = "piece";
	}
	else
	{
		$pieces = "pieces";
	}
	$completed = "<font color=\"yellow\">" . $res->fields['total'] . "</font> <font color=\"lime\">$pieces</font>";
	$output2 .= "<tr><td><b><font color=\"#52ACEA\">" . $artifacts_object->classname . "</font> unclaimed pieces <font color=\"white\">(</font>$completed<font color=\"white\">)</font></b></td><tr>\n";

	$res->MoveNext();
}

if($total == 1)
{
	$pieces = "piece";
}
else
{
	$pieces = "pieces";
}

$output2 .= "<tr><td><b><div align=\"center\"><font color=\"yellow\">" . $total . "</font> total <font color=\"lime\">$pieces</font> unclaimed.</b></td><tr>\n";
$output2 .= "</table></div></td></tr>\n";

echo $output2 . $output;
?>