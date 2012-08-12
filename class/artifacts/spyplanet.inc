<?php
class spyplanet
{
	var $class = "spyplanet";
	var $pieces = 7;
	var $min_cloak = 150; // Cloak value of each artifact piece
	var $max_cloak = 250; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 5; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function spyplanet()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>F&ouml;deratsioon ei luba palju v&auml;iksemate laevade r&uuml;ndamist. Su laeva eest pandi pearaha v&auml;lja.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
			break;

			case "french":
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>La Fйdйration n'a pas aprйcier que vous attaqiez ce vaissau. Elle a placйe une mise а prix sur vous.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
			break;

			case "german":
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>Die Fцderation akzeptiert Attacken auf schwдchere Spieler nicht. Sie hat eine Prдmie auf Sie ausgesetzt.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
			break;

			case "italian":
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>La Federazione non approva chi attacca giocatori molto inferiori quindi ha piazzato una taglia su di te.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
			break;

			case "russian":
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>федерация запрещает атаковать корабли намного меньше вашего. За вашу голову назначена награда.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
			break;

			case "spanish":
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>La Federaciуn no aprueba el atacar naves mucho mбs pequeсas. Ha fijado una recompensa sobre ti.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
			break;

			default:
				$this->classname = "Planetary Spy Artifact";
				$this->description = "This Artifact will place a spy on any enemy planet.  It will completely bypass the planets sensors. You must be in the same sector as the planet and all bounty restrictions will apply.  The Artifact will be able to see ANY planet in the sector no matter what cloak value it possesses.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select the planet to place the spy through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Place Spy on Planet</b></font>";
				$this->select = "Select a planet to place the spy";
				$this->l_bountyscan = "Bounty";
				$this->noplanet = "The selected planet cannot be found in this sector.";
				$this->l_fedbounty = "<font color='red' size='4'><b>The Federation does not approve of attacking much smaller players. It has placed a bounty on you.</b></font>";
				$this->placedspy = "A spy was successfully place on planet [planet].";
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
		global $db, $db_prefix, $playerinfo, $l_global_mmenu, $shipinfo, $templatename, $l_unowned, $l_ranks_evil, $l_ranks_good, $l_ranks_neutral;
		global $colonist_limit, $colonist_tech_add, $maximum_colonists, $max_tech_level, $l_unnamed;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

		include ("globals/good_neutral_evil.inc");
		include ("globals/planet_bounty_check.inc");

		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE sector_id='$shipinfo[sector_id]'", 5);
   		db_op_result($res,__LINE__,__FILE__);

		$output = "<table CELLSPACING=\"0\" CELLPADDING=\"2\" border=1 align=\"center\">
		<tr><td><div align=\"center\">" . $this->title . "</div></td></tr><tr><td align=\"center\"><table CELLSPACING=\"0\" CELLPADDING=\"2\" border=0 width=\"100%\" align=\"center\">
					<tr align=\"center\">";

		while (!$res->EOF)
		{
			$planets = $res->fields;

			$result5 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=". $planets['owner'] . "", 1);
			$planet_owner = $result5->fields;
			$result5->close();

			$planetavg = $planets['fighter'] + $planets['sensors'] + $planets['beams'] + $planets['torp_launchers'] + $planets['shields'] + $planets['cloak'];
			$maximum_colonists = $colonist_limit + floor($colonist_tech_add * floor($planetavg / 6));
			$planetavg += ($planets['colonists'] / $maximum_colonists) * $max_tech_level;
			$planetavg =  floor((($planetavg / 7) / $max_tech_level) * 10 );

			$planetlevel = max(0, min(9, $planetavg));
			$rating = good_neutral_evil($planet_owner['rating']);
			$planetrating = $rating[1];
			$planetratingnumber = $rating[0];

			if($planets['ore_planet'] >= 1 && $planets['organics_planet'] >= 1)
			{
				$planettype = "oo";
			}

			if($planets['ore_planet'] >= 1 && $planets['organics_planet'] < 1)
			{
				$planettype = "oo-";
			}

			if($planets['ore_planet'] < 1 && $planets['organics_planet'] >= 1)
			{
				$planettype = "o-o";
			}

			if($planets['ore_planet'] < 1 && $planets['organics_planet'] < 1)
			{
				$planettype = "o-o-";
			}

			$planetimg = $planettype . (string)($planetlevel + 1);
			if (empty($planets['name']))
			{
				$planetname = $l_unnamed;
			}
			else
			{
				$planetname = $planets['name'];
			}

			if ($planets['owner'] == 0)
			{
				$planetowner = "$l_unowned";
			}
			else
			{
				$planetowner = "$planet_owner[character_name]";
			}

			$output .= "	<td align=center valign=top>
	<a href=\"artifact_process.php?process_type=post&artifact=" . $this->class . "&planetid=" . $planets['planet_id'] . "\">
	<img src=\"templates/" . $templatename . "images/planet" . $planetimg . ".png\" alt=\"\" width=\"100\" height=\"100\"></a>
	<BR><font size=2 color=\"white\" face=\"arial\">
	$planetname
	<br>($planetowner)
				<br>";
			if ($planetratingnumber == -1)
			{
				$output .= "<font color=\"red\">$planetrating</font>";
			}
			elseif ($planetratingnumber == 0)
			{
				$output .= "<font color=\"yellow\">$planetrating</font>";
			}
			else
			{
				$output .= "<font color=\"lime\">$planetrating</font>";
			}
			$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $planet_owner, 0);
			if ($isfedbounty > 0)
			{
				$output .= "<br><font color=\"red\"><b>" . $this->l_bountyscan . "</b></font>";
			}
			$output .= "	</font></td>";
			$res->MoveNext();
		}

		$output .= "</tr><tr><td colspan=\"5\"><div align=\"center\">" . $this->select . "</div></td></tr></table></td></tr><tr><td align=\"center\"><br>$l_global_mmenu<br><br></td></tr>
		</table>";
		return $output;

	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $shipinfo, $l_global_mmenu;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

	  	$planetid = $_GET['planetid'];

		$res = $db->SelectLimit("SELECT * FROM {$db_prefix}planets WHERE planet_id='$planetid'", 5);
   		db_op_result($res,__LINE__,__FILE__);
		$planets = $res->fields;

		$result5 = $db->SelectLimit("SELECT * FROM {$db_prefix}players WHERE player_id=". $planets['owner'] . "", 1);
		$planet_owner = $result5->fields;
   		db_op_result($result5,__LINE__,__FILE__);
		$result5->close();

		if($shipinfo['sector_id'] == $planets['sector_id'])
		{
			include ("globals/planet_bounty_check.inc");

			$isfedbounty = planet_bounty_check($playerinfo, $shipinfo['sector_id'], $planet_owner, 1);

			if($isfedbounty > 0)
			{
				$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
				db_op_result($res,__LINE__,__FILE__);
				$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->l_fedbounty . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
				return $output;
			}

			$debug_query = $db->Execute("INSERT INTO {$db_prefix}spies 
			(spy_id, active, owner_id, planet_id, ship_id, job_id, spy_percent, move_type, spy_cloak) 
			values 
			('','Y',$playerinfo[player_id],'$planetid','0','0','0.0','none', $shipinfo[cloak])");
			db_op_result($debug_query,__LINE__,__FILE__);

			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);

			$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . str_replace("[planet]", $planets['name'], $this->placedspy) . "</b></font></div></td>
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
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->noplanet . "</b></font></div></td>
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