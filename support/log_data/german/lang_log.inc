<?php
$l_log_months 		 = array('Januar','Februar','März','April','Mai','Juni','Juli','August','September','Oktober','November','Dezember');
$l_log_months_short 	 = array('Jan','Feb','Mar','Apr','Mai','Jun','Jul','Aug','Sep','Okt','Nov','Dez');
$l_log_pod 		 = "Glücklicherweise hatten Sie eine Rettungskapsel";
$l_log_nopod 		 = "<font color=yellow><b>Sie hatten keine Rettungskapsel.Sie sind gestorben.</b></font>";
$l_log_log 		 = "[Player] Logbuch";
$l_log_start 		 = "Logbuch-Eintrag für";
$l_log_end 		 = "Ende des Logbuch-Eintrags für";
$l_log_click 		 = "Klick <A HREF=main.php><font color=#00ff00>hier</font></A> um zum Hauptmenu zurückzukehren.";
$l_log_select 		 = "Wählen Sie eine Log:";
$l_log_general 		 = "Haupt-Log";
$l_log_dig 		 = "Dignitary-Log";
$l_log_spy 		 = "Spion-Log";
$l_log_disaster 	 = "Planetenunglücke-Log";
$l_log_nova 		 = "Nova Geräte-Log";
$l_log_attack 		 = "Angriffs-Log";
$l_log_scan 		 = "Scan-Log";
$l_log_starv 		 = "Planetenhungers Log";
$l_log_probe 		 = "Sonden-Log";
$l_log_autotrade 	 = "automatisches Handeln Log";
$l_log_combined 	 = "kombinierte Log";

// Log entry data

