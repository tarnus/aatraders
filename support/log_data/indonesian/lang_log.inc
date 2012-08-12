<?php
$l_log_months = "array ( &#39;Januari&#39;, &#39;Februari&#39;, &#39;Februari&#39;, &#39;April&#39;, &#39;Maret&#39;, &#39;Juni&#39;, &#39;Juli&#39;, &#39;Agustus&#39;, &#39;September&#39;, &#39;Oktober&#39;, &#39;Nopember&#39;, &#39;Desember&#39;)";
$l_log_months_short = "array ( &#39;Jan&#39;, &#39;Peb&#39;, &#39;Mar&#39;, &#39;Apr&#39;, &#39;Mei&#39;, &#39;Jun&#39;, &#39;Jul&#39;, &#39;Agustus&#39;, &#39;Sep&#39;, &#39;Okt&#39;, &#39;Nop&#39;, &#39;Des&#39;)";
$l_log_pod = "Untungnya, Anda memiliki pod pelarian!";
$l_log_nopod 		 = "<font color=yellow><b>You did not have an escape pod, you died.</b></font>";
$l_log_log = "[player] &#39;s log";
$l_log_start = "Entri log";
$l_log_end = "Akhir dari entri log untuk";
$l_log_click 		 = "Click <A HREF=main.php><font color=#00ff00>here</font></A> to return to the main menu.";
$l_log_select = "Pilih Log:";
$l_log_general = "Log umum";
$l_log_dig = "Pembesar Log";
$l_log_spy = "Spy Log";
$l_log_disaster = "Planet Bencana Log";
$l_log_nova = "Nova Device Log";
$l_log_attack = "Attack Log";
$l_log_scan = "Scan Log";
$l_log_starv = "Planet Kelaparan Log";
$l_log_probe = "Probe Log";
$l_log_autotrade = "Perdagangan auto log";
$l_log_combined = "Gabungan Log";


// Log entry data

$l_log_text["LOG_LOGIN"] = "Anda telah login, dari [ip].";
$l_log_title["LOG_LOGIN"] = "Login";
$l_log_text["LOG_LOGOUT"] = "Anda telah log out, dari [ip].";
$l_log_title["LOG_LOGOUT"] = "Logout";

// General Log Entries

