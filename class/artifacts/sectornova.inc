<?php
class sectornova
{
	var $class = "sectornova";
	var $pieces = 10;
	var $min_cloak = 150; // Cloak value of each artifact piece
	var $max_cloak = 350; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 5; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function sectornova()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
			break;

			case "french":
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
			break;

			case "german":
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
			break;

			case "italian":
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
			break;

			case "russian":
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
			break;

			case "spanish":
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
			break;

			default:
				$this->classname = "Sector Nova Artifact";
				$this->description = "This Artifact will set off a Sector Nova in any Warp Linked Non-Federation sector the player has visited or scanned, this includes SG Sectors.  The Sector Nova will destroy massive numbers of Sector Defenses, damage all planets and ships in the sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the sector to attack through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->waiting = "<div align=\"center\">Sensors at Standby.<br><br>Waiting to scan selected sector.</div>";
				$this->fire = "Fire Sector Nova";
				$this->federation = "You cannot use the Sector Nova from a Federation Sector.";
				$this->pretitle = "Select the Sector to attack with the Sector Nova";
				$this->nolink = "A Warp Link to that sector does not exist.";
				$this->novisit = "You have not visited the target sector.";
				$this->nofedtarget = "You cannot target a Federation Sector.";
				$this->scanning = "<div align=\"center\">Scanning Sector</div>";
				$this->imtitle = "Sector Under Attack";
				$this->imbody = "[player] is using a Sector Nova on [sector]";
				$this->warning = "<font size=\"4\" color=\"red\"><b>WARNING: If you get a bounty on one planet when using this Artifact and there are more planets that haven't been hit yet, you will get a bounty for EACH planet.  If there are 5 planets in the sector and you get a bounty on the 3rd planet you will also get another bounty on the 4th planet and another bounty on the 5th planet for a total of 3 different bounties!</b></font";
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
		global $db, $db_prefix, $playerinfo, $shipinfo, $sectorinfo, $template_object, $gameurl, $gamepath, $l_global_mmenu ;

		$output ="";

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

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

		$target_sectorid = $shipinfo["sector_id"];

		$res = $db->Execute("SELECT {$db_prefix}universe.zone_id, {$db_prefix}universe.sector_name, {$db_prefix}universe.sector_id, {$db_prefix}links.link_dest FROM {$db_prefix}links, {$db_prefix}universe WHERE {$db_prefix}links.link_start='$target_sectorid' and {$db_prefix}universe.sector_id ={$db_prefix}links.link_dest ORDER BY {$db_prefix}universe.sector_name ASC");
		db_op_result($res,__LINE__,__FILE__);

		$resultlist = "";
		if ($res > 0)
		{
			while (!$res->EOF)
			{
				$res_return = $db->Execute("SELECT source FROM {$db_prefix}sector_log WHERE player_id=$playerinfo[player_id] and (source='" . $res->fields['sector_id'] . "' or destination='" . $res->fields['sector_id'] . "')");
				db_op_result($res_return,__LINE__,__FILE__);
				$visitedcount = $res_return->RecordCount();
				$res_return->close();
				if($res->fields['zone_id'] != 2)
				{
					if($visitedcount > 0)
					{
						$resultlist .= "<input onClick=\"makeRequest('" . $res->fields['sector_name'] . "');\" type=\"radio\" name=\"attacksector\" value=\"" . $res->fields['sector_name'] . "\"> " . $res->fields['sector_name'] . "<br>";
					}
					else
					{
						$resultlist .= $res->fields['sector_name'] . "<br>";
					}
				}
				else
				{
					$resultlist .= "F>" . $res->fields['sector_name'] . "<br>";
				}
				$res->MoveNext();
			}
		}
		$res->close();

