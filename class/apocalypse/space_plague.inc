<?
class space_plague {

	var $tag = "LOG3_SPACE_PLAGUE";
	var $space_plague_kills= 50; //Maximum Percentage of colonists killed by space plague

	function space_plague()
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
	$retvalue[\'text\'] = str_replace("[percentage]", "$percentage", $retvalue[\'text\']);
	$retvalue[\'title\'] = $l_log_title[$entry[\'type\']];
  }
?>
';
		return $data;
	}

	function log_language_data()
	{
		$log_language_data["estonian"]["title"] = "Kosmiline katk!";
		$log_language_data["estonian"]["text"] = "Su planeeti [name] sektoris [sector] tabas kosmiline katk. [percentage] protsenti kolonistidest hukkus.";
		$log_language_data["french"]["title"] = "Kosmiline katk!";
		$log_language_data["french"]["text"] = "Su planeeti [name] sektoris [sector] tabas kosmiline katk. [percentage] protsenti kolonistidest hukkus.";
		$log_language_data["german"]["title"] = "Weltraum-Pest!";
		$log_language_data["german"]["text"] = "Ihr Planet [name] im Sektor [sector] wurde von der Weltraumpest getroffen. [percentage] Prozent der Kolonisten wurden getцtet";
		$log_language_data["italian"]["title"] = "Piaga Spaziale!";
		$log_language_data["italian"]["text"] = "Il tuo pianeta [name] nel settore [sector] и stato colpito dalla Piaga Spaziale. Il [percentage] percento dei coloni и stato ucciso.";
		$log_language_data["russian"]["title"] = "Космическая чума!";
		$log_language_data["russian"]["text"] = "На вашей планете [name] в секторе [sector] разразилась космическая чума. [percentage] процентов населения погибло.";
		$log_language_data["spanish"]["title"] = "ЎPlaga Espacial!";
		$log_language_data["spanish"]["text"] = "Tu planeta [name] en el sector [sector] ha sido golpeado por una plaga espacial. El [percentage] por ciento de de los colonos fueron asesinados.";
		$log_language_data["english"]["title"] = "Space Plague!";
		$log_language_data["english"]["text"] = "Your planet [name] in sector [sector] has been hit by Space Plague. [percentage] percent of the colonists were killed.";
		return $log_language_data;
	}

	function apocalypse($targetplanet, $targetsector, $targetname, $targetowner)
	{
		global $db, $db_prefix;

		TextFlush ( "Space Plague triggered for $targetname($targeowner).<br>.");
		$percentage = mt_rand( 0, $this->space_plague_kills) * 0.01;
		$debug_query = $db->Execute("UPDATE {$db_prefix}planets SET colonists = ROUND(colonists-colonists * " . $percentage . ") WHERE planet_id = $targetplanet");
		db_op_result($debug_query,__LINE__,__FILE__);

		$logpercent = ROUND($percentage * 100);
		playerlog($targetowner, $this->tag ,"$targetname|$targetsector|$logpercent"); 
	}
}
?>