$l_log_text["LOG_LOGIN"] 	 = "Sie wurden eingeloggt von [ip].";
$l_log_title["LOG_LOGIN"]  = "Eingeloggt";
$l_log_text["LOG_LOGOUT"]  = "Sie wurden ausgeloggt von [ip].";
$l_log_title["LOG_LOGOUT"] = "Ausgeloggt";
$l_log_text["LOG5_ATTACK_OUTMAN"] 		= "[player] wurde in Angriffsposition gesichtet, aber Ihr Können als Pilot und ihren Guten Antriebsaggregaten erlaubten Ihnen dem Feind zu entkommen.";
$l_log_title["LOG5_ATTACK_OUTMAN"] 	= "Ausweichmanöver!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] 	= "Sie spürten [player]'s Waffen auf, die versucht haben Ihr Schiff zu fixieren, aber Ihr Unsichtbarkeitsgenerator hat die primitiven Sensoren des Gegners irritiert.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] 	= "Unsichtbarkeit erfolgreich!";
$l_log_text["LOG5_ATTACK_EWD"] 		= "Sie sind von [player]'s trügerischer Attacke überrascht worden. Sie können die Sprengköpfe, die auf Sie zufliegen schon riechen, als Sie wie wahnsinnig den Notwarp-Punkt erreichen. Die Welt um Sie herum verschwimmt. Für eine Millisekunde denken Sie, Sie sind Tod. Als sie nach langer Ruhe ihre Augen öffnen, sehen Sie, dass sie sicher irgendwohin transportiert wurden. Aber wohin genau? Sie wissen es nicht...";
$l_log_title["LOG5_ATTACK_EWD"] 		= "Notswarp!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] 	= "Ihre Sensoren erkennen [player]'s Schiff in Angriffsposition. \"Lieber in Sicherheit bringen, als draufgehn\", denken Sie, während Sie den Notwarp-Knopf drücken. Sie hören einen seltsamen erschreckenden Ton aus Ihrem Triebwerksraum, und Sie riechen eine brennende Schaltung. \"Verdammte Scheisse!\", schreien Sie, während Sie auf dem Computer herumtrammpeln. Der Computer gibt protestierende Biepser aus, während Sie sich auch den bevorstehenden Angriff vorbereiten...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Notwarp <font color=red>fehlgeschlagen</font>";
$l_log_text["LOG5_ATTACK_LOSE"] 		= "Ihr Schiff wird von [player] angegriffen. Versuchen Sie was Sie können, aber Sie können sich selbst nicht vor den überlegenen Waffen von [player] schützen. Ihr Schiff wurde zerstört.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Kampf verloren!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] 		= "Ihr Schiff wurde von [player] angegriffen. Sie kämpfen einige Zeit, dan bricht der Kampf ab. Sie haben verloren. [armor] Rüstungspunkt und  [fighters] Jäger sind verloren.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Verloren!</font>";
$l_log_text["LOG5_HIT_MINES"] 		= "Sie haben [mines] Minen erwischt, während Sie im Sktor [sector] herumflogen.";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Minenalarm!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] 	= "Ihr Schiff wurde von einem Minenfeld in Sktor [sector] zerstört. ";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Minenalarm!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] 	= "Ihr Planet [planet_name] im Sektor [sector] wurde erfolgreich gegen [name] verteidigt. Glücklicherweise! Die starke Loyalität ihrer Bewohner hat den Sieg begünstigt. Sie haben sich mutig entschlossen viel eher den Planeten zu zerstören, als in die gegnerische Hände fallen zu lassen. Sie organisieren prächtige Begräbnisse für die gefallenen Brüder.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet zerstört</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] 	= "Ihr  Planet [planet_name] im Sektor [sector] wurde gegen [name] verteidigt. Die Leute auf dem Planetenen begrüssen ihren neuen Herrscher. Sie hören eine Rede auf FNN: \"Wir sind glückliche diesen alten Sack los zusein!Wir wollen keinen stinkigen Verlierer, der uns nicht beschützen kann!\". Sie schwören Rache für diese Arroganz.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet verteidigt!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] 	= "Ihr Planet [planet_name] im Sektor [sector] wurde von [name] angegriffen. Die Bürger organisierten eine Bürgerfront, und zerstörten den Gegener erfolgreich. Sie erbeuteten einige Resourcen: [goods] Güter, [ore] Erz, [organics] organischer Material and [salvage]% des Werte der Schiffe: [credits] credits.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] 	= "Sieg!";
$l_log_title["LOG5_AFTER_ACTION"] = "After Action Kampfbericht";
$l_log_title["LOG0_RAW"] 			= "Ankündigung";
$l_log_text["LOG5_DEFS_DESTROYED"] 	= "[quantity] [type] wurden im Sektor [sector] zerstört.";
$l_log_title["LOG5_DEFS_DESTROYED"] 	= "Sektorverteidigung zerstört";
$l_log_text["LOG0_PLANET_EJECT"] 		= "Sie wurden aus dem Planeten in Sektor [sector] geworfen, da [name] das Team verlassen hat.";
$l_log_title["LOG0_PLANET_EJECT"] 		= "Rausgeflogen!";
$l_log_text["LOG0_BADLOGIN"] 		= "Es gab einen Login-Fehlerversuch von [ip].";
$l_log_title["LOG0_BADLOGIN"] 		= "Login fehlgeschlagen";
$l_log_text["LOG6_PLANET_SCAN"] 		= "[name] hat ihren Planeten [planet_name] im Sektor [sector] gescannt.";
$l_log_title["LOG6_PLANET_SCAN"] 		= "Planetenscan";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] 	= "[name] hat versucht Ihren Planeten [planet_name] im Sektor [sector] zu scannen, scheiterte aber.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] 	= "Planetenscna fehlgeschlagen";
$l_log_text["LOG6_SHIP_SCAN"] 		= "[player] hat ihr Schiff gescnannt.";
$l_log_title["LOG6_SHIP_SCAN"] 		= "Schiffscan";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] 	= "[player] hat versucht ihr Schiff zu scannen, scheiterte aber.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] 	= "Schiffscan fehlgeschlagen";
$l_log_text["LOG5_KABAL_ATTACK"] 		= "Angriff auf [player]...";
$l_log_title["LOG5_KABAL_ATTACK"] 		= "Angriff";
$l_log_text["LOG7_STARVATION"] 		= "PLaneten [name] in Sektor [sector] kann die Bevölkerung nicht bestehen bleiben! Es wird mehr organische Material benötigt. [starvation] Kolonisten sind verhungert. Colonists started starving on [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Hungerstod!</font>";
$l_log_title["LOG0_TOW"] 			= "Geschleppt!";
$l_log_text["LOG0_TOW"] = "Das Schiff wurde von Sektor [sector] zu Sektor gezogen [newsector], da die durchschnittliche Tech-level der Grenzwert von [hull] überschritten oder Sie haben ein Schiff in den Lagern.";
$l_log_text["LOG5_DEFS_DESTROYED_F"] 	= "Sie haben [fighters] zerstört. Sie haben [fighters] Pattrolien in Sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] 	= "Jäger zerstört";
$l_log_text["LOG5_DEFS_KABOOM"] 		= "Sie wurden von Jägern im Sektor [sector] zerstört. ";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Schiff zerstört!</font>";
$l_log_text["LOG0_HARAKIRI"] 		= "Sie sind müde diesen Frachtkahn zu befehligen, deshalb haben Sie sich entschieden, dass das Universum ohne diese Rostlaube besser dran ist. Genehmigt von [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Selbstzerstörung!</font>";
$l_log_text["LOG0_TEAM_REJECT"] 		= "[player] hat die Einladung dem Team [teamname] beizutreten ausgeschlagen.";
$l_log_title["LOG0_TEAM_REJECT"] 		= "Einladung abgelehnt!";
$l_log_text["LOG0_TEAM_RENAME"] 		= "Sie haben ihr Team in [team] umgenannt.";
$l_log_title["LOG0_TEAM_RENAME"] 		= "Team umgenannt!";
$l_log_text["LOG0_TEAM_M_RENAME"] 		= "Ihr Temakoordinator hat das Team in [team] umgenannt.";
$l_log_title["LOG0_TEAM_M_RENAME"] 	= "Team umgenannt";
$l_log_text["LOG0_TEAM_KICK"] 		= "Sie wurden aus dem Team [team] herausgeworfen.";
$l_log_title["LOG0_TEAM_KICK"] 		= "Teamrauswurf!";
$l_log_text["LOG0_TEAM_CREATE"] 		= "Sie haben ein neues Team namens [team] erstellt.";
$l_log_title["LOG0_TEAM_CREATE"] 		= "Neues Team erstellt.";
$l_log_text["LOG0_TEAM_LEAVE"] 		= "Sie haben das Team [team] verlassen.";
$l_log_title["LOG0_TEAM_LEAVE"] 		= "Team verlassen";
$l_log_text["LOG0_TEAM_NEWLEAD"] 		= "Sie haben das Team [team] verlassen. Sie haben die Team-Führung von [name] abgegeben.";
$l_log_title["LOG0_TEAM_NEWLEAD"] 		= "Team verlassen";
$l_log_text["LOG0_TEAM_LEAD"] 		= "Ihr Teamkoordinator hat entschieden das Team [team] zu verlassen. Sie wurden als sein Nachfolger ernannt.";
$l_log_title["LOG0_TEAM_LEAD"] 		= "Beförderung!";
$l_log_text["LOG0_TEAM_JOIN"] 		= "Sie sind dem Team [team] beigetreten.";
$l_log_title["LOG0_TEAM_JOIN"] 		= "Team beigetreten";
$l_log_text["LOG0_TEAM_NEWMEMBER"] 	= "[name] hat dem Beitritt zu [team] zugestimmt. Dies bringt sie einen Schritt zur Herrschaft über die Galaxie näher.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] 	= "Es gibt ein neues Teammitglied!";
$l_log_text["LOG0_TEAM_INVITE"] 		= "Sie werden eingeladen dem Team [team] beizutreten.";
$l_log_title["LOG0_TEAM_INVITE"] 		= "Einladung";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] 	= "[player] hat das Team verlassen.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] 	= "Team verliert Mitglied";
$l_log_text["LOG0_ADMIN_HARAKIRI"] 	= "[player] hat die Selbstzerstörung von der Ip [ip] aus eingeleitet.";
$l_log_title["LOG0_ADMIN_HARAKIRI"] 	= "Selbstzerstörung";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] 	= "[player] hatte [quantity] [type], mit dem Maximum an Holds von [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] 	= "Illegaler Schiffwert";
$l_log_text["LOG0_ADMIN_PLANETDEL"] 	= "[attacker] hat versucht [defender]'s planet im Sektor [sector] einzunehmen. Der Planet wurde stattdessen zerstört.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] 	= "Planet zerstört";
$l_log_text["LOG0_defense_DEGRADE"] 	= "Sektor-Verteidigungs-Jäger im Sektor [sector] wurden aufgrund mangelder Energie um  [degrade] Prozent ihrer Stärke erniedrigt.";
$l_log_title["LOG0_defense_DEGRADE"] 	= "Sektor-Verteidigung fällt weiter.";
$l_log_text["LOG5_PLANET_CAPTURED"] 	= "Sie haben einen Planeten von [owner] erobert. Er hatte [cols] Kolonisten und [credits] Credits.";
$l_log_title["LOG5_PLANET_CAPTURED"] 	= "Planet erobert!";
$l_log_text["LOG0_CHEAT_TEAM"] 		= "Der spieler [player] mit der IP-addresse [ip] hat versucht den Team-Kick-cheat anzuwenden. Sein Schiff wurde zerstört.";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Sie forderten eine Prämie von [amount] Credits dür die Zerstörung von [bounty_on]'s Schiffes. Die Prämie wurde ausgestellt von [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Prämie gefordert.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Die Prämie für [bounty_on] wurde ausgezahlt. Die Summe beträgt [amount] Credits.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "Die Prämie für [bounty_on] wurde von der Föderation mit [amount] credits besteuert.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Prämie bezahlt.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Ihre Prämie für [bounty_on] mit der Gesamtsumme von [amount] Credits wurde zurückerstattet.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Prämie zurückerstattet.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "Die Föderation hat eine Prämie von [amount] Credits auf Sie ausgesetzt.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Prämie ausgesetzt!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Das Bündnis hat ein Kopfgeld auf Sie für die Höhe der in [amount] Credits.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliance Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Der Spieler [name] transferierte [sum] Credits auf Ihr IGB-Konto.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Credits übertragen!";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Sie transferierten [sum] Sredits auf Spieler [name]'s IGB-Konto.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Credits übertragen!";
$l_log_text["LOG4_PLANET_novaED_D"] 	= "Ihr Planet [planet_name] im Sektor [sector] wurde mit einer Nova Bombe von [name] zerstört. Niemand überlebt. Es sind keine Resourcen übrig.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet mit Nova Bombe zerstört</font>";
$l_log_text["LOG4_SHIP_novaED_D"] 	= "Ihr Schiff wurde mit einer Nova Bombe von [name] zerstört.";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Schiff mit Nova Bomb zerstört</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] 	= "Ihre dignitary-zahl [DIG] des Planeten [PLANET] wurde unterschlagen.  Möglicherweise wollen Sie sie aufgeben.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Veruntreuer gefunden!</font>";
$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Ihre Sonde mit der id [id] entdeckte [ship_name], wie es den Sektor [sector] betreten hat.</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Erkannt Incoming Schiff";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Ihre Sinde mit der id [id] hat das Schiff [ship_name] gescannt, wie es den Sektor [sector] betretten hat<br>Hülle: [hull] Antrieb: [engines] Energie: [power] Jäger: [computer] Sensoren: [sensors] Beams: [beams] Torp Launchers: [torps] Rüstung: [armor] Schilde: [shields] Tarnung: [cloak]<br>Rüstungspunkt: [armor_pts] Jäger: [fighters] Torpedoes: [avail_torps] Schiffenergie: [energy] Credits: [credits] <br>Minen Deflectoren: [deflectors] Notwarp: [ewd] Rettunsgkapsel: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Probe Gescannte Incoming Schiff";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] Planeten [planetname] ([planetid]) im Besitz von [owner] unabhängig wurde. Durchschnittliche Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet ging unabhängig.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Unabhängige Planeten [planetname] ([planetid]) im Besitz von [owner] in [sector] wurde gelöscht. Durchschnittliche Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Unabhängige Planet gelöscht.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Nie besessen Planeten [planetname] ([planetid]) Erstellt am [date] in [sector] wurde gelöscht. Durchschnittliche Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Nie besessen Planet gelöscht.";
$l_log_text["LOG0_TEAM_CANCEL"] 		= "Ihre Einladung für das Team [team] wurde zurückgezogen.";
$l_log_title["LOG0_TEAM_CANCEL"] 		= "Einladung zurückgezogen!";
$l_log_text["LOG10_AUTOTRADE"]="<font color=yellow>Automatisches Handeln für [planetname] im Sektor [sector] für insgesamt [totalcost] Credits.<br>Güter: [goodsamount] @ [goodsprice] Credits - Erz: [oreamount] @ [oreprice] Credits - organisches Material: [organicsamount] @ [organicsprice] Credits - Energie: [energyamount] @ [energyprice] Credits - Colonists: [colonistamount] @ [colonistprice] credits<br></font>";
$l_log_title["LOG10_AUTOTRADE"] 		= "Bericht für automatisches Handeln";
$l_log_text["LOG10_AUTOTRADE_ABORTED"]="<font color='#00ff00'>Automatisches Handeln für [planetname] im Sektor [sector] wurde wegen gegnerischer Sektorverteidigunng im Sektor [destsector] abgebrochen.<br></font>";
$l_log_title["LOG10_AUTOTRADE_ABORTED"] 		= "Bericht für automatisches Handeln";

