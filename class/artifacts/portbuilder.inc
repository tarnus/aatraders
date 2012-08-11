<?php
class portbuilder
{
	var $class = "portbuilder";
	var $pieces = 10;
	var $min_cloak = 225; // Cloak value of each artifact piece
	var $max_cloak = 350; // Maximum Cloak value of each artifact piece
	var $scoremax = 0; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 5; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.

	function portbuilder()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
			break;

			case "french":
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
			break;

			case "german":
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
			break;

			case "italian":
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
			break;

			case "russian":
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
			break;

			case "spanish":
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
			break;

			default:
				$this->classname = "Port Builder Artifact";
				$this->description = "This Artifact will build a port of your choice in any sector.  This Artifact can be used to replace the port in any sector.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can create the port through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Build Port</b></font>";
				$this->select = "Select the Port Type to build:";
				$this->submit = "Build Port";
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
		global $db, $db_prefix, $playerinfo, $l_global_mmenu;

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

		$output = "<table CELLSPACING=\"0\" CELLPADDING=\"4\" border=1 align=\"center\" bgcolor=\"#000000\">
		<tr><td><div align=\"center\">" . $this->title . "</div></td></tr><tr><td align=\"center\"><table CELLSPACING=\"0\" CELLPADDING=\"2\" border=0 width=\"100%\" align=\"center\">
					<tr><td><div align=\"center\"><b>" . $this->select . "</b></div></td></tr><tr><td>";

		$output .= "<form action=\"artifact_process.php?process_type=post&artifact=" . $this->class . "\" method=\"post\" enctype=\"multipart/form-data\">\n";

		$output .= "<input type=\"radio\" name=\"port_type\" value=\"upgrades\" checked>&nbsp;&nbsp;&nbsp;Upgrades<br>";
		$output .= "<input type=\"radio\" name=\"port_type\" value=\"devices\">&nbsp;&nbsp;&nbsp;Devices<br>";
		$output .= "<input type=\"radio\" name=\"port_type\" value=\"spacedock\">&nbsp;&nbsp;&nbsp;Spacedock<br>";

		$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where cargoport=1 order by classname ASC");
		db_op_result($cargo_query,__LINE__,__FILE__);

		while (!$cargo_query->EOF) 
		{
			if ($cargo_query->fields['cargosellbuy'] != 1)
			{
				$output .= "<input type=\"radio\" name=\"port_type\" value=\"" . $cargo_query->fields['classname'] . "\">&nbsp;&nbsp;&nbsp;" . ucwords($cargo_query->fields['classname']) . "<br>";
			}
			$cargo_query->Movenext();
		}

		$output .= "<br><br>\n
		  <div align=\"center\"><input type=\"submit\" id=\"" . $this->submit . "\" value=\"" . $this->submit . "\" name=\"" . $this->submit . "\" ></div>\n</FORM>";

