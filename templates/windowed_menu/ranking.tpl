<H1>{$title}</H1>
<table width="935" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0">
			<TR align="center">
				<TD NOWRAP>
{if $multiplepages != 0}
	<TABLE border=0 cellpadding=2 cellspacing=1 width=725>
	<form action="ranking.php" method="post">
	<TR><TD align='right'>
	{$l_ranks_select}:
	</td><td align='left'><select name="page">
	{php}
	for($i = 0; $i <= $multiplepages; $i++){
		if(($i * $max_rank) == ($page * $max_rank))
			$selected = "selected";
		else $selected = "";
		
		echo "<option value=\"". $i."\"$selected> $l_ranks_page ".  $i ."</option>\n";
	}
	{/php}
	<option value="-1" {$allselected}>{$l_all}</option>
	</select>
	&nbsp;<input type="submit" value="{$l_submit}">
	<input type="hidden" name="sort" value="{$sort}">
	</TD></tr>
	</form>
	</table>
{/if}

{php}
if($page != 0)
	$prevlink = "<a href=\"ranking.php?page=".($page - 1) ."&sort={$sort}\">$l_ranks_prev</a>";
else $prevlink = "&nbsp;";

if(($page + 1) * $max_rank < $num_players )
	$nextlink = "<a href=\"ranking.php?page=".($page + 1) ."&sort={$sort}\">$l_ranks_next</a>";
else $nextlink = "&nbsp;";

echo "<TABLE border=0 cellpadding=2 cellspacing=1 width=935>\n";
echo "<TR><TD align='left'>$prevlink</td>\n";
echo "<TD align='right'>$nextlink</td></tr>\n";
echo "</table>";
{/php}

{if !$res}
	{$l_ranks_none}<br>
{else}
	<br>{$l_ranks_pnum}: {$num_players}
	<br>{$l_ranks_show} {$rankfrom} {$l_ranks_to} {$rankto}
	<br>{$l_ranks_dships}

	<br><br>

	<table border=0 cellspacing=0 cellpadding=4>
		<tr bgcolor="#585980">
		<td align=center><b>{$l_ranks_standing}</b></td>
		<td align=center><b><a href="ranking.php?page={$page}">{$l_score}</a></b></td>
<td align=center><b>{$l_ranks_rank}</b></td>
		<td colspan=2 align=center><b><a href="ranking.php?sort=name&page={$page}">{$l_player}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=login&page={$page}">{$l_ranks_online}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=team&page={$page}">{$l_team}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=kills&page={$page}">{$l_ranks_kills}</a>/<a href="ranking.php?sort=deaths&page={$page}">{$l_ranks_deaths}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=kill_efficiency&page={$page}">{$l_ranks_killefficiency}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=captures&page={$page}">{$l_ranks_captures}</a></b></td>		
		<td align=center><b><a href="ranking.php?sort=lost&page={$page}">{$l_ranks_lost}</a></b></td>		
		<td align=center><b><a href="ranking.php?sort=built&page={$page}">{$l_ranks_built}</a></b></td>		
		<td align=center><b><a href="ranking.php?sort=based&page={$page}">{$l_ranks_based}</a></b></td>		
		<td align=center><b><a href="ranking.php?sort=destroyed&page={$page}">{$l_ranks_destroyed}</a></b></td>		
		<td align=center><b><a href="ranking.php?sort=good&page={$page}">{$l_ranks_good}</a>/<a href="ranking.php?sort=bad&page={$page}">{$l_ranks_evil}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=experience&page={$page}">{$l_ranks_experience}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=efficiency&page={$page}">{$l_ranks_rating}</a></b></td>
<td align=center><b><a href="ranking.php?sort=turns&page={$page}">{$l_turns_used}</a></b></td>
		<td align=center><b><a href="ranking.php?sort=login&page={$page}">{$l_ranks_lastlog}</a></b></td>
		</tr>

