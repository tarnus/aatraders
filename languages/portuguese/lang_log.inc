<?php
$l_log_months = "array ( &#39;Janeiro&#39;, &#39;Fevereiro&#39;, &#39;Março&#39;, &#39;Abril&#39;, &#39;Maio&#39;, &#39;Junho&#39;, &#39;Julho&#39; Agosto &#39;,&#39; Setembro &#39;,&#39; Outubro &#39;,&#39; Novembro &#39;,&#39; Dezembro &#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;Fev&#39;, &#39;Mar&#39;, &#39;Abr&#39;, &#39;Maio&#39;, &#39;Jun&#39;, &#39;Jul&#39;, &#39;Ago&#39;, &#39;Set&#39;, &#39;Out&#39;, &#39;Nov&#39;, &#39;Dez&#39;)";
$l_log_pod = "Felizmente, você tinha uma cápsula de escape!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s Log";
$l_log_start = "Entrar entrada para";
$l_log_end = "Fim da entrada de log para";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Selecione um Log:";
$l_log_general = "Registro Geral";
$l_log_dig = "Dignitário Entrar";
$l_log_spy = "Spy Entrar";
$l_log_disaster = "Desastres Planet Entrar";
$l_log_nova = "Dispositivo Nova Entrar";
$l_log_attack = "Ataque Entrar";
$l_log_scan = "Registo de Verificação";
$l_log_starv = "Planeta Fome Entrar";
$l_log_probe = "Sonda Entrar";
$l_log_autotrade = "Auto Comércio Entrar";
$l_log_combined = "Combinada Entrar";


// Log entry data

