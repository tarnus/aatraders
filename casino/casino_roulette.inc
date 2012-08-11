<?php
// Roulette Main
// roulette.gif
// In Roulette, the layout consists of 38 numbers ( 0, 00, and 1 through 36 ); the numbers are alternately colored red and black with the 0 and 00 colored green. To play, the player places a bet on a number, color or group of numbers on the layout (or roulette table). The wheel and ball are spun, and the slot the ball falls into determines the winner. The amount of the pay-off depends on the position and the amount of chips that were placed on the winning number.
// casino_roulette
// N

// name - Display Name for the module
// image - image name for the module
// description - description of the module
// casino_link - link for the module This is the module file name minus the .inc. IE: modulename.inc would be listed as modulename
// online_status - "Y" display this file in the list of availible casino modules when the player enters the casino, "N" - do not display module

get_post_ifset("casinogame");

function e_rand($min=false,$max=false){
	if ($min===false) return mt_rand();
	$min*=1000;
	if ($max===false) return round(mt_rand($min)/1000,0);
	$max*=1000;
	if ($min==$max) return round($min/1000,0);
	if ($min==0 && $max==0) return 0; //do NOT as me why this line can be executed, it makes no sense, but it *does* get executed.
	if ($min<$max){
		return round(@mt_rand($min,$max)/1000,0);
	}else if($min>$max){
		return round(@mt_rand($max,$min)/1000,0);
	}
}

if ($HTTP_GET_VARS['op'] == "") {
	echo "<IMG SRC=\"./templates/default/images/casino/roulette/layout-clean.gif\"><br><br>\n";
	echo "You stroll over to the Roulette Table.<br><br>";
	echo "The dealer gives you a sideways glance. He mumbles so low you have a hard time hearing.<br><br>";
	echo "The house limit is 500 credits per bet...<br><br>Place a minimum bet of 100 credits if you would like to play, otherwise ";
	echo "get the hell away from my table you cheap idiot.<br><br>";
	$HTTP_GET_VARS['op'] = "placebet";
}

if ($HTTP_GET_VARS['op'] == "placebet") {
	echo "How much would you like to bet?<br>";
	echo "<form action='roulette.php?op=mybet' method='POST'>
		  <input name='mybet' id='mybet'>
		  <input type='submit' class='button' value='place your bet'>
		  </form>";
	echo "<script language='JavaScript'>
		  document.getElementById('mybet').focus();
		  </script>";
}

if ($HTTP_GET_VARS['op'] == "mybet") {
	$mybet=$HTTP_POST_VARS['mybet'];
	if ($mybet > $playerinfo['credits']) {
		echo "You do not have $mybet credits.<br>";
		echo "<a href=roulette.php?op=placebet>Continue<br></a>";
	} elseif ($mybet < 100) {
		echo "You must place a minimum bet of 100 credits to play!<br>";
		echo "<a href=roulette.php?op=placebet>Continue<br></a>";
	} elseif ($mybet > 500) {
		echo "House limit is 500 gold, your bet is accepted as 500 credits.<br>";
		$HTTP_POST_VARS['mybet']=500;
		$HTTP_GET_VARS['op']="picknums";
	} else {
		$HTTP_GET_VARS['op']="picknums";
	}
}

