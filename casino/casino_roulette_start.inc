<?php
// Roulette
// roulette.gif
// In Roulette, the layout consists of 38 numbers ( 0, 00, and 1 through 36 ); the numbers are alternately colored red and black with the 0 and 00 colored green. To play, the player places a bet on a number, color or group of numbers on the layout (or roulette table). The wheel and ball are spun, and the slot the ball falls into determines the winner. The amount of the pay-off depends on the position and the amount of chips that were placed on the winning number.
// casino_roulette_start
// Y

// name - Display Name for the module
// image - image name for the module
// description - description of the module
// casino_link - link for the module This is the module file name minus the .inc. IE: modulename.inc would be listed as modulename
// online_status - "Y" display this file in the list of availible casino modules when the player enters the casino, "N" - do not display module

$template_object->enable_gzip = 0;

// CLear all current casino related session data
unset($_SESSION['bet'], $bet);
unset($_SESSION['old_bet'], $old_bet);
// End clear

unset($_SESSION['currentprogram'], $currentprogram);
unset ($template_object);
close_database();
echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=casino.php?casinogame=casino_roulette\">";
