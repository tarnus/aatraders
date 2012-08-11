<?php
class maxcloak
{
	var $class = "maxcloak";
	var $pieces = 10;
	var $min_cloak = 200; // Cloak value of each artifact piece
	var $max_cloak = 250; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 3; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.
	var $cloak_limit = 400;  // The max allowed value to upgrade cloak

	function maxcloak()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;

			case "french":
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;

			case "german":
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;

			case "italian":
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;

			case "russian":
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;

			case "spanish":
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;

			default:
				$this->classname = "Max Cloak Artifact";
				$this->description = "This Artifact will add a Max Cloak Device any single ship.  This device will increase the ships Cloaking Tech to the maximum allowed for that ship class to a maximum of 400.  If your cloak is damaged the difference will be deducted from the Max Cloak value.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the ship to upgrade through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Install Device";
				$this->noship = "You do not own that ship.";
				$this->newcloak = "The selected ship now has a Max Cloak Device.";
			break;
		}
	}

	function sched_process_artifact($artifact_type)
	{
		global $db, $db_prefix, $adminexecuted;

		include ("globals/artifacts_sched.inc");

		if($adminexecuted == 1)
		{
			TextFlush ( "<b>" . ucwords($artifact_type) . " Artifact Added</b><br>");
		}

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);

 		$totalpieces = ($this->pieces * $this->maximum_in_galaxy) - $res->fields['total'];
		for ($i = 1; $i <= $totalpieces; $i++)
		{
			artifacts_sched($artifact_type, $this->min_cloak, $this->max_cloak, $this->scoremax, $i);
		}
	}

	function found_artifact_piece($artifact_id)
	{
		global $db, $db_prefix, $playerinfo;

		include ("globals/insert_news.inc");

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
			$updateit = $db->Execute("UPDATE {$db_prefix}artifacts SET on_port=0, on_planet_id=0, sector_id=0, player_id = $playerinfo[player_id] WHERE artifact_id=$artifact_id");
    		db_op_result($updateit,__LINE__,__FILE__);
    		$res->fields['total']++;
    	}

   		if($res->fields['total'] == $this->pieces)
   		{
 			insert_news($this->classname . "|" . $playerinfo['character_name'], 1, "artifact");

   			return $this->success;
   		}
   		else
   		{
   			$incomplete = str_replace("[pieces]", $res->fields['total'], $this->incomplete);
   			$left = $this->pieces - $res->fields['total'];
   			$incomplete = str_replace("[left]", $left, $incomplete);
  			if($left == 1)
   			{
   				$incomplete = str_replace("[piece]", $this->singular, $incomplete);
   				$pieces = $this->singular;
  			}
   			else
   			{
   				$incomplete = str_replace("[piece]", $this->plural, $incomplete);
    			$pieces = $this->plural;
   			}
			insert_news($this->classname . "|" . $playerinfo['character_name'] . "|$left|$pieces", 1, "artifactfound");
   			return $incomplete;
   		}
	}

	function preprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $max_tech_level, $langdir;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

		include("languages/$langdir/lang_common.inc");
		include("languages/$langdir/lang_report.inc");

		for($iz=0; $iz <= 900; $iz++){
			if($iz < floor($max_tech_level/4))
				$colorarray[$iz] = "#FFADAD";
			if($iz >= floor($max_tech_level/4) and $iz < (floor($max_tech_level/4) * 2))
				$colorarray[$iz] = "#FFFF00";
			if($iz >= (floor($max_tech_level/4) * 2) and $iz < (floor($max_tech_level/4) * 3))
				$colorarray[$iz] = "#0CD616";
			if($iz >= (floor($max_tech_level/4) * 3))
				$colorarray[$iz] = "#ffffff";
		}

		$result  = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE player_id=$playerinfo[player_id] order by class ASC");
		db_op_result($result,__LINE__,__FILE__);

		$shipcount = 0;
		while (!$result->EOF) {
			$member = $result->fields;

			$debug_query = $db->SelectLimit("SELECT * FROM {$db_prefix}ship_types WHERE type_id=$member[class]", 1);
			db_op_result($debug_query,__LINE__,__FILE__);
			$classstuff = $debug_query->fields;
			$ship_id[$shipcount] = $member['ship_id'];
			$hull[$shipcount] = $member['hull'];
			$engines[$shipcount] = $member['engines'];
			$power[$shipcount] = $member['power'];
			$fighter[$shipcount] = $member['fighter'];
			$sensors[$shipcount] = $member['sensors'];
			$armor[$shipcount] = $member['armor'];
			$shields[$shipcount] = $member['shields'];
			$beams[$shipcount] = $member['beams'];
			$torps[$shipcount] = $member['torp_launchers'];
			$cloak[$shipcount] = $member['cloak'];
			$ecm[$shipcount] = $member['ecm'];
			$shipname[$shipcount] = $member['name'];
			$shipclassname[$shipcount] = $classstuff['name'];
			$maxcloak[$shipcount] = ($classstuff['maxcloak'] <= $this->cloak_limit) ? $classstuff['maxcloak'] : $this->cloak_limit;
			$memberclass[$shipcount] = $member['class'];
			$colorhull[$shipcount] = $colorarray[$member['hull']];
			$colorengines[$shipcount] = $colorarray[$member['engines']];
			$colorpower[$shipcount] = $colorarray[$member['power']];
			$colorfighter[$shipcount] = $colorarray[$member['fighter']];
			$colorsensors[$shipcount] = $colorarray[$member['sensors']];
			$colorarmor[$shipcount] = $colorarray[$member['armor']];
			$colorshields[$shipcount] = $colorarray[$member['shields']];
			$colorbeams[$shipcount] = $colorarray[$member['beams']];
			$colortorps[$shipcount] = $colorarray[$member['torp_launchers']];
			$colorcloak[$shipcount] = $colorarray[$member['cloak']];
			$colorecm[$shipcount] = $colorarray[$member['ecm']];
			$shipcount++;
			$result->MoveNext();
		}

		$output = "<table width=\"90%\" border=\"1\" cellspacing=\"0\" cellpadding=\"4\" align=\"center\">
  <tr>
    <td bgcolor=\"#000000\" valign=\"top\" align=\"center\" colspan=2>
		<table cellspacing = \"0\" cellpadding = \"0\" border = \"0\" width=\"100%\">
