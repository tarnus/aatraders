<?php
$l_log_months = "array ( &#39;Januari&#39;, &#39;Februari&#39;, &#39;Maart&#39;, &#39;April&#39;, &#39;Mei&#39;, &#39;Juni&#39;, &#39;Juli&#39;, &#39;Augustus&#39;, &#39;September&#39;, &#39;Oktober&#39;, &#39;November&#39;, &#39;December&#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;februari&#39;, &#39;Mar&#39;, &#39;april&#39;, &#39;mei&#39;, &#39;juni&#39;, &#39;juli&#39;, &#39;augustus&#39;, &#39;september&#39;, &#39;oktober&#39;, &#39;november&#39;, &#39;december&#39;)";
$l_log_pod = "Gelukkig had je een escape-pod!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s Log";
$l_log_start = "Aanmelden voor inschrijving";
$l_log_end = "Einde van de regel voor";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Selecteer een Log:";
$l_log_general = "Algemene Log";
$l_log_dig = "Hoogwaardigheidsbekleder Inloggen";
$l_log_spy = "Spy Inloggen";
$l_log_disaster = "Planet Ramp Inloggen";
$l_log_nova = "Nova Device Inloggen";
$l_log_attack = "Attack Inloggen";
$l_log_scan = "Scan Inloggen";
$l_log_starv = "Planet Starvation Inloggen";
$l_log_probe = "Probe Inloggen";
$l_log_autotrade = "Auto Trade Aanmelden";
$l_log_combined = "Gecombineerde Inloggen";


// Log entry data

