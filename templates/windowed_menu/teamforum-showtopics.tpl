<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
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
				  <table border="0" cellspacing="1" width="100%">
					<tr>
					  <td width="75%" align="left"><font color="white" size="2"><b>{$forumname}{$l_forums_title}</b></font></td>
					  <td width="21%" align="center" nowrap><font color="white" size="2">{$l_forums_topics}{$reccount}&nbsp;&nbsp;&nbsp;{$l_forums_date}{$showdate}&nbsp;</font></td>
					  <td width="4%" align="center"><A HREF="main.php"><img alt="Click here to return to the main menu" src="templates/{$templatename}images/c95x.png" width="16" height="14" border="0"></a></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>
		{if $istopics}
			<tr>
			  <td width="100%" align="center" bgcolor="black" height="4"></td>
			</tr>
			<tr>
			  <td width="100%" bgcolor="black">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%" cellpadding="0">
					<tr>
					  <td width="7%" align="center"><font color="white" size="2"><b>{$l_forums_new}</b></font></td>
					  <td width="50%" align="center" ><font color="white" size="2"><b>{$l_forums_topic2}</b></font></td>
					  <td width="14%" align="center" ><font color="yellow" size="2">{$l_forums_author}</font></td>
					  <td width="15%" align="center"><font color="white" size="2">{$l_forums_date2}</font></td>
					  <td width="7%" align="center"><font color="white" size="2">{$l_forums_posts}</font></td>
					  <td width="7%" align="center"><font color="white" size="2">{$l_forums_views}</font></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>
			{php}
			for($i = 0; $i < $count; $i++){
			echo "<tr>";
			echo "  <td width=\"100%\" bgcolor=\"black\" bordercolorlight=\"black\">";
			echo "	<div align=\"center\">";
			echo "	  <table border=\"0\" cellspacing=\"1\" width=\"100%\" cellpadding=\"0\">";
			echo "		<tr>";
			echo "		  <td width=\"7%\" align=\"center\" bordercolorlight=\"black\" bordercolordark=\"gray\"><font color=\"$client[$i]\" size=\"2\"><b>$newpost[$i]</b></font></td>";
			echo "		  <td width=\"50%\" align=\"center\" ><a href=\"team_forum.php?command=readtopic&topic_id=$topicid[$i]#$postid[$i]\"><font color=\"white\" size=\"2\"><b>$topictypes[$i] $topictitle[$i]</b></font></a></td>";
			echo "		  <td width=\"14%\" align=\"center\" ><font color=\"yellow\" size=\"2\">$accounttypes[$i] $topicposter[$i]</font></td>";
			echo "		  <td width=\"15%\" align=\"center\"><font color=\"white\" size=\"2\">$topicdates[$i]</font></td>";
			echo "		  <td width=\"7%\" align=\"center\"><font color=\"white\" size=\"2\">$number[$i]</font></td>";
			echo "		  <td width=\"7%\" align=\"center\" bordercolorlight=\"black\" bordercolordark=\"gray\"><font color=\"white\" size=\"2\">$topicviews[$i]</font></td>";
			echo "		</tr>";
			echo "	  </table>";
			echo "	</div>";
			echo "  </td>";
			echo "</tr>";
			}
			{/php}
		{else}
			<tr>
			  <td width="100%" bgcolor="black" bordercolorlight="black">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%" bgcolor="white" bordercolorlight="black">
					<tr>
					  <td width="100%" align="center" bgcolor="white"><font color="red">{$l_readm_nomessage}</font></td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>
		{/if}
			<tr>
			  <td width="100%" align="center" bgcolor="black" bordercolorlight="black">
				<div align="center">
				  <table border="0" cellspacing="1" width="100%" bordercolorlight="black" cellpadding="0">
					<tr>
					  <td width="100%" align="center" valign="middle"><A class="but" HREF="team_forum.php?command=posttopic">{$l_forums_posttopic}</A>
					  </td>
					</tr>
				  </table>
				</div>
			  </td>
			</tr>

		  </table>
		  </center>
		</div>
</td></tr>
<tr><td><br><a href='team_forum.php?command=showtopics'>{$l_forums_showtopic}</a></td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
