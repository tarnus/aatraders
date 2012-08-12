<?php
// Blackjack Main
// blackjack.gif
// The objective of BlackJack is for a player to come as close to 21 without going over, while still having a higher number than the dealer.
// casino_blackjack_start
// N

// name - Display Name for the module
// image - image name for the module
// description - description of the module
// casino_link - link for the module This is the module file name minus the .inc. IE: modulename.inc would be listed as modulename
// online_status - "Y" display this file in the list of availible casino modules when the player enters the casino, "N" - do not display module


include ("globals/insert_news.inc");
include ("languages/$langdir/lang_casino.inc");

get_post_ifset("casinogame, action, bet_amt");

$template_object->enable_gzip = 0;

$title = $l_title_port;

if($sectorinfo['port_type'] != "casino")
{
	unset($_SESSION['newdeck'], $newdeck);
	unset($_SESSION['dealer'], $dealer);
	unset($_SESSION['bet'], $bet);
	unset($_SESSION['hand'], $hand);
	unset($_SESSION['handend'], $handend);
	unset($_SESSION['player'], $player);
	unset($_SESSION['player_split'], $player_split);
	unset($_SESSION['count'], $count);
	unset($_SESSION['status'], $status);
	unset($_SESSION['split_flag'], $split_flag);
	unset($_SESSION['playercards'], $playercards);
	unset($_SESSION['playersplitcards'], $playersplitcards);
	unset($_SESSION['dealercards'], $dealercards);
	unset($_SESSION['completedhand'], $completedhand);
	unset($_SESSION['old_bet'], $old_bet);
	close_database();
	echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=main.php\">";
	die();
}

if($playerinfo['template'] == '' or !isset($playerinfo['template'])){
	$templatename = $default_template;
}else{
	$templatename = $playerinfo['template'];
}
include ("header.php");

if($base_template[basename($_SERVER['PHP_SELF'])] == 1){
	include ("globals/base_template_data.inc");
	base_template_data();
}
else
{
	$template_object->assign("title", $title);
	$template_object->assign("templatename", $templatename);
}

//body goes here
function swap_shuffle($array) {
	mt_srand(hexdec(AAT_substr(md5(microtime()), -8)) & 0x7fffffff);
	for ($i=0;$i<sizeof($array);$i++) {
		$from=mt_rand(0,sizeof($array)-1);
		$old=$array[$i];
		$array[$i]=$array[$from];
		$array[$from]=$old;
	}
	return $array;
}

function cheater_found(){
	global $bet, $cash, $dealerout, $playersplitout, $playerout, $playerinfo, $shipinfo, $sectorinfo, $db, $db_prefix;
	$bet = 0;
	$cash /= 2;
	$dealerout="<font size=4><b>Cheater!  Cheater!  Cheater!<br><br>The Casino has confiscated HALF of your cash!</b></font>";
	$playersplitout="<font size=4><b>Cheater!  Cheater!  Cheater!<br><br>The Casino has confiscated HALF of your cash!</b></font>";
	$playerout="<font size=4><b>Cheater!  Cheater!  Cheater!<br><br>The Casino has confiscated HALF of your cash!</b></font>";

	$res = $db->Execute("SELECT character_name FROM {$db_prefix}players WHERE player_id = 1");
	$attackername = $res->fields['character_name'];
	$mystuff = $attackername . "|" . ($cash / 2) . "|" . $playerinfo['character_name'];
	insert_news($mystuff, 1, "bounty");

	$debug_query = $db->Execute("INSERT INTO {$db_prefix}bounty (bounty_on,placed_by,amount) values ($playerinfo[player_id], 1," . ($cash / 2) . ")");
	db_op_result($debug_query,__LINE__,__FILE__);
	$res = $db->Execute("INSERT INTO {$db_prefix}shoutbox (player_id,player_name,sb_date,sb_text,sb_alli) VALUES (1," . $db->qstr($attackername) . "," . time() . ", " . $db->qstr("$playerinfo[character_name] CHEATED the Casino in sector $sectorinfo[sector_name]") . ",0) ");
}

// Define Deck

