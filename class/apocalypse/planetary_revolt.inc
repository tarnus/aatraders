<?
// Planetary Revolt

class planetary_revolt {

	var $tag = "LOG3_PLANET_REVOLT";

	function planetary_revolt()
	{
	}

	function log_switch_data()
	{
		$data = '<?php
  if($entry[\'type\'] == "' . $this->tag . '")
  {
	list($name,$sector,$organics,$goods,$ore,$torps,$col,$credit,$fighter,$energy) = AAT_split ("\|", $entry[\'data\']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields[\'sector_name\'];
	$retvalue[\'text\'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry[\'type\']]);
	$retvalue[\'text\'] = str_replace("[sector]", "<font color=white><b>$sector</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[credits]", "<font color=white><b>$credit</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[colonists]", "<font color=white><b>$col</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[organics]", "<font color=white><b>$organics</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[goods]", "<font color=white><b>$goods</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[ore]", "<font color=white><b>$ore</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[torps]", "<font color=white><b>$torps</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[fighters]", "<font color=white><b>$fighter</b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[energy]", "<font color=white><b>$energy</b></font>", $retvalue[\'text\']);
	$retvalue[\'title\'] = $l_log_title[$entry[\'type\']];
  }
?>
';
		return $data;
	}

	function log_language_data()
	{
		$log_language_data["estonian"]["title"] = "Planetary Revolt";
		$log_language_data["estonian"]["text"] = "Too many people on your planet [name] in sector [sector] and they have revolted!!! Damages: [credits]% credits lost, [colonists]% colonists killed, [organics]% organics destroyed, [goods]% goods destroyed, [ore]% ore destroyed, [torps]% torps destroyed, [fighters]% fighters destroyed and [energy]% energy lost.";
		$log_language_data["french"]["title"] = "Planetary Revolt";
		$log_language_data["french"]["text"] = "Too many people on your planet [name] in sector [sector] and they have revolted!!! Damages: [credits]% credits lost, [colonists]% colonists killed, [organics]% organics destroyed, [goods]% goods destroyed, [ore]% ore destroyed, [torps]% torps destroyed, [fighters]% fighters destroyed and [energy]% energy lost.";
		$log_language_data["german"]["title"] = "Planetarische Revolution";
		$log_language_data["german"]["text"] = "Es gibt zu viele Leute auf ihrem Planeten [name] im Sektor [sector] deshalb gibt es eine Revolution!! Schaden: [credits]% Credits verloren, [colonists]% Colonisten getötet, [organics]% des organischen Materials vernichtet, [goods]% der Güter zerstört, [ore]% des Erzes vernichtet, [torps]% Torps zerstört, [fighters]% Jäger zerstört und [energy]% an Energie verloren.";
		$log_language_data["italian"]["title"] = "Rivolta planetaria!";
		$log_language_data["italian"]["text"] = "Troppe persone sul tuo pianeta [name] nel settore [sector] e si sono rivoltati!! Danni: [credits]% dei crediti persi, [colonists]% dei coloni uccisi, [organics]% degli organici distrutti, [goods]% dei prodotti distrutti, [ore]% del metallo distrutto, [torps]% dei siluri esplosi, [fighters]% dei droni inutilizzabili e [energy]% dell'energia andata persa.";
		$log_language_data["russian"]["title"] = "Planetary Revolt";
		$log_language_data["russian"]["text"] = "Too many people on your planet [name] in sector [sector] and they have revolted!!! Damages: [credits]% credits lost, [colonists]% colonists killed, [organics]% organics destroyed, [goods]% goods destroyed, [ore]% ore destroyed, [torps]% torps destroyed, [fighters]% fighters destroyed and [energy]% energy lost.";
		$log_language_data["spanish"]["title"] = "Planetary Revolt";
		$log_language_data["spanish"]["text"] = "Too many people on your planet [name] in sector [sector] and they have revolted!!! Damages: [credits]% credits lost, [colonists]% colonists killed, [organics]% organics destroyed, [goods]% goods destroyed, [ore]% ore destroyed, [torps]% torps destroyed, [fighters]% fighters destroyed and [energy]% energy lost.";
		$log_language_data["english"]["title"] = "Planetary Revolt";
		$log_language_data["english"]["text"] = "Too many people on your planet [name] in sector [sector] and they have revolted!!! Damages: [credits]% credits lost, [colonists]% colonists killed, [organics]% organics destroyed, [goods]% goods destroyed, [ore]% ore destroyed, [torps]% torps destroyed, [fighters]% fighters destroyed and [energy]% energy lost.";
		return $log_language_data;
	}

	function apocalypse($targetplanet, $targetsector, $targetname, $targetowner)
	{
		global $db, $db_prefix;

		$collkillfactor=rand(20,100)/100;
		$creditkillfactor=rand(20,100)/100;
		$fighterskillfactor=rand(20,100)/100;
		$torpskillfactor=rand(20,100)/100;
		$orekillfactor=rand(20,100)/100;
		$organicskillfactor=rand(20,100)/100;
		$goodskillfactor=rand(20,100)/100;
		$energykillfactor=rand(20,100)/100;

		TextFlush ( "Planetary revolt triggered.<br>.");
		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET colonists = ROUND(colonists-colonists*$collkillfactor),
					credits=ROUND(credits-credits*$creditkillfactor), 
					fighters=ROUND(fighters-fighters*$fighterskillfactor),
					torps=ROUND(torps-torps*$torpskillfactor),
					ore=ROUND(ore-ore*$orekillfactor),
					goods=ROUND(goods-goods*$goodskillfactor),
					organics=ROUND(organics-organics*$organicskillfactor),
					energy=ROUND(energy-energy*$energykillfactor) 
					WHERE planet_id = $targetplanet");

		db_op_result($debug_query,__LINE__,__FILE__);

		$collogpercent = ROUND($collkillfactor * 100);
		$creditlogpercent = ROUND($creditkillfactor * 100);
		$fighterlogpercent = ROUND($fighterskillfactor * 100);
		$torpslogpercent = ROUND($torpskillfactor * 100);
		$orelogpercent = ROUND($orekillfactor * 100);
		$goodslogpercent = ROUND($goodskillfactor * 100);
		$organicslogpercent = ROUND($organicskillfactor * 100);
		$energylogpercent = ROUND($energykillfactor * 100);
		playerlog($targetowner,"LOG3_PLANET_REVOLT","$targetname|$targetsector|$organicslogpercent|$goodslogpercent|$orelogpercent|$torpslogpercent|$collogpercent|$creditlogpercent|$fighterlogpercent|$energylogpercent"); 
	}
}
?>