		$output .= "<script type=\"text/javascript\">
<!--
var xmlDoc = null ;
var returndata = '' ;
var sectorname = '' ;

function makeRequest(sectorname)
{
	if (typeof window.ActiveXObject != 'undefined' ) {
		var XMLHTTP_IDS = new Array('MSXML2.XMLHTTP.5.0',
			 'MSXML2.XMLHTTP.4.0',
			 'MSXML2.XMLHTTP.3.0',
			 'MSXML2.XMLHTTP',
			 'Microsoft.XMLHTTP');
		var success = false;
		for (var i=0;i < XMLHTTP_IDS.length && !success; i++)
		{
			try
			{
				xmlDoc = new ActiveXObject
				(XMLHTTP_IDS[i]);
				success = true;
			}
			catch (e)
			{}
		}
	}
	else
	{
		xmlDoc = new XMLHttpRequest();
	}
	document.getElementById('output').innerHTML = '" . $this->scanning . "';

	xmlDoc.onreadystatechange = process;
	xmlDoc.open( \"GET\", \"http://" . $gameurl . $gamepath . ($gamepath == "/" ? "" : "/") . "sector_scan.php?ajax=1&command=scan&sector=\" + sectorname, true );
	xmlDoc.send( null );
}

function process() {
	if ( xmlDoc.readyState != 4 )
	{
		return ;
	}
	returndata = xmlDoc.responseText
//	document.write(returndata)

	document.getElementById('output').innerHTML = returndata;
}

//-->
</script>

<form action=\"artifact_process.php?process_type=post&artifact=" . $artifact_type ."\" method=\"post\" enctype=\"multipart/form-data\">
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td colspan=\"2\"><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->pretitle . "</b></font></div></td>
        </tr>
		<tr>
			<td align=\"center\">
				<font color=\"white\">" . $resultlist ."</font><br>
				<input type=\"submit\" id=\"" . $this->fire . "\" value=\"" . $this->fire . "\" name=\"" . $this->fire . "\" >
			</td>
			<td  id=\"output\">" . $this->waiting ."
			</td>
		</tr>
		<tr>
			<td colspan=\"2\"><div align=\"center\">" . $this->warning . "</div></td>
		</tr>
        <tr>
          <td colspan=\"2\"><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>
</form>";

		return $output;
	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $l_unnamed, $shipinfo, $sectorinfo, $playerinfo, $l_global_mmenu, $langdir;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

		$res = $db->Execute("SELECT * FROM {$db_prefix}universe WHERE sector_name =" . $db->qstr($_POST['attacksector']));
		db_op_result($res,__LINE__,__FILE__);
		$sector = $res->fields['sector_id'];
		$zones['zone_id'] = $res->fields['zone_id'];
	  	$query96 = $res->fields;
		if($res->fields['zone_id'] == 2)
		{
			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->nofedtarget . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
			return $output;
		}

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

		$result = $db->Execute("SELECT * FROM {$db_prefix}links WHERE link_start='$shipinfo[sector_id]' AND link_dest=" . $db->qstr($sector));
		if($result->RecordCount() == 0)
		{
			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->nolink . "</b></font></div></td>
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
			$res_return = $db->Execute("SELECT source FROM {$db_prefix}sector_log WHERE player_id=$playerinfo[player_id] and (source='" . $sector . "' or destination='" . $sector . "')");
			db_op_result($res_return,__LINE__,__FILE__);
			$visitedcount = $res_return->RecordCount();
			$res_return->close();
			if($visitedcount == 0)
			{
				$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->novisit . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
				return $output;
			}
		}

		include("languages/$langdir/lang_novabomb.inc");
		include("languages/$langdir/lang_combat.inc");
	  	include ("globals/set_max_credits.inc");
	  	include ("globals/send_system_im.inc");
	  	include ("globals/planet_bounty_check.inc");

		$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
		db_op_result($res,__LINE__,__FILE__);

	  	$output = "<TABLE BORDER=1 CELLSPACING=0 CELLPADDING=5 align=\"center\" bgcolor=\"#000000\">
		<tr><td><TABLE BORDER=0 CELLSPACING=0 CELLPADDING=5 align=\"center\" bgcolor=\"#000000\">";
	  	$output .= "<TR BGCOLOR=\"#23244F\"><TD><B><font color='#ff0000' size='4'>" . str_replace("[sector]", $query96['sector_name'], $l_novabomb_success) . "</font></B></TD></TR>";
	  	$output .= "<TR><TD>";

	  	$res = $db->Execute("SELECT * FROM {$db_prefix}sector_defense WHERE sector_id='$sector'");
	  	$qtyfighters = 0;
	  	$qtymines = 0;
	  	$i = 0;
	  	if ($res > 0)
	  	{
	  		while (!$res->EOF)
	  		{
	  			$defences = $res->fields;
	  			$defense_id = $defences['defense_id'];
	  			if ($defences['defense_type'] == 'fighters')
	  			{
	  				$fightersleft = floor($defences['quantity'] * (rand(35, 100) * 0.01));
	  				$qtyfighters += $defences['quantity'] - $fightersleft;
	  				$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense SET quantity=$fightersleft WHERE " .
	  											"defense_id = $defense_id");
	  				db_op_result($debug_query,__LINE__,__FILE__);
	  			}
		  		if ($defences['defense_type'] == 'mines')
	  			{
	  				$minesleft = floor($defences['quantity'] * (rand(35, 100) * 0.01));
	  				$qtymines += $defences['quantity'] - $minesleft;
	  				$debug_query = $db->Execute("UPDATE {$db_prefix}sector_defense SET quantity=$minesleft WHERE " .
	  											"defense_id = $defense_id");
	  				db_op_result($debug_query,__LINE__,__FILE__);
	  			}
	  			$i++;
	  			$res->MoveNext();
	  		}
	  	}

