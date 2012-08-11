<?php
$l_log_months = array('jaanuar','veebruar','m&auml;rts','aprill','mai','juuni','juuli','august','september','oktoober','november','detsember');
$l_log_months_short = array('jaan','veebr','m&auml;rts','apr','mai','juuni','juuli','aug','sept','okt','nov','dets');
$l_log_pod = "&Otilde;nneks oli Sul p&auml;&auml;stekapsel!";
$l_log_nopod = "<font color=yellow><b>Sul ei olnud p&auml;&auml;stekapslit. Sa hukkusid.</b></font>";
$l_log_log = "M&auml;ngija [player] logi";
$l_log_start = "Sissekanded:";
$l_log_end = "Logi l&otilde;pp:";
$l_log_click = "Vajuta <A HREF=main.php><font color=#00ff00>siia</font></A> et minna peamen&uuml;&uuml;sse.";
$l_log_select = "Sélectionnez une news:";
$l_log_general = "Journal général";
$l_log_dig = "Dignitaire Log";
$l_log_spy = "Spy Log";
$l_log_disaster = "Planet catastrophes Log";
$l_log_nova = "Nouvelle Device Log";
$l_log_attack = "Connectez-attaque";
$l_log_scan = "Scan Log";
$l_log_starv = "Planet Starvation Log";
$l_log_probe = "Connectez-Probe";
$l_log_autotrade = "Auto commerce des grumes";
$l_log_combined = "Combined Log";