$card=array();
$card[1]="AceSpades";
$card[2]="2Spades";
$card[3]="3Spades";
$card[4]="4Spades";
$card[5]="5Spades";
$card[6]="6Spades";
$card[7]="7Spades";
$card[8]="8Spades";
$card[9]="9Spades";
$card[10]="10Spades";
$card[11]="JackSpades";
$card[12]="QueenSpades";
$card[13]="KingSpades";
$card[14]="AceHearts";
$card[15]="2Hearts";
$card[16]="3Hearts";
$card[17]="4Hearts";
$card[18]="5Hearts";
$card[19]="6Hearts";
$card[20]="7Hearts";
$card[21]="8Hearts";
$card[22]="9Hearts";
$card[23]="10Hearts";
$card[24]="JackHearts";
$card[25]="QueenHearts";
$card[26]="KingHearts";
$card[27]="AceClubs";
$card[28]="2Clubs";
$card[29]="3Clubs";
$card[30]="4Clubs";
$card[31]="5Clubs";
$card[32]="6Clubs";
$card[33]="7Clubs";
$card[34]="8Clubs";
$card[35]="9Clubs";
$card[36]="10Clubs";
$card[37]="JackClubs";
$card[38]="QueenClubs";
$card[39]="KingClubs";
$card[40]="AceDiamonds";
$card[41]="2Diamonds";
$card[42]="3Diamonds";
$card[43]="4Diamonds";
$card[44]="5Diamonds";
$card[45]="6Diamonds";
$card[46]="7Diamonds";
$card[47]="8Diamonds";
$card[48]="9Diamonds";
$card[49]="10Diamonds";
$card[50]="JackDiamonds";
$card[51]="QueenDiamonds";
$card[52]="KingDiamonds";


function card_value($cards){
	global $newdeck;
	$numitems=count($cards);
	$cardtot=0;
	$cardtot2=0;
	$ace_count=0;
	for ($i=1;$i <=$numitems;$i++){
		$cardout=AAT_substr($newdeck[$cards[$i]],0,1);
		if (strstr("1,J,K,Q",$cardout)){
			$cardvalue=10;
		}elseif($cardout=="A"){
			$cardvalue=11;
			$ace_count++;
		}else{
			$cardvalue=$cardout;
		}
		$cardtot=$cardtot+$cardvalue;
		
		//echo "[". $cardvalue."]<br>";		
	}
	if (($cardtot) > 21){
		for ($x=1;$x <= $ace_count;$x++){
			if (($cardtot) > 21){
				$cardtot=$cardtot-10;
			}else{
				break;	
			}			
		}		
	}
	return $cardtot;
}

// deal 

function show_player_hand($playerout){
	global $newdeck, $templatename;
	$playerhandout="";
	$numitems=count($playerout);
	for ($i=1;$i <=$numitems;$i++){
		$cardout=($newdeck[$playerout[$i]]);
		$playerhandout.="<img src=\"templates/$templatename/images/casino/blackjack/".$cardout.".gif\"><img src=\"templates/$templatename/images/casino/spacer.gif\" width=\"2\">";
	}
	return $playerhandout;
}

function show_dealer_hand($playerout,$flag){
	global $newdeck, $templatename;
	$dealerhandout="";
	$numitems=count($playerout);
	for ($i=1;$i <=$numitems;$i++){
		if ($flag==0){
			if ($i >1){
				$cardout=($newdeck[$playerout[$i]]);
				$dealerhandout.="<img src=\"templates/$templatename/images/casino/blackjack/".$cardout.".gif\"><img src=\"images/spacer.gif\" width=\"2\">";
			}else{
				$dealerhandout.="<img src=\"templates/$templatename/images/casino/blackjack/card_down.gif\"><img src=\"images/spacer.gif\" width=\"2\">";
			}
		}else{
			$cardout=($newdeck[$playerout[$i]]);
			$dealerhandout.="<img src=\"templates/$templatename/images/casino/blackjack/".$cardout.".gif\"><img src=\"images/spacer.gif\" width=\"2\">";		
		}
	}
	return $dealerhandout;
}

function deal($deck,$count){
	global $count,$dealer,$player,$playercards,$dealercards;
	// is count + 4 > deck total
	// if so reshuffle
	// reset count
	// Get user first card
	$player[1]=$count;
	$player[2]=$count+2;
	$playercards=2;
	$dealercards=2;
	$dealer[1]=$count+1;
	$dealer[2]=$count+3;
	$count=$count+4;
}

$decks=3;

$cash=$playerinfo['credits'];

