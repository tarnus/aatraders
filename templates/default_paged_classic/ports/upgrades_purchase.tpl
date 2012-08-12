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
	text-align: left; /* Redefines the text alignment defined by the body element. */
	width: 200px;
	color: #000;
}
.rightBuyColumn {
	background-color: #eef6ed;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	width: 200px;
	color: #000;
}
.leftColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: left; /* Redefines the text alignment defined by the body element. */
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
	text-align: left; /* Redefines the text alignment defined by the body element. */
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
    <td class="header"><h3>{$l_port_welcome}</h3></td>
  </tr>
  <tr>
    <td class="leftColumn"><div align="center"><img src="images/ports/port_upgrades.gif" alt="spacedock" /><br><b>{$l_upgrade}</b></div></td>
</td>
  </tr>
  <tr>
    <td align="center" class="portfooter">{$l_trade_result}
    	<br><b><font color="red">{$l_cost} : {$trade_credits} {$l_credits}</font></b>
    </td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">

{foreach key=key value=item from=$techname}
  <tr>
    <td class="leftBuyColumn" nowrap>{$techname[$key]}</td>
    <td class="rightBuyColumn">
    	{if $not_tech[$key] == 0}
    		{$l_trade_upgraded}
    	{else}
    		{$l_trade_added}
    	{/if}
   	</td>
    <td class="centerColumn" nowrap>{$upgradeamount[$key]}</td>
  </tr>
{/foreach}

  <tr><td colspan="3" align="center" class="portfooter">
  	<a href="port.php">{$l_clickme}</a> {$l_port_returntospecial}
  	<br><br>{$gotomain}</td></tr>
</table>

</td></tr></table>
