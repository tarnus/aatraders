<?php
// Blackjack
// blackjack.gif
// The objective of BlackJack is for a player to come as close to 21 without going over, while still having a higher number than the dealer.
// casino_blackjack_start
// Y

// name - Display Name for the module
// image - image name for the module
// description - description of the module
// casino_link - link for the module This is the module file name minus the .inc. IE: modulename.inc would be listed as modulename
// online_status - "Y" display this file in the list of availible casino modules when the player enters the casino, "N" - do not display module

$template_object->enable_gzip = 0;

// CLear all current casino related session data
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
unset($_SESSION['old_bet'], $old_bet);
unset($_SESSION['completedhand'], $completedhand);
// End clear

unset($_SESSION['currentprogram'], $currentprogram);
unset ($template_object);
close_database();
echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=casino.php?casinogame=casino_blackjack\">";
