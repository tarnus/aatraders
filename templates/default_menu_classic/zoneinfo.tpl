<h1>{$title}</h1>
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
<tr><td>
{if $zoneowner != -1}

<table border=0 cellspacing=0 cellpadding=2 width="100%" align=center><tr><td>
	<center>{$l_zi_control}. <a href="zoneedit.php">{$l_clickme}</a> {$l_zi_tochange}</center>
<br><br>
</td></tr>
</table>
{/if}

<tr bgcolor="#000000"><td align=center colspan=2><b><font color=white>{$zone_name}</font></b></td></tr>
<tr><td colspan=2>
<table border=0 cellspacing=0 cellpadding=2 width="100%" align=center>
<tr bgcolor="#000000"><td width="50%"><font color=white size=3>&nbsp;{$l_zi_owner}</font></td><td width="50%"><font color=white size=3>{$ownername}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_beacons}</font></td><td><font color=white size=3>{$beacon}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_att_att}</font></td><td><font color=white size=3>{$attack}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_md_title}</font></td><td><font color=white size=3>{$defense}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_warpedit}</font></td><td><font color=white size=3>{$warpedit}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_planets}</font></td><td><font color=white size=3>{$planet}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_title_port}</font></td><td><font color=white size=3>{$trade}&nbsp;</font></td></tr>
<tr bgcolor="#000000"><td><font color=white size=3>&nbsp;{$l_zi_maxhull}</font></td><td><font color=white size=3>{$hull}&nbsp;</font></td></tr>
			
</table>
				</td>
			</tr>

<tr><td align="center"><br><br>{$gotomain}<br><br></td></tr>
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
