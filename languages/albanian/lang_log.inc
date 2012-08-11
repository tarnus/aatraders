<?php
$l_log_months = "array ( &#39;,, janar&#39;, &#39;Shkurt&#39;, &#39;Mars&#39;, &#39;Prill&#39;, &#39;Maj&#39;, &#39;Qershor&#39;, &#39;Korrik&#39;, &#39;Gusht&#39;, &#39;Shtatore&#39;, &#39;Tetore&#39;, &#39;Nëntore&#39;, &#39;Dhjetore&#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;Shkurt&#39;, &#39;Mars&#39;, &#39;Prill&#39;, &#39;Maj&#39;, &#39;Qershor&#39;, &#39;Korrik&#39;, &#39;Gusht&#39;, &#39;shtator&#39;, &#39;Tetor&#39;, &#39;Nëntor&#39;, &#39;dhjetor&#39;)";
$l_log_pod = "Për fat të mirë, keni pasur një mbulesë shpëtuar!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s Identifikohu";
$l_log_start = "Log hyrjes për";
$l_log_end = "Fundi i hyrjes grisjeve për";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Zgjidh një Log:";
$l_log_general = "Përgjithshëm Identifikohu";
$l_log_dig = "Dignitary Identifikohu";
$l_log_spy = "Spiun Identifikohu";
$l_log_disaster = "Planet Disaster Identifikohu";
$l_log_nova = "Nova Device Identifikohu";
$l_log_attack = "Sulmi Identifikohu";
$l_log_scan = "Scan Identifikohu";
$l_log_starv = "Planet uria Identifikohu";
$l_log_probe = "Hetim Identifikohu";
$l_log_autotrade = "Auto Trade Identifikohu";
$l_log_combined = "Kombinuar Identifikohu";


// Log entry data

