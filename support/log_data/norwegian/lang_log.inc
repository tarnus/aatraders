<?php
$l_log_months = "array ( &#39;januar&#39;, &#39;Februar&#39;, &#39;Mars&#39;, &#39;April&#39;, &#39;Mai&#39;, &#39;Juni&#39;, &#39;juli&#39;, &#39;August&#39;, &#39;September&#39;, &#39;Oktober&#39;, &#39;november&#39;, &#39;desember&#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;Feb&#39;, &#39;Apr&#39;, &#39;Apr&#39;, &#39;Mai&#39;, &#39;Jun&#39;, &#39;Jul&#39;, &#39;Aug&#39;, &#39;Sep&#39;, &#39;Okt&#39;, &#39;Nov&#39;, &#39;Des&#39;)";
$l_log_pod = "Heldigvis hadde du en flukt pod!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s Log";
$l_log_start = "Logg inn for";
$l_log_end = "Slutt på loggoppføring for";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Velg en Log:";
$l_log_general = "General Log";
$l_log_dig = "Herre Log";
$l_log_spy = "Spy Log";
$l_log_disaster = "Planet Disaster Log";
$l_log_nova = "Nova Device Log";
$l_log_attack = "Attack Log";
$l_log_scan = "Scan Log";
$l_log_starv = "Planet Sult Log";
$l_log_probe = "Probe Log";
$l_log_autotrade = "Auto Trade Log";
$l_log_combined = "Kombinert Log";


// Log entry data

