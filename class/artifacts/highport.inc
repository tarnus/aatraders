<?php
class highport
{
	var $class = "highport";
	var $pieces = 5;
	var $min_cloak = 0; // Cloak value of each artifact piece
	var $max_cloak = 200; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 0; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 10; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function highport()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
			break;

			case "french":
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
			break;

			case "german":
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
			break;

			case "italian":
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
			break;

			case "russian":
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
			break;

			case "spanish":
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
			break;

			default:
				$this->classname = "High Port Artifact";
				$this->description = "This Artifact will find the Port with the highest buying selected commodity in realspace as soon as the artifact is completed.  The Captain will select the Commodity Port they would like to find the highest buy price in Realspace.  The Sector Name with the current Commodity Buy Price will be displayed.  There are a total of " . $this->pieces . " pieces that need to be found.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->l_commodity = "Commodity Bought";
				$this->l_amount = "Amount";
				$this->l_price = "Buy Price";
				$this->l_sector = "Sector";
				$this->title = "<font color=\"lime\" size=\"3\"><b>Select the Commodity to find the Highest Buying Port</b></font>";
				$this->submit = "Find Highest Price Port";
				$this->commodity = "Select Commodity: ";
				$this->useorlose = "You must use this artifact NOW.  If you close the screen or use the back button you will lose the artifact.";
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

			$output ="
<form action=\"artifact_process.php?process_type=post&artifact=" . $this->class ."\" method=\"post\" enctype=\"multipart/form-data\">
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
		<tr BGCOLOR=\"#585980\">
			<td colspan=\"2\"><div align=\"center\">" . $this->title . "</div></td>
		</tr>
		<tr BGCOLOR=\"#3A3B6E\">
			<TD>" . $this->commodity . "</td>
			<TD><select size=\"20\" name=\"port_type\">";

			$cargo_query = $db->Execute("SELECT classname from {$db_prefix}class_modules_commodities order by classname ASC");
			db_op_result($cargo_query,__LINE__,__FILE__);
			while (!$cargo_query->EOF)
			{
				$row = $cargo_query->fields;
				$output .= "				<option value=\"$row[classname]\">" . ucwords($row['classname']) . "</option>\n";
				$cargo_query->MoveNext();
			}

			$output .= "</select></td>
		</tr>
		<tr BGCOLOR=\"#000000\">
			<td colspan=\"2\"><div align=\"center\"><font color=\"pink\"><b>" . $this->useorlose . "</b></font></div></td>
		</tr>
 		<tr BGCOLOR=\"#23244F\">
			<td colspan=\"2\"><div align=\"center\"><input type=\"submit\" id=\"" . $this->submit . "\" value=\"" . $this->submit . "\" name=\"" . $this->submit . "\" ></div></td>
		</tr>
	</table>
</div>
</form>";
			if($_SESSION['artifact'] == 0)
			{
				$_SESSION['artifact'] = strtotime(date("Y-m-d H:i:s"));
			}
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
		global $db, $db_prefix, $playerinfo, $inventory_factor, $l_global_mmenu;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces || $_SESSION['artifact'] == 0)
   		{
   			return;
	  	}

		$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
		db_op_result($res,__LINE__,__FILE__);

		$res = $db->SelectLimit("SELECT {$db_prefix}universe.sector_name, {$db_prefix}universe_ports.commodity_type, {$db_prefix}universe_ports.commodity_price, {$db_prefix}universe_ports.commodity_amount
								FROM {$db_prefix}universe , {$db_prefix}universe_ports 
								WHERE {$db_prefix}universe_ports.commodity_type = " . $db->qstr(rawurldecode($_POST['port_type'])) . "
								AND {$db_prefix}universe_ports.sector_id = {$db_prefix}universe.sector_id
								AND {$db_prefix}universe.port_type != {$db_prefix}universe_ports.commodity_type
								AND {$db_prefix}universe.sg_sector = 0
								ORDER BY {$db_prefix}universe_ports.commodity_price DESC", 1);
		db_op_result($res,__LINE__,__FILE__);

		$commodity_query = $db->Execute("SELECT price, delta, itemlimit FROM {$db_prefix}class_modules_commodities WHERE classname=" . $db->qstr(rawurldecode($_POST['port_type'])));
		db_op_result($commodity_query,__LINE__,__FILE__);

		$offered_buy_price = max($res->fields['commodity_price'] + $commodity_query->fields['price'] + $commodity_query->fields['delta'] * $commodity_query->fields['itemlimit'] / $commodity_query->fields['itemlimit'] * $inventory_factor, 0.01);

		$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" bgcolor=\"#000000\">
		<tr BGCOLOR=\"#585980\">
			<td><b>" . $this->l_sector . "</b></td>
			<td><B>" . $this->l_commodity . "</B></td>
			<td><B>" . $this->l_amount . "</B></td>
			<td><B>" . $this->l_price . "</B></td>
		</tr>
		<tr BGCOLOR=\"#3A3B6E\">
			<td><a href=\"main.php?move_method=real&engage=1&destination=" . rawurldecode($res->fields['sector_name']) . "\">" . $res->fields['sector_name'] . "</a></td>
			<TD>" . ucwords($res->fields['commodity_type']) . "</td>
			<TD>" . NUMBER($res->fields['commodity_amount']) . "</td>
			<TD>" . NUMBER(floor($offered_buy_price)) . "</td>
		</tr>
        <tr>
          <td colspan=\"4\"><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
		return $output;
	}
}

?>