		$output .= "</form></td></tr></table>
</td></tr>
<tr><td align=\"center\"><br>$l_global_mmenu<br><br></td></tr>
		</table>";
		return $output;

	}

	function postprocess_artifact($artifact_type)
	{
		global $db, $db_prefix, $playerinfo, $shipinfo, $l_global_mmenu, $max_port_buy_commodities;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

	  	$port_type = $_POST['port_type'];

		if ($port_type == "upgrades" || $port_type == "devices" || $port_type == "spacedock")
		{
			$debug_query = $db->Execute ("UPDATE {$db_prefix}universe SET port_type=" . $db->qstr($port_type) . " WHERE sector_id=$shipinfo[sector_id]");
			db_op_result($debug_query,__LINE__,__FILE__);
			$res = $db->Execute("DELETE FROM {$db_prefix}universe_ports WHERE sector_id=$shipinfo[sector_id]");
			db_op_result($res,__LINE__,__FILE__);
			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);

			$output ="<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			return $output;
		}

		$cargototal = 0;

		$cargo_query = $db->Execute("SELECT * from {$db_prefix}class_modules_commodities where cargoport=1 order by classname ASC");
		db_op_result($cargo_query,__LINE__,__FILE__);

		$default_create_ratio = 100 / $cargo_query->fields['default_create_percent'];
		$default_create_ratio_new = 1;

		while (!$cargo_query->EOF) 
		{
			if($port_type == $cargo_query->fields['classname'])
			{
				$a_fixed_start_price = $cargo_query->fields['fixed_start_price'];
				$a_increaserate = $cargo_info['increaserate'];
				$a_limitamount = $cargo_query->fields['itemlimit'];
				$a_goodevil = $cargo_query->fields['goodevil'];
				$random_port = $cargototal;
			}
			$newcargotype[$cargototal] = $cargo_query->fields['classname'];
			$limitamount[$cargototal] = $cargo_query->fields['itemlimit'];
			$initialamount[$cargototal] = $cargo_query->fields['itemlimit'] * $_POST['initscommod'] / 100.0;
			$fixed_start_price[$cargototal] = $cargo_query->fields['fixed_start_price'];
			$increaserate[$cargototal] = $cargo_info['increaserate'];
			$goodevil[$cargototal] = $cargo_query->fields['goodevil'];
			$cargosellbuy[$cargototal] = $cargo_info['cargosellbuy'];
			$default_create_percent[$cargototal] = $cargo_info['default_create_percent'] * $default_create_ratio;
			if($cargo_info['defaultcargoplanet'] == 0 && $default_create_ratio_new == 1)
			{
				$default_create_ratio_new = 200 / $cargo_info['default_create_percent'];
			}
			$default_create_percent_new[$cargototal] = $cargo_info['default_create_percent'] * $default_create_ratio_new;
			$hold_space[$cargototal] = $cargo_info['hold_space'];
			$cargototal++;
			$cargo_query->Movenext();
		}

		$debug_query = $db->Execute ("UPDATE {$db_prefix}universe SET port_type=" . $db->qstr($port_type) . " WHERE sector_id=$shipinfo[sector_id]");
		db_op_result($debug_query,__LINE__,__FILE__);
		$res = $db->Execute("DELETE FROM {$db_prefix}universe_ports WHERE sector_id=$shipinfo[sector_id]");
		db_op_result($res,__LINE__,__FILE__);

		$randompoint = mt_rand(500000, 1000000) / 1000000;
		$prices = floor($a_fixed_start_price * $randompoint);
		if($a_increaserate == 0)
		{
			$prices = $a_fixed_start_price;
		}

		$maxcommodities = $max_port_buy_commodities;
		$insertlist = "";
		for($ii = 0; $ii < $cargototal; $ii++)
		{
			if($maxcommodities > 0)
			{
				if($ii != $random_port && mt_rand(1, 100) < 50 && $cargosellbuy[$ii] != 2)
				{
					$randompoint = mt_rand(500000, 1000000) / 1000000;
					$buyprices = floor($fixed_start_price[$ii] * $randompoint) * 3;
					$buyprices += $fixed_start_price[$ii] * $ratio;
					if($increaserate[$ii] == 0)
					{
						$buyprices = $fixed_start_price[$ii] / 2;
					}
					$insertlist .= ", ($shipinfo[sector_id], '" . $newcargotype[$ii] . "', $limitamount[$ii], " . $buyprices . ", '" . date("Y-m-d H:i:s") . "', $goodevil[$ii])";
					$maxcommodities--;
				}
			}
		}

		$debug_query = $db->Execute("INSERT INTO {$db_prefix}universe_ports 
			(sector_id, commodity_type, commodity_amount, commodity_price, trade_date, goodevil) 
			VALUES 
			($shipinfo[sector_id], '" . $port_type . "', $a_limitamount, $prices, '" . date("Y-m-d H:i:s") . "', $a_goodevil) 
			$insertlist");
		db_op_result($debug_query,__LINE__,__FILE__);

		$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
		db_op_result($res,__LINE__,__FILE__);

		$output ="<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
		return $output;
	}
}

?>