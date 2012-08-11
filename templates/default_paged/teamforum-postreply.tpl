<H1>{$title}</H1>

<table border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
<form action='team_forum.php' enctype='multipart/form-data' method='post'>
<input type='hidden' name='command' value='finishreply'>
<input type='hidden' name='topic_id' value="{$topic_id}">
<b>{$l_forums_message}</b><br><textarea cols='80' rows='10' name='topicmessage'></textarea><br><br>
<input type='submit' name='Post Topic'>
</form>
</td></tr>

<tr><td><br><a href='team_forum.php?command=showtopics'>{$l_forums_showtopic}</a></td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