$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SEKTORVERTEIDIGUNG i [sector] hat Ihre Sonde zerstört.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] 		= "Sonde zerstört!";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>Sie haben nicht genügend Truns um die Sonde [probe_id] nach [sector] zu bewegen!</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] 		= "Sondenbericht";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"] = "<font color='#00ff00'>Die Verlegung nach [target_sector] ist nicht erlaubt</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] 		= "Sondenbericht";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Die Sonde [probe_id] im Sektor [sector] entdeckte [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] <font color='yellow'>Sondenbericht</font>";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

// added
$l_log_text["LOG5_PLANET_BOMBED"] = "Ihr Planet [planet_name] im Sektor [sector] wurde von [name] bombardiert. Sie haben [beams] Energie und [torps] Torpedos in Ihrer Verteidigung.  Sie haben [figs] Jäger verloren.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombardiert!</font>";

$l_log_text["LOG1_DIG_PRODUCTION"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sector [sector] hat mit der Produktion von Gebäuden begonnen.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Gebäudeproduktion begonnen!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sektor [sector] hat die Geburtenraten erniedrigt.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Geburtenrate fällt!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sektor [sector] erniedrigt die Geburtenrate.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Geburtenrate fällt!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sektor [sector] hat begonnen nach Spionen auf dem PLaneten zu suchens.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spionen-Jagd!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sektor [sector] hat begonnen die Credit-Produktion zu verstärken.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interesse an Gebäuden hat begonnen!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Ihre Dignitary [id] auf dem Planeten [planet_name] produzierte [data] Credits und übergab sie an Sie!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>Sie haben frische Credits erhalten!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Ihre dignitary entdeckte [name]'s Spion auf ihrem Planet [planet_name] im Sektor [sector]. Der Spion ist nun tod.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Feindlicher Spion getötet</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Ihre dig [id] auf dem Planeten [planet_name] im Sektor [sector] ist bei einer schreklichen Überschwemmung auf dem Planetenen umgekommen.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig verloren!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Ihre dig [id] auf [name]'s Schiff [shipname] ist bei einer schrecklichen Katastrophe auf dem Schiff umgekommen.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig verloren!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sektor [sector] baute [data] planetarische Torpedos!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedos gebaut!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Ihre dignitary [id] auf dem Planeten [planet_name] im Sektor [sector] baute [data] planetarische Jäger!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Jäger gebaut!</font>";

$l_log_text["LOG5_PLANET_YOUR_CAPTURED"]   = "Ihr Planet [planet_name] im Sektor [sector] wurde während der Verteidigung von diesem verdammten [name] eingenommen.";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet eingenommern</font>";
$l_log_text["LOG5_STORAGE_EWD"] = "Dein Planet ist überrascht [player] &#39;s anzugreifen. Einer Ihrer gespeicherten Schiffe aus einer Notfall-Warp auf [sector] und die Landung auf dem Planeten [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Gespeicherte Schiff Emergency Warp!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "Eine gespeicherte Schiffe Emergency Warp Device NICHT! Die gespeicherten Schiff wurde durch erfasst [player], nachdem sie eurem Planeten besiegt!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "Eine gespeicherte Schiff wurde durch erfasst [player], nachdem sie eines Ihrer Planeten besiegt!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";

$l_log_text["LOG2_SPY_NEWSHIP"] = "Sie haben ihren Spion [id] auf [name]'s Schiff [shipname]verloren, weil dieser Spieler ein neues Schiff gekauft hat.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spion getötet!</font>";

$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] hat versucht einen Spion auf Ihren Planeten [planet_name] im Sektor [sector] zu senden, aber Ihre Sensoren entdeckten den Spion. Er ist nun tot.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Feindlicher Spion getötet!</font>";