$l_log_text["LOG_LOGIN"] = "Você se identificou, a partir de [ip].";
$l_log_title["LOG_LOGIN"] = "Identificados";
$l_log_text["LOG_LOGOUT"] = "Você saiu, a partir de [ip].";
$l_log_title["LOG_LOGOUT"] = "Logged out";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Database Error Occurred";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Resultado de Acção de Combate";
$l_log_title["LOG0_RAW"] = "Aviso";
$l_log_text["LOG0_PLANET_EJECT"] = "Você foi expulso do planeta no setor [sector] porque [name] saiu do time.";
$l_log_title["LOG0_PLANET_EJECT"] = "Ejected!";
$l_log_text["LOG0_BADLOGIN"] = "Houve uma tentativa de login má [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Bad login";
$l_log_title["LOG0_TOW"] = "Rebocado!";
$l_log_text["LOG0_TOW"] = "Seu navio foi rebocado pelo setor [sector] para o setor [newsector], porque o seu nível médio de tecnologia excedeu o valor limite de [hull] ou você tem um navio de armazenamento.";
$l_log_text["LOG0_HARAKIRI"] = "Você estava cansada de capitanear esta barca do espaço, assim que você decidiu que o Universo estaria melhor sem ele. Autorizado por [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] rejeitou o convite para integrar a sua equipa, [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Convite rejeitado";
$l_log_text["LOG0_TEAM_RENAME"] = "Você tem mudado a sua equipa a equipa [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Equipe renomeado";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Seu coordenador de equipe renomeou a equipa para equipa [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Equipe renomeado";
$l_log_text["LOG0_TEAM_KICK"] = "Você foi expulso do time [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Ejetado da equipe!";
$l_log_text["LOG0_TEAM_CREATE"] = "Você criou uma nova equipa, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Criado novo time";
$l_log_text["LOG0_TEAM_LEAVE"] = "Você deixou a equipa [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Equipe de Esquerda";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Você deixou o time [team]. Você abandonou a liderança da equipa para [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Equipe de Esquerda";
$l_log_text["LOG0_TEAM_LEAD"] = "Seu coordenador de equipe decidiu sair [team]. Você foi designado para ocupar o seu lugar.";
$l_log_title["LOG0_TEAM_LEAD"] = "Promoção!";
$l_log_text["LOG0_TEAM_JOIN"] = "Você se juntaram à equipe [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Registrado em equipe";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name], aceitou participar [team]. Isto traz-lhe mais um passo para a dominação da galáxia.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Novo membro da equipe";
$l_log_text["LOG0_TEAM_INVITE"] = "Você foi convidado para fazer parte [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Convite";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] deixou a sua equipa.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Equipe perde um membro";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] se autodestruiu de ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Autodestruição";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] tinha [quantity] [type], com no máximo tem de [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Valor ilegal navio";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] tentou capturar [defender] &#39;s planeta no sector [sector]. Planeta foi destruído em vez disso.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet destruídos";
$l_log_text["LOG0_defense_DEGRADE"] = "Fighters Setor defesas no sector [sector] degradadas por [degrade] por cento, devido à energia insuficiente.";
$l_log_title["LOG0_defense_DEGRADE"] = "Defesas Setor degradadas.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Player [player] no endereço IP [ip] tentou explorar a qualquer um chute da equipe batota. Seu navio foi destruído.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Equipe Exploit Usado";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Você reivindicou uma recompensa de [amount] de créditos para a destruição do navio pertencente bounty_on [bounty_on]. O prémio foi colocado por [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Bounty anunciada.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Sua recompensa em [bounty_on] tiver sido pago o montante de [amount] créditos.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Bounty pago.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "A generosidade Fedration em [bounty_on], foi taxado pelo valor de [amount] créditos.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Bounty Imposto Pago.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Sua recompensa em [bounty_on] para o montante de [amount] créditos foi restituído.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty Reembolsado.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "A Federação tem colocado uma recompensa por você, no valor de [amount] créditos.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federação Bounty!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "A Aliança tem colocado uma recompensa por você, no valor de [amount] créditos.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Aliança Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Créditos Player [name] transferido [sum] soma à sua conta do IGB.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Créditos transferidos";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Transferiu [sum] soma de créditos para o jogador [name] &#39;s IGB conta.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Créditos transferidos";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] planeta planetname [planetname] (planetid [planetname]) owned by [owner] tornou-se independente. Média Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet fui independente.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Independente do planeta [planetname] (planetid [planetid]) owned by [owner] no [sector] foi eliminada. Média Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Independente Planet purgado.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Nunca planeta Owned [planetname] (planetid [planetid]), criado em [date] no [sector] foi eliminada. Média Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Nunca Owned Planet purgado.";
$l_log_text["LOG0_TEAM_CANCEL"] = "Você está convite para fazer parte [team] foi cancelada.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Convite Cancelado";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "A id [id] no planeta [planet_name] no sector [sector] Tem início a construção de produção.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "A id [id] no planeta [planet_name] no sector [sector] decrescente taxa de natalidade.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "A id [id] no planeta [planet_name] no setor [sector] crescente taxa de natalidade.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "A id [id] no planeta [planet_name] no sector [sector] começou a procurar por spys naquele planeta.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "A id [id] no planeta [planet_name] no sector [sector] começa a aumentar a produção de crédito.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Dignitário [id] no planeta planet_name [planet_name] desviou [data] créditos e doados para você!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Seu jogador dignitário detectado [name] &#39;s espião em seu planeta [planet_name] no sector [sector]. O espião é morto agora.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Sua escavação [id] no planeta [planet_name] no sector [sector] morreu vítima de um terrível cataclismo com o planeta.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Sua escavação [id] sobre o jogador [name] &#39;s navio [shipname] morreu vítima de um terrível cataclismo com esse navio.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "A id [id] no planeta [planet_name] no sector [sector], construído [data] planetária torpedos!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "A id [id] no planeta [planet_name] no sector [sector], construído [data] combatentes planetária!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Você perdeu seu espião [id] [name] &#39;s navio [shipname], uma vez que o jogador comprou um novo navio.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] tentou enviar um espião para o seu planeta [planet_name] no sector [sector], mas seus sensores detectaram a espionagem e ele está morto agora.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Seu espião [id] no planeta [planet_name] no sector [sector] começa a sabotagem. A produção é reduzida por [data] sobre esse planeta.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Seu espião [id] no planeta [planet_name] no sector [sector] diminuiu o índice de natalidade por [data] sobre esse planeta.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "Seu espião [id] no planeta [planet_name] no sector [sector] inicia a coleta de juros planeta [data] para você.";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Seu espião [id] no planeta [planet_name] no sector [sector] roubou [data] créditos para você!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Seu espião [id] no planeta [planet_name] no sector [sector] destruídos [data] planetária torpedos!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Seu espião [id] no planeta [planet_name] no sector [sector] destruídos [data] combatentes planetária!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Seu espião [id] no planeta [planet_name] no sector [sector] capturou esse planeta! Você é um cara de sorte ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] &#39;s espião capturado o planeta [planet_name] no sector [sector]! Parece que a idéia é sábio limpeza de seus planetas mais freqüência ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Não há mensagens em seu espião [id] no planeta [planet_name] no sector [sector], por um longo tempo - parece que a capa de seu dispositivo não poderia cobrir o suficiente e ele é morto.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Seu Sensores detectaram um nome [name] &#39;s espião em seu planeta [planet_name] no sector [sector]. O espião é morto agora.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "Não há mensagens em seu espião [id] sobre o jogador [name] &#39;s navio [shipname] há muito tempo - parece que a capa de seu dispositivo não poderia cobrir o suficiente e ele é morto.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Seu espião [id] no planeta [planet_name] no sector [sector] morreu vítima de um terrível cataclismo com o planeta.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Seu espião [id] sobre o jogador [name] &#39;s navio [shipname] morreu vítima de um terrível cataclismo com esse navio.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Seu espião [id] do planeta [planet_name] no sector [sector] infiltra um jogador [playername] &#39;s navio [shipname] e os actos agora lá.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Seu espião [id] do jogador [playername] &#39;s navio [shipname] se infiltra em um planeta [planet_name] no sector [sector] e os actos agora lá.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Seu número de dignitário [DIG] no planeta [PLANET], foi capturado estelionatário. Você pode querer anulá-las.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Seu planeta [planet_name] no sector [sector] foi destruída com uma bomba de Nova por [name]. Absolutamente nada, continua a marcar os planetas existência anterior.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Seu navio foi destruído com uma Nova Bombardeado por [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Seu planeta [planet_name] no sector [sector] foi bombardeada por [name]. Você usou [beams] ea energia [torps] torpedos em sua defesa. Você perdeu [figs] combatentes.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Seu planeta [planet_name] no sector [sector], foi derrotado e capturado pelos miseráveis [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] foi flagrado em um vetor de ataque, mas suas habilidades grande piloto e bons motores permitiu-lhe passar a perna ao inimigo.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Ação evasiva!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Você detectou [player] &#39;s tentando consertar as armas em seu navio, mas os geradores seu manto conseguiu enganar os circuitos do inimigo sensor primitivo.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Manto de sucesso!";
$l_log_text["LOG5_ATTACK_EWD"] = "Você está surpreso por [player] O ataque traiçoeiro. Você pode ver as ogivas de entrada como chegar freneticamente para o botão de urdidura de emergência. A borra mundo ao seu redor e, por um milisegundo, você pensa que você está morto. Quando você finalmente abrir os olhos, você verá que foram transportados com segurança em outros lugares. Mas onde exatamente, não sei ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Urdidura de Emergência!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Seu sensores detectam [player] &#39;s do navio em um vetor de ataque. &quot;É melhor prevenir do que remediar&quot;, você pensa, bater no botão urdidura de emergência. Você ouve um barulho estranho vindo de asfixia na sala de motores e cheiro de queimado circuitos. &quot;Pedaço estúpido de merda!&quot;, Você gritar, chutar no computador. O computador emite sinais sonoros de protesto como se preparar para a batalha de entrada ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Seu navio está sendo atacado por [player]. Tente como você pode, você não pode defender-se contra o [player] &#39;s armamento superior. Seu navio foi destruído.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Seu barco foi atacado por [player]. Você batalha por um tempo, então, a luta quebre. Você perdeu [armor] pontos de armadura e [fighters] combatentes no conflito.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Você bateu [mines] minas quando viajam sector [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Seu navio foi destruído por um campo minado no sector [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Seu planeta [planet_name] no sector [sector] foi derrotado na batalha por [name]. Felizmente, a forte lealdade de seus cidadãos jogado em seu favor. Eles têm escolhido bravamente para destruir o planeta, em vez de tê-lo cair em mãos inimigas. Você organiza funerais soberba, a memória de seu povo fiel.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Seu planeta [planet_name] no sector [sector] foi derrotado na batalha pelos miseráveis [name]. Os povos do planeta, bem-vindo o novo governador. Você ouve um testemunho sobre FNN: &quot;Nós estamos contentes de ser livrado desse velhote! Nós não queremos nenhum perdedor fedorentos que não podem proteger-nos!&quot;. Você jura para fazê-los pagar por sua arrogância.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Seu planeta [planet_name] no sector [sector] foi atacado por [name]. Os cidadãos organizaram uma defesa Valliant no entanto, e conseguiram destruir o adversário. Eles salvar alguns recursos dos detritos espaciais: [goods] bens, [ore] minério, [organics] orgânicas e [salvage]% do valor do navio de [credits] créditos.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Vitória!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] foram destruídos no sector [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Setor defesas destruídas";
$l_log_text["LOG5_KABAL_ATTACK"] = "Atacando [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Ataque";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Você destruiu [fighters] combatentes patrulhamento no setor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Fighters destruídos";
$l_log_text["LOG5_DEFS_KABOOM"] = "Você foi destruída por uma força de combatentes no sector [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Você capturou um planeta pertencente ao proprietário [owner]. Tinha [cols] colonos e dos [credits] créditos sobre ele.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet capturado!";
$l_log_text["LOG5_STORAGE_EWD"] = "Seu planeta é surpreendido por [player] &#39;s ataque. Um de seus navios armazenados fez uma urdidura de emergência para o setor [sector] e pousou no planeta [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Armazenado Ship warp Emergência!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "Um dispositivo de emergência navios armazenados Warp FAILED! O navio foi capturado por armazenados [player] depois de terem derrotado o seu planeta!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "Um navio foi capturado por armazenados [player] depois de terem derrotado um de seus planetas!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Seu navio foi confiscado por [player]. Não aos ataques excessivos jogadores generosidade do jogador [player], foi confiscado um de seus navios (navio [player]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Seu planeta foi confiscado por [player]. Não aos ataques excessivos jogadores generosidade do jogador [player], foi confiscado um de seus planetas (nome [player]) no sector [sector] vale [score] créditos.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "Um navio armazenados suicidado quando [player] derrotou um de seus planetas e tentou capturá-lo!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "Um míssil disparado por Sector [player] foi detectada distorção no setor e que escapou do ataque.";
$l_log_title["LOG5_SM_OUTMAN"] = "Setor de Mísseis ação evasiva!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Você detectou [player] &#39;s uma entrada do Setor de Mísseis tentando consertar a sua nave, mas os geradores seu manto conseguiu enganar o Setor de circuitos sensores Mísseis.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Setor de Mísseis Manto de sucesso!";
$l_log_text["LOG5_SM_EWD"] = "Você está surpreso por [player] &#39;s Setor de ataque de mísseis e envolver o dispositivo de emergência Warp saltar para um setor desconhecido.";
$l_log_title["LOG5_SM_EWD"] = "Setor de Mísseis warp Emergência!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Seu sensores detectam [player] &#39;s Setor de ataque de mísseis e envolver o dispositivo de emergência Warp. Você ouve um barulho estranho vindo de asfixia na sala de motores e cheiro de queimado circuitos. &quot;Pedaço estúpido de merda!&quot;, Você gritar, chutar no computador. Você preparar para impacto!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Seu barco foi atacado por [player], utilizando um míssil Setor. Você perdeu [armor] pontos de armadura e [energy] unidades de energia no ataque.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Seu navio foi destruído por um míssil do Setor de [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Seu barco foi atacado por uma sonda de propriedade de [player] no sector [sector]. Você perdeu [armor] pontos de armadura e [energy] unidades de energia no ataque.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] sobreviveu a um ataque por sua sonda no sector [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Seu destruiu o navio sonda de propriedade de [player] no sector [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Seu navio foi destruído por uma sonda de [player] no sector [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "Depois de Acção Relatório de Combate";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name], foi verificado o seu planeta [planet_name] no sector [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet scan";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] tentou fazer a varredura de seu planeta [planet_name] no sector [sector], mas não conseguiu.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Planet digitalização falhou";
$l_log_text["LOG6_SHIP_SCAN"] = "[player], foi verificado o seu navio.";
$l_log_title["LOG6_SHIP_SCAN"] = "Envio de digitalização";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] tentou analisar o seu navio, mas não conseguiu.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Envio de digitalização falhou";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] no [sector], não pode sustentar a sua população! Mais produtos orgânicos são necessários. [starvation] colonos morreu de fome. Os colonos começaram a passar fome [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Sonda Detectado entrada de navios";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Scanned Probe entrada de navios";
$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SECTOR defenses in [sector] destroy your probe.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] = "Sonda Destroyed";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>You do not have enough turns for probe [probe_id] to move to [sector]</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] = "Sonda Report";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"] = "<font color='#00ff00'>Moving to sector [target_sector] is not allowed</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] = "Sonda Report";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Probe [probe_id] in sector [sector] detected [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] tentou digitalizar uma de suas sondas no sector [sector], mas não conseguiu.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "Uma de suas sondas no sector sector [sector] foi digitalizada por [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "Uma de suas sondas no sector sector [sector] foi atacado e destruído por [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "Um de seus Probe Hunters destruiu um probe_type [probe_type] propriedade de [name] no [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Sonda Hunter destruídos [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Seu probe_type [probe_type] no sector [sector] foi atacado e destruído por um caçador Probe propriedade de [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Seu Probe Hunter no sector [sector] foi perdida quando a explosão resultante do seu ataque à probe_type [probe_type] propriedade de [name] envolveu-lo.";
$l_log_title["LOG9_PROBEHUNTER_EXPLODED"] 		= "Probe Hunter Probe <font color='yellow'>Destroyed</font>";

// Auto Trade Logs

$l_log_text["LOG10_AUTOTRADE"]="<font color=yellow>Auto Trade for [planetname] in sector [sector] for [totalcost] credits.<br>Goods: [goodsamount] @ [goodsprice] credits - Ore: [oreamount] @ [oreprice] credits - Organics: [organicsamount] @ [organicsprice] credits - Energy: [energyamount] @ [energyprice] credits - Colonists: [colonistamount] @ [colonistprice] credits<br></font>";
$l_log_title["LOG10_AUTOTRADE"] = "Auto Trade Report";
$l_log_text["LOG10_AUTOTRADE_ABORTED"]="<font color='#00ff00'>Auto Trade for [planetname] in sector [sector] was aborted due to enemy sector defense in sector [destsector].<br></font>";
$l_log_title["LOG10_AUTOTRADE_ABORTED"] = "Auto Trade Report";

?>
