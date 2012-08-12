<?php
// 7: Run Create Game (erases current game and builds new one)
// WARNING!!!!!<br><br>This tool will completely reset the currently running game.  All players will be deleted and a new galaxy will be created.

echo "<tr><td><FORM ACTION=create_game.php METHOD=POST>";
echo "  <input type=\"hidden\" name=\"game_number\" value=\"$game_number\">\n";
echo "  <input type=\"hidden\" name=\"autorun\" value=\"1\">\n";
echo "  <input type=\"hidden\" name=\"step\" value=\"10\">\n";
echo "  <input type=\"hidden\" name=\"resetgame\" value=\"1\">\n";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<table><TR nowrap><TD>Click the RUN button if you want to exit the Admin program and run the Create Universe program.&nbsp;&nbsp;<br><font color=\"yellow\"><b>WARNING: This will delete the current game!!!</b></font><br><br>
If you click on <b>Close Game</b> the server will be closed and player profiles<br>
	of all registered players will be compiled and sent to the Profile Server.  The<br>
	Profile Server will only accept closed game updates <b>ONCE EVERY TWO WEEKS<b> from<br>
	a server.  Any futher game closings or game resets will be ignored.</TD>";
echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"RUN\"></TD></TR>";
echo "</table></form></td></td>";
?>