$l_log_text["LOG2_SPY_SABOTAGE"] = "Ihr Spion [id] auf dem Planetenen [planet_name] im Sektor [sector] hat mit der Sabotage begonnen. Die Produktion auf diesem Planeten ist um [data] gefallen.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage begonnen!</font>";

$l_log_text["LOG2_SPY_BIRTH"] = "Ihr Spion [id] auf dem Planeten [planet_name] im Sektor [sector] senkte die Geburtenrate um [data].";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Geburterate erniedrigt</font>";

$l_log_text["LOG2_SPY_INTEREST"] = "Ihr Spion [id] auf dem Planetenen [planet_name] im Sektor [sector] hat begonnen Zinsen von [data] einzusammeln.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Zinsen.Diebstahl begonnen!</font>";

$l_log_text["LOG2_SPY_MONEY"] = "Ihr Spion [id] auf dem Planeten [planet_name] im Sektor [sector] hat [data] Credits für sie gestohlen!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits gestohlen!</font>";

$l_log_text["LOG2_SPY_TORPS"] = "Ihr Spion [id] auf dem Planeten [planet_name] im Sektor [sector] zerstörte [data] planetarische Torpedos!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedos zerstört!</font>";

$l_log_text["LOG2_SPY_FITS"] = "Ihr Spion [id] auf dem Planeten [planet_name] im Sektor [sector] zerstörte [data] planetarische Jäger!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Jäger zerstört!</font>";

