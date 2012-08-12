{literal}
<script language="javascript">
var xmlSourceDoc = null ;
var xmlDestDoc = null ;
var sectorname;

function makeSourceRequest()
{
	var form = document.forms[0];
	sectorname = form.port_id1.value;
	if(sectorname == '')
	{
		return;
	}
	if ( xmlSourceDoc == null )
	{
		if (typeof window.ActiveXObject != 'undefined' ) {
			xmlSourceDoc = new ActiveXObject("Microsoft.XMLHTTP");
			xmlSourceDoc.onreadystatechange = processsource ;
	}
		else
		{
			xmlSourceDoc = new XMLHttpRequest();
			xmlSourceDoc.onload = processsource ;
		}
	}
	xmlSourceDoc.open( "GET", "{/literal}{$full_url}{literal}ajax_processor.php?command=traderoute_portinfo&sectorname=" + sectorname, true );
	xmlSourceDoc.send( null );
}

function processsource() {
	if ( xmlSourceDoc.readyState != 4 ) return ;
	document.getElementById("source").innerHTML = xmlSourceDoc.responseText ;
}

function makeDestRequest()
{
	var form = document.forms[0];
	sectorname = form.port_id2.value;
	if(sectorname == '')
	{
		return;
	}
	if ( xmlDestDoc == null )
	{
		if (typeof window.ActiveXObject != 'undefined' ) {
			xmlDestDoc = new ActiveXObject("Microsoft.XMLHTTP");
			xmlDestDoc.onreadystatechange = processdestination ;
	}
		else
		{
			xmlDestDoc = new XMLHttpRequest();
			xmlDestDoc.onload = processdestination ;
		}
	}
	xmlDestDoc.open( "GET", "{/literal}{$full_url}{literal}ajax_processor.php?command=traderoute_portinfo&sectorname=" + sectorname, true );
	xmlDestDoc.send( null );
}

var planetspecialteam=new Array()
planetspecialteam['none'] = '';
{/literal}{$planetspecialteam}{literal}

var planetspecial=new Array()
planetspecial['none'] = '';
{/literal}{$planetspecial}{literal}

function PopulateSourcePlanet(item) {

   var planet_id1_item = document.frmMain.planet_id1;
   
   // Clear out the list of teams
   ClearOptions(document.frmMain.source_planet_commodity);
   
	AddToOptionList(document.frmMain.source_planet_commodity, "{/literal}{$commodity_commodity_type[0]}{literal}", "{/literal}{$commodity_commodity_type[0]}{literal}",item);
	AddToOptionList(document.frmMain.source_planet_commodity, "{/literal}{$commodity_commodity_type[1]}{literal}", "{/literal}{$commodity_commodity_type[1]}{literal}",item);
	AddToOptionList(document.frmMain.source_planet_commodity, "{/literal}{$commodity_commodity_type[2]}{literal}", "{/literal}{$commodity_commodity_type[2]}{literal}",item);
	AddToOptionList(document.frmMain.source_planet_commodity, "{/literal}{$commodity_commodity_type[3]}{literal}", "{/literal}{$commodity_commodity_type[3]}{literal}",item);
	AddToOptionList(document.frmMain.source_planet_commodity, "{/literal}{$commodity_commodity_type[4]}{literal}", "{/literal}{$commodity_commodity_type[4]}{literal}",item);
	AddToOptionList(document.frmMain.source_planet_commodity, "{/literal}{$commodity_commodity_type[5]}{literal}", "{/literal}{$commodity_commodity_type[5]}{literal}",item);

   if (planetspecial[planet_id1_item[planet_id1_item.selectedIndex].value] != '') {
      AddToOptionList(document.frmMain.source_planet_commodity, planetspecial[planet_id1_item[planet_id1_item.selectedIndex].value], planetspecial[planet_id1_item[planet_id1_item.selectedIndex].value],item);
   }
}