<tr><td>
	<div align=center>
	<h3><font color=\"white\"><B>$team_name</B>
	<br><font size=2><i>" . $this->description . "</i></font></H3>
	</div> 
	<table border=1 cellspacing=0 cellpadding=0 width=\"100%\" align=center>
	<tr bgcolor=\"#585980\">
	<td align=\"center\"><font color=\"white\"><B>$l_ships</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_hull</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_engines</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_power</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_fighter</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_sensors</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_armor</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_shields</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_beams</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_torp_launch</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_cloak</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>$l_ecm</b></font></td>
	<td align=\"center\"><font color=\"white\"><B>" . $this->upgrade . "</b></font></td>

	</tr><tr bgcolor=#000000>";

	for($i = 0; $i < $shipcount; $i++){
		$output .= "<td align=\"center\" valign=\"middle\">";

		$output .= "<font face=\"verdana\" size=\"1\" color=\"#9ff4f8\"><b>SS $shipname[$i]</b></font><br>
		<font face=\"verdana\" size=\"1\" color=\"#FFD161\"><b>$shipclassname[$i]</b></font>
		<font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b> - </b></font>
		<font face=\"verdana\" size=\"1\" color=\"#ffffff\"><b>$memberclass[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorhull[$i]\"><b>$hull[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorengines[$i]\"><b>$engines[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorpower[$i]\"><b>$power[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorfighter[$i]\"><b>$fighter[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorsensors[$i]\"><b>$sensors[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorarmor[$i]\"><b>$armor[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorshields[$i]\"><b>$shields[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorbeams[$i]\"><b>$beams[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colortorps[$i]\"><b>$torps[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorcloak[$i]\"><b>$cloak[$i]</b></font></td>
		<td align=\"center\"><font color=\"$colorecm[$i]\"><b>$ecm[$i]</b></font></td>
		<td align=\"center\"><b><a href=\"artifact_process.php?process_type=post&artifact=$artifact_type&ship_id=$ship_id[$i]\">" . $this->upgrade . " (" . $maxcloak[$i] . ")</a></b></td>";
		$output .= "</tr><tr bgcolor=#000000>";
	}

	$output .= "</tr></table>

</td></tr>
<tr><td align=\"center\"><br>$l_global_mmenu<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>";
		return $output;

	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $l_global_mmenu;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

	  	$ship_id = $_GET['ship_id'];

		$result  = $db->Execute("SELECT * FROM {$db_prefix}ships WHERE player_id=$playerinfo[player_id] and ship_id=$ship_id");
		db_op_result($result,__LINE__,__FILE__);
		if($result->RecordCount() == 1)
		{
			$result  = $db->Execute("UPDATE {$db_prefix}ship_devices SET amount=1 WHERE player_id=$playerinfo[player_id] and ship_id=$ship_id and class='dev_maxcloak'");
			db_op_result($result,__LINE__,__FILE__);

			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);

			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->newcloak . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
			return $output;
		}
		else
		{
			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->noship . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
			return $output;
		}
	}
}

?>