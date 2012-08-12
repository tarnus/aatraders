<H1>{$l_sn_tntitle}</H1>

<table width="80%" border="1" cellspacing="0" cellpadding="4" align="center">
  <tr>
    <td bgcolor="#000000" valign="top" align="center" colspan=2>
		<table cellspacing = "0" cellpadding = "0" border = "0" width="100%">
<tr><td>
<B><A HREF=planet_report.php?PRepType=0>{$l_pr_menulink}</A></B><BR>
{if $count < 1}
	<BR>{$l_sn_nonotes}
{else}
	<BR>
	
	{php}
function strip_places($itemin){

$places = explode(",", $itemin);
if (count($places) <= 1){
	return $itemin;
}
else
{
	$places[1] = AAT_substr($places[1], 0, 2);
	$placecount=count($places);

	switch ($placecount){
		case 2:
			return "$places[0].$places[1] K";
			break;
		case 3:
			return "$places[0].$places[1] M";
			break;	
		case 4:
			return "$places[0].$places[1] B";
			break;	
		case 5:
			return "$places[0].$places[1] T";
			break;
		case 6:
			return "$places[0].$places[1] Qd";
			break;		
		case 7:
			return "$places[0].$places[1] Qn";
			break;
		case 8:
			return "$places[0].$places[1] Sx";
			break;
		case 9:
			return "$places[0].$places[1] Sp";
			break;
		case 10:
			return "$places[0].$places[1] Oc";
			break;
		}		
	
}

}
{/php}
	<FORM ACTION=sector_notes.php METHOD=POST>
	{php}
	if ($command==$l_sn_editnote){
	echo "<b>".$l_sn_editnote."</b><p>";
	echo "<input type=\"Hidden\" name=\"command\" value=\"$l_sn_editnote\">";
	}else{
	echo "<b>".$l_sn_addnote."</b><p>";
	echo "<input type=\"Hidden\" name=\"command\" value=\"$l_sn_addnote\">";
	}
	{/php}
		<input type="Hidden" name="limit" value="{$limit}">
	<input type="Hidden" name="sectornum" value="{$sector}">
	<input type="Hidden" name="note_id" value="{$notelistid}">
	
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=2>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left width="20%"><font size=2><B>&nbsp;{$l_sn_hdsector}&nbsp;</B></font></TD><td width="5">&nbsp;</td>
<TD ALIGN=left width="90%"><font size=2>{$sector}&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdscanfrom}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><input type="Text" name="scanfrom" width="10" value="{$sector_scanfrom}">&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdtype}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><select name=stype>
	<option value="">N/A</option>
	{if $sector_type=="Ally"}
	<option value="Ally" selected>Ally</option>
	{else}
	<option value="Ally" >Ally</option>
	{/if}
	{if $sector_type=="Base"}
	<option value="Base" selected>Base</option>
	{else}
	<option value="Base">Base</option>
	{/if}
	{if $sector_type=="Enemy"}
	<option value="Enemy" selected>Enemy</option>
	{else}
	<option value="Enemy">Enemy</option>
	{/if}
	{if $sector_type=="Indy"}
	<option value="Indy" selected>Indy</option>
	{else}
	<option value="Indy">Indy</option>
	{/if}
	{if $sector_type=="Port"}
	<option value="Port" selected>Port</option>
	{else}
	<option value="Port">Port</option>
	{/if}
	{if $sector_type=="Team Base"}
	<option value="Team Base" selected>Team Base</option>
	{else}
	<option value="Team Base">Team Base</option>
	{/if}
	{if $sector_type=="Minefield"}
	<option value="Minefield" selected>Minefield</option>
	{else}
	<option value="Minefield">Minefield</option>
	{/if}
	{if $sector_type=="SG Entry"}
	<option value="SG Entry" selected>SG Entry</option>
	{else}
	<option value="SG Entry">SG Entry</option>
	{/if}
	{if $sector_type=="Spy Sector"}
	<option value="Spy Sector" selected>Spy Sector</option>
	{else}
	<option value="Spy Sector">Spy Sector</option>
	{/if}	

	
</select>


&nbsp;</font></TD></tr>

	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdowner}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><input type="Text" name="owner" width="10" value="{$sector_owner}">&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdplanets}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><input type="Text" name="planets" width="10" value="{$sector_planets}">&nbsp;</font></TD></tr>

	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdport}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><input type="Text" name="port" width="10" value="{$sector_port}">&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdfighters}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><input type="Text" name="fighters" width="10" value="{$sector_fighters}">&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdmines}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><input type="Text" name="mines" width="10" value="{$sector_mines}">&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hdteam}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2>
{php}
if ($notes_team >0){

	if ($noteplayerid==$playerid){
		if ($playerteam==0){
			echo "<input type=\"checkbox\" name=\"team\" disabled>";
		}else{
			echo "<input type=\"checkbox\" name=\"team\" >";
		}
	}else{
		
	echo "<input type=\"checkbox\" name=\"team\" checked disabled>";
	}
}else{
if ($playerteam==0){
			echo "<input type=\"checkbox\" name=\"team\" disabled>";
		}else{
			echo "<input type=\"checkbox\" name=\"team\" >";
		}
}
{/php}
&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;{$l_sn_hddetail}&nbsp;</B></font></TD><td>&nbsp;</td>
<TD ALIGN=left><font size=2><textarea name="note" cols="30" rows="5">{$notelistnote}</textarea>&nbsp;</font></TD></tr>
	<TR BGCOLOR="{$color_header}" VALIGN=top>
	<TD ALIGN=left><font size=2><B>&nbsp;&nbsp;</B></font></TD><td>&nbsp;</td>
	{if $command==$l_sn_editnote}
<TD ALIGN=left><font size=2><INPUT TYPE=SUBMIT VALUE="{$l_sn_editnote}">&nbsp;</font></TD>
	{else}
<TD ALIGN=left><font size=2><INPUT TYPE=SUBMIT VALUE="{$l_sn_addnote}">&nbsp;</font></TD>	
	{/if}
</tr>

	</TABLE>
{/if}

</td></tr>
<tr><td><br><br><a href="sector_notes.php">{$l_sn_list}</a><br><br></td></tr>
<tr><td><br><br>{$gotomain}<br><br></td></tr>
		</table>
	</td>
  </tr>
</table>