$l_log_text["LOG_LOGIN"] = "Logisid sisse aadressilt [ip].";
$l_log_title["LOG_LOGIN"] = "Sisse logimine";
$l_log_text["LOG_LOGOUT"] = "Logisid v&auml;lja aadressilt [ip].";
$l_log_title["LOG_LOGOUT"] = "V&auml;lja logimine";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] v&otilde;ttis Su laeva sihikule, aga Su piloodioskused ja head mootorid v&otilde;imaldasid Sul vaenlase eest &auml;ra lennata.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "P&otilde;genemine!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Su sensorid avastasid, et m&auml;ngija [player] relvad &uuml;rituvad Su laevale lukustuda, aga Su radarisegajad suutsid vaenlase primitiivseid sensoreid lollitada.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Segamine &otilde;nnestus!";
$l_log_text["LOG5_ATTACK_EWD"] = "Sind tabas m&auml;ngija [player] reeturlik r&uuml;nnak. Sa j&otilde;udsid veel n&auml;ha vaenlase l&otilde;hkepeade l&auml;henemist, enne kui Sa h&auml;daabi varbi nupule vajutasid. Maailm &auml;hmastus korraks, ja Sa arvasid, et Sa oledki juba surnud. Kui Sa l&otilde;puks ikkagi silmad avasid, n&auml;gid Sa, et Su laev on turvaliselt mujale kantud. Aga kuhu, seda Sa ei tea...";
$l_log_title["LOG5_ATTACK_EWD"] = "H&auml;daabi varp!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Su sensorid avastasid, et m&auml;ngija [player] laev on Su sihikule v&otilde;tnud. \"Parem laev varpida kui p&auml;&auml;stekapsel Sol-i parkida,\" m&otilde;tlesid Sa h&auml;daabi varbi nuppu vajutades. Mootoriruumist kostis imelik heli ja Sa tundsid p&otilde;leva isolatsiooni l&otilde;hna. \"K****i varp v&otilde;i asi!\", karjatasid Sa, pekstes vaest pardaarvutit. Arvuti piiksus suurest pahameelest, kuid Sa olid sunnitud valmistuma l&auml;henevaks v&otilde;itluseks ja ei kuulanud seda enam...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] = "H&auml;daabi varp <font color=red>ei t&ouml;&ouml;tanud!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "[player] r&uuml;ndas Su laeva. Proovisid, mis Sa proovisid, Sa ei suutnud t&otilde;rjuda m&auml;ngija [player] superrelvi. Su laev purustati. ";
$l_log_title["LOG5_ATTACK_LOSE"] = "<font color=red>Lahing kaotatud!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "[player] r&uuml;ndas Su laeva. P&auml;rast l&uuml;hikest v&otilde;itlust lahingutegevus peatus. Sa kaotasid [armor] soomusepunkti ja [fighters] h&auml;vitajat.";
$l_log_title["LOG5_ATTACKED_WIN"] = "<font color=yellow>T&uuml;hi v&otilde;itlus</font>";
$l_log_text["LOG5_HIT_MINES"] = "Sa p&otilde;rkasid vastu [mines] miini, kui Sa liikusid sektoris [sector].";
$l_log_title["LOG5_HIT_MINES"] = "<font color=yellow>Miinihoiatus!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Su laev h&auml;vis miiniv&auml;ljal sektoris [sector]. ";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] = "<font color=red>Miiniv&auml;li!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "[name] alistas Su planeedi [planet_name] sektoris [sector]. &Otilde;nneks olid sealsed elanikud Sulle nii lojaalsed, et otsustasid ennast pigem koos planeediga h&auml;vitada kui et langeda sellise j&otilde;hkardi meelevalda. Sa organiseerisid suure matuseteenistuse, et m&auml;lestada neid vapraid inimesi, kes end koos planeediga ohverdasid.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] = "<font color=yellow>Planeet h&auml;vitatud!</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Nurjatu [name] alistas Su planeedi [planet_name] sektoris [sector]. Planeedi elanikud lausa tervitasid oma uut valitsejat! Sa kuulsid FNN teadet: \"Saime ometi l&otilde;puks sellest vanast tolast lahti! Meile ei meeldi valitsejad, kes meid kaitsta ei suuda!\". Sa vandusid, et nad veel maksavad oma jultumuse eest...";
$l_log_title["LOG5_PLANET_DEFEATED"] = "<font color=red>Planeet alistatud!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "[name] r&uuml;ndas Su planeeti [planet_name] sektoris [sector]. Planeedi elanikud osutasid sissetungijale ennast&uuml;letavat vastupanu ja suutsid m&auml;ngija [name] laeva h&auml;vitada. Rusudest &otilde;nnestus neil isegi midagi k&auml;tte saada : [goods] tarbekaupa, [ore] maaki, [organics] orgaanikat ja [salvage]% laevast v&auml;&auml;rtusega [credits] raha.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "V&otilde;it!";
$l_log_title["LOG5_AFTER_ACTION"] = "Après l&#39;action Rapport de combat";
$l_log_title["LOG0_RAW"] = "Teade:";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] purustati sektoris [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Sektori kaitsed purustatud";
$l_log_text["LOG0_PLANET_EJECT"] = "Sind sunniti sektoris [sector] planeedilt lahkuma, sest [name] lahkus liidust.";
$l_log_title["LOG0_PLANET_EJECT"] = "V&auml;lja visatud!";
$l_log_text["LOG0_BADLOGIN"] = "Viga sisse logimisel aadressilt [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Viga sisse logimisel";
$l_log_text["LOG6_PLANET_SCAN"] = "[name] skaneeris Su planeeti [planet_name] sektoris [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planeet skaneeritud";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] &uuml;ritas skaneerida Su planeeti [planet_name] sektoris [sector], aga ei saanud midagi teada.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planeeti &uuml;ritati skaneerida";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] skaneeris Su laeva.";
$l_log_title["LOG6_SHIP_SCAN"] = "Laev skaneeritud";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] &uuml;ritas skaneerida Su laeva, aga ei saanud midagi teada.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Laeva &uuml;ritati skaneerida";
$l_log_text["LOG5_KABAL_ATTACK"] = "R&uuml;ndan m&auml;ngijat [player]...";
$l_log_title["LOG5_KABAL_ATTACK"] = "R&uuml;nnak";
$l_log_text["LOG7_STARVATION"] = "Planeet [name] sektoris [sector] ei suuda oma elanikkonda toita! Vajatakse rohkem orgaanikat. [starvation] kolonisti suri n&auml;lga. Colonists started starving on [date].";
$l_log_title["LOG7_STARVATION"] = "<font color=yellow>N&auml;ljah&auml;da!</font>";
$l_log_title["LOG0_TOW"] = "V&auml;lja t&otilde;stetud!";
$l_log_text["LOG0_TOW"] = "Votre navire a été remorqué de secteur [sector] de secteur [newsector] parce que votre niveau de technologie moyenne a dépassé la valeur limite de [hull] ou si vous avez un bateau dans le stockage.";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Sa purustasid [fighters] h&auml;vitajat sektoris [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "H&auml;vitajad purustatud";
$l_log_text["LOG5_DEFS_KABOOM"] = "H&auml;vitajad purustasid Su laeva sektoris [sector]. ";
$l_log_title["LOG5_DEFS_KABOOM"] = "<font color=red>Laev purustatud!</font>";
$l_log_text["LOG0_HARAKIRI"] = "Sa t&uuml;dinesid sellest m&auml;ngust ja leidsid, et galaktika n&auml;eb ilma Sinuta parem v&auml;lja. Seega - Sa h&auml;vitasid oma laeva. Kinnitatud aadressilt [ip].";
$l_log_title["LOG0_HARAKIRI"] = "<font color=red>Eneseh&auml;vitus!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] keeldus Su liiduga [teamname] &uuml;hinemast.";
$l_log_title["LOG0_TEAM_REJECT"] = "Kutse tagasi l&uuml;katud";
$l_log_text["LOG0_TEAM_RENAME"] = "Sa nimetasid oma liidu &uuml;mber. Uueks nimeks sai [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Liit &uuml;mber nimetatud";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Sinu liidu koordinaator nimetas liidu &uuml;mber. Uueks nimeks sai [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Liit &uuml;mber nimetatud";
$l_log_text["LOG0_TEAM_KICK"] = "Sind visati liidust [team] v&auml;lja.";
$l_log_title["LOG0_TEAM_KICK"] = "Liidust v&auml;lja visatud!";
$l_log_text["LOG0_TEAM_CREATE"] = "Sa oled loonud uue liidu [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Uus liit loodud";
$l_log_text["LOG0_TEAM_LEAVE"] = "Sa oled lahkunud liidust [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Liidust lahkunud";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Sa oled lahkunud liidust [team]. Sa andsid koordinaatori vastutusrikka rolli &uuml;le m&auml;ngijale [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Liidust lahkunud";
$l_log_text["LOG0_TEAM_LEAD"] = "Su liidu [team] koordinaator otsustas liidust lahkuda. Sind on m&auml;&auml;ratud tema vastutusrikkale ametikohale.";
$l_log_title["LOG0_TEAM_LEAD"] = "Ametik&otilde;rgendus!";
$l_log_text["LOG0_TEAM_JOIN"] = "Sa &uuml;hinesid liiduga [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "&Uuml;hinenud liiduga";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] n&otilde;ustus &uuml;hinema liiduga [team]. J&auml;lle &uuml;ks kivi galaktika &uuml;lemv&otilde;imu m&uuml;&uuml;ris!";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Uus liige";
$l_log_text["LOG0_TEAM_INVITE"] = "Sind on kutsutud &uuml;hinema liiduga [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Kutse";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] lahkus Su liidust.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Liit kaotas &uuml;he liikme";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] tegi aadressilt [ip] eneseh&auml;vituse.";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Eneseh&auml;vitus";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "M&auml;ngijal [player] oli [quantity] [type], maksimaalselt suutis ta kanda [holds].";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Lubamatu kogus laeval";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] &uuml;ritas vallutada m&auml;ngija [defender] planeeti sektoris [sector]. Elanikud h&auml;vitasid planeedi.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planeet h&auml;vitatud";
$l_log_text["LOG0_defense_DEGRADE"] = "Sektori kaitse h&auml;vitajad sektoris [sector] v&auml;henesid [degrade] protsenti energianappuse t&otilde;ttu.";
$l_log_title["LOG0_defense_DEGRADE"] = "<font color=yellow>Sektori kaitseid v&auml;hem!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Sa alistasid planeedi, mille omanik oli [owner]. Sellel oli [cols] kolonisti ja [credits] raha.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planeet alistatud!";
$l_log_text["LOG0_CHEAT_TEAM"] = "M&auml;ngija [player] IP-aadressilt [ip] &uuml;ritas kedagi v&otilde;&otilde;rast liidust v&auml;lja visata. Tema laev h&auml;vitati!";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Sa said k&auml;tte [amount] raha suuruse pearaha, kuna purustasid m&auml;ngija [bounty_on] laeva. Pearaha oli v&auml;lja pannud [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Pearaha k&auml;tte saadud";
$l_log_text["LOG0_BOUNTY_PAID"] = "Su pearaha m&auml;ngija [bounty_on] eest on summas [amount] v&auml;lja makstud.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "La prime Fedration sur [bounty_on] a été taxé pour un montant de [amount] crédits.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Pearaha v&auml;lja makstud";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Su pearaha m&auml;ngija [bounty_on] eest summas [amount] raha on Sulle tagastatud.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Pearaha tagasi makstud";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "F&ouml;deratsioon on Su laeva eest [amount] suuruse pearaha v&auml;lja pannud.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "F&ouml;deratsiooni pearaha!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "L&#39;Alliance a placé une prime sur vous pour le montant de [amount] crédits.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliance de Bounty!";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] [planetname] ([planetid]) détenus par [owner] est devenu indépendant. Moyenne Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet allé indépendant.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Planète indépendante [planetname] ([planetid]) détenus par [owner] de [sector] a été purgé. Moyenne Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Independent Planet purgé.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Jamais planète Owned [planetname] ([planetid]) a créé le [date] au [sector] a été purgé. Moyenne Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Jamais possédé Planet purgé.";

$l_log_text["LOG0_IGB_TRANSFER1"] = "M&auml;ngija [name] kandis Su pangakontole üle [sum] raha.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Raha &uuml;le kantud";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Sa kandsid m&auml;ngija [name] pangakontole [sum] raha.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Raha &uuml;le kantud";

$l_log_text["LOG4_PLANET_novaED_D"] = "Votre planète [planet_name] dans le secteur [sector] a été détruit par une bombe Nova par [name]. Absolument rien ne reste pour marquer les planètes existence antérieure.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Votre navire a été détruit avec une Bombed Nova par [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Votre numéro de dignitaire [DIG] sur la planète [PLANET] a été pris détourné. Vous voudrez peut-être de les licencier.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";
$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Détecté entrants Ship";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>
Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>
Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>
Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Scanned Probe entrants Ship";
$l_log_text["LOG0_TEAM_CANCEL"] = "Vous êtes invité à faire partie de [team] a été annulée.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Invitation annulée";
$l_log_text["LOG10_AUTOTRADE"]="<font color=yellow>Auto Trade for [planetname] in sector [sector] for [totalcost] credits.<br>Goods: [goodsamount] @ [goodsprice] credits - Ore: [oreamount] @ [oreprice] credits - Organics: [organicsamount] @ [organicsprice] credits - Energy: [energyamount] @ [energyprice] credits - Colonists: [colonistamount] @ [colonistprice] credits<br></font>";
$l_log_title["LOG10_AUTOTRADE"] = "Rapport sur le commerce automobile";
$l_log_text["LOG10_AUTOTRADE_ABORTED"]="<font color='#00ff00'>Auto Trade for [planetname] in sector [sector] was aborted due to enemy sector defense in sector [destsector].<br></font>";
$l_log_title["LOG10_AUTOTRADE_ABORTED"] = "Rapport sur le commerce automobile";
$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SECTOR defenseS in [sector] destroy your probe.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] = "Probe Destroyed";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>You do not have enough turns for probe [probe_id] to move to [sector]</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] = "Rapport Probe";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"]="<font color='#00ff00'>Moving to sector [target_sector] is not allowed</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] = "Rapport Probe";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Probe [probe_id] in sector [sector] detected [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] Probe Report";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

