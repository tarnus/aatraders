<H1>{$title}</H1>

<table width="650" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
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
										<tr><td width="100%" colspan=3><br><br>{$gotomain}</td></tr>
		</table>
	</td>
  </tr>
</table>
