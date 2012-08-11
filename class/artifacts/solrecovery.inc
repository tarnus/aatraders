<?php
class solrecovery
{
	var $class = "solrecovery";
	var $pieces = 1;
	var $min_cloak = 0; // Cloak value of each artifact piece
	var $max_cloak = 0; // Maximum Cloak value of each artifact piece
	var $scoremax = 100000; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 40; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function solrecovery()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
			break;

			case "french":
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
			break;

			case "german":
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
			break;

			case "italian":
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
			break;

			case "russian":
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
			break;

			case "spanish":
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
			break;

			default:
				$this->classname = "Sol Recovery Artifact";
				$this->description = "This Artifact will create a Wormhole from any sector (realspace or SG) to Sol and transport you there instantly.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the Wormhole through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->upgrade = "Upgrade Cloak";
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
		global $db, $db_prefix, $playerinfo, $shipinfo;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

		$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET sector_id=1 WHERE ship_id=$shipinfo[ship_id]");
		db_op_result($debug_query,__LINE__,__FILE__);

		$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
		db_op_result($res,__LINE__,__FILE__);

		$output ="<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
		return $output;

	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $l_global_mmenu;

	}
}

?>