// added

$l_log_text["LOG2_SPY_NEWSHIP"] = "Vous avez perdu votre espion [id] sur le vaissau [shipname] appartenant à [name], parce que le joueur a acheter un nouveau vaissau.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Espion perdu!</font>";

$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] a essayer d'envoyer un espion sur votre planète [planet_name] dans le secteur [sector], mais vos détecteur l'on détecter et maintenant il est mort.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Espion enemi tuer!</font>";

$l_log_text["LOG2_SPY_SABOTAGE"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a comencer le sabotage. La production décroit par [data] sur cette planète.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage commencer!</font>";

$l_log_text["LOG2_SPY_BIRTH"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a comencer à réduire les naisance de [data] sur cette planète.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Réduction des naissances!</font>";

$l_log_text["LOG2_SPY_INTEREST"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a comencer a colecter les intérets de la planète de [data] pour vous.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Vols des intérets!</font>";

$l_log_text["LOG2_SPY_MONEY"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a voler [data] crédits pour vous!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Crédits volés!</font>";

$l_log_text["LOG2_SPY_TORPS"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a détruit [data] torpies de la planète!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpilles détruites!</font>";

$l_log_text["LOG2_SPY_FITS"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a détruit [data] intercepteurs de la planète!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Intercepteurs détruits!</font>";

$l_log_text["LOG2_SPY_CPTURE"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] a capturer cette planète pour vous!! Vous êtes content de lui...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>planète CAPTUREE!</font>";

$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "Un espion de [name] a capturer votre planète [planet_name] dans le secteur [sector]! Il pense que ce sera plus facile de récuperer vos planète plus fréquement...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planète perdue!</font>";

$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Vous n'avez pas reçu de message de votre espion [id] sur la planète [planet_name] dans le secteur [sector] depuis un moment - Vous pensez que votre camouflage n'as pas été suffisant et qu'il a été tuer.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Espion perdu!</font>";

$l_log_text["LOG2_SPY_KILLED"] = "Vos détecteurs ont détecter un espion à [name] sur votre planète [planet_name] dans le secteur [sector]. L'espion et mort maintenant.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";

$l_log_text["LOG2_SHIPSPY_KILLED"] = "Vous n'avez pas reçu de message de votre espion [id] sur le vaissau [shipname] du joueur [name] depuis un moment - Vous pensez que votre camouflage n'as pas été suffisant et qu'il a été tuer.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Espion perdu!</font>";

$l_log_text["LOG2_SPY_CATACLYSM"] = "Votre espion [id] sur la planète [planet_name] dans le secteur [sector] est mort dans un terrible cataclisme avec cette planète.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Espion perdu!</font>";

$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Votre espion [id] sur le vaissau [shipname] du joueur [name] est mort dans un terrible cataclisme avec ce vaissau.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";

$l_log_text["LOG2_SPY_TOSHIP"] = "Votre espion [id] de la planète [planet_name] dans le secteur [sector] a infiltrer le vaissau [shipname] du joueur [playername] et agit maintenant là.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Infiltration d'un vaissau enemi!</font>";

$l_log_text["LOG2_SPY_TOPLANET"] = "Votre espion [id] sur le vaissau [shipname] de [playername] a infiltrer la planète [planet_name] dans le secteur [sector] et agit maintenant là.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Infiltration d'une planète enemie!</font>";

$l_log_text["LOG5_PLANET_YOUR_CAPTURED"]   = "Votre planète [planet_name] dans le secteur [sector] a été vaincue par [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planète capturée!</font>";
$l_log_text["LOG5_STORAGE_EWD"] = "Votre planète est surpris par [player] &#39;s attaque. Un de vos navires stockés fait une urgence à Warp [sector] et a atterri sur la planète [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Stockées Ship chaîne d&#39;urgence!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "Un dispositif d&#39;urgence habituellement stockés Warp FAILED! Le navire a été capturé par stockées [player] après avoir défait ta planète!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "Un navire stockée a été capturé par [player] après avoir battu l&#39;un de vos planètes!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";

$l_log_text["LOG1_DIG_PRODUCTION"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] commence la construction de la production.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] taux de natalité baisse.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] taux de natalité croissant.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] commencé à chercher des regards indiscrets, sur cette planète.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] commence à accroître la production de crédit.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Dignitaire [id] sur la planète [planet_name] détournés [data] des crédits et des dons à vous!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Votre lecteur dignitaire détectés [name] &#39;s espion sur votre planète [planet_name] dans le secteur [sector]. L&#39;espion est tué maintenant.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Votre creuser [id] sur la planète [planet_name] dans le secteur [sector] ont péri dans un cataclysme terrible avec cette planète.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Votre creuser [id] le joueur [name] &#39;s navire [shipname] péri dans un cataclysme terrible avec ce navire.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] bâti [data] planétaires torpilles!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Votre ID dignitaire [id] sur la planète [planet_name] dans le secteur [sector] bâti [data] combattants planétaire!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

$l_log_text["LOG5_PLANET_BOMBED"] = "Votre planète [planet_name] dans le secteur [sector] a été bombardée par [name]. vous utilisez [beams] énergie et [torps] torpille pour votre défence.  Vous avez perdu [figs] intercepteurs.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>planète bombardée!</font>";


$l_log_text["LOG5_SM_ATTACK"] = "Ship capteurs a détecté une entrants secteur des missiles de feu venant de [sector] par [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "Un missile tiré par le secteur [player] a été repéré dans le secteur de la déformation et vous éludé l&#39;attaque.";
$l_log_title["LOG5_SM_OUTMAN"] = "Secteur des missiles man?uvre d&#39;évitement!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Vous détectés [player] &#39;est un secteur des missiles entrants tentent de fixer sur votre vaisseau, mais votre générateurs manteau réussi à tromper les circuits de capteur Missiles Secteur.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Secteur des missiles Cloak réussie!";
$l_log_text["LOG5_SM_EWD"] = "Vous êtes surpris par [player] &#39;s Secteur attaque de missiles et de s&#39;engager d&#39;urgence Warp Device saut vers un secteur inconnu.";
$l_log_title["LOG5_SM_EWD"] = "Secteur des missiles de chaîne d&#39;urgence!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Votre capteurs détectent [player] &#39;s secteur d&#39;attaque de missiles et enclencher le dispositif d&#39;urgence Warp. Vous entendez un bruit étrange venant de la chambre d&#39;étouffement des moteurs et l&#39;odeur de brûlé circuits. &quot;Stupid morceau de merde!&quot;, Tu cries, coups de pied à l&#39;ordinateur. Vous préparer à l&#39;impact!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Votre navire a été attaqué par [player] utilisant un missile Secteur. Vous avez perdu [armor] points d&#39;armure et [energy] les unités d&#39;énergie énergie dans l&#39;attaque.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Votre navire a été détruit par un missile Secteur de [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat lost!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Votre navire a été confisqué par [player]. Ne aux attaques sur les joueurs excessifs Bounty le joueur [player] a confisqué un de vos navires ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "Un bateau stocké suicidé lorsque [player] défait l&#39;un de vos planètes et essayé de le capturer!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";
$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Votre navire a été attaqué par une sonde de la propriété de [player] dans le secteur [sector]. Vous avez perdu [armor] points d&#39;armure et [energy] les unités d&#39;énergie énergie dans l&#39;attaque.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] a survécu à une attaque par votre sonde dans le secteur [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Votre sonde a détruit le navire appartenant à [player] dans le secteur [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Votre navire a été détruit par une sonde à partir de [player] dans le secteur [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Votre planète a été confisquée par [player]. Ne aux attaques sur les joueurs excessifs Bounty le joueur [player] a confisqué un de vos planètes ([name]) dans le secteur [sector] valeur [score] crédits.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";


$l_log_title["LOG0_ADMIN_DBERROR"] = "Base de données erreur s&#39;est produite";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Action Résultat";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] a tenté de balayer une de vos sondes dans le secteur [sector], mais a échoué.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "Un de vos sondes dans le secteur [sector] a été scannée par [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "Un de vos sondes dans le secteur [sector] a été attaqué et détruit par [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "L&#39;un de vos chasseurs Probe a détruit une probe_type [probe_type] appartenant à [name] de [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe Hunter détruits [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Votre [probe_type] dans le secteur [sector] a été attaqué et détruit par un chasseur de Probe détenue par [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Votre sonde Hunter dans le secteur [sector] a été perdue lors de l&#39;explosion résultant de son attaque contre le probe_type [probe_type] appartenant à [name] enveloppait.";
$l_log_title["LOG9_PROBEHUNTER_EXPLODED"] 		= "Probe Hunter Probe <font color='yellow'>Destroyed</font>";

?>
