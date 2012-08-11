<H1>{$title}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
			<TR>
				<TD>
<form action='casino.php' enctype='multipart/form-data' method='post'>
<input type='hidden' name='casinogame' value='casino_forums'>
<input type='hidden' name='command' value='finishedit'>
<input type='hidden' name='post_id' value="{$post_id}">
<input type='hidden' name='topic_id' value="{$topic_id}">
<b>{$l_forums_editmessage}</b><br><textarea cols='80' rows='10' name='topicmessage'>{$posttext}</textarea><br><br>
<input type='submit' name='Post Text'>
</form>
				</td>
			</tr>
<tr><td><br><a href='casino.php?casinogame=casino_forums&command=showtopics'>{$l_forums_showtopic}</a></td></tr>
<tr><td><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
