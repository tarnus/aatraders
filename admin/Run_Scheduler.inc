<?php
// 4: Run Scheduler
// This tool will allow you to run the Scheduler for the game.  Information will be displayed about every operation the scheduler performs.

echo "<tr><td><FORM ACTION=scheduler.php TARGET=_blank METHOD=POST>";
echo "<INPUT TYPE=HIDDEN NAME=admin_password VALUE=$admin_password>";
echo "<INPUT TYPE=HIDDEN NAME=game_number VALUE=$game_number>";
echo "<INPUT TYPE=HIDDEN NAME=adminexecuted VALUE=1>";
echo "<table><TR nowrap><TD>Click the RUN button if you want to exit the Admin program and run the Scheduler.&nbsp;&nbsp;</TD>";
echo "<TD ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME=command VALUE=\"RUN\"></TD></TR>";
echo "</table></form></td></tr>";
?>
