<H1>{$title}</H1>

<table width="50%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
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
			echo "<TR BGCOLOR=\"#000000\">";
			echo "<TD><B>$l_amount</TD>";
			echo "<TD><B>$l_by_placedby</TD>";
			echo "<TD><B>$l_by_action</TD>";
			echo "</TR>";
			$color = "#000000";
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
{/php}
				</td>
			</tr>
<tr><td><br><br>{$gotobounty}<br></td></tr>
<tr><td><br>{$gotomain}<br></td></tr>
		</table>
	</td>
  </tr>
</table>
