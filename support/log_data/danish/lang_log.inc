<?php
$l_log_months = "array ( &#39;januar&#39;, &#39;februar&#39;, &#39;Marts&#39;, &#39;april&#39;, &#39;maj&#39;, &#39;juni&#39;, &#39;juli&#39;, &#39;august&#39;, &#39;September&#39;, &#39;oktober&#39;, &#39;November&#39;, &#39;December&#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;februar&#39;, &#39;mar&#39;, &#39;apr&#39;, &#39;maj&#39;, &#39;Juni&#39;, &#39;Jul&#39;, &#39;aug&#39;, &#39;September&#39;, &#39;Oktober&#39;, &#39;nov&#39;, &#39;dec&#39;)";
$l_log_pod = "Heldigvis, du havde en flugt pod!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s Log";
$l_log_start = "Log ind for";
$l_log_end = "Udgangen af log ind for";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Vælg en Log:";
$l_log_general = "Generelle log";
$l_log_dig = "Dignitar Log";
$l_log_spy = "Spy Log";
$l_log_disaster = "Planet Disaster Log";
$l_log_nova = "Nova Device Log";
$l_log_attack = "Attack Log";
$l_log_scan = "Scan Log";
$l_log_starv = "Planet Starvation Log";
$l_log_probe = "Probe Log";
$l_log_autotrade = "Auto Handel Log";
$l_log_combined = "Kombineret Log";


// Log entry data