$l_log_text["LOG_LOGIN"] = "Du har logget inn, fra [ip].";
$l_log_title["LOG_LOGIN"] = "Innlogget";
$l_log_text["LOG_LOGOUT"] = "Du har logget ut, fra [ip].";
$l_log_title["LOG_LOGOUT"] = "Logget ut";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Database feil oppstått";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Action Result";
$l_log_title["LOG0_RAW"] = "Merknad";
$l_log_text["LOG0_PLANET_EJECT"] = "Du har blitt kastet ut fra planeten i sektor [sector] fordi [name] forlot teamet.";
$l_log_title["LOG0_PLANET_EJECT"] = "Skyves ut!";
$l_log_text["LOG0_BADLOGIN"] = "Det har vært en dårlig påloggingsforsøket fra [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Bad login";
$l_log_title["LOG0_TOW"] = "Slep!";
$l_log_text["LOG0_TOW"] = "Skipet ditt har blitt slept fra sektor [sector] til sektor [newsector] fordi den gjennomsnittlige tekniske nivået overskredet grenseverdien av [hull] eller du har et skip i magasinene.";
$l_log_text["LOG0_HARAKIRI"] = "Du var lei av captaining denne plassen lekter, slik at du bestemte universet ville være bedre uten. Autorisert av [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] har avvist en invitasjon til å bli med teamet ditt, [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Invitasjon avvist";
$l_log_text["LOG0_TEAM_RENAME"] = "Du har omdøpt laget ditt til [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Team omdøpt";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Ditt team koordinator omdøpt teamet til [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Team omdøpt";
$l_log_text["LOG0_TEAM_KICK"] = "Du har blitt kastet ut av laget [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Kastet ut av laget!";
$l_log_text["LOG0_TEAM_CREATE"] = "Du har opprettet et nytt team, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Opprettet nytt team";
$l_log_text["LOG0_TEAM_LEAVE"] = "Du har forlatt laget [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Venstre team";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Du har forlatt teamet [team]. Du oppga laget ledelsen til [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Venstre team";
$l_log_text["LOG0_TEAM_LEAD"] = "Laget ditt koordinator har besluttet å forlate [team]. Du har blitt utpekt til å ta sin plass.";
$l_log_title["LOG0_TEAM_LEAD"] = "Kampanje!";
$l_log_text["LOG0_TEAM_JOIN"] = "Du har blitt med på laget [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Joined team";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] har akseptert å bli [team]. Dette gir deg et skritt videre til galaktisk herredømme.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Ny medarbeider";
$l_log_text["LOG0_TEAM_INVITE"] = "Du har blitt invitert til å være en del av [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Invitasjon";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] har forlatt laget ditt.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Team mister et medlem";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] har selv destructed fra ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Selvdestrueres";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] hadde [quantity] [type], med maks holder av [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Ulovlig skip verdi";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] har forsøkt å fange [defender] &#39;s planeten i sektor [sector]. Planet ble ødelagt i stedet.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet ødelagt";
$l_log_text["LOG0_defense_DEGRADE"] = "Sector forsvar Fighters i sektor [sector] degradert av [degrade] prosent på grunn av utilstrekkelig energi.";
$l_log_title["LOG0_defense_DEGRADE"] = "Sector forsvar forringet.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Spiller [player] på IP adresse [ip] prøvde å utnytte team kick noen cheat. Hans skip ble ødelagt.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Team Exploit Brukt";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Du hevdet en dusør på [amount] kreditter for ødeleggelse av skipet tilhører [bounty_on]. Bounty ble plassert av [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Bounty hevdet.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Din skuddpremie på [bounty_on] har blitt betalt for mengden [amount] studiepoeng.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Bounty betalt.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "Den Fedration skuddpremie på [bounty_on] har blitt beskattet for mengden [amount] studiepoeng.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Bounty innbetalt skatt.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Din skuddpremie på [bounty_on] for mengden [amount] kreditter er blitt refundert.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty refundert.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "Føderasjonen har plassert en dusør på deg for mye [amount] studiepoeng.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federation Bounty!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliansen har satt en dusør på deg for mye [amount] studiepoeng.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliance Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Spilleren [name] overført [sum] kreditter til IGB konto.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Studiepoeng overføres";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Du overføres [sum] kreditter til spilleren [name] s IGB konto.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Studiepoeng overføres";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] planeten [planetname] ([planetid]) eies av [owner] ble uavhengig. Gjennomsnittlig Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet gikk uavhengig.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Uavhengig planet [planetname] ([planetid]) eies av [owner] i [sector] ble renset. Gjennomsnittlig Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Independent Planet renset.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Aldri Eies planet [planetname] ([planetid]) opprettet på [date] i [sector] ble renset. Gjennomsnittlig Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Aldri Eies Planet renset.";
$l_log_text["LOG0_TEAM_CANCEL"] = "Du er invitasjon til å bli en del av [team] har blitt kansellert.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Invitasjon kansellert";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "Din herre [id] på planeten [planet_name] i sektor [sector] starter bygging produksjon.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Din herre [id] på planeten [planet_name] i sektor [sector] synkende fødselstall.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Din herre [id] på planeten [planet_name] i sektor [sector] økende fødselstall.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Din herre [id] på planeten [planet_name] i sektor [sector] begynte å søke etter spys på denne planeten.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Din herre [id] på planeten [planet_name] i sektor [sector] begynner å øke kreditten produksjon.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Herre [id] på planeten [planet_name] underslåtte [data] kreditter og donert til deg!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Din herre oppdaget spiller [name] s spionere på planeten din [planet_name] i sektor [sector]. Spionen blir drept nå.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Din grave [id] på planeten [planet_name] i sektor [sector] omkom i en forferdelig katastrofen med det planet.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Din grave [id] på spilleren [name] s skip [shipname] omkom i en forferdelig katastrofen med at skipet.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Din herre [id] på planeten [planet_name] i sektor [sector] bygget [data] planetariske torpedoer!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Din herre [id] på planeten [planet_name] i sektor [sector] bygget [data] planetariske jagerfly!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Du mistet din spy [id] på [name] s skip [shipname], fordi at spilleren kjøpte et nytt skip.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] har forsøkt å sende en spion til planeten din [planet_name] i sektor [sector], men Sensorer oppdaget spion, og han blir drept nå.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Din spy [id] på planeten [planet_name] i sektor [sector] starter sabotasje. Produksjonen er redusert med [data] på denne planeten.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Din spy [id] på planeten [planet_name] i sektor [sector] redusert fødselstall av [data] på denne planeten.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "Din spy [id] på planeten [planet_name] i sektor [sector] starter innsamling av planeten interesse av [data] til deg.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Din spy [id] på planeten [planet_name] i sektor [sector] stjal [data] kreditter til deg!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Din spy [id] på planeten [planet_name] i sektor [sector] ødelagt [data] planetariske torpedoer!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Din spy [id] på planeten [planet_name] i sektor [sector] ødelagt [data] planetariske jagerfly!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Din spy [id] på planeten [planet_name] i sektor [sector] fanget at planeten! Du er en heldig fyr ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] s spion fanget ditt planeten [planet_name] i sektor [sector]! Det synes at det er lurt idé til opprydding på planeter oftere ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Det er ingen meldinger fra spion din [id] på planeten [planet_name] i sektor [sector] for lang tid - det synes at kappen enheten ikke kunne dekke seg nok og han er drept.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Din Sensorer oppdaget [name] s spionere på planeten din [planet_name] i sektor [sector]. Spionen blir drept nå.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "Det er ingen meldinger fra spion din [id] på spilleren [name] s skip [shipname] for lang tid - det synes at kappen enheten ikke kunne dekke seg nok og han er drept.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Din spy [id] på planeten [planet_name] i sektor [sector] omkom i en forferdelig katastrofen med det planet.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Din spy [id] på spilleren [name] s skip [shipname] omkom i en forferdelig katastrofen med at skipet.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Din spy [id] fra planeten [planet_name] i sektor [sector] infiltrerer en spiller [playername] &#39;s skip [shipname] og fungerer nå der.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Din spy [id] fra spiller [playername] &#39;s skip [shipname] infiltrerer en planet [planet_name] i sektor [sector] og fungerer nå der.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Ditt herre nummer [DIG] på planeten [PLANET] har blitt fanget underslag. Du ønsker kanskje å avvise dem.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Din planet [planet_name] i sektor [sector] ble ødelagt med en Nova Bomb av [name]. Absolutely nothing gjenstår å markere planetene tidligere eksistens.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Ditt skip ble ødelagt med en Nova bombet av [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Din planet [planet_name] i sektor [sector] ble bombet av [name]. Du brukte [beams] energi og [torps] torpedoer i forsvaret ditt. Du mistet [figs] jagerfly.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Din planet [planet_name] i sektor [sector] ble beseiret og tatt til fange av den elendige [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] ble oppdaget på en angrepsvektor, men stor pilot ferdigheter og gode motorer lov å utmanøvrere fienden.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Unnvikende action!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Du oppdaget [player] &#39;s våpen prøver å fikse på skipet ditt, men kappen generatorer klarte å lure fiendens primitive sensor kretser.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Cloak vellykket!";
$l_log_text["LOG5_ATTACK_EWD"] = "Du er overrasket [player] &#39;s lumske angrep. Du kan se innkommende stridshoder som du nå febrilsk for emergency warp knappen. Verden tåkelegger rundt deg og, for en milisecond, tror du at du er død. Når du endelig åpner øynene, ser du at du ble trygt transportert andre steder. Men hvor nøyaktig, du vet ikke ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Emergency varp!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Din sensorer oppdager [player] &#39;s skip på en angrepsvektor. &quot;Bedre være føre var&quot;, tenker du, treffer nødnummeret warp knappen. Du hører en merkelig choking lyden kommer fra motorer rommet og lukter brent kretser. &quot;Dum piece of crap!&quot;, Yell du sparker på datamaskinen. Datamaskinen avgir piper av protestation som du forberede deg på det innkommende slaget ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Skipet ditt blir angrepet av [player]. Prøv som du kan, kan du ikke forsvare deg mot [player] &#39;s overlegne våpen. Ditt skip ble ødelagt.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Ditt skip ble angrepet av [player]. Du kamp for en stund, så kampen bryter ned. Du mistet [armor] rustning poeng og [fighters] jagerfly i trefningen.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Du treffer [mines] miner når du reiser i sektor [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Ditt skip ble ødelagt av et minefelt i sektor [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Din planet [planet_name] i sektor [sector] ble beseiret i slaget ved [name]. Heldigvis er den sterke lojaliteten til ditt borgere spilt i din favør. De har tappert valgt å ødelegge planeten i stedet har det falle i fiendens hender. Du organisere superb begravelser i minnet på din trofaste mennesker.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Din planet [planet_name] i sektor [sector] ble beseiret i et slag av elendige [name]. Folket i planeten velkommen sin nye hersker. Du hører et vitnesbyrd om FNN: &quot;Vi er glad for å bli kvitt det gamle fart! Ønsker vi ikke noen stinkende taper som ikke kan beskytte oss!&quot;. Du sverger å gjøre dem betale for deres arroganse.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Din planet [planet_name] i sektor [sector] ble angrepet av [name]. Borgerne organiserte en Valliant forsvar imidlertid, og klarte å ødelegge motstanderen. De berge noen ressurser fra verdensrommet rester: [goods] varer, [ore] ore [organics] organiske og [salvage]% av skipets verdi av [credits] studiepoeng.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Victory!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] ble ødelagt i sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Sector forsvar ødelegges";
$l_log_text["LOG5_KABAL_ATTACK"] = "Offensiv [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Attack";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Du har ødelagt [fighters] patruljerende jagerfly i sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Fighters ødelagt";
$l_log_text["LOG5_DEFS_KABOOM"] = "Du ble ødelagt av et jagerfly kraft i sektor [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Du fanget en planet som tilhører [owner]. Det hadde [cols] kolonister og [credits] credits på det.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet captured!";
$l_log_text["LOG5_STORAGE_EWD"] = "Din planeten er overrasket [player] &#39;s angrep. En av de lagrede skip laget en Emergency Warp til [sector] og landet på planeten [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Lagrede Ship Emergency varp!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "En lagret skip Emergency Warp enheten mislyktes! Den lagres skipet ble tatt av [player] etter at de beseiret din planet!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "En lagret skipet ble tatt av [player] etter at de beseiret et av planeter!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Din skipet ble konfiskert av [player]. Må til overdreven angrep på Bounty spillere [player] har beslaglagt ett av skipene ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Din planet ble konfiskert av [player]. Må til overdreven angrep på Bounty spillere [player] har konfiskert en av dine planeter ([name]) i sektor [sector] verdi [score] studiepoeng.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "En lagret skip suicided når [player] beseiret en av planeter og prøvde å fange den!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "Ship Sensorer registrert en innkommende Sector Raketten ble avfyrt fra [sector] av [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "En sektor rakett avfyrt av [player] ble oppdaget fordreining i sektoren, og du unngikk angrepet.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sector Missile Evasive action!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Du oppdaget [player] &#39;s innkommende Sector Missile prøver å fikse på skipet ditt, men kappen generatorer klarte å lure Sector Missiler sensoren kretser.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sector Missile Cloak vellykket!";
$l_log_text["LOG5_SM_EWD"] = "Du er overrasket [player] &#39;s Sector Missile angrep og engasjere Emergency Warp Device hoppe til en ukjent sektor.";
$l_log_title["LOG5_SM_EWD"] = "Sector Missile Emergency varp!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Din sensorer oppdager [player] &#39;s Sector Missile angrep og engasjere Emergency Warp Device. Du hører en merkelig choking lyden kommer fra motorer rommet og lukter brent kretser. &quot;Dum piece of crap!&quot;, Yell du sparker på datamaskinen. Du brace for inntrykk!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Ditt skip ble angrepet av [player] bruker en Sector Missile. Du mistet [armor] rustning poeng og [energy] energi enheter i angrepet.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Ditt skip ble ødelagt av en sektor Missile fra [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Ditt skip ble angrepet av en sonde som eies av [player] i sektor [sector]. Du mistet [armor] rustning poeng og [energy] energi enheter i angrepet.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] overlevde et angrep av sonde i sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Din sonde ødela skipet eid av [player] i sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Ditt skip ble ødelagt av en sonde fra [player] i sektor [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "Etter Action Combat Report";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name] har skannet planeten [planet_name] i sektor [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet scan";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] har forsøkt å skanne planeten [planet_name] i sektor [sector], men mislyktes.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planet scan failed";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] har skannet skipet ditt.";
$l_log_title["LOG6_SHIP_SCAN"] = "Ship scan";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] har forsøkt å skanne skipet, men mislyktes.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Ship scan failed";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] i [sector] ikke kan opprettholde sin befolkning! Flere organiske trengs. [starvation] kolonister døde av sult. Kolonister startet sultende på [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Detected Innkommende Ship";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Probe Skannet Innkommende Ship";
$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SECTOR defenses in [sector] destroy your probe.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] = "Probe Destroyed";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>You do not have enough turns for probe [probe_id] to move to [sector]</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] = "Probe Report";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"] = "<font color='#00ff00'>Moving to sector [target_sector] is not allowed</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] = "Probe Report";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Probe [probe_id] in sector [sector] detected [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] forsøkte å skanne en av sonder i sektor [sector], men mislyktes.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "En av sonder i sektor [sector] ble skannet av [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "En av sonder i sektor [sector] ble angrepet og ødelagt av [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "En av dine Probe Hunters har ødelagt en [probe_type] eid av [name] i [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe Hunter ødelagt [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Dine [probe_type] i sektor [sector] ble angrepet og ødelagt av et Probe Hunter eid av [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Din Probe Hunter i sektor [sector] gikk tapt da den resulterende eksplosjonen fra angrepet på [probe_type] eid av [name] innhyllet det.";
$l_log_title["LOG9_PROBEHUNTER_EXPLODED"] 		= "Probe Hunter Probe <font color='yellow'>Destroyed</font>";

// Auto Trade Logs

$l_log_text["LOG10_AUTOTRADE"]="<font color=yellow>Auto Trade for [planetname] in sector [sector] for [totalcost] credits.<br>Goods: [goodsamount] @ [goodsprice] credits - Ore: [oreamount] @ [oreprice] credits - Organics: [organicsamount] @ [organicsprice] credits - Energy: [energyamount] @ [energyprice] credits - Colonists: [colonistamount] @ [colonistprice] credits<br></font>";
$l_log_title["LOG10_AUTOTRADE"] = "Auto Trade Report";
$l_log_text["LOG10_AUTOTRADE_ABORTED"]="<font color='#00ff00'>Auto Trade for [planetname] in sector [sector] was aborted due to enemy sector defense in sector [destsector].<br></font>";
$l_log_title["LOG10_AUTOTRADE_ABORTED"] = "Auto Trade Report";

?>
<?php
$l_log_title["LOG3_SPACE_PLAGUE"] = "Space Plague!";
$l_log_text["LOG3_SPACE_PLAGUE"] = "Your planet [name] in sector [sector] has been hit by Space Plague. [percentage] percent of the colonists were killed.";
?>
<?php
$l_log_title["LOG3_PLASMA_STORM"] = "Plasma Storm!";
$l_log_text["LOG3_PLASMA_STORM"] = "Your planet [name] in sector [sector] has been hit by a Plasma Storm. All stored Energy has been lost.";
?>
<?php
$l_log_title["LOG3_PLANET_REVOLT"] = "Planetary Revolt";
$l_log_text["LOG3_PLANET_REVOLT"] = "Too many people on your planet [name] in sector [sector] and they have revolted!!! Damages: [credits]% credits lost, [colonists]% colonists killed, [organics]% organics destroyed, [goods]% goods destroyed, [ore]% ore destroyed, [torps]% torps destroyed, [fighters]% fighters destroyed and [energy]% energy lost.";
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
