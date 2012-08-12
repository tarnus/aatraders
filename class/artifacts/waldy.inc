<?php
class waldy
{
	var $class = "waldy";
	var $pieces = 3;
	var $min_cloak = 175; // Cloak value of each artifact piece
	var $max_cloak = 250; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 0; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 15; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function waldy()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
			break;

			case "french":
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
			break;

			case "german":
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
			break;

			case "italian":
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
			break;

			case "russian":
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
			break;

			case "spanish":
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
			break;

			default:
				$this->classname = "Where's Waldy Artifact";
				$this->description = "This Artifact will instantly display a list of every Ship Captain with an Artifact.  The list will show what Artifacts each Captain is carrying and how many of each.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->noonehasany = "<font color=\"red\" size=\"3\"><b>None of the Ship Captains are carrying any artifacts.</b></font>";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Captains With Artifacts</b></font>";
				$this->completed = "Completed";
				$this->needs = "Needs";
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
		global $db, $db_prefix, $playerinfo, $start_armor, $start_energy, $start_fighters;

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
			$res = $db->Execute("SELECT {$db_prefix}artifacts.artifact_type, count( {$db_prefix}artifacts.artifact_id ) AS total, {$db_prefix}players.character_name
								FROM {$db_prefix}artifacts, {$db_prefix}players 
								WHERE {$db_prefix}artifacts.player_id !=0 and {$db_prefix}artifacts.player_id = {$db_prefix}players.player_id
								GROUP BY {$db_prefix}artifacts.artifact_type, {$db_prefix}artifacts.player_id order by {$db_prefix}players.character_name, {$db_prefix}artifacts.artifact_type");
			db_op_result($res,__LINE__,__FILE__);

	   		if($res->RecordCount() == 0)
   			{
   				return $this->noonehasany;
   			}
   			else
   			{
  				$output = "<div align=\"center\"><table cellspacing = \"0\" cellpadding = \"0\" border = \"0\"><tr><td>" . $this->title . "</td></tr></table></div><br>\n";
   				$output .= "<table cellspacing = \"0\" cellpadding = \"2\" border = \"1\">\n";

				$oldname = "";
				while (!$res->EOF)
				{
					$msg = $res->fields;
					if($res->fields['character_name'] != $oldname)
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
   						$pieces = $this->singular;
   					}
		   			else
   					{
 		    			$pieces = $this->plural;
  					}
					if(!class_exists($res->fields['artifact_type'])){
						include ("class/artifacts/" . $res->fields['artifact_type'] . ".inc");
					}
					$artifacts_object = new $res->fields['artifact_type']();
					if($res->fields['total'] >= $artifacts_object->pieces)
					{
						$completed = "<font color=\"yellow\">" . $this->completed . "</font>";
					}
					else
					{
						$completed = "<font color=\"yellow\">" . $res->fields['total'] . "</font> <font color=\"lime\">$pieces</font> - ";
						if(($artifacts_object->pieces - $res->fields['total']) == 1)
						{
							$pieces =  $this->singular;
						}
						else
						{
			   				$pieces = $this->plural;
						}
						$completed .= "<font color=\"lime\">" . $this->needs . "</font> <font color=\"yellow\">" . ($artifacts_object->pieces - $res->fields['total']) . "</font> <font color=\"lime\">$pieces</font>";
					}
					$output .= "<tr><td><b><font color=\"#52ACEA\">" . $artifacts_object->classname . "</font> <font color=\"white\">(</font>$completed<font color=\"white\">)</font></b></td><tr>\n";
					$res->MoveNext();
				}
				$output .= "</table>\n";
   			}

			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);
			insert_news($this->classname . "|" . $playerinfo['character_name'], 1, "artifact");
   			return $output;
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
		global $db, $db_prefix, $playerinfo;
	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo;
	}
}

?>