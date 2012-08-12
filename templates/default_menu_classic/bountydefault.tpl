<H1>{$title}</H1>

<FORM ACTION=bounty.php METHOD=POST>

<table width="50%" border="0" cellspacing="0" cellpadding="0" align="center">
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-top-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-top-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-top-midright.gif" width="100%" height="20"></td>
		<td width=18><img src = "templates/{$templatename}images/g-top-right.gif"></td>
  </tr>
  <tr>
    <td background="templates/{$templatename}images/g-mid-left.gif">&nbsp;</td>
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
			echo "<TR BGCOLOR=\"#000000\">";
			echo "<TD><B>$l_by_bountyon</B></TD>";
			echo "<TD><B>$l_amount</TD>";
			echo "</TR>";
			$color = "#000000";
			for ($i=0; $i<$num_bounties; $i++)
			{
				echo "<TR BGCOLOR=\"$color\">";
				echo "<TD><A HREF=bounty.php?bounty_on=" . $bountyon[$i] . "&response=display>". $bountyname[$i] ."</A></TD>";
				echo "<TD>&nbsp;" . $bountyamount[$i] . "&nbsp;</TD>";
				echo "</TR>";

				if ($color == "#000000")
				{
				   $color = "#000000";
				}
				else
				{
				   $color = "#000000";
				}
			}
		echo "</TABLE>";
		}
{/php}
<BR><BR>
</td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>

		</table>
	</td>
    <td background="templates/{$templatename}images/g-mid-right.gif">&nbsp;</td>
  </tr>
  <tr>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-left.gif"></td>
		<td width=101><img src = "templates/{$templatename}images/g-bottom-midleft.gif"></td>
		<td width="100%"><img src = "templates/{$templatename}images/g-bottom-midright.gif" width="100%" height="12"></td>
		<td width=18><img src = "templates/{$templatename}images/g-bottom-right.gif"></td>
  </tr>
</table>