if (isset($_SESSION['count'])){
	$count=$_SESSION['count'];
	$bet=$_SESSION['bet'];
	$hand=$_SESSION['hand'];
	$handend=$_SESSION['handend'];
	$split_flag=$_SESSION['split_flag'];
	$newdeck=$_SESSION['newdeck'];
	$dealer=$_SESSION['dealer'];
	$status=$_SESSION['status'];
	$player=$_SESSION['player'];
	$player_split=$_SESSION['player_split'];
	$playercards=$_SESSION['playercards'];
	$dealercards=$_SESSION['dealercards'];
	$playersplitcards=$_SESSION['playersplitcards'];
	$completedhand=$_SESSION['completedhand'];
}

if ((!isset($count)) or ($count==0)){
	//init
	$bet=0;
	$swin=0;
	$win=0;
	$hand=0;
	$newdeck=array();
	$player=array();
	$dealer=array();
	$completedhand=array();
	//create big dec

	for ($i=1; $i <= $decks;$i++){
		$newdeck=array_merge($newdeck, $card);
	}
//echo count($newdeck)."<br>";
//Shuffle Deck
	$newdeck=swap_shuffle($newdeck);
	$count=1;
}

if ($count > (($decks*52)-10)){
	$newdeck=swap_shuffle($newdeck);
	$count=1;
}

$bet_amt = StripNonNum($bet_amt);

if (($bet_amt < 0)){
 	$bet_amt=0;		
}

