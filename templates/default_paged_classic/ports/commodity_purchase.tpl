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

	h4 {
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
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.centerBuyColumn {
	background-color: #fff;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.leftBuyColumn {
	background-color: #333;
	margin: 0 auto 0 auto; /* Sets the margin properties for an element using shorthand notation (top, right, bottom, left) */
	text-align: center; /* Redefines the text alignment defined by the body element. */
	color: #000;
}
.portfooter {
	background-color: #eef6ed;
	border-top: solid 1px #8ab573; /* Sets the top border properties for an element using shorthand notation */
	padding: 10px 10px 10px 10px; /* Sets the padding properties for an element using shorthand notation (top, right, bottom, left) */
	color: #000;
	text-align: center;
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
    <td colspan="3" class="header"><h3>{$l_port_welcome}</h3><br>
    	<h4>{$l_trade_result}</h4></td>
  </tr>
  <tr>
    <td class="leftColumn" width="100"><img src="images/ports/big_{$buycommodity}.jpg" width="100" height="99" alt="sellcargo" /></td>
    <td class="leftColumn">{$youbought}:<br>{$buyamount} @ {$buyprice} {$l_credits}</td>
    <td class="rightColumn" width="200">	  <p>{$buycost} {$l_credits} {$l_cost}</p>
</td>
  </tr>
  <tr>
    <td colspan="3" class="portfooter"><b><font color="{$trade_color}">{$trade_result} </font></b> <font color="{$trade_color}"><b>{$trade_result_total} {$l_credits}</font></b></td>
  </tr>
</table>
<table width="600" border="1" align="center" cellpadding="5" cellspacing="0">

{foreach key=key value=item from=$commodity_name}
  <tr>
    <td class="leftBuyColumn" width="12"><img src="images/ports/{$commodity_name[$key]}.png" width="12" height="12" alt="sellcargo" /></td>
    <td class="centerBuyColumn"> {$commodity_boughtsold[$key]}: {$commodity_name[$key]|ucwords} {$commodity_total[$key]} @ {$commodity_value[$key]} {$l_credits}</td>
    <td class="rightBuyColumn" width="200">	 
	    {$sellcost[$key]} {$l_credits} {$l_profit}
</td>
  </tr>
{/foreach}
  <tr><td colspan="3" align="center" class="portfooter">{$l_trade_complete}
  	<br><br>{$gotomain}</td></tr>
</table>
</td></tr></table>
