<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
<TR BGCOLOR='#585980'>
<TH COLSPAN=2 NOWRAP><FONT COLOR=yellow>{$l_shout_teamtitle}</FONT></TH>
</TR>
  <tr>
    <td bgcolor="#000000" valign="top" align="center">
{if $totalpages > 1}
	<TABLE border=0 cellpadding=2 cellspacing=1 width="100%">
	<form action="shoutbox_team.php" method="post">
	<TR>
		<td align="left" width="33%">
			{if $currentpage != 1}
				<a href="shoutbox_team.php?page={$previouspage}">{$l_shout_prev}</a>
			{else}
				&nbsp;
			{/if}
		</td>
		<TD align='center' width="33%">
	{ math equation="x + y" x=1 y=$totalpages assign="forpages" }
	{$l_shout_selectpage} <select name="page">
	{ for start=1 stop=$forpages step=1 value=i }
		<option value="{$i}"
		{if $currentpage == $i}
			selected
		{/if}
		> {$l_shout_page} {$i} </option>
	{/for}
	</select>
	&nbsp;<input type="submit" value="{$l_submit}">
	</TD>
		<td align="right" width="33%">
			{if $currentpage != $totalpages}
				<a href="shoutbox_team.php?page={$nextpage}">{$l_shout_next}</a>
			{else}
				&nbsp;
			{/if}
		</td>
	</tr>
	</form>
	</table>
{/if}

<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<TR><TD COLSPAN=2 NOWRAP ALIGN=CENTER>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2 width=100%>
	{php}
	for ( $i = 0 ; $i < count($playernamea) ; $i++ )
	{
		echo "<tr> 
				<td rowspan=2 align=center valign=middle width=64 height=64><img src='images/$publicavatar[$i]'></td>
				<td ALIGN=LEFT width='50%'><FONT SIZE=-1><B>$playernamea[$i]</B></FONT></td>
				<td ALIGN=RIGHT width='50%'><FONT SIZE=-1><I>$datea[$i]</I></FONT></td>
			  </tr>
			  <tr> 
				<td colspan=2 ALIGN=LEFT width='100%'>$messagea[$i]</td>
			  </tr>";
		echo "<TR>";
		echo "<TD COLSPAN=3 ><IMG height=1 width=1 SRC='images/spacer.gif'><hr></TD>";
		echo "</TR>";
	}
	{/php}

</TABLE>
</TD></TR>

<TR BGCOLOR='#23244F'><TD COLSPAN=2 NOWRAP ALIGN=CENTER>
<FORM NAME='sb' ACTION='shoutbox_save.php'>
<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=2 width=100%>
<TR BGCOLOR='#3A3B6E'>
<TD NOWRAP ALIGN=LEFT>
<INPUT TYPE=TEXT NAME='sbt' Value='' MAXLENGTH=200></TD>
<TD NOWRAP ALIGN=RIGHT></TD>
</TR>
<TR BGCOLOR='#3A3B6E'>
<TD NOWRAP ALIGN=LEFT><INPUT TYPE=SUBMIT VALUE='SHOUT'>&nbsp;&nbsp;<A HREF='shoutbox_smilie.php?template={$template}'>{$l_shout_smiles}</A></TD>
<TD NOWRAP ALIGN=RIGHT><INPUT TYPE=RESET VALUE='CLEAR'></TD>
</TR>
</TABLE>
</FORM>
</TD></TR>
<tr><td align="center"><a href="shoutbox_team.php">{$l_shout_refresh}</a>&nbsp;&nbsp;&nbsp;<a href="javascript:window.close();">{$l_shout_close}</a>
</td></tr>
		</table>
	</td>
  </tr>
</table>
