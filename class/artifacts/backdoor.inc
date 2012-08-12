<?php
class backdoor
{
	var $class = "backdoor";
	var $pieces = 15;
	var $min_cloak = 300; // Cloak value of each artifact piece
	var $max_cloak = 375; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 2; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function backdoor()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
			break;

			case "french":
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
			break;

			case "german":
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
			break;

			case "italian":
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
			break;

			case "russian":
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
			break;

			case "spanish":
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
			break;

			default:
				$this->classname = "Backdoor from Hell Artifact";
				$this->description = "This Artifact will create a two-way warp link to any SG Sector if you know the name.  A two-way warp-link will be created even if the sector is at the limit it can normally support.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the SG Sector to create a two-way warp link through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->failurename = "Could not locate an SG Sector by this name: [sectorname]";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Two-Way Warp Link to SG Sector</b></font>";
				$this->sector = "Enter Sector Name for warplink destination:";
				$this->submit = "Create Warp Link";
				$this->completedlinks = "<font size=\"4\" color=\"lime\"><b>A Two-Way Warp Link Created to Sector [sectorname].</b></font>";
				$this->federation = "You cannot use this Artifact in a Federation Sector.";
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
		global $db, $db_prefix, $playerinfo, $l_global_mmenu;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

			$output ="
<form action=\"artifact_process.php?process_type=post&artifact=" . $this->class ."\" method=\"post\" enctype=\"multipart/form-data\">
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
		<tr BGCOLOR=\"#585980\">
			<td colspan=\"2\"><div align=\"center\"><b>" . $this->title . "</div></td>
		</tr>
		<tr BGCOLOR=\"#3A3B6E\">
			<TD>" . $this->sector . "</td>
			<TD><input type=\"text\" name=\"destination\" maxlength=\"30\" size=\"8\"></td>
		</tr>
 		<tr BGCOLOR=\"#23244F\">
			<td colspan=\"2\"><div align=\"center\"><input type=\"submit\" id=\"" . $this->submit . "\" value=\"" . $this->submit . "\" name=\"" . $this->submit . "\" ></div></td>
		</tr>
		<tr><td colspan=\"2\" align=\"center\"><br>$l_global_mmenu<br><br></td></tr>
	</table>
</div>
</form>";
		return $output;

	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $shipinfo, $sectorinfo, $l_global_mmenu;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

	  	$destination = $_POST['destination'];

		if($sectorinfo['zone_id'] == 2)
		{
			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->federation . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
			return $output;
		}

		$result  = $db->Execute("SELECT sector_id FROM {$db_prefix}universe WHERE sector_name=" . $db->qstr($destination) . " and sg_sector!=0");
		db_op_result($result,__LINE__,__FILE__);
		if($result->RecordCount() == 1)
		{
			$target_sector_id = $result->fields['sector_id'];
			$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links SET link_start=$shipinfo[sector_id], 
										link_dest=$target_sector_id");
			db_op_result($debug_query,__LINE__,__FILE__);
			$debug_query = $db->Execute ("INSERT INTO {$db_prefix}links SET link_start=$target_sector_id, 
										 link_dest=$shipinfo[sector_id]");
			db_op_result($debug_query,__LINE__,__FILE__);

			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);

			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . str_replace("[sectorname]", $destination, $this->completedlinks) . "</b></font></div></td>
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
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . str_replace("[sectorname]", $destination, $this->failurename) . "</b></font></div></td>
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