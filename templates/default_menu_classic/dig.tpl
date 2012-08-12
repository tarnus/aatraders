<p align="center"></p><h1>{$title}</h1>

{literal}
	<style type="text/css">
		.border {
			border-collapse: collapse; 
			border: 1px solid #ccc; 
		}
		.yellow { color: yellow; }
		.white { color: white; }
	</style>
<script language="javascript">

function changed_dig(name)
{
	document.forms[0].elements[name].value = 1;
}

</script>
{/literal}

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
		<TR BGCOLOR="#585980"><td><font color=white><b>{$l_dig_legend}</b></font></td><td><font color=white><b>{$l_dig_max}</b></font></td><TD><font color=white><B>{$l_dig_description}</B></font></TD></TR>
		{foreach key=key value=item from=$job_name}
			<TR BGCOLOR="#000000"><td><font color=white>{$job_name[$key]}</font></td><td><font color=white>{$max_digs[$key]}</font></td><TD><font color=white>{$description[$key]}</font></TD></TR>
		{/foreach}
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
<br>
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
	{if $totaldigs}
		{if $totaldigsbyplanet}
<TR BGCOLOR="#000000"><TD colspan=5 align=center><font color=white><B>{$l_dig_defaulttitle2}</B></font></TD></TR>
			<TR BGCOLOR="#585980">
			<TD><B><A HREF=dig.php?by2=id>{$l_dig_codenumber}</A></B></TD>
			<TD><B><A HREF=dig.php?by2=planet>{$l_dig_planetname}</A></B></TD>
			<TD><B><A HREF=dig.php?by2=sector>{$l_dig_sector}</A></B></TD>
			<TD><B><A HREF=dig.php?by2=job_id>{$l_dig_job}</A></B></TD>
			<TD width="50%"><font color=white><B>{$l_dig_changeerror}</B></font></TD>
			</TR>
			<FORM ACTION="dig.php" METHOD="POST">
			<INPUT TYPE="hidden" name="command" value="update">
			{php}
			$line_color = "#23244F";
			for($i = 0; $i < $digcount; $i++)
			{
				if($line_color == "#3A3B6E")   
					$line_color = "#23244F"; 
				else
					$line_color = "#3A3B6E"; 

				echo "<TR BGCOLOR=\"$line_color\"><TD><font size=\"2\" color=\"white\">$digid[$i]</font></TD><TD><font size=\"2\" color=\"white\">$digname[$i]</font></TD><TD><font size=\"2\"><a href=\"main.php?move_method=real&engage=1&destination=$digsector[$i]\">$digsector[$i]</a></font></TD>\n";
				echo "<TD><font size=\"2\"><select onChange=\"changed_dig('digchanged[" . $i . "]')\" name=\"changedig[$i]\">\n";
				for($type = 0; $type < $classcount; $type++)
				{
					if($digjob[$i] == $job_type[$type])
					{
						echo "<option value=\"$job_type[$type]\" selected>" . $job_name[$job_type[$type]] . "</option>\n";
					}
					else
					{
						echo "<option value=\"$job_type[$type]\">" . $job_name[$job_type[$type]] . "</option>\n";
					}
				}
				echo "</select></font></TD>\n";
				echo "<td>" . $digerrorresult[$i] . "</td>\n";
				echo "<INPUT TYPE=\"hidden\" name=\"planet_id[$i]\" value=\"$digplanetid[$i]\"><INPUT TYPE=\"hidden\" name=\"dig_id[$i]\" value=\"$digid[$i]\"><INPUT TYPE=\"hidden\" name=\"digchanged[$i]\" value=\"0\"></TR>\n";
			}
			{/php}
			<INPUT TYPE="hidden" name="digcount" value="{$digcount}">
			<TR BGCOLOR="#23244F">
			<TD colspan=5 align=center><INPUT TYPE="submit" value="{$l_dig_changebutton}"></td></tr>
			</FORM>
			</TABLE><BR><BR>
		{else}
			<B>{$l_dig_no2}</B><BR><BR>
		{/if}

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td bgcolor="#585980"><font color=white><b>&nbsp;
					{if $digonship}
						{$l_dig_defaulttitle4}:  <span class="yellow">{$digshiptotal}</span>
					{else} 
						{$l_dig_no4}
					{/if}
					</b></font>
				</td>
			</tr>

		&nbsp;<br>
	{else}
		<tr><td>{$l_dig_nodignitaryatall}.</td><tr>
	{/if}

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

