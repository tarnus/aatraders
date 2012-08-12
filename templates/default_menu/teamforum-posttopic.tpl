<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
<form action='team_forum.php' enctype='multipart/form-data' method='post'>
<input type='hidden' name='command' value='finishtopic'>
<b>{$l_forums_subject}</b><br><input type='text' name='topictitle' size='40' maxlength='60'><br><br>
<b>{$l_forums_message}</b><br><textarea cols='80' rows='10' name='topicmessage'></textarea><br><br>
{if $isadmin == 1}
	<input type='radio' name='sticky' value='1' checked>{$l_forums_normaltopic}<br><input type='radio' name='sticky' value='9'>{$l_forums_stickytopic}<br><br>
{else} 
	<input type='hidden' name='sticky' value='1'>
{/if}
<input type='submit' name='Post Topic'>
</form>

</td></tr>
<tr><td><br><a href='team_forum.php?command=showtopics'>{$l_forums_showtopic}</a></td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