$l_log_text["LOG_LOGIN"] = "U bent aangemeld, van [ip].";
$l_log_title["LOG_LOGIN"] = "Logged in";
$l_log_text["LOG_LOGOUT"] = "U heeft zich afgemeld, van [ip].";
$l_log_title["LOG_LOGOUT"] = "Uitgelogd";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Database fout opgetreden";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Action Uitslag";
$l_log_title["LOG0_RAW"] = "Bericht";
$l_log_text["LOG0_PLANET_EJECT"] = "Jullie zijn uitgeworpen van de planeet in de sector [sector] omdat [name] het team verlaten.";
$l_log_title["LOG0_PLANET_EJECT"] = "Uitgeworpen!";
$l_log_text["LOG0_BADLOGIN"] = "Er is een slechte login poging van [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Bad login";
$l_log_title["LOG0_TOW"] = "Gesleept!";
$l_log_text["LOG0_TOW"] = "Uw schip is getrokken uit de sector [sector] tot sector [newsector], omdat de gemiddelde tech niveau van de grenswaarde van [hull] overschreden of je hebt een schip in de opslag.";
$l_log_text["LOG0_HARAKIRI"] = "Je was moe van captaining deze ruimte binnenschip, zodat u besloten het heelal beter zou zijn zonder. Met toestemming van [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] heeft verworpen een uitnodiging om uw team, join [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Uitnodiging afgewezen";
$l_log_text["LOG0_TEAM_RENAME"] = "U hebt de naam van uw team [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Team naam";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Uw team coördinator van het team omgedoopt tot [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Team naam";
$l_log_text["LOG0_TEAM_KICK"] = "Jullie zijn verwijderd uit het team [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Uitgeworpen uit team!";
$l_log_text["LOG0_TEAM_CREATE"] = "U hebt een nieuw team, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Gemaakt nieuw team";
$l_log_text["LOG0_TEAM_LEAVE"] = "Je hebt links team [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Links team";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "U heeft links het team [team]. Je afstand gedaan van de teamleiding van [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Links team";
$l_log_text["LOG0_TEAM_LEAD"] = "Uw team coördinator heeft besloten om weg te gaan [team]. Je bent aangesteld om in de plaats.";
$l_log_title["LOG0_TEAM_LEAD"] = "Actie!";
$l_log_text["LOG0_TEAM_JOIN"] = "U hebt bij het team [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Geregistreerd team";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] heeft aanvaard om deel te nemen [team]. Dit brengt u een stap verder om galactische overheersing.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Nieuw teamlid";
$l_log_text["LOG0_TEAM_INVITE"] = "U bent uitgenodigd om deel uit te maken van [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Uitnodiging";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] heeft verlaten uw team.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Team verliest een lid";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] heeft zichzelf vernietigd vanaf ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Zelfvernietiging";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] had [quantity] [type], met max. bezit van [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Illegale schip waarde";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] heeft gepoogd om [defender] &#39;s planeet vast te leggen in de sector [sector]. Planet werd in plaats daarvan vernietigd.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet vernietigd";
$l_log_text["LOG0_defense_DEGRADE"] = "Sector verdediging Fighters in de sector [sector] afgebroken door [degrade] procent te wijten aan onvoldoende energie.";
$l_log_title["LOG0_defense_DEGRADE"] = "Sector verdediging aangetast.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Player [player] op IP-adres [ip] probeerde te profiteren van de ploeg kick iemand te bedriegen. Zijn schip werd verwoest.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Team Exploit Gebruikt";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "U beweerde dat een premie van [amount] credits voor de vernietiging van het schip dat behoort tot [bounty_on]. De premie werd geplaatst door [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Bounty geclaimd.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Uw premie op [bounty_on] is betaald voor het bedrag van [amount] credits.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Bounty Betaald.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "De Fedration bounty op [bounty_on] is belast voor het bedrag van [amount] credits.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Bounty belasting betaald.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Uw premie op [bounty_on] voor het bedrag van [amount] kredieten is terugbetaald.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty terugbetaald.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "De Federatie heeft geplaatst een bounty op je voor het bedrag van [amount] credits.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federatie Bounty!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "De Alliantie heeft geplaatst een bounty op je voor het bedrag van [amount] credits.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliance Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Player [name] overgedragen [sum] credits IGB aan uw account.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Credits overgedragen";
$l_log_text["LOG0_IGB_TRANSFER2"] = "U overgedragen [sum] credits voor de speler [name] &#39;s IGB-account.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Credits overgedragen";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] planet [planetname] ([planetid]) die eigendom zijn van [owner] onafhankelijk werd. Gemiddelde Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet ging onafhankelijk.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Onafhankelijke planeet [planetname] ([planetid]) die eigendom zijn van [owner] in [sector] was gespoeld. Gemiddelde Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Onafhankelijke Planet gespoeld.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Nooit Owned planeet [planetname] ([planetid]) opgericht op [date] in [sector] was gespoeld. Gemiddelde Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Nooit Owned Planet gespoeld.";
$l_log_text["LOG0_TEAM_CANCEL"] = "Je uitnodiging om deel uit te maken van [team] is geannuleerd.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Uitnodiging Canceled";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] begint met de bouw productie.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] dalende geboortecijfer.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] toenemende geboortecijfer.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] begon te zoeken naar spys op die planeet.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] begint het stimuleren van krediet-productie.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Hoogwaardigheidsbekleder [id] op de planeet [planet_name] verduisterd [data] credits en gedoneerd aan u!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Uw hoogwaardigheidsbekleder ontdekt speler [name] &#39;s spion op je planeet [planet_name] in de sector [sector]. De spion is gedood.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Uw graven [id] op de planeet [planet_name] in de sector [sector] omgekomen in een verschrikkelijke ramp met die planeet.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Uw graven [id] op speler [name] &#39;s schip [shipname] omgekomen in een verschrikkelijke ramp met dat schip.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] gebouwd [data] planetaire torpedo&#39;s!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Uw hoogwaardigheidsbekleder [id] op de planeet [planet_name] in de sector [sector] gebouwd [data] planetaire vechters!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Je verloor je spion [id] op [name] &#39;s schip [shipname], omdat deze speler een nieuw schip gekocht.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] geprobeerd om een spion te sturen naar je planeet [planet_name] in de sector [sector], maar uw Sensoren ontdekt de spion en hij is nu dood.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] begint te saboteren. De productie is gedaald met [data] op die planeet.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] geboortecijfer daalde van [data] op die planeet.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] begint het verzamelen van planeet belang van [data] aan jou.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] heb [data] credits to you!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] vernietigd [data] planetaire torpedo&#39;s!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] vernietigd [data] planetaire vechters!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] gevangen genomen die planeet! U bent een gelukkig man ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] &#39;s spion gevangen je planeet [planet_name] in de sector [sector]! Het lijkt erop dat het is verstandig om uw planeten opruimen vaker ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Er zijn geen berichten van je spion [id] op de planeet [planet_name] in de sector [sector] voor een lange tijd - lijkt het erop dat uw Cloak apparaat niet genoeg kunnen betrekking hebben op hem en hij wordt gedood.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Uw Sensoren ontdekt een [name] &#39;s spion op je planeet [planet_name] in de sector [sector]. De spion is gedood.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "Er zijn geen berichten van je spion [id] op speler [name] &#39;s schip [shipname] voor een lange tijd - lijkt het erop dat uw Cloak apparaat niet genoeg kunnen betrekking hebben op hem en hij wordt gedood.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Uw spion [id] op de planeet [planet_name] in de sector [sector] omgekomen in een verschrikkelijke ramp met die planeet.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Uw spion [id] op speler [name] &#39;s schip [shipname] omgekomen in een verschrikkelijke ramp met dat schip.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Uw spion [id] van planeet [planet_name] in de sector [sector] infiltreert een speler [playername] &#39;s schip [shipname] en fungeert nu daar.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Uw spion [id] van speler [playername] &#39;s schip [shipname] infiltreert een planeet [planet_name] in de sector [sector] en fungeert nu is er.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Uw hoogwaardigheidsbekleder nummer [DIG] op de planeet [PLANET] is gevangen verduistering. Misschien wil je te laten.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Uw planeet [planet_name] in de sector [sector] werd vernietigd met een Nova Bomb door [name]. Absoluut niets blijft aan de planeten merk vroegere bestaan.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Uw schip werd vernietigd met een Nova gebombardeerd door [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Uw planeet [planet_name] in de sector [sector] werd gebombardeerd door [name]. U gebruikt [beams] energie en [torps] torpedo&#39;s in je verdediging. Je hebt verloren [figs] strijders.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Uw planeet [planet_name] in de sector [sector] werd verslagen en gevangen genomen door de ellendige [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] werd gespot op een aanval vector, maar je grote piloot vaardigheden en goede motoren staat je toe om de vijand te slim af zijn.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Ontwijkende actie!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "U ontdekt [player] &#39;s wapens probeert vast te stellen op uw schip, maar uw mantel generatoren in geslaagd om primitieve sensor circuits van de vijand te misleiden.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Cloak succesvol!";
$l_log_text["LOG5_ATTACK_EWD"] = "U bent verrast door [player] &#39;s verraderlijke aanval. U kunt zien dat de inkomende kernkoppen als je wanhopig te bereiken voor de hulpdiensten warp-knop. De wereld om je heen vervaagt en, voor een milisecond, denk je dat je dood bent. Als je dan eindelijk je ogen open, zie je dat je veilig waren elders vervoerd. Maar waar precies, je weet niet ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Emergency ketting!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Uw sensoren detecteren [player] &#39;s schip op een aanvalsmethode. &quot;Better safe than sorry&quot; worden&quot;, denk je, het raken van de nood-warp-knop. Je hoort een vreemd verstikkende geluid dat uit de motoren en de geur kamer brandde circuits. &quot;Stupid piece of crap!&quot;, Schreeuw je, schoppen op de computer. De computer zendt piepjes van protest als je voor te bereiden op het komende gevecht ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Uw schip wordt aangevallen door [player]. Probeer zoals je wel kan, kun je jezelf niet verdedigen tegen [player] &#39;s superieure wapens. Uw schip werd verwoest.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Uw schip werd aangevallen door [player]. Je strijd voor een tijdje, dan is de strijd breekt. Je hebt verloren [armor] armor punten en [fighters] strijders in het gevecht.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Je slaat [mines] mijnen bij het reizen in de sector [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Uw schip werd vernietigd door een mijnenveld in de sector [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Uw planeet [planet_name] in de sector [sector] werd verslagen in een gevecht door [name]. Gelukkig, de sterke loyaliteit van uw burgers gespeeld in uw voordeel. Ze zijn moedig gekozen om de planeet te vernietigen, in plaats van het moeten vallen in handen van de vijand. U organiseert fantastische begrafenissen in het geheugen van uw trouwe mensen.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Uw planeet [planet_name] in de sector [sector] werd verslagen in een gevecht door de ellendige [name]. De mensen van de planeet zijn blij met hun nieuwe heerser. U hoort een getuigenis over FNN: &quot;Wij zijn blij af te zijn van die oude knar! We willen niet dat er geen stinkende sukkel die niet kan beschermen ons!&quot;. U zweert om ze te laten betalen voor hun arrogantie.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Uw planeet [planet_name] in de sector [sector] werd aangevallen door [name]. De burgers organiseerden een Valliant verdediging echter, en wist de tegenstander te vernietigen. Ze redden een aantal middelen van het ruimtepuin: [goods] goederen, [ore] ore [organics] organische en [salvage]% van de waarde van het schip van [credits] credits.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Victory!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] zijn vernietigd in de sector [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Sector verdediging vernietigd";
$l_log_text["LOG5_KABAL_ATTACK"] = "Aanvallen [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Attack";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "U hebt vernietigd [fighters] patrouilleren strijders in de sector [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Fighters vernietigd";
$l_log_text["LOG5_DEFS_KABOOM"] = "Je was verwoest door een vechters van kracht zijn in de sector [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Je veroverde een planeet die toebehoren aan [owner]. Het was [cols] kolonisten en [credits] credits op.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet gevangen genomen!";
$l_log_text["LOG5_STORAGE_EWD"] = "Uw planeet is verrast door [player] &#39;s aanval. Een van uw opgeslagen schepen maakte een Emergency Warp naar [sector] en landde op de planeet [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Opgeslagen Ship Emergency ketting!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "Een opgeslagen schepen Emergency Warp-apparaat is mislukt! De opgeslagen schip werd gevangen genomen door [player] nadat ze jouw planeet verslagen!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "Een opgeslagen schip werd gevangen genomen door [player], nadat zij een van de planeten verslagen!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Uw schip werd in beslag genomen door [player]. Doen om buitensporige aanvallen op bounty-spelers op de [player] heeft in beslag genomen een van je schepen ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Uw planeet werd in beslag genomen door [player]. Doen om buitensporige aanvallen op bounty-spelers op de [player] heeft een beslag van uw planeten ([name]) in de sector [sector] waard [score] credits.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "Een opgeslagen schip suicided wanneer [player] versloeg een van de planeten en probeerde hem te vangen!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "Sensoren schip ontdekt een inkomende Sector raketten worden afgevuurd vanaf [sector] door [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "Een sector raketten afgevuurd door [player] werd gespot kromtrekken in de sector en je ontweek de aanval.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sector Missile uitwijken!";
$l_log_text["LOG5_SM_OUTSCAN"] = "U ontdekt [player] &#39;s een inkomende raketten Sector probeert vast te stellen op uw schip, maar uw mantel generatoren in geslaagd om de sector Raketten sensor circuits dwaas.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sector Missile Cloak succesvol!";
$l_log_text["LOG5_SM_EWD"] = "U bent verrast door [player] &#39;s Sector raketaanval en zich de Emergency Warp Device springen naar een onbekende sector.";
$l_log_title["LOG5_SM_EWD"] = "Sector Missile Emergency ketting!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Uw sensoren detecteren [player] &#39;s Sector raketaanval en zich de Emergency Warp Device. Je hoort een vreemd verstikkende geluid dat uit de motoren en de geur kamer brandde circuits. &quot;Stupid piece of crap!&quot;, Schreeuw je, schoppen op de computer. U Brace for Impact!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Uw schip werd aangevallen door [player] met behulp van een sector Missile. Je hebt verloren [armor] armor punten en [energy] energie-eenheden in de aanval.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Uw schip werd vernietigd door een sector Missile van [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Uw schip werd aangevallen door een sonde in handen van [player] in de sector [sector]. Je hebt verloren [armor] armor punten en [energy] energie-eenheden in de aanval.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] overleefde een aanval van de sonde in de sector [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Uw sonde vernietigde het schip eigendom is van [player] in de sector [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Uw schip werd vernietigd door een sonde van [player] in de sector [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "After Action Report Combat";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name] heeft gescand je planeet [planet_name] in de sector [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet scan";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] heeft geprobeerd om jouw planeet scan [planet_name] in de sector [sector], maar dat mislukte.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planet-scan is mislukt";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] heeft gescand uw schip.";
$l_log_title["LOG6_SHIP_SCAN"] = "Ship-scan";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] heeft geprobeerd het scannen van uw schip, maar dat mislukte.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Ship-scan is mislukt";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] in [sector] kan niet in stand houden van haar bevolking! Meer organische stoffen nodig zijn. [starvation] kolonisten stierven van de honger. Kolonisten begonnen met honger op [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Detected Inkomende schepen";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Probe Gescande Inkomende schepen";
$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SECTOR defenses in [sector] destroy your probe.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] = "Probe Vernietigd";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>You do not have enough turns for probe [probe_id] to move to [sector]</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] = "Probe Verslag";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"] = "<font color='#00ff00'>Moving to sector [target_sector] is not allowed</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] = "Probe Verslag";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Probe [probe_id] in sector [sector] detected [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] probeerde een van de sondes in de sector scan [sector], maar dat mislukte.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "Een van de sondes in de sector [sector] werd gescand door [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "Een van de sondes in de sector [sector] werd aangevallen en verwoest door [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "Een van uw Probe Jagers heeft vernietigd een [probe_type] in eigendom bij [name] in [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe Hunter vernietigd [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Uw [probe_type] in de sector [sector] werd aangevallen en verwoest door een sonde Hunter eigendom van [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Uw Probe Hunter in de sector [sector] verloren is gegaan toen de explosie van de aanval op de [probe_type] in eigendom bij [name] gehuld is.";
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
