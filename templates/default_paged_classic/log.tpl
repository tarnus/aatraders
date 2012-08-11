<h1>{$title}</h1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
	<tr>
		<td bgcolor="#000000" valign="top" align="center" colspan=2>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td align="center">
						<font size=4 color=#52ACEA><b>&nbsp;&nbsp;&nbsp;{$logline}</b></font><br><br><br>
					</td>
				</tr>
				<TR>
					<TD>
						<center>
						<table width=100% border=0 cellspacing=0 cellpadding=0>
							<tr>
								<td align="left">
									<a href=log.php?loglist={$loglist}&startdate={$backlink}><font color=white size =3><b>«« {$backdate}</b></font></a>
								</td>
								<td align="center">
								{if $isadmin}
									<FORM action=admin.php method=POST>
									<input type=hidden name=md5admin_password value="{$md5admin_password}">
									<input type=hidden name=menu value="{$menu}">
									<input type=hidden name=dead_player value="{$dead_player}">
									<input type=submit value="Return to Admin">
									</form>
								{else}
									<font size=2 face=arial>{$l_log_click}</font>
								{/if}
								</td>
								<td align="right">
									<a href=log.php?loglist={$loglist}&startdate={$nextlink}><font color=white size=3><b>{$nextdate} »»</b></font></a>
								</td>
							</tr>
						</table>
						<table width=100% border=0 cellspacing=0 cellpadding=0>
						{if !$isadmin}
							<tr>
								<td>
									<table width=300 border=0 cellspacing=0 cellpadding=0 align=center>
										<tr>
											<td align=center>
												<font color=cyan size =2><b>{$l_log_select}</b></font><br><br>
												<a href=log.php?loglist=&startdate={$startdate}><font color=white size =2><b>{$l_log_general}</b></font></a> - 
												<a href=log.php?loglist=1&startdate={$startdate}><font color=white size=2><b>{$l_log_dig}</b></font></a><br>
												<a href=log.php?loglist=2&startdate={$startdate}><font color=white size=2><b>{$l_log_spy}</b></font></a> - 
												<a href=log.php?loglist=3&startdate={$startdate}><font color=white size=2><b>{$l_log_disaster}</b></font></a><br>
												<a href=log.php?loglist=4&startdate={$startdate}><font color=white size=2><b>{$l_log_nova}</b></font></a> - 
												<a href=log.php?loglist=5&startdate={$startdate}><font color=white size=2><b>{$l_log_attack}</b></font></a><br>
												<a href=log.php?loglist=6&startdate={$startdate}><font color=white size=2><b>{$l_log_scan}</b></font></a> - 
												<a href=log.php?loglist=7&startdate={$startdate}><font color=white size=2><b>{$l_log_starv}</b></font></a><br>
												<a href=log.php?loglist=9&startdate={$startdate}><font color=white size=2><b>{$l_log_probe}</b></font></a> - 
												<a href=log.php?loglist=10&startdate={$startdate}><font color=white size=2><b>{$l_log_autotrade}</b></font></a><br>
												<a href=log.php?loglist=8&startdate={$startdate}><font color=white size=2><b>{$l_log_combined}</b></font></a><br>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						{/if}
							<tr>
								<td>
									<table border=0 width=100%>
										<tr>
											<td>
												<center>
												<br>
												<font size=2 color=#DEDEEF><b>{$l_log_start} {$entry}<br><br>{$logtype}<b></font>
												<hr width=80% size=1 NOSHADE style="color: #52ACEA">
												</center>
{php}
for($i = 0; $i < $logcount; $i++)
{
	echo "<table border=0 cellspacing=5 width=100%>" .
		 "<tr>" .
		 "<td><font size=2 color=#52ACEA><b>$logtitle[$i]</b></td>" .
		 "<td align=right><font size=2 color=#52ACEA><b>$logtime[$i]</b></td>" .
		 "</tr><tr><td colspan=2>" .
		 "<font size=2 color=#DEDEEF>" .
		 "$logbody[$i]" .
		 "</td></tr>" .
		 "</table>" .
		 "<center><hr width=80% size=1 NOSHADE style=\"color: #52ACEA\"></center>";
}
{/php}
												<center>
												<br>
												<font size=2 color=#DEDEEF><b>{$l_log_end} {$endentry}<b></font>
												</center>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
						<table width=100% border=0 cellspacing=0 cellpadding=0>
							<tr>
								<td align="left">
									<a href=log.php?loglist={$loglist}&startdate={$backlink}><font color=white size =3><b>«« {$backdate}</b></font></a>
								</td>
								<td align="center">
									<br><br>
								{if $isadmin}
									<FORM action=admin.php method=POST>
									<input type=hidden name=md5admin_password value="{$md5admin_password}">
									<input type=hidden name=menu value="{$menu}">
									<input type=hidden name=dead_player value="{$dead_player}">
									<input type=submit value="Return to Admin">
									</form>
								{else}
									<font size=2 face=arial>{$l_log_click}</font>
								{/if}
								</td>
								<td align="right">
									<a href=log.php?loglist={$loglist}&startdate={$nextlink}><font color=white size=3><b>{$nextdate} »»</b></font></a>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
 