$l_log_title["LOG0_ADMIN_DBERROR"] = "Terjadi Kesalahan Database";
$l_log_title["LOG0_ADMIN_COMBAT"] = "Aksi Combat Hasil";
$l_log_title["LOG0_RAW"] = "Pemberitahuan";
$l_log_text["LOG0_PLANET_EJECT"] = "Anda telah diusir dari planet di sektor [sector] karena [name] meninggalkan tim.";
$l_log_title["LOG0_PLANET_EJECT"] = "Dikeluarkan!";
$l_log_text["LOG0_BADLOGIN"] = "Telah ada usaha login yang buruk dari [ip].";
$l_log_title["LOG0_BADLOGIN"] = "Bad login";
$l_log_title["LOG0_TOW"] = "Diderek!";
$l_log_text["LOG0_TOW"] = "Kapal anda telah ditarik dari bidang [sector] untuk sektor [newsector] karena tingkat teknologi rata-rata Anda melebihi nilai batas [hull] atau Anda memiliki kapal di gudang.";
$l_log_text["LOG0_HARAKIRI"] = "Anda bosan tongkang captaining ruang ini, sehingga Anda memutuskan bahwa alam semesta akan lebih baik tanpa itu. Authorized oleh [ip].";
$l_log_title["LOG0_HARAKIRI"] 		= "<font color=red>Self-destructed!</font>";
$l_log_text["LOG0_TEAM_REJECT"] = "[player] telah menolak undangan untuk bergabung dengan tim Anda, [teamname].";
$l_log_title["LOG0_TEAM_REJECT"] = "Undangan ditolak";
$l_log_text["LOG0_TEAM_RENAME"] = "Anda telah berganti nama tim Anda untuk [team].";
$l_log_title["LOG0_TEAM_RENAME"] = "Tim nama";
$l_log_text["LOG0_TEAM_M_RENAME"] = "Nama koordinator tim Anda tim untuk [team].";
$l_log_title["LOG0_TEAM_M_RENAME"] = "Tim nama";
$l_log_text["LOG0_TEAM_KICK"] = "Anda telah dikeluarkan dari tim [team].";
$l_log_title["LOG0_TEAM_KICK"] = "Dikeluarkan dari tim!";
$l_log_text["LOG0_TEAM_CREATE"] = "Anda telah membuat tim baru, [team].";
$l_log_title["LOG0_TEAM_CREATE"] = "Dibuat tim baru";
$l_log_text["LOG0_TEAM_LEAVE"] = "Anda telah meninggalkan tim [team].";
$l_log_title["LOG0_TEAM_LEAVE"] = "Waktu tim";
$l_log_text["LOG0_TEAM_NEWLEAD"] = "Anda telah meninggalkan tim [team]. Anda melepaskan tim kepemimpinan untuk [name].";
$l_log_title["LOG0_TEAM_NEWLEAD"] = "Waktu tim";
$l_log_text["LOG0_TEAM_LEAD"] = "Koordinator tim Anda telah memutuskan untuk meninggalkan [team]. Anda telah ditunjuk untuk mengambil tempatnya.";
$l_log_title["LOG0_TEAM_LEAD"] = "Promosi!";
$l_log_text["LOG0_TEAM_JOIN"] = "Anda telah bergabung dengan tim [team].";
$l_log_title["LOG0_TEAM_JOIN"] = "Bergabung dengan tim";
$l_log_text["LOG0_TEAM_NEWMEMBER"] = "[name] telah menerima untuk bergabung [team]. Ini membawa Anda satu langkah lebih jauh ke galaksi dominasi.";
$l_log_title["LOG0_TEAM_NEWMEMBER"] = "Anggota tim baru";
$l_log_text["LOG0_TEAM_INVITE"] = "Anda telah diundang untuk menjadi bagian dari [team].";
$l_log_title["LOG0_TEAM_INVITE"] = "Undangan";
$l_log_text["LOG0_TEAM_NOT_LEAVE"] = "[player] telah meninggalkan tim Anda.";
$l_log_title["LOG0_TEAM_NOT_LEAVE"] = "Tim kehilangan seorang anggota";
$l_log_text["LOG0_ADMIN_HARAKIRI"] = "[player] telah hancur diri dari ip [ip].";
$l_log_title["LOG0_ADMIN_HARAKIRI"] = "Merusak diri";
$l_log_text["LOG0_ADMIN_ILLEGVALUE"] = "[player] telah [quantity] [type], dengan maks memegang dari [holds]";
$l_log_title["LOG0_ADMIN_ILLEGVALUE"] = "Nilai kapal ilegal";
$l_log_text["LOG0_ADMIN_PLANETDEL"] = "[attacker] telah mencoba untuk menangkap [defender] &#39;s planet di sektor [sector]. Planet hancur sebagai gantinya.";
$l_log_title["LOG0_ADMIN_PLANETDEL"] = "Planet hancur";
$l_log_text["LOG0_defense_DEGRADE"] = "Sektor pertahanan di sektor Fighters [sector] terdegradasi oleh [degrade] persen karena energi tidak mencukupi.";
$l_log_title["LOG0_defense_DEGRADE"] = "Sektor pertahanan terdegradasi.";
$l_log_text["LOG0_CHEAT_TEAM"] = "Player [player] di IP address [ip] mencoba memanfaatkan tendangan tim siapa pun menyontek. Kapalnya hancur.";
$l_log_title["LOG0_CHEAT_TEAM"] = "Tim Exploit Digunakan";
$l_log_text["LOG0_BOUNTY_CLAIMED"] = "Anda mengklaim hadiah dari [amount] kredit untuk penghancuran kapal milik [bounty_on]. Karunia ditempatkan oleh [placed_by].";
$l_log_title["LOG0_BOUNTY_CLAIMED"] = "Bounty Diklaim.";
$l_log_text["LOG0_BOUNTY_PAID"] = "Karunia Anda pada [bounty_on] telah dibayar untuk jumlah [amount] kredit.";
$l_log_title["LOG0_BOUNTY_PAID"] = "Bounty Dibayar.";
$l_log_text["LOG0_BOUNTY_TAX_PAID"] = "The Fedration karunia pada [bounty_on] telah dipotong pajak untuk jumlah [amount] kredit.";
$l_log_title["LOG0_BOUNTY_TAX_PAID"] = "Karunia Pajak Dibayar.";
$l_log_text["LOG0_BOUNTY_CANCELLED"] = "Karunia Anda pada [bounty_on] untuk jumlah [amount] kredit yang telah dikembalikan.";
$l_log_title["LOG0_BOUNTY_CANCELLED"] = "Bounty Dikembalikan.";
$l_log_text["LOG0_BOUNTY_FEDBOUNTY"] = "Federasi telah meletakkan karunia pada anda untuk jumlah [amount] kredit.";
$l_log_title["LOG0_BOUNTY_FEDBOUNTY"] = "Federasi Bounty!";
$l_log_text["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Aliansi telah meletakkan karunia pada anda untuk jumlah [amount] kredit.";
$l_log_title["LOG0_BOUNTY_ALLIANCEBOUNTY"] = "Aliansi Bounty!";
$l_log_text["LOG0_IGB_TRANSFER1"] = "Pemain [name] ditransfer [sum] kredit untuk account IGB Anda.";
$l_log_title["LOG0_IGB_TRANSFER1"] = "Credits ditransfer";
$l_log_text["LOG0_IGB_TRANSFER2"] = "Anda ditransfer [sum] kredit untuk pemain [name] &#39;s account IGB.";
$l_log_title["LOG0_IGB_TRANSFER2"] = "Credits ditransfer";
$l_log_text["LOG0_ADMIN_PLANETIND"] = "[sector] planet [planetname] ([planetid]) yang dimiliki oleh [owner] menjadi mandiri. Rata Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_PLANETIND"] = "Planet pergi independen.";
$l_log_text["LOG0_ADMIN_INDYPURGE"] = "Independen planet [planetname] ([planetid]) yang dimiliki oleh [owner] dalam [sector] sudah dibersihkan. Rata Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_INDYPURGE"] = "Planet Independen dibersihkan.";
$l_log_text["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Pernah Dimiliki planet [planetname] ([planetid]) dibuat pada [date] dalam [sector] sudah dibersihkan. Rata Tech: [avgtech]";
$l_log_title["LOG0_ADMIN_NEVEROWNEDPURGE"] = "Dimiliki Planet pernah dibersihkan.";
$l_log_text["LOG0_TEAM_CANCEL"] = "Kau undangan untuk menjadi bagian dari [team] telah dibatalkan.";
$l_log_title["LOG0_TEAM_CANCEL"] = "Undangan Dibatalkan";

// Dignitary Log Entries

$l_log_text["LOG1_DIG_PRODUCTION"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] bangunan mulai produksi.";
$l_log_title["LOG1_DIG_PRODUCTION"] = "<font color=#00FF00>Production Building  Started!</font>";
$l_log_text["LOG1_DIG_BIRTHDEC"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] penurunan angka kelahiran.";
$l_log_title["LOG1_DIG_BIRTHDEC"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG1_DIG_BIRTHINC"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] meningkatkan angka kelahiran.";
$l_log_title["LOG1_DIG_BIRTHINC"] = "<font color=#00FF00>Birthrate Increased!</font>";
$l_log_text["LOG1_DIG_SPYHUNT"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] mulai mencari spys di planet itu.";
$l_log_title["LOG1_DIG_SPYHUNT"] = "<font color=#00FF00>Spy Hunter!</font>";
$l_log_text["LOG1_DIG_INTEREST"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] kredit mulai meningkatkan produksi.";
$l_log_title["LOG1_DIG_INTEREST"] = "<font color=#00FF00>Interest Building Started!</font>";
$l_log_text["LOG1_DIG_MONEY"] = "Pembesar [id] di planet [planet_name] menggelapkan [data] kredit dan disumbangkan kepada Anda!";
$l_log_title["LOG1_DIG_MONEY"] = "<font color=#00FF00>You Recieved Embezzled  Credits!</font>";
$l_log_text["LOG1_DIG_KILLED_SPY"] = "Anda terdeteksi pemain terkemuka [name] &#39;s memata-matai planet Anda [planet_name] di sektor [sector]. Mata-mata dibunuh sekarang.";
$l_log_title["LOG1_DIG_KILLED_SPY"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG1_DIG_CATACLYSM"] = "Anda menggali [id] di planet [planet_name] di sektor [sector] tewas dalam bencana mengerikan dengan planet itu.";
$l_log_title["LOG1_DIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_SHIPDIG_CATACLYSM"] = "Anda menggali [id] pada pemain [name] &#39;s kapal [shipname] tewas dalam bencana mengerikan dengan kapal.";
$l_log_title["LOG1_SHIPDIG_CATACLYSM"] = "<font color=yellow>dig Lost!</font>";
$l_log_text["LOG1_DIG_TORPS"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] dibangun [data] planet torpedo!";
$l_log_title["LOG1_DIG_TORPS"] = "<font color=#00FF00>Torpedoes Built!</font>";
$l_log_text["LOG1_DIG_FITS"] = "Anda pembesar [id] di planet [planet_name] di sektor [sector] dibangun [data] planet pejuang!";
$l_log_title["LOG1_DIG_FITS"] = "<font color=#00FF00>Fighters Built!</font>";

// Spy Log Entries

$l_log_text["LOG2_SPY_NEWSHIP"] = "Anda kehilangan mata-mata [id] pada [name] &#39;s kapal [shipname], karena pemain membeli kapal baru.";
$l_log_title["LOG2_SPY_NEWSHIP"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_SEND_FAIL"] = "[name] mencoba mengirim mata-mata ke planet [planet_name] di sektor [sector], tapi Anda mendeteksi Sensor mata-mata dan ia terbunuh sekarang.";
$l_log_title["LOG2_SPY_SEND_FAIL"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SPY_SABOTAGE"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] mulai sabotase. Produksi berkurang oleh [data] pada planet itu.";
$l_log_title["LOG2_SPY_SABOTAGE"] = "<font color=#00FF00>Sabotage Started!</font>";
$l_log_text["LOG2_SPY_BIRTH"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] penurunan angka kelahiran oleh [data] pada planet itu.";
$l_log_title["LOG2_SPY_BIRTH"] = "<font color=#00FF00>Birthrate Decreased!</font>";
$l_log_text["LOG2_SPY_INTEREST"] = "";
$l_log_title["LOG2_SPY_INTEREST"] = "<font color=#00FF00>Interest Stealing Started!</font>";
$l_log_text["LOG2_SPY_MONEY"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] mencuri [data] kredit untuk Anda!";
$l_log_title["LOG2_SPY_MONEY"] = "<font color=#00FF00>Credits Have Stolen!</font>";
$l_log_text["LOG2_SPY_TORPS"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] hancur [data] planet torpedo!";
$l_log_title["LOG2_SPY_TORPS"] = "<font color=#00FF00>Torpedoes Destroyed!</font>";
$l_log_text["LOG2_SPY_FITS"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] hancur [data] planet pejuang!";
$l_log_title["LOG2_SPY_FITS"] = "<font color=#00FF00>Fighters Destroyed!</font>";
$l_log_text["LOG2_SPY_CPTURE"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] menangkap planet itu!! Anda adalah orang yang beruntung ...";
$l_log_title["LOG2_SPY_CPTURE"] = "<font color=#00FF00>PLANET CAPTURED!</font>";
$l_log_text["LOG2_SPY_CPTURE_OWNER"] = "[name] &#39;s mata-mata ditangkap planet Anda [planet_name] di sektor [sector]! Tampaknya bahwa adalah ide bijaksana pembersihan planet Anda lebih sering ...";
$l_log_title["LOG2_SPY_CPTURE_OWNER"] = "<font color=red>Planet Lost!</font>";
$l_log_text["LOG2_SPY_KILLED_SPYOWNER"] = "Tidak ada pesan dari mata-mata [id] di planet [planet_name] di sektor [sector] untuk waktu yang lama - tampak bahwa perangkat Jubah Anda tidak bisa menutupi dirinya cukup dan ia terbunuh.";
$l_log_title["LOG2_SPY_KILLED_SPYOWNER"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_KILLED"] = "Sensor mendeteksi Anda [name] &#39;s memata-matai planet Anda [planet_name] di sektor [sector]. Mata-mata dibunuh sekarang.";
$l_log_title["LOG2_SPY_KILLED"] = "<font color=yellow>Enemy Spy Killed!</font>";
$l_log_text["LOG2_SHIPSPY_KILLED"] = "Tidak ada pesan dari mata-mata [id] pada pemain [name] &#39;s kapal [shipname] untuk waktu yang lama - tampak bahwa perangkat Jubah Anda tidak bisa menutupi dirinya cukup dan ia terbunuh.";
$l_log_title["LOG2_SHIPSPY_KILLED"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_CATACLYSM"] = "Anda mata-mata [id] di planet [planet_name] di sektor [sector] tewas dalam bencana mengerikan dengan planet itu.";
$l_log_title["LOG2_SPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SHIPSPY_CATACLYSM"] = "Anda mata-mata [id] pada pemain [name] &#39;s kapal [shipname] tewas dalam bencana mengerikan dengan kapal.";
$l_log_title["LOG2_SHIPSPY_CATACLYSM"] = "<font color=yellow>Spy Lost!</font>";
$l_log_text["LOG2_SPY_TOSHIP"] = "Anda mata-mata [id] dari planet [planet_name] di sektor [sector] infiltrat seorang pemain [playername] &#39;s kapal [shipname] dan bertindak sekarang ada.";
$l_log_title["LOG2_SPY_TOSHIP"] = "<font color=#00FF00>Spy Infiltrates Enemy Ship!</font>";
$l_log_text["LOG2_SPY_TOPLANET"] = "Anda mata-mata [id] dari pemain [playername] &#39;s kapal [shipname] infiltrat sebuah planet [planet_name] di sektor [sector] dan bertindak sekarang ada.";
$l_log_title["LOG2_SPY_TOPLANET"] = "<font color=#00FF00>Spy Infiltrates Enemy Planet!</font>";
$l_log_text["LOG2_SPY_FOUND_EMBEZZLER"] = "Nomor pembesar Anda [DIG] di planet [PLANET] telah tertangkap menggelapkan. Anda mungkin ingin untuk mengabaikan mereka.";
$l_log_title["LOG2_SPY_FOUND_EMBEZZLER"] 	= "<font color=yellow>Embezzler found!</font>";

// Nova Bomb Logs

$l_log_text["LOG4_PLANET_novaED_D"] = "Planet Anda [planet_name] di sektor [sector] dihancurkan dengan Nova Bomb oleh [name]. Sama sekali tak ada yang tersisa untuk menandai keberadaan mantan planet.";
$l_log_title["LOG4_PLANET_novaED_D"] 	= "<font color=yellow>Planet destroyed with a Nova Bomb</font>";
$l_log_text["LOG4_SHIP_novaED_D"] = "Kapal anda hancur dengan Nova Dibom oleh [name].";
$l_log_title["LOG4_SHIP_novaED_D"] 	= "<font color=yellow>Ship destroyed with a Nova Bomb</font>";

// Attack Logs

$l_log_text["LOG5_PLANET_BOMBED"] = "Planet Anda [planet_name] di sektor [sector] dibom oleh [name]. Anda menggunakan [beams] energi dan [torps] torpedo dalam pertahanan. Kau kehilangan [figs] pejuang.";
$l_log_title["LOG5_PLANET_BOMBED"] = "<font color=red>Planet bombed!</font>";
$l_log_text["LOG5_PLANET_YOUR_CAPTURED"] = "Planet Anda [planet_name] di sektor [sector] dikalahkan dan ditangkap oleh malang [name].";
$l_log_title["LOG5_PLANET_YOUR_CAPTURED"]  = "<font color=red>Planet captured!</font>";
$l_log_text["LOG5_ATTACK_OUTMAN"] = "[player] terlihat di sebuah serangan vektor, tapi Anda keterampilan pilot besar dan mesin baik diizinkan Anda untuk mengakali musuh.";
$l_log_title["LOG5_ATTACK_OUTMAN"] = "Tindakan menghindar!";
$l_log_text["LOG5_ATTACK_OUTSCAN"] = "Anda terdeteksi [player] &#39;s senjata berusaha untuk memperbaiki kapal Anda, tetapi Anda generator jubah berhasil mengelabui sensor primitif musuh sirkuit.";
$l_log_title["LOG5_ATTACK_OUTSCAN"] = "Jubah sukses!";
$l_log_text["LOG5_ATTACK_EWD"] = "Anda terkejut dengan [player] &#39;s serangan berbahaya. Anda dapat melihat hulu ledak yang masuk ketika anda mencapai panik untuk tombol lungsin darurat. Mengaburkan dunia di sekitar Anda dan, untuk milisecond, Anda pikir Anda sudah mati. Ketika Anda akhirnya membuka mata Anda, Anda melihat bahwa Anda adalah diangkut dengan aman di tempat lain. Tapi di mana tepatnya, kau tidak tahu ...";
$l_log_title["LOG5_ATTACK_EWD"] = "Darurat warp!";
$l_log_text["LOG5_ATTACK_EWDFAIL"] = "Sensor Anda mendeteksi [player] &#39;s kapal pada vektor serangan. &quot;Lebih baik aman daripada menyesal&quot;, Anda berpikir, menekan tombol lungsin darurat. Anda aneh tersedak mendengar suara yang datang dari kamar mesin dan bau terbakar sirkuit. &quot;Bodoh sepotong crap!&quot;, Anda berteriak, menendang di komputer. Memancarkan komputer berbunyi &#39;bip&#39; protes ketika Anda mempersiapkan diri untuk pertempuran yang masuk ...";
$l_log_title["LOG5_ATTACK_EWDFAIL"] 	= "Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_ATTACK_LOSE"] = "Kapal anda sedang diserang oleh [player]. Cobalah seperti yang mungkin Anda, Anda tidak dapat membela diri terhadap [player] &#39;s persenjataan superior. Kapal anda hancur.";
$l_log_title["LOG5_ATTACK_LOSE"] 		= "<font color=red>Combat lost!</font>";
$l_log_text["LOG5_ATTACKED_WIN"] = "Kapal Anda diserang oleh [player]. Anda pertempuran untuk sementara, maka pertarungan rusak. Kau kehilangan [armor] zirah poin dan [fighters] pejuang dalam pertempuran.";
$l_log_title["LOG5_ATTACKED_WIN"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_HIT_MINES"] = "Anda menekan [mines] tambang ketika bepergian di sektor [sector].";
$l_log_title["LOG5_HIT_MINES"] 		= "<font color=yellow>Mines alert!</font>";
$l_log_text["LOG5_SHIP_DESTROYED_MINES"] = "Kapal anda hancur oleh sebuah ranjau di sektor [sector].";
$l_log_title["LOG5_SHIP_DESTROYED_MINES"] 	= "<font color=red>Mines alert!</font>";
$l_log_text["LOG5_PLANET_DEFEATED_D"] = "Planet Anda [planet_name] di sektor [sector] dikalahkan dalam pertempuran oleh [name]. Untungnya, kesetiaan yang kuat dari warga negara Anda bermain dalam mendukung Anda. Mereka telah berani memilih untuk menghancurkan planet daripada harus jatuh ke tangan musuh. Anda mengatur pemakaman yang luar biasa dalam memori orang-orang yang setia Anda.";
$l_log_title["LOG5_PLANET_DEFEATED_D"] 	= "<font color=yellow>Planet destroyed</font>";
$l_log_text["LOG5_PLANET_DEFEATED"] = "Planet Anda [planet_name] di sektor [sector] dikalahkan dalam pertempuran oleh malang [name]. Orang-orang dari planet menyambut penguasa baru mereka. Anda mendengar kesaksian pada FNN: &quot;Kami senang bisa lepas dari yang tua bangka! Kami tidak ingin ada bau pecundang yang tidak bisa melindungi kita!&quot;. Anda bersumpah untuk membuat mereka membayar kesombongan mereka.";
$l_log_title["LOG5_PLANET_DEFEATED"] 	= "<font color=red>Planet defeated!</font>";
$l_log_text["LOG5_PLANET_NOT_DEFEATED"] = "Planet Anda [planet_name] di sektor [sector] diserang oleh [name]. Warga menyelenggarakan valliant Namun pertahanan, dan berhasil menghancurkan lawan. Mereka menyelamatkan beberapa sumber dari ruang puing: [goods] barang, [ore] bijih, [organics] organik dan [salvage]% dari nilai kapal [credits] kredit.";
$l_log_title["LOG5_PLANET_NOT_DEFEATED"] = "Kemenangan!";
$l_log_text["LOG5_DEFS_DESTROYED"] = "[quantity] [type] hancur di sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED"] = "Sektor pertahanan hancur";
$l_log_text["LOG5_KABAL_ATTACK"] = "Menyerang [player] ...";
$l_log_title["LOG5_KABAL_ATTACK"] = "Serangan";
$l_log_text["LOG5_DEFS_DESTROYED_F"] = "Anda telah menghancurkan [fighters] berpatroli pejuang di sektor [sector].";
$l_log_title["LOG5_DEFS_DESTROYED_F"] = "Fighters hancur";
$l_log_text["LOG5_DEFS_KABOOM"] = "Anda dihancurkan oleh sebuah kekuatan pejuang di sektor [sector].";
$l_log_title["LOG5_DEFS_KABOOM"] 		= "<font color=red>Ship destroyed!</font>";
$l_log_text["LOG5_PLANET_CAPTURED"] = "Anda menangkap sebuah planet milik [owner]. Itu [cols] kolonis dan [credits] kredit di atasnya.";
$l_log_title["LOG5_PLANET_CAPTURED"] = "Planet tertangkap!";
$l_log_text["LOG5_STORAGE_EWD"] = "Planet Anda terkejut oleh [player] &#39;s serangan. Salah satu kapal yang tersimpan Anda membuat Warp darurat untuk [sector] dan mendarat di planet [planet]";
$l_log_title["LOG5_STORAGE_EWD"] = "Kapal disimpan warp Darurat!";
$l_log_text["LOG5_STORAGE_EWDFAIL"] = "Sebuah kapal disimpan Darurat Warp Device GAGAL! Kapal yang disimpan ditangkap oleh [player] setelah mereka mengalahkan planet Anda!";
$l_log_title["LOG5_STORAGE_EWDFAIL"] 	= "Stored Ship Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_STORAGE_CAPTURED"] = "Sebuah kapal disimpan ditangkap oleh [player] setelah mereka mengalahkan salah satu planet!";
$l_log_title["LOG5_STORAGE_CAPTURED"] 	= "Stored Ship <font color=red>CAPTURED!</font>";
$l_log_text["LOG5_CONFISCATION"] = "Kapal Anda disita oleh [player]. Lakukan untuk serangan berlebihan pada karunia-pemain yang [player] telah menyita salah satu kapal ([ship]).";
$l_log_title["LOG5_CONFISCATION"] 		= "<font color=yellow>Skirmish!</font>";
$l_log_text["LOG5_PLANET_CONFISCATION"] = "Planet Anda disita oleh [player]. Lakukan untuk serangan berlebihan pada karunia-pemain yang [player] telah menyita salah satu planet ([name]) di sektor [sector] pantas [score] kredit.";
$l_log_title["LOG5_PLANET_CONFISCATION"] 		= "<font color=yellow>Planetary Skirmish!</font>";
$l_log_text["LOG5_STORAGE_SUICIDE"] = "Sebuah kapal disimpan bunuh diri ketika [player] mengalahkan salah satu planet Anda dan mencoba untuk menangkap it!";
$l_log_title["LOG5_STORAGE_SUICIDE"] 	= "Stored Ship <font color=red>SUICIDE!</font>";

$l_log_text["LOG5_SM_ATTACK"] = "Sensor mendeteksi kapal Sektor masuk rudal yang ditembakkan dari [sector] by [player]!";
$l_log_title["LOG5_SM_ATTACK"] 	= "<font color=red>INCOMING SECTOR MISSILE DETECTED</font>";
$l_log_text["LOG5_SM_OUTMAN"] = "Sebuah rudal Sektor dipecat oleh [player] adalah melihat warping ke dalam sektor dan Anda menghindar dari serangan.";
$l_log_title["LOG5_SM_OUTMAN"] = "Sektor Missile tindakan menghindar!";
$l_log_text["LOG5_SM_OUTSCAN"] = "Anda terdeteksi [player] &#39;s Missile Sektor masuk mencoba memperbaiki kapal Anda, tetapi Anda generator jubah berhasil mengelabui sensor Missiles Sektor sirkuit.";
$l_log_title["LOG5_SM_OUTSCAN"] = "Sektor Missile Jubah sukses!";
$l_log_text["LOG5_SM_EWD"] = "Anda terkejut dengan [player] &#39;s Sektor serangan rudal dan terlibat Warp Device Darurat melompat ke sektor yang tidak dikenal.";
$l_log_title["LOG5_SM_EWD"] = "Missile Sektor Darurat warp!";
$l_log_text["LOG5_SM_EWDFAIL"] = "Sensor Anda mendeteksi [player] &#39;s Sektor serangan rudal dan melibatkan Darurat Warp Device. Anda aneh tersedak mendengar suara yang datang dari kamar mesin dan bau terbakar sirkuit. &quot;Bodoh sepotong crap!&quot;, Anda berteriak, menendang di komputer. Anda penjepit untuk dampak!";
$l_log_title["LOG5_SM_EWDFAIL"] 	= "Sector Missile Emergency warp <font color=red>failed!</font>";
$l_log_text["LOG5_SM_WIN"] = "Kapal Anda diserang oleh [player] dengan menggunakan Sektor Missile. Kau kehilangan [armor] zirah poin dan [energy] unit energi dalam serangan itu.";
$l_log_title["LOG5_SM_WIN"] 		= "<font color=yellow>Sector Missile IMPACT!</font>";
$l_log_text["LOG5_SM_LOSE"] = "Kapal anda dihancurkan oleh Sektor rudal dari [player].";
$l_log_title["LOG5_SM_LOSE"] 		= "<font color=red>Sector Missile Combat Lost!</font>";

$l_log_text["LOG5_SURVIVE_PROBE_ATTACK"] = "Kapal Anda diserang oleh sebuah penyelidikan yang dimiliki oleh [player] dalam sektor [sector]. Kau kehilangan [armor] zirah poin dan [energy] unit energi dalam serangan itu.";
$l_log_title["LOG5_SURVIVE_PROBE_ATTACK"] 		= "<font color=yellow>Probe ATTACK!</font>";
$l_log_text["LOG5_PROBE_ATTACK_FAILED"] = "[player] selamat dari serangan oleh probe di sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_FAILED"] 		= "<font color=red>Probe Attack FAILED!</font>";
$l_log_text["LOG5_PROBE_ATTACK_SUCCEEDED"] = "Probe Anda menghancurkan kapal yang dimiliki oleh [player] dalam sektor [sector].";
$l_log_title["LOG5_PROBE_ATTACK_SUCCEEDED"] 		= "<font color=red>Probe Attack Succeeded!</font>";
$l_log_text["LOG5_DESTROYED_PROBE_ATTACK"] = "Kapal Anda dihancurkan oleh sebuah penyelidikan dari [player] dalam sektor [sector].";
$l_log_title["LOG5_DESTROYED_PROBE_ATTACK"] 		= "<font color=red>Probe Attack Lost!</font>";
$l_log_title["LOG5_AFTER_ACTION"] = "Setelah Aksi Combat Laporan";

// Scan Logs

$l_log_text["LOG6_PLANET_SCAN"] = "[name] telah dipindai planet Anda [planet_name] di sektor [sector].";
$l_log_title["LOG6_PLANET_SCAN"] = "Planet scan";
$l_log_text["LOG6_PLANET_SCAN_FAIL"] = "[name] telah mencoba untuk memindai planet [planet_name] di sektor [sector], tapi gagal.";
$l_log_title["LOG6_PLANET_SCAN_FAIL"] = "Scan planet gagal";
$l_log_text["LOG6_SHIP_SCAN"] = "[player] telah dipindai kapal Anda.";
$l_log_title["LOG6_SHIP_SCAN"] = "Kapal scan";
$l_log_text["LOG6_SHIP_SCAN_FAIL"] = "[player] telah mencoba untuk memindai kapal, tapi gagal.";
$l_log_title["LOG6_SHIP_SCAN_FAIL"] = "Kapal scan gagal";

// Starvation Logs

$l_log_text["LOG7_STARVATION"] = "Planet [name] pada [sector] tidak bisa mempertahankan penduduknya! Lebih organik diperlukan. [starvation] kolonis meninggal karena kelaparan. Koloni mulai kelaparan pada [date].";
$l_log_title["LOG7_STARVATION"] 		= "<font color=yellow>Starvation!</font>";

// Probe Logs

$l_log_text["LOG9_PROBE_DETECTED_SHIP"]="<font color=yellow>Your probe id [id] detected [ship_name] entering sector [sector]</font>";
$l_log_title["LOG9_PROBE_DETECTED_SHIP"] = "Probe Terdeteksi Incoming Ship";
$l_log_text["LOG9_PROBE_SCAN_SHIP"]="<font color=yellow>Your probe id [id] scanned [ship_name] entering sector [sector]<br>Hull: [hull] Engines: [engines] Power: [power] Fighter Bay: [fighter] Sensors: [sensors] Beams: [beams] Torp Launchers: [torps] Armor: [armor] Shields: [shields] Cloak: [cloak]<br>Armor Points: [armor_pts] Fighters: [fighters] Torpedoes: [avail_torps] Ship Energy: [energy] Credits: [credits] <br>Mine Deflectors: [deflectors] Emergency Warp: [ewd] Escape Pod: [pod] ECM: [ecm]</font>";
$l_log_title["LOG9_PROBE_SCAN_SHIP"] = "Incoming Scanned probe Kapal";
$l_log_text["LOG9_PROBE_DESTROYED"]="<font color='#00ff00'>SECTOR defenses in [sector] destroy your probe.</font>";
$l_log_title["LOG9_PROBE_DESTROYED"] = "Probe Rusak";
$l_log_text["LOG9_PROBE_NOTURNS"]="<font color='#00ff00'>You do not have enough turns for probe [probe_id] to move to [sector]</font>";
$l_log_title["LOG9_PROBE_NOTURNS"] = "Probe Laporan";
$l_log_text["LOG9_PROBE_INVALIDSECTOR"] = "<font color='#00ff00'>Moving to sector [target_sector] is not allowed</font>";
$l_log_title["LOG9_PROBE_INVALIDSECTOR"] = "Probe Laporan";
$l_log_text["LOG9_PROBE_DETECTPROBE"]="<font color='#00ff00'>Probe [probe_id] in sector [sector] detected [probe_detect]</font>";
$l_log_title["LOG9_PROBE_DETECTPROBE"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_DETECTED_GATEWAY"]="<font color='#00ff00'>Seeker Probe [probe_id] in sector [sector] detected a Gateway Sector</font>";
$l_log_title["LOG9_PROBE_DETECTED_GATEWAY"] 		= "[probe_type] <font color='yellow'>Seeker Probe Report</font>";

$l_log_text["LOG9_PROBE_SCAN_FAIL"] = "[name] berusaha untuk memindai salah satu probe di sektor [sector], tapi gagal.";
$l_log_title["LOG9_PROBE_SCAN_FAIL"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_SCAN"] = "Salah satu probe di sektor [sector] telah discan oleh [name].";
$l_log_title["LOG9_PROBE_SCAN"] 		= "[probe_type] <font color='yellow'>Probe Report</font>";
$l_log_text["LOG9_PROBE_ATTACKED"] = "Salah satu probe di sektor [sector] diserang dan dihancurkan oleh [name].";
$l_log_title["LOG9_PROBE_ATTACKED"] 		= "[probe_type] <font color='yellow'>Probe Destroyed</font>";

$l_log_text["LOG9_PROBEHUNTER_SUCCEED"] = "Salah satu Hunters Probe Anda telah menghancurkan sebuah [probe_type] dimiliki oleh [name] pada [sector].";
$l_log_title["LOG9_PROBEHUNTER_SUCCEED"] = "Probe Hunter hancur [probe_type]";
$l_log_text["LOG9_PROBEHUNTER_DESTROYED"] = "Anda [probe_type] di sektor [sector] diserang dan dihancurkan oleh Hunter Probe dimiliki oleh [name].";
$l_log_title["LOG9_PROBEHUNTER_DESTROYED"] 		= "[probe_type] <font color='yellow'>Probe Attacked and Destroyed</font>";
$l_log_text["LOG9_PROBEHUNTER_EXPLODED"] = "Probe Anda Hunter di sektor [sector] sudah hilang ketika ledakan yang dihasilkan dari serangan pada [probe_type] dimiliki oleh [name] menyelimuti itu.";
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
