{literal}
	<style type="text/css">

body {
	color: #2d2e2e;
	font-family: Arial, Helvetica, sans-serif;
	font-size: 11px;
	line-height: 14px;
	margin: 0 0 0 0; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	padding: 0 0 0 0; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Centers the page content container in IE 5 browsers. */
	background-image: url(templates/{/literal}{$templatename}{literal}images/galactic_arm4.jpg);
}
	h3 {
	margin:0;
	text-align: center;
	color: #000;
    }
	.header {
    	padding:5px 10px;
		background:#ddd;
	}
.rightColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.rightBuyColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}

.rightColumnMini {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.rightBuyColumnMini {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftBuyColumnMini {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.portfooter {
	background-color: #eef6ed;
	border-top: solid 1px #8ab573; /* Sets the top border properties for an element using shorthand notation */
	padding: 10px 10px 10px 10px; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	color: #000;
}
	.inputcss {
		font-family: Verdana, Geneva, sans-serif;
		font-size: 10px;
	}

 	a:link {
		color: #542764;
	}

   </style>

{/literal}

<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="header"><h3>{$target_title}</br>
    	{if $attacktype == "planet"}
			{insert name="img" src="templates/`$templatename`images/planet`$titleimage`.png" alt="" width="100" height="100"}
   		{else}
			<img src="templates/{$templatename}images/{$titleimage}.gif" border=0>
		{/if}</h3>
		{if $isfedbounty > 0}
			</br></br>{$l_by_fedbounty2}
		{/if}
	</td>
  </tr>
{if $attacktype == "planet"}
	{if $shipsonplanet > 0}
  <tr><td colspan="3" align="center" class="portfooter"><b><u>{$l_cmb_ships_are_landed}</u><br><br>{$l_cmb_engshiptoshipcombat}</b></td></tr>
  <tr><td colspan="3" align="center" class="portfooter">
   	{foreach key=key value=item from=$shiponplanet_list}
		<p><b>{$shiponplanet_list[$key]}</b></p>
	{/foreach}
  </td></tr>
	{else}
  <tr><td colspan="3" align="center" class="portfooter"><b><u>{$l_cmb_noshipslanded}</u></b></td></tr>
	{/if}
{/if}
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="leftBuyColumnMini" nowrap><b>{$l_cmb_attacker_beams}</b></br>{$start_attacker_beam_energy}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_fighters}</b></br>{$start_attackerfighters}</td>
    <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_shields}</b></br>{$start_attacker_shield_energy}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_torps}</b></br>{$start_attackertorps}</td>
   <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_armor}</b></br>{$start_attackerarmor}</td>
  </tr>
  <tr>
    <td class="leftBuyColumnMini" nowrap><b>{$l_cmb_target_beams}</b></br>{$start_target_beams}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_target_fighters}</b></br>{$start_target_fighters}</td>
    <td class="leftColumnMini" nowrap><b>{$l_cmb_target_shields}</b></br>{$start_target_shields}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_target_torps}</b></br>{$start_target_torps}</td>
   <td class="leftColumnMini" nowrap><b>{$l_cmb_target_armor}</b></br>{$start_target_armor}</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr><td colspan="3" align="center" class="portfooter"><b><u>{$l_cmb_beam_exchange}</u></b></td></tr>
  <tr>
    <td class="leftBuyColumn" >
    	{foreach key=key value=item from=$attacker_beam_result}
			<p><b>{$attacker_beam_result[$key]}</b></p>
		{/foreach}
	</td>
    <td class="rightBuyColumn" >
    	{foreach key=key value=item from=$target_beam_result}
			<p><b>{$target_beam_result[$key]}</b></p>
		{/foreach}
	</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="leftBuyColumnMini" nowrap><b>{$l_cmb_attacker_beams}</b></br>{$stage2_attacker_energy}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_fighters}</b></br>{$stage2_attacker_fighters}</td>
    <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_shields}</b></br>{$stage2_attacker_shields}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_torps}</b></br>{$stage2_attacker_torps}</td>
   <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_armor}</b></br>{$stage2_attacker_armor}</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr><td colspan="3" align="center" class="portfooter"><b><u>{$l_cmb_fighter_exchange}</u></b></td></tr>
  <tr>
    <td class="leftBuyColumn" >
    	{foreach key=key value=item from=$attacker_fighter_result}
			<p><b>{$attacker_fighter_result[$key]}</b></p>
		{/foreach}
	</td>
    <td class="rightBuyColumn" >
    	{foreach key=key value=item from=$target_fighter_result}
			<p><b>{$target_fighter_result[$key]}</b></p>
		{/foreach}
	</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="leftBuyColumnMini" nowrap><b>{$l_cmb_attacker_beams}</b></br>{$stage3_attacker_energy}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_fighters}</b></br>{$stage3_attacker_fighters}</td>
    <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_shields}</b></br>{$stage3_attacker_shields}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_torps}</b></br>{$stage3_attacker_torps}</td>
   <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_armor}</b></br>{$stage3_attacker_armor}</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr><td colspan="3" align="center" class="portfooter"><b><u>{$l_cmb_torp_exchange}</u></b></td></tr>
  <tr>
    <td class="leftBuyColumn" >
    	{foreach key=key value=item from=$attacker_torp_result}
			<p><b>{$attacker_torp_result[$key]}</b></p>
		{/foreach}
	</td>
    <td class="rightBuyColumn" >
    	{foreach key=key value=item from=$target_torp_result}
			<p><b>{$target_torp_result[$key]}</b></p>
		{/foreach}
	</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="leftBuyColumnMini" nowrap><b>{$l_cmb_attacker_beams}</b></br>{$end_attacker_energy}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_fighters}</b></br>{$end_attacker_fighters}</td>
    <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_shields}</b></br>{$end_attacker_shields}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_attacker_torps}</b></br>{$end_attacker_torps}</td>
   <td class="leftColumnMini" nowrap><b>{$l_cmb_attacker_armor}</b></br>{$end_attacker_armor}</td>
  </tr>
  <tr>
    <td class="leftBuyColumnMini" nowrap><b>{$l_cmb_target_beams}</b></br>{$end_target_beams}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_target_fighters}</b></br>{$end_target_fighters}</td>
    <td class="leftColumnMini" nowrap><b>{$l_cmb_target_shields}</b></br>{$end_target_shields}</td>
    <td class="rightBuyColumnMini" nowrap><b>{$l_cmb_target_torps}</b></br>{$end_target_torps}</td>
   <td class="leftColumnMini" nowrap><b>{$l_cmb_target_armor}</b></br>{$end_target_armor}</td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr><td colspan="3" align="center" class="portfooter"><b><u>{$l_cmb_attack_exchange_results}</u></b></td></tr>
  <tr>
    <td class="leftBuyColumn" >
    	{foreach key=key value=item from=$attacker_exchange_result}
			<p><b>{$attacker_exchange_result[$key]}</b></p>
		{/foreach}
	</td>
    <td class="rightBuyColumn" >
    	{foreach key=key value=item from=$target_exchange_result}
			<p><b>{$target_exchange_result[$key]}</b></p>
		{/foreach}
	</td>
  </tr>
  <tr><td colspan="5" align="center" class="portfooter">{$gotomain}</td></tr>
</table>