function PopulateDestPlanet(item) {

   var planet_id2_item = document.frmMain.planet_id2;
   
   // Clear out the list of teams
   ClearOptions(document.frmMain.destination_planet_commodity);
   
	AddToOptionList(document.frmMain.destination_planet_commodity, "{/literal}{$commodity_commodity_type[0]}{literal}", "{/literal}{$commodity_commodity_type[0]}{literal}",item);
	AddToOptionList(document.frmMain.destination_planet_commodity, "{/literal}{$commodity_commodity_type[1]}{literal}", "{/literal}{$commodity_commodity_type[1]}{literal}",item);
	AddToOptionList(document.frmMain.destination_planet_commodity, "{/literal}{$commodity_commodity_type[2]}{literal}", "{/literal}{$commodity_commodity_type[2]}{literal}",item);
	AddToOptionList(document.frmMain.destination_planet_commodity, "{/literal}{$commodity_commodity_type[3]}{literal}", "{/literal}{$commodity_commodity_type[3]}{literal}",item);
	AddToOptionList(document.frmMain.destination_planet_commodity, "{/literal}{$commodity_commodity_type[4]}{literal}", "{/literal}{$commodity_commodity_type[4]}{literal}",item);
	AddToOptionList(document.frmMain.destination_planet_commodity, "{/literal}{$commodity_commodity_type[5]}{literal}", "{/literal}{$commodity_commodity_type[5]}{literal}",item);

   if (planetspecial[planet_id2_item[planet_id2_item.selectedIndex].value] != '') {
      AddToOptionList(document.frmMain.destination_planet_commodity, planetspecial[planet_id2_item[planet_id2_item.selectedIndex].value], planetspecial[planet_id2_item[planet_id2_item.selectedIndex].value],item);
   }
}


function ClearOptions(OptionList) {

   // Always clear an option list from the last entry to the first
   for (x = OptionList.length; x >= 0; x = x - 1) {
      OptionList[x] = null;
   }
}

function AddToOptionList(OptionList, OptionValue, OptionText, item) {
   // Add option to the bottom of the list
   if(OptionText == item)
   {
		isSelected = 'selected';
	}
	else
	{
		isSelected = '';
	}
   OptionList[OptionList.length] = new Option(OptionText, OptionValue, isSelected);
}

</script>
{/literal}

<h1>{$title}</h1>

<form name="frmMain" action="traderoute_save.php" method=post>
<table width="600" border="1" align="center" cellpadding="4" cellspacing="0">
  <tr>
    <td>
	<table width="100%"  border="0">
      <tr>
        <td colspan="4"><p>{$l_tdr_editinga} {$l_tdr_traderoute} {$l_tdr_cursector} {$shipsector}<br>
          <br>
        </p>
          </td>
        </tr>
      <tr>
        <td colspan="4"><b>{$l_tdr_selspoint}</b><br></td>
        </tr>
      <tr>
        <td>{$l_tdr_port} : </td>
        <td><input type=radio name="ptype1" value="port" 
{if $source_type == 'port'}
	 checked
{/if}
></td>
        <td>
          <input onBlur="makeSourceRequest();" type="text" name="port_id1" size="20" align="center" 
{if $source_type == 'port'}
	value="{$editsource_id}"
{else}
	value="{$shipsector}"
{/if}
></td>
        <td id="source">&nbsp;</td>
      </tr>
      <tr><td colspan="4"><hr></td></tr>
      <tr>
        <td>Personal {$l_tdr_planet} : </td>
        <td><input type=radio name="ptype1" value="planet"
{if $source_type == 'planet'}
	 checked
{/if}
 onclick="PopulateSourcePlanet();"></td>
        <td>
          <select name="planet_id1" onChange="PopulateSourcePlanet();">

{if $num_planets == 0}
	<option value=none>{$l_tdr_none}</option>
{else}
	{php}
	for ($i=0; $i < $num_planets; $i++)
	{
		echo "<option ";
		echo $planetselected[$i];
		echo " value=" . $planetid[$i] . ">" . $planetname[$i] . " $l_tdr_insector " . $planetsectorid[$i] . "</option>";
	}
	{/php}
{/if}
</select></td>
        <td rowspan="2">
          <select name=source_planet_commodity>
<option value=""></option>
</select></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <tr>
        <td colspan="4"><b>{$l_tdr_selendpoint} : </b><br></td>
        </tr>
      <tr>
        <td>{$l_tdr_port} : </td>
        <td><input type=radio name="ptype2" value="port" 
{if $dest_type == 'port'}
	 checked
{/if}
></td>
        <td>
          <input onBlur="makeDestRequest();" type=text name=port_id2 size=20 align=center
{if $dest_type == 'port'}
	value="{$editdest_id}"
{/if}
></td>
        <td id="dest">&nbsp;</td>
      </tr>
      <tr><td colspan="4"><hr></td></tr>
      <tr>
        <td>Personal {$l_tdr_planet} : </td>
        <td><input type=radio name="ptype2" value="planet"
{if $dest_type == 'planet'}
	 checked
{/if}
 onclick="PopulateDestPlanet();"></td>
        <td><select name="planet_id2" onChange="PopulateDestPlanet();">

