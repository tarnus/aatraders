<H1>{$title}</H1>

<table width="80%" border="0" cellspacing="0" cellpadding="0" align="center">
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
<tr>
	  <td width="100%">
		<div align="center">
		  <center>
		  <table border="0" cellspacing="1" width="100%">
			<tr>
			  <td width="100%" bgcolor="black">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%" bordercolorlight="black">
					<tr>
					  <td width="75%" align="left"><font color="white" size="2"><b>{$topictype}{$l_forums_subject}{$topic_title}</b></font></td>
					  <td width="21%" align="center" nowrap><font color="white" size="2">{$l_forums_reply}{$totalposts}&nbsp;&nbsp;&nbsp;{$l_forums_date}{$topicstartdate}&nbsp;</font></td>
					  <td width="4%" align="center" bordercolorlight="black"><A HREF="main.php"><img alt="Click here to return to the main menu" src="templates/{$templatename}images/c95x.png" width="16" height="14" border="0"></a></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>

		{if $totalposts2 > 0}
		{php}
			for($i = 0; $i < $count; $i++){
			echo "<a name=\"$postid[$i]\"></a>";
			echo "<tr>";
			echo "  <td width=\"100%\" align=\"center\" bgcolor=\"black\" height=\"4\"></td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"150\" aligh=\"left\"><font color=\"white\" size=\"2\"><b>$l_readm_sender:</b></td>";
			echo "		  <td width=\"64\" align=\"left\"><img src=\"images/avatars/$avatarimg[$i]\"></td>";
			echo "		  <td align=\"left\">&nbsp;<font color=\"yellow\" size=\"2\">$accounttypes[$i] $postusername[$i]</font></td>";
			echo "		  <td width=\"20%\" align=\"center\"><font color=\"white\" size=\"2\">$postdate[$i]</font></td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bordercolorlight=\"black\">";
			echo "		<tr>";
			echo "		  <td width=\"100%\" class=\"footer\"><font color=\"white\">$posttext[$i]</font></td>";
			echo "		</tr>";
			if($posteditcount[$i] != 0){
			echo "		<tr>";
			echo "		  <td width=\"100%\" class=\"footer\"><font color=\"red\">$l_forums_edited $posteditcount[$i] $shows[$i] - $l_forums_lastedit $posteditdate[$i]</font></td>";
			echo "		</tr>";
			}
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			echo "<tr>";
			echo "  <td width=\"100%\" align=\"center\" bgcolor=\"black\" bordercolorlight=\"black\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bordercolorlight=\"black\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"100%\" align=\"center\" valign=\"middle\">";
			if($forumadmin == 1){
			echo "		  	 | <A class=\"but\" HREF=\"team_forum.php?command=delete&post_id=$postid[$i]&topic_id=$topic_id\">$l_readm_del</A>";
			}
			if(($forumadmin == 1 or $isposter[$i]) and $topic_status != 0){
			echo "		  	 | <A class=\"but\" HREF=\"team_forum.php?command=edit&post_id=$postid[$i]&topic_id=$topic_id\">$l_forums_edit</A>";
			}
			if($topic_status != 0){
			echo "			 | <A class=\"but\" HREF=\"team_forum.php?command=postreply&topic_id=$topic_id\">$l_readm_repl</A>";
			}
			echo " |";
			echo "		  </td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			}
			echo "<tr>";
			echo "  <td width=\"100%\" align=\"center\" bgcolor=\"black\" height=\"4\"></td>";
			echo "</tr>";
			if ($forumadmin == 1 and $topic_status != 9){
			echo "<tr>";
			echo "  <td width=\"100%\" align=\"center\" bgcolor=\"black\" bordercolorlight=\"black\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" bordercolorlight=\"black\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"100%\" align=\"center\" valign=\"middle\">";
			echo "		  	 | <A class=\"but\" HREF=\"team_forum.php?command=lock&topic_id=$topic_id\">$l_forums_lock</A> |";
			echo "		  </td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			}
			{/php}
		{/if}
		  </table>
</td></tr>
<tr><td><br><a href='team_forum.php?command=showtopics'>{$l_forums_showtopic}</a></td></tr>
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