$l_log_text["LOG_LOGIN"] = "Ju keni hyrë brenda, nga [ip].";
$l_log_title["LOG_LOGIN"] = "Loguar";
$l_log_text["LOG_LOGOUT"] = "Ju keni futur jashtë, nga [ip].";
$l_log_title["LOG_LOGOUT"] = "Logged out";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Database Error Occurred";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Rezultati i Veprimit";
$l_log_title["LOG0_RAW"] = "Njoftim";
$l_log_text["LOG0_PLANET_EJECT"] = "Ju keni qenë ejected nga planet në sektorin [sector] sepse [name] la ekip.";
$l_log_title["LOG0_PLANET_EJECT"] = "Ejected!";
$l_log_text["LOG0_BADLOGIN"] = "Ka qenë një përpjekje e keqe hyrje nga [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Login Bad";
$l_log_title["LOG0_TOW"] = "Towed!";
$l_log_text["LOG0_TOW"] = "Anija juaj ka qenë towed nga sektori [sector] ndaj sektorit [newsector], sepse niveli mesatar tuaj tek tejkaluar vlera limit e [hull] ose keni një anije në ruajtje.";
$l_log_text["LOG0_HARAKIRI"] = "Ju keni qenë të lodhur nga captaining këtë ndesh hapësirë, kështu që ju vendosur universi do të ishte më mirë pa të. Autorizuar nga [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] i ka hedhur poshtë ftesën për t&#39;u bashkuar ekipit tuaj, [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Ftesë poshtë";
$l_log_text["LOG0_TEAM_RENAME"] = "Ju keni riemëruar ekipin tuaj të [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Ekipi i riemëruar";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Koordinatori i juaj ekip u quajt ekipi të [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Ekipi i riemëruar";
$l_log_text["LOG0_TEAM_KICK"] = "Ju keni qenë ejected nga ekipi [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Ejected nga ekipi!";
$l_log_text["LOG0_TEAM_CREATE"] = "Ju keni krijuar një ekip të ri, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Created ekip i ri";
$l_log_text["LOG0_TEAM_LEAVE"] = "Ju kanë lënë ekip [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Ekipi Majtas";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Ju kanë lënë ekipi [team]. Ju relinquished udhëheqjes ekip të [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Ekipi Majtas";
$l_log_text["LOG0_TEAM_LEAD"] = "Koordinatori ekipi juaj ka vendosur të largohet nga [team]. Ju keni qenë caktuar për të marrë vendin e saj.";
$l_log_title["LOG0_TEAM_LEAD"] = "Promovimi!";
$l_log_text["LOG0_TEAM_JOIN"] = "Ju keni bashkuar ekipit [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Joined ekip";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] ka pranuar për t&#39;u bashkuar me [team]. Kjo ju sjell një hap më tej në dominimin galaktik.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Anëtar i ri ekipit";
$l_log_text["LOG0_TEAM_INVITE"] = "Ju keni qenë i ftuar të jetë pjesë e [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Ftesë";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] ka lënë ekipin tuaj.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Ekipi i humbet një anëtar";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] ka vetë-destructed nga ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Vetë-destruct";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] kishte [quantity] Sasia [type], me max mban të [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Vlera e paligjshme anije";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] është përpjekur për të kapur [defender] &#39;s planetin në sektorin [sector]. Planet ishte shkatërruar në vend.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet shkatërruar";
$l_log_text["LOG0_defense_DEGRADE"] = "Sektori mbrojtëse Fighters në sektorin [sector] degraduar nga [degrade] qind të energjisë për shkak të pamjaftueshme.";
$l_log_title["LOG0_defense_DEGRADE"] = "Mbrojtëse Sektori i degraduar.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Player [player] në adresën IP [ip] u përpoq për të shfrytëzuar dikush gjuajtje ekip mashtrojnë. Anija e tij u shkatërrua.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Team Used Exploit";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Ju pohoi një dhuratë prej [amount] kredi për shkatërrimin e anijes që i përkasin [bounty_on]. Dhuratë ishte vendosur nga [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Mirat e pohoi.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Mirat e juaj në [bounty_on] ka qenë paguar për shumën prej [amount] credits.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Paid mirësisë.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "Dhuratë Fedration në [bounty_on] ka qenë taksohen për shumën prej [amount] kredi.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Tatimore mirësisë Paid.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Mirat e juaj në [bounty_on] për shumën prej [amount] kredive ka qenë kthehet.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty kthehet.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "Federata ka vendosur një dhuratë për ju për shumën prej [amount] credits.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federata mirat!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Aleanca ka vendosur një dhuratë për ju për shumën prej [amount] kredi.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Aleanca mirat!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Kredi Player [name] transferohet [sum] të IGB llogarinë tuaj.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Kredite transferuar";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Ju transferohet [sum] kredi për player [name] &#39;s llogari IGB.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Kredite transferuar";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] [planetname] ([planetid]) në pronësi nga [owner] u bë e pavarur. Average Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet shkoi pavarur.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Planet e Pavarur [planetname] ([planetid]) në pronësi nga [owner] në [sector] ishte purged. Average Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Planet Pavarur Purged.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Asnjëherë planet Owned [planetname] ([planetid]) e krijuar në [date] në [sector] ishte purged. Average Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Asnjëherë Owned Planet Purged.";
$l_log_text["LOG0_TEAM_CANCEL"] = "Ju jeni ftesë të jetë pjesë e [team] ka qenë i anuluar.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Ftesë anuluar";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] fillon ndërtimin e prodhimit.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] përqindje e lindjeve në rënie.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] përqindje e lindjeve në rritje.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] filloi në kërkim për spys në këtë planet.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] fillon rritja e prodhimit të kredisë.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Dignitary [id] në planetin [planet_name] shpërdoruar [data] kredi dhe dhuruar për ju!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Lojtar dignitary juaj zbuluar [name] &#39;s spiun në planetin tuaj [planet_name] në sektorin [sector]. Spiuni është vrarë tashmë.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Dig juaj [id] në planetin [planet_name] në sektorin [sector] zhdukur në një përmbytje e tmerrshme me atë planet.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Dig juaj [id] më player [name] &#39;s anije [shipname] zhdukur në një përmbytje e tmerrshme me atë anije.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] ndërtuar [data] planetare silurët!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Dignitary juaj [id] në planetin [planet_name] në sektorin [sector] ndërtuar [data] luftëtarë planetar!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Ju humbur spiun tuaj [id] në [name] &#39;s anije [shipname], për shkak se një lojtar i blerë anije të reja.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] u përpoq që të dërgoni një spiun për të planetit tuaj [planet_name] në sektorin [sector], por Sensore tuaj zbuluar spiun dhe ai është vrarë tashmë.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] fillon sabotim. Prodhimi është ulur nga [data] në këtë planet.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] përqindje e lindjeve u ul nga [data] në këtë planet.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] fillon mbledhjen e interesit planetit nga [data] për ju.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] vodhi [data] kredi për ju!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] shkatërruar [data] planetare silurët!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] shkatërruar [data] luftëtarë planetar!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] kapur se planetit!! Ju jeni një djalë me fat ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] &#39;s spiun kapur planetin tuaj [planet_name] në sektorin [sector]! Duket se kjo është ideja e mençur për pastrim planetet tuaj më shpesh ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Nuk ka mesazhe nga spiun i juaj [id] në planetin [planet_name] në sektorin [sector] për një kohë të gjatë - duket se pajisja mantel juaj nuk mund të mbulojnë atë të mjaftueshme dhe ai është vrarë.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Sensore juaj zbuloi një emër [name] &#39;s spiun në planetin tuaj [planet_name] në sektorin [sector]. Spiuni është vrarë tashmë.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "Nuk ka mesazhe nga spiun i juaj [id] më player [name] &#39;s anije [shipname] për një kohë të gjatë - duket se pajisja mantel juaj nuk mund të mbulojnë atë të mjaftueshme dhe ai është vrarë.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Spiun juaj [id] në planetin [planet_name] në sektorin [sector] zhdukur në një përmbytje e tmerrshme me atë planet.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Spiun juaj [id] më player [name] &#39;s anije [shipname] zhdukur në një përmbytje e tmerrshme me atë anije.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Spiun juaj [id] nga planet [planet_name] në sektorin [sector] infiltrates një lojtar [playername] &#39;s anije [shipname] dhe aktet tani atje.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Spiun juaj [id] nga player [playername] &#39;s anije [shipname] infiltrates një planet [planet_name] në sektorin [sector] dhe aktet tani atje.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Numri i juaj dignitary [DIG] në planetin [PLANET] është kapur për shpërdorimin. Ju mund të dëshironi të shkarkuar ato.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Planeti juaj [planet_name] në sektorin [sector] ishte shkatërruar me një bombë Nova nga [name]. Absolutisht asgjë nuk mbetet për të shënuar planetet e ish ekzistencës.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Anija juaj është shkatërruar me një Nova ku shpërtheu bomba nga [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Planeti juaj [planet_name] në sektorin [sector] u bombarduan nga [name]. Ju përdorur [beams] energji dhe [torps] silurët në mbrojtje tuaj. Ju humbur [figs] luftëtarë.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Planeti juaj [planet_name] në sektorin [sector] ishte i mundur dhe pushtua nga fatkeq [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] ishte i ndotur në një vektor sulmi, por aftësitë e madhe tuaj pilote dhe makina të mira që ju lejohet që të ia hedh armikut.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Veprim i paqartë!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Ju zbulohen [player] &#39;s armë duke u përpjekur për të rregulluar në anije tuaj, por gjeneratorëve tuaj mantel arritur të luaj qarqeve primitive armikut sensor.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Mantel i suksesshëm!";
$l_log_text["LOG5_ATTACK_EWD"] = "Ju jeni habitur nga [player] &#39;s sulm të pabesë. Ju mund të shihni mbushjet e ardhshëm si keni arritur çmendurisht për prishje butonin jashtëzakonshme. Blurs bota rreth jush dhe, për një milisecond, ju mendoni se ju jeni të vdekur. Kur ju më në fund hapur sytë tuaj, ju shihni se ju u transportuan të sigurtë tjetërkund. Por ku pikërisht, ju nuk e dini ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Prishje e urgjencës!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Sensorë juaj zbuluar [player] &#39;s anija në një vektor sulmi. &quot;Më i mirë të jetë e sigurt se sa keq&quot;, ju mendoni se, duke goditur butonin prish jashtëzakonshme. Ju dëgjuar një tingull të çuditshme që vijnë nga mbytje dhomë motorët dhe erë të djegur circuitry. &quot;Copë Stupid i mut!&quot;, Ju britmë, duke nisur në kompjuter. Kompjuter lëshon Beeps e solemne si ju përgatit për betejën e ardhshëm ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Anija juaj është duke u sulmuar nga [player]. Provoni si ju mund të, ju nuk mund ta mbrojë veten kundër [player] &#39;s armë superiore. Anija juaj është shkatërruar.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Anija juaj u sulmua nga [player]. Ju betejë për një kohë, atëherë lufta prishet. Ju humbur [armor] pikat forca të blinduara dhe [fighters] UÇK-së në luftim.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Ju hit [mines] mina kur udhëtojnë në sektorin [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Anija juaj u shkatërrua nga një fushë të minuar në sektorin [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Planeti juaj [planet_name] në sektorin [sector] u mund në luftë nga [name]. Për fat të mirë, besnikërinë e fortë e qytetarëve tuaj luajtur në favor tuaj. Ata kanë zgjedhur me guxim për të shkatërruar planetin në vend se kanë ra në duart e armikut. Ju organizojnë funeralet shkëlqyer në kujtesën e popullit tuaj besnik.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Planeti juaj [planet_name] në sektorin [sector] u mund në luftë nga fatkeq [name]. Njerëzit e planetit mirëpritur sunduesit e tyre të ri. Ju dëgjoni një dëshmi më FNN: &quot;Ne jemi të gëzuar që do të shpëtoj se pjerdh vjetra, ne nuk duam asnjë humbës i ndyrë i cili nuk mund të na mbrojë!&quot;. Ju betohem për t&#39;i bërë ata paguajnë për arrogancë e tyre.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Planeti juaj [planet_name] në sektorin [sector] u sulmua nga [name]. Qytetarëve të organizuar një mbrojtje valliant megjithatë, dhe ja doli të shkatërrojë kundërshtar. Ata vjedh disa burimeve nga mbeturinat hapësirës: [goods] mallrave, [ore] ore, [organics] Organics dhe [salvage]% të vlerë së anijes [credits] kredi.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Fitore!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] u shkatërruan në sektorin [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Mbrojtëse Sektori i shkatërruar";
$l_log_text["LOG5_KABAL_ATTACK"] = "Sulmuar [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Sulmi";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Ju keni shkatërruar [fighters] luftëtarë të patrullojnë në sektorin [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Luftëtarë të shkatërruar";
$l_log_text["LOG5_DEFS_KABOOM"] = "Ju u shkatërruan nga një forcë UÇK-së në sektorin [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Ju kapën një planet i përket [owner]. Ajo kishte [cols] kolonistët dhe [credits] kredi mbi të.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet kapur!";
$l_log_text["LOG5_STORAGE_EWD"] = "Planeti juaj është i befasuar nga [player] &#39;s sulm. Një nga anijet tuaja ruajtur bërë një Warp urgjencës të [sector] dhe zbarkoi në planetin [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Ruajtur anijes prishje e urgjencës!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "Një anije ruajtur e urgjencës Device Warp Failed! Anija ruajtur u pushtua nga [player] pasi mundi planetit tuaj!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "Një anije ruajtur u pushtua nga [player] pasi mundi një nga planetet tuaj!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Anija juaj ishte konfiskuar nga [player]. A ndaj sulmeve të tepruar ndaj lojtarëve mirat [player] ka konfiskuar një nga anijet e juaj ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Planeti juaj ishte konfiskuar nga [player]. A ndaj sulmeve të tepruar ndaj lojtarëve mirat [player] ka konfiskuar një nga planetet tuaj ([name]) në sektorin [sector] vlerë [score] credits.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "Një anije ruajtur suicided kur [player] mundi një nga planetet tuaj dhe u përpoqën për të kapur atë!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "Anije Sensore zbuluar një hyrje Sektorin e raketave për shkarkimin nga [sector] nga [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "Një e raketave Sektori i shkarkuar nga [player] u dalloi warping në sektor dhe ju shpëtoi sulmit.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sektori i raketave veprim i paqartë!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Ju zbuluar [player] &#39;s një hyrje Sektorin e raketave duke u përpjekur për të rregulluar më anije tuaj, por gjeneratorëve tuaj mantel arritur të luaj projektilë sensor Sektorin e qarqeve.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sektori i raketave mantel i suksesshëm!";
$l_log_text["LOG5_SM_EWD"] = "Ju jeni habitur nga [player] &#39;s Sektori sulm e raketave dhe të angazhohen Device Warp e urgjencës duke kërcyer në një sektor të panjohur.";
$l_log_title["LOG5_SM_EWD"] = "Sektori i raketave prishje e urgjencës!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Sensorë juaj zbuluar [player] &#39;s Sektori sulm e raketave dhe të angazhohen Device Warp Jashtëzakonshme. Ju dëgjuar një tingull të çuditshme që vijnë nga mbytje dhomë motorët dhe erë të djegur circuitry. &quot;Copë Stupid i mut!&quot;, Ju britmë, duke nisur në kompjuter. Ju shtrëngoj për ndikimin!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Anija juaj u sulmua nga [player] duke përdorur një Sektorin e raketave. Ju humbur [armor] pikat forca të blinduara dhe [energy] njësive të energjisë të energjisë në sulm.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Anija juaj u shkatërrua nga një predhë e Sektorit nga [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Anija juaj u sulmua nga një hetim në pronësi nga [player] në sektorin [sector]. Ju humbur [armor] pikat forca të blinduara dhe [energy] njësive të energjisë të energjisë në sulm.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] shpëtoi një sulmi nga hetimi tuaj në sektorin [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Hetim juaj shkatërruar anije në pronësi nga [player] në sektorin [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Anija juaj u shkatërrua nga një hetim nga [player] në sektorin [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "Pas Action Combat Report";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name] ka skanuar planetin tuaj [planet_name] në sektorin [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet hetim";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] ka tentuar të skanoni planetin tuaj [planet_name] në sektorin [sector], por nuk arriti.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planet scan dështuar";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] ka skanuar anije tuaj.";
$l_log_title["LOG6_SHIP_SCAN"] = "Anije hetim";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] është përpjekur të scan anije tuaj, por dështoi.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Anije scan dështuar";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] në [sector] nuk mund të mbajë popullsisë së saj! Organics Më shumë janë të nevojshme. [starvation] kolonistët vdiq nga uria. Kolonistët filluar ngordhje në [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Hetim zbuluar Incoming Ship";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Hetim skanuar Incoming Ship";
$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SECTOR defenses in [sector] destroy your probe.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] = "Hetim Asgjesuar";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>You do not have enough turns for probe [probe_id] to move to [sector]</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] = "Raporti hetim";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"] = "<font color='#00ff00'>Moving to sector [target_sector] is not allowed</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] = "Raporti hetim";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Probe [probe_id] in sector [sector] detected [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] përpoq të skanoni një nga hetimet tuaj në sektorin [sector], por nuk arriti.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "Një nga hetimet tuaj në sektorin [sector] ishte skanuar nga [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "Një nga hetimet tuaj në sektorin [sector] është sulmuar dhe shkatërruar nga [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "Një nga Gjahtarët hetimin tuaj ka shkatërruar një probe_type [probe_type] në pronësi nga [name] në [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Hetim gjahtari shkatërruar [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Probe_type [probe_type] në sektorin [sector] është sulmuar dhe shkatërruar nga një gjuetar hetimin në pronësi nga [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Gjahtari hetimin juaj në sektorin [sector] është humbur kur shpërthimi që rezultojnë nga sulmet e saj mbi probe_type [probe_type] në pronësi nga [name] mbështjellë atë.";
$l_log_title["LOG9_PROBEHUNTER_EXPLODED"] 		= "Probe Hunter Probe <font color='yellow'>Destroyed</font>";

// Auto Trade Logs

$l_log_text["LOG10_AUTOTRADE"]="<font color=yellow>Auto Trade for [planetname] in sector [sector] for [totalcost] credits.<br>Goods: [goodsamount] @ [goodsprice] credits - Ore: [oreamount] @ [oreprice] credits - Organics: [organicsamount] @ [organicsprice] credits - Energy: [energyamount] @ [energyprice] credits - Colonists: [colonistamount] @ [colonistprice] credits<br></font>";
$l_log_title["LOG10_AUTOTRADE"] = "Auto Raporti i Tregtisë";
$l_log_text["LOG10_AUTOTRADE_ABORTED"]="<font color='#00ff00'>Auto Trade for [planetname] in sector [sector] was aborted due to enemy sector defense in sector [destsector].<br></font>";
$l_log_title["LOG10_AUTOTRADE_ABORTED"] = "Auto Raporti i Tregtisë";

?>
