<?php
// 1: Admin DB Error Log
// Any database errors can be viewd using this tool.  The errors will display the full query that caused the error, where the error occured in the query, the program file and line number where the error occured.

echo "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=log.php?player=0&md5admin_password=" . md5($admin_password) . "&game_number=$game_number&dberror=1\">";

?>
