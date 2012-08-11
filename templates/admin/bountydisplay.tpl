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
<FORM ACTION=admin.php METHOD=POST>
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
						echo "<TD>$l_by_fedcollectonly<br><input type=\"radio\" name=\"bid\" value=\"" . $bountyid[$j] . "\"> $l_by_cancel</A></TD>";
					}
					else
					{
						echo "<TD>$l_none<br><input type=\"radio\" name=\"bid\" value=\"" . $bountyid[$j] . "\"> $l_by_cancel</A></TD>";
					}
				}
				else
				if ($bountyby[$j] == 1)
				{
					echo "<TD>$l_by_thealliance</TD>";
					if ($alliance_bounty_count <= $bountydetails[$j])
					{
						echo "<TD>$l_by_allaincecollectonly<br><input type=\"radio\" name=\"bid\" value=\"" . $bountyid[$j] . "\"> $l_by_cancel</A></TD>";
					}
					else
					{
						echo "<TD>$l_none<br><input type=\"radio\" name=\"bid\" value=\"" . $bountyid[$j] . "\"> $l_by_cancel</A></TD>";
					}
				}
				else
				{
					echo "<TD>" . $bountydetails[$j] . "</TD>";
					echo "<TD><input type=\"radio\" name=\"bid\" value=\"" . $bountyid[$j] . "\"> $l_by_cancel</A></TD>";
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
<tr><td align="center"><INPUT TYPE=SUBMIT VALUE="Cancel Selected Bounty"></td></tr>
<input type=hidden name="bounty_on" value="{$bounty_on}">
<input type=hidden name="response" value="cancel">
<input type="hidden" name="game_number" value="{$game_number}">
<input type=hidden name=md5admin_password value={$md5admin_password}>
<input type="hidden" name="menu" value="Editor_Bounties">
</form>
				</td>
			</tr>
		</table>
	</td>
  </tr>
</table>
