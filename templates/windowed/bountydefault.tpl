<H1>{$title}</H1>

<FORM ACTION=bounty.php METHOD=POST>

<table width="50%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0">
			<TR>
				<TD>
{$l_by_bountyon}</TD><TD><SELECT NAME=bounty_on>
{php}
for($i = 0; $i <$playerlist; $i++){
			echo "<OPTION VALUE=$playerid[$i] $playerselect[$i]>$playername[$i]</OPTION>";
}
{/php}
</SELECT></TD></TR>
<TR><TD>{$l_by_amount}:</TD><TD><INPUT TYPE=TEXT NAME=amount SIZE=20 MAXLENGTH=20></TD></TR>
<TR><TD></TD><TD><INPUT TYPE=SUBMIT VALUE={$l_by_place}><INPUT TYPE=RESET VALUE=Clear></TD>
<tr><td>
<input type=hidden name=response value=place>
</td></tr></TABLE>
</FORM>
<table border=0 cellspacing=0 cellpadding=2 width="100%">
<tr><td>
{php}
		if ($num_bounties < 1)
		{
			echo "$l_by_nobounties<BR>";
		}
		else
		{
			echo $l_by_moredetails . "<BR><BR>";
			echo "<TABLE WIDTH=\"100%\" BORDER=0 CELLSPACING=0 CELLPADDING=2>";
			echo "<TR BGCOLOR=\"#585980\">";
			echo "<TD><B>$l_by_bountyon</B></TD>";
			echo "<TD><B>$l_amount</TD>";
			echo "</TR>";
			$color = "#3A3B6E";
			for ($i=0; $i<$num_bounties; $i++)
			{
				echo "<TR BGCOLOR=\"$color\">";
				echo "<TD><A HREF=bounty.php?bounty_on=" . $bountyon[$i] . "&response=display>". $bountyname[$i] ."</A></TD>";
				echo "<TD>&nbsp;" . $bountyamount[$i] . "&nbsp;</TD>";
				echo "</TR>";

				if ($color == "#3A3B6E")
				{
				   $color = "#23244F";
				}
				else
				{
				   $color = "#3A3B6E";
				}
			}
		echo "</TABLE>";
		}
{/php}
</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>

		</table>
	</td>
  </tr>
</table>
