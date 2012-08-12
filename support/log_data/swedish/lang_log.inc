<?php
$l_log_months = "array ( &#39;januari&#39;, &#39;februari&#39;, &#39;mars&#39;, &#39;April&#39;, &#39;mars&#39;, &#39;Juni&#39;, &#39;Juli&#39;, &#39;augusti&#39;, &#39;September&#39;, &#39;oktober&#39;, &#39;November&#39;, &#39;December&#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;februari&#39;, &#39;mar&#39;, &#39;april&#39;, &#39;Maj&#39;, &#39;juni&#39;, &#39;juli&#39;, &#39;augusti&#39;, &#39;september&#39;, &#39;oktober&#39;, &#39;november&#39;, &#39;december&#39;)";
$l_log_pod = "Lyckligtvis fick du en escape pod!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s logga";
$l_log_start = "Loggpost för";
$l_log_end = "Sista loggpost för";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Välj en logg:";
$l_log_general = "Allmänna loggen";
$l_log_dig = "Dignitär Log";
$l_log_spy = "Spy Log";
$l_log_disaster = "Planet Disaster Log";
$l_log_nova = "Nova Device Log";
$l_log_attack = "Attack Log";
$l_log_scan = "Scan Log";
$l_log_starv = "Planet Svält Log";
$l_log_probe = "Probe Log";
$l_log_autotrade = "Auto Trade Log";
$l_log_combined = "Kombinerad Log";


// Log entry data