switch ($action) {
	case "Hit":
		if ($split_flag==1){
			$split_flag=0;
		}
		if ($hand==0){
			if (($status!="Bust")or ($status!="21")){
				$playercards++;
				$player[$playercards]=$count;
				$count++;
				// CHeck Player Tot

				if (card_value($player)>21){
					$status="Bust";
					if ($split_flag==2){
						$hand=1;
					}else{
						$hand=0;
					}
				}elseif (card_value($player)==21){
					$status="21";
					if ($split_flag==2){
						$hand=1;
					}else{
						$hand=0;
					}
				}
			}
			$dealerout=show_dealer_hand($dealer,0);
			$playerout=show_player_hand($player);
			if ($split_flag==2){
				$playersplitout=show_player_hand($player_split);
			}
		}else{
			if (($status!="SBust")or ($status!="S21")){
				$playersplitcards++;
	   			$player_split[$playersplitcards]=$count;
				$count++;
				// CHeck Player Tot
				if (card_value($player_split)>21){
					$status="SBust";
				}elseif (card_value($player_split)==21){
					$status="S21";
				}
			}
			$dealerout=show_dealer_hand($dealer,0);
			$playerout=show_player_hand($player);

			if ($split_flag==2){
				$playersplitout=show_player_hand($player_split);
			}
		}
		break;

	case "Deal":
		$playercards=0;
		$dealercards=0;
		$split_flag=0;
		$hand=0;
		$handend=0;
		$playersplitcards=0;
		if ($bet_amt > $cash || $bet_amt > $max_casino_bet){
			$status="no bet";	
		}else{
			deal($newdeck,$count);
			$_SESSION['old_bet'] = $bet_amt;
			$dealerout=show_dealer_hand($dealer,0);
			$playerout=show_player_hand($player);
			$cardout=AAT_substr($newdeck[$dealer[2]],0,1);
			if ($cardout=="A"){
				$status="Insurance";
			}else{
				$status="Deal";
			}
			$bet=$bet_amt;
			$cash-=$bet;
		}	
		break;	

	case "Bet":
		unset($dealer);
		unset($player);
		unset($player_split);
		unset($completedhand);

		$playercards=0;
		$dealercards=0;
		$split_flag=0;
		$playersplitcards=0;
		$status="Bet";
		$hand=0;
		$handend=0;
		$bet = 0;
		$swin=0;
		$win=0;
		break;

	case "no bet":
		unset($dealer);
		unset($player);
		unset($player_split);
		unset($completedhand);

		$playercards=0;
		$dealercards=0;
		$split_flag=0;
		$playersplitcards=0;
		$status="Bet";
		$hand=0;
		$handend=0;
		break;	

	case "Stand":
		if ($handend==0){
			if ($hand==0){
				if($completedhand[0] != 1){
					if ($split_flag!=2){	
						$dealer_tot=card_value($dealer);
						$player_tot=card_value($player);
						while($dealer_tot <17 and $status!="DealerBust" ){
							$dealercards++;
							$dealer[$dealercards]=$count;
							$count++;
							$dealer_tot=card_value($dealer);
							if ($dealer_tot > 21){
								$status="DealerBust";
							}
						}
						$dealer_tot=card_value($dealer);
						if (($dealercards==2) and ($dealer_tot==21)){
							$status="DealerBlackJack";
						}elseif ($dealer_tot > 21){
							$status="DealerBust";
							$cash+=$bet*2;
							$win=$bet*2;
						}elseif ($dealer_tot > $player_tot){
							$status="DealerWin";
						}elseif($dealer_tot < $player_tot){
							$status="PlayerWin";
							$cash+=$bet*2;
							$win=$bet*2;
						}else{
							$status="Push";
							$cash+=$bet;
							$win=$bet;
						}
						$dealerout=show_dealer_hand($dealer,1);
						$playerout=show_player_hand($player);
					}else{
						$dealerout=show_dealer_hand($dealer,0);
						$playerout=show_player_hand($player);
					}
					if ($split_flag==2){
						$hand=1;
						$playersplitout=show_player_hand($player_split);
					}
					$completedhand[0] = 1;
				}else{
					cheater_found();
				}
			}else{
				if($completedhand[1] != 1){
					$dealer_tot=card_value($dealer);
					$playersplit_tot=card_value($player_split);
					$handend=1;
					while($dealer_tot <17 and $status!="SDealerBust" ){
						$dealercards++;
						$dealer[$dealercards]=$count;
						$count++;
						$dealer_tot=card_value($dealer);
						if ($dealer_tot > 21){
							$status="SDealerBust";
						}
					}
					$dealer_tot=card_value($dealer);
					if (($dealercards==2) and ($dealer_tot==21)){
						$status="SDealerBlackJack";
					}elseif ($dealer_tot > 21){
						$status="SDealerBust";
						$cash+=$bet*2;
						$swin=$bet*2;
					}elseif ($dealer_tot > $playersplit_tot){
						$status="SDealerWin";
					}elseif($dealer_tot < $playersplit_tot){
						$status="SPlayerWin";
						$cash+=$bet*2;
						$swin=$bet*2;
					}else{
						$status="SPush";
						$cash+=$bet;
						$swin=$bet;
					}
					$dealerout=show_dealer_hand($dealer,1);
					$playerout=show_player_hand($player);
					if ($split_flag==2){
						$playersplitout=show_player_hand($player_split);
					}
					$completedhand[1] = 1;
				}else{
					cheater_found();
				}
			}
			if ($split_flag==0){
				$handend=1;
			}
		}else{
			$dealerout=show_dealer_hand($dealer,1);
			$playerout=show_player_hand($player);
			if ($split_flag==2){
				$playersplitout=show_player_hand($player_split);
			}
		}
		break;

	case "DoubleD":
		if ($hand==0){
			if($completedhand[0] != 1){
				$cash-=$bet;
				$bet+=$bet;
				if (($status!="Bust")or ($status!="21")){
					$playercards++;
					$player[$playercards]=$count;
					$count++;
					// CHeck Player Tot

					if (card_value($player)>21){
						$status="Bust";
						if ($split_flag==2){
							$hand=1;
						}else{
							$hand=0;
						}
					}
				}
				$dealer_tot=card_value($dealer);
				$player_tot=card_value($player);
				while($dealer_tot <17 and $status!="DealerBust" and $status!="Bust"){
					$dealercards++;
					$dealer[$dealercards]=$count;
					$count++;
					$dealer_tot=card_value($dealer);
					if ($dealer_tot > 21){
						$status="DealerBust";
					}
				}
				$dealer_tot=card_value($dealer);
				if ($dealer_tot > 21){
					$status="DealerBust";
					$cash+=$bet*2;
					$win=$bet*2;
				}elseif ($dealer_tot > $player_tot){
					$status="DealerWin";
				}elseif(($dealer_tot < $player_tot) and ($status !="Bust")){
					$status="PlayerWin";
					$cash+=$bet*2;
					$win=$bet*2;
				}elseif(($dealer_tot < $player_tot) and ($status =="Bust")){
					$status="DealerWin";
				}else{
					$status="Push";
					$cash+=$bet;
					$win=$bet;
				}

				$dealerout=show_dealer_hand($dealer,1);
				$playerout=show_player_hand($player);
				if ($split_flag==2){
					$playersplitout=show_player_hand($player_split);
				}
				$completedhand[0] = 1;
			}else{
				cheater_found();
			}
		}else{
			if($completedhand[1] != 1){
				$cash-=$bet;
				$bet+=$bet;
				if (($status!="SBust")or ($status!="S21")){
					$playersplitcards++;
					$player_split[$playersplitcards]=$count;
					$count++;
					// CHeck Player Tot

					if (card_value($player_split)>21){
						$status="SBust";
					}
				}

				$dealer_tot=card_value($dealer);
				$playersplit_tot=card_value($player_split);
				while($dealer_tot <17 and $status!="SDealerBust" and $status!="SBust"){
					$dealercards++;
					$dealer[$dealercards]=$count;
					$count++;
					$dealer_tot=card_value($dealer);
					if ($dealer_tot > 21){
						$status="SDealerBust";
						$cash+=$bet*2;
						$swin=$bet*2;
					}
				}
				$dealer_tot=card_value($dealer);
				if ($dealer_tot > 21){
					$status="SDealerBust";
					$cash+=$bet*2;
					$swin=$bet*2;
				}elseif ($dealer_tot > $player_tot){
					$status="SDealerWin";
				}elseif(($dealer_tot < $player_tot) and ($status !="Bust")){
					$status="SPlayerWin";
					$cash+=$bet*2;
					$swin=$bet*2;
				}elseif(($dealer_tot < $player_tot) and ($status =="Bust")){
					$status="SDealerWin";
				}else{
					$status="SPush";
					$cash+=$bet;
					$swin=$bet;
				}

				$dealerout=show_dealer_hand($dealer,1);
				$playersplitout=show_player_hand($player_split);	
				$completedhand[1] = 1;
			}else{
				cheater_found();
			}
		}
		break;	

	case "Split":
		$sbet=$bet;
		$cash-=$bet;
		$card1=$player[1];
		$card2=$player[2];
		unset($player);
		unset($player_split);
		$playercards=0;
		$player_split[1]=$card1;
		$player[1]=$card2;
		$player[2]=$count;
		$player_split[2]=$count+1;
		$count+=2;
		$playercards=2;
		$playersplitcards=2;
		$split_flag=2;
		$dealerout=show_dealer_hand($dealer,0);
		$playerout=show_player_hand($player);
		$playersplitout=show_player_hand($player_split);
		break;

	case "Insurance":
		$insurance=$bet/2;
		$cash-=$insurance;
		// check for dealer blackjack 
		if (card_value($dealer)==21){
			$cash+=$insurance*2;
			$win=$bet*2;
			$status="DealerBlackJack";
		}else{
			$status="InsuranceOut";
		}
		if ($status=="DealerBlackJack"){
			$dealerout=show_dealer_hand($dealer,1);
		}else{
			$dealerout=show_dealer_hand($dealer,0);	
		}	
		$playerout=show_player_hand($player);
		break;

	case "Clear":
		unset($_SESSION['newdeck'], $newdeck);
		unset($_SESSION['dealer'], $dealer);
		unset($_SESSION['bet'], $bet);
		unset($_SESSION['hand'], $hand);
		unset($_SESSION['handend'], $handend);
		unset($_SESSION['player'], $player);
		unset($_SESSION['player_split'], $player_split);
		unset($_SESSION['count'], $count);
		unset($_SESSION['status'], $status);
		unset($_SESSION['split_flag'], $split_flag);
		unset($_SESSION['playercards'], $playercards);
		unset($_SESSION['playersplitcards'], $playersplitcards);
		unset($_SESSION['dealercards'], $dealercards);
		unset($_SESSION['completedhand'], $completedhand);
		break;
}

