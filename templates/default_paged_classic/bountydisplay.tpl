<H1>{$title}</H1>

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
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD align="center" class="nav_title_14b">
			{$l_by_bountyon} {$playername}
				</td>
			</tr>
			<TR>
				<TD>
{php}
			echo '<table border=1 cellspacing=0 cellpadding=2 align=center width="100%">';
			echo "<TR BGCOLOR=\"#585980\">";
			echo "<TD><B>$l_amount</TD>";
			echo "<TD><B>$l_by_placedby</TD>";
			echo "<TD><B>$l_by_action</TD>";
			echo "</TR>";
			$color = "#3A3B6E";
			for ($j=0; $j<$num_details; $j++)
			{
				echo "<TR BGCOLOR=\"$color\">";
				echo "<TD>&nbsp;" . $bountyamount[$j] . "&nbsp;</TD>";
				if ($bountyby[$j] == 3)
				{
					echo "<TD>$l_by_thefeds</TD>";
					if ($fed_bounty_count <= $bountydetails[$j])
					{
						echo "<TD>$l_by_fedcollectonly</TD>";
					}
					else
					{
						echo "<TD>$l_none</TD>";
					}
				}
				else
				if ($bountyby[$j] == 1)
				{
					echo "<TD>$l_by_thealliance</TD>";
					if ($alliance_bounty_count <= $bountydetails[$j])
					{
						echo "<TD>$l_by_allaincecollectonly</TD>";
					}
					else
					{
						echo "<TD>$l_none</TD>";
					}
				}
				else
				{
					echo "<TD>" . $bountydetails[$j] . "</TD>";

					if ($bountyby[$j] == $playerid)
					{
						echo "<TD><A HREF=bounty.php?bid=" . $bountyid[$j] . "&response=cancel>$l_by_cancel</A></TD>";
					}
					else
					{
						echo "<TD>$l_none</TD>";
					}
				}
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
{/php}
				</td>
			</tr>
<tr><td><br><br>{$gotobounty}<br></td></tr>
<tr><td><br>{$gotomain}<br></td></tr>
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
