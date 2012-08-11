<h1>{$title}</h1>


<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
{$l_new_charis} <font color="yellow"><b>{$character}</b></font><br><br>
{if $display_password}
	{$l_new_pwis} {$makepass}<br><br>
{/if}

{if $enable_profilesupport == 1}
	{$message}<br>
	{$message2}<br><br>
{/if}

{$emailresult}<br><br>
<a href="index.php" class=nav>{$l_clickme}</a> {$l_new_login}<br><br>

</td></tr>
		</table>
	</td>
  </tr>
</table>