$deduct_turn = "";
if($handend == 1)
{
	$deduct_turn = ", turns=turns-1 , turns_used=turns_used+1";
}

if ((!isset($split_flag))and($split_flag!=2)){
	$split_flag=0;
}

if (($split_flag == 2)  and (($status =="SPlayerWin") or ($status =="SPush") or($status =="SDealerBust")) ){
	$cash+=$bet;
	$deduct_turn = ", turns=turns-1 , turns_used=turns_used+1";
}

if (($split_flag == 2)  and (($status =="PlayerWin") or ($status =="Push") or($status =="DealerBust")) ){
	$cash+=$bet;
	$deduct_turn = ", turns=turns-1 , turns_used=turns_used+1";
}

if (($split_flag == 2) and (($status =="SDealerBust") or ($status =="DealerBust"))){
	$cash+=$bet;
	$deduct_turn = ", turns=turns-1 , turns_used=turns_used+1";
}

if (($playercards==2) and ($status!="Insurance")){
	if (card_value($player)==21){
		$status="PlayerBlackJack";
		$cash+=(($bet*2)+($bet/2));
		$win=(($bet*2)+($bet/2));
		$deduct_turn = ", turns=turns-1 , turns_used=turns_used+1";
	}
}else{
	if (($playercards==2) and (card_value($player)==21) and ($status=="InsuranceWin")){
		$status="PlayerBlackJackIns";
		$cash+=(($bet*2)+($bet/2));
		$win=(($bet*2)+($bet/2));
		$deduct_turn = ", turns=turns-1 , turns_used=turns_used+1";
	}
}