$l_log_text["LOG_LOGIN"] = "Du har loggat in, från [ip].";
$l_log_title["LOG_LOGIN"] = "Inloggad";
$l_log_text["LOG_LOGOUT"] = "Du har loggat ut från [ip].";
$l_log_title["LOG_LOGOUT"] = "Utloggad";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Database Error Occurred";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Combat Action Resultat";
$l_log_title["LOG0_RAW"] = "Notice";
$l_log_text["LOG0_PLANET_EJECT"] = "Du har blivit utkastade från planeten inom sektorn [sector] eftersom [name] lämnade laget.";
$l_log_title["LOG0_PLANET_EJECT"] = "Utkastade!";
$l_log_text["LOG0_BADLOGIN"] = "Det har varit en dålig inloggningsförsök från [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Bad login";
$l_log_title["LOG0_TOW"] = "Dragna!";
$l_log_text["LOG0_TOW"] = "Ditt skepp har bogserats från sektor [sector] till sektorn [newsector] eftersom din genomsnittliga tech översteg gränsvärdet [hull] eller om du har ett fartyg i lager.";
$l_log_text["LOG0_HARAKIRI"] = "Du var trött på lagkapten detta utrymme pråm, så att du beslutade universum skulle vara bättre utan den. Tillstånd av [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] har avvisat en inbjudan att gå med ditt team, [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Inbjudan avvisas";
$l_log_text["LOG0_TEAM_RENAME"] = "Du har bytt namn på ditt lag till [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Team namn";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Ditt lag samordnare döpa om laget till [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Team namn";
$l_log_text["LOG0_TEAM_KICK"] = "Du har blivit utkastade från teamet [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Utkastade från team!";
$l_log_text["LOG0_TEAM_CREATE"] = "Du har skapat ett nytt team, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Skapat nya team";
$l_log_text["LOG0_TEAM_LEAVE"] = "Du har lämnat laget [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Vänster team";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Du har lämnat laget [team]. Du avstod laget ledningen att [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Vänster team";
$l_log_text["LOG0_TEAM_LEAD"] = "Ditt lag samordnare har beslutat att lämna [team]. Du har utsetts att ta dess plats.";
$l_log_title["LOG0_TEAM_LEAD"] = "Promotion!";
$l_log_text["LOG0_TEAM_JOIN"] = "Du har gått med i laget [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Joined team";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] har accepterat att gå [team]. Detta tar dig ett steg vidare för att galaktisk dominans.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Ny i teamet";
$l_log_text["LOG0_TEAM_INVITE"] = "Du har blivit inbjuden att vara med [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Inbjudan";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] har lämnat ditt team.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Team förlorar en medlem";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] har själv förstöras från ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Självförstörande";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] hade [quantity] [type], med max håller på [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Illegal fartygets värde";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] har försökt att fånga [defender] s planet inom sektorn [sector]. Planet förstördes istället.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet förstöras";
$l_log_text["LOG0_defense_DEGRADE"] = "Sector försvar Fighters i sektorn [sector] ned av [degrade] procent på grund av otillräcklig energi.";
$l_log_title["LOG0_defense_DEGRADE"] = "Sector försvar försämras.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Spelare [player] på IP-adress [ip] försökt att utnyttja någon lag kick fuska. Hans skepp förstördes.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Team Exploit Begagnade";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Du hävdade en bounty på [amount] krediter för destruktion av fartyg som hör till [bounty_on]. The Bounty lades av [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Bounty begärs.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Din bounty [bounty_on] har betalats till ett belopp på [amount] krediter.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Bounty Paid.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "Den Fedration bounty på [bounty_on] har beskattats för ett belopp på [amount] krediter.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Bounty Tax Paid.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Din skottpengar på [bounty_on] för på [amount] krediter har återbetalats.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty återbetalas.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "Förbundet har placerat en bounty på dig för på [amount] krediter.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federation Bounty!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliansen har placerat en bounty på dig för på [amount] krediter.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Alliance Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Spelare [name] som överförs [sum] krediter till ditt IGB konto.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Anslag som överförs";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Du överförde [sum] Poäng till spelare [name] &#39;s IGB konto.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Anslag som överförs";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] planet [planetname] ([planetid]) som ägs av [owner] blev självständigt. Genomsnitt Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet gick oberoende.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Oberoende planet [planetname] ([planetid]) som ägs av [owner] i [sector] var avinstalleras. Genomsnitt Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Oberoende Planet avinstalleras.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Aldrig ägt planet [planetname] ([planetid]) skapade den [date] i [sector] var avinstalleras. Genomsnitt Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Aldrig ägt Planet avinstalleras.";
$l_log_text["LOG0_TEAM_CANCEL"] = "You&#39;re inbjudan att vara med [team] har avbrutits.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Inbjudan annullerad";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "Din dignitär [id] på planeten [planet_name] i sektorn [sector] byggstarten produktion.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Din dignitär [id] på planeten [planet_name] i sektorn [sector] minskande födelsetal.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Din dignitär [id] på planeten [planet_name] i sektorn [sector] ökande födelsetal.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Din dignitär [id] på planeten [planet_name] i sektorn [sector] började söka efter spys på denna planet.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Din dignitär [id] på planeten [planet_name] i sektorn [sector] börjar öka kredit produktion.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Dignitär [id] på planeten [planet_name] förskingrat [data] krediter och donerade till dig!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Din dignitär upptäckts spelare [name] &#39;s spionera på din planet [planet_name] i sektorn [sector]. Spionen dödas nu.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Din dig [id] på planeten [planet_name] i sektorn [sector] omkom i en fruktansvärd katastrof med det planet.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Din dig [id] på spelare [name] &#39;s fartyg [shipname] omkom i en fruktansvärd katastrof med det fartyget.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Din dignitär [id] på planeten [planet_name] i sektorn [sector] byggda [data] planetariska torpeder!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Din dignitär [id] på planeten [planet_name] inom sektorn [sector] byggda [data] planetariska krigare!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Du har tappat ditt spion [id] på [name] &#39;s fartyg [shipname], eftersom den spelaren köpt ett nytt fartyg.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] försökte skicka en spion till din planet [planet_name] inom sektorn [sector], men din Sensorer upptäckte spion och han dödas nu.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Din spionera [id] på planeten [planet_name] i sektorn [sector] börjar sabotage. Produktionen minskade med [data] på denna planet.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Din spion [id] på planeten [planet_name] i sektorn [sector] minskade födelsetal av [data] på denna planet.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "Din spionera [id] på planeten [planet_name] inom sektorn [sector] börjar samla planet intresse [data] dig.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Din spionera [id] på planeten [planet_name] i sektorn [sector] vann [data] Poäng till dig!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Din spionera [id] på planeten [planet_name] i sektorn [sector] förstöras [data] planetariska torpeder!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Din spion [id] på planeten [planet_name] inom sektorn [sector] förstöras [data] planetariska krigare!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Din spion [id] på planeten [planet_name] i sektorn [sector] fångat detta planet! Du är en lycklig kille ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] &#39;s spion fångat din planet [planet_name] i sektorn [sector]! Det verkar som om det är klokt idé att cleanup din planeter oftare ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Det finns inga meddelanden från din spion [id] på planeten [planet_name] inom sektorn [sector] under lång tid - det verkar som om din mantel enheten inte kan omfatta honom nog, och han blir dödad.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Din Sensorer upptäckt en [name] &#39;s spionera på din planet [planet_name] inom sektorn [sector]. Spionen dödas nu.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Din spion [id] på planeten [planet_name] i sektorn [sector] omkom i en fruktansvärd katastrof med det planet.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Din spionera [id] på spelare [name] &#39;s fartyg [shipname] omkom i en fruktansvärd katastrof med det fartyget.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Din spionera [id] från planet [planet_name] i sektorn [sector] infiltrerar en spelare [playername] &#39;s fartyg [shipname] och agerar nu finns.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Din spionera [id] från spelare [playername] &#39;s fartyg [shipname] infiltrerar en planet [planet_name] i sektorn [sector] och agerar nu finns.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Ditt dignitär nummer [DIG] på planeten [PLANET] PLANET har fångats förskingring. Du kanske vill att avvisa dem.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Din planet [planet_name] i sektorn [sector] förstördes med en Nova Bomb av [name]. Absolut ingenting återstår att markera planeterna forna existens.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Ditt skepp förstördes med en Nova bombats av [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Din planet [planet_name] i sektorn [sector] bombades av [name]. Du använde [beams] energi och [torps] torpeder i ditt försvar. Du förlorade [figs] fighters.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Din planet [planet_name] i sektorn [sector] blev besegrad och tillfångatagen av den usla [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] sågs på en attack vektor, men din stora pilot kunskaper och bra motorer får du outmaneuver fienden.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Undanmanöver!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Du upptäckts [player] s vapen försöker fastställa på ditt skepp, men din kappa generatorer lyckades lura fiendens primitiva sensor kretsar.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Kappa lyckad!";
$l_log_text["LOG5_ATTACK_EWD"] = "Du är förvånad [player] &#39;s lömska angrepp. Du kan se inkommande stridsspetsar som du når frenetiskt för akuta varp-knappen. Världen suddar omkring dig och för en milisecond, du tror att du är död. När du äntligen öppna ögonen, ser ni att ni var transporteras säkert någon annanstans. Men var exakt, du vet inte ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Emergency warp!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Din sensorer [player] &#39;s skepp på en attack vektor. &quot;Bättre vara säkra före det osäkra&quot;, tror du, att trycka på knappen nödsituation varp. Du hör ett konstigt kvävande ljud från motorerna rummet och luktar bränt kretsar. &quot;Stupid piece of crap!&quot;, Skriker du, sparkade på datorn. Datorn avger piper av PROTEST som du förbereder dig för inkommande striden ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Ditt skepp attackeras av [player]. Prova som du kanske, kan du inte försvara dig mot [player] &#39;s överlägsna vapen. Ditt skepp förstördes.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Ditt fartyg attackerades av [player]. Du kamp för en stund, sedan kampen går sönder. Du förlorade [armor] punkter rustning och [fighters] krigare i skärmytsling.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Du slår [mines] gruvor vid resor inom sektorn [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Ditt skepp förstördes av ett minfält i sektor [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Din planet [planet_name] i sektorn [sector] besegrades i strid av [name]. Lyckligtvis starka lojalitet med era medborgare spelas i din favör. De har tappert valt att förstöra planeten istället för att falla i fiendens händer. Du ordna superb begravningar i minnet på din trogna folk.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Din planet [planet_name] i sektorn [sector] besegrades i strid med den usla [name]. Människorna på jorden välkomna sina nya härskare. Du hör ett vittnesmål på FNN: &quot;Vi är glada att bli av med den gamla fart! Vi vill inte ha någon stinkande loser som inte kan skydda oss!&quot;. Du svär att få dem att betala för sin arrogans.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Din planet [planet_name] i sektorn [sector] attackerades av [name]. Medborgarna organiserade en Valliant försvar dock och lyckades förstöra motståndaren. De bärga del resurser från rymden: [goods] varor, [ore] malm, [organics] organiska och [salvage]% av fartygets värde [credits] krediter.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Victory!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] förstördes i sektorn [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Sector försvar förstörs";
$l_log_text["LOG5_KABAL_ATTACK"] = "Attackerande [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Attack";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Ni har förstört [fighters] patrullerar fighters inom sektorn [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Fighters förstöras";
$l_log_text["LOG5_DEFS_KABOOM"] = "Du förstördes av en krigare kraft inom sektorn [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Du fångade en planet som tillhör [owner]. Det hade [cols] kolonister och [credits] krediter på den.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet fångat!";
$l_log_text["LOG5_STORAGE_EWD"] = "Din planet är överraskad av [player] &#39;s attack. En av dina lagrade fartyg gjort en Emergency Warp till [sector] och landade på planeten [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Lagrade Ship Emergency varp!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "En lagrad fartyg Emergency Warp Device misslyckades! Lagrade skeppet fångades av [player] efter att de besegrat din planet!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "En lagrad skepp tillfångatogs av [player] efter de besegrade en av dina planeter!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Ditt skepp beslagtogs av [player]. Göra för att alltför angrepp på Bounty spelare [player] har konfiskerats ett av dina skepp ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Din planet konfiskerades av [player]. Göra för att alltför angrepp på Bounty spelare [player] har konfiskerats en av dina planeter ([name]) inom sektorn [sector] värde [score] krediter.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "En lagrad skepp suicided när [player] besegrade en av dina planeter och försökte fånga den!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "Ship Sensorer upptäckt ett inkommande Sector missiler som avfyras från [sector] av [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "En sektor Missile eldas med [player] sågs snett in i branschen och du undvek attacken.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sector Missile Undanmanöver!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Du upptäckts [player] är ett inkommande Sector Missile att försöka fastställa på ditt skepp, men din kappa generatorer lyckades lura Sector missiler sensorn kretsar.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sector Missile Cloak lyckad!";
$l_log_text["LOG5_SM_EWD"] = "Du är förvånad [player] &#39;s Sector missilattack och engagera Emergency Warp Device hoppa till en okänd sektor.";
$l_log_title["LOG5_SM_EWD"] = "Sector Missile Emergency varp!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Din sensorer [player] &#39;s Sector missilattack och engagera Emergency Warp Device. Du hör ett konstigt kvävande ljud från motorerna rummet och luktar bränt kretsar. &quot;Stupid piece of crap!&quot;, Skriker du, sparkade på datorn. Du brace för effekt!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Ditt fartyg attackerades av [player] med hjälp av en sektor missil. Du förlorade [armor] punkter rustning och [energy] enheter energi i attacken.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Ditt skepp förstördes av en sektor missil från [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Ditt skepp blev attackerad av en sond som ägs av [player] inom sektorn [sector]. Du förlorade [armor] punkter rustning och [energy] enheter energi i attacken.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] överlevt en attack av din sonden i sektorn [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Din sond förstörde fartyg som ägs av [player] inom sektorn [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Ditt skepp förstördes av en sond från [player] inom sektorn [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "Efter Action Krigsrapport";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name] har genomsökt din planet [planet_name] i sektorn [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet scan";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] har försökt att scanna din planet [planet_name] inom sektorn [sector], men misslyckades.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planet scan failed";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] har genomsökt ditt skepp.";
$l_log_title["LOG6_SHIP_SCAN"] = "Ship scan";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] har försökt att scanna ditt skepp, men misslyckades.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Ship scan failed";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] i [sector] kan inte upprätthålla sin befolkning! Fler organiska behövs. [starvation] kolonisatörerna dog av svält. Kolonisterna började svälter den [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Detected Inkommande Ship";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Probe Scanned Inkommande Ship";
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

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] försökte skanna en av dina sonder inom sektorn [sector], men misslyckades.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "En av dina sonder inom sektorn [sector] skannades av [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "En av dina sonder inom sektorn [sector] attackerades och förstördes av [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "En av dina Probe Hunters har förstört en [probe_type] ägs av [name] i [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe Hunter förstöras [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Din [probe_type] i sektorn [sector] attackerades och förstördes av en sond Hunter som ägs av [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Din Probe Hunter inom sektorn [sector] förlorades när den resulterande explosionen från sitt angrepp på [probe_type] ägs av [name] insvept det.";
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
