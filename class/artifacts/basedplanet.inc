<?php
class basedplanet
{
	var $class = "basedplanet";
	var $pieces = 3;
	var $min_cloak = 0; // Cloak value of each artifact piece
	var $max_cloak = 150; // Maximum Cloak value of each artifact piece
	var $scoremax = 400000; // Any player with a score over this value will not be able to see the artifact. Set to 0 for everyone to see.
	var $schedinfo;
	var $delayedprocess = 1; // If the completed artifact can be processed at a different time after completion.  Player can execute the artifact from the Artifact List selection.  Set to 1 for delayed processing.
	var $maximum_in_galaxy = 5; // The maximum number of artifacts of this class in the galaxy.  Multiply this number by $pieces to get the total number of pieces in the galaxy.
	var $limitpercentage = 70; // The percentage of the maximum colonists allowed on a newly based planet to place on this planet.

	function basedplanet()
	{
		global $langdir;
		switch ($langdir)
		{
			case "estonian":
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "Selles sektoris ei ole lubatud mateeriatorpeedot kasutada.";
				$this->l_gns_bforbid = "Selle sektori baasid ei lase Sul mateeriatorpeedot kasutada.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
			break;

			case "french":
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "La création d'une planète dans ce secteur n'est pas permise.";
				$this->l_gns_bforbid = "Les bases dans se secteur interferent avec la torpille genesis. La création d'une planète est impossible.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
			break;

			case "german":
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "Das Erstellen eines Planeten in diesem Sektor ist nicht gestattet.";
				$this->l_gns_bforbid = "Die Basen in diesem Sektor stören sich mit Ihrem Genesis device. Der Planet konnte nicht erstellt werden.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
			break;

			case "italian":
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "Non è permesso creare pianeti in questo settore.";
				$this->l_gns_bforbid = "Le basi di questo settore interferiscono con il tuo dispositivo Genesis. La creazione di pianeti non è possibile.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
			break;

			case "russian":
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "Ïîðîæäåíèå íîâûõ ïëàíåò â ýòîì ñåêòîð çàïðåùåíî.";
				$this->l_gns_bforbid = "Áàçû â ýòîì ñåêòîðå ïðåïÿòñòâóþò ñîçäàíèþ ïëàíåòû.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
			break;

			case "spanish":
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "Crear un planeta en este sector no está permitido.";
				$this->l_gns_bforbid = "Las bases en este sector interfieren con tu dispositivo Génesis. No es posible la creación de planetas.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
			break;

			default:
				$this->classname = "Based Planet Artifact";
				$this->description = "This Artifact will create a Based Planet with " . $this->limitpercentage . "% of the maximum colonists in any Realspace or SG Sector that isn't owned by someone else and has room for the planet.  Once your score reaches " . NUMBER($this->scoremax) . " you will not be able to see or pickup this artifact.  If you are carrying one you will lose it.  There are a total of " . $this->pieces . " pieces that need to be found.  Once all pieces are found you can select when to build the planet through the Artifact List command.  The Artifact pieces will be stored on your ship.  If your ship is destroyed the attacker may find some of the pieces.  Any pieces not captured by the attacker will be randomly distributed around the galaxy.";
				$this->success = "You have found all " . $this->pieces . " pieces of the " . $this->classname . ".  You can use this artifact at any time from the Artifact List page.";
				$this->incomplete = "You have found [pieces] pieces of the " . $this->classname . ".  You need [left] more [piece] to complete the artifact.";
				$this->singular = "piece";
				$this->plural = "pieces";
				$this->toomanyplanets = "There are too many planets in this sector.";
				$this->l_gns_forbid = "Creating a planet in this sector is not permitted.";
				$this->l_gns_bforbid = "The bases in this sector are interfering with your genesis device. Planet creation not possible.";
				$this->title = "<font size=\"4\" color=\"lime\"><b>Create Based Planet Artifact</b></font>";
				$this->question = "Do you wish to create a planet in this sector?";
				$this->submit = "Answer Question";
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
		global $db, $db_prefix, $playerinfo, $l_yes, $l_no, $l_global_mmenu;

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
			<TD>" . $this->question . "</td>
			<TD><input type=\"radio\" name=\"doit\" value=\"yes\" checked> $l_yes
			<input type=\"radio\" name=\"doit\" value=\"no\"> $l_no</td>
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
		global $db, $db_prefix, $playerinfo, $sectorinfo, $shipinfo, $l_global_mmenu, $persuasion_countdown_max;
		global $colonist_limit, $planet_prod_low_percent, $planet_prod_high_percent, $planet_production_skew;
		global $base_credits, $default_prod_fighters, $default_prod_torp;

		$res = $db->Execute("SELECT count(artifact_id) total FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
   		db_op_result($res,__LINE__,__FILE__);
   		if($res->fields['total'] < $this->pieces)
   		{
   			return;
	  	}

		if($_POST['doit'] == "yes")
		{
			include ("globals/myrand.inc");

			$persuasion_countdown = mt_rand(floor($persuasion_countdown_max / 3), $persuasion_countdown_max * 2);
			$old_owner_rating = 2;
			$colonistlimit = floor($colonist_limit * ($this->limitpercentage / 100));

			$res = $db->SelectLimit("SELECT {$db_prefix}universe.zone_id, {$db_prefix}zones.allow_planet, {$db_prefix}zones.team_zone, " .
									"{$db_prefix}zones.owner FROM {$db_prefix}zones,{$db_prefix}universe WHERE " .
									"{$db_prefix}zones.zone_id=$sectorinfo[zone_id] AND {$db_prefix}universe.sector_id = $shipinfo[sector_id]", 1);
			$query97 = $res->fields;

			$result3 = $db->Execute("SELECT COUNT(planet_id) AS total FROM {$db_prefix}planets WHERE sector_id='$shipinfo[sector_id]'");
			$num_planets = $result3->fields['total'];
			$result3->close();

			if ($num_planets >= $sectorinfo['star_size'])
			{
				$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->toomanyplanets . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
				return $output;
			}

			if ($query97['allow_planet'] == 'N')
			{
				$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->l_gns_forbid . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
				return $output;
			}
			elseif ($query97['allow_planet'] == 'L')
			{
				if ($query97['team_zone'] == 'N')
				{
					if ($playerinfo['team'] == 0 && $playerinfo['player_id'] != $query97['owner'])
					{
						$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->l_gns_bforbid . "</b></font></div></td>
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
						$res = $db->SelectLimit("SELECT team FROM {$db_prefix}players WHERE player_id=$query97[owner]", 1);
						$ownerinfo = $res->fields;
						if ($ownerinfo['team'] != $playerinfo['team'] && $playerinfo['player_id'] != $query97['owner'])
						{
							$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->l_gns_bforbid . "</b></font></div></td>
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
				elseif ($playerinfo['team'] != $query97['owner'])
				{
					$output ="
<div align=\"center\">
	<table border=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" bgcolor=\"#000000\">
        <tr>
          <td><div align=\"center\"><font size=\"2\" color=\"lime\"><b>" . $this->l_gns_bforbid . "</b></font></div></td>
        </tr>
        <tr>
          <td><div align=\"center\">$l_global_mmenu</div></td>
        </tr>
	</table>
</div>";
					return $output;
				}
			}

			$stamp = date("Y-m-d H:i:s");
			$defaultcargototal = 0;
			$extracargototal = 0;

			$cargo_query = $db->SelectLimit("SELECT * from {$db_prefix}class_modules_commodities where defaultcargoplanet!=1 and cargoplanet=1 order by default_create_percent DESC", 1);
			db_op_result($cargo_query,__LINE__,__FILE__);

			$p_create_ratio = 100 / $cargo_query->fields['default_create_percent'];

			$cargo_query = $db->Execute("SELECT default_create_percent, classname, cargoclass, default_prod, default_indy_prod, goodevil, defaultcargoplanet, cargoplanet from {$db_prefix}class_modules_commodities where defaultcargoplanet=1 or cargoplanet=1");
			db_op_result($cargo_query,__LINE__,__FILE__);
			while (!$cargo_query->EOF) 
			{
				$cargo_info = $cargo_query->fields;
				if($cargo_info['defaultcargoplanet'] == 1)
				{
					$dnewcargotype[$defaultcargototal] = $cargo_info['classname'];
					$dcargoclass[$defaultcargototal] = $cargo_info['cargoclass'];
					$ddefault_prod[$defaultcargototal] = $cargo_info['default_prod'];
					$ddefault_indy_prod[$defaultcargototal] = $cargo_info['default_indy_prod'];
					$dis_prod[$defaultcargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
					$dgoodevil[$defaultcargototal] = $cargo_info['goodevil'];
					$defaultcargototal++;
				}
				else
				{
					if($cargo_info['cargoplanet'] == 1)
					{
						$newcargotype[$extracargototal] = $cargo_info['classname'];
						$cargoclass[$extracargototal] = $cargo_info['cargoclass'];
						$default_prod[$extracargototal] = $cargo_info['default_prod'];
						$default_indy_prod[$extracargototal] = $cargo_info['default_indy_prod'];
						$is_prod[$extracargototal] = ($cargo_info['cargoclass'] == "commodity") ? 1 : 0;
						$goodevil[$extracargototal] = $cargo_info['goodevil'];
						$p_create_percent[$extracargototal] = $cargo_info['default_create_percent'] * $p_create_ratio;
						$extracargototal++;
					}
				}
				$cargo_query->Movenext();
			}

			array_multisort($p_create_percent, $newcargotype, $cargoclass, $default_prod, $default_indy_prod, $is_prod, $goodevil);

			$insertlist = "";
			$insertlistprod = "";
			for($ii = 0; $ii < $defaultcargototal; $ii++)
			{
				if($ddefault_prod[$ii] > 0)
				{
					$insertlist .= ", prod_" . AAT_strtolower($dnewcargotype[$ii]);
					$insertlistprod .= ", '$ddefault_prod[$ii]'";
				}
			}

			if(mt_rand(0, 100) < 10 && $extracargototal != 0)
			{
				$specialcargo = mt_rand(0, 10000);
				for($checkcargo = $extracargototal - 1; $checkcargo >= 0; $checkcargo--)
				{
					if($specialcargo < floor($p_create_percent[$checkcargo] * 100))
					{
						$special_cargo = $newcargotype[$checkcargo];
						$special_goodevil = $goodevil[$checkcargo];
					}
				}
			}
			else
			{
				$special_cargo = '';
				$special_goodevil = 0;
			}

			if(mt_rand(1, 100) <= $planet_production_skew)
			{
				$organics_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
			}
			else
			{
				$organics_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
			}

			if(mt_rand(1, 100) <= $planet_production_skew)
			{
				$ore_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
			}
			else
			{
				$ore_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
			}

			if(mt_rand(1, 100) <= $planet_production_skew)
			{
				$goods_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
			}
			else
			{
				$goods_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
			}

			if(mt_rand(1, 100) <= $planet_production_skew)
			{
				$energy_planet = (float)sprintf("%01.4f", (myrand(0, floor(30000 * ($planet_prod_low_percent / 100)), 5.0) / 30000.0) + 1);
			}
			else
			{
				$energy_planet = (float)sprintf("%01.4f", 1 - (myrand(0, floor(30000 * ($planet_prod_high_percent / 100)), 5.0) / 30000.0));
			}

			$creation_date = date("Y-m-d H:i:s");
			$debug_query = $db->Execute("INSERT INTO {$db_prefix}planets 
										(sector_id, owner, base, colonists, last_owner_rating, persuasion_countdown, max_credits, prod_fighters, prod_torp, special_name, special_goodevil, organics_planet, ore_planet, goods_planet, energy_planet, creation_date" . $insertlist . ") 
										VALUES 
										('$shipinfo[sector_id]', $playerinfo[player_id], 'Y', $colonistlimit, $old_owner_rating, $persuasion_countdown, '$base_credits', '$default_prod_fighters', '$default_prod_torp', '$special_cargo', '$special_goodevil', '$organics_planet', '$ore_planet', '$goods_planet', '$energy_planet', '$creation_date'" . $insertlistprod . ")");
			db_op_result($debug_query,__LINE__,__FILE__);

			$res = $db->Execute("DELETE FROM {$db_prefix}artifacts WHERE player_id=$playerinfo[player_id] and artifact_type='" . $this->class . "'");
			db_op_result($res,__LINE__,__FILE__);

			$output ="<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			return $output;
		}
		else
		{
			$output ="<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
			return $output;
		}
	}
}

?>