{if $num_planets == 0}
	<option value=none>{$l_tdr_none}</option>
{else}
	{php}
	for ($i=0; $i < $num_planets; $i++)
	{
		echo "<option ";
		echo $planetdestselected[$i];
		echo " value=" . $planetid[$i] . ">" . $planetname[$i] . " $l_tdr_insector " . $planetsectorid[$i] . "</option>";
	}
	{/php}
{/if}
</select></td>
        <td rowspan="2"><select name=destination_planet_commodity>
<option value=""></option>
</select></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
	  </table>
	  <table width="100%"  border="0">
      <tr>
        <td width="50%"><b>{$l_tdr_selmovetype} : </b></td>
        <td width="50%"><input type=radio name="move_type" value="realspace" 
{if $move_type == 'R'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_realspace}&nbsp;&nbsp;
          <input type=radio name="move_type" value="warp" 
{if $move_type == 'W'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_warp}</td>
        </tr>
      <tr>
        <td width="50%"><b>{$l_tdr_selcircuit} : </b></td>
        <td width="50%"><input type=radio name="circuit_type" value="N"
{if $circuit == 'N'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_oneway}&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <input type=radio name="circuit_type" value="Y" 
{if $circuit == 'Y'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_bothways}</td>
        </tr>
      <tr>
        <td width="50%"><strong>{$l_tdr_tdrescooped}</strong></td>
        <td width="50%"><input type=radio name=trade_energy value="Y"
{if $trade_energy == 'Y'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_trade}&nbsp;&nbsp;
          <input type=radio name=trade_energy value="N"
{if $trade_energy == 'N'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_keep}</td>
        </tr>
      <tr>
        <td width="50%"><b>{$l_tdr_trade} {$l_upgrade_ports} {$l_port} {$l_tdr_fighters} : </b></td>
        <td width="50%"><input type=radio name="trade_fighters" value="Y"
{if $trade_fighters == 'Y'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_trade}&nbsp;&nbsp;
          <input type=radio name="trade_fighters" value="N"
{if $trade_fighters == 'N'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_keep}</td>
        </tr>
      <tr>
        <td width="50%"><b>{$l_tdr_trade} {$l_upgrade_ports} {$l_port} {$l_tdr_torps} : </b></td>
        <td width="50%"><input type=radio name="trade_torps" value="Y"
{if $trade_torps == 'Y'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_trade}&nbsp;&nbsp;
          <input type=radio name="trade_torps" value="N"
{if $trade_torps == 'N'}
	 checked
{/if}
>
          &nbsp;{$l_tdr_keep}</td>
        </tr>
    </table>
	  <table width="100%"  border="0">
        <tr>
          <td><div align="center">
              <input type=hidden name=editing value={$editing}>
<input type=submit value="{$l_tdr_modify}" >
              <br>
              <br>
            {$l_tdr_returnmenu}<br>
          </div></td>
        </tr>
        <tr>
          <td><div align="center">{$gotomain}</div></td>
        </tr>
      </table></td>
  </tr>
</table>
</form>

{literal}
<script language="javascript">
function processdestination() {
	if ( xmlDestDoc.readyState != 4 ) return ;
	document.getElementById("dest").innerHTML = xmlDestDoc.responseText ;
}

function FillContent()
{
	makeSourceRequest();
	makeDestRequest();
	{/literal}
	{if $source_type == 'planet'}
	{literal}
		PopulateSourcePlanet('{/literal}{$source_commodityselected}{literal}');
	{/literal}
	{/if}
	{literal}

	{/literal}
	{if $source_type == 'team_planet'}
	{literal}
		PopulateSourceTeamPlanet('{/literal}{$source_commodityselected}{literal}');
	{/literal}
	{/if}
	{literal}

	{/literal}
	{if $dest_type == 'planet'}
	{literal}
		PopulateDestPlanet('{/literal}{$destination_commodityselected}{literal}');
	{/literal}
	{/if}
	{literal}

	{/literal}
	{if $dest_type == 'team_planet'}
	{literal}
		PopulateDestTeamPlanet('{/literal}{$destination_commodityselected}{literal}');
	{/literal}
	{/if}
	{literal}

}

window.onload = FillContent;
</script>
{/literal}