$l_log_text["LOG2_SPY_CPTURE"] = "Ihr Spion [id] auf dem Planeten [planet_name] im Sektor [sector] hat den Planet eingenommen!!";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET EINGENOMMEN!</font>";

$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name]'s Spion hat Ihren Planet [planet_name] im Sektor [sector] eingenommen! Es scheint, als wäre es eine weise Idee, den Planeten öfter zu reinigen...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet verloren!</font>";

$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Es gab schon lange keine Nachrichten von ihrem Spion [id] auf dem Planeten [planet_name] im Sektor [sector] - Es scheint, dass sich dieser Idiot nicht genügend tarnen konnte, und jetzt getötet wurde.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spion verloren!</font>";

$l_log_text["LOG2_SPY_KILLED"] = "Ihre Sensoren entdeckten ein Spion von [name] auf ihrem Planeten [planet_name] im Sektor [sector]. Der Spion ist nun getötet worden.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Feindlicher Spion getötet!</font>";

$l_log_text["LOG2_SHIPSPY_KILLED"] = "Es gab schon lange keine Nachrichten von ihrem Spion [id] auf dem Planeten [planet_name] im Sektor [sector] - Es scheint, dass sich dieser Idiot nicht genügend tarnen konnte, und jetzt getötet wurde.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spion verloren!</font>";