if ($HTTP_GET_VARS['op']=="picknums") {
	$bet=abs((int)$HTTP_GET_VARS['mybet']+(int)$HTTP_POST_VARS['mybet']);
	if ($HTTP_GET_VARS['try']=="") {
		echo "<IMG SRC=\"./templates/default/images/casino/roulette/layout-2.gif\"><br><br>\n";
		echo "You have bet $bet credits. Choose your -type- of bet...:<br><br>";
		echo "Inside bets: (also called layout bets)<br><br>
			A - 1 number, Straight up 38:1<br>
			B - 2 numbers, Split 17:1<br>
			C - 3 numbers, 3 Line 11:1<br>
			D - 4 numbers, Corner 8:1<br>
			E - 5 numbers, Both 0 and 00 and 1st Three 6:1<br>
			F - 6 numbers, 6 Line 5:1<br><br>
			Outside bets:<br><br>
			G - 12 numbers, Column 2:1<br>
			H - 12 numbers, Dozen 2:1<br>
			J - 24 numbers, Split Columns 1:2<br>
			K - 24 numbers, Split Dozens 1:2<br>
			X - Even/Odd - Pays even money 1:1<br>
			Y - Red/Black - Pays even money 1:1<br>
			Z - 1-18/19-36 (also called Low/High) - Pays even money 1:1<br><br>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=A>A - 1 number<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=B>B - 2 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=C>C - 3 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=D>D - 4 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=E>E - 5 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=F>F - 6 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=G>G - 12 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=H>H - 12 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=J>J - 24 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=K>K - 24 numbers<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=X>X - even/odd<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=Y>Y - red/black<br></a>";
		echo "<a href=roulette.php?op=picknums&mybet=$bet&try=Z>Z - 1 to 18/19 to 36<br></a>";
	} else {
		$try=$HTTP_GET_VARS['try'];
		$tbet=AAT_strtolower($try);
		$layoutpic="layout-";
				switch($tbet) {
						case "b": case "c": case "d":
			case "e": case "f": case "g":
			case "h": case "j": case "k":
							$layoutpic .= $tbet;
						break;
						default:
				$layoutpic .= "clean";
				break;
		}
		$layoutpic .= ".gif";
		if ($HTTP_POST_VARS['typea']=="B") { 
			$layoutpic="layout-clean.gif"; 
		}
		echo "<IMG SRC=\"./templates/default/images/casino/roulette/$layoutpic\"><br><br>\n";
		if ($HTTP_GET_VARS['illegalbet']=="Y") {
			echo "PAY ATTENTION AND CHOOSE A NUMBER THATS ON THE TABLE STUPID!<br><br>";
			$HTTP_GET_VARS['illegalbet']="";
		}
		echo "You have selected to place a type-$try bet.<br><br>";
		switch($try) {
			case "A":
				// A - 1 number, Straight up 38:1
				echo "What number do you wish to place your entire bet of $bet credits on? (Valid: 1-36, 37=0, 38=00)<br>";
				echo "<form action='roulette.php?op=spin' method='POST'>
					  <input name='mynum' id='mynum'>
					  <input type='hidden' name='typea' value='A'>
					  <input type='hidden' name='mybet' value=$bet>
					  <input type='submit' class='button' value='spin the wheel'>
					</form>";
				echo "<script language='JavaScript'>
						document.getElementById('mynum').focus();
					</script>";
				break;
			case "B":
				// B - 2 numbers, Split 17:1	 *** 57 choices to pick from ***
				if ($HTTP_POST_VARS['typea']!="B") {
					echo "Select your -FIRST- number, then we'll take you to the next screen. (Valid: 1-36)<br>";
					echo "<form action='roulette.php?op=picknums&try=B' method='POST'>
					  	<input name='mynum' id='mynum'>
					  	<input type='hidden' name='typea' value='B'>
					  	<input type='hidden' name='mybet' value=$bet>
					  	<input type='submit' class='button' value='continue'>
						</form>";
					echo "<script language='JavaScript'>
							document.getElementById('mynum').focus();
						</script>";
				} else {
					$mynum=$HTTP_POST_VARS['mynum'];
					if ($mynum<1 || $mynum>36) { 
						echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=roulette.php?op=picknums&mybet=$bet&try=B&illegalbet=Y\">";
					}
					$valid=array(	 "1"=>"2,4",		 "2"=>"1,3,5",	   "3"=>"2,6",		 "4"=>"1,5,7",
 							 "5"=>"2,4,6,8",	 "6"=>"3,5,9",	   "7"=>"4,8,10",	  "8"=>"5,7,9,11",
 							 "9"=>"6,8,12",	 "10"=>"7,11,13",	"11"=>"8,10,12,14", "12"=>"9,11,15",
							"13"=>"10,14,16",   "14"=>"11,13,15,17","15"=>"12,14,18",   "16"=>"13,17,19",
							"17"=>"14,16,18,20","18"=>"15,17,21",   "19"=>"16,20,22",   "20"=>"17,19,21,23",
							"21"=>"18,20,24",   "22"=>"19,23,25",   "23"=>"20,22,24,26","24"=>"21,23,27",
							"25"=>"22,26,28",   "26"=>"23,25,27,29","27"=>"24,26,30",   "28"=>"25,29,31",
							"29"=>"26,28,30,32","30"=>"27,29,33",   "31"=>"28,32,34",   "32"=>"29,31,33,35",
							"33"=>"30,32,36",   "34"=>"31,35",	  "35"=>"32,34,36",   "36"=>"33,35"
					);
					echo "You selected ". $mynum. " for your -FIRST- number, now...<br><br>";
					echo "Select your appropriate -SECOND- number, then get ready to spin the wheel! ";
					echo "(Valid 2nd Number Choices: ". $valid[$mynum].")<br>";
					$secnum=AAT_split("\,",$valid[$mynum]);
					for ($x=1;$x<count($secnum)+1;$x++) {
					  $choice=chr(64+$x);
						echo "<a href=roulette.php?op=spin&mybet=$bet&mynum=B".$mynum."-".$secnum[$x-1] . ">" . $choice." = ".$secnum[$x-1] . "<br></a>";
					}
				}
				break;
			case "C":
				// C - 3 numbers, 3 Line 11:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = 1,2,3","roulette.php?op=spin&mybet=$bet&mynum=C1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = 4,5,6","roulette.php?op=spin&mybet=$bet&mynum=C2");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("C = 7,8,9","roulette.php?op=spin&mybet=$bet&mynum=C3");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("D = 10,11,12","roulette.php?op=spin&mybet=$bet&mynum=C4");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("E = 13,14,15","roulette.php?op=spin&mybet=$bet&mynum=C5");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("F = 16,17,18","roulette.php?op=spin&mybet=$bet&mynum=C6");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("G = 19,20,21","roulette.php?op=spin&mybet=$bet&mynum=C7");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("H = 22,23,24","roulette.php?op=spin&mybet=$bet&mynum=C8");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("I = 25,26,27","roulette.php?op=spin&mybet=$bet&mynum=C9");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("J = 28,29,30","roulette.php?op=spin&mybet=$bet&mynum=C10");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("K = 31,32,33","roulette.php?op=spin&mybet=$bet&mynum=C11");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("L = 34,35,36","roulette.php?op=spin&mybet=$bet&mynum=C12");
				break;
			case "D":
				// D - 4 numbers, Corner 8:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = 1,2,4,5","roulette.php?op=spin&mybet=$bet&mynum=D1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = 2,3,5,6","roulette.php?op=spin&mybet=$bet&mynum=D2");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("C = 4,5,7,8","roulette.php?op=spin&mybet=$bet&mynum=D3");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("D = 5,6,8,9","roulette.php?op=spin&mybet=$bet&mynum=D4");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("E = 7,8,10,11","roulette.php?op=spin&mybet=$bet&mynum=D5");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("F = 8,9,11,12","roulette.php?op=spin&mybet=$bet&mynum=D6");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("G = 10,11,13,14","roulette.php?op=spin&mybet=$bet&mynum=D7");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("H = 11,12,14,15","roulette.php?op=spin&mybet=$bet&mynum=D8");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("I = 13,14,16,17","roulette.php?op=spin&mybet=$bet&mynum=D9");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("J = 14,15,17,18","roulette.php?op=spin&mybet=$bet&mynum=D10");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("K = 16,17,19,20","roulette.php?op=spin&mybet=$bet&mynum=D11");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("L = 17,18,20,21","roulette.php?op=spin&mybet=$bet&mynum=D12");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("M = 19,20,22,23","roulette.php?op=spin&mybet=$bet&mynum=D13");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("N = 20,21,23,24","roulette.php?op=spin&mybet=$bet&mynum=D14");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("O = 22,23,25,26","roulette.php?op=spin&mybet=$bet&mynum=D15");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("P = 23,24,26,27","roulette.php?op=spin&mybet=$bet&mynum=D16");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("Q = 25,26,28,29","roulette.php?op=spin&mybet=$bet&mynum=D17");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("R = 26,27,29,30","roulette.php?op=spin&mybet=$bet&mynum=D18");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("S = 28,29,31,32","roulette.php?op=spin&mybet=$bet&mynum=D19");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("T = 29,30,32,33","roulette.php?op=spin&mybet=$bet&mynum=D20");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("U = 31,32,34,35","roulette.php?op=spin&mybet=$bet&mynum=D21");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("V = 32,33,35,36","roulette.php?op=spin&mybet=$bet&mynum=D22");
				break;
			case "E":
				// E - 5 numbers, 1st Five 6:1
				echo "-- only 1 choice is available with this bet --<br><br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("click here to spin the wheel","roulette.php?op=spin&mybet=$bet&mynum=E1");
				break;
			case "F":
				// F - 6 numbers, 6 Line 5:1
				echo "Select which spot you wish to place your entire bet on...<br>";
				echo "-- 11 choices to pick from --<br><br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = 1,2,3,4,5,6","roulette.php?op=spin&mybet=$bet&mynum=F1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = 4,5,6,7,8,9","roulette.php?op=spin&mybet=$bet&mynum=F2");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("C = 7,8,9,10,11,12","roulette.php?op=spin&mybet=$bet&mynum=F3");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("D = 10,11,12,13,14,15","roulette.php?op=spin&mybet=$bet&mynum=F4");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("E = 13,14,15,16,17,18","roulette.php?op=spin&mybet=$bet&mynum=F5");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("F = 16,17,18,19,20,21","roulette.php?op=spin&mybet=$bet&mynum=F6");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("G = 19,20,21,22,23,24","roulette.php?op=spin&mybet=$bet&mynum=F7");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("H = 22,23,24,25,26,27","roulette.php?op=spin&mybet=$bet&mynum=F8");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("I = 25,26,27,28,29,30","roulette.php?op=spin&mybet=$bet&mynum=F9");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("J = 28,29,30,31,32,33","roulette.php?op=spin&mybet=$bet&mynum=F10");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("K = 31,32,33,34,35,36","roulette.php?op=spin&mybet=$bet&mynum=F11");
				break;
			case "G":
				// G - 12 numbers, Column 2:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = TOP ROW","roulette.php?op=spin&mybet=$bet&mynum=G1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = MIDDLE ROW","roulette.php?op=spin&mybet=$bet&mynum=G2");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("C = BOTTOM ROW","roulette.php?op=spin&mybet=$bet&mynum=G3");
				break;
			case "H":
				// H - 12 numbers, Dozen 2:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = 1ST 12","roulette.php?op=spin&mybet=$bet&mynum=H1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = 2ND 12","roulette.php?op=spin&mybet=$bet&mynum=H2");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("C = 3RD 12","roulette.php?op=spin&mybet=$bet&mynum=H3");
				break;
			case "J":
				// J - 24 numbers, Split Columns 1:2
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = TOP 2 ROWS","roulette.php?op=spin&mybet=$bet&mynum=J1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = BOTTOM 2 ROWS","roulette.php?op=spin&mybet=$bet&mynum=J2");
				break;
			case "K":
				// K - 24 numbers, Split Dozens 1:2
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = 1ST and 2ND 12","roulette.php?op=spin&mybet=$bet&mynum=K1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = 2ND and 3RD 12","roulette.php?op=spin&mybet=$bet&mynum=K2");
				break;
			case "X":
				// X - Even/Odd - Pays even money 1:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = EVEN","roulette.php?op=spin&mybet=$bet&mynum=X1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = ODD","roulette.php?op=spin&mybet=$bet&mynum=X2");
				break;
			case "Y":
				// Y - Red/Black - Pays even money 1:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = RED","roulette.php?op=spin&mybet=$bet&mynum=Y1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = BLACK","roulette.php?op=spin&mybet=$bet&mynum=Y2");
				break;
			case "Z":
				// Z - 1-18/19-36 (also called Low/High) - Pays even money 1:1
				echo "Select which spot you wish to place your entire bet on...<br>";
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("A = 1 TO 18","roulette.php?op=spin&mybet=$bet&mynum=Z1");
		echo "<a href=" . HTMLEntities($link.$extra) . "$keyrep class='nav'>$text<br></a>";
				addnav("B = 19 TO 36","roulette.php?op=spin&mybet=$bet&mynum=Z2");
				break;
			default:
				break;
		}
	}
}

