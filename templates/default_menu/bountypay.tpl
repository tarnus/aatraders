<h1>{$title}</h1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
				{$notenough}<br>{$l_creds_to_spend}<br>
<center><form action="port.php?pay=2" method="post">
{$l_pay_partial} <input type="text" name="pmt_amt" width="10" size="15" value="0">&nbsp;<input type="Submit" value=" {$l_pay_button} ">
</form></b></font></center></td>
			</tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