$l_log_text["LOG2_SPY_CATACLYSM"] = "Ihr Spion [id] auf dem Planeten [planet_name] im Sektor [sector] wurde bei einer schrecklichen Katastrophe auf dem Planeten getötet.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spion verloren!</font>";

$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Ihr Spion [id] auf [name]'s Schiff [shipname] wurde bei einer schreicklichen Katastrophe auf dem Schiff getötet.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spion verloren!</font>";

$l_log_text["LOG2_SPY_TOSHIP"] = "Ihr Spion [id] auf dem Planet [planet_name] im Sektor [sector] infiltrierte [playername]'s Schiff [shipname] und spioniert nun da.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spion infiltriert feindliches Schiff!</font>";

$l_log_text["LOG2_SPY_TOPLANET"] = "Ihr Spion [id] auf [playername]'s Schiff [shipname] infiltrierte den Planeten [planet_name] im Sektor [sector] und spioniert nun da.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spion infiltriert feindlichen Planeten!</font>";


$l_log_text["LOG5_SM_ATTACK"] = "Ship Sensoren erkannt einen eingehenden Sector Raketenabwehr gegen [sector] von [player] gefeuert!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "Ein Sektor Raketen abgefeuert durch [player] wurde entdeckt Verwerfungen in den Sektor und Sie umgehen den Angriff.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sector Missile Evasive action!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Sie entdeckt [player] &#39;s einen eingehenden Sector Missile versucht, auf Ihr Schiff zu reparieren, aber deinen Mantel Generatoren gelungen, die Raketen Sector Sensorkreise Narr.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sector Missile Umhang erfolgreich!";
$l_log_text["LOG5_SM_EWD"] = "Sie sind überrascht [player] &#39;s Sector Raketenangriff und sich die Notfall-Warp Device Springen zu einem unbekannten Sektor.";
$l_log_title["LOG5_SM_EWD"] = "Sector Missile Emergency Warp!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Ihre Sensoren erfassen [player] &#39;s Sector Raketenangriff und sich die Notfall-Warp-Gerät. Sie hören ein seltsames Würgen Sound aus den Zimmer-Motoren und der Geruch verbrannten Schaltung. &quot;Stupid Stück Scheiße!&quot; Sie schreien, treten am Computer. Sie Klammer für die Wirkung!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Das Schiff wurde angegriffen [player] mit einem Sektor Missile. Sie verloren [armor] Rüstung Punkte und [energy] Energie-Einheiten in den Angriff.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Das Schiff wurde von einem Sektor aus Missile zerstört [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat lost!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Das Schiff wurde beschlagnahmt [player]. Tun, um übermäßige Angriffe auf Bounty Spieler die [player] ist einer der Ihre Schiffe ([ship]) beschlagnahmt.";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "Eine gespeicherte Schiff Suicided wenn [player] ein Ihrer Planeten geschlagen und versucht, sie zu erobern!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";
$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Das Schiff wurde durch eine Sonde im Besitz von [player] in Sektor angegriffen [sector]. Sie verloren [armor] Rüstung Punkte und [energy] Energie-Einheiten in den Angriff.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] überlebt einen Angriff von Ihrem Sonde im Sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Ihre Sonde zerstört das Schiff im Besitz von [player] im Bereich [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Das Schiff wurde von einer Sonde von [player] in Sektor zerstört [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Euer Planet wurde beschlagnahmt [player]. Tun, um übermäßige Angriffe auf Bounty Spieler die [player] ist einer Ihrer Planeten ([name]) dem Sektor [sector] Wert [score] credits beschlagnahmt.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";


$l_log_title["LOG0_ADMIN_DBERROR"] = "Datenbank-Fehler ist aufgetreten";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Aktion Ergebnis";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] versucht, einen Ihrer Sonden im Scan-Bereich [sector], scheiterte aber.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "Einer Ihrer Sonden im Sektor [sector] wurde von gescannten [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "Einer Ihrer Sonden im Sektor [sector] angegriffen und zerstört durch [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "Einer Ihrer Probe Jäger hat eine [probe_type] im Besitz von [name] in [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe zerstört Hunter [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Ihre [probe_type] im Bereich [sector] angegriffen wurde und durch eine Probe Hunter Besitz zerstört [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Ihre Probe Hunter im Sektor [sector] ging verloren, als die daraus resultierende Explosion von seinem Angriff auf die [probe_type] im Besitz von [name] umgeben haben.";
$l_log_title["LOG9_PROBEHUNTER_EXPLODED"] 		= "Probe Hunter Probe <font color='yellow'>Destroyed</font>";

?>
<?php
$l_log_title["LOG3_SPACE_PLAGUE"] = "Weltraum-Pest!";
$l_log_text["LOG3_SPACE_PLAGUE"] = "Ihr Planet [name] im Sektor [sector] wurde von der Weltraumpest getroffen. [percentage] Prozent der Kolonisten wurden getötet";
?>
<?php
$l_log_title["LOG3_PLASMA_STORM"] = "Plasma-Sturm!";
$l_log_text["LOG3_PLASMA_STORM"] = "Ihr Planet [name] im Sektor [sector] wurden von einem Plasmasturm getroffen. Alle gespeicherte Energie ging verloren.";
?>
<?php
$l_log_title["LOG3_PLANET_REVOLT"] = "Planetarische Revolution";
$l_log_text["LOG3_PLANET_REVOLT"] = "Es gibt zu viele Leute auf ihrem Planeten [name] im Sektor [sector] deshalb gibt es eine Revolution!! Schaden: [credits]% Credits verloren, [colonists]% Colonisten getötet, [organics]% des organischen Materials vernichtet, [goods]% der Güter zerstört, [ore]% des Erzes vernichtet, [torps]% Torps zerstört, [fighters]% Jäger zerstört und [energy]% an Energie verloren.";
?>
<?php
$l_log_title["LOG5_PROBE_WARP"] = "";
$l_log_text["LOG5_PROBE_WARP"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_HUNTER"] = "";
$l_log_text["LOG5_PROBE_HUNTER"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_SGSEARCH"] = "";
$l_log_text["LOG5_PROBE_SGSEARCH"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_SENTRY"] = "";
$l_log_text["LOG5_PROBE_SENTRY"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_SEEKER"] = "";
$l_log_text["LOG5_PROBE_SEEKER"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_REALSPACE"] = "";
$l_log_text["LOG5_PROBE_REALSPACE"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_HUNTER_PROBE"] = "";
$l_log_text["LOG5_PROBE_HUNTER_PROBE"] = "";
?>
<?php
$l_log_title["LOG5_PROBE_TRAP"] = "";
$l_log_text["LOG5_PROBE_TRAP"] = "";
?>
