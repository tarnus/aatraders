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
<table border=0 cellspacing=0 cellpadding=0 width="600">
  <tr>
    <td>Player name: </td>
    <td><input type="text" name="character_name" value="{$character_name}" size="32" maxlength="25"></td>
  </tr>
  <tr>
    <td>Password: </td>
    <td><input type="text" name="password2" value="{$password}" size="32" maxlength="{$maxlen_password}"></td>
  </tr>
  <tr>
    <td>E-mail: </td>
    <td><input type="text" name="email" value="{$email}"></td>
  </tr>
  <tr>
    <td>ID: </td>
    <td>{$user}</td>
  </tr>
  <tr>
    <td>Ship ID: </td>
    <td><input type="hidden" name="currentship_id" value="{$currentship_id}">{$currentship_id}</td>
  </tr>
  <tr>
    <td>Ship: </td>
    <td><input type="text" name="ship_name" value="{$shipname}"></td>
  </tr>
  <tr>
    <td>Ship Class: </td>
    <td><input type="text" name="ship_class" value="{$ship_class}"></td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td>Player Status? </td>
    <td>
	<input type="radio" name="destroyed" value="N"{if $destroyed == "N"} checked{/if}>Alive<br>
	<input type="radio" name="destroyed" value="K"{if $destroyed == "K"} checked{/if}>Killed with Escape Pod<br>
	<input type="radio" name="destroyed" value="Y"{if $destroyed == "Y"} checked{/if}>Killed without Escape Pod (out of game)
  	</td>
  </tr> 
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td>Extended Admin Logging: </td>
    <td>
	<input type="radio" name="admin_extended_logging" value="0"{if $admin_extended_logging == "0"} checked{/if}>Disabled<br>
	<input type="radio" name="admin_extended_logging" value="1"{if $admin_extended_logging == "1"} checked{/if}>Enabled<br>
  	</td>
  </tr> 
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td nowrap>Damaged Levels</td>
    <td nowrap>
      <table border=0 cellspacing=0 cellpadding=5>
        <tr>
          <td>Hull: </td>
          <td><input type=text size=5 name="hull" value="{$hull}"></td>
          <td>Engines: </td>
          <td><input type=text size=5 name="engines" value="{$engines}"></td>
          <td>Power: </td>
          <td><input type=text size=5 name="power" value="{$power}"></td>
          <td>Fighter Bay: </td>
          <td><input type=text size=5 name="fighter" value="{$fighter}"></td>
        </tr>
        <tr>
          <td>Sensors: </td>
          <td><input type=text size=5 name="sensors" value="{$sensors}"></td>
          <td>armor: </td>
          <td><input type=text size=5 name="armor" value="{$armor}"></td>
          <td>Shields: </td>
          <td><input type=text size=5 name="shields" value="{$shields}"></td>
          <td>Beams: </td>
          <td><input type=text size=5 name="beams" value="{$beams}"></td>
        </tr>
        <tr>
          <td>Torpedo Launchers: </td>
          <td><input type=text size=5 name="torp_launchers" value="{$torp_launchers}"></td>
          <td>Cloak: </td>
          <td><input type=text size=5 name="cloak" value="{$cloak}"></td>
          <td>ECM: </td>
          <td><input type=text size=5 name="ecm" value="{$ecm}"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td nowrap>Normal Levels</td>
    <td nowrap>
      <table border=0 cellspacing=0 cellpadding=5>
        <tr>
          <td>Hull: </td>
          <td><input type=text size=5 name="hull_normal" value="{$hull_normal}"></td>
          <td>Engines: </td>
          <td><input type=text size=5 name="engines_normal" value="{$engines_normal}"></td>
          <td>Power: </td>
          <td><input type=text size=5 name="power_normal" value="{$power_normal}"></td>
          <td>Fighter Bay: </td>
          <td><input type=text size=5 name="fighter_normal" value="{$fighter_normal}"></td>
        </tr>
        <tr>
          <td>Sensors: </td>
          <td><input type=text size=5 name="sensors_normal" value="{$sensors_normal}"></td>
          <td>armor: </td>
          <td><input type=text size=5 name="armor_normal" value="{$armor_normal}"></td>
          <td>Shields: </td>
          <td><input type=text size=5 name="shields_normal" value="{$shields_normal}"></td>
          <td>Beams: </td>
          <td><input type=text size=5 name="beams_normal" value="{$beams_normal}"></td>
        </tr>
        <tr>
          <td>Torpedo Launchers: </td>
          <td><input type=text size=5 name="torp_launchers_normal" value="{$torp_launchers_normal}"></td>
          <td>Cloak: </td>
          <td><input type=text size=5 name="cloak_normal" value="{$cloak_normal}"></td>
          <td>ECM: </td>
          <td><input type=text size=5 name="ecm_normal" value="{$ecm_normal}"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td nowrap>Holds</td>
    <td nowrap>
      <table border=0 cellspacing=0 cellpadding=5>
	  <tr>
		<td>
		<font size=2><b>
		{$l_total_cargo}&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>
		{php}echo strip_places($hold_space); {/php} / {php}echo strip_places($holds_max); {/php}
		</b></font>
		</td>
	  </tr>
{php}
	for($i = 0; $i < $cargo_items; $i++)
	{
		echo "	  <tr>
		<td>
		<font size=2><b>
		&nbsp;<img src=\"images/ports/" . $cargo_name[$i] . ".png\">&nbsp;" . ucfirst($cargo_name[$i]) . ":&nbsp;&nbsp;&nbsp;
		</b></font>
		<td>
		<font color=white><b>";
			echo "<input type=\"text\" size=30 name=\"commodity_" . str_replace(" ", "_", $cargo_name[$i]) . "\" value=\"" . $cargo_amount[$i] . "\">";
			echo " x $cargo_holds[$i]</b></font>
		</td>
	  </tr>";
	}
{/php}
        <tr>
          <td><font size=2><b>&nbsp;<img src="images/ports/energy.png">&nbsp;Energy:&nbsp;&nbsp;&nbsp;</b></font></td>
          <td><input type="text" size=30 name="ship_energy" value="{$energy}"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td nowrap>Combat</td>
    <td nowrap>
      <table border=0 cellspacing=0 cellpadding=5>
        <tr>
          <td>Fighters: </td>
          <td nowrap><input size=17 type="text" size=8 name="ship_fighters" value="{$fighters}"></td>
          <td>Torpedoes: </td>
          <td nowrap><input size=17 type="text" size=8 name="torps" value="{$torps}"></td>
          <td>Armor Pts: </td>
          <td nowrap><input size=17 type="text" size=8 name="armor_pts" value="{$armor_pts}"></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td nowrap>Money and more</td>
    <td nowrap>
      <table border=0 cellspacing=0 cellpadding=5>
        <tr>
          <td nowrap>Credits: </td>
          <td nowrap><input size=20 type="text" name="credits" value="{$credits}"></td>
          <td nowrap>Current balance: </td>
          <td nowrap><input size=20 type="text" name="igb_balance" value="{$igb_balance}"></td>
        </tr>
        <tr>
          <td nowrap>Turns: </td>
          <td nowrap><input size=20 type="text" name="turns" value="{$turns}"></td>
          <td nowrap>Loan: </td>
          <td nowrap><input size=20 type="text" name="igb_loan" value="{$igb_loan}"></td>
        </tr>
        <tr>
          <td nowrap>Turns Used: </td>
          <td nowrap><input size=20 type="text" name="turns_used" value="{$turns_used}"></td>
          <td nowrap>Loan Timestamp: </td>
          <td nowrap><input size=20 type="text" name="igb_loantime" value="{$igb_loantime}"></td>
        </tr>
        <tr>
          <td nowrap>Current Sector: </td>
          <td nowrap><input type="text" name="sector" value="{$sector_id}"></td>
          <td nowrap>&nbsp;</td>
          <td nowrap>&nbsp;</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td nowrap>Special Information</td>
    <td nowrap>
      <table border=0 cellspacing=0 cellpadding=5>
        <tr>
          <td >Federation Bounty Count: </td>
          <td nowrap><input size="8" type="text" name="fed_bounty_count" value="{$fed_bounty_count}"></td>
          <td >The last team the player left: </td>
          <td nowrap><input type="text" name="last_team" value="{$last_team}"></td>
        </tr>
        <tr>
          <td >Alliance Bounty Count: </td>
          <td nowrap><input size="8"  type="text" name="alliance_bounty_count" value="{$alliance_bounty_count}"></td>
          <td >Date player left team: </td>
          <td nowrap><input type="text" name="left_team_time" value="{$left_team_time}"></td>
        </tr>
        <tr>
          <td nowrap>Template: </td>
          <td nowrap><input type="text" name="template" value="{$template}"></td>
          <td nowrap>Avatar: </td>
          <td nowrap align="center"><img src="images/avatars/{$avatar}"><br><input type="text" name="avatar" value="{$avatar}"></td>
        </tr>

      </table>
    </td>
  </tr>
  <tr>
    <td colspan="2"><hr></td>
  </tr>
  <tr>
    <td colspan="2"><br></td>
  </tr>
  <tr>
    <td align="center" colspan = "2">
      <input type="hidden" name="user" value="{$user}">
      <input type="hidden" name="operation" value="Update">
      <input type="submit" value="Update">
    </td>
  </tr>
</table>