	  	$l_novabomb_fighters = str_replace("[fighters]", "<font color=white><b>" . NUMBER($qtyfighters) . "</b></font>", $l_novabomb_fighters);
	  	$l_novabomb_mines = str_replace("[mines]", "<font color=white><b>" . NUMBER($qtymines) . "</b></font>", $l_novabomb_mines);

	  	if($qtyfighters)
	  	{
	  		$output .= "<TR BGCOLOR=\"#3A3B6E\"><TD><B>$l_novabomb_fighters</B></TD></TR>";
	  	}

	  	if($qtymines)
	  	{
	  		$output .= "<TR BGCOLOR=\"#23244F\"><TD><B>$l_novabomb_mines</B></TD></TR>";
	  	}

	  	$result4 = $db->Execute("SELECT * FROM {$db_prefix}planets WHERE sector_id=$sector");
	  	$sectorplanets = $result4->RecordCount();

	  	$dev_nova_warpdamage = 70;

	  	if ($sectorplanets > 0)
	  	{
	  		$output .= "<TR BGCOLOR=\"#3A3B6E\"><TD>&nbsp;</TD></TR>";
	  		$output .= "<TR BGCOLOR=\"#585980\"><TD><B>$l_novabomb_planetsdamaged</b></TD></TR>";
	  		while (!$result4->EOF)
	  		{
	  			$sectorplanet = $result4->fields;
	  			if ($sectorplanet['owner'] != 0)
	  			{
		  			$result5 = $db->Execute("SELECT * FROM {$db_prefix}players WHERE player_id=". $sectorplanet['owner'] . "");
	  				$planet_owner = $result5->fields;
		  			send_system_im($sectorplanet['owner'], $this->imtitle, str_replace("[player]", $playerinfo['character_name'], str_replace("[sector]", $query96['sector_name'], $this->imbody)), $planet_owner['last_login']);

		  			$isfedbounty = planet_bounty_check($playerinfo, $sectorplanet['sector_id'], $planet_owner, 1, 0.1);

		  			if($isfedbounty > 0)
		  			{
			  			$output .= $l_by_fedbounty2 . "<BR><BR>";
		  			}
		  		}
	  			$afteractionplanettech['fighter'] = floor($sectorplanet['fighter'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['sensors'] = floor($sectorplanet['sensors'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['beams'] = floor($sectorplanet['beams'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['torp_launchers'] = floor($sectorplanet['torp_launchers'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['shields'] = floor($sectorplanet['shields'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['jammer'] = floor($sectorplanet['jammer'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['cloak'] = floor($sectorplanet['cloak'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['armor'] = floor($sectorplanet['armor'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['torps'] = floor($sectorplanet['torps'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['fighters'] = floor($sectorplanet['fighters'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['colonists'] = floor($sectorplanet['colonists'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['special_amount'] = $sectorplanet['special_amount'] * (rand($dev_nova_warpdamage, 100) * 0.01);
			  	$afteractionplanettech['organics'] = floor($sectorplanet['organics'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['ore'] = floor($sectorplanet['ore'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['goods'] = floor($sectorplanet['goods'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['credits'] = floor($sectorplanet['credits'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['energy'] = floor($sectorplanet['energy'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['sector_defense_weapons'] = floor($sectorplanet['sector_defense_weapons'] * (rand($dev_nova_warpdamage, 100) * 0.01));
			  	$afteractionplanettech['sector_defense_cloak'] = floor($sectorplanet['sector_defense_cloak'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionplanettech['sector_defense_sensors'] = floor($sectorplanet['sector_defense_sensors'] * (rand($dev_nova_warpdamage, 100) * 0.01));

				$build_log_entry = $l_cmb_planet_tech_drop;
				$build_log_entry=str_replace("[sector_defense_weapons]","<font color=\"#00ff00\">". $sectorplanet['sector_defense_weapons'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sector_defense_weapons_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_weapons'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sector_defense_sensors]","<font color=\"#00ff00\">". $sectorplanet['sector_defense_sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sector_defense_sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sector_defense_cloak]","<font color=\"#00ff00\">". $sectorplanet['sector_defense_cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sector_defense_cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['sector_defense_cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $sectorplanet['fighter'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionplanettech['fighter'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $sectorplanet['sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionplanettech['sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $sectorplanet['beams'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionplanettech['beams'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $sectorplanet['torp_launchers'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionplanettech['torp_launchers'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $sectorplanet['shields'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionplanettech['shields'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $sectorplanet['cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionplanettech['cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[jammer]","<font color=\"#00ff00\">". $sectorplanet['jammer'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[jammer_new]","<font color=\"#ff0000\">". $afteractionplanettech['jammer'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $sectorplanet['armor'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionplanettech['armor'] . "</font>",$build_log_entry);
				playerlog($sectorplanet['owner'], "LOG5_AFTER_ACTION", $build_log_entry);

	  			if($sectorplanet['name'] == "")
	  			{
			  		$sectorplanet['name'] = $l_unnamed;
			  	}

			  	$output .= "<TR BGCOLOR='#23244F'><TD><B>" . str_replace("[name]", $sectorplanet['name'], $l_novabomb_planet) . "</B></TD></TR>";
	  			$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET 
			  	armor=$afteractionplanettech[armor], special_amount=$afteractionplanettech[special_amount], organics=$afteractionplanettech[organics], 
	  			ore=$afteractionplanettech[ore], goods=$afteractionplanettech[goods], 
			  	sector_defense_weapons=$afteractionplanettech[sector_defense_weapons], sector_defense_cloak=$afteractionplanettech[sector_defense_cloak], sector_defense_sensors=$afteractionplanettech[sector_defense_sensors], 
	  			torps=$afteractionplanettech[torps], fighters=$afteractionplanettech[fighters], colonists=$afteractionplanettech[colonists], 
	  			credits=$afteractionplanettech[credits], energy=$afteractionplanettech[energy], fighter=$afteractionplanettech[fighter], 
	  			sensors=$afteractionplanettech[sensors], beams=$afteractionplanettech[beams], torp_launchers=$afteractionplanettech[torp_launchers], 
	  			shields=$sectorplanet[shields], jammer=$afteractionplanettech[jammer], cloak=$afteractionplanettech[cloak] 
	  			WHERE planet_id=$sectorplanet[planet_id]");
		  		db_op_result($debug_query,__LINE__,__FILE__);
		  		set_max_credits($sectorplanet['planet_id']);

	  			$result4->MoveNext();
		  	}
	  	}

	  	$result4 = $db->Execute("SELECT * FROM {$db_prefix}ships LEFT JOIN {$db_prefix}players ON {$db_prefix}players.player_id = {$db_prefix}ships.player_id " .
	  							"WHERE {$db_prefix}players.currentship={$db_prefix}ships.ship_id and sector_id='$sector' AND on_planet='N'");
	  	$sectorships = $result4->RecordCount();

	  	if ($sectorships > 0)
	  	{
	   		$output .= "<TR BGCOLOR=\"#3A3B6E\"><TD>&nbsp;</TD></TR>";
		  	$output .= "<TR BGCOLOR=\"#585980\"><TD><B>$l_novabomb_shipsdamaged</b></TD></TR>";
	  		while (!$result4->EOF)
	  		{
	  			$sectorship = $result4->fields;
	  			$afteractionshiptech['hull'] = floor($sectorship['hull'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['engines'] = floor($sectorship['engines'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['power'] = floor($sectorship['power'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['fighter'] = floor($sectorship['fighter'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['sensors'] = floor($sectorship['sensors'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['beams'] = floor($sectorship['beams'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionshiptech['torp_launchers'] = floor($sectorship['torp_launchers'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['shields'] = floor($sectorship['shields'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionshiptech['cloak'] = floor($sectorship['cloak'] * (rand($dev_nova_warpdamage, 100) * 0.01));
	  			$afteractionshiptech['armor'] = floor($sectorship['armor'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['armor_pts'] = floor($sectorship['armor_pts'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['torps'] = floor($sectorship['torps'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['fighters'] = floor($sectorship['fighters'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['credits'] = floor($sectorship['credits'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['energy'] = floor($sectorship['energy'] * (rand($dev_nova_warpdamage, 100) * 0.01));
		  		$afteractionshiptech['ecm'] = floor($sectorship['ecm'] * (rand($dev_nova_warpdamage, 100) * 0.01));

				$build_log_entry = $l_cmb_attacker_tech_drop;
				$build_log_entry=str_replace("[hull]","<font color=\"#00ff00\">". $sectorship['hull'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[hull_new]","<font color=\"#ff0000\">". $afteractionshiptech['hull'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[engines]","<font color=\"#00ff00\">". $sectorship['engines'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[engines_new]","<font color=\"#ff0000\">". $afteractionshiptech['engines'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[power]","<font color=\"#00ff00\">". $sectorship['power'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[power_new]","<font color=\"#ff0000\">". $afteractionshiptech['power'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[fighter]","<font color=\"#00ff00\">". $sectorship['fighter'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[fighter_new]","<font color=\"#ff0000\">". $afteractionshiptech['fighter'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sensors]","<font color=\"#00ff00\">". $sectorship['sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[sensors_new]","<font color=\"#ff0000\">". $afteractionshiptech['sensors'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[beams]","<font color=\"#00ff00\">". $sectorship['beams'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[beams_new]","<font color=\"#ff0000\">". $afteractionshiptech['beams'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[torps]","<font color=\"#00ff00\">". $sectorship['torp_launchers'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[torps_new]","<font color=\"#ff0000\">". $afteractionshiptech['torp_launchers'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[shields]","<font color=\"#00ff00\">". $sectorship['shields'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[shields_new]","<font color=\"#ff0000\">". $afteractionshiptech['shields'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[cloak]","<font color=\"#00ff00\">". $sectorship['cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[cloak_new]","<font color=\"#ff0000\">". $afteractionshiptech['cloak'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[ecm]","<font color=\"#00ff00\">". $sectorship['ecm'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[ecm_new]","<font color=\"#ff0000\">". $afteractionshiptech['ecm'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[armor]","<font color=\"#00ff00\">". $sectorship['armor'] . "</font>",$build_log_entry);
				$build_log_entry=str_replace("[armor_new]","<font color=\"#ff0000\">". $afteractionshiptech['armor'] . "</font>",$build_log_entry);
				playerlog($sectorship['player_id'], "LOG5_AFTER_ACTION", $build_log_entry);

	  			$output .= "<TR BGCOLOR='#23244F'><TD><B>" . str_replace("[shipname]", $sectorship['name'], $l_novabomb_ship_damage) . "</B></TD></TR>";
	  			$debug_query = $db->Execute("UPDATE {$db_prefix}ships SET hull=$afteractionshiptech[hull], engines=$afteractionshiptech[engines], power=$afteractionshiptech[power], 
	  			fighter=$afteractionshiptech[fighter], sensors=$afteractionshiptech[sensors], beams=$afteractionshiptech[beams], torp_launchers=$afteractionshiptech[torp_launchers], 
		  		shields=$afteractionshiptech[shields], cloak=$afteractionshiptech[cloak], armor=$afteractionshiptech[armor], armor_pts=$afteractionshiptech[armor_pts], 
		  		torps=$afteractionshiptech[torps], fighters=$afteractionshiptech[fighters], energy=$afteractionshiptech[energy], ecm=$afteractionshiptech[ecm] WHERE ship_id=$sectorship[ship_id]");
	  			db_op_result($debug_query,__LINE__,__FILE__);

	  			$result4->MoveNext();
	  		}
	  	}
	  	$output .= "</table></td></tr>
	  	<tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
</table>";
	  	return $output;
	}
}

?>