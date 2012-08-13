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
		text-align: center; /* Centers the page content container in IE 5 browsers. */
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
 	span.red {
		color: #ff0000;
		font-size: 18px;
	}

   </style>

{/literal}

<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
  <tr>
    <td class="header"><h3>{$l_planet_combatpreview}</br>
    	<img src="templates/{$templatename}images/planet{$titleimage}.png" alt="" width="100" height="100"><br>
		{$planetname}</h3>
	</td>
  </tr>
	{if $isfedbounty == 0}
  		<tr><td colspan="3" align="center" class="portfooter"><b>{$l_by_nofedbounty}</b></td></tr>
	{else}
		<tr><td colspan="3" align="center" class="portfooter"><b><span class="red">{$l_by_fedbounty2}</span></b></td></tr>
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
  <tr>
    <td class="leftBuyColumn" >
    	{$l_planet_scn}
	   	{if $l_planet_att != ""}
    		<br><br>{$l_planet_att}
    	{/if}
 		{if $sofa_on && $planetowner != 3}
			<br><br><a href="planet.php?planet_id={$planet_id}&command=sofa">{$l_sofa}</a>
		{/if}
    </td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">
<tr><td colspan="5" align="center" class="portfooter">
	<a href="planet.php?planet_id={$planet_id}">{$l_clickme}</a> {$l_toplanetmenu}<BR><BR>
	{if $allow_ibank}
		{$l_ifyouneedplan} <A HREF="igb.php?planet_id={$planet_id}">{$l_igb_term}</A>.<BR><BR>
	{/if}
	<A HREF ="bounty.php">{$l_by_placebounty}</A><br>
	<br>
  	{$gotomain}</td></tr>
</table>
