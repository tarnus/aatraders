<h1>{$title}</h1>

<form action=zoneedit.php?command=change method=post>

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
<td align=right><font size=2><b>{$l_ze_name} : &nbsp;</b></font></td>
<td><input type=text name=name size=30 maxlength=30 value="{$name}"></td>
</tr><tr>
<td align=right><font size=2><b>{$l_ze_allow} {$l_beacons} : &nbsp;</b></font></td>
<td><input type=radio name=beacons value=Y {$ybeacon}>&nbsp;{$l_yes}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=beacons value=N {$nbeacon}>&nbsp;{$l_no}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=beacons value=L {$lbeacon}>&nbsp;{$l_zi_limit}</td>
</tr><tr>
<td align=right><font size=2><b>{$l_ze_attacks} : &nbsp;</b></font></td>
<td><input type=radio name=attacks value=Y {$yattack}>&nbsp;{$l_yes}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=attacks value=N {$nattack}>&nbsp;{$l_no}</td>
</tr><tr>
<td align=right><font size=2><b>{$l_ze_allow} {$l_warpedit} : &nbsp;</b></font></td>
<td><input type=radio name=warpedits value=Y {$ywarpedit}>&nbsp;{$l_yes}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=warpedits value=N {$nwarpedit}>&nbsp;{$l_no}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=warpedits value=L {$lwarpedit}>&nbsp;{$l_zi_limit}</td>
</tr><tr>
<td align=right><font size=2><b>{$l_ze_allow} {$l_sector_def} : &nbsp;</b></font></td>
<td><input type=radio name=defenses value=Y {$ydefense}>&nbsp;{$l_yes}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=defenses value=N {$ndefense}>&nbsp;{$l_no}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=defenses value=L {$ldefense}>&nbsp;{$l_zi_limit}</td>
</tr><tr>
<td align=right><font size=2><b>{$l_ze_genesis} : &nbsp;</b></font></td>
<td><input type=radio name=planets value=Y {$yplanet}>&nbsp;{$l_yes}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=planets value=N {$nplanet}>&nbsp;{$l_no}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=planets value=L {$lplanet}>&nbsp;{$l_zi_limit}</td>
</tr><tr>
<td align=right><font size=2><b>{$l_ze_allow} {$l_title_port} : &nbsp;</b></font></td>
<td><input type=radio name=trades value=Y {$ytrade}>&nbsp;{$l_yes}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=trades value=N {$ntrade}>&nbsp;{$l_no}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=radio name=trades value=L {$ltrade}>&nbsp;{$l_zi_limit}</td>
</tr><tr>
<td colspan=2 align=center><br><input type=submit value={$l_submit}></td></tr>

</form>
<tr><td colspan=2 >
<a href=zoneinfo.php>{$l_clickme}</a> {$l_ze_return}.
</td></tr>
<tr><td colspan=2 ><br><br>{$gotomain}<br><br></td></tr>
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