$l_log_text["LOG_LOGIN"] = "Du har logget ind, fra [ip].";
$l_log_title["LOG_LOGIN"] = "Logget på";
$l_log_text["LOG_LOGOUT"] = "Du er logget ud, fra [ip].";
$l_log_title["LOG_LOGOUT"] = "Logget ud";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Database Error Occurred";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Action Resultat";
$l_log_title["LOG0_RAW"] = "Notice";
$l_log_text["LOG0_PLANET_EJECT"] = "Du er blevet bortvist fra planeten i sektoren [sector] fordi [name] forlod holdet.";
$l_log_title["LOG0_PLANET_EJECT"] = "Skubbet ud!";
$l_log_text["LOG0_BADLOGIN"] = "Der har været en dårlig login-forsøg fra [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Bad login";
$l_log_title["LOG0_TOW"] = "Trukne!";
$l_log_text["LOG0_TOW"] = "Dit skib er blevet trukket fra sektor [sector] til sektor [newsector], fordi din gennemsnitlige tech overskredet grænseværdien på [hull] eller du har et skib på lager.";
$l_log_text["LOG0_HARAKIRI"] = "De var trætte af kaptajn dette rum pram, så du har besluttet at universet ville være bedre uden. Godkendt af [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] har afvist en invitation til at tilslutte dit team, [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Invitation afvist";
$l_log_text["LOG0_TEAM_RENAME"] = "Du har omdøbt dit hold til [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Team omdøbt";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Dit team koordinator omdøbt holdet til [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Team omdøbt";
$l_log_text["LOG0_TEAM_KICK"] = "Du er blevet bortvist fra holdet [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Skubbes fra team!";
$l_log_text["LOG0_TEAM_CREATE"] = "Du har oprettet et nyt team, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Oprettet nye hold";
$l_log_text["LOG0_TEAM_LEAVE"] = "Du har forladt teamet [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Venstre team";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Du har forladt teamet [team]. De afgav lederrollen til [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Venstre team";
$l_log_text["LOG0_TEAM_LEAD"] = "Dit team koordinator har besluttet at forlade [team]. Du er blevet udpeget til at indtage sin plads.";
$l_log_title["LOG0_TEAM_LEAD"] = "Promotion!";
$l_log_text["LOG0_TEAM_JOIN"] = "Du har sluttet sig til teamet [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Joined team";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] har accepteret at blive optaget i [team]. Dette bringer dig et skridt videre til galaktisk dominans.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Ny medarbejder";
$l_log_text["LOG0_TEAM_INVITE"] = "Du er blevet inviteret til at være en del af [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Invitation";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] har forladt dit hold.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Team mister et medlem";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] har selv destrueret fra ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Selvdestruerende";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] havde [quantity] [type], med max ejer af [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Ulovlig skibets værdi";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] har forsøgt at erobre [defender] &#39;s planet i sektor [sector]. Planet blev ødelagt i stedet.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet ødelagt";
$l_log_text["LOG0_defense_DEGRADE"] = "Sektor forsvar Fighters i sektor [sector] nedbrydes af [degrade] procent på grund af utilstrækkelig energi.";
$l_log_title["LOG0_defense_DEGRADE"] = "Sektor forsvar forringet.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Spiller [player] på IP-adresse [ip] forsøgt at udnytte holdet sparke nogen snyder. Hans skib blev ødelagt.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Team Exploit Brugt";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Du hævdede en dusør på [amount] kreditter til ødelæggelse af skibet tilhører [bounty_on]. The Bounty blev placeret ved [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Bounty hævdet.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Din dusør på [bounty_on] er blevet betalt for et beløb på [amount] kreditter.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Bounty Betalt.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "Den Fedration dusør på [bounty_on] er blevet beskattet for et beløb på [amount] kreditter.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Bounty erlagte afgift.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Din dusør på [bounty_on] for et beløb på [amount] kreditter er blevet refunderet.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty refunderet.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "Føderationen har sat en dusør på dig for et beløb på [amount] kreditter.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federation Bounty!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliancen har sat en dusør på dig for et beløb på [amount] kreditter.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliance Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Spiller [name], der overføres [sum] kreditter til din IGB konto.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Som overføres";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Du overføres [sum] kreditter til afspilleren [name] &#39;s IGB konto.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Som overføres";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] planet [planetname] ([planetid]), der ejes af [owner] blev selvstændigt. Gennemsnitlig Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet gik uafhængige.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Uafhængige planet [planetname] ([planetid]), der ejes af [owner] i [sector] blev udrenset. Gennemsnitlig Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Uafhængige Planet udrenset.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Aldrig ejet planet [planetname] ([planetid]) er oprettet den [date] i [sector] blev udrenset. Gennemsnitlig Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Aldrig ejet Planet udrenset.";
$l_log_text["LOG0_TEAM_CANCEL"] = "Du er opfordringen til at være en del af [team] er blevet annulleret.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Invitation annulleret";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] påbegynder bygningen af produktionen.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] faldende fødselsrate.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] stigende fødselsrate.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] begyndte at søge efter spys på denne planet.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] starter øget kredit produktion.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Dignitar [id] på planeten [planet_name] underslæb [data] kreditter og doneret til dig!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Din dignitar opdaget spiller [name] &#39;s spionere på din planet [planet_name] i sektor [sector]. Den spion er dræbt nu.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Deres grave [id] på planeten [planet_name] i sektor [sector] omkom i en frygtelig katastrofe med denne planet.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Deres grave [id] om spiller [name] &#39;s skib [shipname] omkom i en frygtelig katastrofe med dette skib.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] bygget [data] planetarisk torpedoer!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Din dignitar [id] på planeten [planet_name] i sektor [sector] bygget [data] planetarisk kæmpere!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Du har mistet dit spion [id] på [name] &#39;s skib [shipname], fordi det spiller købte et nyt skib.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] har forsøgt at sende en spion til din planet [planet_name] i sektor [sector], men din Sensorer opdaget den spion, og han bliver dræbt nu.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Din spion [id] på planeten [planet_name] i sektor [sector] starter sabotage. Produktionen er faldet med [data] på denne planet.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Din spion [id] på planeten [planet_name] i sektor [sector] faldt fødselsraten af [data] på denne planet.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "Din spion [id] på planeten [planet_name] i sektor [sector] starter indsamling planeten interesse ved [data] til jer.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Din spion [id] på planeten [planet_name] i sektor [sector] vandt [data] kreditter til dig!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Din spion [id] på planeten [planet_name] i sektor [sector] ødelagt [data] planetarisk torpedoer!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Din spion [id] på planeten [planet_name] i sektor [sector] ødelagt [data] planetarisk kæmpere!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Din spion [id] på planeten [planet_name] i sektor [sector] tilfangetagne, at planet! Du er en heldig fyr ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] &#39;s spion fanget din planet [planet_name] i sektor [sector]! Det ser ud til, at det er klogt idé til oprydning dine planeter oftere ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Der er ingen meddelelser fra din spion [id] på planeten [planet_name] i sektoren [sector] i lang tid - det lader til, at din kappe enheden ikke kunne dække ham nok, og han bliver dræbt.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Din Sensorer opdaget en [name] &#39;s spionere på din planet [planet_name] i sektor [sector]. Den spion er dræbt nu.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "Der er ingen meddelelser fra din spion [id] spiller på [name] &#39;s skib [shipname] i lang tid - det lader til, at din kappe enheden ikke kunne dække ham nok, og han bliver dræbt.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Din spion [id] på planeten [planet_name] i sektor [sector] omkom i en frygtelig katastrofe med denne planet.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Din spion [id] om spiller [name] &#39;s skib [shipname] omkom i en frygtelig katastrofe med dette skib.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Din spion [id] fra planet [planet_name] i sektor [sector] infiltrater en spiller [playername] &#39;s skib [shipname] og handler nu er der.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Din spion [id] fra spiller [playername] &#39;s skib [shipname] infiltrater en planet [planet_name] i sektor [sector] og handler nu er der.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Dit dignitar nummer [DIG] på planeten [PLANET] er blevet fanget tilranet sig. Du vil måske ønske at afskedige dem.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Deres planet [planet_name] i sektor [sector] blev ødelagt med en Nova Bomb ved [name]. Absolut intet tilbage at markere planeterne tidligere eksistens.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Dit skib blev ødelagt med en Nova bombet af [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Deres planet [planet_name] i sektor [sector] blev bombet af [name]. Du brugte [beams] energi og [torps] torpedoer i dit forsvar. Du mistet [figs] krigere.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Deres planet [planet_name] i sektor [sector] blev besejret og taget til fange af den elendige [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] blev spottet på et angreb vektor, men din store pilot-evner og gode motorer givet mulighed for at udmanøvrere fjenden.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Undvigemanøvre!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Du opdaget [player] &#39;s våben forsøger at lave på dit skib, men din kappe generatorer lykkedes at narre fjenden&#39;s primitive sensor kredsløb.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Cloak vellykket!";
$l_log_text["LOG5_ATTACK_EWD"] = "Du er overrasket over [player] &#39;s forræderiske angreb. Du kan se de indkommende sprænghoveder, som du kommer til rasende til nødhjælpsindsats warp knappen. Verden udvisker omkring dig, og for en milisecond, du tror, du er død. Når du endelig åbne dine øjne, kan du se, at du var sikkert transporteres bort. Men hvor præcis, behøver du ikke vide ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Emergency warp!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Deres sensorer registrerer [player] &#39;s skib på et angreb vektor. &quot;Bedre være sikker end ked af&quot;, du tror, at trykke på nødsituation warp knappen. Du kan høre en underlig kvælning lyd fra motorerne værelse og lugte brændt kredsløb. &quot;Dum stykke crap!&quot;, Du råber og sparker på computeren. Computeren udsender bipper i protest, som du forberede det kommende kamp ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Dit skib bliver angrebet af [player]. Prøv som du måske kan du ikke forsvare dig selv mod [player] &#39;s overlegne våben. Dit skib blev ødelagt.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Dit skib blev angrebet af [player]. Du kamp for et stykke tid, så kampen bryder ned. Du mistet [armor] rustning point og [fighters] krigere i træfning.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Du ramte [mines] miner, når de rejser i sektor [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Dit skib blev ødelagt af et minefelt i sektor [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Deres planet [planet_name] i sektor [sector] blev besejret i slaget ved [name]. Heldigvis er stærk loyalitet over for Deres borgere spillet i din favør. De har modigt valgt at ødelægge planeten snarere end at have det til at falde i fjendens hænder. Du organisere fantastiske begravelser i hukommelsen på din trofaste mennesker.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Deres planet [planet_name] i sektor [sector] blev besejret i slaget ved den elendige [name]. De mennesker på planeten velkommen til deres nye lineal. Du hører et vidnesbyrd om FNN: &quot;Vi er glade for at slippe af med, at gamle prut! Vi ønsker ikke nogen stinkende taberen, som ikke kan beskytte os!&quot;. Du sværger til at få dem til at betale for deres arrogance.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Deres planet [planet_name] i sektor [sector] blev angrebet af [name]. De borgere, organiserede en Valliant forsvar dog, og det lykkedes at ødelægge modstanderen. De redde nogle ressourcer fra rumskrot: [goods] gods, [ore] ore, [organics] organiske og [salvage]% af skibets værdi af [credits] kreditter.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Sejr!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] blev ødelagt i sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Sektor forsvar ødelagt";
$l_log_text["LOG5_KABAL_ATTACK"] = "Angribende [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Attack";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Du har ødelagt [fighters] patruljerer soldaterne i sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Fighters ødelagt";
$l_log_text["LOG5_DEFS_KABOOM"] = "Du blev ødelagt ved en krigere kraft i sektor [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Du fangede en planet, der tilhører [owner]. Det havde [cols] kolonister og [credits] kreditter på det.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet fanget!";
$l_log_text["LOG5_STORAGE_EWD"] = "Jeres planet er overrasket [player] &#39;s angreb. En af dine lagrede skibe lavet en Emergency Warp til [sector] og landede på planeten [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Lagret Ship Emergency warp!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "En gemt skibe Emergency Warp Device TABT! De lagrede Skibet blev taget til fange af [player], efter at de besejrede din planet!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "En gemt skibet blev taget til fange af [player], efter at de slog en af dine planeter!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Dit skib blev beslaglagt af [player]. Gøre for at overdreven angreb på gavmildhed spillere [player] har konfiskeret en af dine skibe ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Din planet blev konfiskeret af [player]. Gøre for at overdreven angreb på gavmildhed spillere [player] har konfiskeret en af dine planeter ([name]) i sektor [sector] værdi [score] kreditter.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "En gemt skib suicided når [player] besejrede en af dine planeter og forsøgte at fange den!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "Skib Sensorer opdaget et indgående Sektor missil blev affyret fra [sector] med [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "En sektor missil affyret af [player] blev spottet vridning i sektoren, og man undgik angrebet.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sektor Missile undvigemanøvre!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Du opdaget [player] &#39;s et indgående Sektor Missile forsøger at lave på dit skib, men din kappe generatorer lykkedes at narre de Sektor Missiler sensor kredsløb.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sektor Missile Cloak succes!";
$l_log_text["LOG5_SM_EWD"] = "Du er overrasket over [player] &#39;s Sektor missilangreb og engagere Emergency Warp Enhed hoppe til et ukendt sektor.";
$l_log_title["LOG5_SM_EWD"] = "Sektor Missile Emergency warp!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Deres sensorer registrerer [player] &#39;s Sektor missilangreb og engagere Emergency Warp enhed. Du kan høre en underlig kvælning lyd fra motorerne værelse og lugte brændt kredsløb. &quot;Dum stykke crap!&quot;, Du råber og sparker på computeren. Du brace for indflydelse!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Dit skib blev angrebet af [player] ved hjælp af en sektor Missile. Du mistet [armor] rustning point og [energy] energi enheder i angrebet.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Dit skib blev ødelagt af en sektor missiler fra [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Dit skib blev angrebet af en sonde, der ejes af [player] i sektor [sector]. Du mistet [armor] rustning point og [energy] energi enheder i angrebet.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] overlevede et angreb fra din sonde i sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Din sonde ødelagt skibet ejes af [player] i sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Dit skib blev ødelagt af en sonde fra [player] i sektor [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "Efter Action Combat Report";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name] har scannet din planet [planet_name] i sektor [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet scanning";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] har forsøgt at scanne din planet [planet_name] i sektor [sector], men det mislykkedes.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planet scanning mislykkedes";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] har scannet dit skib.";
$l_log_title["LOG6_SHIP_SCAN"] = "Ship scanning";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] har forsøgt at scanne dit skib, men det mislykkedes.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Ship scanning mislykkedes";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] i [sector] kan ikke opretholde sin befolkning! Mere organiske er behov for. [starvation] kolonister døde af sult. Kolonister begyndte udsulter den [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Detected Indgående Ship";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Probe Scannet Indgående Ship";
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

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] forsøgt at scanne en af dine sonder i sektor [sector], men det mislykkedes.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "En af dine sonder i sektor [sector] blev scannet af [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "En af dine sonder i sektor [sector] blev angrebet og ødelagt af [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "En af dine Probe Jægere har ødelagt en [probe_type] ejes af [name] i [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe Hunter ødelagt [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Din [probe_type] i sektor [sector] blev angrebet og ødelagt af en Probe Hunter ejet af [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Din Probe Hunter i sektor [sector] blev tabt, når den deraf følgende eksplosion fra sit angreb på [probe_type] ejes af [name] indhyllet det.";
$l_log_title["LOG9_PROBEHUNTER_EXPLODED"] 		= "Probe Hunter Probe <font color='yellow'>Destroyed</font>";

// Auto Trade Logs

$l_log_text["LOG10_AUTOTRADE"]="<font color=yellow>Auto Trade for [planetname] in sector [sector] for [totalcost] credits.<br>Goods: [goodsamount] @ [goodsprice] credits - Ore: [oreamount] @ [oreprice] credits - Organics: [organicsamount] @ [organicsprice] credits - Energy: [energyamount] @ [energyprice] credits - Colonists: [colonistamount] @ [colonistprice] credits<br></font>";
$l_log_title["LOG10_AUTOTRADE"] = "Auto Handel Report";
$l_log_text["LOG10_AUTOTRADE_ABORTED"]="<font color='#00ff00'>Auto Trade for [planetname] in sector [sector] was aborted due to enemy sector defense in sector [destsector].<br></font>";
$l_log_title["LOG10_AUTOTRADE_ABORTED"] = "Auto Handel Report";

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