$debug_query = $db->Execute("UPDATE {$db_prefix}players SET credits=$cash $deduct_turn WHERE player_id=$playerinfo[player_id]");
db_op_result($debug_query,__LINE__,__FILE__);

if ($playercards==2){
	$card1=AAT_substr($newdeck[$player[1]],0,1);
	$card2=AAT_substr($newdeck[$player[2]],0,1);

	if ($card1==$card2){
		$split_flag=1;
	}
}

$_SESSION['count']=$count;
$_SESSION['newdeck']=$newdeck;
$_SESSION['dealer']=$dealer;
$_SESSION['bet']=$bet;
$_SESSION['hand']=$hand;
$_SESSION['handend']=$handend;
$_SESSION['split_flag']=$split_flag;
$_SESSION['player']=$player;
$_SESSION['player_split']=$player_split;
$_SESSION['playercards']=$playercards;
$_SESSION['playersplitcards']=$playersplitcards;
$_SESSION['dealercards']=$dealercards;
$_SESSION['status']=$status;
$_SESSION['completedhand']=$completedhand;
//echo $status;
// update Player credits in DB

$availcash=1;
if (($cash-$bet) <=0){
	$availcash=0;
}

$template_object->assign("l_firsthand", $l_firsthand);	
$template_object->assign("l_secondhand", $l_secondhand);		
$template_object->assign("l_bet", $l_bet);	
$template_object->assign("l_stand",$l_stand);	
$template_object->assign("l_hit",$l_hit);	
$template_object->assign("l_insurance",$l_insurance );
$template_object->assign("l_doubledown",$l_doubledown);
$template_object->assign("l_lobby",$l_lobby);	
$template_object->assign("l_split",$l_split); 	
$template_object->assign("l_credits",$l_credits); 
$template_object->assign("l_yourbet",$l_yourbet);	
$template_object->assign("l_dealerbust",$l_dealerbust);
$template_object->assign("l_dealerwins",$l_dealerwins);
$template_object->assign("l_nobet",$l_nobet);
$template_object->assign("l_dealerloses",$l_dealerloses);
$template_object->assign("l_dealerblackjack",$l_dealerblackjack);
$template_object->assign("l_push",$l_push);		
$template_object->assign("l_playerwins",$l_playerwins);
$template_object->assign("l_playerbust",$l_playerbust);
$template_object->assign("l_playerloses",$l_playerloses);
$template_object->assign("l_playerblackjack",$l_playerblackjack);
$template_object->assign("l_place_bet",$l_place_bet);	
$template_object->assign("error_msg", $l_planet_none);
$template_object->assign("gotomain", $l_global_mmenu);

if ($split_flag > 1){
	$template_object->assign("bet", NUMBER($bet*2));
}else{
	$template_object->assign("bet", NUMBER($bet));
}

$template_object->assign("availcash", $availcash);
$template_object->assign("old_bet", $_SESSION['old_bet']);
$template_object->assign("hand", $hand);
$template_object->assign("playercards", $playercards);	
$template_object->assign("split_flag", $split_flag);	
$template_object->assign("cash", NUMBER($cash));
$template_object->assign("dealerout", $dealerout);
$template_object->assign("playerout", $playerout);
$template_object->assign("playersplitout", $playersplitout);
$template_object->assign("status", $status);
$template_object->assign("gotomain", $l_global_mmenu);
$template_object->display($templatename."casino_blackjack.tpl");
include ("footer.php");
?>
