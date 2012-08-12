<?
// Plasma Storm

class plasma_storm {

	var $tag = "LOG3_PLASMA_STORM";

	function plasma_storm()
	{
	}

	function log_switch_data()
	{
		$data = '<?php
  if($entry[\'type\'] == "' . $this->tag . '")
  {
	list($name,$sector,$percentage) = AAT_split ("\|", $entry[\'data\']);
	$resx = $db->SelectLimit("SELECT sector_name from {$db_prefix}universe WHERE sector_id =" . $sector, 1);
	db_op_result($resx,__LINE__,__FILE__);
	$sector = $resx->fields[\'sector_name\'];
	$retvalue[\'text\'] = str_replace("[name]", "<font color=white><b>$name</b></font>", $l_log_text[$entry[\'type\']]);
	$retvalue[\'text\'] = str_replace("[sector]", "<font color=white><b><a href=main.php?move_method=real&engage=1&destination=$sector>$sector</a></b></font>", $retvalue[\'text\']);
	$retvalue[\'text\'] = str_replace("[percentage]", "<font color=white><b>$percentage</b></font>", $retvalue[\'text\']);
	$retvalue[\'title\'] = $l_log_title[$entry[\'type\']];
  }
?>
';
		return $data;
	}

	function log_language_data()
	{
		$log_language_data["estonian"]["title"] = "Plasmatorm!";
		$log_language_data["estonian"]["text"] = "Su planeeti [name] sektoris [sector] tabas plasmatorm. Selle tagaj&auml;rjel h&auml;vis kogu varutud energia.";
		$log_language_data["french"]["title"] = "Plasmatorm!";
		$log_language_data["french"]["text"] = "Su planeeti [name] sektoris [sector] tabas plasmatorm. Selle tagaj&auml;rjel h&auml;vis kogu varutud energia.";
		$log_language_data["german"]["title"] = "Plasma-Sturm!";
		$log_language_data["german"]["text"] = "Ihr Planet [name] im Sektor [sector] wurden von einem Plasmasturm getroffen. Alle gespeicherte Energie ging verloren.";
		$log_language_data["italian"]["title"] = "Tempesta magnetica!";
		$log_language_data["italian"]["text"] = "Il tuo pianeta [name] nel settore [sector] и stato colpito da una tempesta magnetica. Tutta l'energia immagazzinata и andata persa.";
		$log_language_data["russian"]["title"] = "Плазменный шторм!";
		$log_language_data["russian"]["text"] = "Ваша планета [name] в секторе [sector] попала в плазменный шторм. Все запасы энергии были уничтожены.";
		$log_language_data["spanish"]["title"] = "ЎTormenta de Plasma!";
		$log_language_data["spanish"]["text"] = "Tu planeta [name] en el sector [sector] ha sido golpeado por una tormenta de plasma. Toda la energнa almacenada se ha perdido.";
		$log_language_data["english"]["title"] = "Plasma Storm!";
		$log_language_data["english"]["text"] = "Your planet [name] in sector [sector] has been hit by a Plasma Storm. All stored Energy has been lost.";
		return $log_language_data;
	}

	function apocalypse($targetplanet, $targetsector, $targetname, $targetowner)
	{
		global $db, $db_prefix;

		TextFlush ( "Plasma Storm triggered for $targetname($targetowner).<BR>.");
		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET energy = 0 WHERE planet_id = $targetplanet");
		db_op_result($debug_query,__LINE__,__FILE__);
		playerlog($targetowner,"LOG3_PLASMA_STORM","$targetname|$targetsector");
	}
}
?>