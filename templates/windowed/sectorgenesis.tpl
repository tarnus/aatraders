<H1>{$title}</H1>

<form action="sectorgenesis.php" method="post">
<table width="500" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td colspan=2>{$l_sgns_shipcredits} {$credits}<br>{$l_sgns_createcost} {$sgcostnumber}</td></tr>
<tr><td colspan=2><br><br>{$l_sgcreate}</td></tr>
<tr><td colspan=2><br><br>{$l_sgns_sectorname}&nbsp;<input type="text" name="sectorname" maxlength="30"></td></tr>
<tr><td><input type="hidden" name="sglink" value="1">
<input type="submit" value="{$l_submit}" ><input type="reset" value="{$l_reset}">
</td></tr>
</form>
{if $sector_type != 0}
	<form action="sectorgenesis.php" method="post">
	<tr><td valign="middle" colspan="2"><br><br>{$l_sgcreatens}:&nbsp;<input type="text" name="target_sector" size="10" maxlength="30" value="">
	</td><tr><tr><td colspan=2><input type="hidden" name="rslink" value="1">
	<input type="submit" value="{$l_submit}" onclick="clean_js()"><input type="reset" value="{$l_reset}">
	</td></tr>
	</form>
{/if}
</td></tr>

<tr><td colspan=2><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table> 