if ($HTTP_GET_VARS['op']=="spin") {
	$mybet=abs((int)$HTTP_GET_VARS['mybet']+(int)$HTTP_POST_VARS['mybet']);
		$mynum=$HTTP_POST_VARS['mynum']; 
		if (!$mynum) { 
			$mynum=$HTTP_GET_VARS['mynum']; 
		}
	$mlen=AAT_strlen($mynum);
	if ($HTTP_POST_VARS['typea']!="A") { 
		$bet=AAT_substr($mynum,0,1); 
		$type=AAT_substr($mynum,1,$mlen-1);
		switch($bet) {
			case "B":
				// B - 2 numbers, Split 17:1
				$twonums=AAT_split("-",$type);
				$betarray=array(1=>$twonums[0],$twonums[1]);
				$payout=17;
				break;
			case "C":
				// C - 3 numbers, 3 Line 11:1
				switch($type) {
					case "1":
						$betarray=array(1=>1,2,3);
						break;
					case "2":
						$betarray=array(1=>4,5,6);
						break;
					case "3":
						$betarray=array(1=>7,8,9);
						break;
					case "4":
						$betarray=array(1=>10,11,12);
						break;
					case "5":
						$betarray=array(1=>13,14,15);
						break;
					case "6":
						$betarray=array(1=>16,17,18);
						break;
					case "7":
						$betarray=array(1=>19,20,21);
						break;
					case "8":
						$betarray=array(1=>22,23,24);
						break;
					case "9":
						$betarray=array(1=>25,26,27);
						break;
					case "10":
						$betarray=array(1=>28,29,30);
						break;
					case "11":
						$betarray=array(1=>31,32,33);
						break;
					case "12":
						$betarray=array(1=>34,35,36);
						break;
				}
				$payout=11;
				break;
			case "D":
				// D - 4 numbers, Corner 8:1
				switch($type) {
					case "1":
						$betarray=array(1=>1,2,4,5);
						break;
					case "2":
						$betarray=array(1=>2,3,5,6);
						break;
					case "3":
						$betarray=array(1=>4,5,7,8);
						break;
					case "4":
						$betarray=array(1=>5,6,8,9);
						break;
					case "5":
						$betarray=array(1=>7,8,10,11);
						break;
					case "6":
						$betarray=array(1=>8,9,11,12);
						break;
					case "7":
						$betarray=array(1=>10,11,13,14);
						break;
					case "8":
						$betarray=array(1=>11,12,14,15);
						break;
					case "9":
						$betarray=array(1=>13,14,16,17);
						break;
					case "10":
						$betarray=array(1=>14,15,17,18);
						break;
					case "11":
						$betarray=array(1=>16,17,19,20);
						break;
					case "12":
						$betarray=array(1=>17,18,20,21);
						break;
					case "13":
						$betarray=array(1=>19,20,22,23);
						break;
					case "14":
						$betarray=array(1=>20,21,23,24);
						break;
					case "15":
						$betarray=array(1=>22,23,25,26);
						break;
					case "16":
						$betarray=array(1=>23,24,26,27);
						break;
					case "17":
						$betarray=array(1=>25,26,28,29);
						break;
					case "18":
						$betarray=array(1=>26,27,29,30);
						break;
					case "19":
						$betarray=array(1=>28,29,31,32);
						break;
					case "20":
						$betarray=array(1=>29,30,32,33);
						break;
					case "21":
						$betarray=array(1=>31,32,34,35);
						break;
					case "22":
						$betarray=array(1=>32,33,35,36);
						break;
				}
				$payout=8;
				break;
			case "E":
				// E - 5 numbers, 1st Five 6:1
				$betarray=array(1=>1,2,3,37,38);
				$payout=6;
				break;
			case "F":
				// F - 6 numbers, 6 Line 5:1
				switch($type) {
					case "1":
						$betarray=array(1=>1,2,3,4,5,6);
						break;
					case "2":
						$betarray=array(1=>4,5,6,7,8,9);
						break;
					case "3":
						$betarray=array(1=>7,8,9,10,11,12);
						break;
					case "4":
						$betarray=array(1=>10,11,12,13,14,15);
						break;
					case "5":
						$betarray=array(1=>13,14,15,16,17,18);
						break;
					case "6":
						$betarray=array(1=>16,17,18,19,20,21);
						break;
					case "7":
						$betarray=array(1=>19,20,21,22,23,24);
						break;
					case "8":
						$betarray=array(1=>22,23,24,25,26,27);
						break;
					case "9":
						$betarray=array(1=>25,26,27,28,29,30);
						break;
					case "10":
						$betarray=array(1=>28,29,30,31,32,33);
						break;
					case "11":
						$betarray=array(1=>31,32,33,34,35,36);
						break;
				}
				$payout=5;
				break;
			case "G":
				// G - 12 numbers, Column 2:1
				switch($type) {
					case "1":
						$betarray=array(1=>3,6,9,12,15,18,21,24,27,30,33,36);
						break;
					case "2":
						$betarray=array(1=>2,5,8,11,14,17,20,23,26,29,32,35);
						break;
					case "3":
						$betarray=array(1=>1,4,7,10,13,16,19,22,25,28,31,34);
						break;
				}
				$payout=2;
				break;
			case "H":
				// H - 12 numbers, Dozen 2:1
				switch($type) {
					case "1":
						$betarray=array(1=>1,2,3,4,5,6,7,8,9,10,11,12);
						break;
					case "2":
						$betarray=array(1=>13,14,15,16,17,18,19,20,21,22,23,24);
						break;
					case "3":
						$betarray=array(1=>25,26,27,28,29,30,31,32,33,34,35,36);
						break;
				}
				$payout=2;
				break;
			case "J":
				// J - 24 numbers, Split Columns 1:2
				switch($type) {
					case "1":
						$betarray=array(1=>2,3,5,6,8,9,11,12,14,15,17,18,20,21,23,24,26,27,29,30,32,33,35,36);
						break;
					case "2":
						$betarray=array(1=>1,2,4,5,7,8,10,11,13,14,16,17,19,20,22,23,25,26,28,29,31,32,34,35);
						break;
				}
				$payout=0.5;
				break;
			case "K":
				// K - 24 numbers, Split Dozens 1:2
				switch($type) {
					case "1":
						$betarray=array(1=>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24);
						break;
					case "2":
						$betarray=array(1=>13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36);
						break;
				}
				$payout=0.5;
				break;
			case "X":
				// X - Even/Odd - Pays even money 1:1
				switch($type) {
					case "1":
						$betarray=array(1=>2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36);
						break;
					case "2":
						$betarray=array(1=>1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35);
						break;
				}
				$payout=1;
				break;
			case "Y":
				// Y - Red/Black - Pays even money 1:1
				switch($type) {
					case "1":
						$betarray=array(1=>1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36);
						break;
					case "2":
						$betarray=array(1=>2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35);
						break;
				}
				$payout=1;
				break;
			case "Z":
				// Z - 1-18/19-36 (also called Low/High) - Pays even money 1:1
				switch($type) {
					case "1":
						$betarray=array(1=>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18);
						break;
					case "2":
						$betarray=array(1=>19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36);
						break;
				}
				$payout=1;
				break;
			default:
				break;
		}
	} else {
		if ($mynum<1 || $mynum>38) { 
			echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=roulette.php?op=picknums&mybet=$mybet&try=A&illegalbet=Y\">";
		}
		$payout="38";
	}

	// *** debug'n output - not needed for gameplay ***

	// output("<br>`bDEBUG: op = ".$HTTP_GET_VARS[op]."`b<br>");
	// output("`bDEBUG: mynum = ".$mynum."`b<br>");
	// output("`bDEBUG: mybet = ".$mybet."`b<br>");
	// output("`bDEBUG: typea = ".$HTTP_POST_VARS[typea]."`b<br>");
	// output("`bDEBUG: drop = ".$HTTP_POST_VARS[drop]."`b<br>");
	// output("`bDEBUG: bet = ".$bet."`b<br>");
	// output("`bDEBUG: type = ".$type."`b<br>");
	// output("`bDEBUG: payout = ".$payout."`b<br><br>");

	if ($HTTP_POST_VARS['drop']!="yes") {
		echo "AND THERE THE BALL SPINS! YES! OMG! SO MUCH FUN! LOOK AT IT GO...<br><br>";
		echo "<IMG SRC=\"./templates/default/images/casino/roulette/wheel.gif\"><br><br>\n";
		echo "<form action='roulette.php?op=spin' method='POST'>
		  	<input type='hidden' name='mynum' value=$mynum>
		  	<input type='hidden' name='mybet' value=$mybet>
		  	<input type='hidden' name='typea' value=$HTTP_POST_VARS[typea]>
		  	<input type='hidden' name='drop' value='yes'>
		  	<input type='submit' class='button' value='STOP THE WHEEL!'>
			</form>";
	} else if ($HTTP_POST_VARS['drop']=="yes") {
		$youwon=0; 
		$win=e_rand(1,38); 
		$winpic=$win;
		if ($win==37) { 
			$winpic="0"; $color="Green"; 
		}
		if ($win==38) { 
			$winpic="00"; $color="Green"; 
		}
		$showwin = $winpic;
		$winpic .= ".gif";
		$red=array(1=>1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36);
		while (list($key,$val)=each($red)){
			if ($win==$val) { 
				$color="Red"; 
			}
		}
		if ($color!="Green" && $color!="Red") { 
			$color="Black"; 
		}
		echo "<IMG SRC=\"./templates/default/images/casino/roulette/layout-clean.gif\"><br><br>\n";
		echo "The ball finally fell into the hole as the wheel slowed down and landed on...<br><br>";
		echo "<IMG SRC=\"./templates/default/images/casino/roulette/$winpic\" align=center>\n";
		echo " [ ".$color." ".$showwin." ]<br><br>";
		if ($payout!=38) {
			while (list($key,$val)=each($betarray)){
				if ($win==$val) { 
					$youwon=1; 
				}
			}
		}
		if ($mynum==$win || $youwon) {
			$winnings=round($mybet*$payout,0);
			$playerinfo['credits']+=$winnings;
			echo "You WON $winnings credits from the Roulette table!!!<br><br>";
			if ($payout==0.5) {
				echo "Based off your bet of $mybet credits with the odds of 1:2<br><br>";
			} else { 
				echo "Based off your bet of $mybet credits with the odds of $payout:1<br><br>"; 
			}
			//debuglog("won $winnings credits from the Roulette table");
		} else {
			$playerinfo['credits']-=$mybet;
			echo "You lost $mybet credits from the Roulette table.<br><br>";
			//debuglog("lost $mybet credits from the Roulette table");
		}
		$HTTP_GET_VARS['op']="";
	}
}

if ($HTTP_GET_VARS['op']!="spin") {
	if ($HTTP_GET_VARS['op']!="picknums") { 
		echo "<a href=port.php>port.phpReturn to the Casino<br></a>";
		echo "<a href=roulette.php>Play Again<br></a>";
	}
}

?>