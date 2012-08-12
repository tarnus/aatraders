<H1>{$title}</H1>

<table  cellspacing = "0" cellpadding = "0" border = "0" align="center" width="400">
	<tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
	</tr>
	<tr>
		<td colspan=4>
			<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
				<tr>
					<td>	
						<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
							<tr bgcolor="black">
								<td valign="top" width=18><img src = "templates/{$templatename}images/g-mid-left.gif" height="200" width="18"></TD>
								<td valign="top">
									<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>

{if $sure == 0}
	<FONT COLOR=RED><B>{$l_die_rusure}</B></FONT><BR><BR>
	<A HREF=main.php>{$l_die_nonono}</A> {$l_die_what}<BR><BR>
	<A HREF=self_destruct.php?sure=1>{$l_yes}!</A> {$l_die_goodbye}<BR><BR>
{/if}

{if $sure == 1}
	<FONT COLOR=RED><B>{$l_die_check}</B></FONT><BR><BR>
	<A HREF=main.php>{$l_die_nonono}</A> {$l_die_what}<BR><BR>
	<A HREF=self_destruct.php?sure=2>{$l_yes}!</A> {$l_die_goodbye}<BR><BR>
{/if}

{if $sure == 2}
	{$l_die_count}<BR>
	{$l_die_vapor}<BR><BR>
	{$l_die_please2}<BR>
{/if}

</td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td valign="top" width=18><img src = "templates/{$templatename}images/g-mid-right.gif" height="200" width="18"></TD>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
	</tr>
</table>