{php}
      $color="#3A3B6E";
		for($i = 0; $i < $rankcount; $i++){
			if($userid == $rankplayerid[$i]){
			  $oldcolor=$newbgcolor;
				$newbgcolor = "#454560";

				}
			else $newbgcolor = $color;

			echo "  <tr bgcolor=\"$newbgcolor\">\n";
			echo "	<td align=center>" . $ranknumber[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankscore[$i] . "</td>\n";
			echo "	<td nowrap align=center><img border=\"0\" src=\"templates/$templatename/images/rank/" . $rankimage[$i] . "\" align=\"absmiddle\" alt=\"" . $rankimage_name[$i] . "\"></td>";
			echo "  <td align=center valign=middle width=32 height=32><img src='images/$publicavatar[$i]' width=32 height=32 border=1></td>";
			echo "	<td>";
             if (stristr($rankname[$i],'Guide')){
            $guideout="<br><span style='color:yellow;'>Guide</span>";
            $rankname[$i]=str_replace("Guide","",$rankname[$i]);
            }else{
            $guideout="";
            }
			if($rankprofileid[$i] != 0){
				echo "<a href=\"http://www.aatraders.com?player_id=" . $rankprofileid[$i] . "\" target=\"_blank\"><b>" . $rankname[$i] . "</b></a><b>". $guideout."</b>";
			}else{ 
				echo "<b>" . $rankname[$i] ."".  $guideout.  "</b>";
			}
				echo " <font color=\"red\">" . $rankbounty[$i] . "</font>";
				echo " <font color=\"yellow\">" . $rankbountyb[$i] . "</font>";
			echo "</td>\n";
			echo "	<td align=center>" . $rankonline[$i] . "</td>\n";
			echo "	<td align=center>" . $rankteam[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankkills[$i] . "/" . $rankdeaths[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankkilleff[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankcaptures[$i] . "</td>\n";
			echo "	<td align='center'>" . $ranklost[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankbuilt[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankbased[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankdestroyed[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankrating[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankexperience[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankeff[$i] . "</td>\n";
			echo "	<td align='center'>" . $rankturns[$i] . "</td>\n";
			echo "	<td>" . $ranklastlogin[$i] . "</td>\n";

			echo"</tr>\n";
	   if($userid == $rankplayerid[$i])
			 $newbgcolor=$oldcolor;
				
			if ($color == "#3A3B6E")
			{
				$color = "#23244F";
			}
			else
			{
				$color = "#3A3B6E";
			}
		}
{/php}
	</table>
{/if}
</td></tr>
										<tr><td width="100%" colspan=3><br><br>{$gotomain}<br><br></td></tr>
				</td>
			</tr>
		</table>
	</td>
  </tr>
</table>

{if $teams_count > 0}
<br>
<table width="935" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0">
<TR BGCOLOR="#000000">
<TD colspan=4><font size="2" color=white>
{$l_team_galax}<BR><BR></font></td></tr>
	<tr>
	<TD><B>{$l_name}</B></TD>
	<TD><B>&nbsp;{$l_team_members}</B></TD>
	<TD><B>&nbsp;{$l_team_coord}</B></TD>
	<TD><B>&nbsp;{$l_score}</B></TD>
	</TR>
	{php}
	$color = "#000000";
	for($i = 0; $i < $totalteamcount; $i++) {
		echo "<TR BGCOLOR=\"$color\">";
		echo "<TD><img src=\"images/icons/$teamlisticon[$i]\" width=16 height=16>".$teamlistname[$i]."</TD>";
		echo "<TD>&nbsp;".$teamlistnumber[$i]."</TD>";
		echo "<TD>&nbsp;".$teamlistcname[$i]."</TD>";
		echo "<TD>&nbsp;" . $teamlistscore[$i] . "</TD>";
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
	{/php}
			<tr>
		</table>
	</td>
  </tr>
</table>
{/if}

{if $deadrankcount > 0}
<BR>

<table width="935" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
	<table border=0 cellspacing=0 cellpadding=4>
		<TR><TD align='center' colspan=13><b>{$l_ranks_deadtitle}</b></td></tr>
		<tr bgcolor="#585980">
		<td align=center><b>{$l_ranks_standing}</b></td>
		<td align=center><b>{$l_score}</b></td>
		<td align=center><b>{$l_player}</b></td>
		<td align=center><b>{$l_ranks_death_type}</b></td>
		<td align=center><b>{$l_ranks_kills}/{$l_ranks_deaths}</b></td>
		<td align=center><b>{$l_ranks_captures}</b></td>		
		<td align=center><b>{$l_ranks_lost}</b></td>		
		<td align=center><b>{$l_ranks_built}</b></td>		
		<td align=center><b>{$l_ranks_good}/{$l_ranks_evil}</b></td>
		<td align=center><b>{$l_ranks_experience}</b></td>
		<td align=center><b>{$l_ranks_rating}</b></td>
		<td align=center><b>{$l_turns_used}</b></td>
		<td align=center><b>{$l_ranks_lastlog}</b></td>
		</tr>

{php}
      $color="#3A3B6E";
		for($i = 0; $i < $deadrankcount; $i++){
			$newbgcolor = $color;

			echo "  <tr bgcolor=\"$newbgcolor\">\n";
			echo "	<td align=center>" . $deadranknumber[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankscore[$i] . "</td>\n";
			echo "	<td>";
			if($deadrankprofileid[$i] != 0){
				echo "<a href=\"http://www.aatraders.com?player_id=" . $deadrankprofileid[$i] . "\" target=\"_blank\"><b>" . $deadrankname[$i] . "</b></a>";
			}else{ 
				echo "<b>" . $deadrankname[$i] . "</b>";
			}
			echo "</td>\n";
			echo "  <td align='center'>" . $deaddeath_type[$i] . "</td>";
			echo "	<td align='center'>" . $deadrankkills[$i] . "/" . $deadrankdeaths[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankcaptures[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadranklost[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankbuilt[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankrating[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankexperience[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankeff[$i] . "</td>\n";
			echo "	<td align='center'>" . $deadrankturns[$i] . "</td>\n";
			echo "	<td>" . $deadranklastlogin[$i] . "</td>\n";

			echo"</tr>\n";
				
			if ($color == "#3A3B6E")
			{
				$color = "#23244F";
			}
			else
			{
				$color = "#3A3B6E";
			}
		}
{/php}
	</table>
	</td>
  </tr>
</table>
{/if}